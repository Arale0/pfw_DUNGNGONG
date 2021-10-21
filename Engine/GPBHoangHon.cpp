#include "main.h"
#include "GPBHoangHon.h"
#include "GTaskKetBai.h"
#include "GTeamAlone.h"

CGPBHoangHon::CGPBHoangHon() :CGActivity()
{
	LOG_WRITE("NEW - CGPBHoangHon()");
	m_activity = act_pbhoanghon;
	m_iDelayShowTeamWnd	= -1;
	m_iCountTime		= 0;
	m_bFinished			= FALSE;
	m_bJiebai			= FALSE;
	m_bCountTime		= FALSE;
	m_bSkipCutScene		= FALSE;
	m_bS = FALSE;
	m_iCloseMap			= 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGPBHoangHon::~CGPBHoangHon()
{
	LOG_WRITE("DEL - CGPBHoangHon()");
}

int CGPBHoangHon::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		g_pGameControl->SetCurrentID((int)m_activity);
		//LOG_WRITE("CGPBHoangHon::Process()....%d, m_bFinished = %d, bActivityStatus = %d", g_pGame->m_SyncValues.bUpdateActivityStatusByLeader, m_bFinished, g_pGame->m_SyncValues.bActivityStatus);
		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();
		if (g_pGameControl->IsCopySceneReady()) return LoopNextSleep();
		if (IsFinished()) return m_nStatus;
		if (IsNPCDialog()) return LoopNextSleep();
		if (!IsInMaple()) m_iCloseMap = 0;
		if (IsInMaple()) return LoopNextSleep();
		if (IsInFb()) return LoopNextSleep();
		if (IsTeamWnd()) return LoopNextSleep(500);
		processOutside();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}


BOOL CGPBHoangHon::IsNPCDialog()
{
	CDialogController *pIns = CDialogController::Instance();
	if (pIns) {
		LOG_WRITE("Close NPC Talk");
		pIns->OnOpt_1();
		pIns->AidButtonClick();
		return TRUE;
	}
	return FALSE;
}

BOOL CGPBHoangHon::IsFinished()
{
	if (m_bFinished) {
		
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		
		else if (g_pGameControl->exitTeamIfAloneTeamSet()) return TRUE;

		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(30)) { 
		LOG_WRITE("g_pGameControl->IsLowerLevel(30)");
		m_bFinished = TRUE; 
		return TRUE;
	}
	
	return FALSE;
}

BOOL CGPBHoangHon::IsInFb()
{

	if (IsCopyFinishedFubenWnd()) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Bản đồ hiện tại yêu cầu", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Thao tác hiện tại", MSG_CANCEL)) return TRUE;

	if (g_pGame->m_OptionTab.iHHDifficult == 0 || !g_pGame->m_OptionTab.bHHLeaderSkip) {
		if (IsStoryUIRoot()) { m_iDelayShowTeamWnd = 1; return TRUE;}
	}	
	
	if (g_pGame->m_OptionTab.bHHLeaderSkip) {
		if (g_pGame->m_OptionTab.iHHDifficult != 0 && g_pGameControl->IsTeamLeader()) {
			if (IsStoryUIRoot()) { m_iDelayShowTeamWnd = 1; return TRUE;}
		}
	}

	if (g_pGameControl->IsButtonExitFuben()) {

		g_pGameControl->CloseDialog();

		if (IsPickUpBtn()) return LoopNextSleep();

		if (!m_bCountTime) {
			m_bCountTime = TRUE;
			m_iCountTime = m_iCountTime + 1;
		}
		m_iDelayShowTeamWnd = 1;
		
		processFb();

		if (!m_bS) g_pGameControl->SwitchAutoFight(ON);
		return TRUE;
	}
	return FALSE;
}

void CGPBHoangHon::ShowTeamWnd()
{
	CLeftInfoController *pIns = CLeftInfoController::Instance();
	if (!pIns) return;
	
	if (m_iDelayShowTeamWnd <= 0) {
		LOG_WRITE("Show Team Wnd.................");
		pIns->OnTeamClick();
	}

	if (m_iDelayShowTeamWnd >= 5) m_iDelayShowTeamWnd = -1;

	m_iDelayShowTeamWnd ++;
}

void CGPBHoangHon::processOutside()
{	
	if (g_pGameControl->IsTeamAloneSet()) {
		processAlone();
		LoopNextSleep();
		return;
	}

	if (g_pGameControl->IsMember()) {
		LoopNextSleep();
		return;
	}

	if (g_pGameControl->IsTeamLeader()) {

		if (g_pGameControl->IsLeaderSet() && !m_bJiebai) {
			m_bJiebai = TRUE;
			AddSubGoal(new CGTaskKetBai());
			return;
		}

		if (g_pGameControl->IsNotEnoughMembers()) {LoopNextSleep();return;}

		ShowTeamWnd();
		LoopNextSleep();
		return;
	}
}

BOOL CGPBHoangHon::IsTeamWnd()
{
	CTeamController *pIns = CTeamController::Instance();
	if (pIns) {
		m_iDelayShowTeamWnd = 1;
		int iDiffcult = g_pGame->m_OptionTab.iHHDifficult;

		if (iDiffcult == 0 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Sơ Thám")) {
			m_iDelayShowTeamWnd = 1;
			return TRUE;
		}
		if (iDiffcult == 1 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Không")) {
			m_iDelayShowTeamWnd = 1;
			return TRUE;
		}
		if (iDiffcult == 2 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Phá")) {
			m_iDelayShowTeamWnd = 1;
			return TRUE;
		}
		if (iDiffcult == 3 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Diệt")) {
			m_iDelayShowTeamWnd = 1;
			return TRUE;
		}
		if (iDiffcult == 4 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Nguyên")) {
			m_iDelayShowTeamWnd = 1;
			return TRUE;
		}
		if (iDiffcult == 5 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Chân")) {
			m_iDelayShowTeamWnd = 1;
			return TRUE;
		}
		return TRUE;
	}
	
	return FALSE;
}

BOOL CGPBHoangHon::IsPickUpBtn()
{
	if (!g_pGameControl->IsShowTransform(g_pGameControl->m_pBaseUIRoot)) return FALSE;
	CUE_Transform *p = g_pGameControl->m_pBaseUIRoot->GetChildByName(u"PickUpBtn");
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *pLabel = p->GetChildByPath(u"Offset:Label");
	CStdStringU czULabel = g_pGameControl->GetTextU(pLabel);
	m_bS = FALSE;
	if (czULabel.Compare(u"Mở") == 0) {
		if (g_pGameControl->AutoFightIsOn()) {
			g_pGameControl->SwitchAutoFight(OFF);
			LOG_WRITE("Tat auto truoc khi mooooooooooooooooooooooooooooooooooooooooo");
			return TRUE;
		}	

		g_pGameControl->GetExecPickBtn();
		LOG_WRITE("CGameControl::MOOOOOOOOOOOOOOOOOOOOOOOOO............");
		return TRUE;
	}
	g_pGameControl->GetExecPickBtn();
	LOG_WRITE("CGameControl::IsPickUpBtn............");
	return TRUE;

	/*BOOL bActive = CPickUpBtnLogic::GetPickBtnActive();
	if (!bActive) return FALSE;
	CPickUpBtnLogic *pIns = CPickUpBtnLogic::Instance();
	m_bS = FALSE;
	LOG_WRITE("PickUp................");
	pIns->ExecPickBtn();
	return TRUE;*/
}

BOOL CGPBHoangHon::IsCopyFinishedFubenWnd()
{
	CCopySceneSettlementController *pInstance = CCopySceneSettlementController::Instance();
	if (!pInstance) return FALSE;
	
	int iCountTime = g_pGame->m_OptionTab.iHHCountTime;
	if (m_iCountTime >= iCountTime + 1) {
		LOG_WRITE("Over Time....................................................");
		m_bFinished = TRUE;
	}
	
	m_bSkipCutScene = FALSE;
	m_bCountTime = FALSE;

	if (g_pGameControl->IsTeamLeader()) return TRUE;
	
	LOG_WRITE("Exit Fuben...");
	pInstance->OnExitCopyScene();
	return TRUE;
}

void CGPBHoangHon::processFb()
{
	if (IsShowTargetBar()) return;
	if (g_pGameControl->IsMoving()) return;
	MoveToTarget();

}
BOOL CGPBHoangHon::IsInMaple()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"Map");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			g_pGameControl->Tap(484, 458);
			CloseDialog();
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CGPBHoangHon::IsShowTargetBar()
{
	CUE_Transform *pTransform = NULL;
	CTargetFrameControllerNew *pIns = CTargetFrameControllerNew::Instance();
	if (!pIns) {
		LOG_WRITE("fight..............pIns == NULL");
		return FALSE;
	}
	CUE_Transform *pTargetFrameController = g_pGameControl->get_Transform((UINT)pIns);
	if (pTargetFrameController) {
		CUE_Transform *pMonster = pTargetFrameController->GetChildByPath(u"Offset:Monster&NpcBar");
		CUE_Transform *pBoss = pTargetFrameController->GetChildByPath(u"Offset:BossBar");

		if (g_pGameControl->IsShowTransform(pMonster)) {
			CUE_Transform *pPlayerIcon = pMonster->GetChildByPath(u"Self:MonsterHeadIcon:PlayerIcon");
			if (g_pGameControl->IsShowTransform(pPlayerIcon)) return FALSE;
			LOG_WRITE("Is Have Show Target Bar.................");
			return TRUE;
		}
		if (g_pGameControl->IsShowTransform(pBoss)) {
			CUE_Transform *pPlayerIcon = pBoss->GetChildByPath(u"Self:MonsterHeadIcon:PlayerIcon");
			if (g_pGameControl->IsShowTransform(pPlayerIcon)) return FALSE;
			LOG_WRITE("Is Have Show Target Bar.................");
			return TRUE;
		}
		//if (g_pGameControl->IsShowTransform(pTransform)) 
	}
	return FALSE;
}

void CGPBHoangHon::MoveToTarget()
{
	CObj_MainPlayer *pObj_Player = g_pGameControl->get_MainPlayer();
	if (!pObj_Player) return;
	CObj *pObjPlayer = (CObj *)pObj_Player;
	CUE_Vector3 *pPlayer_Vt3 = pObj_Player->get_Position();
	if (!pPlayer_Vt3) return;
	int xPlayer, yPlayer, zPlayer;
	xPlayer = (int)pPlayer_Vt3->GetX();	yPlayer = (int)pPlayer_Vt3->GetY();	zPlayer = (int)pPlayer_Vt3->GetZ();
	LOG_WRITE("xyz[%d,%d,%d]", xPlayer,yPlayer,zPlayer);
	
	//khu vuc 1 - cua truyen tong
	if (zPlayer >= 200 ) {

		if (xPlayer <= 46) {
			LookforTarget(pObj_Player, 0, 0, 0, TRUE);
			return;
		}
		LOG_WRITE("Chua Qua Cua Truyen Tong.........");
		LookforTarget(pObj_Player, 90, 100, 197);
		return;
	}

	if (g_pGameControl->IsTeamLeader() || g_pGame->m_OptionTab.bHHMemAutoSearch) {
		if (xPlayer >= 44 && yPlayer == 91 && zPlayer >= 29 && !m_bSkipCutScene) {
			LOG_WRITE("den Phong Vo Ngan...............");
			g_pGameControl->ShowMap();
			return;
		}

		//khu vuc 2 - đến Phong Vô Ngấn
		else if (zPlayer <= 80 && xPlayer <= 75) {
			LOG_WRITE("...............");
			LookforTarget(pObj_Player, 44, 91, 29) ;
			return;
		}

		//khu vực 3 - Đến Anh Linh
		else if (zPlayer <= 120 && xPlayer > 100) {
			LOG_WRITE("den Anh Linh.........");
			LookforTarget(pObj_Player, 118, 100, 120);
			return;
		}

		//Cọc cuối
		else if (zPlayer >= 140 && zPlayer < 190) {
			LOG_WRITE("den Coc Cuoi.........");
			LookforTarget(pObj_Player, 91, 103, 154);
			LoopNextSleep();
			return;
		}

		else if (!m_bSkipCutScene){
			LOG_WRITE("Di chuyen.....");
			LookforTarget(pObj_Player, 45, 95, 53);
			return;
		}

		
	}
	
}

void CGPBHoangHon::processAlone()
{
	static BOOL bTeamAlone = FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_ALONE) {

		if (g_pGameControl->IsMember()) bTeamAlone = TRUE;
		if (!bTeamAlone) {
			bTeamAlone = TRUE;
			AddSubGoal(new CGTeamAlone());
		}	
		if (!g_pGameControl->IsHasTeam()) bTeamAlone = FALSE;

		if (g_pGameControl->IsTeamLeader()) bTeamAlone = FALSE;
		return;
	}

	if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_ALONE) bTeamAlone = FALSE;
}

BOOL CGPBHoangHon::IsStoryUIRoot()
{
	CUE_Transform *p = g_pGameControl->m_pStoryUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pSecneDialog = p->GetChildByName(u"synopsis.cutscenedialog");
		if (g_pGameControl->IsShowTransform(pSecneDialog)) {
			m_bSkipCutScene = TRUE;
			CUE_Transform *pSkipBtn = pSecneDialog->GetChildByPath(u"Offset:Top:SkikBtn");
			if (g_pGameControl->IsShowTransform(pSkipBtn)) g_pGameControl->Clicked(pSkipBtn->GetChildByName(u"Label"));
			else LOG_WRITE("Is Cut Scene Dialog..................");
			return TRUE;
		}
	}
	return FALSE;
}

void CGPBHoangHon::LookforTarget(CObj_MainPlayer *pPlayer, int xPos, int yPos, int zPos, BOOL bFirstTime )
{
	if (!pPlayer) return;
	CUE_Transform *pCharRoot = g_pGameControl->get_CharRoot();
	if (!g_pGameControl->IsShowTransform(pCharRoot)) return;
	int iCount = pCharRoot->get_childCount();
	if (iCount == 0) return;
	for (int i = 1; i < iCount; i++) {
		CUE_Transform *pChild = pCharRoot->GetChild(i);
		int iChildCount = pChild->get_childCount();

		if (iChildCount == 4) { //la NPC
			CObj_Char *pChar = g_pGameControl->getNPC(pChild);
			CObj *pObj = (CObj *)pChar;
			CObj_Char *pChar1 = (CObj_Char*)pObj;
			CStdStringU czName = pChar1->get_RoleName();
			if (pObj) {

				if (czName.Compare(u"Cuồng Lang Thủ Vệ Cổ Đô") == 0 && bFirstTime) {
					LOG_WRITE("First time to go to door......");
					pPlayer->MoveToTarget(pChar); 
					LoopNextSleep(2000);
					return;
				}

				CUE_Vector3 *pVt3 = pObj->get_Position();
				float fx, fy, fz;
				fx = pVt3->GetX(); fy = pVt3->GetY(); fz = pVt3->GetZ();
				int x = (int)fx; int y = (int)fy; int z = (int)fz;
				if (x == xPos && y == yPos && z == zPos) {
					LOG_WRITE("Move To Target...................................[%08X][%s]", pChild, _U2A(czName).c_str());

					if (x == 91 && y == 103 && z == 154 && czName.Compare(u"") == 0) {
						LOG_WRITE("Tat auto danh truoc khi mo coc");
						if (g_pGameControl->AutoFightIsOn() && !m_bS) {
							m_bS = TRUE;
							g_pGameControl->SwitchAutoFight(OFF);
							return;
						}
						pPlayer->MoveToTarget(pChar); 
						LoopNextSleep();
						return;
					}
					pPlayer->MoveToTarget(pChar); 
					if (xPos == 90) LoopNextSleep(3000);
					else LoopNextSleep();
					return;
				}
			}
		}
	}
	LOG_WRITE("END LOOP......................NO NPC");
}

BOOL CGPBHoangHon::CheckNearTeam()
{
	if (g_pGameControl->IsMember()) return FALSE;
	CObj_MainPlayer *pPlayer = g_pGameControl->get_MainPlayer();
	if (!pPlayer) return FALSE;

	CTeamList *pIns = CTeamList::Instance();
	if (!pIns) return FALSE;
	CSYS_Array *pArray = pIns->m_TeamMemberUI();
	if (!pArray) return FALSE;
	int iCount = pArray->get_Length();
	if (iCount == 0) return FALSE;
	CTeamMemberUIInfo *pMember = (CTeamMemberUIInfo*)pArray->GetValue(1);
	if (!pMember) return FALSE;
	BOOL bIsHalfShow = pMember->m_bIsHalfShow();
	if (!bIsHalfShow) return FALSE;
	LOG_WRITE("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	
	LookforTarget(pPlayer, 0, 0, 0);
	return TRUE;
}
void CGPBHoangHon::CloseDialog()
{
	if (m_iCloseMap >= 2) {
		g_pGameControl->CloseDialog();
	}
	m_iCloseMap ++;
	LoopNextSleep();
}