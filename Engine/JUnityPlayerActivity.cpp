#include "main.h"
#include "JUnityPlayerActivity.h"

jclass CJUnityPlayerActivity::_jclass = 0;
jfieldID CJUnityPlayerActivity::_mUnityPlayerId = 0;

CJUnityPlayerActivity::CJUnityPlayerActivity(JNIEnv* env, jobject object, bool bGlobal):CJActivity(env,object,bGlobal)
{
}

CJUnityPlayerActivity::~CJUnityPlayerActivity(void)
{
}

void CJUnityPlayerActivity::_Init( JNIEnv* env,CJClassLoader* oAppLoader )
{
	if (_jclass != 0) return;
	CJUnityPlayer::_Init(env,oAppLoader);
	CJUserInfo::_Init(env,oAppLoader);
	CJSDKService::_Init(env, oAppLoader);
	//_jclass = (jclass)env->NewGlobalRef((jobject)oAppLoader->findClass("com/unity3d/player/UnityPlayerActivity"));
	_jclass = (jclass)env->NewGlobalRef((jobject)oAppLoader->findClass(TXT_GAME_MAINACTIVITY));
	_mUnityPlayerId = env->GetFieldID(_jclass,"mUnityPlayer","Lcom/unity3d/player/UnityPlayer;");
	LOG_WRITE(" [%p] CJUnityPlayerActivity::_mUnityPlayerId",_mUnityPlayerId);
}

void CJUnityPlayerActivity::_Exit( JNIEnv* env )
{
	if (_jclass == 0) return;	
	CJUnityPlayer::_Exit(env);
	CJUserInfo::_Exit(env);
	CJSDKService::_Exit(env);
	env->DeleteGlobalRef((jobject)_jclass); _jclass = 0;

}

jobject CJUnityPlayerActivity::GetUnityPlayer()
{
	return m_env->GetObjectField(m_object,_mUnityPlayerId);
}

