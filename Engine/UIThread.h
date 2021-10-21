#pragma once

#include <Main/JNIEnv.h>
#include "JUserInfo.h"
#define RCID_MAINVIEW		0x7F0800D1
#define RCID_MAINVIEW_1		0x7f0800d0
#define RCID_TITLE			0x7f0800c2
#define RCID_TITLE_1		0x7f0800c3
#define RCID_CONTENT		0x7F080079 //7f080079
#define RCID_CONTENT_1		0x7F08007A
#define RCID_IDCONTAINER	0x7f08009e//9e
#define RCID_IDCONTAINER_1	0x7f08009f//9e
#define RCID_USER			0x7f080151
#define RCID_USER_1			0x7f080152
#define RCID_PASS			0x7f080155
#define RCID_PASS_1			0x7f080156
#define RCID_LOGIN			0x7f08004a
#define RCID_MESSAGE		0x7f0800be
#define RCID_VIEWBUTTON		0x7f080167
#define	RCID_TVBACK			0x7f08014f
class CUIThread
{
public:
	CUIThread(JNIEnv* env);
	~CUIThread(void);
	
	CJNIEnv*	m_pJNI;
	CJActivity*	m_pActivity;

	CJUserInfo		GetUserInfo();

	void		Process_ZingLogin();
	void		Process_MessageBox();
	void		Update();
	void		process_LoginByID(int iMainView, int iTitle, int iContent, int iContainer, int iUser, int iPass);

	static BOOL _isRunning;	
	static void _Runtime(JNIEnv* env, jobject self);
	static void _WaitFinished();
};
