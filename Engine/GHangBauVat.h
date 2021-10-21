#pragma once
#include "GActivity.h"

class CGHangBauVat : public CGActivity
{
public:
	CGHangBauVat();
	virtual ~CGHangBauVat();

	int  Process();

	int processOutside();
	int processInside();
};

