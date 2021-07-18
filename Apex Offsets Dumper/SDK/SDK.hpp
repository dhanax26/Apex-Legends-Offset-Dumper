#pragma once

class RecvTable;
class RecvProps
{
public:
	uint32_t GetType()
	{
		return Memory::RPM<uint32_t>((uint64_t)this + 0x0);
	}

	uint32_t GetOffset()
	{
		return Memory::RPM<uint32_t>((uint64_t)this + 0x4);
	}

	RecvTable* GetRecvTable()
	{
		return Memory::RPM<RecvTable*>((uint64_t)this + 0x20);
	}

	std::string GetPropName()
	{
		auto pPropNamePtr = Memory::RPM<uint64_t>((uint64_t)this + 0x28);

		if (!pPropNamePtr)
			return xorstr_("UnknownPropName");

		return Memory::ReadString(pPropNamePtr + 0x0);
	}

	bool IsOnArray()
	{
		return Memory::RPM<bool>((uint64_t)this + 0x30);
	}

	RecvProps* GetPropArray()
	{
		return Memory::RPM<RecvProps*>((uint64_t)this + 0x38);
	}

	void* GetProxy()
	{
		return Memory::RPM<void*>((uint64_t)this + 0x40);
	}

	uint32_t GetFlags()
	{
		return Memory::RPM<uint32_t>((uint64_t)this + 0x54);
	}

	uint32_t GetElements()
	{
		return Memory::RPM<uint32_t>((uint64_t)this + 0x5C);
	}
};

class RecvTable
{
public:
	/*RecvProps** GetRecvProps()
	{
		return Memory::RPM<RecvProps**>((uint64_t)this + 0x8);
	}*/

	RecvProps* GetRecvProps(uint32_t index)
	{
		auto pPropAddress = Memory::RPM<uint64_t>((uint64_t)this + 0x8 + 0x0);

		if (!pPropAddress)
			return nullptr;

		return Memory::RPM<RecvProps*>(pPropAddress + 0x8 * index);//reinterpret_cast<RecvProps*>(pPropAddress + 0x3C * index);
	}

	uint32_t GetPropsNum()
	{
		return Memory::RPM<uint32_t>((uint64_t)this + 0x10);
	}

	void* GetDecoder()
	{
		return Memory::RPM<void*>((uint64_t)this + 0x4C0);
	}

	std::string GetRecvName()
	{
		auto pRecvNamePtr = Memory::RPM<uint64_t>((uint64_t)this + 0x4C8);

		if (!pRecvNamePtr)
			return xorstr_("UnknownRecvName");

		return Memory::ReadString(pRecvNamePtr + 0x0);
	}
};


class CClientClass
{
public:
	void* ClientClassVTable()
	{
		return Memory::RPM<void*>((uint64_t)this + 0x0);
	}

	uint32_t ClientClassEvent()
	{
		return Memory::RPM<uint32_t>((uint64_t)this + 0x8);
	}

	std::string GetNetworkName()
	{
		auto pNetworkNamePtr = Memory::RPM<uint64_t>((uint64_t)this + 0x10);

		if (!pNetworkNamePtr)
			return xorstr_("UnknownClientClass");

		return Memory::ReadString(pNetworkNamePtr + 0x0);
	}

	RecvTable* GetRecvTable()
	{
		return Memory::RPM<RecvTable*>((uint64_t)this + 0x18);
	}

	CClientClass* GetNextClass()
	{
		return Memory::RPM<CClientClass*>((uint64_t)this + 0x20);
	}

	uint32_t GetClassID()
	{
		return Memory::RPM<uint32_t>((uint64_t)this + 0x28);
	}
};