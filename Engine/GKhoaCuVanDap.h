#pragma once
#include "GActivity.h"

class CGKhoaCuVanDap : public CGActivity
{
public:
	CGKhoaCuVanDap();
	virtual ~CGKhoaCuVanDap();
	int  Process();
	BOOL IsExamWnd();
	BOOL IsFinished();
	void JoinExamDaily();
	BOOL IsExamTypeWnd();
	BOOL m_bFinished;
	int m_iClicked;
};

