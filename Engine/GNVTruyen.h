#pragma once
#include "GActivity.h"

class CGNVTruyen : public CGActivity
{
public:
	CGNVTruyen();
	virtual ~CGNVTruyen();
	int  Process();

	void processMain();
	void processActivity();
	BOOL isNewGuilde();
	UINT m_uActivity;
	int	m_iDelay;
	BOOL m_bSub;

	int m_iWaitForFinished;
	int m_iRoleStand;
	BOOL m_bFinished;
	CStdStringU czContentTemp;
};

