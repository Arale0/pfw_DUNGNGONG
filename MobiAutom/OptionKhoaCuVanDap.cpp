//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionKhoaCuVanDap.h"


// COptionKhoaCuVanDap dialog

IMPLEMENT_DYNAMIC(COptionKhoaCuVanDap, CVIETabDialog)

COptionKhoaCuVanDap::COptionKhoaCuVanDap(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionKhoaCuVanDap::IDD, pParent)
{
	m_activity = act_khoacuvandap;
}

COptionKhoaCuVanDap::~COptionKhoaCuVanDap()
{
}

void COptionKhoaCuVanDap::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
}


BEGIN_MESSAGE_MAP(COptionKhoaCuVanDap, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionKhoaCuVanDap::OnBnClickedButtonBack)
END_MESSAGE_MAP()


BOOL COptionKhoaCuVanDap::OnInitDialog(){

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
void COptionKhoaCuVanDap::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
}

void COptionKhoaCuVanDap::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}
