#include "main.h"
#include "SysTypes.h"

CSysTypes::CSysTypes(LPCSTR image)
{	
	m_sysAssembly = CSYS_Assembly::Load(image);	
	//LOG_WRITE("NEW - CSysTypes() [%p] (%s)",m_sysAssembly,image);
}

CSysTypes::~CSysTypes(void)
{
	m_mapSysType.clear();
	//LOG_WRITE("DEL - CSysTypes()");
}

void CSysTypes::Add( LPCSTR name )
{
	if (!m_sysAssembly) return;
	CSYS_Type* p = m_sysAssembly->GetType(name);
	
	if (!p){
		LOG_WRITE("===> CSysTypes::Add(%s)\t : [%p]",name,p);	
		return;
	}
	m_mapSysType[name] = p;	
}

CSYS_Type* CSysTypes::Get( LPCSTR name )
{
	return m_mapSysType[name];
}
