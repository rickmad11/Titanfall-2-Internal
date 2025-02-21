#pragma once

class IClientUnknown;

class IClientThinkable
{
public:
	virtual IClientUnknown *				GetIClientUnknown() = 0;
	virtual void							ClientThink() = 0;
	virtual /*CClientThinkHandlePtr*/void*	GetThinkHandle() = 0;
	virtual void							SetThinkHandle(/*CClientThinkHandlePtr*/void* hThink) = 0;
	virtual void							Release() = 0;
};
