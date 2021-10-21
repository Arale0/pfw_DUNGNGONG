#pragma once
#include "GActivity.h"

class CGKepGiayDoiBietThu : public CGActivity
{
public:
	CGKepGiayDoiBietThu();
	virtual ~CGKepGiayDoiBietThu();
	int  Process();
	void Activate();
	int	ProcessActivity();
	void ClickButtonHuodong();
	int IsFinished();
	void CheckCleanBag();
	BOOL IsActivity();
	void CheckMap();
	void Other();

	BOOL m_bFinished;
	BOOL m_bClickHuoDong;
	UINT m_uActivity;
	int	m_iDelayClicked;
	CUE_Transform *m_pActivity;
	int m_iTemp;

	DWORD m_dwStartTime;
};

