#include "main.h"
#include "JSDKService.h"


jclass CJSDKService::_jclass = 0;
jfieldID CJSDKService::_roleId = 0;
jfieldID CJSDKService::_roleLevel = 0;
jfieldID CJSDKService::_roleName = 0;
jfieldID CJSDKService::_roleinfo = 0;
jfieldID CJSDKService::_serverID = 0;
jfieldID CJSDKService::_serverName = 0;

CJSDKService::CJSDKService(JNIEnv* env, jobject object, bool bGlobal):CJObject(env,object,bGlobal)
{
}

CJSDKService::~CJSDKService(void)
{
}

void CJSDKService::_Init( JNIEnv* env,CJClassLoader* oAppLoader )
{
	if (_jclass != 0) return;
	
	LOG_WRITE("===>CJSDKService::_Init");

	_jclass = (jclass)env->NewGlobalRef((jobject)oAppLoader->findClass("com/wm/shh/zx/SDKService"));
	LOG_WRITE(" + [%p] CJSDKService::_jclass",_jclass);
	if (_jclass == 0) return;
	
	_roleName = env->GetStaticFieldID(_jclass,"roleName","Ljava/lang/String;");
	_serverID = env->GetStaticFieldID(_jclass,"serverID","Ljava/lang/String;");
	_serverName = env->GetStaticFieldID(_jclass,"serverName","Ljava/lang/String;");

	//LOG_WRITE(" + [%p] CJSDKService::_roleName",_roleName);
	//LOG_WRITE(" + [%p] CJSDKService::_serverID",_serverID);
	//LOG_WRITE(" + [%p] CJSDKService::_serverName",_serverName);
}

void CJSDKService::_Exit( JNIEnv* env )
{
	if (_jclass == 0) return;	
	
	env->DeleteGlobalRef((jobject)_jclass); _jclass = 0;

}
const char* CJSDKService::GetRoleId(JNIEnv* env)
{
	jobject o = env->GetStaticObjectField(_jclass,_roleId);
	if (o == NULL) return "";
	CJString oStr(env,o);
	return oStr.GetBuffer();
}
const char* CJSDKService::GetRoleLevel(JNIEnv* env)
{
	jobject o = env->GetStaticObjectField(_jclass,_roleLevel);
	if (o == NULL) return "";
	CJString oStr(env,o);
	return oStr.GetBuffer();
}

const char* CJSDKService::GetRoleName(JNIEnv* env)
{
	jobject o = env->GetStaticObjectField(_jclass,_roleName);
	if (o == NULL) return "";
	CJString oStr(env,o);
	return oStr.GetBuffer();
}
const char* CJSDKService::GetRoleinfo(JNIEnv* env)
{
	jobject o = env->GetStaticObjectField(_jclass,_roleinfo);
	if (o == NULL) return "";
	CJString oStr(env,o);
	return oStr.GetBuffer();
}
const char* CJSDKService::GetServerID(JNIEnv* env)
{
	jobject o = env->GetStaticObjectField(_jclass,_serverID);
	if (o == NULL) return "";
	CJString oStr(env,o);
	return oStr.GetBuffer();
}
const char* CJSDKService::GetServerName(JNIEnv* env)
{
	jobject o = env->GetStaticObjectField(_jclass,_serverName);
	if (o == NULL) return "";
	CJString oStr(env,o);
	return oStr.GetBuffer();
}