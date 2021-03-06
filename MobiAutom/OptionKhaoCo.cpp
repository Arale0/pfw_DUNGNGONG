//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionKhaoCo.h"


// COptionKhaoCo dialog

IMPLEMENT_DYNAMIC(COptionKhaoCo, CVIETabDialog)

COptionKhaoCo::COptionKhaoCo(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionKhaoCo::IDD, pParent)
{
	m_activity = act_khaoco;
}

COptionKhaoCo::~COptionKhaoCo()
{
}

void COptionKhaoCo::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	DDX_Control(pDX, IDC_COMBO2, m_cb2);
	DDX_Control(pDX, IDC_COMBO3, m_cb3);
}


BEGIN_MESSAGE_MAP(COptionKhaoCo, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionKhaoCo::OnBnClickedButtonBack)
	ON_CBN_SELCHANGE(IDC_COMBO1, &COptionKhaoCo::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &COptionKhaoCo::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &COptionKhaoCo::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


BOOL COptionKhaoCo::OnInitDialog(){

	CVIETabDialog::OnInitDialog();
	CGameInfo *pTemp = new CGameInfo();
	pTemp->SetTabDataDefault();
	CActivitySetting::GetInstance()->InitActivity(pTemp);
	if(m_activity < MAX_NUM_ACTIVITY)
		SetWindowText(pTemp->m_ActivityTab.lstActivity[m_activity].szName);

	m_btnBack.SetWindowText(L"X");
	m_btnBack.SetFont(L"Tahoma", 10, FALSE, FALSE, FALSE);
	//m_btnBack.SetIcon(IDI_ICON_CLOSE_17,17,17);
	m_btnBack.SetFlatStyle(TRUE,FALSE);


	for (int i = 0; i < 10; i++) {
		CString czNum;
		czNum.Format(L"%d", i);
		m_cb1.AddString(czNum);
		m_cb2.AddString(czNum);
		m_cb3.AddString(czNum);
	}

	delete pTemp;
	return TRUE;
}
void COptionKhaoCo::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_cb1.SetCurSel(pTab->iKhaoCoNo1);
	m_cb2.SetCurSel(pTab->iKhaoCoNo2);
	m_cb3.SetCurSel(pTab->iKhaoCoNo3);
}

void COptionKhaoCo::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionKhaoCo::OnCbnSelchangeCombo1()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iKhaoCoNo1 = m_cb1.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionKhaoCo::OnCbnSelchangeCombo2()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iKhaoCoNo2 = m_cb2.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionKhaoCo::OnCbnSelchangeCombo3()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iKhaoCoNo3 = m_cb3.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}
