#include "main.h"
#include "JUserInfo.h"


jclass CJUserInfo::_jclass = 0;
jmethodID CJUserInfo::_currentUserId = 0;

jfieldID CJUserInfo::_typeId = 0;
jfieldID CJUserInfo::_displayNameId = 0;
jfieldID CJUserInfo::_userIdId = 0;
jfieldID CJUserInfo::_emailId = 0;
jfieldID CJUserInfo::_socialIdId = 0;

CJUserInfo::CJUserInfo(JNIEnv* env, jobject object, bool bGlobal):CJObject(env,object,bGlobal)
{
}

CJUserInfo::~CJUserInfo(void)
{
}

void CJUserInfo::_Init( JNIEnv* env,CJClassLoader* oAppLoader )
{
	if (_jclass != 0) return;
	
	//LOG_WRITE("===>CJUserInfo::_Init");

	_jclass = (jclass)env->NewGlobalRef((jobject)oAppLoader->findClass("vng/com/gtsdk/core/model/UserInfo"));
	_currentUserId = env->GetStaticMethodID(_jclass,"currentUser","()Lvng/com/gtsdk/core/model/UserInfo;");
	_typeId = env->GetFieldID(_jclass,"type","I");
	_displayNameId = env->GetFieldID(_jclass,"displayName","Ljava/lang/String;");

	//LOG_WRITE(" + [%p] CJUserInfo::currentUser()",_currentUserId);
	//LOG_WRITE(" + [%p] CJUserInfo::_typeId",_typeId);
	//LOG_WRITE(" + [%p] CJUserInfo::_displayNameId",_displayNameId)
}

void CJUserInfo::_Exit( JNIEnv* env )
{
	if (_jclass == 0) return;	
	
	env->DeleteGlobalRef((jobject)_jclass); _jclass = 0;

}

int CJUserInfo::GetType()
{
	return m_env->GetIntField(m_object,_typeId);
}

const char* CJUserInfo::GetDisplayName()
{
	jobject o = m_env->GetObjectField(m_object,_displayNameId);
	if (o == NULL) return "";
	CJString oStr(m_env,o);
	return oStr.GetBuffer();
}

const char* CJUserInfo::GetUserID()
{
	jobject o = m_env->GetObjectField(m_object,_userIdId);
	if (o == NULL) return "";
	CJString oStr(m_env,o);
	return oStr.GetBuffer();
}

const char* CJUserInfo::GetEmail()
{
	jobject o = m_env->GetObjectField(m_object,_emailId);
	if (o == NULL) return "";
	CJString oStr(m_env,o);
	return oStr.GetBuffer();
}

const char* CJUserInfo::GetSocialId()
{
	jobject o = m_env->GetObjectField(m_object,_socialIdId);
	if (o == NULL) return "";
	CJString oStr(m_env,o);
	return oStr.GetBuffer();
}
