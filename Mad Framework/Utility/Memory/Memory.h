#pragma once

#ifdef USING_OWN_HEADER
#include "Headers.h"
#endif

namespace MadFramework::Memory
{
	bool IsValid(void const* const pMemoryBlock);
	bool IsValid(void const* const pMemoryBlock, MEMORY_BASIC_INFORMATION& outMemoryInfo);
	bool HasWritePermission(void const* const pMemoryBlock);
	bool HasReadPermission(void const* const pMemoryBlock);

	/*
	 * Example Signatures that are supported
	 * E8 ?? ?? ?? ?? 3D 01 00 15 C0 74 ?? 8B C8 C1 F9 1F 83 E1 01 FF C1 83 E9 01 75 ?? 8B 43
	 * E8 ? ? ? ? 3D 01 00 15 C0 74 ? 8B C8 C1 F9 1F 83 E1 01 FF C1 83 E9 01 75 ? 8B 43
	 * you can use anything for the ? just set the cEliminator appropriately
	 */
	BYTE* SignatureScan(std::span<const char> ByteArray, char cEliminator, BYTE* pModule);
	BYTE* SignatureScan(const char* pByteArray, char cEliminator, BYTE* pModule);
	BYTE* SignatureScan(std::span<const char> ByteArray, char cEliminator, const wchar_t* ModuleName);

	//Same as above but checks for page protection (way slower)
	BYTE* SafeSignatureScan(const char* pByteArray, char cEliminator, BYTE* pModule);
	BYTE* SafeSignatureScan(std::span<const char> ByteArray, char cEliminator, BYTE* pModule);
	BYTE* SafeSignatureScan(std::span<const char> ByteArray, char cEliminator, const wchar_t* ModuleName);

	void* GetModuleBase(std::wstring ModuleName);
	std::wstring GetModuleName(void* const ModuleBase);

	DWORD GetModuleSize(const wchar_t* ModuleName);
	DWORD GetModuleSize(void* const ModuleBase);

	DWORD GetCurrentSessionID();
	bool IsBeingDebugged();

	void* GetExport(const wchar_t* ModuleName, const char* ExportFunctionName);
	void* GetExport(void* ModuleBase, const char* ExportFunctionName);

	//Used internally for my Sig scanners, should not really be available for other translation units but who knows maybe has more usage
	std::vector<int> ToNormalizedSignature(const char* pString, char cEliminator);

	template <typename ReturnType, typename... Args>
	ReturnType InvokeVTableFunction(void* pClassInstance, const int VTableIndex, Args... args)
	{
		if(pClassInstance)
		{
			void** fTable = *reinterpret_cast<void***>(pClassInstance);
			return reinterpret_cast<ReturnType(__thiscall*)(void*, decltype(args)...)>(fTable[VTableIndex])(pClassInstance, args...);
		}

		return ReturnType{};
	}

	void* GetVTableFunctionAddress(void* pClassInstance, const int VTableIndex);
}
