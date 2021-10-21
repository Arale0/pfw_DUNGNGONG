#include "main.h"
#include "GSleep.h"

CGSleep::CGSleep(DWORD dwSleep)
{
	m_dwSleep = dwSleep;
}

CGSleep::~CGSleep(void)
{
}

void CGSleep::Activate()
{
	m_nStatus = ACTIVE;
	m_dwStart = (DWORD)g_pUEThread->GetTickCount();
}

int CGSleep::Process()
{
	DWORD dwTime = (DWORD)g_pUEThread->GetTickCount();
	if (dwTime - m_dwStart < m_dwSleep) return m_nStatus;
	m_nStatus = COMPLETED;
	return m_nStatus;
}
