#pragma once
#include <Main/JNIEnv.h>
#include "JAigoUILooper.h"
#include "JAigoUELooper.h"
#include "JUnityPlayerActivity.h"


typedef enum _UIActivity{
	ACT_UI_None = 0,
	ACT_UI_VNGActivity,
	ACT_UI_ZaloActivity,
	ACT_UI_MainActivity,
	ACT_UI_Unkown
}UIActivity;


class CJNIEnvEx : public CJNIEnv
{
public:
	CJNIEnvEx(JNIEnv* env);
	virtual ~CJNIEnvEx(void);

	CJAigoUELooper*	m_pAigoUELooper;
	CJAigoUILooper*	m_pAigoUILooper;
	CJHandler*		m_pHandler;
	CJWindowManagerGlobal*	m_pWndMgrGlobal;
	CJActivity*	m_pActivity;

	UIActivity		m_uiActivity;	
	CJUnityPlayer*	m_pUnityPlayer;

	void	Init();
	void	Exit();
	bool	runUIThread();
	bool	runUEThread();
	int		GetViewCount();
	bool	UpdateCurrentActivity();
	
	void	ShowClassInfo(jclass cClass);
	static 	void ShowViewInfo(JNIEnv* env,jobject oView);
	
	void	TerminateApp();
};
