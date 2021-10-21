#pragma once
#include "GActivity.h"

class CGNVBang : public CGActivity
{
public:
	CGNVBang();
	virtual ~CGNVBang();
	int  Process();
	void Activate();
	int	 ProcessNVBang();
	BOOL IsGuildFrame();
	BOOL IsCopyFinishedFubenWnd();
	void JoinGuildMap();
	void get_GuildMission();
	void other();
	BOOL IsFinished();
	BOOL IsMissionTrack();
	BOOL IsNPCTalk(CStdStringU czContent);
	void CheckCleanBag();
	void GoBackGuildScene();

	BOOL IsGuildScene();
	BOOL IsGuildMap();
	void CheckMap();

	BOOL m_bClickedButtonHuoDong;
	UINT m_uActivity;
	BOOL m_bFinished;
	BOOL m_iDelayClick;
	BOOL m_bGoGuild;
	CUE_Transform *m_pTransform;
	int m_iTemp;

	DWORD m_dwStartTime;
};

