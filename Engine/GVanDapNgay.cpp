#include "main.h"
#include "GVanDapNgay.h"

CGVanDapNgay::CGVanDapNgay() :CGActivity()
{
	LOG_WRITE("NEW - CGVanDapNgay()");
	m_activity = act_vandapngay;
	m_bFinished = FALSE;
	m_iClicked = 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGVanDapNgay::~CGVanDapNgay()
{
	LOG_WRITE("DEL - CGVanDapNgay()");
}

int CGVanDapNgay::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{

		if (g_pGameControl->IsMessageBox(u"mời bạn vào đội,", OFF)) return LoopNextSleep(1000);
		
		if (IsFinished()) return m_nStatus;
		
		if (IsExamWnd()) return LoopNextSleep(1000);

		JoinExamDaily();

		LOG_WRITE("CGVanDapNgay::Process()....");
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGVanDapNgay::IsExamWnd()
{
	static CStdStringU czQuest = u"";
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *p1 = p->GetChildByName(u"exam.examroot");
		if (g_pGameControl->IsShowTransform(p1)) {
			CUE_Transform *pFinished = p1->GetChildByPath(u"Offset:Right_view:Finish");
			if (g_pGameControl->IsShowTransform(pFinished)) {LOG_WRITE("IsShowTransform(pFinished).......");m_bFinished = TRUE; return TRUE;}

			CUE_Transform *pAnswerList = p1->GetChildByPath(u"Offset:Right_view:QA:Bottom:Grid");
			if (pAnswerList) {
				int iAllChild = pAnswerList->get_childCount();
				int idxRandom = g_pUEThread->GetTickCount() % iAllChild;
				CUE_Transform* pBtn = pAnswerList->GetChild(idxRandom);
				g_pGameControl->Clicked(pBtn); 
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGVanDapNgay::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(20)) {m_bFinished = TRUE; return TRUE;}
	return FALSE;
}

void CGVanDapNgay::JoinExamDaily()
{
	if (m_iClicked >= 2) {m_bFinished = TRUE; return;}
	LOG_WRITE("CGVanDapNgay::JoinExamDaily().......");
	CActivityHuoDongWindow::OnClickExamDaily();
	m_iClicked++;
	LoopNextSleep();
}



