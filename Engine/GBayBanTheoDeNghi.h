#pragma once
#include "GActivity.h"

class CGBayBanTheoDeNghi : public CGActivity
{
public:
	CGBayBanTheoDeNghi();
	virtual ~CGBayBanTheoDeNghi();
	int  Process();
	BOOL isShopWnd();
	BOOL isStallMenu(CUE_Transform *p);
	BOOL isStallSell();
	BOOL isStallSellMultiConfirm();
	BOOL isStallSellSingleConfirm();
	BOOL isTradeTooMany(CStdStringU czName);
	void CheckCost();
	void ClickShop();
	void SellItemWithPercent(int idx, int iItemPercent, BOOL isEquip = FALSE);

	int m_iClicked;
	int m_iNumSell;
	BOOL m_bFinished;
	CStdStringU m_czTBD;
	CStdStringU m_czTCT;
	CStdStringU m_czItemName;
	BOOL m_bTradeTBD;
	BOOL m_bTradeTCT;

};

