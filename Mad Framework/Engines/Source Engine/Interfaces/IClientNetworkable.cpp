#include "pch.h"

ClientClass* IClientNetworkable::GetClientClass()
{
	return MadFramework::Memory::InvokeVTableFunction<ClientClass*>(this, SourceEngine::IClientNetworkable::Index::GetClientClass);
}