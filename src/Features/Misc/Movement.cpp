#include "pch.h"

#include "Movement.hpp"

static safetyhook::InlineHook ihCmdSend;
static bool lg_should_run = false, lg_fake_down = false, lg_fake_up = false;
__int64 __fastcall CmdSend(__int64* a1, CUserCmd* a2, void* a3)
{
    if (lg_should_run)
    {
        float originalPitch = a2->m_worldViewAngles.x;
        float originalYaw = a2->m_worldViewAngles.y;

        static std::mt19937 generator(std::random_device{}());
        static std::uniform_int_distribution<int> distribution_yaw(-20, 20);
        static std::uniform_int_distribution<int> distribution_pitch(-85, 89);

        float yawOffset = static_cast<float>(distribution_yaw(generator));

        if (lg_fake_down)
            a2->m_worldViewAngles.x = 85.0f;

        if (!lg_fake_down && lg_fake_up)
            a2->m_worldViewAngles.x = -85.0f;

        if (lg_fake_down && lg_fake_up)
            a2->m_worldViewAngles.x = static_cast<float>(distribution_pitch(generator));

        a2->m_worldViewAngles.y = originalYaw + yawOffset;

        __int64 result = ihCmdSend.fastcall<__int64>(a1, a2, a3);

        a2->m_worldViewAngles.x = originalPitch;
        a2->m_worldViewAngles.y = originalYaw;

        return result;
    }

    return ihCmdSend.fastcall<__int64>(a1, a2, a3);
}

void SetupCmdSendHook()
{
    static bool init = false;

    if (!init)
    {
        void* pCmdSender = MadFramework::Memory::SignatureScan("4C 89 44 24 ? 48 89 54 24 ? 53 55 56", '?', L"client.dll");
        ihCmdSend = safetyhook::create_inline(pCmdSender, CmdSend);
        PLOG_INFO << "Hooked CmdSender: " << pCmdSender;

        init = true;
    }
}

void MenuCmdSendFlags(bool should_run, bool fake_down_angles, bool fake_up_angles)
{
    lg_should_run = should_run;
    lg_fake_down = fake_down_angles;
    lg_fake_up = fake_up_angles;
}

void RemoveCmdSendHook()
{
    if (ihCmdSend.enabled())
    {
        std::expected<void, safetyhook::InlineHook::Error> hook_status = ihCmdSend.disable();

        if (!hook_status.has_value())
        {
            safetyhook::InlineHook::Error safetyError = hook_status.error();

            PLOG_ERROR << "Fatal Error unhooking CmdSend";
            PLOG_ERROR << "Error Type: " << safetyError.type;
            PLOG_ERROR << "IP: " << safetyError.ip;
        }
    }
}

void Bhop(CUserCmd* pCUserCmd, C_BaseEntity* pLocalClientEntity)
{
    if (!pLocalClientEntity->IsGrappling())
    {
        if (pLocalClientEntity && pLocalClientEntity->IsAlive() &&
            pLocalClientEntity->IsInAir() && !pLocalClientEntity->IsTitan() &&
            !pLocalClientEntity->IsOnWall())
        {
            Vector3 velocity = pLocalClientEntity->GetVelocity();
            float speed = velocity.Length();

            if (speed < 5.0f)
                return;

            const float yaw = pCUserCmd->m_worldViewAngles.y;

            const float vel_yaw = std::atan2(velocity.y, velocity.x) * (180 / std::numbers::pi_v<float>);
            const float delta = std::remainderf(yaw - vel_yaw, 360.f);

            if (delta > 0.f)
                pCUserCmd->m_moves.y = -1;
            else
                pCUserCmd->m_moves.y = 1;

            pCUserCmd->m_buttons |= 0x400'0000;
            pCUserCmd->m_buttons &= ~0x2;
        }
        else if (pLocalClientEntity->IsOnWall())
        {
            pCUserCmd->m_buttons |= 8;
            pCUserCmd->m_moves.x = 1;
        }
    }
}