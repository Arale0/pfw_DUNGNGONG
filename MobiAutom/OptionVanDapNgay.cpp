//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionVanDapNgay.h"


// COptionVanDapNgay dialog

IMPLEMENT_DYNAMIC(COptionVanDapNgay, CVIETabDialog)

COptionVanDapNgay::COptionVanDapNgay(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionVanDapNgay::IDD, pParent)
{
	m_activity = act_vandapngay;
}

COptionVanDapNgay::~COptionVanDapNgay()
{
}

void COptionVanDapNgay::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
}


BEGIN_MESSAGE_MAP(COptionVanDapNgay, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionVanDapNgay::OnBnClickedButtonBack)
END_MESSAGE_MAP()


BOOL COptionVanDapNgay::OnInitDialog(){

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
void COptionVanDapNgay::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
}

void COptionVanDapNgay::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}
