#pragma once
#include "GActivity.h"

class CGTaskCDTuChan : public CGoalComposite
{
public:
	CGTaskCDTuChan();
	virtual ~CGTaskCDTuChan();	
	int  Process();

	int LoopNextSleep(int delay = 1000);
	BOOL IsFinished();
	void ShowImmotalityWnd();
	BOOL IsImmortalityWnd();

	BOOL m_bFinished;
	int m_iDelayClicked;

};

