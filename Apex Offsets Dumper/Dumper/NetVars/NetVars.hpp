#pragma once
#include "../../Globals/Globals.hpp"
//CSGO Netvar Manager Tutorial - How to get Netvar offsets https://www.youtube.com/watch?v=hBA-_aAETX4
//https://guidedhacking.com/attachments/1574801031879-png.7827/
//https://guidedhacking.com/attachments/1574801050022-png.7828/

namespace NetVars
{
	inline std::ofstream m_file;
	inline nlohmann::json netjson;

	__forceinline void DumpTable(RecvTable* pRecv)//https://github.com/A5-/Gamerfood_CSGO/blob/master/csgo_internal/csgo_internal/NetVarManager.cpp
	{
		for (int i = 0; i < pRecv->GetPropsNum(); i++)
		{
			RecvProps* pRecvProp = pRecv->GetRecvProps(i);//pRecvPropOff[i];//pRecv->GetRecvProps()[i];

			if (!pRecvProp)
				continue;

			std::string pPropName = pRecvProp->GetPropName();

			if (pPropName.empty()|| pPropName.find(xorstr_("m_")) > 0)
				continue;

			std::stringstream toHex;
			toHex << xorstr_("[0x") << std::hex << std::uppercase << pRecvProp->GetOffset() << xorstr_("]");

			netjson =
			{
				{pRecv->GetRecvName(),
				{
					{pPropName, toHex.str()}
				}},
			};

			m_file << netjson << std::endl;

			if (!pRecvProp->GetRecvTable() || pRecvProp->GetRecvTable()->GetRecvName().find(xorstr_("DT_")) > 0)
				continue;

			DumpTable(pRecvProp->GetRecvTable());
		}
	}

	__forceinline void DumpNetvars()
	{
		printa->title<45>(xorstr_("#### Dumping Netvars ####"));

		m_file.open(xorstr_("dumps\\NetVars Dump.json"));

		/*GetAllClasses its the 13th index of CHLClient on Apex Legends*/
		auto IVClientEngineGetAllClasses = Memory::FindPattern(xorstr_("48 8B 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 89 74 24 20"));//4C 8B 1D ? ? ? ? 4D 85 DB 74 19 49 8B 4B 10 48 8B D3 E8 ? ? ? ? 85 C0 74 11 ------------- 48 8B 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 89 74 24 20

		if (IVClientEngineGetAllClasses)
			printa->print<found>(xorstr_("GetAllClasses {}\r\n"), reinterpret_cast<void*>(IVClientEngineGetAllClasses));
		else
			printa->print<notfound>(xorstr_("GetAllClasses\r\n"));

		CClientClass* IClientEngineGetAllClasses = Memory::RPM<CClientClass*>(Memory::moduleBase + IVClientEngineGetAllClasses);

		for (CClientClass* pClientClass = IClientEngineGetAllClasses; pClientClass != nullptr; pClientClass = pClientClass->GetNextClass())
		{
			if (!pClientClass || pClientClass->GetNetworkName().find(xorstr_("UnknownClientClass")) == 0)
				continue;

			auto pRecvTable = pClientClass->GetRecvTable();

			if (!pRecvTable || pRecvTable->GetRecvName().find(xorstr_("DT_")) > 0)
				continue;

			DumpTable(pRecvTable);
		}

		m_file.close();

		printa->print<found>(xorstr_("Netvars Dumped\r\n"));
	}
}