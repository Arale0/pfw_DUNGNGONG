#pragma once
#include "GActivity.h"

class CGMainQuest : public CGActivity
{
public:
	CGMainQuest();
	virtual ~CGMainQuest();
	int  Process();
	void Activate();

	BOOL ClickQuest();
	CStdString	m_szTitle;
};

