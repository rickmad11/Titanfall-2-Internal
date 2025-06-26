#pragma once

class ConCommandBase
{
	friend class CCvar;
	friend class ConVar;
	friend class ConCommand;
	friend void ConVar_Register(int nCVarFlag, void* pAccessor);
	friend void ConVar_PublishToVXConsole();
	friend class CDefaultCvar;

public:
	ConCommandBase(void);
	ConCommandBase(const char* pName, const char* pHelpString = 0,
		int flags = 0);
	virtual						~ConCommandBase(void);
	virtual	bool				IsCommand(void) const;
	virtual bool				IsFlagSet(int flag) const;
	virtual void				AddFlags(int flags);
	virtual void                RemoveFlags(int flags);
	virtual int                 GetFlags() const;
	virtual const char* GetName(void) const;
	virtual const char* GetHelpText(void) const;
	const ConCommandBase* GetNext(void) const;
	ConCommandBase* GetNext(void);
	virtual bool				IsRegistered(void) const;
	virtual int	GetDLLIdentifier() const;

protected:
	virtual void				Create(const char* pName, const char* pHelpString = 0,
		int flags = 0);
	virtual void				Init();
	void						Shutdown();
	char* CopyString(const char* from);

private:
	ConCommandBase* m_pNext;
	bool						m_bRegistered;
	const char* m_pszName;
	const char* m_pszHelpString;
	int							m_nFlags;

protected:
	static ConCommandBase* s_pConCommandBases;
	static void* s_pAccessor;
};
