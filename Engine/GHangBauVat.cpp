#include "main.h"
#include "GHangBauVat.h"

CGHangBauVat::CGHangBauVat() :CGActivity()
{
	LOG_WRITE("NEW - CGHangBauVat()");
	//m_activity = act_hangbauvat;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGHangBauVat::~CGHangBauVat()
{
	LOG_WRITE("DEL - CGHangBauVat()");
}

int CGHangBauVat::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGHangBauVat::Process()....");

		return LoopNextSleep(1000);

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

int CGHangBauVat::processOutside()
{
	if (g_pGameControl->IsReliveWnd()) return LoopNextSleep();
	if (g_pGameControl->IsCopySceneReady()) return LoopNextSleep();
	

	return LoopNextSleep();
}



