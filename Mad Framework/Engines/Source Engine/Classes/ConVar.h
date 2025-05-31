#pragma once

typedef void (*FnChangeCallback_t)(IConVar* var, const char* pOldValue, float flOldValue);

class ConVar : public ConCommandBase, public IConVar
{
	friend class CCvar;
	friend class ConVarRef;

public:
	typedef ConCommandBase BaseClass;

	ConVar(const char* pName, const char* pDefaultValue, int flags = 0);

	ConVar(const char* pName, const char* pDefaultValue, int flags,
		const char* pHelpString);
	ConVar(const char* pName, const char* pDefaultValue, int flags,
		const char* pHelpString, bool bMin, float fMin, bool bMax, float fMax);
	ConVar(const char* pName, const char* pDefaultValue, int flags,
		const char* pHelpString, FnChangeCallback_t callback);
	ConVar(const char* pName, const char* pDefaultValue, int flags,
		const char* pHelpString, bool bMin, float fMin, bool bMax, float fMax,
		FnChangeCallback_t callback);

	virtual						~ConVar(void);
	virtual bool				IsFlagSet(int flag) const;
	virtual const char*			GetHelpText(void) const;
	virtual bool				IsRegistered(void) const;
	virtual const char*			GetName(void) const;
	virtual void				AddFlags(int flags);
	virtual	bool				IsCommand(void) const;
	//void InstallChangeCallback(FnChangeCallback_t callback);
	//float			GetFloat(void) const;
	//int			GetInt(void) const;
	//bool			GetBool() const { return !!GetInt(); }
	//char const* GetString(void) const;
	virtual void				SetValue(const char* value);
	virtual void				SetValue(float value);
	virtual void				SetValue(int value);
	//void						Revert(void);
	//bool						GetMin(float& minVal) const;
	//bool						GetMax(float& maxVal) const;
	//const char* GetDefault(void) const;

public:
	virtual void				InternalSetValue(const char* value);
	virtual void				InternalSetFloatValue(float fNewValue);
	virtual void				InternalSetIntValue(int nValue);
	virtual bool				ClampValue(float& value);
	virtual void				ChangeStringValue(const char* tempVal, float flOldValue);
	virtual void				Create(const char* pName, const char* pDefaultValue, int flags = 0,
		const char* pHelpString = 0, bool bMin = false, float fMin = 0.0,
		bool bMax = false, float fMax = false, FnChangeCallback_t callback = 0);
	virtual void				Init();

public:
	const char* m_pszDefaultValue;
	ConVar* m_pParent;
	char* m_pszString;
	int							m_StringLength;
	float						m_fValue;
	int							m_nValue;
	bool						m_bHasMin;
	float						m_fMinVal;
	bool						m_bHasMax;
	float						m_fMaxVal;
	FnChangeCallback_t			m_fnChangeCallback;
};
