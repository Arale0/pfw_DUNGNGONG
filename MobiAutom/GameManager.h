#pragma once
#include "GameInfo.h"
#define MAX_CLIENT_GAMEINFO	100

class CGameManager
{

public:
	CGameManager(void);
	~CGameManager(void);

	CGameInfo*	GetFreeSlot();
	CGameInfo*	FindGameByVMName(LPCWSTR lpVMName, int& index);
	CGameInfo*	FindGameByVMName(EmulatorType eType,LPCWSTR lpVMName, int& index);
	CGameInfo*	GetGameInfo(int index);
	CPtrList*	GetListGame();
	int			GetGameIndex(CGameInfo* pGame);

	BOOL		AnyGameActivated();
	void		SwapPosition(int idx1, int idx2);
	void		SetPosition(int idx, CGameInfo* pGame);
	CGameInfo*	GetGameInfoByAccountInlist(CRoleAccount *pAcc);
	CGameInfo*  GetGameInfoByRoleName(LPCSTR czName);
	void		RemoveGame(CGameInfo* pGame);
	CGameInfo*	GetOrderRunEmulator();
	CGameInfo*	GetOrderRunGame();
protected:
	
	
protected:
	CGameInfo	gameInfo[MAX_CLIENT_GAMEINFO];
	CPtrList	m_lstGame;		//danh sach xuat hien trong list
};
