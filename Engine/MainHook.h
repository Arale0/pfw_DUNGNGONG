#pragma once
#include <EThread.h>

#include <Base64Url.h>

//#include "../Common/global_android.h"
#include "MainEpoll.h"

#include "GameInfo.h"
#include "JNIEnvEx.h"
#include "Il2cppEx.h"
#include "UIThread.h"
#include "UEThread.h"
//#include "ToLuaEx.h"

#define g_pGame			_theApp->m_pGame
#define g_pMono			_theApp->m_pMono
#define g_pNetwork		_theApp->m_pEpoll
#define g_pUIThread		_theApp->m_pUIThread
#define g_pUEThread		_theApp->m_pUEThread
#define g_pAutoAI		g_pUEThread->m_pAutoAI
#define g_pGameControl  g_pUEThread->m_pGameControl

class CMainHook : public CEThread
{
public:
	friend class CMainEpoll;

	CMainHook();
	virtual ~CMainHook(void);

	CMainEpoll*	m_pEpoll;		
	CJNIEnvEx*	m_pJNI;

	CStdString		m_szPathLibrary;

	CGameInfo*		m_pGame;

	CIl2cppEx*		m_pMono;	
	CUIThread*		m_pUIThread;
	CUEThread*		m_pUEThread;

	jlong			m_dwNextTimer;
	void			NextTimer(jlong dwDelay = 200);
	void			ResetHookState();

	static  void	_UnloadLibrary();
	static  void	DumpHex(BYTE* pAddress, int iSize);
	BOOL			m_bRunUEThread;	
	jlong			m_dwWaitRunUEThread;
	BOOL			IsWaitRunUEThread();

	//CToLuaEx*		m_pLua;
protected:	
	BOOL			IsNextTimer();	

#pragma region PROCESS_SYSTEM_HOOK
	virtual void	InitInstance();
	virtual void	ExitInstance();
	virtual void	Run();	

	BOOL			ProcessControl();
	void			FreeLibraryAndExitThread();
	static void*	_FreeLibraryAndExitThread( void* lpData );

	static pthread_mutex_t  s_mutex;
	static int				s_isFreeLibrary;
#pragma endregion
};
