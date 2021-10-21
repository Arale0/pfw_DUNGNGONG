#include "main.h"
#include "GTaskAchievement.h"
#include "GSleep.h"

CGTaskAchievement::CGTaskAchievement() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskTaskAchievement()");
	m_iTimeCount = 0;
	m_bFinished = FALSE;
}

CGTaskAchievement::~CGTaskAchievement()
{
	LOG_WRITE("DEL - CGTaskTaskAchievement()");
	g_pGameControl->CloseDialog();
	g_pGame->m_iCurrentID = -1;
}

int CGTaskAchievement::Process()
{

	g_pGameControl->SetCurrentID(100);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("CGTaskTaskAchievement::Process()");

	if (!g_pGame->m_OptionTab.bAchievement) {LOG_WRITE("Finishedddddddddddd"); return Finished();}

	if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep(500);

	if (g_pGameControl->IsFBResultWnd()) return m_nStatus;

	if (IsFinished()) return m_nStatus;

	if (IsOverTime()) return m_nStatus;

	if (g_pGameControl->ProcessMessageBox(u"Thoát phó bản?", MSG_OK)) return LoopNextSleep();

	if (g_pGameControl->IsBagFull()) {m_bFinished = TRUE; return m_nStatus; }

	if (IsNotActiveRedot()) {
		LOG_WRITE("IsActiveRedot");
		m_bFinished = TRUE;
		return m_nStatus;
	}

	if (IsTaskAchievementWnd()) return LoopNextSleep(500);

	ShowTaskAchievementWnd();
	return m_nStatus;
}

int CGTaskAchievement::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);
	return LoopNext();
}

void CGTaskAchievement::ShowTaskAchievementWnd()
{
	if (g_pGameControl->IsStoryUIRoot()) return;
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) {return; }
	LOG_WRITE("CGTaskTaskAchievement::OnClickAchievement()....");
	pInstance->OnClickAchievement();
	LoopNextSleep();

}


BOOL CGTaskAchievement::IsNotActiveRedot()
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	CUE_Transform *pRedDot = pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:RightBottom:No.2:Grid_01:ChengJiu:RedDot");
	if (!g_pGameControl->IsShowTransform(pRedDot)) {
		LOG_WRITE("sssssssssssssssssssss");
		m_bFinished = TRUE;
		return TRUE;
	}
	return FALSE;
}


BOOL CGTaskAchievement::IsTaskAchievementWnd()
{
	CUE_Transform *pListTemp = NULL;

	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		LOG_WRITE("AAAAAAAAAAAAAAAAAAAAAaa");
		CUE_Transform *pWnd = pPopUIRoot->GetChildByName(u"ChengJiuRoot");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			CUE_Transform *pList = pWnd->GetChildByPath(u"Offset:ChengJiuWindow:ListGrid:ScrollView:Grid");
			if (g_pGameControl->IsShowTransform(pList)) {
				LOG_WRITE("BBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
				int iAllChild = pList->get_childCount();

				if (iAllChild == 0) {
					m_bFinished = TRUE;
					return TRUE;
				}
				for (int i = 0; i < iAllChild; i++) {
					CUE_Transform *pChild = pList->GetChild(i);	
					if (pChild) {
						LOG_WRITE("Received %d........................", i);
						CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","AchievementRecordItem");
						CAchievementRecordItem*  pShiJiao= (CAchievementRecordItem *)pChild->GetComponent(pType);
						if (pShiJiao) {
							pShiJiao->OnClickGetReward();
							return TRUE;
						}
						//g_pGameControl->Clicked(pChild->GetChildByPath(u"Offset:LQBtn"));
						return TRUE;
					}
				}
			}

			CUE_Transform *pList1 = pWnd->GetChildByPath(u"Offset:ChengJiuWindow:ListRewardGrid:ScrollView:Grid");
			if (g_pGameControl->IsShowTransform(pList1)) {
				LOG_WRITE("CCCCCCCCCCCCCCCCCCCCCCCCCCCC");
				int iAllChild = pList1->get_childCount();

				if (iAllChild == 0) {
					m_bFinished = TRUE;
					return TRUE;
				}
				for (int i = 0; i < iAllChild; i++) {
					CUE_Transform *pChild = pList1->GetChild(i);	
					if (pChild) {
						CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","AchievementRewardItem");
						CAchievementRewardItem*  pShiJiao= (CAchievementRewardItem *)pChild->GetComponent(pType);
						if (pShiJiao) {
							BOOL bHaveReward = pShiJiao->get_bHaveReward();
							//LOG_WRITE("Received %d -- bHaveReward[%d]", i, bHaveReward);
							if (!bHaveReward) {
								LOG_WRITE("Received %d........................", i);
								pShiJiao->OnClickGetReward();
								LoopNextSleep();
								return TRUE;
							}
						}
						//g_pGameControl->Clicked(pChild->GetChildByPath(u"Offset:LQBtn"));
					}
				}
			}

		}
	}
	return FALSE;
}

BOOL CGTaskAchievement::IsOverTime()
{
	if (m_iTimeCount >= 20) {
		m_bFinished = TRUE;
		LOG_WRITE("CGTaskFuli::IsOverTime()..................");
		return TRUE;
	}
	m_iTimeCount ++;
	LOG_WRITE("m_iTimeCount = %d", m_iTimeCount);
	LoopNextSleep();
	return FALSE;
}

BOOL CGTaskAchievement::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return Finished();
		return TRUE;
	}

	return FALSE;
}
