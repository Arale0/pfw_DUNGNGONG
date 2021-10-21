#include "main.h"
#include "GTaskKetBai.h"
#include "GSleep.h"

CGTaskKetBai::CGTaskKetBai() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskKetBai()");
	m_bFinished = FALSE;
	m_iBrotherhoodCount = 0;
	m_iDelayInvite = 0;
}

CGTaskKetBai::~CGTaskKetBai()
{
	LOG_WRITE("DEL - CGTaskKetBai()");
	g_pGame->m_iCurrentID = -1;
}

int CGTaskKetBai::Process()
{

	g_pGameControl->SetCurrentID(106);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;
	
	if (IsFinished()) return m_nStatus;
	if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_LEADER) m_bFinished = TRUE;
	
	init_NumberOfJiebai();
	if (IsFriendWnd()) return LoopNextSleep();
	ShowFriendWnd();
	return LoopNextSleep();
}

int CGTaskKetBai::LoopNextSleep( int delay /*= 1000*/ )
{
	//AddSubGoal(new CGSleep(delay));
	_theApp->NextTimer(delay);
	return LoopNext();
}

void CGTaskKetBai::ShowFriendWnd()
{

	CChatFrameController *pIns = CChatFrameController::Instance();
	if (!pIns) return;
	if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
	LOG_WRITE("ShowFriendWnd...................");
	pIns->OnClickOpenFriend();
	LoopNextSleep();
}

BOOL CGTaskKetBai::IsFriendWnd()
{
	CBrotherhoodPanelMy *pIns = CBrotherhoodPanelMy::Instance();
	if (pIns) {
		int iHaveTeamCount = get_haveTeamCount();
		if (iHaveTeamCount < m_iBrotherhoodCount) {
			if (m_iDelayInvite <= 0) {
				LOG_WRITE("Invite Brotherhood....");
				pIns->OnClickTeamup();
			}
			
			if (m_iDelayInvite >= 3) {
				m_iDelayInvite = 0;
				return TRUE;
			}
			m_iDelayInvite ++;
			return TRUE;
		}
		return TRUE;
	}

	else {
		CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
		if (g_pGameControl->IsShowTransform(p)) {
			CUE_Transform *pFriendWnd = p->GetChildByName(u"friends.friendsfunction");
			if (g_pGameControl->IsShowTransform(pFriendWnd)) {
				CUE_Transform *pTabJiebai = pFriendWnd->GetChildByPath(u"tweenFrame:offset:tabbtn:Grid:Tabjiebai");
				if (g_pGameControl->IsShowTransform(pTabJiebai)) {
					LOG_WRITE("Clicked Jiebai TAB............");
					g_pGameControl->Clicked(pTabJiebai);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
	//CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	//if (g_pGameControl->IsShowTransform(p)) {
	//	CUE_Transform *pFriendWnd = p->GetChildByName(u"friends.friendsfunction");
	//	if (g_pGameControl->IsShowTransform(pFriendWnd)) {
	//		CBrotherhoodPanelMy *pIns = CBrotherhoodPanelMy::Instance();
	//		if (pIns) {
	//			CPlayerData *pPlayerData
	//			return TRUE;
	//			//LOG_WRITE("m_iDelayClicked.................................%d", m_iDelayClicked);
	//			//int iHaveTeamCount = get_haveTeamCount();
	//			int iTeamCount = get_JiebaiTeamCount();

	//			//LOG_WRITE("iTeamCount............%d, get_haveTeamCount() ... %d", iTeamCount, iHaveTeamCount);
	//			if (iTeamCount == get_haveTeamCount()) {
	//				pIns->OnClickTeamup();
	//				m_bFinished = TRUE;
	//				return TRUE;
	//			}

	//			if (m_iBrotherhoodCount <= 0) {
	//				m_iBrotherhoodCount ++;
	//				LOG_WRITE("Clicked TEAM......................");
	//				pIns->OnClickTeamup();
	//				return TRUE;
	//			}

	//			if (m_iBrotherhoodCount >= 5) m_iBrotherhoodCount = -1;

	//			m_iBrotherhoodCount ++;
	//			return TRUE;
	//		}
	//		
	//		CUE_Transform *pTabJiebai = pFriendWnd->GetChildByPath(u"tweenFrame:offset:tabbtn:Grid:Tabjiebai");
	//		if (g_pGameControl->IsShowTransform(pTabJiebai)) {
	//			LOG_WRITE("Clicked Jiebai TAB............");
	//			g_pGameControl->Clicked(pTabJiebai);
	//			return TRUE;
	//		}
	//		return TRUE;
	//	} 
	//}
	//return FALSE;
}

int CGTaskKetBai::get_haveTeamCount()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return -1;
	CTeam *pTeam = pPlayerData->get_TeamInfo();
	if (!pTeam) return -1;
	return pTeam->GetTeamMemberCount();
}

BOOL CGTaskKetBai::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return Finished();
		return TRUE;
	}
	
	if (g_pGameControl->IsFullTeam()) {
		LOG_WRITE("Team Is Full..");
		m_bFinished = TRUE;
		return TRUE;
	}
	/*CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (pPlayerData) {
		CTeam *pTeam = pPlayerData->get_TeamInfo();
		if (pTeam) {
			BOOL bIsFullTeam = pTeam->IsFull();
			LOG_WRITE("CGTaskKetBai::Process()......................%d", bIsFullTeam);
			if (bIsFullTeam) {
				m_bFinished = TRUE; 
				return TRUE;
			}

			int iHaveTeamCount = pTeam->GetTeamMemberCount();
			if (m_iBrotherhoodCount != 0 && iHaveTeamCount >= m_iBrotherhoodCount) {
				LOG_WRITE("CGTaskKetBai:: Enough......................%d", m_iBrotherhoodCount);
				m_bFinished = TRUE;
				return TRUE;
			}

		}
	}*/

	if (!g_pGame->m_TeamOption.bJiebai) {m_bFinished = TRUE; return TRUE;}

	if (g_pGameControl->IsButtonExitFuben()) {m_bFinished = TRUE; return TRUE;}
	return FALSE;
}

int CGTaskKetBai::get_JiebaiTeamCount()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pFriendWnd = p->GetChildByName(u"friends.friendsfunction");
		if (g_pGameControl->IsShowTransform(pFriendWnd)) {
			CUE_Transform *pList = pFriendWnd->GetChildByPath(u"tweenFrame:offset:jiebai(Clone):offset:Content:GridReal");
			int iAllChild = pList->get_childCount();
			if (iAllChild != 0) {
				int i = 0;
				for (i = 0; i < iAllChild; i++) {
					CUE_Transform *pItem = pList->GetChild(i);
					CUE_Transform *pEmpty = pItem->GetChildByName(u"Empty");
					if (g_pGameControl->IsShowTransform(pEmpty)) {
						return i;
					}
				}
			}
		}
	}
	return 0;
}

void CGTaskKetBai::InviteBrotherhoodMember()
{
	//static int iDelayInvite = 0;

	//CObj_MainPlayer *pPlayer = CObjManager::get_MainPlayer();

	//CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	//if (!pPlayerData) return;
	//LOG_WRITE("pPlayerData %08X", pPlayerData);
	//CBrotherhood *pBrotherhood = pPlayerData->get_BrotherhoodInfo();
	//if (!pBrotherhood) return;
	//LOG_WRITE("pFriendList %08X", pBrotherhood);
	//CSYS_List *pBrotherhoodList = pBrotherhood->m_BrotherhoodMemberList();
	//if (!pBrotherhoodList) return;
	//LOG_WRITE("pRelationList %08X", pBrotherhoodList);
	//int iCount = pBrotherhoodList->get_Count();
	//if (iCount != 0) {
	//	m_iBrotherhoodCount = iCount;

	//	if (iDelayInvite > 0) {
	//		if (iDelayInvite >= 5) {
	//			iDelayInvite = 0;
	//			return;
	//		}
	//		LOG_WRITE("Wait for invite Team............");
	//		iDelayInvite ++;
	//		return;
	//	}

	//	CSYS_Type* sysList = NULL;
	//	CSYS_Type* sysInt32 = NULL;
	//	CSYS_Type* sysUInt64 = NULL;

	//	CSYS_Type* sysType = NULL;

	//	CSYS_Assembly* sysAssembly = CSYS_Assembly::Load("mscorlib");

	//	if (sysAssembly){
	//		sysList = sysAssembly->GetType("System.Collections.Generic.List`1");
	//		sysUInt64 = sysAssembly->GetType("System.UInt64");

	//		sysType = sysAssembly->GetType("System.Type");
	//	}
	//	LOG_WRITE("Type:%p,%p",sysList,sysUInt64);
	//	if(!sysList) return;
	//	if(!sysUInt64) return;

	//	CSYS_Array *pArrParams = CSYS_Array::CreateInstance(sysType, 1);
	//	pArrParams->SetValue(sysUInt64, 0);

	//	CSYS_Type *pTypeListReal =  CSYS_TypeEx::MakeGenericType(sysList, pArrParams);
	//	LOG_WRITE("pTypeListReal:%p",pTypeListReal);

	//	CSYS_ListEx* lstBrother = (CSYS_ListEx*)Activator::CreateInstance(pTypeListReal);
	//	LOG_WRITE("lstFriend:%p",lstBrother);
	//	//add list item

	//	for(int i = 0; i < iCount; i++) {
	//		CBrotherhoodMember *pMember = (CBrotherhoodMember *)pBrotherhoodList->get_Item(i);
	//		if (pMember) {
	//			ULONGLONG uGuid = pMember->get_BrotherhoodGuid();
	//			//CStdStringU czName = pMember->get_MemberName();
	//			//LOG_WRITE("[%d] -- %s", i, _U2A(czName).c_str());
	//			LOG_WRITE("[%d][%08X] -- %lld", i, pMember, uGuid);
	//			lstBrother->Add_UInt64(uGuid);
	//		}
	//	}
	//	pPlayer->ReqInviteTeam((LPVOID)lstBrother, 0, 0);

	//	CSYS_ListEx *pLst = (CSYS_ListEx *)lstBrother;
	//	
	//	for(int i = 0; i < iCount; i++) {
	//		ULONGLONG uMember = (ULONGLONG)pLst->get_Item(i);
	//		LOG_WRITE("%lld", uMember);
	//		
	//	}
	//	iDelayInvite = 1;
	//}	

}

void CGTaskKetBai::init_NumberOfJiebai()
{
	CPlayerData *pPlayerData = CGameManager::get_PlayerDataPool();
	if (!pPlayerData) return;
	LOG_WRITE("pPlayerData %08X", pPlayerData);
	CBrotherhood *pBrotherhood = pPlayerData->get_BrotherhoodInfo();
	if (!pBrotherhood) return;
	LOG_WRITE("pFriendList %08X", pBrotherhood);
	CSYS_List *pBrotherhoodList = pBrotherhood->m_BrotherhoodMemberList();
	if (!pBrotherhoodList) return;
	LOG_WRITE("pRelationList %08X", pBrotherhoodList);
	int iCount = pBrotherhoodList->get_Count();
	if (iCount != 0) {
		m_iBrotherhoodCount = iCount;
	}

	int iHaveTeamCount = get_haveTeamCount();

	if (iHaveTeamCount >= m_iBrotherhoodCount) {
		LOG_WRITE("m_iBrotherhoodCount == [%d, %d] == iHaveTeamCount", m_iBrotherhoodCount, iHaveTeamCount);
		m_bFinished = TRUE;
		return;
	}
}
