#pragma once

//Windows
#include <Windows.h>
#include <wrl/client.h>
#include <shlobj_core.h>

//C++
#include <cstdint>
#include <span>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cwctype>
#include <numbers>
#include <filesystem>
#include <array>

//DirectX
#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

//MadRenderer Internal DirectXTK lib
#include "lib/MadRenderer Internal/inc/Audio.h"
#include "lib/MadRenderer Internal/inc/CommonStates.h"
#include "lib/MadRenderer Internal/inc/SimpleMath.h"
#include "lib/MadRenderer Internal/inc/SpriteFont.h"
#include "lib/MadRenderer Internal/inc/WICTextureLoader.h"

//MadRenderer Internal
#include "lib/MadRenderer Internal/DX11.h"
#pragma comment(lib, "MadRenderer Internal.lib")
#pragma comment(lib, "DirectXTK.lib")
#include "lib/MadRenderer Internal/CursorRaw.h"

//Mad Framework Libs
#include "lib/plog/Log.h"
#include "lib/plog/Initializers/ConsoleInitializer.h"
#include "lib/plog/Appenders/ConsoleAppender.h"
#include "lib/plog/Formatters/TxtFormatter.h"
#include "lib/mINI/ini.h"

//Mad Framework Menu (zgui)
#include "lib/ZGUI/zgui.hh"

//Mad Framework
#include "Types.h"
#include "Settings.h"
#include "Utility/Memory/Memory.h"
#include "Utility/Math/Math.h"
#include "Utility/Utility.h"
#include "Log Manager/LogManager.h"
#include "Config Manager/ConfigManager.h"

//Mad Framework Source SDK
#include "Engines/Source Engine/Source-SDK.h"

//SafetyHook
#include "lib/SafetyHook/safetyhook.hpp"