//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionDaNgongCuong.h"


// COptionDaNgongCuong dialog

IMPLEMENT_DYNAMIC(COptionDaNgongCuong, CVIETabDialog)

COptionDaNgongCuong::COptionDaNgongCuong(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionDaNgongCuong::IDD, pParent)
{
	m_activity = act_dangongcuong;
}

COptionDaNgongCuong::~COptionDaNgongCuong()
{
}

void COptionDaNgongCuong::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK_BUY_BYGOLDDRAGON, m_chkBuyByGoldDrg);
	DDX_Control(pDX, IDC_COMBO_AMOUNT, m_cbAmountOf);
}


BEGIN_MESSAGE_MAP(COptionDaNgongCuong, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionDaNgongCuong::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_BUY_BYGOLDDRAGON, &COptionDaNgongCuong::OnBnClickedCheckBuyBygolddragon)
	ON_CBN_SELCHANGE(IDC_COMBO_AMOUNT, &COptionDaNgongCuong::OnCbnSelchangeComboAmount)
END_MESSAGE_MAP()


BOOL COptionDaNgongCuong::OnInitDialog(){

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

	m_cbAmountOf.AddString(L"100");
	m_cbAmountOf.AddString(L"200");
	m_cbAmountOf.AddString(L"300");
	m_cbAmountOf.AddString(L"400");
	m_cbAmountOf.AddString(L"500");
	m_cbAmountOf.AddString(L"1000");
	m_cbAmountOf.AddString(L"2000");
	delete pTemp;
	return TRUE;
}
void COptionDaNgongCuong::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkBuyByGoldDrg.SetCheck(pTab->bDNCBuyByGold);
	m_cbAmountOf.SetCurSel(pTab->iDNCAmountOf);
	InitControls();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDaNgongCuong::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionDaNgongCuong::OnBnClickedCheckBuyBygolddragon()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bDNCBuyByGold = m_chkBuyByGoldDrg.GetCheck() == TRUE;
	InitControls();
	pGame->m_bSyncOptionTab = TRUE;
	// TODO: Add your control notification handler code here
}

void COptionDaNgongCuong::OnCbnSelchangeComboAmount()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iDNCAmountOf = m_cbAmountOf.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
	// TODO: Add your control notification handler code here
}

void COptionDaNgongCuong::InitControls()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab(); 
	if (m_chkBuyByGoldDrg.GetCheck() == 1 || pTab->bDNCBuyByGold) {
		m_cbAmountOf.EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_BUY)->EnableWindow(TRUE);
	}
	if (m_chkBuyByGoldDrg.GetCheck() == 0 || !pTab->bDNCBuyByGold) {
		m_cbAmountOf.EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_BUY)->EnableWindow(FALSE);
	}
}
