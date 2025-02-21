#pragma once

namespace MadFramework::Hook
{
	bool DirectX11PresentAndResize(void* pDetourFunctionPresent, safetyhook::InlineHook* pInlineHookPresent,
	                      void* pDetourFunctionResizeBuffers, safetyhook::InlineHook* pInlineHookResizeBuffers);

	bool WindowsBitBlt(void* pDetourFunctionBitBlt, safetyhook::InlineHook* pInlineHookBitBlt);

	bool WindowProc(void* pDetourFunctionWindowProc, WNDPROC* ppWNDPROC);

	bool WindowsGetCursorPos(void* pDetourFunctionGetCursorPos, safetyhook::InlineHook* pInlineHookGetCursorPos);

	bool WindowsSetCursorPos(void* pDetourFunctionSetCursorPos, safetyhook::InlineHook* pInlineHookSetCursorPos);

	bool SourceEngineHudUpdate(void* pDetourFunctionHudUpdate, safetyhook::InlineHook* pInlineHookHudUpdate);

	bool SourceEngineCreateMove(void* pDetourFunctionCreateMove, safetyhook::InlineHook* pInlineHookCreateMove);
}
