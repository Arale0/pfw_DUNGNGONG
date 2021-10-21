#include "main.h"
#include "GTruThienPhuDo.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"

CGTruThienPhuDo::CGTruThienPhuDo() :CGActivity()
{
	LOG_WRITE("NEW - CGTruThienPhuDo()");
	m_activity = act_truthienphudo;
	m_bFinished = FALSE;
	m_bSweep = FALSE;
	m_bShowTowerWnd = FALSE;
	m_iDelay = 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGTruThienPhuDo::~CGTruThienPhuDo()
{
	LOG_WRITE("DEL - CGTruThienPhuDo()");
}

int CGTruThienPhuDo::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{

		if (IsTowerResult()) return LoopNextSleep();

		if (IsFinished()) return m_nStatus;

		if (IsResultWnd()) return LoopNextSleep();
		
		if (IsInFb()) return LoopNextSleep(500);	

		if (IsTowerWnd()) return LoopNextSleep();

		ShowTowerWnd();

		LOG_WRITE("CGTruThienPhuDo::Process()....");
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGTruThienPhuDo::ShowTowerWnd()
{
	if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
	
	if (!m_bShowTowerWnd) {
		m_iDelay = 0;
		m_bShowTowerWnd = TRUE;
		LOG_WRITE("ShowAsynPVPWnd()");
		CActivityHuoDongWindow::OnClickTower();
		return;
	}

	if (m_iDelay >= 7) m_bShowTowerWnd = FALSE;

	m_iDelay ++;
	LOG_WRITE("m_iDelay = %d", m_iDelay);
	LoopNextSleep();
}

BOOL CGTruThienPhuDo::IsTowerWnd()
{
	CTowerWindow *pInstance = CTowerWindow::Instance();
	if (pInstance) {
		m_iDelay = 0;
		CStdStringU czSweepCount = pInstance->get_LeftSweepCount();
		CStdStringU czCount = pInstance->get_LeftFightCount();
		
		if (czCount.Find(u"[c][22875AFF]0[-][/c]") >= 0) m_bSweep = TRUE;

		if (m_bSweep) {
			
			CUIButton *pSweepBtn = pInstance->get_TowerSweepBtn();
			if (pSweepBtn) {
				BOOL bIsEnable = pSweepBtn->get_isEnabled();
				if (!bIsEnable) {
					LOG_WRITE("Sweep btn Is Disable.....");
					m_bFinished = TRUE;
					return TRUE;
				}

				if (czSweepCount.Find(u"0[-][/c]") < 0) {
					LOG_WRITE("Sweep............................");
					pInstance->OnClickTowerSweep();
					return TRUE;
				}
				else m_bFinished = TRUE;
			}
			return TRUE;
		}


		if (g_pGame->m_OptionTab.bTruThienSweepOnly) {
			LOG_WRITE("Sweep Only.........");
			m_bSweep = TRUE;
			return TRUE;
		}

		if (g_pGame->m_OptionTab.bTruThienGoAllTime) {
			//co check
			LOG_WRITE("IsTowerWnd::OnClickTowerFight().............[%s]", _U2A(czCount).c_str());
			pInstance->OnClickTowerFight();
			return TRUE;
		}

		LOG_WRITE("IsTowerWnd::OnClickTowerFight().............[%s]", _U2A(czCount).c_str());
		pInstance->OnClickTowerFight();
		return TRUE;
	}
	return FALSE;
}

BOOL CGTruThienPhuDo::IsResultWnd()
{
	CCopySceneSettlementController *pInstance = CCopySceneSettlementController::Instance();
	if (!pInstance) return FALSE;
	CUE_Transform *pLoseWnd = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"settlement.settlement:Offset:jiesuan:shibai");
	if (g_pGameControl->IsShowTransform(pLoseWnd)) {
		if (!g_pGame->m_OptionTab.bTruThienGoAllTime) m_bSweep = TRUE;
		LOG_WRITE("Exit fb................................");
		g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"settlement.settlement:Offset:jiesuan:shibai:btn_exist"));
		return TRUE;
	}

	LOG_WRITE("OnClickTowerNext()........");
	pInstance->OnClickTowerNext();

	return TRUE;
}

BOOL CGTruThienPhuDo::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowTransform(g_pGameControl->m_pFloatUIRoot->GetChildByName(u"activity.fututa.fututa_saodang"))) {
			g_pGameControl->CloseDialog();
			return TRUE;
		}
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(27)) { m_bFinished = TRUE; return TRUE;}

	return FALSE;
}

void CGTruThienPhuDo::Activate()
{	
	m_nStatus = ACTIVE;

	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
}

BOOL CGTruThienPhuDo::IsInFb()
{
	if (g_pGameControl->IsButtonExitFuben()) {
		m_iDelay = 0;
		g_pGameControl->SwitchAutoFight(ON);
		return TRUE;
	}

	return FALSE;
}

BOOL CGTruThienPhuDo::IsTowerResult()
{
	CTowerSweepResult *pIns = CTowerSweepResult::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("Close Tower Result.............");
	pIns->OnClickClose();
	return TRUE;
}



