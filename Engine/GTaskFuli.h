#pragma once
#include "GActivity.h"

class CGTaskFuli : public CGoalComposite
{
public:
	CGTaskFuli();
	virtual ~CGTaskFuli();	
	int  Process();
	void ShowFuliWnd();
	BOOL IsFuliWnd();
	BOOL IsRedDot();
	BOOL IsUIWelfareQianDao();
	BOOL IsUIWelfare_KGDJ();
	BOOL IsUIStartWorkGiftController();
	BOOL IsDzaixian_daily();
	BOOL IsShengji();
	BOOL IsUIWelfareKaiFu();
	BOOL IsNotActiveRedot();
	BOOL IsOverTime();
	BOOL IsButtonReceived();
	int LoopNextSleep(int delay = 1000);
	BOOL IsFinished();
	void ExitFuben();
	BOOL IsChangeWnd();
	BOOL IsNumericKeyBoard();
	BOOL IsUIScrollExchangeController();

	int m_iTimeCount;
	BOOL m_bFinished;


};

