#include "main.h"
#include "GameControl.h"
#include <math.h>
#include "GSleep.h"

CGameControl::CGameControl(void)
{
	LOG_WRITE("===> CGameControl ....NEW ");	
	m_pUIManager = NULL;
	m_pUIRoot = NULL;
	m_pBaseUIRoot = NULL;
	m_pPopUIRoot = NULL;
	m_pStoryUIRoot = NULL;
	m_pTipUIRoot = NULL;
	m_pMessageUIRoot = NULL;
	m_pDeathUIRoot = NULL;
	m_pFloatUIRoot = NULL;
	m_pStoryMessageUIRoot = NULL;
	m_pPlayerData = NULL;
	m_pDeviceStatus = NULL;

	m_gameSysTypes = new CSysTypes(IMAGE_ASSEMBLY_CSHARP);
	m_ueuiSysTypes = new CSysTypes(IMAGE_UNITY_ENGINE_UI);
	m_uecoreSysTypes = new CSysTypes(IMAGE_UNITY_ENGINE_COREMODULE);
	
	m_gameSysTypes->Add(TYPE_UIButton);
	m_gameSysTypes->Add(TYPE_UILabel);
	m_gameSysTypes->Add(TYPE_MissionItem);
	m_gameSysTypes->Add(TYPE_TeamMemberUIInfo);
	m_gameSysTypes->Add(TYPE_TeamInvite);
	m_gameSysTypes->Add(TYPE_TeamFriendItem);
	m_gameSysTypes->Add(TYPE_TeamMemberItem);
	m_gameSysTypes->Add(TYPE_TabController);
	m_gameSysTypes->Add(TYPE_TabButton);
	m_gameSysTypes->Add(TYPE_MessageBoxWithCheckBox);
	m_gameSysTypes->Add(TYPE_ServerListItem);
	m_gameSysTypes->Add(TYPE_RoleSelectItem);
	m_gameSysTypes->Add(TYPE_ShiJiaoSetting);
	m_gameSysTypes->Add(TYPE_ActivityHuoDongItem);
	m_gameSysTypes->Add(TYPE_AsynPVPItem);
	m_gameSysTypes->Add(TYPE_KnapsackItem);
	m_uecoreSysTypes->Add(TYPE_Camera);
	
}

CGameControl::~CGameControl(void)
{
	LOG_WRITE("===> CGameControl ....DEL ");
	SAFE_DELETE(m_gameSysTypes);
	SAFE_DELETE(m_ueuiSysTypes);
	SAFE_DELETE(m_uecoreSysTypes);
}
BOOL CGameControl::InitUnity()
{
	//if(m_pBaseUIRoot) return TRUE;
	CUIManager *pUIManager = CUIManager::Intance();
	if (!pUIManager) {
		LOG_WRITE("pUIManger = NULL");
		return FALSE;
	}
	if(m_pUIManager !=  pUIManager){
		m_pUIManager = pUIManager;
		LOG_WRITE("%p m_pUIManager", m_pUIManager);
		if(!m_pUIManager) return FALSE;
		InitBaseTransform();
		
		CUE_Display* _display = CUE_Display::get_current();
		LOG_WRITE("%p _display", _display);
		if(_display)
		{
			int systemWidth = _display->get_systemWidth();
			int systemHeight = _display->get_systemHeight();


			//m_renderWidth = _display->get_renderingWidth();
			//m_renderHeight = _display->get_renderingHeight();
			m_othorgraphicSize = 1.0f;
			CUE_Transform *pCamera = pUIManager->get_UICameraTransform();
			LOG_WRITE("%p pCamera",pCamera);
			if(pCamera)
			{
				CUE_Camera* _camera = (CUE_Camera*)pCamera->GetComponent(m_uecoreSysTypes->Get(TYPE_Camera));
				LOG_WRITE("%p _camera",_camera);
				m_othorgraphicSize = _camera->get_orthographicSize();
				m_renderWidth = _camera->get_pixelWidth();
				m_renderHeight = _camera->get_pixelHeight();
			}
			else return FALSE;
			LOG_WRITE("%0.1f m_othorgraphicSize", m_othorgraphicSize);


			m_renderRate = (float)m_renderWidth / m_renderHeight;
			m_renderWidthHalf = (float)m_renderWidth  / 2;
			m_renderHeightHalf = (float)m_renderHeight / 2;

			m_system_render_rateWidth = (float)systemWidth / m_renderWidth;
			m_system_render_rateHeight = (float)systemHeight / m_renderHeight;
			LOG_WRITE(" (%d,%d) EMULATOR SIZE",systemWidth,systemHeight);
			LOG_WRITE(" (%d,%d) UNITY SIZE  RATE:%.4f ",m_renderWidth,m_renderHeight,m_renderRate);
			LOG_WRITE(" (%0.1f,%0.1f) RATE EMULATOR/UNITY SIZE ",m_system_render_rateWidth,m_system_render_rateHeight);
		}

		CSYS_Object* objList = (CSYS_Object*)CObj_MainPlayer::get_AttackList();
		m_dwVAF_ListUint64 = objList?*objList->GetOffset(0):0;
		
		CSYS_Object* objArr = CCopySceneReady::get_m_LastTeamGuids();
		m_dwVAF_ArrUint64 = objArr?*objArr->GetOffset(0):0;

		LOG_WRITE("vaf %08X %08X",m_dwVAF_ListUint64,m_dwVAF_ArrUint64);
	}
	
	return IsInitBaseTransform();
}
BOOL CGameControl::IsInitBaseTransform(){
	if(!m_pUIRoot)				return FALSE;
	if(!m_pBaseUIRoot)			return FALSE;
	if(!m_pPopUIRoot)			return FALSE;
	if(!m_pStoryUIRoot)			return FALSE;
	if(!m_pTipUIRoot)			return FALSE;
	if(!m_pMessageUIRoot)		return FALSE;
	if(!m_pDeathUIRoot)			return FALSE;
	if(!m_pFloatUIRoot)			return FALSE;
	if(!m_pStoryMessageUIRoot)	return FALSE;
	if(!m_pPlayerData)			return FALSE;
	return TRUE;
}
void CGameControl::InitBaseTransform(){
	if(!m_pUIManager) return;
	m_pUIRoot				= m_pUIManager->get_UIRootTrans();
	m_pBaseUIRoot			= m_pUIManager->get_baseUIRoot();
	m_pPopUIRoot			= m_pUIManager->get_popUIRoot();
	m_pStoryUIRoot			= m_pUIManager->get_storyUIRoot();
	m_pTipUIRoot			= m_pUIManager->get_tipUIRoot();
	m_pMessageUIRoot		= m_pUIManager->get_messageUIRoot();
	m_pDeathUIRoot			= m_pUIManager->get_deathUIRoot();
	m_pFloatUIRoot			= m_pUIManager->get_FloatUIRoot();
	m_pStoryMessageUIRoot	= m_pUIManager->get_storyMessageUIRoot();
	m_pPlayerData			= CGameManager::get_PlayerDataPool();
	LOG_WRITE("=================");
	LOG_WRITE("%p m_pUIRoot",				m_pUIRoot);
	LOG_WRITE("%p m_pBaseUIRoot",			m_pBaseUIRoot);
	LOG_WRITE("%p m_pPopUIRoot",			m_pPopUIRoot);
	LOG_WRITE("%p m_pStoryUIRoot",			m_pStoryUIRoot);
	LOG_WRITE("%p m_pTipUIRoot",			m_pTipUIRoot);
	LOG_WRITE("%p m_pMessageUIRoot",		m_pMessageUIRoot);
	LOG_WRITE("%p m_pDeathUIRoot",			m_pDeathUIRoot);
	LOG_WRITE("%p m_pFloatUIRoot",			m_pFloatUIRoot);
	LOG_WRITE("%p m_pStoryMessageUIRoot",	m_pStoryMessageUIRoot);
	LOG_WRITE("%p m_pPlayerData",			m_pPlayerData);
}
BOOL CGameControl::IsShowTransform(CUE_Transform *p)
{
	if (!p) return FALSE;
	return p->IsVisible();
}
BOOL CGameControl::GetPixelCenter( CUE_Transform* p, POINT& pt )
{
	if (!p) return FALSE;
	CUE_Vector3* v3 = p->get_position();
	float vX = (v3->GetX()/ m_othorgraphicSize);
	float vY = (v3->GetY()/ m_othorgraphicSize);
	float tempX = m_renderWidthHalf + ((vX * m_renderWidthHalf) / m_renderRate);
	float tempY = m_renderHeightHalf -(vY * m_renderHeightHalf);
	pt.x = (int)round(tempX * m_system_render_rateWidth);//
	pt.y = (int)round(tempY * m_system_render_rateHeight);//
	return TRUE;
}

BOOL CGameControl::Tap( CUE_Transform* p )
{
	if (!p) return FALSE;
	POINT pt;
	if (!GetPixelCenter(p,pt)) return FALSE;
	CStdString szName = U2A(p->GetName()->GetText());
	LOG_WRITE("+++ TAP(%d,%d) [%s]",pt.x,pt.y,szName.c_str());
	g_pUEThread->m_pJNI->SendTap((float)pt.x,(float)pt.y);
	return TRUE;
}

BOOL CGameControl::Tap( int x, int y )
{
	int xNew = x;
	int yNew = y;
	if (m_renderWidth != 960) {
		xNew = m_renderWidth * xNew / 960;    
	}

	if (m_renderWidth != 960) {
		xNew = m_renderHeight * yNew / 540;    
	}

	float fx = m_system_render_rateWidth*xNew;
	float fy = m_system_render_rateHeight*yNew;

	g_pUEThread->m_pJNI->SendTap(fx,fy);
	return TRUE;
}

BOOL CGameControl::Clicked( CUE_Transform* p )
{
	if (!p) return FALSE;
	/*if (!IsShowTransform(p)) {
		LOG_WRITE("Not Show Transform p");
		return FALSE;
	}*/
	CUIButton* pbtn = (CUIButton *)p->GetComponent(m_gameSysTypes->Get("UIButton"));
	if (pbtn){
		LOG_WRITE("==> UIButton OnClick(%s)",U2A(p->GetPath().c_str()).c_str());
		pbtn->OnClick();
		return TRUE;
	}
	return Tap(p);
}
BOOL CGameControl::ClickServerListItem(CUE_Transform *pChooseList, int iServer){
	if(!pChooseList) return FALSE;
	if(!IsShowTransform(pChooseList->GetChildByName(u"ServerList"))) return FALSE;
	CUE_Transform *pGrid = pChooseList->GetChildByPath(u"ServerList:Panel:Grid");
	if(!pGrid) return FALSE;
	int iItemID = 56000+ iServer;
	CStdString czName;
	czName.Fmt("%d", iItemID);
	//LOG_WRITE("[%s] ItemID",czName.c_str());
	CUE_Transform *pItem = pGrid->GetChildByName(_A2U(czName.c_str()).c_str());
	if(!pItem) return FALSE;
	//LOG_WRITE("%p pItem",pItem);
	CServerListItem *pTypeItem = (CServerListItem *)pItem->GetComponent(m_gameSysTypes->Get(TYPE_ServerListItem));
	//LOG_WRITE("%p pTypeItem",pTypeItem);
	if(!pTypeItem) return FALSE;
	//LOG_WRITE("pTypeItem->OnClickItem()");
	pTypeItem->OnClickItem();
	return TRUE;
}
CStdString CGameControl::GetTextA(CUE_Transform* p)
{
	if (!p) return CStdString("");
	CUILabel* pTxt = (CUILabel*)p->GetComponent(m_gameSysTypes->Get("UILabel"));
	if (!pTxt) return CStdString("");
	CSYS_String* pStr = pTxt->get_text();
	if (!pStr) return CStdString("");
	return CStdString(U2A(pStr->GetText()));
}

CStdStringU CGameControl::GetTextU(CUE_Transform* p)
{
	if (!p) return CStdStringU("");
	CUILabel* pTxt = (CUILabel*)p->GetComponent(m_gameSysTypes->Get("UILabel"));
	if (!pTxt) return CStdStringU("");
	CSYS_String* pStr = pTxt->get_text();
	if (!pStr) return CStdStringU("");
	return CStdStringU(pStr->GetText());
}

BOOL CGameControl::MissionClicked( CUE_Transform* p ) 
{
	if (!IsShowTransform(p)) return FALSE;
	CMissionItem* pbtn = (CMissionItem*)p->GetComponent(m_gameSysTypes->Get("MissionItem"));
	if (pbtn){
		//LOG_WRITE("==> MissionItem OnMisClick(%s)",U2A(p->GetPath().c_str()).c_str());
		pbtn->OnMisClick();
		return TRUE;
	}
	return Tap(p);
}

CStdString CGameControl::U2A( LPCUSTR czU )
{
	if (!czU) return CStdString("");
	return CStdString(_U2A(czU).c_str());
}

BOOL CGameControl::Process_FirstLogout()
{
	if (!g_pGame->m_bIsLogined) return TRUE;
	LOG_WRITE("*****  CGameControl::Process_FirstLogout() *****");
	g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
	
	g_pGame->m_bIsLogined = FALSE;
	return g_pGame->m_bIsLogined;
}

BOOL CGameControl::Process_FirstLogined()
{
	if (g_pGame->m_bIsLogined) return TRUE;
	LOG_WRITE("*****  CGameControl::Process_FirstLogined() *****");
	if(!UpdateAccountInfo()) return FALSE;
	if(!UpdateRoleInfo()) return FALSE;
	LOG_WRITE("Process_FirstLogined()...................");
	g_pNetwork->Sync_AccountInfo();
	g_pGame->m_bIsLogined = TRUE;
	return g_pGame->m_bIsLogined;
}
BOOL CGameControl::UpdateLoginState()
{
	BOOL bLogined = m_pBaseUIRoot->get_childCount() > 0;
	if (g_pGame->m_bIsLogined != bLogined){	
		if (bLogined) Process_FirstLogined();
		else Process_FirstLogout();		
		return TRUE;
	}
	return FALSE;
}
BOOL CGameControl::UpdateAccountInfo(){
	CJUserInfo oUser = g_pUEThread->GetUserInfo();
	if (!oUser.Get()) return FALSE;
	ACCOUNT_INFO* pAccount = &g_pGame->m_accountInfo;
	pAccount->uTypeLogin = oUser.GetType();

	strcpy(pAccount->czUsername,oUser.GetDisplayName());

	LOG_WRITE("***** ACCOUNT LOGINED *****");
	//LOG_WRITE("Username\t[%s]",pAccount->czUsername);	
	return (pAccount->czUsername[0] != 0);

}
BOOL CGameControl::UpdateRoleInfo(){
	ACCOUNT_INFO* pAccount = &g_pGame->m_accountInfo;
	strcpy(pAccount->czRoleName,CJSDKService::GetRoleName(g_pUEThread->m_pJNI->m_env));
	strcpy(pAccount->czServerName,CJSDKService::GetServerName(g_pUEThread->m_pJNI->m_env));
	CStdString czServerID(CJSDKService::GetServerID(g_pUEThread->m_pJNI->m_env));
	pAccount->uServerId = atoi(czServerID.Right(3));
	LOG_WRITE("***** ROLE LOGINED *****");
	LOG_WRITE("RoleName\t[%s]",pAccount->czRoleName);	
	LOG_WRITE("uServerId\t[%d]",pAccount->uServerId);	
	LOG_WRITE("czServerName\t[%s]",pAccount->czServerName);	
	
	return (pAccount->czRoleName[0] != 0);
}
BOOL CGameControl::IsUIServerChoose()
{
	return IsShowTransform(m_pUIRoot->GetChildByName(u"login.serverchoosewindow"));
}

BOOL CGameControl::IsUIRoleChoose()
{
	return IsShowTransform(m_pUIRoot->GetChildByName(u"login.rolechoosewindow"));
}

BOOL CGameControl::GetExecPickBtn()
{
	CPickUpBtnLogic* pInstance = CPickUpBtnLogic::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("OnClick PickUpBtn");
	pInstance->ExecPickBtn();
	return TRUE;
}

BOOL CGameControl::IsPickUpBtn()
{
	if (!IsShowTransform(m_pBaseUIRoot)) return FALSE;
	CUE_Transform *p = m_pBaseUIRoot->GetChildByName(u"PickUpBtn");
	if (!IsShowTransform(p)) return FALSE;
	CUE_Transform *pLabel = p->GetChildByPath(u"Offset:Label");
	CStdStringU czULabel = GetTextU(pLabel);
	if (czULabel.Compare(u"Trò chuyện") == 0) return FALSE;
	LOG_WRITE("CGameControl::IsPickUpBtn............");
	return TRUE;
}

BOOL CGameControl::IsBatterySaver()
{
	CUE_Transform *p = m_pMessageUIRoot;
	if (!IsShowTransform(p))  return FALSE;
	CUE_Transform *pSaveBattery = p->GetChildByName(u"mainbaseui.shengdian");
	if (!pSaveBattery) return FALSE;
	if (!IsShowTransform(pSaveBattery)) return FALSE;
	LOG_WRITE("IsShowTransform(pSaveBattery)");
	Tap(1,1);//Clicked(pSaveBattery->GetChildByName(u"name"));
	return TRUE;
}

BOOL CGameControl::IsButtonExitFuben()
{
	CFunctionButtonController *pIns = CFunctionButtonController::Instance();
	if (!pIns) return FALSE;
	BOOL bShowButton = pIns->IsShow_ExitCopySceneButton();
	if (!bShowButton) return FALSE;
	LOG_WRITE("CGameControl::IsExitFuben()");
	return TRUE;
}

void CGameControl::CloseNPCTalk()
{
	CDialogController *pInstance = CDialogController::Instance();
	if (!pInstance) return;

	CUE_Transform *pOpt = m_pStoryUIRoot->GetChildByPath(u"synopsis.taskdialog:Offset:dialogSmall:btn_choiceOpt");
	if (IsShowTransform(pOpt)) {
		LOG_WRITE("pInstance->OnOpt_1()");
		pInstance->OnOpt_1(); 
		return;
	}

	CUE_Transform *pMis = m_pStoryUIRoot->GetChildByPath(u"synopsis.taskdialog:Offset:dialogSmall:btn_choiceMis");
	if (IsShowTransform(pMis)) {
		LOG_WRITE("pInstance->OnClickMisButton0()");
		pInstance->OnClickMisButton0(); 
		return;
	}

	CUE_Transform *pEnterCopyScene = m_pStoryUIRoot->GetChildByPath(u"synopsis.taskdialog:Offset:EnterCopyScene");
	if (IsShowTransform(pEnterCopyScene)) {
		LOG_WRITE("pInstance->ClickEnterCopyScene()");
		pInstance->ClickEnterCopyScene(); 
		return;
	}
	LOG_WRITE("CGameControl::CloseNPCTalk()......");
	pInstance->AidButtonClick();
}


BOOL CGameControl::IsSetSceneUI()
{
	
	if (!IsShowTransform(m_pFloatUIRoot)) return FALSE;
	CUE_Transform *p1 = m_pFloatUIRoot->GetChildByName(u"mainbaseui.shijiao");
	if (!IsShowTransform(p1)) return FALSE;
	//CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","ShiJiaoSetting");
	CShiJiaoSetting* pShiJiao = (CShiJiaoSetting *)p1->GetComponent(m_gameSysTypes->Get(TYPE_ShiJiaoSetting));

	LOG_WRITE("pShiJiao [%08X]", pShiJiao);
	if (!pShiJiao) return FALSE;
	LOG_WRITE("Set 3D Scene");
	pShiJiao->Set3D();

	return TRUE;
}

void CGameControl::Test()
{
	
	CObj_MainPlayer *pPlayer = CObjManager::get_MainPlayer();

	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return;
	LOG_WRITE("pPlayerData %08X", pPlayerData);
	CBrotherhood *pBrotherhood = pPlayerData->get_BrotherhoodInfo();
	if (!pBrotherhood) return;
	LOG_WRITE("pFriendList %08X", pBrotherhood);
	CSYS_List *pBrotherhoodList = pBrotherhood->m_BrotherhoodMemberList();
	if (!pBrotherhoodList) return;
	LOG_WRITE("pRelationList %08X", pBrotherhoodList);
	int iCount = pBrotherhoodList->get_Count();
	if (iCount == 0) return;
	for (int i = 0; i < iCount; i++) {
		CBrotherhoodMember *pMember = (CBrotherhoodMember *)pBrotherhoodList->get_Item(i);
		if (pMember) {
			CStdStringU czName = pMember->get_MemberName();
			ULONGLONG uGuid = pMember->get_BrotherhoodGuid();
			LOG_WRITE("[%d] -- %s %llu", i, _U2A(czName).c_str(), uGuid);
		}
	}
	LOG_WRITE(".................................");
	//CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","ShiJiaoSetting");
	//CShiJiaoSetting* pShiJiao = (CShiJiaoSetting *)p1->GetComponent(m_gameSysTypes->Get(TYPE_ShiJiaoSetting));

	/*CTargetWindow *pTemp = NULL;
	CTargetFrameControllerNew *pIns = CTargetFrameControllerNew::Instance();
	if (!pIns) return;
	
	CUE_Transform *pMonsterNPCBar = getTransformFromString("Monster&NpcBar");
	CUE_Transform *pBossBar = getTransformFromString("BossBar");
	if (IsShowTransform(pMonsterNPCBar)) {LOG_WRITE("pMonsterNPCBar"); pTemp = pIns->get_TargetNormal();}
	if (IsShowTransform(pBossBar)) {LOG_WRITE("pBoss"); pTemp = pIns->get_TargetBoss();}
	
	if (!pTemp) return;
	CStdStringU czName = pTemp->get_NameLabel();
	CStdStringU czLevel = pTemp->get_LevelLabel();
	CStdStringU czHP = pTemp->get_HPLabel();
	LOG_WRITE("Name[%s] -- Level[%s] -- HP[%d]", _U2A(czName).c_str(), _U2A(czLevel).c_str(), _U2A(czHP).c_str());
	CSYS_List *pListBuff = pTemp->get_BuffList();
	int iCount = pListBuff->get_Count();
	if (iCount != 0) {
		for (int i = 0; i < iCount; i++) {
			CBuffInfo* pBuffInfo = (CBuffInfo*)pListBuff->get_Item(i);
			BOOL bMove = pBuffInfo->get_DisableMove();
			BOOL bSkill = pBuffInfo->get_DisableSkill();

			LOG_WRITE("%d BuffInfo -- %08X -- get_DisableMove[%d] -- get_DisableSkill[%d]", i, pBuffInfo, pBuffInfo->get_DisableMove(), pBuffInfo->get_DisableSkill());
		}
	}
	LOG_WRITE("END.......................");*/

	
}

BOOL CGameControl::IsLoading()
{
	CUE_Transform *pCloudLoading = m_pUIRoot->GetChildByPath(u"sceneloading:LoadingEffect:CloudLoading");
	CGameSceneLogic *pInstance = CGameSceneLogic::Instance();
	if (!pInstance) return FALSE;
	BOOL bget_IsMovingToDoor = pInstance->get_IsMovingToDoor();
	BOOL bget_bIsTransDoor = pInstance->get_bIsTransDoor();
	if (bget_bIsTransDoor || bget_IsMovingToDoor) {
		LOG_WRITE("CGameControl::IsLoading()...................");
		return TRUE;
	}
	return FALSE;
}


BOOL CGameControl::TeamCreate()
{
	CTeamList *pTeamList = CTeamList::Instance();
	LOG_WRITE("%p pTeamList",pTeamList);
	if(pTeamList){
		LOG_WRITE("pTeamList->OnCreateTeam");
		pTeamList->OnCreateTeam();
		return TRUE;
	}

	if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
	return FALSE;
}

BOOL CGameControl::TeamInvite(LPCSTR szName)
{
	LOG_WRITE("[%s] TeamInvite",szName);

	CUE_Transform *pTeamInvite = m_pTipUIRoot->GetChildByName(u"teamfunction.teaminvitelistpanel");
	if(IsShowTransform(pTeamInvite)){
		CUE_Transform *pGrid = pTeamInvite->GetChildByPath(u"Offset:BG:Scroll View:Grid");
		if(pGrid){
			int iMemCount = pGrid->get_childCount();
			for(int i = 0; i < iMemCount ; i++){
				CUE_Transform *pItem = pGrid->GetChild(i);
				if(!IsShowTransform(pItem)) continue;
				CTeamFriendItem *pFriendItem = (CTeamFriendItem *)pItem->GetComponent(m_gameSysTypes->Get(TYPE_TeamFriendItem));
				if(!pFriendItem) continue;
				CStdString czFriendName = pFriendItem->GetName();
				LOG_WRITE("[%s][%s] czFriendName - szName",czFriendName.c_str(),szName);
				if(czFriendName.Compare(szName) == 0){
					pFriendItem->OnInviteClick();
					//return TRUE;
				}
			}
		}
	}
	
	OpenInvite();
	return TRUE;
}

BOOL CGameControl::TeamInvite(MEMBER *pMembers)
{	
	static int iCurrentFriends = 0;
	static int iDelayInvite = -1;
	static int iDelayMax = 0;
	static int iCurMemberUI = 1;
	CStdStringU czMember1 = get_NameMemberOnUIAuto(g_pGame->m_Members, 1);
	CStdStringU czMember2 = get_NameMemberOnUIAuto(g_pGame->m_Members, 2);
	CStdStringU czMember3 = get_NameMemberOnUIAuto(g_pGame->m_Members, 3);
	CStdStringU czMember4 = get_NameMemberOnUIAuto(g_pGame->m_Members, 4);
	CStdStringU czMember5 = get_NameMemberOnUIAuto(g_pGame->m_Members, 5);

	CObj_MainPlayer *pPlayer = CObjManager::get_MainPlayer();

	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return FALSE;
	CTeam *pTeam = pPlayerData->get_TeamInfo();
	CRelationList *pFriendList = pPlayerData->get_FriendList();
	if (!pFriendList) return FALSE;
	CSYS_List *pRelationList = pFriendList->get_sortedList();
	if (!pRelationList) return FALSE;;
	int iCount = pRelationList->get_Count();
	int iTeamID = pTeam->get_TeamID();

	LOG_WRITE("%08X pTeam", pTeam);

	if (iCount != 0) {
		BOOL bInviteFriends = g_pGame->m_TeamOption.bInviteFriends;
		if (bInviteFriends) iDelayMax = iCount * 3 - 2;
		if (!bInviteFriends) iDelayMax = 13;

		int iAmountOfMembers = g_pGame->m_TeamOption.iSLTV;
		if (g_pGameControl->IsTeamEnoughMembers(iAmountOfMembers)) {
			iDelayInvite = -1;
			iCurMemberUI = 1;
			g_pGame->m_bIsFullMember = TRUE;
			return TRUE;
		}

		iDelayInvite ++;
		if (iDelayInvite >= 17) {
			iDelayInvite = -1;
			iCurrentFriends = 0;
			iCurMemberUI = 1;
			return TRUE;
		}
		LOG_WRITE("Wait for invite Team............%d [%d]", iDelayInvite, bInviteFriends);
		if ((iDelayInvite % 4) == 0) {
			LOG_WRITE("m_TeamOption.bInviteFriends = %d", iDelayInvite);

			if (!g_pGame->m_TeamOption.bInviteFriends) {
				if (iCurMemberUI > 5) iCurMemberUI = 1;
				CStdStringU czMemberUI = get_NameMemberOnUIAuto(g_pGame->m_Members, iCurMemberUI);
				int j = 1;
				for (j = 1; j < 6; j++ ) {
					CStdStringU czMember = getNameMember(pTeam, j);
					if (czMemberUI.Compare(czMember) == 0) { //neu da co thanh vien nay trong team, -> check mem tiep theo.
						iCurMemberUI = iCurMemberUI + 1;
						iDelayInvite = iDelayInvite - 1;
						return TRUE;
					}
				}

				if (j >= 6) { //chuaw co nguoi nay trong team
					for (int k = 0; k < iCount; k++) {
						CRelation * pRelation = (CRelation *)pRelationList->get_Item(k);
						CStdStringU czName = pRelation->get_Name();
						ULONGLONG uGuid = pRelation->get_Guid();
						if (czMemberUI.Compare(czName) == 0) {
							iDelayInvite = 1;
							pPlayer->ReqInviteTeam(uGuid);
							LOG_WRITE("Invite Online [%s], [%s]", _U2A(czName).c_str(),  _U2A(czMemberUI).c_str());
							break;
						}
		
					}
				}
				return TRUE;
			}

			else {
				int i = 0;
				for(i = iCurrentFriends; i < iCount; i++){
					CRelation * pRelation = (CRelation *)pRelationList->get_Item(i);
					if (pRelation) {
						CStdStringU czName = pRelation->get_Name();
						ULONGLONG uGuid = pRelation->get_Guid();
						LOG_WRITE("%d[%d] - name: %s", i , _U2A(czName).c_str());
						LOG_WRITE("...........................................");

						CStdStringU czMem1 = getNameMember(pTeam, 1);
						CStdStringU czMem2 = getNameMember(pTeam, 2);
						CStdStringU czMem3 = getNameMember(pTeam, 3);
						CStdStringU czMem4 = getNameMember(pTeam, 4);
						CStdStringU czMem5 = getNameMember(pTeam, 5);
						LOG_WRITE("Friend ..... Invite Online [%s], [%s]", _U2A(czName).c_str(),  _U2A(czMem1).c_str());

						if (g_pGame->m_TeamOption.bInviteFriends) {
							if (czName.Compare(czMem1) == 0) continue;
							if (czName.Compare(czMem2) == 0) continue;
							if (czName.Compare(czMem3) == 0) continue;
							if (czName.Compare(czMem4) == 0) continue;
							if (czName.Compare(czMem5) == 0) continue;

							iCurrentFriends = i + 1;
							pPlayer->ReqInviteTeam(uGuid);
							break;
						}	
					}
				}		
				LOG_WRITE("i for end looop = %d, iCount = %d", i, iCount);
				if (i > iCount) iCurrentFriends = 0;
				return TRUE;
			}
			
			if (iDelayInvite >= 17) {
				iDelayInvite = -1;
				iCurrentFriends = 0;
				return TRUE;
			}
			return TRUE;
			
		}

		//if ((iDelayInvite - 1)%3 == 0) { //1 3 4 7 10
		//	int i = 0;
		//	for(i = iCurrentFriends; i < iCount; i++){
		//		CRelation * pRelation = (CRelation *)pRelationList->get_Item(i);
		//		CStdStringU czName = pRelation->get_Name();
		//		ULONGLONG uGuid = pRelation->get_Guid();
		//		LOG_WRITE("czName[%d][%s][%08X]", i, _U2A(czName).c_str(), pRelation);

		//		//if (czName.Compare(czMember1) == 0 && iDelayInvite == 1) {
		//		//	pPlayer->ReqInviteTeam(uGuid);
		//		//	LOG_WRITE("delayInvite[%d] - Invite Online [%s]", iDelayInvite, _U2A(czName).c_str());
		//		//	break;
		//		//}
		//		//if (czName.Compare(czMember2) == 0 && iDelayInvite == 4) {
		//		//	pPlayer->ReqInviteTeam(uGuid);
		//		//	LOG_WRITE("delayInvite[%d] - Invite Online [%s]", iDelayInvite, _U2A(czName).c_str());
		//		//	break;
		//		//}
		//		//if (czName.Compare(czMember3) == 0 && iDelayInvite == 7) {
		//		//	pPlayer->ReqInviteTeam(uGuid);
		//		//	LOG_WRITE("delayInvite[%d] - Invite Online [%s]", iDelayInvite, _U2A(czName).c_str());
		//		//	break;
		//		//}
		//		//if (czName.Compare(czMember4) == 0 && iDelayInvite == 10) {
		//		//	pPlayer->ReqInviteTeam(uGuid);
		//		//	LOG_WRITE("delayInvite[%d] - Invite Online [%s]", iDelayInvite, _U2A(czName).c_str());
		//		//	break;
		//		//}
		//		//if (czName.Compare(czMember5) == 0 && iDelayInvite == 13) {
		//		//	pPlayer->ReqInviteTeam(uGuid);
		//		//	LOG_WRITE("delayInvite[%d] - Invite Online [%s]", iDelayInvite, _U2A(czName).c_str());
		//		//	break;
		//		//}
		//		////}

		//	}

		//	LOG_WRITE("i for end looop = %d, iCount = %d", i, iCount);
		//	if (i >= iCount) iCurrentFriends = iCount;

		//	if (iCurrentFriends >= iCount) {
		//		LOG_WRITE("End friends");
		//		iDelayInvite = 0;
		//		iCurrentFriends = 0;
		//	}
		//}
		

		/*if (iDelayInvite > 0) {
			if (iDelayInvite >= 5) {
				iDelayInvite = 0;
				return TRUE;
			}
			LOG_WRITE("Wait for invite Team............");
			iDelayInvite ++;
			return TRUE;
		}

		CSYS_Type* sysList = NULL;
		CSYS_Type* sysInt32 = NULL;
		CSYS_Type* sysUInt64 = NULL;

		CSYS_Type* sysType = NULL;

		CSYS_Assembly* sysAssembly = CSYS_Assembly::Load("mscorlib");

		if (sysAssembly){
			sysList = sysAssembly->GetType("System.Collections.Generic.List`1");
			sysUInt64 = sysAssembly->GetType("System.UInt64");

			sysType = sysAssembly->GetType("System.Type");
		}
		LOG_WRITE("Type:%p,%p",sysList,sysUInt64);
		if(!sysList) return FALSE;
		if(!sysUInt64) return FALSE;

		CSYS_Array *pArrParams = CSYS_Array::CreateInstance(sysType, 1);
		pArrParams->SetValue(sysUInt64, 0);

		CSYS_Type *pTypeListReal =  CSYS_TypeEx::MakeGenericType(sysList, pArrParams);
		LOG_WRITE("pTypeListReal:%p",pTypeListReal);

		CSYS_ListEx* lstFriend = (CSYS_ListEx*)Activator::CreateInstance(pTypeListReal);
		LOG_WRITE("lstFriend:%p",lstFriend);
		//add list item

		for(int i =0; i < iCount; i++){
			CRelation * pRelation = (CRelation *)pRelationList->get_Item(i);
			CStdStringU czName = pRelation->get_Name();
			ULONGLONG uGuid = pRelation->get_Guid();
			if (g_pGame->m_TeamOption.bInviteFriends) {
				LOG_WRITE("Add friends into the Array.........[%s] [%llu]", _U2A(czName).c_str(), uGuid);
				lstFriend->Add_UInt64(uGuid);
			}
			else {
				if (czName.Compare(czMember1) == 0) lstFriend->Add_UInt64(uGuid);
				if (czName.Compare(czMember2) == 0)	lstFriend->Add_UInt64(uGuid);
				if (czName.Compare(czMember3) == 0) lstFriend->Add_UInt64(uGuid);
				if (czName.Compare(czMember4) == 0) lstFriend->Add_UInt64(uGuid);
				if (czName.Compare(czMember5) == 0) lstFriend->Add_UInt64(uGuid);
			}
		}

		if (g_pGame->m_TeamOption.bInviteFriends) LOG_WRITE("Invite All friends.........");
		LOG_WRITE("player[%08X] - [%08X]", pPlayer, lstFriend);
		pPlayer->ReqInviteTeam((LPVOID)lstFriend, 0, 0);
		iDelayInvite = 1;*/

		return TRUE;
	}
	return FALSE;
}	

void CGameControl::OpenInvite(){
	CUE_Transform *pTeamMem = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem");
	if(pTeamMem){
		int nCount = pTeamMem->get_childCount();
		int idx = 0;
		for(int i=0; i < nCount; i++){
			CUE_Transform *pMem = pTeamMem->GetChild(i);
			if(!IsShowTransform(pMem)) continue;
			CTeamMemberUIInfo *pMemberInfo = (CTeamMemberUIInfo *)pMem->GetComponent(m_gameSysTypes->Get(TYPE_TeamMemberUIInfo));
			if(pMemberInfo){

				CStdString czName =  _U2A(pMemberInfo->get_PlayerName().c_str());
				if(czName.IsEmpty()){
					pMemberInfo->OnClickInvite();
					return;
				}
				
			}
		}
	}
}

BOOL CGameControl::TeamInviteAccept(LPCSTR szName)
{
	if(CMessageBoxWithCheckBox::IsTeamInviteBy(szName)){
		CMessageBoxWithCheckBox *pMsg = CMessageBoxWithCheckBox::Instance();
		LOG_WRITE("OnOk...");
		pMsg->MessageBoxOK();
		return TRUE;
	}
	return FALSE;
}
void CGameControl::SwitchTeamTab(){
	//if(CTeamList::Instance() != 0) return;
	CUE_Transform *pTab = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:ButtonC");
	if(!pTab) return;
	CTabController *pTabController = (CTabController *)pTab->GetComponent(m_gameSysTypes->Get(TYPE_TabController));
	if(!pTabController) return;
	if(pTab->get_childCount() < 2) return;
	CUE_Transform *pTeamTab = pTab->GetChild(1);
	if(!pTeamTab) return;
	CUE_Component *pTeamTabButton = pTeamTab->GetComponent(m_gameSysTypes->Get(TYPE_TabButton));
	pTabController->DoChangeTab(pTeamTabButton);
}
BOOL CGameControl::IsHaveTeam()
{
	if(CTeamList::Instance() == 0) {
		LOG_WRITE("CGameControl::IsHaveTeam()..................");
		OnTeamTabClick();
		return FALSE;
	}
	CUE_Transform *pButtons = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:Buttons");
	if(!pButtons) return FALSE;
	BOOL bShowButtons = IsShowTransform(pButtons);
	//LOG_WRITE("CGameControl::IsHaveTeam [%d]",bShowButtons);
	return !bShowButtons; 
}

BOOL CGameControl::CanLeaveTeam()
{
	return TRUE;
}

void CGameControl::TeamLeave()
{
	LOG_WRITE("CGameControl::TeamLeave...");
	if(ProcessMessageBox(u"Đồng ý thoát đội?", MSG_OK))
		return;
	 CMyTeamController* pMyTeam = CMyTeamController::Instance();
	 if(pMyTeam){
		LOG_WRITE("CGameControl::TeamLeave...OnClickTeam");
		pMyTeam->OnClickTeam();
		return;
	 }
	 CTeamList *pTeamList = CTeamList::Instance();
	 if(pTeamList){
		 //Open TeamController
		 LOG_WRITE("CGameControl::TeamLeave...OnCreateTeam");
		 pTeamList->OnCreateTeam();
		 return;
	 }
}


BOOL CGameControl::ProcessMessageBox(LPCUSTR czTxt, int iID){
	CMessageBoxController *pMsg = CMessageBoxController::Instance();
	if(!pMsg) return FALSE;
	CStdStringU czMsgText = pMsg->getText();
	if(czMsgText.Find(czTxt) >=0){
		if(iID == MSG_OK){
			LOG_WRITE("OK>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
			pMsg->MessageBoxOK();
			return TRUE;
		}
		if(iID == MSG_CANCEL){
			pMsg->MessageBoxCancel();
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CGameControl::IsLeader(){
	CUE_Transform *pTeamMem = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem");
	if(pTeamMem){
		int nCount = pTeamMem->get_childCount();
		int idx = 0;
		for(int i=0; i < nCount; i++){
			CUE_Transform *pMem = pTeamMem->GetChild(i);
			if(!IsShowTransform(pMem)) continue;
			CTeamMemberUIInfo *pMemberInfo = (CTeamMemberUIInfo *)pMem->GetComponent(m_gameSysTypes->Get(TYPE_TeamMemberUIInfo));
			if(pMemberInfo){
				
				CStdString czName =  _U2A(pMemberInfo->get_PlayerName().c_str());
				if(idx == 0){
					return (czName.Compare(g_pGame->m_accountInfo.czRoleName) == 0);
				}
				return FALSE;
			}
		}
	}
	return FALSE;
}

BOOL CGameControl::IsRightLeader(LPCSTR szName)
{
	CUE_Transform *pTeamMem = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem");
	if(pTeamMem){
		int nCount = pTeamMem->get_childCount();
		int idx = 0;
		for(int i=0; i < nCount; i++){
			CUE_Transform *pMem = pTeamMem->GetChild(i);
			if(!IsShowTransform(pMem)) continue;
			CTeamMemberUIInfo *pMemberInfo = (CTeamMemberUIInfo *)pMem->GetComponent(m_gameSysTypes->Get(TYPE_TeamMemberUIInfo));
			if(pMemberInfo){

				CStdString czName =  _U2A(pMemberInfo->get_PlayerName().c_str());
				if(idx == 0){
					//LOG_WRITE("IsRightLeader[%s][%s]",czName.c_str(), szName);
					return (czName.Compare(szName) == 0);
				}
				return FALSE;
			}
		}
	}
	return FALSE;
}

BOOL CGameControl::IsFullMemberInController(MEMBER* pMembers)
{
	CUE_Transform *pGrid =  m_pPopUIRoot->GetChildByPath(u"TeamRoot:Offset:MyTeamParent:MyTeam:List Of Team Member:Grid");
	if(!pGrid) return FALSE;
	int count = pGrid->get_childCount();

	int countRightMember = 0;
	int countMember = 0;
	for(int i = 0; i< count ;i++){
		CUE_Transform *pItem = pGrid->GetChild(i);
		if(!IsShowTransform(pItem))continue;

		CTeamMemberItem *pMemberInfo = (CTeamMemberItem*)pItem->GetComponent(m_gameSysTypes->Get(TYPE_TeamMemberItem));
		if(!pMemberInfo) continue;
		CStdString czNameMember = _U2A(pMemberInfo->get_PlayerName().c_str());
		if(czNameMember.IsEmpty()) continue;
		//LOG_WRITE("CGameControl::IsFullMember...CheckMember[%s]",czNameMember.c_str());
		if(i == 0) continue;
		countMember++;
		BOOL bRightMember = FALSE;

		for(int j = 0; j < MAX_NUM_TEAMMEMBER; j++){
			if(pMembers[j].czTeamName[0] > 0 && czNameMember.compare(pMembers[j].czTeamName) == 0){
				bRightMember = TRUE;
				countRightMember++;
				break;
			}
		}
		if(!bRightMember){
			//LOG_WRITE("[%s] This members is not in MembersList",czNameMember.c_str());
			/*
			if(bKickOther){
				CMyTeamController *pTeamController = CMyTeamController::Instance();
				CTeamMenu *pTeamMenu = NULL;
				if(pTeamController){
					pTeamMenu = pTeamController->get_Menu();
					if(pTeamController->get_curSelectItem() != pMemberInfo){
						pMemberInfo->OnItemClick();
						return FALSE;
					}
				}
				
				if(pTeamMenu){
					pTeamMenu->OnClickKickBtn();
					return FALSE;
				}
				return FALSE;
			}
			*/
		}
	}
	int countMemberInList = 0;
	for(int k= 1; k < MAX_NUM_TEAMMEMBER; k++){
		if(pMembers[k].czTeamName[0] > 0) countMemberInList++;
	}
	//BOOL bIsFullMember = (countMember == countRightMember) && (countMember == countMemberInList);
	BOOL bIsFullMember = (countRightMember == countMemberInList);

	//LOG_WRITE("%d bIsFullMember %d countMember %d countRightMember %d countMemberInList",bIsFullMember,countMember,countRightMember,countMemberInList);
	return bIsFullMember; 

}
BOOL CGameControl::IsFullMember(MEMBER* pMembers)
{
	//LOG_WRITE("CGameControl::IsFullMember...");
	if(CTeamController::Instance()){
		return IsFullMemberInController(pMembers);
	}
	if(!IsHaveTeam()) return FALSE;
	CUE_Transform *pTeamMember =  m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem");
	if(!pTeamMember) return FALSE;
	int count = pTeamMember->get_childCount();
	int countRightMember = 0;
	int countMember = 0;
	for(int i = 0; i< count ;i++){
		CUE_Transform *pItem = pTeamMember->GetChild(i);
		if(!IsShowTransform(pItem))continue;
		
		CTeamMemberUIInfo *pMemberInfo = (CTeamMemberUIInfo *)pItem->GetComponent(m_gameSysTypes->Get(TYPE_TeamMemberUIInfo));
		if(!pMemberInfo) continue;
		CStdString czNameMember = _U2A(pMemberInfo->get_PlayerName().c_str());
		if(czNameMember.IsEmpty()) continue;
		//LOG_WRITE("CGameControl::IsFullMember...CheckMember[%s]",czNameMember.c_str());
		if(i == 0) continue;
		countMember++;
		BOOL bRightMember = FALSE;
		
		for(int j = 0; j < MAX_NUM_TEAMMEMBER; j++){
			if(pMembers[j].czTeamName[0] > 0 && czNameMember.compare(pMembers[j].czTeamName) == 0){
				bRightMember = TRUE;
				countRightMember++;
				break;
			}
		}
		if(!bRightMember){
			//LOG_WRITE("[%s] This members is not in MembersList",czNameMember.c_str());
			
			/*
			if(bKickOther){
				CTeamList *pTeamList = CTeamList::Instance();
				CTeamMenuFast *pTeamMenuFast = NULL;
				if(pTeamList){
					pTeamMenuFast = pTeamList->get_TeamMenuFast();
				}
				if(!pMemberInfo->GetCurSelLight()){
					pMemberInfo->OnItemClick();
					return FALSE;
				}
				if(pTeamMenuFast){
					pTeamMenuFast->OnClickKick();
					return FALSE;
				}
				return FALSE;
			}
			*/
		}
	}
	int countMemberInList = 0;
	for(int k= 1; k < MAX_NUM_TEAMMEMBER; k++){
		if(pMembers[k].czTeamName[0] > 0) countMemberInList++;
	}
	//BOOL bIsFullMember = (countMember == countRightMember) && (countMember == countMemberInList);
	BOOL bIsFullMember = (countRightMember == countMemberInList);
	//LOG_WRITE("%d bIsFullMember %d countMember %d countRightMember %d countMemberInList",bIsFullMember,countMember,countRightMember,countMemberInList);
	return bIsFullMember; 
}

BOOL CGameControl::KickMemberInController(MEMBER* pMembers)
{
	CUE_Transform *pGrid =  m_pPopUIRoot->GetChildByPath(u"TeamRoot:Offset:MyTeamParent:MyTeam:List Of Team Member:Grid");
	if(!pGrid) return FALSE;
	int count = pGrid->get_childCount();

	int countRightMember = 0;
	int countMember = 0;
	for(int i = 0; i< count ;i++){
		CUE_Transform *pItem = pGrid->GetChild(i);
		if(!IsShowTransform(pItem))continue;

		CTeamMemberItem *pMemberInfo = (CTeamMemberItem*)pItem->GetComponent(m_gameSysTypes->Get(TYPE_TeamMemberItem));
		if(!pMemberInfo) continue;
		CStdString czNameMember = _U2A(pMemberInfo->get_PlayerName().c_str());
		if(czNameMember.IsEmpty()) continue;
		//LOG_WRITE("CGameControl::IsFullMember...CheckMember[%s]",czNameMember.c_str());
		if(i == 0) continue;
		countMember++;
		BOOL bRightMember = FALSE;

		for(int j = 0; j < MAX_NUM_TEAMMEMBER; j++){
			if(pMembers[j].czTeamName[0] > 0 && czNameMember.compare(pMembers[j].czTeamName) == 0){
				bRightMember = TRUE;
				countRightMember++;
				break;
			}
		}
		if(!bRightMember){
			//LOG_WRITE("[%s] This members is not in MembersList",czNameMember.c_str());
			CMyTeamController *pTeamController = CMyTeamController::Instance();
			CTeamMenu *pTeamMenu = NULL;
			if(pTeamController){
				pTeamMenu = pTeamController->get_Menu();
				if(pTeamController->get_curSelectItem() != pMemberInfo){
					pMemberInfo->OnItemClick();
					return TRUE;
				}
			}

			if(pTeamMenu){
				pTeamMenu->OnClickKickBtn();
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameControl::KickMember(MEMBER* pMembers)
{
	if(CTeamController::Instance()){
		return KickMemberInController(pMembers);
	}
	else{
		
	}
	if(!IsHaveTeam()) return FALSE;
	CUE_Transform *pTeamMember =  m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem");
	if(!pTeamMember) return FALSE;
	int count = pTeamMember->get_childCount();
	int countRightMember = 0;
	int countMember = 0;
	for(int i = 0; i< count ;i++){
		CUE_Transform *pItem = pTeamMember->GetChild(i);
		if(!IsShowTransform(pItem))continue;

		CTeamMemberUIInfo *pMemberInfo = (CTeamMemberUIInfo *)pItem->GetComponent(m_gameSysTypes->Get(TYPE_TeamMemberUIInfo));
		if(!pMemberInfo) continue;
		CStdString czNameMember = _U2A(pMemberInfo->get_PlayerName().c_str());
		if(czNameMember.IsEmpty()) continue;
		//LOG_WRITE("CGameControl::IsFullMember...CheckMember[%s]",czNameMember.c_str());
		if(i == 0) continue;
		countMember++;
		BOOL bRightMember = FALSE;

		for(int j = 0; j < MAX_NUM_TEAMMEMBER; j++){
			if(pMembers[j].czTeamName[0] > 0 && czNameMember.compare(pMembers[j].czTeamName) == 0){
				bRightMember = TRUE;
				countRightMember++;
				break;
			}
		}
		if(!bRightMember){
			
			//LOG_WRITE("[%s] This members is not in MembersList",czNameMember.c_str());
			CTeamList *pTeamList = CTeamList::Instance();
			CTeamMenuFast *pTeamMenuFast = NULL;
			if(pTeamList){
				LOG_WRITE("CGameControl::TeamLeave...OnCreateTeam");
				pTeamList->OnCreateTeam();
				return TRUE;
				//pTeamMenuFast = pTeamList->get_TeamMenuFast();
				//LOG_WRITE("pMemberInfo [%p] [%p] pTeamMenuFast [%p]",pTeamList->get_curSelectItem(),pMemberInfo,pTeamMenuFast);
				//if(pTeamList->get_curSelectItem() != pMemberInfo){
				//	LOG_WRITE("pMemberInfo->OnItemClick()");
				//	pMemberInfo->OnItemClick();
				//	return TRUE;
				//}
			}
			
			//if(!pMemberInfo->GetCurSelLight()){
			//	pMemberInfo->OnItemClick();
			//	return TRUE;
			//}
			/*
			if(pTeamMenuFast){
				LOG_WRITE("pTeamMenuFast->OnClickKick()");
				pTeamMenuFast->OnClickKick();
				return TRUE;
			}
			*/
			return TRUE;
		}
	}
	return FALSE;

}

void CGameControl::SwitchAutoFight( BOOL bSwicth /*= FALSE*/ )
{
	
	CPlayerData *pData = CGameManager::get_PlayerDataPool();
	if (!pData) return;
	BOOL bAutoCombat = pData->IsAutoCombat();
	BOOL bIsOpen = pData->IsOpenAutoCombat();
	if (!bSwicth && bIsOpen) { //tat auto danh 
		LOG_WRITE("CGameControl::SwitchAutoFight......OFF");
		CChatFrameController::OnClickStopAutoFight();
		return;
	}
	if (bSwicth && !bIsOpen) { //bat auto danh
		LOG_WRITE("CGameControl::SwitchAutoFight......ON");
		CChatFrameController::OnClickAutoFight();
		return;
	}	
}

CUE_Transform * CGameControl::getTransformFromString(CUE_Transform *p,  CStdString czString )
{
	CTransform *p1 = (CTransform *)p;
	CStdStringU czStringz = czString.c_str();
	return p1->Find(czStringz);
}

void CGameControl::CloseDialog()
{
	ClosePopManyChar();
	
	CUIManager *pUIManagerInstance = CUIManager::Intance();
	pUIManagerInstance->CloseAllTipUI();

	if (IsShowPopUI()) {
		LOG_WRITE("Close dialog");
		pUIManagerInstance->CloseAllPopUI();
		return;
	}

	/*CUE_Transform *pUI = g_pGameControl->m_pPopUIRoot->GetChildByName(u"asynpvp.asynpvproot");
	if (g_pGameControl->IsShowTransform(pUI)) {
		g_pGameControl->Clicked(pUI->GetChildByPath(u"Offset:Frame (1):CloseButton"));
	}

	if (!g_pGameControl->IsShowPopUI()) return;
	CChatInfoController *pIns = CChatInfoController::Instance();
	if (pIns) pIns->OnCloseClick();

	CRecoverySettingLogic *pPatch = CRecoverySettingLogic::Instance();
	if (pPatch) pPatch->OnClickClose();

	CUIScrollExchangeController *pExchange = CUIScrollExchangeController::Instance();
	if (pExchange) {
		LOG_WRITE("Close pExchange");
		pExchange->OnClickCloseBtn();
		return;
	}

	CTeamController *pTeamCtrl = CTeamController::Instance();
	if (pTeamCtrl) {
		LOG_WRITE("Close Team");
		pTeamCtrl->OnClose();
		return;
	}

	CExamController *pexam = CExamController::Instance();
	if (pexam) {
		LOG_WRITE("Close pexam");
		pexam->OnClickCloseWindow();
		return;
	}

	CUIJianMuXBPanel *pjianmu = CUIJianMuXBPanel::Instance();
	if (pjianmu) {
		LOG_WRITE("Close pjianmu");
		pjianmu->OnClickClose();
		return;
	}

	CTowerWindow *ptower = CTowerWindow::Instance();
	if (ptower) {
		LOG_WRITE("Close ptower");
		ptower->OnClickClose();
		return;
	}

	CSceneMapController *pScene = CSceneMapController::Instance();
	if (pScene) {
		LOG_WRITE("Close pScene");
		pScene->OnCloseWindow();
		return;
	}

	CSocialRootController *pSocial = CSocialRootController::Instance();
	if (pSocial) {
		LOG_WRITE("Close pSocial");
		pSocial->OnClickCloseWindow();
		return;
	}

	CSettingController *pSetting = CSettingController::Instance();
	if (pSetting) {
		LOG_WRITE("Close pSetting");
		pSetting->OnCloseClick();
		return;
	}

	CImmortalityViewLogic *pImmo = CImmortalityViewLogic::Instance();
	if (pImmo) {
		LOG_WRITE("Close pImmo");
		pImmo->OnClickClose();
		return;
	}

	CFuLiRootController *pFuli = CFuLiRootController::Instance();
	if (pFuli) {
		LOG_WRITE("Close pFuli");
		pFuli->Close();
		return;
	}

	CMisInfoController *pMis = CMisInfoController::Instance();
	if (pMis) {
		LOG_WRITE("Close pMis");
		pMis->CloseWindow();
		return;
	}

	CFirstCharge *pFirst = CFirstCharge::Instance();
	if (pFirst) {
		LOG_WRITE("Close pFirst");
		pFirst->CloseClick();
		return;
	}

	CTeHuiRootController *pTehui = CTeHuiRootController::Instance();
	if (pTehui) {
		LOG_WRITE("Close pTehui");
		pTehui->Close();
		return;
	}

	CShoppingMallController *pshoping = CShoppingMallController::Instance();
	if (pshoping) {
		LOG_WRITE("Close pshoping");
		pshoping->Close();
		return;
	}

	CGrowWayViewLogic *pGrow = CGrowWayViewLogic::Instance();
	if (pGrow) {
		LOG_WRITE("Close pGrow");
		pGrow->OnClickClose();
		return;
	}

	CArtifactProveController *parti = CArtifactProveController::Instance();
	if (parti) {
		LOG_WRITE("Close parti");
		parti->OnClickClose();
		return;
	}

	CActivityRootLogic *pact = CActivityRootLogic::Instance();
	if (pact) {
		LOG_WRITE("Close pact");
		pact->OnClickClose();
		return;
	}

	CEquipBuildWindowController *equip = CEquipBuildWindowController::Instance();
	if (equip) {
		LOG_WRITE("Close equip");
		equip->OnClose();
		return;
	}

	CSkillRootController *pskill = CSkillRootController::Instance();
	if (pskill) {
		LOG_WRITE("Close pskill");
		pskill->CloseWindow();
		return;
	}

	CGuildController *pguild = CGuildController::Instance();
	if (pguild) {
		LOG_WRITE("Close pguild");
		pguild->OnClose();
		return;
	}

	CAchievementControl *pachie = CAchievementControl::Instance();
	if (pachie) {
		LOG_WRITE("Close pachie");
		pachie->OnClose();
		return;
	}

	CUIXiuZhenController *puixiu = CUIXiuZhenController::Instance();
	if (puixiu) {
		LOG_WRITE("Close puixiu");
		puixiu->OnClickClose();
		return;
	}

	CUIServant *puiser = CUIServant::Instance();
	if (puiser) {
		LOG_WRITE("Close puiser");
		puiser->ClickCloseButton();
		return;
	}

	CMentorRootController *pmentor = CMentorRootController::Instance();
	if (pmentor) {
		LOG_WRITE("Close pmentor");
		pmentor->OnClickClose();
		return;
	}

	CUIFairy *puifairy = CUIFairy::Instance();
	if (puifairy) {
		LOG_WRITE("Close puifairy");
		puifairy->ClickCloseButton();
		return;
	}
	
	CUIPetRoot *puipet = CUIPetRoot::Instance();
	if (puipet) {
		LOG_WRITE("Close puipet");
		puipet->OnClickClose();
		return;
	}

	CRankWindow *prank = CRankWindow::Instance();
	if (prank) {
		LOG_WRITE("Close prank");
		prank->OnCloseClick();
		return;
	}

	CRoleViewWindow *pRole = CRoleViewWindow::Instance();
	if (pRole) {
		LOG_WRITE("Close pRole");
		pRole->CloseWindow();
		return;
	}

	CKnapsackController *pKNAP = CKnapsackController::Instance();
	if (pKNAP) {
		LOG_WRITE("Close pKNAP");
		pKNAP->OnClose();
		return;
	}*/

	
	
	/*int iCount = m_pPopUIRoot->get_childCount();
	if (iCount != 0) {
		for (int i = 0; i < iCount; i++) {
			CUE_Transform *pPop = m_pPopUIRoot->GetChild(i);
			if (IsShowTransform(pPop)) {
				CUE_Transform *pOffSet = pPop->GetChildByName(u"Offset");
				if (IsShowTransform(pOffSet)) {
					CUE_Transform *pFrame = pOffSet->GetChildByName(u"Frame");
					CUE_Transform *pFrameFolder = pOffSet->GetChildByName(u"Frame_Folder");
					CUE_Transform *pFrameFolder1 = pOffSet->GetChildByName(u"frameFolder");
					CUE_Transform *pFrameFolder2 = pOffSet->GetChildByName(u"FrameFolder");
					CUE_Transform *pFrameFolder3 = pOffSet->GetChildByName(u"frame");
					if (IsShowTransform(pFrame)) {
						if (ButtonCloseIsShow(pFrame)) return;
						else {
							CUE_Transform *pFrame1 = pFrame->GetChildByName(u"Frame");
							if (IsShowTransform(pFrame1)) {
								if (ButtonCloseIsShow(pFrame1)) return;
							}
						}
					}

					else if (IsShowTransform(pFrameFolder)) {
						if (ButtonCloseIsShow(pFrameFolder)) return;
					}

					else if (IsShowTransform(pFrameFolder1)) {
						if (ButtonCloseIsShow(pFrameFolder1)) return;
					}

					else if (IsShowTransform(pFrameFolder2)) {
						if (ButtonCloseIsShow(pFrameFolder2)) return;
					}

					else if (IsShowTransform(pFrameFolder3)) {
						if (ButtonCloseIsShow(pFrameFolder3)) return;
					}
				}

				
			}
		}
	}*/
	
}

BOOL CGameControl::IsMessageBox( CStdStringU czU, BOOL bSwitch )
{
	CUE_Transform *p = m_pMessageUIRoot;
	if ( IsShowTransform(p)) {
		CUE_Transform *pMsgBox = p->GetChildByName(u"messageboxroot");
		if (IsShowTransform(pMsgBox)) {
			CUE_Transform *pContent = pMsgBox->GetChildByPath(u"Offset:Sprite:Content");
			if (pContent) {
				CStdStringU czUContent = GetTextU(pContent);
				if (czUContent.Find(czU) >= 0) {//u"Xác nhận chọn ngựa"
					if (!bSwitch) {
						LOG_WRITE("Cancel MessageBox"); 
						Clicked(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:01CancelButton"));
						return TRUE;
					}

					if (bSwitch) {
						LOG_WRITE("OK MessageBox");
						Clicked(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:03OKButton"));
						return TRUE;
					}
					return TRUE;
				}
			}
		}//messageboxroot

		CUE_Transform *pMsgBoxW = p->GetChildByName(u"messageboxwithcheckbox");
		if (IsShowTransform(pMsgBoxW)) {
			CUE_Transform *pContent = pMsgBoxW->GetChildByPath(u"Offset:lbl_Content");
			if (pContent) {
				CStdStringU czUContent = GetTextU(pContent);
				if (czUContent.Find(czU) >= 0) {
					if (!bSwitch) {
						LOG_WRITE("Cancel MessageBox"); 
						Clicked(pMsgBoxW->GetChildByPath(u"Offset:Buttons:btn_Cancel"));
						return TRUE;
					}

					if (bSwitch) {
						LOG_WRITE("OK MessageBox");
						Clicked(pMsgBoxW->GetChildByPath(u"Offset:Buttons:btn_Sure"));
						return TRUE;
					}
					return TRUE;
				}
			}
		}
	}

	
	return FALSE;

	/*CMessageBoxController* pInstance = CMessageBoxController::Instance();
	if (!pInstance) return FALSE;
	CStdStringU czContent = pInstance->getText();
	if (czContent.Find(czU) < 0) return FALSE;
	if (!bSwitch) {
		LOG_WRITE("Cancel MessageBox");
		pInstance->MessageBoxCancel();
	}
	if (bSwitch) {
		LOG_WRITE("OK MessageBox");
		pInstance->MessageBoxOK();
	}
	return TRUE;*/
}

BOOL CGameControl::IsMap( CStdStringU czU )
{
	CRadarWindow *pInstance = CRadarWindow::Instance();
	if (!pInstance) return FALSE;
	CStdStringU czUName = pInstance->getSceneName();
	if (czUName.Find(czU) < 0){
		LOG_WRITE("CGameControl::NOTIsMap...........");
		return FALSE;
	}
	LOG_WRITE("CGameControl::IsMap...........");
	return TRUE;
}

BOOL CGameControl::IsActivity( CStdStringU czU, BOOL &bFinished, BOOL bOnlyCheck)
{
	CStdString czActivity = _U2A(czU).c_str();
	CUE_Transform *pWnd = m_pPopUIRoot->GetChildByName(u"activity.activity_frame");
	if (!IsShowTransform(pWnd)) return FALSE;
	CUE_Transform *pPanel = pWnd->GetChildByPath(u"Offset:ActivityList_huodong(Clone):huodonglist:Offset:textlist:huodonglistPanel");
	if (IsShowTransform(pPanel)) {
		CUE_Transform *pGrid = pPanel->GetChildByName(u"Grid");
		int iCount = pGrid->get_childCount();
		if (iCount == 0) return FALSE;
		for (int i = 0; i < iCount; i++ ) {
			CUE_Transform *pActiv = pGrid->GetChild(i);
			CStdStringU czName = pActiv->GetName()->GetText();
			if (czName.Find(czU) == 0 && IsShowTransform(pActiv)) {
				CUE_Transform *pBtnGo = pActiv->GetChildByPath(u"zhuangtai:qianwang");
				if (IsShowTransform(pBtnGo)) {
					/*LOG_WRITE("---[%s]", _U2A(pBtnGo->GetPath()).c_str());*/
					if (!bOnlyCheck) Clicked(pBtnGo);
					_theApp->NextTimer(1000);
					return TRUE;
				}
			}
		}
		LOG_WRITE("NOO");
		bFinished = TRUE;
		return TRUE;
		
	}
	return FALSE;
		
}

BOOL CGameControl::IsStoryUIRoot()
{
	CUE_Transform *p = m_pStoryUIRoot;
	if (IsShowTransform(p)) {
		CUE_Transform *pDialog = p->GetChildByName(u"synopsis.taskdialog");
		if (IsShowTransform(pDialog)) {

			CUE_Transform *pGrid = pDialog->GetChildByPath(u"Offset:dialogSmall:btn_choiceMis:Grid");
			if (pGrid) {
				int iCount = pGrid->get_childCount();
				if (iCount != 0) {
					for (int i = 0; i < iCount; i++ ) {
						CUE_Transform *pChild = pGrid->GetChild(i);
						if (IsShowTransform(pChild)) {
							CUE_Transform *pText = pChild->GetChildByName(u"lbl_content");
							CStdStringU czText = GetTextU(pText);
							if (czText.Find(u"Kẹp Giấy Đổi Biệt") >= 0) {
								Tap(pText);
								return TRUE;
							}
						}
					}
				}
			}

			CloseNPCTalk();
			return TRUE;
		}

		CUE_Transform *pSecneDialog = p->GetChildByName(u"synopsis.cutscenedialog");
		if (IsShowTransform(pSecneDialog)) {
			CUE_Transform *pSkipBtn = pSecneDialog->GetChildByPath(u"Offset:Top:SkikBtn");
			if (IsShowTransform(pSkipBtn)) Clicked(pSkipBtn->GetChildByName(u"Label"));
			else LOG_WRITE("Is Cut Scene Dialog..................");
			return TRUE;
		}

		CUE_Transform *pSynopsis = p->GetChildByName(u"Synopsis");
		if (IsShowTransform(pSynopsis)) {
			CUE_Transform *pSkipBtn = pSynopsis->GetChildByPath(u"Offset:dialogLarge:btn_next");
			if (IsShowTransform(pSkipBtn)) Tap(pSkipBtn);
			else LOG_WRITE("Is Cut Scene Dialog..................");
			return TRUE;
		}
	}
	return FALSE;
}

void CGameControl::ClickButtonHuDong()
{
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) return;
	LOG_WRITE("CGameControl::ClickButtonHuDong().................");
	pInstance->OnClickHuoDong();
	_theApp->NextTimer(1000);
}

BOOL CGameControl::IsMissionTrack( CStdStringU czU, UINT &uTransform )
{
	CStdString czActivity = _U2A(czU).c_str();
	 
	CMissionTrack *pIns = CMissionTrack::Instance();
	if (pIns) {
		CUE_Transform *pPanel = get_Transform(UINT(pIns));
		CUE_Transform *pGrid = pPanel->GetChildByName(u"Grid");
		for (int i = 0; i < pGrid->get_childCount(); i++) {
			LOG_WRITE("LOOP............................");
			CUE_Transform *pChild = pGrid->GetChild(i);
			if (pChild) {
				CUE_Transform *pname = pChild->GetChildByPath(u"Offest:Sprite:TypeLabel");
				CStdStringU czName = GetTextU(pname);
				if (czName.Find(czU) >= 0) {
					uTransform = (UINT)pChild;
					//LOG_WRITE("%08X", pChild);
					return TRUE;
				}
			}
		}
		LOG_WRITE("End........");
	}
	return FALSE;
}

BOOL CGameControl::IsProcessing()
{
	CPickItemProgressController *pInstance = CPickItemProgressController::Instance();
	if (pInstance) {
		BOOL bIsRunning = pInstance->IsRunning();
		if (!bIsRunning) return FALSE;
		CStdStringU czName = pInstance->m_OptDecLabel();
		if (czName.Compare(u"Đang đào kho báu") == 0) return FALSE;
		//LOG_WRITE("[%s]", _U2A(czName).c_str());
		LOG_WRITE("CGameControl::IsProcessing().........");
		return TRUE;
	}
	
	if (IsShowTransform(m_pBaseUIRoot)) {
		CUE_Transform *pBar = m_pBaseUIRoot->GetChildByName(u"SkillProgressRoot");
		if (g_pGameControl->IsShowTransform(pBar)) {
			CSkillProgressController *pInstance = CSkillProgressController::Instance();
			if (pInstance) {
				CStdStringU czText = pInstance->getText();
				if (czText.Compare(u"Truyền tống") == 0) {
					LOG_WRITE("------------>Truyền tống");
					return TRUE;
				}
				//LOG_WRITE("------------>[%s]", _U2A(czText).c_str());
			}		
		}
	}
	return FALSE;
}

BOOL CGameControl::get_LoadingScene()
{
	BOOL bLoading = CGameManager::get_LoadingScene();
	if (!bLoading) return FALSE;
	LOG_WRITE("CGameControl::get_LoadingScene()...........");
	_theApp->NextTimer(1000);
	return TRUE;
}

BOOL CGameControl::IsMoving(BOOL bStopMove)
{
	CObj_MainPlayer *pMainPlayer = get_MainPlayer();
	if (!pMainPlayer) return FALSE;
	CObj_Char *pChar = (CObj_Char*)pMainPlayer;
	BOOL bIsMoving = pChar->get_IsMoving();
	if (!bIsMoving) return FALSE;

	if (bStopMove) {
		LOG_WRITE("CGameControl::Stop Move.........");
		pMainPlayer->StopMoveAndSync();
		return TRUE;
	}
	LOG_WRITE("CGameControl::IsMoving()......................");
	return TRUE;
	
}

BOOL CGameControl::IsMovingXYZ()
{
	static float x = 0,y = 0,z = 0;
	CObj_MainPlayer *pMainplayer = get_MainPlayer();
	if (!pMainplayer) return FALSE;
	CObj *pObj = (CObj*)pMainplayer;

	CUE_Vector3 *pMainPlayerPos = pObj->get_Position();
	float fx = 0, fy = 0, fz = 0;
	if (pMainPlayerPos) {
		fx = pMainPlayerPos->GetX();
		fy = pMainPlayerPos->GetY();
		fz = pMainPlayerPos->GetZ();

		if (x != fx || y != fy || z != fz) {
			x = fx; y = fy; z = fz;
			LOG_WRITE("Player is moving.....");
			return TRUE;
		}

		LOG_WRITE("Player is standing.....");
	}
	return FALSE;
}

BOOL CGameControl::IsShowPopUI()
{
	return CUIManager::IsPopUIShow();
}

BOOL CGameControl::AutoFightIsOn()
{
	CPlayerData *pData = CGameManager::get_PlayerDataPool();
	if (!pData) return FALSE;
	BOOL bAutoCombat = pData->IsAutoCombat();
	BOOL bIsOpen = pData->IsOpenAutoCombat();
	if (!bIsOpen) return FALSE;
	//if (!bAutoCombat) return FALSE;
	LOG_WRITE("CGameControl::AutoFightIsOn()...............");
	return TRUE;
}

BOOL CGameControl::IsLowerLevel( int iNeedLevel )
{
	CUE_Transform *pLevel = m_pBaseUIRoot->GetChildByPath(u"PlayerFrameRoot:Offset:SubPanel:Level:LevelLabel");
	if (!pLevel) return FALSE;
	CStdStringU czLevel = GetTextU(pLevel);
	int iCurrentLevel = atoi(_U2A(czLevel).c_str());
	//LOG_WRITE("iCurrentLevel = %d", iCurrentLevel);
	if (iCurrentLevel >= iNeedLevel) return FALSE;
	LOG_WRITE("Current Level is Lower Need Level");
	return TRUE;
}

BOOL CGameControl::IsCenterNotice( CStdStringU czU )
{
	if (IsShowTransform(m_pStoryMessageUIRoot)) {
		CUE_Transform *p = m_pStoryMessageUIRoot->GetChildByName(u"prompt.prompt_tishi_centrenoticecontroller");
		if (IsShowTransform(p)) {
			CUE_Transform *pList = p->GetChildByName(u"Offset");
			int iAllChild = pList->get_childCount();
			for (int i = iAllChild - 1; i >= 0; i--) {
				CUE_Transform *pChild = pList->GetChild(i);
				if (IsShowTransform(pChild)) {
					CStdStringU czLabel = GetTextU(pChild);
					if (czLabel.Find(czU) >= 0) {
						LOG_WRITE("Is Right Notice..... [%s]", _U2A(czLabel).c_str());
						return TRUE;
					}
					//LOG_WRITE("Notice  [%s]", _U2A(czLabel).c_str());
				}
			}
		}
	}
	return FALSE;
}

BOOL CGameControl::IsGuildName( CStdStringU czU )
{
	CPlayerData *pData = CGameManager::get_PlayerDataPool();
	if (!pData) return FALSE;
	CGuild *pGuild = pData->GuildInfo();
	if (!pGuild) return FALSE;
	CStdStringU czName = pGuild->get_GuildName();
	if (czName.Compare(czU) != 0) return FALSE;
	LOG_WRITE("CGameControl::IsGuildName().........[%s]", _U2A(czName).c_str());
	return TRUE;
}

BOOL CGameControl::IsReliveWnd()
{
	CReliveController *pInstance = CReliveController::Instance();
	if (pInstance) {
		if (g_pGame->m_OptionTab.bUsePatchRelive) {
			LOG_WRITE("UsePatchRelive.....");
			pInstance->OnClickYuanBaoOriginal();
		}
		LOG_WRITE("CGameControl::IsReliveWnd()........................");
		pInstance->OnClickEntry();
		//CReliveController::OnClickNearRelive();
		return TRUE;
	}
	return FALSE;
}

CPlayerData		* CGameControl::get_PlayerData()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return NULL;
	return pPlayerData;
}

BOOL CGameControl::IsCopyFinishedFubenWnd()
{
	CCopySceneSettlementController *pInstance = CCopySceneSettlementController::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("Exit Fuben...");
	//if (!IsMember()) return FALSE;
	pInstance->OnExitCopyScene();
	return TRUE;
}

BOOL CGameControl::IsUILevelUpWnd()
{	
	if (!IsShowTransform(m_pTipUIRoot)) return FALSE;
	CUE_Transform *p = m_pTipUIRoot->GetChildByName(u"mainbaseui.tupotishi");
	if (!IsShowTransform(p)) return FALSE;
	LOG_WRITE("IsUILevelUpWnd::Close.................");
	Clicked(p->GetChildByPath(u"Offset:btn_cancel_anchor:btn_cancel"));
	return TRUE;
}

BOOL CGameControl::IsYingFuPopup()
{
	if (!IsShowTransform(m_pMessageUIRoot)) return FALSE;
	CUE_Transform *p = m_pMessageUIRoot->GetChildByName(u"welfare.welfare_yingfupopup");
	if (!IsShowTransform(p)) return FALSE;
	LOG_WRITE("IsYingFuPopup::Close.................");
	Clicked(p->GetChildByPath(u"Offset:Container:left:btn"));
	return TRUE;
}

void CGameControl::ExitFB()
{
	Clicked(m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:Especial_TopRightButtons:ExitCopyScene"));
}

BOOL CGameControl::IsFBResultWnd()
{
	CAsynPVPRewardLogic *pInstance = CAsynPVPRewardLogic::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("ChallengeAgain().......");
	pInstance->ChallengeAgain();
	return TRUE;
}

BOOL CGameControl::IsMember()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		BOOL bHaveTeam = pPlayerData->IsHaveTeam();
		if (!bHaveTeam) return FALSE;
		if (bHaveTeam) {
			BOOL bIsLeader = pPlayerData->PlayerIsTeamLeader();

			if (IsMemberSet()) {
				if (bIsLeader) {
					LeaveTeam();
					return TRUE;
				}
				
				//khac leader duoc chon o auto
				CStdStringU czLeaderOnUI = get_NameMemberOnUIAuto(g_pGame->m_Members, 0); //leader

				if (czLeaderOnUI.Compare(u"") != 0) {
					CStdStringU czLeaderOnGame = get_NameLeader();
					if (czLeaderOnUI.Compare(czLeaderOnGame) != 0) {
						LeaveTeam();
						return TRUE;
					}
				}
				
				return TRUE;
			}

			if (IsTeamAvailableSet(FALSE) && !bIsLeader) return TRUE;
		}
	}
	return FALSE;
}

void CGameControl::FollowLeader(BOOL bFollow)
{
	if (IsMember()) {
		CTeamList *pIns = CTeamList::Instance();
		if (!pIns) {
			OnTeamTabClick();
			return;
		}
		CStdStringU czULabel = pIns->get_FollowLabel();
		if (!bFollow) {
			if (czULabel.Compare(u"Bỏ theo") == 0) {
				LOG_WRITE("Cancel Follow Leader....................");
				pIns->OnFollow();
				return;
			}
			return;
		}
		if (czULabel.Compare(u"Bỏ theo") == 0) return;
		LOG_WRITE("Follow Leader....................");
		pIns->OnFollow();
	}
}

BOOL CGameControl::IsActivityWithName( CStdStringU czU, BOOL &bFinished )
{
	CActivityHuoDongWindow *pIns = CActivityHuoDongWindow::Instance();
	if (pIns) {
		LOG_WRITE("IsActivity wnd");
		CSYS_List *pList = pIns->get_ActivityitemList();
		//LOG_WRITE("pList = %08X", pList);
		int Count  = pList->get_Count();
		if (Count != 0) {
			for (int i = 0; i < Count; i++) {
				CActivityHuoDongItem *pItem = (CActivityHuoDongItem *)pList->get_Item(i);
				if (pItem) {
					CStdStringU czUName = pItem->get_ActivityName();
					CStdStringU czUCount = pItem->get_ActivityCountLabel();
					if (czUName.Find(czU) >= 0) {
						CUE_Component *pCom = (CUE_Component*)pItem;
						CUE_Transform *pTrans = pCom->get_transform();
						CUE_Transform *pFinish = pTrans->GetChildByPath(u"zhuangtai:Activity_Finish");
						if (IsShowTransform(pFinish)) {
							LOG_WRITE("Finished Activity....................");
							bFinished = TRUE;
							return TRUE;
						}
						LOG_WRITE("Is Right Activity.............................");
						pItem->OnItemClick();
						return TRUE;
					}
					//LOG_WRITE("item[%d] -- Ins[%08X] -- name[%s] -- count[%s]", i, pItem, _U2A(czUName).c_str(), _U2A(czUCount).c_str());
				}

			}
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}


CUE_Transform * CGameControl::get_Transform(UINT uTemp)
{
	if (uTemp == 0) return NULL;
	CUE_Component *pCom = (CUE_Component*)uTemp;
	if (!pCom) return NULL;
	return pCom->get_transform();
	//component - behavior - monobehavior - class
}

BOOL CGameControl::IsFightFb( CStdStringU czUNameFb, int iLevelDifficult )
{
	CActivityRaidWindow *pIns = CActivityRaidWindow::Instance();
	if (pIns) {
		CSYS_List *pList = pIns->get_RaidMenuItemList();
		int iCount = pList->get_Count();
		if (iCount != 0) {
			LOG_WRITE("---------------START--------------");
			for (int i = 0; i < iCount; i++) {
				CActivityRaidMenuItem *pItem = (CActivityRaidMenuItem *)pList->get_Item(i);
				CStdStringU czName1 = pItem->get_NorItemNameLabel();
				CStdStringU czName2 = pItem->get_SelItemNameLabel();

				if (czName2.Find(czUNameFb) >= 0) {
					CUE_Transform *pTrans = g_pGameControl->get_Transform((UINT)pItem);
					CUE_Transform *pSelected = pTrans->GetChildByName(u"ItemCheckedBG");
					if (g_pGameControl->IsShowTransform(pSelected)) {
						CSYS_List *pChildList = pItem->get_SecondaryItemList();
						int iChildCount = pChildList->get_Count();
						if (iChildCount != 0) {
							CUE_Transform *pTransform = g_pGameControl->get_Transform((UINT)pChildList->get_Item(iLevelDifficult));
							CUE_Transform *pSelected = pTransform->GetChildByName(u"ItemCheckedBG");
							if (!g_pGameControl->IsShowTransform(pSelected)) {
								g_pGameControl->Clicked(pTransform);
								LOG_WRITE("Selected fb level.........................");
								return TRUE;
							}

							//
							pIns->OnEnterClick();
							LOG_WRITE("Join fb.......................");
							return TRUE;
						}
						return TRUE;
					}
					LOG_WRITE("Selected fb .........................");
					g_pGameControl->Clicked(pTrans);
					return TRUE;
				}
			}
			LOG_WRITE("---------------END----------------");
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsTeamTarget( CStdStringU czUName, BOOL bIsLeader )
{
	CMyTeamController *pIns = CMyTeamController::Instance();
	if (pIns) {
		CStdStringU czUMainTargetName = pIns->get_TargetLabel();
		if (czUMainTargetName.Find(czUName) >= 0) {
			if (bIsLeader) {
				LOG_WRITE("Right........................");
				pIns->OnEnterSceneClick();
				return TRUE;
			}

			if (IsTeamAloneSet()) {
				static int i = -1;
				
				int iSLTV = g_pGame->m_TeamOption.iSLTV;
				if (IsTeamEnoughMembers(iSLTV)) {
					LOG_WRITE("Right........................");
					pIns->OnEnterSceneClick();
					return TRUE;
				}

				CStdStringU czAutoTeam = pIns->get_AutoTeamLabel();
				if (czAutoTeam.Compare(u"Tự ghép") == 0) {
					LOG_WRITE("Auto TEam......................");
					pIns->StartAutoTeam();
					return TRUE;
				}

				if (ProcessMessageBox(u"mời vào đội, đồng ý?", MSG_OK)) return TRUE;

				//

				if (i <= 0) pIns->OnHanHuaNomal();

				if (i == 10) pIns->OnHanHuaGuild();

				if (i == 20) pIns->OnHanHuaWorld();

				if (i == 30) pIns->OnHanHuaZhaomu();

				if (i >= 40) i = -1;

				i ++;

				LOG_WRITE("Wait for Loud .... [%d]", i);
				return TRUE;
			}
			return TRUE;
		}

		CTeamTargetAdjust *pInstance = CTeamTargetAdjust::Instance();
		if (!pInstance) {
			LOG_WRITE("Show Target Wnd......................");
			pIns->onClickTarget();
			return TRUE;
		}

		CSYS_List *pList = pInstance->get_SubClassList();
		int iCount = pList->get_Count();
		if (iCount != 0) {
			for (int i = 0; i < iCount; i++) {
				CJoinTeamSubItem *pItem = (CJoinTeamSubItem *)pList->get_Item(i);
				CStdStringU czUTargetName = pItem->get_secondNameLabel();
				if (czUTargetName.Find(czUName) >= 0) {
					LOG_WRITE("Select Target.................");
					pItem->OnItemClick();
					pInstance->OnOK();
				}
				//LOG_WRITE("%d -- [%08X] -- %s", i, pItem, _U2A(czUTargetName).c_str());
			}
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsLowerLevelWnd()
{
	CUICopySceneLowLevelTips *pIns = CUICopySceneLowLevelTips::Instance();
	if (!pIns) return FALSE;
	CUE_Transform *pTrans = get_Transform((UINT)pIns);
	if (!pTrans) return FALSE;
	CUE_Transform *pSelected = pTrans->GetChildByPath(u"offset:btn_Select:select");
	if (IsShowTransform(pSelected)) {
		LOG_WRITE("pIns->OnCheckBtnClick().............");
		pIns->OnCheckBtnClick();
		return FALSE;
	}
	LOG_WRITE("CGameControl::IsLowerLevelWnd().................");
	pIns->OnConfirmBtnClick();
	return TRUE;
}

BOOL CGameControl::IsNPCHeadInfo(CStdStringU czName, UINT &uObj_NPC)
{
	
	CUE_Transform *p = m_pUIRoot->GetChildByName(u"NameBoardRoot");
	if (IsShowTransform(p)) {
		int iCount = p->get_childCount();
		if (iCount != 0) {
			for (int i = 0; i < iCount; i++) {
				CUE_Transform *pNPCHeadInfo = p->GetChild(i);
				
				CStdStringU czName = pNPCHeadInfo->GetName()->GetText();
				
				if (czName.Compare(u"NPCHeadInfo") == 0) {
					CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
					CNpcHeadInfoLogic* pHeadInfo = (CNpcHeadInfoLogic *)pNPCHeadInfo->GetComponent(pType);
					if (pHeadInfo) {
						CObj_Char *pNPC = pHeadInfo->get_NPC();
						CStdStringU czNameLabel = pHeadInfo->get_NameLabel();
						//LOG_WRITE("%d -- NPC[%s]", i, _U2A(czNameLabel).c_str());
						if (czNameLabel.Find(u"Quan Ngoại Giao") >= 0) {
							uObj_NPC = (UINT)pNPC;
							return TRUE;
						}
					}
				}
			}
			LOG_WRITE("..........END............");
		}
	}
	//CUE_Transform *
	return FALSE;
}

void CGameControl::ShowMap()
{
	CRadarWindow *pIns = CRadarWindow::Instance();
	if (!pIns) return;
	LOG_WRITE("ShowSceneMap.................");
	pIns->ShowSceneMap();
}

int CGameControl::get_GoldCoin()
{
	int iGoldCoin = 0;
	CUE_Transform *pWnd = m_pPopUIRoot->GetChildByName(u"shop.shoppingmall");
	if (!pWnd) return 0;

	CUE_Transform *p = pWnd->GetChildByPath(u"Offset:Currency");
	if (IsShowTransform(p)) {
		CUE_Transform *pCount = p->GetChildByPath(u"Grid:Currency_GoldCoin:Count");
		CStdStringU czCount = GetTextU(pCount);
		if (czCount.Find(u"vạn") >= 0) return iGoldCoin = 10000;
		iGoldCoin = atoi(_U2A(czCount).c_str());
	}
	return iGoldCoin;
}

BOOL CGameControl::IsTeamEnoughMembers( int iSLTV )
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		BOOL bIsLeader = pPlayerData->PlayerIsTeamLeader();
		if (!bIsLeader) return FALSE;
		CTeam* pTeam = pPlayerData->get_TeamInfo();
		if (pTeam) {
			int iMemberCount = pTeam->GetTeamMemberCount();
			if (iMemberCount >= iSLTV) {
				LOG_WRITE("Enoughed Member.................%d", iMemberCount);
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CGameControl::MemberAccept(int iFrom)
{
	CSYS_List *pLstBrotherMember = get_BrotherhoodList();
	CSYS_List *pLstFriend = get_FriendsList();
	
	CMessageBoxWithCheckBox *pMsg = CMessageBoxWithCheckBox::Instance();
	if (pMsg) {
		CStdStringU czContent = pMsg->get_Content();

		if (iFrom == NameLeader) {
			CStdStringU czLeader = g_pGame->m_Members[0].czTeamName;
			if (czContent.Find(czLeader) >= 0) {
				LOG_WRITE("OnOk...");
				pMsg->MessageBoxOK();
				return TRUE;
			}
		}
		
		if (pLstBrotherMember && iFrom == Jiebai) {
			int iCount = pLstBrotherMember->get_Count();
			if (iCount != 0) {
				for(int i = 0; i < iCount; i++) {
					CBrotherhoodMember *pMember = (CBrotherhoodMember *)pLstBrotherMember->get_Item(i);
					if (pMember) {
						CStdStringU czName = pMember->get_MemberName();
						//LOG_WRITE("[%d] -- %s", i, _U2A(czName).c_str());
						if (czContent.Find(czName) >= 0) {
							LOG_WRITE("OnOk...");
							pMsg->MessageBoxOK();
							return TRUE;
						}
					}
				}
			}
		}

		if (pLstFriend && iFrom == Friends) {
			int iCount = pLstFriend->get_Count();
			if (iCount != 0) {
				for(int i = 0; i < iCount; i++) {
					CRelation *pFriend = (CRelation *)pLstFriend->get_Item(i);
					if (pFriend) {
						CStdStringU czName = pFriend->get_Name();
						//LOG_WRITE("[%d] -- %s", i, _U2A(czName).c_str());
						if (czContent.Find(czName) >= 0) {
							LOG_WRITE("Join team of Friend [%s]", _U2A(czName).c_str());
							pMsg->MessageBoxOK();
							return TRUE;
						}
					}
				}
			}
		}

		return FALSE;
	}
		
	return FALSE;
}

void CGameControl::CancelAcceptMessageBoxWithCheckBox()
{
	CMessageBoxWithCheckBox *pMsg = CMessageBoxWithCheckBox::Instance();
	if (pMsg) {
		LOG_WRITE("OnCancel...");
		pMsg->MessageBoxCancel();
		return;
	}
}

CStdStringU CGameControl::get_NameLeader()
{
	if (!m_pPlayerData) return u"No m_pPlayerData";
	BOOL bIsHaveTeam = m_pPlayerData->IsHaveTeam();
	if (!bIsHaveTeam) return u" NO bIsHaveTeam";
	CTeam *pTeam = m_pPlayerData->get_TeamInfo();
	if (!pTeam) return u"No pTeam";
	CTeamMember *pLeader = pTeam->GetTeamMember(0);
	if (!pLeader) return u"No pLeader";
	return pLeader->get_MemberName();
	
}

BOOL CGameControl::IsCopySceneReady()
{
	CCopySceneReady *pIns = CCopySceneReady::Instance();
	if (!pIns) return FALSE;
	LOG_WRITE("CGameControl::IsCopySceneReady()......Confirm");
	if (!IsMember()) return FALSE;
	LOG_WRITE("Join fb......................");
	pIns->OnClickConfirm();
	return TRUE;
}

CObj_MainPlayer * CGameControl::get_MainPlayer()
{
	return (CObj_MainPlayer*)CObjManager::get_MainPlayer();
	/*CUE_Transform *p = m_pUIRoot->GetChildByName(u"NameBoardRoot");
	if ((p)) {
		int iCount = p->get_childCount();
		if (iCount != 0) {
			CUE_Transform *pChild = p->GetChild(0);
			if (pChild) {
				CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","PlayerHeadInfoLogic");
				CPlayerHeadInfoLogic* pHeadInfo = (CPlayerHeadInfoLogic *)pChild->GetComponent(pType);
				if (pHeadInfo) return pHeadInfo->get_MainPlayer();
			}
		}
	}
	return NULL;*/
}

CObj_Char	* CGameControl::getNPC( CStdStringU czName )
{
	CObj_Char *pChar = NULL;
	CActiveSceneLogic *pActiveSceneLogic = CGameManager::get_CurActiveScene();
	if (pActiveSceneLogic) {
		CUE_Transform *pCharRoot = pActiveSceneLogic->get_CharRoot();
		int iCount = pCharRoot->get_childCount();
		if (iCount != 0) {
			int i = 0;
			for (i = 0; i < iCount; i++) {
				LOG_WRITE("Loop find NPC...........");
				CUE_Transform *pChild = pCharRoot->GetChild(i);
				CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Char");
				CObj_Char *pNPC = (CObj_Char *)pChild->GetComponent(pType);
				if (pNPC) {
					CStdStringU czNPCName = pNPC->get_RoleName();
					if (czNPCName.Find(czName) >= 0) {
						pChar = pNPC;
						return pChar;
					}
				}//pNpc
			} //endloop

			LOG_WRITE("..........END LIST NPC AROUND............OFF auto Fight");
		} 
	}
	return pChar;
	/*CUE_Transform *p = m_pUIRoot->GetChildByName(u"NameBoardRoot");
	if (p) {
		int iCount = p->get_childCount();
		if (iCount != 0) {
			for (int i = 0; i < iCount; i++) {
				CUE_Transform *pNPCHeadInfo = p->GetChild(i);
				CStdStringU czName = pNPCHeadInfo->GetName()->GetText();

				if (czName.Compare(u"NPCHeadInfo") == 0) {
					CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
					CNpcHeadInfoLogic* pHeadInfo = (CNpcHeadInfoLogic *)pNPCHeadInfo->GetComponent(pType);
					if (pHeadInfo) {
						CStdStringU czNameLabel = pHeadInfo->get_NameLabel();
						if (czNameLabel.Find(czName) >= 0) {
							LOG_WRITE("Yessssss....");
							return pHeadInfo->get_NPC();
						}
					}
				}
			}
		}
	}*/
	//return NULL;
}

CObj_Char	* CGameControl::getNPC( CUE_Transform *p, CStdString czObjName )
{
	if (!p) return NULL;
	CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj",czObjName);
	CObj_NPC *pChar = (CObj_NPC *)p->GetComponent(pType);
	if (!pChar) return NULL;
	return (CObj_Char *)pChar;
}

void CGameControl::LeaveTeam()
{
	CObj_MainPlayer *pObj_Player = get_MainPlayer();
	if (pObj_Player) {
		if (IsHasTeam()) {
			LOG_WRITE("Leave Cur Team.................");
			pObj_Player->LeaveTeamOk();
			return;
		}
	}
}

BOOL CGameControl::IsMemberSet()
{
	if (g_pGame->m_TeamOption.iTeamType != 2) return FALSE;
	return TRUE;
}

BOOL CGameControl::IsTeamLeader()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		BOOL bHaveTeam = pPlayerData->IsHaveTeam();
		if (!bHaveTeam) return FALSE;
		BOOL bIsLeader = pPlayerData->PlayerIsTeamLeader();
		//LOG_WRITE("teamOption .... %d", g_pGame->m_TeamOption.iTeamType);
		if (IsTeamAvailableSet() && bIsLeader) {
			//LOG_WRITE("IsTeamAvailableSet() && bIsLeader ........................");
			return TRUE;
		}
		else if (IsLeaderSet()) {
			LOG_WRITE("Is Leader.................");
			return TRUE;
		}
		else if (bIsLeader) return TRUE;
	}
	return FALSE;
}

void CGameControl::ShowLimitTips()
{
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) return;
	LOG_WRITE("CGameControl::ShowLimitTips().................");
	pInstance->OnCliskShowLimitTimePushActivityTips();
	_theApp->NextTimer(1000);
}

BOOL CGameControl::IsTeamAloneSet()
{
	if (g_pGame->m_TeamOption.iTeamType != 3) return FALSE;
	return TRUE;
}

void CGameControl::TeamWnd()
{
	CTeamPlatformWindow *pIns = CTeamPlatformWindow::Instance();
	if (pIns) {
		CSYS_List *pList = pIns->get_SubClassList();
		if (pList) {
			CJoinTeamSubItem *pCurItem = pIns->get_CurSelecItem();
			CStdStringU czSecondName = pCurItem->get_secondNameLabel();

			int iCount = pList->get_Count();
			if (iCount != 0) {
				for (int i = 0; i < iCount; i++) {
					CJoinTeamSubItem *pItem = (CJoinTeamSubItem*)pList->get_Item(i);
					CStdStringU czSecondNameItem = pItem->get_secondNameLabel();
					LOG_WRITE("[%s]", _U2A(czSecondNameItem).c_str());
					//if (czSecondNameItem.Find(czSecondNameItem))
				}
				
			}
		}
	}
}

void CGameControl::set_teamTarget( CStdStringU czName )
{
	CTeamPlatformWindow *pIns = CTeamPlatformWindow::Instance();
	if (pIns) {
		CSYS_List *pList = pIns->get_SubClassList();
		if (pList) {
			CJoinTeamSubItem *pCurItem = pIns->get_CurSelecItem();
			CStdStringU czSecondName = pCurItem->get_secondNameLabel();
			if (czSecondName.Compare(czName) == 0) {
				BOOL bAutoTeam = pCurItem->get_AutoTeam();
				if (!bAutoTeam) {
					LOG_WRITE("Auto Team...............................");
					pIns->OnAutoTeam();
					return;
				}
				LOG_WRITE("Right target.............");
				return;
			}

			int iCount = pList->get_Count();
			if (iCount != 0) {
				for (int i = 0; i < iCount; i++) {
					CJoinTeamSubItem *pItem = (CJoinTeamSubItem*)pList->get_Item(i);
					CStdStringU czSecondNameItem = pItem->get_secondNameLabel();
					if (czSecondNameItem.Find(czName) >= 0) {
						pItem->OnItemClick();
						LOG_WRITE("[%s]", _U2A(czSecondNameItem).c_str());
						return;
					}

					LOG_WRITE("[%s]", _U2A(czSecondNameItem).c_str());
				}



			}
		}
	}
}

BOOL CGameControl::IsConvoyConfirm()
{
	CGuildConvoyConfirm *pIns = CGuildConvoyConfirm::Instance();
	if (pIns) {
		LOG_WRITE("Yes.................................");
		pIns->OnClickYes();
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsItem_qbzroot()
{
	CUE_Transform *p = m_pPopUIRoot;
	if (!IsShowTransform(p)) return FALSE;
	CUE_Transform *pUI = p->GetChildByName(u"item.qbzroot");
	if (IsShowTransform(pUI)) {
		LOG_WRITE("Close.....");
		g_pGameControl->Clicked(pUI->GetChildByPath(u"Offset:Frame:btn_close"));
		//CloseDialog();
		return TRUE;
	}
	return FALSE;
}

void CGameControl::show_WorldMap()
{
	CWorldMapController::SceneMapOpenMap();
}

BOOL CGameControl::IsWorldMap(UINT &uParent)
{
	CUE_Transform *p = m_pPopUIRoot->GetChildByName(u"WorldMap");
	if (!IsShowTransform(p)) return FALSE;
	uParent = (UINT)p;
	return TRUE;
}

void CGameControl::skipTrailer()
{
	LOG_WRITE("skipTrailer().....");
	CSYS_List *pListUIRoot = CUIRoot::get_ListUIRoot();
	if (!pListUIRoot) return;
	LOG_WRITE("pListUIRoot..........");
	int iCount = pListUIRoot->get_Count();
	if (iCount == 0) {
		LOG_WRITE("uiRoot= NULL");
		return;
	}

	CUIRoot* pUIRoot = (CUIRoot*)pListUIRoot->get_Item(0);
	LOG_WRITE("uiRoot[%08X]", pUIRoot);
	if (!pUIRoot) return;
	LOG_WRITE("0");
	CUE_Transform *pTransform = pUIRoot->get_Trans();
	if (!pTransform) return;
	LOG_WRITE("1");
	CUE_Transform *pTrailer = pTransform->GetChildByName(u"LaunchLoadingWindow");
	if (IsShowTransform(pTrailer)) {
		LOG_WRITE("SKIP...........................");
		Tap(1,1);
		_theApp->NextTimer(2000);
		return;
	}
	LOG_WRITE("2");
}

int CGameControl::get_Level()
{
	int iLevel = 0;
	CObj_MainPlayer *pPlayer = get_MainPlayer();
	if (pPlayer) {
		iLevel = pPlayer->get_LastLevel();
	}
	return iLevel;
}

void CGameControl::OnClickButtonManaLack()
{
	if (!IsShowTransform(m_pBaseUIRoot)) return;
	CUE_Transform *p = m_pBaseUIRoot->GetChildByPath(u"ChatFrameRoot:Offset:ChatTop:Grid:exhausted_Reserve");
	if (!IsShowTransform(p)) return;
	LOG_WRITE("Clicked ManaLack on Screen............");
	Clicked(p);
	_theApp->NextTimer(1000);
}

BOOL CGameControl::IsRoleviewReserve()
{
	return FALSE;
}

void CGameControl::get_PositionWithEmulatorSize( CUE_Transform *p, int &x, int &y )
{
	if (!p) return;
	CUE_Vector3* v3 = p->get_position();
	float vX = (v3->GetX()/ m_othorgraphicSize);
	float vY = (v3->GetY()/ m_othorgraphicSize);
	float tempX = m_renderWidthHalf + ((vX * m_renderWidthHalf) / m_renderRate);
	float tempY = m_renderHeightHalf -(vY * m_renderHeightHalf);
	x = (int)tempX;
	y = (int)tempY;
}

CStdStringU CGameControl::get_NameMember( int iMember )
{
	CStdStringU czMemberName = u"No text";
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		BOOL bHaveTeam = pPlayerData->IsHaveTeam();
		if (bHaveTeam) {
			CTeamList *pIns = CTeamList::Instance();
			if (!pIns) {LOG_WRITE("CGameControl::get_NameMember( int iMember )..................."); OnTeamTabClick();}

			if (pIns) {
				CUE_Transform *pMember = NULL;
				if (iMember == 0) pMember = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem:Team01 (2)");
				if (iMember == 1) pMember = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem:Team01 (3)");
				if (iMember == 2) pMember = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem:Team01 (4)");
				if (iMember == 3) pMember = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem:Team01 (5)");
				if (iMember == 4) pMember = m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:TeamMem:Team01 (6)");
				if (!IsShowTransform(pMember)) { 
					OnTeamTabClick();
				}
				else {
					czMemberName = GetTextU(pMember->GetChildByPath(u"Main:name"));
				}
			}	
		}
	}
	return czMemberName;
}

int CGameControl::get_haveTeamCount()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return -1;
	CTeam *pTeam = pPlayerData->get_TeamInfo();
	if (!pTeam) return -1;
	return pTeam->GetTeamMemberCount();
}

BOOL CGameControl::IsNearPlayer( CStdStringU czNamePlayer )
{
	//CUE_Transform *p = g_pGameControl->m_pUIRoot->GetChildByName(u"NameBoardRoot");
	//if (g_pGameControl->IsShowTransform(p)) {
	//	int iCount = p->get_childCount();
	//	if (iCount != 0) {
	//		int i = 0;
	//		for (i = 0; i < iCount; i++) {
	//			CUE_Transform *pPlayerHeadInfo = p->GetChild(i);
	//			if (g_pGameControl->IsShowTransform(pPlayerHeadInfo)) {
	//				CStdStringU czName = pPlayerHeadInfo->GetName()->GetText();
	//				if (czName.Compare(u"PlayerHeadInfo") == 0) {
	//					CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","PlayerHeadInfoLogic");
	//					CPlayerHeadInfoLogic* pHeadInfo = (CPlayerHeadInfoLogic *)pPlayerHeadInfo->GetComponent(pType);
	//					if (pHeadInfo) {
	//						CStdStringU czNameLabel = pHeadInfo->get_NameLabel();
	//						if (czNameLabel.Find(czNamePlayer) >= 0) {
	//							//LOG_WRITE("czNameLabel = %s", _U2A(czNameLabel).c_str());
	//							return TRUE;
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
		
	CActiveSceneLogic *pActiveSceneLogic = CGameManager::get_CurActiveScene();
	if (pActiveSceneLogic) {
		CUE_Transform *pCharRoot = pActiveSceneLogic->get_CharRoot();
		//LOG_WRITE("pCharRoot == %08X", pCharRoot);
		int iCount = pCharRoot->get_childCount();
		if (iCount != 0) {
			for (int i = 0; i < iCount; i++) {
				LOG_WRITE("IsNearPlayer():: Loop find Leader.......");
				CUE_Transform *pChild = pCharRoot->GetChild(i);
				CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Player");
				CObj_Char *pChar = (CObj_Char *)pChild->GetComponent(pType);
				if (pChar) {
					CStdStringU czName = pChar->get_RoleName();
					if (czName.Find(czNamePlayer) >= 0) {
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

void CGameControl::AskTeamFollow()
{
	CTeamList *pIns = CTeamList::Instance();
	if (!pIns) {
		LOG_WRITE("CGameControl::AskTeamFollow()..........................");
		OnTeamTabClick();
		return;
	}
	LOG_WRITE("Call Follow Team............");
	pIns->OnFollow();
}

void CGameControl::OnTeamTabClick()
{
	LOG_WRITE("Show Tab Team");
	Clicked(m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:ButtonC:ZuDui"));
	_theApp->NextTimer(1000);
	return;
}

void CGameControl::ClickNPCInMaple( CStdStringU czNPCName )
{
	CSceneMapController *pIns = CSceneMapController::Instance();
	if (pIns) {
		CUE_Transform *p = g_pGameControl->get_Transform((UINT)pIns);
		CUE_Transform *pListNPC = p->GetChildByPath(u"Offset:Map_Popup_npclist:Offset:npc:Info:NpcGrid");
		if (!pListNPC) return;
		int iCount = pListNPC->get_childCount();
		if (iCount == 0) return;
		for (int i = 0; i < iCount; i++) {
			CUE_Transform *pNPC = pListNPC->GetChild(i);
			CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","AutoSearchPointLogic");
			CAutoSearchPointLogic* pAutoSearch = (CAutoSearchPointLogic *)pNPC->GetComponent(pType);
			if (pAutoSearch) {
				CStdStringU czNameNPC = pAutoSearch->get_LabelName();
				if (czNameNPC.Find(czNPCName) >= 0) {
					LOG_WRITE("Go to NPC.......................");
					pAutoSearch->OnTransmitPointClick();
					CloseDialog();
					return;
				}
			}
		}
	}
}

BOOL CGameControl::IsFollowLeader()
{
	if (IsMember()) {
		CTeamList *pIns = CTeamList::Instance();
		if (!pIns) return FALSE;
		CStdStringU czULabel = pIns->get_FollowLabel();
		
		if (czULabel.Compare(u"Bỏ theo") == 0) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameControl::IsSingleActivity()
{
	ActivityId iCurrentActivity = g_pGame->m_iCurrentActivity;
	if (iCurrentActivity == act_mainquest) return TRUE;
	if (iCurrentActivity == act_nvbang) return TRUE;
	if (iCurrentActivity == act_vandapngay) return TRUE;
	if (iCurrentActivity == act_kepgiaydoibietthu) return TRUE;
	if (iCurrentActivity == act_quyetdaudinhcao) return TRUE;
	if (iCurrentActivity == act_truthienphudo) return TRUE;
	if (iCurrentActivity == act_tangbaodo) return TRUE;
	if (iCurrentActivity == act_dangongcuong) return TRUE;
	if (iCurrentActivity == act_phutuyen) return TRUE;
	if (iCurrentActivity == act_soncocdatlinh) return TRUE;
	if (iCurrentActivity == act_hungvanquan) return TRUE;

	return FALSE;
}

CObj_Char * CGameControl::getPlayer( CStdStringU czName )
{
	CActiveSceneLogic *pActiveSceneLogic = CGameManager::get_CurActiveScene();
	if (pActiveSceneLogic) {
		CUE_Transform *pCharRoot = pActiveSceneLogic->get_CharRoot();
		//LOG_WRITE("pCharRoot == %08X", pCharRoot);
		int iCount = pCharRoot->get_childCount();
		if (iCount != 0) {
			for (int i = 0; i < iCount; i++) {
				CUE_Transform *pChild = pCharRoot->GetChild(i);
				CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Player");
				CObj_Char *pChar = (CObj_Char *)pChild->GetComponent(pType);
				CStdStringU czNamePlayer = pChar->get_RoleName();
				if (czNamePlayer.Find(czName) >= 0) {
					return pChar;
				}
			}
		}
	}
	return NULL;
}

CUE_Transform * CGameControl::get_CharRoot()
{
	CActiveSceneLogic *pActiveSceneLogic = CGameManager::get_CurActiveScene();
	if (!pActiveSceneLogic) return NULL;
	return pActiveSceneLogic->get_CharRoot();
}

CStdStringU CGameControl::get_NameMap()
{
	CRadarWindow *pInstance = CRadarWindow::Instance();
	if (!pInstance) return u"";
	CStdStringU czUName = pInstance->getSceneName();
	return czUName;
}

void CGameControl::CheckSilverBox()
{
	//if (!IsMap("Cứ Địa Bang")) {
	//	//LOG_WRITE("No Guild map....");
	//	return;
	//}

	CDeviceStatusWindow *pStatus = CDeviceStatusWindow::Instance();
	if (!pStatus) return;
	int iHour = pStatus->get_Hour();
	if (iHour != 20) return;

	int iScene = CGameManager::m_RunningScene();
	if (iScene != 1029) return;
	LOG_WRITE("Yes is map....");

	CObj_MainPlayer *pObj_Player = g_pGameControl->get_MainPlayer();
	CUE_Vector3 *pPlayerPosition = pObj_Player->get_Position();
	CActiveSceneLogic *pActiveSceneLogic = CGameManager::get_CurActiveScene();
	if (pActiveSceneLogic) {
		CUE_Transform *pCharRoot = pActiveSceneLogic->get_CharRoot();
		LOG_WRITE("[%08X]charRoot -- [%08X]player", pCharRoot, pObj_Player);
		int iCount = pCharRoot->get_childCount();
		if (iCount != 0) {			
			static int i = 0;
			for (i = 0; i < iCount; i++) {
				CUE_Transform *pChild = pCharRoot->GetChild(i);
				CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC");
				CObj_NPC *pNPC = (CObj_NPC *)pChild->GetComponent(pType);
				if (pNPC) {
					CObj_Char *pchar = (CObj_Char*)pNPC;

					CStdStringU czNameLabel = pchar->get_RoleName();
					if (czNameLabel.Find(u"Rương Bạc") >= 0) {
						LOG_WRITE("czNameLabel[%s]", _U2A(czNameLabel).c_str());
						pObj_Player->MoveToTarget(pchar);
						g_pAutoAI->GetGoalSystem()->AddSubGoal(new CGSleep(3000));
						return;
					}
					
				}
			}
		}
	}
}

BOOL CGameControl::IsShowTargetBar(CStdStringU czNameBoss)
{
	CUE_Transform *pTransform = NULL;
	CTargetFrameControllerNew *pIns = CTargetFrameControllerNew::Instance();
	if (!pIns) {
		LOG_WRITE("fight..............pIns == NULL");
		return FALSE;
	}
	CUE_Transform *pTargetFrameController = get_Transform((UINT)pIns);
	if (pTargetFrameController) {
		CUE_Transform *pMonster = pTargetFrameController->GetChildByPath(u"Offset:Monster&NpcBar");
		CUE_Transform *pBoss = pTargetFrameController->GetChildByPath(u"Offset:BossBar");

		if (IsShowTransform(pMonster)) {
			CUE_Transform *pPlayerIcon = pMonster->GetChildByPath(u"Self:MonsterHeadIcon:PlayerIcon");
			if (IsShowTransform(pPlayerIcon)) return FALSE;
			CUE_Transform *pNameMonsterTarget = pMonster->GetChildByPath(u"Self:lbl_MonsterName");
			CStdStringU czNameTarget = g_pGameControl->GetTextU(pNameMonsterTarget);
			if (czNameTarget.Find(czNameBoss) < 0) return FALSE; 
			LOG_WRITE("Is Have Show Target Bar.................");
			return TRUE;
		}
		if (IsShowTransform(pBoss)) {
			CUE_Transform *pPlayerIcon = pBoss->GetChildByPath(u"Self:MonsterHeadIcon:PlayerIcon");
			if (IsShowTransform(pPlayerIcon)) return FALSE;
			CUE_Transform *pNameBossTarget = pBoss->GetChildByPath(u"Self:lbl_MonsterName");
			CStdStringU czNameTarget = g_pGameControl->GetTextU(pNameBossTarget);
			if (czNameTarget.Find(czNameBoss) < 0) return FALSE; 
			LOG_WRITE("Is Have Show Target Bar.................");
			return TRUE;
		}
		//if (g_pGameControl->IsShowTransform(pTransform)) 
	}
	return FALSE;
}

BOOL CGameControl::IsHasTeam()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		BOOL bHaveTeam = pPlayerData->IsHaveTeam();
		if (!bHaveTeam) return FALSE;
		LOG_WRITE("Is Has team.................");
		return TRUE;
	}
	return FALSE;
}

void CGameControl::Test1()
{
	
}

BOOL CGameControl::get_WaitForLoadAllBlock()
{
	static int iSet_WaitForLoadAllBlock = 0;
	BOOL bget_WaitForLoadAllBlock = CGameManager::get_WaitForLoadAllBlock();
	if (!bget_WaitForLoadAllBlock) {
		iSet_WaitForLoadAllBlock = 0;
		return FALSE;
	}
	iSet_WaitForLoadAllBlock ++;
	if (iSet_WaitForLoadAllBlock >= 50) {
		LOG_WRITE("Too long.... set FALSE");
		iSet_WaitForLoadAllBlock = 0;
		CGameManager::set_WaitForLoadAllBlock();
	}
	LOG_WRITE("get_WaitForLoadAllBlock()......................%d",iSet_WaitForLoadAllBlock);
	_theApp->NextTimer(1000);
	return TRUE;
}

BOOL CGameControl::checkCanJoinActivity( ActivityId iActivityID, BOOL &bFinished )
{
	static int iDelayFinishActivity = 0;
	static int iCurActivityID = -5;

	if (iCurActivityID != (int)iActivityID) {
		LOG_WRITE("iCurActivityID != iActivityID");
		iCurActivityID = iActivityID;
		iDelayFinishActivity = 0;
		return TRUE;
	}

	int iActid = 0;
	if (iActivityID == act_thuongthienphatac)	iActid = 2004;
	if (iActivityID == act_nvbang)				iActid = 2002;//222;
	if (iActivityID == act_kepgiaydoibietthu)	iActid = 2010;
	if (iActivityID == act_soncocdatlinh)		iActid = 2014;
	if (iActivityID == act_phuongdegian)		iActid = 161;
	if (iActivityID == act_phuongminhcoc)		iActid = 15;
	if (iActivityID == act_trucdietaclinh)		iActid = 2006;
	if (iActivityID == act_vantieubang)			iActid = 2038;
	if (iActivityID == act_pbtuchan)			iActid = 2021;


	LOG_WRITE("can not join Activity delay... %d, iActid[%d]", iDelayFinishActivity, iActid);
	BOOL bIsCanJoin = CActivityHuoDongWindow::CheckIsCanJion(iActid);
	if (iDelayFinishActivity >= 5) {
		iDelayFinishActivity = 0;
		bFinished = TRUE;
		return TRUE;
	}
	if (bIsCanJoin) {
		iDelayFinishActivity = 0;
		//return FALSE;
	}

	if (!bIsCanJoin) {
		iDelayFinishActivity ++;
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsLeaderSet()
{
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_LEADER) return TRUE;
	return FALSE;
}

BOOL CGameControl::exitTeamIfAloneTeamSet()
{
	if (!IsTeamAloneSet()) return FALSE;
	BOOL bTeam = g_pGame->m_TeamOption.bAloneExitTeam;
	if (bTeam) {
		if (IsHasTeam()) {
			LOG_WRITE("bTeam.....................%d", bTeam);
			LeaveTeam();
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CGameControl::IsPVPResultWnd()
{
	CAsynPVPRewardLogic *pInstance = CAsynPVPRewardLogic::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("ChallengeAgain().......");
	pInstance->ChallengeAgain();
	return TRUE;
}

BOOL CGameControl::IsShowReliveWnd()
{
	CReliveController *pInstance = CReliveController::Instance();
	if (pInstance) {
		LOG_WRITE("CGameControl::IsReliveWnd()........................");
		//CReliveController::OnClickNearRelive();
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsTeamAvailableSet(BOOL bIsLeader)
{
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_INTELLIGENCE) {
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsNPC( CUE_Transform *p )
{
	if (!p) return FALSE;
	CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj");
	CObj *pNPC = (CObj *)p->GetComponent(pType);
	if (!pNPC) return FALSE;
	BOOL bIsNPC = pNPC->IsNpc();
	if (!bIsNPC) return FALSE;
	return TRUE;
}

CUE_Transform * CGameControl::get_NPCHeadInfoLogic( CUE_Transform *p)
{
	if (!p) return NULL;
	CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Char");
	CObj_Char *pNPC = (CObj_Char *)p->GetComponent(pType);
	if (!pNPC) return NULL;

	return (CUE_Transform*)pNPC->get_HeadInfoTran();

}

BOOL CGameControl::IsNotEnoughMembers()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return FALSE;
	BOOL bIsLeader = pPlayerData->PlayerIsTeamLeader();
	if (!bIsLeader) return FALSE;
	CTeam* pTeam = pPlayerData->get_TeamInfo();
	if (!pTeam) return FALSE;
	int iMemberCount = pTeam->GetTeamMemberCount();
	if (iMemberCount >= 3) return FALSE;
	LOG_WRITE("NOT Enoughed Member.................");
	return TRUE;
}

BOOL CGameControl::IsBagFull()
{
	int iEmptySize = -1;
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return FALSE;
	CItemPack *pItemPack = pPlayerData->get_BackPack();
	if (!pItemPack) return FALSE;
	iEmptySize = pItemPack->GetEmptySize();
	if (iEmptySize == -1) {
		LOG_WRITE("iEmptySize != pItemPack->GetEmptySize()");
		return FALSE;
	}

	if (iEmptySize > 2) return FALSE;

	LOG_WRITE("CGameControl::IsBagFull.....................%d", g_pGame->m_OptionTab.bTachTrangBiVang);
	return TRUE;
}	

BOOL CGameControl::IsFuliRedDot()
{
	if (IsShowPopUI()) return FALSE;
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	CUE_Transform *pRedDot = pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightUpButtons:1st_Grid:FuLi:RedDot");
	if (IsShowTransform(pRedDot)) {
		if (g_pGameControl->IsButtonExitFuben()) return FALSE;
		//LOG_WRITE(" CGameControl::IsFuliRedDot().......");
		return TRUE; 
	}
	return FALSE;
}

BOOL CGameControl::IsAchievementRedDot()
{
	if (IsShowPopUI()) return FALSE;
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	CUE_Transform *pRedDot = pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:RightBottom:No.2:Grid_01:ChengJiu:RedDot");
	if (IsShowTransform(pRedDot)) {
		LOG_WRITE("CGameControl::IsAchievementRedDot()..............");
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsNewMail()
{
	if (!IsShowTransform(m_pBaseUIRoot)) return FALSE;
	CUE_Transform *pChatFrame = m_pBaseUIRoot->GetChildByName(u"ChatFrameRoot");
	if (!IsShowTransform(pChatFrame)) return FALSE;
	CUE_Transform *pFriend = pChatFrame->GetChildByPath(u"Offset:Friend:GameObject");
	if (!IsShowTransform(pFriend)) return FALSE;
	CUE_Transform *pMail = pFriend->GetChildByName(u"Mail");
	if (!IsShowTransform(pMail)) {
		CUE_Transform *pMailMention = pChatFrame->GetChildByPath(u"Offset:Friend:MailMention");
		if (g_pGameControl->IsShowTransform(pMailMention)) {
			LOG_WRITE("Full Mail........");
			return TRUE;
		}
		return FALSE;
	}
		
	LOG_WRITE("New Mail....................");
	return TRUE;
}

void CGameControl::ShowSettingWnd()
{
	CFunctionButtonController *pIns = CFunctionButtonController::Instance();
	if (pIns) {
		pIns->OnNewClickSetting();
		_theApp->NextTimer(2000);
	}
}

BOOL CGameControl::IsMoving_Transform()
{
	if (!IsShowTransform(m_pBaseUIRoot)) return FALSE;
	CUE_Transform *pAuto = m_pBaseUIRoot->GetChildByName(u"Auto");
	if (!IsShowTransform(pAuto)) {
		LOG_WRITE("No transform....");
		return FALSE;
	}
	LOG_WRITE("CGameControl::IsMoving_Transform()..........");
	return TRUE;
}

void CGameControl::showAllActivity()
{
	CUE_Transform *pList = m_pPopUIRoot->GetChildByPath(u"activity.activity_frame:Offset:ActivityList_huodong(Clone):huodonglist:Offset:textlist:huodonglistPanel:Grid");
	if (!pList) return;
	int iCount  = pList->get_childCount();
	for (int i = 0; i < iCount; i++) {
		CUE_Transform *pChild = pList->GetChild(i);
		CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongItem");
		CActivityHuoDongItem *pChar = (CActivityHuoDongItem *)pChild->GetComponent(pType);
		CStdStringU czName = pChar->get_ActivityName();
		int iID = pChar->get_ActivityID();
		LOG_WRITE("ID - [%d] -- %s", iID, _U2A(czName).c_str());
		
	}
	LOG_WRITE("ENd.....................................");
}

void CGameControl::showAllNPC(BOOL bShowed)
{	
	//LOG_WRITE("bShowed = FALSE..............");
	//LOG_WRITE("bShowed = TRUE...............");
	//
	//static CObj_Char *pChar1 = NULL;

	//if (pChar1) {
	//	CStdStringU czName1 = pChar1->get_RoleName();
	//	BOOL IsDie = pChar1->IsDie();
	//	LOG_WRITE("[%08X].............%s[%d]", pChar1, _U2A(czName1).c_str(), IsDie);
	//	return;
	//}
	//CUE_Transform *pNameBoard = g_pGameControl->m_pUIRoot->GetChildByName(u"NameBoardRoot");
	//if (!g_pGameControl->IsShowTransform(pNameBoard)) return;
	//int iCount = pNameBoard->get_childCount();
	//if (iCount <= 1) return;

	//for (int i = 1; i < iCount; i++) {
	//	CUE_Transform *pName = pNameBoard->GetChild(i);
	//	if (pName->get_childCount() == 6 && g_pGameControl->IsShowTransform(pName)) {
	//		CUE_Transform *pNameNPC = pName->GetChildByPath(u"Offset:OriginalHeadInfo:NameLabel");
	//		if (pNameNPC) {
	//			CStdStringU czNameNPC = g_pGameControl->GetTextU(pNameNPC);
	//			if (czNameNPC.Find(u"Ác Linh" )>= 0) {
	//				CUE_Transform *pChatBubble = pName->GetChildByName(u"ChatBubble");
	//				if (pChatBubble) {
	//					CUE_Transform *pLabel = pChatBubble->GetChildByName(u"Label");
	//					CStdStringU czLabel = g_pGameControl->GetTextU(pLabel);
	//					if (g_pGameControl->IsShowTransform(pChatBubble)) {
	//						if (czLabel.Find(u"Arale") >= 0) {
	//							LOG_WRITE("Yessssssssssssssssssssssssssssss %08X", pName);

	//							CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic");
	//							CNpcHeadInfoLogic *pHead = (CNpcHeadInfoLogic *)pName->GetComponent(pType);
	//							if (pHead) pChar1 = pHead->get_NPC();
	//							return;
	//						}
	//					}

	//					if (!bShowed) {
	//						if (!g_pGameControl->IsShowTransform(pChatBubble)) {
	//							LOG_WRITE("NOOOOOOOOOOOOOOO %08X", pName);
	//						}

	//					}
	//					LOG_WRITE("Ac linh %08X", pName);

	//				} //pChatBubble

	//			} //aclinh
	//		}//pNameNPC
	//	} //la NPC
	//} //for 

	CObj_MainPlayer *pPlayer = get_MainPlayer();
	CActiveSceneLogic *pIns = CGameManager::get_CurActiveScene();
	if (!pIns) return;
	CUE_Transform *pCharRoot = pIns->get_CharRoot();
	LOG_WRITE("pIns[%08X], pCharRoot = %08X, Obj_MainPlayer[%08X]", pIns, pCharRoot, pPlayer);
	int iCount = pCharRoot->get_childCount();
	if (iCount == 0) return;
	for (int i = 0; i < iCount; i++) {
		CUE_Transform *pChild = pCharRoot->GetChild(i);
		int iChildCount = pChild->get_childCount();
		if (iChildCount != 0) {
			CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj");
			CObj *pChar = (CObj *)pChild->GetComponent(pType);
			CUE_Vector3 *pPos = pChar->get_Position();
			CObj_Char *pName = (CObj_Char *)pChar;
			CStdStringU czName = u"";
			if (pChar) {
				czName = pName->get_RoleName();
			}
			float x,y,z;
			x = pPos->GetX();
			y = pPos->GetY();
			z = pPos->GetZ();
			LOG_WRITE("Name : %s", _U2A(czName).c_str());
			LOG_WRITE("--->[%d][%08X][%d] -- Obj[%08X] -- Pos[%.2f, %.2f, %.2f]", i, pChild, iChildCount, pChar, x, y, z);
			LOG_WRITE("");
		}
	}
	LOG_WRITE("ENd........................");
}

BOOL CGameControl::IsEnableButton( CUE_Transform *p )
{
	if (!p) return FALSE;
	CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","UIButton");
	CUIButton *pBtn = (CUIButton *)p->GetComponent(pType);
	if (!pBtn) return FALSE;
	return pBtn->get_isEnabled();
}

void CGameControl::ReceivedBonusItem()
{
	CActivityHuoDongWindow *pIns = CActivityHuoDongWindow::Instance();
	if (!pIns) return;
	CUE_Transform *pWnd = g_pGameControl->get_Transform((UINT)pIns);
	if (pWnd) {
		CStdStringU czName = pWnd->GetName()->GetText();
		CUE_Transform *pGridBonusItem = pWnd->GetChildByPath(u"huodonglist:Offset:bottom:huoyuedu:Grid");
		if (pGridBonusItem) {
			
			int iCount = pGridBonusItem->get_childCount();
			if (iCount != 0) {
				for (int i = 0; i < iCount; i++) {
					CUE_Transform *pItem = pGridBonusItem->GetChild(i);
					if (pItem) {
						CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","ActivenessBonusItem");
						CActivenessBonusItem *pBonusItem = (CActivenessBonusItem *)pItem->GetComponent(pType);
						if (pBonusItem) {
							BOOL isCanGet = pBonusItem->get_IsCanReceived();
							if (isCanGet) {
								LOG_WRITE("Get..........................");
								pBonusItem->ClickItem();
								return;
							}
						}
					}
				}
			}
		}
	}
}

void CGameControl::FindNameASSEMBLY()
{

	CStdString czU = "ChannelListItem";

	LOG_WRITE("Search Begin [%s][%s]...",IMAGE_ASSEMBLY_CSHARP, czU.c_str());
	int count = 0;
	int loop = 0;
	CImage* pImage = g_pMono->GetImage(IMAGE_ASSEMBLY_CSHARP);
	if (!pImage) {
		LOG_WRITE("Result:%d loop:%d",count,loop);
		return;
	}

	CVList<CClass*> lstClass;
	pImage->EnumClasses(&lstClass);

	for(CVList<CClass*>::iterator it = lstClass.begin(); it != lstClass.end(); it++){
		CClass* pClass = *it;
		loop++;
		if(strcmp(pClass->GetName(), czU.c_str()) == 0){
			LOG_WRITE("[C][%s:%s]",pClass->GetNameSpace(), pClass->GetName());
			count++;


		}
		CVList<CField*> lstField;
		pClass->EnumFields(&lstField);

		for(CVList<CField*>::iterator itf = lstField.begin(); itf != lstField.end(); itf++){
			CField* pField = *itf;
			loop++;
			if(strstr(pField->GetType()->GetName(), czU.c_str()) != NULL){
				LOG_WRITE("[F][%s:%s][%s] type:[%s]",pClass->GetNameSpace(), pClass->GetName(), pField->GetName(),pField->GetType()->GetName());
				count++;	
			}

			if(strstr(pField->GetName(), czU.c_str()) != NULL){
				LOG_WRITE("[F][%s:%s][%s]",pClass->GetNameSpace(), pClass->GetName(), pField->GetName());
				count++;	
			}

		}

		
		CVList<CMethod*> lstMethods;
		pClass->EnumMethods(&lstMethods);
		for(CVList<CMethod*>::iterator itm = lstMethods.begin(); itm != lstMethods.end(); itm++){
			CMethod* pMethod = *itm;
			loop++;
			if(strstr(pMethod->GetReturnType(), czU.c_str()) != NULL){
				LOG_WRITE("[M][%s:%s][%s(%s)] return:[%s]",pClass->GetNameSpace(), pClass->GetName(), pMethod->GetName(),pMethod->GetArgs().c_str(),pMethod->GetReturnType());
				count++;	
			}
			if(pMethod->GetArgs().Find(czU.c_str()) >= 0){
				LOG_WRITE("[M][%s:%s][%s(%s)]",pClass->GetNameSpace(), pClass->GetName(), pMethod->GetName(),pMethod->GetArgs().c_str());
				count++;
			}
			if(strstr(pMethod->GetName(), czU.c_str()) != NULL){
				LOG_WRITE("[M][%s:%s][%s(%s)]",pClass->GetNameSpace(), pClass->GetName(), pMethod->GetName(),pMethod->GetArgs().c_str());
				count++;	
			}
		}
	}
	LOG_WRITE("Result:%d loop:%d",count,loop);
}

void CGameControl::TestTeam()
{
	CUE_Transform *pCharRoot = g_pGameControl->get_CharRoot();
	if (!g_pGameControl->IsShowTransform(pCharRoot)) return;
	int iCount = pCharRoot->get_childCount();
	if (iCount == 0) return;
	for (int i = 1; i < iCount; i++) {
		CUE_Transform *pChild = pCharRoot->GetChild(i);
		int iChildCount = pChild->get_childCount();

		if (iChildCount == 4) { //la NPC
			CObj_Char *pChar = g_pGameControl->getNPC(pChild);
			CObj *pObj = (CObj *)pChar;
			CObj_Char *pChar1 = (CObj_Char*)pObj;
			CStdStringU czName = pChar1->get_RoleName();
			if (pObj) {
				CUE_Vector3 *pVt3 = pObj->get_Position();
				float fx, fy, fz;
				fx = pVt3->GetX(); fy = pVt3->GetY(); fz = pVt3->GetZ();
				int x = (int)fx; int y = (int)fy; int z = (int)fz;
				LOG_WRITE("....................[%08X][%d,%d,%d][%s]", pChar, x, y, z, _U2A(czName).c_str());
			}
		}
	}
	LOG_WRITE("END LOOP......................NO NPC");
	/*CTeamList *pIns = CTeamList::Instance();
	if (!pIns) return;
	CSYS_Array *pArray = pIns->m_TeamMemberUI();
	if (!pArray) return;
	int iCount = pArray->get_Length();
	if (iCount == 0) return;
	for (int i = 0; i < iCount; i++) {
		CTeamMemberUIInfo *pMember = (CTeamMemberUIInfo*)pArray->GetValue(i);
		if (pMember) {
			BOOL bLight = pMember->GetCurSelLight();
			BOOL bButtonEnable = pMember->buttonEnable();
			BOOL bIsHalfShow = pMember->m_bIsHalfShow();

			LOG_WRITE("bLight%d bButtonEnable%d bIsHalfShow%d", bLight, bButtonEnable, bIsHalfShow);
		}
	}*/
}

CStdStringU CGameControl::get_NameMemberOnUIAuto(MEMBER *pMembers, int idx )
{
	CStdStringU czNameMemberOnAuto;
	if(pMembers[idx].czTeamName[0] !=0) {
		czNameMemberOnAuto = pMembers[idx].czTeamName;
	}
	return czNameMemberOnAuto;
}

void CGameControl::TestQuest()
{
	CMissionTrack *pIns = CMissionTrack::Instance();
	if (!pIns) return;
	CSYS_List *a = pIns->m_ChuanQiAceptedList();
	TestQuest1(a);
	CSYS_List *a1 = pIns->m_ChuanQiCompletedList();
	TestQuest1(a1);

	CSYS_List *b = pIns->m_BranchAceptedList();
	TestQuest1(b);
	CSYS_List *b1 = pIns->m_BranchCompletedList();
	TestQuest1(b1);

	CSYS_List *c = pIns->m_SurpriseAceptedList();
	TestQuest1(c);
	CSYS_List *c1 = pIns->m_SurpriseCompletedList();
	TestQuest1(c1);

	CSYS_List *d = pIns->m_CircleAceptedList();
	TestQuest1(d);
	CSYS_List *d1 = pIns->m_CircleCompletedList();
	TestQuest1(d1);

	CSYS_List *e = pIns->m_NewGuideAceptedList();
	TestQuest1(e);
	CSYS_List *e1 = pIns->m_NewGuideCompletedList();
	TestQuest1(e1);

	CSYS_List *f = pIns->m_QiYuAceptedList();
	TestQuest1(f);
	CSYS_List *f1 = pIns->m_QiYuCompletedList();
	TestQuest1(f1);

	CSYS_List *g = pIns->m_ApprenticeAcceptedList();
	TestQuest1(g);
	CSYS_List *g1 = pIns->m_ApprenticeCompletedList();
	TestQuest1(g1);

	
}

void CGameControl::TestQuest1( CSYS_List *pList )
{
	if (!pList) {
		LOG_WRITE("NO List"); 
		return;
	}

	int iCount = pList->get_Count();
	LOG_WRITE("[%08X]Count = [%d]", pList, iCount);

	if (iCount != 0) {
		for (int i = 0; i < iCount; i++) {
			CMissionItem *pItem = (CMissionItem *)pList->get_Item(i);
			CStdStringU czName = pItem->get_NameLabel();
			CStdStringU czType = pItem->get_TypeLabel();
			CStdStringU czCircle = pItem->get_CircleLabel();
			LOG_WRITE("%d [%s] -- [%s] -- [%s]", i, _U2A(czName).c_str(), _U2A(czType).c_str(), _U2A(czCircle).c_str());
		}
	}
}

void CGameControl::TestObjectArray()
{
	CImmortalityViewLogic *pIns = CImmortalityViewLogic::Instance();
	if (!pIns) return;
	
	CImmortalityActivityButton *pCurButton = pIns->m_CurSelectActivityButton();

	CSYS_Array *pArrParams = pIns->m_BottomnImmortalityButtons();
	if (pArrParams) {
		if (pArrParams) {
			int iCount = pArrParams->get_Length();
			for (int i = 0; i < iCount; i++) {
				CImmortalityActivityButton *pButton = (CImmortalityActivityButton *)pArrParams->GetValue(i);
				BOOL bIsActive = pButton->get_ImmortalityActivityActivate();
				BOOL bUnAcept = pButton->get_UnAcceptReward();
				//LOG_WRITE("[%d][%08X] => bIsActive[%d], bUnAcept[%d]", i, pButton, bIsActive, bUnAcept);
				if (bIsActive && bUnAcept) {
					if (pButton != pCurButton) {
						pButton->OnClickActivityButton();
						LOG_WRITE("[%d][%08X] => bIsActive[%d], bUnAcept[%d]", i, pButton, bIsActive, bUnAcept);
						return;
					}
					CSYS_List *pListButtonReceive = pIns->m_ResourceWayItemList();
					if (pListButtonReceive) {
						int iListItem = pListButtonReceive->get_Count();
						if (iListItem != 0) {
							for (int j = 0; j < iListItem; j++) {
								CImmortalityWayItem *pItem = (CImmortalityWayItem *)pListButtonReceive->get_Item(j);
								if (pItem) {
									CUE_GameObject *pAccecptObj = pItem->m_AccpetGameObject();
									if (pAccecptObj) {
										CUE_Transform *pRedTransform = pAccecptObj->get_transform();
										if (IsShowTransform(pRedTransform)) {
											//LOG_WRITE("[%d][%08X]Show", j, pRedTransform);
											LOG_WRITE("OnClickAcceptBtn................");
											pItem->OnClickAcceptBtn();
											_theApp->NextTimer(1000);
											return;
										}
									}
								}
							}
						}
					}
					LOG_WRITE("...........................");
					return;
				}
				
			}
		}
		
	}


}

BOOL CGameControl::IsImmortalRedot()
{
	CFunctionButtonController *pIns = CFunctionButtonController::Instance();
	if (pIns) {
		BOOL bIsRedot = pIns->IsNeedImmortaityRedDot();
		if (bIsRedot) return TRUE;
		return FALSE;
	}
	return FALSE;
}

void CGameControl::TestBag()
{
	CKnapsackWindow *pIns = CKnapsackWindow::Instance();
	if (!pIns) return;
	CSYS_List *pKnapsackList = pIns->filterItemList();
	if (!pKnapsackList) return;
	int iCount  = pKnapsackList->get_Count();
	if (iCount == 0) return;
	int i = 0;
	LOG_WRITE("level player : %d", get_Level());
	for (i = 0; i < iCount; i++) {
		CGameItem *pGameItem = (CGameItem *)pKnapsackList->get_Item(i);
		if (pGameItem) {
			CStdStringU czUName = pGameItem->GetName();
			CStdStringU czUClassName = pGameItem->GetTipsClassDesc();
			int iQuality = pGameItem->GetQuality();
			int iLevel = pGameItem->GetEquipLevel();

			LOG_WRITE("..............................");
			LOG_WRITE("[%d][%d] - Name: %s", i, iLevel, _U2A(czUName).c_str());
			LOG_WRITE("[%d][%d] - ClassName: %s", i, iLevel, _U2A(czUClassName).c_str());
		}
	}

	/*CSYS_List *pKnapsackList = pIns->get_KnapsackList();
	
	if (!pKnapsackList) return;
	int iCount  = pKnapsackList->get_Count();
	if (iCount == 0) return;
	int i = 0;
	LOG_WRITE("level player : %d", get_Level());
	for (i = 0; i < iCount; i++) {
		CKnapsackItem *pItem = (CKnapsackItem *)pKnapsackList->get_Item(i);
		if (pItem) {
			CGameItem *gameItem = pItem->GetGameItem();
			if (gameItem) {
				CUISprite *pUp = pItem->m_Up();
				CUISprite *pDisable = pItem->m_Disable();
				CStdStringU czNameUP = pUp->mSpriteName();
				CStdStringU czNameDisable = pDisable->mSpriteName();
				LOG_WRITE("...............................................");
				LOG_WRITE("%d - up[%08X] --  Disable[%08X]", i, pUp, pDisable);
				LOG_WRITE("%d - up[%s] -- [%s]Disable", i, _U2A(czNameUP).c_str(), _U2A(czNameDisable).c_str());

			}
		}
	}*/
}

void CGameControl::TestYLTX()
{	
	int x = 0;
	int y = 0;
	int x1 = 0;
	int y1 = 0;

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
						get_PositionWithEmulatorSize(pChild, x1, y1);
						LOG_WRITE("Player Position[%d, %d]", x1, y1);
					}

					//xuất hiện vị trí boss trên bản đồ
					/*if (czNameChild.Find(u"Map_icon_boss02(Clone)") >= 0) {
						g_pGameControl->get_PositionWithEmulatorSize(pChild, x, y);
						LOG_WRITE("[%d] -- [%d, %d]", i, x, y);
					}*/
				}
			}

			LOG_WRITE("END................................");
		}
	}
}

CStdStringU CGameControl::get_LineMap()
{
	CRadarWindow *pIns = CRadarWindow::Instance();
	if (!pIns) return u"";
	return pIns->labelLine();
}

void CGameControl::TestPatch()
{
	/*CRecoverySettingLogic *pIns = CRecoverySettingLogic::Instance();
	if (!pIns) return;
	CSYS_Array *pListMPFood = pIns->m_MPFoodList();
	if (!pListMPFood) return;
	int iCount = pListMPFood->get_Length();
	if (iCount == 0) return;
	for (int i = 0; i < iCount; i++) {
		CKnapsackItem *pItem = (CKnapsackItem *)pListMPFood->GetValue(i);
		if (pItem) {
			int iDataId = pItem->GetDataId();
			CGameItem *pGameItem = pItem->GetGameItem();
			CStdStringU czName;
			if (pGameItem) {
				czName = pGameItem->GetName();
			}
			LOG_WRITE("[%08X]iDataId == %d, [%s]", pItem, iDataId, _U2A(czName).c_str());
		}
	}
	LOG_WRITE("..............");*/
	CStdStringU czName = u"Cháo Lươn";

	CSystemShopWindow *pIns = CSystemShopWindow::Instance();
	if (pIns) {
		CStdStringU czCurNameItemSelected = pIns->LabelItemName();
		if (czCurNameItemSelected.Find(czName) >= 0) {
			LOG_WRITE("Item is Selected...");
			return;
		}

		CSystemShopWindow *pCurPage = pIns->m_curShowPage();
		if (pCurPage) {
			CUE_Transform *pTransformCurPage = get_Transform((UINT)pCurPage);
			if (pTransformCurPage) {
				int iCount = pTransformCurPage->get_childCount();
				for (int i = 0; i < iCount; i++) {
					CUE_Transform *pItem = pTransformCurPage->GetChild(i);
					if (IsShowTransform(pItem)) {
						CUE_Transform *pNameItem = pItem->GetChildByPath(u"Offset:LabelFram:BackGround:Name");
						CStdStringU czNameItem = GetTextU(pNameItem);
						if (czNameItem.Find(czName) >= 0) {
							LOG_WRITE("Clicked Item .....");
							Clicked(pItem);
							return;
						}
					}
				}
			}
		}
	}
}

BOOL CGameControl::IsShowTransformKnapsack()
{
	CKnapsackController *pController = CKnapsackController::Instance();
	if (!pController) return FALSE;
	CUE_Transform *pTrans = g_pGameControl->get_Transform((UINT)pController);
	if (!g_pGameControl->IsShowTransform(pTrans)) return FALSE;
	return TRUE;
}

BOOL CGameControl::IsShowFuliWnd()
{
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pWnd = pPopUIRoot->GetChildByName(u"welfare.welfareframe");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			if (!g_pGame->m_OptionTab.bFuli) {
				CloseDialog();
				return TRUE;
			}
			
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameControl::IsAchievementWnd()
{
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pWnd = pPopUIRoot->GetChildByName(u"ChengJiuRoot");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			if (!g_pGame->m_OptionTab.bAchievement) {
				CloseDialog();
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}	

void CGameControl::ShowFuliWnd()
{
	if (IsStoryUIRoot()) return;
	if (IsShowPopUI()) return;
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) {return; }
	LOG_WRITE("CGTaskFuli::ShowFuliWnd()....");
	pInstance->OnFuLiClick();
	_theApp->NextTimer(1000);
}

void CGameControl::ShowTaskAchievementWnd()
{
	if (IsStoryUIRoot()) return;
	if (IsShowPopUI()) return;
	CFunctionButtonController *pInstance = CFunctionButtonController::Instance();
	if (!pInstance) {return; }
	LOG_WRITE("CGTaskFuli::ShowTaskAchievementWnd()....");
	pInstance->OnClickAchievement();
	_theApp->NextTimer(1000);
}

BOOL CGameControl::IsNoticeWnd()
{
	CUE_Transform *pNotice = g_pGameControl->m_pMessageUIRoot->GetChildByName(u"notice.noticeroot");
	if(g_pGameControl->IsShowTransform(pNotice)){
		
		return TRUE;
	}
	return FALSE;
}

BOOL CGameControl::IsHaveGuild()
{
	if (!m_pPlayerData) {
		LOG_WRITE("No m_pPlayerData");
		return FALSE;
	}
	CGuild *pGuild = m_pPlayerData->GuildInfo();

	if (!pGuild) {
		LOG_WRITE("No pGuild");
		return FALSE;
	}

	int guildSceneID = pGuild->get_GuildSceneID();
	if (guildSceneID == 0) {
		LOG_WRITE("No guildSceneID");
		return FALSE;
	}
	return TRUE;
}

void CGameControl::TestTimeYLTX()
{
	static int iArray[5] = {0, 0, 4, 0, 6};
	for (int i = 0; i < 5; i++) {
		if (iArray[i] == 0 && iArray[i+1] == 0) {
			iArray[i] = 2;
			break;
		}
	}

	static int j = 0;
	for (j = 0; j < 15; j++) {
		if (j != iArray[1] && j != iArray[2] && j != iArray[3] && j != iArray[4] && j != iArray[0]) {
			LOG_WRITE("j duoc duyet %d", j);
		}
	}



}

void CGameControl::ChangeScene( int sceneId )
{

	//id: 34 -> ngoai thanh to long
	//id: 4 -> ho thong thien
	//id: 92-> ben tam mong

	CWorldMapController *pInstance = CWorldMapController::Instance();
	if (!pInstance) {
		if (IsShowPopUI()) {
			CloseDialog();
			return;
		}
		LOG_WRITE("Show World Map.......");
		CWorldMapController::SceneMapOpenMap();
		_theApp->NextTimer(2000);
		return;
	}

	CSYS_List *pListMap = pInstance->m_SmallMapItemList();

	if (!pListMap) return;
	int iCount = pListMap->get_Count();
	if (iCount <= 0) return;

	for (int i = 0; i < iCount; i++) {
		CSmallMapItem *pItem = (CSmallMapItem *)pListMap->get_Item(i);
		if (pItem) {
			int iSceneID = pItem->m_nSceneId();
			if (iSceneID == sceneId) {
				LOG_WRITE("Teleport to %d", iSceneID);
				pInstance->OnMapItemBtnClick(pItem);
			}
			//LOG_WRITE("[%d] -> [%08X] --> sceneId[%d]", i, pItem, iSceneID);
		}
	}


}

int CGameControl::getPos( int iPos )
{
	int Pos = 0;
	CObj_MainPlayer *pPlayer = get_MainPlayer();
	if (!pPlayer) return 0;
	CObj  *pObj = (CObj *)pPlayer;
	CUE_Vector3 *pVt3 = pObj->get_Position();
	if (iPos == 0) iPos = (int)pVt3->GetX();
	if (iPos == 1) iPos = (int)pVt3->GetY();
	if (iPos == 2) iPos = (int)pVt3->GetZ();
	return iPos;
}

int CGameControl::getCurrentLine()
{
	/*CStdStringU czLineMap = get_LineMap();
	if (czLineMap.Compare(u"Kenh [1]") == 0) return 1;
	if (czLineMap.Compare(u"Kenh [2]") == 0) return 2;
	if (czLineMap.Compare(u"Kenh [3]") == 0) return 3;
	if (czLineMap.Compare(u"Kenh [4]") == 0) return 4;
	if (czLineMap.Compare(u"Kenh [5]") == 0) return 5;
	if (czLineMap.Compare(u"Kenh [6]") == 0) return 6;
	if (czLineMap.Compare(u"Kenh [7]") == 0) return 7;
	if (czLineMap.Compare(u"Kenh [8]") == 0) return 8;
	if (czLineMap.Compare(u"Kenh [9]") == 0) return 9;
	if (czLineMap.Compare(u"Kenh [10]") == 0) return 10;
	if (czLineMap.Compare(u"Kenh [11]") == 0) return 11;
	if (czLineMap.Compare(u"Kenh [12]") == 0) return 12;
	if (czLineMap.Compare(u"Kenh [13]") == 0) return 13;
	if (czLineMap.Compare(u"Kenh [14]") == 0) return 14;
	if (czLineMap.Compare(u"Kenh [15]") == 0) return 15;
	if (czLineMap.Compare(u"Kenh [16]") == 0) return 16;
	if (czLineMap.Compare(u"Kenh [17]") == 0) return 17;
	if (czLineMap.Compare(u"Kenh [18]") == 0) return 18;
	if (czLineMap.Compare(u"Kenh [19]") == 0) return 19;
	if (czLineMap.Compare(u"Kenh [20]") == 0) return 20;
	if (czLineMap.Compare(u"Kenh [21]") == 0) return 21;
	if (czLineMap.Compare(u"Kenh [22]") == 0) return 22;
	if (czLineMap.Compare(u"Kenh [23]") == 0) return 23;
	if (czLineMap.Compare(u"Kenh [24]") == 0) return 24;
	if (czLineMap.Compare(u"Kenh [25]") == 0) return 25;
	if (czLineMap.Compare(u"Kenh [26]") == 0) return 26;
	if (czLineMap.Compare(u"Kenh [27]") == 0) return 27;
	if (czLineMap.Compare(u"Kenh [28]") == 0) return 28;
	if (czLineMap.Compare(u"Kenh [29]") == 0) return 29;
	if (czLineMap.Compare(u"Kenh [30]") == 0) return 30;*/
	return 0;
}

CStdStringU CGameControl::getCurrentNameLine()
{
	CStdStringU czLineMap = get_LineMap();
	if (czLineMap.Compare(u"1") == 0) return u"Kênh 1";
	if (czLineMap.Compare(u"2") == 0) return u"Kênh 2";
	if (czLineMap.Compare(u"3") == 0) return u"Kênh 3";
	if (czLineMap.Compare(u"4") == 0) return u"Kênh 4";
	if (czLineMap.Compare(u"5") == 0) return u"Kênh 5";
	if (czLineMap.Compare(u"6") == 0) return u"Kênh 6";
	if (czLineMap.Compare(u"7") == 0) return u"Kênh 7";
	if (czLineMap.Compare(u"8") == 0) return u"Kênh 8";
	if (czLineMap.Compare(u"9") == 0) return u"Kênh 9";
	if (czLineMap.Compare(u"10") == 0) return u"Kênh 10";
	if (czLineMap.Compare(u"11") == 0) return u"Kênh 11";
	if (czLineMap.Compare(u"12") == 0) return u"Kênh 12";
	if (czLineMap.Compare(u"13") == 0) return u"Kênh 13";
	if (czLineMap.Compare(u"14") == 0) return u"Kênh 14";
	if (czLineMap.Compare(u"15") == 0) return u"Kênh 15";
	if (czLineMap.Compare(u"16") == 0) return u"Kênh 16";
	if (czLineMap.Compare(u"17") == 0) return u"Kênh 17";
	if (czLineMap.Compare(u"18") == 0) return u"Kênh 18";
	if (czLineMap.Compare(u"19") == 0) return u"Kênh 19";
	if (czLineMap.Compare(u"20") == 0) return u"Kênh 20";
	if (czLineMap.Compare(u"21") == 0) return u"Kênh 21";
	if (czLineMap.Compare(u"22") == 0) return u"Kênh 22";
	if (czLineMap.Compare(u"23") == 0) return u"Kênh 23";
	if (czLineMap.Compare(u"24") == 0) return u"Kênh 24";
	if (czLineMap.Compare(u"25") == 0) return u"Kênh 25";
	if (czLineMap.Compare(u"26") == 0) return u"Kênh 26";
	if (czLineMap.Compare(u"27") == 0) return u"Kênh 27";
	if (czLineMap.Compare(u"28") == 0) return u"Kênh 28";
	if (czLineMap.Compare(u"29") == 0) return u"Kênh 29";
	if (czLineMap.Compare(u"30") == 0) return u"Kênh 30";
	return "error";
}

CSYS_List * CGameControl::get_BrotherhoodList()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return NULL;
	CBrotherhood *pBrotherhood = pPlayerData->get_BrotherhoodInfo();
	if (!pBrotherhood) return NULL;
	return (CSYS_List*)pBrotherhood->m_BrotherhoodMemberList();
}

CSYS_List * CGameControl::get_FriendsList()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return NULL;
	//LOG_WRITE("pPlayerData %08X", pPlayerData);
	CRelationList *pFriendList = pPlayerData->get_FriendList();
	if (!pFriendList) return NULL;
	//LOG_WRITE("pFriendList %08X", pFriendList);
	return (CSYS_List *)pFriendList->get_sortedList();
}

BOOL CGameControl::IsMemberInTeam( CStdStringU czName )
{
	
}


void CGameControl::ReqJoinTeam( CStdStringU czNameLeader )
{
	if (czNameLeader.Compare(u"") != 0) {
		CObj_MainPlayer *pPlayer = CObjManager::get_MainPlayer();

		CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
		if (!pPlayerData) return;
		LOG_WRITE("pPlayerData %08X", pPlayerData);
		CRelationList *pFriendList = pPlayerData->get_FriendList();
		if (!pFriendList) return;
		LOG_WRITE("pFriendList %08X", pFriendList);
		CSYS_List *pRelationList = pFriendList->get_sortedList();
		if (!pRelationList) return;
		LOG_WRITE("pRelationList %08X", pRelationList);
		int iCount = pRelationList->get_Count();
		if (iCount != 0) {

			int i = 0;
			for(i = 0; i < iCount; i++) {
				CRelation * pRelation = (CRelation *)pRelationList->get_Item(i);
				CStdStringU czName = pRelation->get_Name();
				ULONGLONG uGuid = pRelation->get_Guid();
				if (czName.Compare(czNameLeader) == 0) {
					LOG_WRITE("ReqJoinTeam of [%s] ", _U2A(czNameLeader).c_str());
					pPlayer->ReqJoinTeam(uGuid);
					return;
					
				}
			}
		}
	}// czNameLeader.Compare(u"") != 0
}

BOOL CGameControl::processIfReqJoinTeam()
{
	CStdStringU czMember1 = get_NameMemberOnUIAuto(g_pGame->m_Members, 1);
	CStdStringU czMember2 = get_NameMemberOnUIAuto(g_pGame->m_Members, 2);
	CStdStringU czMember3 = get_NameMemberOnUIAuto(g_pGame->m_Members, 3);
	CStdStringU czMember4 = get_NameMemberOnUIAuto(g_pGame->m_Members, 4);
	CStdStringU czMember5 = get_NameMemberOnUIAuto(g_pGame->m_Members, 5);
	CUE_Transform *p = m_pMessageUIRoot;
	if ( IsShowTransform(p)) {
		CUE_Transform *pMsgBox = p->GetChildByName(u"messageboxroot");
		if (IsShowTransform(pMsgBox)) {
			CUE_Transform *pContent = pMsgBox->GetChildByPath(u"Offset:Sprite:Content");
			CStdStringU czUContent = GetTextU(pContent);
			if (czUContent.Compare(czMember1) == 0) {
				LOG_WRITE("OK MessageBox");
				Clicked(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:03OKButton"));
				return TRUE;
			}
			if (czUContent.Compare(czMember2) == 0) {
				LOG_WRITE("OK MessageBox");
				Clicked(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:03OKButton"));
				return TRUE;
			}
			if (czUContent.Compare(czMember3) == 0) {
				LOG_WRITE("OK MessageBox");
				Clicked(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:03OKButton"));
				return TRUE;
			}
			if (czUContent.Compare(czMember4) == 0) {
				LOG_WRITE("OK MessageBox");
				Clicked(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:03OKButton"));
				return TRUE;
			}
			if (czUContent.Compare(czMember5) == 0) {
				LOG_WRITE("OK MessageBox");
				Clicked(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:03OKButton"));
				return TRUE;
			}
		}
	}
	

	CUE_Transform *pJoinMyTeam = m_pPopUIRoot->GetChildByPath(u"TeamRoot:Offset:JoinMyTeam");
	if (IsShowTransform(pJoinMyTeam)) {
		CUE_Transform *pList = pJoinMyTeam->GetChildByName(u"List Of Team Member:ScrollView:Grid");
		int iCount = pList->get_childCount();
		if (iCount != 0) {
			for (int i = 0; i < iCount; i++) {
				CUE_Transform *piTem = pList->GetChild(i);
				if (IsShowTransform(piTem)) {
					CUE_Transform* pMem = piTem->GetChildByPath(u"Panel:Label");
					CStdStringU czMem = GetTextU(pMem);
					if (czMem.Compare(czMember1) == 0) {
						LOG_WRITE("Accept %s", _U2A(czMem).c_str());
						Clicked(pMem->GetChildByPath(u"Panel:Button05"));
						return TRUE;
					}
					if (czMem.Compare(czMember2) == 0) {
						LOG_WRITE("Accept %s", _U2A(czMem).c_str());
						Clicked(pMem->GetChildByPath(u"Panel:Button05"));
						return TRUE;
					}
					if (czMem.Compare(czMember3) == 0) {
						LOG_WRITE("Accept %s", _U2A(czMem).c_str());
						Clicked(pMem->GetChildByPath(u"Panel:Button05"));
						return TRUE;
					}
					if (czMem.Compare(czMember4) == 0) {
						LOG_WRITE("Accept %s", _U2A(czMem).c_str());
						Clicked(pMem->GetChildByPath(u"Panel:Button05"));
						return TRUE;
					}
					if (czMem.Compare(czMember5) == 0) {
						LOG_WRITE("Accept %s", _U2A(czMem).c_str());
						Clicked(pMem->GetChildByPath(u"Panel:Button05"));
						return TRUE;
					}
				}
			}
		}
		return TRUE;
	}

	if(CTeamList::Instance() == 0) {
		g_pGameControl->OnTeamTabClick();
		return TRUE;
	}
	
	if (!IsShowTransform(m_pBaseUIRoot)) return FALSE;

	CUE_Transform *pTeamList =  m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:TeamList");
	if (!IsShowTransform(pTeamList)) {
		SwitchTeamTab();
		return TRUE;
	}

	if (IsShowTransform(pTeamList)) {
		CUE_Transform *pList = pTeamList->GetChildByPath(u"Real:TeamMem");
		int iCount = pList->get_childCount();
		if (iCount == 0) return FALSE;
		for (int i = 1; i < iCount; i ++) {
			CUE_Transform *pMem = pList->GetChild(i);
			if (IsShowTransform(pMem)) {
				CUE_Transform *pEmpty = pMem->GetChildByName(u"Empty");
				if (IsShowTransform(pEmpty)) {
					CUE_Transform *pCheck = pEmpty->GetChildByName(u"check");
					if (IsShowTransform(pCheck)) {
						LOG_WRITE("Clicked Check..");
						Clicked(pEmpty->GetChildByName(u"check"));
						return TRUE;
					}
				}
			}
		}
	}
}

void CGameControl::CloseTeamWnd()
{
	CTeamController *pTeamCtrl = CTeamController::Instance();
	if (pTeamCtrl) {
		LOG_WRITE("Close Team");
		pTeamCtrl->OnClose();
	}
}

void CGameControl::ClosePopManyChar()
{
	CPopManyCharMenu *pIns = CPopManyCharMenu::Instance();
	if (pIns) {
		LOG_WRITE("Close PopManyChar()");
		pIns->CloseWindow();
	}
}

BOOL CGameControl::ButtonCloseIsShow( CUE_Transform *p )
{
	if (!p ) return FALSE;
	CUE_Transform *pClose = p->GetChildByName(u"CloseButton");
	CUE_Transform *pClose4 = p->GetChildByName(u"Map_btn_close");
	CUE_Transform *pClose1 = p->GetChildByName(u"btn_close");
	CUE_Transform *pClose2 = p->GetChildByName(u"Close");
	CUE_Transform *pClose3 = p->GetChildByName(u"close");
	CUE_Transform *pClose5 = p->GetChildByName(u"Btn_Close");
	CUE_Transform *pClose6 = p->GetChildByName(u"btn_Close");
	CUE_Transform *pClose7	 = p->GetChildByName(u"CloseBtn");
	LOG_WRITE("Close Dialog With Button TRansform");
	if (IsShowTransform(pClose4)) Tap(pClose4->GetChildByName(u"Sprite"));
	if (IsShowTransform(pClose)) Clicked(pClose);
	if (IsShowTransform(pClose1)) Clicked(pClose1);
	if (IsShowTransform(pClose2)) Clicked(pClose2);
	if (IsShowTransform(pClose3)) Clicked(pClose3);
	if (IsShowTransform(pClose5)) Clicked(pClose5);
	if (IsShowTransform(pClose6)) Clicked(pClose6);
	if (IsShowTransform(pClose7)) Clicked(pClose7);
	_theApp->NextTimer(1000);
	return TRUE;
}

void CGameControl::OnOffSettingWnd()
{
	BOOL bOn = g_pGame->m_OptionTab.bOptimizeCPUAct;
	CSettingController *pIns = CSettingController::Instance();
	if (bOn) {
		ShowSettingWnd();
		return;
	}

	if (!bOn) {
		if (pIns) pIns->OnCloseClick();
	}
}

void CGameControl::MoveToTarget( CObj_Char *pChar )
{
	CObj_MainPlayer *p = CObjManager::get_MainPlayer();
	if (p) p->MoveToTarget(pChar);
}

CStdStringU CGameControl::getNameMember(CTeam* pTeam, int iMember )
{
	CTeamMember *pMember = pTeam->GetTeamMember(iMember);
	if (!pMember) return u"No Member";
	return pMember->get_MemberName();
}

void CGameControl::SetCurrentID( int iIdSet )
{
	if (iIdSet != g_pGame->m_iCurrentID ) {
		g_pGame->m_iCurrentID = iIdSet;
	}
}

int CGameControl::getTime( int iTypeTime )
{
	CDeviceStatusWindow *pStatus = CDeviceStatusWindow::Instance();
	if (!pStatus) return -5;
	if (iTypeTime == 0) return pStatus->get_Hour();
	if (iTypeTime == 1) return pStatus->get_Minute();
	return -5;
}

void CGameControl::ShowListNPC()
{
	CUE_Transform *pCharRoot = g_pGameControl->get_CharRoot();
	if (!g_pGameControl->IsShowTransform(pCharRoot)) return;
	int iCount = pCharRoot->get_childCount();
	if (iCount == 0) return;
	for (int i = 1; i < iCount; i++) {
		CUE_Transform *pChild = pCharRoot->GetChild(i);
		int iChildCount = pChild->get_childCount();

		CObj_Char *pChar = g_pGameControl->getNPC(pChild);
		CObj *pObj = (CObj *)pChar;
		CObj_Char *pChar1 = (CObj_Char*)pObj;
		CStdStringU czName = pChar1->get_RoleName();
		LOG_WRITE("%d - [%d]:%s", i, iChildCount, _U2A(czName).c_str());
		LOG_WRITE("....................................");
	}
			
}

BOOL CGameControl::IsFullTeam()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		CTeam *pTeam = pPlayerData->get_TeamInfo();
		if (pTeam) {
			BOOL bIsFullTeam = pTeam->IsFull();
			return bIsFullTeam;
		}
	}
	return FALSE;
}



void CGameControl::ClickTab( CUE_Transform *p )
{
	if (!p) return;
	CSYS_Type* pType = g_pMono->GetSysType(IMAGE_ASSEMBLY_CSHARP,"","TabButton");
	CTabButton* pTab = (CTabButton *)p->GetComponent(pType);
	if (pTab){
		LOG_WRITE("==> UIButton OnClick(%s)",U2A(p->GetPath().c_str()).c_str());
		pTab->OnTabClick();
	}
}
