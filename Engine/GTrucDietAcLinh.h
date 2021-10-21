#pragma once
#include "GActivity.h"
#define YL_HOUR	0
#define YL_MINUTE	1

class CGTrucDietAcLinh : public CGActivity
{
public:
	CGTrucDietAcLinh();
	virtual ~CGTrucDietAcLinh();
	int  Process();
	void processTeam();
	void UpdateNPC1(BOOL bShowed);
	void initEmulatorSize();
	void newMethod();
	void get_NameLeader();
	void checkSetTimeOnUI();
	void TeleportOnTime(BOOL bOnTime = TRUE);

	BOOL IsInMaple();
	BOOL IsNPCDialog();
	BOOL IsResultWnd();
	BOOL IsNotBannedArea(int x, int y);
	BOOL IsEspecialPoint(int x, int y, int xPlayer = 0, int yPlayer = 0);
	BOOL IsLeaderAutoFight();

	int convertXPointWithEmulatorSize(int x);
	int convertYPointWithEmulatorSize(int y);
	int getTime(int iTypeTime = YL_HOUR);
	void CloseDialog();
	
	void processAlone();
	
	void ChangeLine();

	void CloseBountyMain();
	void CloseDomainXuanZhanMap();
	
	CStdStringU m_czNameMap;
	BOOL m_bFinished;
	BOOL m_bJiebai;
	BOOL m_bRightMap;
	int m_CurrentPosX;
	int m_CurrentPosY;
	int m_screenWidth;
	int m_screenHeight;
	BOOL m_bOpenFight1;

	BOOL m_bNotFoundNPC;
	BOOL m_bRightNPC;
	BOOL m_bOverTime;
	int m_iCloseMap;

	CStdStringU m_czLeaderName;

	BOOL m_bChangeLine;
	BOOL m_bChangeLineIfFull;
	CStdStringU m_czLine;
};
