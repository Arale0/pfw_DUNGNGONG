#include "main.h"
#include "GSonCocDatLinh.h"

CGSonCocDatLinh::CGSonCocDatLinh() :CGActivity()
{
	LOG_WRITE("NEW - CGSonCocDatLinh()");
	m_activity = act_soncocdatlinh;
	m_bFinished = FALSE;
	m_bCanjoin = FALSE;
	m_bShowMap = FALSE;
	m_iShowMap = -1;
	_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_doing);
}

CGSonCocDatLinh::~CGSonCocDatLinh()
{
	LOG_WRITE("DEL - CGSonCocDatLinh()");
}

int CGSonCocDatLinh::Process()
{
 	if (!g_pGame->CheckCurrentActivity(m_activity)) /*|| g_pGame->GetStatusByActivity(m_activity) != ast_doing*/
 	{
 		_theApp->m_pEpoll->Sync_ActivityStatus(m_activity,ast_donot);
		return Finished();
 	}
	
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus == COMPLETED)
	{
		LOG_WRITE("CGSonCocDatLinh::Process()....");
		
		if (m_bFinished) {
			if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
			return FinishedActivity();
		}
		
		if (g_pGameControl->IsMember() && g_pGameControl->IsFollowLeader()) {
			if (g_pGameControl->IsShowPopUI()) {
				g_pGameControl->CloseDialog();
				return LoopNextSleep();
			}
			g_pGameControl->FollowLeader(OFF);
			return	LoopNextSleep();
		}

		if (IsMaple()) return LoopNextSleep();

		if (!IsInFb()) m_iShowMap = -1;

		if (IsInFb()) return LoopNextSleep();

		if (IsBattleFieldWnd()) return LoopNextSleep();

		ShowBattleFieldWnd();
		return m_nStatus;

	}//if (nSubGoalStatus == COMPLETED)
	return m_nStatus;
}

void CGSonCocDatLinh::ShowBattleFieldWnd()
{	
	/*if (g_pGameControl->checkCanJoinActivity(m_activity, m_bFinished) && m_bCanjoin) {
		LoopNextSleep();
		return;
	}*/

	static int i = -1;
	if (g_pGameControl->IsShowPopUI()) i = 1;
		
	if (i >= 5) {
		i = 0;
		LOG_WRITE("ShowBattleFieldWnd............. ");
		CActivityHuoDongWindow::OnClickBattleField();
		LoopNextSleep();
		return;
	}
	i ++;
	LoopNextSleep();
}

BOOL CGSonCocDatLinh::IsBattleFieldWnd()
{	
	CUE_Transform *pPopUIRoot = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(pPopUIRoot)) {
		LOG_WRITE("pPopUIRoot.....");
		CUE_Transform *pBattleFieldWnd = pPopUIRoot->GetChildByName(u"zhanchang.zhanchang_baoming");
		if (g_pGameControl->IsShowTransform(pBattleFieldWnd)) {
			LOG_WRITE("pBattleFieldWnd.....");
			m_bShowMap = FALSE;
			CUE_Transform *pLabel = pBattleFieldWnd->GetChildByPath(u"tishi01:Label");
			if (pLabel) {
				CStdStringU czNum = g_pGameControl->GetTextU(pLabel);
				if (czNum.Find(u"2000/ 2000") >= 0) {
					m_bFinished = TRUE;
					return TRUE;
				}
			}

			CUE_Transform *pListTime = pBattleFieldWnd->GetChildByPath(u"bg:Panel:Grid");
			if (pListTime) {
				int iCount = pListTime->get_childCount();
				if (iCount != 0) {

					LOG_WRITE("iCount != 0.....");
					CUE_Transform *pChild0 = pListTime->GetChildByName(u"1");
					CUE_Transform *pChild1 = pListTime->GetChildByName(u"2");
					CUE_Transform *pChild2 = pListTime->GetChildByName(u"3");
					CheckTime(pChild0, pChild1);
					CheckTime(pChild1, pChild2);
					CheckTime(pChild2);
					return TRUE;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}


void CGSonCocDatLinh::CheckTime( CUE_Transform *p0, CUE_Transform *p1 /*= NULL*/ )
{
	if (!p0) return;
	CUE_Transform *pBaoDanh = p0->GetChildByPath(u"btn:Btnbaoming");
	CUE_Transform *pHuy = p0->GetChildByPath(u"btn:Btnquxiao");

	if (g_pGameControl->IsShowTransform(pHuy)) {
		return;
	}

	if (g_pGameControl->IsEnableButton(pBaoDanh)) g_pGameControl->Clicked(pBaoDanh);

}

int CGSonCocDatLinh::isFinished()
{
	if (m_bFinished) {
		if (g_pGameControl->IsShowPopUI()) g_pGameControl->CloseDialog();
		return FinishedActivity();
	}
	return m_nStatus;
}

BOOL CGSonCocDatLinh::IsInFb()
{
	if (g_pGameControl->IsButtonExitFuben()) {
		m_bCanjoin = TRUE;

		g_pGameControl->SwitchAutoFight(ON);

		if (m_iShowMap <= 0) {
			g_pGameControl->ShowMap();
		}

		if (!m_bShowMap) m_iShowMap ++;
		if (m_bShowMap) m_iShowMap = 1;
		return TRUE;
	}
	return FALSE;
}

BOOL CGSonCocDatLinh::IsMaple()
{
	static int i = 0;
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pWnd = p->GetChildByName(u"Map");
		if (g_pGameControl->IsShowTransform(pWnd)) {
			float x = g_pGameControl->m_renderWidthHalf;
			float y = g_pGameControl->m_renderHeightHalf;
			LOG_WRITE("x, y = [%.2f, %.2f]", x,y);
			m_bShowMap = TRUE;
			if (i <= 2) g_pGameControl->Tap(x, y);
			if (i > 2) { i = 0; g_pGameControl->CloseDialog();}
			i ++;
			return TRUE;
		}
	}
	return FALSE;
}



