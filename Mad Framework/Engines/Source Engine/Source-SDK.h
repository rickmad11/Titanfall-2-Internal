#pragma once

#ifdef SOURCE_ENGINE_SDK

//VTable indices
namespace SourceEngine::IClientEntityList::Index
{
	constexpr int GetClientNetworkable = 0;
	constexpr int GetClientEntity = 3;
	constexpr int NumberOfEntities = 5;
	constexpr int GetHighestEntity = 6;
	constexpr int SetMaxEntities = 7;
	constexpr int GetMaxEntities = 8;
}

namespace SourceEngine::IViewRender::Index
{
	constexpr int GetWorldToScreenMatrix = 14;
	constexpr int HasWorldToScreenMatrix = 15;
}

namespace SourceEngine::IClientNetworkable::Index
{
	constexpr int GetClientClass = 2;
}

namespace SourceEngine::IBaseClientDLL::Index
{
	constexpr int GetAllClasses = 11;
}

namespace SourceEngine::IVEngineClient::Index
{
	constexpr int GetLocalPlayer = 43;
	constexpr int GetPlayerInfo = 28;
	constexpr int IsInGame = 200;
}

namespace SourceEngine::IClientRenderable::Index
{
	constexpr int SetupBones = 13;
}

namespace SourceEngine::IEngineTrace::Index
{
	constexpr int TraceRay = 3;
}

//Class relative Offsets
namespace SourceEngine::ClientClass::Offset
{
	constexpr int GetName = 0x40;
	constexpr int GetClassID = 0x38;
}

//Interface Strings
#define INTERFACE_NAME_I_BASE_CLIENT_DLL "VClient018"
#define INTERFACE_NAME_I_VENGINE_CLIENT "VEngineClient013"
#define INTERFACE_NAME_I_CLIENT_ENTITY_LIST "VClientEntityList003"
#define INTERFACE_NAME_I_ENGINE_TRACE "EngineTraceClient004"

//All the Interfaces we get through pattern scanning may require manual adjustments in the GetInterface function
//Interface AOB
#define INTERFACE_AOB_I_VIEW_RENDER "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 8B 05 ? ? ? ? 48 8D 35 ? ? ? ? A8 02"

#include "Classes/ClientClass.h"
#include "Classes/CBaseHandle.h"
#include "Classes/C_BaseEntity.h"
#include "Classes/matrix3x4_t.h"
#include "Classes/QAngle.h"
#include "Classes/RecvProp.h"
#include "Classes/RecvTable.h"
#include "Classes/Quaternion.h"
#include "Classes/CGlobalVarsBase.h"
#include "Classes/vrect_t.h"
#include "Classes/VMatrix.h"
#include "Classes/CViewRender.h"
#include "Classes/CViewSetup.h"
#include "Classes/CWeapon.h"
#include "Classes/CGlobalVars.h"
#include "Classes/CTraceFilter.h"
#include "Classes/CUserCmd.h"


#include "Interfaces/IClientNetworkable.h"
#include "Interfaces/IHandleEntity.h"
#include "Interfaces/IClientEntity.h"
#include "Interfaces/IClientRenderable.h"
#include "Interfaces/IClientThinkable.h"
#include "Interfaces/IClientUnknown.h"
#include "Interfaces/IBaseClientDLL.h"
#include "Interfaces/INetChannelInfo.h"
#include "Interfaces/IVEngineClient.h"
#include "Interfaces/IClientEntityList.h"
#include "Interfaces/IViewRender.h"
#include "Interfaces/IEngineTrace.h"
#include "Interfaces/ITraceFilter.h"

#include "NetVarManager/NetVarManager.h"
#include "Interface Manager/Interface Manager.h"

#endif
