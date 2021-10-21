#include "StdAfx.h"
#include "mobiAuto.h"
#include "TeamList.h"

CTeamList::CTeamList(void)
{
	m_iLastID = 0;
}

CTeamList::~CTeamList(void)
{
	Clear();
}
void CTeamList::UpdateTeamList(){
	POSITION posPrev;
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		posPrev = pos;
		CTeam *pTeam = (CTeam *)GetNext(pos);
		if(pTeam->IsEmpty()){
			RemoveAt(posPrev);
			LOGA_DEBUG("-+-+-+-+ Team %d be deleted",pTeam->iTeamID);
			delete pTeam;
		}
		else {
			pTeam->UpdateGame();
			if(pTeam->IsEmpty())
			{
				RemoveAt(posPrev);
				LOGA_DEBUG("-+-+-+-+ Team %d be deleted",pTeam->iTeamID);
				delete pTeam;
				
			}
		}
	}
}
void CTeamList::MatchTeamList(CPtrList* lstGame)
{
	if(!lstGame)return;
	
	for(POSITION pos = lstGame->GetHeadPosition(); pos != NULL;){
		CGameInfo *pGame = (CGameInfo *)lstGame->GetNext(pos);
		if(pGame->IsNeedJoinTeam()){
			MatchTeam(pGame);	
		}
	}
} 
void CTeamList::Clear(){
	while(!IsEmpty()){
		CTeam *pTeam = (CTeam *)RemoveHead();
		delete pTeam;
	}
}	

BOOL CTeamList::MatchTeam(CGameInfo *pGame){
	if(!pGame) return FALSE;
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CTeam *pTeam = (CTeam *)GetNext(pos);
		if(pTeam->IsFull()) continue;
		if(pTeam->IsEmpty()){
			pTeam->AddGame(pGame);
			return TRUE;
		}
		if(pTeam->iServer == pGame->m_accountInfo.uServerId && 
			pTeam->iActivity == (int)pGame->m_iCurrentActivity){
			pTeam->AddGame(pGame);
			return TRUE;
		}
	}
	CTeam *pTeam = new CTeam();
	pTeam->iTeamID = ++m_iLastID;
	pTeam->iServer = pGame->m_accountInfo.uServerId;
	pTeam->iActivity = (int)pGame->m_iCurrentActivity;
	pTeam->AddGame(pGame);
	AddTail(pTeam);
	return TRUE;
}
void CTeamList::LogInfo(){
	LOGA_DEBUG("Team Count:%d",GetCount());
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CTeam *pTeam = (CTeam*)GetNext(pos);
		pTeam->LogInfo();
	}
}

CTeam* CTeamList::GetTeam(int teamid)
{
	if(teamid == 0) return NULL;
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CTeam *pTeam = (CTeam *)GetNext(pos);
		if(pTeam->iTeamID == teamid){
			return pTeam;
		}
	}
	return NULL;
}

CTeam::CTeam(void)
{
	memset(pMembers,0,sizeof(pMembers));
	

}

CTeam::~CTeam(void)
{

}

BOOL CTeam::IsFull()
{
	return (GetMembers() == MAX_NUM_TEAMMEMBER);
}

BOOL CTeam::IsEmpty()
{
	return (GetMembers() == 0);
}

void CTeam::AddGame(CGameInfo *pGame)
{
	LOGA_DEBUG("-+-+-+-+ Team %d Add Game %08x",iTeamID, pGame);
	for(int i = 0; i< MAX_NUM_TEAMMEMBER; i++){
		if(pMembers[i] == NULL){
			pMembers[i] = pGame;
			pGame->GetTeamTab()->iTeamId = iTeamID;
			break;
		}
		
	}
	for(int i = 0; i< MAX_NUM_TEAMMEMBER; i++){
		if(pMembers[i] != NULL){
			UpdateTeamMembers(pMembers[i]);
		}
	}
}
void CTeam::RemoveGame(CGameInfo *pGame)
{
	if(!pGame) return;
	for(int i = 0; i< MAX_NUM_TEAMMEMBER; i++){
		if(pMembers[i] == pGame){
			pMembers[i] = NULL;
			if(pGame->GetTeamTab()->iTeamMode == TEAMMODE_MATCH)
				pGame->ResetTeam();
			break;
		}
	}
}
void CTeam::UpdateGame(){
	BOOL bNeedUpdateMembers = FALSE;
	for(int j =0; j< MAX_NUM_TEAMMEMBER; j++){
		if(pMembers[j] != NULL){
			BOOL bNeedRemove = pMembers[j]->IsDontNeedJoinTeam() || 
					pMembers[j]->m_iCurrentActivity != (ActivityId)iActivity;
			//LOGA_DEBUG("NeedJoinTeam:%d Activity:%d %d",pMembers[j]->IsNeedJoinTeam(), pMembers[j]->m_iCurrentActivity ,iActivity);
			if(bNeedRemove){
				LOGA_DEBUG("-+-+-+-+ Team %d Remove Game %08x",iTeamID, pMembers[j]);
				RemoveGame(pMembers[j]);
				//LOGA_DEBUG("1");
				bNeedUpdateMembers =TRUE;
			}
		}
	}
	if(pMembers[0] == NULL){
		//set new leader
		for(int i = 1; i< MAX_NUM_TEAMMEMBER; i++){
			if(pMembers[i] != NULL){
				pMembers[0] = pMembers[i];
				pMembers[i] = NULL;
				//LOGA_DEBUG("2");
				bNeedUpdateMembers = TRUE;
				break;
			}
		}		
	}
	if(bNeedUpdateMembers){
		//LOGA_DEBUG("...");
		for(int i = 0; i< MAX_NUM_TEAMMEMBER; i++){
			if(pMembers[i] != NULL){
				UpdateTeamMembers(pMembers[i]);
			}
		}
	}
}
void CTeam::UpdateTeamMembers(CGameInfo *pGame){
	if(!pGame) return;
	UINT uCurtime = GetTickCount();
	
	TEAMTAB* pTeamTab = pGame->GetTeamTab();
	for(int j =0; j< MAX_NUM_TEAMMEMBER; j++){
		if(pMembers[j] != NULL){
			strcpy_s(pTeamTab->members[j].czTeamName, 64, pMembers[j]->m_accountInfo.czRoleName);		
		}
		else {
			memset(pTeamTab->members[j].czTeamName, 0, 64);
		}
		LOGA_INFO(" pTeamTab->czTeamName[%d]:[%s]",j, pTeamTab->members[j].czTeamName);
	}

	pTeamTab->uTimeUpdate = uCurtime;
	pTeamTab->bUpdateNow = TRUE;	
}

int CTeam::GetMembers()
{
	int count = 0;
	for(int i = 0; i< MAX_NUM_TEAMMEMBER; i++){
		if(pMembers[i] != NULL){
			count++;
		}
	}
	return count;
}
void CTeam::LogInfo(){
	LOGA_DEBUG("ID:%d Server:%d Count:%d", iTeamID, iServer, GetMembers());
	if(pMembers[0]) LOGA_DEBUG("------[%s]", pMembers[0]->m_accountInfo.czRoleName);
	if(pMembers[1]) LOGA_DEBUG("------[%s]", pMembers[1]->m_accountInfo.czRoleName);
	if(pMembers[2]) LOGA_DEBUG("------[%s]", pMembers[2]->m_accountInfo.czRoleName);
	if(pMembers[3]) LOGA_DEBUG("------[%s]", pMembers[3]->m_accountInfo.czRoleName);
	if(pMembers[4]) LOGA_DEBUG("------[%s]", pMembers[4]->m_accountInfo.czRoleName);
}