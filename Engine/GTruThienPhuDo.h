#pragma once
#include "GActivity.h"

class CGTruThienPhuDo : public CGActivity
{
public:
	CGTruThienPhuDo();
	virtual ~CGTruThienPhuDo();
	int  Process();
	void Activate();
	void ShowTowerWnd();
	BOOL IsTowerWnd();
	BOOL IsInFb();
	BOOL IsResultWnd();
	BOOL IsFinished();
	BOOL IsTowerResult();
	BOOL m_bFinished;
	BOOL m_bSweep;
	BOOL m_bShowTowerWnd;
	int m_iDelay;
};

