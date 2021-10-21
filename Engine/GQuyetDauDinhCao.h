#pragma once
#include "GActivity.h"

class CGQuyetDauDinhCao : public CGActivity
{
public:
	CGQuyetDauDinhCao();
	virtual ~CGQuyetDauDinhCao();
	int  Process();
	void Activate();

	BOOL IsFinished();
	BOOL IsAsynPVP();
	BOOL IsResultWnd();
	void ShowAsynPVPWnd();
	void Fight(CUE_Transform* p);
	void Test();
	BOOL IsInFb();

	BOOL m_bFinished;
	BOOL m_bShowAsynWnd;
	int m_iDelay;
};

