#pragma once
#include "GameInfo.h"

class CActivitySetting
{
public:
	static CActivitySetting *GetInstance();
	void	InitActivity(CGameInfo* pGame);
	void	AddActivity(int iId, CString szName, CStringA szAlias, UINT uIDD = NULL, UINT uFuncId = MAXUINT);

private:
	static CActivitySetting *m_pActivitySetting;
	CActivitySetting(void) {}
	~CActivitySetting(void) {}
	ACTIVITYTAB* m_pActivityTab;
};
