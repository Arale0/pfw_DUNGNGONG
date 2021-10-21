#pragma once
#include "Il2cppEx.h"
#include "../../__AIGGlobal/Androids/inc/Main/SYS_Object.h"

class CSYS_UInt64:public CSYS_Object{
public:
	CSYS_UInt64(void);
	~CSYS_UInt64(void);
public:
	ULONGLONG	m_value;
	int		GetHashCode();
	BOOL Equals(CSYS_UInt64*pObj);
public:
	//static CSYS_UInt64 * Parse(LPCWSTR str);
	static CSYS_UInt64 *CreateObject(ULONGLONG value);

};
