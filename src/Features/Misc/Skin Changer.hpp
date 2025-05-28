#pragma once

void SkinChanger(C_BaseEntity* pLocalClientEntity, int skin_id);
void SaveSkinsToConfig(ConfigManager* p_config_manager);
void LoadSkinsFromConfig(ConfigManager* p_config_manager);