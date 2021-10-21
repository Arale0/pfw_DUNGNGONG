#pragma once
#include <Main/Il2cpp.h>


class CIl2cppEx : public CIl2cpp
{
public:	
	CIl2cppEx(void);
	~CIl2cppEx(void);

public:
	void CreateEx();
	
	CField*		GetField(LPCSTR image,LPCSTR space,LPCSTR klass,LPCSTR field);
	CMethod*	GetMethod(LPCSTR image,LPCSTR space,LPCSTR klass,LPCSTR func,int paramcount = -1);
	CMethod*	FindMethod(LPCSTR image,LPCSTR space,LPCSTR klass,LPCSTR func);

	CSYS_Type*	GetSystemTypeCSharp(LPCSTR name);
	CSYS_Type* GetSysType(LPCSTR imagename,LPCSTR spacename,LPCSTR classname);
};
