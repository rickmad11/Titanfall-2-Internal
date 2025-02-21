#include "pch.h"

#include "Framework.h"
#include "AntiScreenshot/Antiscreenshot.h"
#include "Features/Misc/HitSound.h"
#include "Hooks/HookHelper.h"
#include "Hooks/DirectX11/DirectX11 Hooks.h"
#include "Hooks/Source Engine/Source Engine Hooks.h"
#include "Hooks/Windows/Windows Hooks.h"
#include "Menu/Menu.h"

DWORD WINAPI ThreadEntry(LPVOID lpThreadParameter)
{
#ifdef DEBUG_CONSOLE_LOG
    if(!LogManager::Get()->InitializeLogConsole())
        MessageBoxW(nullptr, L"Console Creation Error", L"Main Thread", MB_OKCANCEL | MB_ICONWARNING);
#endif

    PLOG_INFO << "Console Initialized!";

    if (!ConfigManager::Get()->InitializeConfigManager("RM11_TF2_Config.ini") && ConfigManager::Get()->HasFailed())
        PLOG_WARNING << "Config error (this can be ignored if you don't care about saving your settings)";

    if (!CLC_ScreenshotFunctionsHook())
        PLOG_ERROR << "Hooking CLC_ScreenshotFunctions Failed!";

    if(!EnableUserMessageHook())
        PLOG_ERROR << "Hooking OnHitUserMessage Failed!";

    if (!MadFramework::Hook::DirectX11PresentAndResize(&MadFramework::RenderHooks::Present, &MadFramework::RenderHooks::ihPresent,
        &MadFramework::RenderHooks::ResizeBuffers, &MadFramework::RenderHooks::ihResizeBuffers))
        PLOG_ERROR << "Hooking DirectX11 Render Functions Failed!";

    if (!MadFramework::Hook::WindowsBitBlt(&MadFramework::WindowsHooks::BitBlt, &MadFramework::WindowsHooks::ihBitBlt))
        PLOG_WARNING << "BitBlt Hook failed";

    if (!MadFramework::Hook::WindowProc(&MadFramework::WindowsHooks::WindowProc, &MadFramework::WindowsHooks::pWindowProc))
        PLOG_ERROR << "Failed Hooking WindowProc";

    if (!MadFramework::Hook::WindowsSetCursorPos(&MadFramework::WindowsHooks::SetCursorPos, &MadFramework::WindowsHooks::ihSetCursorPos))
        PLOG_WARNING << "Failed Hooking SetCursorPos";

    MadFramework::Menu::SetupZGUI();

#ifdef SOURCE_ENGINE_SDK

    if (!MadFramework::Hook::SourceEngineHudUpdate(&MadFramework::SourceEngineHooks::HudUpdate, &MadFramework::SourceEngineHooks::ihHudUpdate))
        PLOG_WARNING << "Failed Hooking HudUpdate";

    if (!MadFramework::Hook::SourceEngineCreateMove(&MadFramework::SourceEngineHooks::CreateMove, &MadFramework::SourceEngineHooks::ihCreateMove))
        PLOG_WARNING << "Failed Hooking CreateMove";

    IVEngineClient* pIVEngineClient = MadFramework::InterfaceManager::GetInterface<IVEngineClient>();

    PLOG_INFO << "IClientEntityList: "  << MadFramework::InterfaceManager::GetInterface<IClientEntityList>();
    PLOG_INFO << "IVEngineClient: "     << MadFramework::InterfaceManager::GetInterface<IVEngineClient>();
    PLOG_INFO << "IBaseClientDLL: "     << MadFramework::InterfaceManager::GetInterface<IBaseClientDLL>();
    PLOG_INFO << "IViewRender: "        << MadFramework::InterfaceManager::GetInterface<IViewRender>();
    PLOG_INFO << "IEngineTrace: "       << MadFramework::InterfaceManager::GetInterface<IEngineTrace>();

    PLOG_INFO << "Has ViewMatrix: " << MadFramework::InterfaceManager::GetInterface<IViewRender>()->HasWorldToScreenMatrix();
    PLOG_INFO << "ViewMatrix: " << MadFramework::InterfaceManager::GetInterface<IViewRender>()->GetWorldToScreenMatrix();
#endif

    //@TODO 2D Map
	//@TODO check wtf this is dword_130D0298 is 2 or 0 (2 means is cheater?)
    //MadFramework::NetVarManager::ConsoleDump();

#ifdef SOURCE_ENGINE_SDK
    while (!pIVEngineClient->IsInGame())
    {
        if (!MadFramework::Running())
        {
            PLOG_INFO << "Exiting Module Early";
            FreeLibraryAndExitThread(static_cast<HMODULE>(lpThreadParameter), 0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    MadFramework::Math::SourceEngine::SetViewMatrix(MadFramework::InterfaceManager::GetInterface<IViewRender>()->GetWorldToScreenMatrix());
    MadFramework::Math::SourceEngine::SetScreenInfo();
#endif

    InitSounds(); //For Hit Sounds

    while(MadFramework::Running())
        MadFramework::MainThreadLogic();

    PLOG_INFO << "Exiting Module";
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpThreadParameter), 0);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpvReserved)  
{
    UNREFERENCED_PARAMETER(lpvReserved);

    if(fdwReason == DLL_PROCESS_ATTACH)
    {
        (void)DisableThreadLibraryCalls(hInstance);

        HANDLE thread_handle = CreateThread(nullptr, 0, ThreadEntry, hInstance, 0, nullptr);
        (void)CloseHandle(thread_handle);
    }

    if(fdwReason == DLL_PROCESS_DETACH)
    {
        MadFramework::FrameworkExit();
        DisableCLC_ScreenshotFunctionsHook();
        DisableUserMessageHook();
    }

    return TRUE;  
}