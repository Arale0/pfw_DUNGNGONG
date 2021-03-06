//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionBayBan.h"


// COptionBayBan dialog

IMPLEMENT_DYNAMIC(COptionBayBan, CVIETabDialog)

COptionBayBan::COptionBayBan(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionBayBan::IDD, pParent)
{
	m_activity = act_mainquest;
}

COptionBayBan::~COptionBayBan()
{
}

void COptionBayBan::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK_ORANGE_FOOD, m_chkOrangeFood);
	DDX_Control(pDX, IDC_CHECK_ORANGE_EQUIPS, m_chkOrangeEquips);
	DDX_Control(pDX, IDC_CHECK_LV59, m_chkLV59);
	DDX_Control(pDX, IDC_CHECK_LV69, m_chkLV69);
	DDX_Control(pDX, IDC_CHECK_LV89, m_chkLV89);
	DDX_Control(pDX, IDC_CHECK_LV79, m_chkLV79);
	
	DDX_Control(pDX, IDC_BUTTON_30L, m_btnSellPercent[0]);
	DDX_Control(pDX, IDC_BUTTON_20L, m_btnSellPercent[1]);
	DDX_Control(pDX, IDC_BUTTON_10L, m_btnSellPercent[2]);
	DDX_Control(pDX, IDC_BUTTON_0, m_btnSellPercent[3]);
	DDX_Control(pDX, IDC_BUTTON_10R, m_btnSellPercent[4]);
	DDX_Control(pDX, IDC_BUTTON_20R, m_btnSellPercent[5]);
	DDX_Control(pDX, IDC_BUTTON_30R, m_btnSellPercent[6]);

}


BEGIN_MESSAGE_MAP(COptionBayBan, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionBayBan::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_ORANGE_FOOD, &COptionBayBan::OnBnClickedCheckOrangeFood)
	ON_BN_CLICKED(IDC_CHECK_ORANGE_EQUIPS, &COptionBayBan::OnBnClickedCheckOrangeEquips)
	ON_BN_CLICKED(IDC_CHECK_LV59, &COptionBayBan::OnBnClickedCheckLv59)
	ON_BN_CLICKED(IDC_CHECK_LV69, &COptionBayBan::OnBnClickedCheckLv69)
	ON_BN_CLICKED(IDC_CHECK_LV79, &COptionBayBan::OnBnClickedCheckLv79)
	ON_BN_CLICKED(IDC_CHECK_LV89, &COptionBayBan::OnBnClickedCheckLv89)
	ON_BN_CLICKED(IDC_BUTTON_30L, &COptionBayBan::OnBnClickedButton30l)
	ON_BN_CLICKED(IDC_BUTTON_20L, &COptionBayBan::OnBnClickedButton20l)
	ON_BN_CLICKED(IDC_BUTTON_10L, &COptionBayBan::OnBnClickedButton10l)
	ON_BN_CLICKED(IDC_BUTTON_0, &COptionBayBan::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_10R, &COptionBayBan::OnBnClickedButton10r)
	ON_BN_CLICKED(IDC_BUTTON_20R, &COptionBayBan::OnBnClickedButton20r)
	ON_BN_CLICKED(IDC_BUTTON_30R, &COptionBayBan::OnBnClickedButton30r)
END_MESSAGE_MAP()


BOOL COptionBayBan::OnInitDialog(){

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
void COptionBayBan::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkOrangeFood.SetCheck(pTab->bSellOrangeFood);
	m_chkOrangeEquips.SetCheck(pTab->bSellOrangeEquips);
	m_chkLV59.SetCheck(pTab->bSellLV59);
	m_chkLV69.SetCheck(pTab->bSellLV69);
	m_chkLV79.SetCheck(pTab->bSellLV79);
	m_chkLV89.SetCheck(pTab->bSellLV89);
	UpdateUI_SellPercent_SelectIndex(pTab->iSellPercent);

}

void COptionBayBan::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionBayBan::OnBnClickedCheckOrangeFood()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellOrangeFood = m_chkOrangeFood.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBan::OnBnClickedCheckOrangeEquips()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellOrangeEquips = m_chkOrangeEquips.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBan::OnBnClickedCheckLv59()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellLV59 = m_chkLV59.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBan::OnBnClickedCheckLv69()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellLV69 = m_chkLV69.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBan::OnBnClickedCheckLv79()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellLV79 = m_chkLV79.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBan::OnBnClickedCheckLv89()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellLV89 = m_chkLV89.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBan::OnBnClickedButton30l()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int i = 1;
	pTab->iSellPercent = i;
	UpdateUI_SellPercent_SelectIndex(i);
}

void COptionBayBan::OnBnClickedButton20l()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int i = 2;
	pTab->iSellPercent = i;
	UpdateUI_SellPercent_SelectIndex(i);
}

void COptionBayBan::OnBnClickedButton10l()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int i = 3;
	pTab->iSellPercent = i;
	UpdateUI_SellPercent_SelectIndex(i);
}

void COptionBayBan::OnBnClickedButton0()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int i = 0;
	pTab->iSellPercent = i;
	UpdateUI_SellPercent_SelectIndex(i);
}

void COptionBayBan::OnBnClickedButton10r()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int i = 4;
	pTab->iSellPercent = i;
	UpdateUI_SellPercent_SelectIndex(i);
}

void COptionBayBan::OnBnClickedButton20r()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int i = 5;
	pTab->iSellPercent = i;
	UpdateUI_SellPercent_SelectIndex(i);
}

void COptionBayBan::OnBnClickedButton30r()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int i = 6;
	pTab->iSellPercent = i;
	UpdateUI_SellPercent_SelectIndex(i);
}

void COptionBayBan::UpdateUI_SellPercent_SelectIndex( int idx )
{
	UpdateUI_Reset_SellPercent_Color();
	COLORREF clr = RGB(32, 0, 206);
	m_btnSellPercent[idx].SetTextColor(clr);
	m_btnSellPercent[idx].SetBorderColor(clr, clr);
}

void COptionBayBan::UpdateUI_Reset_SellPercent_Color()
{
	for(int i = 0; i< 7; i++){
		m_btnSellPercent[i].SetFlatStyle(TRUE, TRUE);
		COLORREF clr = RGB(209, 210, 203);
		m_btnSellPercent[i].SetTextColor(clr);
		m_btnSellPercent[i].SetBorderColor(clr, clr);
	}
}
