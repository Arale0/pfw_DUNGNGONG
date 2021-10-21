#pragma once
#include "GActivity.h"

class CGTruongLaoTuTien : public CGActivity
{
public:
	CGTruongLaoTuTien();
	virtual ~CGTruongLaoTuTien();
	int  Process();

	void GoBackGuildScene();
	BOOL IsGuildScene();
	BOOL IsNPCDialog();
	void ProcessGuildScene();
	BOOL IsGuildThiefResult();
	BOOL IsGuildMap();

	int m_iDelayClick;
	BOOL m_bGoGuild	;
	BOOL m_bFinished;
	BOOL m_bShowMap;
	int m_iClickedNPC;
	BOOL m_bJiebai;
};

