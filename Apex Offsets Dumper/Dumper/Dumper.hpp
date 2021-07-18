#pragma once
#include "../Globals/Globals.hpp"
#include "NetVars/NetVars.hpp"

namespace Dumper
{
	inline std::ofstream m_file;

	__forceinline void DumpInterfaces()
	{
		m_file.open(xorstr_("dumps\\Offsets Dump.txt"));

		Management::LogToFile(m_file, xorstr_("#### Interfaces Dump ####"));

		printa->title<45>(xorstr_("#### Dumping Interfaces ####"));

		auto ClientRenderTargets = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? 48 85 C9 74 33 48 8B 01"));

		if (ClientRenderTargets)
			printa->print<found>(xorstr_("ClientRenderTargets {}\r\n"), reinterpret_cast<void*>(ClientRenderTargets));
		else
			printa->print<notfound>(xorstr_("ClientRenderTargets\r\n"));

		Management::LogToFile(m_file, xorstr_("[ClientRenderTargets]"), ClientRenderTargets);

		auto IBaseClientDLL = Memory::FindPattern(xorstr_("48 8D 0D ? ? ? ? 48 8B 05 ? ? ? ? 4C 8D 05 ? ? ? ?"));

		if (IBaseClientDLL)
			printa->print<found>(xorstr_("IBaseClientDLL {}\r\n"), reinterpret_cast<void*>(IBaseClientDLL));
		else
			printa->print<notfound>(xorstr_("IBaseClientDLL\r\n"));

		Management::LogToFile(m_file, xorstr_("[IBaseClientDLL]"), IBaseClientDLL);

		auto IClientEntityList = Memory::FindPattern(xorstr_("4C 8B 05 ? ? ? ? 48 8D 0D ? ? ? ? 33 DB 4C 8D 2D ? ? ? ? 33 FF 0F 1F 40 00"));

		if (IClientEntityList)
			printa->print<found>(xorstr_("IClientEntityList {}\r\n"), reinterpret_cast<void*>(IClientEntityList));
		else
			printa->print<notfound>(xorstr_("IClientEntityList\r\n"));

		Management::LogToFile(m_file, xorstr_("[IClientEntityList]"), IClientEntityList);

		auto CPrediction = Memory::FindPattern(xorstr_("48 89 15 ? ? ? ? 48 3B C1"));

		if (CPrediction)
			printa->print<found>(xorstr_("CPrediction {}\r\n"), reinterpret_cast<void*>(CPrediction));
		else
			printa->print<notfound>(xorstr_("CPrediction\r\n"));

		Management::LogToFile(m_file, xorstr_("[CPrediction]"), CPrediction);

		auto IVModelRender = Memory::FindPattern(xorstr_("4C 8B 05 ? ? ? ? 48 8D 35 ? ? ? ?"));

		if (IVModelRender)
			printa->print<found>(xorstr_("IVModelRender {}\r\n"), reinterpret_cast<void*>(IVModelRender));
		else
			printa->print<notfound>(xorstr_("IVModelRender\r\n"));

		Management::LogToFile(m_file, xorstr_("[IVModelRender]"), IVModelRender);

		auto VGUISystem = Memory::FindPattern(xorstr_("48 8B 05 ? ? ? ? 4C 8D 3D ? ? ? ? 48 8B 50 10"));

		if (VGUISystem)
			printa->print<found>(xorstr_("VGUISystem {}\r\n"), reinterpret_cast<void*>(VGUISystem));
		else
			printa->print<notfound>(xorstr_("VGUISystem\r\n"));

		Management::LogToFile(m_file, xorstr_("[VGUISystem]"), VGUISystem, true);
	}

	__forceinline void DumpClasses()
	{
		Management::LogToFile(m_file, xorstr_("#### Classes Dump ####"));

		printa->title<46>(xorstr_("#### Dumping Classes ####"));

		auto IVRenderView = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? 45 8B 40 04"));

		if (IVRenderView)
			printa->print<found>(xorstr_("IVRenderView {}\r\n"), reinterpret_cast<void*>(IVRenderView));
		else
			printa->print<notfound>(xorstr_("IVRenderView\r\n"));

		Management::LogToFile(m_file, xorstr_("[IVRenderView]"), IVRenderView);

		auto IVDebugOverlay = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? F3 41 0F 5C F2"));

		if (IVDebugOverlay)
			printa->print<found>(xorstr_("IVDebugOverlay {}\r\n"), reinterpret_cast<void*>(IVDebugOverlay));
		else
			printa->print<notfound>(xorstr_("IVDebugOverlay\r\n"));

		Management::LogToFile(m_file, xorstr_("[IVDebugOverlay]"), IVDebugOverlay);

		auto IVModelInfoClient = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? C7 46 28 FF FF FF FF"));

		if (IVModelInfoClient)
			printa->print<found>(xorstr_("IVModelInfoClient {}\r\n"), reinterpret_cast<void*>(IVModelInfoClient));
		else
			printa->print<notfound>(xorstr_("IVModelInfoClient\r\n"));

		Management::LogToFile(m_file, xorstr_("[IVModelInfoClient]"), IVModelInfoClient);

		auto IVEngineClient = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? 4C 8D 84 24 40 01 00 00"));

		if (IVEngineClient)
			printa->print<found>(xorstr_("IVEngineClient {}\r\n"), reinterpret_cast<void*>(IVEngineClient));
		else
			printa->print<notfound>(xorstr_("IVEngineClient\r\n"));

		Management::LogToFile(m_file, xorstr_("[IVEngineClient]"), IVEngineClient);

		auto IVEngineTrace = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? 89 84 24 A4 00 00 00"));

		if (IVEngineTrace)
			printa->print<found>(xorstr_("IVEngineTrace {}\r\n"), reinterpret_cast<void*>(IVEngineTrace));
		else
			printa->print<notfound>(xorstr_("IVEngineTrace\r\n"));

		Management::LogToFile(m_file, xorstr_("[IVEngineTrace]"), IVEngineTrace);

		auto INetworkStringTable = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? 48 8B 01 FF 50 50 3D FF FF 00 00 74 06 89 83 80 0A 00 00"));

		if (INetworkStringTable)
			printa->print<found>(xorstr_("INetworkStringTable {}\r\n"), reinterpret_cast<void*>(INetworkStringTable));
		else
			printa->print<notfound>(xorstr_("INetworkStringTable\r\n"));

		Management::LogToFile(m_file, xorstr_("[INetworkStringTable]"), INetworkStringTable);

		auto CNetworkU64Table = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? 4C 8D 45 67 48 C7 45 67 00 00 00 00"));

		if (CNetworkU64Table)
			printa->print<found>(xorstr_("CNetworkU64Table {}\r\n"), reinterpret_cast<void*>(CNetworkU64Table));
		else
			printa->print<notfound>(xorstr_("CNetworkU64Table\r\n"));

		Management::LogToFile(m_file, xorstr_("[CNetworkU64Table]"), INetworkStringTable);
	
		auto CInput = Memory::FindPattern(xorstr_("4C 8B 05 ? ? ? ? 48 8D 0D ? ? ? ? 49 8B 80 80 00 00 00"));

		if (CInput)
			printa->print<found>(xorstr_("CInput {}\r\n"), reinterpret_cast<void*>(CInput));
		else
			printa->print<notfound>(xorstr_("CInput\r\n"));

		Management::LogToFile(m_file, xorstr_("[CInput]"), CInput);

		auto CEngine = Memory::FindPattern(xorstr_("48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B6 C8"));

		if (CEngine)
			printa->print<found>(xorstr_("CEngine {}\r\n"), reinterpret_cast<void*>(CEngine));
		else
			printa->print<notfound>(xorstr_("CEngine\r\n"));

		Management::LogToFile(m_file, xorstr_("[CEngine]"), CEngine, true);
	}

	__forceinline void DumpOffsets()
	{
		Management::LogToFile(m_file, xorstr_("#### Offsets Dump ####"));

		printa->title<46>(xorstr_("#### Dumping Offsets ####"));

		auto ISwapChain = Memory::FindPattern(xorstr_("48 39 35 ? ? ? ? 0F 84 ? ? ? ? 40 38 35 ? ? ? ?"));

		if (ISwapChain)
			printa->print<found>(xorstr_("ISwapChain {}\r\n"), reinterpret_cast<void*>(ISwapChain));
		else
			printa->print<notfound>(xorstr_("ISwapChain\r\n"));

		Management::LogToFile(m_file, xorstr_("[ISwapChain]"), ISwapChain);

		auto cl_entitylist = Memory::FindPattern(xorstr_("4C 8D 05 ? ? ? ? 4C 8B 25 ? ? ? ?"));

		if (cl_entitylist)
			printa->print<found>(xorstr_("cl_entitylist {}\r\n"), reinterpret_cast<void*>(cl_entitylist));
		else
			printa->print<notfound>(xorstr_("cl_entitylist\r\n"));

		Management::LogToFile(m_file, xorstr_("[cl_entitylist]"), cl_entitylist);

		auto LocalPlayer = Memory::FindPattern(xorstr_("48 8B 05 ? ? ? ? 48 0F 44 C7"));//refence: PlayerRunCommand_Prediction

		if (LocalPlayer)
			printa->print<found>(xorstr_("LocalPlayer {}\r\n"), reinterpret_cast<void*>(LocalPlayer));
		else
			printa->print<notfound>(xorstr_("LocalPlayer\r\n"));

		Management::LogToFile(m_file, xorstr_("[LocalPlayer]"), LocalPlayer);

		auto GlobalVars = Memory::FindPattern(xorstr_("4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 41 FF D1"));//refence: Client.dll Init() in library client failed.

		if (GlobalVars)
			printa->print<found>(xorstr_("GlobalVars {}\r\n"), reinterpret_cast<void*>(GlobalVars));
		else
			printa->print<notfound>(xorstr_("GlobalVars\r\n"));

		Management::LogToFile(m_file, xorstr_("[GlobalVars]"), GlobalVars);

		auto NameList = Memory::FindPattern(xorstr_("48 8D 05 ? ? ? ? FF CA"));

		if (NameList)
			printa->print<found>(xorstr_("NameList {}\r\n"), reinterpret_cast<void*>(NameList));
		else
			printa->print<notfound>(xorstr_("NameList\r\n"));

		Management::LogToFile(m_file, xorstr_("[NameList]"), NameList);

		auto ViewRender = Memory::FindPattern(xorstr_("48 8B 0D ? ? ? ? 48 8B 01 FF 50 40 48 8B 0D ? ? ? ?"));//refence: _rt_FullFrameFB

		if (ViewRender)
			printa->print<found>(xorstr_("ViewRender {}\r\n"), reinterpret_cast<void*>(ViewRender));
		else
			printa->print<notfound>(xorstr_("ViewRender\r\n"));

		Management::LogToFile(m_file, xorstr_("[ViewRender]"), ViewRender);

		auto ViewMatrix = Memory::FindPattern(xorstr_("48 8D 0D ? ? ? ? 48 8B D3 E8 ? ? ? ? 8B 05 ? ? ? ? 83 C8 08"));

		if (ViewMatrix)
			printa->print<found>(xorstr_("ViewMatrix {}\r\n"), reinterpret_cast<void*>(ViewMatrix));
		else
			printa->print<notfound>(xorstr_("ViewMatrix\r\n"));

		Management::LogToFile(m_file, xorstr_("[ViewMatrix]"), ViewMatrix);

		auto ClientState = Memory::FindPattern(xorstr_("48 8D 0D ? ? ? ? E8 ? ? ? ? FF 15 ? ? ? ? 89 05 ? ? ? ?"));//refence: Out of thread local storage!

		if (ClientState)
			printa->print<found>(xorstr_("ClientState {}\r\n"), reinterpret_cast<void*>(ClientState));
		else
			printa->print<notfound>(xorstr_("ClientState\r\n"));

		Management::LogToFile(m_file, xorstr_("[ClientState]"), ClientState);

		auto LevelName = Memory::FindPattern(xorstr_("48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC 83 3D ? ? ? ? ?"));//refence: dedicated - mp_lobby

		if (LevelName)
			printa->print<found>(xorstr_("LevelName {}\r\n"), reinterpret_cast<void*>(LevelName));
		else
			printa->print<notfound>(xorstr_("LevelName\r\n"));

		Management::LogToFile(m_file, xorstr_("[LevelName]"), LevelName, true);

		auto LastVisibleTime = Memory::PatternScanEx(xorstr_("\x8B\x8F\xCC\x1A\x00\x00"), xorstr_("xxxxxx"));//refence: lastVisibleTime

		if (LastVisibleTime)
		{
			auto Offset = Memory::GetOffset(reinterpret_cast<uint64_t>(LastVisibleTime));
			printa->print<found>(xorstr_("LastVisibleTime {}\r\n"), Offset);
		}
		else
			printa->print<notfound>(xorstr_("LastVisibleTime\r\n"));


		m_file.close();
	}

	__forceinline void DumperThread()
	{
		DumpInterfaces();
		DumpClasses();
		DumpOffsets();
		NetVars::DumpNetvars();
	}
}