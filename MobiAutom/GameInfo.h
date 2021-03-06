#pragma once
#include "autom\ginfo.h"
//#include "../Common/GameInfoDef.h"
#include "../Common/global_windows.h"
#include "AccountList2.h"
//-----------------------------ACTIVITY-----------------------------------
//enum GameStatusEx { gs_getplayername = gs_last + 1, gs_next };
class CDeviceManagerEx;

class CGameInfo : public CGInfo
{
public:
	time_t		m_timeGame;
	//PUBLISHER_ACCOUNT  m_publisherAccount;
	//ROLE_LOGIN		m_roleLogin;
	CRoleAccount*	m_pAccountInlist;//Account tren danh sach account, dung khi LogginMode == ACCOUNTMODE_INLIST
	LOGIN_ACCOUNT	m_loginAccount;// dung de dong bo, gui account vao trong hook

	_LIST_GIAODICH	m_syncGiaoDich;
	ACCOUNT_INFO	m_accountInfo;//dung de dong bo, nhan  account info tu hook
	
	WCHAR		_czServer[64];
	WCHAR		_czPlayer[64];

	CHAR		_czFakeName[64];	//Tên thay thế hiển thị trên listGame
	WCHAR		_czEmulatorExe[MAX_PATH];	
	WCHAR		m_czPlayerName[64];	
	HWND		m_hWndControl;
	int			m_iCurrentActivity;
	int			m_iCurrentID;

	BOOL		m_bSyncOptionTab;	//TRUE => Sync_OptionTab
	BOOL		m_bSyncLoginTab;
	BOOL		m_bSyncGiaoDich;	//TRUE => Sync_GiaoDich
	
	SyncCurrentAgain	m_flagSyncAgain;
	int			m_iconEmulator;
	UINT_PTR		uiTimerID;
	BOOL			bUpdateUINow;
	BOOL			bUpdateLoginDlgNow;

	WCHAR		m_czMapName[64];	

	ACTIVITYTAB		m_ActivityTab;
	ACTIVITYTAB*	GetActivityTab() {return &m_ActivityTab;}

	OPTIONTAB		m_OptionTab;
	OPTIONTAB*		GetOptionTab() {return &m_OptionTab;}

	SYNCVALUES		m_SyncValues;
	SYNCVALUES*		GetSyncValues() {return &m_SyncValues;}

	TEAMTAB			m_TeamTab;
	TEAMTAB*		GetTeamTab() {return &m_TeamTab;};
	
	LOGINTAB		m_LoginTab;
	LOGINTAB*		GetLoginTab() {return &m_LoginTab;};

	_LIST_GIAODICH	m_LstGiaoDich;
	_LIST_GIAODICH*		GetGiaoDich() {return &m_LstGiaoDich;};

	ACTIVITYINFOEX_MAINQUEST		m_Option_MainQuest;
	ACTIVITYINFOEX_MAINQUEST*		GetOptionMainQuest() {return &m_Option_MainQuest;}

public:
	void		SetTabDataDefault();
	int			GetDictionaryItemIndex(int iActId);
	void		SetEmulType(EmulatorType eType);
	ACTIVITYINFO*	GetActivityByAlias(LPCSTR lpAlias);
	BOOL			CheckLicenseByActivity(int iActId);
	void			SetStatusByActivity(int iActId, ActivityStatus iStatus, BOOL bUpdateControl = TRUE);
	void		UpdateCurrentActivity();
	int			GetCurrentLeaderActivity();
	BOOL		InTime(ACTIVITYINFO *pAct );

	
	void		SetPublisherAccount( LPCWSTR czUsername,LPCWSTR czPass );
	void		SetPublisherAccount( LPCSTR czUsername,LPCSTR czPass );
	void		SetRoleLogin( int iServerID, int iRoleIndex, LPCWSTR czRoleName);
	void		SetRoleLogin( int iServerID, int iRoleIndex, LPCSTR czRoleName);
	void		ResetLoginAccount();

	BOOL		IsOnTeamAcitivity();
	void		ResetTeam();
	BOOL		IsNeedJoinTeam();
	BOOL		IsDontNeedJoinTeam();
	void		UpdateTeam();
	void		RecheckDoingAcitivity();


	void			ResetActivityStatus();
	void			CheckAllActivity(BOOL bCheck);
public:
	CGameInfo(void);
	~CGameInfo(void);
	
};
