#include "main.h"
#include "GKhoaCuVanDap.h"

CGKhoaCuVanDap::CGKhoaCuVanDap() :CGActivity()
{
	LOG_WRITE("NEW - CGKhoaCuVanDap()");
	m_activity = act_khoacuvandap;
	m_bFinished = FALSE;
	m_iClicked = 0;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGKhoaCuVanDap::~CGKhoaCuVanDap()
{
	LOG_WRITE("DEL - CGKhoaCuVanDap()");
}

int CGKhoaCuVanDap::Process()
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

		if (IsExamTypeWnd()) return LoopNextSleep();

		if (IsExamWnd()) return LoopNextSleep(1000);

		JoinExamDaily();

		LOG_WRITE("CGKhoaCuVanDap::Process()....");
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

BOOL CGKhoaCuVanDap::IsExamWnd()
{
	static CStdStringU czQuest = u"";
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *p1 = p->GetChildByName(u"exam.examroot");
		if (g_pGameControl->IsShowTransform(p1)) {
			CUE_Transform *pFinished = p1->GetChildByPath(u"Offset:Right_view:Finish");
			if (g_pGameControl->IsShowTransform(pFinished)) {
				CUE_Transform *pBtnJoin = pFinished->GetChildByName(u"btn_Join");
				if (g_pGameControl->IsShowTransform(pBtnJoin)) {
					LOG_WRITE("Join round 2");
					g_pGameControl->Clicked(pBtnJoin);
					return TRUE;
				}
				else {
					LOG_WRITE("IsShowTransform(pFinished).......");
					m_bFinished = TRUE; 
					return TRUE;
				}
			}

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

BOOL CGKhoaCuVanDap::IsFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		else return FinishedActivity();
		return TRUE;
	}

	if (g_pGameControl->IsLowerLevel(20)) {m_bFinished = TRUE; return TRUE;}
	return FALSE;
}

void CGKhoaCuVanDap::JoinExamDaily()
{
	if (m_iClicked >= 2) {m_bFinished = TRUE; return;}
	LOG_WRITE("CGKhoaCuVanDap::JoinExamDaily().......");
	CActivityHuoDongWindow::OnClickExamKeju();
	m_iClicked++;
	LoopNextSleep();
}

BOOL CGKhoaCuVanDap::IsExamTypeWnd()
{
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		CUE_Transform *pExamType = pPopUIRoot->GetChildByName(u"exam.examselecttype");
		if (g_pGameControl->IsShowTransform(pExamType)) {
			CUE_Transform *pListType = pExamType->GetChildByPath(u"Offset:ExamType");
			if (g_pGameControl->IsShowTransform(pListType)) {
				int iCount = pListType->get_childCount();
				if (iCount != 0) {
					int idxRandom = g_pUEThread->GetTickCount() % iCount;
					CUE_Transform* pBtn = pListType->GetChild(idxRandom);
					LOG_WRITE("Select Type Exam........");
					g_pGameControl->Clicked(pBtn); 
					return TRUE;
				}
				return TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}



