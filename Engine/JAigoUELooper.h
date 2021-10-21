#pragma once
#include <JObject.h>

class CJPathClassLoader;

class CJAigoUELooper : public CJObject
{
public:
	CJAigoUELooper(JNIEnv* env, jobject object);
	virtual ~CJAigoUELooper(void);
	static jclass			_jclass;
	static jmethodID		_initId;

	static void _Init(JNIEnv* env,CJPathClassLoader* oPathLoader);
	static void _Exit(JNIEnv* env);

	
};
