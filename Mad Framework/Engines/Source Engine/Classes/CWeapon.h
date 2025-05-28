#pragma once

class CWeapon
{
public:
	NETVAR_STRING(GetWeaponName, const char, "CWeaponX", "m_iName")
	NETVAR_OFFSET(GetWeaponModel, const char*, 0x7B8)
	NETVAR_OFFSET(GetWeaponRealName, const char*, 0x1700)
	NETVAR_OFFSET(GetWeaponRecoil, float, 0x12F0)
	NETVAR_OFFSET(GetWeaponZoom, float, 0x12E0)
	NETVAR_OFFSET(GetActiveSkinID, int, 0xF80)
	NETVAR_OFFSET(GetFiringRate, int, 0x171C)
	NETVAR_OFFSET(GetWeaponSlot, int, 0x12FC)
	NETVAR_OFFSET(HasOwner, bool, 0x1e6) // honestly idk what this value is however it is the only one that I found to be different if an entity is owning this weapon (0x1e7 was also a candidate)
	NETVAR(GetWeaponClipAmmo, int, "CWeaponX", "m_ammoInClip")
	NETVAR(GetWeaponStockAmmo, int, "CWeaponX", "m_ammoInStockpile")
	NETVAR(IsReloading, bool, "CWeaponX", "m_bInReload")
};