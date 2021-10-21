#pragma once
#include "GActivity.h"

class CGLoginRoleChoose : public CGActivity
{
public:
	CGLoginRoleChoose();
	virtual ~CGLoginRoleChoose();
	int  Process();
	BOOL IsWrongAccount(CUE_Transform *pServerChoose);
	BOOL EnterGame(CUE_Transform *pServerChoose);
	BOOL ChooseRole(CUE_Transform* pRoleChoose);
};

