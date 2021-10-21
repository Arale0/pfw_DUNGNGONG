// LoginAddServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "LoginAddServerDlg.h"


// CLoginAddServerDlg dialog

IMPLEMENT_DYNAMIC(CLoginAddServerDlg, CDialog)

CLoginAddServerDlg::CLoginAddServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginAddServerDlg::IDD, pParent)
{
	m_pAccount = g_pMainDlg->m_tabMain.m_AccountDlg.m_pAccountSelected;
	LOGA_DEBUG("%08x m_pAccount",m_pAccount);
}

CLoginAddServerDlg::~CLoginAddServerDlg()
{
}

void CLoginAddServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_cbServer);
	DDX_Control(pDX, IDC_LBL_ADDSERVER_STATUS, m_lblStatus);
}


BOOL CLoginAddServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_lblStatus.SetText(L"");
	m_lblStatus.SetFont(L"Tahoma",8,TRUE);
	m_lblStatus.SetTextColor(RGB(255,0,0));

	m_cbServer.AddString(L"Select Server");
	CString szServer;
	for(int i = 1; i< 50; i++){
		szServer.Format(L"S%d",i);
		m_cbServer.AddString(szServer);
	}
	m_cbServer.SetCurSel(0);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CLoginAddServerDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER, &CLoginAddServerDlg::OnCbnSelchangeComboServer)
	ON_BN_CLICKED(IDOK, &CLoginAddServerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginAddServerDlg message handlers

void CLoginAddServerDlg::OnCbnSelchangeComboServer()
{
	
}

void CLoginAddServerDlg::OnBnClickedOk()
{
	if(!m_pAccount) { 
		
		OnCancel(); return;
	}
	int server  = m_cbServer.GetCurSel();
	if(server <=0) {
		m_lblStatus.SetText(L"Select server to add");
		return;
	}
	if(m_pAccount->AddServer(server)){
		LOGA_DEBUG("AddServer %d",server );
		OnOK();
		return;
	}
	else{
		m_lblStatus.SetText(L"Server is exist");
		return;
	}
	OnCancel();
}
