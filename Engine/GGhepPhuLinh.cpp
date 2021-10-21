#include "main.h"
#include "GGhepPhuLinh.h"

CGGhepPhuLinh::CGGhepPhuLinh() :CGActivity()
{
	LOG_WRITE("NEW - CGGhepPhuLinh()");
	m_activity = act_ghepphulinh;
	m_iCurrentItem = -1;
	m_iDelayShowKnapsack = -1;
	m_bFinished = FALSE;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGGhepPhuLinh::~CGGhepPhuLinh()
{
	LOG_WRITE("DEL - CGGhepPhuLinh()");
}

int CGGhepPhuLinh::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGGhepPhuLinh::Process()....%d", m_iDelayShowKnapsack);
		
		if (m_iDelayShowKnapsack == 100) {
			if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
			else FinishedActivity();
			return m_nStatus;
		}

		if (g_pGameControl->ProcessMessageBox(u"Trong nguyên liệu có vật phẩm khóa,", MSG_OK)) return LoopNextSleep();

		if (IsNumericKeyBoard()) return LoopNextSleep();

		if (IsItemTipsWnd()) return LoopNextSleep();

		if (IsKnapsackWnd()) return LoopNextSleep();
		
		showKnapsackWnd();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGGhepPhuLinh::IsKnapsackWnd()
{
	CKnapsackWindow *pIns = CKnapsackWindow::Instance();
	if (pIns) {
		if (IsQianKunDaiWnd()) return TRUE;

		else g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"Knapsack:Offset:List Of Top:Grid:TianDiHongLu"));
		return TRUE;
	}
	return FALSE;
}

BOOL CGGhepPhuLinh::IsQianKunDaiWnd()
{
	CQianKunDaiWindow *pIns = CQianKunDaiWindow::Instance();
	if (pIns) {
		
		if (IsHasSuccessItem(pIns)) return TRUE;

		CSYS_List *pListBuffItem = pIns->get_QianKunDaiStuff();
		if (pListBuffItem) {
			int iCount = pListBuffItem->get_Count();
			if (iCount == 6) {
				LOG_WRITE("Ghep.............");
				pIns->OnCombineClick();
				return TRUE;
			}
			
			if (m_iDelayShowKnapsack == 99) {
				LOG_WRITE("m_iDelayShowKnapsack == 99");
				if (iCount >= 3) {
					LOG_WRITE("Ghep thieu.............");
					pIns->OnCombineClick();
					return TRUE;
				}
				else m_iDelayShowKnapsack = 100;
				return TRUE;
			}
			put_GameItem(pIns);
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGGhepPhuLinh::IsItemTipsWnd()
{
	CUE_Transform *p = g_pGameControl->m_pTipUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"item.itemtips");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			LOG_WRITE("Put in......");
			g_pGameControl->Clicked(pWnd->GetChildByPath(u"Offset:TipsFolder:Offset Bottom:Button List:Grid:0:Offset:Button"));
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGGhepPhuLinh::IsNumericKeyBoard()
{
	CNumericKeyboardWindow *pIns = CNumericKeyboardWindow::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("IsNumericKeyBoard::Submit....................");
	pIns->OnMaxClick();
	pIns->OnClickSumbit();
	return TRUE;
}

BOOL CGGhepPhuLinh::IsHasSuccessItem( CQianKunDaiWindow *pInstance )
{
	if (!pInstance) return FALSE;
	CGameItem *pSuccessItem = pInstance->get_SuccessItem();
	if (!pSuccessItem) return FALSE;
	CStdStringU czName = pSuccessItem->GetName();
	if (czName.Compare(u"") == 0) return FALSE;
	LOG_WRITE("Yes, There is SuccessItem....");
	g_pGameControl->CloseDialog();
	return TRUE;
}

void CGGhepPhuLinh::put_GameItem( CQianKunDaiWindow *pInstance )
{
	if (!pInstance) return;
	CSYS_List *pListGameItemHas = pInstance->get_QianKunDaiFilter();
	if (pListGameItemHas) {
		m_iDelayShowKnapsack = 1;
		int iCount = pListGameItemHas->get_Count();
		if (iCount != 0) {
			if (m_iCurrentItem < iCount) {
				int i = 0;
				for (i = m_iCurrentItem + 1; i < iCount; i++) {
					CGameItem *pGameItem = (CGameItem *)pListGameItemHas->get_Item(i);
					CStdStringU czName = pGameItem->GetName();
					CStdStringU czClaseName = pGameItem->GetTipsClassDesc();
					if (czName.Find(u"Thái Thanh Linh") >= 0) {
						m_iCurrentItem = i;
						pInstance->OnBackItemClick(pGameItem);
						return;
					}
				}

				if (i >= iCount ) {
					LOG_WRITE("End Loop......");
					m_iDelayShowKnapsack = 99;
					return;
				}
				return;
				
				//Xanh - Thái Thanh Linh
				//Vàng - Thái Thanh Thần
				//Tím - Thượng Thanh Huyền
				/*if (czName.Find(u"Thượng Thanh Huyền") >= 0) {
					LOG_WRITE("[%d][%08X] -- [%s] -- [%s]", i, pGameItem, _U2A(czName).c_str(), _U2A(czClaseName).c_str());
					pInstance->OnBackItemClick(pGameItem);
					return TRUE;
				}*/
			}

			LOG_WRITE("No game item found in list.............");
			m_iDelayShowKnapsack = 100;
			return;
		}
	}
}

void CGGhepPhuLinh::showKnapsackWnd()
{
	if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
	if (m_iDelayShowKnapsack <= 0) {
		CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
		if (pInstance) pInstance->OnClickBackPack();
	}
	if (m_iDelayShowKnapsack >= 3) {
		m_iDelayShowKnapsack = -1;
		return;
	}
	m_iDelayShowKnapsack ++;
	LoopNextSleep();
}



