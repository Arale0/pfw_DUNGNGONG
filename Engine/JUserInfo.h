#pragma once
#include <Main/JObject.h>


class CJClassLoader;

class CJUserInfo : public CJObject
{
public:
	CJUserInfo(JNIEnv* env, jobject object, bool bGlobal = false);
	virtual ~CJUserInfo(void);
	static jclass			_jclass;
	static jmethodID		_currentUserId;
	static jfieldID			_typeId;
	static jfieldID			_displayNameId;
	static jfieldID			_userIdId;
	static jfieldID			_emailId;
	static jfieldID			_socialIdId;


	static void _Init(JNIEnv* env,CJClassLoader* oAppLoader);
	static void _Exit(JNIEnv* env);

	int				GetType();
	const char*		GetDisplayName();
	const char*		GetUserID();
	const char*		GetEmail();
	const char*		GetSocialId();
};
