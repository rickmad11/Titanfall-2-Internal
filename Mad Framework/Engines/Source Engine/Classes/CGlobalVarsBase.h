#pragma once

class CGlobalVarsBase
{
public:

	CGlobalVarsBase(bool bIsClient) :
		m_bClient(bIsClient),
		nTimestampNetworkingBase(100),
		nTimestampRandomizeWindow(32)
	{
	}

	// This can be used to filter debug output or to catch the client or server in the act.
	bool IsClient() const
	{
		return m_bClient;
	}

	// for encoding m_flSimulationTime, m_flAnimTime
	int GetNetworkBase(int nTick, int nEntity)
	{
		int nEntityMod = nEntity % nTimestampRandomizeWindow;
		int nBaseTick = nTimestampNetworkingBase * (int)((nTick - nEntityMod) / nTimestampNetworkingBase);
		return nBaseTick;
	}

public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				maxClients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				simTicksThisFrame;
	int				network_protocol;
	/*CSaveRestoreData*/void* pSaveData;
	bool			m_bClient;
	int				nTimestampNetworkingBase;
	int				nTimestampRandomizeWindow;

};