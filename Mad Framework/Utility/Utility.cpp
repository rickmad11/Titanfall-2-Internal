#include "pch.h"
#include "Utility.h"

namespace MadFramework::Utility
{
	WindowInfo GetCurrentWindowData()
	{
		WindowInfo windowData {};

		windowData.processID = GetCurrentProcessId();
		EnumWindows([](HWND hwnd, LPARAM lparam) -> BOOL
			{
				WindowInfo* pWindowInfo = reinterpret_cast<WindowInfo*>(lparam);

				DWORD curr_processID = 0;
				DWORD current_thread_id = GetWindowThreadProcessId(hwnd, &curr_processID);

				//I was wondering why my Window resized and the Game froze then I realized I got my debug Console handle lol
				wchar_t window_class_name[MAX_PATH];
				if (GetClassNameW(hwnd, window_class_name, MAX_PATH) &&
					wcscmp(window_class_name, L"ConsoleWindowClass") != 0 && wcscmp(window_class_name, L"DXGIWatchdogThreadWindow") != 0 &&
					pWindowInfo->processID == curr_processID)
				{
					GUITHREADINFO gui_thread_info{ .cbSize = sizeof(GUITHREADINFO) };
					if (GetGUIThreadInfo(current_thread_id, &gui_thread_info))
					{
						pWindowInfo->windowHandle = hwnd;
						return FALSE;
					}
					return TRUE;
				}

				return TRUE;
			}, reinterpret_cast<LPARAM>(&windowData));

		return windowData;
	}
}