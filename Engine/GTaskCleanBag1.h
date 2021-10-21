#pragma once
#include "GActivity.h"

class CGTaskCleanBag1 : public CGoalComposite
{
public:
	CGTaskCleanBag1();
	virtual ~CGTaskCleanBag1();	
	int  Process();

	void ShowTaskCleanBagWnd();
	BOOL IsTaskCleanBagWnd();
	int LoopNextSleep(int delay = 1000);
	BOOL IsFinished();
	BOOL IsItemTips();
	BOOL GopTrangBi();
	BOOL IsCopyFinishedFubenWnd();
	BOOL IsMilitaryWnd();

	void SelectOtherTab(CKnapsackWindow *pIns);
	void ProcessCleanBag(CKnapsackWindow *pIns);

	BOOL m_bFinished;
	int m_iTypeCleanBag;

	int m_iCurrentIndex;
};

