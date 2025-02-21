#pragma once

struct CGlobalVars : CGlobalVarsBase {
	char pad[0x8]; 
	int m_frameCount; 
	int absoluteframetime; 
	float m_curTime; // 0x10 (0x4)
	char pa2d[0xc];
	float m_float20; // 0x20 (0x4)
	char aa[0x8];
	float m_float2C; // 0x2C (0x4)
	float m_frameTime; // 0x30 (0x4)
	int m_int34; // 0x34 (0x4)
	char ok[0x4];
	unsigned int m_int3C; // 0x3C (0x4)
	float m_intervalPerTick; // 0x40 (0x4)

	static CGlobalVars* Get() noexcept;
};