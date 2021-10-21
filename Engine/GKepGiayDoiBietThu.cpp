#include "main.h"
#include "GKepGiayDoiBietThu.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"
#include "GTaskCleanBag.h"

CGKepGiayDoiBietThu::CGKepGiayDoiBietThu() :CGActivity()
{
	LOG_WRITE("NEW - CGKepGiayDoiBietThu()");
	m_activity = act_kepgiaydoibietthu;
	m_bFinished = FALSE;
	m_bClickHuoDong = FALSE;
	m_uActivity = 0;
	m_iDelayClicked = 0;
	m_pActivity = NULL;
	m_iTemp = -1;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGKepGiayDoiBietThu::~CGKepGiayDoiBietThu()
{
	LOG_WRITE("DEL - CGKepGiayDoiBietThu()");
}

int CGKepGiayDoiBietThu::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{	
		
		if (IsFinished()) return m_nStatus;

		//if (g_pGameControl->IsCenterNotice(u"Nhiệm vụ đã đầy")) {m_bFinished = TRUE; return m_nStatus;}
		
		if (g_pGameControl->IsMoving()) {m_iTemp = 1; m_iDelayClicked = 0; return LoopNextSleep();}
		
		if (g_pGameControl->IsPickUpBtn()) {m_iTemp = 1; m_iDelayClicked = 0; return LoopNextSleep();}

		if (g_pGameControl->IsStoryUIRoot()) {m_iTemp = 1; m_iDelayClicked = 0; return LoopNextSleep();}

		if (g_pGameControl->IsMessageBox(u"mời bạn vào đội,", OFF)) return LoopNextSleep();

		if (g_pGameControl->IsButtonExitFuben()) {
			m_iTemp = 1;
			m_uActivity = 0;
			g_pGameControl->SwitchAutoFight(ON);
			return LoopNextSleep();
		}


		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();

		Other();
		
		g_pGameControl->CloseDialog();

		LOG_WRITE("CGKepGiayDoiBietThu::Process()....");
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGKepGiayDoiBietThu::ClickButtonHuodong()
{
	LOG_WRITE("m_iDelayClicked = %d", m_iDelayClicked);
	if (m_bClickHuoDong) {
		if (m_iDelayClicked >= 9) {
			m_iDelayClicked = 0;
			m_bClickHuoDong = FALSE;
		}
		m_iDelayClicked ++;
		LoopNextSleep();
		return;
	}
	m_bClickHuoDong = TRUE;
	g_pGameControl->ClickButtonHuDong();
	LoopNextSleep();
}

int CGKepGiayDoiBietThu::ProcessActivity()
{
	m_iDelayClicked = 0;
	CUE_Transform *pActivity = (CUE_Transform *)m_uActivity;
	if (!pActivity || !g_pGameControl->IsShowTransform(pActivity)) {
		LOG_WRITE("No m_pActivity");
		return m_nStatus;
	}

	if (g_pGameControl->IsMoving()) return LoopNextSleep(1000);
	g_pGameControl->MissionClicked(pActivity);

	return LoopNextSleep(1000);
}

BOOL CGKepGiayDoiBietThu::IsFinished()
{
	if (m_bFinished) {
	
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return FinishedActivity();
		return TRUE;
	}

	//if (g_pGameControl->IsLowerLevel(25)) { m_bFinished = TRUE; return TRUE;}

	return FALSE;
}

void CGKepGiayDoiBietThu::Activate()
{
	m_nStatus = ACTIVE;
	m_dwStartTime = (DWORD)g_pUEThread->GetTickCount();
	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
}


void CGKepGiayDoiBietThu::Other()
{
	

	if (g_pGameControl->checkCanJoinActivity(m_activity, m_bFinished)) {
		LoopNextSleep();
		return;
	}

	LOG_WRITE("Yes.............%d", m_iTemp);
	
	if (m_iTemp <= 0) CActivityHuoDongWindow::OnClickGoActivityBtnByActivityId(2010, 0);

	if (m_iTemp >= 3) m_iTemp = -1;

	m_iTemp ++;
	LoopNextSleep();
}



