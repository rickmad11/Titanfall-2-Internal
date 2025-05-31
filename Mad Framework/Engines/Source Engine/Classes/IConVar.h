#pragma once

class IConVar
{
public:
	virtual void SetValue(const char* pValue) = 0;
	virtual void SetValue(float flValue) = 0;
	virtual void SetValue(int nValue) = 0;
	virtual const char* GetName(void) const = 0;
	virtual bool IsFlagSet(int nFlag) const = 0;
};