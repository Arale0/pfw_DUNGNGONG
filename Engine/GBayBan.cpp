#include "main.h"
#include "GBayBan.h"

CGBayBan::CGBayBan() :CGActivity()
{
	LOG_WRITE("NEW - CGBayBan()");
	m_activity = act_mainquest;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGBayBan::~CGBayBan()
{
	LOG_WRITE("DEL - CGBayBan()");
}

int CGBayBan::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGBayBan::Process()....");

		return LoopNextSleep(1000);

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}



