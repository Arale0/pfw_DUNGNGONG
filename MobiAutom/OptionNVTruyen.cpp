//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionNVTruyen.h"


// COptionNVTruyen dialog

IMPLEMENT_DYNAMIC(COptionNVTruyen, CVIETabDialog)

COptionNVTruyen::COptionNVTruyen(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionNVTruyen::IDD, pParent)
{
	m_activity = act_nvtruyen;
}

COptionNVTruyen::~COptionNVTruyen()
{
}

void COptionNVTruyen::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
}


BEGIN_MESSAGE_MAP(COptionNVTruyen, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionNVTruyen::OnBnClickedButtonBack)
END_MESSAGE_MAP()


BOOL COptionNVTruyen::OnInitDialog(){

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
void COptionNVTruyen::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
}

void COptionNVTruyen::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}
