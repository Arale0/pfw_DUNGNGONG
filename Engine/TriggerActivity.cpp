#include "main.h"
#include "TriggerActivity.h"
#include "GMainQuest.h"
#include "GLoginServerChoose.h"
#include "GLoginRoleChoose.h"
#include "GNVBang.h"
#include "GVanDapNgay.h"
#include "GKepGiayDoiBietThu.h"
#include "GQuyetDauDinhCao.h"
#include "GTruThienPhuDo.h"
#include "GTaskFuli.h"
#include "GTeamBuild.h"
#include "GPhuongDeGian.h"
#include "GPhuongMinhCoc.h"
#include "GTangBaoDo.h"
#include "GTaskCleanBag.h"
#include "GThuongThienPhatAc.h"
#include "GPBHoangHon.h"
#include "GPBTuChan.h"
#include "GDaNgongCuong.h"
#include "GVanTieuBang.h"
#include "GTaskCleanBag1.h"
#include "GChienTuBang.h"
#include "GTruongLaoTuTien.h"
#include "GNVPhuTuyen.h"
#include "GTrucDietAcLinh.h"
#include "GThoSanTienThuong.h"
#include "GTaskBuyPatch.h"
#include "GGhepPhuLinh.h"
#include "GSonCocDatLinh.h"
#include "GTaskAchievement.h"
#include "GHungVanQuan.h"
#include "GTaskGetMail.h"
#include "GTaskCDTuChan.h"
#include "GBayBan.h"
#include "GKhoaCuVanDap.h"
#include "GGTienMaKiep.h"
#include "GHangBauVat.h"
#include "GNVHuongDan.h"
#include "GNVTuChan.h"
#include "GNVAn.h"
#include "GNVPhu.h"
#include "GNVThan.h"
#include "GNVTruyen.h"
#include "GTaskChangeScene.h"
#include "GKhaoCo.h"
#include "GBayBanTheoDeNghi.h"
int CTriggerActivity::_lstGoalId[goal_LAST];

CTriggerActivity::CTriggerActivity(void)
{
	m_uTimeStarted = 0;
	m_bEnableAcitvity = FALSE;
	m_dwTimeUtilityStarted  = 0;
	m_dwTimeResetFPS		= 0;
	m_dwTimeFuliCheck		= 0;
	m_bSetFPS = FALSE;
}

CTriggerActivity::~CTriggerActivity(void)
{	
}

BOOL CTriggerActivity::IsReady( DWORD dwMiliseconds)
{
	ULONGLONG uCurrentTime = g_pUEThread->GetTickCount();
	if (m_uTimeStarted == 0) {
		m_uTimeStarted = uCurrentTime;
		return TRUE;
	}
	DWORD dwElapsed = (DWORD)(uCurrentTime - m_uTimeStarted);
	if (dwElapsed < dwMiliseconds) return FALSE;
	m_uTimeStarted = uCurrentTime;
	return TRUE;
}

BOOL CTriggerActivity::IsExistActivityGoal( int actId )
{
	return g_pAutoAI->GetGoalSystem()->IsExistSubGoal(_lstGoalId[actId]);
}

void CTriggerActivity::AddActivityGoal( int actId, CGoal* pG )
{
	_lstGoalId[actId] = g_pAutoAI->GetGoalSystem()->AddSubGoal(pG);
}

BOOL CTriggerActivity::AddActivityGoalIfNew( int actId)
{
	if (IsExistActivityGoal(actId)) return FALSE;
	switch (actId){
		case act_mainquest:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGMainQuest());
			return TRUE;
		case goal_UILoginServer:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGLoginServerChoose());
			return TRUE;
		case goal_UILoginRole:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGLoginRoleChoose());
			return TRUE;
		case goal_TeamBuild:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTeamBuild());
			return TRUE;
		case goal_buyPatch:
			//g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTaskBuyPatch());
			return TRUE;
		case goal_Bag:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTaskCleanBag());
			return TRUE;
		case goal_Mail:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTaskGetMail());
			return TRUE;

		case act_nvbang:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGNVBang());
			return TRUE;
		case act_vandapngay:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGVanDapNgay());
			return TRUE;
		case act_kepgiaydoibietthu:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGKepGiayDoiBietThu());
			return TRUE;
		case act_quyetdaudinhcao:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGQuyetDauDinhCao());
			return TRUE;
		case act_truthienphudo:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTruThienPhuDo());
			return TRUE;
		case act_phuongdegian:
			//g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGPhuongDeGian());
			return TRUE;
		case act_phuongminhcoc:
			//g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGPhuongMinhCoc());
			return TRUE;
		case act_tangbaodo:
			//g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTangBaoDo());
			return TRUE;
		case act_thuongthienphatac:
			//g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGThuongThienPhatAc());
			return TRUE;
		case act_pbhoanghon:
			//g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGPBHoangHon());
			return TRUE;
		case act_pbtuchan:
			if (IsExistActivityGoal(goal_buyPatch)) return FALSE;
			AddActivityGoal(actId, new CGPBTuChan());
			return TRUE;
		case act_dangongcuong:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGDaNgongCuong());
			return TRUE;
		case act_vantieubang:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGVanTieuBang());
			return TRUE;
		case act_chientubang:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGChienTuBang());
			return TRUE;
		case act_truonglaotutien:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTruongLaoTuTien());
			return TRUE;
		case act_phutuyen:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGNVPhuTuyen());
			return TRUE;
		case act_trucdietaclinh:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGTrucDietAcLinh());
			return TRUE;
		case act_thosantienthuong:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGThoSanTienThuong());
			return TRUE;
		case act_ghepphulinh:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGGhepPhuLinh());
			return TRUE;
		case act_soncocdatlinh:
			g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
			AddActivityGoal(actId, new CGSonCocDatLinh());
			return TRUE;

		case act_hungvanquan:
			AddActivityGoal(actId, new CGHungVanQuan());
			return TRUE;

		case act_khoacuvandap:
			AddActivityGoal(actId, new CGKhoaCuVanDap());
			return TRUE;
		case act_gtienmakiep:
			AddActivityGoal(actId, new CGGTienMaKiep());
			return TRUE;
		
		case act_nvhuongdan:
			AddActivityGoal(actId, new CGNVHuongDan());
			return TRUE;
		case act_nvtuchan:
			AddActivityGoal(actId, new CGNVTuChan());
			return TRUE;
		case act_nvan:
			AddActivityGoal(actId, new CGNVAn());
			return TRUE;
		case act_nvphu:
			AddActivityGoal(actId, new CGNVPhu());
			return TRUE;
		case act_nvthan:
			AddActivityGoal(actId, new CGNVThan());
			return TRUE;
		case act_nvtruyen:
			AddActivityGoal(actId, new CGNVTruyen());
			return TRUE;
		case act_khaoco:
			AddActivityGoal(actId, new CGKhaoCo());
			return TRUE;
		case act_baybantheodenghi:
			AddActivityGoal(actId, new CGBayBanTheoDeNghi());
			return TRUE;
	}

	return FALSE;
}

void CTriggerActivity::Process_LoginGame()
{
	if (!g_pAutoAI->IsEmpty()) {
		LOG_WRITE("g_pAutoAI->IsEmpty() == 0");
		return;
	}
	if(g_pGameControl->IsUIServerChoose()){
		LOG_WRITE("g_pGameControl->IsUIServerChoose().......................");
		AddActivityGoalIfNew(goal_UILoginServer);	
		return;
	}
	if(g_pGameControl->IsUIRoleChoose()){
		AddActivityGoalIfNew(goal_UILoginRole);	
		return;
	}
}

void CTriggerActivity::Update()
{
	if (!IsReady()) return;
	if (UtilityProcess()) return;
	if (!g_pGame->m_bIsLogined){
		Process_LoginGame();
		return;
	}
	if(TeamProcess()) {
		LOG_WRITE("TeamProcess..........");
		return;
	}
	int iActId = g_pGame->m_iCurrentActivity;
	if (iActId == -1){
		//iActId = g_pGame->m_iCurrentActivity;
		//yeu cau lai neu qua lau
		return;
	}
	if (g_pGame->m_iCurrentID <= -1) AddActivityGoalIfNew(iActId);

}

BOOL CTriggerActivity::TeamProcess(){
	if (IsExistActivityGoal(goal_TeamBuild)) return TRUE;

	if(NeedTeamBuild())
	{
		AddActivityGoalIfNew(goal_TeamBuild);
		return TRUE;
	}

	/*if (g_pGameControl->IsSingleActivity()) return FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_ALONE) return FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_INTELLIGENCE) return FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_MATCH) return FALSE;


	if(CTeamList::Instance() == 0) {
		g_pGameControl->OnTeamTabClick();
		return TRUE;
	}

	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_LEADER) {

		if (g_pGameControl->IsMember()) {
			g_pGameControl->LeaveTeam();
			return TRUE;
		}

		if (!g_pGameControl->IsHasTeam()) {
			g_pGameControl->TeamCreate();
			return TRUE;
		}

		if(g_pGameControl->IsTeamLeader()){

			if(g_pGame->m_TeamOption.bJiebai){
				//LOG_WRITE("........................................................................");
				return FALSE;
			}

			int iAmountOfMembers = g_pGame->m_TeamOption.iSLTV;
			if (g_pGameControl->IsTeamEnoughMembers(iAmountOfMembers)) {
				LOG_WRITE("Enoughed Members....................");
				return FALSE;
			}

			if (g_pGame->m_TeamOption.bInviteFriends) {
				AddActivityGoalIfNew(goal_TeamBuild);
				return TRUE;
			}

			if (g_pGameControl->processIfReqJoinTeam()) return TRUE;

			if (!g_pGameControl->IsTeamEnoughMembers(iAmountOfMembers)) {
				g_pGameControl->CloseTeamWnd();
				return TRUE;
			}

		}
	}


	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_MEMBER) {
		if (g_pGameControl->IsTeamLeader()) {
			if(g_pGameControl->IsHaveTeam()){
				g_pGameControl->LeaveTeam();
				return TRUE;
			}
		}

		if (g_pGameControl->IsCopySceneReady()) return FALSE;

		if (g_pGame->m_TeamOption.bMemberAcceptJiebai) {
			g_pGameControl->MemberAccept(Jiebai);
		}

		if (g_pGame->m_TeamOption.bMemAcceptFriendsInvite) {
			g_pGameControl->MemberAccept(Friends);
		}

		g_pGameControl->TeamInviteAccept(g_pGame->m_Members[0].czTeamName);

		g_pGameControl->ReqJoinTeam(g_pGame->m_Members[0].czTeamName);

		return FALSE;
	}*/

	return FALSE;
}
BOOL CTriggerActivity::NeedTeamBuild(){

	//if(!g_pGame->IsHaveTeam()) return FALSE;
	if (g_pGameControl->IsSingleActivity()) return FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_ALONE) return FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_INTELLIGENCE) return FALSE;
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_MATCH) return FALSE;

	if(g_pGame->IsTeamLeader()){
		if(g_pGameControl->IsLeader()) {
			if(/*g_pGameControl->IsFullMember(g_pGame->m_Members) ||*/
				g_pGame->m_TeamOption.bJiebai){
					//LOG_WRITE("........................................................................");
				return FALSE;
			}
		}

		int iAmountOfMembers = g_pGame->m_TeamOption.iSLTV;
		if (g_pGameControl->IsTeamEnoughMembers(iAmountOfMembers)) {
			//LOG_WRITE("Enoughed Members....................");
			return FALSE;
		}

		AddActivityGoalIfNew(goal_TeamBuild);
		return TRUE;
	}
	
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_MEMBER) {
		if (g_pGameControl->IsTeamLeader()) {
			g_pGameControl->LeaveTeam();
			return FALSE;
		}

		if (g_pGameControl->IsCopySceneReady()) return FALSE;

		if (g_pGame->m_TeamOption.bMemberAcceptJiebai) {
			g_pGameControl->MemberAccept(Jiebai);
		}

		if (g_pGame->m_TeamOption.bMemAcceptFriendsInvite) {
			//LOG_WRITE("sssssssssssssssssssssssssssss");
			g_pGameControl->MemberAccept(Friends);
			//g_pGameControl->CancelAcceptMessageBoxWithCheckBox();
		}

		g_pGameControl->MemberAccept(NameLeader);

		return FALSE;
	}
	
	return TRUE;
}

BOOL CTriggerActivity::Test() {
	
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"zhanling.zhanling_root:Offset:SubUi:ZhanLing_YingHun(Clone):Offset:ScrollViewFolder:Scroll View:Grid");
	if (g_pGameControl->IsShowTransform(p)) {
		
		int iCount = p->get_childCount();
		for (int i = 0; i < iCount; i++) {
			CUE_Transform *pItem = p->GetChild(i);
			CUE_Transform *pName = pItem->GetChildByName(u"lbl_Name");
			CStdStringU czName = g_pGameControl->GetTextU(pName);
			LOG_WRITE("[%d] %s", i, _U2A(czName).c_str());
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CTriggerActivity::UtilityProcess()
{
	/*if (g_pGame->m_OptionTab.bOptimizeCPUAct) {
		g_pGameControl->IsMovingXYZ();
		return TRUE;
	}

	return FALSE;
	static BOOL bTest1 = FALSE;
	if (g_pGame->m_OptionTab.bCleanBag)  {
		if (!bTest1) {
			bTest1 = TRUE;
			g_pGameControl->ShowListNPC();
			return TRUE;
		}
	}
	if (!g_pGame->m_OptionTab.bCleanBag) bTest1 = FALSE;*/

	/*if (g_pGame->m_OptionTab.bTC2TimeToFinished) {
		CStdStringU czCOunt = CActivityHuoDongWindow::GetActivityCountByActivityId(2021);
		LOG_WRITE("czCount = [%s]", _U2A(czCOunt).c_str());
	}*/

	//LOG_WRITE("czCount = [%d]", g_pGame->m_iCurrentID);




	if (g_pGameControl->ProcessMessageBox(u"Đồng ý ", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Sau khi mặc,", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Sau khi dùng,", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Trang bị này có thể", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Hiện vào bản đồ PK", MSG_CANCEL)) return TRUE;
	if (g_pGameControl->ProcessMessageBox(u"Nhiệm vụ cần làm", MSG_CANCEL)) return TRUE;

	if (g_pGame->m_iCurrentActivity == -1) {
		if (g_pGameControl->IsReliveWnd()) return TRUE;
	}

	if (g_pGameControl->IsPVPResultWnd()) return TRUE;
	if (IsLackMana()) return TRUE;
	if (IsOptimizeCPU()) return TRUE;
	
	static BOOL bTest = FALSE;
	if (!g_pGame->m_OptionTab.bGetSilverBox) bTest = FALSE;

	if (g_pGame->m_OptionTab.bGetSilverBox) {
		//g_pGameControl->Test();
		g_pGameControl->CheckSilverBox();
		//CStdStringU czU = g_pGameControl->getCurrentNameLine();
		//LOG_WRITE("Current Line [%s]", _U2A(czU).c_str());

	}
	static BOOL bCleanBag = FALSE;
	BOOL bIsBagFull = g_pGameControl->IsBagFull();
	if (!bIsBagFull) {
		bCleanBag = FALSE;
		if (g_pGame->m_OptionTab.bFuli) {
			static BOOL bFirstCheck = FALSE;

			DWORD dwCurrentTime = g_pUEThread->GetTickCount();
			if (m_dwTimeFuliCheck == 0) {
				m_dwTimeFuliCheck = dwCurrentTime;
				return TRUE;
			}

			if (dwCurrentTime - m_dwTimeFuliCheck >= 120000) {
				bFirstCheck = FALSE;
				LOG_WRITE("REsetttt............................");
				m_dwTimeFuliCheck = dwCurrentTime;
				return TRUE;
			}

			if (!bFirstCheck) {
				bFirstCheck = TRUE;
				if (g_pGameControl->IsFuliRedDot() && !g_pGameControl->IsButtonExitFuben()) {
					g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskFuli());
					return TRUE;
				}
				return TRUE;
			}
		}

		if (g_pGame->m_OptionTab.bAchievement) {
			if (g_pGameControl->IsAchievementRedDot() && !g_pGameControl->IsButtonExitFuben()) {
				g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskAchievement());
				return TRUE;
			}
		}
		
	}

	if (g_pGame->m_OptionTab.bCheckMail) {
		if (!bIsBagFull && g_pGameControl->IsNewMail() && !g_pGameControl->IsShowPopUI()) {
			g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskGetMail());
			return TRUE;
		}
			//return TRUE;
	}

	if (g_pGame->m_OptionTab.bRecDynamic) {
		if (!bIsBagFull) {
			g_pGameControl->ReceivedBonusItem();
		}
	}
	
	///////////////////////BAG///////////////////////
	int iBagCleanType = g_pGame->m_OptionTab.iBagCleanType;
	if (iBagCleanType == 1) {
		static BOOL bFirstCleanBagTime1 = FALSE;
		static BOOL bFirstCleanBagTime2 = FALSE;
		int iCurrentMinute				= g_pGameControl->getTime(1);
		int iMinuteP1					= g_pGame->m_OptionTab.iBagCleanPoint1;
		int iMinuteP2					= g_pGame->m_OptionTab.iBagCleanPoint2;
		BOOL bCheckPointTime1			= g_pGame->m_OptionTab.bBagCleanPoint1;
		BOOL bCheckPointTime2			= g_pGame->m_OptionTab.bBagCleanPoint2;

		if (!bCheckPointTime1) bFirstCleanBagTime1			= FALSE;
		if (!bCheckPointTime2) bFirstCleanBagTime2			= FALSE;
		if (iCurrentMinute < iMinuteP1) bCheckPointTime1	= FALSE;
		if (iCurrentMinute < iMinuteP2) bCheckPointTime2	= FALSE;
		if (!g_pGame->m_OptionTab.bCleanBag) {bFirstCleanBagTime1 = FALSE; bFirstCleanBagTime2 = FALSE;}
		if (iMinuteP1 != 0 && iCurrentMinute >= iMinuteP1 && iCurrentMinute < 28) {

			if (iCurrentMinute >= iMinuteP2) bFirstCleanBagTime1 = TRUE;
			
			if (bCheckPointTime1 && !bFirstCleanBagTime1) {
				if (g_pGame->m_OptionTab.bCleanBag) {
					if (!g_pGameControl->IsShowPopUI()) {
						bFirstCleanBagTime1 = TRUE;
						LOG_WRITE("Add new Clean Bag 1");
						g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskCleanBag());
						return TRUE;
					}
				}
			}
			if (iCurrentMinute < 28 && g_pGameControl->IsBagFull() && !g_pGameControl->IsShowPopUI()) bFirstCleanBagTime1 = FALSE;
		}

		if (iMinuteP2 != 0 && iCurrentMinute >= iMinuteP2 && iCurrentMinute < 58) {
			if (bCheckPointTime2 && !bFirstCleanBagTime2) {
				if (g_pGame->m_OptionTab.bCleanBag) {
					if (!g_pGameControl->IsShowPopUI()) {
						bFirstCleanBagTime2 = TRUE;
						LOG_WRITE("Add new Clean Bag 2");
						g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskCleanBag());
						return TRUE;
					}
				}
			}

			if (iCurrentMinute < 58 && g_pGameControl->IsBagFull() && !g_pGameControl->IsShowPopUI()) bFirstCleanBagTime2 = FALSE;
		}
	}

	
	if (iBagCleanType == 0) {

		DWORD dwCurrentTime = g_pUEThread->GetTickCount();
		if (m_dwTimeUtilityStarted == 0) {
			m_dwTimeUtilityStarted = dwCurrentTime;
			return TRUE;
		}

		DWORD dwCleanTime = g_pGame->m_OptionTab.iDeMinute * 60000;
		if (dwCurrentTime - m_dwTimeUtilityStarted >= dwCleanTime) {
			if (g_pGame->m_OptionTab.bCleanBag) {

				if (!g_pGameControl->IsShowTransform(g_pGameControl->m_pBaseUIRoot)) return FALSE; 

				int iActId = g_pGame->m_iCurrentActivity;
				int iStatus = g_pGame->m_curActivity.iStatus;
				if (iActId == (int)act_pbtuchan && iStatus == 1) {
					m_dwTimeUtilityStarted = dwCurrentTime;
					return TRUE;
				}

				if (iActId == (int)act_pbhoanghon && iStatus == 1) {
					m_dwTimeUtilityStarted = dwCurrentTime;
					return TRUE;
				}

				if (iActId == (int)act_vantieubang && iStatus == 1) { //dang ap tieu
					if (!g_pGame->m_OptionTab.bVTCleanBag) {
						m_dwTimeUtilityStarted = dwCurrentTime;
						return TRUE;
					}

					if (g_pGame->m_OptionTab.bVTCleanBag) {
						m_dwTimeUtilityStarted = dwCurrentTime;
						//g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskCleanBag1());
						g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskCleanBag());
						
						return TRUE;
					}
					return TRUE;
				}

				m_dwTimeUtilityStarted = dwCurrentTime;
				//g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskCleanBag1());
				g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskCleanBag());
				return TRUE;
			}

			m_dwTimeUtilityStarted = dwCurrentTime;
		}
	}
	return FALSE;
}	

BOOL CTriggerActivity::IsOptimizeCPU()
{

	if (g_pGame->m_OptionTab.bOptimizeCPU) {
		LOG_WRITE("Optimize CPU checked...");
		CActiveSceneLogic *pActiveSceneLogic = CGameManager::get_CurActiveScene();
		if (pActiveSceneLogic) {
			float m_CurFPS = pActiveSceneLogic->get_CurFPS();
			
			if (!m_bSetFPS) {
				LOG_WRITE("m_bSetFPS = FALSE...");
				LOG_WRITE("iOptionFPS = %d...", g_pGame->m_OptionTab.iOptionFPS);
				if (g_pGame->m_OptionTab.iOptionFPS == 0) { //normal
					if (m_CurFPS <= 20) {
						LOG_WRITE("CApplication::set_targetFrameRate(30).................");
						CApplication::set_targetFrameRate(30);
					}
					m_bSetFPS = TRUE;
				}

				if (g_pGame->m_OptionTab.iOptionFPS == 1) { //medium
					if (m_CurFPS >= 22) {
						LOG_WRITE("CApplication::set_targetFrameRate(20).................");
						CApplication::set_targetFrameRate(20);
					}
					m_bSetFPS = TRUE;
				}

				if (g_pGame->m_OptionTab.iOptionFPS == 2) { //low
					if (m_CurFPS >= 17) {
						LOG_WRITE("CApplication::set_targetFrameRate(15).................");
						CApplication::set_targetFrameRate(15);
					}
					m_bSetFPS = TRUE;
				}

				if (g_pGame->m_OptionTab.iOptionFPS == 3) { //verylow
					if (m_CurFPS >= 12) {
						LOG_WRITE("CApplication::set_targetFrameRate(10).................");
						CApplication::set_targetFrameRate(10);
					}
					m_bSetFPS = TRUE;
				}
				return TRUE;
			}
			//DWORD dwCleanTime = g_pGame->m_OptionTab.iDeMinute * 60000;
			else {

				DWORD dwCurrentTime = g_pUEThread->GetTickCount();
				if (m_dwTimeResetFPS == 0) {
					m_dwTimeResetFPS = dwCurrentTime;
					return TRUE;
				}

				if (dwCurrentTime - m_dwTimeResetFPS >= 120000) {
					LOG_WRITE("set m_bSetFPS = FALSE");
					m_bSetFPS = FALSE;
					m_dwTimeResetFPS = dwCurrentTime;
					return TRUE;
				}

				//LOG_WRITE("m_CurFPS == %.2f, ----%d", m_CurFPS, dwCurrentTime - m_dwTimeResetFPS);
			}
		}

		
	}

	
	return FALSE;
}

BOOL CTriggerActivity::IsLackMana()
{

	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (!g_pGameControl->IsShowTransform(pBaseUIRoot)) return FALSE;
	CUE_Transform *pIcon = pBaseUIRoot->GetChildByPath(u"ChatFrameRoot:Offset:ChatTop:Grid:exhausted_Reserve");
	if (g_pGameControl->IsShowTransform(pIcon)) {

		
		if (CChatFrameController::IsbMPEmpty() || CChatFrameController::IsbHPEmpty()) { 

			if (g_pGame->m_OptionTab.bAutoBuyPatch2 && !g_pGameControl->IsBagFull()) {
				LOG_WRITE("CChatFrameController::IsbMPEmpty() || CChatFrameController::IsbHPEmpty()");

				if (!g_pGameControl->IsShowPopUI()) {
					g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskBuyPatch());
					return TRUE;
				}
			}
		}

		else if (CChatFrameController::IsbMPLack() || CChatFrameController::IsbHPLack()) { 
			if (g_pGame->m_OptionTab.bAutoBuyPatch ) {
				LOG_WRITE("CChatFrameController::IsbMPLack() || CChatFrameController::IsbHPLack()");
				if (!g_pGameControl->IsShowPopUI()) {
					g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGTaskBuyPatch());
					return TRUE;
				}
			}
		}
		
	}
		
	return FALSE;
}





