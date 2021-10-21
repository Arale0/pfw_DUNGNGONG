#pragma once

#include <Main/JNIEnv.h>
#include "AutoAI.h"
#include "GameControl.h"
#include "JUserInfo.h"

class CUEThread
{
public:
	CUEThread(JNIEnv* env);
	~CUEThread(void);
	
	CJNIEnv*		m_pJNI;
	CAutoAI*		m_pAutoAI;
	CGameControl*	m_pGameControl;

	jlong			GetTickCount();


	CJUserInfo	GetUserInfo();

	void		Update();

	static BOOL _isRunning;	
	static void _Runtime(JNIEnv* env, jobject self);
	static void _WaitFinished();
	
};
