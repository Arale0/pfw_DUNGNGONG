#pragma once
#include "GActivity.h"

class CGPhuongDeGian : public CGActivity
{
public:
	CGPhuongDeGian();
	virtual ~CGPhuongDeGian();
	int  Process();
	int ProcessTeam();
	void Activate();
	BOOL IsCopySceneReady(BOOL bIsMember = TRUE);
	BOOL IsLowerLevel();
	BOOL IsFinished();
	void DelayClickButtonHuoDong();
	void ShowAcitivyWnd();
	void CheckCleanBag();
	void processAlone();


	BOOL m_bFinished;
	BOOL m_bClickButtonHuoDong;
	int m_iDelayClicked;
	BOOL m_bJiebai;
	DWORD m_dwStartTime;
	BOOL m_bTeamAlone;
};

