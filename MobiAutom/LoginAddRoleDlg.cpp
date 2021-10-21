// LoginAddRoleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "LoginAddRoleDlg.h"


// CLoginAddRoleDlg dialog

IMPLEMENT_DYNAMIC(CLoginAddRoleDlg, CDialog)

CLoginAddRoleDlg::CLoginAddRoleDlg(CWnd* pParent /*=NULL*/, int iMode)
	: CDialog(CLoginAddRoleDlg::IDD, pParent),m_iMode(iMode)
{
	m_pServerSelected = g_pMainDlg->m_tabMain.m_AccountDlg.m_pServerSelected;
}

CLoginAddRoleDlg::~CLoginAddRoleDlg()
{
}

void CLoginAddRoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NEW_ROLE, m_txtRolename);
	DDX_Control(pDX, IDC_LBL_ADDROLE_STATUS, m_lblStatus);
	DDX_Control(pDX, IDC_BUTTON_ADDROLE, m_btnAdd);

}


BOOL CLoginAddRoleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_lblStatus.SetText(L"");
	m_lblStatus.SetFont(L"Tahoma",8,TRUE);
	m_lblStatus.SetTextColor(RGB(255,0,0));
	if(m_iMode == ADDROLE_MODE_ADD){
		SetWindowText(L"Add role");
		m_btnAdd.SetWindowText(L"Add");
	}
	else {
		SetWindowText(L"Edit role");
		m_btnAdd.SetWindowText(L"OK");
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CLoginAddRoleDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDROLE, &CLoginAddRoleDlg::OnBnClickedButtonAddrole)
END_MESSAGE_MAP()


// CLoginAddRoleDlg message handlers

void CLoginAddRoleDlg::OnBnClickedButtonAddrole()
{
	if(m_iMode == ADDROLE_MODE_ADD){
		if(!m_pServerSelected){
			OnCancel();
			return;
		}

		if(m_pServerSelected->AddRole(0, CUtils::_W2A(m_txtRolename.GetText()))){
			OnOK();
			return;
		}
		else {
			m_lblStatus.SetText(L"Role is exist");
		}
	}
	else {
		CRoleAccount *pRole = g_pMainDlg->m_tabMain.m_AccountDlg.m_pRoleSelected;
		if(pRole){
			strcpy_s(pRole->czRoleName, 64, CUtils::_W2A(m_txtRolename.GetText()));
			CGameInfo* pGame = g_pGameManager->GetGameInfoByAccountInlist(pRole);
			if(pGame){
				if(pRole)LOGA_DEBUG("Set new login role info [%s]",pRole->czRoleName);
				if(pRole)pGame->SetRoleLogin(pGame->m_loginAccount.roleLogin.iServer, pRole->idxPlayer, pRole->czRoleName);
			}


			OnOK();
			return;
		}
	}
	OnCancel();
}
