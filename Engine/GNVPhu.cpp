﻿#include "main.h"
#include "GNVPhu.h"

CGNVPhu::CGNVPhu() :CGActivity()
{
	LOG_WRITE("NEW - CGNVPhu()");
	m_activity = act_nvphu;
	m_iDelay  = -1;
	m_bSub = FALSE;
	m_iWaitForFinished = 0;
	m_bFinished = FALSE;
	m_iRoleStand = 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGNVPhu::~CGNVPhu()
{
	LOG_WRITE("DEL - CGNVPhu()");
}

int CGNVPhu::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGNVPhu::Process()....");
		if (m_bFinished) return FinishedActivity();
		if (g_pGameControl->IsCenterNotice(u"Mở khóa thất bại,")) m_bSub = TRUE; 
		if (g_pGameControl->ProcessMessageBox(u"Thoát phó bản?", MSG_OK)) return LoopNextSleep();
		if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep();
		if (g_pGameControl->IsMoving()) return LoopNextSleep();
		if (isNewGuilde()) return LoopNextSleep();
		if (IsAnswer()) return LoopNextSleep();
		if (IsChooseLogic()) return LoopNextSleep();

		processMain();
		return LoopNextSleep(1000);

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGNVPhu::processMain()
{

	g_pGameControl->CloseDialog();
	CMissionTrack *pIns = CMissionTrack::Instance();
	if (pIns) {
		CUE_Transform *pPanel = g_pGameControl->get_Transform(UINT(pIns));
		CUE_Transform *pGrid = pPanel->GetChildByName(u"Grid");
		int i = 0;
		int iCount = pGrid->get_childCount();
		for (i = 0; i < iCount; i++) {
			CUE_Transform *pChild = pGrid->GetChild(i);
			if (pChild) {
				CStdStringU czNameMainQuest = pChild->GetName()->GetText();
				if (czNameMainQuest.Compare(u"0") != 0) {
					CUE_Transform *pname = pChild->GetChildByPath(u"Offest:Sprite:TypeLabel");
					CUE_Transform *pNameAct = pChild->GetChildByPath(u"Offest:Label");
					CUE_Transform *pContent = pChild->GetChildByPath(u"Offest:Label0");
					CStdStringU czName =  g_pGameControl->GetTextU(pname);
					CStdStringU czNameAct = g_pGameControl->GetTextU(pNameAct);
					CStdStringU czContent = g_pGameControl->GetTextU(pContent);

					if (czName.Compare(u"[Phụ]") == 0) {

						if (czContent.Find(u"Tìm Ấn Bá Chủ") >= 0 && !g_pGameControl->IsHaveGuild()) continue;
						if (czContent.Find(u"[c][5aef8e]") >= 0) {
							m_uActivity = (UINT)pChild;
							processActivity();
							return;
						}
					}
				}
			}
		}

		//tim nhiem vu chua mo
		for (int j = 0; j < iCount; j++) {
			CUE_Transform *pChild = pGrid->GetChild(j);
			if (pChild) {
				CStdStringU czNameMainQuest = pChild->GetName()->GetText();
				if (czNameMainQuest.Compare(u"0") != 0) {
					CUE_Transform *pname = pChild->GetChildByPath(u"Offest:Sprite:TypeLabel");
					CUE_Transform *pNameAct = pChild->GetChildByPath(u"Offest:Label");
					CUE_Transform *pContent = pChild->GetChildByPath(u"Offest:Label0");
					CStdStringU czName =  g_pGameControl->GetTextU(pname);
					CStdStringU czNameAct = g_pGameControl->GetTextU(pNameAct);
					CStdStringU czContent = g_pGameControl->GetTextU(pContent);

					if (czName.Compare(u"[Phụ]") == 0) {
						if (czNameAct.Find(u"Thợ Giỏi") >= 0) continue;
						if (czNameAct.Find(u"Thăm Bạn") >= 0) continue;
						if (czNameAct.Find(u"Kết bái huynh đệ") >= 0) continue;
						if (czNameAct.Find(u"Linh hoạt") >= 0) continue;
						if (czNameAct.Find(u"Hỏi Trời") >= 0) continue;
						if (czContent.Find(u"Mở Ấn Bá Chủ") >= 0) continue;
						if (czContent.Find(u"Tìm Ấn Bá Chủ") >= 0 && !g_pGameControl->IsHaveGuild()) continue;

						
						LOG_WRITE("[+] Content:	%s", _U2A(czContent).c_str());
						if (czContentTemp != czContent) {
							m_iWaitForFinished = 0;
							m_iRoleStand = 0;
							czContentTemp = czContent;
						}

						if (czContent == czContentTemp && !g_pGameControl->IsMoving() && !g_pGameControl->IsButtonExitFuben()) {
							LOG_WRITE("Role is standing ....%d", m_iRoleStand);
							if (m_iRoleStand >= 20) m_bFinished = TRUE;
							m_iRoleStand ++;
						}

						m_uActivity = (UINT)pChild;
						processActivity();
						return;					
					}
				}
			}
		}

		LOG_WRITE("********************************************************");
		if (!g_pGameControl->IsMoving()) {
			if (m_iWaitForFinished >= 10) {
				m_bFinished = TRUE;
				return;
			}
			LOG_WRITE("wait for Finished --> %d", m_iWaitForFinished);
			m_iWaitForFinished ++;
		}
	}
}

void CGNVPhu::processActivity()
{
	CUE_Transform *pActivity = (CUE_Transform*)m_uActivity;
	if (!pActivity) return;
	if (m_iDelay <= 0) {
		g_pGameControl->MissionClicked(pActivity);
	}

	if (g_pGameControl->IsMoving()) return;

	if (m_iDelay >= 5) {
		m_iDelay = -1;
		return;
	}
	m_iDelay ++;
}

BOOL CGNVPhu::isNewGuilde()
{
	CUE_Transform *pBase = g_pGameControl->m_pMessageUIRoot;
	if (!pBase) return FALSE;
	CUE_Transform *pGuide = pBase->GetChildByName(u"newbieguide");
	if (g_pGameControl->IsShowTransform(pGuide)) {
		CUE_Transform *pOffset = pGuide->GetChildByName(u"Offset");
		if (!g_pGameControl->IsShowTransform(pOffset)) return FALSE;

		m_iRoleStand = 0;
		m_iWaitForFinished = 0;
		CUE_Transform *pBox = pGuide->GetChildByPath(u"Offset:Box");
		if (g_pGameControl->IsShowTransform(pBox)) {
			LOG_WRITE("TAp Box......");
			g_pGameControl->Tap(pBox);
			return TRUE;
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CGNVPhu::IsChooseLogic()
{
	CMisChooseLogic *pIns = CMisChooseLogic::Instance();
	if (pIns) {
		LOG_WRITE("Click Left....................");
		pIns->ClickLeft();
		return TRUE;
	}
	return FALSE;
}
BOOL CGNVPhu::IsAnswer()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"synopsis.synopsisqa"); 
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	CUE_Transform *pBtn = p1->GetChildByPath(u"Offset:choice4:Grid:Answer1:Label");
	if (!pBtn) return FALSE;
	LOG_WRITE("Answerrrrrrrrrrrr");
	g_pGameControl->Clicked(pBtn);
	return TRUE;
}



