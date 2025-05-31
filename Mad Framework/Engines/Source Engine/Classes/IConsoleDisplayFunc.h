#pragma once

class IConsoleDisplayFunc
{
public:
	virtual void ColorPrint(const Color & clr, const char* pMessage) = 0;
	virtual void Print(const char* pMessage) = 0;
	virtual void DPrint(const char* pMessage) = 0;
};