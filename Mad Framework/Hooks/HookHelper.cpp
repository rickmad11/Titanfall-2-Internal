#include "pch.h"

#include "HookHelper.h"

namespace MadFramework::Hook
{
	bool DirectX11PresentAndResize(void* pDetourFunctionPresent, safetyhook::InlineHook* pInlineHookPresent ,
					      void* pDetourFunctionResizeBuffers, safetyhook::InlineHook* pInlineHookResizeBuffers)
	{
		Utility::WindowInfo windowData = Utility::GetCurrentWindowData();

		if(windowData.windowHandle == nullptr)
		{
			PLOG_ERROR << "Window Handle was nullptr";
			return false;
		}

		wchar_t window_name_buffer[256] {};
		int c_length = GetWindowTextW(windowData.windowHandle, window_name_buffer, 256);

		PLOG_INFO << "Window Title: " << ( (c_length > 0) ? window_name_buffer : L" " );
		PLOG_INFO << "Process ID: " << windowData.processID;
		PLOG_INFO << "Window Handle: " << windowData.windowHandle;

		DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
		swap_chain_desc.OutputWindow = windowData.windowHandle;
		swap_chain_desc.BufferUsage	 = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain = nullptr;
		HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_NULL, nullptr,
			NULL, nullptr, NULL,
			D3D11_SDK_VERSION, &swap_chain_desc,
			pSwapChain.GetAddressOf(), nullptr, nullptr, nullptr);

		//bcs of D3D_DRIVER_TYPE_NULL it will return something like D3DERR_INVALIDCALL (I don't remember but this can be ignored)
		if(result < S_OK) 
		{
			PLOG_ERROR << "D3D11CreateDeviceAndSwapChain returned: " << result;
			PLOG_ERROR << "Fatal Error could not create SwapChain";
			return false;
		}

		//8 -> Vtable index for Present
		void* pPresent = Memory::GetVTableFunctionAddress(pSwapChain.Get(), 8);
		//13 -> Vtable index for ResizeBuffers
		void* pResizeBuffers = Memory::GetVTableFunctionAddress(pSwapChain.Get(), 13);

		pSwapChain.Reset();

		if (pPresent == nullptr || pResizeBuffers == nullptr)
		{
			PLOG_WARNING << "Failed Creating SwapChain retrying...";
			PLOG_WARNING << "D3D11CreateDeviceAndSwapChain returned: " << result;

			swap_chain_desc.Windowed = true;

			result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
				NULL, nullptr, NULL,
				D3D11_SDK_VERSION, &swap_chain_desc,
				pSwapChain.GetAddressOf(), nullptr, nullptr, nullptr);

			pPresent = Memory::GetVTableFunctionAddress(pSwapChain.Get(), 8);
			pResizeBuffers = Memory::GetVTableFunctionAddress(pSwapChain.Get(), 13);
		}

		if(pPresent == nullptr || pResizeBuffers == nullptr)
		{
			PLOG_ERROR << "Could either not get Present or ResizeBuffers Address Incorrect Vtable Index?";
			PLOG_ERROR << "D3D11CreateDeviceAndSwapChain returned: " << result;
			PLOG_ERROR << "Present: " << pPresent << " " << "ResizeBuffers: " << pResizeBuffers;
			return false;
		}

		PLOG_INFO << "DX11 Present: " << pPresent;
		PLOG_INFO << "DX11 Resize Buffers: " << pResizeBuffers;

		if(pDetourFunctionPresent)
			*pInlineHookPresent = safetyhook::create_inline(pPresent, pDetourFunctionPresent);

		if(pDetourFunctionResizeBuffers)
			*pInlineHookResizeBuffers = safetyhook::create_inline(pResizeBuffers, pDetourFunctionResizeBuffers);
		
		return true;
	}

	bool WindowsBitBlt(void* pDetourFunctionBitBlt, safetyhook::InlineHook* pInlineHookBitBlt)
	{
		void* pBitBlt = Memory::GetExport(L"GDI32.dll", "BitBlt");

		if(pBitBlt == nullptr)
		{
			PLOG_INFO << "BitBlt was: Nullptr";
			return false;
		}

		PLOG_INFO << "BitBlt found at: " << pBitBlt;

		if(pDetourFunctionBitBlt)
			*pInlineHookBitBlt = safetyhook::create_inline(pBitBlt, pDetourFunctionBitBlt);

		PLOG_INFO << "Hooked BitBlt: " << pDetourFunctionBitBlt;

		return true;
	}

	bool WindowProc(void* pDetourFunctionWindowProc, WNDPROC* ppWNDPROC)
	{
		if (ppWNDPROC)
		{
			Utility::WindowInfo windowData = Utility::GetCurrentWindowData();

			*ppWNDPROC = reinterpret_cast<WNDPROC>(SetWindowLongPtr(windowData.windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(pDetourFunctionWindowProc)));
			PLOG_INFO << "Hooked WindowProc: " << *ppWNDPROC;

			return *ppWNDPROC;
		}

		return false;
	}

	bool WindowsGetCursorPos(void* pDetourFunctionGetCursorPos, safetyhook::InlineHook* pInlineHookGetCursorPos)
	{
		if(pDetourFunctionGetCursorPos || pInlineHookGetCursorPos)
		{
			*pInlineHookGetCursorPos = safetyhook::create_inline(&::GetCursorPos, pDetourFunctionGetCursorPos);
			PLOG_INFO << "Hooked GetCursorPos: " << &::GetCursorPos;

			return true;
		}

		return false;
	}

	bool WindowsSetCursorPos(void* pDetourFunctionSetCursorPos, safetyhook::InlineHook* pInlineHookSetCursorPos)
	{
		if (pDetourFunctionSetCursorPos || pInlineHookSetCursorPos)
		{
			*pInlineHookSetCursorPos = safetyhook::create_inline(&::SetCursorPos, pDetourFunctionSetCursorPos);
			PLOG_INFO << "Hooked SetCursorPos: " << &::SetCursorPos;

			return true;
		}

		return false;
	}

	bool SourceEngineHudUpdate(void* pDetourFunctionHudUpdate, safetyhook::InlineHook* pInlineHookHudUpdate)
	{
		if (pDetourFunctionHudUpdate || pInlineHookHudUpdate)
		{
			void* const pHudUpdate = Memory::SignatureScan("40 53 48 83 EC 40 48 8B 05 ? ? ? ? 0F 29 74 24", '?', L"client.dll");

			*pInlineHookHudUpdate = safetyhook::create_inline(pHudUpdate, pDetourFunctionHudUpdate);
			PLOG_INFO << "Hooked HudUpdate: " << pHudUpdate;

			return true;
		}

		return false;
	}

	bool SourceEngineCreateMove(void* pDetourFunctionCreateMove, safetyhook::InlineHook* pInlineHookCreateMove)
	{
		if (pDetourFunctionCreateMove || pInlineHookCreateMove)
		{
			void* const pCreateMove = Memory::SignatureScan("48 89 5C 24 ? 57 48 83 EC 30 48 8B 0D ? ? ? ? 0F 29 74 24", '?', L"client.dll");

			*pInlineHookCreateMove = safetyhook::create_inline(pCreateMove, pDetourFunctionCreateMove);
			PLOG_INFO << "Hooked CreateMove: " << pCreateMove;

			return true;
		}

		return false;
	}
}
