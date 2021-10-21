#pragma once
#include <EClient.h>

class CMainEpoll;

class CAigoClient : public CEClient
{
public:
	CAigoClient(CMainEpoll* pThread);
	virtual ~CAigoClient(void);
	
	CMainEpoll*	m_pThread;
	CStdString	m_szCmdCrypto;
	void		ShowBufferInfo();

protected:
	virtual void	OnCreated();
	virtual void	OnConnected();
	virtual void	OnReceive(int uBytes);
	virtual void	OnSend(int uBytes);
};
