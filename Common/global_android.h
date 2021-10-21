#pragma once
#include "global.h"

#define TXT_GAME_MAINACTIVITY	"com.wanmei.pwim.UnityPlayerActivity"

enum GoalId{
	goal_UILoginServer = actex_LAST + 1,
	goal_UILoginRole,
	goal_TeamBuild,
	goal_Fuli,
	goal_Mail,
	goal_Achievement,
	goal_cdTuChan,
	goal_Bag,
	goal_buyPatch,
	goal_LAST
};


typedef struct _RUNTIME_INFO{
	int			iRoleLevel;		
	float		posX;
	float		posY;
	BOOL		isMoving;
}RUNTIME_INFO;	//1s update 1 lan