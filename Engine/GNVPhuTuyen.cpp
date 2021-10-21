#include "main.h"
#include "GNVPhuTuyen.h"

CGNVPhuTuyen::CGNVPhuTuyen() :CGActivity()
{
	LOG_WRITE("NEW - CGNVPhuTuyen()");
	m_activity = act_phutuyen;
	iDelay  = -1;
	m_iMission = -1;
	m_bFinished = FALSE;
	m_bFindQuetsDone = FALSE;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGNVPhuTuyen::~CGNVPhuTuyen()
{
	LOG_WRITE("DEL - CGNVPhuTuyen()");
}

int CGNVPhuTuyen::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGNVPhuTuyen::Process()....");

		if (m_bFinished) return FinishedActivity();
		if (g_pGameControl->ProcessMessageBox(u"Thoát phó bản?", MSG_OK)) return LoopNextSleep();
		if (g_pGameControl->IsStoryUIRoot()) return LoopNextSleep();
		if (IsChooseLogic()) return LoopNextSleep();
		if (IsAnswer()) return LoopNextSleep();
		if (g_pGameControl->IsMoving()) return LoopNextSleep();

		/*if (m_iMission == TUCHAN) {
			getMission(u"Tu");
			getMission(u"Thần");
			getMission(u"Dẫn");
			return LoopNextSleep();
		}

		if (m_iMission == THAN) {
			getMission(u"Thần");
			return LoopNextSleep();
		}

		if (m_iMission == DU) {
			getMission(u"Dẫn");
			return LoopNextSleep();
		}*/

		getActivity();

		/*if (g_pGameControl->IsMissionTrack(u"Phụ", m_uActivity)) {
			processActivity();
			return LoopNextSleep();
		} */

		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGNVPhuTuyen::processActivity()
{
	CUE_Transform *pActivity = (CUE_Transform*)m_uActivity;
	if (!pActivity) return;
	if (iDelay <= 0) {
		g_pGameControl->MissionClicked(pActivity);
	}
	
	if (g_pGameControl->IsMoving()) return;

	if (iDelay >= 5) {
		iDelay = -1;
		return;
	}
	iDelay ++;
	if (m_iMission != TUCHAN) LoopNextSleep();
}

BOOL CGNVPhuTuyen::IsAnswer()
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

void CGNVPhuTuyen::getActivity()
{
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

					if (czContent.Find(u"[c][5aef8e]") >= 0) {
						//bFindQuetsDone = TRUE;
						LOG_WRITE("Content ==> %s", _U2A(czContent).c_str());
						m_uActivity = (UINT)pChild;
						processActivity();
						return;
					}
					
					if (m_bFindQuetsDone) {

						static BOOL bExit = FALSE;

						if (czNameAct.Find(u"Cốc Thiên Kiếp") <= 0 &&
							czNameAct.Find(u"Thanh Y Chủng") <= 0 &&
							czNameAct.Find(u"Oán Linh Môn") <= 0 &&
							czNameAct.Find(u"Hang Báu Vật") <= 0 &&
							czNameAct.Find(u"Linh hoạt") <= 0 && 
							czNameAct.Find(u"Trẻ con mất tích") <= 0 &&
							czNameAct.Find(u"Thức Tỉnh") <= 0 &&
							czNameAct.Find(u"Điều kiện Kết Hôn") <= 0 &&
							czNameAct.Find(u"Đúc lại") <= 0 &&
							czNameAct.Find(u"Đến Gia Viên") <= 0 &&
							czNameAct.Find(u"Thưởng Thiện") <= 0 &&
							czNameAct.Find(u"Hang Báu Vật") <= 0 &&
							czNameAct.Find(u"Kỹ Năng Hóa") <= 0 &&
							czNameAct.Find(u"Trật Tự Ngũ Hành") <= 0 &&
							czNameAct.Find(u"Kết Nghĩa Huynh Đệ") <= 0 &&
							czNameAct.Find(u"Tranh Bá Thiên Hạ") <= 0 &&
							czNameAct.Find(u"Tìm Hiểu Anh Hồn") <= 0 &&
							czNameAct.Find(u"3 Vật") <= 0 &&
							czNameAct.Find(u"Hạt Oán Linh") <= 0 &&
							czNameAct.Find(u"Hướng dẫn Quyết Đấu") <= 0 &&
							(czNameAct.Find(u"Thiên Mệnh Thần Dụ") <= 0 && czContent.Find(u"Chờ Ngày Mai") <= 0) &&
							czNameAct.Find(u"Góp trang bị") <= 0 &&
							czNameAct.Find(u"Hỏi Trời") <= 0 &&
							czNameAct.Find(u"Thủ Công Tinh Xảo") <= 0 &&
							czNameAct.Find(u"Tham Lam") <= 0 &&
							czNameAct.Find(u"Thức Tỉnh") <= 0 &&
							czNameAct.Find(u"Chế Linh Dược") <= 0 &&
							czNameAct.Find(u"Trở Về Quá Khứ") <= 0) {
								m_uActivity = (UINT)pChild;
								LOG_WRITE("czNAme[%s]", _U2A(czNameAct).c_str());
								if (g_pGameControl->IsButtonExitFuben()) {
									g_pGameControl->SwitchAutoFight(ON);
									if (czNameAct.Find(u"Thức Vật") >= 0) g_pGameControl->SwitchAutoFight(ON);
									if (bExit) {
										g_pGameControl->ExitFB();
										return;
									}

									if (czContent.Find(u"Tìm Ấn Bá Chủ") >= 0 && !bExit) {
										if (g_pGameControl->IsMap(u"Vực Thẳm Vô Đáy")) {
											if (g_pGameControl->IsShowReliveWnd()) bExit = TRUE;
											g_pGameControl->SwitchAutoFight(ON);
										}
									}
								}
								if (!bExit) processActivity();
								return;
						}
					}

					/*static BOOL bExit = FALSE;
					if (czName.Find(u"Phụ") >= 0) {
						if (czNameAct.Find(u"Linh hoạt") <= 0 && 
							czNameAct.Find(u"Trẻ con mất tích") <= 0 &&
							czNameAct.Find(u"Thức Tỉnh") <= 0) {
								m_uActivity = (UINT)pChild;

								if (g_pGameControl->IsButtonExitFuben()) {
									if (czNameAct.Find(u"Thức Vật") >= 0) g_pGameControl->SwitchAutoFight(ON);
									if (bExit) {
										g_pGameControl->ExitFB();
										return;
									}

									if (czContent.Find(u"Tìm Ấn Bá Chủ") >= 0 && !bExit) {
										if (g_pGameControl->IsMap(u"Vực Thẳm Vô Đáy")) {
											if (g_pGameControl->IsShowReliveWnd()) bExit = TRUE;
											g_pGameControl->SwitchAutoFight(ON);
										}
									}
								}
								if (!bExit) processActivity();
								return;
						}
					}*/
				}
			}
		}

		if (i >= iCount) {
			if (!m_bFindQuetsDone) {
				m_bFindQuetsDone = TRUE;
				return;
			}
			LOG_WRITE("m_bFinished = TRUE...........%d", m_iMission);
			m_bFinished = TRUE;
			return;
			/*if (m_iMission == -1) {
				m_iMission = TUCHAN;
				return;
			}

			if (m_iMission == TUCHAN) {
				m_iMission = THAN;
				return;
			}

			if (m_iMission == TUCHAN) {
				m_iMission = DU;
				return;
			}*/

			/*if (m_iMission == TUCHAN) {
				m_bFinished = TRUE;
				return;
			}*/
		}
	}
}

BOOL CGNVPhuTuyen::IsChooseLogic()
{
	CMisChooseLogic *pIns = CMisChooseLogic::Instance();
	if (pIns) {
		LOG_WRITE("Click Left....................");
		pIns->ClickLeft();
		return TRUE;
	}
	return FALSE;
}

void CGNVPhuTuyen::getMission( CStdStringU czType )
{

	CMissionTrack *pIns = CMissionTrack::Instance();
	if (pIns) {
		CUE_Transform *pPanel = g_pGameControl->get_Transform(UINT(pIns));
		CUE_Transform *pGrid = pPanel->GetChildByName(u"Grid");
		int i = 0;
		int iCount = pGrid->get_childCount();
		for (i = 0; i < iCount; i++) {
			CUE_Transform *pChild = pGrid->GetChild(i);
			if (pChild) {
				CUE_Transform *pname = pChild->GetChildByPath(u"Offest:Sprite:TypeLabel");
				CUE_Transform *pNameAct = pChild->GetChildByPath(u"Offest:Label");
				CUE_Transform *pContent = pChild->GetChildByPath(u"Offest:Label0");
				CStdStringU czNameType =  g_pGameControl->GetTextU(pname);
				CStdStringU czNameAct = g_pGameControl->GetTextU(pNameAct);
				CStdStringU czContent = g_pGameControl->GetTextU(pContent);

				if (czNameType.Find(czType) >= 0) {
					if (czNameAct.Find(u"Cốc Thiên Kiếp") <= 0 &&
						czNameAct.Find(u"Thanh Y Chủng") <= 0 &&
						czNameAct.Find(u"Oán Linh Môn") <= 0 &&
						czNameAct.Find(u"Hang Báu Vật") <= 0 
						/*&&czNameAct.Find(u"Oán Linh") <= 0*/) {
						
						LOG_WRITE("czNAme[%s]", czNameAct.c_str());
						m_uActivity = (UINT)pChild;
						processActivity();
						return;
					}
				}
			}
		}

		if (i >= iCount) {
			LOG_WRITE("aaaaaaaaaaaaaaaaa");

			if (m_iMission == -1) {
				m_iMission = TUCHAN;
				return;
			}

			if (m_iMission == DU) {
				m_bFinished = TRUE;
				return;
			}
		}
	}
}



