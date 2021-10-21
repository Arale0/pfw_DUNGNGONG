#include "main.h"
#include "GDaNgongCuong.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"
#include "GTaskCleanBag.h"
#include "GTaskCleanBag1.h"

CGDaNgongCuong::CGDaNgongCuong() :CGActivity()
{
	LOG_WRITE("NEW - CGDaNgongCuong()");
	m_activity = act_dangongcuong;
	m_iDelayClick = 0;
	m_iItem		  = -1;
	m_iMinMoney	  = 0;
	m_iNeedItemCount = 0;
	m_bGoGuild	  = FALSE;
	m_bBought	  = FALSE;
	m_bFinished	  = FALSE;
	m_bSelected   = FALSE;
	m_pSelectItem = NULL;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGDaNgongCuong::~CGDaNgongCuong()
{
	LOG_WRITE("DEL - CGDaNgongCuong()");
}

int CGDaNgongCuong::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGDaNgongCuong::Process()....");
		
		if (IsFinished()) return m_nStatus;

		if (g_pGameControl->IsBagFull()) {m_bFinished = TRUE; return m_nStatus;}

		if (IsFirmBuy()) return LoopNextSleep();

		if (IsSystemShopWindow())return LoopNextSleep();

		if (IsStallBuyWnd()) return LoopNextSleep();

		if (IsShopWnd()) return LoopNextSleep();
		
		if (IsUIJianMu()) return LoopNextSleep();

		if (IsNPCDialog()) return LoopNextSleep();

		if (IsGuildMap()) return LoopNextSleep();

		if (IsGuildScene()) return LoopNextSleep();

		GoBackGuildScene();

		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGDaNgongCuong::GoBackGuildScene()
{
	

	if (g_pGameControl->IsShowPopUI()) {
		LOG_WRITE("POP UI.....................");
		//g_pGameControl->CloseDialog();
		return;
	}

	if (!g_pGameControl->IsHaveGuild()) {m_bFinished = TRUE; return;}

	if (!m_bGoGuild) {
		m_bGoGuild = TRUE;
		LOG_WRITE("GoBackGuildScene..............");
		CActivityHuoDongWindow::OnClickBangHuaBtn();
		return;
	}
	
	if (m_iDelayClick >= 7) {
		m_bGoGuild = FALSE;
		m_iDelayClick = 0;
	}
	m_iDelayClick ++;
	LOG_WRITE("m_iDelayClick = [%d]", m_iDelayClick);
	LoopNextSleep();
}

BOOL CGDaNgongCuong::IsGuildScene()
{
	if (g_pGameControl->IsMap(u"Cứ Địa Bang")) {

		if (g_pGameControl->IsMoving()) return TRUE;

		m_iDelayClick = 0;
		g_pGameControl->ShowMap();
		LoopNextSleep(500);
		return TRUE;
	}
	return FALSE;
}

BOOL CGDaNgongCuong::IsGuildMap()
{
	CSceneMapController *pIns = CSceneMapController::Instance();
	if (pIns) {
		CStdStringU czUNameMap = pIns->get_SceneNameLabel();
		if (czUNameMap.Find(u"Cứ Địa Bang") >= 0) {
			m_iDelayClick = 0;
			CUE_Transform *p = g_pGameControl->get_Transform((UINT)pIns);
			CUE_Transform *pListNPC = p->GetChildByPath(u"Offset:Map_Popup_npclist:Offset:npc:Info:NpcGrid");
			if (!pListNPC) return FALSE;
			int iCount = pListNPC->get_childCount();
			if (iCount == 0) return FALSE;
			for (int i = 0; i < iCount; i++) {
				CUE_Transform *pNPC = pListNPC->GetChild(i);
				CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","AutoSearchPointLogic");
				CAutoSearchPointLogic* pAutoSearch = (CAutoSearchPointLogic *)pNPC->GetComponent(pType);
				if (pAutoSearch) {
					CStdStringU czNameNPC = pAutoSearch->get_LabelName();
					if (czNameNPC.Compare(u"Hậu Nhân Hề") == 0) {
						LOG_WRITE("Go to NPC.......................");
						pAutoSearch->OnTransmitPointClick();
						LoopNextSleep(1500);
						return TRUE;
					}
					//LOG_WRITE("%d -- pAutoSearch [%08X] -- NPC[%s]", i, pAutoSearch, _U2A(czNameNPC).c_str());
				}

			}
			return TRUE;	
		}
		m_bGoGuild = FALSE;
		g_pGameControl->CloseDialog();
		return TRUE;
	}
	return FALSE;
}

BOOL CGDaNgongCuong::IsNPCDialog()
{
	CDialogController *pIns = CDialogController::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("Close NPC Dialog................");
	pIns->OnOpt_1();
	pIns->AidButtonClick();
	return TRUE;
}

BOOL CGDaNgongCuong::IsUIJianMu()
{

	LOG_WRITE("m_iItem == %d", m_iItem);
	if (IsItemTips()) return TRUE;
	CUIJianMuXBPanel *pIns = CUIJianMuXBPanel::Instance();
	if (pIns) {
		if (!m_bSelected) {
			if (m_iItem == -1) m_iItem += 1;
			if (m_iItem >= 8) {
				BOOL bCanReward = pIns->get_bCanGetReward();
				if (bCanReward) {
					LOG_WRITE("Get Reward............................");
					m_bFinished = TRUE;
					pIns->OnClickReward();
					return TRUE;
				}

				m_bFinished = TRUE;
				return TRUE;
			}
			m_bSelected = TRUE;
			pIns->OnSelectItem(m_iItem);
			return TRUE;
		}

		if (m_bSelected) {
			//lay thong so
			CUIJianMuXBSlot *pSelectItem = pIns->get_selectSlot();
			m_czSelectItem = pIns->get_SelectName();
			BOOL bEnough = pSelectItem->get_BEnough();
			CUE_Transform *pItem = g_pGameControl->get_Transform((UINT)pSelectItem);
			CUE_Transform *pCount = pItem->GetChildByPath(u"KnapsackItem:Count");
			CStdStringU czCount = g_pGameControl->GetTextU(pCount);
			CStdStringU czsHasItemCount = czCount.Right(10);
			CStdStringU czTotaltemCount = czCount.Right(8);
			int iHasItemCount = atoi(_U2A(czsHasItemCount).c_str());
			int iTotalItemCount = atoi(_U2A(czTotaltemCount).c_str());
			m_iNeedItemCount = iTotalItemCount - iHasItemCount;
			LOG_WRITE("iHasItemCount[%d] --- iTotalItemCount[%d] -- NeedItemCount[%d]", iHasItemCount, iTotalItemCount, m_iNeedItemCount);
			
			
			CUE_Transform *pSprite = pItem->GetChildByName(u"Sprite");
			if (!g_pGameControl->IsShowTransform(pSprite)) {

				if (!bEnough) { 
					LOG_WRITE("Not Enough Item.................. %d", m_iItem);
					g_pGameControl->Clicked(pItem);
					return TRUE;
				}
				else {
					LOG_WRITE("Fill in Box....................");
					m_iItem = m_iItem + 1;
					m_bSelected = FALSE;
					pIns->OnClickFill();
				}
				return TRUE;
			}

			if (g_pGameControl->IsShowTransform(pSprite))  {
				LOG_WRITE("Filled....................");
				m_iItem = m_iItem + 1;
				m_bSelected = FALSE;
				return TRUE;
			}

			return TRUE;
		}

		return TRUE;
	}
	
	return FALSE;
}

BOOL CGDaNgongCuong::IsItemTips()
{
	CUE_Transform *p = g_pGameControl->m_pTipUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"item.itemtips");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			
			CUE_Transform *pNameItem = pWnd->GetChildByPath(u"Offset:TipsFolder:Offset TopLeft:TopFolder:InfoFolder:Name");
			CStdStringU czNameItem = g_pGameControl->GetTextU(pNameItem);
			if (czNameItem.Find(m_czSelectItem) < 0) {
				LOG_WRITE("Other Item..............");
				m_bSelected = FALSE;
				g_pGameControl->Tap(1,1);
				return TRUE;
			}

			CUE_Transform *pButtonList = pWnd->GetChildByPath(u"Offset:Offset:Source:Content:Grid1");
			int iAllChild = pButtonList->get_childCount();
			if (iAllChild != 0) {
				for (int i = 0; i < iAllChild; i++ ) {
					CUE_Transform *pButton = pButtonList->GetChild(i);
					CUE_Transform *pLabel = pButton->GetChildByPath(u"item_off:name");
					CStdStringU czULabel = g_pGameControl->GetTextU(pLabel);

					if (czULabel.Find(u"Thương Hội") >= 0) {
						LOG_WRITE("...............get in Guild................");
						g_pGameControl->Clicked(pButton);
						return TRUE;
					}

					if (czULabel.Compare(u"Cửa hàng hệ thống") == 0) {
						LOG_WRITE("...............get in Market................");
						g_pGameControl->Clicked(pButton);
						return TRUE;
					}

					if (czULabel.Find(u"Bày Bán") >= 0) {
						if (!g_pGame->m_OptionTab.bDNCBuyByGold) {
							LOG_WRITE("...............NOOOOOOOOOOOOO................");
							g_pGameControl->Tap(1,1);
							m_iItem += 1;
							m_bSelected = FALSE;
							return TRUE;
						}
						LOG_WRITE("...............get in Seller................");
						g_pGameControl->Clicked(pButton);
						return TRUE;
					}
				}
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGDaNgongCuong::IsShopWnd()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		
		if (IsBought()) return TRUE;

		CUE_Transform *pWnd = p->GetChildByName(u"shop.shoppingmall");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			CUE_Transform *pWndListItem = pWnd->GetChildByPath(u"Offset:TabContent:Stal_menuList(Clone):Content:Stal_main(Clone):offset:stal_text_list");
			if (!g_pGameControl->IsShowTransform(pWndListItem)) {
				LOG_WRITE("No item in Shop.................");
				m_iItem += 1;
				m_bSelected = FALSE;
				g_pGameControl->CloseDialog();
				return TRUE;
			}

			CUE_Transform *pListItem = pWndListItem->GetChildByPath(u"Shoplist:ShopPageRoot");
			if (g_pGameControl->IsShowTransform(pListItem)) {
				int iCount = pListItem->get_childCount();
				if (iCount == 0) {
					LOG_WRITE("No item in shop...");
					return FALSE;
				}

				int i = 0;
				for (i = 0; i < iCount; i++) {
					CUE_Transform *pItem = pListItem->GetChild(i);
					CUE_Transform *pOffset = pItem->GetChildByName(u"Offset");
					if (g_pGameControl->IsShowTransform(pOffset)) {
						CUE_Transform *pName = pOffset->GetChildByName(u"Name");
						CStdStringU czName = g_pGameControl->GetTextU(pName);
						if (czName != m_czSelectItem) {
							LOG_WRITE("Not Item %s -- %s", _U2A(czName).c_str(), _U2A(m_czSelectItem).c_str());
							setBuyData();
							//m_bSelected = FALSE;
							g_pGameControl->CloseDialog();
							return TRUE;
						}
	
						CUE_Transform *pCount = pOffset->GetChildByPath(u"Sprite:Count");
						CStdStringU czCount = g_pGameControl->GetTextU(pCount);
						int iMoney = atoi(_U2A(czCount).c_str());
						if (m_iMinMoney == 0 || iMoney < m_iMinMoney) {
							m_iMinMoney = iMoney;
							if (m_iMinMoney != 0) m_pSelectItem = pItem;
						}
					}
				}
				if (i == iCount) {
					LOG_WRITE("m_iMinMoney ======== %d, m_pSelectItem[%08X]", m_iMinMoney, m_pSelectItem);

					int iHasGoldCoin = g_pGameControl->get_GoldCoin();
					int iTotalGoldBuy = m_iMinMoney * m_iNeedItemCount;
					if (iHasGoldCoin < iTotalGoldBuy) {
						LOG_WRITE("Lower............................%d", iHasGoldCoin);
						setBuyData();
						return TRUE;
					}
			
					if (m_pSelectItem) {

						CUE_Transform *pSelect = m_pSelectItem->GetChildByPath(u"Offset:HightLight");
						if (!g_pGameControl->IsShowTransform(pSelect)) {
							LOG_WRITE("Select Item.......");
							g_pGameControl->Clicked(m_pSelectItem);
							return TRUE;
						}

						CUE_Transform *pBuy = pWnd->GetChildByPath(u"Offset:TabContent:Stal_menuList(Clone):Content:Stal_main(Clone):offset:btn:GouMai");
						LOG_WRITE("Buy Item...................");
						g_pGameControl->Clicked(pBuy);
						return TRUE;
					}


					return TRUE;
				}
				//LOG_WRITE("%d......................", i);
				
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGDaNgongCuong::IsStallBuyWnd()
{	
	if (IsBought()) return TRUE;

	CStallMultiBuyConfirm *pIns = CStallMultiBuyConfirm::Instance();
	if (pIns) {
		m_pSelectItem = NULL;
		m_iMinMoney = 0;
		CStdStringU czName = pIns->get_ItemName();
		if (czName.Compare(m_czSelectItem) != 0 || m_iNeedItemCount <= 0) {
			LOG_WRITE("Not Item Or m_iNeedItemCount = 0");
			m_bSelected = FALSE;
			g_pGameControl->CloseDialog();
			return TRUE;
		}

		if (checkOptionControl()) return TRUE;
		
		LOG_WRITE("StallBuyConfirm..................");
		m_bSelected = FALSE;
		m_bBought = TRUE;
		pIns->OnInputCountOver(m_iNeedItemCount);
		pIns->BuyItem();
		return TRUE;
	}
	return FALSE;
}

BOOL CGDaNgongCuong::IsSystemShopWindow()
{
	if (IsBought()) return TRUE;

	CSystemShopWindow *pIns = CSystemShopWindow::Instance();
	if (pIns) {
		if (m_iItem < 0) {
			m_bSelected = FALSE;
			LOG_WRITE("Close IsSystemShopWindow()........");
			g_pGameControl->CloseDialog();
			return TRUE;
		}
		m_bSelected = FALSE;
		m_bBought = TRUE;
		LOG_WRITE("Buy..................");
		pIns->Buy();
		return TRUE;
	}
	return FALSE;
}

BOOL CGDaNgongCuong::checkOptionControl()
{
	CStallMultiBuyConfirm *pIns = CStallMultiBuyConfirm::Instance();
	if (pIns) {
		int iNowMonney = pIns->get_NowMonney();
		int iTotalGoldBuy = iNowMonney * m_iNeedItemCount;
		LOG_WRITE("Lower............................%d", iNowMonney);
		if (g_pGame->m_OptionTab.iDNCAmountOf == 0) {
			if (iTotalGoldBuy > 100) {
				LOG_WRITE("Lower 100");
				setBuyData();
				//g_pGameControl->CloseDialog();
				return TRUE;
			}
		}
		if (g_pGame->m_OptionTab.iDNCAmountOf == 1) {
			if (iTotalGoldBuy > 200) {
				LOG_WRITE("Lower 200");
				setBuyData();
				//g_pGameControl->CloseDialog();
				return TRUE;
			}
		}
		if (g_pGame->m_OptionTab.iDNCAmountOf == 2) {
			if (iTotalGoldBuy > 300) {
				LOG_WRITE("Lower 300");
				setBuyData();
				//g_pGameControl->CloseDialog();
				return TRUE;
			}
		}
		if (g_pGame->m_OptionTab.iDNCAmountOf == 3) {
			if (iTotalGoldBuy > 400) {
				LOG_WRITE("Lower 400");
				setBuyData();
				//g_pGameControl->CloseDialog();
				return TRUE;
			}
		}
		if (g_pGame->m_OptionTab.iDNCAmountOf == 4) {
			if (iTotalGoldBuy > 500) {
				LOG_WRITE("Lower 500");
				setBuyData();
				//g_pGameControl->CloseDialog();
				return TRUE;
			}
		}

		if (g_pGame->m_OptionTab.iDNCAmountOf == 5) {
			if (iTotalGoldBuy > 1000) {
				LOG_WRITE("Lower 1000");
				setBuyData();
				//g_pGameControl->CloseDialog();
				return TRUE;
			}
		}

		if (g_pGame->m_OptionTab.iDNCAmountOf == 6) {
			if (iTotalGoldBuy > 2000) {
				LOG_WRITE("Lower 2000");
				setBuyData();
				//g_pGameControl->CloseDialog();
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CGDaNgongCuong::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return FinishedActivity();
		return TRUE;
	}
	return FALSE;
}

BOOL CGDaNgongCuong::IsFirmBuy()
{
	if (IsBought()) return TRUE;

	CFirmBuy *pIns = CFirmBuy::Instance();
	if (pIns) {

		if (m_czSelectItem.Compare(u"") == 0) {
			m_bSelected = FALSE;
			LOG_WRITE("CGDaNgongCuong::IsFirmBuy()............. NOT .m_czSelectItem");
			g_pGameControl->CloseDialog();
			return TRUE;
		}

		LOG_WRITE("Buy...............");
		pIns->OnInputCountOver(m_iNeedItemCount);
		pIns->ConfirmBuy();
		m_bSelected = FALSE;
		m_bBought = TRUE;
		return TRUE;
	}
	return FALSE;
}

void CGDaNgongCuong::Activate()
{
	m_nStatus = ACTIVE;

	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
	AddSubGoal(new CGTaskCleanBag());
	//AddSubGoal(new CGTaskCleanBag1());
}

void CGDaNgongCuong::setBuyData()
{
	LOG_WRITE("CGDaNgongCuong::setBuyData()...................");
	m_iItem += 1;
	m_iMinMoney = 0;
	m_pSelectItem = NULL;
	m_bSelected = FALSE;
	m_bBought = TRUE;
}

BOOL CGDaNgongCuong::IsBought()
{
	if (m_bBought) {
		m_bBought = FALSE;
		LOG_WRITE("CGDaNgongCuong::IsFirmBuy()..............");
		CShoppingMallController *pshoping = CShoppingMallController::Instance();
		if (pshoping) {
			LOG_WRITE("Close pshoping");
			pshoping->Close();
			return TRUE;
		}

		g_pGameControl->CloseDialog();
		return TRUE;
	}
	return FALSE;
}



