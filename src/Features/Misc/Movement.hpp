#pragma once

void Bhop(CUserCmd* pCUserCmd, C_BaseEntity* pLocalClientEntity);
void SetupCmdSendHook();
void RemoveCmdSendHook();
void MenuCmdSendFlags(bool should_run, bool fake_down_angles, bool fake_up_angles);