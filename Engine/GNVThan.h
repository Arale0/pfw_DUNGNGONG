#pragma once
#include "GActivity.h"

class CGNVThan : public CGActivity
{
public:
	CGNVThan();
	virtual ~CGNVThan();
	int  Process();

	void processMain();
	void processActivity();
	BOOL isNewGuilde();
	BOOL IsAnswer();
	BOOL IsChooseLogic();
	UINT m_uActivity;
	int	m_iDelay;
	BOOL m_bSub;

	int m_iWaitForFinished;
	int m_iRoleStand;
	BOOL m_bFinished;
	CStdStringU czContentTemp;
};

