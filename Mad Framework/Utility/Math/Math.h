#pragma once

#ifdef SOURCE_ENGINE_SDK
namespace MadFramework::Math::SourceEngine
{
	void SetScreenInfo(int width, int height);
	void SetScreenInfo();
	void SetViewMatrix(Matrix4 const* const viewMatrix);
	bool WorldToScreen(Vector3& entity_position) noexcept;
	bool WorldToScreenWithBoundCheck(Vector3& entity_position) noexcept;
}
#endif

namespace MadFramework::Math
{
	Vector2 CalcAngles(Vector3 from, Vector3 to) noexcept;
	Vector2 CalcAngles(Vector3 from, Vector3 to, float pitch_min, float pitch_max, float yaw_min, float yaw_max) noexcept;
	Vector2 CalcAngles(Vector3 from, Vector3 to, float pitch_min, float pitch_max, float yaw_min, float yaw_max, Vector2 weapon_sway) noexcept;
	Vector2 CalcAngles(Vector3 from, Vector3 to, Vector2 weapon_sway) noexcept;
	Vector2 Lerp(const Vector2& start_angle, const Vector2& end_angle, float smooth) noexcept;
	Vector3 PredictProjectilePosition(Vector3 vLocalPosition, Vector3 vTargetPosition, Vector3 vTargetVelocity, float projectile_speed, float gravity) noexcept;
}