//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionPBHoangHon.h"


// COptionPBHoangHon dialog

IMPLEMENT_DYNAMIC(COptionPBHoangHon, CVIETabDialog)

COptionPBHoangHon::COptionPBHoangHon(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionPBHoangHon::IDD, pParent)
{
	m_activity = act_pbhoanghon;
}

COptionPBHoangHon::~COptionPBHoangHon()
{
}

void COptionPBHoangHon::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_COMBO_DIFFICULT, m_cbDifficult);
	DDX_Control(pDX, IDC_COMBO_DIFFICULT2, m_cbCount);
	DDX_Control(pDX, IDC_CHECK_LEADER_SKIP, m_chkLeaderSkip);
	DDX_Control(pDX, IDC_CHECK_MEM_AUTOSEARCH, m_chkMemAutoSearch);
}


BEGIN_MESSAGE_MAP(COptionPBHoangHon, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionPBHoangHon::OnBnClickedButtonBack)
	ON_CBN_SELCHANGE(IDC_COMBO_DIFFICULT, &COptionPBHoangHon::OnCbnSelchangeComboDifficult)
	ON_CBN_SELCHANGE(IDC_COMBO_DIFFICULT2, &COptionPBHoangHon::OnCbnSelchangeComboTime)
	ON_BN_CLICKED(IDC_CHECK_LEADER_SKIP, &COptionPBHoangHon::OnBnClickedCheckLeaderSkip)
	ON_BN_CLICKED(IDC_CHECK_MEM_AUTOSEARCH, &COptionPBHoangHon::OnBnClickedCheckMemAutosearch)
END_MESSAGE_MAP()


BOOL COptionPBHoangHon::OnInitDialog(){

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

	
	m_cbDifficult.AddString(L"Sơ Thám");
	m_cbDifficult.AddString(L"Không");
	m_cbDifficult.AddString(L"Phá");
	m_cbDifficult.AddString(L"Diệt");
	m_cbDifficult.AddString(L"Nguyên");
	m_cbDifficult.AddString(L"Chân");

	m_cbCount.AddString(L"1");
	m_cbCount.AddString(L"2");
	m_cbCount.AddString(L"3");
	m_cbCount.AddString(L"4");
	m_cbCount.AddString(L"5");
	m_cbCount.AddString(L"6");
	m_cbCount.AddString(L"7");
	m_cbCount.AddString(L"8");
	m_cbCount.AddString(L"9");
	m_cbCount.AddString(L"10");
	m_cbCount.AddString(L"11");
	m_cbCount.AddString(L"12");
	m_cbCount.AddString(L"13");
	m_cbCount.AddString(L"14");
	m_cbCount.AddString(L"15");
	m_cbCount.AddString(L"16");
	m_cbCount.AddString(L"17");
	m_cbCount.AddString(L"18");
	m_cbCount.AddString(L"19");
	m_cbCount.AddString(L"20");

	delete pTemp;
	return TRUE;
}
void COptionPBHoangHon::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_cbDifficult.SetCurSel(pTab->iHHDifficult);
	m_cbCount.SetCurSel(pTab->iHHCountTime);
	m_chkLeaderSkip.SetCheck(pTab->bHHLeaderSkip);
	m_chkMemAutoSearch.SetCheck(pTab->bHHMemAutoSearch);
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBHoangHon::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionPBHoangHon::OnCbnSelchangeComboDifficult()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iHHDifficult = m_cbDifficult.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBHoangHon::OnCbnSelchangeComboTime()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iHHCountTime = m_cbCount.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
	// TODO: Add your control notification handler code here
}

void COptionPBHoangHon::OnBnClickedCheckLeaderSkip()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bHHLeaderSkip = m_chkLeaderSkip.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBHoangHon::OnBnClickedCheckMemAutosearch()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bHHMemAutoSearch = m_chkMemAutoSearch.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}
