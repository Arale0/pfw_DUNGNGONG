// OptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionDlg.h"


// COptionDlg dialog

IMPLEMENT_DYNAMIC(COptionDlg, CVIEChildDlg)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CVIEChildDlg(COptionDlg::IDD, pParent)
{

}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_TEST, m_chkTest);

	DDX_Control(pDX, IDC_CHECK_FULI, m_chkFuli);
	DDX_Control(pDX, IDC_CHECK_ACHIEVEMENT, m_chkAchievement);
	DDX_Control(pDX, IDC_CHECK_CLEANBAG, m_chkCleanBag);
	DDX_Control(pDX, IDC_BUTTON_CLEANBAG_OPTION, m_btnCleanBagOption);
	DDX_Control(pDX, IDC_CHECK_OPTIMIZE_CPU_GPU, m_chkOptimizeCPU);
	DDX_Control(pDX, IDC_RADIO_FPS_MEDIUM, m_radfpsMedium);
	DDX_Control(pDX, IDC_RADIO_FPS_LOW, m_radfpsLow);
	DDX_Control(pDX, IDC_RADIO_FPS_VERYLOW, m_radfpsVeryLow);
	DDX_Control(pDX, IDC_AUTO_BUY_PATCH, m_chkAutoBuyPatch);
	DDX_Control(pDX, IDC_COMBO_HP, m_cbHp);
	DDX_Control(pDX, IDC_COMBO_MP, m_cbMP);
	DDX_Control(pDX, IDC_CHECK_GET_SILVERBOX, m_chkGetSilverBox);
	DDX_Control(pDX, IDC_AUTO_BUY_PATCH_2, m_chkBuyPatch2);
	DDX_Control(pDX, IDC_COMBO_HP_LEVEL, m_cbHPLevel);
	DDX_Control(pDX, IDC_COMBO_MP_LEVEL, m_cbMPLevel);
	DDX_Control(pDX, IDC_CHECK__RUNGAME, m_chkRunGameWCrash);
	DDX_Control(pDX, IDC_CHECK_DYNAMIC, m_chkRecDynamic);
	DDX_Control(pDX, IDC_CHECK_OPTIMIZE_CPU_ACT, m_chkOptimizeCPUAct);
	DDX_Control(pDX, IDC_CHECK_MAIL, m_chkMail);
	DDX_Control(pDX, IDC_CHECK_CDTUCHAN, m_chkCdTuChan);
	DDX_Control(pDX, IDC_TRADE_PIORITY, m_chkTradePiority);
	DDX_Control(pDX, IDC_STATIC_CURRENTID, m_lblCurrentID);
	DDX_Control(pDX, IDC_STATIC_CURRENTID2, m_lblNameUtility);
	DDX_Control(pDX, IDC_CHECK_USEPATCH_RELIVE, m_chkUsePacthRelive);
}


BOOL COptionDlg::OnInitDialog()
{
	CVIEChildDlg::OnInitDialog();
#ifndef BUILD_FLAG_DEBUG
	m_chkTest.ShowWindow(SW_HIDE);
#endif
	m_OptionCleanBag = new COptionCleanBag();
	m_OptionCleanBag->Create(IDD_DIALOG_OPTION_CLEANBAG);
	m_OptionCleanBag->ShowWindow(FALSE);

	m_btnCleanBagOption.SetIcon(IDI_ICON_SETTING,17,17);
	m_btnCleanBagOption.SetFlatStyle(TRUE,FALSE);

	m_cbHp.AddString(L"100");
	m_cbHp.AddString(L"200");
	m_cbHp.AddString(L"300");
	m_cbHp.AddString(L"400");
	m_cbHp.AddString(L"500");
	m_cbHp.AddString(L"600");
	m_cbHp.AddString(L"700");
	m_cbHp.AddString(L"800");
	m_cbHp.AddString(L"900");
	m_cbHp.AddString(L"50");

	m_cbMP.AddString(L"100");
	m_cbMP.AddString(L"200");
	m_cbMP.AddString(L"300");
	m_cbMP.AddString(L"400");
	m_cbMP.AddString(L"500");
	m_cbMP.AddString(L"600");
	m_cbMP.AddString(L"700");
	m_cbMP.AddString(L"800");
	m_cbMP.AddString(L"900");
	m_cbMP.AddString(L"50");

	m_cbMPLevel.AddString(L"Level 1");
	m_cbMPLevel.AddString(L"Level 2");
	m_cbMPLevel.AddString(L"Level 3");
	m_cbMPLevel.AddString(L"Level 4");
	m_cbMPLevel.AddString(L"Level 5");
	m_cbMPLevel.AddString(L"Level 6");
	m_cbMPLevel.AddString(L"Level 7");

	m_cbHPLevel.AddString(L"Level 1");
	m_cbHPLevel.AddString(L"Level 2");
	m_cbHPLevel.AddString(L"Level 3");
	m_cbHPLevel.AddString(L"Level 4");
	m_cbHPLevel.AddString(L"Level 5");
	m_cbHPLevel.AddString(L"Level 6");
	m_cbHPLevel.AddString(L"Level 7");

	return TRUE;
}

BEGIN_MESSAGE_MAP(COptionDlg, CVIEChildDlg)
	ON_BN_CLICKED(IDC_CHECK_TEST, &COptionDlg::OnBnClickedCheckTest)
	ON_BN_CLICKED(IDC_CHECK_FULI, &COptionDlg::OnBnClickedCheckFuli)
	ON_BN_CLICKED(IDC_CHECK_ACHIEVEMENT, &COptionDlg::OnBnClickedCheckAchievement)
	ON_BN_CLICKED(IDC_CHECK_CLEANBAG, &COptionDlg::OnBnClickedCheckCleanbag)
	ON_BN_CLICKED(IDC_RAD_SIZE5, &COptionDlg::OnBnClickedRadSize5)
	ON_BN_CLICKED(IDC_RAD_SIZE10, &COptionDlg::OnBnClickedRadSize10)
	ON_BN_CLICKED(IDC_RAD_SIZE15, &COptionDlg::OnBnClickedRadSize15)
	ON_BN_CLICKED(IDC_BUTTON_CLEANBAG_OPTION, &COptionDlg::OnBnClickedButtonCleanbagOption)
	ON_BN_CLICKED(IDC_CHECK_OPTIMIZE_CPU_GPU, &COptionDlg::OnBnClickedCheckOptimizeCpuGpu)
	ON_BN_CLICKED(IDC_RADIO_FPS_MEDIUM, &COptionDlg::OnBnClickedRadioFpsMedium)
	ON_BN_CLICKED(IDC_RADIO_FPS_LOW, &COptionDlg::OnBnClickedRadioFpsLow)
	ON_BN_CLICKED(IDC_RADIO_FPS_VERYLOW, &COptionDlg::OnBnClickedRadioFpsVerylow)
	ON_BN_CLICKED(IDC_AUTO_BUY_PATCH, &COptionDlg::OnBnClickedAutoBuyPatch)
	ON_CBN_SELCHANGE(IDC_COMBO_HP, &COptionDlg::OnCbnSelchangeComboHp)
	ON_CBN_SELCHANGE(IDC_COMBO_MP, &COptionDlg::OnCbnSelchangeComboMp)
	ON_BN_CLICKED(IDC_CHECK_GET_SILVERBOX, &COptionDlg::OnBnClickedCheckGetSilverbox)
	ON_BN_CLICKED(IDC_AUTO_BUY_PATCH_2, &COptionDlg::OnBnClickedAutoBuyPatch2)
	ON_CBN_SELCHANGE(IDC_COMBO_HP_LEVEL, &COptionDlg::OnCbnSelchangeComboHpLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_MP_LEVEL, &COptionDlg::OnCbnSelchangeComboMpLevel)
	ON_BN_CLICKED(IDC_CHECK__RUNGAME, &COptionDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_DYNAMIC, &COptionDlg::OnBnClickedCheckDynamic)
	ON_BN_CLICKED(IDC_CHECK_OPTIMIZE_CPU_ACT, &COptionDlg::OnBnClickedCheckOptimizeCpuAct)
	ON_BN_CLICKED(IDC_CHECK_MAIL, &COptionDlg::OnBnClickedCheckMail)
	ON_BN_CLICKED(IDC_CHECK_CDTUCHAN, &COptionDlg::OnBnClickedCheckCdtuchan)
	ON_BN_CLICKED(IDC_TRADE_PIORITY, &COptionDlg::OnBnClickedTradePriority)
	ON_BN_CLICKED(IDC_CHECK_USEPATCH_RELIVE, &COptionDlg::OnBnClickedCheckUsepatchRelive)
END_MESSAGE_MAP()


// COptionDlg message handlers

void COptionDlg::OnBnClickedCheckTest()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTest = m_chkTest.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkFuli.SetCheck(pTab->bFuli);
	m_chkAchievement.SetCheck(pTab->bAchievement);
	m_chkCleanBag.SetCheck(pTab->bCleanBag);
	m_chkOptimizeCPU.SetCheck(pTab->bOptimizeCPU);
	m_radfpsMedium.SetCheck(pTab->iOptionFPS == 1);
	m_radfpsLow.SetCheck(pTab->iOptionFPS == 2);
	m_radfpsVeryLow.SetCheck(pTab->iOptionFPS == 3);
	m_chkAutoBuyPatch.SetCheck(pTab->bAutoBuyPatch);
	m_cbHp.SetCurSel(pTab->iAmountOfPatchHP);
	m_cbMP.SetCurSel(pTab->iAmountOfPatchMP);
	m_chkGetSilverBox.SetCheck(pTab->bGetSilverBox);
	m_chkBuyPatch2.SetCheck(pTab->bAutoBuyPatch2);
	m_cbHPLevel.SetCurSel(pTab->iHPLevel);
	m_cbMPLevel.SetCurSel(pTab->iMPLevel);
	m_chkRunGameWCrash.SetCheck(pTab->bRunGameWhenCrash);
	m_chkRecDynamic.SetCheck(pTab->bRecDynamic);
	m_chkOptimizeCPUAct.SetCheck(pTab->bOptimizeCPUAct);
	m_chkMail.SetCheck(pTab->bCheckMail);
	m_chkCdTuChan.SetCheck(pTab->bCdTuChan);
	m_chkTradePiority.SetCheck(pTab->bTradePriority);
	m_chkUsePacthRelive.SetCheck(pTab->bUsePatchRelive);

	updateCurrentID(pGame);
	
	pGame->m_bSyncOptionTab = TRUE;
}


void COptionDlg::OnBnClickedCheckFuli()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bFuli		= m_chkFuli.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheckAchievement()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bAchievement = m_chkAchievement.GetCheck() == TRUE;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheckCleanbag()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bCleanBag		= m_chkCleanBag.GetCheck();
	
	pGame->m_bSyncOptionTab = TRUE;
	// TODO: Add your control notification handler code here
}

void COptionDlg::OnBnClickedRadSize5()
{
	g_pMainDlg->OnChangeUI(0);
}

void COptionDlg::OnBnClickedRadSize10()
{
	g_pMainDlg->OnChangeUI(1);
}

void COptionDlg::OnBnClickedRadSize15()
{
	g_pMainDlg->OnChangeUI(2);
}


void COptionDlg::OnBnClickedButtonCleanbagOption()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	g_pMainDlg->ShowOptionDlg((CWnd*)m_OptionCleanBag,(CWnd*)this);
	m_OptionCleanBag->UpdateControls(pGame);
}

void COptionDlg::OnBnClickedCheckOptimizeCpuGpu()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bOptimizeCPU	= m_chkOptimizeCPU.GetCheck();

	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedRadioFpsMedium()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iFPS = 1;
	pTab->iOptionFPS	= iFPS;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedRadioFpsLow()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iFPS = 2;
	pTab->iOptionFPS	= iFPS;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedRadioFpsVerylow()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	int iFPS = 3;
	pTab->iOptionFPS	= iFPS;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedAutoBuyPatch()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bAutoBuyPatch	= m_chkAutoBuyPatch.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnCbnSelchangeComboHp()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iAmountOfPatchHP	= m_cbHp.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnCbnSelchangeComboMp()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iAmountOfPatchMP	= m_cbMP.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheckGetSilverbox()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bGetSilverBox	= m_chkGetSilverBox.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedAutoBuyPatch2()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bAutoBuyPatch2	= m_chkBuyPatch2.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnCbnSelchangeComboHpLevel()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iHPLevel	= m_cbHPLevel.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnCbnSelchangeComboMpLevel()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->iMPLevel	= m_cbMPLevel.GetCurSel();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheck()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bRunGameWhenCrash	= m_chkRunGameWCrash.GetCheck();
	//pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheckDynamic()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bRecDynamic	= m_chkRecDynamic.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheckOptimizeCpuAct()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bOptimizeCPUAct	= m_chkOptimizeCPUAct.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheckMail()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bCheckMail	= m_chkMail.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedCheckCdtuchan()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bCdTuChan	= m_chkCdTuChan.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::OnBnClickedTradePriority()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTradePriority	= m_chkTradePiority.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionDlg::updateCurrentID( CGameInfo* pGame )
{
	if(!pGame) return;
	CGameInfo *pGame1 = g_pMainDlg->m_pGameSelected;
	if(!pGame1) return;

	CString czCurrentID;
	CString czNameUtility = L"none";
	int iCurrentID = pGame->m_iCurrentID;
	switch(iCurrentID) {
		case 109: 
			czNameUtility = L"Team Doing";
			break;
		case 108: 
			czNameUtility = L"Team Alone Team Doing";
			break;
		case 106: 
			czNameUtility = L"Team Jiebai Team Doing";
			break;
		case 105: 
			czNameUtility = L"Mail Doing";
			break;
		case 104: 
			czNameUtility = L"Fuli Doing";
			break;
		case 103: 
			czNameUtility = L"Bag Doing";
			break;
		case 101: 
			czNameUtility = L"Patch Doing";
			break;
		case 100: 
			czNameUtility = L"Achievement Doing";
			break;
	}

	if (iCurrentID < 100 && iCurrentID >= 0) czNameUtility = L"Actitivy Doing";

	czCurrentID.Format(L"%d", iCurrentID);
	LOGA_DEBUG("Current ID: %d", pGame->m_iCurrentID);
	m_lblCurrentID.SetText(czCurrentID);
	m_lblNameUtility.SetText(czNameUtility);
	//m_edtCurrentID.SetText(czCurrentID);
}

void COptionDlg::OnBnClickedCheckUsepatchRelive()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bUsePatchRelive	= m_chkUsePacthRelive.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}
