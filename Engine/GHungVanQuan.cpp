#include "main.h"
#include "GHungVanQuan.h"

CGHungVanQuan::CGHungVanQuan() :CGActivity()
{
	LOG_WRITE("NEW - CGHungVanQuan()");
	m_activity = act_hungvanquan;
	m_bFinished = FALSE;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGHungVanQuan::~CGHungVanQuan()
{
	LOG_WRITE("DEL - CGHungVanQuan()");
}

int CGHungVanQuan::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGHungVanQuan::Process()....");
		
		if (m_bFinished) return FinishedActivity();

		if (IsResult()) return LoopNextSleep();

		if (IsGuildScene()) return LoopNextSleep();

		BackGuildScene();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGHungVanQuan::IsGuildScene()
{
	if (g_pGameControl->IsMap("Cứ Địa Bang")) {
		if (g_pGameControl->IsMember() && g_pGameControl->IsFollowLeader()) {
			g_pGameControl->FollowLeader(OFF);
			return TRUE;
		}

		g_pGameControl->SwitchAutoFight(ON);
		return TRUE;
	}
	return FALSE;
}

void CGHungVanQuan::BackGuildScene()
{
	LOG_WRITE("Back Guild Scene.........");
	CActivityHuoDongWindow::OnClickGoActivityBtnByActivityId(2012, 0);
	LoopNextSleep();
}

BOOL CGHungVanQuan::IsResult()
{
	CGuildBanghuaResultController *pIns = CGuildBanghuaResultController::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("Close");
	m_bFinished = TRUE;
	CGuildBanghuaResultController::CloseWindow();
	return TRUE;
}



