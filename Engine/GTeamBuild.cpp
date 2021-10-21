#include "main.h"
#include "GTeamBuild.h"
#include "GSleep.h"

CGTeamBuild::CGTeamBuild()
{
	m_dwStartTime = 0;
	m_dwDelay = 1000;
	m_dwTimeOver = 0;
	m_pGame = g_pGame;
	g_pGame->m_bIsFullMember = FALSE;
	LOG_WRITE("NEW - CGTeamBuild()");
}


CGTeamBuild::~CGTeamBuild(void)
{
	LOG_WRITE("DEL - CGTeamBuild()");
	CTeamInvite* pInvite = CTeamInvite::Instance();
	CTeamController* pController = CTeamController::Instance();
	if(pInvite) pInvite->OnClose();
	if(pController) pController->OnClose();
	g_pGame->m_iCurrentID = -1;
	
}

void CGTeamBuild::Activate()
{
	CGoalComposite::Activate();	
	if(CTeamList::Instance() == NULL){
		g_pGameControl->SwitchTeamTab();
	}
	
}
int CGTeamBuild::FinishedActivity()
{
	return Finished();
}

int CGTeamBuild::LoopNextSleep(int delay)
{
	_theApp->NextTimer(delay);
	//AddSubGoal(new CGSleep(delay));
	return LoopNext();
}

int CGTeamBuild::LoopNext()
{
	m_nStatus = ACTIVE; 
	return m_nStatus;
}
DWORD CGTeamBuild::GetAliveTime()
{
	DWORD dwCurTime = _GetTickCount();
	return dwCurTime - m_dwStartTime;
}
BOOL CGTeamBuild::IsTimeOver()
{
	return (m_dwStartTime > 0)&& (m_dwTimeOver > 0) && (GetAliveTime() > m_dwTimeOver);
		
}



int CGTeamBuild::Process()
{
	g_pGameControl->SetCurrentID(109);
	int nSubGoalStatus = ProcessSubGoals();

	if(nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGTeamBuild::Process...");

		//if (!g_pGame->m_TeamOption.bInviteFriends ) return Finished();

		if (g_pGame->m_TeamOption.iTeamType != TEAMMODE_LEADER) return Finished();
		
		if (g_pGameControl->IsSingleActivity()) return Finished();

		if(g_pGameControl->IsHaveTeam() && !g_pGameControl->CanLeaveTeam())
			return Finished();

		if(g_pGame->IsTeamLeader()){ //lay ten doi truong tu mobiAuto
			if(g_pGameControl->IsLeader()) {

				if(g_pGame->m_TeamOption.bJiebai){
					return Finished();
				}
				BOOL bKickMembers = g_pGame->m_TeamOption.bKickMembers;
				if(bKickMembers){
					if(g_pGameControl->KickMember(g_pGame->m_Members)){
						return LoopNextSleep();
					}
				}

				int iAmountOfMembers = g_pGame->m_TeamOption.iSLTV;
				if (g_pGameControl->IsTeamEnoughMembers(iAmountOfMembers) && g_pGame->m_bIsFullMember) {
					LOG_WRITE("Enoughed Members....................");
					return Finished();
				}

				//if(g_pGameControl->IsFullMember(g_pGame->m_Members)){
				//	//LOG_WRITE("Finished..................... %d", g_pGame->m_TeamOption.bJiebai);
				//	return Finished();
				//}
				
				
				LOG_WRITE("CGTeamBuild::TeamInvite...");
				
				g_pGameControl->TeamInvite(g_pGame->m_Members);

				//if(!CTeamController::Instance())
				//g_pGameControl->SwitchTeamTab();
				//g_pGameControl->TeamInvite(g_pGame->m_Members);
				
				return LoopNextSleep();
			}
			LOG_WRITE("CGTeamBuild::ProcessLeader...");
			ProcessLeader();	
			return LoopNextSleep();
		}

		if(g_pGame->IsHaveTeam()){//i am member
			if(g_pGameControl->IsRightLeader(g_pGame->m_Members[0].czTeamName)){
				return Finished();
			}
			LOG_WRITE("CGTeamBuild::ProcessMember..........1");
			ProcessMember();	
			return LoopNextSleep();
		}
		return Finished();
	}

	return m_nStatus;
}
void CGTeamBuild::ProcessLeader()
{
	if(!g_pGameControl->IsHaveTeam()){
		g_pGameControl->TeamCreate();
		return;
	}
	LOG_WRITE("CGTeamBuild::ProcessLeader ... HaveTeam");
	if(!g_pGameControl->IsLeader()){
		g_pGameControl->LeaveTeam();
		return;
	}
	LOG_WRITE("CGTeamBuild::ProcessLeader ... DoNothing");

}

void CGTeamBuild::ProcessMember()
{
	if(g_pGameControl->IsHaveTeam()){
		g_pGameControl->LeaveTeam();
		return;
	}
	
	LOG_WRITE("CGTeamBuild::ProcessMember..........1");
	if (g_pGame->m_TeamOption.iTeamType == TEAMMODE_MEMBER) {
		Finished();
		return;
	}

	LOG_WRITE("CGTeamBuild::ProcessMember..........2");
	g_pGameControl->TeamInviteAccept(g_pGame->m_Members[0].czTeamName);
}
//BaseUIRoot:LeftInfoRoot:OffsetNew:Container:Offset:TeamList:Real:Buttons:Button01