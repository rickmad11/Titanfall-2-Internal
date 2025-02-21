#pragma once

namespace MadFramework
{
	//Flags that tell the Render function if it should render stuff
	struct RenderControlFlags
	{
		bool isTakingScreenshot = false;
		bool isMenuOpen = false;
	}inline RenderCFs {};

	inline bool g_running_flag = true;

	//Everything that requires rendering goes here. (Will be called by the Render Hook)
	void Render() noexcept;

	//Stuff that is not required to Render and is being executed by the thread that has been created at DllEntry
	void MainThreadLogic() noexcept;

	//Stuff that is not required to Render but is executed inside a Hook (When Creating a thread is not an option)
	void MainHookLogic() noexcept;

	//Is expected to be called when Dll is trying to be unloaded (unhooking, saving settings...)
	void Cleanup() noexcept;

	//Does default Framework Cleanup (unhooking stuff)
	void FrameworkExit() noexcept;

	//whenever or not the cheat is running or wants to exit Default Key: VK_END
	bool Running() noexcept;

	//Calls Running with false (@TODO this is an ugly way to handle running/exit find a better way doing this)
	void Exit() noexcept;

	//Draws top left fps and project name
	void Watermark() noexcept;
}