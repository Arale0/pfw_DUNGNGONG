#include "main.h"
#include "MainHook.h"
#include <ModuleInfo.h>

pthread_mutex_t CMainHook::s_mutex = PTHREAD_MUTEX_INITIALIZER;;
int CMainHook::s_isFreeLibrary = 0;

CMainHook::CMainHook():CEThread()
{	
	m_pJNI = NULL;
	m_pEpoll = NULL;

	m_pGame = NULL;
	m_pMono = NULL;
	//m_pLua = NULL;
	//m_pGameControl  = NULL;
	//m_pAutoAI		= NULL;

	m_dwNextTimer = 100;	
	m_pUIThread = NULL;
	m_pUEThread = NULL;
	m_bRunUEThread = FALSE;
	m_dwWaitRunUEThread = 0;

}

CMainHook::~CMainHook(void)
{
}

void CMainHook::InitInstance()
{	
	LOG_WRITE("CMainHook::InitInstance()....TID");

	//Khoi tao Unity
	CIl2cpp *pIl = CIl2cpp::GetInstance();
	if (pIl) {
		m_pMono = (CIl2cppEx*)pIl;
		LOG_WRITE("CMainHook::InitInstance()....TID1");
		m_pMono->CreateEx();
	}
	
	LOG_WRITE("CMainHook::InitInstance()....TID2");

	m_pGame			= new CGameInfo();	
	LOG_WRITE("CMainHook::InitInstance()....TID3");

	m_pEpoll = new CMainEpoll();
	LOG_WRITE("CMainHook::InitInstance()....TID4");
	if (!m_pEpoll) return;

	m_pEpoll->Start();
	LOG_WRITE("CMainHook::InitInstance()....TID5");

	while (!m_pEpoll->m_pClient) usleep(100000);//100ms

	JNIEnv* env = NULL;
	_jvm->AttachCurrentThread(&env,NULL);
	
	LOG_WRITE("CMainHook::InitInstance(%p) ....",env);

	CJNIEnv::_Init(env);
	m_pJNI = new CJNIEnvEx(env);
	m_pJNI->Init();	
	
	LOG_WRITE("***WAITING CMainHook::Run() ....");
	//m_pGame->SetPublisherAccount("paladin7610", "yuH191286");
	//m_pGame->SetRoleLogin(5,0,"");
	NextTimer(1000);
}

void CMainHook::ExitInstance()
{	
	LOG_WRITE("CMainHook::ExitInstance()....");

	CUEThread::_WaitFinished();
	CUIThread::_WaitFinished();

	SAFE_DELETE(m_pGame);

	if (m_pJNI){
		
		m_pJNI->Exit();
		CJNIEnv::_Exit(m_pJNI->m_env);
		SAFE_DELETE(m_pJNI);		
	}

	//SAFE_DELETE(m_pAutoAI);
	//SAFE_DELETE(m_pGameControl);

	CIl2cpp::DeInitialize();
	//CToLua::DeInitialize();
	_jvm->DetachCurrentThread();


	if (m_pEpoll) m_pEpoll->Exit();
	SAFE_DELETE(m_pEpoll);	
	//LOG_WRITE("CMainHook::ExitInstance()");
}

void CMainHook::Run()
{
	if (!m_pEpoll->Process_Networking()) return;
	
	if (!m_pEpoll->IsAuthentication()) return;

	if (!IsNextTimer()) return;
	int iViewCount = m_pJNI->GetViewCount();
	if (iViewCount > 1){
		if (m_pJNI->UpdateCurrentActivity()) return;
		NextTimer(1000);
		if (g_pGame->m_bControl) {
			LOG_WRITE("m_pJNI->runUIThread().........000000.....................%d", m_pJNI->runUIThread());
			CUIThread::_isRunning = FALSE;
			m_pJNI->runUIThread();
		}
		else {
			LOG_WRITE("COUNT VIEWS[%d] ... [%lld]",iViewCount,m_pJNI->uptimeMillis());
			return;
		}
		return;
	}
	//LOG_WRITE("PROCESS AUTO - UNITY [%p]g_pGameControl.....[%lld]",g_pGameControl,m_pJNI->uptimeMillis());	
	m_pJNI->runUEThread();	
	
	//aigo_fix
	//LOG_WRITE("m_bRunUEThread:%d",m_bRunUEThread);
	//if(!m_bRunUEThread){
	//	// thoat
	//	LOG_WRITE("WAIT RUN UE THREAD");
	//	if(!IsWaitRunUEThread()){
	//		LOG_WRITE("CMainHook::Run()    GAME DA DUNG LAI!!!!!!!!!!");
	//		m_pEpoll->Sync_StopGame();

	//	}

	//}else m_dwWaitRunUEThread = 0;
}


BOOL CMainHook::ProcessControl()
{//mat ket noi se tu dong noi lai den auto
	if (_pShared->typeControl == TYPE_CONTROL_NONE) return FALSE;

	switch (_pShared->typeControl){
		case TYPE_CONTROL_AIGOENTRY:
			_pShared->typeControl = TYPE_CONTROL_WAITCONNECT;
			m_pEpoll->ConnectServer(&_pShared->aigoEntry);			
			return TRUE;
		case TYPE_CONTROL_WAITCONNECT:{
			ULONGLONG uTime = _GetTickCount();
			if (uTime - m_pEpoll->m_pClient->GetTTL() > 10000){
				LOG_WRITE("ProcessControl() TYPE_CONTROL_WAITCONNECT > 10s => RECONECT"); 
				m_pEpoll->Del(m_pEpoll->m_pClient);
				_pShared->typeControl = TYPE_CONTROL_NONE;
				return TRUE;
			}

			LOG_WRITE("ProcessControl()...TYPE_CONTROL_WAITCONNECT [%lld]",_GetTickCount());
			NextDelay(1000);
									  }

									  return TRUE;
		case TYPE_CONTROL_UNHOOK:
			_theApp->FreeLibraryAndExitThread();
			_pShared->typeControl = TYPE_CONTROL_NONE;
			return TRUE;

		default:
			break;
	}
	_pShared->typeControl = TYPE_CONTROL_NONE;
	return FALSE;
}

void CMainHook::NextTimer( jlong dwDelay)
{
	m_dwNextTimer = dwDelay;
}

void CMainHook::ResetHookState()
{
	g_pAutoAI->GetGoalSystem()->RemoveAllSubGoals();
	m_pGame->ResetHookState();
}

#pragma region PROCESS_UNLOAD_HOOK
void CMainHook::_UnloadLibrary()
{
	if (!_theApp) return;
	s_isFreeLibrary = 1;
	pthread_mutex_lock(&s_mutex);
	pthread_mutex_unlock(&s_mutex);	
	pthread_mutex_destroy(&s_mutex);
	s_mutex = PTHREAD_MUTEX_INITIALIZER;
	SAFE_DELETE(_theApp);
}


void CMainHook::DumpHex( BYTE* pAddress, int iSize )
{
	if (!pAddress || iSize <= 0){
		LOG_WRITE("DumpHex() FAILED! pAddress:[%p] iSize:%d",pAddress,iSize);
		return;
	}
	int k = 0;
	CStdString s,st,szByte,szAddress,szValue;
	s.Fmt("%p  ", pAddress);
	for (int i = 0; i < iSize; i++)
	{
		szByte.Fmt("%02X ",pAddress[i]);
		if (pAddress[i] >= 32 && pAddress[i] < 127) szValue.Fmt("%c", pAddress[i]);
		else szValue = ".";
		st += szValue;
		if ((i + 1) % 16 == 0) {
			++k;
			szAddress.Fmt("%p  ", pAddress + k * 16);
			s = s + szByte + "  " + st + "\n" + szAddress;
			st = "";
		}
		else s += szByte;
	}
	if (st.IsEmpty()) LOG_WRITE(s.c_str());
	else{
		LOG_WRITE(CStdString(s + st).c_str());
	}
}

BOOL CMainHook::IsNextTimer()
{
	static jlong dwStart = 0;
	jlong dwTimer = m_pJNI->uptimeMillis();
	if (dwTimer - dwStart < m_dwNextTimer) return FALSE;
	dwStart = dwTimer;
	m_dwNextTimer = 100;
	return TRUE;
}

void CMainHook::FreeLibraryAndExitThread()
{
	LOG_WRITE("***** FreeLibraryAndExitThread()");
	pthread_t uTid;
	pthread_attr_t tAttr;	
	pthread_attr_init(&tAttr);
	pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
	pthread_create(&uTid,&tAttr,_FreeLibraryAndExitThread,NULL);	

}

void* CMainHook::_FreeLibraryAndExitThread( void* lpData )
{
	if (!_theApp) return NULL;
	_theApp->Exit();
	_ExitParametes();

	s_mutex = PTHREAD_MUTEX_INITIALIZER;
	s_isFreeLibrary = 0;
	pthread_mutex_lock(&s_mutex);
	pthread_t uTID;
	pthread_attr_t tAttr;		
	pthread_attr_init(&tAttr);
	pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);

	while (!s_isFreeLibrary){
		pthread_create(&uTID, &tAttr, (void *(*)(void *))dlclose, _hModule);
		usleep(100000); //100ms
	}
	pthread_mutex_unlock(&s_mutex);
	return NULL;
}

BOOL CMainHook::IsWaitRunUEThread()
{
	jlong dwTimer = m_pJNI->uptimeMillis();
	if(m_dwWaitRunUEThread == 0){
		m_dwWaitRunUEThread = dwTimer;
		return TRUE;
	}

	if (dwTimer - m_dwWaitRunUEThread > 2*60*1000) return FALSE;
	m_dwWaitRunUEThread = dwTimer;
	return TRUE;
}

#pragma endregion

