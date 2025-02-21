#include "pch.h"

#include "DirectX11 Hooks.h"
#include "Framework.h"

namespace MadFramework::RenderHooks
{
	DECLSPEC_NOINLINE HRESULT __stdcall Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		static bool Initialized = false;
		if(!Initialized)
		{
			Initialized = MadRenderer::DX11::Get()->Initialize(pSwapChain);

#ifdef SOURCE_ENGINE_SDK
			Math::SourceEngine::SetViewMatrix(InterfaceManager::GetInterface<IViewRender>()->GetWorldToScreenMatrix());
			Math::SourceEngine::SetScreenInfo();
#endif

			return ihPresent.stdcall<HRESULT>(pSwapChain, SyncInterval, Flags);
		}

        //Every Draw Call is expected to happen here between Begin and End, Draw calls outside of this block are undefined and not considered by my renderer!
		//--------------------------------------------------------------------------------------------------
		MadRenderer::DX11::Get()->Begin();
		Render();
		MadRenderer::DX11::Get()->End();
		//--------------------------------------------------------------------------------------------------

		return ihPresent.stdcall<HRESULT>(pSwapChain, SyncInterval, Flags);
	}

	DECLSPEC_NOINLINE HRESULT __stdcall ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		if(pSwapChain)
		{
			MadRenderer::DX11::BeforeResize();
			HRESULT result = ihResizeBuffers.stdcall<HRESULT>(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
			MadRenderer::DX11::AfterResize(pSwapChain);

#ifdef SOURCE_ENGINE_SDK
			Math::SourceEngine::SetViewMatrix(InterfaceManager::GetInterface<IViewRender>()->GetWorldToScreenMatrix());
			Math::SourceEngine::SetScreenInfo();
#endif

			return result;
		}

		return ihResizeBuffers.stdcall<HRESULT>(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	}
}
