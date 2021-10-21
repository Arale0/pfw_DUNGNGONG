#include "main.h"
#include "GTaskFuli.h"
#include "GSleep.h"

CGTaskFuli::CGTaskFuli() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskFuli()");
	m_iTimeCount = 0;
	m_bFinished = FALSE;
}

CGTaskFuli::~CGTaskFuli()
{
	LOG_WRITE("DEL - CGTaskFuli()");
	g_pGameControl->CloseDialog();
	g_pGame->m_iCurrentID = -1;
}

int CGTaskFuli::Process()
{

	g_pGameControl->SetCurrentID(104);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("CGTaskFuli::Process()");

	if (!g_pGame->m_OptionTab.bFuli) {LOG_WRITE("Finishedddddddddddd"); return Finished();}

	if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep(500);

	if (g_pGameControl->IsFBResultWnd()) return m_nStatus;

	if (IsFinished()) return m_nStatus;

	if (IsUIScrollExchangeController()) return m_nStatus;

	if (IsOverTime()) return m_nStatus;
	
	if (g_pGameControl->ProcessMessageBox(u"Thoát phó bản?", MSG_OK)) return LoopNextSleep();

	//if (g_pGameControl->IsButtonExitFuben()) {g_pGameControl->ExitFB(); return LoopNextSleep();} 
	
	if (g_pGameControl->IsBagFull()) {m_bFinished = TRUE; return m_nStatus; }

	if (IsNotActiveRedot()) {
		LOG_WRITE("IsActiveRedot"); 
		m_bFinished = TRUE;
		return m_nStatus;
	}

	if (IsChangeWnd()) return m_nStatus;

	if (IsFuliWnd()) return m_nStatus;

	ShowFuliWnd();
	return m_nStatus;
}

int CGTaskFuli::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);//AddSubGoal(new CGSleep(delay));
	return LoopNext();
}

void CGTaskFuli::ShowFuliWnd()
{
	if (g_pGameControl->IsStoryUIRoot()) return;
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) {return; }
	LOG_WRITE("CGTaskFuli::ShowFuliWnd()....");
	pInstance->OnFuLiClick();
	LoopNextSleep();

}

BOOL CGTaskFuli::IsFuliWnd()
{

	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pWnd = pPopUIRoot->GetChildByName(u"welfare.welfareframe");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			CUIActivityBuyback *pInstanceBuyBack = CUIActivityBuyback::Instance();
			if (pInstanceBuyBack) {
				g_pGameControl->CloseDialog();
				return TRUE;
			}
		
			if (IsUIWelfareKaiFu()) return LoopNextSleep(500);
			if (IsUIWelfare_KGDJ()) return LoopNextSleep(500);
			if (IsUIWelfareQianDao()) return LoopNextSleep(500);
			if (IsButtonReceived()) return LoopNextSleep(200);
			/*if (IsShengji()) return LoopNextSleep();
			if (IsDzaixian_daily()) return LoopNextSleep(500);*/
			if (IsRedDot()) return LoopNextSleep();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGTaskFuli::IsRedDot( )
{
	CUE_Transform *pMenu = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"PopUIRoot:welfare.welfareframe:Offset:menuRoot:menu");
	if (g_pGameControl->IsShowTransform(pMenu)) {
		int iAllChild = pMenu->get_childCount();
		int iChild = 0;
		for (iChild = 0; iChild < iAllChild; iChild++) {
			CUE_Transform *pChild = pMenu->GetChild(iChild);
			if (g_pGameControl->IsShowTransform(pChild)) {
				CUE_Transform *pRedDot = pChild->GetChildByName(u"red");
				if (g_pGameControl->IsShowTransform(pRedDot)) {
					CUE_Transform *pLabel = pChild->GetChildByPath(u"pre:Label");
					CStdStringU czLabel = g_pGameControl->GetTextU(pLabel);
					if (czLabel.Compare(u"May Mắn Liên Tiếp") == 0) {
						m_bFinished = TRUE;	
						return TRUE;
					}
					LOG_WRITE("Is RedDot int Child %d, %s", iChild, _U2A(czLabel).c_str());
					g_pGameControl->Tap(pChild);
					return TRUE;
				}
			}
		}

	}
	return FALSE;
}

BOOL CGTaskFuli::IsUIWelfareQianDao()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"welfare.welfareframe:Offset:SubUi:Welfare_qiandao(Clone)");
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUIWelfareQianDao *pInstance = CUIWelfareQianDao::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("CGTaskFuli::IsUIWelfareQianDao()..............");
	pInstance->OnClickGetReWard();
	return FALSE;
}

BOOL CGTaskFuli::IsUIWelfare_KGDJ()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"welfare.welfareframe:Offset:SubUi:Welfare_KGDJ(Clone)");
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pNum = p->GetChildByPath(u"Offset:LotteryLabel:LeftTime:Num");
		CStdStringU czNum = g_pGameControl->GetTextU(pNum);
		if (czNum.Compare(u"0") != 0) {
			LOG_WRITE("Rut Thuong");
			g_pGameControl->Clicked(p->GetChildByPath(u"Offset:Lottery:Title"));
			LoopNextSleep(5000);
			return TRUE;
		}

		CUE_Transform *pList = p->GetChildByPath(u"Offset:leijidenglu:Grid");
		int iAllChild = pList->get_childCount();
		if (iAllChild == 0) return FALSE;
		for (int i = 0; i < iAllChild; i++) {
			CUE_Transform *pChild = pList->GetChild(i);	
			CUE_Transform *pShow = pChild->GetChildByName(u"ui_huodongjiangli_tishi_001");
			if (g_pGameControl->IsShowTransform(pShow)) {
				LOG_WRITE("Click Reward");
				g_pGameControl->Tap(pChild->GetChildByName(u"KnapsackItem01"));
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CGTaskFuli::IsDzaixian_daily()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"welfare.welfareframe:Offset:SubUi:Welfare_zaixian_daily(Clone)");
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pList = p->GetChildByPath(u"qiandaolist:Grid");
		int iAllChild = pList->get_childCount();
		if (iAllChild == 0) return FALSE;
		for (int i = 0; i < iAllChild; i++) {
			CUE_Transform *pChild = pList->GetChild(i);	
			CUE_Transform *pBtn = pChild->GetChildByPath(u"btn:button");
			if (g_pGameControl->IsShowTransform(pBtn)) {
				LOG_WRITE("Click Received..........");
				g_pGameControl->Clicked(pBtn);
				return TRUE;
			}
		}	
	}
	return FALSE;
}

BOOL CGTaskFuli::IsShengji()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"welfare.welfareframe:Offset:SubUi:Welfare_shengji(Clone)");
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pList = p->GetChildByPath(u"qiandaolist:items");
		int iAllChild = pList->get_childCount();
		if (iAllChild == 0) return FALSE;
		for (int i = 0; i < iAllChild; i++) {
			CUE_Transform *pChild = pList->GetChild(i);	
			CUE_Transform *pBtn = pChild->GetChildByPath(u"btn:button");
			if (g_pGameControl->IsShowTransform(pBtn)) {
				LOG_WRITE("Click Received..........");
				g_pGameControl->Clicked(pBtn);
				return TRUE;
			}
		}	
	}
	return FALSE;

}

BOOL CGTaskFuli::IsUIWelfareKaiFu()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"welfare.welfareframe:Offset:SubUi:Welfare_kaifu(Clone)");
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *pButton = p->GetChildByPath(u"wupin:lingqu:button");
	if (!g_pGameControl->IsShowTransform(pButton)) return FALSE;
	LOG_WRITE("CGTaskFuli::IsUIWelfareKaiFu()........Click button");
	g_pGameControl->Clicked(pButton);
	return TRUE;
}

BOOL CGTaskFuli::IsNotActiveRedot()
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	CUE_Transform *pRedDot = pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightUpButtons:1st_Grid:FuLi:RedDot");
	if (!g_pGameControl->IsShowTransform(pRedDot)) {
		LOG_WRITE("sssssssssssssssssssss");
		m_bFinished = TRUE;
		return TRUE; 
	}
	return FALSE;
}

BOOL CGTaskFuli::IsOverTime()
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

BOOL CGTaskFuli::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return Finished();
		return TRUE;
	}

	return FALSE;
}

BOOL CGTaskFuli::IsButtonReceived()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"welfare.welfareframe:Offset:SubUi");
	if (g_pGameControl->IsShowTransform(p)) {
		int iAllChild = p->get_childCount();
		if (iAllChild != 0) {
			for (int i = 0; i < iAllChild; i++) {
				CUE_Transform *pChild = p->GetChild(i);
				if (g_pGameControl->IsShowTransform(pChild)) {
					CUE_Transform *pQiandaolist = pChild->GetChildByName(u"qiandaolist");
					if (g_pGameControl->IsShowTransform(pQiandaolist)) {
						int iAllChild1 = pQiandaolist->get_childCount();
						if (iAllChild1 != 0) {
							for (int j = 0; j < iAllChild1; j++) {
								CUE_Transform *pChild1 = pQiandaolist->GetChild(j);
								if (g_pGameControl->IsShowTransform(pChild1)) {
									int iAllChild2 = pChild1->get_childCount();
									if (iAllChild2 == 0) return FALSE;
									for (int k = 0; k < iAllChild2; k++) {
										CUE_Transform *pChild2 = pChild1->GetChild(k);	
										CUE_Transform *pBtn = pChild2->GetChildByPath(u"btn:button");
										if (g_pGameControl->IsShowTransform(pBtn)) {
											LOG_WRITE("Click Received..........");
											g_pGameControl->Clicked(pBtn);
											return TRUE;
										}
									}	
								}
							}
						}
					} 
				}
			}
		}
	}
	return FALSE;
}

BOOL CGTaskFuli::IsChangeWnd()
{
	if (IsNumericKeyBoard()) return TRUE;
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pChangeWnd = pPopUIRoot->GetChildByName(u"welfare.welfare_juanzhou");
		if (g_pGameControl->IsShowTransform(pChangeWnd)) {
			CUE_Transform *pGrid = pChangeWnd->GetChildByPath(u"Offset:Panel:Grid");
			int iCount = pGrid->get_childCount();
			if (iCount != 0) {
				int i = 0;
				for (i = 0; i < iCount; i++) {
					CUE_Transform *pChild = pGrid->GetChild(i);
					if (pChild) {
						CUE_Transform *pButton = pChild->GetChildByPath(u"btn:button");
						CUE_Transform *pRed = pButton->GetChildByName(u"red");
						if (g_pGameControl->IsShowTransform(pRed)) {
							LOG_WRITE("Change.............................");
							g_pGameControl->Clicked(pButton);
							return TRUE;
						}
					}
				}
				
				if (i >= iCount) g_pGameControl->CloseDialog();
				
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGTaskFuli::IsNumericKeyBoard()
{
	CNumericKeyboardWindow *pIns = CNumericKeyboardWindow::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("IsNumericKeyBoard::Submit....................");
	pIns->OnMaxClick();
	pIns->OnClickSumbit();
	return TRUE;
}

BOOL CGTaskFuli::IsUIScrollExchangeController()
{
	CUIScrollExchangeController *pIns = CUIScrollExchangeController::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("CGTaskFuli::IsUIScrollExchangeController().......................");
	m_bFinished = TRUE;
	return TRUE;
}

