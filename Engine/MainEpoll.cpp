#include "main.h"
#include "MainEpoll.h"

CMainEpoll::CMainEpoll()
{
	LOG_WRITE("CMainEpoll *** NEW ");
	m_bAigoAuth = FALSE;
	m_pClient = NULL;
	m_uLastTimeRequestAccount = 0;
	m_szKeyCrypto = "";
	m_szKeyTemp = "";
}

CMainEpoll::~CMainEpoll(void)
{
	LOG_WRITE("CMainEpoll *** DEL ");
}

void CMainEpoll::PrepareReconnect()
{
	m_pClient->SetState(CESocket::NONE);
	m_szKeyCrypto = "";
	m_bAigoAuth = FALSE;
	g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
	g_pGame->ResetHookState();

	//m_pClient->ShowBufferInfo();
	LOG_WRITE("PrepareReconnect() => WAITING RECONNECT ...");
}


BOOL CMainEpoll::Process_Networking(){
	static CESocket::State _prevState = CESocket::NONE;

	if (!m_pClient) return FALSE; // || _prevState == CESocket::CLOSED) 

	//-----Check Status Network
	CESocket::State curState = m_pClient->GetState();
	if (curState == CESocket::CLOSED){
		if (_prevState != curState){			
			_prevState = CESocket::NONE;

#ifdef BUILD_FLAG_DEBUG
			PrepareReconnect();	//_theApp->FreeLibraryAndExitThread(); //thoat hook			
#else
			PrepareReconnect();					//khong thoat hook, cho reconnet
#endif

			//PrepareReconnect();
		}
		_theApp->NextDelay(2000);
		return FALSE;
	}

	//Xu ly ket noi server
	if (_theApp->ProcessControl()) return FALSE;

	if (curState != CESocket::READY){
		_theApp->NextDelay(1000);
		return FALSE;
	}

	OnSynchronized();	
	m_pClient->Flush();
	return TRUE;
}


void CMainEpoll::ConnectServer( AIGOENTRY* aigoEntry )
{
	CESocket::State state = m_pClient->GetState();
	if (state != CESocket::NONE){
		_pShared->typeControl = TYPE_CONTROL_AIGOENTRY;
		//if (state == CESocket::CLOSED) return;
		//LOG_WRITE("CMainEpoll::ConnectServer() m_pClient->GetState() != CESocket::NONE (%d)",state);
		Del(m_pClient);		
		_theApp->NextDelay(1000);
		return;
	}

	LOG_WRITE("AutoPID:%d GamePID:%d PORT[%d]",aigoEntry->uAutoPID,aigoEntry->uGamePID,aigoEntry->iPortServer);
	CStdString szServer = CESocket::GetPublicIPAddress();
	BOOL bOk = m_pClient->Connect(szServer.c_str(),aigoEntry->iPortServer);
	LOG_WRITE(" => [%p] SOCKET [%d] Connect(%s:%d) => %d",m_pClient,m_pClient->GetSocket(),szServer.c_str(),aigoEntry->iPortServer, bOk);
	Add(m_pClient);
}

BOOL CMainEpoll::IsAuthentication()
{
	//LOG_WRITE("IsAuthentication() ....[%d]",m_bAigoAuth);
	return m_bAigoAuth;
}

void CMainEpoll::OnInitInstance()
{
	LOG_WRITE("CMainEpoll::OnInitInstance() TID:%d ....",gettid());
	m_szKeyCrypto = "";
	m_bAigoAuth = FALSE;
	CAigoClient* p = new CAigoClient(this);//khoi tao xong
	m_pClient = p;
}


void CMainEpoll::OnExitInstance()
{
	LOG_WRITE("CMainEpoll::OnExitInstance() ....");
	SAFE_DELETE(m_pClient);
}

////////////RECV DATA WINDOWS => ANDROID
void CMainEpoll::Recv_Authenticaton( CStdString& szArgs )
{
	m_szKeyCrypto = m_szKeyTemp;
	m_szKeyTemp = "";
	g_pGame->m_bControl = atoi(szArgs.c_str());
	m_bAigoAuth = TRUE;
	LOG_WRITE("Recv_Authenticaton() Control:%d [%s]...",g_pGame->m_bControl,m_szKeyCrypto.c_str());
}

void CMainEpoll::Recv_CommandControl( CStdString& szArgs )
{
	g_pGame->m_bControl = atoi(szArgs.c_str());
	LOG_WRITE("Recv_CommandControl(): %d ...",g_pGame->m_bControl);
}


void CMainEpoll::Recv_CurrentActitivty(ACTIVITY_BASE* pActBase)
{		
	g_pGame->m_iCurrentActivity = pActBase->iId;
	memcpy(&g_pGame->m_curActivity,(void*)pActBase,sizeof(ACTIVITY_BASE));		
	LOG_WRITE("Recv_CurrentActitivty():%d Status:%d ...",g_pGame->m_iCurrentActivity,g_pGame->m_curActivity.iStatus);
}
void CMainEpoll::Recv_LoginAccount(LOGIN_ACCOUNT* pLoginAcount)
{		
	memcpy(&g_pGame->m_publisherAccount,(void*)&pLoginAcount->publisherAccount,sizeof(PUBLISHER_ACCOUNT));		
	memcpy(&g_pGame->m_roleLogin,(void*)&pLoginAcount->roleLogin,sizeof(ROLE_LOGIN));		
	LOG_WRITE("Recv_PublisherAccount():[%s] [%s] ...",g_pGame->m_publisherAccount.czUsername,g_pGame->m_publisherAccount.czPassword);
	LOG_WRITE("Recv_RoleLogin():[%d] [%d] [%s]...",g_pGame->m_roleLogin.iServer,g_pGame->m_roleLogin.idxPlayer, g_pGame->m_roleLogin.czRoleName);
}
void CMainEpoll::Recv_Team(MEMBER *pMembers)
{		
	memcpy(&g_pGame->m_Members,pMembers,sizeof(MEMBER) * MAX_NUM_TEAMMEMBER);		
	LOG_WRITE("Recv_Team(): \n-[%s]\n-[%s]\n-[%s]\n-[%s]\n-[%s]",g_pGame->m_Members[0].czTeamName,g_pGame->m_Members[1].czTeamName,g_pGame->m_Members[2].czTeamName,g_pGame->m_Members[3].czTeamName,g_pGame->m_Members[4].czTeamName);
}

void CMainEpoll::Recv_TeamOption( TEAMOPTION* teamOption)
{
	LOG_WRITE("Recv_TeamOption() uSize:%d",sizeof(TEAMOPTION));
	memcpy(&g_pGame->m_TeamOption,(BYTE*)teamOption,sizeof(TEAMOPTION));
	TEAMOPTION* pTeamOption = &g_pGame->m_TeamOption;
	LOG_WRITE("bJiebai:%d", pTeamOption->bJiebai);
}
void CMainEpoll::Recv_OptionTab( OPTIONTAB* lpOptionTab )
{
	LOG_WRITE("Recv_OptionTab() uSize:%d",sizeof(OPTIONTAB));
	memcpy(&g_pGame->m_OptionTab,(BYTE*)lpOptionTab,sizeof(OPTIONTAB));
	OPTIONTAB* pTab = &g_pGame->m_OptionTab;
	//LOG_WRITE("bTest:%d", pTab->bTest);
}
void CMainEpoll::Recv_ExitAuto()
{
	LOG_WRITE("CMainEpoll::Recv_ExitAuto()...");	
	m_pClient->ShowBufferInfo();
	Del(m_pClient);
	//Exit();
	//_theApp->FreeLibraryAndExitThread(); //muon thoat hook thi uncomment
}
////////////SEND DATA ANDROID => WINDOWS
void CMainEpoll::OnSynchronized()
{	
	if (Sync_Authentication()) return;

	if (!IsAuthentication()) return;

	if (Sync_GameLogined()) return;

	if (Sync_CurrentID()) return;
}


CStdString CMainEpoll::Sync_Encode( NetCommands cmd,CStdString& szArgs )
{
	CStdString szCmd;
	szCmd.Fmt("%x ",cmd);
	CStdString szText(szCmd + szArgs);

	CXOR aXor(m_szKeyCrypto.c_str());

	aXor.Encode(szText.c_str());
	CStdString szShell,szEncode = aXor.ToBase64Url();
	CChecksum sum;
	sum.Add(szEncode.c_str());
	CStdString szSum;
	szSum.Fmt(".%X\n",sum.GetChecksum());
	return CStdString(szEncode + szSum);

}

CStdString CMainEpoll::Sync_Encode( NetCommands cmd,CStdStringU& szArgs )
{	
	UINT iSize = (szArgs.size() + 1) * 2;
	CXOR aXor1;
	aXor1.Encode((BYTE*)szArgs.GetBuffer(),iSize);
	CStdString szCmd;
	szCmd.Fmt("%x ",cmd);
	CStdString szText(szCmd + aXor1.ToBase64Url().c_str());

	CXOR aXor(m_szKeyCrypto.c_str());
	aXor.Encode(szText.c_str());
	CStdString szShell,szEncode = aXor.ToBase64Url();
	CChecksum sum;
	sum.Add(szEncode.c_str());
	CStdString szSum;
	szSum.Fmt(".%X\n",sum.GetChecksum());

	return CStdString(szEncode + szSum);	
}

CStdString CMainEpoll::Sync_Encode( NetCommands cmd,BYTE* lpBytes, UINT uSize )
{
	CStdString szCmd;
	szCmd.Fmt("%x ",cmd);
	int iLenCmd = szCmd.GetLength() + 1;
	int uTotal =  iLenCmd + uSize;
	BYTE* pData = (BYTE*)malloc(uTotal);
	CopyMemory(pData,szCmd.c_str(),iLenCmd);
	CopyMemory(&pData[iLenCmd],lpBytes,uSize);
	CXOR aXor(m_szKeyCrypto.c_str());
	aXor.Encode(pData,uTotal);
	free(pData);
	CStdString szEncode = aXor.ToBase64Url();
	CChecksum sum;
	sum.Add(szEncode.c_str());
	CStdString szSum;
	szSum.Fmt(".%X\n",sum.GetChecksum());
	//LOG_WRITE("szEncode SIZE: %d + szSum SIZE:%d", szEncode.size(),szSum.GetLength());
	return CStdString(szEncode + szSum);
}


void CMainEpoll::Sync_Send( CStdString& szCipherText,BOOL bFlush)
{
	if (!m_pClient || m_pClient->GetState() != CESocket::READY) return;
	m_pClient->Send((char*)szCipherText.c_str(),szCipherText.size(),bFlush);
}

void CMainEpoll::Sync_AccountInfo()
{
	
	ACCOUNT_INFO* pAccInfo = &g_pGame->m_accountInfo;
	LPBYTE lpBytes = (LPBYTE)pAccInfo;
	UINT uSize = sizeof(ACCOUNT_INFO);
	CStdString szCipher = Sync_Encode(NET_CMD_ACCOUNT_INFO,lpBytes,uSize);
	LOG_WRITE(" - Sync_AccountInfo uSize[%d] szCipher:%d",uSize, szCipher.size());	
	Sync_Send(szCipher, TRUE);

}
BOOL CMainEpoll::Sync_Authentication()
{
	static ULONGLONG _uStart = 0;
	if (m_bAigoAuth) return FALSE;
	ULONGLONG uTime = _GetTickCount();
	if (uTime - _uStart < 10000) return TRUE;

	if (m_szKeyTemp.empty())
		m_szKeyTemp =  CBase64Url::GenerateKey();

	CStdString szText;
	szText.Fmt("%x %s",_pShared->aigoEntry.uAutoPID,m_szKeyTemp.c_str());
	CStdString szCipher = Sync_Encode(NET_CMD_AUTH,szText);

	LOG_WRITE(" - Sync_Authentication szCipher:%d [%s]",szCipher.size(),szText.c_str());	
	Sync_Send(szCipher);	

	_uStart = _GetTickCount();
	//_theApp->NextDelay(1000);
	return TRUE;
}
BOOL CMainEpoll::Sync_GameLogined()
{
	static BOOL _bIsLogined = FALSE;
	if (_bIsLogined == g_pGame->m_bIsLogined) return FALSE;
	_bIsLogined = g_pGame->m_bIsLogined;	
	CStdString szText;
	szText.Fmt("%d",_bIsLogined);
	CStdString szCipher = Sync_Encode(NET_CMD_LOGINED,szText);
	LOG_WRITE(" - Sync_GameLogined %d szCipher:%d",_bIsLogined, szCipher.size());
	Sync_Send(szCipher);
	//_theApp->NextDelay(1000);
	return TRUE;
}


void CMainEpoll::Sync_ActivityStatus(ActivityId actId, ActivityStatus actStatus, BOOL bSyncStatusByLeader)
{
	g_pGame->m_curActivity.iStatus = actStatus;
	if (actStatus == ast_done) g_pGame->m_iCurrentActivity = act_none;
	
	int info[] = {(int)actId, (int)actStatus, (int)bSyncStatusByLeader};

	CStdString szCipher = Sync_Encode(NET_CMD_ACTIVITY_STATUS,(BYTE*)info, sizeof(int) * 3);
	Sync_Send(szCipher);
}

void CMainEpoll::Sync_GameRequestAccount()
{
	ULONGLONG uTime = _GetTickCount();
	if (uTime - m_uLastTimeRequestAccount < 10000) return;
	m_uLastTimeRequestAccount = uTime;
	CStdString szText;
	szText.Fmt("%d",1);
	CStdString szCipher = Sync_Encode(NET_CMD_GAME_REQUESTACCOUNT,szText);
	Sync_Send(szCipher);

}


void CMainEpoll::Sync_StopGame()
{
	CStdString szText("");
	CStdString szCipher = Sync_Encode(NET_CMD_STOPGAME,szText);
	Sync_Send(szCipher);
	LOG_WRITE("CMainHook::Sync_StopGame()");
}

void CMainEpoll::Sync_ActivitySttByLeader()
{
	if (g_pGame->m_SyncValues.bUpdateActivityStatusByLeader) return;
	g_pGame->m_SyncValues.bUpdateActivityStatusByLeader = TRUE;
	CStdString szText;
	szText.Fmt("%d",1);
	CStdString szCipher = Sync_Encode(NET_CMD_ACTIVITY_STT_BYLEADER, szText);
	Sync_Send(szCipher);
	LOG_WRITE("CMainEpoll::Sync_ActivitySttByLeader()......");
}

void CMainEpoll::Recv_ActivityStatusByLeader( CStdString& szArgs )
{
	g_pGame->m_SyncValues.bActivityStatus = atoi(szArgs.c_str());
	LOG_WRITE("Recv_ActivityStatusByLeader(): %d ...",g_pGame->m_SyncValues.bActivityStatus);
}

BOOL CMainEpoll::Sync_CurrentID()
{
	static int iCurrentID = -1;
	if (iCurrentID == g_pGame->m_iCurrentID) return FALSE;
	iCurrentID = g_pGame->m_iCurrentID;	
	CStdString szText;
	szText.Fmt("%d", iCurrentID);
	CStdString szCipher = Sync_Encode(NET_CMD_CURRENTID,szText);
	LOG_WRITE(" - Sync_Gold %d szCipher:%d",iCurrentID, szCipher.size());
	Sync_Send(szCipher);

	//_theApp->NextDelay(1000);
	return TRUE;
}


