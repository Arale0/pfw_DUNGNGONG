#pragma once
#include "GActivity.h"

class CGNVPhu : public CGActivity
{
public:
	CGNVPhu();
	virtual ~CGNVPhu();
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

