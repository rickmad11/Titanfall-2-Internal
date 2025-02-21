#pragma once

namespace MadFramework::WindowsHooks
{
	inline safetyhook::InlineHook ihBitBlt{};
	BOOL __stdcall BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);

	inline WNDPROC pWindowProc = nullptr;
	LRESULT __stdcall WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	inline safetyhook::InlineHook ihGetCursorPos{};
	BOOL __stdcall GetCursorPos(LPPOINT lpPoint);

	inline safetyhook::InlineHook ihSetCursorPos{};
	BOOL __stdcall SetCursorPos(int X, int Y);
}