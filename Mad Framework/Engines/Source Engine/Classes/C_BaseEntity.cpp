#include "pch.h"

#include "C_BaseEntity.h"

CWeapon* C_BaseEntity::GetActiveWeapon() noexcept
{
	static BYTE* pPattern = MadFramework::Memory::SignatureScan("E8 ? ? ? ? 48 85 C0 74 28 48 8B CF", '?', L"client.dll");
	static CWeapon*(__fastcall* pfGetActiveWeapon)(C_BaseEntity*) = reinterpret_cast<decltype(pfGetActiveWeapon)>( (pPattern + 5) + (*reinterpret_cast<int*>(pPattern + 1)) );

	return pfGetActiveWeapon(this);
}

bool C_BaseEntity::IsTitan() noexcept
{
	//Vtable Index is 0x96 in case pattern scan is too ugly for u
	static BYTE* pPattern = MadFramework::Memory::SignatureScan("48 8B 01 FF A0 B0 04 00 00", '?', L"client.dll");
	static bool (__fastcall * pfIsTitan)(C_BaseEntity*) = reinterpret_cast<decltype(pfIsTitan)>(pPattern);

	return pfIsTitan(this);
}

bool C_BaseEntity::IsPlayer() noexcept
{
	//Vtable Index is 0x95 in case pattern scan is too ugly for u
	static BYTE* pPattern = MadFramework::Memory::SignatureScan("48 8B 01 FF A0 A8 04 00 00", '?', L"client.dll");
	static bool(__fastcall * pfIsPlayer)(C_BaseEntity*) = reinterpret_cast<decltype(pfIsPlayer)>(pPattern);

	return pfIsPlayer(this);
}

