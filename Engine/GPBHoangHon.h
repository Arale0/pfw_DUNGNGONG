#pragma once
#include "GActivity.h"

class CGPBHoangHon : public CGActivity
{
public:
	CGPBHoangHon();
	virtual ~CGPBHoangHon();
	int  Process();
	BOOL IsNPCDialog();
	BOOL IsFinished();
	BOOL IsInFb();
	void ShowTeamWnd();
	void processOutside();
	void processFb();
	void MoveToTarget();
	BOOL IsTeamWnd();
	BOOL IsPickUpBtn();
	BOOL IsCopyFinishedFubenWnd();
	BOOL IsInMaple();
	BOOL IsShowTargetBar();
	void processAlone();
	BOOL IsStoryUIRoot();
	void LookforTarget(CObj_MainPlayer *pPlayer, int xPos, int yPos, int zPos, BOOL bFirstTime = FALSE);
	BOOL CheckNearTeam();
	void CloseDialog();

	BOOL m_bFinished;
	BOOL m_bJiebai;
	BOOL m_bCountTime;
	BOOL m_bSkipCutScene;
	BOOL m_bS;


	int m_iDelayShowTeamWnd;
	int m_iCountTime;
	int m_iCloseMap;
};

