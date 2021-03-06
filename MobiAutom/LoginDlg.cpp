// LogginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "LoginDlg.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CVIEChildDlg)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CVIEChildDlg(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEChildDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RAD_ACCOUNT_INLIST, m_radAccountInlist);
	DDX_Control(pDX, IDC_RAD_ACCOUNT_FIXED, m_radAccountFixed);
	DDX_Control(pDX, IDC_EDIT_ACCOUNTINFO_USERNAME, m_txtUsername);
	DDX_Control(pDX, IDC_EDIT_ACCOUNTINFO_PASSWORD, m_txtPassword);
	DDX_Control(pDX, IDC_EDIT_ACCOUNTINFO_ROLE, m_txtRole);
	DDX_Control(pDX, IDC_CBO_ACCOUNTINFO_SERVER, m_cboServer);
	DDX_Control(pDX, IDC_BUTTON_ACCOUNTINFO_SHOWPASS, m_btnShowPassword);
	DDX_Control(pDX, IDC_BUTTON_ACCOUNTINFO_SAVE, m_btnSave);

	DDX_Control(pDX, IDC_GROUP_ACCOUNTFIXED, m_groupAccount);
	DDX_Control(pDX, IDC_LBL_USERNAME, m_lblUsername);
	DDX_Control(pDX, IDC_LBL_PASSWORD, m_lblPassword);
	DDX_Control(pDX, IDC_LBL_SERVER, m_lblServer);
	DDX_Control(pDX, IDC_LBL_ROLE, m_lblRole);

	DDX_Control(pDX, IDC_BUTTON_OPEN_ACCOUNTLIST, m_btnOpenAccountList);
	DDX_Control(pDX, IDC_BUTTON_OPEN_ACCOUNTLIST2, m_btnOpenAccountList2);

	DDX_Control(pDX, IDC_LBL_ACCOUNTFIXED_STATUS, m_lblWarning);
	DDX_Control(pDX, IDC_CBO_ROLE, m_cbRole);
}


BOOL CLoginDlg::OnInitDialog()
{
	CVIEChildDlg::OnInitDialog();
	m_groupAccountMgr.SetGroup(10, &m_txtUsername,&m_txtPassword,&m_cboServer,&m_btnShowPassword,&m_btnSave,&m_lblUsername,&m_lblPassword,&m_lblServer,&m_lblRole, &m_lblWarning);
	m_btnShowPassword.SetFlatStyle(TRUE, FALSE);
	//m_btnShowPassword.SetIcon(IDI_ICON_EYE);

	m_btnOpenAccountList.SetFlatStyle(TRUE, FALSE);
	m_btnOpenAccountList.SetIcon(IDI_ICON_EDIT);
	
	m_btnOpenAccountList2.SetFlatStyle(TRUE, FALSE);
	m_btnOpenAccountList2.SetIcon(IDI_ICON_EDIT);

	m_lblWarning.SetText(L"");
	m_lblWarning.SetFont(L"Tahoma",8,TRUE);
	m_lblWarning.SetTextColor(RGB(255,0,0));

	m_cboServer.AddString(L"Chọn server");
	CString szServer;
	for(int i = 1; i< MAXNUM_SERVERINDEX; i++){
		szServer.Format(L"S%d",i);
		m_cboServer.AddString(szServer);
	}
	m_cboServer.SetCurSel(0);

	m_cbRole.AddString(L"Nhân vật 1");
	m_cbRole.AddString(L"Nhân vật 2");
	m_cbRole.AddString(L"Nhân vật 3");
	m_cbRole.AddString(L"Nhân vật 4");
	m_cbRole.AddString(L"Nhân vật tự chọn");

	m_txtRole.ShowWindow(FALSE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CLoginDlg, CVIEChildDlg)
	ON_BN_CLICKED(IDC_RAD_ACCOUNT_INLIST, &CLoginDlg::OnBnClickedRadAccountInlist)
	ON_BN_CLICKED(IDC_RAD_ACCOUNT_FIXED, &CLoginDlg::OnBnClickedRadAccountFixed)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_ACCOUNTLIST, &CLoginDlg::OnBnClickedButtonOpenAccountlist)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_ACCOUNTLIST2, &CLoginDlg::OnBnClickedButtonOpenAccountlist2)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNTINFO_SAVE, &CLoginDlg::OnBnClickedButtonAccountinfoSave)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNTINFO_SHOWPASS, &CLoginDlg::OnBnClickedButtonAccountinfoShowpass)
	ON_EN_SETFOCUS(IDC_EDIT_ACCOUNTINFO_USERNAME, &CLoginDlg::OnEnSetfocusEditAccountinfoUsername)
	ON_EN_SETFOCUS(IDC_EDIT_ACCOUNTINFO_PASSWORD, &CLoginDlg::OnEnSetfocusEditAccountinfoPassword)
	ON_CBN_SETFOCUS(IDC_CBO_ACCOUNTINFO_SERVER, &CLoginDlg::OnCbnSetfocusCboAccountinfoServer)
	ON_EN_SETFOCUS(IDC_EDIT_ACCOUNTINFO_ROLE, &CLoginDlg::OnEnSetfocusEditAccountinfoRole)
	ON_CBN_SELCHANGE(IDC_CBO_ROLE, &CLoginDlg::OnCbnSelchangeCboRole)
	ON_CBN_SELCHANGE(IDC_CBO_ACCOUNTINFO_SERVER, &CLoginDlg::OnCbnSelchangeCboAccountinfoServer)
END_MESSAGE_MAP()

void CLoginDlg::UpdateControls(CGameInfo* pGame){
	if(!pGame) return;
	LOGA_DEBUG("UpdateControls...");
	LOGINTAB *pTab = pGame->GetLoginTab();
	m_radAccountInlist.SetCheck(pTab->iAccountMode == ACCOUNTMODE_INLIST);
	m_radAccountFixed.SetCheck(pTab->iAccountMode == ACCOUNTMODE_FIXED);
	UpdateUIByMode(pTab->iAccountMode);

	PUBLISHER_ACCOUNT* account = &pTab->accountFixed.publisherAccount;
	m_txtUsername.SetText(CUtils::_A2W(account->czUsername));
	m_txtPassword.SetText(CUtils::_A2W(account->czPassword));
	ROLE_LOGIN* rolelogin = &pTab->accountFixed.roleLogin;
	//m_txtRole.SetText(CUtils::_A2W(rolelogin->czRoleName));
	m_cboServer.SetCurSel(rolelogin->iServer);
	m_cbRole.SetCurSel(rolelogin->iRoleNo);
	m_lblWarning.SetText(L"");
}	

void CLoginDlg::OnBnClickedRadAccountInlist()
{
	LOGA_DEBUG("OnBnClickedRadAccountInlist");
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	LOGINTAB *pTab = pGame->GetLoginTab();
	pTab->iAccountMode = ACCOUNTMODE_INLIST;
	UpdateUIByMode(pTab->iAccountMode);
	pGame->ResetLoginAccount();
}

void CLoginDlg::OnBnClickedRadAccountFixed()
{
	LOGA_DEBUG("OnBnClickedRadAccountFixed");
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	LOGINTAB *pTab = pGame->GetLoginTab();
	pTab->iAccountMode = ACCOUNTMODE_FIXED;
	UpdateUIByMode(pTab->iAccountMode);
	memcpy(&pGame->m_loginAccount, &pTab->accountFixed, sizeof(LOGIN_ACCOUNT));
	if(pGame->m_pAccountInlist){
		pGame->m_pAccountInlist->bRunning = FALSE;
		pGame->m_pAccountInlist = NULL;
	}
}
void CLoginDlg::UpdateUIByMode(int iMode){
	LOGA_DEBUG("UpdateUIByMode %d",iMode);
	m_groupAccountMgr.SetVisible(iMode == ACCOUNTMODE_FIXED);
	m_btnOpenAccountList.ShowWindow(iMode == ACCOUNTMODE_INLIST);
	m_btnOpenAccountList2.ShowWindow(iMode == ACCOUNTMODE_FIXED);
}

void CLoginDlg::OnBnClickedButtonOpenAccountlist()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACCOUNT);
}
void CLoginDlg::OnBnClickedButtonOpenAccountlist2()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACCOUNT);
}

void CLoginDlg::OnBnClickedButtonAccountinfoSave()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	memset(&pGame->m_loginAccount,0,sizeof(LOGIN_ACCOUNT));
	LOGINTAB *pTab = pGame->GetLoginTab();
	CString czUsername = m_txtUsername.GetText();
	CString czPassword = m_txtPassword.GetText();
	CString czRolename = m_txtRole.GetText();
	int		iServerIdx  = m_cboServer.GetCurSel();
	int		iRoleIdx = m_cbRole.GetCurSel();
	
	if(czUsername.IsEmpty()) czUsername = "No Account";
	int iRandom = rand()%1000;
	czRolename.Format(L"PerfectWorld%d", iRandom);
	LOGW_DEBUG(L"czRolename[%s]", czRolename);
	if(iServerIdx <= 0){
		m_lblWarning.SetText(L"Vui lòng chọn server!");
		m_lblWarning.SetTextColor(RGB(255,0,0));
		return;
	}
	 
	strcpy_s(pTab->accountFixed.publisherAccount.czUsername, 64, CUtils::_W2A(czUsername));
	strcpy_s(pTab->accountFixed.publisherAccount.czPassword, 64, CUtils::_W2A(czPassword));
	strcpy_s(pTab->accountFixed.roleLogin.czRoleName, 64, CUtils::_W2A(czRolename));
	pTab->accountFixed.roleLogin.idxPlayer = 0;
	pTab->accountFixed.roleLogin.iServer = iServerIdx;
	pTab->accountFixed.roleLogin.iRoleNo = iRoleIdx;
	m_lblWarning.SetText(L"Đã lưu thông tin tài khoản!");
	m_lblWarning.SetTextColor(RGB(0,0,255));
	
	memcpy(&pGame->m_loginAccount, &pTab->accountFixed, sizeof(LOGIN_ACCOUNT));
}

void CLoginDlg::OnBnClickedButtonAccountinfoShowpass()
{
	static DWORD dwResult = m_txtPassword.SendMessage(EM_GETPASSWORDCHAR, 0, 0);
	static BOOL bClicked = FALSE;
	bClicked = !bClicked;
	if (bClicked) m_txtPassword.SendMessage(EM_SETPASSWORDCHAR, 0, 0);	
	else m_txtPassword.SendMessage(EM_SETPASSWORDCHAR, dwResult, 0);	
	m_txtPassword.Invalidate();
}

void CLoginDlg::OnEnSetfocusEditAccountinfoUsername()
{
	m_lblWarning.SetText(L"");
}

void CLoginDlg::OnEnSetfocusEditAccountinfoPassword()
{
	m_lblWarning.SetText(L"");
}

void CLoginDlg::OnCbnSetfocusCboAccountinfoServer()
{
	m_lblWarning.SetText(L"");
}

void CLoginDlg::OnEnSetfocusEditAccountinfoRole()
{
	m_lblWarning.SetText(L"");
}

void CLoginDlg::OnCbnSelchangeCboRole()
{
	
}

void CLoginDlg::OnCbnSelchangeCboAccountinfoServer()
{
	// TODO: Add your control notification handler code here
}
