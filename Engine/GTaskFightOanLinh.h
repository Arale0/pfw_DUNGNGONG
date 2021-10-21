#pragma once
#include "GActivity.h"

class CGTaskFightOanLinh : public CGoalComposite
{
public:
	CGTaskFightOanLinh();
	virtual ~CGTaskFightOanLinh();	
	int  Process();

	int ProcessMainTask();
	int  LoopNextSleep(int delay = 1000);
	BOOL IsTask(CStdStringU czUNameTask);

	void ClickedSkillButton();
	void CheckCDSkill(CUE_Transform *p);
	void ClickedNormalSkill();

	BOOL m_bCheckTeam;
	BOOL m_bEquip;

};

