#pragma once
#include "GActivity.h"

class CGVanDapNgay : public CGActivity
{
public:
	CGVanDapNgay();
	virtual ~CGVanDapNgay();
	int  Process();
	BOOL IsExamWnd();
	BOOL IsFinished();
	void JoinExamDaily();
	BOOL m_bFinished;
	int m_iClicked;
};

