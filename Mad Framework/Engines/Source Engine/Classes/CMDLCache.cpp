#include "pch.h"
#include "CMDLCache.h"

MDLHandle_t CMDLCache::FindMDL(const char* pMDLRelativePath)
{
	return MadFramework::Memory::InvokeVTableFunction<MDLHandle_t>(this, 0xA, pMDLRelativePath);
}
