#pragma once

#include "Utility/Memory/Memory.h"

namespace MadFramework::InterfaceManager::Types
{
#ifndef _WIN64
	typedef void* (__cdecl* CreateInterface)(const char* pString, DWORD* pReturnCode);
#else
	typedef void* (__fastcall* CreateInterface)(const char* pString, DWORD* pReturnCode);
#endif
}

namespace MadFramework::InterfaceManager
{
	template <typename T_INTERFACE>
	T_INTERFACE GetInterfaceAddress(const wchar_t* ModuleName, const char* InterfaceName)
	{
		DWORD discard_return_code;
		void* pInterface = static_cast<Types::CreateInterface>(Memory::GetExport(ModuleName, "CreateInterface")) (InterfaceName, &discard_return_code);
		return pInterface ? static_cast<T_INTERFACE>(pInterface) : T_INTERFACE{};
	}

	template <typename T_INTERFACE, typename TCOMPARE_INTERFACE = void*>
	T_INTERFACE* GetOrInitializeInterface(T_INTERFACE*& interfacePtr, const wchar_t* module, std::span<const char> const& interfaceName)
	{
		if (interfacePtr == nullptr)
		{
			if constexpr (std::is_same_v<T_INTERFACE, IViewRender>) {
				if (BYTE* const signature_result = Memory::SignatureScan(interfaceName, '?', module))
				{
					int offset = *reinterpret_cast<int*>(signature_result + 3);
					BYTE* next_ip = signature_result + 7;
					interfacePtr = *reinterpret_cast<T_INTERFACE**>(next_ip + offset);
					return interfacePtr;
				}
				return nullptr;
			}

			if constexpr (std::is_same_v<TCOMPARE_INTERFACE, void*>)
			{
				interfacePtr = GetInterfaceAddress<T_INTERFACE*>(module, interfaceName.data());
				return interfacePtr;
			}
		}

		return interfacePtr;
	}

	template <typename T_INTERFACE>
	T_INTERFACE* GetInterface() requires !std::is_pointer_v<T_INTERFACE>
	{
		if constexpr (std::is_same_v<T_INTERFACE, IBaseClientDLL>)
		{
			static IBaseClientDLL* pIBaseClientDLL = nullptr;
			return GetOrInitializeInterface(pIBaseClientDLL, L"client.dll", INTERFACE_NAME_I_BASE_CLIENT_DLL);
		}

		if constexpr  (std::is_same_v<T_INTERFACE, IVEngineClient>)
		{
			static IVEngineClient* pIVEngineClient = nullptr;
			return GetOrInitializeInterface(pIVEngineClient, L"engine.dll", INTERFACE_NAME_I_VENGINE_CLIENT);;
		}

		if constexpr (std::is_same_v<T_INTERFACE, IClientEntityList>)
		{
			static IClientEntityList* pIClientEntityList = nullptr;
			return GetOrInitializeInterface(pIClientEntityList, L"client.dll", INTERFACE_NAME_I_CLIENT_ENTITY_LIST);
		}

		if constexpr (std::is_same_v<T_INTERFACE, IEngineTrace>)
		{
			static IEngineTrace* pIEngineTrace = nullptr;
			return GetOrInitializeInterface(pIEngineTrace, L"engine.dll", INTERFACE_NAME_I_ENGINE_TRACE);
		}

		if constexpr (std::is_same_v<T_INTERFACE, IViewRender>)
		{
			static IViewRender* pIViewRender = nullptr;
			return GetOrInitializeInterface<T_INTERFACE, IViewRender>(pIViewRender, L"client.dll", INTERFACE_AOB_I_VIEW_RENDER);
		}

		return nullptr;
	}
}