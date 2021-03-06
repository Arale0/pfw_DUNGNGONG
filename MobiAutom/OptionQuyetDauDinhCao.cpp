//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionQuyetDauDinhCao.h"


// COptionQuyetDauDinhCao dialog

IMPLEMENT_DYNAMIC(COptionQuyetDauDinhCao, CVIETabDialog)

COptionQuyetDauDinhCao::COptionQuyetDauDinhCao(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionQuyetDauDinhCao::IDD, pParent)
{
	m_activity = act_quyetdaudinhcao;
}

COptionQuyetDauDinhCao::~COptionQuyetDauDinhCao()
{
}

void COptionQuyetDauDinhCao::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK_RANDOM, m_chkRandom);
}


BEGIN_MESSAGE_MAP(COptionQuyetDauDinhCao, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionQuyetDauDinhCao::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_RANDOM, &COptionQuyetDauDinhCao::OnBnClickedCheckRandom)
END_MESSAGE_MAP()


BOOL COptionQuyetDauDinhCao::OnInitDialog(){

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
void COptionQuyetDauDinhCao::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkRandom.SetCheck(pTab->bQDDCRandom);
}

void COptionQuyetDauDinhCao::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionQuyetDauDinhCao::OnBnClickedCheckRandom()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bQDDCRandom	= m_chkRandom.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}
