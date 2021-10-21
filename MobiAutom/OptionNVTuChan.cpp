//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionNVTuChan.h"


// COptionNVTuChan dialog

IMPLEMENT_DYNAMIC(COptionNVTuChan, CVIETabDialog)

COptionNVTuChan::COptionNVTuChan(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionNVTuChan::IDD, pParent)
{
	m_activity = act_nvtuchan;
}

COptionNVTuChan::~COptionNVTuChan()
{
}

void COptionNVTuChan::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
}


BEGIN_MESSAGE_MAP(COptionNVTuChan, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionNVTuChan::OnBnClickedButtonBack)
END_MESSAGE_MAP()


BOOL COptionNVTuChan::OnInitDialog(){

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
void COptionNVTuChan::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
}

void COptionNVTuChan::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}
