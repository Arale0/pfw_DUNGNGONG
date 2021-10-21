#include "GameInfo.h"
#include "main.h"

CGameInfo::CGameInfo(void)
{
	m_bControl = FALSE;
	m_bIsLogined = FALSE;
	m_bIsFullMember = FALSE;
	
	ZeroMemory(&m_curActivity,sizeof(ACTIVITY_BASE));
	ZeroMemory(&m_publisherAccount,sizeof(PUBLISHER_ACCOUNT));
	ZeroMemory(&m_roleLogin,sizeof(ROLE_LOGIN));
	ZeroMemory(&m_accountInfo,sizeof(ACCOUNT_INFO));
	ZeroMemory(&m_OptionTab,sizeof(OPTIONTAB));
	ZeroMemory(m_Members,sizeof(MEMBER) * MAX_NUM_TEAMMEMBER);
	ZeroMemory(&m_SyncValues, sizeof(SYNCVALUES));

	m_iCurrentActivity = act_none;
	m_curActivity.iId = act_none;
	m_iCurrentID = -1;

	m_bCheckPublisherAccount = TRUE;
	m_bCheckRoleLogin = TRUE;

}

CGameInfo::~CGameInfo(void)
{
}

void CGameInfo::SetPublisherAccount( LPCSTR czUsername,LPCSTR czPass )
{
	strcpy(m_publisherAccount.czUsername,czUsername);
	strcpy(m_publisherAccount.czPassword,czPass);
	LOG_WRITE("SetPublisherAccount(%s,%s)",m_publisherAccount.czUsername,m_publisherAccount.czPassword);
}

void CGameInfo::SetRoleLogin( int iServer, int idxPlayer, LPCSTR czRoleName)
{
	m_roleLogin.iServer = iServer;
	m_roleLogin.idxPlayer = idxPlayer;
	strcpy(m_roleLogin.czRoleName,czRoleName);
	LOG_WRITE("SetRoleLogin(%d,%d,[%s])",m_roleLogin.iServer,m_roleLogin.idxPlayer,m_roleLogin.czRoleName);
}

BOOL CGameInfo::IsRightUsername()
{
	static BOOL _bOk = FALSE;
	BOOL b = (strcmp(m_accountInfo.czUsername,m_publisherAccount.czUsername) == 0) &&  m_publisherAccount.czUsername[0] != 0;
	if (b && !_bOk) LOG_WRITE("************ YEAH ACCOUNT OKIE ************");		
	_bOk = b;
	return b;
}

void CGameInfo::ResetAccountInfo()
{
	if (m_accountInfo.czUsername[0] == 0) return;
	ZeroMemory(&m_accountInfo,sizeof(ACCOUNT_INFO));
}
void CGameInfo::ResetHookState()
{
	m_bControl = FALSE;
	m_bIsLogined = FALSE;
	m_bIsFullMember = FALSE;
	m_iCurrentActivity = act_none;
	m_iCurrentID	= -1;
	m_curActivity.iId = act_none;
}

BOOL CGameInfo::IsTeamLeader()
{
	static BOOL _bLeader = FALSE;
	BOOL b = (strcmp(m_accountInfo.czRoleName,m_Members[0].czTeamName) == 0) &&  m_Members[0].czTeamName[0] != 0;
	if (b && !_bLeader) LOG_WRITE("************ YEAH I'M LEADER ************");		
	_bLeader = b;
	return b;
}
BOOL CGameInfo::IsHaveTeam(){
	return m_Members[0].czTeamName[0] != 0;
}



BOOL CGameInfo::IsControl()
{
	return m_bControl;
}

BOOL CGameInfo::CheckCurrentActivity(int iActId)
{
	return (iActId == m_iCurrentActivity);
}

