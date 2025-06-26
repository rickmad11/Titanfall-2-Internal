#include "pch.h"

ConVar* ICvar::FindVar(const char* var_name)
{
	return MadFramework::Memory::InvokeVTableFunction<ConVar*>(this, 16, var_name);
}

ConCommand* ICvar::FindCommand(const char* name)
{
	return MadFramework::Memory::InvokeVTableFunction<ConCommand*>(this, 13, name);
}

const ConCommand* ICvar::FindCommand_c(const char* name)
{
	return MadFramework::Memory::InvokeVTableFunction<ConCommand*>(this, 14, name);
}
