#pragma once
#include "GActivity.h"

class CGLoginServerChoose : public CGActivity
{
public:
	CGLoginServerChoose();
	virtual ~CGLoginServerChoose();
	int  Process();

	BOOL IsWrongAccount(CUE_Transform *pRoleChoose);
	BOOL EnterGame(CUE_Transform *pServerChoose);
	BOOL ChooseServer(CUE_Transform *pServerChoose);
	BOOL CloseNotice();
};

