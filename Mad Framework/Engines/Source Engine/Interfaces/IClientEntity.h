#pragma once


#include "IClientRenderable.h"
#include "IClientUnknown.h"
#include "IClientNetworkable.h"
#include "IClientThinkable.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void				Release(void) = 0;
	virtual const Vector3&		GetAbsOrigin(void) const = 0;
	virtual const QAngle&		GetAbsAngles(void) const = 0;
	virtual class CMouthInfo*	GetMouth(void) = 0;
	virtual bool				GetSoundSpatialization(struct SpatializationInfo_t& info) = 0;
};
