#pragma once

#include "Engines/Source Engine/Interfaces/ITraceFilter.h"

class CTraceFilter : public ITraceFilter
{
public:

	virtual bool ShouldHitEntity(IHandleEntity* pEntity, int contentsMask) override
	{
		UNREFERENCED_PARAMETER(contentsMask);
		return pEntity != pBaseEntity;
	}

	virtual TraceType_t	GetTraceType() const override
	{
		return TRACE_EVERYTHING;
	}

	C_BaseEntity* pBaseEntity = nullptr;
};
