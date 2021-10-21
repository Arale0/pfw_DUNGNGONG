#include "main.h"
#include "GTruongLaoTuTien.h"
#include "GTaskKetBai.h"

CGTruongLaoTuTien::CGTruongLaoTuTien() :CGActivity()
{
	LOG_WRITE("NEW - CGTruongLaoTuTien()");
	m_activity = act_truonglaotutien;
	m_iDelayClick = 0;
	m_bGoGuild	  = FALSE;
	m_bFinished	  = FALSE;
	m_bShowMap = FALSE;
	m_bJiebai	= FALSE;
	m_iClickedNPC = 0;
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGTruongLaoTuTien::~CGTruongLaoTuTien()
{
	LOG_WRITE("DEL - CGTruongLaoTuTien()");
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
}

int CGTruongLaoTuTien::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGTruongLaoTuTien::Process()....");
		if (m_bFinished) return FinishedActivity();
		if (IsGuildThiefResult()) return LoopNextSleep();
		if (IsNPCDialog()) return LoopNextSleep();
		if (IsGuildMap()) return LoopNextSleep();
		if (IsGuildScene()) return LoopNextSleep();

		GoBackGuildScene();
		return m_nStatus;
	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGTruongLaoTuTien::GoBackGuildScene()
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

BOOL CGTruongLaoTuTien::IsGuildScene()
{
	if (g_pGameControl->IsMap(u"Cứ Địa Bang")) {

		if (g_pGameControl->IsMember()) {
			if (g_pGame->m_SyncValues.bActivityStatus) m_bFinished = TRUE;
			ProcessGuildScene();
			g_pGameControl->SwitchAutoFight(ON);
			return TRUE;
		}

		if (g_pGameControl->IsTeamLeader() && !m_bJiebai) {
			m_bJiebai = TRUE;
			AddSubGoal(new CGTaskKetBai());
			return TRUE;
		}

		if (g_pGameControl->IsMoving()) return TRUE;
		g_pGameControl->SwitchAutoFight(ON);

		ProcessGuildScene();
		m_iDelayClick = 0;

		LoopNextSleep(500);
		return TRUE;
	}
	return FALSE;
}

BOOL CGTruongLaoTuTien::IsNPCDialog()
{
	CDialogController *pIns = CDialogController::Instance();
	if (pIns) {
		int iID = CDialogController::get_DialogID();
		LOG_WRITE("Close NPC Dialog................%d", iID);
		/*if (iID == 80) {

		}*/
		pIns->AidButtonClick();
		return TRUE;
	}
	return FALSE;
}

void CGTruongLaoTuTien::ProcessGuildScene()
{
	LOG_WRITE("ProcessGuildScene.....................");
	if (m_bShowMap) return;
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

							if (czNameLabel.Find(u"Quản Lý Sảnh Tụ") >= 0) {
								m_bGoGuild = TRUE;
								if (pNPC && pObj_Player) {
									LOG_WRITE("%d -- NPC[%s]", i, _U2A(czNameLabel).c_str());
									
									if (m_bShowMap) return;
									m_bShowMap = TRUE;
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
				if (!m_bShowMap) g_pGameControl->ShowMap();
				return;
			}
		}
	}
}

BOOL CGTruongLaoTuTien::IsGuildThiefResult()
{
	CGuildThiefSettlementController *pIns = CGuildThiefSettlementController::Instance();
	if (pIns) {
		
		LOG_WRITE("On Close......................");
		if (g_pGameControl->IsTeamLeader()) _theApp->m_pEpoll->Sync_ActivitySttByLeader();
		m_bFinished = TRUE;
		pIns->OnClose();
		return TRUE;
	}
	return FALSE;
}

BOOL CGTruongLaoTuTien::IsGuildMap()
{
	
	CSceneMapController *pIns = CSceneMapController::Instance();
	if (pIns) {

		if (m_bShowMap) {
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
					
					if (czNameNPC.Find(u"Quản Lý Sảnh") >= 0) {
						LOG_WRITE("Go to NPC.......................");
						m_bShowMap = TRUE;
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



