#pragma once
#include "GoalSystem.h"
//#include "TriggerTimer.h"
#include "TriggerActivity.h"

class CAutoAI
{
public:
	CGameInfo*			m_pGame;
	CTriggerActivity	m_TriggerActivity;
	BOOL				m_bControl;


	CGoalSystem*	GetGoalSystem();
	void			Update();
	BOOL			IsGameControlUnchecked();
	BOOL			IsEmpty();
	
public:
	CAutoAI(void);
	~CAutoAI(void);

};
