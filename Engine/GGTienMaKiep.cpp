#include "main.h"
#include "GGTienMaKiep.h"

CGGTienMaKiep::CGGTienMaKiep() :CGActivity()
{
	LOG_WRITE("NEW - CGGTienMaKiep()");
	m_activity = act_gtienmakiep;
	m_iState = 0;
	m_iClicked = 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGGTienMaKiep::~CGGTienMaKiep()
{
	LOG_WRITE("DEL - CGGTienMaKiep()");
}

int CGGTienMaKiep::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGGTienMaKiep::Process()....");

		CStdStringU czCountTime = CActivityHuoDongWindow::GetActivityCountByActivityId(2003);
		LOG_WRITE("czCountTime [%s]", _U2A(czCountTime).c_str());
		
		if (czCountTime.Compare(u"1/1") == 0) return FinishedActivity();

		if (g_pGameControl->IsMoving()) return LoopNextSleep();

		ProcessMain();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGGTienMaKiep::ProcessMain()
{

	int iHour = getTime(0);
	int iMinute = getTime(1);
	if (iHour == 19 && iMinute >= 30) {
		g_pGameControl->SwitchAutoFight(ON);
	}
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (g_pGameControl->IsShowTransform(pBaseUIRoot)) {
		CUE_Transform *pPanel = pBaseUIRoot->GetChildByName(u"activity.huodong_limittimelist");
		if (g_pGameControl->IsShowTransform(pPanel)) {
			CUE_Transform *pList = pPanel->GetChildByPath(u"Offset:Panel:Offset:Grid");
			if (!pList) return;
			int iCount = pList->get_childCount();
			if (iCount <= 0) return;
			for (int i = 0; i < iCount; i++) {
				CUE_Transform *pItem = pList->GetChild(i);
				if (pItem) {
					CUE_Transform *pName = pItem->GetChildByName(u"Name");
					CStdStringU czName = g_pGameControl->GetTextU(pName);
					LOG_WRITE("[%s]", _U2A(czName).c_str());
					if (czName.Find(u"Tiên Ma Kiếp") >= 0) {
						LOG_WRITE("Click vao %s", _U2A(czName).c_str());

						if (m_iClicked <= 0) {
							m_iState = 1;
							g_pGameControl->Clicked(pItem);
						}

						if (m_iClicked >= 5) {
							m_iClicked = -1;
						}

						m_iClicked ++;

						LoopNextSleep();
						return;
					}
				}
			}
		}
		else {
			CUE_Transform *pBtn = pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:LimitTimeActivity");
			if (pBtn) {
				LOG_WRITE("Show Limit Activity.....");
				g_pGameControl->Clicked(pBtn);
				LoopNextSleep();
				return;
			}
		}
	}
	else g_pGameControl->CloseDialog();

	LoopNextSleep();
}

int CGGTienMaKiep::getTime( int iTypeTime /*= 0*/ )
{
	CDeviceStatusWindow *pStatus = CDeviceStatusWindow::Instance();
	if (!pStatus) return -5;
	if (iTypeTime == 0) return pStatus->get_Hour();
	if (iTypeTime == 1) return pStatus->get_Minute();
	return -1;
}

