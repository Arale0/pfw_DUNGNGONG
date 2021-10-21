#include "main.h"
#include "UIThread.h"

BOOL CUIThread::_isRunning = FALSE;

CUIThread::CUIThread(JNIEnv* env)
{
	//m_env = env;
	m_pJNI = new CJNIEnv(env);
	m_pActivity = new CJActivity(env,NULL,true);
	LOG_WRITE("CUIThread *** [%p] NEW ",env);
}

CUIThread::~CUIThread(void)
{
	SAFE_DELETE(m_pActivity);
	SAFE_DELETE(m_pJNI);
	

	LOG_WRITE("CUIThread *** DEL ");
}
CJUserInfo CUIThread::GetUserInfo()
{
	jobject o = m_pJNI->m_env->CallStaticObjectMethod(CJUserInfo::_jclass,CJUserInfo::_currentUserId);
	if (!o) return CJUserInfo(m_pJNI->m_env,NULL);
	return CJUserInfo(m_pJNI->m_env,o);
}



void CUIThread::Process_ZingLogin()
{
	LOG_WRITE("Process_ZingLogin()......");
	//_theApp->NextTimer(2000);
	//return;
	LOG_WRITE("Process_ZingLogin()......0.8");

	process_LoginByID(RCID_MAINVIEW, RCID_TITLE_1, RCID_CONTENT_1, RCID_IDCONTAINER_1, RCID_USER_1, RCID_PASS_1);
	process_LoginByID(RCID_MAINVIEW_1, RCID_TITLE, RCID_CONTENT, RCID_IDCONTAINER, RCID_USER, RCID_PASS);

	
}

void CUIThread::Process_MessageBox()
{
	CJWindowManagerGlobal oWndMgr(m_pJNI->m_env,_theApp->m_pJNI->m_pWndMgrGlobal->Get());
	CJViewGroup oLastView = oWndMgr.GetLastView();
	CJTextView oTitle(m_pJNI->m_env,oLastView.findViewById(RCID_TITLE));
	if (!oTitle.Get()) return;
	CJTextView oMessage(m_pJNI->m_env,oLastView.findViewById(RCID_MESSAGE));
	if (!oMessage.Get()) return;

	CStdString szMsg = oMessage.getJCharSequence().GetBuffer();
	LOG_WRITE(" Title [%s]",oTitle.getJCharSequence().GetBuffer());
	LOG_WRITE(" Message [%s]",szMsg.c_str());

	if (szMsg.Find("không chính xác") >= 0) {

		return;
	}

	CJViewGroup oBtnVG(m_pJNI->m_env,oLastView.findViewById(RCID_VIEWBUTTON));
	if (!oBtnVG.Get()) return;
	if (oBtnVG.Get()){
		LOG_WRITE("Need to click on this MessageBox???");
		//CJTextView oBtnText(m_pJNI->m_env,oBtnVG.getChildAt(0));//Button not TextView		
		//LOG_WRITE(" CLICKED Button [%s]",oBtnText.getJCharSequence().GetBuffer());
		//oBtnText.performClick();
	}
	
	_theApp->NextTimer(2000);

}


void CUIThread::Update()
{
	LOG_WRITE("CUIThread::Update()............0");
	jobject oActivity = _theApp->m_pJNI->m_pActivity->Get();
	if (!m_pActivity->IsSameObject(oActivity)){
		LOG_WRITE("CUIThread::Update()............3");
		LOG_WRITE("==> CUIThread(m_pActivity->IsSameObject(oActivity))::Update() uiActivity[%d]",_theApp->m_pJNI->m_uiActivity);
		//CUIThread::_isRunning = FALSE;
		m_pActivity->Attach(m_pJNI->m_env->NewGlobalRef(oActivity));
		return;
	}

	if (!m_pActivity->hasWindowFocus()){
		LOG_WRITE("CUIThread::Update()............2");
		Process_MessageBox();
		return;
	}
	LOG_WRITE("CUIThread::Update()............1");
	UIActivity uiActivity = _theApp->m_pJNI->m_uiActivity;
	LOG_WRITE("==> CUIThread::Update() uiActivity[%d]",uiActivity);
	
	switch (uiActivity){
		case ACT_UI_ZaloActivity:
			LOG_WRITE("===> CLOSE ZALO [%d]",_theApp->m_pJNI->m_uiActivity);
			m_pActivity->finish();
			return;
		case ACT_UI_VNGActivity:
			Process_ZingLogin();
			return;
		default:
			return;
	}
}



void CUIThread::_Runtime( JNIEnv* env, jobject self )
{
	
	_isRunning = TRUE;
	if (!g_pGame){
		SAFE_DELETE(g_pUIThread);
		_isRunning = FALSE;
		return;
	}
	if (g_pUIThread == NULL) g_pUIThread = new CUIThread(env);
	g_pUIThread->Update();
	
	_isRunning = FALSE;
}

void CUIThread::_WaitFinished()
{
	while (_isRunning && g_pUIThread) usleep(100000); //100s
}

void CUIThread::process_LoginByID( int iMainView, int iTitle, int iContent, int iContainer, int iUser, int iPass )
{
	CJViewGroup oMainView(m_pJNI->m_env,m_pActivity->findViewById(iMainView));
	if (oMainView.Get()) {
		LOG_WRITE("Process_ZingLogin()......1");
		CJViewGroup oLast(m_pJNI->m_env,oMainView.GetLastView());
		if (!oLast.Get()) return;
		LOG_WRITE("Process_ZingLogin()......2");

		CJTextView oTitle(m_pJNI->m_env,oLast.findViewById(iTitle));
		LOG_WRITE(" [%p] oTitle",oTitle.Get());
		if (!oTitle.Get()) {
			LOG_WRITE("oTitle.Get() = 0");
			return;
		}

		CStdString szTitle = oTitle.getJCharSequence().GetBuffer();
		LOG_WRITE(" WINDOW TITLE [%s]",szTitle.c_str());

		if (szTitle.Compare("Processing") == 0) return;

		if (szTitle.Compare("Login") == 0 || szTitle.Compare("Đăng nhập") == 0) {
			CJViewGroup oContent(m_pJNI->m_env,oLast.findViewById(iContent));
			//LOG_WRITE(" + [%p] oContent",oContent.Get());
			if (oContent.Get()){
				CJViewGroup oZingLayout(m_pJNI->m_env,oContent.getChildAt(1));
				//LOG_WRITE(" + [%p] oZingLayout",oZingLayout.Get());
				if (!oZingLayout.Get()) return;

				CJTextView oButton(m_pJNI->m_env,oZingLayout.getChildAt(0));
				//LOG_WRITE(" + [%p] oButton",oButton.Get());
				if (!oButton.Get()) return;
				CJTextView oText(m_pJNI->m_env,oButton.findViewById(iTitle));

				LOG_WRITE("CLICKED 0 [%s]",oText.getJCharSequence().GetBuffer());
				oButton.performClick();	
				_theApp->NextTimer(2000);
			}
			return;
		}

		PUBLISHER_ACCOUNT* pAccount = &g_pGame->m_publisherAccount;
		if(pAccount->czUsername[0] == 0){
			LOG_WRITE("Process_ZingLogin()......0.5");
			_theApp->m_pEpoll->Sync_GameRequestAccount();
			return;
		}

		if (szTitle.Compare("Login with Zing ID") == 0 || szTitle.Compare("Đăng nhập bằng Zing ID") == 0){
			CJViewGroup oIdContainer(m_pJNI->m_env,oLast.findViewById(iContainer));
			//LOG_WRITE(" + [%p] oIdContainer",oIdContainer.Get());
			if (oIdContainer.Get()){
				LOG_WRITE("Process_UI_LoginWithZingID ...0");
				CJTextView oUser(m_pJNI->m_env,oIdContainer.findViewById(iUser));
				if (!oUser.Get()) return;
				LOG_WRITE("Process_UI_LoginWithZingID ...0.1");
				CJTextView oPass(m_pJNI->m_env,oIdContainer.findViewById(iPass));
				if (!oPass.Get()) return;
				LOG_WRITE("Process_UI_LoginWithZingID ...0.11");
				CJView oBtn(m_pJNI->m_env,oLast.findViewById(0x7f08004a));
				if (!oBtn.Get()) return;
				LOG_WRITE("Process_UI_LoginWithZingID ...1");
				oUser.setText(g_pGame->m_publisherAccount.czUsername);
				oPass.setText(g_pGame->m_publisherAccount.czPassword);
				oBtn.performClick();
				_theApp->NextTimer(2000);
			}
		}

		if (szTitle.Compare("Protect Guest Account") == 0){
			CJTextView otvBack(m_pJNI->m_env,oLast.findViewById(RCID_TVBACK));//how to show this
			if (!otvBack.Get()) return;
			CJTextView obtnBack(m_pJNI->m_env,otvBack.getParent());
			if (!obtnBack.Get()) return;
			LOG_WRITE("CLICKED 1 [%s]",otvBack.getJCharSequence().GetBuffer());
			obtnBack.performClick();
			_theApp->NextTimer(2000);
			return;
		}

	}
}
