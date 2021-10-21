#pragma once
#include "GActivity.h"

class CGTaskAchievement : public CGoalComposite
{
public:
	CGTaskAchievement();
	virtual ~CGTaskAchievement();	
	int  Process();

	void ShowTaskAchievementWnd();
	BOOL IsTaskAchievementWnd();
	BOOL IsNotActiveRedot();
	BOOL IsOverTime();
	int LoopNextSleep(int delay = 1000);
	BOOL IsFinished();

	int m_iTimeCount;
	BOOL m_bFinished;
};

