#pragma once

struct SoundIDs
{
	int id_RustHS = 0;
	int id_Skeet = 0;
	int id_CoD = 0;

	int* SelectedSoundID[3] = {&id_RustHS, &id_Skeet, &id_CoD};

}inline sound_data {};

void InitSounds();

inline safetyhook::InlineHook ihOnHitUserMessageHook{};
char __fastcall OnHitUserMessageHook(void* a1, int a2, void* a3);

bool EnableUserMessageHook();
void DisableUserMessageHook();