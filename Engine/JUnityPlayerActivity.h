#pragma once
#include <Main/JActivity.h>
#include <Main/JUnityPlayer.h>
#include "JUserInfo.h"
#include "JSDKService.h"
class CJClassLoader;

class CJUnityPlayerActivity : public CJActivity
{
public:
	CJUnityPlayerActivity(JNIEnv* env, jobject object, bool bGlobal = false);
	virtual ~CJUnityPlayerActivity(void);
	static jclass			_jclass;
	static jfieldID			_mUnityPlayerId;

	static void _Init(JNIEnv* env,CJClassLoader* oAppLoader);
	static void _Exit(JNIEnv* env);

	jobject		GetUnityPlayer();

};
