#pragma once

class CUserCmd
{
public:
	int32_t m_commandNumber; //0x0000
	int32_t m_commandNumber2; //0x0004
	int32_t m_commandTick; //0x0008
	Vector3 m_worldViewAngles; //0x000C
	char pad_0018[4]; //0x0018
	Vector3 m_localViewAngles; //0x001C
	Vector3 m_attackAngles; //0x0028
	Vector3 m_moves; //0x0034
	int32_t m_buttons; //0x0040
	int8_t m_impulse; //0x0044
	int16_t m_weaponSelect; //0x0045
	int32_t m_weaponSubType; //0x0047
	char pad_004B[4]; //0x004B
	int32_t m_randomSeed; //0x0050
	char pad_0054[84]; //0x0054
	char pad1[4];
	float m_gameTime; //0x00AC
	char pad[4];
	double m_msTime; //0x00B0
}; //Size: 0x10DC