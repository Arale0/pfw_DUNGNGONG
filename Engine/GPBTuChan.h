#pragma once
#include "GActivity.h"

class CGPBTuChan : public CGActivity
{
public:
	CGPBTuChan();
	virtual ~CGPBTuChan();
	int  Process();

	void ShowActivityWnd();
	void processFb();
	void MoveToPos(int x, int y);
	void DelayClick();
	BOOL IsNPCDialog();
	BOOL IsFinished();
	BOOL IsInFb();
	void ShowTeamWnd();
	void processOutside();
	BOOL IsTeamWnd();
	BOOL IsPickUpBtn();
	BOOL IsCopyFinishedFubenWnd();
	BOOL IsShowMap();
	BOOL IsMonsterTarget();
	int get_CountNPC();
	BOOL IsInMaple();
	void initEmulatorSize();
	int convertYPointWithEmulatorSize(int y);
	int convertXPointWithEmulatorSize(int x);
	
	BOOL IsShowTargetBar();
	void MoveToTarget(int scene);
	void CheckTarget(CObj_MainPlayer *pPlayer, CUE_Transform *p);
	void processAlone();
	void GotoDoor();
	void CloseDialog();

	BOOL m_bFinished;
	BOOL m_bShowWnd;
	BOOL m_bJiebai;
	BOOL m_bCountTime;
	BOOL m_bShowMap;
	int m_iDelayClicked;
	int m_iCountTime;
	int m_iShowMap;
	int m_iMoveToPos;
	BOOL m_bTeamAlone;
	BOOL m_bTransDoor;
	int m_screenHeight;
	int m_screenWidth;
	int m_iCloseMap;
	BOOL m_bGone;
	BOOL m_bHBV;
	int m_iCountNPC;
};

