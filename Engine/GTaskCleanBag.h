#pragma once
#include "GActivity.h"

class CGTaskCleanBag : public CGoalComposite
{
public:
	CGTaskCleanBag();
	virtual ~CGTaskCleanBag();	
	int  Process();

	void ShowTaskCleanBagWnd();
	BOOL IsTaskCleanBagWnd();
	BOOL IsOverTime();
	int LoopNextSleep(int delay = 1000);
	BOOL IsFinished();
	BOOL IsDeposeBag(CUE_Transform *p);
	BOOL IsSellStone(CUE_Transform *p);
	BOOL IsProcessOptionBag(CUE_Transform *p = NULL);
	BOOL IsItemTips();
	BOOL IsEquipsTips();
	BOOL IsNumericKeyBoard();
	BOOL IsSellWnd();
	int get_ItemCount();
	BOOL IsItemPromt();
	BOOL IsCopyFinishedFubenWnd();

	void SelectOtherTab(CKnapsackWindow *pIns);
	void ProcessCleanBag(CKnapsackWindow *pIns);
	BOOL IsItem(CStdStringU czClassName, CStdStringU czName);
	BOOL IsItemUse();
	BOOL fairy_settlement();

	void ProcessEquipment(CKnapsackWindow *pIns);

	void ClickItem();
	void SetValue();

	void processIfYuanLingIsCheck(int iHour, int iMiute);

	BOOL m_bFinished;
	BOOL m_bDeposeEquip;
	int m_iTypeCleanBag;
	BOOL m_bSortItem;
	BOOL m_bFull;
	int m_iCurrentIndex;
	BOOL m_bBought;
	BOOL m_bSplitEquip;
	CStdStringU m_czTempItem;

};

