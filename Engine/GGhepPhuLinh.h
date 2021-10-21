#pragma once
#include "GActivity.h"

class CGGhepPhuLinh : public CGActivity
{
public:
	CGGhepPhuLinh();
	virtual ~CGGhepPhuLinh();
	int  Process();

	BOOL IsKnapsackWnd();
	BOOL IsQianKunDaiWnd();
	BOOL IsItemTipsWnd();
	BOOL IsNumericKeyBoard();
	BOOL IsHasSuccessItem(CQianKunDaiWindow *pInstance);
	void put_GameItem(CQianKunDaiWindow *pInstance);
	void showKnapsackWnd();

	int m_iCurrentItem;
	int m_iDelayShowKnapsack;
	BOOL m_bFinished;
};

