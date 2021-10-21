#include "main.h"
#include "GTaskBuyPatch.h"
#include "GSleep.h"

CGTaskBuyPatch::CGTaskBuyPatch() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskTaskBuyPatch()");
	m_iRealNumber = 0;
	m_iMinPrice = 100000;
	m_iPositionPrice = -1;
	m_iBuyPlace = 0;
	m_bFinished = FALSE;
	m_bHPLack = FALSE;
	m_bMPLack = FALSE;
	m_bBought = FALSE;
	m_bNotHpPatch = FALSE;
	m_bNotMpPacth = FALSE;
	m_bSelectedFood = FALSE;
	m_czNameTemp = u"No name";
}

CGTaskBuyPatch::~CGTaskBuyPatch()
{
	LOG_WRITE("DEL - CGTaskTaskBuyPatch()");
	g_pGame->m_iCurrentID = -1;
}

int CGTaskBuyPatch::Process()
{

	g_pGameControl->SetCurrentID(101);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("CGTaskTaskBuyPatch::Process()");

	m_bMPLack = CChatFrameController::IsbMPLack();
	m_bHPLack = CChatFrameController::IsbHPLack();
	m_bNotMpPacth = CChatFrameController::IsbMPEmpty();
	m_bNotHpPatch = CChatFrameController::IsbHPEmpty();

	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) {
			g_pGameControl->CloseDialog();
			return LoopNextSleep();
		}
		else return Finished();
		return m_nStatus;
	}
	if (IsFinished()) return m_nStatus;
	get_PatchNameByLevel();
	if (IsPopup_Goumai()) return LoopNextSleep();
	if (IsShopWnd()) return LoopNextSleep();
	if (IsRoleviewReserve()) return LoopNextSleep();
	if (IsLackMana()) return LoopNextSleep();

	return m_nStatus;
}

int CGTaskBuyPatch::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);
	return LoopNext();
}

BOOL CGTaskBuyPatch::IsFinished()
{	
	if (!g_pGame->m_OptionTab.bAutoBuyPatch && !g_pGame->m_OptionTab.bAutoBuyPatch2) {
		m_bFinished = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL CGTaskBuyPatch::IsLackMana()
{

	BOOL bMPEmpty = CChatFrameController::IsbMPEmpty();
	BOOL bMPLack = CChatFrameController::IsbMPLack();

	BOOL bHPEmpty = CChatFrameController::IsbHPEmpty();
	BOOL bHPLack = CChatFrameController::IsbHPLack();

	if (!bHPLack && !bMPEmpty && !bHPEmpty && !bMPLack) {
		m_bFinished = TRUE;
		return TRUE;
	}
	
	if (g_pGameControl->IsShowPopUI()) {
		g_pGameControl->CloseDialog();
		return TRUE;
	}

	if (g_pGame->m_OptionTab.bAutoBuyPatch2 || g_pGame->m_OptionTab.bAutoBuyPatch) {
		g_pGameControl->OnClickButtonManaLack();
	}
	return TRUE;
}

BOOL CGTaskBuyPatch::IsRoleviewReserve()
{
	OPTIONTAB *pTab = &g_pGame->m_OptionTab;
	BOOL bTradePriority = pTab->bTradePriority;
	if (!g_pGameControl->IsShowTransform(g_pGameControl->m_pTipUIRoot)) return FALSE;
	
	CUE_Transform *pWnd = g_pGameControl->m_pTipUIRoot->GetChildByName(u"roleview.reserve");
	if (g_pGameControl->IsShowTransform(pWnd) ) {
		
		CUE_Transform *pFoodTips = pWnd->GetChildByPath(u"Offset:TipsRoot:FoodTips(Clone)");
		if (g_pGameControl->IsShowTransform(pFoodTips)) {
			// danh sach thuoc co the mua
			CUE_Transform *pListItemBuy = pFoodTips->GetChildByPath(u"offset:Scroll View:Grid");
			if (pListItemBuy) {
				int iItemBuyCount = pListItemBuy->get_childCount();
				if (iItemBuyCount != 0) {
					for (int i = 0; i < iItemBuyCount; i++) {
						CUE_Transform *pItem = pListItemBuy->GetChild(i);
						if (pItem) {
							CUE_Transform *pName = pItem->GetChildByName(u"lbl_name");
							CStdStringU czName = g_pGameControl->GetTextU(pName);
							LOG_WRITE("%d - name: %s", i, _U2A(czName).c_str());
							if (czName.Find(m_czNameTemp) == 0) {
								CUE_Transform *pSelected = pItem->GetChildByName(u"ItemBg");
								if (!g_pGameControl->IsShowTransform(pSelected)) {
									LOG_WRITE("Can buy %s -- %s", _U2A(czName).c_str(), _U2A(m_czNameTemp).c_str());
									CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","RecoveryFoodItem");
									CRecoveryFoodItem* pShiJiao = (CRecoveryFoodItem *)pItem->GetComponent(pType); 
									if (pShiJiao) pShiJiao->OnClickitemResource();
									return TRUE;
								}
								else {
									//danh sach nơi có thể mua
									CUE_Transform *pSource = pFoodTips->GetChildByName(u"Source");
									if (!g_pGameControl->IsShowTransform(pSource)) {
										g_pGameControl->Clicked(pItem->GetChildByPath(u"food:item"));
										return TRUE;
									}
									if (g_pGameControl->IsShowTransform(pSource)) {
										CUE_Transform *pSourceList = pSource->GetChildByPath(u"Content:Grid1");
										if (pSourceList) {
											int iSourceCount = pSourceList->get_childCount();
											if (iSourceCount != 0) {
												int i = 0;
												for (i = 0; i < iSourceCount; i++) {
													CUE_Transform *pSourceItem = pSourceList->GetChild(i);
													CUE_Transform *pName = pSourceItem->GetChildByPath(u"item_off:name");
													CStdStringU czNameSource = g_pGameControl->GetTextU(pName);
													
													if (!bTradePriority) {
														if (m_iBuyPlace == 0 && czNameSource.Find(u"Cửa hàng hệ thống") >= 0) {//
															LOG_WRITE("Clicked %s %s", _U2A(czNameSource).c_str(), _U2A(czName).c_str());
															m_iBuyPlace = 0;
															g_pGameControl->Clicked(pSourceItem);
															return TRUE;
														}

														if (m_iBuyPlace == 1 && czNameSource.Find(u"Bày Bán") >= 0) {//Cửa hàng hệ thống
															LOG_WRITE("Clicked %s", _U2A(czNameSource).c_str());
															m_iBuyPlace = 0;
															g_pGameControl->Clicked(pSourceItem);
															return TRUE;
														}
													}

													if (bTradePriority) {
														LOG_WRITE("Priority Trade is set.....");
														if (m_iBuyPlace == 0 && czNameSource.Find(u"Bày Bán") >= 0) {//
															LOG_WRITE("Clicked %s %s", _U2A(czNameSource).c_str(), _U2A(czName).c_str());
															m_iBuyPlace = 0;
															g_pGameControl->Clicked(pSourceItem);
															return TRUE;
														}

														if (m_iBuyPlace == 1 && czNameSource.Find(u"Cửa hàng hệ thống") >= 0) {//Cửa hàng hệ thống
															LOG_WRITE("Clicked %s", _U2A(czNameSource).c_str());
															m_iBuyPlace = 0;
															g_pGameControl->Clicked(pSourceItem);
															return TRUE;
														}
													}
												}

												if (i >= iSourceCount) {
													if (m_iBuyPlace <= 0 && !bTradePriority) {LOG_WRITE("không tìm thấy cửa hàng hệ thống"); m_iBuyPlace = 1;}
													if (m_iBuyPlace <= 0 && bTradePriority) {LOG_WRITE("không tìm thấy bay ban"); m_iBuyPlace = 1;}
												}
											}
										}
										return TRUE;
									} //if (g_pGameControl->IsShowTransform(pSource)) {
									return TRUE;
								}
								return TRUE;
							}
						}
					}
				}
			}
		}


		//list mp, hp có đã trang bị
		CUE_Transform *pHPGrid = pWnd->GetChildByPath(u"Offset:Food:Scroll View:ReserveInfo01:ItemList:Grid");
		CUE_Transform *pMPGrid = pWnd->GetChildByPath(u"Offset:Food:Scroll View:ReserveInfo02:ItemList:Grid");
		if (m_bNotMpPacth) {
			if (g_pGameControl->IsBagFull()) {
				m_bFinished = TRUE;
				return TRUE;
			}
			OnClickFood(pMPGrid);
			return TRUE;
		}

		else if (m_bNotHpPatch) {
			if (g_pGameControl->IsBagFull()) {
				m_bFinished = TRUE;
				return TRUE;
			}
			OnClickFood(pHPGrid);
			return TRUE;
		}

		else if (m_bMPLack) { 
			OnClickFood(pMPGrid);
			return TRUE;
		}

		else if (m_bHPLack) {
			OnClickFood(pHPGrid);
			return TRUE;
		}  

		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskBuyPatch::OnClickFood( CUE_Transform *pParent )
{
	int iItemMPCount = pParent->get_childCount();
	if (iItemMPCount != 0) {
		//ko co thi chon item dau tien

		//thieu thi duyet
		for (int i = 0; i < iItemMPCount; i++) {
			CUE_Transform*	pItem = pParent->GetChild(i);
			CSYS_Type*		pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem");
			CKnapsackItem*	pKnapsack = (CKnapsackItem *)pItem->GetComponent(pType);
			CGameItem*		pGameItem = pKnapsack->GetGameItem();
			if (pGameItem) {
				CStdStringU czNameItem = pGameItem->GetName();
				if (czNameItem.Compare(u"") != 0) m_czNameTemp = czNameItem;

				LOG_WRITE("Clicked Item aa%s %s", _U2A(czNameItem).c_str(), _U2A(m_czNameTemp).c_str());
				m_bSelectedFood = TRUE;
				pKnapsack->OnItemClick();
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CGTaskBuyPatch::IsShopWnd()
{
	CUE_Transform *pShop = g_pGameControl->m_pPopUIRoot->GetChildByName(u"shop.shoppingmall");

	if (g_pGameControl->IsShowTransform(pShop)) {
		if (IsSystemShopWindow()) return TRUE;
		if (IsStallMenu()) return TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskBuyPatch::IsSystemShopWindow()
{
	CSystemShopWindow *pIns = CSystemShopWindow::Instance();
	if (pIns) {
		if (IsBought()) return TRUE;

		CSystemShopWindow *pIns = CSystemShopWindow::Instance();
		if (pIns) {
			CStdStringU czCurNameItemSelected = pIns->LabelItemName();
			if (czCurNameItemSelected.Find(m_czNameTemp) >= 0) {
				LOG_WRITE("Item is Selected...");

				CStdStringU czNumText = pIns->get_InputNumber();
				int iNumText = atoi(_U2A(czNumText).c_str());

				int iUserInput = 0;
				if (m_bHPLack || m_bNotHpPatch) {
					iUserInput = g_pGame->m_OptionTab.iAmountOfPatchHP;
					LOG_WRITE("iUserInput HP %d", iUserInput);
					ConvertNumber(iUserInput);
				} 

				if (m_bMPLack || m_bNotMpPacth) {
					iUserInput = g_pGame->m_OptionTab.iAmountOfPatchMP;
					LOG_WRITE("iUserInput MP %d", iUserInput);
					ConvertNumber(iUserInput);
				}

				LOG_WRITE("Input .................%d, %d", m_iRealNumber, iUserInput);
				pIns->OnItemNumChoose(m_iRealNumber);
				if (m_iRealNumber >= iNumText) {
					LOG_WRITE("Buy..................");
					m_bBought = TRUE;
					pIns->Buy();
				}
				return TRUE;
			}

			CSystemShopWindow *pCurPage = pIns->m_curShowPage();
			if (pCurPage) {
				CUE_Transform *pTransformCurPage = g_pGameControl->get_Transform((UINT)pCurPage);
				if (pTransformCurPage) {
					int iCount = pTransformCurPage->get_childCount();
					for (int i = 0; i < iCount; i++) {
						CUE_Transform *pItem = pTransformCurPage->GetChild(i);
						if (g_pGameControl->IsShowTransform(pItem)) {
							CUE_Transform *pNameItem = pItem->GetChildByPath(u"Offset:LabelFram:BackGround:Name");
							CStdStringU czNameItem = g_pGameControl->GetTextU(pNameItem);
							if (czNameItem.Find(m_czNameTemp) >= 0) {
								LOG_WRITE("Clicked Item .....");
								g_pGameControl->Clicked(pItem);
								return TRUE;
							}
						}
					}
				}
			}
		}
		g_pGameControl->CloseDialog();

		return TRUE;
	}
	return FALSE;
}

void CGTaskBuyPatch::ConvertNumber( int iSource )
{
	if (iSource == 0) m_iRealNumber = 100;//60;
	if (iSource == 1) m_iRealNumber = 200;
	if (iSource == 2) m_iRealNumber = 300;
	if (iSource == 3) m_iRealNumber = 400;
	if (iSource == 4) m_iRealNumber = 500;
	if (iSource == 5) m_iRealNumber = 600;
	if (iSource == 6) m_iRealNumber = 700;
	if (iSource == 7) m_iRealNumber = 800;
	if (iSource == 8) m_iRealNumber = 900;
	if (iSource == 9) m_iRealNumber = 50;
}

BOOL CGTaskBuyPatch::IsBought()
{	
	if (m_czNameTemp.Compare(u"") == 0) {
		LOG_WRITE("Item not found");
		g_pGameControl->CloseDialog();
		return TRUE;
	}
	if (m_bBought) {
		LOG_WRITE("Item is Bought....");
		m_bFinished = TRUE;
		g_pGameControl->CloseDialog();
		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskBuyPatch::IsStallMenu()
{	
	CUE_Transform *pShop = g_pGameControl->m_pPopUIRoot->GetChildByName(u"shop.shoppingmall");

	if (IsBought()) return TRUE;
	CUE_Transform *pWndListItem = pShop->GetChildByPath(u"Offset:TabContent:Stal_menuList(Clone):Content:Stal_main(Clone):offset:stal_text_list");
	if (!g_pGameControl->IsShowTransform(pWndListItem)) {
		LOG_WRITE("No item in Shop.................");
		//g_pGameControl->CloseDialog();
		return TRUE;
	}

	CUE_Transform *pListItem = pWndListItem->GetChildByPath(u"Shoplist:ShopPageRoot");
	if (g_pGameControl->IsShowTransform(pListItem)) {
		int iCount = pListItem->get_childCount();
		if (iCount == 0) {
			LOG_WRITE("No item in shop...");
			//m_bFinished = TRUE;
			return TRUE;
		}

		
		CUE_Transform *pItem = pListItem->GetChild(0);
		CUE_Transform *pOffset = pItem->GetChildByName(u"Offset");
		if (g_pGameControl->IsShowTransform(pOffset)) {
			CUE_Transform *pName = pOffset->GetChildByName(u"Name");
			CStdStringU czName = g_pGameControl->GetTextU(pName);
			if (czName.Find(m_czNameTemp) < 0 ) {
				LOG_WRITE("Not Item %s -- %s", _U2A(czName).c_str(), _U2A(m_czNameTemp).c_str());
				g_pGameControl->CloseDialog();
				return TRUE;
			}

			CUE_Transform *pSelect = pItem->GetChildByPath(u"Offset:HightLight");
			if (!g_pGameControl->IsShowTransform(pSelect)) {
				LOG_WRITE("Select Item.......");
				g_pGameControl->Clicked(pItem);
				return TRUE;
			}

			CUE_Transform *pBuy = pShop->GetChildByPath(u"Offset:TabContent:Stal_menuList(Clone):Content:Stal_main(Clone):offset:btn:GouMai");
			LOG_WRITE("Buy Item...................");
			g_pGameControl->Clicked(pBuy);
			return TRUE;

		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskBuyPatch::IsPopup_Goumai()
{
	CStallMultiBuyConfirm *pIns = CStallMultiBuyConfirm::Instance();
	if (pIns) {

		if (IsBought()) return TRUE;

		if (m_czNameTemp.Compare(u"") == 0) {
			LOG_WRITE("Item not found");
			g_pGameControl->CloseDialog();
			return TRUE;
		}

		CSYS_List *pListPrice = pIns->get_ListPrice();
		int iListPriceCount = pListPrice->get_Count();
		if (iListPriceCount != 0) {
			for (int i = 0; i < iListPriceCount; i++) {
				int iPrice = (int)pListPrice->get_Item(i);
				if (iPrice != 0 && iPrice < m_iMinPrice) {
					m_iMinPrice = iPrice;
					m_iPositionPrice = i;
				}
			}
		}
		
		CStdStringU czNumText = pIns->get_NumText();
		int iNumText = atoi(_U2A(czNumText).c_str());

		if (m_iMinPrice != 0 && m_iPositionPrice != -1) {
			CSYS_List *pListCount = pIns->get_ListCount();
			int iListCount = pListCount->get_Count();
			if (iListCount != 0) {
				int iNumber = (int)pListCount->get_Item(m_iPositionPrice);
				LOG_WRITE("iNumber == %d", iNumber);
				int iUserInput = 0;
				if (m_bHPLack || m_bNotHpPatch) {
					iUserInput = g_pGame->m_OptionTab.iAmountOfPatchHP;
					ConvertNumber(iUserInput);
				} 

				if (m_bMPLack || m_bNotMpPacth) {
					iUserInput = g_pGame->m_OptionTab.iAmountOfPatchMP;
					ConvertNumber(iUserInput);
				}
				LOG_WRITE("Input .................%d", m_iRealNumber);
				
				if (iNumber >= m_iRealNumber) {
					pIns->OnInputCountOver(m_iRealNumber);
					
					if (m_iRealNumber == iNumText) {
						m_bBought = TRUE;
						LOG_WRITE("Buy iNumber >= m_iRealNumber");
						pIns->BuyItem();
					}
					return TRUE;
				}

				if (iNumber < m_iRealNumber) {
					pIns->OnInputCountOver(iNumber);
					if (iNumber == iNumText) {
						m_bBought = TRUE;
						LOG_WRITE("Buy iNumber < m_iRealNumber");
						pIns->BuyItem();
					}
					return TRUE;
				}	
			}
		}
		return TRUE;
	}
	/*CUE_Transform *pFloatUIRoot = g_pGameControl->m_pFloatUIRoot;
	if (!g_pGameControl->IsShowTransform(pFloatUIRoot)) return FALSE;
	CUE_Transform *pWnd = pFloatUIRoot->GetChildByName(u"shop.stall.stal_popup_goumai");
	if (g_pGameControl->IsShowTransform(pWnd)) {
		LOG_WRITE("Yessssss");
		return TRUE;
	}*/
	return FALSE;
}

void CGTaskBuyPatch::get_PatchNameByLevel()
{


	if (CChatFrameController::IsbMPEmpty()) {
		if (g_pGame->m_OptionTab.iMPLevel == 0) m_czNameTemp = u"Tôm Xào";
		if (g_pGame->m_OptionTab.iMPLevel == 1) m_czNameTemp = u"Thịt Nướng";
		if (g_pGame->m_OptionTab.iMPLevel == 2) m_czNameTemp = u"Cháo Lươn";
		if (g_pGame->m_OptionTab.iMPLevel == 3) m_czNameTemp = u"Canh Ba Ba";
		if (g_pGame->m_OptionTab.iMPLevel == 4) m_czNameTemp = u"Sò Điệp";
		if (g_pGame->m_OptionTab.iMPLevel == 5) m_czNameTemp = u"Tiên Ngư";
		if (g_pGame->m_OptionTab.iMPLevel == 6) m_czNameTemp = u"Ghẹ";
		LOG_WRITE("set MP pacth[%s]", _U2A(m_czNameTemp).c_str());
	} 
	else if (CChatFrameController::IsbHPEmpty()) {
		if (g_pGame->m_OptionTab.iHPLevel == 0) m_czNameTemp = u"Thanh Thảo Lộ";
		if (g_pGame->m_OptionTab.iHPLevel == 1) m_czNameTemp = u"Thanh Lương";
		if (g_pGame->m_OptionTab.iHPLevel == 2) m_czNameTemp = u"Nước Ép";
		if (g_pGame->m_OptionTab.iHPLevel == 3) m_czNameTemp = u"Canh Rau Củ";
		if (g_pGame->m_OptionTab.iHPLevel == 4) m_czNameTemp = u"Rau Quả";
		if (g_pGame->m_OptionTab.iHPLevel == 5) m_czNameTemp = u"Rượu Ngon";
		if (g_pGame->m_OptionTab.iHPLevel == 6) m_czNameTemp = u"Canh Bát";
		LOG_WRITE("set HP pacth[%s]", _U2A(m_czNameTemp).c_str());
	} 
}
