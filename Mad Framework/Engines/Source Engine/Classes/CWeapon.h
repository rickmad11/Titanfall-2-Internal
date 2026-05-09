#pragma once

class CWeapon
{
public:
	NETVAR_STRING(GetWeaponName, const char, "CWeaponX", "m_iName")
	NETVAR_OFFSET(GetWeaponView, Vector3, 0x12C)
	NETVAR_OFFSET(GetWeaponModel, const char*, 0x7B8)
	NETVAR_OFFSET(GetWeaponRealName, const char*, 0x1700)
	NETVAR_OFFSET(GetProjectileSpeed, float, 0x1740)
	NETVAR_OFFSET(GetGravityScale, int, 0x1718)
	NETVAR_OFFSET(GetWeaponRecoil, float, 0x12F0)
	NETVAR_OFFSET(GetWeaponZoom, float, 0x12E0)
	NETVAR_OFFSET(GetActiveSkinID, int, 0xF80)
	NETVAR_OFFSET(GetFiringRate, int, 0x171C)
	NETVAR_OFFSET(GetWeaponSlot, int, 0x12FC)
	NETVAR_OFFSET(HasOwner, int, 0x3E0)
	NETVAR_OFFSET(GetCamoRange, int, 0xF88)
	NETVAR(GetWeaponClipAmmo, int, "CWeaponX", "m_ammoInClip")
	NETVAR(GetWeaponStockAmmo, int, "CWeaponX", "m_ammoInStockpile")
	NETVAR(IsReloading, bool, "CWeaponX", "m_bInReload")
};