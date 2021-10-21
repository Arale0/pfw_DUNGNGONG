#include "main.h"
#include "GActivity.h"
#include "GSleep.h"

CGActivity::CGActivity()
{
	m_dwStartTime = 0;
	m_dwDelay = 1000;
	m_dwTimeOver = 0;
	m_pGame = g_pGame;
}


CGActivity::~CGActivity(void)
{
	//LOG_WRITE("DEL - CGActivity()");
	/*
	if(m_activity != act_LAST){
		if(m_pGame->GetStatusByActivity(m_activity) == ast_doing)
			m_pGame->SetStatusByActivity(m_activity, ast_donot);
	}
	*/
	m_pGame->m_iCurrentID = -1;
}

void CGActivity::Activate()
{
	CGoalComposite::Activate();	
	/*
	if(m_activity != act_LAST)
			m_pGame->SetStatusByActivity(m_activity, ast_doing);
	m_dwStartTime = GetTickCount();
	*/
}
int CGActivity::FinishedActivity()
{
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_done);
	//if(m_activity != act_LAST)
	//	m_pGame->SetStatusByActivity(m_activity, ast_done);
	return Finished();
}

int CGActivity::LoopNextSleep(int delay)
{
	//_theApp->NextTimer(delay);
	AddSubGoal(new CGSleep(delay));
	return LoopNext();
}

int CGActivity::LoopNext()
{
	m_nStatus = ACTIVE; 
	return m_nStatus;
}
DWORD CGActivity::GetAliveTime()
{
	DWORD dwCurTime = _GetTickCount();
	return dwCurTime - m_dwStartTime;
}
BOOL CGActivity::IsTimeOver()
{
	return (m_dwStartTime > 0)&& (m_dwTimeOver > 0) && (GetAliveTime() > m_dwTimeOver);
		
}

int CGActivity::Process()
{
	/*
	if(m_activity!= act_LAST)
	{
		if(!m_pGame->GetCheckByActivity(m_activity) || 
			m_pGame->GetStatusByActivity(m_activity) != ast_doing)
		{
			return Finished();
		}
	}
	*/
	int nSubGoalStatus = ProcessSubGoals();

	/*if(nSubGoalStatus == COMPLETED)
	{
		LOGA_DEBUG("..");
	}*/

	return m_nStatus;
}
