#include "main.h"
#include "GChienTuBang.h"
#include "GTaskKetBai.h"
#include "GTeamAlone.h"

CGChienTuBang::CGChienTuBang() :CGActivity()
{
	LOG_WRITE("NEW - CGChienTuBang()");
	m_activity = act_chientubang;
	m_iDelayClick = 0;
	m_bGoGuild	  = FALSE;
	m_bFinished	  = FALSE;
	m_bShowMap = FALSE;
	m_bJiebai	= FALSE;
	m_iClickedNPC = 0;
	m_bCheckCountTime = FALSE;
	m_bTeamAlone = FALSE;
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGChienTuBang::~CGChienTuBang()
{
	LOG_WRITE("DEL - CGChienTuBang()");
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
}

int CGChienTuBang::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGChienTuBang::Process()....");
		if (m_bFinished){
			g_pGameControl->FollowLeader(FALSE);
			return FinishedActivity();
		}

		HuoDongLimitWnd();
		if (g_pGameControl->IsMoving()) return LoopNextSleep();
		if (IsNPCDialog()) return LoopNextSleep();
		if (IsInFb()) return LoopNextSleep();
		if (IsGuildMap()) return LoopNextSleep();
		if (IsGuildScene()) return LoopNextSleep();

		GoBackGuildScene();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGChienTuBang::GoBackGuildScene()
{
	LOG_WRITE("GoBackGuildScene()......................");

	if (g_pGameControl->IsShowPopUI()) {
		LOG_WRITE("POP UI.....................");
		//g_pGameControl->CloseDialog();
		return;
	}

	if (!m_bGoGuild) {
		m_bGoGuild = TRUE;
		LOG_WRITE("GoBackGuildScene..............");
		CActivityHuoDongWindow::OnClickBangHuaBtn();
		return;
	}

	if (m_iDelayClick >= 5) {
		m_bGoGuild = FALSE;
		m_iDelayClick = 0;
	}
	m_iDelayClick ++;
	LOG_WRITE("m_iDelayClick = [%d]", m_iDelayClick);
	LoopNextSleep();
}

BOOL CGChienTuBang::IsGuildScene()
{
	if (g_pGameControl->IsMap(u"Cứ Địa Bang")) {

		if (g_pGameControl->IsTeamAloneSet()) {
			processAlone();
			return TRUE;
		}

		if (g_pGameControl->IsMember()) {
			if (g_pGame->m_SyncValues.bActivityStatus) m_bFinished = TRUE;
			g_pGameControl->FollowLeader(ON);
			return TRUE;
		}

		if (g_pGameControl->IsTeamLeader()) {

			if (g_pGameControl->IsLeaderSet() && !m_bJiebai) {
				m_bJiebai = TRUE;
				AddSubGoal(new CGTaskKetBai());
				return TRUE;
			}

			if (g_pGameControl->IsNotEnoughMembers()) return TRUE;

			m_iDelayClick = 0;

			//ProcessGuild
			ProcessGuildScene();
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGChienTuBang::IsNPCDialog()
{
	CDialogController *pIns = CDialogController::Instance();
	if (pIns) {
		int iID = CDialogController::get_DialogID();
		//LOG_WRITE("Close NPC Dialog................%d", iID);

		if (iID == 80 || iID == 79 || iID == 314 || iID == 286) {
			LOG_WRITE("Close NPC Dialog................");
			pIns->AidButtonClick();
			return TRUE;
		}
		else {
			LOG_WRITE("Fight...................");
			pIns->OnOpt_1();
			pIns->AidButtonClick();
		}

		return TRUE;
	}
	return FALSE;
}

void CGChienTuBang::ProcessGuildScene()
{
	LOG_WRITE("ProcessGuildScene.....................");
	CObj_MainPlayer *pObj_Player = g_pGameControl->get_MainPlayer();
	CUE_Transform *p = g_pGameControl->m_pUIRoot->GetChildByName(u"NameBoardRoot");
	if (g_pGameControl->IsShowTransform(p)) {
		int iCount = p->get_childCount();
		if (iCount != 0) {
			int i = 0;
			for (i = 0; i < iCount; i++) {
				CUE_Transform *pNPCHeadInfo = p->GetChild(i);
				if (g_pGameControl->IsShowTransform(pNPCHeadInfo)) {
					CStdStringU czName = pNPCHeadInfo->GetName()->GetText();

					if (czName.Compare(u"NPCHeadInfo") == 0) {
						CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
						CNpcHeadInfoLogic* pHeadInfo = (CNpcHeadInfoLogic *)pNPCHeadInfo->GetComponent(pType);
						if (pHeadInfo) {
							CObj_Char *pNPC = pHeadInfo->get_NPC();
							CStdStringU czNameLabel = pHeadInfo->get_NameLabel();
							CStdStringU czTitle = pHeadInfo->get_TitleLabel();

							if (czNameLabel.Find(u"Đệ Tử Tu Tiên") >= 0 && czTitle.Find(u"Nhấp vào phó bản") >= 0) {
								m_bGoGuild = TRUE;
								if (pNPC && pObj_Player) {
									LOG_WRITE("%d -- NPC[%s]", i, _U2A(czNameLabel).c_str());
									pObj_Player->MoveToTarget(pNPC);
									LoopNextSleep();
									return;
								}
							}
						}
					}
				}
			}
			LOG_WRITE("..........END............");
			if (i == iCount) {
				LOG_WRITE("No NPC........................");
				g_pGameControl->ShowMap();
				return;
			}
		}
	}
}

BOOL CGChienTuBang::IsInFb()
{
	if (m_bFinished) {
		return FinishedActivity();
	}

	if (g_pGameControl->IsButtonExitFuben()) {
		
		m_iDelayClick = 0;
		m_bShowMap = FALSE;
		g_pGameControl->SwitchAutoFight(ON);
		return TRUE;
	}
	return FALSE;
}

void CGChienTuBang::HuoDongLimitWnd()
{

	CUE_Transform *pBase = g_pGameControl->m_pBaseUIRoot;
	if (g_pGameControl->IsShowTransform(pBase)) {
		CUE_Transform *pWnd = pBase->GetChildByName(u"activity.huodong_limittimelist");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			CUE_Transform *pGrid = pWnd->GetChildByPath(u"Offset:Panel:Offset:Grid");
			if (pGrid) {
				int iCount = pGrid->get_childCount();
				if (iCount != 0) {
					int i = 0;
					for (i = 0; i < iCount; i++) {
						CUE_Transform *pChild = pGrid->GetChild(i);
						CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsItem");
						CLimitTimePushTipsItem* pLimit = (CLimitTimePushTipsItem *)pChild->GetComponent(pType);
						if (pLimit) {
							CStdStringU czName = pLimit->get_ActivityName();
							CStdStringU czCount = pLimit->get_Count();
							if (czName.Find(u"Chiến Tu Tiên") >= 0) {
								m_bCheckCountTime = TRUE;
								if (czCount.Find(u"Số lần còn: 0") >= 0) {
									m_bFinished = TRUE;
									if (g_pGameControl->IsTeamLeader()) _theApp->m_pEpoll->Sync_ActivitySttByLeader();
									return;
								}
							}
							//LOG_WRITE("name[%s] -- count[%s]", _U2A(czName).c_str(), _U2A(czCount).c_str());
						}
					}
					LOG_WRITE("..........END HuoDongLimitWnd............");
					if (i == iCount && m_bCheckCountTime) {
						if (g_pGameControl->IsButtonExitFuben()) {
							LOG_WRITE("Wait for end fight.........................");
							return ;
						}/*
						else {
							m_bFinished = TRUE;
							if (g_pGameControl->IsLeader()) _theApp->m_pEpoll->Sync_ActivitySttByLeader();
						}*/
					}
				}
			}
		}

		else {
			g_pGameControl->ShowLimitTips();
			LoopNextSleep();
		}
	}
}

BOOL CGChienTuBang::IsGuildMap()
{
	CSceneMapController *pIns = CSceneMapController::Instance();
	if (pIns) {

		if (m_iClickedNPC > 2 || g_pGameControl->IsMember()) {
			g_pGameControl->CloseDialog();
			return TRUE;
		}

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
					if (m_iClickedNPC == 0) {
						if (czNameNPC.Find(u"Quản Lý Bang Chiến") >= 0) {
							LOG_WRITE("Go to NPC.......................");
							m_bShowMap = TRUE;
							m_iClickedNPC = 1;
							pAutoSearch->OnTransmitPointClick();
							LoopNextSleep(1500);
							return TRUE;
						}
					}

					if (m_iClickedNPC == 1) {
						if (czNameNPC.Find(u"Quản Lý Sảnh") >= 0) {
							LOG_WRITE("Go to NPC.......................");
							m_bShowMap = TRUE;
							m_iClickedNPC = 2;
							pAutoSearch->OnTransmitPointClick();
							LoopNextSleep(1500);
							return TRUE;
						}
					}

					if (m_iClickedNPC == 2) {
						if (czNameNPC.Find(u"Hậu Nhân Hề") >= 0) {
							LOG_WRITE("Go to NPC.......................");
							m_bShowMap = TRUE;
							m_iClickedNPC = 0;
							pAutoSearch->OnTransmitPointClick();
							LoopNextSleep(1500);
							return TRUE;
						}
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

void CGChienTuBang::processAlone()
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



