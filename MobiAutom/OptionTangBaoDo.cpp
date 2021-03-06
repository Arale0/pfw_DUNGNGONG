//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 
// OptionTLKyCuocDlg.cpp : implementation file


#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionTangBaoDo.h"


// COptionTangBaoDo dialog

IMPLEMENT_DYNAMIC(COptionTangBaoDo, CVIETabDialog)

COptionTangBaoDo::COptionTangBaoDo(CWnd* pParent /*=NULL*/)
	: CVIETabDialog(COptionTangBaoDo::IDD, pParent)
{
	m_activity = act_tangbaodo;
}

COptionTangBaoDo::~COptionTangBaoDo()
{
}

void COptionTangBaoDo::DoDataExchange(CDataExchange* pDX)
{
	CVIETabDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_CHECK_TDB_KHOA, m_chkTBDKhoa);
	DDX_Control(pDX, IDC_CHECK_TDB_TRUNG, m_chkTBDTrung);
	DDX_Control(pDX, IDC_CHECK_TDB_CAO, m_chkTBDCao);
}


BEGIN_MESSAGE_MAP(COptionTangBaoDo, CVIETabDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &COptionTangBaoDo::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_CHECK_TDB_KHOA, &COptionTangBaoDo::OnBnClickedCheckTdbKhoa)
	ON_BN_CLICKED(IDC_CHECK_TDB_TRUNG, &COptionTangBaoDo::OnBnClickedCheckTdbTrung)
	ON_BN_CLICKED(IDC_CHECK_TDB_CAO, &COptionTangBaoDo::OnBnClickedCheckTdbCao)
END_MESSAGE_MAP()


BOOL COptionTangBaoDo::OnInitDialog(){

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
void COptionTangBaoDo::UpdateControls(CGameInfo* pGame)
{
	if (!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkTBDKhoa.SetCheck(pTab->bTBDGiaoDich);
	m_chkTBDTrung.SetCheck(pTab->bTBDTrung);
	m_chkTBDCao.SetCheck(pTab->bTBDCao);
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionTangBaoDo::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_ACTIVITY);
}

void COptionTangBaoDo::OnBnClickedCheckTdbKhoa()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTBDGiaoDich		= m_chkTBDKhoa.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionTangBaoDo::OnBnClickedCheckTdbTrung()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTBDTrung		= m_chkTBDTrung.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionTangBaoDo::OnBnClickedCheckTdbCao()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTBDCao		= m_chkTBDCao.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}
