#pragma once

class RecvProp;

class RecvTable
{
public:
	typedef RecvProp	PropType;

	int			GetNumProps()
	{
		return m_nProps;
	}

	RecvProp* GetProp(int i)
	{
		return &(*m_pProps)[i];
	}

	const char* GetName()
	{
		return m_pNetTableName;
	}

public:
	char					_unk0x0000[0x8];
	RecvProp**				m_pProps;
	int						m_nProps;
	char					_unk0x0014[0x10C];		
	void*					m_pDecoder;				
	char*					m_pNetTableName;		
	bool					m_bInitialized;			
	bool					m_bInMainList;			
};
