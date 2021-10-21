#include "main.h"
#include "GTaskGetMail.h"
#include "GSleep.h"

CGTaskGetMail::CGTaskGetMail() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskGetMail()");
	m_iTimeCount = 0;
	m_bFinished = FALSE;
	m_bDeleteAllMailFirst = FALSE;
}

CGTaskGetMail::~CGTaskGetMail()
{
	LOG_WRITE("DEL - CGTaskGetMail()");
	g_pGameControl->CloseDialog();
	g_pGame->m_iCurrentID = -1;
}

int CGTaskGetMail::Process()
{

	g_pGameControl->SetCurrentID(105);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("CGTaskGetMail::Process()");
	
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) {
			g_pGameControl->CloseDialog();
			return LoopNextSleep();
		}
		else return Finished();
		return m_nStatus;
	}

	if (!g_pGame->m_OptionTab.bCheckMail) {
		m_bFinished = TRUE;
		return LoopNextSleep();
	}

	if (g_pGameControl->IsBagFull()) {
		m_bFinished = TRUE;
		return LoopNextSleep();
	}

	if (IsMailWnd()) return LoopNextSleep();

	ShowMailWnd();
	return m_nStatus;
}

int CGTaskGetMail::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);//AddSubGoal(new CGSleep(delay));
	return LoopNext();
}


void CGTaskGetMail::ShowMailWnd()
{
	if (!IsNewMail()) {
		m_bFinished = TRUE;
		return;
	}
	
	if (g_pGameControl->IsShowPopUI()) {
		g_pGameControl->CloseDialog();
		return;
	}

	CChatFrameController *pIns = CChatFrameController::Instance();
	if (pIns) {
		LOG_WRITE("CGTaskGetMail::ShowMailWnd()..............");
		pIns->OnClickOpenFriend();
		LoopNextSleep();
	}
	
	LoopNextSleep();

	//else {
	//	/*static int i = -1;
	//	if (g_pGameControl->IsShowPopUI()) i = 1;
	//	if (i <= 0) {
	//		CChatFrameController *pIns = CChatFrameController::Instance();
	//		if (pIns) {
	//			LOG_WRITE("CGTaskGetMail::ShowMailWnd()..............");
	//			pIns->OnClickOpenFriend();
	//		}
	//	}
	//	if (i >= 5) i = -1;
	//	LoopNextSleep();*/
	//}

} 

BOOL CGTaskGetMail::IsNewMail()
{
	return g_pGameControl->IsNewMail();
}

BOOL CGTaskGetMail::IsMailWnd()
{
	CSocialRootController *pIns = CSocialRootController::Instance();
	if (pIns) {
		CReadMailLogic *pMailInstance = CReadMailLogic::Instance();
		if (pMailInstance) {

			LOG_WRITE("OnClickExtractAll................");
			pMailInstance->OnClickExtractAll();

			if (!m_bDeleteAllMailFirst) {
				LOG_WRITE("Delete all Read Mail first.....");
				m_bDeleteAllMailFirst = TRUE;
				pMailInstance->DoDeleteAll();
				return TRUE;
			}

			if (!pMailInstance->IsAllMailsHaveItem()) {
				m_bFinished = TRUE;
				return TRUE;
			}
 			return TRUE;
		}

		CUE_Transform *pWnd = g_pGameControl->get_Transform((UINT)pIns);
		if (pWnd ) {
			LOG_WRITE("Change to Mail Tab.............");
			g_pGameControl->Clicked(pWnd->GetChildByPath(u"tweenFrame:offset:tabbtn:Grid:Tabmail"));
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}

