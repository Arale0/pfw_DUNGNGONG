#pragma once
#include <map>

class CSYS_Type;
class CSYS_Assembly;

class CSysTypes
{
public:
	CSysTypes(LPCSTR image);
	~CSysTypes(void);
	void			Add(LPCSTR name);
	CSYS_Type*		Get(LPCSTR name);
protected:
	CSYS_Assembly*	m_sysAssembly;
	
	std::map<std::string,CSYS_Type *>	m_mapSysType;

};
