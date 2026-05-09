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

bool C_BaseEntity::IsPlayerDecoy() noexcept
{
	return MadFramework::Memory::InvokeVTableFunction<bool>(this, 0x9D);
}

bool C_BaseEntity::IsNpc() noexcept
{
	return MadFramework::Memory::InvokeVTableFunction<bool>(this, 0x9C);
}

static bool GunRequiresAimFix(CWeapon* p_weapon)
{
	if (const char* p_weapon_name = p_weapon->GetWeaponRealName())
	{
		auto hash_check = [](std::string_view str) -> size_t
			{
				size_t hash = 14695981039346656037ULL;
				for (char c : str) {
					hash ^= static_cast<size_t>(c);
					hash *= 1099511628211ULL;
				}
				return hash;
			};

		constexpr size_t kraber_hash = 15350399102872810817;
		constexpr size_t longbow_hash = 8865983035117277415;

		auto hash_value = hash_check(p_weapon_name);
		if (hash_value == kraber_hash || hash_value == longbow_hash)
			return true;
	}

	return false;
}

Vector2* C_BaseEntity::fixAngles(float (&buffer)[3])
{
	static BYTE* pPattern = MadFramework::Memory::SignatureScan("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 60 0F 29 74 24 ? 0F 29 7C 24 ? 48 8B F2", '?', L"client.dll");
	static Vector2* (__fastcall * weapon_angle)(C_BaseEntity*, void*) = reinterpret_cast<decltype(weapon_angle)>(pPattern);

	if (auto weapon = this->GetActiveWeapon(); weapon && GunRequiresAimFix(weapon))
		return weapon_angle(this, buffer);

	memset(buffer, 0, sizeof(buffer));
	return reinterpret_cast<Vector2*>(buffer);
}
