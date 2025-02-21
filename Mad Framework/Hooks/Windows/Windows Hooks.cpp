#include "pch.h"

#include "Windows Hooks.h"
#include "Framework.h"
#include "Menu/Menu.h"

namespace MadFramework::WindowsHooks
{
	BOOL __stdcall BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop) {
		PLOG_INFO << "BitBlt invoked Disabled Rendering!";
		RenderCFs.isTakingScreenshot = true;
		return ihBitBlt.stdcall<BOOL>(hdc, x, y, cx, cy, hdcSrc, x1, y1, rop);
	}

	LRESULT __stdcall WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				if(wParam == Menu::config.MenuOpenKey)
					RenderCFs.isMenuOpen = !RenderCFs.isMenuOpen;
				if(wParam == Menu::config.PanicKey)
					MadFramework::Exit();
					break;
		}

		if (RenderCFs.isMenuOpen)
			return NULL;
		
		return CallWindowProcW(pWindowProc, hWnd, Msg, wParam, lParam);
	}

	BOOL __stdcall GetCursorPos(LPPOINT lpPoint)
	{
		return ihGetCursorPos.stdcall<BOOL>(lpPoint);
	}

	BOOL __stdcall SetCursorPos(int X, int Y)
	{
		if (RenderCFs.isMenuOpen)
			return TRUE;

		return ihSetCursorPos.stdcall<BOOL>(X, Y);
	}

}
