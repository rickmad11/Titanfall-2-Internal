#include "pch.h"

#include "Menu.h"

#include "Features/Aimbot/Aimbot.h"
#include "Features/Misc/SaveManager.h"

static MadRenderer::RenderList* g_pForegroundRenderList = nullptr;
static MadRenderer::DX11* g_pRenderer = nullptr;

static void ZguiDrawLine(int x, int y, int x2, int y2, zgui::color color) noexcept
{
	if(g_pForegroundRenderList)
	{
		g_pForegroundRenderList->DrawLine({ static_cast<float>(x), static_cast<float>(y) },
			{ static_cast<float>(x2), static_cast<float>(y2) },
			{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
	}
}

static void ZguiDrawRect(int x, int y, int x2, int y2, zgui::color color) noexcept
{
	if(g_pForegroundRenderList)
	{
		g_pForegroundRenderList->DrawRect({ static_cast<float>(x), static_cast<float>(y), static_cast<float>(x2), static_cast<float>(y2) }, 0.f,
			{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
	}
}

static void ZguiDrawFilledRect(int x, int y, int x2, int y2, zgui::color color) noexcept
{
	if (g_pForegroundRenderList)
	{
		g_pForegroundRenderList->DrawFilledRect({ static_cast<float>(x), static_cast<float>(y), static_cast<float>(x2), static_cast<float>(y2) },
			{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) });
	}
}

static void ZguiDrawText(int x, int y, zgui::color color, int font, bool center, const char* text) noexcept
{
	UNREFERENCED_PARAMETER(font);

	if(g_pForegroundRenderList)
	{
		if(center)
		{
			MadRenderer::RenderList::Vector2 string_size = g_pForegroundRenderList->MeasureString(text);
			x -= static_cast<int>( (string_size.x * MadFramework::Menu::g_text_scale) * .5f );
		}

		g_pForegroundRenderList->DrawString(text, { static_cast<float>(x), static_cast<float>(y) }, 
			{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) }, MadFramework::Menu::g_text_scale);
	}
}

static void ZguiGetTextSize(unsigned long font, const char* text, int& width, int& height) noexcept
{
	UNREFERENCED_PARAMETER(font);

	if(g_pForegroundRenderList)
	{
		MadRenderer::RenderList::Vector2 string_size = g_pForegroundRenderList->MeasureString(text);

		width = static_cast<int>(string_size.x * MadFramework::Menu::g_text_scale);
		height = static_cast<int>(string_size.y * MadFramework::Menu::g_text_scale);
	}
}

static float ZguiGetFrameTime() noexcept
{
	return static_cast<float>(MadFramework::Utility::GetCurrentFpsCount<1>());
}

void HandleClipboardData(std::string& message)
{
	if (!OpenClipboard(nullptr))
		return;

	if (HANDLE h_clipboard = GetClipboardData(CF_TEXT))
	{
		if (const char* pszText = static_cast<const char*>(GlobalLock(h_clipboard)))
		{
			message.clear();
			message = pszText;
			GlobalUnlock(h_clipboard);
		}
	}

	CloseClipboard();
}

void MadFramework::Menu::SetupZGUI() noexcept
{
	g_pForegroundRenderList = MadRenderer::DX11::Get()->GetForegroundRenderList();
	g_pRenderer = MadRenderer::DX11::Get();

	zgui::functions.draw_line = ZguiDrawLine;
	zgui::functions.draw_rect = ZguiDrawRect;
	zgui::functions.draw_filled_rect = ZguiDrawFilledRect;
	zgui::functions.draw_text = ZguiDrawText;
	zgui::functions.get_text_size = ZguiGetTextSize;
	zgui::functions.get_frametime = ZguiGetFrameTime;
}

void MadFramework::Menu::Render() noexcept
{
	zgui::poll_input(g_pRenderer->windowHandle, g_pRenderer->windowWidth, g_pRenderer->windowHeight);

	constexpr int menuWidth = 850;
	constexpr int menuHeight = 480;

	constexpr int buttonWidth = 200;
	constexpr int buttonHeight = 25;
	constexpr int buttonCount = 4;

	constexpr int groupBoxWidth = static_cast<int>(menuWidth * .313f);
	constexpr int groupBoxHeight = static_cast<int>(menuHeight * .85f);

	static bool init = false;
	//Spawn Menu Centered
	if (!init)
	{
		zgui::globals::window_ctx.position = zgui::vec2
		{
			(static_cast<float>(MadRenderer::DX11::Get()->windowWidth) * 0.5f) - (menuWidth * 0.5f),
			(static_cast<float>(MadRenderer::DX11::Get()->windowHeight) * 0.5f) - (menuHeight * 0.5f)
		};

		LoadMenuKeyBind();

		init = true;
	}

	if (zgui::begin_window("Titanfall 2 Internal Public Build v2.1", { menuWidth - 16, menuHeight }, NULL, zgui::zgui_window_flags_no_ontoggle_animation)) {

		zgui::tab_button("Aimbot", { buttonWidth, buttonHeight }, state.aimbotTab);

		if (state.aimbotTab)
		{
			state.visualsTab = false;
			state.miscTab = false;
			state.settingsTab = false;
		}

		zgui::next_column(buttonWidth, 0);
		zgui::tab_button("Visuals", { buttonWidth, buttonHeight }, state.visualsTab);

		if (state.visualsTab)
		{
			state.aimbotTab = false;
			state.miscTab = false;
			state.settingsTab = false;
		}


		zgui::next_column(buttonWidth, 0);
		zgui::tab_button("Misc", { buttonWidth, buttonHeight }, state.miscTab);

		if (state.miscTab)
		{
			state.aimbotTab = false;
			state.visualsTab = false;
			state.settingsTab = false;
		}

		zgui::next_column(buttonWidth, 0);
		zgui::tab_button("Settings", { buttonWidth, buttonHeight }, state.settingsTab);

		if (state.settingsTab)
		{
			state.aimbotTab = false;
			state.visualsTab = false;
			state.miscTab = false;
		}

		zgui::next_column(-( (buttonCount - 1) * buttonWidth), buttonHeight + 10 );

		if (state.aimbotTab)
		{
			static const std::vector<std::string> bone_names{ "Head", "Neck" , "Pelvis"};
			static std::vector<zgui::multi_select_item_thread_safe> selectable_targest{};

			zgui::begin_groupbox("Players", { groupBoxWidth, groupBoxHeight });
			{
				zgui::checkbox("Enable Player Aimbot", state.aPlayers);
				zgui::checkbox("Silent Aim#2", state.aSilentAimPlayers);
				zgui::checkbox("Aimlock#1", state.aAimlockPlayers);

				zgui::combobox("Aimbot Target Player Bone", bone_names, reinterpret_cast<int&>(state.aBonePlayer));

				for (size_t i = 0; i < 3; i++) 
					zgui::dummy(); //ghetto fix lol

				zgui::checkbox("Hate Mode", state.hate_mode);

				if (zgui::button("Refresh List", { 120, 20 }))
					RefreshPlayerList();

				zgui::multi_combobox("Rage On Selected Player", selectable_targest);

				if (state.hate_mode)
					UpdateHateModeTargets(selectable_targest);
			}
			zgui::end_groupbox();

			zgui::next_column(groupBoxWidth + 2, buttonHeight + 10);

			zgui::begin_groupbox("Npcs", { groupBoxWidth, groupBoxHeight });
			{
				zgui::checkbox("Enable Npc Aimbot", state.aNpcs);
				zgui::checkbox("Silent Aim#1", state.aSilentAimNpcs);
				zgui::checkbox("Aimlock#2", state.aAimlockNpcs);

				zgui::combobox("Aimbot Target Npc Bone", bone_names, reinterpret_cast<int&>(state.aBoneNpc));
			}
			zgui::end_groupbox();

			zgui::next_column(groupBoxWidth + 2, buttonHeight + 10);

			zgui::begin_groupbox("Settings", { groupBoxWidth, groupBoxHeight });
			{
				zgui::checkbox("Visible Check", state.aVisibleCheck);
				zgui::checkbox("Fov Circle Check", state.aInsideFovCircleCheck);
				zgui::checkbox("Ignore Titans", state.aIgnoreTitans);
				zgui::checkbox("Autto Attack", state.aAutoAttack);
				zgui::checkbox("Autto Zoom", state.aAutoZoom);
				zgui::checkbox("Auto Melee", state.mAutoMelee);

				zgui::dummy();

				zgui::key_bind("Aimlock Key", state.aAimlockKey);
				zgui::checkbox("Aimlock enable smoothing", state.aAimlockSmooth);
				zgui::slider_float("Aimlock smooth", 0.f, 100.f, state.aAimlock_smoothness);
				zgui::checkbox("Only Close Range", state.aOnlyCloseRange);
				zgui::checkbox("Aimbot Prediction", state.aPrediction);
			}
			zgui::end_groupbox();
		}

		if (state.visualsTab)
		{
			zgui::begin_groupbox("Players", { groupBoxWidth, groupBoxHeight });
			{
				zgui::checkbox("Enable Player ESP", state.vPlayers);
				zgui::checkbox("Team ESP", state.vPlayerTeam);
				zgui::checkbox("2D Box", state.vPlayer_box_2d);
				zgui::checkbox("Name", state.vPlayer_name);
				zgui::checkbox("Thick Name Box", state.vPlayer_ThickBoxName);
				zgui::checkbox("Health", state.vPlayer_health);
				zgui::checkbox("Health Bar", state.vPlayer_health_bar);
				zgui::checkbox("Distance", state.vPlayer_distance);
				zgui::checkbox("Weapon Info", state.vPlayer_weapon_info);
				zgui::checkbox("Bones", state.vPlayer_bones);
				zgui::checkbox("SnapLine", state.vPlayer_snap_lines);
				zgui::checkbox("EdgeBox", state.vPlayer_edge_box);
				zgui::checkbox("Speed", state.vPlayer_speed);
				zgui::checkbox("Filled Box", state.vPlayer_FilledBox);
				zgui::checkbox("OOF Arrow", state.vPlayer_OOFArrow);
				zgui::slider_float("OOF Arrow Radius", 10.f, 500.f, state.vOOFArrow_Radius);
			}
			zgui::end_groupbox();

			zgui::next_column(groupBoxWidth + 2, buttonHeight + 10);

			zgui::begin_groupbox("World", { groupBoxWidth, groupBoxHeight });
			{
				zgui::checkbox("Enable World ESP", state.vWorld);
				zgui::checkbox("Enable Npc ESP", state.vNpcs);
				zgui::checkbox("NPC 2D Box", state.vNpc_box_2d);
				zgui::checkbox("Npc Name", state.vNpc_name);
				zgui::checkbox("Thick Npc Name Box", state.vNpc_ThickBoxName);
				zgui::checkbox("Npc Health", state.vNpc_health);
				zgui::checkbox("Npc Health Bar", state.vNpc_health_bar);
				zgui::checkbox("Npc Weapon Info", state.vNpc_weapon_info);
				zgui::checkbox("Npc Bones", state.vNpc_bones);
				zgui::checkbox("Npc SnapLine", state.vNpc_snap_lines);
				zgui::checkbox("Npc EdgeBox", state.vNpc_edge_box);
				zgui::checkbox("Npc Filled Box", state.vNpc_FilledBox);
				zgui::checkbox("Entity Distance", state.vEntity_distance);
				zgui::checkbox("Grenades ESP", state.vGrenades);
				zgui::checkbox("Weapons ESP", state.vWeapons);
			}
			zgui::end_groupbox();

			zgui::next_column(groupBoxWidth + 2, buttonHeight + 10);

			zgui::begin_groupbox("Settings", { groupBoxWidth, groupBoxHeight });
			{
				zgui::color_picker("Player Color", menu_colors.cPlayer, 150);
				zgui::color_picker("Player Bones Color", menu_colors.cPlayerBones, 150);
				zgui::color_picker("Player Name Color", menu_colors.cPlayerName, 150);
				zgui::color_picker("Player Filled Box Color", menu_colors.cPlayerFilledBox, 150);
				zgui::color_picker("Player OOF Arrow Color", menu_colors.cPlayerOOFArrow, 150);
				zgui::color_picker("Npc Color", menu_colors.cNpc, 150);
				zgui::color_picker("Npc Bones Color", menu_colors.cNpcBones, 150);
				zgui::color_picker("Npc Name Color", menu_colors.cNpcName, 150);
				zgui::color_picker("Npc Filled Box Color", menu_colors.cNpcFilledBox, 150);

				zgui::dummy();

				zgui::checkbox("Visible Check", state.vVisbleCheck);
				zgui::color_picker("Invisible Player Color", menu_colors.cInvPlayer, 150);
				zgui::color_picker("Invisible Player Bones Color", menu_colors.cInvPlayerBones, 150);
				zgui::color_picker("Invisible Player Name Color", menu_colors.cInvPlayerName, 150);
				zgui::color_picker("Invisible Player Filled Box Color", menu_colors.cInvPlayerFilledBox, 150);
				zgui::color_picker("Invisible Player OOF Arrow Color", menu_colors.cInvPlayerOOFArrow, 150);
				zgui::color_picker("Invisible Npc Color", menu_colors.cInvNpc, 150);
				zgui::color_picker("Invisible Npc Bones Color", menu_colors.cInvNpcBones, 150);
				zgui::color_picker("Invisible Npc Name Color", menu_colors.cInvNpcName, 150);
				zgui::color_picker("Invisible Npc Filled Box Color", menu_colors.cInvNpcFilledBox, 150);

				zgui::dummy();
				zgui::checkbox("Draw Fov Circle", state.vDrawFovCircle);
				zgui::slider_float("Fov Circle Size", 0.f, 720.f, state.vFovCircleSize);

				zgui::color_picker("Fov Circle Color", menu_colors.cFovCircle, 150);
			}
			zgui::end_groupbox();
		}

		if(state.miscTab)
		{
			static const std::vector<std::string> hit_sounds{ "Rust HS", "Skeet" , "CoD" };
			static const std::vector<std::string> crosshair_variants{ "Variant 1", "Variant 2" , "Variant 3" };

			zgui::begin_groupbox("World", { groupBoxWidth * 3.018f, groupBoxHeight });
			{
				zgui::checkbox("UnlockAllAchievements", state.mUnlockAllAchievements);
				zgui::checkbox("SpeedExploit", state.mSpeedExploit);
				zgui::slider_float("Speed", 0.f, 0.01f, state.mSpeed);
				zgui::checkbox("Airstuck Enable", state.mAirstuck);
				zgui::key_bind("Airstuck Key", state.mAirstuckKey);
				zgui::checkbox("Enable Viewmodel Modifiers", state.mViewmodelChanges);
				zgui::slider_float("Fov", 0.750f, 3.f, state.mFov);
				zgui::slider_float("Viewmodel Fov", 0.4f, 1.875f, state.mViewmodel_fov);

				zgui::dummy();

				zgui::slider_float("Hit Sound Volume", 1.f, 5.f, state.mHitSoundVolume);
				zgui::slider_float("Hit Sound Pitch", 0.f, 10.f, state.mHitSoundPitch);
				zgui::checkbox("Hit Sounds", state.mHitSounds);
				zgui::same_line();
				zgui::combobox("Sound List", hit_sounds, state.mSelectedHitSound);

				zgui::next_column(174, 18);

				zgui::dummy();
				zgui::checkbox("Enable Custom Crosshair", state.mCustomCrosshair);
				zgui::checkbox("Disable Standard Crosshair", state.mDisableGameCrosshair);
				zgui::slider_float("Crosshair Size", 0.f, 0.5f, state.mCustomCrosshairSize);
				zgui::combobox("Crosshair Variants", crosshair_variants, state.mSelectedCrosshairVariant);

				zgui::dummy();

				zgui::checkbox("Bhop Auto Strafe", state.bhop);

				zgui::checkbox("Enable Fake Angles", state.fake_angles);
				zgui::checkbox("Fake Down", state.fake_down_angle);
				zgui::checkbox("Fake Up", state.fake_up_angle);

				zgui::dummy();

				zgui::checkbox("Infinite Money", state.infinite_money);
				zgui::checkbox("Skin Changer", state.skin_changer);

				zgui::slider_int("Skin ID", 0, 50, state.selected_skinID);

				zgui::dummy();

				zgui::checkbox("Server Info Log", state.log_server_info);

				if (zgui::button("Get Server IP", { 120, 20 }))
					state.log_current_server_info = true;

				zgui::next_column(174, 18);

				zgui::dummy();

				zgui::checkbox("Chat Spam", state.chat_spam);

				static std::string user_input{};

				if (zgui::button("Get Clipboard text", {120, 20}))
					HandleClipboardData(user_input);

				if (zgui::button("Clear Message", { 120, 20 }))
					user_input.clear();

				zgui::text_input("Chat Spam Text", user_input, 200, 20, 64, 0);

				if (!user_input.empty())
					state.chat_message = user_input.c_str();
			}
			zgui::end_groupbox();
		}

		if(state.settingsTab)
		{
			zgui::begin_groupbox("Menu Settings", { groupBoxWidth * 3.018f, groupBoxHeight });
			{
				zgui::menu_color_options();

				if(zgui::button("Save Config", {120, 20 }))
					state.mSaveConfig = true;

				if (zgui::button("Load Config", { 120, 20 }))
					state.mLoadConfig = true;

				static int selected_config = 0;
				static std::vector<std::string> config_names{ ConfigManager::default_string };

				//this should also be in the config manager but i dont care about this project anymore so i want this to be quickly finished
				static bool configs_parsed = false;
				if (!configs_parsed)
				{
					configs_parsed = true;

					std::unordered_set<std::string> _dup(config_names.begin(), config_names.end());

					for (std::string _config : ConfigManager::Get()->GetAllConfigs())
					{
						if (_dup.insert(_config).second)
							config_names.push_back(_config);
					}

					selected_config = static_cast<int>(config_names.size()) - 1;
				}

				static std::string config_name = {};
				zgui::text_input("Config Name", config_name, 200, 20, 32, 0);

				if (zgui::button("Create Config", { 120, 20 }))
				{
					config_names.push_back(config_name);
					++selected_config;

					//This should be a separate function somewhere else also 

					constexpr int min_size = sizeof(".ini") - 1;
					if (config_names[selected_config].length() > min_size)
					{
						if (config_names[selected_config].compare(config_names[selected_config].length() - min_size, min_size, std::string{ ".ini" }))
						{
							config_names[selected_config] += ".ini";
						}
					}
					else
						config_names[selected_config] += ".ini";

					if (!ConfigManager::Get()->InitializeConfigManager(config_names[selected_config]))
					{
						PLOG_WARNING << "failed initializing config";
						config_names.erase(config_names.cbegin() + selected_config - 1);
						--selected_config;
					}
				}

				if (zgui::button("Remove Config", { 120, 20 }))
				{
					if (selected_config != 0) //Main Config File no reason to delete it imo
					{
						ConfigManager::Get()->RemoveConfigFile();
						config_names.erase(config_names.cbegin() + selected_config);
						--selected_config;
					}
				}

				if (selected_config > config_names.size() || selected_config < 0)
					selected_config = static_cast<int>(config_names.size()) - 1;

				state.mSelectedConfigName = config_names[selected_config].c_str();

				if (state.mSelectedConfigName)
					ConfigManager::Get()->UpdateConfigFile(state.mSelectedConfigName);

				zgui::combobox("Config ComboBox", config_names, selected_config, 150, 20);

				zgui::next_column(174, 18);
				zgui::dummy();

				zgui::key_bind("Menu Open/Close Key", reinterpret_cast<int&>(config.MenuOpenKey));

				if (zgui::button("Save Keybind", { 120, 20 }))
					SaveMenuKeyBind(config.MenuOpenKey);
			}
			zgui::end_groupbox();
		}


		zgui::end_window();
	}
}

void MadFramework::Menu::Cursor() noexcept
{
	MadRenderer::TextureManager* pTextureManager = g_pRenderer->GetTextureRenderList();

	static int s_TextureID = pTextureManager->AddTexture(CursorData, sizeof(CursorData));

	POINT mouse_pos;
	GetCursorPos(&mouse_pos);
	ScreenToClient(g_pRenderer->windowHandle, &mouse_pos);

	//This hardcoded offset is there to adjust the image so it is almost in the same position as the actual mouse, otherwise clicks might be missed since the actual mouse is off
	//If you want to change the Cursor to another style make sure to adjust the position of the image with the real cursor position
	pTextureManager->DrawTexture({ static_cast<float>(mouse_pos.x - 6.3), static_cast<float>(mouse_pos.y - 0.3) }, s_TextureID);
}

