#include "main.h"
#include "GPhuongMinhCoc.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"
#include "GTaskCleanBag.h"
#include "GTaskKetBai.h"
#include "GTeamAlone.h"


CGPhuongMinhCoc::CGPhuongMinhCoc() :CGActivity()
{
	LOG_WRITE("NEW - CGPhuongMinhCoc()");
	m_activity = act_phuongminhcoc;
	m_bFinished = FALSE;
	m_bClickButtonHuoDong = FALSE;
	m_iDelayClicked = 0;
	m_bJiebai = FALSE;
	m_bTeamAlone = FALSE;
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGPhuongMinhCoc::~CGPhuongMinhCoc()
{
	LOG_WRITE("DEL - CGPhuongMinhCoc()");
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
}

int CGPhuongMinhCoc::Process()
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

		if (IsLowerLevel()) return LoopNextSleep();

		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();

		if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep(500);

		//if (g_pGameControl->IsCopyFinishedFubenWnd()) {m_bFinished = TRUE;return LoopNextSleep();}

		if (g_pGameControl->IsMap(u"Phượng Minh Cốc")) {/*g_pGameControl->IsButtonExitFuben()*/
			//CheckCleanBag();
			m_iDelayClicked = 0;
			g_pGameControl->SwitchAutoFight(ON);
			g_pGameControl->OnOffSettingWnd();
			return LoopNextSleep(500);
		}

		ProcessTeam();
		LOG_WRITE("CGPhuongMinhCoc::Process()....");
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGPhuongMinhCoc::Activate()
{
	m_nStatus = ACTIVE;

	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
}

int CGPhuongMinhCoc::ProcessTeam()
{

	if (g_pGameControl->ProcessMessageBox(u"Tổ đội trên 3 người", MSG_CANCEL)) {m_bJiebai = FALSE; return LoopNextSleep();}

	if (IsCopySceneReady(FALSE)) return LoopNextSleep();

	if (g_pGameControl->IsActivity(u"9", m_bFinished)) return LoopNextSleep();

	if (g_pGameControl->checkCanJoinActivity(m_activity, m_bFinished)) return LoopNextSleep();

	if (g_pGameControl->IsTeamAloneSet()) {
		processAlone();
		return LoopNextSleep();
	}

	if (g_pGameControl->IsMember()) LoopNextSleep();

	if (g_pGameControl->IsTeamLeader()) {
		if (g_pGameControl->IsLeaderSet() && !m_bJiebai) {
			m_bJiebai = TRUE;
			AddSubGoal(new CGTaskKetBai());
			return LoopNextSleep();
		}
		if (g_pGameControl->IsNotEnoughMembers()) return LoopNextSleep();
		ShowAcitivyWnd();
		return LoopNextSleep();
	}

	return m_nStatus;
}

BOOL CGPhuongMinhCoc::IsCopySceneReady(BOOL bIsMember)
{
	CCopySceneReady *pIns = CCopySceneReady::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("CGPhuongMinhCoc::IsCopySceneReady()......Confirm");
	if (g_pGameControl->IsMember()) pIns->OnClickConfirm();
	LOG_WRITE("Enter scene.......");
	//if (bIsMember) 
	return TRUE;
}

BOOL CGPhuongMinhCoc::IsLowerLevel()
{
	CUICopySceneLowLevelTips *pIns = CUICopySceneLowLevelTips::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("CGPhuongMinhCoc::IsLowerLevel().................");
	pIns->OnConfirmBtnClick();
	return TRUE;
}

BOOL CGPhuongMinhCoc::IsFinished()
{
	if (m_bFinished) {
		//if (g_pGameControl->IsTeamLeader()) _theApp->m_pEpoll->Sync_ActivitySttByLeader();
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		if (g_pGameControl->exitTeamIfAloneTeamSet()) return TRUE;
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(15)) { m_bFinished = TRUE; return TRUE;}
	
	return FALSE;
}

void CGPhuongMinhCoc::DelayClickButtonHuoDong()
{
	if (m_iDelayClicked >= 9) m_bClickButtonHuoDong = FALSE;
	if (g_pGameControl->IsShowPopUI()) m_iDelayClicked = 0;
	if (g_pGameControl->IsButtonExitFuben()) m_iDelayClicked = 0;
	m_iDelayClicked ++;
	LOG_WRITE("Wait for clicked huoDong %d", m_iDelayClicked);
	LoopNextSleep();
}

void CGPhuongMinhCoc::ShowAcitivyWnd()
{
	DelayClickButtonHuoDong();
	//la doi truong
	if (!m_bClickButtonHuoDong) {
		m_bClickButtonHuoDong = TRUE;
		g_pGameControl->ClickButtonHuDong();
		LoopNextSleep();
	}

	g_pGameControl->CloseDialog();
}

void CGPhuongMinhCoc::CheckCleanBag()
{
	//DWORD dwTime = (DWORD)g_pUEThread->GetTickCount();
	//DWORD dwCleanTime = g_pGame->m_OptionTab.iDeMinute * 60000;
	//if (dwCleanTime <= 0) dwCleanTime = 120000;
	////LOG_WRITE("%d", dwTime - m_dwStartTime);
	//if (dwTime - m_dwStartTime >= dwCleanTime) {
	//	LOG_WRITE("Timeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
	//	m_dwStartTime = (DWORD)g_pUEThread->GetTickCount();
	//	AddSubGoal(new CGTaskCleanBag());
	//	return;
	//}
	//LoopNextSleep();
}

void CGPhuongMinhCoc::processAlone()
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
		return;
	}

	if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_ALONE) bTeamAlone = FALSE;
}



