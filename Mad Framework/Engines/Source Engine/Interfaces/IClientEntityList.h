#pragma once

class IClientEntityList
{
public:
	IClientNetworkable *			GetClientNetworkable(int entnum);
	virtual IClientNetworkable*		GetClientNetworkableFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientUnknown*			GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
	IClientEntity*					GetClientEntity(int entnum);
	virtual IClientEntity*			GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	int								NumberOfEntities(bool bIncludeNonNetworkable);
	int								GetHighestEntityIndex(void);
	void							SetMaxEntities(int maxents);
	int								GetMaxEntities();
};
