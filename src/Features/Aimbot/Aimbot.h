#pragma once

struct WeaponPredictionData
{
	std::string weapon_name{};
	bool requires_prediction = false;
	bool requires_gravity = false;
	bool is_single_fire = false;
};

void SilentAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, bool prediction_enabled, C_BaseEntity* pTargetEntity, bool is_npc, bool thirdperson);
bool IsVisible(C_BaseEntity* pEntity, C_BaseEntity* pLocalPlayer);
bool IsInsideFovCircle(float radius, Vector3 pos_to_check);
void Aimlock(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, bool prediction_enabled, C_BaseEntity* pTargetEntity, bool is_npc, bool thirdperson);
void SmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth, bool prediction_enabled, C_BaseEntity* pTargetEntity, bool is_npc, bool thirdperson);
void SilentSmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth, Vector2& prev_attack_angle);
void UpdateHateModePlayerList(std::string_view name);
void UpdateHateModeTargets(std::vector<zgui::multi_select_item_thread_safe>& selected_targets);
bool TryKillSelectedTarget(C_BaseEntity* pTarget, C_BaseEntity* pLocalClientEntity, CGlobalVars* pCGlobalVars, CUserCmd* pCUserCmd, std::string_view name, bool thirdperson);
void RefreshPlayerList();
bool IsVisible(Vector3 bone_pos, C_BaseEntity* pLocalPlayer, bool thirdperson);
bool GunRequiresPrediction(CWeapon* p_weapon, WeaponPredictionData& prediction_data);
void AutoShoot(CUserCmd* pCUserCmd, C_BaseEntity* pLocalPlayer);