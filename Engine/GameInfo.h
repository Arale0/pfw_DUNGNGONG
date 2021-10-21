#pragma once
#include <../define.h>
#include "../Common/global_android.h"
#include "../Common/global.h"

#define ON 1
#define OFF 0
#define HOUR 1
#define MINUTE 2
#define DAYOFWEEK 3


class CGameInfo
{
public:

	BOOL	IsControl();
	BOOL	CheckCurrentActivity(int iActId);

public:
	CGameInfo(void);
	~CGameInfo(void);

	BOOL	m_bControl;
	BOOL	m_bIsLogined;
	BOOL	m_bIsFullMember;
	int		m_iCurrentID;
	
	ActivityId		m_iCurrentActivity;
	ACTIVITY_BASE	m_curActivity;
	ACTIVITYINFOEX	m_optActivity;
	OPTIONTAB		m_OptionTab;
	TEAMOPTION		m_TeamOption;
	SYNCVALUES		m_SyncValues;
	MEMBER			m_Members[MAX_NUM_TEAMMEMBER];
	//using to login auto
	PUBLISHER_ACCOUNT	m_publisherAccount;	
	BOOL			m_bCheckPublisherAccount;

	ROLE_LOGIN		m_roleLogin;
	BOOL			m_bCheckRoleLogin;

	ACCOUNT_INFO	m_accountInfo;
	_LIST_GIAODICH	m_lstGiaoDich;
	_LIST_GIAODICH*		GetGiaoDich() {return &m_lstGiaoDich;};

	void		SetPublisherAccount(LPCSTR czUsername,LPCSTR czPass);
	void		SetRoleLogin(int iServer, int idxPlayer, LPCSTR czRoleName = "");
	BOOL		IsRightUsername();
	void		ResetAccountInfo();
	void		ResetHookState();
	BOOL		IsTeamLeader();
	BOOL		IsHaveTeam();
	
};
