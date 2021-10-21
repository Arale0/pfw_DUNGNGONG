#pragma once
#include <PollThread.h>
#include "AigoClient.h"


class CMainEpoll : public CPollThread
{
public:
	CMainEpoll();
	virtual ~CMainEpoll(void);
	CAigoClient*	m_pClient;

	CStdString		m_szKeyCrypto;
	CStdString		m_szKeyTemp;
	BOOL			m_bAigoAuth;
	ULONGLONG		m_uLastTimeRequestAccount;

	void			PrepareReconnect();
	BOOL			Process_Networking();
	void			ConnectServer(AIGOENTRY* aigoEntry); 
	BOOL			IsAuthentication();

	void			Recv_Authenticaton(CStdString& szArgs);
	void			Recv_CommandControl(CStdString& szArgs);
	void			Recv_CurrentActitivty(ACTIVITY_BASE* pActBase);
	void			Recv_ActivityStatusByLeader(CStdString& szArgs);

	void			Recv_LoginAccount(LOGIN_ACCOUNT* pLoginAcount);
	void			Recv_Team(MEMBER *pMembers);
	void			Recv_TeamOption( TEAMOPTION* teamOption);
	void			Recv_OptionTab( OPTIONTAB* lpOptionTab );
	void			Recv_ExitAuto();
	void			OnSynchronized();
	CStdString 		Sync_Encode( NetCommands cmd,CStdString& szArgs );
	CStdString 		Sync_Encode( NetCommands cmd,CStdStringU& szArgs );
	CStdString		Sync_Encode( NetCommands cmd,BYTE* lpBytes, UINT uSize );
	void			Sync_Send(CStdString& szCipherText,BOOL bFlush = FALSE);

	BOOL			Sync_Authentication();
	void			Sync_AccountInfo();
	BOOL			Sync_GameLogined();
	void			Sync_ActivityStatus(ActivityId actId, ActivityStatus actStatus, BOOL bSyncStatusByLeader = FALSE);
	void			Sync_GameRequestAccount();
	void			Sync_StopGame();
	void			Sync_ActivitySttByLeader();
	BOOL			Sync_CurrentID();
protected:
	virtual void OnInitInstance();	
	virtual void OnExitInstance();
	

};
