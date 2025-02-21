#include "pch.h"

ClientClass* IBaseClientDLL::GetAllClasses()
{
	return MadFramework::Memory::InvokeVTableFunction<ClientClass*>(this, SourceEngine::IBaseClientDLL::Index::GetAllClasses);
}
