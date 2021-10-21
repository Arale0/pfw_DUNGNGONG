#pragma once
#include "GActivity.h"

class CGThuongThienPhatAc : public CGActivity
{
public:
	CGThuongThienPhatAc();
	virtual ~CGThuongThienPhatAc();
	int  Process();
	void Activate();
	void ShowActivityWnd();
	void DelayClickButtonHuoDong();
	BOOL IsNPCDialog();
	BOOL IsFinished();
	void processMember();
	void processLeader();
	void get_activity();
	void processAlone();
	void OnOffSettingWnd();

	UINT m_uActivity;
	BOOL m_bFinished;
	BOOL m_bClickButtonHuoDong;
	int m_iDelayClickedActivity;
	BOOL m_bJiebai;
};

