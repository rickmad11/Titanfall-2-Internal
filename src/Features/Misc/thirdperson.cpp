#include "pch.h"

#include "thirdperson.hpp"

static BYTE* client_module = nullptr;
static bool init = false;
static bool thirdperson_enabled = false;

safetyhook::InlineHook ih_cam_think;
__int64 __fastcall cam_think(BYTE* this_CInput)
{
    static uint8_t o_values[4] = 
    {
    	*(this_CInput + 1672LL * -1 + 24 + 117) , *(this_CInput + 1672LL * -1 + 24 + 132),
    	*(this_CInput + 24 + 117) , *(this_CInput + 24 + 132)
    };

    if (thirdperson_enabled && client_module)
    {
        if ((client_module + 0x2E43F80) && *(void**)(client_module + 0x2E43F80))
			*(void**)(client_module + 0x11BC4D0) = **(void***)(client_module + 0x2E43F80); //vtable of CCvar -> sv_cheats check bypass

        *(this_CInput + 1672LL * -1 + 24 + 117) = 1;
        *(this_CInput + 1672LL * -1 + 24 + 132) = 1;

        *(this_CInput + 24 + 117) = 1;
        *(this_CInput + 24 + 132) = 1;
    }
    else
    {
        *(this_CInput + 1672LL * -1 + 24 + 117) = o_values[0];
        *(this_CInput + 1672LL * -1 + 24 + 132) = o_values[1];

        *(this_CInput + 24 + 117) = o_values[2];
        *(this_CInput + 24 + 132) = o_values[3];
    }

    return ih_cam_think.fastcall<__int64>(this_CInput);
}

void EnableThirdPerson(bool shoulder, int shoulder_height)
{
	if (!init)
	{
        client_module = (BYTE*)GetModuleHandleW(L"client.dll");
        void* p_cam_think = MadFramework::Memory::SignatureScan("40 55 53 57 48 8D AC 24 ? ? ? ? 48 81 EC 00 02 00 00" ,'?', L"client.dll");
        ih_cam_think = safetyhook::create_inline(p_cam_think, cam_think);
        PLOG_INFO << "Hooked cam_think: " << p_cam_think;
		init = true;
	}

    if (!thirdperson_enabled)
    {
        ICvar* g_CVar = MadFramework::InterfaceManager::GetInterface<ICvar>();

        if (shoulder)
        {
            if (ConVar* c_thirdpersonshoulder_cvar = g_CVar->FindVar("c_thirdpersonshoulder"))
                c_thirdpersonshoulder_cvar->SetValue(1);

            if (ConVar* c_thirdpersonshoulderheight_cvar = g_CVar->FindVar("c_thirdpersonshoulderheight"))
                c_thirdpersonshoulderheight_cvar->SetValue(shoulder_height);
        }
        thirdperson_enabled = true;
        return;
    }

    static int s_shoulder_height = -1;

    if (s_shoulder_height != shoulder_height)
    {
        if (shoulder && thirdperson_enabled)
        {
            ICvar* g_CVar = MadFramework::InterfaceManager::GetInterface<ICvar>();

            if (ConVar* c_thirdpersonshoulder_cvar = g_CVar->FindVar("c_thirdpersonshoulder"))
                c_thirdpersonshoulder_cvar->SetValue(1);

            if (ConVar* c_thirdpersonshoulderheight_cvar = g_CVar->FindVar("c_thirdpersonshoulderheight"))
                c_thirdpersonshoulderheight_cvar->SetValue(shoulder_height);
        }
        s_shoulder_height = shoulder_height;
    }
}

void DisableThirdPerson(bool shoulder)
{
    if (thirdperson_enabled)
    {
        ICvar* g_CVar = MadFramework::InterfaceManager::GetInterface<ICvar>();
        thirdperson_enabled = false;

        if (shoulder)
        {
            if (ConVar* c_thirdpersonshoulder_cvar = g_CVar->FindVar("c_thirdpersonshoulder"))
                c_thirdpersonshoulder_cvar->SetValue(0);

            if (ConVar* c_thirdpersonshoulderheight_cvar = g_CVar->FindVar("c_thirdpersonshoulderheight"))
                c_thirdpersonshoulderheight_cvar->SetValue(0);
        }
    }
}

void RemoveCamThinkHook()
{
    if (ih_cam_think.enabled())
    {
        std::expected<void, safetyhook::InlineHook::Error> hook_status = ih_cam_think.disable();

        if (!hook_status.has_value())
        {
            safetyhook::InlineHook::Error safetyError = hook_status.error();

            PLOG_ERROR << "Fatal Error unhooking cam_think";
            PLOG_ERROR << "Error Type: " << safetyError.type;
            PLOG_ERROR << "IP: " << safetyError.ip;
        }
    }
}