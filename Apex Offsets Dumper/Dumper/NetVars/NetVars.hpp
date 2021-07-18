#pragma once
#include "../../Globals/Globals.hpp"

//CSGO Netvar Manager Tutorial - How to get Netvar offsets https://www.youtube.com/watch?v=hBA-_aAETX4
//https://guidedhacking.com/attachments/1574801031879-png.7827/
//https://guidedhacking.com/attachments/1574801050022-png.7828/

namespace NetVars
{
	inline std::ofstream m_file;

	__forceinline void DumpTable(RecvTable* pRecv, int depth)//https://github.com/A5-/Gamerfood_CSGO/blob/master/csgo_internal/csgo_internal/NetVarManager.cpp
	{
		std::string pre(xorstr_(""));

		for (int i = 0; i < depth; i++)
			pre.append(xorstr_("\t"));

		m_file << pre << pRecv->GetRecvName() << xorstr_("\n");

		for (int i = 0; i < pRecv->GetPropsNum(); i++)
		{
			RecvProps* pRecvProp = pRecv->GetRecvProps(i);//pRecvPropOff[i];//pRecv->GetRecvProps()[i];

			if (!pRecvProp)
				continue;

			std::string pPropName = pRecvProp->GetPropName();

			if (pPropName.empty() || pPropName.find(xorstr_("m_")) > 0)//|| pPropName.find(xorstr_("baseclass")) == 0 || pPropName.find(xorstr_("0")) == 0 || pPropName.find(xorstr_("1")) == 0 || pPropName.find(xorstr_("2")) == 0 || pPropName.find(xorstr_("m_")) > 0)
				continue;

			m_file << pre << xorstr_("\t ") << pPropName << xorstr_(" ")
				<< std::setfill('_') << std::setw(60 - pPropName.length() - (depth * 4))
				<< xorstr_("[0x") << std::setfill('0') << std::setw(8) << std::hex
				<< std::uppercase << pRecvProp->GetOffset() << xorstr_("]\n");

			if (!pRecvProp->GetRecvTable() || pRecvProp->GetRecvTable()->GetRecvName().find(xorstr_("DT_")) > 0)
				continue;

			DumpTable(pRecvProp->GetRecvTable(), depth + 1);
		}
	}

	__forceinline void DumpNetvars()
	{
		printa->title<45>(xorstr_("#### Dumping Netvars ####"));

		m_file.open(xorstr_("dumps\\NetVars Dump.txt"));

		Management::LogToFile(m_file, xorstr_("#### NetVar Dumper ####\n"));

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

			//printf("ClientClass: 0x%p | Name: %s | Recv: %s\r\n", pClientClass, pClientClass->GetNetworkName().c_str(), pRecvTable->GetRecvName().c_str());

			DumpTable(pRecvTable, 0);
		}

		m_file.close();

		printa->print<found>(xorstr_("Netvars Dumped\r\n"));
	}
}