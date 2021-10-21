#include "main.h"
#include "GTaskCleanBag1.h"
#include "GSleep.h"

CGTaskCleanBag1::CGTaskCleanBag1() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskTaskCleanBag1()");
	m_bFinished = FALSE;
	m_iTypeCleanBag = 0;
}

CGTaskCleanBag1::~CGTaskCleanBag1()
{
	LOG_WRITE("DEL - CGTaskTaskCleanBag1()");
}

int CGTaskCleanBag1::Process()
{
 
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("CGTaskTaskCleanBag1::Process()");

	if (g_pGameControl->ProcessMessageBox(u"Cần đến bản đồ chỉ định ", MSG_OK)) return LoopNextSleep(500);

	if (g_pGameControl->IsNoticeWnd()) return Finished();

	if (g_pGameControl->IsLowerLevelWnd()) return LoopNextSleep();

	if (IsCopyFinishedFubenWnd()) return Finished();

	if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep(500);
	
	if (IsFinished()) return m_nStatus;
	
	if (g_pGameControl->ProcessMessageBox(u"Sau khi mặc,", MSG_OK)) return m_nStatus;

	if (g_pGameControl->ProcessMessageBox(u"Trang bị đã góp", MSG_OK)) return m_nStatus;

	if (g_pGameControl->ProcessMessageBox(u"mời bạn vào đội,", MSG_CANCEL)) return LoopNextSleep(500);

	if (g_pGameControl->ProcessMessageBox(u"Trang bị này có thể", MSG_OK)) return LoopNextSleep(500);

	if (g_pGameControl->ProcessMessageBox(u"Đồng ý", MSG_OK)) return LoopNextSleep(500);

	if (IsTaskCleanBagWnd()) return LoopNextSleep();

	ShowTaskCleanBagWnd();
	return m_nStatus;
}

int CGTaskCleanBag1::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);
	return LoopNext();
}

void CGTaskCleanBag1::ShowTaskCleanBagWnd()
{
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) {return; }
	if (g_pGameControl->IsShowPopUI()) {g_pGameControl->CloseDialog(); return;}
	LOG_WRITE("CGTaskTaskCleanBag::OnClickCleanBag()....");
	pInstance->OnClickBackPack();
	LoopNextSleep();

}

BOOL CGTaskCleanBag1::IsTaskCleanBagWnd()
{
	
	if (IsMilitaryWnd()) return TRUE;
	if (IsItemTips())  return TRUE;

	if (!g_pGameControl->IsShowTransformKnapsack()) return FALSE;

	CKnapsackWindow *pIns = CKnapsackWindow::Instance();
	if (pIns) {
		CKnapsackWindow *pIns = CKnapsackWindow::Instance();
		
		int iFilterType = pIns->m_FilterType();
		if (iFilterType != 1) {
			SelectOtherTab(pIns);
			return TRUE;
		}

		ProcessCleanBag(pIns);
		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskCleanBag1::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return Finished();
		return TRUE;
	}
	
	if (!g_pGame->m_OptionTab.bBagInFb) {
		if (g_pGameControl->IsButtonExitFuben()) {
			m_bFinished = TRUE;
			return TRUE;
		}
	}

	if (!g_pGame->m_OptionTab.bCleanBag) {
			m_bFinished = TRUE;
			return TRUE;
	}

	if (!g_pGame->m_OptionTab.bTachTrangBiKhoa && 
		!g_pGame->m_OptionTab.bDungTrangBi	   && 
		!g_pGame->m_OptionTab.bTachTrangBiVang &&
		!g_pGame->m_OptionTab.bTachTrangBiLcCao) {
		m_bFinished = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL CGTaskCleanBag1::IsItemTips()
{
	CUE_Transform *p = g_pGameControl->m_pTipUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"item.equiptipsnew");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			CUE_Transform *pButtonList = pWnd->GetChildByPath(u"Offset:Grid:Equip_Now:Offset ButtonList:Offset:Grid");
			int iAllChild = pButtonList->get_childCount();
			if (iAllChild != 0) {
				int i = 0;
				for (i = 0; i < iAllChild; i++ ) {
					CUE_Transform *pButton = pButtonList->GetChild(i);
					CUE_Transform *pLabel = pButton->GetChildByPath(u"Offset:Button:Label");
					CStdStringU czULabel = g_pGameControl->GetTextU(pLabel);

					if (g_pGame->m_OptionTab.bGop) {
						if (czULabel.Find(u"Góp") >= 0 && m_iTypeCleanBag == 3) {
							LOG_WRITE("...............GOP................");
							g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
							return TRUE;
						}
					}

					if (g_pGame->m_OptionTab.bTachTrangBiKhoa || 
						g_pGame->m_OptionTab.bTachTrangBiLcCao ||
						g_pGame->m_OptionTab.bTachTrangBiVang) {
						LOG_WRITE("Yeah........................");
						if (czULabel.Find(u"Tách") >= 0 && m_iTypeCleanBag == 2) {
							LOG_WRITE("...............TACH................");
							g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
							return TRUE;
						}
					}

					if (g_pGame->m_OptionTab.bDungTrangBi && czULabel.Find(u"Trang Bị") >= 0 && m_iTypeCleanBag == 1) {
						LOG_WRITE("...............EQUIPS................");
						g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
						return TRUE;
					}

					g_pGameControl->Tap(1,1);
				}

				if (i == iAllChild) {
					m_bFinished = TRUE;
					return TRUE;
				}
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CGTaskCleanBag1::IsCopyFinishedFubenWnd()
{
	CCopySceneSettlementController *pInstance = CCopySceneSettlementController::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("IsCopyFinishedFubenWnd...............");
	return TRUE;
}

BOOL CGTaskCleanBag1::GopTrangBi()
{
	CUE_Transform *pWnd = g_pGameControl->m_pTipUIRoot->GetChildByName(u"roleview.junxian_juanxian");
	if (g_pGameControl->IsShowTransform(pWnd)) {
		LOG_WRITE("...............GOP............");
		g_pGameControl->Clicked(pWnd->GetChildByPath(u"Offset:btn_sure"));
		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskCleanBag1::IsMilitaryWnd()
{
	CMilitaryDonationWindow *pIns = CMilitaryDonationWindow::Instance();
	if (pIns) {
		pIns->OnClickDonate();
		pIns->OnClickClose();
		return TRUE;
	}
	return FALSE;
}

void CGTaskCleanBag1::SelectOtherTab( CKnapsackWindow *pIns )
{
	if (!pIns) return;
	CSYS_List *pFilterList = pIns->m_FilterItemList();
	if (!pFilterList) return;
	int iCount = pFilterList->get_Count();
	if (iCount == 0) return;

	UINT uFilter = (UINT)pFilterList->get_Item(1);
	if (uFilter == 0) return;
	CUE_Transform *pTransform = g_pGameControl->get_Transform(uFilter);
	if (pTransform) {
		LOG_WRITE("CGTaskCleanBag1::Click Other Btn.....");
		g_pGameControl->Clicked(pTransform->GetChildByName(u"equip_off"));
		return;
	}
}	

void CGTaskCleanBag1::ProcessCleanBag( CKnapsackWindow *pIns )
{
	//if (!pIns) return;

	//CSYS_List *pKnapsackList = pIns->filterItemList();
	//if (!pKnapsackList) return;
	//int iCount  = pKnapsackList->get_Count();
	//if (iCount == 0) return;
	//int i = 0;
	//for (i = 0; i < iCount; i++) {
	//	//CKnapsackItem *pItem = (CKnapsackItem *)pKnapsackList->get_Item(i);
	//
	//	//if (pItem) {
	//		LOG_WRITE("......................%d", i);
	//		CGameItem *pGameItem = (CGameItem *)pKnapsackList->get_Item(i);
	//		if (pGameItem) {
	//			int iLevel = pGameItem->GetEquipLevel();
	//			CStdStringU czUName = pGameItem->GetName();
	//			CStdStringU czUClassName = pGameItem->GetTipsClassDesc();
	//			if (g_pGame->m_OptionTab.bDungTrangBi) {
	//				
	//			}
	//			
	//			if (!g_pGameControl->IsBagFull()) {
	//				if (g_pGame->m_OptionTab.bTachTrangBiLcCao) {
	//					
	//				}

	//				if (g_pGame->m_OptionTab.bTachTrangBiKhoa) {
	//					
	//				}

	//				if (g_pGame->m_OptionTab.bTachTrangBiVang) {
	//					if (!g_pGame->m_OptionTab.bTachGold59 &&
	//						!g_pGame->m_OptionTab.bTachGold69 && 
	//						!g_pGame->m_OptionTab.bTachGold79 &&
	//						!g_pGame->m_OptionTab.bTachGold89  &&
	//						!g_pGame->m_OptionTab.bTachGoldAllLV  ) {
	//							g_pGame->m_OptionTab.bTachTrangBiVang = FALSE;
	//							return;
	//					}

	//					if (czNameQuality.Compare(u"common_x_knapsack_bg_04") == 0) {

	//						if (czUName.Find(u"Quân Hàm") <= 0) {
	//							if (g_pGame->m_OptionTab.bTachGoldAllLV) {
	//								LOG_WRITE("On Click bTachGoldAllLV [%s]", _U2A(czUName).c_str());
	//								m_iTypeCleanBag = 2;
	//								pIns->Click_Item_BelongBackPack(pGameItem);
	//								return ;
	//							}

	//							if (g_pGame->m_OptionTab.bTachGold59 && iLevel <= 59) {
	//								LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
	//								m_iTypeCleanBag = 2;
	//								pIns->Click_Item_BelongBackPack(pGameItem);
	//								return ;
	//							}

	//							if (g_pGame->m_OptionTab.bTachGold69 && iLevel == 69) {
	//								LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
	//								m_iTypeCleanBag = 2;
	//								pIns->Click_Item_BelongBackPack(pGameItem);
	//								return ;
	//							}

	//							if (g_pGame->m_OptionTab.bTachGold79 && iLevel == 79) {
	//								LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
	//								m_iTypeCleanBag = 2;
	//								pIns->Click_Item_BelongBackPack(pGameItem);
	//								return ;
	//							}

	//							if (g_pGame->m_OptionTab.bTachGold89 && iLevel == 89) {
	//								LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
	//								m_iTypeCleanBag = 2;
	//								pIns->Click_Item_BelongBackPack(pGameItem);
	//								return ;
	//							}
	//						}
	//					}
	//				}
	//			}
	//		//}
	//	}
	//}

	//if (i == iCount) {
	//	m_bFinished = TRUE; 
	//	return;
	//}
}
