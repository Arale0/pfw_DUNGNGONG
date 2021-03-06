//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionChienTuBang.h"


// COptionChienTuBang dialog

IMPLEMENT_DYNAMIC(COptionChienTuBang, CVIETabDialog)

COptionChienTuBang::COptionChienTuBang(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionChienTuBang::IDD, pParent)
{
	m_activity = act_chientubang;
}

COptionChienTuBang::~COptionChienTuBang()
{
}

void COptionChienTuBang::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK13, m_chk13);
	DDX_Control(pDX, IDC_CHECK14, m_chk14);
	DDX_Control(pDX, IDC_CHECK15, m_chk15);
	DDX_Control(pDX, IDC_CHECK16, m_chk16);
	DDX_Control(pDX, IDC_CHECK17, m_chk17);
	DDX_Control(pDX, IDC_CHECK18, m_chk18);
	DDX_Control(pDX, IDC_CHECK19, m_chk19);
}


BEGIN_MESSAGE_MAP(COptionChienTuBang, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionChienTuBang::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK13, &COptionChienTuBang::OnBnClickedCheck13)
	ON_BN_CLICKED(IDC_CHECK14, &COptionChienTuBang::OnBnClickedCheck14)
	ON_BN_CLICKED(IDC_CHECK15, &COptionChienTuBang::OnBnClickedCheck15)
	ON_BN_CLICKED(IDC_CHECK16, &COptionChienTuBang::OnBnClickedCheck16)
	ON_BN_CLICKED(IDC_CHECK17, &COptionChienTuBang::OnBnClickedCheck17)
	ON_BN_CLICKED(IDC_CHECK18, &COptionChienTuBang::OnBnClickedCheck18)
	ON_BN_CLICKED(IDC_CHECK19, &COptionChienTuBang::OnBnClickedCheck19)
END_MESSAGE_MAP()


BOOL COptionChienTuBang::OnInitDialog(){

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
void COptionChienTuBang::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();

	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex =0;
	if(timeIndex < MAX_ACTIVITY_PERIOD) m_chk13.SetCheck(pActInfo->time[timeIndex].bChecked);timeIndex++;
	if(timeIndex < MAX_ACTIVITY_PERIOD) m_chk14.SetCheck(pActInfo->time[timeIndex].bChecked);timeIndex++;
	if(timeIndex < MAX_ACTIVITY_PERIOD) m_chk15.SetCheck(pActInfo->time[timeIndex].bChecked);timeIndex++;
	if(timeIndex < MAX_ACTIVITY_PERIOD) m_chk16.SetCheck(pActInfo->time[timeIndex].bChecked);timeIndex++;
	if(timeIndex < MAX_ACTIVITY_PERIOD) m_chk17.SetCheck(pActInfo->time[timeIndex].bChecked);timeIndex++;
	if(timeIndex < MAX_ACTIVITY_PERIOD) m_chk18.SetCheck(pActInfo->time[timeIndex].bChecked);timeIndex++;
	if(timeIndex < MAX_ACTIVITY_PERIOD) m_chk19.SetCheck(pActInfo->time[timeIndex].bChecked);timeIndex++;

	//LogWriteA("timeIndex == %d", timeIndex);
	pGame->m_bSyncOptionTab = TRUE;
	//m_chk19h30.SetCheck(pTab->bCTB19h30);
}

void COptionChienTuBang::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionChienTuBang::OnBnClickedCheck13()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex = 0;
	pActInfo->time[timeIndex].bChecked = m_chk13.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionChienTuBang::OnBnClickedCheck14()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex = 1;
	pActInfo->time[timeIndex].bChecked = m_chk14.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionChienTuBang::OnBnClickedCheck15()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex = 2;
	pActInfo->time[timeIndex].bChecked = m_chk15.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionChienTuBang::OnBnClickedCheck16()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex = 3;
	pActInfo->time[timeIndex].bChecked = m_chk16.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionChienTuBang::OnBnClickedCheck17()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex = 4;
	pActInfo->time[timeIndex].bChecked = m_chk17.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionChienTuBang::OnBnClickedCheck18()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex = 5;
	pActInfo->time[timeIndex].bChecked = m_chk18.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionChienTuBang::OnBnClickedCheck19()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	ACTIVITYINFO *pActInfo = &pGame->GetActivityTab()->lstActivity[m_activity];
	int timeIndex = 6;
	pActInfo->time[timeIndex].bChecked = m_chk19.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}
