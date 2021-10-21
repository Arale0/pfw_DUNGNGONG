#pragma once
#include "GActivity.h"

class CGSonCocDatLinh : public CGActivity
{
public:
	CGSonCocDatLinh();
	virtual ~CGSonCocDatLinh();
	int  Process();

	void ShowBattleFieldWnd();
	BOOL IsBattleFieldWnd();
	void CheckTime(CUE_Transform *p0, CUE_Transform *p1 = NULL);
	int isFinished();
	BOOL IsInFb();
	BOOL IsMaple();

	BOOL m_bFinished;
	BOOL m_bCanjoin;
	BOOL m_bShowMap;
	int m_iShowMap;
};

