#pragma once
#include "../../__AIGGlobal/Androids/src/AI2/GoalComposite.h"
#include "GameInfo.h"

class CGActivity : public CGoalComposite
{
public:
	CGActivity();
	virtual ~CGActivity (void);
	ActivityId m_activity;
	void Activate();
	int  Process();
	int  FinishedActivity();
	int  LoopNextSleep(int delay = 1000);
	int	 LoopNext();
	
	DWORD GetAliveTime();
	BOOL  IsTimeOver();

public:
	DWORD		m_dwStartTime;	
	DWORD		m_dwDelay;
	DWORD		m_dwTimeOver;
	CGameInfo*	m_pGame;
	
};
