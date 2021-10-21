#pragma once
#include "GActivity.h"

class CGNVAn : public CGActivity
{
public:
	CGNVAn();
	virtual ~CGNVAn();
	int  Process();

	void processMain();
	void processActivity();
	BOOL isNewGuilde();
	UINT m_uActivity;
	BOOL m_bSub;
	int	m_iDelay;

	int m_iWaitForFinished;
	int m_iRoleStand;
	BOOL m_bFinished;
	CStdStringU czContentTemp;
};

