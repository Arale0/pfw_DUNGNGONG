#pragma once
#include "GActivity.h"

class CGTaskGetMail : public CGoalComposite
{
public:
	CGTaskGetMail();
	virtual ~CGTaskGetMail();	
	int  Process();
	BOOL IsMailWnd();
	void ShowMailWnd();
	BOOL IsNewMail();

	int LoopNextSleep(int delay = 1000);
	int m_iTimeCount;
	BOOL m_bFinished;
	BOOL m_bDeleteAllMailFirst;


};

