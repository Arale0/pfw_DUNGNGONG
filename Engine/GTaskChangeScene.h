#pragma once
#include "GActivity.h"

class CGTaskChangeScene: public CGoalComposite
{
public:
	CGTaskChangeScene(int iSceneId);
	virtual ~CGTaskChangeScene();	
	int  Process();

	BOOL IsLackMana();
	int LoopNextSleep(int delay = 1000);
	BOOL IsFinished();
	int m_iSceneID;
};

