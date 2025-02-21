#include "pch.h"

#include "Memory.h"
#include "../../Windows/PEB.h"
#include "../../Windows/TEB.h"

namespace MadFramework::Memory
{
	bool IsValid(void const* const pMemoryBlock)
	{
		MEMORY_BASIC_INFORMATION memory_basic_information {};

		if (VirtualQuery(pMemoryBlock, &memory_basic_information, sizeof(MEMORY_BASIC_INFORMATION)) == 0)
			return false;

		if(memory_basic_information.AllocationProtect != 0)
		{
			if (memory_basic_information.State == MEM_FREE || memory_basic_information.State == MEM_RESERVE)
				return false;

			return true;
		}

		return false;
	}

	bool IsValid(void const* const pMemoryBlock, MEMORY_BASIC_INFORMATION& outMemoryInfo)
	{
		MEMORY_BASIC_INFORMATION memory_basic_information{};

		if (VirtualQuery(pMemoryBlock, &memory_basic_information, sizeof(MEMORY_BASIC_INFORMATION)) == 0)
			return false;

		outMemoryInfo = memory_basic_information;

		if (memory_basic_information.AllocationProtect != 0)
		{
			if (memory_basic_information.State == MEM_FREE || memory_basic_information.State == MEM_RESERVE)
				return false;

			return true;
		}

		return false;
	}

	bool HasWritePermission(void const* const pMemoryBlock)
	{
		MEMORY_BASIC_INFORMATION memory_basic_information{};

		if(IsValid(pMemoryBlock, memory_basic_information))
		{
			const DWORD protection_flags = memory_basic_information.Protect;
			return (protection_flags & (PAGE_READWRITE | PAGE_EXECUTE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_WRITECOPY)) != 0;
		}

		return false;
	}

	bool HasReadPermission(void const* const pMemoryBlock)
	{
		MEMORY_BASIC_INFORMATION memory_basic_information{};

		if (IsValid(pMemoryBlock, memory_basic_information))
		{
			const DWORD protection_flags = memory_basic_information.Protect;
			return (protection_flags & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_READ)) != 0;
		}

		return false;
	}

	std::vector<int> ToNormalizedSignature(const char* pString, char cEliminator)
	{
		std::vector<int> vTempSignature{};
		while (pString && *pString != '\0')
		{
			if (*pString == ' ')
			{
				++pString;
				continue;
			}

			if (*pString == cEliminator && (pString + 1) != nullptr && *(pString + 1) != '\0' && *(pString + 1) == cEliminator) {
				vTempSignature.push_back(-1);
				pString += 2;
				continue;
			}

			if (*pString == cEliminator)
			{
				vTempSignature.push_back(-1);
				++pString;
				continue;
			}

			unsigned long ul = std::strtoul(pString, const_cast<char**>(&pString), 16);
			vTempSignature.push_back(static_cast<int>(ul));
		}
		return vTempSignature;
	}

	BYTE* SafeSignatureScan(const char* pByteArray, char cEliminator, BYTE* pModule)
	{

		if (pModule)
		{
			PIMAGE_DOS_HEADER pimage_dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(pModule);
			PIMAGE_NT_HEADERS pimage_nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(pimage_dos_header->e_lfanew + pModule);

			DWORD dwImageSize = pimage_nt_headers->OptionalHeader.SizeOfImage;

			std::vector<int> vSignature = ToNormalizedSignature(pByteArray, cEliminator);

			BYTE* pMemoryBlock = nullptr;
			for (size_t i = 0; i < dwImageSize - vSignature.size(); i++)
			{
				if(i % (1 << 12))
				{
					if (!HasReadPermission(pModule + i))
						continue;
				}

				bool found = true;

				for (size_t j = 0; j < vSignature.size(); j++)
				{
					if (pModule[j + i] != vSignature[j] && vSignature[j] != -1)
					{
						found = false;
						break;
					}
				}

				if (found)
				{
					pMemoryBlock = pModule + i;
					break;
				}

			}

			return pMemoryBlock;
		}

		return nullptr;
	}

	BYTE* SafeSignatureScan(std::span<const char> ByteArray, char cEliminator, BYTE* pModule)
	{
		return SafeSignatureScan(ByteArray.data(), cEliminator, pModule);
	}

	BYTE* SignatureScan(const char* pByteArray, char cEliminator, BYTE* pModule)
	{
		if (pModule)
		{
			PIMAGE_DOS_HEADER pimage_dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(pModule);
			PIMAGE_NT_HEADERS pimage_nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(pimage_dos_header->e_lfanew + pModule);

			DWORD dwImageSize = pimage_nt_headers->OptionalHeader.SizeOfImage;

			std::vector<int> vSignature = ToNormalizedSignature(pByteArray, cEliminator);

			BYTE* pMemoryBlock = nullptr;
			for (size_t i = 0; i < dwImageSize - vSignature.size(); i++)
			{
				bool found = true;

				for (size_t j = 0; j < vSignature.size(); j++)
				{
					if (pModule[j + i] != vSignature[j] && vSignature[j] != -1)
					{
						found = false;
						break;
					}
				}

				if (found)
				{
					pMemoryBlock = pModule + i;
					break;
				}

			}

			return pMemoryBlock;
		}

		return nullptr;
	}

	BYTE* SignatureScan(std::span<const char> ByteArray, char cEliminator, BYTE* pModule)
	{
		return SignatureScan(ByteArray.data(), cEliminator, pModule);
	}

	BYTE* SignatureScan(std::span<const char> ByteArray, char cEliminator, const wchar_t* ModuleName)
	{
		return SignatureScan(ByteArray.data(), cEliminator, static_cast<BYTE*>(GetModuleBase(ModuleName)));
	}

	BYTE* SafeSignatureScan(std::span<const char> ByteArray, char cEliminator, const wchar_t* ModuleName)
	{
		return SafeSignatureScan(ByteArray.data(), cEliminator, static_cast<BYTE*>(GetModuleBase(ModuleName)));
	}

	void* GetModuleBase(std::wstring ModuleName)
	{
		std::transform(ModuleName.begin(), ModuleName.end(), ModuleName.begin(),
			[](wchar_t c) { return std::towlower(c); });

		PPEB pProcessEnvironmentBlock = NtCurrentTeb()->ProcessEnvironmentBlock;
		PPEB_LDR_DATA pProcessLdrData = pProcessEnvironmentBlock->Ldr;

		PLIST_ENTRY pFirstListEntry = reinterpret_cast<PLIST_ENTRY>(reinterpret_cast<BYTE*>(pProcessLdrData) + offsetof(_PEB_LDR_DATA, InLoadOrderModuleList));

		for (std::size_t index = 0; index < 3; index++)
		{
			for (PLIST_ENTRY curr = pFirstListEntry[index].Flink; curr != &pFirstListEntry[index]; curr = curr->Flink)
			{
				PLDR_DATA_TABLE_ENTRY pLdrDataTableEntry = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<BYTE*>(curr) - sizeof(LIST_ENTRY) * index);

				std::wstring wDllName{ pLdrDataTableEntry->BaseDllName.Buffer };

				std::transform(wDllName.begin(), wDllName.end(), wDllName.begin(),
					[](wchar_t c) { return std::towlower(c); });

				if (wDllName == ModuleName)
					return pLdrDataTableEntry->DllBase;
			}
		}

		return nullptr;
	}

	std::wstring GetModuleName(void* const ModuleBase)
	{
		PPEB pProcessEnvironmentBlock = NtCurrentTeb()->ProcessEnvironmentBlock;
		PPEB_LDR_DATA pProcessLdrData = pProcessEnvironmentBlock->Ldr;

		PLIST_ENTRY pFirstListEntry = reinterpret_cast<PLIST_ENTRY>(reinterpret_cast<BYTE*>(pProcessLdrData) + offsetof(_PEB_LDR_DATA, InLoadOrderModuleList));

		for (std::size_t index = 0; index < 3; index++)
		{
			for (PLIST_ENTRY curr = pFirstListEntry[index].Flink; curr != &pFirstListEntry[index]; curr = curr->Flink)
			{
				PLDR_DATA_TABLE_ENTRY pLdrDataTableEntry = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<BYTE*>(curr) - sizeof(LIST_ENTRY) * index);

				if (pLdrDataTableEntry->DllBase == ModuleBase)
					return std::wstring{pLdrDataTableEntry->BaseDllName.Buffer};
			}
		}

		return {};
	}

	DWORD GetModuleSize(const wchar_t* ModuleName)
	{
		BYTE* const pModule = reinterpret_cast<BYTE*>(GetModuleBase(ModuleName));

		PIMAGE_DOS_HEADER pimage_dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(pModule);
		PIMAGE_NT_HEADERS pimage_nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(pimage_dos_header->e_lfanew + pModule);

		return pimage_nt_headers->OptionalHeader.SizeOfImage;
	}

	DWORD GetModuleSize(void* const ModuleBase)
	{
		BYTE* const pModule = reinterpret_cast<BYTE*>(ModuleBase);

		PIMAGE_DOS_HEADER pimage_dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(pModule);
		PIMAGE_NT_HEADERS pimage_nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(pimage_dos_header->e_lfanew + pModule);

		return pimage_nt_headers->OptionalHeader.SizeOfImage;
	}

	DWORD GetCurrentSessionID()
	{
		return NtCurrentTeb()->ProcessEnvironmentBlock->SessionId;
	}

	bool IsBeingDebugged()
	{
		return NtCurrentTeb()->ProcessEnvironmentBlock->BeingDebugged;
	}

	void* GetExport(const wchar_t* ModuleName, const char* ExportFunctionName)
	{
		BYTE* const pModule = static_cast<BYTE*>(GetModuleBase(ModuleName));

		if(pModule)
		{
			PIMAGE_DOS_HEADER pimage_dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(pModule);
			PIMAGE_NT_HEADERS pimage_nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(pimage_dos_header->e_lfanew + pModule);

			PIMAGE_DATA_DIRECTORY pimage_data_directory = &pimage_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

			if (pimage_data_directory->Size > 0)
			{
				void* found_function = nullptr;

				PIMAGE_EXPORT_DIRECTORY p_image_export_directory = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(pimage_data_directory->VirtualAddress + pModule);

				DWORD* pAddressOfFunctions = reinterpret_cast<DWORD*>(p_image_export_directory->AddressOfFunctions + pModule);
				DWORD* pAddressOfNames = reinterpret_cast<DWORD*>(p_image_export_directory->AddressOfNames + pModule);
				WORD* pAddressOfNameOrdinals = reinterpret_cast<WORD*>(p_image_export_directory->AddressOfNameOrdinals + pModule);

				for (size_t i = 0; i < p_image_export_directory->NumberOfNames; i++)
				{
					if (strcmp(reinterpret_cast<const char*>(pAddressOfNames[i] + pModule), ExportFunctionName) == 0)
						found_function = pAddressOfFunctions[pAddressOfNameOrdinals[i]] + pModule;
				}

				if (found_function >= p_image_export_directory && found_function < reinterpret_cast<void*>(p_image_export_directory + pimage_data_directory->Size))
				{
					std::string forwarded_function{ static_cast<const char*>(found_function) };

					std::size_t index = forwarded_function.find('.');

					std::wstring module_name{ forwarded_function.cbegin(), forwarded_function.cbegin() + index };
					std::string function_name{ forwarded_function.cbegin() + index, forwarded_function.cend() };

					module_name += L".dll";

					return GetExport(module_name.c_str(), function_name.c_str());
				}

				return found_function;
			}
		}

		return nullptr;
	}

	void* GetExport(void* ModuleBase, const char* ExportFunctionName)
	{
		return GetExport(GetModuleName(ModuleBase).c_str(), ExportFunctionName);
	}

	void* GetVTableFunctionAddress(void* pClassInstance, const int VTableIndex)
	{
		if (pClassInstance)
		{
			void** fTable = *reinterpret_cast<void***>(pClassInstance);
			return fTable[VTableIndex];
		}

		return nullptr;
	}
}
