#pragma once

namespace MadFramework::SourceEngineHooks
{
	inline safetyhook::InlineHook ihHudUpdate{};
	void __fastcall HudUpdate(void* self, bool bActive);

	inline safetyhook::InlineHook ihCreateMove{};
	bool __fastcall CreateMove(void* pIClientMode, float input_sample_frametime, class CUserCmd* pCUserCmd, bool game_active);
}