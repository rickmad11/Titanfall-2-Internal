#pragma once

class RecvTable;

typedef class IClientNetworkable* (*CreateEventFn)();
typedef class IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);

class ClientClass
{
public:
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;	
	char*					m_pNetworkName;
	RecvTable*				m_pRecvTable;
	ClientClass*			m_pNext;
	int						m_ClassID;

public:
	const char* GetName();
	int GetClassID();
};
