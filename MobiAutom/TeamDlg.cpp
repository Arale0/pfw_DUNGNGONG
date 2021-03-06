// TeamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "TeamDlg.h"


// CTeamDlg dialog

IMPLEMENT_DYNAMIC(CTeamDlg, CVIEChildDlg)

CTeamDlg::CTeamDlg(CWnd* pParent /*=NULL*/)
	: CVIEChildDlg(CTeamDlg::IDD, pParent)
{

}

CTeamDlg::~CTeamDlg()
{
	KillTimer(m_uiTimeID);
}

void CTeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TEAM, m_lstCtrlTeam);
	DDX_Control(pDX, IDC_RADIO_TEAMMODE_MATCH, m_radTeammodeMatch);
	DDX_Control(pDX, IDC_RADIO_TEAMMODE_LEADER, m_radTeammodeLeader);
	DDX_Control(pDX, IDC_RADIO_TEAMMODE_MEMBER, m_radTeammodeMember);
	DDX_Control(pDX, IDC_RADIO_TEAMMODE_ALONE, m_radTeammodeAlone);
	DDX_Control(pDX, IDC_RADIO_TEAMMODE_INTELLIGENCE, m_radTeammodeIntelligence);
	DDX_Control(pDX, IDC_COMBO_MEMBERNAME, m_cboMemberName);
	DDX_Control(pDX, IDC_BUTTON_TEAM_SAVECHANGE, m_btnSaveChange);
	DDX_Control(pDX, IDC_BUTTON_LOG, m_btnLog);

	//DDX_Control(pDX, IDC_LBL_EXPLAIN, m_lblExplain);
	DDX_Control(pDX, IDC_CHECK_MAKE_FIREND, m_chkJiebai);
	DDX_Control(pDX, IDC_CHECK_KICK_MEMBERS, m_chkKickMembers);


	DDX_Control(pDX, IDC_RADIO_MEMBER3, m_radMem3);
	DDX_Control(pDX, IDC_RADIO_MEMBER4, m_radMem4);
	DDX_Control(pDX, IDC_RADIO_MEMBER5, m_radMem5);
	DDX_Control(pDX, IDC_RADIO_MEMBER6, m_radMem6);
	DDX_Control(pDX, IDC_CHECK_ACEPT_JIEBAI, m_chkAceptJiebai);
	DDX_Control(pDX, IDC_CHECK_EXIT_TEAM, m_chkAloneExitTeam);
	DDX_Control(pDX, IDC_CHECK_TEAM_TARGET, m_chkAloneCheckTeamTarget);
	DDX_Control(pDX, IDC_COMBO_ALONE_TIME, m_cbAloneTime);
	DDX_Control(pDX, IDC_CHECK_INVITE_FRIENDS, m_chkInviteFriends);
	DDX_Control(pDX, IDC_CHECK_ACEPT_FRIEND, m_chkAcceptFriend);
}


BOOL CTeamDlg::OnInitDialog()
{
	CVIEChildDlg::OnInitDialog();
	m_uiTimeID = SetTimer(0,1000,TimerProc);

	m_lstCtrlTeam.InsertColumn(LV_TEAM_INDEX_POS, L"", LVCFMT_LEFT, 30);
	m_lstCtrlTeam.InsertColumn(LV_TEAM_INDEX_NAME, L"Name", LVCFMT_LEFT, 200);
	m_lstCtrlTeam.SetRowAutoBkColor(RGB(255,255,255), RGB(250, 250, 255));
	m_lstCtrlTeam.SetItemsHeight(18);
	
	m_radTeammodeMatch.SetGroupId(1);
	m_radTeammodeLeader.SetGroupId(1);
	m_radTeammodeMember.SetGroupId(1);
	m_radTeammodeAlone.SetGroupId(1);
	m_radTeammodeIntelligence.SetGroupId(1);
	m_btnSaveChange.ShowWindow(SW_HIDE);

	m_cbAloneTime.AddString(L"30s");
	m_cbAloneTime.AddString(L"60s");
	m_cbAloneTime.AddString(L"90s");
	m_cbAloneTime.AddString(L"120s");

	//m_chkInviteFriends.EnableWindow(FALSE);

	/*m_lblExplain.SetFont(L"Tahoma", 8, TRUE);
	m_lblExplain.SetTextColor(RGB(0,0,255));
	m_lblExplain.SetText(L"");*/
	


#ifndef BUILD_FLAG_DEBUG
	m_btnLog.ShowWindow(SW_HIDE);
#endif
	return TRUE;
}



BEGIN_MESSAGE_MAP(CTeamDlg, CVIEChildDlg)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &CTeamDlg::OnBnClickedButtonLog)
	ON_BN_CLICKED(IDC_RADIO_TEAMMODE_MATCH, &CTeamDlg::OnBnClickedRadioTeammodeMatch)
	ON_BN_CLICKED(IDC_RADIO_TEAMMODE_LEADER, &CTeamDlg::OnBnClickedRadioTeammodeLeader)
	ON_BN_CLICKED(IDC_RADIO_TEAMMODE_MEMBER, &CTeamDlg::OnBnClickedRadioTeammodeMember)
	ON_BN_CLICKED(IDC_RADIO_TEAMMODE_ALONE, &CTeamDlg::OnBnClickedRadioTeammodeAlone)
	ON_CBN_DROPDOWN(IDC_COMBO_MEMBERNAME, &CTeamDlg::OnCbnDropdownComboMembername)
	ON_CBN_EDITCHANGE(IDC_COMBO_MEMBERNAME, &CTeamDlg::OnCbnEditchangeComboMembername)
	ON_BN_CLICKED(IDC_BUTTON_TEAM_SAVECHANGE, &CTeamDlg::OnBnClickedButtonTeamSavechange)
	//ON_CBN_KILLFOCUS(IDC_COMBO_MEMBERNAME, &CTeamDlg::OnCbnKillfocusComboMembername)
	ON_CBN_SELCHANGE(IDC_COMBO_MEMBERNAME, &CTeamDlg::OnCbnSelchangeComboMembername)
	ON_BN_CLICKED(IDC_CHECK_MAKE_FIREND, &CTeamDlg::OnBnClickedCheckMakeFirend)
	ON_BN_CLICKED(IDC_CHECK_KICK_MEMBERS, &CTeamDlg::OnBnClickedCheckKickMembers)
	ON_BN_CLICKED(IDC_RADIO_MEMBER3, &CTeamDlg::OnBnClickedRadioMember3)
	ON_BN_CLICKED(IDC_RADIO_MEMBER4, &CTeamDlg::OnBnClickedRadioMember4)
	ON_BN_CLICKED(IDC_RADIO_MEMBER5, &CTeamDlg::OnBnClickedRadioMember5)
	ON_BN_CLICKED(IDC_RADIO_MEMBER6, &CTeamDlg::OnBnClickedRadioMember6)
	ON_BN_CLICKED(IDC_CHECK_ACEPT_JIEBAI, &CTeamDlg::OnBnClickedCheckAceptJiebai)
	ON_BN_CLICKED(IDC_CHECK_EXIT_TEAM, &CTeamDlg::OnBnClickedCheckExitTeam)
	ON_BN_CLICKED(IDC_CHECK_TEAM_TARGET, &CTeamDlg::OnBnClickedCheckTeamTarget)
	ON_CBN_SELCHANGE(IDC_COMBO_ALONE_TIME, &CTeamDlg::OnCbnSelchangeComboAloneTime)
	ON_BN_CLICKED(IDC_RADIO_TEAMMODE_INTELLIGENCE, &CTeamDlg::OnBnClickedRadioTeammodeIntelligence)
	ON_BN_CLICKED(IDC_CHECK_INVITE_FRIENDS, &CTeamDlg::OnBnClickedCheckInviteFriends)
	ON_BN_CLICKED(IDC_CHECK_ACEPT_FRIEND, &CTeamDlg::OnBnClickedCheckAceptFriend)
END_MESSAGE_MAP()

VOID CALLBACK CTeamDlg::TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
	g_pAutoManager->m_TeamList.UpdateTeamList();
	
	CPtrList* lstGame =  g_pGameManager->GetListGame();
	g_pAutoManager->m_TeamList.MatchTeamList(lstGame);
	
	CGameInfo *pGameSelected = g_pMainDlg->m_pGameSelected;
	if(pGameSelected && g_pMainDlg->m_tabMain.GetCurSel() == ID_TEAM_DLG){
		if(pGameSelected->GetTeamTab()->bUpdateNow){
			g_pMainDlg->m_tabMain.m_TeamDlg.UpdateControls(pGameSelected);
		}
	}
}
void CTeamDlg::OnBnClickedButtonLog()
{
	g_pAutoManager->m_TeamList.LogInfo();
}

void CTeamDlg::UpdateControls(CGameInfo *pGame)
{
	if(!pGame) return;
	
	m_lstCtrlTeam.DeleteAllItems();
	m_btnSaveChange.ShowWindow(SW_HIDE);
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->bUpdateNow = FALSE;
	LOGW_DEBUG(L"teammode :%d",pTeamTab->iTeamMode );
	//if(pTeamTab->iTeamMode == TEAMMODE_INTELLIGENCE) m_radTeammodeIntelligence.SetCheck(BST_CHECKED);
	m_radTeammodeMatch.SetCheck(pTeamTab->teamOption.iTeamType == 0);
	m_radTeammodeLeader.SetCheck(pTeamTab->teamOption.iTeamType == 1);
	m_radTeammodeMember.SetCheck(pTeamTab->teamOption.iTeamType == 2);
	m_radTeammodeAlone.SetCheck(pTeamTab->teamOption.iTeamType == 3);
	m_radTeammodeIntelligence.SetCheck(pTeamTab->teamOption.iTeamType == 4);
	//
	if(pTeamTab->iTeamMode == TEAMMODE_MATCH){
		//m_radTeammodeMatch.SetCheck(BST_CHECKED);
		for(int i = 0; i< MAX_NUM_TEAMMEMBER; i++){
			int iIndex = m_lstCtrlTeam.InsertItem(i, L"");
			if(iIndex == 0){
				//m_lstCtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_POS	, L"Leader");
				m_lstCtrlTeam.SetItemIcon(iIndex, LV_TEAM_INDEX_POS, IDI_ICON_FLAG);
			}
			//else CtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_POS	, L"-");
			m_lstCtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_NAME, CUtils::_A2W(pGame->GetTeamTab()->members[i].czTeamName));
		}	
		
		//m_lblExplain.SetText(L"All Roles need join team in auto\r\nwill match team together");
	}
	if(pTeamTab->iTeamMode == TEAMMODE_LEADER){
		for(int i = 0; i< MAX_NUM_TEAMMEMBER; i++){
			int iIndex = m_lstCtrlTeam.InsertItem(i, L"");
			if(iIndex == 0){
				//m_lstCtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_POS	, L"Leader");
				m_lstCtrlTeam.SetItemIcon(iIndex, LV_TEAM_INDEX_POS, IDI_ICON_FLAG);
			}
			else {
				//m_lstCtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_POS	, L"-");
				m_lstCtrlTeam.SetComboBox(iIndex, LV_TEAM_INDEX_NAME, &m_cboMemberName);
			}
			m_lstCtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_NAME, CUtils::_A2W(pGame->GetTeamTab()->members[i].czTeamName));
		}
		//m_radTeammodeLeader.SetCheck(BST_CHECKED);

		//m_lblExplain.SetText(L"You are team leader\r\nSet your teamates manually");
	}
	if(pTeamTab->iTeamMode == TEAMMODE_MEMBER){
		int i = 0;
		int iIndex = m_lstCtrlTeam.InsertItem(i, L"");
		//m_lstCtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_POS	, L"Leader");
		m_lstCtrlTeam.SetItemIcon(iIndex, LV_TEAM_INDEX_POS, IDI_ICON_FLAG);
		m_lstCtrlTeam.SetComboBox(iIndex, LV_TEAM_INDEX_NAME, &m_cboMemberName);
		m_lstCtrlTeam.SetItemText(iIndex, LV_TEAM_INDEX_NAME, CUtils::_A2W(pGame->GetTeamTab()->members[i].czTeamName));
		//m_radTeammodeMember.SetCheck(BST_CHECKED);

		//m_lblExplain.SetText(L"You are team member\r\nSet your team leader manually");
	}

	m_chkAloneCheckTeamTarget.SetCheck(pTeamTab->teamOption.bAloneCheckTeamTarget);
	m_chkAloneExitTeam.SetCheck(pTeamTab->teamOption.bAloneExitTeam);
	m_cbAloneTime.SetCurSel(pTeamTab->teamOption.iAloneCheckTime);

	if(pTeamTab->iTeamMode == TEAMMODE_ALONE){
		//m_radTeammodeAlone.SetCheck(BST_CHECKED);
		//m_lblExplain.SetText(L"You are in alone mode");
	}

	


	//OPTIONTAB *pTab = pGame->GetOptionTab();
	m_chkJiebai.SetCheck(pTeamTab->teamOption.bJiebai);
	m_chkKickMembers.SetCheck(pTeamTab->teamOption.bKickMembers);
	m_chkAceptJiebai.SetCheck(pTeamTab->teamOption.bMemberAcceptJiebai);
	m_chkInviteFriends.SetCheck(pTeamTab->teamOption.bInviteFriends);
	m_chkAcceptFriend.SetCheck(pTeamTab->teamOption.bMemAcceptFriendsInvite);
	m_radMem3.SetCheck(pTeamTab->teamOption.iSLTV == 3);
	m_radMem4.SetCheck(pTeamTab->teamOption.iSLTV == 4);
	m_radMem5.SetCheck(pTeamTab->teamOption.iSLTV == 5);
	m_radMem6.SetCheck(pTeamTab->teamOption.iSLTV == 6);

	
	UpdateTeamControls();
	pTeamTab->bSyncTeamOption = TRUE;


}
void CTeamDlg::UpdateUITeamMode(int teammode){
	if(teammode == TEAMMODE_MATCH){
		m_lstCtrlTeam.ShowWindow(SW_SHOW);
		return;	
	}
	
	if(teammode == TEAMMODE_LEADER){

		m_lstCtrlTeam.ShowWindow(SW_SHOW);
		return;	
	}
	if(teammode == TEAMMODE_MEMBER){
		m_lstCtrlTeam.ShowWindow(SW_SHOW);
		return;	
	}
	if(teammode == TEAMMODE_ALONE){
		m_lstCtrlTeam.ShowWindow(SW_HIDE);
	}
}

void CTeamDlg::OnBnClickedRadioTeammodeMatch()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	if(pTeamTab->iTeamMode != TEAMMODE_MATCH){
		pTeamTab->iTeamMode = TEAMMODE_MATCH;
		pTeamTab->teamOption.iTeamType = pTeamTab->iTeamMode;
		//pGame->ResetTeam();
		UpdateTeamControls();
		pGame->UpdateTeam();
		UpdateUITeamMode(pTeamTab->iTeamMode);
		UpdateControls(pGame);
	}
}

void CTeamDlg::OnBnClickedRadioTeammodeLeader()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	if(pTeamTab->iTeamMode != TEAMMODE_LEADER){
		pTeamTab->iTeamMode = TEAMMODE_LEADER;
		pTeamTab->teamOption.iTeamType = pTeamTab->iTeamMode;
		CTeam *pTeam = g_pAutoManager->m_TeamList.GetTeam(pTeamTab->iTeamId);
		if(pTeam){
			pTeam->UpdateGame();
		}
		/*
		pGame->ResetTeam();
		strcpy_s(pTeamTab->members[0].czTeamName, 64, pGame->m_accountInfo.czRoleName);
		for(int i =1; i < MAX_NUM_TEAMMEMBER; i++){
			strcpy_s(pTeamTab->members[i].czTeamName, 64, pTeamTab->membersInLeaderMode[i].czTeamName);
		}
		pTeamTab->uTimeUpdate = GetTickCount();
		*/
		UpdateTeamControls();
		pGame->UpdateTeam();
		UpdateUITeamMode(pTeamTab->iTeamMode);
		UpdateControls(pGame);
	}
}

void CTeamDlg::OnBnClickedRadioTeammodeMember()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	if(pTeamTab->iTeamMode != TEAMMODE_MEMBER){		
		pTeamTab->iTeamMode = TEAMMODE_MEMBER; 
		pTeamTab->teamOption.iTeamType = pTeamTab->iTeamMode;
		CTeam *pTeam = g_pAutoManager->m_TeamList.GetTeam(pTeamTab->iTeamId);
		if(pTeam){
			pTeam->UpdateGame();
		}
		/*
		pGame->ResetTeam();
		strcpy_s(pTeamTab->members[0].czTeamName, 64, pTeamTab->czLeaderInMemberMode);
		pTeamTab->uTimeUpdate = GetTickCount();
		*/
		UpdateTeamControls();
		pGame->UpdateTeam();
		UpdateUITeamMode(pTeamTab->iTeamMode);
		UpdateControls(pGame);
	}
}

void CTeamDlg::OnBnClickedRadioTeammodeAlone()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	if(pTeamTab->iTeamMode != TEAMMODE_ALONE){
		pTeamTab->iTeamMode = TEAMMODE_ALONE;
		pTeamTab->teamOption.iTeamType = pTeamTab->iTeamMode;		
		CTeam *pTeam = g_pAutoManager->m_TeamList.GetTeam(pTeamTab->iTeamId);
		if(pTeam){
			pTeam->UpdateGame();
		}
		//pGame->ResetTeam();
		UpdateTeamControls();
		pGame->UpdateTeam();
		pTeamTab->uTimeUpdate = GetTickCount();
		UpdateUITeamMode(pTeamTab->iTeamMode);
		UpdateControls(pGame);
	}
}

void CTeamDlg::OnCbnDropdownComboMembername()
{
	CGameInfo *pGameSelected = g_pMainDlg->m_pGameSelected;
	if(!pGameSelected) return;
	m_cboMemberName.ResetContent();
	CPtrList* lstGame = g_pGameManager->GetListGame();
	for(POSITION pos  = lstGame->GetHeadPosition(); pos != NULL;){
		CGameInfo *pGame = (CGameInfo *)lstGame->GetNext(pos);
		if(pGame == pGameSelected) continue;
		if(pGame->m_accountInfo.czRoleName[0] != 0){
			m_cboMemberName.AddString(CUtils::_A2W(pGame->m_accountInfo.czRoleName));
		}
	}
}

void CTeamDlg::OnCbnEditchangeComboMembername()
{
	m_btnSaveChange.ShowWindow(SW_SHOW);
}
void CTeamDlg::OnCbnSelchangeComboMembername()
{
	m_btnSaveChange.ShowWindow(SW_SHOW);
}

void CTeamDlg::OnBnClickedButtonTeamSavechange()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	for(int i= 0; i< MAX_NUM_TEAMMEMBER; i++){
		CString szName =  m_lstCtrlTeam.GetItemText(i, LV_TEAM_INDEX_NAME);
		strcpy_s(pTeamTab->members[i].czTeamName, 64, CUtils::_W2A(szName.GetBuffer()));
	}
	if(pTeamTab->iTeamMode == TEAMMODE_LEADER){
		for(int i= 0; i< MAX_NUM_TEAMMEMBER; i++){
			strcpy_s(pTeamTab->membersInLeaderMode[i].czTeamName, 64, pTeamTab->members[i].czTeamName);
		}
	}
	if(pTeamTab->iTeamMode == TEAMMODE_MEMBER){
		strcpy_s(pTeamTab->czLeaderInMemberMode, 64, pTeamTab->members[0].czTeamName);
	}
	pTeamTab->uTimeUpdate = GetTickCount();
	m_btnSaveChange.ShowWindow(SW_HIDE);
}
/*
void CTeamDlg::OnCbnKillfocusComboMembername()
{
	m_btnSaveChange.ShowWindow(SW_SHOW);
	int item = m_lstCtrlTeam.GetSelectedItem();
	CString szName =  m_lstCtrlTeam.GetItemText(item, LV_TEAM_INDEX_NAME);
	LOGW_DEBUG(L"item %d [%s]", item, szName);
}
*/

void CTeamDlg::OnBnClickedCheckMakeFirend()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.bJiebai = m_chkJiebai.GetCheck();
	LOGW_DEBUG(L"pTeamTab->teamOption.bJiebai === %d", pTeamTab->teamOption.bJiebai);
	UpdateTeamControls();
	pTeamTab->bSyncTeamOption = TRUE;
	// TODO: Add your control notification handler code here
}

void CTeamDlg::OnBnClickedCheckKickMembers()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.bKickMembers = m_chkKickMembers.GetCheck();
	LOGW_DEBUG(L"pTeamTab->teamOption.bJiebai === %d", pTeamTab->teamOption.bKickMembers);
	pTeamTab->bSyncTeamOption = TRUE;
}


void CTeamDlg::OnBnClickedRadioMember3()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	int iSLTV = 3;
	pTeamTab->teamOption.iSLTV = iSLTV;
	pTeamTab->bSyncTeamOption = TRUE;
	// TODO: Add your control notification handler code here
}

void CTeamDlg::OnBnClickedRadioMember4()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	int iSLTV = 4;
	pTeamTab->teamOption.iSLTV = iSLTV;
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::OnBnClickedRadioMember5()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	int iSLTV = 5;
	pTeamTab->teamOption.iSLTV = iSLTV;
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::OnBnClickedRadioMember6()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	int iSLTV = 6;
	pTeamTab->teamOption.iSLTV = iSLTV;
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::UpdateTeamControls()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	

	if(pTeamTab->iTeamMode == TEAMMODE_ALONE) {
		m_lstCtrlTeam.ShowWindow(FALSE);
		m_cbAloneTime.ShowWindow(FALSE);
		m_chkAloneCheckTeamTarget.ShowWindow(FALSE);
		m_chkAloneExitTeam.ShowWindow(TRUE);
	}

	if(pTeamTab->iTeamMode != TEAMMODE_ALONE) {
		m_lstCtrlTeam.ShowWindow(TRUE);
		m_cbAloneTime.ShowWindow(FALSE);
		m_chkAloneCheckTeamTarget.ShowWindow(FALSE);
		m_chkAloneExitTeam.ShowWindow(FALSE);
	}


	if(pTeamTab->iTeamMode == TEAMMODE_LEADER) {
		
		m_chkJiebai.EnableWindow(TRUE);
		m_chkInviteFriends.EnableWindow(TRUE);
		if (m_chkJiebai.GetCheck() == 1 || pTeamTab->teamOption.bJiebai) {
			m_chkKickMembers.EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_SLTV)->EnableWindow(FALSE);
			m_radMem3.EnableWindow(FALSE);
			m_radMem4.EnableWindow(FALSE);
			m_radMem5.EnableWindow(FALSE);
			m_radMem6.EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_TEXT_MEMBER)->EnableWindow(FALSE);
			m_chkAceptJiebai.EnableWindow(FALSE);
			m_chkAcceptFriend.EnableWindow(FALSE);
		}
		else {
			m_chkKickMembers.EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_SLTV)->EnableWindow(TRUE);
			m_radMem3.EnableWindow(TRUE);
			m_radMem4.EnableWindow(TRUE);
			m_radMem5.EnableWindow(TRUE);
			m_radMem6.EnableWindow(TRUE);
		}
	}
	else {
		m_chkJiebai.EnableWindow(FALSE);
		m_chkInviteFriends.EnableWindow(FALSE);
		m_chkKickMembers.EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_SLTV)->EnableWindow(FALSE);
		/*if (pTeamTab->iTeamMode == TEAMMODE_ALONE) {
			m_radMem3.EnableWindow(TRUE);
			m_radMem4.EnableWindow(TRUE);
			m_radMem5.EnableWindow(TRUE);
			m_radMem6.EnableWindow(TRUE);

			GetDlgItem(IDC_STATIC_TEXT_MEMBER)->EnableWindow(TRUE);
		}

		if (pTeamTab->iTeamMode != TEAMMODE_ALONE) {
			m_radMem3.EnableWindow(FALSE);
			m_radMem4.EnableWindow(FALSE);
			m_radMem5.EnableWindow(FALSE);
			m_radMem6.EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_TEXT_MEMBER)->EnableWindow(FALSE);
		}*/
		m_radMem3.EnableWindow(FALSE);
		m_radMem4.EnableWindow(FALSE);
		m_radMem5.EnableWindow(FALSE);
		m_radMem6.EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_TEXT_MEMBER)->EnableWindow(FALSE);

		if (pTeamTab->iTeamMode == TEAMMODE_MEMBER) {
			GetDlgItem(IDC_STATIC_TEXT_MEMBER)->EnableWindow(TRUE);
			m_chkAceptJiebai.EnableWindow(TRUE);
			m_chkAcceptFriend.EnableWindow(TRUE);
		}
		else  {
			GetDlgItem(IDC_STATIC_TEXT_MEMBER)->EnableWindow(FALSE);
			m_chkAceptJiebai.EnableWindow(FALSE);
			m_chkAcceptFriend.EnableWindow(FALSE);
		}
	}
}

void CTeamDlg::OnBnClickedCheckAceptJiebai()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.bMemberAcceptJiebai = m_chkAceptJiebai.GetCheck();
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::OnBnClickedCheckExitTeam()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.bAloneExitTeam = m_chkAloneExitTeam.GetCheck();
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::OnBnClickedCheckTeamTarget()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.bAloneCheckTeamTarget = m_chkAloneCheckTeamTarget.GetCheck();
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::OnCbnSelchangeComboAloneTime()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.iAloneCheckTime = m_cbAloneTime.GetCurSel();
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::OnBnClickedRadioTeammodeIntelligence()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	if(pTeamTab->iTeamMode != TEAMMODE_INTELLIGENCE){
		pTeamTab->iTeamMode = TEAMMODE_INTELLIGENCE;
		pTeamTab->teamOption.iTeamType = pTeamTab->iTeamMode;
		pTeamTab->bSyncTeamOption = TRUE;
		UpdateControls(pGame);
		//MessageBox(L"Chế độ này yêu cầu phải có đội 3 người trở lên và \ntất cả các acc đều chọn chế độ này", L"Lưu ý", MB_OK);
	}
}

void CTeamDlg::OnBnClickedCheckInviteFriends()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.bInviteFriends = m_chkInviteFriends.GetCheck();
	pTeamTab->bSyncTeamOption = TRUE;
}

void CTeamDlg::OnBnClickedCheckAceptFriend()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	TEAMTAB *pTeamTab = pGame->GetTeamTab();
	pTeamTab->teamOption.bMemAcceptFriendsInvite = m_chkAcceptFriend.GetCheck();
	pTeamTab->bSyncTeamOption = TRUE;
}
