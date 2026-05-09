#pragma once

namespace MadFramework::SourceEngineHooks
{
	inline safetyhook::InlineHook ihHudUpdate{};
	void __fastcall HudUpdate(void* self, bool bActive);

	inline safetyhook::InlineHook ihCreateMove{};
	bool __fastcall CreateMove(void* pIClientMode, float input_sample_frametime, class CUserCmd* pCUserCmd, bool game_active);

	inline safetyhook::InlineHook ihFindMDL;
	void* __fastcall FindMDL(void* _this, studiohdr_t* studio, int flag);
}