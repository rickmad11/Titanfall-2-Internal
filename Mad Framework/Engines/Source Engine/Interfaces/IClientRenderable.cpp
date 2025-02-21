#include "pch.h"

#include "IClientRenderable.h"

bool IClientRenderable::SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	//C_Player IClientRenderable vtable is 0x10 from base we are at 0x8 from base
	return MadFramework::Memory::InvokeVTableFunction<bool>(reinterpret_cast<BYTE*>(this) + 0x8, SourceEngine::IClientRenderable::Index::SetupBones, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}
