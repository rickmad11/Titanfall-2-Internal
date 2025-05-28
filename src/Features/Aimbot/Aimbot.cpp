#include "pch.h"

#include "Aimbot.h"

bool IsVisible(C_BaseEntity* pEntity, C_BaseEntity* pLocalPlayer)
{
	IEngineTrace* pIEngineTrace = MadFramework::InterfaceManager::GetInterface<IEngineTrace>();

	CTraceFilter trace_filter{};
	trace_filter.pBaseEntity = pLocalPlayer;

	std::array<Vector3, 3> trace_points = {
		pEntity->GetLocalOrigin() + Vector3{0, 0, 60},
		pEntity->GetLocalOrigin() + Vector3{0, 0, 30},
		pEntity->GetLocalOrigin() + Vector3{0, 0, 15},
	};

	bool is_visible = false;
	for (Vector3 pos : trace_points)
	{
		Trace_t trace{};
		Ray_t ray{};

		ray.init(pLocalPlayer->GetCameraPos(), pos);
		pIEngineTrace->TraceRay(ray, TRACE_MASK_SHOT, &trace_filter, &trace);

		if (trace.fraction > 0.97f)
		{
			is_visible = true;
			break;
		}
	}

	return is_visible;
}

bool IsVisible(Vector3 bone_pos, C_BaseEntity* pLocalPlayer)
{
	IEngineTrace* pIEngineTrace = MadFramework::InterfaceManager::GetInterface<IEngineTrace>();

	Trace_t trace{};
	Ray_t ray{};

	CTraceFilter trace_filter{};
	trace_filter.pBaseEntity = pLocalPlayer;

	ray.init(pLocalPlayer->GetCameraPos(), bone_pos);

	pIEngineTrace->TraceRay(ray, TRACE_MASK_SHOT, &trace_filter, &trace);

	return (trace.fraction > 0.97f);
}

bool IsInsideFovCircle(float radius, Vector3 pos_to_check)
{
	if (!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(pos_to_check))
		return false;

	MadRenderer::DX11* pRenderer = MadRenderer::DX11::Get();
	Vector3 circle_pos = { pRenderer->windowWidth * 0.5f, pRenderer->windowHeight * 0.5f , 0 };

	Vector3 vMagnitude = (circle_pos - pos_to_check) * (circle_pos - pos_to_check);

	float screen_distance = std::sqrt(vMagnitude.x + vMagnitude.y);

	if (screen_distance > radius)
		return false;

	return true;
}

static void ApplyPrediction(C_BaseEntity* pTargetEntity, C_BaseEntity* pLocalPlayer, Vector3& vTarget, bool is_npc)
{
	if (!is_npc)
	{
		WeaponPredictionData weapon_pred_data = GunRequiresPrediction(pLocalPlayer);
		float gravity = weapon_pred_data.requires_gravity ? 750.f : 0.f;
		if (weapon_pred_data.requires_prediction)
			vTarget = MadFramework::Math::PredictProjectilePosition(pLocalPlayer->GetCameraPos(), vTarget, pTargetEntity->GetVelocity(), weapon_pred_data.projectile_speed, gravity);
	}
}

void SilentAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, bool prediction_enabled, C_BaseEntity* pTargetEntity, bool is_npc)
{
	if (prediction_enabled)
		ApplyPrediction(pTargetEntity, pLocalPlayer, vTarget, is_npc);

	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_attackAngles = { pitch, yaw };
}

void Aimlock(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, bool prediction_enabled, C_BaseEntity* pTargetEntity, bool is_npc)
{
	if (prediction_enabled)
		ApplyPrediction(pTargetEntity, pLocalPlayer, vTarget, is_npc);

	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_worldViewAngles = { pitch, yaw };
}

void SmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth, bool prediction_enabled, C_BaseEntity* pTargetEntity, bool is_npc)
{
	if (prediction_enabled)
		ApplyPrediction(pTargetEntity, pLocalPlayer, vTarget, is_npc);

	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_worldViewAngles = MadFramework::Math::Lerp(pCmd->m_worldViewAngles, { pitch, yaw }, smooth);
}

void SilentSmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth, Vector2& prev_attack_angle)
{
	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_attackAngles = MadFramework::Math::Lerp(prev_attack_angle, { pitch, yaw }, smooth);

	prev_attack_angle = pCmd->m_attackAngles;
}

static std::mutex player_list_mutex;
static std::vector<std::pair<std::string, bool>> player_list {};
static std::unordered_set<std::string> player_name_set;

void UpdateHateModeTargets(std::vector<zgui::multi_select_item_thread_safe>& selected_targets)
{
	std::lock_guard<std::mutex> lock(player_list_mutex);

	for (std::pair<std::string, bool>& player : player_list)
	{
		for (zgui::multi_select_item_thread_safe& player_menu : selected_targets)
			if (player_menu.name.compare(player.first) == 0)
			{
				player.second = player_menu.value;
				break;
			}
	}

	selected_targets.clear();
	for (std::pair<std::string, bool>& player : player_list)
		selected_targets.push_back({ player.first, player.second });
}

void UpdateHateModePlayerList(std::string_view name)
{
	std::lock_guard<std::mutex> lock(player_list_mutex);

	if (name.data() && player_name_set.find(name.data()) == player_name_set.end())
	{
		player_list.push_back({ name.data(), false });
		player_name_set.insert(name.data());
	}
}

void RefreshPlayerList()
{
	player_list.clear();
	player_name_set.clear();
}

bool TryKillSelectedTarget(C_BaseEntity* pTarget, C_BaseEntity* pLocalClientEntity, CGlobalVars* pCGlobalVars, CUserCmd* pCUserCmd, std::string_view name)
{
	bool player_is_target = false;

	{
		std::lock_guard<std::mutex> lock(player_list_mutex);

		for (std::pair<std::string, bool>& player : player_list)
		{
			if (player.first.compare(name.data()) == 0 && player.second)
			{
				player_is_target = true;
				break;
			}
		}
	}

	if (player_is_target)
	{
		if (pTarget->IsTitan())
			return false;

		matrix3x4_t boneMatrix[256]{};
		if (!pTarget->SetupBones(&boneMatrix[0], 256, 1024, pCGlobalVars->m_curTime))
			return false;

		constexpr int head_bone_id = 12;
		Vector3 bone_pos = Vector3{ boneMatrix[head_bone_id][0][3], boneMatrix[head_bone_id][1][3], boneMatrix[head_bone_id][2][3] };

		if (!IsVisible(bone_pos, pLocalClientEntity))
			return false;

		SilentAim(pCUserCmd, pLocalClientEntity, bone_pos, false, pTarget, false);

		static int shoot_tick = 0;
		constexpr int shoot_interval = 1;

		if (shoot_tick++ >= shoot_interval)
		{
			pCUserCmd->m_buttons |= 1;
			shoot_tick = 0;
		}
		else
		{
			pCUserCmd->m_buttons &= ~1;
		}

		if (!pLocalClientEntity->IsZooming())
			pCUserCmd->m_buttons |= 1 << 17;

		return true;
	}

	return false;
}

static std::array<WeaponPredictionData, 29> prediction_weapon_data = { {
	{ "Spitfire", false, 0.f, false },
	{ "Alternator", false, 0.f, false },
	{ "R-201 Carbine", false, 0.f, false },
	{ "Longbow-DMR", false, 0.f, false },
	{ "Hammond P2016", false, 0.f, false },
	{ "RE-45 Auto", false, 0.f, false },
	{ "B3 Wingman", false, 0.f, false },
	{ "EVA-8 Auto", false, 0.f, false },
	{ "EPG-1", true, 2000.f, false },
	{ "CAR", false, 0.f, false },
	{ "MGL Mag Launcher", true, 1700.f, true },
	{ "Volt", false, 0.f, false },
	{ "Archer", false, 0.f, false },
	{ "D-2 Double Take", true, 5000.f, false },
	{ "Charge Rifle", false, 0.f, false },
	{ "Kraber-AP Sniper", false, 0.f, false },
	{ "Sidewinder SMR", true, 3200.f, false },
	{ "LG-97 Thunderbolt", false, 0.f, false },
	{ "R-97", false, 0.f, false },
	{ "R-101 Carbine", false, 0.f, false },
	{ "Hemlok BF-R", false, 0.f, false },
	{ "G2A5", false, 0.f, false },
	{ "V-47 Flatline", false, 0.f, false },
	{ "L-STAR", true, 3000.f, false },
	{ "X-55 Devotion", false, 0.f, false },
	{ "Mastiff", true, 2468.f, false },
	{ "EM-4 Cold War", true, 3300.f, true },
	{ "R-6P Softball", true, 2468.f, true },
	{ "SA-3 Mozambique", false, 0.f, false }
} };

WeaponPredictionData GunRequiresPrediction(C_BaseEntity* pLocalClientEntity)
{
	if (CWeapon* p_weapon = pLocalClientEntity->GetActiveWeapon())
	{
		if (const char* p_weapon_name = p_weapon->GetWeaponRealName())
		{
			std::string s_weapon_name { p_weapon_name };
			for (WeaponPredictionData const& weapon_data : prediction_weapon_data)
			{
				if (weapon_data.weapon_name.compare(s_weapon_name) == 0)
					return weapon_data;
			}
		}
	}

	return {};
}