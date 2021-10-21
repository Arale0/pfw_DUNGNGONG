#include "main.h"
#include "GTaskCleanBag.h"
#include "GSleep.h"
#include "GTaskChangeScene.h"

CGTaskCleanBag::CGTaskCleanBag() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskTaskCleanBag()");
	m_bFinished = FALSE;
	m_bDeposeEquip = FALSE;
	m_iTypeCleanBag = 0;
	m_iCurrentIndex = 0;
	m_bFull = FALSE;
	m_bBought = FALSE;
	m_bSplitEquip = FALSE;
	m_bSortItem = FALSE;
	m_czTempItem = u"None";
}

CGTaskCleanBag::~CGTaskCleanBag()
{
	LOG_WRITE("DEL - CGTaskTaskCleanBag()");
	g_pGame->m_iCurrentID = -1;
}

int CGTaskCleanBag::Process()
{

	g_pGameControl->SetCurrentID(103);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("CGTaskTaskCleanBag::Process() %d", m_iTypeCleanBag);

	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) {
			g_pGameControl->CloseDialog();
			return LoopNextSleep();
		}

		else return Finished();
		return m_nStatus;
	}

	int iHour	= g_pGameControl->getTime(0);
	int iMinute = g_pGameControl->getTime(1);
	if (iHour >= 12) {
		if (iMinute >= 28 && iMinute < 30) {
			m_bFinished = TRUE; 
			return LoopNextSleep();
		}

		if (iMinute >= 58) {
			m_bFinished = TRUE; 
			return LoopNextSleep();
		}
	}

	if (g_pGame->m_OptionTab.bBagChangeMapYuanLing) {
		int iCurActivity = g_pGame->m_iCurrentActivity;
		if (iCurActivity == (int)act_trucdietaclinh) {
			if (g_pGame->m_OptionTab.bTDALTimeGotoBoss) {
				//AddSubGoal(new CGTaskChangeScene(SCENEID_BENTAMMONG));
				processIfYuanLingIsCheck(iHour, iMinute);
			}
		}
	}


	if (g_pGameControl->IsCenterNotice(u"Nguyên Thần đã")) m_bFull = TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Cần đến bản đồ chỉ định ", MSG_OK)) return LoopNextSleep(500);

	if (g_pGameControl->IsNoticeWnd()) return Finished();

	if (g_pGameControl->IsLowerLevelWnd()) return LoopNextSleep();

	if (fairy_settlement()) return LoopNextSleep();

	if (IsCopyFinishedFubenWnd()) return Finished();

	if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep(500);
	
	if (IsFinished()) return m_nStatus;

	//if (g_pGameControl->ProcessMessageBox(u"Đồng ý ", MSG_OK)) return m_nStatus;

	//if (g_pGameControl->ProcessMessageBox(u"Sau khi mặc,", MSG_OK)) return m_nStatus;
	//
	//if (g_pGameControl->ProcessMessageBox(u"Sau khi dùng,", MSG_OK)) return m_nStatus;

	//if (g_pGameControl->ProcessMessageBox(u"Trang bị này có thể", MSG_OK)) return m_nStatus;

	if (g_pGameControl->ProcessMessageBox(u"mời bạn vào đội,", MSG_CANCEL)) return LoopNextSleep(500);

	if (IsItemPromt()) return m_nStatus;

	if (IsSellWnd()) return LoopNextSleep(500);

	if (IsEquipsTips())     return LoopNextSleep();

	if (IsTaskCleanBagWnd()) return LoopNextSleep(1000);

	ShowTaskCleanBagWnd();
	return m_nStatus;
}

int CGTaskCleanBag::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);
	return LoopNext();
}

void CGTaskCleanBag::ShowTaskCleanBagWnd()
{
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) {return; }
	if (g_pGameControl->IsShowPopUI()) {g_pGameControl->CloseDialog(); return;}
	LOG_WRITE("CGTaskTaskCleanBag::OnClickCleanBag()....");
	pInstance->OnClickBackPack();
	LoopNextSleep();

}

BOOL CGTaskCleanBag::IsTaskCleanBagWnd()
{

	if (IsNumericKeyBoard()) return TRUE;
	if (IsItemTips())		 return TRUE;
	CUE_Transform *p = NULL;
	if (!g_pGameControl->IsShowTransformKnapsack()) return FALSE;
	LOG_WRITE("IsTaskCleanBagWnd() 3");
	CKnapsackWindow *pIns = CKnapsackWindow::Instance();
	if (pIns) {
		
		m_bBought = FALSE;
		if (!m_bSortItem) {
			LOG_WRITE("Sort backpack first........");
			m_bSortItem = TRUE;
			pIns->OnClickNeaten();
			return TRUE;
		}
		if (IsDeposeBag(p)) return TRUE;

		int iFilterType = pIns->m_FilterType();
		if (iFilterType != 6 && !m_bSplitEquip) {
			SelectOtherTab(pIns);
			return TRUE;
		}

		if (iFilterType != 1 && m_bSplitEquip) {
			SelectOtherTab(pIns);
			return TRUE;
		}
		ProcessCleanBag(pIns);
		return TRUE;
	}

	return FALSE;
}

BOOL CGTaskCleanBag::IsFinished()
{
	
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

	return FALSE;
}

BOOL CGTaskCleanBag::IsDeposeBag(CUE_Transform *p)
{
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pWnd = pPopUIRoot->GetChildByName(u"Knapsack");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			if (g_pGame->m_OptionTab.bDeBlue   ||
				g_pGame->m_OptionTab.bDeViolet ||
				g_pGame->m_OptionTab.bDeWhite) {
					CKnapsackWindow *pIns = CKnapsackWindow::Instance();
					if (!pIns) return FALSE;
					CUE_Transform *pDecompose = pWnd->GetChildByPath(u"Offset:KnapsackClient:Appearance:Decompose");
					if (!m_bDeposeEquip) {
						if (g_pGameControl->IsShowTransform(pDecompose)) {
							if (g_pGame->m_OptionTab.bDeWhite) g_pGameControl->Clicked(pDecompose->GetChildByPath(u"Offset:Frame:Btn_DeWhite"));
							if (g_pGame->m_OptionTab.bDeBlue) g_pGameControl->Clicked(pDecompose->GetChildByPath(u"Offset:Frame:Btn_DeBlue"));
							if (g_pGame->m_OptionTab.bDeViolet) g_pGameControl->Clicked(pDecompose->GetChildByPath(u"Offset:Frame:Btn_DePurple"));
							m_bDeposeEquip = TRUE;
							return TRUE;
						}
						pIns->OnClickOpenDecompose();
						return TRUE;
					}

					if (g_pGameControl->IsShowTransform(pDecompose)) {
						g_pGameControl->Clicked(pDecompose->GetChildByPath(u"Offset:Frame:btn_close"));
						return TRUE;
					}
			}
			m_bDeposeEquip = TRUE;
		}
	}
	
	return FALSE;
}


BOOL CGTaskCleanBag::IsItemTips()
{
	CUE_Transform *p = g_pGameControl->m_pTipUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"item.itemtips");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			CUE_Transform *pName = pWnd->GetChildByPath(u"Offset:TipsFolder:Offset TopLeft:TopFolder:InfoFolder:Name");
			CStdStringU czUName = g_pGameControl->GetTextU(pName);
			CUE_Transform *pButtonList = pWnd->GetChildByPath(u"Offset:TipsFolder:Offset Bottom:Button List:Grid");
			int iAllChild = pButtonList->get_childCount();

			if (iAllChild != 0) {
				for (int i = 0; i < iAllChild; i++ ) {
					CUE_Transform *pButton = pButtonList->GetChild(i);
					CUE_Transform *pLabel = pButton->GetChildByPath(u"Offset:Button:Label");
					CStdStringU czULabel = g_pGameControl->GetTextU(pLabel);
					
					if (m_iTypeCleanBag == 2 && czULabel.Find(u"Thương Hội") >= 0) {
						m_iTypeCleanBag = 0;
						m_czTempItem = u"None";
						LOG_WRITE("...............SELL THuong Hoi................");
						g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
						return TRUE;
					}
				
					if (m_iTypeCleanBag == 1 && czULabel.Compare(u"Dùng") == 0) {
						
						if (czUName.Find(u"Tàng Bảo Đồ") >= 0) {
							g_pGameControl->Tap(1,1);
							return TRUE;
						}
						
						m_iTypeCleanBag = 0;
						m_czTempItem = u"None";
						LOG_WRITE("...............USE................");
						g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
						return TRUE;
					}

					if (m_iTypeCleanBag == 3 && czULabel.Compare(u"Bán") == 0) {

						LOG_WRITE("...............BAN................");
						m_czTempItem = u"None";
						g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
						return TRUE;
					}

					g_pGameControl->Tap(1,1);
				}
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGTaskCleanBag::IsNumericKeyBoard()
{
	CNumericKeyboardWindow *pIns = CNumericKeyboardWindow::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("IsNumericKeyBoard::Submit....................");
	pIns->OnMaxClick();
	pIns->OnClickSumbit();

	if (m_bFull) pIns->OnCloseUI();
	return TRUE;
}

BOOL CGTaskCleanBag::IsSellWnd()
{
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pWnd = pPopUIRoot->GetChildByName(u"shop.shoppingmall");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			if (!g_pGame->m_OptionTab.bBagSellStone && 
				!g_pGame->m_OptionTab.bBanBua		&& 
				!g_pGame->m_OptionTab.bBanDaAoTien	&& 
				!g_pGame->m_OptionTab.bBanDaCanKhon && 
				!g_pGame->m_OptionTab.bSell_DaThienCanh ) {
					m_bFinished = TRUE; 
					return TRUE;
			}
			CFirmSell *pFirmSell = CFirmSell::Instance();
			if (!pFirmSell) return FALSE;

			CSYS_List *pList = pFirmSell->m_Items();
			if (pList) {
				if (m_bBought) {
					LOG_WRITE("Close Shopping.....");
					CShoppingMallController *pshoping = CShoppingMallController::Instance();
					pshoping->Close();
					return TRUE;
				}

				int iAllChild = pList->get_Count();
				if (iAllChild == 0) {
					m_bBought = TRUE;
					return TRUE;
				}
				CGameItem *pCurItem = pFirmSell->GetGameItem();
				CStdStringU czUCurName = pCurItem->GetName();

				int i = 0;
				for (i = 0; i < iAllChild; i++) {
					CKnapsackItem* pKnapsackItem = (CKnapsackItem *)pList->get_Item(i);
					if (pKnapsackItem){
						CStdStringU czUCount = pKnapsackItem->get_Count();
						CStdStringU czNum = czUCount.Mid(11);
						int iCount = atoi(_U2A(czNum).c_str());

						CGameItem *pGameItem = pKnapsackItem->GetGameItem();
						CStdStringU czUName = pGameItem->GetName();
						CStdStringU czUClassName = pGameItem->GetTipsClassDesc();

						if (czUName == czUCurName) {
							if (iCount == 0) iCount = 1;
							LOG_WRITE("SOLD........");
							pFirmSell->OnInputCountOver(iCount);
							pFirmSell->DoSellClick();
							return TRUE;
						}

						if (g_pGame->m_OptionTab.bBagSellStone && czUClassName.Find(u"Đá Hồn") >= 0) {
							pKnapsackItem->OnItemClick();
							return TRUE;
						}

						if (g_pGame->m_OptionTab.bBanDaAoTien && czUClassName.Find(u"Nguyên liệu tinh luyện") >= 0) {
							pKnapsackItem->OnItemClick();
							return TRUE;
						}

						if (g_pGame->m_OptionTab.bBanBua && czUClassName.Find(u"Khắc") >= 0) {
							pKnapsackItem->OnItemClick();
							return TRUE;
						}

						if (czUClassName.Find(u"Nguyên liệu trang sức") >= 0) {
							pKnapsackItem->OnItemClick();
							return TRUE;
						}

						if (czUName.Find(u"Đá Thiên Canh") >= 0) {
							pKnapsackItem->OnItemClick();
							return TRUE;
						}

						if (g_pGame->m_OptionTab.bSell_BiQuyenCoDai && czUName.Find(u"Bí Quyển Cổ Đại") >= 0) {
							pKnapsackItem->OnItemClick();
							return TRUE;
						}

						//LOG_WRITE("czUClassName == %s, icount == %d", _U2A(czUClassName).c_str(), iCount);
					}
				}
				if ( i >= iAllChild) {
					m_bBought = TRUE;
					return TRUE;
				}
				return TRUE;
			}

		}
	}
	return FALSE;
}


int CGTaskCleanBag::get_ItemCount()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"Knapsack:Offset:KnapsackClient:Appearance:BackPack:ItemNum:lbl_num");
	if (!p) return -1;
	CStdStringU czNum = g_pGameControl->GetTextU(p);
	return atoi(_U2A(czNum).c_str());
}

BOOL CGTaskCleanBag::IsItemPromt()
{
	CUE_Transform *p = g_pGameControl->m_pMessageUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"item.prompt");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			LOG_WRITE("Close IsItemPromtWnd...............");
			g_pGameControl->Clicked(pWnd->GetChildByPath(u"Offset:CloseButton"));
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGTaskCleanBag::IsCopyFinishedFubenWnd()
{
	CCopySceneSettlementController *pInstance = CCopySceneSettlementController::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("IsCopyFinishedFubenWnd...............");
	return TRUE;
}

void CGTaskCleanBag::SelectOtherTab( CKnapsackWindow *pIns )
{
	if (!pIns) return;
	CSYS_List *pFilterList = pIns->m_FilterItemList();
	if (!pFilterList) return;
	int iCount = pFilterList->get_Count();
	if (iCount == 0) return;

	UINT uFilter = 0;
	if (!m_bSplitEquip) uFilter = (UINT)pFilterList->get_Item(4);
	if (m_bSplitEquip) uFilter = (UINT)pFilterList->get_Item(1);
	if (uFilter == 0) return;

	CUE_Transform *pTransform = g_pGameControl->get_Transform(uFilter);
	if (pTransform) {
		if (!m_bSplitEquip) {
			LOG_WRITE("CGTaskCleanBag::Click Other Btn.....");
			g_pGameControl->Clicked(pTransform->GetChildByName(u"other_off"));
		}

		if (m_bSplitEquip) {
			LOG_WRITE("CGTaskCleanBag::Click Equip Btn.....");
			g_pGameControl->Clicked(pTransform->GetChildByName(u"equip_off"));
		}
		return;
	}
}

void CGTaskCleanBag::ProcessCleanBag( CKnapsackWindow *pIns )
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return;
	CFairyPack *pFairy = pPlayerData->get_FairyPack();
	if (!pFairy) return;
	int iSizeFairyPack = CFairyPack::get_DefaultSize();
	int iCoutFairyPack = pFairy->GetFairyCount();
	
	if (!pIns) return;
	if (m_bSplitEquip) {
		ProcessEquipment(pIns);
		return;
	}

	CSYS_List *pKnapsackList = pIns->filterItemList();
	if (!pKnapsackList) return;
	int iCount  = pKnapsackList->get_Count();
	if (iCount == 0) {
		m_bFinished = TRUE;
		return;
	}
	int i = 0;
	for (i = m_iCurrentIndex; i < iCount; i++) {
			CGameItem *pGameItem = (CGameItem *)pKnapsackList->get_Item(i);
			if (pGameItem) {
				CStdStringU czUName = pGameItem->GetName();
				CStdStringU czUClassName = pGameItem->GetTipsClassDesc();
				int iQuality = pGameItem->GetQuality();
				int iLevel = pGameItem->GetEquipLevel();

				if (m_bSplitEquip) {
					LOG_WRITE("[%d] - Name: %s", iQuality, _U2A(czUName).c_str());
				}

				if (czUName.Compare(m_czTempItem) == 0) continue;

				/****************************USE*************************************/
				if (g_pGame->m_OptionTab.bUseFairyEgg) {
					if (czUName.Find(u"Trứng Tinh Linh") >= 0) {
						if (iCoutFairyPack < iSizeFairyPack) {
							SetValue();
							m_iTypeCleanBag = 1;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return;
						}
						else LOG_WRITE("Not enough Box to save this Fariy [%d] >= [%d]", iCoutFairyPack, iSizeFairyPack);
					}
				}
				
				if (g_pGame->m_OptionTab.bBagUseEquips) {
					if (czUClassName.Compare(u"Quà") == 0) {
						//LOG_WRITE("%s %s", _U2A(czUClassName).c_str(), _U2A(czUName).c_str());
						if (czUName.Find(u"Đạo cụ May Mắn") >= 0) {
							/*LOG_WRITE("Set ----------------------> m_iCurrentIndex = %d + 1", i);
							m_iCurrentIndex = i + 1;*/

							LOG_WRITE("Ban Dao Cu May Man Lien Tiep");
							SetValue();
							m_iTypeCleanBag = 3;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return;
						}
						else if (czUName.Find(u"Bổng Lộc Lãnh Thổ") >= 0) {
							LOG_WRITE("Set ----------------------> m_iCurrentIndex = %d + 1", i);
							m_iCurrentIndex = i + 1;
							return;
						}
						else if (czUName.Find(u"Quà Chọn Đá Hồn") >= 0) {
							LOG_WRITE("Set ----------------------> m_iCurrentIndex = %d + 1", i);
							m_iCurrentIndex = i + 1;
							return;
						}
						else if (czUName.Find(u"Hoa Đăng") >= 0) {
							LOG_WRITE("Set ----------------------> m_iCurrentIndex = %d + 1", i);
							m_iCurrentIndex = i + 1;
							return;
						}

						else if (czUName.Find(u"Cỏ May Mắn") >= 0) {
							LOG_WRITE("Set ----------------------> m_iCurrentIndex = %d + 1", i);
							m_iCurrentIndex = i + 1;
							return;
						}

						SetValue();
						m_iTypeCleanBag = 1;
						pIns->Click_Item_BelongBackPack(pGameItem);
						return;
					}

					if (IsItem(czUClassName, czUName)) {
						//LOG_WRITE("%s %s", _U2A(czUClassName).c_str(), _U2A(czUName).c_str());
						SetValue();
						m_iTypeCleanBag = 1;
						m_czTempItem = czUName;
						if (m_bSortItem) pIns->Click_Item_BelongBackPack(pGameItem);
						return;
					}
				}
			
				/****************************END USE*************************************/
				/****************************SELL*************************************/

				if (g_pGame->m_OptionTab.bBagSellStone && czUClassName.Find(u"Đá Hồn") >= 0) {
					SetValue();
					m_iTypeCleanBag = 2;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;
				}

				if (g_pGame->m_OptionTab.bBanDaAoTien && czUName.Find(u"Đá Ảo Tiên") >= 0) {
					SetValue();
					m_iTypeCleanBag = 2;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;	
				}

				if (g_pGame->m_OptionTab.bBanDaCanKhon && czUName.Compare(u"Đá Càn Khôn") == 0) {
					SetValue();		
					m_iTypeCleanBag = 2;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;	
				}

				if (g_pGame->m_OptionTab.bBanBua && czUClassName.Find(u"Khắc") >= 0) {
					SetValue();					
					m_iTypeCleanBag = 2;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;	
				}

				if (g_pGame->m_OptionTab.bSell_DaThienCanh && czUName.Find(u"Đá Thiên Canh") >= 0) {
					SetValue();					
					m_iTypeCleanBag = 2;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;	
				}

				if (g_pGame->m_OptionTab.bSell_BiQuyenCoDai && czUName.Find(u"Bí Quyển Cổ Đại") >= 0) {
					SetValue();					
					m_iTypeCleanBag = 2;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;	
				}

				if (g_pGame->m_OptionTab.bBanDaCanKhon && czUName.Compare(u"Đá Càn Khôn Bậc 2") == 0) {
					SetValue();		
					m_iTypeCleanBag = 3;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;	
				}

				if (g_pGame->m_OptionTab.bSellCertification && czUClassName.Find(u"Chứng Minh") >= 0) {	
					SetValue();
					m_iTypeCleanBag = 3;
					pIns->Click_Item_BelongBackPack(pGameItem);
					return ;	
				}
				
				if (g_pGame->m_OptionTab.bBanNgLieuCam59) {	
					if (czUName.Find(u"Bụi Ác Ma") >= 0 || 
						czUName.Find(u"Thất Diệu Xúc") >= 0 ||
						czUName.Find(u"Phong Vô Ngấn-Giáp Đen") >= 0) {
							SetValue();
							m_iTypeCleanBag = 3;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
					}	
				}

				if (g_pGame->m_OptionTab.bBanPhuLinh) {	
					if (czUClassName.Find(u"Phụ Linh") >= 0) {
						SetValue();
						m_iTypeCleanBag = 3;
						pIns->Click_Item_BelongBackPack(pGameItem);
						return ;
					}	
				}

				if (g_pGame->m_OptionTab.bBagSellSoul) {	
					if (czUClassName.Find(u"Tâm Phách") >= 0) {
						if (czUName.Find(u"Lv1") >= 0) {
							SetValue();
							m_iTypeCleanBag = 2;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
						}
						
					}	
				}

				if (g_pGame->m_OptionTab.bSellOther) {	
					if (czUName.Find(u"Cành Cây") >= 0 ||
						czUName.Find(u"Kẹo Ngọt") >= 0 ||
						czUName.Find(u"Bánh Xào") >= 0 ||
						czUName.Find(u"Xu Lễ Tạ Ơn") >= 0 ||
						czUName.Find(u"Cỏ May Mắn") >= 0 ||
						czUName.Find(u"Tình Yêu Cả Đời") >= 0||
						czUName.Find(u"Bùa May Mắn") >= 0) {
							SetValue();
							m_iTypeCleanBag = 3;
							m_czTempItem = czUName;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
					}	
				}
				/********************************END SELL******************/
				//nguyen lieu do cam
				//czUClassName.Find(u"Nguyên liệu đồ Cam")
			//}
		}
	}
	
	if (i >= iCount) {
		if (!m_bSplitEquip) {
			LOG_WRITE("Change to Equips TAB....");
			m_bSplitEquip = TRUE;
			return;
		}

		if (m_bSplitEquip) m_bFinished = TRUE; 
		return;
	}	
}

BOOL CGTaskCleanBag::IsItem( CStdStringU czUClassName, CStdStringU czUName )
{
	if (czUClassName.Compare(u"Đạo cụ Trang Sách") == 0) return TRUE;
	if (czUClassName.Compare(u"Nguyên Bảo") == 0)		 return TRUE;
	if (czUClassName.Compare(u"Vinh dự") == 0)			 return TRUE;
	if (czUClassName.Compare(u"Bạc") == 0)				 {return TRUE;}
	if (czUClassName.Compare(u"NB Khóa") == 0)			 return TRUE;
	if (czUClassName.Compare(u"Quà Khắc") == 0)			 return TRUE;
	if (czUClassName.Compare(u"Thời Trang") == 0)		 return TRUE;
	if (czUClassName.Compare(u"Thú Cưỡi") == 0)			 return TRUE;
	if (czUClassName.Compare(u"Thiết Bị Bay") == 0)		 return TRUE;
	if (czUClassName.Compare(u"Vũ Khí Thời Trang") == 0) return TRUE;
	//if (czUClassName.Compare(u"Anh Hồn 1 Sao") == 0) return TRUE;

	if (czUClassName.Find(u"Nguyên Thần Đơn")   >= 0 && !m_bFull) return TRUE;

	if (czUName.Find(u"Truyện")      >= 0)			return TRUE;
	if (czUName.Find(u"Ngân NB")     >= 0)			return TRUE;
	if (czUName.Find(u"Rương")       >= 0)			return TRUE;
	if (czUName.Find(u"Phong Tục")   >= 0 && czUName.Find(u"Sử Ký Hoàn Mỹ") < 0)			return TRUE;
	if (czUName.Find(u"Nguyên Thần") >= 0 && !m_bFull)			return TRUE;
	if (czUName.Find(u"Cống hiến cá nhân") >= 0 && g_pGameControl->IsHaveGuild())	return TRUE;

	if (czUName.Find(u"Hộp Lưu Vân") >= 0)			return TRUE;

	if (czUName.Find(u"Ấn Chương Hắc Ám") >= 0 && !g_pGameControl->IsLowerLevel(60)) return TRUE;

	if (g_pGame->m_OptionTab.bBagAnhHon) {
		if (czUName.Find(u"Mệ Tuyết Hồ") >= 0) return TRUE;
		if (czUName.Find(u"Lưu Hỏa Điệp") >= 0) return TRUE;
		if (czUName.Find(u"Nhạc Vương") >= 0) return TRUE;
		if (czUName.Find(u"Bàn Cổ") >= 0) return TRUE;
		if (czUName.Find(u"Ngọc Hưởng") >= 0) return TRUE;
		if (czUName.Find(u"Yến Sinh") >= 0) return TRUE;
		if (czUName.Find(u"Dực Phong") >= 0) return TRUE;
		if (czUName.Find(u"Dao Hoa") >= 0) return TRUE;
		if (czUName.Find(u"Thiên Diệp Giao Nhân") >= 0) return TRUE;
		if (czUName.Find(u"Tiểu Sảnh") >= 0) return TRUE;
		if (czUName.Find(u"Chim Loan Âm Thầm") >= 0) return TRUE;
		if (czUName.Find(u"Thanh Y Tử") >= 0) return TRUE;
	}
	
	return FALSE;
}

void CGTaskCleanBag::SetValue()
{
	LOG_WRITE("Da thay item --------------> m_iCurrentIndex = 0");
	m_iCurrentIndex = 0;
}

BOOL CGTaskCleanBag::fairy_settlement()
{
	CUE_Transform *pTipRoot = g_pGameControl->m_pTipUIRoot;
	if (!g_pGameControl->IsShowTransform(pTipRoot)) return FALSE;
	CUE_Transform *p = pTipRoot->GetChildByName(u"fairy.fairy_settlement");
	if (g_pGameControl->IsShowTransform(p)) {
		LOG_WRITE("Close........");
		g_pGameControl->Clicked(p->GetChildByPath(u"Offset:jiesuan:shengli:btn_statistic"));
		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskCleanBag::IsEquipsTips()
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

					if (czULabel.Find(u"Tách") >= 0 && m_iTypeCleanBag == 2) {
						LOG_WRITE("...............TACH................");
						g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
						//g_pGameControl->Tap(1,1);
						return TRUE;
			
					}

					if (czULabel.Find(u"Trang Bị") >= 0 && m_iTypeCleanBag == 1) {
						LOG_WRITE("...............EQUIPS................");
						g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
						//g_pGameControl->Tap(1,1);
						return TRUE;
					}

					g_pGameControl->Tap(1,1);
				}

				if (i >= iAllChild) {
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

void CGTaskCleanBag::ProcessEquipment( CKnapsackWindow *pIns )
{
	if (!pIns) return; 
	CSYS_List *pKnapsackList = pIns->get_KnapsackList();
	if (!pKnapsackList) return;
	int iCount  = pKnapsackList->get_Count();
	if (iCount == 0) {
		LOG_WRITE("ProcessEquipment....a");
		m_bFinished = TRUE; 
		return;
	}

	int i = 0;
	for (i = 0; i < iCount; i++) {
		CKnapsackItem *pItem = (CKnapsackItem *)pKnapsackList->get_Item(i);
		if (pItem) {
			CUISprite *pUp = pItem->m_Up();
			CUE_Transform *pUpTransform = pUp->get_TransformUIRect();
			CUISprite *pDisable = pItem->m_Disable();
			CUE_Transform *pDisableTransform = pDisable->get_TransformUIRect();
			BOOL bSpriteUpSet = g_pGameControl->IsShowTransform(pUpTransform);
			BOOL bSpriteDisableSet = g_pGameControl->IsShowTransform(pDisableTransform);

			CUISprite* uQuality = pItem->m_QualityBg();
			CStdStringU czNameQuality = uQuality->mSpriteName();

			CGameItem *pGameItem = pItem->GetGameItem();
			if (!pGameItem) continue;
			
			CStdStringU czUName = pGameItem->GetName();
			CStdStringU czUClassName = pGameItem->GetTipsClassDesc();
			int iQuality = pGameItem->GetQuality();
			int iLevel = pGameItem->GetEquipLevel();

			if (g_pGame->m_OptionTab.bTachTrangBiVang) {
				if (!g_pGame->m_OptionTab.bTachGold59 &&
					!g_pGame->m_OptionTab.bTachGold69 && 
					!g_pGame->m_OptionTab.bTachGold79 &&
					!g_pGame->m_OptionTab.bTachGold89  &&
					!g_pGame->m_OptionTab.bTachGoldAllLV  ) {
						g_pGame->m_OptionTab.bTachTrangBiVang = FALSE;
				}

				LOG_WRITE("count %d name Quality: %s", i, _U2A(czNameQuality).c_str());
				if (czNameQuality.Compare(u"common_x_knapsack_bg_04") == 0) {

					if (czUName.Find(u"Quân Hàm") <= 0) {
						if (g_pGame->m_OptionTab.bTachGoldAllLV) {
							LOG_WRITE("On Click bTachGoldAllLV [%s]", _U2A(czUName).c_str());
							m_iTypeCleanBag = 2;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
						}

						if (g_pGame->m_OptionTab.bTachGold59 && iLevel <= 59) {
							LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
							m_iTypeCleanBag = 2;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
						}

						if (g_pGame->m_OptionTab.bTachGold69 && iLevel == 69) {
							LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
							m_iTypeCleanBag = 2;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
						}

						if (g_pGame->m_OptionTab.bTachGold79 && iLevel == 79) {
							LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
							m_iTypeCleanBag = 2;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
						}

						if (g_pGame->m_OptionTab.bTachGold89 && iLevel == 89) {
							LOG_WRITE("On Click [%s]", _U2A(czUName).c_str());
							m_iTypeCleanBag = 2;
							pIns->Click_Item_BelongBackPack(pGameItem);
							return ;
						}
					}
				}
			} //if Trang Bi Vang

			if (czNameQuality.Compare(u"common_x_knapsack_bg_04") != 0) {
				
				if (bSpriteUpSet && g_pGame->m_OptionTab.bDungTrangBi) {
					m_iTypeCleanBag = 1;
					LOG_WRITE("USE EQUIPS..........................");
					pItem->OnItemClick();
					break;
				}

				if (g_pGame->m_OptionTab.bTachTrangBiKhoa && bSpriteDisableSet) {
					m_iTypeCleanBag = 2;
					LOG_WRITE("SPLIT DISABLE EQUIPS..........................%d", iQuality);
					pItem->OnItemClick();
					break;

				}

				if (g_pGame->m_OptionTab.bTachTrangBiLcCao && bSpriteUpSet) {
					m_iTypeCleanBag = 2;
					LOG_WRITE("SPLIT UP EQUIPS..........................");
					pItem->OnItemClick();
					break;
				}	
			}	
		} //if)pItem
	} //for

	if (i >= iCount) {
		LOG_WRITE("ProcessEquipment....bbbbbbbbbbbbbbbbbbbb");
		m_bFinished = TRUE;
	}

	LoopNextSleep();
}

void CGTaskCleanBag::processIfYuanLingIsCheck( int iHour, int iMinute )
{
	int UIMinute = 0;
	int iSTT = g_pGame->m_OptionTab.iTDALTime;
	if (iSTT > 0) {
		if (g_pGame->m_OptionTab.iTDALTime == 1) UIMinute = 57; //3
		if (g_pGame->m_OptionTab.iTDALTime == 2) UIMinute = 55; //5
		if (g_pGame->m_OptionTab.iTDALTime == 3) UIMinute = 53; //7
		if (g_pGame->m_OptionTab.iTDALTime == 4) UIMinute = 51; //9

		if (g_pGame->m_OptionTab.iTDALTime == 5) UIMinute = 45; //15
		if (g_pGame->m_OptionTab.iTDALTime == 6) UIMinute = 41; //19

		switch (iHour) {
		case 11: case 14: case 17: case 20:
			{
				if (iMinute >= UIMinute) {
					if (CGameManager::m_RunningScene() != 4) {AddSubGoal(new CGTaskChangeScene(SCENEID_HOTHONGTHIEN)); return;}
				}
				break;
			}

		case 12: case 15: case 18: case 21:
			{
				if (iMinute >= UIMinute) {
					if (CGameManager::m_RunningScene() != 34) {
						AddSubGoal(new CGTaskChangeScene(SCENEID_NGTHANHTOLONG));
						return;
					}
				}
				break;
			}

		case 13: case 16: case 19: case 22:
			{
				if (iMinute >= UIMinute) {
					if (CGameManager::m_RunningScene() != 92) {AddSubGoal(new CGTaskChangeScene(SCENEID_BENTAMMONG)); return;}
				}
				break;
			}
		}
	}
}
