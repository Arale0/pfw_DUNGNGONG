#include "main.h"
#include "GTeamAlone.h"
#include "GSleep.h"

CGTeamAlone::CGTeamAlone() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTeamAlone()");
	m_bFinished = FALSE;
	m_iDelayClicked = 0;
	m_iLoopNext = 0;
	m_iChildFormList = 0;
}

CGTeamAlone::~CGTeamAlone()
{
	LOG_WRITE("DEL - CGTeamAlone()_");
	g_pGame->m_iCurrentID = -1;
}

int CGTeamAlone::Process()
{

	g_pGameControl->SetCurrentID(108);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	initTeam();
	get_CurrentActivityName();
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return Finished();
		return m_nStatus;
	}
	if (g_pGameControl->ProcessMessageBox(u"mời theo sau", MSG_OK)) return LoopNextSleep();

	if (g_pGameControl->IsCopySceneReady()) return Finished();

	if (g_pGameControl->IsButtonExitFuben()) return Finished();
	
	if (IsChatController()) return m_nStatus;

	ShowChatController();
	return LoopNextSleep();
}

int CGTeamAlone::LoopNextSleep( int delay /*= 1000*/ )
{
	AddSubGoal(new CGSleep(delay));
	//_theApp->NextTimer(delay);
	return LoopNext();
}

int CGTeamAlone::initTeam()
{
	if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_ALONE) return Finished();

	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		BOOL IsLeader = pPlayerData->PlayerIsTeamLeader();
		//da co doi
		if (IsLeader) {
			g_pGameControl->LeaveTeam();
			return LoopNextSleep();
		}
		
		if (g_pGameControl->IsMember()) {
			LOG_WRITE("Member ............");
			m_bFinished = TRUE;
			return LoopNextSleep();
		}
	}
	return m_nStatus;
}

BOOL CGTeamAlone::IsTeamWnd()
{
	CTeamController *pIns = CTeamController::Instance();
	if (pIns) {
		LOG_WRITE("IsTeamWnd...............");
		if (!g_pGameControl->IsHaveTeam()) g_pGameControl->CloseDialog();
		if (g_pGameControl->IsMember()) g_pGameControl->LeaveTeam();
		
		ActivityId ActID = g_pGame->m_iCurrentActivity;
		int iSLTV = g_pGame->m_TeamOption.iSLTV;
		if (ActID == act_phuongdegian) {
			g_pGameControl->IsTeamTarget(u"Phượng Đề Giản", FALSE);
			return TRUE;
		}

		if (ActID == act_phuongminhcoc) {
			g_pGameControl->IsTeamTarget(u"Phượng Minh Cốc", FALSE);
			return TRUE;
		}

		if (ActID == act_thuongthienphatac) {
			g_pGameControl->IsTeamTarget(u"Thưởng Thiện Phạt Ác", FALSE);
			return TRUE;
		}

		if (ActID == act_trucdietaclinh) {
			if (g_pGameControl->IsTeamEnoughMembers(iSLTV)) {m_bFinished = TRUE; return TRUE;}
			g_pGameControl->IsTeamTarget(u"Diệt Ác Linh", FALSE);
			return TRUE;
		}

		if (ActID == act_chientubang) {
			if (g_pGameControl->IsTeamEnoughMembers(iSLTV)) {m_bFinished = TRUE; return TRUE;}
			g_pGameControl->IsTeamTarget(u"Chiến Tu Tiên Bang", FALSE);
			return TRUE;
		}

		if (ActID == act_vantieubang) {
			if (g_pGameControl->IsTeamEnoughMembers(iSLTV)) {m_bFinished = TRUE; return TRUE;}
			g_pGameControl->IsTeamTarget(u"Bang áp tiêu", FALSE);
			return TRUE;
		}

		if (ActID == act_pbhoanghon) {
			int iDiffcult = g_pGame->m_OptionTab.iHHDifficult;

			if (iDiffcult == 0 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Sơ Thám")) return TRUE;
			if (iDiffcult == 1 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Không")) return TRUE;
			if (iDiffcult == 2 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Phá")) return TRUE;
			if (iDiffcult == 3 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Diệt")) return TRUE;
			if (iDiffcult == 4 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Nguyên")) return TRUE;
			if (iDiffcult == 5 && g_pGameControl->IsTeamTarget("Hoàng Hôn-Chân")) return TRUE;
			return TRUE;
		}
		
		if (ActID == act_pbtuchan) {
			int iDiffcult = g_pGame->m_OptionTab.iTCDifficult;
			if (iDiffcult == 0 && g_pGameControl->IsTeamTarget(u"Thanh Y Chủng")) return TRUE;
			if (iDiffcult == 1 && g_pGameControl->IsTeamTarget(u"Cốc Thiên Kiếp")) return TRUE;
			if (iDiffcult == 2 && g_pGameControl->IsTeamTarget(u"Oán Linh Môn")) return TRUE;
			if (iDiffcult == 3 && g_pGameControl->IsTeamTarget(u"Hang Báu Vật")) return TRUE;
			if (iDiffcult == 4 && g_pGameControl->IsTeamTarget(u"Tiên Ma Ảo Thiên")) return TRUE;
			//if (iDiffcult == 5 && g_pGameControl->IsTeamTarget(u"Đào Nguyên Luyện Ngục")) return TRUE;
			if (iDiffcult == 5 && g_pGameControl->IsTeamTarget(u"Thanh Y Chủng-Ngục")) return TRUE;
			if (iDiffcult == 7 && g_pGameControl->IsTeamTarget(u"Phiêu Miểu Tiên Cư")) return TRUE;
			if (iDiffcult == 8 && g_pGameControl->IsTeamTarget(u"Cốc Thiên Kiếp-Thần")) return TRUE;
			if (iDiffcult == 9 && g_pGameControl->IsTeamTarget(u"Oán Linh Môn-Quỷ")) return TRUE;
			return TRUE;
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CGTeamAlone::IsChatController()
{
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pChatRoot = pPopUIRoot->GetChildByName(u"chat.chatroot");
		if (!pChatRoot) return FALSE;
		if (g_pGameControl->IsShowTransform(pChatRoot)) {
			m_iDelayClicked = 1;
			CUE_Transform *pChieuMoTab = pChatRoot->GetChildByPath(u"Offset:chat:Offset:MainModuleOpen:MainModule:ChannalObj:List Of Left:GameObject:Grid:tabchannel12-Recruit");//g_pGameControl->getTransformFromString("tabchannel12-Recruit");
			//CUE_Transform *pChieuMoTab = g_pGameControl->getTransformFromString(pChatRoot, "tabchannel12-Recruit");
			if (!pChieuMoTab) return FALSE;
			if (!g_pGameControl->IsShowTransform(pChieuMoTab)) return FALSE; 
			//CUE_Transform *pPress = pChieuMoTab->GetChildByName(u"Press");
			CUE_Transform *pNormal = pChieuMoTab->GetChildByName(u"Normal");
			if (g_pGameControl->IsShowTransform(pNormal)) {
				g_pGameControl->Clicked(pChieuMoTab);
				LoopNextSleep();
				return TRUE;
			}

			//pChieuMoTab is showed
			CUE_Transform *pContent = pChatRoot->GetChildByPath(u"Offset:chat:Offset:MainModuleOpen:MainModule:Frame:ChatContent");//g_pGameControl->getTransformFromString("ChatContent");
			//CUE_Transform *pContent = g_pGameControl->getTransformFromString(pChatRoot, "ChatContent");
			if (!pContent) return FALSE;
			if (!g_pGameControl->IsShowTransform(pContent)) return FALSE; 
			CUE_Transform *pList = pContent->GetChildByPath(u"GameObject:ItemTable");
			if (!pList) return FALSE;
			int iCount  = pList->get_childCount();
			if (iCount != 0) {
				if (m_iChildFormList < 0) {

					if (m_iLoopNext <= 0) m_iChildFormList = iCount - 1;
					if (m_iLoopNext >= 5) {
						m_iChildFormList = iCount - 1;
						m_iLoopNext = 0;
						return TRUE;
					}

					m_iLoopNext ++;
					LOG_WRITE("iLoopNext == %d", m_iLoopNext);
					LoopNextSleep();

					return TRUE;
				}
				CUE_Transform *pChild = pList->GetChild(m_iChildFormList);
				if (pChild) {
					CUE_Transform *pTextContent = pChild->GetChildByName(u"content");
					CStdStringU czTextContent = g_pGameControl->GetTextU(pTextContent);
					if (czTextContent.Find(m_czActiviyName) >= 0) {
						CUE_Transform *pLink = pTextContent->GetChildByName(u"ChatLinkItem(Clone)");
						CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","ChatLinkItem");
						CChatLinkItem* pChatLink = (CChatLinkItem *)pLink->GetComponent(pType);
						if (pChatLink) {
							LOG_WRITE("Yesssssssssssssssssssssss %d %s", m_iChildFormList, _U2A(m_czActiviyName).c_str());
							m_iChildFormList = m_iChildFormList - 1;
							pChatLink->OnBtnClick();
							LoopNextSleep(1500);
							return TRUE;
						}
					}
					else {
						//LOG_WRITE("NOOOOOOOOOOOOOOOOOO %d %s", m_iChildFormList, _U2A(czTextContent).c_str());
						m_iChildFormList = m_iChildFormList - 1;
					}
				}
				return TRUE;
			}
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}
		

void CGTeamAlone::ShowChatController()
{
	CChatFrameController *pIns	 = CChatFrameController::Instance();
	if (!pIns) return;
	if (m_iDelayClicked <= 0) {
		LOG_WRITE("CGTeamAlone::ShowChatController()................");
		pIns->OnChatInfoClick();
	}

	if (m_iDelayClicked >= 5) m_iDelayClicked = -1;
	m_iDelayClicked ++;
	LoopNextSleep();
}

void CGTeamAlone::get_CurrentActivityName()
{
	ActivityId iCurrentActivity = g_pGame->m_iCurrentActivity;
	if (iCurrentActivity == act_thuongthienphatac) m_czActiviyName = u"Thưởng Thiện Phạt Ác";
	if (iCurrentActivity == act_phuongdegian) m_czActiviyName = u"Phượng Đề Giản";
	if (iCurrentActivity == act_phuongminhcoc) m_czActiviyName = u"Phượng Minh Cốc";
	if (iCurrentActivity == act_vantieubang) m_czActiviyName = u"Vận Tiêu Bang";
	if (iCurrentActivity == act_trucdietaclinh) m_czActiviyName = u"Trục Diệt Ác Linh";
	if (iCurrentActivity == act_thosantienthuong)m_czActiviyName = u"Thợ Săn Tiền Thưởng";
	if (iCurrentActivity == act_pbhoanghon) {
		int iDiffcult = g_pGame->m_OptionTab.iHHDifficult;
		if (iDiffcult == 0) m_czActiviyName = u"Hoàng Hôn-Sơ Thám";
		if (iDiffcult == 1) m_czActiviyName = u"Hoàng Hôn-Không";
		if (iDiffcult == 2) m_czActiviyName = u"Hoàng Hôn-Phá";
		if (iDiffcult == 3) m_czActiviyName = u"Hoàng Hôn-Diệt";
		if (iDiffcult == 4) m_czActiviyName = u"Hoàng Hôn-Nguyên";
		if (iDiffcult == 5) m_czActiviyName = u"Hoàng Hôn-Chân";
	}
	if (iCurrentActivity == act_pbtuchan){
		int iDiffcult = g_pGame->m_OptionTab.iTCDifficult;
		if (iDiffcult == 0) m_czActiviyName = u"Thanh Y Chủng";
		if (iDiffcult == 1) m_czActiviyName = u"Cốc Thiên Kiếp";
		if (iDiffcult == 2) m_czActiviyName = u"Oán Linh Môn";
		if (iDiffcult == 3) m_czActiviyName = u"Hang Báu Vật";
		if (iDiffcult == 4) m_czActiviyName = u"Tiên Ma Ảo Thiên";
		if (iDiffcult == 5) m_czActiviyName = u"Thanh Y Chủng-Ngục";
	}
}

void CGTeamAlone::OnClickLink(CUE_Transform *pList, int iChild)
{	
	if (!pList) return;
	CUE_Transform *pChild = pList->GetChild(iChild);
	if (pChild) {
		CUE_Transform *pTextContent = pChild->GetChildByName(u"content");
		CStdStringU czTextContent = g_pGameControl->GetTextU(pTextContent);
		if (czTextContent.Find(m_czActiviyName) >= 0) {
			CUE_Transform *pLink = pTextContent->GetChildByName(u"ChatLinkItem(Clone)");
			CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","ChatLinkItem");
			CChatLinkItem* pChatLink = (CChatLinkItem *)pLink->GetComponent(pType);
			if (pChatLink) {
				LOG_WRITE("Yesssssssssssssssssssssss %d %s", iChild, _U2A(m_czActiviyName).c_str());
				LoopNextSleep(1000);
				//pChatLink->OnBtnClick();
			}
		}
	}
	LoopNextSleep(1000);
	
}

