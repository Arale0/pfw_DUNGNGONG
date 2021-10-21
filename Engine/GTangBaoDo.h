#pragma once
#include "GActivity.h"

class CGTangBaoDo : public CGActivity
{
public:
	CGTangBaoDo();
	virtual ~CGTangBaoDo();
	int  Process();
	BOOL IsBagWnd();
	void ShowBag();
	BOOL IsFinished();
	BOOL IsNumericKeyBoard();
	BOOL IsItemTips();
	void UseItemTips(CUE_Transform *p);
	int get_ItemCount();
	void SortItem();
	BOOL IsPicking();
	BOOL IsPickUpBtn();

	void SelectOtherTab(CKnapsackWindow *pIns);

	BOOL m_bFinished;
	int m_iDelayClicked;
	BOOL m_bSortItem;
	BOOL m_bTBDCao;
	BOOL m_bTBDTrung;
	int m_iSTT;
};

