#include "main.h"
#include "GTangBaoDo.h"

CGTangBaoDo::CGTangBaoDo() :CGActivity()
{
	LOG_WRITE("NEW - CGTangBaoDo()");
	m_activity = act_tangbaodo;
	m_bFinished = FALSE;
	m_iDelayClicked = 0;
	m_iSTT = 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity, ast_doing);
}

CGTangBaoDo::~CGTangBaoDo()
{
	LOG_WRITE("DEL - CGTangBaoDo()");
	//g_pGame->m_iCurrentID = -1;
}

int CGTangBaoDo::Process()
{
	g_pGameControl->SetCurrentID((int)m_activity);
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGTangBaoDo::Process()....");

		if (IsFinished()) return m_nStatus;

		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();
		
		if (IsPicking()) return LoopNextSleep(500);

		if (IsPickUpBtn()) return m_nStatus;

		if (IsItemTips()) return LoopNextSleep();

		if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep(500);

		if (g_pGameControl->ProcessMessageBox(u"Cần đến bản đồ chỉ định ", MSG_OK)) return LoopNextSleep(500);

		if (g_pGameControl->IsMessageBox(u"mời bạn vào đội,", OFF)) return LoopNextSleep(500);

		if (g_pGameControl->IsButtonExitFuben()) {g_pGameControl->SwitchAutoFight(ON);return LoopNextSleep(500);}

		if (g_pGameControl->IsMoving()) { g_pGameControl->CloseDialog(); m_iDelayClicked = 0; return LoopNextSleep(500);}

		//if (g_pGameControl->IsPickUpBtn()) return m_nStatus;

		if (IsBagWnd()) return LoopNextSleep(500);

		ShowBag();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGTangBaoDo::IsBagWnd()
{
	if (IsNumericKeyBoard()) return TRUE;
	if (!g_pGameControl->IsShowTransformKnapsack()) return FALSE;
	CKnapsackWindow *pKnapsackWindow = CKnapsackWindow::Instance();
	if (pKnapsackWindow) {
		m_bTBDCao	=	FALSE;
		m_bTBDTrung =	FALSE;

		int iFilterType = pKnapsackWindow->m_FilterType();
		LOG_WRITE("IsCopyFinishedFubenWnd...............%d", iFilterType);
		if (iFilterType != 6) {
			SelectOtherTab(pKnapsackWindow);
			return TRUE;
		}

		CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
		if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
			LOG_WRITE(".................................1");
			CUE_Transform *pWnd = pPopUIRoot->GetChildByName(u"Knapsack");
			if (g_pGameControl->IsShowTransform(pWnd)) {
				m_iDelayClicked = 0;

				
				CSYS_List *pLst = pKnapsackWindow->filterItemList();
				if (pLst) {
					int iCount = pLst->get_Count();
					if (iCount != 0) {
						if (m_iSTT == 0) LOG_WRITE("Duyet lan 1..");

						if (m_iSTT == 1) LOG_WRITE("Duyet lan 2..");

						if (m_iSTT == 2) LOG_WRITE("Duyet lan 3..");
						int i = 0;
						for (i = 0; i < iCount; i++) {
							LOG_WRITE("duyet %d", i);
							//CKnapsackItem *pKnapsackItem = (CKnapsackItem *)pLst->get_Item(i);
							//if (pKnapsackItem) {
								CGameItem *pGameItem = (CGameItem *)pLst->get_Item(i); //pKnapsackItem->GetGameItem();
								if (pGameItem) {
									CStdStringU czUName = pGameItem->GetName();
									CStdStringU czDecription = pGameItem->GetTipsClassDesc();

									/*LOG_WRITE("%d[%08X] + Name: %s", i, pGameItem, _U2A(czUName).c_str());
									LOG_WRITE("%d[%08X] + Desc: %s", i, pGameItem, _U2A(czDecription).c_str());
									LOG_WRITE("............................................");*/

									if (m_iSTT == 0) {//dao tang bao do khoa 

										if (czUName.Compare(u"Tàng Bảo Đồ (Chưa giám định)") == 0) {
											BOOL bCanInStall = pGameItem->IsCanInStall();
											if (g_pGame->m_OptionTab.bTBDGiaoDich && bCanInStall) {
												LOG_WRITE("Dung TAng BAo Do duoc Giao dich");
												pKnapsackWindow->Click_Item_BelongBackPack(pGameItem);
												return TRUE;
											}

											if (!bCanInStall) {
												LOG_WRITE("Dung TAng BAo Do Khoa");
												pKnapsackWindow->Click_Item_BelongBackPack(pGameItem);
												return TRUE;
											}
										}
									}

									if (m_iSTT == 1) {
										if (czUName.Compare(u"Tàng Bảo Đồ Cũ") == 0) {
											pKnapsackWindow->Click_Item_BelongBackPack(pGameItem);
											return TRUE;
										}
									}
									
									if (m_iSTT == 2) {
										if (czUName.Compare(u"Tàng Bảo Đồ-Thường") == 0 && m_pGame->m_OptionTab.bTBDTrung) {
											pKnapsackWindow->Click_Item_BelongBackPack(pGameItem);
											return TRUE;
										}
									}
									
									if (m_iSTT == 3) {
										if (czUName.Compare(u"Tàng Bảo Đồ-Cao") == 0 && m_pGame->m_OptionTab.bTBDCao) {
											pKnapsackWindow->Click_Item_BelongBackPack(pGameItem);
											return TRUE;
										}
									}
									
									
								}
							//}

						}
						
						if (i >= iCount) {
							if (m_iSTT == 0) {
								m_iSTT = 1;
								i = 0;
								LOG_WRITE("Khong tim thay TBD Khoa --> Tim TBD Cu");
								return TRUE;
							}

							if (m_iSTT == 1) {
								m_iSTT = 2;
								i = 0;
								LOG_WRITE("Khong tim thay TBD Cu --> Tim TBD Thuong");
								return TRUE;
							}

							if (m_iSTT == 2) {
								m_iSTT = 3;
								i = 0;
								LOG_WRITE("Khong tim thay TBD Thuong --> Tim TBD Cao");
								return TRUE;
							}

							if (m_iSTT == 3) {
								LOG_WRITE("Khong tim thay TBD Cao --> Finished");
								m_bFinished = TRUE; 
								return TRUE;
							}
							return TRUE;
						}
					}
				}
				return TRUE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

void CGTangBaoDo::ShowBag()
{
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) {return; }
	if (g_pGameControl->IsShowPopUI()) {g_pGameControl->CloseDialog(); return;}
	
	if (m_iDelayClicked >= 3) {
		m_iDelayClicked = 0;

		pInstance->OnClickBackPack();
		return;
	}
	m_iDelayClicked = m_iDelayClicked + 1;
	LOG_WRITE("ShowBag().... %d", m_iDelayClicked);
	LoopNextSleep();
}

BOOL CGTangBaoDo::IsNumericKeyBoard()
{
	CNumericKeyboardWindow *pIns = CNumericKeyboardWindow::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("IsNumericKeyBoard::Submit....................");
	pIns->OnMaxClick();
	pIns->OnClickSumbit();
	return TRUE;
}

BOOL CGTangBaoDo::IsItemTips()
{
	CUE_Transform *p = g_pGameControl->m_pTipUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"item.itemtips");
		if (g_pGameControl->IsShowTransform(pWnd)) {

			CItemTipsController *pIns = CItemTipsController::Instance();
			if (pIns) {
				CGameItem *pSelectItem = pIns->m_SeletItem();
				if (pSelectItem) {
					CStdStringU czUName = pSelectItem->GetName();
					BOOL bCanInStall = pSelectItem->IsCanInStall();

					if (czUName.Compare(u"Tàng Bảo Đồ Cũ") == 0) {
						UseItemTips(pWnd);
						return TRUE;
					}

					else if (czUName.Compare(u"Tàng Bảo Đồ-Thường") == 0 && m_pGame->m_OptionTab.bTBDTrung) {
						UseItemTips(pWnd);
						return TRUE;
					}

					else if (czUName.Compare(u"Tàng Bảo Đồ-Cao") == 0 && m_pGame->m_OptionTab.bTBDCao) {
						LOG_WRITE("TANG BAo do cao................");
						UseItemTips(pWnd);
						return TRUE;
					}

					else if (czUName.Compare(u"Tàng Bảo Đồ (Chưa giám định)") == 0) {
						BOOL bCanInStall = pSelectItem->IsCanInStall();
						if (g_pGame->m_OptionTab.bTBDGiaoDich && bCanInStall) {
							LOG_WRITE("Dung TAng BAo Do duoc Giao dich");
							UseItemTips(pWnd);
							return TRUE;
						}

						if (!g_pGame->m_OptionTab.bTBDGiaoDich && bCanInStall) {
							g_pGameControl->Tap(1, 1);
							return TRUE;
						}
						
						if (!bCanInStall) {
							LOG_WRITE("Dung TAng BAo Do Khoa");
							UseItemTips(pWnd);
							return TRUE;
						}
						
					}
					else g_pGameControl->Tap(1, 1);
				}
			}
		}
	}
	return FALSE;
}

BOOL CGTangBaoDo::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();

		else if (g_pGameControl->IsMoving(TRUE)) return FinishedActivity();

		else if (IsPicking()) return TRUE;

		else if (IsPickUpBtn()) return TRUE;

		else return FinishedActivity();
		return TRUE;
	}
	return FALSE;
}

int CGTangBaoDo::get_ItemCount()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"Knapsack:Offset:KnapsackClient:Appearance:BackPack:ItemNum:lbl_num");
	if (!p) return -1;
	CStdStringU czNum = g_pGameControl->GetTextU(p);
	return atoi(_U2A(czNum).c_str());
}

void CGTangBaoDo::SortItem()
{
	

}

BOOL CGTangBaoDo::IsPicking()
{
	CPickItemProgressController *pInstance = CPickItemProgressController::Instance();
	if (pInstance) {
		BOOL bIsRunning = pInstance->IsRunning();
		if (!bIsRunning) return FALSE;
		if (m_bFinished) {
			LOG_WRITE("FINISH -> close processss...............");
			pInstance->CloseProgress();
			return FinishedActivity();
		}
		if (m_bTBDCao) {
			m_iDelayClicked = 2;
			LOG_WRITE("CGTangBaoDo::Close  Progress........................................1");
			pInstance->CloseProgress();
			return TRUE;
		}

		if (m_bTBDTrung) {
			m_iDelayClicked = 2;
			LOG_WRITE("CGTangBaoDo::Close  Progress........................................2");
			pInstance->CloseProgress();
			return TRUE;
		}

		m_iDelayClicked = 0;
		LOG_WRITE("CGTangBaoDo::IsPicking().........");
		return TRUE;
	}
	return FALSE;
}

void CGTangBaoDo::UseItemTips( CUE_Transform *p )
{
	CUE_Transform *pButtonList = p->GetChildByPath(u"Offset:TipsFolder:Offset Bottom:Button List:Grid");
	int iAllChild = pButtonList->get_childCount();
	if (iAllChild != 0) {
		for (int i = 0; i < iAllChild; i++ ) {
			CUE_Transform *pButton = pButtonList->GetChild(i);
			CUE_Transform *pLabel = pButton->GetChildByPath(u"Offset:Button:Label");
			CStdStringU czULabel = g_pGameControl->GetTextU(pLabel);
			if (czULabel.Compare(u"Dùng") == 0) {
				LOG_WRITE("...............USE................");
				g_pGameControl->Clicked(pButton->GetChildByPath(u"Offset:Button"));
			}
		}
	}
}

void CGTangBaoDo::SelectOtherTab( CKnapsackWindow *pIns )
{
	if (!pIns) return;
	CSYS_List *pFilterList = pIns->m_FilterItemList();
	if (!pFilterList) return;
	int iCount = pFilterList->get_Count();
	if (iCount == 0) return;

	UINT uFilter = (UINT)pFilterList->get_Item(4);
	if (uFilter == 0) return;
	CUE_Transform *pTransform = g_pGameControl->get_Transform(uFilter);
	if (pTransform) {
		LOG_WRITE("CGTaskCleanBag::Click Other Btn.....");
		g_pGameControl->Clicked(pTransform->GetChildByName(u"other_off"));
		return;
	}
}

BOOL CGTangBaoDo::IsPickUpBtn()
{
	BOOL bTBDCao = m_pGame->m_OptionTab.bTBDCao;
	BOOL bTBDTrung = m_pGame->m_OptionTab.bTBDTrung;

	BOOL bIsActive = CPickUpBtnLogic::GetPickBtnActive();
	if (!bIsActive) return FALSE;
	CPickUpBtnLogic *pIns = CPickUpBtnLogic::Instance();

	CStdStringU czLabel = pIns->m_Label();

	if (m_bFinished) {
		if (czLabel.Find(u"Tàng Bảo Đồ") >= 0) {
			LOG_WRITE("wait for processing ................................");
			return TRUE;
		}

		if (czLabel.Compare(u"Đào Kho Báu") == 0) {
			LOG_WRITE("wait for processing.....");
			return TRUE;
		}
	}

	if (czLabel.Compare(u"Tàng Bảo Đồ-Cao") == 0 && !bTBDCao) {
		LOG_WRITE("=============> Khong dao Tang Bao Do Cao");
		m_bTBDCao = TRUE;
		return TRUE;
	}

	if (czLabel.Compare(u"Tàng Bảo Đồ-Thường") == 0 && !bTBDTrung) {
		LOG_WRITE("=============> Khong dao Tang Bao Do Trung");
		m_bTBDTrung = TRUE;
		return TRUE;
	}
	LOG_WRITE("============= Pickup Label: %s", _U2A(czLabel).c_str());
	return FALSE;
}



