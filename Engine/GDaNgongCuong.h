#pragma once
#include "GActivity.h"

class CGDaNgongCuong : public CGActivity
{
public:
	CGDaNgongCuong();
	virtual ~CGDaNgongCuong();
	int  Process();
	void Activate();

	BOOL IsNPCDialog();
	BOOL IsGuildScene();
	BOOL IsGuildMap();
	BOOL IsUIJianMu();
	BOOL IsItemTips();
	BOOL IsShopWnd();
	BOOL IsStallBuyWnd();
	BOOL IsSystemShopWindow();
	BOOL IsFinished();
	BOOL IsFirmBuy();
	BOOL IsBought();
	void GoBackGuildScene();
	BOOL checkOptionControl();
	void setBuyData();

	int m_iDelayClick;
	int m_iItem;
	int m_iMinMoney;
	int m_iNeedItemCount;
	BOOL m_bGoGuild;
	BOOL m_bBought;
	BOOL m_bFinished;
	BOOL m_bSelected;
	CUE_Transform *m_pSelectItem;
	CStdStringU m_czSelectItem;
};

