#pragma once
#include "GActivity.h"

class CGTeamAlone : public CGoalComposite
{
public:
	CGTeamAlone();
	virtual ~CGTeamAlone();	
	int  Process();


	BOOL IsChatController();
	BOOL IsTeamWnd();
	int initTeam();
	int LoopNextSleep(int delay = 1000);
	void ShowChatController();
	void get_CurrentActivityName();
	void OnClickLink(CUE_Transform *pList, int iChild);

	BOOL m_bFinished;
	int m_iDelayClicked;
	int m_iChildFormList;
	int m_iLoopNext;
	CStdStringU m_czActiviyName;

};

