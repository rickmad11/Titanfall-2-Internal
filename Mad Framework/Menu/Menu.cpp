#include "pch.h"

#include "Menu.h"

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

	if (zgui::begin_window("Titanfall 2 Internal Public Build v1.1", { menuWidth - 16, menuHeight }, NULL)) {

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

			zgui::begin_groupbox("Players", { groupBoxWidth, groupBoxHeight });
			{
				zgui::checkbox("Enable Player Aimbot", state.aPlayers);
				zgui::checkbox("Silent Aim#2", state.aSilentAimPlayers);
				zgui::checkbox("Aimlock#1", state.aAimlockPlayers);

				zgui::combobox("Aimbot Target Player Bone", bone_names, reinterpret_cast<int&>(state.aBonePlayer));
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
				zgui::checkbox("Health", state.vPlayer_health);
				zgui::checkbox("Health Bar", state.vPlayer_health_bar);
				zgui::checkbox("Distance", state.vPlayer_distance);
				zgui::checkbox("Weapon Info", state.vPlayer_weapon_info);
				zgui::checkbox("Bones", state.vPlayer_bones);
				zgui::checkbox("SnapLine", state.vPlayer_snap_lines);
				zgui::checkbox("EdgeBox", state.vPlayer_edge_box);
				zgui::checkbox("Speed", state.vPlayer_speed);
				zgui::checkbox("Filled Box", state.vPlayer_FilledBox);
			}
			zgui::end_groupbox();

			zgui::next_column(groupBoxWidth + 2, buttonHeight + 10);

			zgui::begin_groupbox("World", { groupBoxWidth, groupBoxHeight });
			{
				zgui::checkbox("Enable World ESP", state.vWorld);
				zgui::checkbox("Enable Npc ESP", state.vNpcs);
				zgui::checkbox("NPC 2D Box", state.vNpc_box_2d);
				zgui::checkbox("Npc Name", state.vNpc_name);
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
				zgui::slider_float("Speed", 0.f, 0.003f, state.mSpeed);
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

