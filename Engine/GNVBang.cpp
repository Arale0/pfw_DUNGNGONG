#include "main.h"
#include "GNVBang.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"
#include "GTaskCleanBag.h"
#include "GTaskKetBai.h"

CGNVBang::CGNVBang() :CGActivity()
{
	LOG_WRITE("NEW - CGNVBang()");
	m_activity = act_nvbang;
	m_bFinished				= FALSE;
	m_bGoGuild				= FALSE;
	m_pTransform			= NULL;
	m_uActivity				= 0;
	m_iDelayClick			= 0;
	m_iTemp = -1;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGNVBang::~CGNVBang()
{
	LOG_WRITE("DEL - CGNVBang()");
}

int CGNVBang::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		//CheckMap();
		
		if (IsFinished()) return m_nStatus;

		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();
		
		if (g_pGameControl->IsPickUpBtn()) return LoopNextSleep();

		if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep(500);
		
		if (g_pGameControl->IsMessageBox(u"mời bạn vào đội,", OFF)) return LoopNextSleep(500);

		if (IsCopyFinishedFubenWnd()) {m_iTemp = 1; return LoopNextSleep();}

		if (g_pGameControl->IsButtonExitFuben()) {
			m_iTemp = 1;
			m_uActivity = 0;
			g_pGameControl->SwitchAutoFight(ON);
			return LoopNextSleep();
		}
		
		if (g_pGameControl->IsMoving()) {m_iTemp = 1; return LoopNextSleep();}
		
		other();

		/*if (g_pGameControl->IsMap(u"Cứ Địa Bang")) get_GuildMission();

		if (!g_pGameControl->IsMap(u"Cứ Địa Bang")) JoinGuildMap();*/
		
		//if (IsMissionTrack()) return LoopNextSleep();

		
		LOG_WRITE("CGNVBang::Process()....");

		return m_nStatus;
	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

int CGNVBang::ProcessNVBang()
{
	//LOG_WRITE("m_uActivity");
	m_iDelayClick = 0;
	CUE_Transform *pActivity = (CUE_Transform *)m_uActivity;
	if (!pActivity) {
		LOG_WRITE("No m_pActivity");
		return m_nStatus;
	}
	
	if (g_pGameControl->IsMoving()) return LoopNextSleep(1000);
	g_pGameControl->MissionClicked(pActivity);

	return LoopNextSleep(1000);
}

BOOL CGNVBang::IsGuildFrame()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *pGuild1 = p->GetChildByName(u"guild.guild");
	if (g_pGameControl->IsShowTransform(pGuild1)) {LOG_WRITE("CGNVBang::IsGuildFrame()............");return TRUE;}
	CUE_Transform *pGuild = p->GetChildByName(u"guild.guild_frame");
	if (!g_pGameControl->IsShowTransform(pGuild)) return FALSE;
	LOG_WRITE("CGNVBang::IsGuildFrame()............");
	return TRUE;
}

BOOL CGNVBang::IsCopyFinishedFubenWnd()
{
	CCopySceneSettlementController *pInstance = CCopySceneSettlementController::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("Exit Fuben...");
	pInstance->OnExitCopyScene();
	return TRUE;
}

void CGNVBang::JoinGuildMap()
{
	if (m_iDelayClick >= 3) {
		m_iDelayClick = 0;
		CActivityHuoDongWindow::OnClickBangHuaBtn();
		return;
	}
	m_iDelayClick ++;
	LOG_WRITE("CGNVBang::JoinGuildMap()... %d", m_iDelayClick);
	LoopNextSleep();
}

void CGNVBang::get_GuildMission()
{
	m_iDelayClick = 0;
	CActivityHuoDongWindow::OnClickGuildMission();
	LOG_WRITE("CGNVBang::get_GuildMission()...");
	LoopNextSleep();
}

void CGNVBang::other()
{
	/*int iActID = CActivityHuoDongWindow::GetActivityId(2002);

	if (iActID != 2002) {
		LOG_WRITE("ID is Wrong........");
		return;
	}

	BOOL bIsCanJoin = CActivityHuoDongWindow::CheckIsCanJion(iActID);
	if (!bIsCanJoin) {
		m_bFinished = TRUE;
		return;
	}*/
	/*if (g_pGameControl->checkCanJoinActivity(m_activity, m_bFinished)) {
		LoopNextSleep();
		return;
	}*/

	LOG_WRITE("Yes.............%d", m_iTemp);

	if (m_iTemp <= 0) CActivityHuoDongWindow::OnClickGoActivityBtnByActivityId(2002, 0);

	if (m_iTemp >= 3) m_iTemp = -1;

	m_iTemp ++;
	LoopNextSleep();
}

BOOL CGNVBang::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(17)) { m_bFinished = TRUE; return TRUE;}

	if (g_pGameControl->IsGuildName(u"")) { m_bFinished = TRUE; return TRUE;}
	
	if (IsNPCTalk(u"Thân là Tổng Quản Bang,")) return TRUE;

	return FALSE;
}

BOOL CGNVBang::IsNPCTalk( CStdStringU czContent )
{
	CUE_Transform *p = g_pGameControl->m_pStoryUIRoot;
	CUE_Transform *p1 = p->GetChildByName(u"synopsis.taskdialog");
	if (g_pGameControl->IsShowTransform(p1)) {
		CUE_Transform *pContent = p1->GetChildByPath(u"Offset:dialogLarge:lbl_des:lbl_des");
		if (pContent) {
			CStdStringU czUContent = g_pGameControl->GetTextU(pContent);
			if (czUContent.Find(czContent) >= 0) {
				m_bFinished = TRUE;
				LOG_WRITE("FInissheeeeeeeeeeeeeeeeeee");
				g_pGameControl->CloseNPCTalk();
				return TRUE;
			}
		}
	}
	return FALSE;
}

void CGNVBang::Activate()
{
	m_nStatus = ACTIVE;
	m_dwStartTime = (DWORD)g_pUEThread->GetTickCount();
	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
}

void CGNVBang::CheckCleanBag()
{
	//DWORD dwTime = (DWORD)g_pUEThread->GetTickCount();
	//DWORD dwCleanTime = g_pGame->m_OptionTab.iDeMinute * 60000;
	//if (dwCleanTime <= 0) dwCleanTime = 120000;
	////LOG_WRITE("%d", dwTime - m_dwStartTime);
	//if (dwTime - m_dwStartTime >= dwCleanTime) {
	//	LOG_WRITE("Timeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
	//	m_dwStartTime = (DWORD)g_pUEThread->GetTickCount();
	//	AddSubGoal(new CGTaskCleanBag());
	//	return;
	//}
	//LoopNextSleep();
}

BOOL CGNVBang::IsGuildScene()
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

BOOL CGNVBang::IsGuildMap()
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
					if (czNameNPC.Compare(u"Tổng Quản Bang") == 0) {
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

void CGNVBang::GoBackGuildScene()
{
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

	if (m_iDelayClick >= 7) {
		m_bGoGuild = FALSE;
		m_iDelayClick = 0;
	}
	m_iDelayClick ++;
	LOG_WRITE("m_iDelayClick = [%d]", m_iDelayClick);
	LoopNextSleep();
}

BOOL CGNVBang::IsMissionTrack()
{
	//LOG_WRITE("m_pTransform[%08X], m_uActivity[%08X]", m_pTransform, m_uActivity);
	if (!m_uActivity) {
		LOG_WRITE(".............0");

		if (g_pGameControl->IsMissionTrack(u"Bang", m_uActivity)) return TRUE;//return ProcessNVBang();

		if (IsGuildMap()) return TRUE;

		if (IsGuildScene()) return TRUE;

		GoBackGuildScene();
		return TRUE;
		
	}

	LOG_WRITE(".............1");
	CUE_Transform *pTransform = (CUE_Transform *)m_uActivity;
	LOG_WRITE(".............2");
	if (!pTransform) {m_uActivity = 0; return TRUE;}
	LOG_WRITE(".............5");
	if (g_pGameControl->IsShowTransform(pTransform)) {
		LOG_WRITE(".............7");
		static int i = -1;
		LOG_WRITE(".............8");
		CUE_Transform *pname = pTransform->GetChildByPath(u"Offest:Sprite:TypeLabel");
		LOG_WRITE(".............9");
		CStdStringU czName = g_pGameControl->GetTextU(pname);
		if (czName.Find(u"Bang") >= 0) {
			LOG_WRITE("Yes.............");
			if (i <= 0) g_pGameControl->MissionClicked(pTransform);

			if (i >= 3) i = -1;

			i ++;
			return TRUE;
		}

		LOG_WRITE(".............4");
		i = -1;
		m_uActivity = 0;
		return TRUE;
	}
	LOG_WRITE(".............3");

	m_uActivity = 0;
	return FALSE;
}

void CGNVBang::CheckMap()
{
	static CStdStringU czNameMap = u"No name";
	if (!g_pGameControl->IsMap(czNameMap)) {
		LOG_WRITE("Is Not Map.....................................");
		m_uActivity = 0;
		czNameMap = g_pGameControl->get_NameMap();
	}
}



