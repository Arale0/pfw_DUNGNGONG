#pragma once
#include "GActivity.h"

class CGTaskBuyPatch : public CGoalComposite
{
public:
	CGTaskBuyPatch();
	virtual ~CGTaskBuyPatch();	
	int  Process();

	BOOL IsLackMana();
	int LoopNextSleep(int delay = 1000);
	BOOL IsFinished();
	BOOL IsRoleviewReserve();
	BOOL IsShopWnd();
	BOOL IsSystemShopWindow();
	BOOL IsBought();
	BOOL IsStallMenu();
	BOOL IsPopup_Goumai();
	void ConvertNumber(int iSource);
	void get_PatchNameByLevel();
	BOOL OnClickFood(CUE_Transform *pParent);

	int m_iRealNumber;
	BOOL m_bFinished;
	BOOL m_bHPLack;
	BOOL m_bMPLack;
	BOOL m_bNotHpPatch;
	BOOL m_bNotMpPacth;
	BOOL m_bBought;
	int m_iMinPrice;
	int m_iPositionPrice;
	int m_iBuyPlace;
	BOOL m_bSelectedFood;
	CStdStringU m_czNameTemp;
};

