#include "main.h"
#include "SYS_UInt64.h"

CSYS_UInt64::CSYS_UInt64(void){
}

CSYS_UInt64::~CSYS_UInt64(void){

}



int CSYS_UInt64::GetHashCode()
{	
	return (int)m_value ^ (int)(m_value >> 32);
	//return (LONGLONG)(m_value);
}

BOOL CSYS_UInt64::Equals(CSYS_UInt64 *pObj){

	return (BOOL)(m_value == (ULONGLONG)pObj);
}
/*
CSYS_UInt64 * CSYS_UInt64::Parse(LPCWSTR str)
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->FindMethod("mscorlib", "System", "Int64", "Parse(System.String)");
	if (!pfn) return NULL;
	CSYS_String *pStr = CSYS_String::_CreateString(str);
	void *agrs[] = {pStr};
	return (CSYS_UInt64*)pfn->Invoke(NULL,agrs);
}
*/
CSYS_UInt64 * CSYS_UInt64::CreateObject(ULONGLONG value)
{
	static CMethod* pfn = NULL;
	CClass* pKlass = g_pMono->FindClass("mscorlib", "System", "UInt64");
	if (!pKlass) return NULL;
	CSYS_UInt64 *pInt64 = (CSYS_UInt64 *)pKlass->NewObject();
	pInt64->m_value = value;
	return pInt64;
}
