#include "StdAfx.h"
#include "GameManager.h"

CGameManager::CGameManager(void)
{
	ZeroMemory(gameInfo,MAX_CLIENT_GAMEINFO * sizeof(CGameInfo));
}

CGameManager::~CGameManager(void)
{
}

CGameInfo* CGameManager::GetFreeSlot()
{
	for (int index = 0; index < MAX_CLIENT_GAMEINFO; ++index)
	{
		if (GetGameIndex(&gameInfo[index]) == -1 && !IsWindow(gameInfo[index].m_hWnd)) 
		{
			CGameInfo* pGame = &gameInfo[index];
			pGame->SetTabDataDefault();
			return pGame;
		}			
	}	
	return NULL;
}

CGameInfo* CGameManager::FindGameByVMName( LPCWSTR lpVMName, int& index )
{
	index = -1;
	if (lpVMName == NULL || lpVMName[0] == 0) return NULL;
	CPtrList* plstGame = &m_lstGame;	
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		++index;
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		if (_wcsicmp(pGame->m_czVMName, lpVMName) == 0) return pGame;		
	}	
	index = -1;
	return NULL;
}

CGameInfo* CGameManager::FindGameByVMName( EmulatorType eType,LPCWSTR lpVMName, int& index )
{
	index = -1;
	if (lpVMName == NULL || lpVMName[0] == 0) return NULL;
	CPtrList* plstGame = &m_lstGame;	
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		++index;
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		if (pGame->m_eType == eType && _wcsicmp(pGame->m_czVMName, lpVMName) == 0) return pGame;		
	}	
	index = -1;
	return NULL;
}

CGameInfo* CGameManager::GetGameInfo( int index )
{
	CPtrList* plstGame = &m_lstGame;
	POSITION pos = plstGame->FindIndex(index);
	if (pos) return (CGameInfo*)plstGame->GetAt(pos);
	return NULL;
}

CPtrList* CGameManager::GetListGame()
{
	return &m_lstGame;
}

int CGameManager::GetGameIndex( CGameInfo* pGame )
{
	CPtrList* plstGame = &m_lstGame;
	int index = 0;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{		
		CGameInfo* pGameExist = (CGameInfo*)plstGame->GetNext(pos);
		if (pGameExist == pGame) return index;
		index++;
	}
	return -1;
}

BOOL CGameManager::AnyGameActivated()
{
	CPtrList* plstGame = &m_lstGame;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{				
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		if (pGame->IsWindowActivated()) return TRUE;

	}
	return FALSE;
}

void CGameManager::SwapPosition( int idx1, int idx2 )
{
	CPtrList* plstGame = &m_lstGame;
	POSITION p1 = plstGame->FindIndex(idx1);
	POSITION p2 = plstGame->FindIndex(idx2);
	if (p1 == NULL || p2 == NULL) return;
	CGameInfo* pG1 = (CGameInfo*)plstGame->GetAt(p1);
	CGameInfo* pG2 = (CGameInfo*)plstGame->GetAt(p2);
	plstGame->SetAt(p1,pG2);
	plstGame->SetAt(p2,pG1);
}

void CGameManager::SetPosition( int idx, CGameInfo* pGame )
{
	CPtrList* plstGame = &m_lstGame;
	POSITION pos = plstGame->FindIndex(idx);
	if (pos) plstGame->SetAt(pos,pGame);
}

CGameInfo* CGameManager::GetGameInfoByAccountInlist(CRoleAccount *pAcc)
{
	CPtrList* plstGame = &m_lstGame;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{				
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		if (pGame->m_pAccountInlist == pAcc) return pGame;

	}
	return NULL;
}


CGameInfo* CGameManager::GetGameInfoByRoleName(LPCSTR czName)
{
	CPtrList* plstGame = &m_lstGame;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{				
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		if(strcmp(pGame->m_accountInfo.czRoleName, czName) == 0){
			return pGame;
		}

	}
	return NULL;
}

void CGameManager::RemoveGame( CGameInfo* pGame )
{
	CPtrList* plstGame = &m_lstGame;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{		
		POSITION posAt = pos;
		CGameInfo* pGameExist = (CGameInfo*)plstGame->GetNext(pos);
		if (pGameExist == pGame)
		{
			pGame->Reset();
			plstGame->RemoveAt(posAt);
			return;
		}
	}
}

CGameInfo* CGameManager::GetOrderRunEmulator()
{
	CPtrList* plstGame = &m_lstGame;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{		
		POSITION posAt = pos;
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		if (!pGame->m_bControl) continue;
		if (pGame->IsWindowActivated()) continue;
		if (pGame->GetGameStatus() == gs_runemulator) return pGame;
	}
	return NULL;
}

CGameInfo* CGameManager::GetOrderRunGame()
{
	CPtrList* plstGame = &m_lstGame;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{		
		POSITION posAt = pos;
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		if (!pGame->m_bControl) continue;
		if (pGame->GetGameStatus() != gs_gamenotrunning) continue;
		if (!pGame->IsWindowActivated()){
			if (pGame->m_eType == EmulType_BlueStacks){
				return pGame;
			}
			continue;
		}
		return pGame;
	}
	return NULL;
}
