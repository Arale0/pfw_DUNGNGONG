#include "JNIEnvEx.h"
#include "main.h"


CJNIEnvEx::CJNIEnvEx(JNIEnv* env):CJNIEnv(env)
{	
	m_pAigoUELooper = NULL;
	m_pAigoUILooper = NULL;
	m_pHandler = NULL;
	m_pWndMgrGlobal = NULL;
	m_pActivity = NULL;
	m_pUnityPlayer = NULL;
	m_uiActivity = ACT_UI_None;
}

CJNIEnvEx::~CJNIEnvEx(void)
{
}

void CJNIEnvEx::Init()
{
	LOG_WRITE("CJNIEnvEx()::Init()");

	CStdString szDexAigor;
	szDexAigor.Fmt("/data/local/tmp/aigo/aigor.dex");
	if (!_PathFileExists(szDexAigor.c_str())){
		LOG_WRITE("NOT FOUND [AigoMain.dex]");	
		return;
	}
	LOG_WRITE("LOAD AIGOMAIN ****");
	jobject oSystemLoader = m_env->CallStaticObjectMethod(CJClassLoader::_jclass,CJClassLoader::_getSystemClassLoaderId);
	LOG_WRITE(" [%p] oSystemLoader",oSystemLoader);	
	jstring strDexPath = m_env->NewStringUTF(szDexAigor.c_str());
	jobject objPathClassLoader = m_env->NewObject(CJPathClassLoader::_jclass, CJPathClassLoader::_initId,strDexPath, oSystemLoader);

	LOG_WRITE(" [%p] objPathClassLoader",objPathClassLoader);
	CJPathClassLoader oPathAigoMain(m_env,objPathClassLoader);
	CJAigoUILooper::_Init(m_env,&oPathAigoMain);
	CJAigoUELooper::_Init(m_env,&oPathAigoMain);

	m_pAigoUILooper = new CJAigoUILooper(m_env,m_env->NewObject(CJAigoUILooper::_jclass,CJAigoUILooper::_initId,NULL));
	LOG_WRITE(" [%p] oAigoUILooper",m_pAigoUILooper->Get());	

	m_pAigoUELooper = new CJAigoUELooper(m_env,m_env->NewObject(CJAigoUELooper::_jclass,CJAigoUELooper::_initId,NULL));
	LOG_WRITE(" [%p] oAigoUELooper",m_pAigoUELooper->Get());	

	m_env->DeleteLocalRef(strDexPath);	
	remove(szDexAigor.c_str());

	LOG_WRITE("GET HANDLER MAINLOOPER ****");
	jobject oMainLooper = m_env->CallStaticObjectMethod(CJLooper::_jclass,CJLooper::_getMainLooperId);
	LOG_WRITE(" [%p] oMainLooper",oMainLooper);
	if (oMainLooper){
		m_pHandler = new CJHandler(m_env,m_env->NewObject(CJHandler::_jclass,CJHandler::_initId,oMainLooper));
		LOG_WRITE(" [%p] m_pHandler",m_pHandler->Get());
	}

	//
	LOG_WRITE("LOAD CLASS APPCLASSLOADER ****");
	CJActivityThread oActivityThread(m_env,currentActivityThread());
	CJContext		oApp(m_env,oActivityThread.getApplication());
	CJClassLoader	oAppLoader(m_env,oApp.getClassLoader());
	
	CJUnityPlayerActivity::_Init(m_env,&oAppLoader);
	jobject ocurrentActivity = m_env->GetStaticObjectField(CJUnityPlayer::_jclass,CJUnityPlayer::_currentActivityId);
	CJUnityPlayerActivity oCurrentActivity(m_env,ocurrentActivity);
	m_pUnityPlayer = new CJUnityPlayer(m_env,m_env->NewGlobalRef(oCurrentActivity.GetUnityPlayer()),true);
	LOG_WRITE(" [%p] m_pUnityPlayer",m_pUnityPlayer->Get());
	
	m_pActivity = new CJActivity(m_env,NULL,true);


	m_pWndMgrGlobal = new CJWindowManagerGlobal(m_env,m_env->NewGlobalRef(getWindowManagerGlobal()),true);
	//CJArrayList arrViews(m_env,m_pWndMgrGlobal->getViews());

	//CJViewGroup oFirstView = CJViewGroup(m_env,arrViews.get(0));

	//LOG_WRITE("REAL SCREEN SIZE (%d,%d)\[%s]",oFirstView.getWidth(),oFirstView.getHeight(),oFirstView.toJString().GetBuffer());
	//ShowViewInfo(m_env,oFirstView.Get());
	//LOG_WRITE("LAST VIEW");
	//ShowViewInfo(m_env,arrViews.get(arrViews.size() - 1));
	//ShowClassInfo(CJGameInfo::_jclass);

}

void CJNIEnvEx::Exit()
{
	LOG_WRITE("CJNIEnvEx::Exit() ****");

	if (g_pUIThread){			
		m_pHandler->removeCallbacks(m_pAigoUILooper->Get());
		CUIThread::_isRunning = FALSE;
		runUIThread();
		CUIThread::_WaitFinished();
	}
	if (g_pUEThread){
		m_pUnityPlayer->remJobs(m_pAigoUELooper->Get());
		SAFE_DELETE(g_pUEThread);
	}

	SAFE_DELETE(m_pAigoUELooper);
	SAFE_DELETE(m_pAigoUILooper);
	SAFE_DELETE(m_pHandler);
	SAFE_DELETE(m_pWndMgrGlobal);
	SAFE_DELETE(m_pActivity);
	SAFE_DELETE(m_pUnityPlayer);

	CJAigoUILooper::_Exit(m_env);
	CJAigoUELooper::_Exit(m_env);

	CJUnityPlayerActivity::_Exit(m_env);	
}

bool CJNIEnvEx::runUIThread()
{
	if (!m_pHandler || !m_pAigoUILooper || !m_pAigoUILooper->Get()) {
		LOG_WRITE("!m_pHandler || !m_pAigoUILooper || !m_pAigoUILooper->Get()");
		return false;
	}

	if (CUIThread::_isRunning) {
		LOG_WRITE("CUIThread::_isRunning %d", CUIThread::_isRunning);
		return false;
	}

	LOG_WRITE("ABC CUIThread::_isRunning %d", CUIThread::_isRunning);

	CUIThread::_isRunning = m_pHandler->post(m_pAigoUILooper->Get());
	return CUIThread::_isRunning;
}

bool CJNIEnvEx::runUEThread()
{
	if (!m_pUnityPlayer->Get()) return false;
	if (!m_pAigoUELooper || !m_pAigoUELooper->Get()) return false;
	if (CUEThread::_isRunning) return false;
	_theApp->m_bRunUEThread = m_pUnityPlayer->addJob(m_pAigoUELooper->Get());
	CUEThread::_isRunning = _theApp->m_bRunUEThread;
	return CUEThread::_isRunning;
}

int CJNIEnvEx::GetViewCount()
{
	if (!m_pWndMgrGlobal) return -1;
	CJArrayList arrViews(m_env,m_pWndMgrGlobal->getViews());
	return arrViews.size();
}

bool CJNIEnvEx::UpdateCurrentActivity()
{
	IsActivityChanged();
	CJActivityClientRecord* pActClient = GetActivityClientRecord();
	if (!pActClient){
		m_pActivity->Attach(NULL);
		m_uiActivity = ACT_UI_None; 		
		_theApp->NextTimer(1000);
		LOG_WRITE(" pActClient == NULL");
		return true;
	}
	BOOL bChanged = false;
	jobject oActivity = pActClient->activity();
	if (!m_pActivity->IsSameObject(oActivity)){
		m_pActivity->Attach(m_env->NewGlobalRef(oActivity));
		CStdString nameActvity = m_pActivity->toJString().GetBuffer();

		m_uiActivity = ACT_UI_Unkown;
		if (nameActvity.Find("vng.com.gtsdk.core.MainActivity") >= 0) m_uiActivity = ACT_UI_VNGActivity;
		else if (nameActvity.Find("com.zing.zalo.zalosdk.oauth.WebLoginActivity") >= 0) m_uiActivity = ACT_UI_ZaloActivity;
		else if (nameActvity.Find(TXT_GAME_MAINACTIVITY) >= 0) m_uiActivity = ACT_UI_MainActivity;

		if (m_uiActivity == ACT_UI_VNGActivity){

			g_pGame->ResetAccountInfo();

		}
		//com.wanmei.pwrdsdk_lib.ui.ActivityUserCenter
		_theApp->NextTimer(1000);
		LOG_WRITE(" **** [%d] ACTIVITY [%s]",m_uiActivity, nameActvity.c_str());
		bChanged = true;
	}

	m_env->DeleteLocalRef(oActivity);
	return bChanged;
}


void CJNIEnvEx::ShowClassInfo( jclass cClass )
{
	jclass oClass = (jclass) m_env->NewLocalRef((jobject)cClass);
	CJClass oUserInfo(m_env,oClass);
	jobjectArray oArr = oUserInfo.getDeclaredFields();
	int iLenField = m_env->GetArrayLength(oArr);
	LOG_WRITE("----FIELDS : %d",iLenField);
	CJObject oField(m_env,NULL);
	for ( int i = 0; i < iLenField; ++i)
	{
		oField.Attach(m_env->GetObjectArrayElement(oArr,i));
		LOG_WRITE(" + %d [%s]",i,oField.toJString().GetBuffer());
	}
	oArr = oUserInfo.getDeclaredMethods();
	int iLenMethod = m_env->GetArrayLength(oArr);
	LOG_WRITE("----METHODS : %d",iLenMethod);
	CJObject oMethod(m_env,NULL);
	for ( int i = 0; i < iLenMethod; ++i)
	{
		oMethod.Attach(m_env->GetObjectArrayElement(oArr,i));
		LOG_WRITE(" + %d [%s]",i,oMethod.toJString().GetBuffer());
	}	
}

void CJNIEnvEx::ShowViewInfo( JNIEnv* env,jobject oView )
{
	static CStdString _szSpace = "";

	if (!oView) return;
	CJViewGroup oVG(env,oView);	
	CStdString	szViewName = oVG.toJString().GetBuffer();
	if (!oVG.IsViewGroup())	
		LOG_WRITE("%s+ [%s]",_szSpace.c_str(),szViewName.c_str());
	else{
		int iChilds = oVG.getChildCount();
		LOG_WRITE("%s- [%s] CHILDS:%d",_szSpace.c_str(),szViewName.c_str(),iChilds);		
		for (int i = 0; i< iChilds; ++i)
		{
			jobject o = oVG.getChildAt(i);
			_szSpace += " ";
			ShowViewInfo(env,o);
			_szSpace.Delete(0);
		}
	}
}


void CJNIEnvEx::TerminateApp()
{
	LOG_WRITE("CJNIEnvEx::TerminateApp()..");
	m_env->CallStaticVoidMethod(CJSystem::_jclass,CJSystem::_exitId,-1);
}

