#pragma once

namespace MadFramework::Menu
{
	constexpr float g_text_scale = 1.f;

	struct Config
	{
		std::size_t MenuOpenKey = VK_INSERT;
		std::size_t PanicKey = VK_END;
	}inline config {};

	struct MenuState //this struct is being access in a non thread safe way everywhere, seems fine for now xD
	{
		bool aimbotTab = true;
		bool visualsTab = false;
		bool miscTab = false;
		bool settingsTab = false;

		//Visuals Player
		bool vPlayers = false;
		bool vPlayer_box_2d = false;
		bool vPlayer_name = false;
		bool vPlayerTeam = false;
		bool vPlayer_health = false;
		bool vPlayer_distance = false;
		bool vPlayer_weapon_info = false;
		bool vPlayer_health_bar = false;
		bool vPlayer_bones = false;
		bool vPlayer_snap_lines = false;
		bool vPlayer_edge_box = false;
		bool vPlayer_speed = false;
		bool vPlayer_FilledBox = false;

		//Visuals World
		bool vWorld = false;
		bool vNpcs = false;
		bool vNpc_box_2d = false;
		bool vNpc_name = false;
		bool vNpc_health = false;
		bool vNpc_weapon_info = false;
		bool vNpc_health_bar = false;
		bool vNpc_bones = false;
		bool vNpc_snap_lines = false;
		bool vNpc_edge_box = false;
		bool vNpc_FilledBox = false;
		bool vEntity_distance = false;
		bool vGrenades = false;
		bool vWeapons = false;

		//Visuals Settings
		bool vVisbleCheck = false;
		bool vDrawFovCircle = false;
		float vFovCircleSize = 30.f;

		//Aimbot Player and Npc
		bool aPlayers = false;
		bool aNpcs = false;
		bool aSilentAimPlayers = false;
		bool aSilentAimNpcs = false;
		bool aAimlockPlayers = false;
		bool aAimlockNpcs = false;
		bool aVisibleCheck = false;
		bool aInsideFovCircleCheck = false;
		bool aIgnoreTitans = false;
		bool aAutoAttack = false;
		bool aAutoZoom = false;
		int aAimlockKey = VK_LBUTTON;
		bool aAimlockSmooth = false;
		float aAimlock_smoothness = 0.f;

		//Misc
		bool mSpeedExploit = false;
		bool mAirstuck = false;
		int mAirstuckKey = 'M';
		bool mViewmodelChanges = false;
		bool mUnlockAllAchievements = false;
		bool mCustomCrosshair = false;
		bool mDisableGameCrosshair = false;
		int mSelectedCrosshairVariant = 0;
		float mCustomCrosshairSize = 0.15f;

		bool mHitSounds = false;
		int mSelectedHitSound = 0;
		float mHitSoundVolume = 1.f;
		float mHitSoundPitch = 0.f;

		float mSpeed = 0.f;
		float mFov = 0.750f;
		float mViewmodel_fov = 1.875f;

		bool mAutoMelee = false;

		bool mLoadConfig = false;
		bool mSaveConfig = false;

		enum AimbotBone : int //Has to map to the bone names vector inside menu, (yes im aware I should really change this)
		{
			Head,
			Neck,
			Pelvis,
		}aBonePlayer {}, aBoneNpc {};

	}inline state {};

	struct MenuColors
	{
		//Visible
		zgui::color cPlayer {255, 255, 255, 255};
		zgui::color cPlayerBones{ 255, 255, 255, 255 };
		zgui::color cNpc{ 255, 255, 255, 255 };
		zgui::color cNpcBones{ 255, 255, 255, 255 };
		zgui::color cNpcName{ 255, 255, 255, 255 };
		zgui::color cNpcFilledBox{ 255, 255, 255, 100 };
		zgui::color cPlayerName{ 255, 255, 255, 255 };
		zgui::color cPlayerFilledBox{ 255, 255, 255, 100 };

		//Not Visible
		zgui::color cInvPlayer{ 255, 3, 3, 255 };
		zgui::color cInvPlayerBones{ 255, 3, 3, 255 };
		zgui::color cInvPlayerFilledBox{ 255, 3, 3, 100 };
		zgui::color cInvNpc{ 255, 3, 3, 255 };
		zgui::color cInvNpcBones{ 255, 3, 3, 255 };
		zgui::color cInvNpcName{ 255, 3, 3, 255 };
		zgui::color cInvPlayerName{ 255, 3, 3, 255 };
		zgui::color cInvNpcFilledBox{ 255, 3, 3, 100 };

		//Fov Circle
		zgui::color cFovCircle{ 255, 255, 255, 255 };
	}inline menu_colors {};

	void SetupZGUI() noexcept;

	//Expected only to be called in the Render Hook each frame
	void Render() noexcept;

	//Rendering the cursor only 
	void Cursor() noexcept;
}
