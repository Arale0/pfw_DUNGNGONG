#include "main.h"
#include "GMainQuest.h"
#include "GTaskMainQuest.h"
#include "GTaskFuli.h"
#include "GTaskAchievement.h"
#include "GNVPhuTuyen.h"

CGMainQuest::CGMainQuest() :CGActivity()
{
	LOG_WRITE("NEW - CGMainQuest()");
	m_activity = act_mainquest;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGMainQuest::~CGMainQuest()
{
	LOG_WRITE("DEL - CGMainQuest()");
}

int CGMainQuest::Process()
{
	if (!g_pGame->CheckCurrentActivity(m_activity))
	{
		g_pNetwork->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
	}

	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("NEW - CGMainQuest:: Process()");
	g_pNetwork->Sync_ActivityStatus(m_activity,ast_done);
	return Finished();	
	return m_nStatus;
}

void CGMainQuest::Activate()
{
	CGActivity::Activate();
	AddSubGoal(new CGTaskMainQuest());
	/*AddSubGoal(new CGTaskFuli());	
	AddSubGoal(new CGTaskAchievement());*/
	//AddSubGoal(new CGNVPhuTuyen());
}

BOOL CGMainQuest::ClickQuest(){
	CUE_Transform *pQuestGrid = g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid");
	if(!pQuestGrid) {
		Finished();
		return FALSE;
	}
	CUE_Transform *pQuest0 = pQuestGrid->GetChildByName(u"0");
	if(!pQuest0) {
		Finished();
		return FALSE;
	}
	g_pGameControl->Tap(pQuest0);
	//g_pGameControl->Clicked(pQuest0);
	//g_pGameControl->MissionClicked(pQuest0);
	return TRUE;

}