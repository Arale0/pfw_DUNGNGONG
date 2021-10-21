#include "StdAfx.h"
#include "GameInfo.h"
#include "resource.h"
#include "Log.h"
#include "..\..\__AIGGlobal\Windows\Utils.h"
CGameInfo::CGameInfo(void)
{
	this->uiTimerID = 0;
	m_flagSyncAgain = SYNC_CURRENT_NONE;
	bUpdateUINow = FALSE;
	m_pAccountInlist= NULL;
	m_bSyncOptionTab = FALSE;
	m_bSyncGiaoDich = FALSE;
	m_bSyncLoginTab = TRUE;
}

CGameInfo::~CGameInfo(void)
{
}

void CGameInfo::SetTabDataDefault()
{
	memset(&m_ActivityTab,0,sizeof(ACTIVITYTAB));
	memset(&m_OptionTab,0,sizeof(OPTIONTAB));
	memset(&m_accountInfo,0,sizeof(ACCOUNT_INFO));
	memset(&m_TeamTab,0,sizeof(TEAMTAB));
	memset(&m_LoginTab,0,sizeof(LOGINTAB));
	memset(&m_loginAccount,0,sizeof(LOGIN_ACCOUNT));

	bUpdateUINow = FALSE;
	m_bSyncOptionTab = TRUE;
	m_bSyncLoginTab = TRUE;
	m_iCurrentActivity = -1;
	m_iCurrentID = -1;
	m_flagSyncAgain = SYNC_CURRENT_NONE;
	m_pAccountInlist= NULL;

	m_TeamTab.iTeamId = 0;
}

int CGameInfo::GetDictionaryItemIndex( int iActId )
{
	for(int i = 0; i< MAX_NUM_ACTIVITY; i++)
	{
		if(m_ActivityTab.lstDictionary[i] == iActId)
			return i;
	}
	return -1;
}

void CGameInfo::SetEmulType( EmulatorType eType )
{
	m_eType = eType;
	switch (m_eType){
		case EmulType_NoxPlayer:
			m_iconEmulator = IDI_ICON_NOX;
			break;
		case EmulType_LDPlayer:
			m_iconEmulator = IDI_ICON_LD;
			break;
		case EmulType_MemuPlayer:
			m_iconEmulator = IDI_ICON_MEMU;
			break;
		case EmulType_BlueStacks:
			m_iconEmulator = IDI_ICON_BLUE;

		case EmulType_BlueStacks64:
			m_iconEmulator = IDI_ICON_BLUE;
			break;
		case EmulType_BlueStacks5:
			m_iconEmulator = IDI_ICON_BLUE;
			break;

		default:
			m_iconEmulator = IDI_ICON_LD;
			break;
	}
}

ACTIVITYINFO* CGameInfo::GetActivityByAlias( LPCSTR lpAlias )
{
	for (int i = 0; i < MAX_NUM_ACTIVITY; i++)
	{
		if (strcmp(m_ActivityTab.lstActivity[i].szAlias, lpAlias) == 0) return &m_ActivityTab.lstActivity[i];
	}
	return NULL;
}

BOOL CGameInfo::CheckLicenseByActivity( int iActId )
{
#ifdef BUILD_FLAG_DEBUG
	return TRUE;
#endif
	LOGA_DEBUG(" iActId %d/%d",iActId,MAX_NUM_ACTIVITY);
	if(iActId >= MAX_NUM_ACTIVITY) return FALSE;
	LOGA_DEBUG(" iActId %d",m_ActivityTab.lstActivity[iActId].bLicensed);
	return m_ActivityTab.lstActivity[iActId].bLicensed;
}

void CGameInfo::SetStatusByActivity(int iActId, ActivityStatus iStatus , BOOL bUpdateControl /*= TRUE*/)
{
	if(iActId >= MAX_NUM_ACTIVITY) return;
	if(m_ActivityTab.lstActivity[iActId].iStatus != iStatus) {

		if (m_ActivityTab.lstActivity[iActId].bChecked && 
			m_ActivityTab.lstActivity[iActId].iStatus == ast_done){
			LOGA_DEBUG("Sync Current ........................");
			m_flagSyncAgain = SYNC_CURRENT_ACTIVITY;
		}
		m_ActivityTab.lstActivity[iActId].iStatus = iStatus;		
		bUpdateUINow = bUpdateControl;
	}
}
void CGameInfo::UpdateCurrentActivity(){
	//LOGW_DEBUG(L"[%s]  .............................",m_czVMName);
	int idResult =  -1;
	for (int i = 0; i < MAX_NUM_ACTIVITY; i++)	{
		int actID  = m_ActivityTab.lstDictionary[i];
		if(actID < MAX_NUM_ACTIVITY){
			ACTIVITYINFO *pAct = &m_ActivityTab.lstActivity[actID];
			BOOL bCond = pAct->bChecked && 
						pAct->bLicensed && pAct->iStatus != ast_done;
			
			//LOGA_INFO("----Activity:%d Cond:%d [Check:%d Lic:%d Status:%d] Intime:%d",actID, bCond, pAct->bChecked , pAct->bLicensed, pAct->iStatus, InTime(pAct));
			if(bCond){
				if(InTime(pAct)){
					idResult = actID;
					break;
				}
			}
		}
	}
	m_iCurrentActivity  = idResult;
	//LOGW_DEBUG(L"[%s]  m_iCurrentActivity.............................%d",m_czVMName,  m_iCurrentActivity);
	
	
}
void CGameInfo::RecheckDoingAcitivity(){
	//cap nhat lai cac activity doing -> donot
	for (int i = 0; i < MAX_NUM_ACTIVITY; i++)	{
		int actID  = m_ActivityTab.lstDictionary[i];
		if(actID < MAX_NUM_ACTIVITY){
			ACTIVITYINFO *pAct = &m_ActivityTab.lstActivity[actID];
			if(pAct->iStatus== ast_doing && m_iCurrentActivity != actID){
				SetStatusByActivity(actID, ast_donot);
			}
		}
	}
}
BOOL CGameInfo::InTime(ACTIVITYINFO *pAct ){
	
	if(!pAct) return FALSE;
	if(pAct->iType == atp_fixedtime){
		CTime tTime = CTime::GetCurrentTime();
		int curTime = CUtils::GetTimeLine(tTime.GetHour(), tTime.GetMinute(), tTime.GetSecond());
		int dow = tTime.GetDayOfWeek();
		BYTE dayofweek = DAY_SUNDAY << (dow -1);

		//LOGA_DEBUG("activity %d dayofweek %d %d %d",(int)pAct->iId, dayofweek,pAct->week,(int)(dayofweek & pAct->week));
		if(dayofweek & pAct->week) {
			for(int i = 0; i < MAX_ACTIVITY_PERIOD; i++){
				ACTIVITY_PERIOD *pPeriod = & pAct->time[i];
				if(pPeriod->bChecked && pPeriod->iFrom >= 0 && pPeriod->iTo > 0){
					if( curTime >= pPeriod->iFrom &&  curTime <= pPeriod->iTo){
						return TRUE;
					}
				}
			}
		}
		if(pAct->iStatus == ast_donot){
			SetStatusByActivity(pAct->iId, ast_waiting, TRUE);
		}
		return FALSE;
	}
	return TRUE;
}

void CGameInfo::SetPublisherAccount(LPCWSTR czUsername,LPCWSTR czPass)
{
	CHAR szUsername[64];
	CHAR szPassword[64];
	WideCharToMultiByte(CP_UTF8,0, czUsername, -1, szUsername, 64, NULL, NULL);
	WideCharToMultiByte(CP_UTF8,0, czPass, -1, szPassword, 64, NULL, NULL);
	SetPublisherAccount(szUsername, szPassword);
}

void CGameInfo::SetPublisherAccount( LPCSTR czUsername,LPCSTR czPass )
{
	strcpy(m_loginAccount.publisherAccount.czUsername,czUsername);
	strcpy(m_loginAccount.publisherAccount.czPassword,czPass);
	LOGA_DEBUG("SetPublisherAccount(%s,%s)",m_loginAccount.publisherAccount.czUsername,m_loginAccount.publisherAccount.czPassword);
}
void CGameInfo::SetRoleLogin(int iServerID, int iRoleIndex, LPCWSTR czRoleName)
{
	CHAR szRoleName[64];
	WideCharToMultiByte(CP_UTF8,0, czRoleName, -1, szRoleName, 64, NULL, NULL);
	SetRoleLogin(iServerID,iRoleIndex, szRoleName);
}
void CGameInfo::SetRoleLogin(int iServerID, int iRoleIndex, LPCSTR czRoleName)
{
	m_loginAccount.roleLogin.iServer = iServerID;
	m_loginAccount.roleLogin.idxPlayer = iRoleIndex;
	strcpy(m_loginAccount.roleLogin.czRoleName,czRoleName);
	LOGA_DEBUG("SetRoleLogin(%d,%d,%s)",m_loginAccount.roleLogin.iServer,m_loginAccount.roleLogin.idxPlayer,m_loginAccount.roleLogin.czRoleName);
}

void CGameInfo::ResetLoginAccount()
{
	memset(&m_loginAccount,0,sizeof(LOGIN_ACCOUNT));
}

BOOL CGameInfo::IsOnTeamAcitivity()
{
	if(m_iCurrentActivity == act_phuongdegian) return TRUE;
	if(m_iCurrentActivity == act_phuongminhcoc) return TRUE;
	if(m_iCurrentActivity == act_thuongthienphatac) return TRUE;
	if(m_iCurrentActivity == act_pbhoanghon) return TRUE;
	//if(m_iCurrentActivity == act_elewar) return TRUE;
	return FALSE;
}

void CGameInfo::ResetTeam()
{
	
	GetTeamTab()->iTeamId = 0;
	GetTeamTab()->uTimeUpdate = 0;
	GetTeamTab()->bUpdateNow = TRUE;
	memset(GetTeamTab()->members, 0, sizeof(MEMBER) * MAX_NUM_TEAMMEMBER);

}

BOOL CGameInfo::IsNeedJoinTeam()
{
	//GetTeamTab()->chkTeamMatch &&
	return m_bIsLogined && 
		GetTeamTab()->iTeamId == 0 && 
		GetTeamTab()->iTeamMode == TEAMMODE_MATCH && 
		IsOnTeamAcitivity();
}

BOOL CGameInfo::IsDontNeedJoinTeam()
{
	//GetTeamTab()->chkTeamMatch &&
	return !m_bIsLogined || 
		GetTeamTab()->iTeamMode != TEAMMODE_MATCH ||
		!IsOnTeamAcitivity();
}

void CGameInfo::UpdateTeam()
{
	TEAMTAB *pTeamTab = GetTeamTab();
	//if(pTeamTab->iTeamMode == TEAMMODE_INTELLIGENCE){
	//	ResetTeam();
	//	//return;
	//}
	if(pTeamTab->iTeamMode == TEAMMODE_MATCH){
		ResetTeam();
		return;
	}
	if(pTeamTab->iTeamMode == TEAMMODE_LEADER){
		ResetTeam();
		strcpy_s(pTeamTab->members[0].czTeamName, 64, m_accountInfo.czRoleName);
		for(int i =1; i < MAX_NUM_TEAMMEMBER; i++){
			strcpy_s(pTeamTab->members[i].czTeamName, 64, pTeamTab->membersInLeaderMode[i].czTeamName);
		}
		pTeamTab->uTimeUpdate = GetTickCount();
		return;
	}
	if(pTeamTab->iTeamMode == TEAMMODE_MEMBER){
		ResetTeam();
		strcpy_s(pTeamTab->members[0].czTeamName, 64, pTeamTab->czLeaderInMemberMode);
		pTeamTab->uTimeUpdate = GetTickCount();	
		return;
	}
	if(pTeamTab->iTeamMode == TEAMMODE_ALONE){
		ResetTeam();
		return;
	}
}

void CGameInfo::CheckAllActivity( BOOL bCheck )
{
	for(int i = 0; i< MAX_NUM_ACTIVITY; i++)
	{
		if(m_ActivityTab.lstActivity[i].bChecked != bCheck) 
		{
			bUpdateUINow = TRUE;
			m_ActivityTab.lstActivity[i].bChecked = bCheck;
		}
	}
}

void CGameInfo::ResetActivityStatus()
{
	for(int i = 0; i< MAX_NUM_ACTIVITY; i++)
	{
		if(m_ActivityTab.lstActivity[i].iStatus != ast_donot && m_ActivityTab.lstActivity[i].iStatus != ast_doing) bUpdateUINow = TRUE;
		m_ActivityTab.lstActivity[i].iStatus = ast_donot;

	}

	ZeroMemory(&m_SyncValues,sizeof(SYNCVALUES));
}



