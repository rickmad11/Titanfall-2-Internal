#pragma once

namespace CLC_ScreenshotHooks
{
	inline safetyhook::InlineHook ihWriteToBuffer{};
	bool __fastcall WriteToBuffer(void* pCLC_Screenshot, void* pCBitWrite);

	inline safetyhook::InlineHook ihReadFromBuffer{};
	__int64 __fastcall ReadFromBuffer(void* pCLC_Screenshot, void* pBuffer);
}

bool CLC_ScreenshotFunctionsHook();
void DisableCLC_ScreenshotFunctionsHook();