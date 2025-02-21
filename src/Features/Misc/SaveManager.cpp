#include "pch.h"

#include "SaveManager.h"
#include "Menu/Menu.h"

void SaveSettings() 
{
	MadFramework::Menu::MenuState menuState = MadFramework::Menu::state;

	ConfigManager* p_config_manager = ConfigManager::Get();

	p_config_manager->Begin();

    p_config_manager->AddValue("MenuState", "aimbotTab", menuState.aimbotTab);
    p_config_manager->AddValue("MenuState", "visualsTab", menuState.visualsTab);
    p_config_manager->AddValue("MenuState", "miscTab", menuState.miscTab);
    p_config_manager->AddValue("MenuState", "settingsTab", menuState.settingsTab);

    p_config_manager->AddValue("Visuals", "vPlayers", menuState.vPlayers);
    p_config_manager->AddValue("Visuals", "vPlayer_box_2d", menuState.vPlayer_box_2d);
    p_config_manager->AddValue("Visuals", "vPlayer_name", menuState.vPlayer_name);
    p_config_manager->AddValue("Visuals", "vPlayerTeam", menuState.vPlayerTeam);
    p_config_manager->AddValue("Visuals", "vPlayer_health", menuState.vPlayer_health);
    p_config_manager->AddValue("Visuals", "vPlayer_distance", menuState.vPlayer_distance);
    p_config_manager->AddValue("Visuals", "vPlayer_weapon_info", menuState.vPlayer_weapon_info);
    p_config_manager->AddValue("Visuals", "vPlayer_health_bar", menuState.vPlayer_health_bar);
    p_config_manager->AddValue("Visuals", "vPlayer_bones", menuState.vPlayer_bones);
    p_config_manager->AddValue("Visuals", "vPlayer_snap_lines", menuState.vPlayer_snap_lines);
    p_config_manager->AddValue("Visuals", "vPlayer_edge_box", menuState.vPlayer_edge_box);
    p_config_manager->AddValue("Visuals", "vPlayer_speed", menuState.vPlayer_speed);
    p_config_manager->AddValue("Visuals", "vPlayer_FilledBox", menuState.vPlayer_FilledBox);

    p_config_manager->AddValue("World", "vWorld", menuState.vWorld);
    p_config_manager->AddValue("World", "vNpcs", menuState.vNpcs);
    p_config_manager->AddValue("World", "vNpc_box_2d", menuState.vNpc_box_2d);
    p_config_manager->AddValue("World", "vNpc_name", menuState.vNpc_name);
    p_config_manager->AddValue("World", "vNpc_health", menuState.vNpc_health);
    p_config_manager->AddValue("World", "vNpc_weapon_info", menuState.vNpc_weapon_info);
    p_config_manager->AddValue("World", "vNpc_health_bar", menuState.vNpc_health_bar);
    p_config_manager->AddValue("World", "vNpc_bones", menuState.vNpc_bones);
    p_config_manager->AddValue("World", "vNpc_snap_lines", menuState.vNpc_snap_lines);
    p_config_manager->AddValue("World", "vNpc_edge_box", menuState.vNpc_edge_box);
    p_config_manager->AddValue("World", "vNpc_FilledBox", menuState.vNpc_FilledBox);
    p_config_manager->AddValue("World", "vEntity_distance", menuState.vEntity_distance);
    p_config_manager->AddValue("World", "vGrenades", menuState.vGrenades);
    p_config_manager->AddValue("World", "vWeapons", menuState.vWeapons);

    p_config_manager->AddValue("VisualsSettings", "vVisbleCheck", menuState.vVisbleCheck);
    p_config_manager->AddValue("VisualsSettings", "vDrawFovCircle", menuState.vDrawFovCircle);
    p_config_manager->AddValue("VisualsSettings", "vFovCircleSize", menuState.vFovCircleSize);

    p_config_manager->AddValue("Aimbot", "aPlayers", menuState.aPlayers);
    p_config_manager->AddValue("Aimbot", "aNpcs", menuState.aNpcs);
    p_config_manager->AddValue("Aimbot", "aSilentAimPlayers", menuState.aSilentAimPlayers);
    p_config_manager->AddValue("Aimbot", "aSilentAimNpcs", menuState.aSilentAimNpcs);
    p_config_manager->AddValue("Aimbot", "aAimlockPlayers", menuState.aAimlockPlayers);
    p_config_manager->AddValue("Aimbot", "aAimlockNpcs", menuState.aAimlockNpcs);
    p_config_manager->AddValue("Aimbot", "aVisibleCheck", menuState.aVisibleCheck);
    p_config_manager->AddValue("Aimbot", "aInsideFovCircleCheck", menuState.aInsideFovCircleCheck);
    p_config_manager->AddValue("Aimbot", "aIgnoreTitans", menuState.aIgnoreTitans);
    p_config_manager->AddValue("Aimbot", "aAutoAttack", menuState.aAutoAttack);
    p_config_manager->AddValue("Aimbot", "aAutoZoom", menuState.aAutoZoom);
    p_config_manager->AddValue("Aimbot", "aAimlockKey", menuState.aAimlockKey);
    p_config_manager->AddValue("Aimbot", "aAimlockSmooth", menuState.aAimlockSmooth);
    p_config_manager->AddValue("Aimbot", "aAimlock_smoothness", menuState.aAimlock_smoothness);

    p_config_manager->AddValue("Misc", "mSpeedExploit", menuState.mSpeedExploit);
    p_config_manager->AddValue("Misc", "mAirstuck", menuState.mAirstuck);
    p_config_manager->AddValue("Misc", "mAirstuckKey", menuState.mAirstuckKey);
    p_config_manager->AddValue("Misc", "mViewmodelChanges", menuState.mViewmodelChanges);
    p_config_manager->AddValue("Misc", "mUnlockAllAchievements", menuState.mUnlockAllAchievements);
    p_config_manager->AddValue("Misc", "mCustomCrosshair", menuState.mCustomCrosshair);
    p_config_manager->AddValue("Misc", "mDisableGameCrosshair", menuState.mDisableGameCrosshair);
    p_config_manager->AddValue("Misc", "mSelectedCrosshairVariant", menuState.mSelectedCrosshairVariant);
    p_config_manager->AddValue("Misc", "mCustomCrosshairSize", menuState.mCustomCrosshairSize);
    p_config_manager->AddValue("Misc", "mHitSounds", menuState.mHitSounds);
    p_config_manager->AddValue("Misc", "mSelectedHitSound", menuState.mSelectedHitSound);
    p_config_manager->AddValue("Misc", "mHitSoundVolume", menuState.mHitSoundVolume);
    p_config_manager->AddValue("Misc", "mHitSoundPitch", menuState.mHitSoundPitch);
    p_config_manager->AddValue("Misc", "mSpeed", menuState.mSpeed);
    p_config_manager->AddValue("Misc", "mFov", menuState.mFov);
    p_config_manager->AddValue("Misc", "mViewmodel_fov", menuState.mViewmodel_fov);
    p_config_manager->AddValue("Misc", "mAutoMelee", menuState.mAutoMelee);

    p_config_manager->AddValue("MenuColors", "cPlayer_r", MadFramework::Menu::menu_colors.cPlayer.r);
    p_config_manager->AddValue("MenuColors", "cPlayer_g", MadFramework::Menu::menu_colors.cPlayer.g);
    p_config_manager->AddValue("MenuColors", "cPlayer_b", MadFramework::Menu::menu_colors.cPlayer.b);
    p_config_manager->AddValue("MenuColors", "cPlayer_a", MadFramework::Menu::menu_colors.cPlayer.a);

    p_config_manager->AddValue("MenuColors", "cPlayerBones_r", MadFramework::Menu::menu_colors.cPlayerBones.r);
    p_config_manager->AddValue("MenuColors", "cPlayerBones_g", MadFramework::Menu::menu_colors.cPlayerBones.g);
    p_config_manager->AddValue("MenuColors", "cPlayerBones_b", MadFramework::Menu::menu_colors.cPlayerBones.b);
    p_config_manager->AddValue("MenuColors", "cPlayerBones_a", MadFramework::Menu::menu_colors.cPlayerBones.a);

    p_config_manager->AddValue("MenuColors", "cNpc_r", MadFramework::Menu::menu_colors.cNpc.r);
    p_config_manager->AddValue("MenuColors", "cNpc_g", MadFramework::Menu::menu_colors.cNpc.g);
    p_config_manager->AddValue("MenuColors", "cNpc_b", MadFramework::Menu::menu_colors.cNpc.b);
    p_config_manager->AddValue("MenuColors", "cNpc_a", MadFramework::Menu::menu_colors.cNpc.a);

    p_config_manager->AddValue("MenuColors", "cNpcBones_r", MadFramework::Menu::menu_colors.cNpcBones.r);
    p_config_manager->AddValue("MenuColors", "cNpcBones_g", MadFramework::Menu::menu_colors.cNpcBones.g);
    p_config_manager->AddValue("MenuColors", "cNpcBones_b", MadFramework::Menu::menu_colors.cNpcBones.b);
    p_config_manager->AddValue("MenuColors", "cNpcBones_a", MadFramework::Menu::menu_colors.cNpcBones.a);

    p_config_manager->AddValue("MenuColors", "cNpcName_r", MadFramework::Menu::menu_colors.cNpcName.r);
    p_config_manager->AddValue("MenuColors", "cNpcName_g", MadFramework::Menu::menu_colors.cNpcName.g);
    p_config_manager->AddValue("MenuColors", "cNpcName_b", MadFramework::Menu::menu_colors.cNpcName.b);
    p_config_manager->AddValue("MenuColors", "cNpcName_a", MadFramework::Menu::menu_colors.cNpcName.a);

    p_config_manager->AddValue("MenuColors", "cNpcFilledBox_r", MadFramework::Menu::menu_colors.cNpcFilledBox.r);
    p_config_manager->AddValue("MenuColors", "cNpcFilledBox_g", MadFramework::Menu::menu_colors.cNpcFilledBox.g);
    p_config_manager->AddValue("MenuColors", "cNpcFilledBox_b", MadFramework::Menu::menu_colors.cNpcFilledBox.b);
    p_config_manager->AddValue("MenuColors", "cNpcFilledBox_a", MadFramework::Menu::menu_colors.cNpcFilledBox.a);

    p_config_manager->AddValue("MenuColors", "cPlayerName_r", MadFramework::Menu::menu_colors.cPlayerName.r);
    p_config_manager->AddValue("MenuColors", "cPlayerName_g", MadFramework::Menu::menu_colors.cPlayerName.g);
    p_config_manager->AddValue("MenuColors", "cPlayerName_b", MadFramework::Menu::menu_colors.cPlayerName.b);
    p_config_manager->AddValue("MenuColors", "cPlayerName_a", MadFramework::Menu::menu_colors.cPlayerName.a);

    p_config_manager->AddValue("MenuColors", "cPlayerFilledBox_r", MadFramework::Menu::menu_colors.cPlayerFilledBox.r);
    p_config_manager->AddValue("MenuColors", "cPlayerFilledBox_g", MadFramework::Menu::menu_colors.cPlayerFilledBox.g);
    p_config_manager->AddValue("MenuColors", "cPlayerFilledBox_b", MadFramework::Menu::menu_colors.cPlayerFilledBox.b);
    p_config_manager->AddValue("MenuColors", "cPlayerFilledBox_a", MadFramework::Menu::menu_colors.cPlayerFilledBox.a);

    p_config_manager->AddValue("MenuColors", "cInvPlayer_r", MadFramework::Menu::menu_colors.cInvPlayer.r);
    p_config_manager->AddValue("MenuColors", "cInvPlayer_g", MadFramework::Menu::menu_colors.cInvPlayer.g);
    p_config_manager->AddValue("MenuColors", "cInvPlayer_b", MadFramework::Menu::menu_colors.cInvPlayer.b);
    p_config_manager->AddValue("MenuColors", "cInvPlayer_a", MadFramework::Menu::menu_colors.cInvPlayer.a);

    p_config_manager->AddValue("MenuColors", "cInvPlayerBones_r", MadFramework::Menu::menu_colors.cInvPlayerBones.r);
    p_config_manager->AddValue("MenuColors", "cInvPlayerBones_g", MadFramework::Menu::menu_colors.cInvPlayerBones.g);
    p_config_manager->AddValue("MenuColors", "cInvPlayerBones_b", MadFramework::Menu::menu_colors.cInvPlayerBones.b);
    p_config_manager->AddValue("MenuColors", "cInvPlayerBones_a", MadFramework::Menu::menu_colors.cInvPlayerBones.a);

    p_config_manager->AddValue("MenuColors", "cInvPlayerFilledBox_r", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.r);
    p_config_manager->AddValue("MenuColors", "cInvPlayerFilledBox_g", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.g);
    p_config_manager->AddValue("MenuColors", "cInvPlayerFilledBox_b", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.b);
    p_config_manager->AddValue("MenuColors", "cInvPlayerFilledBox_a", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.a);

    p_config_manager->AddValue("MenuColors", "cInvNpc_r", MadFramework::Menu::menu_colors.cInvNpc.r);
    p_config_manager->AddValue("MenuColors", "cInvNpc_g", MadFramework::Menu::menu_colors.cInvNpc.g);
    p_config_manager->AddValue("MenuColors", "cInvNpc_b", MadFramework::Menu::menu_colors.cInvNpc.b);
    p_config_manager->AddValue("MenuColors", "cInvNpc_a", MadFramework::Menu::menu_colors.cInvNpc.a);

    p_config_manager->AddValue("MenuColors", "cInvNpcBones_r", MadFramework::Menu::menu_colors.cInvNpcBones.r);
    p_config_manager->AddValue("MenuColors", "cInvNpcBones_g", MadFramework::Menu::menu_colors.cInvNpcBones.g);
    p_config_manager->AddValue("MenuColors", "cInvNpcBones_b", MadFramework::Menu::menu_colors.cInvNpcBones.b);
    p_config_manager->AddValue("MenuColors", "cInvNpcBones_a", MadFramework::Menu::menu_colors.cInvNpcBones.a);

    p_config_manager->AddValue("MenuColors", "cInvNpcName_r", MadFramework::Menu::menu_colors.cInvNpcName.r);
    p_config_manager->AddValue("MenuColors", "cInvNpcName_g", MadFramework::Menu::menu_colors.cInvNpcName.g);
    p_config_manager->AddValue("MenuColors", "cInvNpcName_b", MadFramework::Menu::menu_colors.cInvNpcName.b);
    p_config_manager->AddValue("MenuColors", "cInvNpcName_a", MadFramework::Menu::menu_colors.cInvNpcName.a);

    p_config_manager->AddValue("MenuColors", "cInvPlayerName_r", MadFramework::Menu::menu_colors.cInvPlayerName.r);
    p_config_manager->AddValue("MenuColors", "cInvPlayerName_g", MadFramework::Menu::menu_colors.cInvPlayerName.g);
    p_config_manager->AddValue("MenuColors", "cInvPlayerName_b", MadFramework::Menu::menu_colors.cInvPlayerName.b);
    p_config_manager->AddValue("MenuColors", "cInvPlayerName_a", MadFramework::Menu::menu_colors.cInvPlayerName.a);

    p_config_manager->AddValue("MenuColors", "cInvNpcFilledBox_r", MadFramework::Menu::menu_colors.cInvNpcFilledBox.r);
    p_config_manager->AddValue("MenuColors", "cInvNpcFilledBox_g", MadFramework::Menu::menu_colors.cInvNpcFilledBox.g);
    p_config_manager->AddValue("MenuColors", "cInvNpcFilledBox_b", MadFramework::Menu::menu_colors.cInvNpcFilledBox.b);
    p_config_manager->AddValue("MenuColors", "cInvNpcFilledBox_a", MadFramework::Menu::menu_colors.cInvNpcFilledBox.a);

    p_config_manager->AddValue("MenuColors", "cFovCircle_r", MadFramework::Menu::menu_colors.cFovCircle.r);
    p_config_manager->AddValue("MenuColors", "cFovCircle_g", MadFramework::Menu::menu_colors.cFovCircle.g);
    p_config_manager->AddValue("MenuColors", "cFovCircle_b", MadFramework::Menu::menu_colors.cFovCircle.b);
    p_config_manager->AddValue("MenuColors", "cFovCircle_a", MadFramework::Menu::menu_colors.cFovCircle.a);

    decltype(zgui::get_menu_colors()) pGlobal_menu_colors = zgui::get_menu_colors();

    p_config_manager->AddValue("MainMenuColors", "window_border_inner_fill_r", pGlobal_menu_colors->window_border_inner_fill.r);
    p_config_manager->AddValue("MainMenuColors", "window_border_inner_fill_g", pGlobal_menu_colors->window_border_inner_fill.g);
    p_config_manager->AddValue("MainMenuColors", "window_border_inner_fill_b", pGlobal_menu_colors->window_border_inner_fill.b);
    p_config_manager->AddValue("MainMenuColors", "window_border_inner_fill_a", pGlobal_menu_colors->window_border_inner_fill.a);

    p_config_manager->AddValue("MainMenuColors", "window_border_fill_r", pGlobal_menu_colors->window_border_fill.r);
    p_config_manager->AddValue("MainMenuColors", "window_border_fill_g", pGlobal_menu_colors->window_border_fill.g);
    p_config_manager->AddValue("MainMenuColors", "window_border_fill_b", pGlobal_menu_colors->window_border_fill.b);
    p_config_manager->AddValue("MainMenuColors", "window_border_fill_a", pGlobal_menu_colors->window_border_fill.a);

    p_config_manager->AddValue("MainMenuColors", "window_border_color_r", pGlobal_menu_colors->window_border_color.r);
    p_config_manager->AddValue("MainMenuColors", "window_border_color_g", pGlobal_menu_colors->window_border_color.g);
    p_config_manager->AddValue("MainMenuColors", "window_border_color_b", pGlobal_menu_colors->window_border_color.b);
    p_config_manager->AddValue("MainMenuColors", "window_border_color_a", pGlobal_menu_colors->window_border_color.a);

    p_config_manager->AddValue("MainMenuColors", "window_background_r", pGlobal_menu_colors->window_background.r);
    p_config_manager->AddValue("MainMenuColors", "window_background_g", pGlobal_menu_colors->window_background.g);
    p_config_manager->AddValue("MainMenuColors", "window_background_b", pGlobal_menu_colors->window_background.b);
    p_config_manager->AddValue("MainMenuColors", "window_background_a", pGlobal_menu_colors->window_background.a);

    p_config_manager->AddValue("MainMenuColors", "control_outline_r", pGlobal_menu_colors->control_outline.r);
    p_config_manager->AddValue("MainMenuColors", "control_outline_g", pGlobal_menu_colors->control_outline.g);
    p_config_manager->AddValue("MainMenuColors", "control_outline_b", pGlobal_menu_colors->control_outline.b);
    p_config_manager->AddValue("MainMenuColors", "control_outline_a", pGlobal_menu_colors->control_outline.a);

    p_config_manager->AddValue("MainMenuColors", "control_active_or_clicked_r", pGlobal_menu_colors->control_active_or_clicked.r);
    p_config_manager->AddValue("MainMenuColors", "control_active_or_clicked_g", pGlobal_menu_colors->control_active_or_clicked.g);
    p_config_manager->AddValue("MainMenuColors", "control_active_or_clicked_b", pGlobal_menu_colors->control_active_or_clicked.b);
    p_config_manager->AddValue("MainMenuColors", "control_active_or_clicked_a", pGlobal_menu_colors->control_active_or_clicked.a);

    p_config_manager->AddValue("MainMenuColors", "control_idle_r", pGlobal_menu_colors->control_idle.r);
    p_config_manager->AddValue("MainMenuColors", "control_idle_g", pGlobal_menu_colors->control_idle.g);
    p_config_manager->AddValue("MainMenuColors", "control_idle_b", pGlobal_menu_colors->control_idle.b);
    p_config_manager->AddValue("MainMenuColors", "control_idle_a", pGlobal_menu_colors->control_idle.a);

    p_config_manager->AddValue("MainMenuColors", "color_groupbox_bg_r", pGlobal_menu_colors->color_groupbox_bg.r);
    p_config_manager->AddValue("MainMenuColors", "color_groupbox_bg_g", pGlobal_menu_colors->color_groupbox_bg.g);
    p_config_manager->AddValue("MainMenuColors", "color_groupbox_bg_b", pGlobal_menu_colors->color_groupbox_bg.b);
    p_config_manager->AddValue("MainMenuColors", "color_groupbox_bg_a", pGlobal_menu_colors->color_groupbox_bg.a);

    p_config_manager->AddValue("MainMenuColors", "color_text_r", pGlobal_menu_colors->color_text.r);
    p_config_manager->AddValue("MainMenuColors", "color_text_g", pGlobal_menu_colors->color_text.g);
    p_config_manager->AddValue("MainMenuColors", "color_text_b", pGlobal_menu_colors->color_text.b);
    p_config_manager->AddValue("MainMenuColors", "color_text_a", pGlobal_menu_colors->color_text.a);

    p_config_manager->AddValue("MainMenuColors", "color_text_dimmer_r", pGlobal_menu_colors->color_text_dimmer.r);
    p_config_manager->AddValue("MainMenuColors", "color_text_dimmer_g", pGlobal_menu_colors->color_text_dimmer.g);
    p_config_manager->AddValue("MainMenuColors", "color_text_dimmer_b", pGlobal_menu_colors->color_text_dimmer.b);
    p_config_manager->AddValue("MainMenuColors", "color_text_dimmer_a", pGlobal_menu_colors->color_text_dimmer.a);

    p_config_manager->AddValue("MainMenuColors", "color_slider_r", pGlobal_menu_colors->color_slider.r);
    p_config_manager->AddValue("MainMenuColors", "color_slider_g", pGlobal_menu_colors->color_slider.g);
    p_config_manager->AddValue("MainMenuColors", "color_slider_b", pGlobal_menu_colors->color_slider.b);
    p_config_manager->AddValue("MainMenuColors", "color_slider_a", pGlobal_menu_colors->color_slider.a);

    p_config_manager->AddValue("MainMenuColors", "color_combo_bg_r", pGlobal_menu_colors->color_combo_bg.r);
    p_config_manager->AddValue("MainMenuColors", "color_combo_bg_g", pGlobal_menu_colors->color_combo_bg.g);
    p_config_manager->AddValue("MainMenuColors", "color_combo_bg_b", pGlobal_menu_colors->color_combo_bg.b);
    p_config_manager->AddValue("MainMenuColors", "color_combo_bg_a", pGlobal_menu_colors->color_combo_bg.a);

    p_config_manager->AddValue("MainMenuColors", "color_groupbox_header_r", pGlobal_menu_colors->color_groupbox_header.r);
    p_config_manager->AddValue("MainMenuColors", "color_groupbox_header_g", pGlobal_menu_colors->color_groupbox_header.g);
    p_config_manager->AddValue("MainMenuColors", "color_groupbox_header_b", pGlobal_menu_colors->color_groupbox_header.b);
    p_config_manager->AddValue("MainMenuColors", "color_groupbox_header_a", pGlobal_menu_colors->color_groupbox_header.a);

	p_config_manager->End();
}

void LoadSettings()
{
    MadFramework::Menu::MenuState& menuState = MadFramework::Menu::state = {};

    ConfigManager* p_config_manager = ConfigManager::Get();

    p_config_manager->Begin();

    p_config_manager->GetValue("MenuState", "aimbotTab", menuState.aimbotTab);
    p_config_manager->GetValue("MenuState", "visualsTab", menuState.visualsTab);
    p_config_manager->GetValue("MenuState", "miscTab", menuState.miscTab);
    p_config_manager->GetValue("MenuState", "settingsTab", menuState.settingsTab);

    p_config_manager->GetValue("Visuals", "vPlayers", menuState.vPlayers);
    p_config_manager->GetValue("Visuals", "vPlayer_box_2d", menuState.vPlayer_box_2d);
    p_config_manager->GetValue("Visuals", "vPlayer_name", menuState.vPlayer_name);
    p_config_manager->GetValue("Visuals", "vPlayerTeam", menuState.vPlayerTeam);
    p_config_manager->GetValue("Visuals", "vPlayer_health", menuState.vPlayer_health);
    p_config_manager->GetValue("Visuals", "vPlayer_distance", menuState.vPlayer_distance);
    p_config_manager->GetValue("Visuals", "vPlayer_weapon_info", menuState.vPlayer_weapon_info);
    p_config_manager->GetValue("Visuals", "vPlayer_health_bar", menuState.vPlayer_health_bar);
    p_config_manager->GetValue("Visuals", "vPlayer_bones", menuState.vPlayer_bones);
    p_config_manager->GetValue("Visuals", "vPlayer_snap_lines", menuState.vPlayer_snap_lines);
    p_config_manager->GetValue("Visuals", "vPlayer_edge_box", menuState.vPlayer_edge_box);
    p_config_manager->GetValue("Visuals", "vPlayer_speed", menuState.vPlayer_speed);
    p_config_manager->GetValue("Visuals", "vPlayer_FilledBox", menuState.vPlayer_FilledBox);

    p_config_manager->GetValue("World", "vWorld", menuState.vWorld);
    p_config_manager->GetValue("World", "vNpcs", menuState.vNpcs);
    p_config_manager->GetValue("World", "vNpc_box_2d", menuState.vNpc_box_2d);
    p_config_manager->GetValue("World", "vNpc_name", menuState.vNpc_name);
    p_config_manager->GetValue("World", "vNpc_health", menuState.vNpc_health);
    p_config_manager->GetValue("World", "vNpc_weapon_info", menuState.vNpc_weapon_info);
    p_config_manager->GetValue("World", "vNpc_health_bar", menuState.vNpc_health_bar);
    p_config_manager->GetValue("World", "vNpc_bones", menuState.vNpc_bones);
    p_config_manager->GetValue("World", "vNpc_snap_lines", menuState.vNpc_snap_lines);
    p_config_manager->GetValue("World", "vNpc_edge_box", menuState.vNpc_edge_box);
    p_config_manager->GetValue("World", "vNpc_FilledBox", menuState.vNpc_FilledBox);
    p_config_manager->GetValue("World", "vEntity_distance", menuState.vEntity_distance);
    p_config_manager->GetValue("World", "vGrenades", menuState.vGrenades);
    p_config_manager->GetValue("World", "vWeapons", menuState.vWeapons);

    p_config_manager->GetValue("VisualsSettings", "vVisbleCheck", menuState.vVisbleCheck);
    p_config_manager->GetValue("VisualsSettings", "vDrawFovCircle", menuState.vDrawFovCircle);
    p_config_manager->GetValue("VisualsSettings", "vFovCircleSize", menuState.vFovCircleSize);

    p_config_manager->GetValue("Aimbot", "aPlayers", menuState.aPlayers);
    p_config_manager->GetValue("Aimbot", "aNpcs", menuState.aNpcs);
    p_config_manager->GetValue("Aimbot", "aSilentAimPlayers", menuState.aSilentAimPlayers);
    p_config_manager->GetValue("Aimbot", "aSilentAimNpcs", menuState.aSilentAimNpcs);
    p_config_manager->GetValue("Aimbot", "aAimlockPlayers", menuState.aAimlockPlayers);
    p_config_manager->GetValue("Aimbot", "aAimlockNpcs", menuState.aAimlockNpcs);
    p_config_manager->GetValue("Aimbot", "aVisibleCheck", menuState.aVisibleCheck);
    p_config_manager->GetValue("Aimbot", "aInsideFovCircleCheck", menuState.aInsideFovCircleCheck);
    p_config_manager->GetValue("Aimbot", "aIgnoreTitans", menuState.aIgnoreTitans);
    p_config_manager->GetValue("Aimbot", "aAutoAttack", menuState.aAutoAttack);
    p_config_manager->GetValue("Aimbot", "aAutoZoom", menuState.aAutoZoom);
    p_config_manager->GetValue("Aimbot", "aAimlockKey", menuState.aAimlockKey);
    p_config_manager->GetValue("Aimbot", "aAimlockSmooth", menuState.aAimlockSmooth);
    p_config_manager->GetValue("Aimbot", "aAimlock_smoothness", menuState.aAimlock_smoothness);

    p_config_manager->GetValue("Misc", "mSpeedExploit", menuState.mSpeedExploit);
    p_config_manager->GetValue("Misc", "mAirstuck", menuState.mAirstuck);
    p_config_manager->GetValue("Misc", "mAirstuckKey", menuState.mAirstuckKey);
    p_config_manager->GetValue("Misc", "mViewmodelChanges", menuState.mViewmodelChanges);
    p_config_manager->GetValue("Misc", "mUnlockAllAchievements", menuState.mUnlockAllAchievements);
    p_config_manager->GetValue("Misc", "mCustomCrosshair", menuState.mCustomCrosshair);
    p_config_manager->GetValue("Misc", "mDisableGameCrosshair", menuState.mDisableGameCrosshair);
    p_config_manager->GetValue("Misc", "mSelectedCrosshairVariant", menuState.mSelectedCrosshairVariant);
    p_config_manager->GetValue("Misc", "mCustomCrosshairSize", menuState.mCustomCrosshairSize);
    p_config_manager->GetValue("Misc", "mHitSounds", menuState.mHitSounds);
    p_config_manager->GetValue("Misc", "mSelectedHitSound", menuState.mSelectedHitSound);
    p_config_manager->GetValue("Misc", "mHitSoundVolume", menuState.mHitSoundVolume);
    p_config_manager->GetValue("Misc", "mHitSoundPitch", menuState.mHitSoundPitch);
    p_config_manager->GetValue("Misc", "mSpeed", menuState.mSpeed);
    p_config_manager->GetValue("Misc", "mFov", menuState.mFov);
    p_config_manager->GetValue("Misc", "mViewmodel_fov", menuState.mViewmodel_fov);
    p_config_manager->GetValue("Misc", "mAutoMelee", menuState.mAutoMelee);

    p_config_manager->GetValue("MenuColors", "cPlayer_r", MadFramework::Menu::menu_colors.cPlayer.r);
    p_config_manager->GetValue("MenuColors", "cPlayer_g", MadFramework::Menu::menu_colors.cPlayer.g);
    p_config_manager->GetValue("MenuColors", "cPlayer_b", MadFramework::Menu::menu_colors.cPlayer.b);
    p_config_manager->GetValue("MenuColors", "cPlayer_a", MadFramework::Menu::menu_colors.cPlayer.a);

    p_config_manager->GetValue("MenuColors", "cPlayerBones_r", MadFramework::Menu::menu_colors.cPlayerBones.r);
    p_config_manager->GetValue("MenuColors", "cPlayerBones_g", MadFramework::Menu::menu_colors.cPlayerBones.g);
    p_config_manager->GetValue("MenuColors", "cPlayerBones_b", MadFramework::Menu::menu_colors.cPlayerBones.b);
    p_config_manager->GetValue("MenuColors", "cPlayerBones_a", MadFramework::Menu::menu_colors.cPlayerBones.a);

    p_config_manager->GetValue("MenuColors", "cNpc_r", MadFramework::Menu::menu_colors.cNpc.r);
    p_config_manager->GetValue("MenuColors", "cNpc_g", MadFramework::Menu::menu_colors.cNpc.g);
    p_config_manager->GetValue("MenuColors", "cNpc_b", MadFramework::Menu::menu_colors.cNpc.b);
    p_config_manager->GetValue("MenuColors", "cNpc_a", MadFramework::Menu::menu_colors.cNpc.a);

    p_config_manager->GetValue("MenuColors", "cNpcBones_r", MadFramework::Menu::menu_colors.cNpcBones.r);
    p_config_manager->GetValue("MenuColors", "cNpcBones_g", MadFramework::Menu::menu_colors.cNpcBones.g);
    p_config_manager->GetValue("MenuColors", "cNpcBones_b", MadFramework::Menu::menu_colors.cNpcBones.b);
    p_config_manager->GetValue("MenuColors", "cNpcBones_a", MadFramework::Menu::menu_colors.cNpcBones.a);

    p_config_manager->GetValue("MenuColors", "cNpcName_r", MadFramework::Menu::menu_colors.cNpcName.r);
    p_config_manager->GetValue("MenuColors", "cNpcName_g", MadFramework::Menu::menu_colors.cNpcName.g);
    p_config_manager->GetValue("MenuColors", "cNpcName_b", MadFramework::Menu::menu_colors.cNpcName.b);
    p_config_manager->GetValue("MenuColors", "cNpcName_a", MadFramework::Menu::menu_colors.cNpcName.a);

    p_config_manager->GetValue("MenuColors", "cNpcFilledBox_r", MadFramework::Menu::menu_colors.cNpcFilledBox.r);
    p_config_manager->GetValue("MenuColors", "cNpcFilledBox_g", MadFramework::Menu::menu_colors.cNpcFilledBox.g);
    p_config_manager->GetValue("MenuColors", "cNpcFilledBox_b", MadFramework::Menu::menu_colors.cNpcFilledBox.b);
    p_config_manager->GetValue("MenuColors", "cNpcFilledBox_a", MadFramework::Menu::menu_colors.cNpcFilledBox.a);

    p_config_manager->GetValue("MenuColors", "cPlayerName_r", MadFramework::Menu::menu_colors.cPlayerName.r);
    p_config_manager->GetValue("MenuColors", "cPlayerName_g", MadFramework::Menu::menu_colors.cPlayerName.g);
    p_config_manager->GetValue("MenuColors", "cPlayerName_b", MadFramework::Menu::menu_colors.cPlayerName.b);
    p_config_manager->GetValue("MenuColors", "cPlayerName_a", MadFramework::Menu::menu_colors.cPlayerName.a);

    p_config_manager->GetValue("MenuColors", "cPlayerFilledBox_r", MadFramework::Menu::menu_colors.cPlayerFilledBox.r);
    p_config_manager->GetValue("MenuColors", "cPlayerFilledBox_g", MadFramework::Menu::menu_colors.cPlayerFilledBox.g);
    p_config_manager->GetValue("MenuColors", "cPlayerFilledBox_b", MadFramework::Menu::menu_colors.cPlayerFilledBox.b);
    p_config_manager->GetValue("MenuColors", "cPlayerFilledBox_a", MadFramework::Menu::menu_colors.cPlayerFilledBox.a);

    p_config_manager->GetValue("MenuColors", "cInvPlayer_r", MadFramework::Menu::menu_colors.cInvPlayer.r);
    p_config_manager->GetValue("MenuColors", "cInvPlayer_g", MadFramework::Menu::menu_colors.cInvPlayer.g);
    p_config_manager->GetValue("MenuColors", "cInvPlayer_b", MadFramework::Menu::menu_colors.cInvPlayer.b);
    p_config_manager->GetValue("MenuColors", "cInvPlayer_a", MadFramework::Menu::menu_colors.cInvPlayer.a);

    p_config_manager->GetValue("MenuColors", "cInvPlayerBones_r", MadFramework::Menu::menu_colors.cInvPlayerBones.r);
    p_config_manager->GetValue("MenuColors", "cInvPlayerBones_g", MadFramework::Menu::menu_colors.cInvPlayerBones.g);
    p_config_manager->GetValue("MenuColors", "cInvPlayerBones_b", MadFramework::Menu::menu_colors.cInvPlayerBones.b);
    p_config_manager->GetValue("MenuColors", "cInvPlayerBones_a", MadFramework::Menu::menu_colors.cInvPlayerBones.a);

    p_config_manager->GetValue("MenuColors", "cInvPlayerFilledBox_r", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.r);
    p_config_manager->GetValue("MenuColors", "cInvPlayerFilledBox_g", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.g);
    p_config_manager->GetValue("MenuColors", "cInvPlayerFilledBox_b", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.b);
    p_config_manager->GetValue("MenuColors", "cInvPlayerFilledBox_a", MadFramework::Menu::menu_colors.cInvPlayerFilledBox.a);

    p_config_manager->GetValue("MenuColors", "cInvNpc_r", MadFramework::Menu::menu_colors.cInvNpc.r);
    p_config_manager->GetValue("MenuColors", "cInvNpc_g", MadFramework::Menu::menu_colors.cInvNpc.g);
    p_config_manager->GetValue("MenuColors", "cInvNpc_b", MadFramework::Menu::menu_colors.cInvNpc.b);
    p_config_manager->GetValue("MenuColors", "cInvNpc_a", MadFramework::Menu::menu_colors.cInvNpc.a);

    p_config_manager->GetValue("MenuColors", "cInvNpcBones_r", MadFramework::Menu::menu_colors.cInvNpcBones.r);
    p_config_manager->GetValue("MenuColors", "cInvNpcBones_g", MadFramework::Menu::menu_colors.cInvNpcBones.g);
    p_config_manager->GetValue("MenuColors", "cInvNpcBones_b", MadFramework::Menu::menu_colors.cInvNpcBones.b);
    p_config_manager->GetValue("MenuColors", "cInvNpcBones_a", MadFramework::Menu::menu_colors.cInvNpcBones.a);

    p_config_manager->GetValue("MenuColors", "cInvNpcName_r", MadFramework::Menu::menu_colors.cInvNpcName.r);
    p_config_manager->GetValue("MenuColors", "cInvNpcName_g", MadFramework::Menu::menu_colors.cInvNpcName.g);
    p_config_manager->GetValue("MenuColors", "cInvNpcName_b", MadFramework::Menu::menu_colors.cInvNpcName.b);
    p_config_manager->GetValue("MenuColors", "cInvNpcName_a", MadFramework::Menu::menu_colors.cInvNpcName.a);

    p_config_manager->GetValue("MenuColors", "cInvPlayerName_r", MadFramework::Menu::menu_colors.cInvPlayerName.r);
    p_config_manager->GetValue("MenuColors", "cInvPlayerName_g", MadFramework::Menu::menu_colors.cInvPlayerName.g);
    p_config_manager->GetValue("MenuColors", "cInvPlayerName_b", MadFramework::Menu::menu_colors.cInvPlayerName.b);
    p_config_manager->GetValue("MenuColors", "cInvPlayerName_a", MadFramework::Menu::menu_colors.cInvPlayerName.a);

    p_config_manager->GetValue("MenuColors", "cInvNpcFilledBox_r", MadFramework::Menu::menu_colors.cInvNpcFilledBox.r);
    p_config_manager->GetValue("MenuColors", "cInvNpcFilledBox_g", MadFramework::Menu::menu_colors.cInvNpcFilledBox.g);
    p_config_manager->GetValue("MenuColors", "cInvNpcFilledBox_b", MadFramework::Menu::menu_colors.cInvNpcFilledBox.b);
    p_config_manager->GetValue("MenuColors", "cInvNpcFilledBox_a", MadFramework::Menu::menu_colors.cInvNpcFilledBox.a);

    p_config_manager->GetValue("MenuColors", "cFovCircle_r", MadFramework::Menu::menu_colors.cFovCircle.r);
    p_config_manager->GetValue("MenuColors", "cFovCircle_g", MadFramework::Menu::menu_colors.cFovCircle.g);
    p_config_manager->GetValue("MenuColors", "cFovCircle_b", MadFramework::Menu::menu_colors.cFovCircle.b);
    p_config_manager->GetValue("MenuColors", "cFovCircle_a", MadFramework::Menu::menu_colors.cFovCircle.a);

    decltype(zgui::get_menu_colors()) pGlobal_menu_colors = zgui::get_menu_colors();

    p_config_manager->GetValue("MainMenuColors", "window_border_inner_fill_r", pGlobal_menu_colors->window_border_inner_fill.r);
    p_config_manager->GetValue("MainMenuColors", "window_border_inner_fill_g", pGlobal_menu_colors->window_border_inner_fill.g);
    p_config_manager->GetValue("MainMenuColors", "window_border_inner_fill_b", pGlobal_menu_colors->window_border_inner_fill.b);
    p_config_manager->GetValue("MainMenuColors", "window_border_inner_fill_a", pGlobal_menu_colors->window_border_inner_fill.a);

    p_config_manager->GetValue("MainMenuColors", "window_border_fill_r", pGlobal_menu_colors->window_border_fill.r);
    p_config_manager->GetValue("MainMenuColors", "window_border_fill_g", pGlobal_menu_colors->window_border_fill.g);
    p_config_manager->GetValue("MainMenuColors", "window_border_fill_b", pGlobal_menu_colors->window_border_fill.b);
    p_config_manager->GetValue("MainMenuColors", "window_border_fill_a", pGlobal_menu_colors->window_border_fill.a);

    p_config_manager->GetValue("MainMenuColors", "window_border_color_r", pGlobal_menu_colors->window_border_color.r);
    p_config_manager->GetValue("MainMenuColors", "window_border_color_g", pGlobal_menu_colors->window_border_color.g);
    p_config_manager->GetValue("MainMenuColors", "window_border_color_b", pGlobal_menu_colors->window_border_color.b);
    p_config_manager->GetValue("MainMenuColors", "window_border_color_a", pGlobal_menu_colors->window_border_color.a);

    p_config_manager->GetValue("MainMenuColors", "window_background_r", pGlobal_menu_colors->window_background.r);
    p_config_manager->GetValue("MainMenuColors", "window_background_g", pGlobal_menu_colors->window_background.g);
    p_config_manager->GetValue("MainMenuColors", "window_background_b", pGlobal_menu_colors->window_background.b);
    p_config_manager->GetValue("MainMenuColors", "window_background_a", pGlobal_menu_colors->window_background.a);

    p_config_manager->GetValue("MainMenuColors", "control_outline_r", pGlobal_menu_colors->control_outline.r);
    p_config_manager->GetValue("MainMenuColors", "control_outline_g", pGlobal_menu_colors->control_outline.g);
    p_config_manager->GetValue("MainMenuColors", "control_outline_b", pGlobal_menu_colors->control_outline.b);
    p_config_manager->GetValue("MainMenuColors", "control_outline_a", pGlobal_menu_colors->control_outline.a);

    p_config_manager->GetValue("MainMenuColors", "control_active_or_clicked_r", pGlobal_menu_colors->control_active_or_clicked.r);
    p_config_manager->GetValue("MainMenuColors", "control_active_or_clicked_g", pGlobal_menu_colors->control_active_or_clicked.g);
    p_config_manager->GetValue("MainMenuColors", "control_active_or_clicked_b", pGlobal_menu_colors->control_active_or_clicked.b);
    p_config_manager->GetValue("MainMenuColors", "control_active_or_clicked_a", pGlobal_menu_colors->control_active_or_clicked.a);

    p_config_manager->GetValue("MainMenuColors", "control_idle_r", pGlobal_menu_colors->control_idle.r);
    p_config_manager->GetValue("MainMenuColors", "control_idle_g", pGlobal_menu_colors->control_idle.g);
    p_config_manager->GetValue("MainMenuColors", "control_idle_b", pGlobal_menu_colors->control_idle.b);
    p_config_manager->GetValue("MainMenuColors", "control_idle_a", pGlobal_menu_colors->control_idle.a);

    p_config_manager->GetValue("MainMenuColors", "color_groupbox_bg_r", pGlobal_menu_colors->color_groupbox_bg.r);
    p_config_manager->GetValue("MainMenuColors", "color_groupbox_bg_g", pGlobal_menu_colors->color_groupbox_bg.g);
    p_config_manager->GetValue("MainMenuColors", "color_groupbox_bg_b", pGlobal_menu_colors->color_groupbox_bg.b);
    p_config_manager->GetValue("MainMenuColors", "color_groupbox_bg_a", pGlobal_menu_colors->color_groupbox_bg.a);

    p_config_manager->GetValue("MainMenuColors", "color_text_r", pGlobal_menu_colors->color_text.r);
    p_config_manager->GetValue("MainMenuColors", "color_text_g", pGlobal_menu_colors->color_text.g);
    p_config_manager->GetValue("MainMenuColors", "color_text_b", pGlobal_menu_colors->color_text.b);
    p_config_manager->GetValue("MainMenuColors", "color_text_a", pGlobal_menu_colors->color_text.a);

    p_config_manager->GetValue("MainMenuColors", "color_text_dimmer_r", pGlobal_menu_colors->color_text_dimmer.r);
    p_config_manager->GetValue("MainMenuColors", "color_text_dimmer_g", pGlobal_menu_colors->color_text_dimmer.g);
    p_config_manager->GetValue("MainMenuColors", "color_text_dimmer_b", pGlobal_menu_colors->color_text_dimmer.b);
    p_config_manager->GetValue("MainMenuColors", "color_text_dimmer_a", pGlobal_menu_colors->color_text_dimmer.a);

    p_config_manager->GetValue("MainMenuColors", "color_slider_r", pGlobal_menu_colors->color_slider.r);
    p_config_manager->GetValue("MainMenuColors", "color_slider_g", pGlobal_menu_colors->color_slider.g);
    p_config_manager->GetValue("MainMenuColors", "color_slider_b", pGlobal_menu_colors->color_slider.b);
    p_config_manager->GetValue("MainMenuColors", "color_slider_a", pGlobal_menu_colors->color_slider.a);

    p_config_manager->GetValue("MainMenuColors", "color_combo_bg_r", pGlobal_menu_colors->color_combo_bg.r);
    p_config_manager->GetValue("MainMenuColors", "color_combo_bg_g", pGlobal_menu_colors->color_combo_bg.g);
    p_config_manager->GetValue("MainMenuColors", "color_combo_bg_b", pGlobal_menu_colors->color_combo_bg.b);
    p_config_manager->GetValue("MainMenuColors", "color_combo_bg_a", pGlobal_menu_colors->color_combo_bg.a);

    p_config_manager->GetValue("MainMenuColors", "color_groupbox_header_r", pGlobal_menu_colors->color_groupbox_header.r);
    p_config_manager->GetValue("MainMenuColors", "color_groupbox_header_g", pGlobal_menu_colors->color_groupbox_header.g);
    p_config_manager->GetValue("MainMenuColors", "color_groupbox_header_b", pGlobal_menu_colors->color_groupbox_header.b);
    p_config_manager->GetValue("MainMenuColors", "color_groupbox_header_a", pGlobal_menu_colors->color_groupbox_header.a);

    p_config_manager->End();
}