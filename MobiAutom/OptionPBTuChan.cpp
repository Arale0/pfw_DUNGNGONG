//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionPBTuChan.h"


// COptionPBTuChan dialog

IMPLEMENT_DYNAMIC(COptionPBTuChan, CVIETabDialog)

COptionPBTuChan::COptionPBTuChan(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionPBTuChan::IDD, pParent)
{
	m_activity = act_pbtuchan;
}

COptionPBTuChan::~COptionPBTuChan()
{
}

void COptionPBTuChan::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_COMBO_DIFFICULT, m_cbDifficult);
	DDX_Control(pDX, IDC_COMBO_TC_DIFFICULT, m_cbCountTime);

	DDX_Control(pDX, IDC_RADIO_LV29, m_radLV29);
	DDX_Control(pDX, IDC_RADIO_LV35, m_radLV35);
	DDX_Control(pDX, IDC_RADIO_LV59, m_radLV59);
	DDX_Control(pDX, IDC_RADIO_LV69, m_radLV69);
	DDX_Control(pDX, IDC_RADIO_LV89, m_radLV89);
	DDX_Control(pDX, IDC_CHECK_LEADER_SKIP, m_chkLeaderSkip);
	DDX_Control(pDX, IDC_CHECK_MEM_AUTOSEARCH, m_chkMemAutoSearch);
	DDX_Control(pDX, IDC_CHECK_2_TIME, m_chk2TimeToFinished);
	DDX_Control(pDX, IDC_STATIC_COUNTTIME, m_lblCountTime);
}


BEGIN_MESSAGE_MAP(COptionPBTuChan, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionPBTuChan::OnBnClickedButtonBack)
	ON_CBN_SELCHANGE(IDC_COMBO_DIFFICULT, &COptionPBTuChan::OnCbnSelchangeComboDifficult)
	ON_BN_CLICKED(IDC_RADIO_LV35, &COptionPBTuChan::OnBnClickedRadioLv35)
	ON_BN_CLICKED(IDC_RADIO_LV59, &COptionPBTuChan::OnBnClickedRadioLv59)
	ON_BN_CLICKED(IDC_RADIO_LV69, &COptionPBTuChan::OnBnClickedRadioLv69)
	ON_CBN_SELCHANGE(IDC_COMBO_TC_DIFFICULT, &COptionPBTuChan::OnCbnSelchangeComboTcDifficult)
	ON_BN_CLICKED(IDC_RADIO_LV29, &COptionPBTuChan::OnBnClickedRadioLv29)
	ON_BN_CLICKED(IDC_CHECK_LEADER_SKIP, &COptionPBTuChan::OnBnClickedCheckLeaderSkip)
	ON_BN_CLICKED(IDC_RADIO_LV89, &COptionPBTuChan::OnBnClickedRadioLv89)
	ON_BN_CLICKED(IDC_CHECK_MEM_AUTOSEARCH, &COptionPBTuChan::OnBnClickedCheckMemAutosearch)
	ON_BN_CLICKED(IDC_CHECK_2_TIME, &COptionPBTuChan::OnBnClickedCheck2Time)
	ON_STN_CLICKED(IDC_STATIC_COUNTTIME, &COptionPBTuChan::OnStnClickedStaticCounttime)
END_MESSAGE_MAP()


BOOL COptionPBTuChan::OnInitDialog(){

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



	m_cbDifficult.AddString(L"Thanh Y Chủng");
	m_cbDifficult.AddString(L"Cốc Thiên Kiếp");
	m_cbDifficult.AddString(L"Oán Linh Môn");
	m_cbDifficult.AddString(L"Hang Báu Vật");
	m_cbDifficult.AddString(L"Tiên Ma Ảo Thiên");
	m_cbDifficult.AddString(L"Đào Nguyên Luyện Ngục");
	m_cbDifficult.AddString(L"Thanh Y Chủng-Ngục");
	m_cbDifficult.AddString(L"Phiêu Miểu Tiên Cư");
	m_cbDifficult.AddString(L"Cốc Thiên Kiếp-Thần");
	m_cbDifficult.AddString(L"Oán Linh Môn-Quỷ");

	m_cbCountTime.AddString(L"1");
	m_cbCountTime.AddString(L"2");
	m_cbCountTime.AddString(L"3");
	m_cbCountTime.AddString(L"4");
	m_cbCountTime.AddString(L"5");/*
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
	m_cbCount.AddString(L"20");*/

	delete pTemp;
	return TRUE;
}
void COptionPBTuChan::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_radLV29.SetCheck(pTab->iTCDifficult == 0);
	m_radLV35.SetCheck(pTab->iTCDifficult == 1);
	m_radLV59.SetCheck(pTab->iTCDifficult == 3);
	m_radLV69.SetCheck(pTab->iTCDifficult == 4);
	m_cbCountTime.SetCurSel(pTab->iTCCountTime);
	m_chkLeaderSkip.SetCheck(pTab->bTCLeaderSkip);
	m_chkMemAutoSearch.SetCheck(pTab->bTCMemAutoSearch);
	m_chk2TimeToFinished.SetCheck(pTab->bTC2TimeToFinished);
	//LOGW_ERROR(L"pTab->iTCDifficult == %d", pTab->iTCDifficult);
	pGame->m_bSyncOptionTab = TRUE;

	if (pTab->bTC2TimeToFinished) m_cbCountTime.EnableWindow(FALSE);
	if (!pTab->bTC2TimeToFinished) m_cbCountTime.EnableWindow(TRUE);

}

void COptionPBTuChan::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionPBTuChan::OnCbnSelchangeComboDifficult()
{
	/*CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iTCDifficult = m_cbDifficult.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;*/
}

void COptionPBTuChan::OnBnClickedRadioLv35()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iPb = 1;/*1;*/
	pTab->iTCDifficult = iPb;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnBnClickedRadioLv59()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iPb = 3;
	pTab->iTCDifficult = iPb;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnBnClickedRadioLv69()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iPb = 4;
	pTab->iTCDifficult = iPb;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnCbnSelchangeComboTcDifficult()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iTCCountTime = m_cbCountTime.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnBnClickedRadioLv29()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iPb = 0;
	pTab->iTCDifficult = iPb;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnBnClickedCheckLeaderSkip()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTCLeaderSkip = m_chkLeaderSkip.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnBnClickedRadioLv89()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iPb = 5;
	pTab->iTCDifficult = iPb;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnBnClickedCheckMemAutosearch()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTCMemAutoSearch = m_chkMemAutoSearch.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionPBTuChan::OnBnClickedCheck2Time()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTC2TimeToFinished = m_chk2TimeToFinished.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
	if (m_chk2TimeToFinished.GetCheck() == 1) {
		m_cbCountTime.EnableWindow(FALSE);
	}
	else m_cbCountTime.EnableWindow(TRUE);
}

void COptionPBTuChan::OnStnClickedStaticCounttime()
{
	// TODO: Add your control notification handler code here
}
