//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionTruongLaoTuTien.h"


// COptionTruongLaoTuTien dialog

IMPLEMENT_DYNAMIC(COptionTruongLaoTuTien, CVIETabDialog)

COptionTruongLaoTuTien::COptionTruongLaoTuTien(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionTruongLaoTuTien::IDD, pParent)
{
	m_activity = act_trucdietaclinh;
}

COptionTruongLaoTuTien::~COptionTruongLaoTuTien()
{
}

void COptionTruongLaoTuTien::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK_NOCHECK, m_chkNoCheckCountTime);
	DDX_Control(pDX, IDC_CHECK_OPEN_SETTING, m_chkOpenSetting);
	DDX_Control(pDX, IDC_CHECK_SETTIME, m_chkGotoBossTime);
	DDX_Control(pDX, IDC_CHECK_NOTAUTO_CHOOSE, m_chkPlayerCheck);
	DDX_Control(pDX, IDC_COMBO_TIME, m_cbTimeToBoss);
}


BEGIN_MESSAGE_MAP(COptionTruongLaoTuTien, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionTruongLaoTuTien::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_NOCHECK, &COptionTruongLaoTuTien::OnBnClickedCheckNocheck)
	ON_BN_CLICKED(IDC_CHECK_OPEN_SETTING, &COptionTruongLaoTuTien::OnBnClickedCheckOpenSetting)
	ON_BN_CLICKED(IDC_CHECK_SETTIME, &COptionTruongLaoTuTien::OnBnClickedCheckSettime)
	ON_BN_CLICKED(IDC_CHECK_NOTAUTO_CHOOSE, &COptionTruongLaoTuTien::OnBnClickedCheckNotautoChoose)
	ON_CBN_SELCHANGE(IDC_COMBO_TIME, &COptionTruongLaoTuTien::OnCbnSelchangeComboTime)
END_MESSAGE_MAP()


BOOL COptionTruongLaoTuTien::OnInitDialog(){

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

	m_cbTimeToBoss.AddString(L"0");
	m_cbTimeToBoss.AddString(L"3");
	m_cbTimeToBoss.AddString(L"5");
	m_cbTimeToBoss.AddString(L"7");
	m_cbTimeToBoss.AddString(L"9");
	m_cbTimeToBoss.AddString(L"15");
	m_cbTimeToBoss.AddString(L"19");
	delete pTemp;
	return TRUE;
}
void COptionTruongLaoTuTien::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkNoCheckCountTime.SetCheck(pTab->bTDALNotCheckCountTime);
	m_chkOpenSetting.SetCheck(pTab->bTDALOpenSetting);
	m_chkGotoBossTime.SetCheck(pTab->bTDALTimeGotoBoss);
	m_chkPlayerCheck.SetCheck(pTab->bTDALPlayerSet);
	m_cbTimeToBoss.SetCurSel(pTab->iTDALTime);
}

void COptionTruongLaoTuTien::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionTruongLaoTuTien::OnBnClickedCheckNotautoChoose()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTDALPlayerSet = m_chkPlayerCheck.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;

}

//void COptionTruongLaoTuTien::OnBnClickedCheckFollowLeader()
//{
//	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
//	if(!pGame) return;
//	OPTIONTAB *pTab = pGame->GetOptionTab();
//	pTab->bTDALFollowLeader = m_chkFollowLeader.GetCheck() == TRUE;
//	pGame->m_bSyncOptionTab = TRUE;
//}

void COptionTruongLaoTuTien::OnBnClickedCheckNocheck()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTDALNotCheckCountTime = m_chkNoCheckCountTime.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionTruongLaoTuTien::OnBnClickedCheckOpenSetting()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTDALOpenSetting = m_chkOpenSetting.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionTruongLaoTuTien::OnBnClickedCheckSettime()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTDALTimeGotoBoss = m_chkGotoBossTime.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionTruongLaoTuTien::OnCbnSelchangeComboTime()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iTDALTime = m_cbTimeToBoss.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}
