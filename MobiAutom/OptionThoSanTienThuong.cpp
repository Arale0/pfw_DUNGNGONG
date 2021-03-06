//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionThoSanTienThuong.h"


// COptionThoSanTienThuong dialog

IMPLEMENT_DYNAMIC(COptionThoSanTienThuong, CVIETabDialog)

COptionThoSanTienThuong::COptionThoSanTienThuong(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionThoSanTienThuong::IDD, pParent)
{
	m_activity = act_thosantienthuong;
}

COptionThoSanTienThuong::~COptionThoSanTienThuong()
{
}

void COptionThoSanTienThuong::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_RADIO_LV60, m_rd60);
	DDX_Control(pDX, IDC_RADIO_LV70, m_rd70);
	DDX_Control(pDX, IDC_RADIO_LV80, m_rd80);
	DDX_Control(pDX, IDC_RADIO_LV90, m_rd90);
	DDX_Control(pDX, IDC_RADIO_LV100, m_rd100);
}


BEGIN_MESSAGE_MAP(COptionThoSanTienThuong, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionThoSanTienThuong::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_RADIO_LV60, &COptionThoSanTienThuong::OnBnClickedRadioLv60)
	ON_BN_CLICKED(IDC_RADIO_LV70, &COptionThoSanTienThuong::OnBnClickedRadioLv70)
	ON_BN_CLICKED(IDC_RADIO_LV80, &COptionThoSanTienThuong::OnBnClickedRadioLv80)
	ON_BN_CLICKED(IDC_RADIO_LV90, &COptionThoSanTienThuong::OnBnClickedRadioLv90)
	ON_BN_CLICKED(IDC_RADIO_LV100, &COptionThoSanTienThuong::OnBnClickedRadioLv100)
END_MESSAGE_MAP()


BOOL COptionThoSanTienThuong::OnInitDialog(){

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
void COptionThoSanTienThuong::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_rd60.SetCheck(pTab->iTSTTBossLevel == 0);
	m_rd70.SetCheck(pTab->iTSTTBossLevel == 1);
	m_rd80.SetCheck(pTab->iTSTTBossLevel == 2);
	m_rd90.SetCheck(pTab->iTSTTBossLevel == 3);
	m_rd100.SetCheck(pTab->iTSTTBossLevel == 4);
}	

void COptionThoSanTienThuong::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionThoSanTienThuong::OnBnClickedRadioLv60()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iLevel = 0;
	pTab->iTSTTBossLevel = iLevel;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionThoSanTienThuong::OnBnClickedRadioLv70()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iLevel = 1;
	pTab->iTSTTBossLevel = iLevel;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionThoSanTienThuong::OnBnClickedRadioLv80()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iLevel = 2;
	pTab->iTSTTBossLevel = iLevel;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionThoSanTienThuong::OnBnClickedRadioLv90()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iLevel = 3;
	pTab->iTSTTBossLevel = iLevel;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionThoSanTienThuong::OnBnClickedRadioLv100()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iLevel = 4;
	pTab->iTSTTBossLevel = iLevel;
	pGame->m_bSyncOptionTab = TRUE;
}
