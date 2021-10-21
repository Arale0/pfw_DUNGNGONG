#include "main.h"
#include "GTaskCDTuChan.h"
#include "GSleep.h"

CGTaskCDTuChan::CGTaskCDTuChan() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskCDTuChan()");
	m_bFinished = FALSE;
	m_iDelayClicked = 0;
}

CGTaskCDTuChan::~CGTaskCDTuChan()
{
	LOG_WRITE("DEL - CGTaskCDTuChan()");
	g_pGame->m_iCurrentID = -1;
}

int CGTaskCDTuChan::Process()
{
 
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;
	
	if (IsFinished()) return m_nStatus;
	
	if (IsImmortalityWnd()) return LoopNextSleep();

	ShowImmotalityWnd();

	return m_nStatus;
}

int CGTaskCDTuChan::LoopNextSleep( int delay /*= 1000*/ )
{
	AddSubGoal(new CGSleep(delay));
	
	return LoopNext();
}


BOOL CGTaskCDTuChan::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return Finished();
		return TRUE;
	}

	if (!g_pGame->m_bControl) {
		m_bFinished = TRUE;
		return TRUE;
	}

	if (!g_pGame->m_OptionTab.bCdTuChan) {
		m_bFinished = TRUE;
		return TRUE;
	}

	if (!g_pGameControl->IsImmortalRedot()) {
		m_bFinished = TRUE;
		return TRUE;
	}

	if (g_pGameControl->IsBagFull()) {
		m_bFinished = TRUE;
		return TRUE;
	}

	return FALSE;
}


void CGTaskCDTuChan::ShowImmotalityWnd()
{
	CFunctionButtonController *pIns = CFunctionButtonController::Instance();
	if (!pIns) return;

	if (m_iDelayClicked <= 0) {
		LOG_WRITE("CGTaskCDTuChan::ShowImmotalityWnd().......");
		pIns->OnClickImmortality();
	}

	if (m_iDelayClicked >= 4) {
		m_iDelayClicked = -1;
		return;
	}

	m_iDelayClicked ++;
	LoopNextSleep();
}

BOOL CGTaskCDTuChan::IsImmortalityWnd()
{
	CImmortalityViewLogic *pIns = CImmortalityViewLogic::Instance();
	if (pIns) {
		CImmortalityActivityButton *pCurButton = pIns->m_CurSelectActivityButton();
		CSYS_Array *pListButton = pIns->m_BottomnImmortalityButtons();
		if (pListButton) {
			int iCount = pListButton->get_Length();
			for (int i = 0; i < iCount; i++) {
				CImmortalityActivityButton *pButton = (CImmortalityActivityButton *)pListButton->GetValue(i);
				BOOL bIsActive = pButton->get_ImmortalityActivityActivate();
				BOOL bUnAcept = pButton->get_UnAcceptReward();
				if (bIsActive && bUnAcept) {
					if (pButton != pCurButton) {
						pButton->OnClickActivityButton();
						LOG_WRITE("[%d][%08X] => bIsActive[%d], bUnAcept[%d]", i, pButton, bIsActive, bUnAcept);
						return TRUE;
					}

					CSYS_List *pListButtonReceive = pIns->m_ResourceWayItemList();
					if (pListButtonReceive) {
						int iListItem = pListButtonReceive->get_Count();
						if (iListItem != 0) {
							for (int j = 0; j < iListItem; j++) {
								CImmortalityWayItem *pItem = (CImmortalityWayItem *)pListButtonReceive->get_Item(j);
								if (pItem) {
									CUE_GameObject *pAccecptObj = pItem->m_AccpetGameObject();
									if (pAccecptObj) {
										CUE_Transform *pTransform = pAccecptObj->get_transform();
										if (g_pGameControl->IsShowTransform(pTransform)) {
											//LOG_WRITE("[%d][%08X]Show", j, pRedTransform);
											LOG_WRITE("OnClickAcceptBtn................");
											pItem->OnClickAcceptBtn();
											return TRUE;
										}
									}
								}
							}
						}
					}

					return TRUE;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}
