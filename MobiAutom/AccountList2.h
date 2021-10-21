#pragma once
#include "../Common/global.h"

class CRoleAccount{
public:
	CRoleAccount(int playeridx, LPCSTR rolename);
	~CRoleAccount(void);
public:
	HTREEITEM hItem;
	BOOL bRunning;
	BOOL bFinished;
	int		idxPlayer;
	char	czRoleName[64];
};
class CServerAccount{
public:
	CServerAccount(int server);
	~CServerAccount(void);
	HTREEITEM hItem;
	CRoleAccount* GetReadyRole();
	
	CRoleAccount* GetRoleByTreeItem(HTREEITEM item);
	int iServer;
	CPtrList lstRole;
	CRoleAccount* AddRole(int iPlayerIdx, LPCSTR czRolename);
	CRoleAccount* GetRole(int iPlayerIdx, LPCSTR czRolename);
	CRoleAccount* GetRole(LPCSTR czRolename);
	CRoleAccount* GetRole(int iPlayerIdx);
	CRoleAccount* GetRoleRunning();
	BOOL DeleteRole(CRoleAccount *pServer);
};

class CGameAccount{
public:
	CGameAccount(LPCSTR username, LPCSTR password);
	CGameAccount(void);
	~CGameAccount(void);
	HTREEITEM hItem;
	PUBLISHER_ACCOUNT  publisherAccount;
	CPtrList lstServer;
	CServerAccount* GetServer(int iServer);
	CServerAccount* AddServer(int iServer);
	CRoleAccount* GetReadyRole(ROLE_LOGIN *pRole);
	CRoleAccount* GetRoleByTreeItem(HTREEITEM item);
	CServerAccount* GetServerByTreeItem(HTREEITEM item);
	CRoleAccount* GetRoleRunning();
	BOOL DeleteServer(CServerAccount *pServer);
};
class CAccountList2 : public CPtrList
{
public:
	
	CAccountList2(void);
	~CAccountList2(void);

	CGameAccount* AddAccount(LPCSTR czUsername, LPCSTR czPassword);
	CGameAccount* AddAccount(LPCWSTR czUsername, LPCWSTR czPassword);
	CGameAccount* GetAccount(LPCSTR czUsername);

	CRoleAccount* GetAccountReady(PUBLISHER_ACCOUNT *pAcc, ROLE_LOGIN *pRole);
	void TestAccount();
	BOOL LoadAccount(LPCWSTR szFile);
	BOOL SaveAccount(LPCWSTR szFile);
	void ShowAll();
	CRoleAccount* GetRoleByTreeItem(HTREEITEM item);
	CGameAccount* GetAccountByTreeItem(HTREEITEM item);
	CServerAccount* GetServerByTreeItem(HTREEITEM item);
	CRoleAccount* FindAccount(LPCSTR czUsername,int iServer, LPCSTR czRolename);

	BOOL DeleteAccount(CGameAccount *pAccount);

	void Clear();
	//BOOL LoadAccount(LPCWSTR czPath);
	//BOOL SaveAccount(LPCWSTR czPath);
	//void Clear();
	//GAMEACCOUNT* GetByIndex(int index);
	//GAMEACCOUNT* GetReadyAccount();
	//GAMEACCOUNT* FindAccount(LPCSTR czUsername,LPCSTR czRolename);
	//void SwapPosition( int idx1, int idx2 );
	//void SetPosition( int idx, GAMEACCOUNT* pAcc);
	

};
