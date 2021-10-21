#include "main.h"
#include "GBayBanTheoDeNghi.h"

CGBayBanTheoDeNghi::CGBayBanTheoDeNghi() :CGActivity()
{
	LOG_WRITE("NEW - CGBayBanTheoDeNghi()");
	m_activity = act_baybantheodenghi;
	m_iClicked = 0;
	m_iNumSell = 0;
	m_bFinished = FALSE;
	m_bTradeTBD = TRUE;
	m_bTradeTCT = TRUE;
	m_czItemName = u"None";
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGBayBanTheoDeNghi::~CGBayBanTheoDeNghi()
{
	LOG_WRITE("DEL - CGBayBanTheoDeNghi()");
}

int CGBayBanTheoDeNghi::Process()
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

			if (g_pGameControl->IsShowPopUI()) {
				g_pGameControl->CloseDialog();
				return LoopNextSleep();
			}
			else return FinishedActivity();
			return m_nStatus;
		}
		LOG_WRITE("CGBayBanTheoDeNghi::Process()....0");
		if (isTradeTooMany(m_czItemName)) return LoopNextSleep();
		if (isStallSellMultiConfirm()) return LoopNextSleep();
		if (isStallSellSingleConfirm()) return LoopNextSleep();

		if (isShopWnd()) return LoopNextSleep();

		ClickShop();
		return LoopNextSleep(1000);

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}


BOOL CGBayBanTheoDeNghi::isShopWnd()
{
	CUE_Transform *pUI = g_pGameControl->m_pPopUIRoot->GetChildByName(u"shop.shoppingmall");
	if (g_pGameControl->IsShowTransform(pUI)) {
		CUE_Transform *pTabStall = pUI->GetChildByPath((u"Offset:List Of Left:LeftGrid:tabStall"));
		if (pTabStall) {
			m_iClicked = 0;
			CUE_Transform *pPress = pTabStall->GetChildByName(u"Press");
			if (!g_pGameControl->IsShowTransform(pPress)) {
				LOG_WRITE("On click stall Tap");
				g_pGameControl->ClickTab(pTabStall);
				return TRUE;
			}
			
			if (isStallMenu(pUI)) return TRUE;

		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGBayBanTheoDeNghi::isStallMenu( CUE_Transform *p )
{
	CUE_Transform *pMenu = p->GetChildByPath(u"Offset:TabContent:Stal_menuList(Clone)");
	if (g_pGameControl->IsShowTransform(pMenu)) {
		CUE_Transform *pSellMenu = pMenu->GetChildByPath(u"Content:Stal_chushou(Clone)");
		if (!g_pGameControl->IsShowTransform(pSellMenu)) {
			LOG_WRITE("Click Sell Menu");
			g_pGameControl->ClickTab(pMenu->GetChildByPath(u"Offset:Grid:menu02"));
			return TRUE;
		}
		
		if (isStallSell()) return TRUE;

		return TRUE;
	}
	return FALSE;
}

BOOL CGBayBanTheoDeNghi::isStallSell()
{
	CStallSell *pIns = CStallSell::Instance();
	if (pIns) {
		_LIST_GIAODICH *pGiaoDich = &g_pGame->m_lstGiaoDich;
		int iVang59Per = g_pGame->m_OptionTab.iPercentGdVang59;
		CSYS_List *pItemChoosed = pIns->m_StallSellListItemList();
		int iCountChoosed = pItemChoosed->get_Count();
		if (iCountChoosed == 8) {
			LOG_WRITE("YESSSSSSSSSSSSSSSS");
			m_bFinished = TRUE;
			return TRUE;
		}

		CSYS_List *pListItem = pIns->m_ItemPackList();
		int iCount = pListItem->get_Count();
		LOG_WRITE("ListCount [%d]", iCount);

		for (int i = 0; i < iCount; i++) {
			CKnapsackItem *kItem = (CKnapsackItem*)pListItem->get_Item(i);
			if (kItem) {
				CGameItem *gameItem = kItem->GetGameItem();
				CStdStringU czName = gameItem->GetName();
				CStdStringU czClassName = gameItem->GetTipsClassDesc();

				if (czName.Compare(u"") != 0) { //kiểm tra tên của món này có trống hay ko 
					CStdString czNameA = g_pGameControl->U2A(czName);
					BOOL bIsEquipment = gameItem->IsEquipMent();
					int iStackCount = gameItem->get_StackCount();
					int iLevel = gameItem->GetEquipLevel();
					
					if (bIsEquipment && iLevel <= 59 && iVang59Per != 11) {
						LOG_WRITE("Clicked [%s]", czNameA.c_str());
						m_iNumSell = iStackCount;
						pIns->ConfirmSellItem(gameItem);
						return TRUE;
					}

					if (czNameA.Find("Tàng Bảo Đồ") >= 0 && m_bTradeTBD) {
						LOG_WRITE("Clicked [%s]", czNameA.c_str());
						m_iNumSell = iStackCount;
						pIns->ConfirmSellItem(gameItem);
						return TRUE;
					}

					if (czNameA.Find("Thiên Cơ Tài") >= 0 && m_bTradeTCT) {
						LOG_WRITE("Clicked [%s]", czNameA.c_str());
						m_iNumSell = iStackCount;
						pIns->ConfirmSellItem(gameItem);
						return TRUE;
					}
	

				}
				//else LOG_WRITE("[%08X][%d] -- [%s][%d]count", gameItem, bIsEquipment, _U2A(czName).c_str(), iStackCount);
			}
		}
		m_bFinished = TRUE;
		return TRUE;
	}
	return FALSE;
}

void CGBayBanTheoDeNghi::ClickShop()
{
	if (m_iClicked == 1) {
		CFunctionButtonController *pIns = CFunctionButtonController::Instance();
		pIns->OnNewClickShop();
	}
	if (m_iClicked >= 5) {
		m_iClicked = 0;
		return;
	}

	m_iClicked ++;
	
}

BOOL CGBayBanTheoDeNghi::isStallSellMultiConfirm()
{
	CStallMultiSellConfirm *pIns = CStallMultiSellConfirm::Instance();
	if (pIns) {
		int iTBDPer = g_pGame->m_OptionTab.iPercentGdTBD;
		int iThienCoTaiPer = g_pGame->m_OptionTab.iPercentGdThienCoTai;
		//int iVang59Per = &g_pGame->m_OptionTab.iPercentGdVang59;

		CKnapsackItem *pItem = pIns->m_Item();
		CGameItem *gameitem = pItem->GetGameItem();
		CStdStringU czName = gameitem->GetName();
		
		int index = pIns->m_StepIdx();
		pIns->OnInputCountOver(m_iNumSell);

		if (m_iNumSell == 0) pIns->CloseWindow();

		if (czName.Find(u"Tàng Bảo Đồ") >= 0) {
			m_czItemName = czName;
			LOG_WRITE("--- [%s] indexPercent[%d]", _U2A(czName).c_str(), iTBDPer);
			SellItemWithPercent( index, iTBDPer);
			return TRUE;
		}

		if (czName.Find(u"Thiên Cơ Tài") >= 0) {
			m_czItemName = czName;
			LOG_WRITE("--- [%s] indexPercent[%d]", _U2A(czName).c_str(), iThienCoTaiPer);
			SellItemWithPercent( index, iThienCoTaiPer);
			return TRUE;
		}

		return TRUE;
	}
	return FALSE;
}

BOOL CGBayBanTheoDeNghi::isStallSellSingleConfirm()
{
	CStallSingleSellConfirm *pIns = CStallSingleSellConfirm::Instance();
	if (pIns) {
		int iVang59Per = g_pGame->m_OptionTab.iPercentGdVang59;
		int index = pIns->m_StepCount();
		LOG_WRITE("StepCount = %d", iVang59Per);
		SellItemWithPercent(index, iVang59Per, TRUE);
		return TRUE;
	}
	return FALSE;
}


void CGBayBanTheoDeNghi::SellItemWithPercent(int idx, int iItemPercent, BOOL isEquip /*= FALSE*/ )
{
	CStallMultiSellConfirm *pIns = CStallMultiSellConfirm::Instance();
	CStallSingleSellConfirm *pIns1 = CStallSingleSellConfirm::Instance();
	int index = idx;
	if (pIns) {
		if (iItemPercent == 0) { //-50
			if (index == 0) pIns->SellItem();
			if (index < 0) pIns->AddMoneyByStep();
			if (index > 0) pIns->MinusMoneyByStep();
		}
		if (iItemPercent == 1) { //-40
			if (index == 1) pIns->SellItem();
			if (index < 1) pIns->AddMoneyByStep();
			if (index > 1) pIns->MinusMoneyByStep();
		}
		if (iItemPercent == 2) { //-30
			if (index == 2) pIns->SellItem();
			if (index < 2) pIns->AddMoneyByStep();
			if (index > 2) pIns->MinusMoneyByStep();
		}
		if (iItemPercent == 3) { //-20
			if (index == 3) pIns->SellItem();
			if (index < 3) pIns->AddMoneyByStep();
			if (index > 3) pIns->MinusMoneyByStep();
		}
		if (iItemPercent == 4) { //-10
			if (index == 4) pIns->SellItem();
			if (index < 4) pIns->AddMoneyByStep();
			if (index > 4) pIns->MinusMoneyByStep();
		}
		if (iItemPercent == 5) { //+0
			if (index == 5) pIns->SellItem();
			if (index < 5) pIns->AddMoneyByStep();
			if (index > 5) pIns->MinusMoneyByStep();
		}
		if (iItemPercent == 6) { //+10
			if (index == 6) pIns->SellItem();
			if (index < 6) pIns->AddMoneyByStep();
			if (index > 6) pIns->MinusMoneyByStep();
		}
		if (iItemPercent == 7) { //+20
			if (index == 7) pIns->SellItem();
			if (index < 7) pIns->AddMoneyByStep();
			if (index > 7) pIns->MinusMoneyByStep();
		}

		if (iItemPercent == 8) { //+30
			if (index == 8) pIns->SellItem();
			if (index < 8) pIns->AddMoneyByStep();
			if (index > 8) pIns->MinusMoneyByStep();
		}

		if (iItemPercent == 9) { //+40
			if (index == 9) pIns->SellItem();
			if (index < 9) pIns->AddMoneyByStep();
			if (index > 9) pIns->MinusMoneyByStep();
		}

		if (iItemPercent == 10) { //+50
			if (index == 10) pIns->SellItem();
			if (index < 10) pIns->AddMoneyByStep();
			if (index > 10) pIns->MinusMoneyByStep();
		}
	}
	
	if (pIns1 && isEquip) {
		if (iItemPercent == 0) { //-50
			if (index == -50) pIns1->SellItem();
			if (index < -50) pIns1->AddMoneyByStep();
			if (index > -50) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 1) { //-40
			if (index == -40) pIns1->SellItem();
			if (index < -40) pIns1->AddMoneyByStep();
			if (index > -40) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 2) { //-30
			if (index == -30) pIns1->SellItem();
			if (index < -30) pIns1->AddMoneyByStep();
			if (index > -30) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 3) { //-20
			if (index == -20) pIns1->SellItem();
			if (index < -20) pIns1->AddMoneyByStep();
			if (index > -20) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 4) { //-10
			if (index == -10) pIns1->SellItem();
			if (index < -10) pIns1->AddMoneyByStep();
			if (index > -10) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 5) { //+0
			if (index == 0) pIns1->SellItem();
			if (index < 0) pIns1->AddMoneyByStep();
			if (index > 0) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 6) { //+10
			if (index == 10) pIns1->SellItem();
			if (index < 10) pIns1->AddMoneyByStep();
			if (index > 10) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 7) { //+20
			if (index == 20) pIns1->SellItem();
			if (index < 20) pIns1->AddMoneyByStep();
			if (index > 20) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 8) { //+30
			if (index == 30) pIns1->SellItem();
			if (index < 30) pIns1->AddMoneyByStep();
			if (index > 30) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 9) { //+40
			if (index == 40) pIns1->SellItem();
			if (index < 40) pIns1->AddMoneyByStep();
			if (index > 40) pIns1->MinusMoneyByStep();
		}
		if (iItemPercent == 10) { //+50
			if (index == 50) pIns1->SellItem();
			if (index < 50) pIns1->AddMoneyByStep();
			if (index > 50) pIns1->MinusMoneyByStep();
		}
	}
}

BOOL CGBayBanTheoDeNghi::isTradeTooMany(CStdStringU czName)
{
	if (g_pGameControl->IsShowTransform(g_pGameControl->m_pStoryMessageUIRoot)) {
		CUE_Transform *p = g_pGameControl->m_pStoryMessageUIRoot->GetChildByName(u"prompt.prompt_tishi_centrenoticecontroller");
		if (g_pGameControl->IsShowTransform(p)) {
			CUE_Transform *pList = p->GetChildByName(u"Offset");
			int iAllChild = pList->get_childCount();
			for (int i = iAllChild - 1; i >= 0; i--) {
				CUE_Transform *pChild = pList->GetChild(i);
				if (g_pGameControl->IsShowTransform(pChild)) {
					CStdStringU czLabel = g_pGameControl->GetTextU(pChild);
					if (czLabel.Find(czName) >= 0) {
						if (m_czItemName.Find(u"Tàng Bảo Đồ") >= 0) m_bTradeTBD = FALSE;
						if (m_czItemName.Find(u"Thiên Cơ Tài") >= 0) m_bTradeTBD = FALSE;
						LOG_WRITE("Is Right Notice..... [%s]", _U2A(czLabel).c_str());
						return TRUE;
					}
					//LOG_WRITE("Notice  [%s]", _U2A(czLabel).c_str());
				}
			}
		}
	}
	return FALSE;
}

