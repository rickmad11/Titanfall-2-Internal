#pragma once

struct EntityRenderData
{
	enum EntityType : int
	{
		Player,
		Npc,
		Weapon,
		Grenade
	}type;

	std::string name {};
	std::string weapon_name {};
	Vector4 screenBasePosition {};
	int Health = 0;
	int MaxHealth = 0;
	float distance = 0.f;
	float speed = 0.f;
	int clipAmmo = 0;
	int stockAmmo = 0;
	bool isReloading = false;
	bool hasBones = false;
	bool isVisible = false;
	matrix3x4_t boneMatrix[256]{};

};

inline std::mutex render_mutex;
inline std::vector<EntityRenderData> entity_render_data;

//only player
struct EntityRenderDataOOFArrow
{
	Vector4 screenBasePosition{};
	bool is_visible = false;
};

inline std::mutex render_mutex_oof_arrow;
inline std::vector<EntityRenderDataOOFArrow> entity_render_data_oof_arrow;



void MainVisuals();