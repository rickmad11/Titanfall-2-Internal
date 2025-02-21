#include "pch.h"

#include "Source Engine Hooks.h"

#include "Features/Aimbot/Aimbot.h"
#include "Features/Visuals/ESP.h"
#include "Features/Visuals/Visuals.h"
#include "Menu/Menu.h"

namespace MadFramework::SourceEngineHooks
{
	void __fastcall HudUpdate(void* self, bool bActive)
	{
		Menu::MenuState menuState = Menu::state;

		if (menuState.vPlayers || menuState.vWorld)
		{
			std::lock_guard<std::mutex> lock(render_mutex);

			IClientEntityList* pIClientEntityList = MadFramework::InterfaceManager::GetInterface<IClientEntityList>();
			IVEngineClient* pIVEngineClient = MadFramework::InterfaceManager::GetInterface<IVEngineClient>();

			IEngineTrace* pIEngineTrace = nullptr;

			if (menuState.vVisbleCheck)
				pIEngineTrace = MadFramework::InterfaceManager::GetInterface<IEngineTrace>();

			if (pIVEngineClient->IsInGame())
			{
				C_BaseEntity* pLocalClientEntity = reinterpret_cast<C_BaseEntity*>(pIClientEntityList->GetClientEntity(pIVEngineClient->GetLocalPlayer()));
				int lpTeamNum = pLocalClientEntity->GetTeamNum();

				for (int index = 0; index < pIClientEntityList->GetMaxEntities(); index++)
				{
					IClientEntity* pClientEntity = pIClientEntityList->GetClientEntity(index);

					if (pLocalClientEntity == pClientEntity)
						continue;

					if (pClientEntity == nullptr)
						continue;

					C_BaseEntity* pC_BaseEntity = reinterpret_cast<C_BaseEntity*>(pClientEntity);

					if (pC_BaseEntity == nullptr)
						continue;

					const char* pC_EntitySignifierName = pC_BaseEntity->GetSignifierName();

					if (pC_EntitySignifierName == nullptr)
						continue;

					EntityRenderData local_entity_render_data;
					local_entity_render_data.hasBones = false;

					if(menuState.vVisbleCheck && pIEngineTrace)
					{
						if ( ( ( *pC_EntitySignifierName == 'p' && pC_EntitySignifierName[1] == 'l' ) || *pC_EntitySignifierName == 'n' ) && pC_BaseEntity->GetLifeState() == 0)
						{
							Trace_t trace{};
							Ray_t ray{};

							CTraceFilter trace_filter{};
							trace_filter.pBaseEntity = pLocalClientEntity;

							Vector3 trace_end_pos = pC_BaseEntity->GetLocalOrigin() + Vector3 {0, 30, 50 };
							ray.init(pLocalClientEntity->GetCameraPos(), trace_end_pos);

							pIEngineTrace->TraceRay(ray, TRACE_MASK_SHOT, &trace_filter, &trace);

							local_entity_render_data.isVisible = (trace.fraction > 0.97f);
						}
					}

					if (menuState.vPlayers)
					{
						if (*pC_EntitySignifierName == 'p' && *(pC_EntitySignifierName + 1) == 'l' && pC_BaseEntity->GetLifeState() == 0)
						{
							local_entity_render_data.type = EntityRenderData::Player;

							if (!menuState.vPlayerTeam)
							{
								if (lpTeamNum == pC_BaseEntity->GetTeamNum())
									continue;
							}

							Vector4 entity_screen_pos{};

							if (pC_BaseEntity->IsTitan())
							{
								if (!GetTitan2DBounds(pC_BaseEntity, entity_screen_pos))
									continue;

								local_entity_render_data.hasBones = false;
							}
							else
							{
								if (!GetPlayer2DBounds(pC_BaseEntity, entity_screen_pos))
									continue;
							}

							local_entity_render_data.screenBasePosition = entity_screen_pos;

							if (menuState.vPlayer_name)
							{
								player_info_t player_info{};
								if (pIVEngineClient->GetPlayerInfo(index, &player_info))
									local_entity_render_data.name = player_info.name;
							}

							if (menuState.vPlayer_health || menuState.vPlayer_health_bar)
							{
								local_entity_render_data.MaxHealth = pC_BaseEntity->GetMaxHealth();
								local_entity_render_data.Health = pC_BaseEntity->GetHealth();
							}

							if (menuState.vPlayer_distance)
							{
								const Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();
								const Vector3 local_origin = pLocalClientEntity->GetLocalOrigin();

								const Vector3 direction = entity_origin - local_origin;

								const float distance = std::sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z) * .1f;

								local_entity_render_data.distance = distance;
							}

							if (menuState.vPlayer_weapon_info)
							{
								if (CWeapon* pActiveWeapon = pC_BaseEntity->GetActiveWeapon())
								{
									local_entity_render_data.clipAmmo = pActiveWeapon->GetWeaponClipAmmo();
									local_entity_render_data.stockAmmo = pActiveWeapon->GetWeaponStockAmmo();
									local_entity_render_data.weapon_name = pActiveWeapon->GetWeaponRealName();
								}
							}

							if(menuState.vPlayer_speed)
								local_entity_render_data.speed = GetPlayerSpeed(pC_BaseEntity);

							if (menuState.vPlayer_bones && !pC_BaseEntity->IsTitan())
							{
								static CGlobalVars* pCGlobalVars = CGlobalVars::Get();

								if (!pC_BaseEntity->SetupBones(&local_entity_render_data.boneMatrix[0], 256, 1024, pCGlobalVars->m_curTime))
								{
									std::memset(&local_entity_render_data.boneMatrix[0], 0, sizeof(local_entity_render_data.boneMatrix));
									local_entity_render_data.hasBones = false;
									//entity_render_data.emplace_back(local_entity_render_data);
									//continue;
								}
								else
									local_entity_render_data.hasBones = true;
							}

							entity_render_data.emplace_back(local_entity_render_data);
							continue;
						}
					}

					if (menuState.vWorld)
					{
						if (menuState.vNpcs && *pC_EntitySignifierName == 'n' && pC_BaseEntity->GetLifeState() == 0)
						{
							local_entity_render_data.type = EntityRenderData::Npc;

							if (!menuState.vPlayerTeam)
							{
								if (lpTeamNum == pC_BaseEntity->GetTeamNum())
									continue;
							}

							Vector4 entity_screen_pos{};

							if (pC_BaseEntity->IsTitan())
							{
								if (!GetTitan2DBounds(pC_BaseEntity, entity_screen_pos))
									continue;

								//not going to make bones for this stupid shit
								local_entity_render_data.hasBones = false;
							}
							else
							{
								if (!GetPlayer2DBounds(pC_BaseEntity, entity_screen_pos))
									continue;
							}

							local_entity_render_data.screenBasePosition = entity_screen_pos;

							if (menuState.vNpc_name)
								local_entity_render_data.name = pC_EntitySignifierName;

							if (menuState.vNpc_health || menuState.vNpc_health_bar)
							{
								local_entity_render_data.MaxHealth = pC_BaseEntity->GetMaxHealth();
								local_entity_render_data.Health = pC_BaseEntity->GetHealth();
							}

							if (menuState.vEntity_distance)
							{
								const Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();
								const Vector3 local_origin = pLocalClientEntity->GetLocalOrigin();

								const Vector3 direction = entity_origin - local_origin;

								const float distance = std::sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z) * .1f;

								local_entity_render_data.distance = distance;
							}

							if (menuState.vNpc_weapon_info)
							{
								if (CWeapon* pActiveWeapon = pC_BaseEntity->GetActiveWeapon())
								{
									local_entity_render_data.clipAmmo = pActiveWeapon->GetWeaponClipAmmo();
									local_entity_render_data.stockAmmo = pActiveWeapon->GetWeaponStockAmmo();
									local_entity_render_data.weapon_name = pActiveWeapon->GetWeaponRealName();
								}
							}

							if (menuState.vNpc_bones && !pC_BaseEntity->IsTitan() && pC_EntitySignifierName[4] == 's' && pC_EntitySignifierName[5] != 'u')
							{
								static CGlobalVars* pCGlobalVars = CGlobalVars::Get();

								if (!pC_BaseEntity->SetupBones(&local_entity_render_data.boneMatrix[0], 256, 1024, pCGlobalVars->m_curTime))
								{
									std::memset(&local_entity_render_data.boneMatrix[0], 0, sizeof(local_entity_render_data.boneMatrix));
									local_entity_render_data.hasBones = false;
									//entity_render_data.emplace_back(local_entity_render_data);
									//continue;
								}

								local_entity_render_data.hasBones = true;
							}

							entity_render_data.emplace_back(local_entity_render_data);
							continue;
						}

						if(*pC_EntitySignifierName == 'w' && *(pC_EntitySignifierName + 1) == 'e')
						{
							const char* weapon_name = reinterpret_cast<CWeapon*>(pC_BaseEntity)->GetWeaponModel();

							if (weapon_name == nullptr)
								continue;

							//I don't want to catch guns that are being held by a player/npc
							if (!reinterpret_cast<CWeapon*>(pC_BaseEntity)->HasOwner())
								continue;

							constexpr int str_offset = sizeof("models/weapons/") - sizeof(' ');

							float weapon_distance = 0.f;

							if(menuState.vGrenades || menuState.vWeapons)
							{
								const Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();
								const Vector3 local_origin = pLocalClientEntity->GetLocalOrigin();

								const Vector3 direction = entity_origin - local_origin;

								weapon_distance = std::sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z) * .1f;
							}

							if (menuState.vGrenades && weapon_name[str_offset] == 'g')
							{
								local_entity_render_data.type = EntityRenderData::Grenade;

								Vector4 entity_screen_pos{};
								if (!GetGrenade2DBounds(pC_BaseEntity, entity_screen_pos))
									continue;

								local_entity_render_data.screenBasePosition = entity_screen_pos;
								local_entity_render_data.distance = weapon_distance;

								entity_render_data.emplace_back(local_entity_render_data);
								continue;
							}

							if(menuState.vWeapons && weapon_name[str_offset] != 'g')
							{
								local_entity_render_data.type = EntityRenderData::Weapon;

								Vector4 entity_screen_pos{};
								if (!GetWeapon2DBounds(pC_BaseEntity, entity_screen_pos))
									continue;

								local_entity_render_data.name = reinterpret_cast<CWeapon*>(pC_BaseEntity)->GetWeaponRealName();
								local_entity_render_data.screenBasePosition = entity_screen_pos;
								local_entity_render_data.distance = weapon_distance;

								entity_render_data.emplace_back(local_entity_render_data);
								continue;
							}
						}
					}

				}
			}
		}

		if(menuState.mUnlockAllAchievements)
		{
			static bool unlocked = false;
			static void* pTargetFunction = Memory::SignatureScan("40 53 48 83 EC 40 80 3D ? ? ? ? ? 8B D9", '?', L"engine.dll");

			if(!unlocked)
			{
				//idk random guess I think it only goes to 50 but who cares lol
				for (unsigned int i = 0; i < 200; i++)
					reinterpret_cast<void(__fastcall*)(unsigned int)>(pTargetFunction)(i);
			}

			unlocked = true;
		}

		return ihHudUpdate.fastcall(self, bActive);
	}

	bool __fastcall CreateMove(void* pIClientMode, float input_sample_frametime, CUserCmd* pCUserCmd, bool game_active)
	{
		bool result = ihCreateMove.thiscall<long long int>(pIClientMode, input_sample_frametime, pCUserCmd, game_active);

		if (!pCUserCmd->m_commandNumber)
			return result;

		Menu::MenuState menuState = Menu::state;

		if(menuState.aPlayers || menuState.aNpcs)
		{
			static CGlobalVars* pCGlobalVars = CGlobalVars::Get();

			//shut up idc if the code looks shit
			static const std::unordered_map<Menu::MenuState::AimbotBone, int> bone_map
			{
				{Menu::MenuState::AimbotBone::Head, 12} , {Menu::MenuState::AimbotBone::Neck, 9},
				{Menu::MenuState::AimbotBone::Pelvis, 5}
			};

			IClientEntityList* pIClientEntityList = MadFramework::InterfaceManager::GetInterface<IClientEntityList>();
			IVEngineClient* pIVEngineClient = MadFramework::InterfaceManager::GetInterface<IVEngineClient>();

			if (pIVEngineClient->IsInGame())
			{
				C_BaseEntity* pLocalClientEntity = reinterpret_cast<C_BaseEntity*>(pIClientEntityList->GetClientEntity(pIVEngineClient->GetLocalPlayer()));
				C_BaseEntity* pTargetEntity = nullptr;
				enum entity_type {player, npc , null} type { null };

				int lpTeamNum = pLocalClientEntity->GetTeamNum();

				const Vector3 local_origin = pLocalClientEntity->GetLocalOrigin();

				float closest_entity = 99999.f;
				bool inMeleeRange = false;

				for (int index = 0; index < pIClientEntityList->GetMaxEntities(); index++)
				{
					IClientEntity* pClientEntity = pIClientEntityList->GetClientEntity(index);

					if (pLocalClientEntity == pClientEntity)
						continue;

					if (pClientEntity == nullptr)
						continue;

					C_BaseEntity* pC_BaseEntity = reinterpret_cast<C_BaseEntity*>(pClientEntity);

					if (pC_BaseEntity == nullptr)
						continue;

					const char* pC_EntitySignifierName = pC_BaseEntity->GetSignifierName();

					if (pC_EntitySignifierName == nullptr)
						continue;

					if (lpTeamNum == pC_BaseEntity->GetTeamNum())
						continue;

					if(menuState.aNpcs)
					{
						if (*pC_EntitySignifierName == 'n' && pC_BaseEntity->GetLifeState() == 0)
						{
							if(menuState.aIgnoreTitans)
							{
								if(pC_BaseEntity->IsTitan())
									continue;
							}

							if(menuState.aVisibleCheck)
							{
								if(!IsVisible(pC_BaseEntity, pLocalClientEntity))
									continue;
							}

							const Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();

							const Vector3 direction = entity_origin - local_origin;

							const float distance = std::sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z) * .1f;

							if(menuState.aInsideFovCircleCheck)
							{
								matrix3x4_t boneMatrix[256]{};
								if (!pC_BaseEntity->SetupBones(&boneMatrix[0], 256, 1024, pCGlobalVars->m_curTime))
									continue;

								Vector3 screen_bone = Vector3{ boneMatrix[bone_map.at(menuState.aBoneNpc)][0][3], boneMatrix[bone_map.at(menuState.aBoneNpc)][1][3], boneMatrix[bone_map.at(menuState.aBoneNpc)][2][3] };

								if (!IsInsideFovCircle(menuState.vFovCircleSize, screen_bone))
									continue;
							}

							if(distance < closest_entity)
							{
								pTargetEntity = pC_BaseEntity;
								type = npc;
								closest_entity = distance;

								if (distance <= 15.f)
									inMeleeRange = true;
							}

							continue;
						}
					}

					if(menuState.aPlayers)
					{
						if (*pC_EntitySignifierName == 'p' && *(pC_EntitySignifierName + 1) == 'l' && pC_BaseEntity->GetLifeState() == 0)
						{
							if (menuState.aIgnoreTitans)
							{
								if (pC_BaseEntity->IsTitan())
									continue;
							}

							if (menuState.aVisibleCheck)
							{
								if (!IsVisible(pC_BaseEntity, pLocalClientEntity))
									continue;
							}

							const Vector3 entity_origin = pC_BaseEntity->GetLocalOrigin();
							
							const Vector3 direction = entity_origin - local_origin;

							const float distance = std::sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z) * .1f;

							if (menuState.aInsideFovCircleCheck)
							{
								matrix3x4_t boneMatrix[256]{};
								if (!pC_BaseEntity->SetupBones(&boneMatrix[0], 256, 1024, pCGlobalVars->m_curTime))
									continue;
							
								Vector3 screen_bone = Vector3{ boneMatrix[bone_map.at(menuState.aBonePlayer)][0][3], boneMatrix[bone_map.at(menuState.aBonePlayer)][1][3], boneMatrix[bone_map.at(menuState.aBonePlayer)][2][3] };
							
								if (!IsInsideFovCircle(menuState.vFovCircleSize, screen_bone))
									continue;
							}

							if (distance < closest_entity)
							{
								pTargetEntity = pC_BaseEntity;
								type = player;
								closest_entity = distance;

								if (distance <= 15.f)
									inMeleeRange = true;
							}

							continue;
						}
					}

				}//Entity Loop end

				//@TODO clean this mess holy shit wtf did I do
				if(pTargetEntity)
				{
					bool bones_setup = false;

					matrix3x4_t boneMatrix[256]{};
					if (pTargetEntity->SetupBones(&boneMatrix[0], 256, 1024, pCGlobalVars->m_curTime))
						bones_setup = true;

					if(bones_setup)
					{
						if (menuState.aSilentAimNpcs && type == npc)
						{
							Vector3 bone_pos = Vector3{ boneMatrix[bone_map.at(menuState.aBoneNpc)][0][3], boneMatrix[bone_map.at(menuState.aBoneNpc)][1][3], boneMatrix[bone_map.at(menuState.aBoneNpc)][2][3]};
							SilentAim(pCUserCmd, pLocalClientEntity, bone_pos);
						}

						if(menuState.aSilentAimPlayers && type == player)
						{
							Vector3 bone_pos = Vector3{ boneMatrix[bone_map.at(menuState.aBonePlayer)][0][3], boneMatrix[bone_map.at(menuState.aBonePlayer)][1][3], boneMatrix[bone_map.at(menuState.aBonePlayer)][2][3] };
							SilentAim(pCUserCmd, pLocalClientEntity, bone_pos);
						}

						bool bAimlockKeyPressed = false;
						if(menuState.aAimlockNpcs || menuState.aAimlockPlayers)
						{
							bAimlockKeyPressed = GetAsyncKeyState(menuState.aAimlockKey) & 0x8000;
						}

						if(menuState.aAimlockPlayers && type == player && bAimlockKeyPressed)
						{
							Vector3 bone_pos = Vector3{ boneMatrix[bone_map.at(menuState.aBonePlayer)][0][3], boneMatrix[bone_map.at(menuState.aBonePlayer)][1][3], boneMatrix[bone_map.at(menuState.aBonePlayer)][2][3] };

							if(menuState.aAimlockSmooth)
								SmoothAim(pCUserCmd, pLocalClientEntity, bone_pos, ((100 - menuState.aAimlock_smoothness) / 100) * 0.025f);
							else
								Aimlock(pCUserCmd, pLocalClientEntity, bone_pos);
						}

						if (menuState.aAimlockNpcs && type == npc && bAimlockKeyPressed)
						{
							Vector3 bone_pos = Vector3{ boneMatrix[bone_map.at(menuState.aBoneNpc)][0][3], boneMatrix[bone_map.at(menuState.aBoneNpc)][1][3], boneMatrix[bone_map.at(menuState.aBoneNpc)][2][3] };

							if (menuState.aAimlockSmooth)
								SmoothAim(pCUserCmd, pLocalClientEntity, bone_pos, ((100 - menuState.aAimlock_smoothness) / 100) * 0.025f);
							else
								Aimlock(pCUserCmd, pLocalClientEntity, bone_pos);
						}

						//Should only be used with Silent aim, aimlock and auto aim sucks therefore I won't support it
						if (menuState.aAutoAttack)
							pCUserCmd->m_buttons |= 1 << 0;

						if(menuState.aAutoZoom)
						{
							if(!pLocalClientEntity->IsZooming())
								pCUserCmd->m_buttons |= 1 << 17;
						}

						//Works best with silent aim therefore it should only be used with it
						if(menuState.mAutoMelee && inMeleeRange && (menuState.aSilentAimNpcs || menuState.aSilentAimPlayers))
						{
							static float previousTick = 0.f;
							float currentTick = clock() * 0.001f;

							if (previousTick == 0.f) {
								previousTick = currentTick;
							}

							if (currentTick - previousTick >= 1.f)
							{
								pCUserCmd->m_buttons |= 1 << 18;
								previousTick = 0.f;
							}
						}
					}
				}

				if(pTargetEntity == nullptr)
				{
					if (menuState.aAutoZoom && pLocalClientEntity->IsZooming())
						pCUserCmd->m_buttons |= 1 << 17;
				}

			}
		}

		if(menuState.mSpeedExploit)
			pCUserCmd->m_gameTime += menuState.mSpeed;

		if(menuState.mAirstuck && GetAsyncKeyState(menuState.mAirstuckKey) & 0x8000)
			pCUserCmd->m_commandNumber = 0x7FFFFFFF;

		struct GlobalVars //.rdata //F3 44 0F 59 25 ?? ?? ?? ?? EB
		{
			char pad_0000[56]; //0x0000
			float fov; //0x0038
			char pad_003C[64]; //0x003C
			float viewmodel_fov; //0x007C
			char pad_0080[12]; //0x0080
			float crosshair_draw_flag; //0x008C
		}static * pGlobalVars = reinterpret_cast<GlobalVars*>(static_cast<BYTE*>(Memory::GetModuleBase(L"client.dll")) + 0x8A2F60);

		//wow, im impressed how good I am writing SHIT code
		static DWORD original_page_protection = PAGE_READONLY;
		static BOOL page_status = VirtualProtect(pGlobalVars, sizeof(GlobalVars), PAGE_READWRITE, &original_page_protection);

		if(menuState.mViewmodelChanges && page_status != NULL)
		{
			pGlobalVars->fov = menuState.mFov;
			pGlobalVars->viewmodel_fov = menuState.mViewmodel_fov;
		}

		if (menuState.mDisableGameCrosshair && page_status != NULL)
			pGlobalVars->crosshair_draw_flag = 0;
		else
			pGlobalVars->crosshair_draw_flag = 2;

		return result;
	}
}
