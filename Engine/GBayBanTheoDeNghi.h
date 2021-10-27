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
	BOOL m_bTradeTBD;
	BOOL m_bTradeTCT;
	BOOL m_bTradeEquips;
	BOOL m_bTradeTinhLinh;
	BOOL m_bTradeBiKip;

	CStdStringU m_czItemName;
	CStdStringU m_czTangBaoDo;
	CStdStringU m_czThienCoTai;
	CStdStringU m_czTinhLinh;
	CStdStringU m_czBiKip;
	CStdStringU m_czTrangBi;
};

