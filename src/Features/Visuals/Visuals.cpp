#include "pch.h"
#include "Visuals.h"

#include "ESP.h"
#include "Features/Misc/MiscVisuals.h"
#include "Menu/Menu.h"

void MainVisuals() {

	MadFramework::Menu::MenuState menuState = MadFramework::Menu::state;

	if (menuState.vPlayers || menuState.vWorld) 
	{
		std::lock_guard<std::mutex> lock(render_mutex);

		MadRenderer::RenderList* pBackGroundRenderList = MadRenderer::DX11::Get()->GetBackGroundRenderList();

		for (EntityRenderData const& render_data : entity_render_data)
		{
			if (menuState.vPlayers && render_data.type == EntityRenderData::Player)
			{
				if (menuState.vPlayer_box_2d)
				{
					if(menuState.vVisbleCheck)
						Entity2dBox(render_data.screenBasePosition, pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cPlayer : MadFramework::Menu::menu_colors.cInvPlayer);
					else
						Entity2dBox(render_data.screenBasePosition, pBackGroundRenderList, MadFramework::Menu::menu_colors.cPlayer);
				}

				if (menuState.vPlayer_name)
				{
					if (menuState.vVisbleCheck)
						EntityName(render_data.screenBasePosition, render_data.name.c_str(), pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cPlayerName : MadFramework::Menu::menu_colors.cInvPlayerName);
					else
						EntityName(render_data.screenBasePosition, render_data.name.c_str(), pBackGroundRenderList, MadFramework::Menu::menu_colors.cPlayerName);
				}

				if (menuState.vPlayer_health)
					EntityHealth(render_data, render_data.screenBasePosition, pBackGroundRenderList);
				
				if (menuState.vPlayer_distance)
					EntityDistance(render_data, render_data.screenBasePosition, pBackGroundRenderList);
				
				if (menuState.vPlayer_weapon_info)
					EntityWeaponData(render_data, render_data.screenBasePosition, pBackGroundRenderList);
				
				if (menuState.vPlayer_health_bar)
					EntityHealthBar(render_data, render_data.screenBasePosition, pBackGroundRenderList);
				
				if (menuState.vPlayer_bones && render_data.hasBones)
				{
					if (menuState.vVisbleCheck)
						EntityBones(render_data, pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cPlayerBones : MadFramework::Menu::menu_colors.cInvPlayerBones);
					else
						EntityBones(render_data, pBackGroundRenderList, MadFramework::Menu::menu_colors.cPlayerBones);
				}

				if (menuState.vPlayer_snap_lines)
					EntitySnapLines(render_data.screenBasePosition, pBackGroundRenderList);

				if (menuState.vPlayer_edge_box)
				{
					if (menuState.vVisbleCheck)
						EntityEdgeBox(render_data.screenBasePosition, pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cPlayer : MadFramework::Menu::menu_colors.cInvPlayer);
					else
						EntityEdgeBox(render_data.screenBasePosition, pBackGroundRenderList, MadFramework::Menu::menu_colors.cPlayer);
				}

				if (menuState.vPlayer_speed)
					DrawPlayerSpeed(render_data.speed, render_data.screenBasePosition, pBackGroundRenderList);

				if (menuState.vPlayer_FilledBox)
				{
					if (menuState.vVisbleCheck)
						EntityFilledBox(render_data.screenBasePosition, pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cPlayerFilledBox : MadFramework::Menu::menu_colors.cInvPlayerFilledBox);
					else
						EntityFilledBox(render_data.screenBasePosition, pBackGroundRenderList, MadFramework::Menu::menu_colors.cPlayerFilledBox);
				}

				continue;
			}

			if (menuState.vWorld)
			{
				if(menuState.vNpcs && render_data.type == EntityRenderData::Npc)
				{
					if (menuState.vNpc_box_2d)
					{
						if (menuState.vVisbleCheck)
							Entity2dBox(render_data.screenBasePosition, pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cNpc : MadFramework::Menu::menu_colors.cInvNpc);
						else
							Entity2dBox(render_data.screenBasePosition, pBackGroundRenderList, MadFramework::Menu::menu_colors.cNpc);
					}

					if (menuState.vNpc_name)
					{
						if (menuState.vVisbleCheck)
							EntityName(render_data.screenBasePosition, render_data.name.c_str(), pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cNpcName : MadFramework::Menu::menu_colors.cInvNpcName);
						else
							EntityName(render_data.screenBasePosition, render_data.name.c_str(), pBackGroundRenderList, MadFramework::Menu::menu_colors.cNpcName);
					}

					if (menuState.vNpc_health)
						EntityHealth(render_data, render_data.screenBasePosition, pBackGroundRenderList);
					
					if (menuState.vEntity_distance)
						EntityDistance(render_data, render_data.screenBasePosition, pBackGroundRenderList);
					
					if (menuState.vNpc_weapon_info)
						EntityWeaponData(render_data, render_data.screenBasePosition, pBackGroundRenderList);
					
					if (menuState.vNpc_health_bar)
						EntityHealthBar(render_data, render_data.screenBasePosition, pBackGroundRenderList);
					
					if (menuState.vNpc_bones && render_data.hasBones)
					{
						if (menuState.vVisbleCheck)
							EntityBones(render_data, pBackGroundRenderList, render_data.isVisible ?  MadFramework::Menu::menu_colors.cNpcBones : MadFramework::Menu::menu_colors.cInvNpcBones);
						else
							EntityBones(render_data, pBackGroundRenderList, MadFramework::Menu::menu_colors.cNpcBones);
					}

					if (menuState.vNpc_snap_lines)
						EntitySnapLines(render_data.screenBasePosition, pBackGroundRenderList);

					if(menuState.vNpc_edge_box)
					{
						if (menuState.vVisbleCheck)
							EntityEdgeBox(render_data.screenBasePosition, pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cNpc : MadFramework::Menu::menu_colors.cInvNpc);
						else
							EntityEdgeBox(render_data.screenBasePosition, pBackGroundRenderList, MadFramework::Menu::menu_colors.cNpc);
					}

					if (menuState.vNpc_FilledBox)
					{
						if (menuState.vVisbleCheck)
							EntityFilledBox(render_data.screenBasePosition, pBackGroundRenderList, render_data.isVisible ? MadFramework::Menu::menu_colors.cNpcFilledBox : MadFramework::Menu::menu_colors.cInvNpcFilledBox);
						else
							EntityFilledBox(render_data.screenBasePosition, pBackGroundRenderList, MadFramework::Menu::menu_colors.cNpcFilledBox);
					}

					continue;
				}

				if(menuState.vGrenades && render_data.type == EntityRenderData::Grenade)
				{
					EntityDistance(render_data, render_data.screenBasePosition, "Grenade", pBackGroundRenderList);
					continue;
				}

				if(menuState.vWeapons && render_data.type == EntityRenderData::Weapon)
				{
					EntityDistance(render_data, render_data.screenBasePosition, render_data.name.c_str(), pBackGroundRenderList);
					continue;
				}
			}
		}

		entity_render_data.clear();
	}

	if(menuState.vDrawFovCircle)
		DrawFovCircle(MadFramework::Menu::menu_colors.cFovCircle, menuState.vFovCircleSize);

	if(menuState.mCustomCrosshair)
		DrawCrosshair(menuState.mSelectedCrosshairVariant, menuState.mCustomCrosshairSize);

}