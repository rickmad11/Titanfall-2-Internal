#pragma once

#define NETVAR(_name, type, table, name) inline type &_name() \
{ \
	static const int nOffset = MadFramework::NetVarManager::GetNetVar(table, name); \
	return *reinterpret_cast<type *>(reinterpret_cast<std::uintptr_t>(this) + nOffset); \
}

#define NETVAR_OFFSET(_name, type, offset) inline type &_name() \
{ \
	return *reinterpret_cast<type *>(reinterpret_cast<std::uintptr_t>(this) + offset); \
}

#define NETVAR_STRING(_name, type, table, name) inline type *_name() \
{ \
	static const int nOffset = MadFramework::NetVarManager::GetNetVar(table, name); \
	return reinterpret_cast<type *>(reinterpret_cast<std::uintptr_t>(this) + nOffset); \
}

namespace MadFramework::NetVarManager
{
	int GetNetVar(const char* TableName, const char* NetVarName);
	int NetVarOffset(RecvTable* pRecvTable, const char* NetVarName);
	void ConsoleDump();
}
