#include "main.h"
#include "GTrucDietAcLinh.h"
#include "GTaskKetBai.h"
#include "GTeamAlone.h"
#include "GTaskBuyPatch.h"
#include "GTaskChangeScene.h"

CGTrucDietAcLinh::CGTrucDietAcLinh() :CGActivity()
{
	LOG_WRITE("NEW - CGTrucDietAcLinh()");
	m_activity = act_trucdietaclinh;
	m_bFinished = FALSE;
	m_bJiebai = FALSE;
	m_CurrentPosX = 0;
	m_CurrentPosY = 0;
	m_screenWidth = 0;
	m_screenHeight = 0;
	m_bRightMap = FALSE;
	m_bOpenFight1 = FALSE;
	m_bNotFoundNPC = FALSE;
	m_bRightNPC = FALSE;
	m_czLeaderName = u"No name";
	m_bChangeLine = FALSE;
	m_bChangeLineIfFull = FALSE;
	m_czLine = u"No line";
	m_bOverTime = FALSE;
	m_iCloseMap = 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGTrucDietAcLinh::~CGTrucDietAcLinh()
{
	LOG_WRITE("DEL - CGTrucDietAcLinh()");
}

int CGTrucDietAcLinh::Process()
{
	g_pGameControl->SetCurrentID((int)m_activity);
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		initEmulatorSize();
		get_NameLeader();
		if (m_bFinished) {
			if (g_pGameControl->exitTeamIfAloneTeamSet()) return LoopNextSleep();
			else return FinishedActivity();
			return m_nStatus;
		}
		CloseBountyMain();
		CloseDomainXuanZhanMap();
		g_pGameControl->ClosePopManyChar();

		if (g_pGameControl->IsCenterNotice(u"Kênh đã đầy,")) m_bChangeLineIfFull = TRUE;

		if (IsResultWnd()) return LoopNextSleep();

		if (!g_pGame->m_OptionTab.bTDALNotCheckCountTime) {
			if (g_pGameControl->checkCanJoinActivity(m_activity, m_bFinished)) return LoopNextSleep();
		}

		if (g_pGameControl->IsCenterNotice(u"Đã ở bản đồ")) m_bRightMap = TRUE;
		
		if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();

		if (IsNPCDialog()) return LoopNextSleep();
		
		if (!IsInMaple()) m_iCloseMap = 0;
		if (IsInMaple()) return LoopNextSleep();

		if (g_pGameControl->IsMoving()) {
			if (m_pGame->m_OptionTab.bTDALOpenSetting) {
				if (g_pGameControl->IsShowPopUI()) return LoopNextSleep();
				g_pGameControl->ShowSettingWnd();
			}
			else {
				g_pGameControl->CloseDialog();
				return LoopNextSleep();
			} 
			return LoopNextSleep();
		}

		if (!g_pGameControl->IsMoving() && m_pGame->m_OptionTab.bTDALOpenSetting) {
			LOG_WRITE("not Moving.....................");
			g_pGameControl->CloseDialog();
		}
		
		if (g_pGame->m_OptionTab.bTDALPlayerSet) {
			if (m_bChangeLine || m_bChangeLineIfFull) {
				if (g_pGameControl->IsMember()) { 
					m_bChangeLine = FALSE;
					return TRUE;
				}

				if (getTime(YL_MINUTE) >= 40) {
					m_bChangeLine = FALSE;
					return TRUE;
				}

				ChangeLine();

				return LoopNextSleep();
			}
		}

		processTeam();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGTrucDietAcLinh::processTeam()
{
	if (g_pGameControl->IsTeamAloneSet()) {
		processAlone();
		LoopNextSleep();
		return;
	}
	if (g_pGameControl->IsMember()) {
		LOG_WRITE("%d ------------------>Thanh vien tim ac linh da mo", m_bNotFoundNPC);
		UpdateNPC1(TRUE);
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

		//kiem tra ac linh da chon truoc
		if (!m_bNotFoundNPC) {
			LOG_WRITE("m_bNotFoundNPC=FALSE.................................Tim ac linh da mo");
			UpdateNPC1(TRUE);
		}
		
		//khong thay ac linh da chon - tim ac linh chua chon
		if (m_bNotFoundNPC) {
			LOG_WRITE("m_bNotFoundNPC=TRUE.................................Tim ac linh chua mo");
			UpdateNPC1(FALSE);
		}
	}

	g_pGameControl->CloseDialog();
	LoopNextSleep();
}


BOOL CGTrucDietAcLinh::IsInMaple()
{
	int xPos = 0;
	int yPos = 0;
	int MinDistance = 100000;
	int xPlayerPos = 0;
	int yPlayerPos = 0;
	static CUE_Transform *pTemp = NULL;

	CSceneMapController *pIns = CSceneMapController::Instance();
	if (!pIns) return FALSE;

	CStdStringU czUNameMap = pIns->get_SceneNameLabel();
	if (czUNameMap.Find(m_czNameMap) < 0) {
		LOG_WRITE("Wrong map..... %s", _U2A(m_czNameMap).c_str());
		g_pGameControl->CloseDialog();
		return TRUE;
	}
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"Map");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			CUE_Transform *pListBoss = pWnd->GetChildByPath(u"Offset:Scroll View:Map_Texture");
			int iCount = pListBoss->get_childCount();
			int i = 0;
			for (i = 0; i < iCount; i++) {

				CUE_Transform *pChild = pListBoss->GetChild(i);
				CStdStringU czNameChild = pChild->GetName()->GetText();

				if (g_pGameControl->IsShowTransform(pChild)) {
					if (czNameChild.Compare(u"self") == 0) {
						g_pGameControl->get_PositionWithEmulatorSize(pChild, xPlayerPos, yPlayerPos);
						LOG_WRITE("Player Position[%d, %d]", xPlayerPos, yPlayerPos);
					}

					//xuất hiện vị trí boss trên bản đồ
					if (czNameChild.Find(u"Map_icon_boss02(Clone)") >= 0) {
						g_pGameControl->get_PositionWithEmulatorSize(pChild, xPos, yPos);
						
						//tính toán khoảng cách trong phạm vi cho phép
						if (IsNotBannedArea(xPos, yPos)) {
							//tính khoảng cách từ boss đến nhân vật
							int xDistance = xPlayerPos - xPos;
							int yDistance = yPlayerPos - yPos;
							int Distance = sqrt((xDistance*xDistance) + (yDistance*yDistance));

							//tìm khoảng cách ngắn nhất
							if (MinDistance > Distance) {
								pTemp = pChild;
								m_CurrentPosX = xPos;
								m_CurrentPosY = yPos;
								MinDistance = Distance;
							}
							LOG_WRITE("[BOSS %d] -- Position Root[%d, %d] -- Positon New From Player[%d, %d] -- Distance[%d]", i, xPos, yPos, xDistance, yDistance, Distance);

						}
					}
				}
			}

			if (i >= iCount) {
				
				if (MinDistance == 100000) {
					LOG_WRITE("No boss in Maple");
					if (getTime(YL_MINUTE) < 40) m_bChangeLine = TRUE;
					g_pGameControl->CloseDialog();
					return TRUE;
				}
				
				// kiếm tra quái có nằm trong điểm đặc biệt của bến tầm mộng hay không?
				if (IsEspecialPoint(m_CurrentPosX, m_CurrentPosY, xPlayerPos, yPlayerPos)) return TRUE;

				if (pTemp && g_pGameControl->IsTeamLeader()) {
					g_pGameControl->Clicked(pTemp);
					CloseDialog();
				}

				LOG_WRITE(".........................................MinDistance[%d]", MinDistance);

			}
			return TRUE;
		}
	}

	return FALSE;
}


BOOL CGTrucDietAcLinh::IsNPCDialog()
{
	if (g_pGameControl->ProcessMessageBox(u"Truyền tống đến", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"mời vào đội, đồng ý?", MSG_OK)) return TRUE;

	if (g_pGameControl->ProcessMessageBox(u"mời theo sau", MSG_OK)) return TRUE;

	CDialogController *pIns = CDialogController::Instance();
	if (pIns) {
		int iID = CDialogController::get_DialogID();
		if (iID == 135) {
			if (g_pGameControl->IsMember()) {
				pIns->AidButtonClick();
				return TRUE;
			}
			LOG_WRITE("Fight................... %d", iID);
			m_bOpenFight1 = TRUE;
			pIns->OnOpt_1();
			return TRUE;
		}
		pIns->AidButtonClick();
		return TRUE;
	}
	return FALSE;
}

BOOL CGTrucDietAcLinh::IsResultWnd()
{
	CUE_Transform *p = g_pGameControl->m_pTipUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"prompt.commonreward");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			LOG_WRITE("Yessssssssssssssssssssssssssssssssssssssss");
			m_bOpenFight1 = FALSE;

			if (g_pGameControl->AutoFightIsOn()) {
				g_pGameControl->SwitchAutoFight(OFF);
				return TRUE;
			}

			g_pGameControl->Tap(1,1);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGTrucDietAcLinh::IsNotBannedArea( int x, int y )
{
	int xPos = x;
	int yPos = y;
	int xMax = 0;
	int xMin = 0;
	int yMax = 0;
	int yMin = 0;

	

	if (m_czNameMap.Find(u"Bến Tầm Mộng") >= 0) {
		if (y < 316) {
			yMax = convertYPointWithEmulatorSize(289) ;
			yMin = convertYPointWithEmulatorSize(193) ;
			xMax = convertXPointWithEmulatorSize(454) ;
			xMin = convertXPointWithEmulatorSize(339) ;
		}

		if (y > 316) {
			yMax = convertYPointWithEmulatorSize(405) ;
			yMin = convertYPointWithEmulatorSize(367) ;
			xMax = convertXPointWithEmulatorSize(669) ;
			xMin = convertXPointWithEmulatorSize(628) ;
		}
		LOG_WRITE("xMax[%d], xMin[%d], yMax[%d], yMin[%d]", xMax, xMin, yMax, yMin);
	}

	if (m_czNameMap.Find(u"Hồ Thông Thiên") >= 0) {
		yMax = convertYPointWithEmulatorSize(235) ;
		yMin = convertYPointWithEmulatorSize(195) ;
		xMax = convertXPointWithEmulatorSize(410) ;
		xMin = convertXPointWithEmulatorSize(361) ;
		LOG_WRITE("xMax[%d], xMin[%d], yMax[%d], yMin[%d]", xMax, xMin, yMax, yMin);
	}

	if (x < xMin) {
		LOG_WRITE("x < xMin");
		return TRUE;
	}
	if (x > xMax) {
		LOG_WRITE("x > xMax");
		return TRUE;
	}
	if (y < yMin) {
		LOG_WRITE("y < yMin");
		return TRUE;
	}
	if (y > yMax) {
		LOG_WRITE("y > yMax");
		return TRUE;
	}
	//382, 251

	LOG_WRITE("toa do quai nam trong vung cam [%d < %d < %d], [%d < %d < %d]", xMin, x, xMax, yMin, y, yMax);

	return FALSE;
}

int CGTrucDietAcLinh::convertXPointWithEmulatorSize( int x )
{
	int xNew = x;
	
	if (960 != m_screenWidth) {
		xNew = m_screenWidth*xNew / 960;
	}
	return xNew;
}

int CGTrucDietAcLinh::convertYPointWithEmulatorSize( int y )
{
	int yNew = y;
	if (540 != m_screenHeight) {
		yNew = m_screenHeight*yNew / 540;
	}

	return yNew;
}

BOOL CGTrucDietAcLinh::IsEspecialPoint( int x, int y, int xPlayer, int yPlayer )
{
	int xPos = x;
	int yPos = y;
	int xMax, xMin, yMax, yMin, xMax1, xMin1, yMax1, yMin1, xMax2, xMin2, yMax2, yMin2;
	xMax = xMin = yMax = yMin = xMax1 = xMin1 = yMax1 = yMin1 = xMax2 = xMin2 = yMax2 = yMin2 =0;

	if (m_czNameMap.Find(u"Bến Tầm Mộng") >= 0) {
		//huyen minh thien ton
		yMax = convertYPointWithEmulatorSize(465) ;
		yMin = convertYPointWithEmulatorSize(419) ;
		xMax = convertXPointWithEmulatorSize(594) ;
		xMin = convertXPointWithEmulatorSize(547) ;
		
		//truong lao tam mong
		yMax1 = convertYPointWithEmulatorSize(465) ;
		yMin1 = convertYPointWithEmulatorSize(376) ;
		xMax1 = convertXPointWithEmulatorSize(683) ;
		xMin1 = convertXPointWithEmulatorSize(594) ;

		//doi truong tam mong
		yMax2 = convertYPointWithEmulatorSize(376) ;
		yMin2 = convertYPointWithEmulatorSize(328) ;
		xMax2 = convertXPointWithEmulatorSize(683) ;
		xMin2 = convertXPointWithEmulatorSize(638) ;



		if ((xPos > xMin && xPos < xMax) && (yPos > yMin && yPos < yMax)) {
			LOG_WRITE("quai nam o khu vuc Huyen Minh Thien Ton");
			g_pGameControl->ClickNPCInMaple(u"Huyền Minh Thiên Tôn");
			return TRUE;
		}

		if ((xPos > xMin1 && xPos < xMax1) && (yPos > yMin1 && yPos < yMax1)) {
			if ((xPlayer > xMin1 && xPlayer < xMax1) && (yPlayer > yMin1 && yPlayer < yMax1)) {
				LOG_WRITE("Nguoi choi dang dung gan TRuong Lao Tam Mong --> Den toa do Quai");
				g_pGameControl->Tap(xPos, yPos);
				CloseDialog();
				return TRUE;
			}
			LOG_WRITE("quai nam o khu vuc Truong Lao Tam Mong");
			g_pGameControl->ClickNPCInMaple(u"Trưởng Lão Tầm Mộng");
			return TRUE;
		}

		if ((xPos > xMin2 && xPos < xMax2) && (yPos > yMin2 && yPos < yMax2)) {
			LOG_WRITE("quai nam o khu vuc Doi Truong Tam Mong");
			g_pGameControl->ClickNPCInMaple(u"Đội Trưởng Tầm Mộng");
			return TRUE;
		}
	}


	if (m_czNameMap.Find(u"Hồ Thông Thiên") >= 0) {
		int yPlayerPos = g_pGameControl->getPos(1);

		//Linh Bao Thien Ton
		if ((xPos >= 427 && xPos <= 483) && (yPos >= 223 && yPos <= 280)) {
			if (yPlayerPos >= 498) {
				LOG_WRITE("Nguoi choi dang dung gan Linh bao thien ton --> Den toa do Quai");
				g_pGameControl->Tap(xPos, yPos);
				CloseDialog();
			}
			else {
				LOG_WRITE("quai nam o khu vuc Linh bao thien ton");
				g_pGameControl->ClickNPCInMaple(u"Linh Bảo Thiên Tôn");
			}
			return TRUE;
		}

		//Linh Hu Dai Tien
		if ((xPos >= 517 && xPos <= 558) && (yPos >= 197 && yPos <= 239)) {
			if (yPlayerPos >= 486) {
				LOG_WRITE("Nguoi choi dang dung gan Linh Hu Dai Tien --> Den toa do Quai");
				g_pGameControl->Tap(xPos, yPos);
				CloseDialog();
			}
			else {
				LOG_WRITE("quai nam o khu vuc Linh Hu Dai Tien");
				g_pGameControl->ClickNPCInMaple(u"Linh Hư Đại Tiên");
			}
			return TRUE;
		}

		//Quy Vuc Ton Gia
		if ((xPos >= 366 && xPos <= 408) && (yPos >= 182 && yPos <= 229)) {
			if (yPlayerPos >= 489) {
				LOG_WRITE("Nguoi choi dang dung gan Quy Vuc Ton Gia --> Den toa do Quai");
				g_pGameControl->Tap(xPos, yPos);
				CloseDialog();
			}
			else {
				LOG_WRITE("quai nam o khu vuc Quy Vuc Ton Gia");
				g_pGameControl->ClickNPCInMaple(u"Quỷ Vực Tôn Giả");
			}
			return TRUE;
		}

		//khu vuc tren thap ko co NPC
		if ((xPos >= 427 && xPos <= 469) && (yPos >= 313 && yPos <= 340)) {
			if (yPlayerPos >= 498) {
				LOG_WRITE("Nguoi choi dang dung gan Linh bao thien ton --> Den toa do Quai");
				g_pGameControl->Tap(xPos, yPos);
				CloseDialog();
			}
			else {
				LOG_WRITE("quai nam o khu vuc khong co NPC -> den Linh bao thien ton");
				g_pGameControl->ClickNPCInMaple(u"Linh Bảo Thiên Tôn");
			}
			return TRUE;
		}	

	}

		////quy vuc
		//yMax = convertYPointWithEmulatorSize(225) ;
		//yMin = convertYPointWithEmulatorSize(171) ;
		//xMax = convertXPointWithEmulatorSize(406) ;
		//xMin = convertXPointWithEmulatorSize(318) ;
		//
		//if ((xPos > xMin && xPos < xMax) && (yPos > yMin && yPos < yMax)) {
		//	LOG_WRITE("quai nam o khu vuc Quy Vuc");
		//	if ((xPlayer > xMin && xPlayer < xMax) && (yPlayer > yMin && yPlayer < yMax)) {
		//		LOG_WRITE("Nguoi choi dang dung gan Quy Vuc --> Den toa do Quai");
		//		g_pGameControl->Tap(xPos, yPos);
		//		g_pGameControl->CloseDialog();
		//		return TRUE;
		//	}
		//	g_pGameControl->ClickNPCInMaple(u"Quỷ Vực Tôn Giả");
		//	return TRUE;
		//}
		//
		//yMax2 = convertYPointWithEmulatorSize(307) ;
		//yMin2 = convertYPointWithEmulatorSize(178) ;
		//xMax2 = convertXPointWithEmulatorSize(487) ;
		//xMin2 = convertXPointWithEmulatorSize(318) ;

		//if ((xPos > xMin2 && xPos < xMax2) && (yPos > yMin2 && yPos < yMax2)) {

		//	if ((xPlayer > xMin2 && xPlayer < xMax2) && (yPlayer > yMin2 && yPlayer < yMax2)) {
		//		LOG_WRITE("Nguoi choi dang dung gan Linh bao thien ton --> Den toa do Quai");
		//		g_pGameControl->Tap(xPos, yPos);
		//		g_pGameControl->CloseDialog();
		//		return TRUE;
		//	}

		//	LOG_WRITE("quai nam o khu vuc Linh bao thien ton");
		//	g_pGameControl->ClickNPCInMaple(u"Linh Bảo Thiên Tôn");
		//	return TRUE;
		//}

	//}
	
	return FALSE;
}



BOOL CGTrucDietAcLinh::IsLeaderAutoFight()
{
	if(CTeamList::Instance() == 0) {
		g_pGameControl->OnTeamTabClick();
		return FALSE;
	}

	CUE_Transform *pIconAutoFight = g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"BaseUIRoot:LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem:Team01 (1):Main:RightBtn:Table:RealTimeState:tuoguan");
	
	if (g_pGameControl->IsShowTransform(pIconAutoFight)) return TRUE;
	return FALSE;
}

void CGTrucDietAcLinh::initEmulatorSize()
{
	if (m_screenWidth == 0 && m_screenHeight == 0) {
		m_screenWidth = g_pGameControl->m_renderWidth;
		m_screenHeight = g_pGameControl->m_renderHeight;
		return;
	}
}


void CGTrucDietAcLinh::processAlone()
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
		
		UpdateNPC1(TRUE);
		return;
	}

	if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_ALONE) bTeamAlone = FALSE;
}

void CGTrucDietAcLinh::newMethod()
{	
	if (m_bRightMap) {
		if (g_pGameControl->IsMap(u"Hồ Thông Thiên")) m_czNameMap = u"Hồ Thông Thiên";
		if (g_pGameControl->IsMap(u"Bến Tầm Mộng")) m_czNameMap = u"Bến Tầm Mộng";
		if (g_pGameControl->IsMap(u"Thành Tổ Long")) m_czNameMap = u"Thành Tổ Long";

		g_pGameControl->ShowMap();
		return;
	}

	if (g_pGameControl->IsMember()) {
		m_bRightMap = TRUE;
		return;
	}

	if (g_pGameControl->IsShowPopUI()) {
		g_pGameControl->CloseDialog();
	}
}

void CGTrucDietAcLinh::get_NameLeader()
{
	CStdStringU czLeaderName = g_pGameControl->get_NameLeader();
	if (m_czLeaderName != czLeaderName) {
		LOG_WRITE("get_LeaderName....................");
		m_czLeaderName = czLeaderName;

		LOG_WRITE("%s name leader", _U2A(m_czLeaderName).c_str());
		return;
	}
}


void CGTrucDietAcLinh::UpdateNPC1(BOOL bShowed)
{
	checkSetTimeOnUI();
	CObj_MainPlayer *pPlayer = g_pGameControl->get_MainPlayer();
	static CObj_Char *pChar1 = NULL;

	CUE_Transform *pNameBoard = g_pGameControl->m_pUIRoot->GetChildByName(u"NameBoardRoot");
	if (!g_pGameControl->IsShowTransform(pNameBoard)) return;
	int iCount = pNameBoard->get_childCount();
	if (iCount <= 1) return;

	int i = 1;
	for (i = 1; i < iCount; i++) {
		CUE_Transform *pName = pNameBoard->GetChild(i);
		CUE_Transform *pNameNPC = pName->GetChildByPath(u"Offset:OriginalHeadInfo:NameLabel");
		CStdStringU czName =  g_pGameControl->GetTextU(pNameNPC);
		//LOG_WRITE("[%d] [%s][%08X]", i, _U2A(czName).c_str(), pName);
		int iChildCount = pName->get_childCount();

		if (pName->get_childCount() == 8 && g_pGameControl->IsShowTransform(pName)) {
			CUE_Transform *pNameNPC = pName->GetChildByPath(u"Offset:OriginalHeadInfo:NameLabel");
			if (pNameNPC) {
				CStdStringU czNameNPC = g_pGameControl->GetTextU(pNameNPC);

				if (czNameNPC.Find(u"Ác Linh" )>= 0) {

					//tim ac linh khi da mo ac linh == UPdateNPC(TRUE)
					CUE_Transform *pChatBubble = pName->GetChildByName(u"ChatBubble");
					if (pChatBubble) {
						CUE_Transform *pLabel = pChatBubble->GetChildByName(u"Label");
						CStdStringU czLabel = g_pGameControl->GetTextU(pLabel);
						if (g_pGameControl->IsShowTransform(pChatBubble)) {

							CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
							CNpcHeadInfoLogic *pHead = (CNpcHeadInfoLogic *)pName->GetComponent(pType);

							if (czLabel.Find(m_czLeaderName) >= 0) {
								m_bNotFoundNPC = FALSE;
								LOG_WRITE("Yessssssssssssssssssssssssssssss %08X", pName);

								//CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
								//CNpcHeadInfoLogic *pHead = (CNpcHeadInfoLogic *)pName->GetComponent(pType);
								
								BOOL IsDie = pHead->get_NPC()->IsDie();
								CStdStringU czName1 = pHead->get_NPC()->get_RoleName();
								LOG_WRITE(".............%s[%d]", _U2A(czName1).c_str(), IsDie);
								if (IsDie) {
									m_bNotFoundNPC = FALSE;
									//pChar1 = NULL;
								}
								g_pGameControl->FollowLeader(OFF);
								g_pGameControl->SwitchAutoFight(ON);
								LOG_WRITE("Move To Target.....");
								pPlayer->MoveToTarget(pHead->get_NPC());
								m_bNotFoundNPC = FALSE;
								LoopNextSleep(5000);
								return;
							}
						}
						
						//tim ac linh khi chua mo ac linh
						if (!bShowed) {
							if (!g_pGameControl->IsShowTransform(pChatBubble)) {
								LOG_WRITE("NOOOOOOOOOOOOOOO %08X", pName);
								CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
								CNpcHeadInfoLogic *pHead = (CNpcHeadInfoLogic *)pName->GetComponent(pType);
								CObj_Char *pChar = pHead->get_NPC();
								pPlayer->MoveToTarget(pHead->get_NPC());
								m_bNotFoundNPC = FALSE; // tim ac linh da mo;
								return;
							}

						}
						LOG_WRITE("Ac linh %08X", pName);

					} //pChatBubble

				} //aclinh
			}//pNameNPC
		} //la NPC
	} //for 

	if (i >= iCount) {
		LOG_WRITE("NOT FOUND NPC....................");
		if (!m_bNotFoundNPC && g_pGameControl->IsTeamLeader()) { 
			m_bNotFoundNPC = TRUE; 
			return;
		}

		if (g_pGameControl->IsMember()) {
			g_pGameControl->FollowLeader(ON);
			LoopNextSleep();
			return;
		}
		g_pGameControl->SwitchAutoFight(OFF);
		
		if (m_bOverTime) {
			LOG_WRITE("iMinute.......................%d..", getTime(YL_MINUTE));
			checkSetTimeOnUI();
			return;
		}
		
		newMethod();
		
		return;
	}
}

void CGTrucDietAcLinh::ChangeLine()
{
	CStdStringU czCurrentLine = g_pGameControl->getCurrentNameLine();
	CLimitTimePushTipsController *pInsLimit = CLimitTimePushTipsController::Instance();

	if (!pInsLimit) {
		if (g_pGameControl->IsShowPopUI()) {
			g_pGameControl->CloseDialog();
			return;
		}

		CFunctionButtonController *pIns = CFunctionButtonController::Instance();
		if (!pIns) return;
		pIns->OnCliskShowLimitTimePushActivityTips();
		return;
	}

	CLimitActivityYLTX *pLimitYLTX = pInsLimit->get_LimitActivityYLTX();
	if (!pLimitYLTX) {
		return;
	}

	CUE_Transform *pYLTXTransform = g_pGameControl->get_Transform((UINT)pLimitYLTX);
	if (!g_pGameControl->IsShowTransform(pYLTXTransform)) {
		LOG_WRITE("Show YLTX window....");
		CUE_Transform *pPushTipsController = g_pGameControl->get_Transform((UINT)pInsLimit);
		if (pPushTipsController) {
			CUE_Transform *pListActivity = pPushTipsController->GetChildByPath(u"Offset:Panel:Offset:Grid");
			if (pListActivity) {
				int iCount = pListActivity->get_childCount();
				if (iCount != 0) {
					for (int j = 0; j < iCount; j++) {
						CUE_Transform *pActiv = pListActivity->GetChild(j);
						if (!pActiv) return;
						CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsItem");
						CLimitTimePushTipsItem* pPushTipsItem = (CLimitTimePushTipsItem *)pActiv->GetComponent(pType);
						if (pPushTipsItem) {
							CStdStringU czNPCNum = pPushTipsItem->get_ActivityName();
							LOG_WRITE("czNPCNum [%s]", _U2A(czNPCNum).c_str());
							if (czNPCNum.Find(u"Ác Linh") >= 0) {
								LOG_WRITE("Show YLTX window....");
								pPushTipsItem->OnClickGoBtn();
								return;
							}
						}
					}
				}
			}
			return;
		}
		return;
	}
	
	static int iLine = 0;
	int iNumMax = 0;
	CLimitActivityYLTXItem* pShiJiao1 = NULL;
	CUE_Transform *pListYLTX = pYLTXTransform->GetChildByPath(u"Offset:Panel:Grid");
	if (pListYLTX) {
		int iCountt = pListYLTX->get_childCount();
		LOG_WRITE("pListYLTX %d", iCountt);
		if (iCountt != 0) {
			for (int i = iCountt - 1; i >= 0; i--) {
				CUE_Transform *pItem = pListYLTX->GetChild(i);
				if (!pItem) return;
				CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","LimitActivityYLTXItem");
				CLimitActivityYLTXItem* pShiJiao = (CLimitActivityYLTXItem *)pItem->GetComponent(pType);
				if (pShiJiao) {
					CStdStringU czNameLine = pShiJiao->m_SceneLabel();
					CStdStringU czNPCNum = pShiJiao->m_NpcNumLabel();
					int iNum = atoi(_U2A(czNPCNum).c_str());
					if (iNumMax < iNum) {
						iNumMax = iNum;
						pShiJiao1 = pShiJiao;
					}
				}
			}
			
			LOG_WRITE("iLine = %d", iNumMax);
			m_bChangeLineIfFull = FALSE;
			m_bChangeLine = FALSE;
			pShiJiao1->OnClick();
			LoopNextSleep(3000);


			pLimitYLTX->OnClickSyncYLTXData();
		}
		return;
	}
}

void CGTrucDietAcLinh::checkSetTimeOnUI()
{
	if (g_pGameControl->IsTeamLeader()) {

		//khong den map truoc
		if (!g_pGame->m_OptionTab.bTDALTimeGotoBoss) {
			LOG_WRITE("AAAAAAAAAAAAAAa");
			TeleportOnTime();
			return;
		}

		if (g_pGame->m_OptionTab.iTDALTime == 0) {
			LOG_WRITE("BBBBBBBBBBBBBBBBB");
			TeleportOnTime();
			return;
		}

		//chon thoi gian den truoc map
		if (g_pGame->m_OptionTab.bTDALTimeGotoBoss) {
			//LOG_WRITE("CCCCCCCCCCCCCCCCCCCCC");
			TeleportOnTime(FALSE);
			return;
		}
	}

}

void CGTrucDietAcLinh::TeleportOnTime( BOOL bOnTime )
{
	
	static BOOL bOnTimeCurrent = FALSE;
	int iHour = getTime(YL_HOUR);
	int iMinute = getTime(YL_MINUTE);

	//truong hop chon den truoc map va dung gio
	if (iMinute >= 0 && iMinute < 40) {
		bOnTimeCurrent = TRUE;
		m_bOverTime = FALSE;
	}

	//dung gio hoat dong hoac ko dung gio ma dang trong gio hoat dong
	if (bOnTime || bOnTimeCurrent) {
		if (iMinute >= 40) {
			m_bOverTime = TRUE;
			if (bOnTime) LOG_WRITE("OVER TIME::Waiting for On time11111111111");
			if (bOnTimeCurrent) {
				LOG_WRITE("OVER TIME::Waiting for On time222222");
				bOnTimeCurrent = FALSE;
				return;
			}
			return;
		}

		switch (iHour) {
			case 12: case 15: case 18: case 21:
				{
					if (CGameManager::m_RunningScene() == 4) m_bRightMap = TRUE; //ho thong thien
					else AddSubGoal(new CGTaskChangeScene(SCENEID_HOTHONGTHIEN));
					break;
				}
			
			case 13: case 16: case 19: case 22: 
				{
					if (CGameManager::m_RunningScene() == 34) m_bRightMap = TRUE; //ngoai thanh to long
					else AddSubGoal(new CGTaskChangeScene(SCENEID_NGTHANHTOLONG));
					break;
				}

			case 14: case 17: case 20: case 23: 
				{
					if (CGameManager::m_RunningScene() == 92) m_bRightMap = TRUE; //ben tam mong
					else AddSubGoal(new CGTaskChangeScene(SCENEID_BENTAMMONG));
					break;
				}
		}
		return;
	}

	if (!bOnTime) {
		
		int UIMinute = 0;
		int iSTT = g_pGame->m_OptionTab.iTDALTime;
		if (iSTT > 0) {
			if (g_pGame->m_OptionTab.iTDALTime == 1) UIMinute = 57; //3
			if (g_pGame->m_OptionTab.iTDALTime == 2) UIMinute = 55; //5
			if (g_pGame->m_OptionTab.iTDALTime == 3) UIMinute = 53; //7
			if (g_pGame->m_OptionTab.iTDALTime == 4) UIMinute = 51; //9

			if (g_pGame->m_OptionTab.iTDALTime == 5) {
				//LOG_WRITE("g_pGame->m_OptionTab.iTDALTime == 5");
				UIMinute = 45; //15
				if (iMinute >= 40 && iMinute < UIMinute) {
					if (bOnTimeCurrent) bOnTimeCurrent = FALSE;
					LOG_WRITE("OVER TIME::Waiting for On time --> %d", UIMinute);
					return;
				}
			}
			if (g_pGame->m_OptionTab.iTDALTime == 6) {
				//LOG_WRITE("g_pGame->m_OptionTab.iTDALTime == 6");
				UIMinute = 41; //19
				if (iMinute < UIMinute) {
					if (bOnTimeCurrent) bOnTimeCurrent = FALSE;
					LOG_WRITE("OVER TIME::Waiting for On time --> %d", UIMinute);
					return;
				}
			}
			/*
			if (iMinute >= 40 && iMinute <= 50) {
				if (bOnTimeCurrent) bOnTimeCurrent = FALSE;
				LOG_WRITE("OVER TIME::Waiting for On time");
				return;
			}*/

			
			//LOG_WRITE("UIMinute...............%d", UIMinute);
			switch (iHour) {
			case 11: case 14: case 17: case 20:
				{
					if (iMinute >= UIMinute) {
						if (CGameManager::m_RunningScene() == 4) LOG_WRITE("Waiting for On time");
						else AddSubGoal(new CGTaskChangeScene(SCENEID_HOTHONGTHIEN));
					}
					break;
				}

			case 12: case 15: case 18: case 21:
				{
					if (iMinute >= UIMinute) {
						if (CGameManager::m_RunningScene() == 34) LOG_WRITE("Waiting for On time");
						else AddSubGoal(new CGTaskChangeScene(SCENEID_NGTHANHTOLONG));
					}
					break;
				}

			case 13: case 16: case 19: case 22:
				{
					if (iMinute >= UIMinute) {
						if (CGameManager::m_RunningScene() == 92) LOG_WRITE("Waiting for On time");
						else AddSubGoal(new CGTaskChangeScene(SCENEID_BENTAMMONG));
					}
					break;
				}
			}
		}
		return;
	}
}

int CGTrucDietAcLinh::getTime( int iTypeTime /*= HOUR*/ )
{
	CDeviceStatusWindow *pStatus = CDeviceStatusWindow::Instance();
	if (!pStatus) return -5;
	if (iTypeTime == YL_HOUR) return pStatus->get_Hour();
	if (iTypeTime == YL_MINUTE) return pStatus->get_Minute();
	return -1;
}

void CGTrucDietAcLinh::CloseDialog()
{
	if (m_iCloseMap >= 2) {
		g_pGameControl->CloseDialog();
	}
	m_iCloseMap ++;
	LoopNextSleep();
}

void CGTrucDietAcLinh::CloseBountyMain()
{
	CUIBounty_Main *pIns = CUIBounty_Main::Instance();
	if (pIns) pIns->OnClickClose();
}

void CGTrucDietAcLinh::CloseDomainXuanZhanMap()
{
	CDomainXuanZhanMap *pIns = CDomainXuanZhanMap::Instance();
	if (pIns) CDomainXuanZhanMap::CloseWindow();

	/*CBrotherhoodPanelMy *pIns1 = CBrotherhoodPanelMy::Instance();
	if (pIns1) {g_pGameControl->CloseDialog(); return;}*/

}

