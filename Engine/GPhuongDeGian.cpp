#include "main.h"
#include "GPhuongDeGian.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"
#include "GTaskCleanBag.h"
#include "GTaskKetBai.h"
#include "GTeamAlone.h"


CGPhuongDeGian::CGPhuongDeGian() :CGActivity()
{
	LOG_WRITE("NEW - CGPhuongDeGian()");
	m_activity = act_phuongdegian;
	m_bFinished = FALSE;
	m_bClickButtonHuoDong = FALSE;
	m_iDelayClicked = 0;
	m_bJiebai = FALSE;
	m_bTeamAlone = FALSE;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGPhuongDeGian::~CGPhuongDeGian()
{
	LOG_WRITE("DEL - CGPhuongDeGian()");
}

int CGPhuongDeGian::Process()
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

		//if (g_pGameControl->IsCopyFinishedFubenWnd()) {m_bFinished = TRUE; return LoopNextSleep();}

		if (g_pGameControl->IsButtonExitFuben()) {
			//CheckCleanBag();
			g_pGameControl->OnOffSettingWnd();
			m_iDelayClicked = 0;
			g_pGameControl->SwitchAutoFight(ON);
			return LoopNextSleep(500);
		}

		ProcessTeam();
		LOG_WRITE("CGPhuongDeGian::bActivityStatus.........");
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGPhuongDeGian::Activate()
{
	m_nStatus = ACTIVE;

	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
}

int CGPhuongDeGian::ProcessTeam()
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

BOOL CGPhuongDeGian::IsCopySceneReady(BOOL bIsMember)
{
	CCopySceneReady *pIns = CCopySceneReady::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("CGPhuongDeGian::IsCopySceneReady()......Confirm");
	if (bIsMember) pIns->OnClickConfirm();
	return TRUE;
}

BOOL CGPhuongDeGian::IsLowerLevel()
{
	CUICopySceneLowLevelTips *pIns = CUICopySceneLowLevelTips::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("CGPhuongDeGian::IsLowerLevel().................");
	pIns->OnConfirmBtnClick();
	return TRUE;
}

BOOL CGPhuongDeGian::IsFinished()
{
	if (m_bFinished) {
		/*if (g_pGameControl->IsTeamLeader()) {
			_theApp->m_pEpoll->Sync_ActivitySttByLeader();
			return FinishedActivity();
		}*/
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		if (g_pGameControl->exitTeamIfAloneTeamSet()) return TRUE;
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(15)) { m_bFinished = TRUE; return TRUE;}

	return FALSE;
}

void CGPhuongDeGian::DelayClickButtonHuoDong()
{
	if (m_iDelayClicked >= 9) m_bClickButtonHuoDong = FALSE;
	if (g_pGameControl->IsShowPopUI()) m_iDelayClicked = 0;
	m_iDelayClicked ++;
	LOG_WRITE("Wait for clicked huoDong %d", m_iDelayClicked);
	LoopNextSleep();
}

void CGPhuongDeGian::ShowAcitivyWnd()
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

void CGPhuongDeGian::CheckCleanBag()
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

void CGPhuongDeGian::processAlone()
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



