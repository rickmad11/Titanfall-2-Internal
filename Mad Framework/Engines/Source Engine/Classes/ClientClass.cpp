#include "pch.h"

#include "ClientClass.h"

const char* ClientClass::GetName()
{
	return *reinterpret_cast<const char**>(reinterpret_cast<BYTE*>(this) + SourceEngine::ClientClass::Offset::GetName);
}

int ClientClass::GetClassID()
{
	return *reinterpret_cast<int*>(reinterpret_cast<BYTE*>(this) + SourceEngine::ClientClass::Offset::GetClassID);
}
