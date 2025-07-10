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
		if (!Menu::config.block_game_window)
		{
			switch (Msg)
			{
				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
					if (wParam == Menu::config.MenuOpenKey)
						RenderCFs.isMenuOpen = !RenderCFs.isMenuOpen;
					if (wParam == Menu::config.PanicKey)
						MadFramework::Exit();
					break;

				case WM_SYSCOMMAND:
				case WM_WINDOWPOSCHANGED:
				case WM_WINDOWPOSCHANGING:
				case WM_NCACTIVATE:
				case WM_SIZE:
				case WM_QUERYOPEN:
				case WM_PAINT:
				case WM_ACTIVATE:
				case WA_INACTIVE:
				case WM_SETFOCUS:
				case WM_KILLFOCUS:
				case WM_MOUSEACTIVATE:
				case WM_NCHITTEST:
				case WM_NCLBUTTONDOWN:
				case WM_NCMOUSEMOVE:
				case WM_NCLBUTTONUP:
				case WM_NCLBUTTONDBLCLK:
				case WM_NCRBUTTONDOWN:
				case WM_ACTIVATEAPP:
				case WM_GETICON:
				case WM_NCPAINT:
				case WM_NCCALCSIZE:
				case WM_ERASEBKGND:
				case WM_MOVE:
				{
					if (RenderCFs.isMenuOpen)
						return CallWindowProcW(pWindowProc, hWnd, Msg, wParam, lParam);
				}
			}
		}
		else
		{
			switch (Msg)
			{
				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
					if (wParam == Menu::config.MenuOpenKey)
						RenderCFs.isMenuOpen = !RenderCFs.isMenuOpen;
					if (wParam == Menu::config.PanicKey)
						MadFramework::Exit();
					break;
			}
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
