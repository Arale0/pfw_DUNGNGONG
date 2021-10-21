#pragma once
#include <Autom\DeviceManager.h>
//#include <Autom\ADBDClient.h>

class CDeviceManagerEx : public CDeviceManager
{
public:
	DECLARE_DYNCREATE(CDeviceManagerEx)
	CDeviceManagerEx(void);
	~CDeviceManagerEx(void);

	BOOL IsAuthentication();
protected:
	virtual void		OnInitDevice();
	virtual void		OnExitDevice();
	virtual void		OnInitGame();
	virtual void		OnExitGame();
		
	virtual void		OnReceiveCommand(SENDBUFFER* p);
	virtual void		OnSynchronized();

	void				Recv_Authentication(CStringA szArgs);

	void				ReceiveAccountInfo(ACCOUNT_INFO* pAccInfo);
	void				Recv_StopGame( CStringA szArgs );
	void				Recv_ActivityStatusByLeader( CStringA szArgs );
	void				ReceiveLogined(CStringA szArgs);
	void				ReceiveCommandActivityStatus(ActivityId actId, ActivityStatus actStatus, BOOL bSyncStatusByLeader);
	void				ReceiveCommandGameRequestAccount( CStringA szArgs );
	void				Recv_CurrentID(CStringA szArgs);
	void				SetSyncFlag();
	BOOL				Sync_GameControl();
	BOOL				Sync_OptionTab();
	BOOL				Sync_GiaoDich();
	BOOL				Sync_TeamTab();
	BOOL				Sync_TeamOption();

	BOOL				Sync_CurrentActivity();
	BOOL				Sync_CurrentActivityOption();
	BOOL				Sync_LoginTab();
	BOOL				Sync_ActivityStatusByLeader();
	void				UpdateActivityOption(int actId,ACTIVITYINFOEX *pActEx);
	GAME_SYNC_FLAGS		m_gameSync;	
	CGameInfo*			m_pGame;
	CStringA			m_szCmdCrypto;
	DWORD				m_dwTTL;
};
