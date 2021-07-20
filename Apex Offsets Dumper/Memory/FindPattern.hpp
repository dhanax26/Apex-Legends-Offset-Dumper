#pragma once

namespace Memory
{
	inline HANDLE hProcess;
	inline uint64_t moduleBase, modulesize;
	inline int found, missed = 0;
	inline MODULEENTRY32 ModuleEntry;

	__forceinline void GetModule(const char* modName, DWORD procId) 
	{
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

		if (hSnapShot != INVALID_HANDLE_VALUE)
		{
			ModuleEntry.dwSize = sizeof(ModuleEntry);
			if (Module32First(hSnapShot, &ModuleEntry))
			{
				do 
				{
					if (!strcmp(ModuleEntry.szModule, modName))
					{
						CloseHandle(hSnapShot);
						modulesize = ModuleEntry.modBaseSize;
						moduleBase = reinterpret_cast<uint64_t>(ModuleEntry.modBaseAddr);
						return;
					}
				} 
				while (Module32Next(hSnapShot, &ModuleEntry));
			}
		}
	}

	template<typename T> T RPM(SIZE_T Address)
	{
		T buffer; ReadProcessMemory(hProcess, (void*)Address, &buffer, sizeof(T), nullptr);
		return buffer;
	}

	__forceinline std::string ReadString(uint64_t Address)
	{
		char buffer[100];
		ReadProcessMemory(Memory::hProcess, (void*)Address, &buffer, sizeof(buffer), NULL);
		return buffer;
	}

	__forceinline std::string GetOffset(uint64_t Address, int delimiter = 6, int offset = 0)//Shit way of doing it
	{
		auto integerbuffer = 0;
		ReadProcessMemory(hProcess, (void*)Address, &integerbuffer, sizeof(int), NULL);

		if (!integerbuffer)
			return xorstr_("");

		std::stringstream conver;
		conver << xorstr_("0x") << std::hex << std::uppercase << integerbuffer + offset;

		auto Offset = conver.str();

		if (Offset.empty())
			return xorstr_("not found");

		Offset.resize(delimiter);

		return Offset;
	}

	__forceinline uint64_t find_pattern(const char* pattern, const char* mask, uint64_t begin, uint64_t end, HANDLE hProc)//https://guidedhacking.com/threads/external-signature-pattern-scan-issues.12618/?view=votes#post-73200
	{
		auto scan = [](const char* pattern, const char* mask, char* begin, unsigned int size) -> char*
		{
			size_t patternLen = strlen(mask);
			for (unsigned int i = 0; i < size - patternLen; i++)
			{
				bool found = true;
				for (unsigned int j = 0; j < patternLen; j++) {
					if (mask[j] != '?' && pattern[j] != *(begin + i + j))
					{
						found = false;
						break;
					}
				}

				if (found)
					return (begin + i);
			}
			return nullptr;
		};

		uint64_t match = NULL;
		SIZE_T bytesRead;
		DWORD oldprotect;
		char* buffer = nullptr;
		MEMORY_BASIC_INFORMATION mbi = { 0 };

		uint64_t curr = begin;

		for (uint64_t curr = begin; curr < end; curr += mbi.RegionSize)
		{
			if (!VirtualQueryEx(hProc, (void*)curr, &mbi, sizeof(mbi)))
				continue;

			if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS)
				continue;

			buffer = new char[mbi.RegionSize];

			ReadProcessMemory(hProc, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);

			char* internalAddr = scan(pattern, mask, buffer, (unsigned int)bytesRead);

			if (internalAddr != nullptr)
			{
				match = curr + (uint64_t)(internalAddr - buffer);
				break;
			}
		}
		delete[] buffer;
		return match;
	}

	__forceinline uintptr_t FindPattern(const char* sig)//https://guidedhacking.com/threads/universal-pattern-signature-parser.9588/
	{
		char pattern[100];
		char mask[100];

		char lastChar = ' ';
		unsigned int j = 0;

		for (unsigned int i = 0; i < strlen(sig); i++) {
			if ((sig[i] == '?' || sig[i] == '*') && (lastChar != '?' && lastChar != '*'))
			{
				pattern[j] = mask[j] = '?';
				j++;
			}

			else if (isspace(lastChar))
			{
				pattern[j] = lastChar = (char)strtol(&sig[i], 0, 16);
				mask[j] = 'x';
				j++;
			}
			lastChar = sig[i];
		}
		pattern[j] = mask[j] = '\0';

		auto current_address = find_pattern(pattern, mask, moduleBase, moduleBase + modulesize, hProcess) + 0x3;

		if (current_address <= 0x5)
		{
			missed++;
			return 0x0;
		}

		found++;
		return current_address + RPM<int32_t>(current_address) + 4 - moduleBase;
	}

	void* PatternScan(char* base, size_t size, char* pattern, char* mask)//https://guidedhacking.com/threads/external-pattern-scanning.8207/
	{
		size_t patternLength = strlen(mask);

		for (unsigned int i = 0; i < size - patternLength; i++)
		{
			bool found = true;
			for (unsigned int j = 0; j < patternLength; j++)
			{
				if (mask[j] != '?' && pattern[j] != *(base + i + j))
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				return (void*)(base + i);
			}
		}
		return nullptr;
	}

	void* PatternScanEx(char* pattern, char* mask)//https://guidedhacking.com/threads/external-pattern-scanning.8207/
	{
		uint64_t currentChunk = moduleBase;
		uint64_t end = moduleBase + modulesize;
		SIZE_T bytesRead;

		while (currentChunk < end)
		{
			char buffer[4096];

			DWORD oldprotect;
			ReadProcessMemory(hProcess, (void*)currentChunk, &buffer, sizeof(buffer), &bytesRead);

			if (bytesRead == 0)
				return nullptr;

			void* internalAddress = PatternScan((char*)&buffer, bytesRead, pattern, mask);

			if (internalAddress != nullptr)
			{
				//calculate from internal to external
				uint64_t offsetFromBuffer = (uint64_t)internalAddress - (uint64_t)&buffer;
				return (void*)(currentChunk + offsetFromBuffer);
			}
			else
				currentChunk = currentChunk + bytesRead;
		}
		return nullptr;
	}

	__forceinline bool Initialize()
	{
		HWND hWindow = FindWindowA(NULL, xorstr_("Apex Legends"));

		if (hWindow)
		{
			DWORD ProcessId = 0x0;

			GetWindowThreadProcessId(hWindow, &ProcessId);

			if (ProcessId)
			{
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcessId);

				if (hProcess)
					GetModule(xorstr_("EasyAntiCheat_launcher.exe"), ProcessId);

				if (moduleBase)
				{
					Management::CreateDataFolder();
					return true;
				}
			}
		}
		return false;
	}
}