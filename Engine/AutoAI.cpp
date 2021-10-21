#include "AutoAI.h"
#include "main.h"
//#include "GLogin.h"
CAutoAI::CAutoAI(void)
{
	m_pGame = g_pGame;
	m_bControl = FALSE;
}

CAutoAI::~CAutoAI(void)
{
	GetGoalSystem()->RemoveAllSubGoals();
}

CGoalSystem* CAutoAI::GetGoalSystem()
{
	return CGoalSystem::Instance(); 
}

//CTriggerTimer* CAutoAI::GetTriggerTimer()
//{
//	return CTriggerTimer::Instance();
//}

void CAutoAI::Update()
{	
	if (IsGameControlUnchecked()) return;

	GetGoalSystem()->Process();


	if (!m_pGame->m_bControl) return;

	m_TriggerActivity.Update();
}
BOOL CAutoAI::IsGameControlUnchecked()
{
	if (m_bControl != m_pGame->m_bControl){
		m_bControl = m_pGame->m_bControl;
		if (!m_bControl){
			LOG_WRITE("CAutoAI::IsGameControlUnchecked()...");
			GetGoalSystem()->RemoveAllSubGoals();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAutoAI::IsEmpty()
{
	return GetGoalSystem()->IsEmpty();
}
