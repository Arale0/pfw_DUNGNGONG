#pragma once
#include "GActivity.h"

class CGThoSanTienThuong : public CGActivity
{
public:
	CGThoSanTienThuong();
	virtual ~CGThoSanTienThuong();
	int  Process();
	BOOL IsBountyMain();
	BOOL IsLeaderAutoFight();
	
	
	void ShowBountyMain();
	void processMember();
	void processLeader();
	void initNameBoss();
	void CloseDialogIfShow();

	CStdStringU m_czBossName;
	int m_iDelayClicked;
	BOOL m_bJiebai;
	BOOL m_bShowBountyMain;
};

