#include "pch.h"

ConVar* ICvar::FindVar(const char* var_name)
{
	return (ConVar*) ((MadFramework::Memory::InvokeVTableFunction<BYTE*>(this, 11, var_name)) + 0x8);
}

ConCommand* ICvar::FindCommand(const char* name)
{
	return MadFramework::Memory::InvokeVTableFunction<ConCommand*>(this, 13, name);
}

const ConCommand* ICvar::FindCommand_c(const char* name)
{
	return MadFramework::Memory::InvokeVTableFunction<ConCommand*>(this, 14, name);
}
