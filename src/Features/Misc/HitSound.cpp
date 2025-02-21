#include "pch.h"

#include "HitSound.h"

#include "HitSoundFiles.h"
#include "Menu/Menu.h"

char __fastcall OnHitUserMessageHook(void* pData, int message_flag, void* pMessageBuffer)
{
	if (message_flag == 0x3A && MadFramework::Menu::state.mHitSounds) // 0x3A Entity hit flag
	{
		MadFramework::Menu::MenuState menu_state = MadFramework::Menu::state;
		MadRenderer::DX11::Get()->GetAudioManager()->PlaySoundEffect(*sound_data.SelectedSoundID[menu_state.mSelectedHitSound], menu_state.mHitSoundVolume, menu_state.mHitSoundPitch);
	}

	return ihOnHitUserMessageHook.fastcall<char>(pData, message_flag, pMessageBuffer);
}

bool EnableUserMessageHook()
{
	ihOnHitUserMessageHook = safetyhook::create_inline(MadFramework::Memory::SignatureScan("4C 8B DC 57 48 83 EC 60", '?', L"client.dll"), OnHitUserMessageHook);

	PLOG_INFO << "Hooked OnHitUserMessage: " << ihOnHitUserMessageHook.original<void*>();

	return ihOnHitUserMessageHook.enabled();
}

void DisableUserMessageHook()
{
	std::expected<void, safetyhook::InlineHook::Error> hook_status = ihOnHitUserMessageHook.disable();

	if (!hook_status.has_value())
	{
		safetyhook::InlineHook::Error safetyError = hook_status.error();

		PLOG_ERROR << "Fatal Error unhooking OnHitUserMessage";
		PLOG_ERROR << "Error Type: " << safetyError.type;
		PLOG_ERROR << "IP: " << safetyError.ip;
	}
}

void InitSounds()
{
	MadRenderer::AudioManager* p_audio_manager = MadRenderer::DX11::Get()->GetAudioManager();
	p_audio_manager->InitializeAudioManager();

	sound_data.id_RustHS = p_audio_manager->AddSoundEffect(RustHSSoundFile, sizeof(RustHSSoundFile));
	sound_data.id_Skeet = p_audio_manager->AddSoundEffect(SkeetSoundFile, sizeof(SkeetSoundFile));
	sound_data.id_CoD = p_audio_manager->AddSoundEffect(CoDSoundFile, sizeof(CoDSoundFile));
}
