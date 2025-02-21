#include "pch.h"

#include "CGlobalVars.h"

CGlobalVars* CGlobalVars::Get() noexcept
{
	static BYTE* offset = MadFramework::Memory::SignatureScan("48 8B 05 ? ? ? ? 48 8D 8B ? ? ? ? F3 0F 10 48", '?', L"client.dll") + 3;
	static CGlobalVars* pCGlobalVars = *reinterpret_cast<CGlobalVars**>((offset + 4) + *reinterpret_cast<int*>(offset));
	return pCGlobalVars;
}
