#include "main.h"
#include "UEThread.h"

BOOL CUEThread::_isRunning = FALSE;


CUEThread::CUEThread(JNIEnv* env)
{	
	LOG_WRITE("CUEThread *** TID[%d] NEW ",gettid());
	m_pJNI			= new CJNIEnv(env);
	m_pGameControl	= new CGameControl();
	m_pAutoAI		= new CAutoAI();	
}

CUEThread::~CUEThread(void)
{	
	SAFE_DELETE(m_pAutoAI);
	SAFE_DELETE(m_pGameControl);
	SAFE_DELETE(m_pJNI);
	LOG_WRITE("CUEThread *** DEL ");
}


jlong CUEThread::GetTickCount()
{
	return m_pJNI->uptimeMillis();
}

CJUserInfo CUEThread::GetUserInfo()
{
	jobject o = m_pJNI->m_env->CallStaticObjectMethod(CJUserInfo::_jclass,CJUserInfo::_currentUserId);
	if (!o) return CJUserInfo(m_pJNI->m_env,NULL);
	return CJUserInfo(m_pJNI->m_env,o);
}

void CUEThread::Update()
{
	//LOG_WRITE("CUEThread::Update() ....[%lld]",GetTickCount());
	//if (!g_pGame->m_bControl) return;
	if(!g_pGameControl->InitUnity()) return;
	if(g_pGameControl->UpdateLoginState()) return;
	if (g_pGameControl->get_LoadingScene()) return;
	if (g_pGameControl->get_WaitForLoadAllBlock()) return;
	if (g_pGameControl->IsProcessing()) return;
	if (g_pGameControl->IsUILevelUpWnd()) return;
	if (g_pGameControl->IsYingFuPopup()) return;
	if (g_pGameControl->IsItem_qbzroot()) return;
	if (g_pGameControl->ProcessMessageBox(u"Kim Thân Niết Bàn?", MSG_OK)) return;
	
	m_pAutoAI->Update();
}


void CUEThread::_Runtime( JNIEnv* env, jobject self )
{
	_isRunning = TRUE;
	if (!g_pGame){
		SAFE_DELETE(g_pUEThread);
		_isRunning = FALSE;
		return;
	}
	if (g_pUEThread == NULL) g_pUEThread = new CUEThread(env);		
	g_pUEThread->Update();
	_isRunning = FALSE;
}

void CUEThread::_WaitFinished()
{
	while (_isRunning && g_pUEThread) usleep(100000); //100s
}

