#pragma once

#include "IHandleEntity.h"

class IClientNetworkable;
class IClientEntity;
class C_BaseEntity;
class IClientThinkable;

class IClientUnknown : public IHandleEntity
{
public:
	virtual /*ICollideable*/void*		GetCollideable() = 0;
	virtual IClientNetworkable*			GetClientNetworkable() = 0;
	virtual /*IClientRenderable*/void*	GetClientRenderable() = 0;
	virtual IClientEntity* GetIClientEntity() = 0;
	virtual C_BaseEntity* GetBaseEntity() = 0;
	virtual IClientThinkable* GetClientThinkable() = 0;
};