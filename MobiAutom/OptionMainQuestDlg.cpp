// OptionMainQuestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionMainQuestDlg.h"


// COptionMainQuestDlg dialog

IMPLEMENT_DYNAMIC(COptionMainQuestDlg, CVIEChildDlg)

COptionMainQuestDlg::COptionMainQuestDlg(CWnd* pParent /*=NULL*/)
	: CVIEChildDlg(COptionMainQuestDlg::IDD, pParent)
{

}

COptionMainQuestDlg::~COptionMainQuestDlg()
{
}

void COptionMainQuestDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_LEVEL_LIMITED, m_chkLevelLimited);
}


BEGIN_MESSAGE_MAP(COptionMainQuestDlg, CVIEChildDlg)
	ON_BN_CLICKED(IDC_CHECK_LEVEL_LIMITED, &COptionMainQuestDlg::OnBnClickedCheckLevelLimited)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionMainQuestDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// COptionMainQuestDlg message handlers

void COptionMainQuestDlg::OnBnClickedCheckLevelLimited()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	ACTIVITYINFOEX_MAINQUEST *pTab = pGame->GetOptionMainQuest();
	pTab->iLevelLimit = m_chkLevelLimited.GetCheck();
	LOGA_DEBUG("pTab->iLevelLimit %d",pTab->iLevelLimit);
}

void COptionMainQuestDlg::UpdateControls(CGameInfo* pGame)
{
	if(!pGame) return;
	ACTIVITYINFOEX_MAINQUEST *pTab = pGame->GetOptionMainQuest();

	m_chkLevelLimited.SetCheck(pTab->iLevelLimit);
}

void COptionMainQuestDlg::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}