#include "pch.h"

#include "Skin Changer.hpp"

static std::unordered_map<std::string, int> weapon_skin_map
{
	{"Spitfire", 0},
	{"Alternator", 0},
	{"R-201 Carbine", 0},
	{"Longbow-DMR", 0},
	{"Hammond P2016", 0},
	{"RE-45 Auto", 0},
	{"B3 Wingman", 0},
	{"EVA-8 Auto", 0},
	{"EPG-1", 0},
	{"CAR", 0},
	{"MGL Mag Launcher", 0},
	{"Volt", 0},
	{"Archer", 0},
	{"D-2 Double Take", 0},
	{"Charge Rifle", 0},
	{"Kraber-AP Sniper", 0},
	{"Sidewinder SMR", 0},
	{"LG-97 Thunderbolt", 0},
	{"R-97", 0},
	{"R-101 Carbine", 0},
	{"Hemlok BF-R", 0},
	{"G2A5", 0},
	{"V-47 Flatline", 0},
	{"L-STAR", 0},
	{"X-55 Devotion", 0},
	{"Mastiff", 0},
	{"EM-4 Cold War", 0},
	{"R-6P Softball", 0},
	{"SA-3 Mozambique", 0}
};

static int GetSelectedSkin(std::string_view weapon_name)
{
	for (auto& pair : weapon_skin_map)
		if (pair.first.compare(weapon_name) == 0)
			return pair.second;

	return 0;
}

static void UpdateSkin(std::string_view weapon_name, int skin_id)
{
	for (auto& pair : weapon_skin_map)
		if (pair.first.compare(weapon_name) == 0)
			pair.second = skin_id;
}

void SaveSkinsToConfig(ConfigManager* p_config_manager)
{
	for (auto& pair : weapon_skin_map)
		p_config_manager->AddValue("SkinIDs", "Skin->" + pair.first, pair.second);
}

void LoadSkinsFromConfig(ConfigManager* p_config_manager)
{
	for (auto& pair : weapon_skin_map)
		p_config_manager->GetValue("SkinIDs", "Skin->" + pair.first, pair.second);
}

void SkinChanger(C_BaseEntity* pLocalClientEntity, int skin_id)
{
	static int prev_skin_id = 0;

	if (pLocalClientEntity && pLocalClientEntity->IsAlive())
	{
		if (CWeapon* p_weapon = pLocalClientEntity->GetActiveWeapon())
		{
			if (int* r_skinID = &p_weapon->GetActiveSkinID())
			{
				if (const char* weapon_name = p_weapon->GetWeaponRealName())
				{
					std::string s_weapon_name = weapon_name;

					if (pLocalClientEntity->GetActiveWeapon()) //just making sure 
					{
						if (skin_id != 0 && skin_id != prev_skin_id)
							UpdateSkin(s_weapon_name, skin_id);

						*r_skinID = GetSelectedSkin(s_weapon_name);
					}
				}
			}
		}
	}

	prev_skin_id = skin_id;
}