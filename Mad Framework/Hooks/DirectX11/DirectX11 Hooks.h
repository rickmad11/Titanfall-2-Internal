#pragma once

namespace MadFramework::RenderHooks
{
	inline safetyhook::InlineHook ihPresent {};
	HRESULT __stdcall Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	inline safetyhook::InlineHook ihResizeBuffers{};
	HRESULT __stdcall ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
}

