#include "pch.h"
#include "ESP.h"

constexpr float g_visuals_text_scale = 1.2f;

bool GetPlayer2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out)
{
	Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();
	Vector3 entity_head = entity_origin - Vector3{ 0, 0, -70 };

	if (!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(entity_origin) ||
		!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(entity_head))
		return false;

	const float entity_height = entity_origin.y - entity_head.y;
	const float entity_width = entity_height * .5f;

	out = Vector4{ entity_origin.x, entity_origin.y, entity_width, entity_height };

	return true;
}

bool GetGrenade2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out)
{
	Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();

	if (!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(entity_origin))
		return false;

	out = Vector4{ entity_origin.x, entity_origin.y, 0, 0 };

	return true;
}

bool GetWeapon2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out)
{
	Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin() - Vector3{0, 0, 5};
	Vector3 entity_head = entity_origin - Vector3{ 0, 0, -10 };

	if (!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(entity_origin) ||
		!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(entity_head))
		return false;

	const float entity_height = entity_origin.y - entity_head.y;
	const float entity_width = entity_height * .5f;

	out = Vector4{ entity_origin.x, entity_origin.y, entity_width, entity_height };

	return true;
}

bool GetTitan2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out)
{
	Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();
	Vector3 entity_head = entity_origin - Vector3{ 0, 0, -216 };

	if (!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(entity_origin) ||
		!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(entity_head))
		return false;

	const float entity_height = entity_origin.y - entity_head.y;
	const float entity_width = entity_height * .5f;

	out = Vector4{ entity_origin.x, entity_origin.y, entity_width, entity_height };

	return true;
}

void Entity2dBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	pBackGroundRenderList->DrawRect({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w, screenBaseEntity.z, screenBaseEntity.w }, { 255, 255, 255, 255 }, {0, 0, 0, 255});
}

void Entity2dBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color)
{
	pBackGroundRenderList->DrawRect({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w, screenBaseEntity.z, screenBaseEntity.w },
		{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) }, { 0, 0, 0, 255 });
}

void EntityEdgeBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y }, { screenBaseEntity.x - (screenBaseEntity.z * .25f), screenBaseEntity.y }, { 255, 255, 255, 255 });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w * 0.25f}, { screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y }, { 255, 255, 255, 255 });

	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y }, { screenBaseEntity.x + (screenBaseEntity.z * .25f), screenBaseEntity.y }, { 255, 255, 255, 255 });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w * 0.25f }, { screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y }, { 255, 255, 255, 255 });

	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x - (screenBaseEntity.z * .5f), (screenBaseEntity.y - screenBaseEntity.w) + screenBaseEntity.w * 0.25f }, { 255, 255, 255, 255 });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x - (screenBaseEntity.z * .25f), screenBaseEntity.y - screenBaseEntity.w }, { 255, 255, 255, 255 });

	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x + (screenBaseEntity.z * .5f), (screenBaseEntity.y - screenBaseEntity.w) + screenBaseEntity.w * 0.25f }, { 255, 255, 255, 255 });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x + (screenBaseEntity.z * .25f), screenBaseEntity.y - screenBaseEntity.w }, { 255, 255, 255, 255 });
}

void EntityEdgeBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color)
{
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y }, { screenBaseEntity.x - (screenBaseEntity.z * .25f), screenBaseEntity.y }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w * 0.25f }, { screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });

	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y }, { screenBaseEntity.x + (screenBaseEntity.z * .25f), screenBaseEntity.y }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w * 0.25f }, { screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });

	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x - (screenBaseEntity.z * .5f), (screenBaseEntity.y - screenBaseEntity.w) + screenBaseEntity.w * 0.25f }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x - (screenBaseEntity.z * .25f), screenBaseEntity.y - screenBaseEntity.w }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });

	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x + (screenBaseEntity.z * .5f), (screenBaseEntity.y - screenBaseEntity.w) + screenBaseEntity.w * 0.25f }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
	pBackGroundRenderList->DrawLine({ screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { screenBaseEntity.x + (screenBaseEntity.z * .25f), screenBaseEntity.y - screenBaseEntity.w }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
}

void EntitySnapLines(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	const float windowWidth = MadRenderer::DX11::Get()->windowWidth * 0.5f;
	const float windowHeight = static_cast<float>(MadRenderer::DX11::Get()->windowHeight);
	pBackGroundRenderList->DrawLine({ windowWidth, windowHeight }, { screenBaseEntity.x, screenBaseEntity.y }, { 255, 255, 255, 255 });
}

void EntityName(Vector4 screenBaseEntity, const char* pEntityName, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color)
{
	pBackGroundRenderList->DrawOutlinedString(pEntityName, { screenBaseEntity.x - (pBackGroundRenderList->MeasureString(pEntityName).x * 0.5f), screenBaseEntity.y - (screenBaseEntity.w + pBackGroundRenderList->MeasureString(pEntityName).y * g_visuals_text_scale) },
		{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) }, g_visuals_text_scale);
}

void EntityHealth(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	const std::string health_string = std::to_string(C_BaseEntity.Health) + "/" + std::to_string(C_BaseEntity.MaxHealth);

	pBackGroundRenderList->DrawString(health_string.c_str(), { screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w }, { 255, 255, 255, 255 }, g_visuals_text_scale);
}

void EntityDistance(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	const float distance = C_BaseEntity.distance;

	std::string distance_string = "[" + std::to_string(static_cast<int>(distance)) + "]";

	pBackGroundRenderList->DrawString(distance_string.c_str(), { screenBaseEntity.x - pBackGroundRenderList->MeasureString(distance_string.c_str()).x * g_visuals_text_scale * .5f , screenBaseEntity.y}, { 255, 255, 255, 255 }, g_visuals_text_scale);
}

void EntityDistance(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, const char* text ,MadRenderer::RenderList* pBackGroundRenderList)
{
	const float distance = C_BaseEntity.distance;

	std::string distance_string = "[" + std::to_string(static_cast<int>(distance)) + "]";

	pBackGroundRenderList->DrawString(distance_string.c_str(), { screenBaseEntity.x - pBackGroundRenderList->MeasureString(distance_string.c_str()).x * g_visuals_text_scale * .5f , screenBaseEntity.y }, { 255, 255, 255, 255 }, g_visuals_text_scale);
	pBackGroundRenderList->DrawString(text, { screenBaseEntity.x - pBackGroundRenderList->MeasureString(text).x * g_visuals_text_scale * .5f , screenBaseEntity.y - pBackGroundRenderList->MeasureString(text).y }, { 255, 255, 255, 255 }, g_visuals_text_scale);
}

void EntityWeaponData(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	const std::string ammo_string = std::to_string(C_BaseEntity.clipAmmo) + "/" + std::to_string(C_BaseEntity.stockAmmo);
	const std::string isReloading = C_BaseEntity.isReloading ? "Reloading" : "Loaded";

	const float string_ammo_height = pBackGroundRenderList->MeasureString(ammo_string.c_str()).y;
	const float string_isreload_height = pBackGroundRenderList->MeasureString(isReloading.c_str()).y;
	const float string_weapon_name_height = pBackGroundRenderList->MeasureString(C_BaseEntity.weapon_name.c_str()).y;

	pBackGroundRenderList->DrawString(ammo_string.c_str(), { screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w + string_ammo_height }, { 255, 255, 255, 255 }, g_visuals_text_scale);
	pBackGroundRenderList->DrawString(C_BaseEntity.weapon_name.c_str(), { screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w + (string_weapon_name_height * 2.f)}, { 255, 255, 255, 255 }, g_visuals_text_scale);
	pBackGroundRenderList->DrawString(isReloading.c_str(), { screenBaseEntity.x + (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w + (string_isreload_height * 3.f) }, { 255, 255, 255, 255 }, g_visuals_text_scale);
}

void EntityHealthBar(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	const float currHealth = static_cast<float>(C_BaseEntity.Health);
	const float maxHealth = static_cast<float>(C_BaseEntity.MaxHealth);
	const float healthPercent = currHealth / maxHealth;

	constexpr float width = -3;

	pBackGroundRenderList->DrawRect({ screenBaseEntity.x - (screenBaseEntity.z * .5f) - 2, screenBaseEntity.y - screenBaseEntity.w, width, screenBaseEntity.w }, { 255, 255, 255, 255 }, { 0, 0, 0, 255 });
	pBackGroundRenderList->DrawFilledRect({ screenBaseEntity.x - (screenBaseEntity.z * .5f) - 2, (screenBaseEntity.y - screenBaseEntity.w) + 2, width, screenBaseEntity.w - 4 }, { 0, 0, 0, 255 });
	pBackGroundRenderList->DrawFilledRect({ screenBaseEntity.x - (screenBaseEntity.z * .5f) - 2,  ((screenBaseEntity.y - screenBaseEntity.w) + 2) + (screenBaseEntity.w * (1.f - healthPercent)), width , screenBaseEntity.w - 4 - (screenBaseEntity.w * (1.f - healthPercent)) }, { 255 * (1.0f - healthPercent) , 255 * healthPercent, 0.f, 255 });

}

void EntityBones(EntityRenderData const& C_BaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color)
{
	static constexpr std::pair<int, int> bone_pair[]
	{
		//idk anymore make (draw all indices and make picture)
		//Left half
		{69,68}, 
		{68,70}, 
		{70,66},
		{66,5},
		{5,6},
		{6,7},
		{7,9},
		{9,12},

		//Lower Right half
		{64,63},
		{63,65},
		{65,61},
		{61,5},

		//Right Arm
		{37,15},
		{15,17},
		{17,16},
		{16,19},
		{19,20},

		//Left Arm
		{37,38},
		{38,41},
		{41,40},
		{40,43},
		{43,44}
	};

	//int count = 0;
	//for (matrix3x4_t bone : boneMatrix)
	//{
	//	if (count > 100)
	//		break;
	//
	//	Vector3 bone_pos = Vector3{ bone[0][3], bone[1][3], bone[2][3] };
	//
	//	if(!MadFramework::Math::SourceEngine::WorldToScreenWithBoundCheck(bone_pos))
	//		continue;
	//
	//	pBackGroundRenderList->DrawString(std::to_string(count).c_str(), { bone_pos.x, bone_pos.y }, {255, 255, 255}, 1.f);
	//
	//	++count;
	//}

	for( auto const [first, second] : bone_pair)
	{
		Vector3 bone_pos1 = Vector3{ C_BaseEntity.boneMatrix[first][0][3], C_BaseEntity.boneMatrix[first][1][3], C_BaseEntity.boneMatrix[first][2][3] };
		Vector3 bone_pos2 = Vector3{ C_BaseEntity.boneMatrix[second][0][3], C_BaseEntity.boneMatrix[second][1][3], C_BaseEntity.boneMatrix[second][2][3] };
	
		if (!MadFramework::Math::SourceEngine::WorldToScreen(bone_pos1) ||
			!MadFramework::Math::SourceEngine::WorldToScreen(bone_pos2))
			continue;
	
		pBackGroundRenderList->DrawLine( {bone_pos1.x, bone_pos1.y}, { bone_pos2.x, bone_pos2.y }, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a)});
	}
}

void DrawFovCircle(zgui::color color, float radius)
{
	MadRenderer::DX11* pRenderer = MadRenderer::DX11::Get();
	MadRenderer::RenderList* pBackGroundRenderList = pRenderer->GetBackGroundRenderList();

	pBackGroundRenderList->DrawSmoothCircle<80>({ pRenderer->windowWidth * 0.5f, pRenderer->windowHeight * 0.5f },
		radius, { static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
}

float GetPlayerSpeed(C_BaseEntity* pPlayerEntity) noexcept
{
	float* _this = reinterpret_cast<float*>(pPlayerEntity);

	float speed = std::sqrt(*(_this + 0x48) * *(_this + 0x48) + *(_this + 0x49) * *(_this + 0x49)) + *(_this + 0x4A) * *(_this + 0x4A);

	return speed;
}

void DrawPlayerSpeed(float player_speed, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList)
{
	std::string speed_string = "Speed: " + std::to_string(static_cast<int>(player_speed));

	pBackGroundRenderList->DrawString(speed_string.c_str(), { screenBaseEntity.x - pBackGroundRenderList->MeasureString(speed_string.c_str()).x * g_visuals_text_scale * .5f , screenBaseEntity.y - (pBackGroundRenderList->MeasureString(speed_string.c_str()).y * 2.f) }, { 255, 255, 255, 255 }, g_visuals_text_scale);
}

void EntityFilledBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color)
{
	pBackGroundRenderList->DrawFilledRect({ screenBaseEntity.x - (screenBaseEntity.z * .5f), screenBaseEntity.y - screenBaseEntity.w, screenBaseEntity.z, screenBaseEntity.w},
		{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
}