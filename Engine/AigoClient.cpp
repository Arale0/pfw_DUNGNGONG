#include "main.h"
#include "AigoClient.h"
//#include <Checksum.h>
//#include <XOR.h>


CAigoClient::CAigoClient(CMainEpoll* pThread):CEClient()
{
	m_pThread = pThread;
	LOG_WRITE("CAigoClient - NEW size CGameInfo:");
}

CAigoClient::~CAigoClient(void)
{
	LOG_WRITE("CAigoClient - DEL");
	//ShowBufferInfo();
}

void CAigoClient::ShowBufferInfo()
{
	LOG_WRITE("BUFFER FREE SIZE:%d",m_ListSendBuffer.m_lstFree.size());
	LOG_WRITE("BUFFER USED SIZE:%d",m_ListSendBuffer.m_lstUsed.size());
}

void CAigoClient::OnCreated()
{
	CEClient::OnCreated();

}

void CAigoClient::OnConnected()
{
	CEClient::OnConnected();

	m_pThread->m_szKeyCrypto = "";
	m_pThread->m_bAigoAuth = FALSE;

	_pShared->typeControl = TYPE_CONTROL_NONE;
	//m_pThread->Sync_Authentication();
}

void CAigoClient::OnReceive( int uBytes )
{
	CEClient::OnReceive(uBytes);
	
	if (uBytes <= 0) return;

	char* pBytes = (char*)m_pRecvBuffer;
	UINT uLen = uBytes - 1;
	if (pBytes[uLen] != 0x0A){
		pBytes[uBytes] = 0;
		m_szCmdCrypto += pBytes;
		return;
	}

	pBytes[uLen] = 0;		
	CStdString szCrypto(pBytes);
	m_szCmdCrypto += szCrypto;	
	int iPos = m_szCmdCrypto.Find(".");
	if (iPos == -1){
		m_szCmdCrypto.Empty();
		LOG_WRITE("ERROR m_szCmdCrypto.Find(DOT)");		
		return;
	}

	CStdString szPayload = m_szCmdCrypto.Left(iPos);
	CStdString szChecksum = m_szCmdCrypto.Mid(iPos + 1);
	DWORD uSum = strtoul(szChecksum.c_str(),NULL,16);
	CChecksum sum;
	sum.Add(szPayload.c_str());
	if (uSum != sum.GetChecksum()){
		m_szCmdCrypto.Empty();
		LOG_WRITE("ERROR Checksum");		
		return;
	}
	m_szCmdCrypto.Empty();

	CXOR aXor(m_pThread->m_szKeyCrypto.c_str());
	CStdString szText = aXor.DecodeBase64Url(szPayload.c_str());
	iPos = szText.Find(" ");
	if (iPos >= 0){
		std::vector<BYTE>* pVertor;
		LPBYTE pData = NULL;
		UINT uSize = 0;

		CStdString szCmd = szText.Left(iPos);
		CStdString szArgs = szText.Mid(iPos + 1);
		NetCommands cmd = (NetCommands)strtoul(szCmd.c_str(),NULL,16);
		switch ((int)cmd){
			case NET_CMD_AUTH:
				m_pThread->Recv_Authenticaton(szArgs);
				break;
			case NET_CMD_EXIT_AUTO:
				m_pThread->Recv_ExitAuto();
				break;
			case NET_CMD_CONTROL:
				m_pThread->Recv_CommandControl(szArgs);
				break;
			case NET_CMD_ACTIVITY_CURRENT:
				pVertor = aXor.GetBytes();
				pData =  pVertor->data();
				uSize =  pVertor->size();// - iPos - 2;//2 kytu " " + 0x0
				//LOG_WRITE("ReceiveCurrentAcitivty[%p] size:%d SIZE[%d == %d]",pData,uSize,uSize - iPos - 2,sizeof(ACTIVITY_BASE));
				//_theApp->DumpHex(pData,(int)uSize);
				m_pThread->Recv_CurrentActitivty((ACTIVITY_BASE*)&pData[iPos + 2]);
				break;
			case NET_CMD_LOGIN_ACCOUNT:
				pVertor = aXor.GetBytes();
				pData =  pVertor->data();
				uSize =  pVertor->size();// - iPos - 2;//2 kytu " " + 0x0
				//LOG_WRITE("ReceiveCurrentAcitivty[%p] size:%d SIZE[%d == %d]",pData,uSize,uSize - iPos - 2,sizeof(LOGIN_ACCOUNT));
				//_theApp->DumpHex(pData,(int)uSize);
				m_pThread->Recv_LoginAccount((LOGIN_ACCOUNT*)&pData[iPos + 2]);
				break;
			case NET_CMD_TEAM:
				pVertor = aXor.GetBytes();
				pData =  pVertor->data();
				uSize =  pVertor->size();// - iPos - 2;//2 kytu " " + 0x0
				//LOG_WRITE("ReceiveCurrentAcitivty[%p] size:%d SIZE[%d == %d]",pData,uSize,uSize - iPos - 2,sizeof(LOGIN_ACCOUNT));
				//_theApp->DumpHex(pData,(int)uSize);
				m_pThread->Recv_Team((MEMBER*)&pData[iPos + 2]);
				break;
			case NET_CMD_TEAM_OPTION:
				pVertor = aXor.GetBytes();
				pData =  pVertor->data();
				uSize =  pVertor->size() - iPos - 2;//2 kytu " " + 0x0
				m_pThread->Recv_TeamOption((TEAMOPTION*)&pData[iPos + 2]);
				break;
			case NET_CMD_OPTIONTAB:
				pVertor = aXor.GetBytes();
				pData =  pVertor->data();
				uSize =  pVertor->size() - iPos - 2;//2 kytu " " + 0x0
				m_pThread->Recv_OptionTab((OPTIONTAB*)&pData[iPos + 2]);
				break;
			case NET_CMD_ACTIVITY_STT_BYLEADER:
				
				m_pThread->Recv_ActivityStatusByLeader(szArgs);
				break;
			default:
				LOG_WRITE("???WTF cmd:%d",cmd);
		}//switch (cmd){
	}//	if (iPos >= 0){
	else{
		LOG_WRITE("???WTF Text:(%s) [%s]",szText.c_str(),m_pThread->m_szKeyCrypto.c_str());
	}
	
}

void CAigoClient::OnSend( int uBytes )
{
	CEClient::OnSend(uBytes);
}
