#pragma once
#include "GActivity.h"

class CGVanTieuBang : public CGActivity
{
public:
	CGVanTieuBang();
	virtual ~CGVanTieuBang();
	int  Process();


	BOOL IsFinished();
	BOOL IsActivityWnd();
	BOOL IsGuildConvoyWnd();
	BOOL IsNPCDialog();
	void ShowActivityWnd();
	BOOL IsActivity();
	BOOL IsGuildScene();
	BOOL IsPickUpBtn();
	void ProcessGuildConvoy();
	void GoBackGuildScene();
	BOOL IsMember();
	void processAlone();
	void OnClickGuildConvoy(CObj_MainPlayer *pMainPlayer);

	BOOL m_bShowActivityWnd;
	UINT m_uActivity;
	BOOL m_bFinished;
	BOOL m_iDelayClicked;
	BOOL m_bGoGuild;
	BOOL m_bClickRandom;
	BOOL m_bMemberConfirm;
	BOOL m_bJiebai;
	int  m_iClickedNPC;
	BOOL m_bApTieu;
	CObj_Char *m_pTieuXA;
};

