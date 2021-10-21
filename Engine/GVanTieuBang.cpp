#include "main.h"
#include "GVanTieuBang.h"
#include "GTaskKetBai.h"

CGVanTieuBang::CGVanTieuBang() :CGActivity()
{
	LOG_WRITE("NEW - CGVanTieuBang()");
	m_activity = act_vantieubang;
	m_bFinished				= FALSE;
	m_bGoGuild				= FALSE;
	m_bClickRandom			= FALSE;
	m_bMemberConfirm		= FALSE;
	m_bShowActivityWnd		= FALSE;
	m_bJiebai				= FALSE;
	m_bApTieu				= FALSE;
	m_iDelayClicked			= 0;
	m_pTieuXA					= NULL;
	m_iClickedNPC			= 0;
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGVanTieuBang::~CGVanTieuBang()
{
	LOG_WRITE("DEL - CGVanTieuBang()");
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
}

int CGVanTieuBang::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGVanTieuBang::Process()....");
		//LOG_WRITE("g_pGameControl->IsMember() == %d -- g_pGame->m_SyncValues.bActivityStatus == %d", g_pGameControl->IsMember(), g_pGame->m_SyncValues.bActivityStatus);
		 //return m_nStatus;
		

		if (g_pGameControl->ProcessMessageBox(u"1 số thành viên cự ly", MSG_OK)) return m_nStatus;

		if (g_pGameControl->IsConvoyConfirm()) return m_nStatus;

		if (g_pGameControl->IsCopySceneReady()) return m_nStatus;
		
		if (IsFinished()) return m_nStatus;

		//if (g_pGameControl->checkCanJoinActivity(m_activity, m_bFinished)) return LoopNextSleep(); 

		if (g_pGameControl->IsMoving()) return LoopNextSleep();

		if (IsGuildConvoyWnd()) return LoopNextSleep();

		if (IsNPCDialog()) return LoopNextSleep();
		
		if (IsActivity()) return LoopNextSleep();

		if (IsGuildScene()) return LoopNextSleep();

		ProcessGuildConvoy();

		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGVanTieuBang::IsActivityWnd()
{
	return FALSE;
}

BOOL CGVanTieuBang::IsGuildConvoyWnd()
{
	CGuildConvoyFillPanel *pIns = CGuildConvoyFillPanel::Instance();
	if (pIns) {
		m_bGoGuild = TRUE;
		if (!m_bClickRandom) {
			m_bClickRandom = TRUE;
			LOG_WRITE("Random click..............................");
			pIns->OnClickRandom();
			return TRUE;
		}

		if (g_pGameControl->IsMember()) {
			CUE_Transform *pTrans = g_pGameControl->get_Transform((UINT)pIns);
			if (pTrans) {
				CUE_Transform *pBtn = pTrans->GetChildByPath(u"Offset:Btn:Start:Label");
				CStdStringU czText = g_pGameControl->GetTextU(pBtn);
				if (czText.Compare(u"Chuẩn bị")	== 0) {
					LOG_WRITE("Member Confirm...........................");
					pIns->OnClickConfirm();
					return TRUE;
				}
			}
		}
		
		if (g_pGameControl->IsTeamLeader()) {
			LOG_WRITE("Leader Confirm...........................");
			pIns->OnClickConfirm();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGVanTieuBang::IsNPCDialog()
{
	CDialogController *pIns = CDialogController::Instance();
	if (pIns) {
		CUE_Transform *pOpt1Label = g_pGameControl->m_pStoryUIRoot->GetChildByPath(u"synopsis.taskdialog:Offset:dialogSmall:btn_choiceOpt:Grid:choice01:lbl_content");
		if (pOpt1Label) {
			CStdStringU czOptLabel = g_pGameControl->GetTextU(pOpt1Label);
			if (czOptLabel.Find(u"Giao Tiêu Xa") >= 0) {
				if (g_pGameControl->IsTeamLeader()) {
					LOG_WRITE("Over Time....................................................");
					_theApp->m_pEpoll->Sync_ActivitySttByLeader();
					m_bFinished = TRUE;
				}
				return TRUE;
			}
		}

		LOG_WRITE("Close NPC Talk................");
		pIns->OnOpt_1();
		pIns->AidButtonClick();
		return TRUE;
	}
	return FALSE;
}

void CGVanTieuBang::ShowActivityWnd()
{
	if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();

	if (!m_bShowActivityWnd) {
		m_bShowActivityWnd = TRUE;
		LOG_WRITE("ShowActivityWnd()....................");
		g_pGameControl->ClickButtonHuDong();
		return;
	}

	if (m_iDelayClicked >= 3) {
		m_bShowActivityWnd = FALSE;
		m_iDelayClicked = 0;
		return;
	}

	m_iDelayClicked ++;
	LoopNextSleep();
}

BOOL CGVanTieuBang::IsGuildScene()
{
	if (g_pGameControl->IsMap(u"Cứ Địa Bang")) {
		m_bGoGuild = TRUE;
		if (g_pGameControl->IsTeamAloneSet()) {
			processAlone();
			return TRUE;
		}

		if (g_pGameControl->IsMember()) {
			return TRUE;
		}

		if (g_pGameControl->IsTeamLeader()) {

			if (g_pGameControl->IsLeaderSet() && !m_bJiebai) {
				m_bJiebai = TRUE;
				AddSubGoal(new CGTaskKetBai());
				return TRUE;
			}

			if (g_pGameControl->IsNotEnoughMembers()) return TRUE;

			ShowActivityWnd();
			return TRUE;
		}
		
		return TRUE;
	}
	return FALSE;
}

BOOL CGVanTieuBang::IsActivity()
{
	if (g_pGameControl->IsTeamLeader()) {
		if (g_pGameControl->IsActivityWithName(u"Bang áp tiêu", m_bFinished)) {
			//g_pGameControl->CloseDialog();
			m_iDelayClicked = 0;
			return TRUE;
		}
	}
	return FALSE; 
}

void CGVanTieuBang::GoBackGuildScene()
{
	if (!m_bGoGuild) {
		m_bGoGuild = TRUE;
		LOG_WRITE("GoBackGuildScene..............");
		CActivityHuoDongWindow::OnClickBangHuaBtn();
		return;
	}

	if (IsMember()) return ;
}

BOOL CGVanTieuBang::IsPickUpBtn()
{
	if (!g_pGameControl->IsShowTransform(g_pGameControl->m_pBaseUIRoot)) return FALSE;
	CUE_Transform *p = g_pGameControl->m_pBaseUIRoot->GetChildByName(u"PickUpBtn");
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *pLabel = p->GetChildByPath(u"Offset:Label");
	CStdStringU czULabel = g_pGameControl->GetTextU(pLabel);
	//if (czULabel.Compare(u"Trò chuyện") != 0) return FALSE;
	if (g_pGameControl->IsMember()) return FALSE;
	LOG_WRITE("CGameControl::IsPickUpBtn............");
	g_pGameControl->GetExecPickBtn();
	return TRUE;
}

void CGVanTieuBang::ProcessGuildConvoy()
{
	static int iScene = -1;
	int iCurScene = CGameManager::m_RunningScene();
	if (iScene != iCurScene) {
		iScene = iCurScene;
		m_pTieuXA = NULL;
		return;
	}
	LOG_WRITE("CGVanTieuBang::ProcessGuildConvoy()...........................");
	CObj_MainPlayer *pObj_Player = g_pGameControl->get_MainPlayer();
	CFunctionButtonController *pFunc = CFunctionButtonController::Instance();
	if (m_iClickedNPC <= 0 && pFunc) {
		LOG_WRITE("OnClickGuildConvoyGo().................");
		pFunc->OnClickGuildConvoyGo();
	}

	//kiem tra tieu xa
	if (m_pTieuXA) {
		m_bGoGuild = TRUE;
		CStdStringU czName = m_pTieuXA->get_RoleName();		
		if (czName.Find(u"Tiêu Xa") < 0) { //khong phai tieu xa -> pTieuXa = NULL;
			LOG_WRITE("Not convoy -- Name NPC: %s", _U2A(czName).c_str());
			m_pTieuXA = NULL;
			return;
		}

		LOG_WRITE("Click to Convoy..............................");
		OnClickGuildConvoy(pObj_Player);
		return;
	}

	//tim tieu xa
	CTeam *pTeam = g_pGameControl->m_pPlayerData->get_TeamInfo();
	int iTeamID = 0;
	if (pTeam) iTeamID = pTeam->get_TeamID();	
	CActiveSceneLogic *pScene = CGameManager::get_CurActiveScene();
	if (!pScene) return;
	CUE_Transform *pCharRoot = pScene->get_CharRoot();
	if (!g_pGameControl->IsShowTransform(pCharRoot)) return ;
	int iCount = pCharRoot->get_childCount();
	if (iCount == 0) return;
	for (int i = 0; i < iCount; i++) {
		CUE_Transform *pItem = pCharRoot->GetChild(i);
		int iChildCount = pItem->get_childCount();
		CObj_Char *pChar = g_pGameControl->getNPC(pItem, "Obj_Char");
		if (pChar) {
			CStdStringU czName = pChar->get_RoleName();
			if (czName.Find(u"Tiêu Xa") >= 0) {
				CObj_NPC *pNPC = (CObj_NPC*)pChar;
				int iOwnTeamID = pNPC->get_OwnTeamId();
				LOG_WRITE("iOwnTeamID[%d] -- [%d]iTeamId", iOwnTeamID, iTeamID);
				if (iOwnTeamID == iTeamID) {
					m_bGoGuild = TRUE;
					LOG_WRITE("Click to Convoy..............................");
					m_pTieuXA = (CObj_Char *)pChar;
					pObj_Player->MoveToTarget(pChar);
					m_bApTieu = TRUE;
					return;
				}
			}
		}
	}
	
	m_bGoGuild = FALSE;

	if (!m_bApTieu) GoBackGuildScene();
}

BOOL CGVanTieuBang::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsMember()) g_pGameControl->FollowLeader(FALSE);

		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();

		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsMember() && g_pGame->m_SyncValues.bActivityStatus) {
		LOG_WRITE("Member Finihsed.......................");
		m_bFinished = TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CGVanTieuBang::IsMember()
{
	if (g_pGameControl->IsMember()) {
		if (!g_pGame->m_OptionTab.bTVNotFollow) {
			g_pGameControl->FollowLeader();
		}

		if (g_pGame->m_OptionTab.bTVNotFollow) {
			g_pGameControl->FollowLeader(FALSE);
		}

		return TRUE;
	}
	return FALSE;
}

void CGVanTieuBang::processAlone()
{
	static BOOL bTeamAlone = FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_ALONE) {

		if (g_pGameControl->IsMember()) bTeamAlone = TRUE;
		if (!bTeamAlone) {
			bTeamAlone = TRUE;
			//AddSubGoal(new CGTeamAlone());
		}	
		if (!g_pGameControl->IsHasTeam()) bTeamAlone = FALSE;

		if (g_pGameControl->IsTeamLeader()) bTeamAlone = FALSE;
		return;
	}

	if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_ALONE) bTeamAlone = FALSE;
}

void CGVanTieuBang::OnClickGuildConvoy(CObj_MainPlayer *pMainPlayer)
{

	if (m_iClickedNPC == 1) {
		LOG_WRITE("OnClickGuildConvoy().................");
		pMainPlayer->MoveToTarget(m_pTieuXA);
	}
	
	if (m_iClickedNPC == 3) {
		LOG_WRITE("GuildConvoyTransNext().................");
		COptionLogic::GuildConvoyTransNext();
	}

	if (m_iClickedNPC >= 5) {
		LOG_WRITE("GuildConvoyFinish().................");
		m_iClickedNPC = -1;
		COptionLogic::GuildConvoyFinish();
	}

	m_iClickedNPC ++;
	LoopNextSleep();
}



