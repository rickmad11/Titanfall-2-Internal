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

void IVEngineClient::SendClientMessage(const char* message) noexcept
{
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC 50 01 00 00 engine.dll
	return MadFramework::Memory::InvokeVTableFunction<void>(this, SourceEngine::IVEngineClient::Index::ClientSendMessage, message, 1, false);
}