#include "main.h"
#include "GLoginServerChoose.h"

CGLoginServerChoose::CGLoginServerChoose() :CGActivity()
{
	LOG_WRITE("NEW - CGLoginServerChoose()");
	m_activity = (ActivityId)goal_UILoginServer;
	//g_pNetwork->Sync_StatusLogin(TRUE);
}

CGLoginServerChoose::~CGLoginServerChoose()
{
	LOG_WRITE("DEL - CGLoginServerChoose()");
}

int CGLoginServerChoose::Process()
{
 	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGLoginServerChoose::Process()....");

		CUE_Transform *pServerChoose = g_pGameControl->m_pUIRoot->GetChildByName(u"login.serverchoosewindow");
		if(!g_pGameControl->IsShowTransform(pServerChoose))	return Finished();
		
		if(CloseNotice()) return LoopNextSleep();
		
		if(IsWrongAccount(pServerChoose)) return LoopNextSleep();

		if(ChooseServer(pServerChoose)) return LoopNextSleep(500);
		
		if(EnterGame(pServerChoose)) return LoopNextSleep();
		
		return LoopNextSleep(1000);

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}
BOOL CGLoginServerChoose::IsWrongAccount(CUE_Transform *pServerChoose){
	if(!pServerChoose) return FALSE;
	ACCOUNT_INFO* pAccount = &g_pGame->m_accountInfo;
	if(pAccount->czUsername[0] == 0){
		g_pGameControl->UpdateAccountInfo();
		return TRUE;
	}

	if(strcmp(g_pGame->m_publisherAccount.czUsername, "No Account") == 0){
		LOG_WRITE("NO ACCOUNT:[%s]",pAccount->czUsername);
		return FALSE;
	}

	if(strcmp(g_pGame->m_publisherAccount.czUsername, "") == 0){
		LOG_WRITE("NO ACCOUNT1:[%s]",pAccount->czUsername);
		return FALSE;
	}

	if(strcmp(pAccount->czUsername, g_pGame->m_publisherAccount.czUsername) == 0){
		LOG_WRITE("RIGHT ACCOUNT:[%s]",pAccount->czUsername);
		return FALSE;
	}
	
	LOG_WRITE("g_pGame->m_publisherAccount.czUsername.....[%s]", g_pGame->m_publisherAccount.czUsername);
	if(strcmp(g_pGame->m_publisherAccount.czUsername, "") == 0) {
		LOG_WRITE("NO ACOUNT.......................[%s]", g_pGame->m_publisherAccount.czUsername);
		g_pGameControl->Tap(pServerChoose->GetChildByPath(u"Panel:FirstWindow:EnterGame"));
		return TRUE;
	}

	LOG_WRITE("Wrong ACCOUNT:[%s], [%s]",pAccount->czUsername, g_pGame->m_publisherAccount.czUsername);
	g_pGameControl->Tap(pServerChoose->GetChildByPath(u"Panel:FirstWindow:TopLeft:Offset:MSDK_Account:zhanghao"));
	//CServerChooseWindow::OnClickChangeAccount()
	return TRUE;
}
BOOL CGLoginServerChoose::EnterGame(CUE_Transform *pServerChoose){
	CServerChooseWindow *pWindow =  CServerChooseWindow::Instance();
	if(!pWindow) return FALSE;

	if(strcmp(g_pGame->m_publisherAccount.czUsername, "No Account") == 0) {
		LOG_WRITE("NO ACCOUNT and NOT CHECK SERVER ---> ENTER GAME");

		g_pGameControl->Tap(pServerChoose->GetChildByPath(u"Panel:FirstWindow:EnterGame"));
		return LoopNextSleep();
	}

	CStdString czServerId = pWindow->GetSelServerID();
	CStdString czServerLogin; 
	int iServerLogin = g_pGame->m_roleLogin.iServer;
	czServerLogin.Fmt("%dS", iServerLogin);
	LOG_WRITE("Compare SeverId [%s][%s]",czServerId.c_str(), czServerLogin.c_str());
	//LOG_WRITE("%d get_curSelectServer", pWindow->get_curSelectServer());
	if(czServerId.Compare(czServerLogin.c_str()) == 0){
		//pWindow->OnClickEnterGame();
		CUIToggle *pToggle = pWindow->get_PrivacyToggle();
		if (!pToggle) return FALSE;
		BOOL bCheck = pToggle->get_isChecked();
		if (!bCheck) {
			LOG_WRITE("Check Privacy................");
			g_pGameControl->Tap(pServerChoose->GetChildByPath(u"Panel:FirstWindow:privacy:privacytoggle"));
			return TRUE;
		}

		LOG_WRITE("Enter Game.................... %d", bCheck);
		g_pGameControl->Tap(pServerChoose->GetChildByPath(u"Panel:FirstWindow:EnterGame"));
		return LoopNextSleep();
	}
	else {
		pWindow->OnClickChooseServer();
		return LoopNextSleep();
	}
	/*
		CStdString czServerId = g_pGameControl->GetTextA(pServerChoose->GetChildByPath(u"Panel:FirstWindow:ServerSelect:SelectServerID"));
		CStdString czServerLogin; 
		czServerLogin.Fmt("%dS", g_pGame->m_roleLogin.iServer);
		LOG_WRITE("Compare SeverId [%s][%s]",czServerId.c_str(), czServerLogin.c_str());
		if(czServerId.Compare(czServerLogin.c_str()) == 0){
			g_pGameControl->Clicked(pServerChoose->GetChildByPath(u"Panel:FirstWindow:EnterGame"));
			return LoopNextSleep();
		}
		else {
			g_pGameControl->Clicked(pServerChoose->GetChildByPath(u"Panel:FirstWindow:ServerSelect:Change"));
			return LoopNextSleep();
		}
		*/
	return FALSE;
}
BOOL CGLoginServerChoose::ChooseServer(CUE_Transform *pServerChoose){

	if(!pServerChoose) return FALSE;

	CUE_Transform *pChooseList = pServerChoose->GetChildByPath(u"Panel:Chooselist");
	if(!g_pGameControl->IsShowTransform(pChooseList)) return FALSE;
	int iServer = g_pGame->m_roleLogin.iServer;
	if(g_pGameControl->ClickServerListItem(pChooseList, iServer)) {
		LOG_WRITE("aaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		return TRUE;
	}

	int iGroup = ((iServer -1)/ 10) + 1; 
	int firstNum = ((iGroup -1)*10) +1;
	CStdString czGroupName;
	czGroupName.Fmt("VNG[%d~%d]", firstNum, (iGroup * 10));
	CUE_Transform *pGrid =  pChooseList->GetChildByPath(u"ServerGroup:Grid");
	if(!pGrid) return FALSE;
	int nCountGroup = pGrid->get_childCount();
	for(int i = 0; i < nCountGroup; i++){
		CUE_Transform *pItem = pGrid->GetChild(i);
		CStdString czName = g_pGameControl->GetTextA(pItem->GetChildByPath(u"Offset:Normal:Name"));
		if(czGroupName.Compare(czName.c_str()) == 0){
			BOOL bUnSelect = g_pGameControl->IsShowTransform(pItem->GetChildByPath(u"Offset:Normal"));
			if(bUnSelect){
				g_pGameControl->Clicked(pItem);
				return TRUE;
			}
			return TRUE;

		}
	}
	return FALSE;
}

BOOL CGLoginServerChoose::CloseNotice()
{
	CUE_Transform *pNotice = g_pGameControl->m_pMessageUIRoot->GetChildByName(u"notice.noticeroot");
	if(g_pGameControl->IsShowTransform(pNotice)){
		g_pGameControl->Clicked(pNotice->GetChildByPath(u"Offset:Frame_Folder:close"));
		return TRUE;
	}
	return FALSE;
}

