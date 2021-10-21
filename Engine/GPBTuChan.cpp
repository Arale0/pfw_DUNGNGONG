#include "main.h"
#include "GPBTuChan.h"
#include "GTaskKetBai.h"
#include "GTeamAlone.h"
CGPBTuChan::CGPBTuChan() :CGActivity()
{
	LOG_WRITE("NEW - CGPBTuChan()");
	m_activity = act_pbtuchan;
	m_iDelayClicked		= 0;
	m_iCountTime		= 0;
	m_iShowMap			= 0;
	m_iMoveToPos		= 0;
	m_bShowMap			= FALSE;
	m_bFinished			= FALSE;
	m_bShowWnd			= FALSE;
	m_bJiebai			= FALSE;
	m_bCountTime		= FALSE;
	m_bTeamAlone		= FALSE;
	m_bTransDoor		= FALSE;
	m_screenHeight      = 0;
	m_screenWidth		= 0;
	m_iCloseMap			= 0;
	m_iCountNPC			= 0;
	m_bHBV = FALSE;
	m_bGone = FALSE;

	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGPBTuChan::~CGPBTuChan()
{
	LOG_WRITE("DEL - CGPBTuChan()");
	ZeroMemory(&g_pGame->m_SyncValues,sizeof(SYNCVALUES));	
}

int CGPBTuChan::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGPBTuChan::Process()....%d", m_iCountTime);
		initEmulatorSize();

		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();
		if (g_pGameControl->IsCopySceneReady()) return LoopNextSleep();
		if (IsFinished()) return m_nStatus;
		if (!IsInMaple()) m_iCloseMap = 0;
		if (IsInMaple()) return LoopNextSleep();
		if (IsNPCDialog()) return LoopNextSleep();
		if (IsInFb()) return LoopNextSleep();
		if (IsTeamWnd()) return LoopNextSleep();
		processOutside();

		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGPBTuChan::ShowActivityWnd()
{
	if (!m_bShowWnd) {
		m_bShowWnd = TRUE;
		g_pGameControl->ClickButtonHuDong();
		return;
	}
}

void CGPBTuChan::DelayClick()
{
	if (g_pGameControl->IsMember()) return;
	if (m_iDelayClicked >= 5) m_bShowWnd = FALSE;
	if (g_pGameControl->IsShowPopUI()) m_iDelayClicked = 0;
	m_iDelayClicked ++;
	LOG_WRITE("Wait for clicked huoDong %d", m_iDelayClicked);
	LoopNextSleep();
}

BOOL CGPBTuChan::IsNPCDialog()
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

BOOL CGPBTuChan::IsFinished()
{
	if (m_bFinished) {
		//if (g_pGameControl->IsTeamLeader()) _theApp->m_pEpoll->Sync_ActivitySttByLeader();
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else if (g_pGameControl->exitTeamIfAloneTeamSet()) return TRUE;
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(30)) { m_bFinished = TRUE; return TRUE;}

	return FALSE;
}

BOOL CGPBTuChan::IsInFb()
{

	if (IsCopyFinishedFubenWnd()) return TRUE;
	
	if (g_pGameControl->IsLowerLevelWnd()) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Bản đồ hiện tại yêu cầu", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"Thao tác hiện tại", MSG_CANCEL)) return TRUE;

	if (!g_pGame->m_OptionTab.bTCLeaderSkip) {
		if (g_pGameControl->IsStoryUIRoot()) {m_iDelayClicked = 0;return TRUE;}
	}

	if (g_pGame->m_OptionTab.bTCLeaderSkip) {
		if (g_pGameControl->IsTeamLeader()) {
			if (g_pGameControl->IsStoryUIRoot()) {m_iDelayClicked = 0;return TRUE;}
		}
	}

	if (IsPickUpBtn()) return LoopNextSleep(1000);

	if (g_pGameControl->IsButtonExitFuben()) {

		if (!m_bCountTime && !g_pGame->m_OptionTab.bTC2TimeToFinished) {
			m_iCountTime = m_iCountTime + 1;
			m_bCountTime = TRUE;
			LOG_WRITE("so Lan di %d", m_iCountTime);
		}
		m_iDelayClicked = 0;
		g_pGameControl->SwitchAutoFight(ON);
		processFb();
		return TRUE;
	}
	return FALSE;
}

void CGPBTuChan::ShowTeamWnd()
{
	CLeftInfoController *pIns = CLeftInfoController::Instance();
	if (!pIns) return;
	if (g_pGameControl->IsMember()) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		return;
	}
	if (!m_bShowWnd && g_pGameControl->IsTeamLeader()) {
		m_bShowWnd = TRUE;
		LOG_WRITE("Show Team Wnd.................");
		pIns->OnTeamClick();
		return;
	}
}

void CGPBTuChan::processOutside()
{
	if (g_pGame->m_OptionTab.bTC2TimeToFinished) {
		CStdStringU czCOunt = CActivityHuoDongWindow::GetActivityCountByActivityId(2021);
		LOG_WRITE("czCount = [%s]", _U2A(czCOunt).c_str());
		if (czCOunt.Compare(u"2/2") == 0) {
			m_bFinished = TRUE;
			return;
		}
	}

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
		DelayClick();
		return;
	}
}

BOOL CGPBTuChan::IsTeamWnd()
{
	int iDiffcult = g_pGame->m_OptionTab.iTCDifficult;
	LOG_WRITE("iDifff == %d", iDiffcult);
	if (iDiffcult == 0 && g_pGameControl->IsTeamTarget(u"Thanh Y Chủng")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	if (iDiffcult == 1 && g_pGameControl->IsTeamTarget(u"Cốc Thiên Kiếp")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	if (iDiffcult == 2 && g_pGameControl->IsTeamTarget(u"Oán Linh Môn")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	if (iDiffcult == 3 && g_pGameControl->IsTeamTarget(u"Hang Báu Vật")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	if (iDiffcult == 4 && g_pGameControl->IsTeamTarget(u"Tiên Ma Ảo Thiên")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	/*if (iDiffcult == 5 && g_pGameControl->IsTeamTarget(u"Đào Nguyên Luyện Ngục")) {
		m_iDelayClicked = 0;
		return TRUE;
	}*/
	if (iDiffcult == 5 && g_pGameControl->IsTeamTarget(u"Thanh Y Chủng-Ngục")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	if (iDiffcult == 7 && g_pGameControl->IsTeamTarget(u"Phiêu Miểu Tiên Cư")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	if (iDiffcult == 8 && g_pGameControl->IsTeamTarget(u"Cốc Thiên Kiếp-Thần")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	if (iDiffcult == 9 && g_pGameControl->IsTeamTarget(u"Oán Linh Môn-Quỷ")) {
		m_bCountTime = FALSE;
		m_iDelayClicked = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CGPBTuChan::IsPickUpBtn()
{
	return FALSE;
	/*CPickUpBtnLogic *pIns = CPickUpBtnLogic::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("PickUp................");
	pIns->ExecPickBtn();
	return TRUE;*/
}

BOOL CGPBTuChan::IsCopyFinishedFubenWnd()
{
	CCopySceneSettlementController *pInstance = CCopySceneSettlementController::Instance();
	if (!pInstance) return FALSE;
	if (pInstance) {
		m_bHBV = FALSE;
		m_bGone = FALSE;
		m_bCountTime = FALSE;
		int iCountTime = g_pGame->m_OptionTab.iTCCountTime;
		if (m_iCountTime >= iCountTime + 1) {
			LOG_WRITE("Over Time....................................................");
			m_bFinished = TRUE;
		}

		if (g_pGameControl->IsTeamLeader()) return TRUE;
	
		LOG_WRITE("Exit Fuben...");
		pInstance->OnExitCopyScene();
	
		return TRUE;
		
	}
	return FALSE;
}

int CGPBTuChan::get_CountNPC()
{
	int iNPC = 0;
	CUE_Transform *p = g_pGameControl->m_pUIRoot->GetChildByName(u"NameBoardRoot");
	if (g_pGameControl->IsShowTransform(p)) {
		int iCount = p->get_childCount();
		if (iCount != 0) {
			for (int i = 0; i < iCount; i++) {
				CUE_Transform *pNPCHeadInfo = p->GetChild(i);
				if (g_pGameControl->IsShowTransform(pNPCHeadInfo)) {


					CStdStringU czName = pNPCHeadInfo->GetName()->GetText();

					if (czName.Compare(u"NPCHeadInfo") == 0) {
						CUE_Transform* pOffset = pNPCHeadInfo->GetChildByName(u"Offset");
						if (g_pGameControl->IsShowTransform(pOffset)) {
							iNPC = iNPC + 1;
							CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
							CNpcHeadInfoLogic* pHeadInfo = (CNpcHeadInfoLogic *)pNPCHeadInfo->GetComponent(pType);
							if (pHeadInfo) {
								CObj_Char *pNPC = pHeadInfo->get_NPC();
								CStdStringU czNameLabel = pHeadInfo->get_NameLabel();
								if (czNameLabel.Find(u"Sĩ Binh Thoi") >= 0) iNPC = iNPC - 1;
								if (czNameLabel.Find(u"Đá Tổ Chú") >= 0) iNPC = iNPC - 1;
								if (czNameLabel.Find(u"Vàng Tổ Chú") >= 0) iNPC = iNPC - 1;
								//LOG_WRITE("%d -- NPC[%s]", i, _U2A(czNameLabel).c_str());
							}
						}
					}	
				}
			}
			LOG_WRITE("..........END............");
		}
	}
	return iNPC;
}

void CGPBTuChan::processFb()   // nhan vat dang dung 58,1,84  max 63,1,88
{
	
	if (g_pGameControl->AutoFightIsOn()) {
		int iDiff = g_pGame->m_OptionTab.iTCDifficult;
		int mRunningScene = CGameManager::m_RunningScene();
		
		g_pGameControl->CloseDialog();

		if (g_pGameControl->IsMovingXYZ()) { m_iShowMap = 0; return; }

		if (g_pGame->m_OptionTab.iTCDifficult == 0 || g_pGame->m_OptionTab.iTCDifficult == 5) {
			
			LOG_WRITE("....................................");
			if (IsShowTargetBar()) return;
			
			if (g_pGameControl->IsTeamLeader() || g_pGame->m_OptionTab.bTCMemAutoSearch) GotoDoor();
			return;
		}

		if (IsShowTargetBar()) { 
			//if (!m_bHBV && mRunningScene == 224) return;//hang bau vat
			
			m_iShowMap = 0; 
			if (g_pGameControl->IsShowTargetBar(u"Phạn Thiên")) m_bTransDoor = TRUE;

			if (g_pGameControl->IsShowTargetBar(u"Ma Vực Giáp")) {
				g_pGameControl->ShowMap();
				return;
			}
			return; 
		}
		
		if (m_bTransDoor) {
			LOG_WRITE("m_bTransDoor = %d", m_bTransDoor);
			MoveToTarget(mRunningScene);
			return;
		}

		if (m_iShowMap >= 3) {
			m_iShowMap = 0;
			int zPlayerPos = g_pGameControl->getPos(2);
			int yPlayerPos = g_pGameControl->getPos(1);
			int xPlayerPos = g_pGameControl->getPos(0);
			if (mRunningScene == 44) return; //ko bat map khi dang o coc thien kiep

			if (mRunningScene == 224) {
				if (zPlayerPos < 64 && zPlayerPos > 20) {
					MoveToTarget(mRunningScene);
					return;
				}
				else if (xPlayerPos < 63 && zPlayerPos < 88) {
					MoveToTarget(mRunningScene);
					return;
				}
				else if (!m_bHBV) m_bHBV = TRUE;
			}
			else if (g_pGameControl->IsTeamLeader() || g_pGame->m_OptionTab.bTCMemAutoSearch) g_pGameControl->ShowMap();
			return;
		}

		m_iShowMap ++;
		LOG_WRITE("not show target bar.............%d", m_iShowMap);
	
		return;
	}
}


void CGPBTuChan::MoveToPos( int x, int y )
{
	//static int iDelay = 0;
	//int xNew = x;
	//int yNew = y;

	////chuan 960x540
	//CUE_Display* _display = CUE_Display::get_current();
	//if(_display){
	//	int systemWidth = _display->get_systemWidth();
	//	int systemHeight = _display->get_systemHeight();
	//	if (systemWidth != 960) { 
	//		if (systemWidth == 500 && m_iMoveToPos == 2 && g_pGame->m_OptionTab.iTCDifficult == 4) xNew = 265;
	//		else 	xNew = systemWidth * x / 960;
	//	}

	//	if (systemHeight != 540) {
	//		if (systemHeight == 300 && m_iMoveToPos == 2 && g_pGame->m_OptionTab.iTCDifficult == 4) yNew = 217;
	//		else yNew = systemHeight * y / 540;
	//	}
	//}
	//
	//m_iShowMap = -1;
	//if (iDelay >= 2) {
	//	if (m_iMoveToPos >= 3) m_iMoveToPos = 0;
	//	iDelay = 0;
	//	g_pGameControl->CloseDialog();
	//}
	//LOG_WRITE("POS[%d, %d].......................", xNew, yNew);
	//g_pUEThread->m_pJNI->SendTap((float)xNew, (float)yNew);
	//iDelay ++;
	
}

BOOL CGPBTuChan::IsMonsterTarget()
{
	/*LOG_WRITE("CGPBTuChan::IsMonsterTarget().........................");
	CTargetWindow *pTemp = NULL;
	CTargetFrameControllerNew *pIns = CTargetFrameControllerNew::Instance();
	if (!pIns) return FALSE;

	CUE_Transform *pMonsterNPCBar = g_pGameControl->getTransformFromString("Monster&NpcBar");
	CUE_Transform *pBossBar = g_pGameControl->getTransformFromString("BossBar");
	if (g_pGameControl->IsShowTransform(pMonsterNPCBar)) {LOG_WRITE("pMonsterNPCBar"); pTemp = pIns->get_TargetNormal();}
	if (g_pGameControl->IsShowTransform(pBossBar)) {LOG_WRITE("pBoss"); pTemp = pIns->get_TargetBoss();}

	if (!pTemp) return FALSE;
	CStdStringU czName = pTemp->get_NameLabel();
	if (czName.Find(u"Ma Vực Giáp") >= 0) {
		LOG_WRITE("Monters is Yes.........................");
		return TRUE;
	}*/
	//CStdStringU czLevel = pTemp->get_LevelLabel();
	//CStdStringU czHP = pTemp->get_HPLabel();
	//LOG_WRITE("Name[%s] -- Level[%s] -- HP[%d]", _U2A(czName).c_str(), _U2A(czLevel).c_str(), _U2A(czHP).c_str());
	/*CSYS_List *pListBuff = pTemp->get_BuffList();
	int iCount = pListBuff->get_Count();
	if (iCount != 0) {
		for (int i = 0; i < iCount; i++) {
			CBuffInfo* pBuffInfo = (CBuffInfo*)pListBuff->get_Item(i);
			BOOL bMove = pBuffInfo->get_DisableMove();
			BOOL bSkill = pBuffInfo->get_DisableSkill();

			LOG_WRITE("%d BuffInfo -- %08X -- get_DisableMove[%d] -- get_DisableSkill[%d]", i, pBuffInfo, pBuffInfo->get_DisableMove(), pBuffInfo->get_DisableSkill());
		}
	}*/
	return FALSE;
}

BOOL CGPBTuChan::IsShowTargetBar()
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

		if (g_pGameControl->IsShowTransform(pMonster)) pTransform = pMonster;
		if (g_pGameControl->IsShowTransform(pBoss)) pTransform = pBoss;
		if (g_pGameControl->IsShowTransform(pTransform)) {
			CUE_Transform *pPlayerIcon = pTransform->GetChildByPath(u"Self:MonsterHeadIcon:PlayerIcon");
			if (g_pGameControl->IsShowTransform(pPlayerIcon)) return FALSE;
			LOG_WRITE("Is Have Show Target Bar.................");
			return TRUE;
		}
	}
	return FALSE;
}

void CGPBTuChan::MoveToTarget(int scene)
{
	int iDiff = g_pGame->m_OptionTab.iTCDifficult;
	int m_RunningScene = scene;//CGameManager::m_RunningScene();

	/*CObj_MainPlayer *pObj_Player = g_pGameControl->get_MainPlayer();
	if (!pObj_Player) return;
	CUE_Vector3 *pPlayerPosition = pObj_Player->get_Position();
	float fz0 = 0;
	if (pPlayerPosition) {
		fz0 = pPlayerPosition->GetZ();
		LOG_WRITE("PlayerPos[%.2f]", fz0);
	}*/
	int zPlayerPos = g_pGameControl->getPos(2);
	int xPlayerPos = g_pGameControl->getPos(0);
	int yPlayerPos = g_pGameControl->getPos(1);

	CUE_Transform *pCharRoot = g_pGameControl->get_CharRoot();
	if (!g_pGameControl->IsShowTransform(pCharRoot)) return;
	int iCount = pCharRoot->get_childCount();
	if (iCount == 0) return;
	for (int i = 0; i < iCount; i++) {
		CUE_Transform *pChild = pCharRoot->GetChild(i);
		if (pChild) {
			CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC");
			CObj_NPC *pNPC = (CObj_NPC *)pChild->GetComponent(pType);
			if (pNPC) {
				int NPCType = pNPC->get_NPCType();
				BOOL bCanBeSelect = pNPC->get_CanBeSeleByClient();

				CObj_Char *pChar = (CObj_Char*)pNPC;
				CStdStringU czName = pChar->get_RoleName();
				CObj *pObj = (CObj*)pChar;
				
				//if (czName.Compare(u"") != 0) m_iCountNPC ++; 

				if (czName.Find(u"Cửa Truyền Tống") >= 0) {
					LOG_WRITE("Di chuyển đến %s",  _U2A(czName).c_str());
					g_pGameControl->MoveToTarget(pChar);
					LoopNextSleep(2000);
				}

				if (m_RunningScene == 224) {//hang bau vat

					//LOG_WRITE("%d .... pNPCPos[%s]", i, _U2A(czName).c_str());
					
					int fCurPercent = (int)CGameManager::m_SavedCurValue();
					LOG_WRITE("Tien do pho ban === %d", fCurPercent);
					if (fCurPercent == 67) {
						LOG_WRITE("show map...........................");
						g_pGameControl->ShowMap();
						return;
					}

					if (bCanBeSelect) {

						LOG_WRITE("Co Quai Xuat Hien.......... %s, %d", _U2A(czName).c_str(), NPCType);

						if (czName.Find(u"Vua Hải Tặc Lãng Phiên Thiên") >= 0) {
							CObj_MainPlayer *pObj_Player = g_pGameControl->get_MainPlayer();
							LOG_WRITE("chay den vua hai tac...");
							m_iCountNPC = 0;
							g_pGameControl->MoveToTarget(pChar);
							LoopNextSleep(40000);
							return;
						}

						if (czName.Find(u"Yêu Lang Phế Đô") >= 0) {
							CActiveSceneLogic *pActiveScene = CGameManager::get_CurActiveScene();
							if (pActiveScene) {
								CUE_GameObject *pObject = pActiveScene->get_AirWallRoot();
								if (!pObject) LOG_WRITE("No airWall....");
								if (pObject) {
									CUE_Transform *pTrans = pObject->get_transform();
									if (pTrans) {
										int iCount = pTrans->get_childCount();
										if (iCount != 0) {

											CUE_Transform *pChild0 = pTrans->GetChild(0);
											if (g_pGameControl->IsShowTransform(pChild0)) {
												LOG_WRITE("Da thay airwall....");
												m_bTransDoor = FALSE;
												m_iCountNPC = 0;
												g_pGameControl->ShowMap();
												return;
											}

										}
									}
								}
							}
						}
					}
					
					CUE_Vector3 *pCharPos = pObj->get_Position();
					if (pCharPos) {
						float fx = 0, fy = 0, fz = 0;
						fx = pCharPos->GetX();
						fy = pCharPos->GetY();
						fz = pCharPos->GetZ();

						if (zPlayerPos > 14 && zPlayerPos < 65 && yPlayerPos > 1) {//nhan vat dang o trung tam 
							LOG_WRITE("nhan vat dang o trung tam ............");
							if ((int)fx == 34 && (int)fy == 7 && (int)fz == 44) {
								LOG_WRITE("Co ten chi duong ............");
								if (xPlayerPos == (int)fx) {
									LOG_WRITE("nhan vat dang dung o mui ten chi duong........");
									m_bTransDoor = TRUE;
									m_iCountNPC = 0;
									if (g_pGameControl->IsTeamLeader()) g_pGameControl->ShowMap();
									return;
								}
								else {
									LOG_WRITE("Da thay mui ten chi duong...go");
									m_bTransDoor = TRUE;
									m_iCountNPC = 0;
									g_pGameControl->MoveToTarget(pChar);
									return;
								}
							}
				
						}
					}
					//LOG_WRITE("[%08X][%s] NPC Type [%d][%d]",pNPC, _U2A(czName).c_str(), NPCType, bCanBeSelect);
				}
			}
		}
	}
	
	//// nhan vat dang dung 58,1,84  max 63,1,88
	//if (xPlayerPos < 63 && zPlayerPos < 88 && m_iCountNPC <= 1) {
	//	g_pGameControl->ShowMap();
	//	return;
	//}

	if (iDiff == 3 && zPlayerPos > 14 && zPlayerPos < 65) {
		m_bTransDoor = FALSE;
		LOG_WRITE("Khong thay mui ten chi duong -> Show map....");
		g_pGameControl->ShowMap();
		return;
	}

	LOG_WRITE("END LOOP......................");
}


BOOL CGPBTuChan::IsInMaple()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"Map");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			if (g_pGame->m_OptionTab.iTCDifficult == 1) g_pGameControl->CloseDialog();

			if (g_pGame->m_OptionTab.iTCDifficult == 0 || g_pGame->m_OptionTab.iTCDifficult == 5) {
				int xPos1 = convertXPointWithEmulatorSize(511);//
				int yPos1 = convertYPointWithEmulatorSize(423);//
				g_pGameControl->Tap(xPos1, yPos1);
				LOG_WRITE("Tap to %d, %d", xPos1, yPos1);
				CloseDialog();
				return TRUE;
			}

			if (g_pGame->m_OptionTab.iTCDifficult == 3) { //MoveToPos(488, 131);
				if (!m_bTransDoor) { //khong thay mui ten chi duong

					g_pGameControl->Tap(498, 337);
					LOG_WRITE("Tap to 498d, 337d");
				}
				if (m_bTransDoor) { //thay mui ten chi duong
					int xPos1 = convertXPointWithEmulatorSize(488);//
					int yPos1 = convertYPointWithEmulatorSize(131);//
					g_pGameControl->Tap(xPos1, yPos1);
					LOG_WRITE("Tap to %d, %d", xPos1, yPos1);
				}
				CloseDialog();
				return TRUE;
			}
			
			if (g_pGame->m_OptionTab.iTCDifficult == 4) {
				int xPlayerPos = 0;
				int yPlayerPos = 0;
				int yTemp = m_screenHeight/2;
				int yHalfScreen = convertYPointWithEmulatorSize(yTemp); 
				int xPos2 = convertXPointWithEmulatorSize(479);//x
				int yPos2 = convertYPointWithEmulatorSize(390);//yphan thien
				int xPos3 = convertXPointWithEmulatorSize(498);//xtien ma
				int yPos3 = convertYPointWithEmulatorSize(84);//ytien ma

				CUE_Transform *pListBoss = pWnd->GetChildByPath(u"Offset:Scroll View:Map_Texture");
				int iCount = pListBoss->get_childCount();
				CUE_Transform *pSelf = pListBoss->GetChild(0);

				if (g_pGameControl->IsShowTransform(pSelf)) {
					g_pGameControl->get_PositionWithEmulatorSize(pSelf, xPlayerPos, yPlayerPos);
					//LOG_WRITE("Player Position_0[%d, %d], yPos1[%d]", xPlayerPos, yPlayerPos, yPos1);
					//LOG_WRITE("Player Position_1[%d, %d], yPos1[%d]", xPlayerPos, yPlayerPos, yPos1);
					//convertXPointWithEmulatorSize(xPlayerPos);
					//convertYPointWithEmulatorSize(yPlayerPos);
					LOG_WRITE("Player Position_1[%d, %d], yPos1[%d]", xPlayerPos, yPlayerPos, yHalfScreen);

					if (yPlayerPos > yHalfScreen ) { //nhan vat dang dung map phanthien
						if (m_bTransDoor) {
							LOG_WRITE("Inmaple:: toi cong truyen tong");
							g_pGameControl->CloseDialog();
							return TRUE;
						}
						LOG_WRITE("Den phan thien......");
						g_pGameControl->Tap(xPos2, yPos2);
						CloseDialog();
						return TRUE;
					}

					if (yPlayerPos < yHalfScreen) { //nhan vat dang dung map tien ma
						LOG_WRITE("Den tien ma......");
						m_bTransDoor = FALSE;
						g_pGameControl->Tap(xPos3, yPos3);
						CloseDialog();
						return TRUE;
					}
					CloseDialog();

				}
			}
			
			return TRUE;
		}
	}
	return FALSE;
}

void CGPBTuChan::initEmulatorSize()
{
	if (m_screenWidth == 0 && m_screenHeight == 0) {
		m_screenWidth = g_pGameControl->m_renderWidth;
		m_screenHeight = g_pGameControl->m_renderHeight;
	}
}

int CGPBTuChan::convertYPointWithEmulatorSize( int y )
{
	int yNew = y;
	if (540 != g_pGameControl->m_systemHeight) {
		yNew = m_screenHeight*yNew / 540;
		LOG_WRITE("y[%d], m_systemHeight = %d, m_systemHeight*yNew[%d], yNew[%d]", y, m_screenHeight,  m_screenHeight*yNew, m_screenHeight*yNew / 540);
	}

	return yNew;
}

int CGPBTuChan::convertXPointWithEmulatorSize( int x )
{
	int xNew = x;

	if (960 != m_screenWidth) {
		xNew = m_screenWidth*xNew / 960;
	}
	return xNew;
}

void CGPBTuChan::processAlone()
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

void CGPBTuChan::GotoDoor()
{
	if (m_bGone) return;
	CObj_MainPlayer *pObj_Player = g_pGameControl->get_MainPlayer();
	if (!pObj_Player) return;

	CObj *pObjPlayer = (CObj *)pObj_Player;
	CUE_Vector3 *pPlayer_Vt3 = pObj_Player->get_Position();
	if (!pPlayer_Vt3) return;
	int xPlayer, yPlayer, zPlayer;
	xPlayer = (int)pPlayer_Vt3->GetX();	yPlayer = (int)pPlayer_Vt3->GetY();	zPlayer = (int)pPlayer_Vt3->GetZ();
	if (xPlayer == 116 && yPlayer == 75 && zPlayer == 21) m_bGone = TRUE;

	CUE_Transform *pCharRoot = g_pGameControl->get_CharRoot();
	if (!g_pGameControl->IsShowTransform(pCharRoot)) return;
	int iCount = pCharRoot->get_childCount();
	if (iCount == 0) return;
	for (int i = 0; i < iCount; i++) {
		CUE_Transform *pChild = pCharRoot->GetChild(i);
		int iChildCount = pChild->get_childCount();
		if (iChildCount != 8) { //la NPC
			CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj");
			CObj_NPC *pObj = (CObj_NPC *)pChild->GetComponent(pType);
			if (pObj) {
				CUE_Vector3 *pVt3 = pObj->get_Position();
				float fx, fy, fz;
				fx = pVt3->GetX(); fy = pVt3->GetY(); fz = pVt3->GetZ();
				int x = (int)fx; int y = (int)fy; int z = (int)fz;
				if (x == 116 && y == 75 && z == 21 && !m_bGone) {
					LOG_WRITE("Move To Target...................................");
					pObj_Player->MoveToTarget((CObj_Char*)pObj);
					LoopNextSleep(5000);
					return;
				}
			}
		}
	}

	LOG_WRITE("End Loop..............");
}

void CGPBTuChan::CloseDialog()
{
	if (m_iCloseMap >= 2) {
		g_pGameControl->CloseDialog();
	}
	m_iCloseMap ++;
	LoopNextSleep();
}







