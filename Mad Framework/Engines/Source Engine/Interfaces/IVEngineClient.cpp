#include "pch.h"

int IVEngineClient::GetLocalPlayer()
{
	return MadFramework::Memory::InvokeVTableFunction<int>(this, SourceEngine::IVEngineClient::Index::GetLocalPlayer);
}

bool IVEngineClient::GetPlayerInfo(int ent_num, player_info_t* pinfo)
{
	return MadFramework::Memory::InvokeVTableFunction<bool>(this, SourceEngine::IVEngineClient::Index::GetPlayerInfo, ent_num, pinfo);
}

bool IVEngineClient::IsInGame(void)
{
	return MadFramework::Memory::InvokeVTableFunction<bool>(this, SourceEngine::IVEngineClient::Index::IsInGame);
}