#pragma once
#include "GActivity.h"

class CGTaskKetBai : public CGoalComposite
{
public:
	CGTaskKetBai();
	virtual ~CGTaskKetBai();	
	int  Process();
	
	void ShowFriendWnd();
	int LoopNextSleep(int delay = 1000);
	BOOL IsFriendWnd();
	int get_haveTeamCount();
	int get_JiebaiTeamCount();
	BOOL IsFinished();
	void InviteBrotherhoodMember();

	void init_NumberOfJiebai();

	BOOL m_bFinished;
	int m_iBrotherhoodCount;
	int m_iDelayInvite;

};

