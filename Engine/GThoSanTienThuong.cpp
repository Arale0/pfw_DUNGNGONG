#include "main.h"
#include "GThoSanTienThuong.h"
#include "GTaskKetBai.h"

CGThoSanTienThuong::CGThoSanTienThuong() :CGActivity()
{
	LOG_WRITE("NEW - CGThoSanTienThuong()");
	m_activity = act_thosantienthuong;
	//m_czBossName = u"Thanh Y Tử";
	m_iDelayClicked = -1;
	m_bJiebai = FALSE;
	m_bShowBountyMain = FALSE;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGThoSanTienThuong::~CGThoSanTienThuong()
{
	LOG_WRITE("DEL - CGThoSanTienThuong()");
}

int CGThoSanTienThuong::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGThoSanTienThuong::Process()....");
		initNameBoss();
		
		if (g_pGameControl->IsMoving()) {m_iDelayClicked = 0; return LoopNextSleep();}
		
		if (IsBountyMain()) return LoopNextSleep();

		if (g_pGameControl->IsShowTargetBar(m_czBossName)) {
			LOG_WRITE("IsShowTargetBar.....%s", _U2A(m_czBossName).c_str());
			m_iDelayClicked = 0;
			if (g_pGameControl->AutoFightIsOn()) g_pGameControl->SwitchAutoFight(ON);
			processLeader();
			return LoopNextSleep();
		}

		CObj_Char *pNPC = g_pGameControl->getNPC(m_czBossName);
		if (pNPC) {
			LOG_WRITE("YEsssssssssssssssssssssssssssssss");
			if (g_pGameControl->IsFollowLeader()) {
				g_pGameControl->FollowLeader(OFF);
				return LoopNextSleep();
			}
			g_pGameControl->SwitchAutoFight(ON);
			CObj_MainPlayer *pPlayer = g_pGameControl->get_MainPlayer();
			if (pPlayer) pPlayer->MoveToTarget(pNPC);
			return LoopNextSleep();
		}

		if (g_pGameControl->IsMember()) {
			processMember();
			return LoopNextSleep();
		}

		ShowBountyMain();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGThoSanTienThuong::IsBountyMain()
{
	CUIBounty_Main *pIns = CUIBounty_Main::Instance();
	if (pIns) {
		m_iDelayClicked = 0;
		CSYS_List *pListBossItem = pIns->get_UIBounty_BossItem();
		if (pListBossItem) {
			int iCount = pListBossItem->get_Count();
			if (iCount == 0) return LoopNextSleep();
			CStdStringU czCombatValue = pIns->get_CombatValue();
			if (g_pGame->m_OptionTab.iTSTTBossLevel == 0) {
				if (czCombatValue.Compare(u"60000") != 0) {
					CUIBounty_BossItem *pBossItem = (CUIBounty_BossItem*)pListBossItem->get_Item(0);
					LOG_WRITE("Click Boss....%s", _U2A(m_czBossName).c_str());
					if (pBossItem) {
						pBossItem->OnClick();
						g_pGameControl->CloseDialog();
					}
					CloseDialogIfShow();
					return TRUE;
				}
			}

			if (g_pGame->m_OptionTab.iTSTTBossLevel == 1) {
				if (czCombatValue.Compare(u"90000") != 0) {
					CUIBounty_BossItem *pBossItem = (CUIBounty_BossItem*)pListBossItem->get_Item(1);
					LOG_WRITE("Click Boss....%s", _U2A(m_czBossName).c_str());
					if (pBossItem) {
						pBossItem->OnClick();
						g_pGameControl->CloseDialog();
					}
					CloseDialogIfShow();
					return TRUE;
				}
			}

			if (g_pGame->m_OptionTab.iTSTTBossLevel == 2) {
				if (czCombatValue.Compare(u"130000") != 0) {
					CUIBounty_BossItem *pBossItem = (CUIBounty_BossItem*)pListBossItem->get_Item(2);
					LOG_WRITE("Click Boss....%s", _U2A(m_czBossName).c_str());
					if (pBossItem) {
						pBossItem->OnClick();
						g_pGameControl->CloseDialog();
					}
					CloseDialogIfShow();
					return TRUE;
				}
			}

			if (g_pGame->m_OptionTab.iTSTTBossLevel == 3) {
				if (czCombatValue.Compare(u"170000") != 0) {
					CUIBounty_BossItem *pBossItem = (CUIBounty_BossItem*)pListBossItem->get_Item(3);
					LOG_WRITE("Click Boss....%s", _U2A(m_czBossName).c_str());
					if (pBossItem) {
						pBossItem->OnClick();
						g_pGameControl->CloseDialog();
					}
					CloseDialogIfShow();
					return TRUE;
				}
			}

			if (g_pGame->m_OptionTab.iTSTTBossLevel == 4) {
				if (czCombatValue.Compare(u"250000") != 0) {
					CUIBounty_BossItem *pBossItem = (CUIBounty_BossItem*)pListBossItem->get_Item(4);
					LOG_WRITE("Click Boss....%s", _U2A(m_czBossName).c_str());
					if (pBossItem) {
						pBossItem->OnClick();
						g_pGameControl->CloseDialog();
					}
					CloseDialogIfShow();
					return TRUE;
				}
			}
			

			CSYS_List *pListBossDetail = pIns->get_UIBounty_DetailInfo();
			if (pListBossDetail) {
				int iCountBossDetail = pListBossDetail->get_Count();
				if (iCountBossDetail != 0) {
					for (int i = 0; i < iCountBossDetail; i++ ) {
						CUIBounty_DetailInfo *pBossDetailInfo = (CUIBounty_DetailInfo*)pListBossDetail->get_Item(i);
						CStdStringU czName = pBossDetailInfo->get_PosLabel();
						if (czName.Compare(u"Đang hỗn loạn") != 0) {
							LOG_WRITE("Click Boss Position............");
							pBossDetailInfo->OnClick();
							return TRUE;
						}
						//LOG_WRITE("Name = [%s]", _U2A(czName).c_str());
					}

				}
				LOG_WRITE("End..................");
			}
			/*for (int i = 0; i < iCount; i++) {
				CUIBounty_BossItem *pBossItem = (CUIBounty_BossItem*)pListBossItem->get_Item(i);
				CStdStringU czName = pBossItem->get_NameLabel();
				CStdStringU csLevel = pBossItem->get_LevelLabel();
				CUE_Transform *pTransform  = g_pGameControl->get_Transform((UINT)pBossItem);
				int iNeedLevel = atoi(_U2A(csLevel).c_str());
				LOG_WRITE("ins[%08X], trans[%08X], czName = %s, Level = %d", pBossItem, pTransform, _U2A(czName).c_str(), iNeedLevel);
			}
			LOG_WRITE("End..................");*/
		}
		return TRUE;
	}
	return FALSE;
}

void CGThoSanTienThuong::ShowBountyMain()
{
	if (g_pGameControl->IsShowPopUI()) {
		g_pGameControl->Tap(1,1);
		g_pGameControl->CloseDialog();
		return;
	}

	LOG_WRITE("CGThoSanTienThuong::ShowBountyMain()..........%d", m_iDelayClicked);
	
	if (g_pGameControl->IsMember()) return;

	if (m_iDelayClicked <= 0 && !m_bShowBountyMain) {
		m_bShowBountyMain = TRUE;
		CActivityHuoDongWindow::OnClickGoActivityBtnByActivityId(2040, 1);
	}
	if (m_iDelayClicked >= 6) {m_bShowBountyMain = FALSE;m_iDelayClicked = -1;}
	m_iDelayClicked ++;
	LoopNextSleep();
}

void CGThoSanTienThuong::processMember()
{
	if (g_pGameControl->IsHasTeam()) {
		CStdStringU czLeader = g_pGameControl->get_NameLeader();
		if (!g_pGameControl->IsNearPlayer(czLeader)) {
			g_pGameControl->FollowLeader(ON);
			return;
		}

		if (IsLeaderAutoFight()) {
			if (g_pGameControl->IsFollowLeader()) {
				g_pGameControl->FollowLeader(OFF);
			}
			else g_pGameControl->SwitchAutoFight(ON);
			LoopNextSleep(500);
		}

		if (!IsLeaderAutoFight()) {
			if (g_pGameControl->AutoFightIsOn()) {
				g_pGameControl->SwitchAutoFight(OFF);
			}
			else if (!g_pGameControl->IsFollowLeader()) {
				g_pGameControl->FollowLeader(ON);
			}
			LoopNextSleep(500);
		}
		return;
	}
	LOG_WRITE("No team.................");
}

BOOL CGThoSanTienThuong::IsLeaderAutoFight()
{
	if(CTeamList::Instance() == 0) {
		g_pGameControl->OnTeamTabClick();
		return FALSE;
	}

	CUE_Transform *pIconAutoFight = g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"BaseUIRoot:LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem:Team01 (1):Main:RightBtn:Table:RealTimeState:tuoguan");

	if (g_pGameControl->IsShowTransform(pIconAutoFight)) return TRUE;
	return FALSE;
}

void CGThoSanTienThuong::processLeader()
{
	if (g_pGameControl->IsTeamLeader()) {

		if (g_pGameControl->IsLeaderSet() && !m_bJiebai) {
			m_bJiebai = TRUE;
			AddSubGoal(new CGTaskKetBai());
			return;
		}

		if (g_pGameControl->IsNotEnoughMembers()) return;

		return;
	}
}

void CGThoSanTienThuong::initNameBoss()
{
	if (g_pGame->m_OptionTab.iTSTTBossLevel == 0) m_czBossName = u"Thanh Y Tử";
	if (g_pGame->m_OptionTab.iTSTTBossLevel == 1) m_czBossName = u"Câu Mang";
	if (g_pGame->m_OptionTab.iTSTTBossLevel == 2) m_czBossName = u"Thao Thiết";
	if (g_pGame->m_OptionTab.iTSTTBossLevel == 3) m_czBossName = u"Nhện Mặt Quỷ";
	if (g_pGame->m_OptionTab.iTSTTBossLevel == 4) m_czBossName = u"Rắn Chúa";
}

void CGThoSanTienThuong::CloseDialogIfShow()
{
	if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
}



