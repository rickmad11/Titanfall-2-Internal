#include "pch.h"

#include "Math.h"

#ifdef SOURCE_ENGINE_SDK
namespace MadFramework::Math::SourceEngine
{
	//Globals for the SourceEngine W2S and Screen Info stuff
	static Matrix4 const* g_pViewMatrix{};
	static float gScreenWidth = 0.f, gScreenHeight = 0.f;

	void SetViewMatrix(Matrix4 const* const viewMatrix)
	{
		g_pViewMatrix = viewMatrix;
	}

	void SetScreenInfo(int width, int height)
	{
		gScreenWidth = static_cast<float>(width);
		gScreenHeight = static_cast<float>(height);
	}

	void SetScreenInfo()
	{
		gScreenWidth = static_cast<float>(MadRenderer::DX11::Get()->windowWidth);
		gScreenHeight = static_cast<float>(MadRenderer::DX11::Get()->windowHeight);
	}

	bool WorldToScreen(Vector3& entity_position) noexcept
	{
		if (g_pViewMatrix)
		{
			const float(*m)[4] = g_pViewMatrix->m;

			const float w = m[3][0] * entity_position.x + m[3][1] * entity_position.y + m[3][2] * entity_position.z + m[3][3];

			if (w < 0.01f)
				return false;

			float x = m[0][0] * entity_position.x + m[0][1] * entity_position.y + m[0][2] * entity_position.z + m[0][3];
			float y = m[1][0] * entity_position.x + m[1][1] * entity_position.y + m[1][2] * entity_position.z + m[1][3];

			const float inverseW = 1.f / w;

			x *= inverseW;
			y *= inverseW;

			x = (.5f * x) * (gScreenWidth + .5f) + (gScreenWidth * .5f);
			y = (gScreenHeight * .5f) - ((.5f * y) * (gScreenHeight + .5f));

			entity_position.x = x;
			entity_position.y = y;

			return true;
		}

		return false;
	}

	bool WorldToScreenWithBoundCheck(Vector3& entity_position) noexcept
	{
		if (g_pViewMatrix)
		{
			const float(*m)[4] = g_pViewMatrix->m;

			const float w = m[3][0] * entity_position.x + m[3][1] * entity_position.y + m[3][2] * entity_position.z + m[3][3];

			if (w < 0.01f)
				return false;

			float x = m[0][0] * entity_position.x + m[0][1] * entity_position.y + m[0][2] * entity_position.z + m[0][3];
			float y = m[1][0] * entity_position.x + m[1][1] * entity_position.y + m[1][2] * entity_position.z + m[1][3];

			const float inverseW = 1.f / w;

			x *= inverseW;
			y *= inverseW;

			x = (.5f * x) * (gScreenWidth + .5f) + (gScreenWidth * .5f);
			y = (gScreenHeight * .5f) - ((.5f * y) * (gScreenHeight + .5f));

			if (x > gScreenWidth || x < 0 || y > gScreenHeight || y < 0)
				return false;

			entity_position.x = x;
			entity_position.y = y;

			return true;
		}

		return false;
	}
}
#endif

namespace MadFramework::Math
{
	Vector2 CalcAngles(Vector3 from, Vector3 to) noexcept
	{
		const Vector3 direction_vec = to - from;
		const Vector3 direction_vec_squared = direction_vec * direction_vec;

		const float direction_vec_magnitude = std::sqrtf(direction_vec_squared.x + direction_vec_squared.y + direction_vec_squared.z);

		constexpr float to_degrees = 180 / std::numbers::pi_v<float>;

		const float pitch = -std::asin(direction_vec.z / direction_vec_magnitude) * to_degrees;
		const float yaw = std::atan2f(direction_vec.y, direction_vec.x) * to_degrees;

		return { yaw, pitch };
	}

	Vector2 CalcAngles(Vector3 from, Vector3 to, Vector2 weapon_sway) noexcept
	{
		const Vector3 direction_vec = to - from;
		const Vector3 direction_vec_squared = direction_vec * direction_vec;

		const float direction_vec_magnitude = std::sqrtf(direction_vec_squared.x + direction_vec_squared.y + direction_vec_squared.z);

		constexpr float to_degrees = 180 / std::numbers::pi_v<float>;

		float pitch = -std::asin(direction_vec.z / direction_vec_magnitude) * to_degrees;
		float yaw = std::atan2f(direction_vec.y, direction_vec.x) * to_degrees;

		pitch -= weapon_sway.x;
		yaw -= weapon_sway.y;

		return { yaw, pitch };
	}

	Vector2 CalcAngles(Vector3 from, Vector3 to, float pitch_min, float pitch_max, float yaw_min, float yaw_max) noexcept
	{
		const Vector3 direction_vec = to - from;
		const Vector3 direction_vec_squared = direction_vec * direction_vec;

		const float direction_vec_magnitude = std::sqrtf(direction_vec_squared.x + direction_vec_squared.y + direction_vec_squared.z);

		constexpr float to_degrees = 180 / std::numbers::pi_v<float>;

		float pitch = -std::asin(direction_vec.z / direction_vec_magnitude) * to_degrees;
		float yaw = std::atan2f(direction_vec.y, direction_vec.x) * to_degrees;

		pitch = std::clamp(pitch, pitch_min, pitch_max);
		yaw = std::clamp(yaw, yaw_min, yaw_max);

		return { yaw, pitch };
	}

	Vector2 CalcAngles(Vector3 from, Vector3 to, float pitch_min, float pitch_max, float yaw_min, float yaw_max, Vector2 weapon_sway) noexcept
	{
		Vector3 direction_vec = to - from;
		const Vector3 direction_vec_squared = direction_vec * direction_vec;

		const float direction_vec_magnitude = std::sqrtf(direction_vec_squared.x + direction_vec_squared.y + direction_vec_squared.z);

		constexpr float to_degrees = 180 / std::numbers::pi_v<float>;

		float pitch = -std::asin(direction_vec.z / direction_vec_magnitude) * to_degrees;
		float yaw = std::atan2f(direction_vec.y, direction_vec.x) * to_degrees;

		pitch -= weapon_sway.x;
		yaw -= weapon_sway.y;

		pitch = std::clamp(pitch, pitch_min, pitch_max);
		yaw = std::clamp(yaw, yaw_min, yaw_max);

		return { yaw, pitch };
	}

	Vector2 Lerp(const Vector2& start_angle, const Vector2& end_angle, float smooth) noexcept
	{
		return start_angle + (end_angle - start_angle) * smooth;
	}
}