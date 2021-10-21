#include "StdAfx.h"
#include "AccountList2.h"
#include "Log.h"
#include <Utils.h>
#include "document.h"
#include "writer.h"
using namespace rapidjson;
CAccountList2::CAccountList2(void)
{
	RemoveAll();
}

CAccountList2::~CAccountList2(void)
{
	Clear();
}
CGameAccount* CAccountList2::AddAccount(LPCWSTR czUsername, LPCWSTR czPassword)
{
	CHAR szUsernameA[64];
	CHAR szPasswordA[32];

	WideCharToMultiByte(CP_UTF8, 0, czUsername, -1, szUsernameA, 64, 0,0);
	WideCharToMultiByte(CP_UTF8, 0, czPassword, -1, szPasswordA, 64, 0,0);
	return AddAccount(szUsernameA,szPasswordA);
}
CGameAccount* CAccountList2::AddAccount(LPCSTR czUsername, LPCSTR czPassword)
{
	if(GetAccount(czUsername)) return NULL;
	CGameAccount *pAccount = new CGameAccount(czUsername,czPassword);
	this->AddTail(pAccount);
	return pAccount;
}

CGameAccount* CAccountList2::GetAccount(LPCSTR czUsername){
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CGameAccount* pAccount = (CGameAccount*)GetNext(pos);
		if( strcmp(pAccount->publisherAccount.czUsername, czUsername) == 0) return pAccount;
		
	}
	return NULL;
}
CRoleAccount* CAccountList2::GetAccountReady(PUBLISHER_ACCOUNT *pAcc, ROLE_LOGIN *pRole){
	if(!pAcc) return NULL;
	if(!pRole) return NULL;

	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CGameAccount* pAccount = (CGameAccount*)GetNext(pos);
		if(pAccount->GetRoleRunning()) continue;
		CRoleAccount* pRoleAccount=  pAccount->GetReadyRole(pRole);
		if(pRoleAccount) {
			memcpy(pAcc, &pAccount->publisherAccount, sizeof(PUBLISHER_ACCOUNT));
			return pRoleAccount;
		}
	}
	return NULL;
}
void CAccountList2::TestAccount()
{
	CGameAccount *pAcc = AddAccount("paladin7610", "191286");
	CServerAccount* pServer = pAcc->AddServer(21);
	pServer->AddRole(0,"stanislaw");
	pServer = pAcc->AddServer(22);
	pServer->AddRole(0,"abc");
	pServer->AddRole(0,"def");

	pAcc = AddAccount("huynt.social.1@gmail.com", "191286");
	pServer = pAcc->AddServer(22);
	pServer->AddRole(0,"Fr0stbyte");
	pServer->AddRole(0,"raknarog");
	ShowAll();
}
BOOL  CAccountList2::LoadAccount(LPCWSTR szFile){
	CFile f;
	if (!f.Open(szFile, CFile::modeRead | CFile::shareDenyWrite)) return FALSE;

	UINT uSize = (UINT)f.GetLength();
	CStringA szContextA('0', uSize);
	char* lpText = szContextA.GetBuffer();
	f.Read(lpText, uSize);
	f.Close();

	Document d;
	d.Parse(szContextA);
	if (d.HasParseError()) {
		LOGA_ERROR("ERROR Parse: %d", d.GetParseError());
		return FALSE;
	}
	
	if (d.HasMember("accs")) {
		Value& aAccounts = d["accs"];	
		int iCount = (int)aAccounts.Size();
		for (int i = 0; i < iCount; i++) {
			Value& oAcc = aAccounts[i];
			if (oAcc.IsNull()) continue;	
			if (!oAcc.HasMember("u")) continue;
			if (!oAcc.HasMember("p")) continue;
			CGameAccount* pAcc = AddAccount(oAcc["u"].GetString(), oAcc["p"].GetString());
			if(!pAcc) continue;
			if (oAcc.HasMember("s")) {
				Value& aServer = oAcc["s"];	
				int iCountSvr = (int)aServer.Size();	
				for(int j =0; j < iCountSvr; j++){
					Value& oServer  = aServer[j];
					if(oServer.IsNull()) continue;
					if(!oServer.HasMember("i"))continue;
					CServerAccount* pServer = pAcc->AddServer(oServer["i"].GetUint());	
					if(!pServer) continue;
					if(oServer.HasMember("r")){
						Value& sRoles = oServer["r"];			
						int iCountRole = (int)sRoles.Size();
						for(int k=0; k< iCountRole; k++){
							Value& oRole = sRoles[k];
							if(oRole.IsNull()) continue;
							if(!oRole.HasMember("i"))continue;
							if(!oRole.HasMember("n"))continue;
							pServer->AddRole(oRole["i"].GetUint(), oRole["n"].GetString());
						}
					}
				}
			}

		}
	}
	return TRUE;

}
BOOL  CAccountList2::SaveAccount(LPCWSTR szFile){
	Document json;
	Document::AllocatorType& alt = json.GetAllocator();
	Value& oRoot = json.SetObject();
	Value sValue(kStringType);
	
	Value aAccounts(kArrayType);
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CGameAccount *pAcc = (CGameAccount *)GetNext(pos);
		//
		Value oAccount(kObjectType);
		sValue.SetString(pAcc->publisherAccount.czUsername,alt);
		oAccount.AddMember("u",sValue,alt);
		
		sValue.SetString(pAcc->publisherAccount.czPassword,alt);
		oAccount.AddMember("p",sValue,alt);
		if(!pAcc->lstServer.IsEmpty()){
			Value aServer(kArrayType);
			for(POSITION posSvr = pAcc->lstServer.GetHeadPosition(); posSvr != NULL;){
				CServerAccount*pSvr = (CServerAccount *)GetNext(posSvr);
				//
				Value oServer(kObjectType);
				oServer.AddMember("i",pSvr->iServer, alt);
				if(!pSvr->lstRole.IsEmpty()){
					Value aRoles(kArrayType);
					for(POSITION posRole = pSvr->lstRole.GetHeadPosition(); posRole!= NULL;){
						CRoleAccount* pRole = (CRoleAccount*)GetNext(posRole);
						//
						Value oRole(kObjectType);
						oRole.AddMember("i",pRole->idxPlayer, alt);
						sValue.SetString(pRole->czRoleName,alt);
						oRole.AddMember("n",sValue, alt);
						aRoles.PushBack(oRole, alt);
					}
					oServer.AddMember("r",aRoles, alt);
				}
				aServer.PushBack(oServer, alt);
				
			}
			oAccount.AddMember("s",aServer,alt);
		}
		aAccounts.PushBack(oAccount,alt);
		
	}
	oRoot.AddMember("accs",aAccounts,alt);
	StringBuffer buff;
	Writer<StringBuffer> writer(buff);
	json.Accept(writer);

	CFile f;
	if (f.Open(szFile, CFile::modeCreate | CFile::modeReadWrite)) {
		f.Write(buff.GetString(), buff.GetSize());
		f.Close();
	}
	return TRUE;
}
void CAccountList2::ShowAll()
{
	LOGA_INFO("[%d]",GetCount());
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CGameAccount* pAccount = (CGameAccount*)GetNext(pos);
		LOGA_INFO("%s",pAccount->publisherAccount.czUsername);
	}
}
CRoleAccount* CAccountList2::GetRoleByTreeItem(HTREEITEM item){
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CGameAccount *pAcc = (CGameAccount *)GetNext(pos);
		CRoleAccount *pRole = pAcc->GetRoleByTreeItem(item);
		if(pRole) return pRole;
	}
	return NULL;
}
CGameAccount* CAccountList2::GetAccountByTreeItem(HTREEITEM item){
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CGameAccount *pAcc = (CGameAccount *)GetNext(pos);
		if(pAcc->hItem == item) return pAcc;
	}
	return NULL;
}
CServerAccount* CAccountList2::GetServerByTreeItem(HTREEITEM item){
	for(POSITION pos = GetHeadPosition(); pos != NULL;){
		CGameAccount *pAcc = (CGameAccount *)GetNext(pos);
		CServerAccount *pServer = pAcc->GetServerByTreeItem(item);
		if(pServer) return pServer;
	}
	return NULL;
}

CRoleAccount* CAccountList2::FindAccount(LPCSTR czUsername,int iServer, LPCSTR czRolename)
{
	CGameAccount *pAcc = GetAccount(czUsername);
	if(!pAcc) return NULL;
	CServerAccount *pSvr = pAcc->GetServer(iServer);
	if(!pSvr) return NULL;
	return pSvr->GetRole(czRolename);
}

BOOL CAccountList2::DeleteAccount(CGameAccount *pAccount)
{
	POSITION posPrev;
	for (POSITION pos = GetHeadPosition(); pos != NULL;)
	{	
		posPrev = pos;
		CGameAccount* pAcc = (CGameAccount*)GetNext(pos);
		if(pAcc == pAccount){
			RemoveAt(posPrev);
			delete pAcc;
			return TRUE;
		}
	}
	return FALSE;
}

void CAccountList2::Clear(){
	while(!IsEmpty()){
		CGameAccount *pAcc= (CGameAccount *)RemoveHead();
		while(pAcc->lstServer.IsEmpty()){
			CServerAccount *pServer = (CServerAccount *)pAcc->lstServer.RemoveHead();
			while(pServer->lstRole.IsEmpty()){
				CRoleAccount *pRole = (CRoleAccount *)pServer->lstRole.RemoveHead();
				delete pRole;
			}
			delete pServer;
		}
		delete pAcc;
	}
}
CGameAccount::CGameAccount()
{

}

CGameAccount::CGameAccount(LPCSTR username, LPCSTR password)
{
	strcpy_s(publisherAccount.czUsername, 64, username);
	strcpy_s(publisherAccount.czPassword, 32, password);
}

CGameAccount::~CGameAccount(void)
{

}

CServerAccount* CGameAccount::GetServer(int iServer)
{
	for(POSITION pos = lstServer.GetHeadPosition(); pos != NULL;){
		CServerAccount* pServer = (CServerAccount*)lstServer.GetNext(pos);
		if(pServer->iServer == iServer) return pServer;

	}
	return NULL;	
}

CServerAccount* CGameAccount::AddServer(int iServer)
{
	if(!GetServer(iServer)){
		
		CServerAccount *pSA =  new CServerAccount(iServer);
		if(lstServer.IsEmpty())	lstServer.AddHead(pSA);
		else {
			POSITION posPrev;
			for(POSITION pos = lstServer.GetHeadPosition(); pos != NULL;){
				posPrev = pos;
				CServerAccount *pServer= (CServerAccount *)lstServer.GetNext(pos);
				if(pServer->iServer > iServer){
					lstServer.InsertBefore(posPrev, pSA);
					return pSA;
				}
			}
			lstServer.AddTail(pSA);

		}
		return pSA;
	}
	return NULL;
}
CRoleAccount* CGameAccount::GetReadyRole(ROLE_LOGIN *pRole){
	for(POSITION pos = lstServer.GetHeadPosition(); pos != NULL;){
		CServerAccount* pServer = (CServerAccount*)lstServer.GetNext(pos);
		CRoleAccount*pRoleAcc = pServer->GetReadyRole();
		if(pRoleAcc) {
			strcpy_s(pRole->czRoleName, 64, pRoleAcc->czRoleName);
			pRole->idxPlayer = pRoleAcc->idxPlayer;
			pRole->iServer = pServer->iServer;
			return pRoleAcc;
		}

	}
	return NULL;
}
CRoleAccount* CGameAccount::GetRoleByTreeItem(HTREEITEM item){
	for(POSITION pos = lstServer.GetHeadPosition(); pos != NULL;){
		CServerAccount* pServer = (CServerAccount*)lstServer.GetNext(pos);
		CRoleAccount*pRoleAcc = pServer->GetRoleByTreeItem(item);
		if(pRoleAcc) {
			return pRoleAcc;
		}

	}
	return NULL;
}
CServerAccount* CGameAccount::GetServerByTreeItem(HTREEITEM item){
	for(POSITION pos = lstServer.GetHeadPosition(); pos != NULL;){
		CServerAccount* pServer = (CServerAccount*)lstServer.GetNext(pos);
		if(pServer->hItem == item) {
			return pServer;
		}

	}
	return NULL;
}
CRoleAccount* CGameAccount::GetRoleRunning(){
	for(POSITION pos = lstServer.GetHeadPosition(); pos != NULL;){
		CServerAccount* pServer = (CServerAccount*)lstServer.GetNext(pos);
		CRoleAccount*pRoleAcc = pServer->GetRoleRunning();
		if(pRoleAcc) {
			return pRoleAcc;
		}

	}
	return NULL;
}
BOOL CGameAccount::DeleteServer(CServerAccount *pServer){
	POSITION posPrev;
	for (POSITION pos = lstServer.GetHeadPosition(); pos != NULL;)
	{	
		posPrev = pos;
		CServerAccount* pAcc = (CServerAccount*)lstServer.GetNext(pos);
		if(pAcc == pServer){
			lstServer.RemoveAt(posPrev);
			delete pAcc;
			return TRUE;
		}
	}
	return FALSE;
}
CServerAccount::CServerAccount(int server)
{
	iServer = server;
}

CServerAccount::~CServerAccount(void)
{

}
CRoleAccount* CServerAccount::GetReadyRole()
{
	for(POSITION pos = lstRole.GetHeadPosition(); pos != NULL;){
		CRoleAccount* pRole = (CRoleAccount*)lstRole.GetNext(pos);
		if(!pRole->bRunning && !pRole->bFinished) {
			return pRole;
		}

	}
	return NULL;
}
CRoleAccount* CServerAccount::GetRoleByTreeItem(HTREEITEM item)
{
	for(POSITION pos = lstRole.GetHeadPosition(); pos != NULL;){
		CRoleAccount* pRole = (CRoleAccount*)lstRole.GetNext(pos);
		if(pRole->hItem == item) {
			return pRole;
		}

	}
	return NULL;
}

CRoleAccount * CServerAccount::AddRole(int iPlayerIdx, LPCSTR czRolename)
{
	if(GetRole(czRolename)) return FALSE;
	if(strlen(czRolename) ==0 &&  GetRole(iPlayerIdx, "")) return FALSE;
	CRoleAccount *pRole = new CRoleAccount(iPlayerIdx,czRolename);
	lstRole.AddTail(pRole);
	return pRole;
}

CRoleAccount* CServerAccount::GetRole(int iPlayerIdx, LPCSTR czRolename)
{
	for(POSITION pos = lstRole.GetHeadPosition(); pos != NULL;){
		CRoleAccount* pRole = (CRoleAccount*)lstRole.GetNext(pos);
		if(pRole->idxPlayer == iPlayerIdx && 
			strcmp(czRolename, pRole->czRoleName) == 0) return pRole;

	}
	return NULL;
}

CRoleAccount* CServerAccount::GetRole(int iPlayerIdx)
{
	for(POSITION pos = lstRole.GetHeadPosition(); pos != NULL;){
		CRoleAccount* pRole = (CRoleAccount*)lstRole.GetNext(pos);
		if(pRole->idxPlayer == iPlayerIdx ) return pRole;

	}
	return NULL;
}

CRoleAccount* CServerAccount::GetRole(LPCSTR czRolename)
{
	for(POSITION pos = lstRole.GetHeadPosition(); pos != NULL;){
		CRoleAccount* pRole = (CRoleAccount*)lstRole.GetNext(pos);
		if(strcmp(czRolename, pRole->czRoleName) == 0) return pRole;

	}
	return NULL;
}
CRoleAccount* CServerAccount::GetRoleRunning()
{
	for(POSITION pos = lstRole.GetHeadPosition(); pos != NULL;){
		CRoleAccount* pRole = (CRoleAccount*)lstRole.GetNext(pos);
		if(pRole->bRunning) return pRole;

	}
	return NULL;
}
BOOL CServerAccount::DeleteRole(CRoleAccount *pRole){
	POSITION posPrev;
	for (POSITION pos = lstRole.GetHeadPosition(); pos != NULL;)
	{	
		posPrev = pos;
		CRoleAccount* pR = (CRoleAccount*)lstRole.GetNext(pos);
		if(pR == pRole){
			lstRole.RemoveAt(posPrev);
			delete pR;
			return TRUE;
		}
	}
	return FALSE;
}
CRoleAccount::CRoleAccount(int playeridx, LPCSTR rolename)
{
	idxPlayer = playeridx;
	strcpy_s(czRoleName, 64, rolename);
	bFinished=  FALSE;
	bRunning = FALSE;
}

CRoleAccount::~CRoleAccount(void)
{

}
