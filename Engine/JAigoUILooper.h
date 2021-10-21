#pragma once
#include <Main/JObject.h>

class CJPathClassLoader;

class CJAigoUILooper : public CJObject
{
public:
	CJAigoUILooper(JNIEnv* env, jobject object);
	virtual ~CJAigoUILooper(void);
	static jclass			_jclass;
	static jmethodID		_initId;

	static void _Init(JNIEnv* env,CJPathClassLoader* oPathLoader);
	static void _Exit(JNIEnv* env);

	
};
