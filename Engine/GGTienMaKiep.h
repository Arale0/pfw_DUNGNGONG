#pragma once
#include "GActivity.h"

class CGGTienMaKiep : public CGActivity
{
public:
	CGGTienMaKiep();
	virtual ~CGGTienMaKiep();
	int  Process();
	void ProcessMain();
	int getTime(int iTypeTime = 0);

	int m_iClicked;
	int m_iState;
};

