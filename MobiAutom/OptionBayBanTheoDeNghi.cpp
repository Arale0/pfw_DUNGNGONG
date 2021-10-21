//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionBayBanTheoDeNghi.h"


// COptionBayBanTheoDeNghi dialog

IMPLEMENT_DYNAMIC(COptionBayBanTheoDeNghi, CVIETabDialog)

COptionBayBanTheoDeNghi::COptionBayBanTheoDeNghi(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionBayBanTheoDeNghi::IDD, pParent)
{
	m_activity = act_baybantheodenghi;
}

COptionBayBanTheoDeNghi::~COptionBayBanTheoDeNghi()
{
}

void COptionBayBanTheoDeNghi::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_COMBO_TBD, m_cbTBD);
	DDX_Control(pDX, IDC_COMBO_TCT, m_cbThienCoTai);
	DDX_Control(pDX, IDC_COMBO_TBIVANG59, m_cbVang59);
}


BEGIN_MESSAGE_MAP(COptionBayBanTheoDeNghi, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionBayBanTheoDeNghi::OnBnClickedButtonBack)
	ON_CBN_SELCHANGE(IDC_COMBO_TBD, &COptionBayBanTheoDeNghi::OnCbnSelchangeComboTbd)
	ON_CBN_SELCHANGE(IDC_COMBO_TCT, &COptionBayBanTheoDeNghi::OnCbnSelchangeComboTct)
	ON_CBN_SELCHANGE(IDC_COMBO_TBIVANG59, &COptionBayBanTheoDeNghi::OnCbnSelchangeComboTbivang59)
END_MESSAGE_MAP()


BOOL COptionBayBanTheoDeNghi::OnInitDialog(){

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

	m_cbTBD.AddString(L"-50%");
	m_cbTBD.AddString(L"-40%");
	m_cbTBD.AddString(L"-30%");
	m_cbTBD.AddString(L"-20%");
	m_cbTBD.AddString(L"-10%");
	m_cbTBD.AddString(L" 0%");
	m_cbTBD.AddString(L"+10%");
	m_cbTBD.AddString(L"+20%");
	m_cbTBD.AddString(L"+30%");
	m_cbTBD.AddString(L"+40%");
	m_cbTBD.AddString(L"+50%");

	m_cbThienCoTai.AddString(L"-50%");
	m_cbThienCoTai.AddString(L"-40%");
	m_cbThienCoTai.AddString(L"-30%");
	m_cbThienCoTai.AddString(L"-20%");
	m_cbThienCoTai.AddString(L"-10%");
	m_cbThienCoTai.AddString(L" 0%");
	m_cbThienCoTai.AddString(L"+10%");
	m_cbThienCoTai.AddString(L"+20%");
	m_cbThienCoTai.AddString(L"+30%");
	m_cbThienCoTai.AddString(L"+40%");
	m_cbThienCoTai.AddString(L"+50%");

	m_cbVang59.AddString(L"-50%");
	m_cbVang59.AddString(L"-40%");
	m_cbVang59.AddString(L"-30%");
	m_cbVang59.AddString(L"-20%");
	m_cbVang59.AddString(L"-10%");
	m_cbVang59.AddString(L" 0%");
	m_cbVang59.AddString(L"+10%");
	m_cbVang59.AddString(L"+20%");
	m_cbVang59.AddString(L"+30%");
	m_cbVang59.AddString(L"+40%");
	m_cbVang59.AddString(L"+50%");
	m_cbVang59.AddString(L"Không bán");


	delete pTemp;
	return TRUE;
}
void COptionBayBanTheoDeNghi::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_cbTBD.SetCurSel(pTab->iPercentGdTBD);
	m_cbThienCoTai.SetCurSel(pTab->iPercentGdThienCoTai);
	m_cbVang59.SetCurSel(pTab->iPercentGdVang59);

}

void COptionBayBanTheoDeNghi::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionBayBanTheoDeNghi::OnCbnSelchangeComboTbd()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iPercentGdTBD = m_cbTBD.GetCurSel();

	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBanTheoDeNghi::OnCbnSelchangeComboTct()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iPercentGdThienCoTai = m_cbThienCoTai.GetCurSel();

	pGame->m_bSyncOptionTab = TRUE;
}

void COptionBayBanTheoDeNghi::OnCbnSelchangeComboTbivang59()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iPercentGdVang59 = m_cbVang59.GetCurSel();

	pGame->m_bSyncOptionTab = TRUE;
}
