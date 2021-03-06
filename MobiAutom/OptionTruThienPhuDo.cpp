//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionTruThienPhuDo.h"


// COptionTruThienPhuDo dialog

IMPLEMENT_DYNAMIC(COptionTruThienPhuDo, CVIETabDialog)

COptionTruThienPhuDo::COptionTruThienPhuDo(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionTruThienPhuDo::IDD, pParent)
{
	m_activity = act_truthienphudo;
}

COptionTruThienPhuDo::~COptionTruThienPhuDo()
{
}

void COptionTruThienPhuDo::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK_GO_ALL, m_chkGoAll);
	DDX_Control(pDX, IDC_CHECK_SWEEPONLY, m_chkSweepOnly);
}


BEGIN_MESSAGE_MAP(COptionTruThienPhuDo, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionTruThienPhuDo::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_GO_ALL, &COptionTruThienPhuDo::OnBnClickedCheckGoAll)
	ON_BN_CLICKED(IDC_CHECK_SWEEPONLY, &COptionTruThienPhuDo::OnBnClickedCheckSweeponly)
END_MESSAGE_MAP()


BOOL COptionTruThienPhuDo::OnInitDialog(){

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


	delete pTemp;
	return TRUE;
}
void COptionTruThienPhuDo::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkGoAll.SetCheck(pTab->bTruThienGoAllTime);
	m_chkSweepOnly.SetCheck(pTab->bTruThienSweepOnly);
	pGame->m_bSyncOptionTab = TRUE;
	setupControls();
}

void COptionTruThienPhuDo::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionTruThienPhuDo::OnBnClickedCheckGoAll()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTruThienGoAllTime = m_chkGoAll.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
	setupControls();
}

void COptionTruThienPhuDo::OnBnClickedCheckSweeponly()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTruThienSweepOnly = m_chkSweepOnly.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
	setupControls();
}

void COptionTruThienPhuDo::setupControls()
{
	if (m_chkGoAll.GetCheck() == 1) m_chkSweepOnly.EnableWindow(FALSE);
	if (m_chkGoAll.GetCheck() == 0) m_chkSweepOnly.EnableWindow(TRUE);
	if (m_chkSweepOnly.GetCheck() == 1) m_chkGoAll.EnableWindow(FALSE);
	if (m_chkSweepOnly.GetCheck() == 0) m_chkGoAll.EnableWindow(TRUE);
}
