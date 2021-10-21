#include "main.h"
#include "GThuongThienPhatAc.h"
#include "GTaskKetBai.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"
#include "GTaskCleanBag.h"
#include "GTeamAlone.h"

CGThuongThienPhatAc::CGThuongThienPhatAc() :CGActivity()
{
	LOG_WRITE("NEW - CGThuongThienPhatAc()");
	m_activity				= act_thuongthienphatac;
	m_uActivity				= 0;
	m_iDelayClickedActivity	= 0;
	m_bFinished				= FALSE;
	m_bJiebai				= FALSE;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGThuongThienPhatAc::~CGThuongThienPhatAc()
{
	LOG_WRITE("DEL - CGThuongThienPhatAc()");
}

int CGThuongThienPhatAc::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		if (m_bFinished) {
			if (g_pGameControl->IsMember()) {LOG_WRITE("FollowLeader....................OFF");g_pGameControl->FollowLeader(OFF);}
			if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
			if (g_pGameControl->exitTeamIfAloneTeamSet()) return TRUE;
			else return FinishedActivity();
			return TRUE;
		}

		if (g_pGameControl->ProcessMessageBox(u"1 số thành viên cự ly", MSG_OK)) return LoopNextSleep();
		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();
		if (g_pGameControl->IsCopySceneReady()) return LoopNextSleep();
		if (g_pGameControl->IsMoving()) return LoopNextSleep();

		if (IsFinished()) return m_nStatus;

		if (g_pGameControl->IsButtonExitFuben()) {
			m_iDelayClickedActivity = 1;
			g_pGameControl->SwitchAutoFight(ON);
			OnOffSettingWnd();
			return LoopNextSleep();
		}

		if (IsNPCDialog()) return LoopNextSleep();

		if (g_pGameControl->checkCanJoinActivity(m_activity, m_bFinished)) return LoopNextSleep();

		processAlone();
		processMember();
		processLeader();
		return m_nStatus;
	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGThuongThienPhatAc::ShowActivityWnd()
{

	////la doi truong
	//if (!m_bClickButtonHuoDong) {
	//	m_bClickButtonHuoDong = TRUE;
	//	g_pGameControl->ClickButtonHuDong();
	//	return;
	//}

	//DelayClickButtonHuoDong();

	//g_pGameControl->CloseDialog();
}

void CGThuongThienPhatAc::DelayClickButtonHuoDong()
{
	/*if (m_iDelayClicked >= 9) m_bClickButtonHuoDong = FALSE;
	if (g_pGameControl->IsShowPopUI()) m_iDelayClicked = 0;
	m_iDelayClicked ++;
	LOG_WRITE("Wait for clicked huoDong %d", m_iDelayClicked);
	LoopNextSleep();*/
}

BOOL CGThuongThienPhatAc::IsNPCDialog()
{
	CDialogController *pIns = CDialogController::Instance();
	if (pIns) {
		m_iDelayClickedActivity = 1;
		int iDialog = CDialogController::get_DialogID();
		if (iDialog == 136) {
			pIns->OnOpt_1();
			pIns->AidButtonClick();
			return TRUE;
		}

		pIns->AidButtonClick();
		//LOG_WRITE("iDialog == %d", iDialog); //136
		return TRUE;
	}
	return FALSE;
}	

BOOL CGThuongThienPhatAc::IsFinished()
{

	if (g_pGameControl->IsLowerLevel(30)) {
		LOG_WRITE("Lower level 30");
		m_bFinished = TRUE; 
		return TRUE;
	}

	CMessageBoxController *pMsg = CMessageBoxController::Instance();
	if(!pMsg) return FALSE;
	CStdStringU czMsgText = pMsg->getText();
	if(czMsgText.Find(u"Hôm nay đã hoàn thành") >=0){
		LOG_WRITE("Hom nay da het luot");
		m_bFinished = TRUE;
		pMsg->MessageBoxCancel();
		return TRUE;	
	}

	return FALSE;
}

void CGThuongThienPhatAc::Activate()
{
	m_nStatus = ACTIVE;

	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
}

void CGThuongThienPhatAc::processMember()
{
	if (g_pGameControl->IsMember()) {
		if (g_pGameControl->ProcessMessageBox(u"mời theo sau", MSG_OK)) return ;
		LoopNextSleep();
		return;
	}
}

void CGThuongThienPhatAc::processLeader()
{
	if (!m_bJiebai && g_pGameControl->IsTeamLeader()) {
		m_bJiebai = TRUE;
		AddSubGoal(new CGTaskKetBai());
		return;
	}
	
	if (g_pGameControl->IsTeamLeader()) get_activity();

	LoopNextSleep();
}

void CGThuongThienPhatAc::get_activity()
{
	
	LOG_WRITE("Yes.............%d", m_iDelayClickedActivity);

	if (m_iDelayClickedActivity <= 0) CActivityHuoDongWindow::OnClickGoActivityBtnByActivityId(2004, 0);

	if (m_iDelayClickedActivity >= 3) m_iDelayClickedActivity = -1;

	m_iDelayClickedActivity ++;
	LoopNextSleep();
}

void CGThuongThienPhatAc::processAlone()
{
	static BOOL bTeamAlone = FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_ALONE) {

		if (g_pGameControl->IsMember()) bTeamAlone = TRUE;
		if (!bTeamAlone) {
			bTeamAlone = TRUE;
			AddSubGoal(new CGTeamAlone());
		}	
		if (!g_pGameControl->IsHasTeam()) bTeamAlone = FALSE;

		if (g_pGameControl->IsTeamLeader()) bTeamAlone = FALSE;

		g_pGameControl->FollowLeader(ON);
		return;
	}

	if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_ALONE) bTeamAlone = FALSE;
}

void CGThuongThienPhatAc::OnOffSettingWnd()
{
	g_pGameControl->OnOffSettingWnd();
}




