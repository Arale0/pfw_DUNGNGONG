
// vlvAutom.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "mobiAuto.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"VIEControl32.lib")
#pragma comment(lib,"Autom32.lib")
#pragma comment(lib,"Crypto32.lib")

// CAutoApp

BEGIN_MESSAGE_MAP(CAutoApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAutoApp construction

CAutoApp::CAutoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAutoApp object

CAutoApp theApp;


// CAutoApp initialization

BOOL CAutoApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();
	
	if(!InitLicense()) return FALSE;
	
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	m_pGameManager = new CGameManager();
	
	m_pMainDlg = new CAutoDlg();
	m_pMainWnd = m_pMainDlg;
	m_pMainDlg->DoModal();
	
	SAFE_DELETE(m_pMainDlg);
	SAFE_DELETE(m_pGameManager);
	return FALSE;
}

BOOL CAutoApp::CheckLicense( CGameInfo *pGame )
{
	if (!pGame) return FALSE;	
	return CheckLicense(lic_player,pGame->_czPlayer,pGame->_czServer,0);
	//return TRUE;
}

BOOL CAutoApp::CheckLicense( LICType licType,LPCWSTR lpName,LPCWSTR lpServer,UINT uFuncId )
{
#ifdef BUILD_FLAG_DEBUG
	return TRUE;
#endif
	BOOL bOk;
	CAIGLicense::CheckLicense(licType,lpName,lpServer,uFuncId,&bOk);	
	//LogWriteW(L"CheckLicense(%s,%s,%d) : %d",lpName,lpServer,uFuncId,bOk);
	return bOk;
}

void CAutoApp::UpdateLicenseActivityList( CGameInfo *pGame )
{
	if (!pGame) return;
	ACTIVITYTAB* pActivityTab =	pGame->GetActivityTab();	
	for(int i =0; i< MAX_NUM_ACTIVITY; i++)
	{
		ACTIVITYINFO *pUA  = &pActivityTab->lstActivity[i];
		pUA->bLicensed = CheckLicense(lic_player,pGame->_czPlayer,pGame->_czServer,pUA->uFuncId);		 
	}
	UpdateLicenseActivityExList(pGame);
}

void CAutoApp::UpdateLicenseActivityExList( CGameInfo *pGame )
{
	if (!pGame) return;
	ACTIVITYTAB* pActivityTab = pGame->GetActivityTab();
	for (int i = 0; i < MAX_NUM_ACTIVITYEX; i++)
	{
		ACTIVITYINFOEX *pUA = &pActivityTab->lstActivityEx[i];
		pUA->bLicensed = CheckLicense(lic_player, pGame->_czPlayer, pGame->_czServer, pUA->uFuncId);
	}
}

UINT CAutoApp::_ThreadLimitedLicenseAlert( LPVOID lpParam )
{
	return VIEMsgBox(L"Bạn phải đăng ký License (miễn phí trong giai đoạn thử nghiệm) mới có thể sử dụng được auto [Trợ giúp -> Hướng dẫn đăng ký]", L"Thông báo", MB_ICONWARNING);

}

void CAutoApp::LimitedLicenseAlert()
{
	AfxBeginThread(_ThreadLimitedLicenseAlert, this);
}

void CAutoApp::DisplayUnregisterToolTip( int x, int y )
{
	m_pUnregisterToolTip = CVIEToolTip::Create(m_pUnregisterToolTip);
	m_pUnregisterToolTip->SetPosition(x, y, 254, 68);
	m_pUnregisterToolTip->SetTimeOut(10000);
	m_pUnregisterToolTip->RegisterCallbackMessage(g_pMainDlg, WM_USER + 1407);
	m_pUnregisterToolTip->Display(L"Bạn phải đăng ký bản quyền mới có thể sử dụng được auto. Nhấp chuột vào thông báo này để xem hướng dẫn đăng ký.", L"Chưa đăng ký quyền sử dụng");

}

void CAutoApp::UpdateAllLicenses()
{
	LOGA_WARNING(" aigo_update_all_lics");
	CAIGLicense::ShowManageCode(NULL, TRUE);
	//cap nhat lai lic
	CPtrList *plstGame = g_pGameManager->GetListGame();	
	int index = 0;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);

		if (theApp.CheckLicense(pGame))
			g_pMainDlg->m_lstEmulator.SetRowTextColor(index, RGB(0, 0, 255));
		else {
			g_pMainDlg->m_lstEmulator.SetRowTextColor(index, RGB(255, 0, 0));
			if (pGame->m_bControl) {
				g_pMainDlg->m_lstEmulator.SetCheck(index, BST_UNCHECKED);
				pGame->m_bControl = FALSE;
			}
		}
		theApp.UpdateLicenseActivityList(pGame);
		++index;
	}
	if (m_pMainDlg->m_pGameSelected)
		m_pMainDlg->m_tabMain.UpdateTabDialogs(m_pMainDlg->m_pGameSelected);
}

BOOL CAutoApp::InitLicense()
{
#ifndef BUILD_FLAG_DEBUG
	//	CString szVerEXE = GetAppVersion(NULL);
	//	CString szVerDLL = GetAppVersion(m_hModuleHook);
	//	if (szVerEXE.Compare(szVerDLL) != 0) return FALSE;	//khac version giua dll va exe

	CString szMD5;
	szMD5.Format(L"%s_%s",TXT_LICENSE_AIG,TXT_AUTO_EXE);
	CMD5 md5;
	CString szSigned = md5.FromStringW(szMD5);
	
	HANDLE hSigned = OpenFileMapping(FILE_MAP_READ,FALSE,szSigned);
	if (hSigned){
		CloseHandle(hSigned);
		AfxMessageBox(L"Auto đang hoạt động.\nNếu thấy hộp thoại này xin kiểm tra lại.\n\nAuto có thể ở dưới khay hệ thống hoặc đang bị treo.",MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	if (!CAIGLicense::InitLicense(szSigned, UINT_ENTRY_ENCODE)) return FALSE; //khong xac thuc License.aig
	CAIGLicense::LoginForm((CALLBACK_API_AIGATO)_ApiCallback);
#endif


	m_InfoList.plstServerName	= new CStringArray();
	m_InfoList.plstFamilyName	= new CStringArray();
	m_InfoList.plstGuildName	= new CStringArray();
	m_InfoList.plstPlayerName	= new CStringArray();
	return TRUE;
}

BOOL CAutoApp::_ApiCallback( APICBType cbType, LPVOID lParam )
{
	return TRUE;
}