#include "pch.h"

IClientNetworkable* IClientEntityList::GetClientNetworkable(int entnum)
{
	return MadFramework::Memory::InvokeVTableFunction<IClientNetworkable*>(this, SourceEngine::IClientEntityList::Index::GetClientNetworkable, entnum);
}

IClientEntity* IClientEntityList::GetClientEntity(int entnum)
{
	return MadFramework::Memory::InvokeVTableFunction<IClientEntity*>(this, SourceEngine::IClientEntityList::Index::GetClientEntity, entnum);
}

int IClientEntityList::NumberOfEntities(bool bIncludeNonNetworkable)
{
	return MadFramework::Memory::InvokeVTableFunction<int>(this, SourceEngine::IClientEntityList::Index::NumberOfEntities, bIncludeNonNetworkable);
}

int IClientEntityList::GetHighestEntityIndex()
{
	return MadFramework::Memory::InvokeVTableFunction<int>(this, SourceEngine::IClientEntityList::Index::GetHighestEntity);
}

void IClientEntityList::SetMaxEntities(int maxents)
{
	return MadFramework::Memory::InvokeVTableFunction<void>(this, SourceEngine::IClientEntityList::Index::SetMaxEntities, maxents);
}

int IClientEntityList::GetMaxEntities()
{
	return MadFramework::Memory::InvokeVTableFunction<int>(this, SourceEngine::IClientEntityList::Index::GetMaxEntities);
}

