#include "Il2cppEx.h"
#include "log.h"

CIl2cppEx::CIl2cppEx()
{
}

CIl2cppEx::~CIl2cppEx(void)
{
}

void CIl2cppEx::CreateEx()
{
	Create();

	//m_pSelf->thread_attach(m_pSelf->m_pDomain);//Quan trong => Runtime UNITY Invoke()
}

CField* CIl2cppEx::GetField( LPCSTR image,LPCSTR space,LPCSTR klass,LPCSTR field )
{
	CImage* pImage = GetImage(image);
	if (!pImage) return NULL;
	CClass* pKlass = pImage->FindClass(space,klass);
	if (!pKlass) return NULL;
	return pKlass->FindField(field);
}

CMethod* CIl2cppEx::GetMethod( LPCSTR image,LPCSTR space,LPCSTR klass,LPCSTR func,int paramcount /*= -1*/ )
{
	CImage* pImage = GetImage(image);
	if (!pImage) return NULL;
	CClass* pKlass = pImage->FindClass(space,klass);
	if (!pKlass) return NULL;
	return pKlass->GetMethod(func,paramcount);
}

CMethod* CIl2cppEx::FindMethod( LPCSTR image,LPCSTR space,LPCSTR klass,LPCSTR func )
{
	CImage* pImage = GetImage(image);
	if (!pImage) return NULL;
	CClass* pKlass = pImage->FindClass(space,klass);
	if (!pKlass) return NULL;
	return pKlass->FindMethod(func);
}

CSYS_Type* CIl2cppEx::GetSystemTypeCSharp( LPCSTR name )
{
	static CSYS_Assembly* sysAssembly = NULL;
	if (!sysAssembly) sysAssembly = CSYS_Assembly::Load(IMAGE_ASSEMBLY_CSHARP);
	if (!sysAssembly) return NULL;
	return sysAssembly->GetType(name);
}

CSYS_Type* CIl2cppEx::GetSysType( LPCSTR imagename,LPCSTR spacename,LPCSTR classname )
{
	CImage* pImg = GetImage(imagename);
	if(!pImg) return NULL;
	CVList<CSYS_MonoType*> lstTypeClass;
	pImg->EnumTypeClasses(&lstTypeClass);

	CStdStringU szClassName = _A2U(classname);
	CStdStringU szSpaceName = _A2U(spacename);

	CSYS_Type* p = NULL;
	CVList<CSYS_MonoType*>::iterator it;
	for (it = lstTypeClass.begin(); it != lstTypeClass.end();++it)
	{
		CSYS_MonoType* pType = *it;
		CStdStringU	szSpace = u"";
		if(pType->get_Namespace()) szSpace = pType->get_Namespace()->GetText();
		if(szSpace.Compare(szSpaceName) !=0) continue;
		CStdStringU	szClass = pType->get_Name()->GetText();
		if(szClass.Compare(szClassName) == 0){
			p = (CSYS_Type*)pType;
			break;
		}
	}
	lstTypeClass.clear();

	return p;
}

