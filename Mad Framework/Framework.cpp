#include "pch.h"

#include "Framework.h"

//----------------------Not part of MadFramework----------------------
#include "Features/Visuals/Visuals.h"
#include "Features/Misc/SaveManager.h"
//----------------------Not part of MadFramework----------------------

#include "Hooks/DirectX11/DirectX11 Hooks.h"
#include "Hooks/Source Engine/Source Engine Hooks.h"
#include "Hooks/Windows/Windows Hooks.h"
#include "Menu/Menu.h"

namespace MadFramework
{
	void Render() noexcept
	{
		if(RenderCFs.isTakingScreenshot)
		{
			static float previousTick = 0.f;
			float currentTick = clock() * 0.001f;

			if (previousTick == 0.f) {
				previousTick = currentTick;
			}

			if (currentTick - previousTick >= 2.f)
			{
				RenderCFs.isTakingScreenshot = false; 
				previousTick = 0.f;
			}

			return;
		}

		Watermark();

		//----------------------Not part of MadFramework----------------------
		MainVisuals();

		if(Menu::state.mLoadConfig)
		{
			Menu::state.mLoadConfig = false;
			LoadSettings();
		}

		if (Menu::state.mSaveConfig)
		{
			Menu::state.mSaveConfig = false;
			SaveSettings();
		}

		//----------------------Not part of MadFramework----------------------

		//MainHookLogic();

		if(RenderCFs.isMenuOpen)
		{
			zgui::globals::window_ctx.opened = true;
			Menu::Render();
			Menu::Cursor();
		}
	}

	void MainThreadLogic() noexcept
	{
		volatile int ok = 0;
		++ok;
	}

	void MainHookLogic() noexcept
	{
		//Empty
	}

	void Cleanup() noexcept
	{
		//Empty
	}

	void FrameworkExit() noexcept
	{
		auto DisableHook = [](safetyhook::InlineHook& safety_hook) -> void
			{
				if (safety_hook.enabled())
				{
					std::expected<void, safetyhook::InlineHook::Error> hook_status = safety_hook.disable();

					if (!hook_status.has_value())
					{
						safetyhook::InlineHook::Error safetyError = hook_status.error();

						PLOG_ERROR << "Fatal Error unhooking Present DirectX11";
						PLOG_ERROR << "Error Type: " << safetyError.type;
						PLOG_ERROR << "IP: " << safetyError.ip;
					}
				}
			};


		DisableHook(RenderHooks::ihPresent);
		DisableHook(RenderHooks::ihResizeBuffers);

		DisableHook(WindowsHooks::ihBitBlt);
		DisableHook(WindowsHooks::ihGetCursorPos);
		DisableHook(WindowsHooks::ihSetCursorPos);

#ifdef SOURCE_ENGINE_SDK
		DisableHook(SourceEngineHooks::ihHudUpdate);
		DisableHook(SourceEngineHooks::ihCreateMove);
#endif

		if(WindowsHooks::pWindowProc)
		{
			Utility::WindowInfo windowData = Utility::GetCurrentWindowData();

			(void)SetWindowLongPtr(windowData.windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowsHooks::pWindowProc));
		}
	}

	bool Running() noexcept
	{
		return g_running_flag;
	}

	void Exit() noexcept
	{
		g_running_flag = false;
	}

	void Watermark() noexcept
	{
		MadRenderer::RenderList* pForegroundRenderList = MadRenderer::DX11::Get()->GetForegroundRenderList();

		constexpr float text_scale = 1.f;

		pForegroundRenderList->DrawString("MadFramework Private Testing v0.1", { 0, 0 }, { 255, 255, 255 }, text_scale);
		pForegroundRenderList->DrawString("Rickmad11 Titanfall 2 Internal v1.0", { 0, 10 }, { 255, 255, 255 }, text_scale);

		pForegroundRenderList->DrawString("FPS: ", { 0, 20 }, { 255, 255, 255 }, text_scale);
		pForegroundRenderList->DrawString(std::to_string(Utility::GetCurrentFpsCount<0>()).c_str(), { 30, 20 }, { 255, 255, 255 }, text_scale);
	}
}
