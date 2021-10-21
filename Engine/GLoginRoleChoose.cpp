#include "main.h"
#include "GLoginRoleChoose.h"

CGLoginRoleChoose::CGLoginRoleChoose() :CGActivity()
{
	LOG_WRITE("NEW - CGLoginRoleChoose()");
	m_activity = (ActivityId)goal_UILoginServer;
	//g_pNetwork->Sync_StatusLogin(TRUE);
}

CGLoginRoleChoose::~CGLoginRoleChoose()
{
	LOG_WRITE("DEL - CGLoginRoleChoose()");
}

int CGLoginRoleChoose::Process()
{
 	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGLoginRoleChoose::Process()....");

		CUE_Transform *pRoleChoose = g_pGameControl->m_pUIRoot->GetChildByName(u"login.rolechoosewindow");
		if(!g_pGameControl->IsShowTransform(pRoleChoose))	return Finished();
		
		if(IsWrongAccount(pRoleChoose)) return LoopNextSleep();

		if(ChooseRole(pRoleChoose)) return LoopNextSleep(500);
		
		if(EnterGame(pRoleChoose)) return LoopNextSleep();
		
		return LoopNextSleep(1000);

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}
BOOL CGLoginRoleChoose::IsWrongAccount(CUE_Transform *pRoleChoose){
	if(!pRoleChoose) return FALSE;
	ACCOUNT_INFO* pAccount = &g_pGame->m_accountInfo;
	if(pAccount->czUsername[0] == 0){
		g_pGameControl->UpdateAccountInfo();
		return TRUE;
	}

	if(strcmp(g_pGame->m_publisherAccount.czUsername, "No Account") == 0){
		LOG_WRITE("NO ACCOUNT:[%s]",pAccount->czUsername);
		return FALSE;
	}

	if(strcmp(g_pGame->m_publisherAccount.czUsername, "") == 0){
		LOG_WRITE("NO ACCOUNT1:[%s]",pAccount->czUsername);
		return FALSE;
	}

	if(strcmp(pAccount->czUsername, g_pGame->m_publisherAccount.czUsername) == 0){
		LOG_WRITE("RIGHT ACCOUNT:[%s]",pAccount->czUsername);
		return FALSE;
	}
	LOG_WRITE("Wrong account......");
	g_pGameControl->Tap(pRoleChoose->GetChildByPath(u"topleft:Offset:Back"));
	//CRoleChooseWindow::OnClickBack()
	return TRUE;
}
BOOL CGLoginRoleChoose::EnterGame(CUE_Transform *pServerChoose){
	CRoleChooseWindow *pWindow =  CRoleChooseWindow::Instance();
	if(!pWindow) return FALSE;
	pWindow->OnEnterGameClick();
	return FALSE;
}

BOOL CGLoginRoleChoose::ChooseRole(CUE_Transform* pRoleChoose){
	if(!pRoleChoose) return FALSE;
	if(g_pGame->m_roleLogin.czRoleName[0] == 0) return FALSE;

	CRoleChooseWindow *pIns = CRoleChooseWindow::Instance();
	if (!pIns) return FALSE;

	int iRoleIdx = g_pGame->m_roleLogin.iRoleNo;

	CUE_Transform *pGrid = pRoleChoose->GetChildByPath(u"Panel:Left:Offset:Panel:Grid");
	if(!pGrid) return FALSE;
	LOG_WRITE("Role chose..................%d %d", iRoleIdx);
	int iCount = pGrid->get_childCount();
	
	if (iRoleIdx == 4) {
		LOG_WRITE("Enter game with no choose role");
		pIns->OnEnterGameClick();
		return TRUE;
	}

	if (iRoleIdx < iCount) {
		CUE_Transform *pRole = pGrid->GetChild(iRoleIdx);
		if(g_pGameControl->IsShowTransform(pRole)) {
			CRoleSelectItem *pRoleSelectItem =  (CRoleSelectItem *)pRole->GetComponent(g_pGameControl->m_gameSysTypes->Get(TYPE_RoleSelectItem));
			if (pRoleSelectItem) {
				CRoleSelectItem *pData = pRoleSelectItem->GetRoleData();
				if (!pData) {
					LOG_WRITE("Role is not create --> enter game");
					pIns->OnEnterGameClick();
					return TRUE;
				}

				int iCurRoleIdx = pIns->m_curSelectItemIndex();
				if (iCurRoleIdx == iRoleIdx) {
					LOG_WRITE("Is selected Role---> Entergame");
					pIns->OnEnterGameClick();
					return TRUE;
				}

				LOG_WRITE("Role is not choose --> Choose Role");
				pIns->OnRoleSelectItemClick(pRoleSelectItem);
				return TRUE;
			}
		}
	}
	
	return TRUE;
}