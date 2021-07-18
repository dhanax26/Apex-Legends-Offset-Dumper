#pragma once

namespace Memory
{
	inline HANDLE hProcess;
	inline uint64_t moduleBase, size;
	inline int found, missed = 0;

	__forceinline void GetModule(const char* modName, DWORD procId) 
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

		if (hSnap != INVALID_HANDLE_VALUE) 
		{
			MODULEENTRY32 modEntry;
			modEntry.dwSize = sizeof(modEntry);
			if (Module32First(hSnap, &modEntry)) 
			{
				do 
				{
					if (!strcmp(modEntry.szModule, modName)) 
					{
						CloseHandle(hSnap);
						size = modEntry.modBaseSize;
						moduleBase = (uint64_t)modEntry.modBaseAddr;
						return;
					}
				} 
				while (Module32Next(hSnap, &modEntry));
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

			if (VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect)) 
			{
				ReadProcessMemory(hProc, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
				VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);

				char* internalAddr = scan(pattern, mask, buffer, (unsigned int)bytesRead);

				if (internalAddr != nullptr) 
				{
					match = curr + (uint64_t)(internalAddr - buffer);
					break;
				}
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

		auto current_address = find_pattern(pattern, mask, moduleBase, moduleBase + size, hProcess) + 0x3;

		if (current_address <= 0x5)
		{
			missed++;
			return 0x0;
		}

		found++;
		return current_address + RPM<int32_t>(current_address) + 4 - moduleBase;
	}

	__forceinline bool Initialize()
	{
		HWND hWindow = FindWindowA(NULL, xorstr_("Apex Legends"));

		if (hWindow)
		{
			DWORD dwPID; GetWindowThreadProcessId(hWindow, &dwPID);

			if (dwPID)
			{
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, dwPID);

				if (hProcess)
					GetModule(xorstr_("EasyAntiCheat_launcher.exe"), dwPID);

				if (moduleBase)
					return true;
			}
		}
		return false;
	}
}