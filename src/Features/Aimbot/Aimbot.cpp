#include "pch.h"

#include "Aimbot.h"

bool IsVisible(C_BaseEntity* pEntity, C_BaseEntity* pLocalPlayer)
{
	IEngineTrace* pIEngineTrace = MadFramework::InterfaceManager::GetInterface<IEngineTrace>();

	Trace_t trace{};
	Ray_t ray{};

	CTraceFilter trace_filter{};
	trace_filter.pBaseEntity = pLocalPlayer;

	Vector3 trace_end_pos = pEntity->GetLocalOrigin() + Vector3{ 0, 30, 50 };
	ray.init(pLocalPlayer->GetCameraPos(), trace_end_pos);

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

void SilentAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget) 
{
	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_attackAngles = { pitch, yaw };
}

void Aimlock(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget)
{
	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_worldViewAngles = { pitch, yaw };
}

void SmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth)
{
	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_worldViewAngles = MadFramework::Math::Lerp(pCmd->m_worldViewAngles, { pitch, yaw }, smooth);
}

void SilentSmoothAim(CUserCmd* pCmd, C_BaseEntity* pLocalPlayer, Vector3 vTarget, float smooth, Vector2& prev_attack_angle)
{
	auto [yaw, pitch] = MadFramework::Math::CalcAngles(pLocalPlayer->GetCameraPos(), vTarget, -89, 89, -180, 180, pLocalPlayer->GetWeaponSway());

	pCmd->m_attackAngles = MadFramework::Math::Lerp(prev_attack_angle, { pitch, yaw }, smooth);

	prev_attack_angle = pCmd->m_attackAngles;
}
