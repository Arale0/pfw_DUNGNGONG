#pragma once
#include "GameInfo.h"
#include "GameClasses.h"

class CGameControl;

class CTriggerActivity
{
public:

	CTriggerActivity(void);
	~CTriggerActivity(void);

	static int	_lstGoalId[goal_LAST];

	BOOL	IsReady(DWORD dwMiliseconds = 1000);
	//add vao GoalSystem()
	BOOL	IsExistActivityGoal(int actId);			//GoalSystem()
	void	AddActivityGoal(int actId, CGoal* pG);	//GoalSystem()
	BOOL    AddActivityGoalIfNew(int actId);		//GoalSystem()


	void	Process_LoginGame();
	void	Update();
	BOOL	TeamProcess();
	BOOL	NeedTeamBuild();
	BOOL	Test();
	BOOL	UtilityProcess();
	BOOL	IsOptimizeCPU();
	BOOL	IsLackMana();

	void CheckTarget(CObj_MainPlayer *pPlayer, CUE_Transform *p);

protected:
	ULONGLONG		m_uTimeStarted;
	DWORD		m_dwTimeUtilityStarted;
	BOOL	m_bEnableAcitvity;
	int		m_iFPSDefault;
	BOOL	m_bSetFPS;
	DWORD	m_dwTimeResetFPS;
	DWORD	m_dwTimeFuliCheck;


};
