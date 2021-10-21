#include "main.h"
#include "GKhaoCo.h"

CGKhaoCo::CGKhaoCo() :CGActivity()
{
	LOG_WRITE("NEW - CGKhaoCo()");
	m_activity = act_khaoco;
	m_bFinished = FALSE;
	m_bEmpty = FALSE;
	m_iPass[0] = -1;
	m_iPass[1] = -1;
	m_iPass[2] = -1;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGKhaoCo::~CGKhaoCo()
{
	LOG_WRITE("DEL - CGKhaoCo()");
}

int CGKhaoCo::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		UpdatePass();

		LOG_WRITE("CGKhaoCo::Process()....");
		if (g_pGameControl->ProcessMessageBox(u"Bán hết manh mối", MSG_OK)) return m_nStatus;

		if (IsPassWnd()) return LoopNextSleep(500);
		if (archaeologypop()) return LoopNextSleep();
		if (g_pGameControl->IsMoving()) return LoopNextSleep();
		if (IsPickUpBtn()) return LoopNextSleep();

		ShowArchaeologyWindow();
		return LoopNextSleep(1000);

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGKhaoCo::archaeologypop()
{	
	CUE_Transform *pFloatUI = g_pGameControl->m_pFloatUIRoot;
	if (!g_pGameControl->IsShowTransform(pFloatUI)) return FALSE;

	CUE_Transform *pUI = pFloatUI->GetChildByName(u"home.home_archaeologypop_kg");
	if (!g_pGameControl->IsShowTransform(pUI)) return FALSE;

	CUE_Transform *pGrid = pUI->GetChildByPath(u"Offset:Bottom:right:Grid");
	if (!pGrid) return FALSE;
	
	int iCount = pGrid->get_childCount();
	if (iCount <= 0) {m_bFinished = TRUE; return FALSE;}

	for (int i = 0; i < iCount; i++) {
		CUE_Transform *pItem = pGrid->GetChild(i);

		if (!g_pGameControl->IsShowTransform(pItem)) continue;

		CUE_Transform *pBtn = pItem->GetChildByName(u"btn_go");
		if (g_pGameControl->IsShowTransform(pBtn)) {
			LOG_WRITE("Go to map %d....", i);
			g_pGameControl->Clicked(pBtn);
			return TRUE;
		}
	}
	return TRUE;
}

BOOL CGKhaoCo::IsPickUpBtn()
{
	BOOL bIsActive = CPickUpBtnLogic::GetPickBtnActive();
	if (!bIsActive) return FALSE;
	CPickUpBtnLogic *pIns = CPickUpBtnLogic::Instance();
	if (!pIns) return FALSE;

	CStdStringU czLabel = pIns->m_Label();
	if (czLabel.Find(u"Khảo Cổ") < 0) return FALSE;

	LOG_WRITE("Pick up.....");
	pIns->ExecPickBtn();
	return TRUE;
}

BOOL CGKhaoCo::IsPassWnd()
{
	CUIArchaeologyPoint *pIns = CUIArchaeologyPoint::Instance();
	if (pIns) {
		CUE_Transform *pTrans = g_pGameControl->get_Transform((UINT)pIns);
		if (g_pGameControl->IsShowTransform(pTrans)) {
			return CheckAllBoxClue(pIns, pTrans);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGKhaoCo::CheckAllBoxClue(CUIArchaeologyPoint *pInstance, CUE_Transform *p )
{
	if (!p) return FALSE;
	CUE_Transform *pRightView = p->GetChildByPath(u"Offset:Right_View");
	if (!pRightView) return FALSE;
	int iCount = pRightView->get_childCount();
	for (int i = 0; i < iCount; i++) {
		CUE_Transform *pGrid = pRightView->GetChild(i);
		if (!pGrid) continue;
		CStdStringU czNameTrans = pGrid->GetName()->GetText();
		int iChildCount = pGrid->get_childCount();
		if (czNameTrans.Compare(u"Grid") == 0 && iChildCount == 3) {
			
			if (IsEmptyClueInArchaeologyWith(pInstance, 9, 2, pGrid)) return TRUE;   //so thu tu tu duoi len - tu trai sang, 2, child = 2;
			if (IsEmptyClueInArchaeologyWith(pInstance, 8, 2, pGrid)) return TRUE;
			if (IsEmptyClueInArchaeologyWith(pInstance, 7, 2, pGrid)) return TRUE;
			
			pInstance->OnClickArchaeology();
			LOG_WRITE("Line 3 Is Full -----> OnClickArchaeology()");
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGKhaoCo::IsEmptyClueInArchaeologyWith(CUIArchaeologyPoint *pInstance, int iBox, int iChild, CUE_Transform *p /*= NULL*/, BOOL bLineFirst )
{
	if (!p) return FALSE;
	CUE_Transform *pChild = p->GetChild(iChild);
	if (!pChild) return FALSE;
	CUE_Transform *pListClue = pChild->GetChildByName(u"Grid");
	if (!pListClue) return FALSE;

	int iCount = pListClue->get_childCount();
	int iClue = 0;
	if (iBox == 9 || iBox == 3) iClue = 0;
	if (iBox == 8 || iBox == 2) iClue = 1;
	if (iBox == 7 || iBox == 1) iClue = 2;
	CUE_Transform *pItem = pListClue->GetChild(iClue);
	if (!pItem) return FALSE;

	CUIArchaeologyClue *pClue = get_Clue(pItem);
	if (!pClue) return FALSE;

	int iNO = pClue->GetNo();
	if (iNO == iunknown) {
		LOG_WRITE("No clue in box %d - line: %d..", iBox, iChild);
		if (bLineFirst) return CollectClue(iBox);

		if (IsEmptyClueInAnalysWith(pInstance, 6, 1, p)) return TRUE;
		if (IsEmptyClueInAnalysWith(pInstance, 5, 1, p)) return TRUE;
		if (IsEmptyClueInAnalysWith(pInstance, 4, 1, p)) return TRUE;
		
		pInstance->OnClickAnalysisInfo();
		LOG_WRITE("Line 2 Is Full -----> OnClickArchaeology()");
		return TRUE;
	}
	return FALSE;
}

CUIArchaeologyClue * CGKhaoCo::get_Clue( CUE_Transform *p )
{
	CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyClue");
	return (CUIArchaeologyClue *)p->GetComponent(pType);
}

BOOL CGKhaoCo::IsEmptyClueInAnalysWith(CUIArchaeologyPoint *pInstance, int iBox, int iChild, CUE_Transform *p /*= NULL*/ )
{
	if (!p) return FALSE;
	CUE_Transform *pChild = p->GetChild(iChild);
	if (!pChild) return FALSE;
	CUE_Transform *pListClue = pChild->GetChildByName(u"Grid");
	if (!pListClue) return FALSE;

	int iCount = pListClue->get_childCount();
	int iClue = 0;
	if (iBox == 6 ) iClue = 0;
	if (iBox == 5 ) iClue = 1;
	if (iBox == 4 ) iClue = 2;
	CUE_Transform *pItem = pListClue->GetChild(iClue);
	if (!pItem) return FALSE;

	CUIArchaeologyClue *pClue = get_Clue(pItem);
	if (!pClue) return FALSE;

	int iNO = pClue->GetNo();
	if (iNO == iunknown) {
		LOG_WRITE("No: %d clue in box %d - line: %d..", iNO, iBox, iChild);
		if (IsEmptyClueInArchaeologyWith(pInstance,3, 0, p, TRUE)) return TRUE;
		if (IsEmptyClueInArchaeologyWith(pInstance,2, 0, p, TRUE)) return TRUE;
		if (IsEmptyClueInArchaeologyWith(pInstance,1, 0, p, TRUE)) return TRUE;
		
		pInstance->OnCollectInfo();
		LOG_WRITE("Line 1 Is Full -----> OnClickArchaeology()");
		return TRUE;//CollectClue();
	}
	return FALSE;
}

BOOL CGKhaoCo::CollectClue(int iSTT)
{
	CUIArchaeologyPoint *pIns = CUIArchaeologyPoint::Instance();
	CUE_Transform *p = g_pGameControl->get_Transform((UINT)pIns);
	CUE_Transform *pListClue = p->GetChildByPath(u"Offset:Right_View:Grid");

	int iNumPass = set_Num(iSTT);
	if (iNumPass == -1) UpdatePass();

	if (g_pGameControl->IsShowTransform(pListClue)) {
		int i = 0;
		int iCount = pListClue->get_childCount();
		for (i = 0; i < iCount; i++) {
			CUE_Transform *pItem = pListClue->GetChild(i);
			if (!g_pGameControl->IsShowTransform(pItem)) continue;
			CUIArchaeologyClue *pShiJiao = get_Clue(pItem);
			if (pShiJiao) {
				int iNo = pShiJiao->GetNo();
				if (iNo == iunknown) m_bEmpty = TRUE;
				if (iNo == iNumPass) {
					LOG_WRITE("Clicked Item With No %d....", iNumPass);
					pShiJiao->OnClickItem();
					return TRUE;
				}
				LOG_WRITE("%d: No: %d", i, iNo);
			}
		}

		if (i >= iCount) {
			if (!m_bEmpty) {
				//khong co o trong
				LOG_WRITE("SEll clue");
				pIns->OnClickSellClue();
				return TRUE;
			}

			if (m_bEmpty) { //co o trong
				LOG_WRITE("Is has Empty Box -> Add");
				m_bEmpty = FALSE;
				pIns->OnClickCollectClue();
				return TRUE;
			}
		}

		return TRUE;
	}

	return FALSE;
}

void CGKhaoCo::ShowArchaeologyWindow()
{
	if (!g_pGameControl->IsShowPopUI()) {
		LOG_WRITE("Onlicked Home.....");
		CFunctionButtonController *pIns = CFunctionButtonController::Instance();
		if (pIns) pIns->OnClickHome();
		return;
	}

	CHomeGeoController *pHomeGeo = CHomeGeoController::Instance();
	if (pHomeGeo) pHomeGeo->OnClickOpenArchaeology();

	CHomeRootController *pInstance = CHomeRootController::Instance();
	if (!pInstance) { 
		g_pGameControl->CloseDialog();
		return;
	}

	LOG_WRITE("Show HomeGeo Controller....");
	CHomeRootController::OnOpenHomeGeo();
}

void CGKhaoCo::UpdatePass()
{
	OPTIONTAB *pTab = &g_pGame->m_OptionTab;
	m_iPass[0] = pTab->iKhaoCoNo1;
	m_iPass[1] = pTab->iKhaoCoNo2;
	m_iPass[2] = pTab->iKhaoCoNo3;
}

int CGKhaoCo::set_Num( int iSTT )
{
	UpdatePass();

	if (iSTT == 3) return m_iPass[0];
	if (iSTT == 2) return m_iPass[1];
	if (iSTT == 1) return m_iPass[2];

	return -1;
}



