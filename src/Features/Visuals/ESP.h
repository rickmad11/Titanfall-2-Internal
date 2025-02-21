#pragma once

#include "Visuals.h"

void Entity2dBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
void EntityName(Vector4 screenBaseEntity, const char* pEntityName, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color);
bool GetWeapon2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out);
bool GetPlayer2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out);
bool GetGrenade2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out);
void EntityHealth(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
void EntityDistance(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
void EntityWeaponData(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
bool GetTitan2DBounds(C_BaseEntity* pC_BaseEntity, Vector4& out);
void EntityHealthBar(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
void EntityBones(EntityRenderData const& C_BaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color);
void EntityDistance(EntityRenderData const& C_BaseEntity, Vector4 screenBaseEntity, const char* text, MadRenderer::RenderList* pBackGroundRenderList);
void EntitySnapLines(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
void EntityEdgeBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
void Entity2dBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color);
void EntityEdgeBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color);
void DrawFovCircle(zgui::color color, float radius);
float GetPlayerSpeed(C_BaseEntity* pPlayerEntity) noexcept;
void DrawPlayerSpeed(float player_speed, Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList);
void EntityFilledBox(Vector4 screenBaseEntity, MadRenderer::RenderList* pBackGroundRenderList, zgui::color color);