#pragma once
#include "../../__AIGGlobal/Androids/src/AI2/Goal.h"

class CGSleep : public CGoal
{
public:
	CGSleep(DWORD dwSleep = 1000);
	~CGSleep(void);
public:
	void	Activate();
	int		Process();
private:
	DWORD	m_dwSleep;
	DWORD	m_dwStart;
};
