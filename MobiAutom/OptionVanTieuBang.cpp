//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionVanTieuBang.h"


// COptionVanTieuBang dialog

IMPLEMENT_DYNAMIC(COptionVanTieuBang, CVIETabDialog)

COptionVanTieuBang::COptionVanTieuBang(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionVanTieuBang::IDD, pParent)
{
	m_activity = act_vantieubang;
}

COptionVanTieuBang::~COptionVanTieuBang()
{
}

void COptionVanTieuBang::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK_vt_CLEAN_BAG, m_chkCleanBag);
	DDX_Control(pDX, IDC_CHECK_TV_NOTFOLLOW, m_chkTVNotFollow);
}


BEGIN_MESSAGE_MAP(COptionVanTieuBang, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionVanTieuBang::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_vt_CLEAN_BAG, &COptionVanTieuBang::OnBnClickedCheckvtCleanBag)
	ON_BN_CLICKED(IDC_CHECK_TV_NOTFOLLOW, &COptionVanTieuBang::OnBnClickedCheckTvNotfollow)
END_MESSAGE_MAP()


BOOL COptionVanTieuBang::OnInitDialog(){

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
void COptionVanTieuBang::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkTVNotFollow.SetCheck(pTab->bTVNotFollow);
	m_chkCleanBag.SetCheck((pTab->bVTCleanBag));
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionVanTieuBang::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionVanTieuBang::OnBnClickedCheckvtCleanBag()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bVTCleanBag = m_chkCleanBag.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionVanTieuBang::OnBnClickedCheckTvNotfollow()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTVNotFollow = m_chkTVNotFollow.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}
