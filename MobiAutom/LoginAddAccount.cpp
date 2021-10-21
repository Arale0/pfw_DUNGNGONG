// LoginAddAccount.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "LoginAddAccount.h"


// CLoginAddAccount dialog

IMPLEMENT_DYNAMIC(CLoginAddAccount, CDialog)

CLoginAddAccount::CLoginAddAccount(CWnd* pParent /*=NULL*/,int iMode)
: CDialog(CLoginAddAccount::IDD, pParent),m_iMode(iMode)
{	
	
	LOGA_DEBUG("Mode %d,%d",m_iMode,iMode);
}

CLoginAddAccount::~CLoginAddAccount()
{
}

void CLoginAddAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NEW_USERNAME, m_txtUsername);
	DDX_Control(pDX, IDC_EDIT_NEW_PASS, m_txtPassword);
	DDX_Control(pDX, IDC_BUTTON_ADDACCOUNT, m_btnSubmit);
	DDX_Control(pDX, IDC_LBL_ACCOUNT_WARNING, m_lblWarning);
	DDX_Control(pDX, IDC_BUTTON_SHOWPASSWORD, m_btnShowPassword);

	
	
}


BOOL CLoginAddAccount::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_btnShowPassword.SetFlatStyle(TRUE, FALSE);
	m_btnShowPassword.SetIcon(IDI_ICON_EYE);

	m_lblWarning.SetFont(L"Tahoma",8,TRUE);
	m_lblWarning.SetTextColor(RGB(0,0,255));
	m_lblWarning.SetText(L"Game account only save in your pc");
	if(m_iMode == ACCOUNTFORM_MODE_ADD){
		m_btnSubmit.SetWindowText(L"Add");
		SetWindowText(L"Add new account");
	}
	else {
		m_btnSubmit.SetWindowText(L"OK");
		SetWindowText(L"Edit account");
		CGameAccount *pAcc = g_pMainDlg->m_tabMain.m_AccountDlg.m_pAccountSelected;
		if(pAcc){
			m_txtUsername.SetText(CUtils::_A2W(pAcc->publisherAccount.czUsername));
			m_txtPassword.SetText(CUtils::_A2W(pAcc->publisherAccount.czPassword));
		}

	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CLoginAddAccount, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDACCOUNT, &CLoginAddAccount::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SHOWPASSWORD, &CLoginAddAccount::OnBnClickedButtonShowpassword)
END_MESSAGE_MAP()


// CLoginAddAccount message handlers

void CLoginAddAccount::OnBnClickedButtonAdd()
{
	if(m_txtUsername.GetText().IsEmpty() || 
		m_txtPassword.GetText().IsEmpty()){
		//MessageBox(L"Input username and password!");
		//OnCancel();
		m_lblWarning.SetTextColor(RGB(255,0,0));
		m_lblWarning.SetText(L"Please input Username and password");
		return;
	}
	if(m_iMode == ACCOUNTFORM_MODE_ADD){
		if(g_pAutoManager->m_AccountList2.AddAccount(m_txtUsername.GetText(), m_txtPassword.GetText())){
			OnOK();
			return;
		}else{
			m_lblWarning.SetTextColor(RGB(255,0,0));
			m_lblWarning.SetText(L"Game account is exist!");
			return;
		}
	}
	else {
		CGameAccount *pAcc = g_pMainDlg->m_tabMain.m_AccountDlg.m_pAccountSelected;
		if(pAcc){
			strcpy_s(pAcc->publisherAccount.czUsername, 64, CUtils::_W2A(m_txtUsername.GetText()));
			strcpy_s(pAcc->publisherAccount.czPassword, 64, CUtils::_W2A(m_txtPassword.GetText()));
			CRoleAccount *pRoleRunning = pAcc->GetRoleRunning();
			CGameInfo* pGame = g_pGameManager->GetGameInfoByAccountInlist(pRoleRunning);
			if(pGame){
				LOGA_DEBUG("Set new login acc  info [%s][%s]",pAcc->publisherAccount.czUsername, pAcc->publisherAccount.czPassword);

				pGame->SetPublisherAccount(pAcc->publisherAccount.czUsername, pAcc->publisherAccount.czPassword);
			}
			OnOK();
			return;
		}
	}
	OnCancel();
}

void CLoginAddAccount::OnBnClickedButtonShowpassword()
{
	static DWORD dwResult = m_txtPassword.SendMessage(EM_GETPASSWORDCHAR, 0, 0);
	static BOOL bClicked = FALSE;
	bClicked = !bClicked;
	if (bClicked) m_txtPassword.SendMessage(EM_SETPASSWORDCHAR, 0, 0);	
	else m_txtPassword.SendMessage(EM_SETPASSWORDCHAR, dwResult, 0);	
	m_txtPassword.Invalidate();	
}
