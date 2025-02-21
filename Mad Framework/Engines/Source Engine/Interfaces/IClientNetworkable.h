#pragma once

class ClientClass;
class IClientUnknown;
class bf_read;

class IClientNetworkable
{
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	ClientClass*			GetClientClass();
	virtual void			NotifyShouldTransmit(int state) = 0;
	virtual void			OnPreDataChanged(int updateType) = 0;
	virtual void			OnDataChanged(int updateType) = 0;
	virtual void			PreDataUpdate(int updateType) = 0;
	virtual void			PostDataUpdate(int updateType) = 0;
	virtual bool			IsDormant(void) = 0;
	virtual int				entindex(void) const = 0;
	virtual void			ReceiveMessage(int classID, bf_read& msg) = 0;
	virtual void*			GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;
};
