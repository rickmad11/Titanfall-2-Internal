#include "pch.h"

#include "Antiscreenshot.h"
#include "Framework.h"

//Thanks to https://github.com/jz0/r2-internal/blob/main/Hooks/Screenshot.cpp I didn't even notice that this class exists lol
namespace CLC_ScreenshotHooks
{
	bool __fastcall WriteToBuffer(void* pCLC_Screenshot, void* pCBitWrite)
	{
		UNREFERENCED_PARAMETER(pCLC_Screenshot);
		UNREFERENCED_PARAMETER(pCBitWrite);
		MadFramework::RenderCFs.isTakingScreenshot = true;
		return false;
	}

	__int64 __fastcall ReadFromBuffer(void* pCLC_Screenshot, void* pBuffer)
	{
		UNREFERENCED_PARAMETER(pCLC_Screenshot);
		UNREFERENCED_PARAMETER(pBuffer);
		MadFramework::RenderCFs.isTakingScreenshot = true;
		return 0;
	}
}


bool CLC_ScreenshotFunctionsHook() 
{
	CLC_ScreenshotHooks::ihWriteToBuffer = safetyhook::create_inline(
		MadFramework::Memory::SignatureScan("48 89 5C 24 ? 57 48 83 EC 20 8B 42 ? 48 8B DA", '?', L"engine.dll"),
		CLC_ScreenshotHooks::WriteToBuffer);

	CLC_ScreenshotHooks::ihReadFromBuffer = safetyhook::create_inline(
		MadFramework::Memory::SignatureScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B DA 48 8B 52", '?', L"engine.dll"),
		CLC_ScreenshotHooks::ReadFromBuffer);

	PLOG_INFO << "CLC WriteToBuffer: " << CLC_ScreenshotHooks::ihWriteToBuffer.original<void*>();
	PLOG_INFO << "CLC ReadFromBuffer: " << CLC_ScreenshotHooks::ihReadFromBuffer.original<void*>();

	return CLC_ScreenshotHooks::ihWriteToBuffer.enabled() && CLC_ScreenshotHooks::ihReadFromBuffer.enabled();
}

void DisableCLC_ScreenshotFunctionsHook()
{
	if (CLC_ScreenshotHooks::ihWriteToBuffer.enabled() && CLC_ScreenshotHooks::ihReadFromBuffer.enabled())
	{
		std::expected<void, safetyhook::InlineHook::Error> hook_status_write_buffer = CLC_ScreenshotHooks::ihWriteToBuffer.disable();
		std::expected<void, safetyhook::InlineHook::Error> hook_status_read_buffer = CLC_ScreenshotHooks::ihReadFromBuffer.disable();

		if (!hook_status_write_buffer.has_value())
		{
			safetyhook::InlineHook::Error safetyError = hook_status_write_buffer.error();

			PLOG_ERROR << "Fatal Error unhooking CLC_WriteToBuffer";
			PLOG_ERROR << "Error Type: " << safetyError.type;
			PLOG_ERROR << "IP: " << safetyError.ip;
		}

		if (!hook_status_read_buffer.has_value())
		{
			safetyhook::InlineHook::Error safetyError = hook_status_read_buffer.error();

			PLOG_ERROR << "Fatal Error unhooking CLC_ReadFromBuffer";
			PLOG_ERROR << "Error Type: " << safetyError.type;
			PLOG_ERROR << "IP: " << safetyError.ip;
		}
	}
}