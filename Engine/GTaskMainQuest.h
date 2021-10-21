#pragma once
#include "GActivity.h"

class CGTaskMainQuest : public CGoalComposite
{
public:
	CGTaskMainQuest();
	virtual ~CGTaskMainQuest();	
	int  Process();

	int ProcessMainTask();
	int  LoopNextSleep(int delay = 1000);
	BOOL IsStoryUIRoot();
	BOOL IsMessageUIRoot();
	BOOL IsDeathUI();
	BOOL IsMessageBox();
	BOOL IsTask(CStdStringU czUNameTask);
	BOOL IsMagicEraser();
	BOOL IsItemPromptSkillLogic();
	BOOL IsFilterChoose();
	BOOL IsPickUpBtn();
	BOOL IsPrompt_xinshouben();
	BOOL IsAnswer();
	BOOL IsSynopsisselect();
	BOOL IsFriend();

	void ClickedSkillButton();
	void CheckCDSkill(CUE_Transform *p);
	void ClickedNormalSkill();
	void processSecondQuest();
	int processTask();

	BOOL m_bCheckTeam;
	BOOL m_bEquip;
	CStdStringU m_czTemp;
	int m_iDelayClicked;
	UINT m_uTemp;
};

