#pragma once

void SilentAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget);
bool IsVisible(C_BaseEntity* pEntity, C_BaseEntity* pLocalPlayer);
bool IsInsideFovCircle(float radius, Vector3 pos_to_check);
void Aimlock(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget);
void SmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth);
void SilentSmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth, Vector2& prev_attack_angle);