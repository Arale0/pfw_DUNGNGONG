#pragma once
#include "GActivity.h"

class CGChienTuBang : public CGActivity
{
public:
	CGChienTuBang();
	virtual ~CGChienTuBang();
	int  Process();

	void GoBackGuildScene();
	BOOL IsGuildScene();
	BOOL IsInFb();
	BOOL IsNPCDialog();
	BOOL IsGuildMap();
	void HuoDongLimitWnd();
	void ProcessGuildScene();
	void processAlone();


	int m_iDelayClick;
	BOOL m_bGoGuild	;
	BOOL m_bFinished;
	BOOL m_bShowMap;
	int m_iClickedNPC;
	BOOL m_bJiebai;
	BOOL m_bCheckCountTime;
	BOOL m_bTeamAlone;
};

