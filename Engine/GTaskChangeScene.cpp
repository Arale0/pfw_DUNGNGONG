#include "main.h"
#include "GTaskChangeScene.h"
#include "GSleep.h"

CGTaskChangeScene::CGTaskChangeScene(int iSceneId) :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskTaskChangeScene()");
	m_iSceneID = iSceneId;
}

CGTaskChangeScene::~CGTaskChangeScene()
{
	LOG_WRITE("DEL - CGTaskTaskChangeScene()");
	g_pGame->m_iCurrentID = -1;

}

int CGTaskChangeScene::Process()
{

	g_pGameControl->SetCurrentID(102);
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	LOG_WRITE("CGTaskChangeScene::Process()");
	
	if (CGameManager::m_RunningScene() == m_iSceneID) {
		LOG_WRITE("Yesssssssssssssssssss");
		return Finished();
	}

	if (g_pGameControl->ProcessMessageBox(u"Truyền tống đến", MSG_OK)) { return LoopNextSleep(4000); }

	g_pGameControl->ChangeScene(m_iSceneID);

	return LoopNextSleep();
}

int CGTaskChangeScene::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);
	return LoopNext();
}

BOOL CGTaskChangeScene::IsFinished()
{	
	

	return FALSE;
}
