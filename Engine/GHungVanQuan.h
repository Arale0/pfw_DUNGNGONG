#pragma once
#include "GActivity.h"

class CGHungVanQuan : public CGActivity
{
public:
	CGHungVanQuan();
	virtual ~CGHungVanQuan();
	int  Process();
	BOOL IsResult();
	BOOL IsGuildScene();
	void BackGuildScene();

	BOOL m_bFinished;

};

