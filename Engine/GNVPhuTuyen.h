#pragma once
#include "GActivity.h"

#define TUCHAN 1
#define THAN 2
#define DU 3

class CGNVPhuTuyen : public CGActivity
{
public:
	CGNVPhuTuyen();
	virtual ~CGNVPhuTuyen();
	int  Process();
	void processActivity();
	BOOL IsAnswer();
	BOOL IsChooseLogic();
	
	void getActivity();

	void getMission(CStdStringU czType);

	UINT m_uActivity;
	int iDelay;
	BOOL m_bFinished;
	BOOL m_bFindQuetsDone;

	int m_iMission;



};

