#pragma once
#include <Main/JObject.h>


class CJClassLoader;

class CJSDKService : public CJObject
{
public:
	CJSDKService(JNIEnv* env, jobject object, bool bGlobal = false);
	virtual ~CJSDKService(void);
	static jclass			_jclass;
	static jfieldID			_roleId;
	static jfieldID			_roleLevel;
	static jfieldID			_roleName;
	static jfieldID			_roleinfo;
	static jfieldID			_serverID;
	static jfieldID			_serverName;

	static void _Init(JNIEnv* env,CJClassLoader* oAppLoader);
	static void _Exit(JNIEnv* env);

	static const char* GetRoleId(JNIEnv* env);
	static const char* GetRoleLevel(JNIEnv* env);
	static const char* GetRoleName(JNIEnv* env);
	static const char* GetRoleinfo(JNIEnv* env);
	static const char* GetServerID(JNIEnv* env);
	static const char* GetServerName(JNIEnv* env);
};
