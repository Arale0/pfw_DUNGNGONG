#include "main.h"
#include "GQuyetDauDinhCao.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"

CGQuyetDauDinhCao::CGQuyetDauDinhCao() :CGActivity()
{
	LOG_WRITE("NEW - CGQuyetDauDinhCao()");
	m_activity = act_quyetdaudinhcao;
	m_bFinished = FALSE;
	//m_bShowAsynWnd = FALSE;
	m_iDelay = -1;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGQuyetDauDinhCao::~CGQuyetDauDinhCao()
{
	LOG_WRITE("DEL - CGQuyetDauDinhCao()");
}

int CGQuyetDauDinhCao::Process()
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

		if (IsAsynPVP()) return LoopNextSleep();

		if (IsInFb()) return LoopNextSleep();
		
		ShowAsynPVPWnd();

		LOG_WRITE("CGQuyetDauDinhCao::Process()....");
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGQuyetDauDinhCao::IsFinished()
{
	if (m_bFinished) {
		CUE_Transform *pUI = g_pGameControl->m_pPopUIRoot->GetChildByName(u"asynpvp.asynpvproot");
		if (g_pGameControl->IsShowTransform(pUI)) {
			g_pGameControl->Clicked(pUI->GetChildByPath(u"Offset:Frame (1):CloseButton"));
		}
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(27)) { m_bFinished = TRUE; return TRUE;}
	
	return FALSE;
}

void CGQuyetDauDinhCao::ShowAsynPVPWnd()
{
	if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();

	if (m_iDelay <= 0) {
		LOG_WRITE("ShowAsynPVPWnd()");
		CActivityHuoDongWindow::OnClickAsynPVP();
	}

	if (m_iDelay >= 5) m_iDelay = -1;
	
	m_iDelay ++;
	LOG_WRITE("m_iDelay == %d", m_iDelay);
	LoopNextSleep();
}

BOOL CGQuyetDauDinhCao::IsAsynPVP()
{
	CAsynPVPMatchWindow *pInstance = CAsynPVPMatchWindow::Instance();
	if (pInstance) {
		CStdStringU czUCount = pInstance->get_ChallengeCount();
		if (czUCount.Compare(u"5/5") == 0) {
			//LOG_WRITE("ssssssssssssssssssssssssssssssssssssssss");
			m_bFinished = TRUE;
			return TRUE;
		}

		CSYS_List *pLst = pInstance->get_FightList();
		if (!pLst) return FALSE;
		int iCount = pLst->get_Count();
		if (iCount != 0) {

			if (g_pGame->m_OptionTab.bQDDCRandom) {
				int idxRandom = g_pUEThread->GetTickCount() % iCount;
				CAsynPVPItem *pItem = (CAsynPVPItem *)pLst->get_Item(idxRandom);
				LOG_WRITE("CGQuyetDauDinhCao::Fight......................");
				pItem->OnFightClick();
				LoopNextSleep(3000);
				return TRUE;
			}
			
			int iMin = 1000000;
			CAsynPVPItem *pItemTemp = NULL;
			int i = 0;
			for (i = 0; i < iCount; i ++) {
				CAsynPVPItem *pItem = (CAsynPVPItem *)pLst->get_Item(i);
				CStdStringU czCombatValue = pItem->get_CombatValue();
				int iNum = atoi(_U2A(czCombatValue).c_str());
				if (iNum < iMin) {
					iMin = iNum;
					pItemTemp = pItem;
				}
			}

			if (i >= iCount) {
				if (pItemTemp) {
					LOG_WRITE("iMin = [%d]", iMin);
					pItemTemp->OnFightClick();
					LoopNextSleep(3000);
					return TRUE;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

void CGQuyetDauDinhCao::Activate()
{
	m_nStatus = ACTIVE;
}

BOOL CGQuyetDauDinhCao::IsInFb()
{
	if (g_pGameControl->IsButtonExitFuben()) {
		g_pGameControl->SwitchAutoFight(ON);
		return TRUE;
	}
	return FALSE;
}



