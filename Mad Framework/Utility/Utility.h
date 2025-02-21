#pragma once

namespace MadFramework::Utility
{
	struct WindowInfo
	{
		HWND windowHandle = nullptr;
		DWORD processID = 0;
	};

	WindowInfo GetCurrentWindowData();

	//Assuming this is running in a Thread which is being executed each frame
	//since this function may be called by multiple functions (menu, watermark...) I need different local static vars and the template helps me here 
	template <unsigned int callerID = 0>
	inline unsigned int GetCurrentFpsCount() noexcept
	{
		//I cant decide anymore whenever or not to use snake case style
		static unsigned int fixed_fps_count = 0;
		static unsigned int fps_counter = 0;
		static float prevTickCount = 0.f;

		float currTickCount = clock() * 0.001f;

		++fps_counter;
		if (currTickCount - prevTickCount >= 1.f)
		{
			fixed_fps_count = fps_counter;
			fps_counter = 0;
			prevTickCount = currTickCount;
		}

		return fixed_fps_count;
	}
}