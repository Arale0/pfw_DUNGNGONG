#include "StdAfx.h"
#include "mobiAuto.h"
#include "DeviceManagerEx.h"
#include <Crypto/XOR.h>
#include <Crypto/Checksum.h>

#ifndef BUILD_FLAG_DEBUG 
//#include "x86_mono.h"
//#include "arm_mono.h"
#include "x86_il2cpp.h"
#include "arm_il2cpp.h"
#endif

IMPLEMENT_DYNCREATE(CDeviceManagerEx, CDeviceManager)

CDeviceManagerEx::CDeviceManagerEx(void)
{
	ZeroMemory(&m_gameSync,sizeof(GAME_SYNC_FLAGS));
	m_gameSync.iCurrentActivity = -1;
	m_gameSync.bControl = FALSE;
	
	//m_dwTTL = 0;
}

CDeviceManagerEx::~CDeviceManagerEx(void)
{
}
BOOL CDeviceManagerEx::IsAuthentication()
{
	return m_bAigoAuth;
}
void CDeviceManagerEx::OnInitDevice()
{

	CDeviceManager::OnInitDevice();

	LOGA_WARNING("");

	m_uGameRanOver = 30;		//game must run >= 15s
	m_uAndroidVersionMin = 4;	//vlv android >= 4
	m_uAndroidVersionMax = 7;	//<=6;
	m_pGame = (CGameInfo*)m_pProcess->GetGameInfo(); 
	//m_dwTTL = 0;
	m_pGame->m_iArch = arch_arm;
	m_pGame->m_iUnityType = unity_il2cpp;


#ifndef BUILD_FLAG_DEBUG
	MemAigoFiles* pMemFiles = &m_pGame->m_MemAigoFile;
	//pMemFiles->mem[LIBAIGO_X86_MONO].iSize = X86_MONO_size;
	//pMemFiles->mem[LIBAIGO_X86_MONO].pMemory = (LPBYTE)X86_MONO;
	//pMemFiles->mem[LIBAIGO_ARM_MONO].iSize = ARM_MONO_size;
	//pMemFiles->mem[LIBAIGO_ARM_MONO].pMemory = (LPBYTE)ARM_MONO;
	pMemFiles->mem[LIBAIGO_X86_IL2CPP].iSize = X86_IL2CPP_size;
	pMemFiles->mem[LIBAIGO_X86_IL2CPP].pMemory = (LPBYTE)X86_IL2CPP;
	pMemFiles->mem[LIBAIGO_ARM_IL2CPP].iSize = ARM_IL2CPP_size;
	pMemFiles->mem[LIBAIGO_ARM_IL2CPP].pMemory = (LPBYTE)ARM_IL2CPP;
#endif

}

void CDeviceManagerEx::OnExitDevice()
{
	LOGW_WARNING(L"[%s] TID[%d]",m_pProcess->szVMName,GetCurrentThreadId());
	if (!m_pAigoConnect) return;
	CStringA szArgs;
	szArgs.Format("1");
	CStringA szCipher = Sync_Encode(NET_CMD_EXIT_AUTO,szArgs);
	Sync_Send(szCipher,TRUE);
	Sleep(100);
}

void CDeviceManagerEx::OnInitGame()
{

	/*CDeviceManager::OnInitGame();
	CDeviceManager::OnInitGame();
	CDeviceManager::OnInitGame();
	CDeviceManager::OnInitGame();
	CDeviceManager::OnInitGame();*/

	SetSyncFlag();

	/*if (m_pGame->m_czWndName[0] == 0){
		GetWindowText(m_pGame->m_hWnd,m_pGame->m_czWndName,MAX_PATH);
		LOGW_WARNING(L"[%s] HWND[%s]",m_pGame->m_czVMName,m_pGame->m_czWndName);
	}

	if (m_pGame->m_eType == EmulType_BlueStacks){

		LOGA_WARNING("----- 4");
		WCHAR czText[MAX_PATH];
		GetWindowText(m_pGame->m_hWnd,czText,MAX_PATH);
		CStringA szFakeNameA = CUtils::_W2A(czText);
		szFakeNameA.Trim();
		strcpy_s(m_pGame->_czFakeName, 64, szFakeNameA);
	}*/

	LOGA_WARNING("----- 3");
}

void CDeviceManagerEx::OnExitGame()
{
	LOGA_WARNING("");
	m_szCmdCrypto = "";	
	ZeroMemory(&m_gameSync,sizeof(GAME_SYNC_FLAGS));
	m_gameSync.iCurrentActivity = -1;


	CDeviceManager::OnExitGame();
}

void CDeviceManagerEx::OnReceiveCommand( SENDBUFFER* p )
{	
//	CLog::DumpHex(p->pBytes,p->nSize);
	char* pBytes = (char*)p->pBytes;
	UINT uLen = p->nSize - 1;
	if (pBytes[uLen] != 0x0A){
		pBytes[p->nSize] = 0;
		m_szCmdCrypto += pBytes;
		return;
	}
	
	pBytes[uLen] = 0;		
	CStringA szCrypto(pBytes);
	m_szCmdCrypto += szCrypto;	
	int iPos = m_szCmdCrypto.Find(".");
	if (iPos == -1){
		m_szCmdCrypto.Empty();
		return;
	}
	CStringA szPayload = m_szCmdCrypto.Left(iPos);
	CStringA szChecksum = m_szCmdCrypto.Mid(iPos + 1);
	DWORD uSum = strtoul(szChecksum.GetBuffer(),NULL,16);
	CChecksum sum;
	sum.Add(szPayload);
	if (uSum != sum.GetChecksum()){
		m_szCmdCrypto.Empty();
		return;
	}
	CStringA szText;
	CXOR* pXor;
	CXOR aXor1;
	CXOR aXor2(m_szKeyCrypto);
	if (!m_bAigoAuth){	
		pXor = &aXor1;
		szText = aXor1.DecodeBase64UrlA(szPayload);
	}
	else{
		pXor = &aXor2;
		szText = aXor2.DecodeBase64UrlA(szPayload);
	}
	
	iPos = szText.Find(" ");
	if (iPos >= 0){
		LPBYTE pData = NULL;
		UINT uSize = 0;
		CStringA szCmd = szText.Left(iPos);
		CStringA szArgs = szText.Mid(iPos + 1);
		NetCommands cmd = (NetCommands)strtoul(szCmd.GetBuffer(),NULL,16);
		//LOGW_WARNING(L"cmd: [%d]",cmd);
		switch (cmd){
			case NET_CMD_AUTH:
				Recv_Authentication(szArgs);
				break;
			case NET_CMD_ACCOUNT_INFO:
				pData = pXor->GetBytes()->GetData();
				ReceiveAccountInfo((ACCOUNT_INFO*)&pData[iPos + 2]);
				break;
			case NET_CMD_LOGINED:
				LOGW_WARNING(L"NET_CMD_LOGINED");
				ReceiveLogined(szArgs);
				break;
			case NET_CMD_ACTIVITY_STATUS:{
				LOGW_WARNING(L"NET_CMD_ACTIVITY_STATUS");
				pData = pXor->GetBytes()->GetData();
				int* pInfo = (int*)&pData[iPos + 2];
				ReceiveCommandActivityStatus((ActivityId)pInfo[0], (ActivityStatus)pInfo[1], (BOOL)pInfo[2]);
										 }
				break;
			case NET_CMD_STOPGAME:
				Recv_StopGame(szArgs);
			case NET_CMD_GAME_REQUESTACCOUNT:
				LOGW_WARNING(L"NET_CMD_GAME_REQUESTACCOUNT");
				ReceiveCommandGameRequestAccount(szArgs);
				break;
			case NET_CMD_ACTIVITY_STT_BYLEADER:
				Recv_ActivityStatusByLeader(szArgs);
				break;
			case NET_CMD_CURRENTID:
				Recv_CurrentID(szArgs);
				break;
			default:
				LOGA_ERROR("??? WTF cmd: [%d][\n]",cmd,szText);
				break;
		}//switch (cmd){
	}//	if (iPos >= 0){

	//LogWriteA("[%s]",szText);
	
	m_szCmdCrypto.Empty();
}

void CDeviceManagerEx::OnSynchronized()
{
	//if (m_szKeyCrypto.IsEmpty()) return;
	if (!IsAuthentication()) return;	

	if (Sync_GameControl()) return;
	if (Sync_CurrentActivity()) return;
	if (Sync_TeamTab()) return;
	if (Sync_TeamOption()) return;
	if (Sync_OptionTab()) return;
	if (Sync_GiaoDich()) return;
	if (Sync_LoginTab()) return;

}

void CDeviceManagerEx::Recv_Authentication( CStringA szArgs )
{
	UINT uAutoPID = strtoul(szArgs.GetBuffer(),NULL,16);
	BOOL bAuthen = (uAutoPID == GetCurrentProcessId());
	int i = szArgs.Find(" ");
	CStringA szKey;
	szKey.Format("%s",szArgs.Mid(i + 1));
	LOGW_WARNING(L"[%s] AUTH: %d [%s]",m_pProcess->GetGameInfo()->m_czVMName,bAuthen,CUtils::_A2W(szKey));
	CStringA szText;
	szText.Format("%d",m_pGame->m_bControl);
	CStringA szCipher = Sync_Encode(NET_CMD_AUTH,szText);
	Sync_Send(szCipher,TRUE);
	m_szKeyCrypto = szKey;
	m_bAigoAuth = bAuthen;
	NextDelay();
}

void CDeviceManagerEx::ReceiveAccountInfo( ACCOUNT_INFO* pAccInfo )
{
	memcpy_s(&m_pGame->m_accountInfo,sizeof(ACCOUNT_INFO),pAccInfo,sizeof(ACCOUNT_INFO));
	//LOGA_DEBUG("[+] [%s] czUserID",pAccInfo->czUserID);
	LOGA_DEBUG("[+] [%s] czUsername",pAccInfo->czUsername);
	//LOGA_DEBUG("[+] [%s] czSocialID",pAccInfo->czSocialID);
	//LOGA_DEBUG("[+] [%d] uTypeLogin",pAccInfo->uTypeLogin);

	
	//LOGA_DEBUG("[+] [%s] czRoleId",pAccInfo->czRoleId);
	//LOGA_DEBUG("[+] [%d] uRoleLevel",pAccInfo->uRoleLevel);
	//LOGA_DEBUG("[+] [%s] czRoleInfo",pAccInfo->czRoleInfo);
	LOGA_DEBUG("[+] [%s] czRoleName",pAccInfo->czRoleName);
	LOGA_DEBUG("[+] [%d] uServerId",pAccInfo->uServerId);
	LOGA_DEBUG("[+] [%s] czServerName",pAccInfo->czServerName);
	
	int iAccountMode = m_pGame->GetLoginTab()->iAccountMode;
	LOGA_DEBUG("[+] [%d] iAccountMode",iAccountMode);

	if(iAccountMode == ACCOUNTMODE_FIXED){
		LOGIN_ACCOUNT *pLoginAccount = &m_pGame->GetLoginTab()->accountFixed;
		if(strcmp(pLoginAccount->publisherAccount.czUsername, pAccInfo->czUsername) != 0){
			strcpy_s(pLoginAccount->publisherAccount.czUsername, 64, pAccInfo->czUsername);
			m_pGame->bUpdateLoginDlgNow = TRUE;
		}
		if(strcmp(pLoginAccount->roleLogin.czRoleName, pAccInfo->czRoleName) != 0){
			strcpy_s(pLoginAccount->roleLogin.czRoleName, 64, pAccInfo->czRoleName);
			m_pGame->bUpdateLoginDlgNow = TRUE;
		}
		if(pLoginAccount->roleLogin.iServer != (int)pAccInfo->uServerId){
			pLoginAccount->roleLogin.iServer = (int)pAccInfo->uServerId;
			m_pGame->bUpdateLoginDlgNow = TRUE;
		}
	}
	//if(iAccountMode == ACCOUNTMODE_INLIST){
	//	CRoleAccount* pAccountInlist =  g_pAutoManager->m_AccountList2.FindAccount(pAccInfo->czUsername, pAccInfo->uServerId, pAccInfo->czRoleName);
	//	if(!pAccountInlist){
	//		pAccountInlist =  g_pAutoManager->m_AccountList2.FindAccount(pAccInfo->czUsername, pAccInfo->uServerId, "");
	//		if(pAccountInlist)	strcpy_s(pAccountInlist->czRoleName, 64, pAccInfo->czRoleName);
	//	}
	//	if(pAccountInlist){
	//		if(m_pGame->m_pAccountInlist != pAccountInlist){
	//			if(m_pGame->m_pAccountInlist){
	//				m_pGame->m_pAccountInlist->bRunning = FALSE;
	//			}
	//			m_pGame->m_pAccountInlist = pAccountInlist;
	//		}
	//		pAccountInlist->bRunning = TRUE;
	//		//g_pMainDlg->m_tabMain.m_AccountDlg.UpdateTree();
	//	}
	//}
	
}
void CDeviceManagerEx::Recv_StopGame( CStringA szArgs )
{
	KillGame();
}
void CDeviceManagerEx::ReceiveLogined( CStringA szArgs )
{
	m_pGame->m_bIsLogined = (atoi(szArgs.GetBuffer()) == 1);
	LOGW_DEBUG(L"[%s] LOGINED: %d",m_pProcess->GetGameInfo()->m_czVMName,m_pGame->m_bIsLogined);
	if (m_pGame->m_bIsLogined) m_pGame->SetGameStatus(gs_logined);
	else m_pGame->SetGameStatus(gs_gameinit);
}

void CDeviceManagerEx::ReceiveCommandActivityStatus(ActivityId actId, ActivityStatus actStatus, BOOL bSyncStatusByLeader)
{
	LOGW_DEBUG(L"[%s] ACTIVITY STATUS: [%d] [%d]",m_pProcess->GetGameInfo()->m_czVMName,actId,actStatus);
	CPtrList* plstGame = g_pGameManager->GetListGame();

	if (bSyncStatusByLeader) {
		for(POSITION pos = plstGame->GetHeadPosition(); pos != NULL;){
			CGameInfo *pGame = (CGameInfo *)plstGame->GetNext(pos);
			if(pGame != m_pGame && pGame->m_iCurrentActivity == (int)actId){
				pGame->SetStatusByActivity(actId,actStatus);
			}
		}
		return;
	}
	((CGameInfo *)m_pProcess->GetGameInfo())->SetStatusByActivity(actId,actStatus);
}
void CDeviceManagerEx::ReceiveCommandGameRequestAccount( CStringA szArgs ){
	
	if(m_pGame->GetLoginTab()->iAccountMode == ACCOUNTMODE_FIXED){
		LOGIN_ACCOUNT *pLoginAccount = &m_pGame->GetLoginTab()->accountFixed;
		m_pGame->SetPublisherAccount(pLoginAccount->publisherAccount.czUsername, pLoginAccount->publisherAccount.czPassword);
		m_pGame->SetRoleLogin(pLoginAccount->roleLogin.iServer, pLoginAccount->roleLogin.idxPlayer, pLoginAccount->roleLogin.czRoleName);
		return;
	}
	if(m_pGame->m_pAccountInlist) return;
	PUBLISHER_ACCOUNT publisherAccount;
	ROLE_LOGIN		roleLogin;
	CRoleAccount *pAcc = g_pAutoManager->m_AccountList2.GetAccountReady(&publisherAccount, &roleLogin);
	LOGA_DEBUG("pAcc %08x",pAcc);
	if(!pAcc) return;
	
	m_pGame->SetPublisherAccount(publisherAccount.czUsername, publisherAccount.czPassword);
	m_pGame->SetRoleLogin(roleLogin.iServer, roleLogin.idxPlayer, roleLogin.czRoleName);
	m_pGame->m_pAccountInlist = pAcc;
	pAcc->bRunning = TRUE;
	//g_pMainDlg->m_tabMain.m_LoginDlg.UpdateTree();
}

void CDeviceManagerEx::SetSyncFlag()
{
	//m_pGame->m_bSyncLoginInfo = TRUE;
	//m_pGame->m_bSyncOptionTab = TRUE;
	//m_bDisConnectServer = FALSE;
	//m_dwConnectServer = 0;
	m_pGame->m_iCurrentActivity  = -1;
	m_pGame->m_iCurrentID	= -1;

	m_gameSync.bControl = FALSE;
	LOGW_DEBUG(L"[%s] m_bControl:%d",m_pProcess->GetGameInfo()->m_czVMName,m_pGame->m_bControl);

}

BOOL CDeviceManagerEx::Sync_GameControl()
{
	if (m_gameSync.bControl == m_pGame->m_bControl) return FALSE;
	LOGW_DEBUG(L"[%s] m_bControl:%d",m_pProcess->GetGameInfo()->m_czVMName,m_pGame->m_bControl);
	m_gameSync.bControl = m_pGame->m_bControl;
	CStringA szArgs;
	szArgs.Format("%d",m_pGame->m_bControl);
	CStringA szCipher = Sync_Encode(NET_CMD_CONTROL,szArgs);
	Sync_Send(szCipher);
	return TRUE;
}

BOOL CDeviceManagerEx::Sync_OptionTab()
{
	if (!m_pGame->m_bSyncOptionTab) return FALSE;
	m_pGame->m_bSyncOptionTab = FALSE;

	OPTIONTAB* pTab = m_pGame->GetOptionTab();
	LOGW_DEBUG(L"[%s] OPTIONTAB:%d",m_pProcess->GetGameInfo()->m_czVMName,pTab->bTest);

	CStringA szCipher = Sync_Encode(NET_CMD_OPTIONTAB,(BYTE*)pTab,sizeof(OPTIONTAB));
	Sync_Send(szCipher);
	return TRUE;
	
}
BOOL CDeviceManagerEx::Sync_TeamTab(){
	TEAMTAB *pTeamTab =  m_pGame->GetTeamTab();
	if(pTeamTab->uTimeUpdate == m_gameSync.uTimeUpdateTeam) return FALSE;
	m_gameSync.uTimeUpdateTeam = pTeamTab->uTimeUpdate;
	CStringA szCipher = Sync_Encode(NET_CMD_TEAM,(BYTE*)pTeamTab->members,(sizeof(MEMBER) * MAX_NUM_TEAMMEMBER));
	Sync_Send(szCipher);
	return TRUE;
	
}

BOOL CDeviceManagerEx::Sync_TeamOption(){
	TEAMTAB *pTeamTab =  m_pGame->GetTeamTab();
	if(!pTeamTab->bSyncTeamOption) return FALSE;
	TEAMOPTION *pTeamOption = &pTeamTab->teamOption;
	pTeamTab->bSyncTeamOption = FALSE;
	CStringA szCipher = Sync_Encode(NET_CMD_TEAM_OPTION,(BYTE*)pTeamOption,sizeof(TEAMOPTION));
	Sync_Send(szCipher);
	return TRUE;
}
BOOL CDeviceManagerEx::Sync_CurrentActivity()
{
	if (m_gameSync.iCurrentActivity == m_pGame->m_iCurrentActivity &&
		m_pGame->m_flagSyncAgain != SYNC_CURRENT_ACTIVITY) return FALSE;

	LOGW_DEBUG(L"[%s] m_iCurrentActivity:%d SIZE:%d",m_pProcess->GetGameInfo()->m_czVMName,m_pGame->m_iCurrentActivity,sizeof(ACTIVITY_BASE));
	m_gameSync.iCurrentActivity = m_pGame->m_iCurrentActivity;
		
	ACTIVITY_BASE actBase;	
	ZeroMemory(&actBase,sizeof(ACTIVITY_BASE));
	ACTIVITY_BASE* pActBase = &actBase;

	if (m_pGame->m_iCurrentActivity == -1) actBase.iId = (ActivityId)-1;	
	else pActBase = (ACTIVITY_BASE*)&m_pGame->m_ActivityTab.lstActivity[m_pGame->m_iCurrentActivity];
	
	CStringA szCipher = Sync_Encode(NET_CMD_ACTIVITY_CURRENT,(BYTE*)pActBase,sizeof(ACTIVITY_BASE));
	Sync_Send(szCipher);

	if (m_pGame->m_flagSyncAgain == SYNC_CURRENT_ACTIVITY) m_pGame->m_flagSyncAgain = SYNC_CURRENT_NONE;
	return TRUE;
}
BOOL CDeviceManagerEx::Sync_CurrentActivityOption()
{
	if (!m_gameSync.bCurrentActivityOption) return FALSE;
	/*
	CStringA szCipher;
	switch (m_pGame->m_iCurrentActivity){
		
		case act_clonePlayer:{				//NET_CMD_CLONE_PLAYER
			szCipher = Sync_Encode(NET_CMD_CLONE_PLAYER,(BYTE*)&m_pGame->m_clonePlayer,sizeof(CLONEPLAYER));
			LOGW_DEBUG(L"[%s] m_iCurrentActivity:%d CLONEPLAYER:%d",m_pGame->m_czVMName,m_pGame->m_iCurrentActivity,sizeof(CLONEPLAYER));
			Sync_Send(szCipher);
					   }
							 break;
		case act_singleSecret:
			szCipher = Sync_Encode(NET_CMD_SINGLE_SERECT,(BYTE*)&m_pGame->m_singleSerect,sizeof(SINGLE_SERECT));
			LOGW_DEBUG(L"[%s] m_iCurrentActivity:%d SINGLE_SERECT:%d",m_pGame->m_czVMName,m_pGame->m_iCurrentActivity,sizeof(SINGLE_SERECT));
			Sync_Send(szCipher);
			break;
			
	}
	*/
	m_gameSync.bCurrentActivityOption = FALSE;
	return TRUE;
	
}
BOOL CDeviceManagerEx::Sync_LoginTab()
{
	if(strcmp(m_pGame->m_loginAccount.publisherAccount.czUsername,m_gameSync.loginAccount.publisherAccount.czUsername) != 0 ||
		strcmp(m_pGame->m_loginAccount.publisherAccount.czPassword,m_gameSync.loginAccount.publisherAccount.czPassword) != 0 ||
		strcmp(m_pGame->m_loginAccount.roleLogin.czRoleName, m_gameSync.loginAccount.roleLogin.czRoleName) != 0 ||
		m_pGame->m_loginAccount.roleLogin.iServer != m_gameSync.loginAccount.roleLogin.iServer || 
		m_pGame->m_loginAccount.roleLogin.idxPlayer != m_gameSync.loginAccount.roleLogin.idxPlayer) { //||
		//m_pGame->m_bSyncLoginTab == TRUE){
			LOGA_INFO("Sync login Account...");
			//m_pGame->m_bSyncLoginTab = FALSE;
			memcpy(&m_gameSync.loginAccount, &m_pGame->m_loginAccount,sizeof(LOGIN_ACCOUNT));
			CStringA szCipher = Sync_Encode(NET_CMD_LOGIN_ACCOUNT,(LPBYTE)&m_gameSync.loginAccount, sizeof(LOGIN_ACCOUNT));
			Sync_Send(szCipher);
			return TRUE;
	}
	return FALSE;
}
void CDeviceManagerEx::UpdateActivityOption(int actId,ACTIVITYINFOEX *pActEx)
{
	//pActEx->bLicensed = 
	if(actId == act_mainquest){
		memcpy(&pActEx->mainquest, m_pGame->GetOptionMainQuest(), sizeof(ACTIVITYINFOEX_MAINQUEST));  
		return;
	}
	//if(actId == act_pbanhhung){
	//	memcpy(&pActEx->pbanhhung, m_pGame->GetOptionPBAnhHung(), sizeof(ACTIVITYINFOEX_PBANHHUNG));
	//	return;
	//}
}

void CDeviceManagerEx::Recv_ActivityStatusByLeader( CStringA szArgs )
{
	SYNCVALUES *pValue = m_pGame->GetSyncValues();
	pValue->bActivityStatus = atoi(szArgs.GetBuffer());
	LOGW_DEBUG(L"%s m_pGame->m_SyncValues.bActivityStatus = %d", m_pGame->m_czVMName, m_pGame->m_SyncValues.bActivityStatus);
	CPtrList* plstGame = g_pGameManager->GetListGame();
	for(POSITION pos = plstGame->GetHeadPosition(); pos != NULL;){
		CGameInfo *pGame = (CGameInfo *)plstGame->GetNext(pos);
		if(pGame != m_pGame){
			pGame->m_SyncValues.bActivityStatus = m_pGame->m_SyncValues.bActivityStatus;
			//memcpy(&pGame->m_OptionTab.bActivityStatus, &m_pGame->m_OptionTab.bActivityStatus, sizeof(OPTIONTAB));
			LOGW_DEBUG(L"%s pGame->m_SyncValues.bActivityStatus = %d", pGame->m_czVMName, pGame->m_SyncValues.bActivityStatus);
		}
	}
}

BOOL CDeviceManagerEx::Sync_ActivityStatusByLeader()
{
	SYNCVALUES *pValue = m_pGame->GetSyncValues();
	if (!pValue->bActivityStatus) return FALSE;
	LOGW_DEBUG(L"[%s] ---------------------------->bActivityStatus:%d",m_pProcess->GetGameInfo()->m_czVMName, pValue->bActivityStatus);
	//m_gameSync.bActivityStatusByLeader = pValue->bActivityStatus;
	CStringA szArgs;
	szArgs.Format("%d", 1);
	pValue->bActivityStatus = FALSE;
	CStringA szCipher = Sync_Encode(NET_CMD_ACTIVITY_STT_BYLEADER, szArgs);
	Sync_Send(szCipher);
	return TRUE;
}

void CDeviceManagerEx::Recv_CurrentID( CStringA szArgs )
{
	m_pGame->m_iCurrentID = atoi(szArgs.GetBuffer());
	LOGW_DEBUG(L"[%s] LOGINED: %d",m_pProcess->GetGameInfo()->m_czVMName, m_pGame->m_iCurrentID);
	g_pMainDlg->m_tabMain.m_OptionDlg.updateCurrentID(m_pGame);
}

BOOL CDeviceManagerEx::Sync_GiaoDich()
{
	if (!m_pGame->m_bSyncGiaoDich) return FALSE;
	m_pGame->m_bSyncGiaoDich = FALSE;

	_LIST_GIAODICH* pTab = m_pGame->GetGiaoDich();
	LOGW_DEBUG(L"OK SYNC");

	CStringA szCipher = Sync_Encode(NET_CMD_GIAODICH,(BYTE*)pTab,sizeof(_LIST_GIAODICH));
	Sync_Send(szCipher);
	return TRUE;

}

