#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTeamDlg dialog


#define  LV_TEAM_INDEX_POS	0
#define  LV_TEAM_INDEX_NAME	1

class CTeamDlg : public CVIEChildDlg
{
	DECLARE_DYNAMIC(CTeamDlg)

public:
	CTeamDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTeamDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TEAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	
	UINT_PTR		m_uiTimeID;
	static VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLog();
	CVIEListCtrl m_lstCtrlTeam;
	void UpdateControls(CGameInfo *pGame);
	CVIERadioButton m_radTeammodeMatch;
	CVIERadioButton m_radTeammodeLeader;
	CVIERadioButton m_radTeammodeMember;
	CVIERadioButton m_radTeammodeAlone;
	CVIERadioButton m_radTeammodeIntelligence;


	afx_msg void OnBnClickedRadioTeammodeMatch();
	void UpdateUITeamMode(int teammode);
	void UpdateTeamByMode();
	void UpdateTeamControls();
	afx_msg void OnBnClickedRadioTeammodeLeader();
	afx_msg void OnBnClickedRadioTeammodeMember();
	afx_msg void OnBnClickedRadioTeammodeAlone();
	CVIEComboBox m_cboMemberName;
	afx_msg void OnCbnDropdownComboMembername();
	afx_msg void OnCbnEditchangeComboMembername();
	afx_msg void OnBnClickedButtonTeamSavechange();
	CVIEButton	 m_btnSaveChange;
	//afx_msg void OnCbnKillfocusComboMembername();
	afx_msg void OnCbnSelchangeComboMembername();
	CVIEButton	m_btnLog;
	//CVIEComboBox m_cbNumMembers;
	//CVIELabel m_lblExplain;
	CVIECheckBox m_chkJiebai;
	afx_msg void OnBnClickedCheckMakeFirend();
	CVIECheckBox m_chkKickMembers;
	afx_msg void OnBnClickedCheckKickMembers();

	CVIERadioButton m_radMem3;
	CVIERadioButton m_radMem4;
	CVIERadioButton m_radMem5;
	CVIERadioButton m_radMem6;
	
	afx_msg void OnBnClickedRadioMember3();
	afx_msg void OnBnClickedRadioMember4();
	afx_msg void OnBnClickedRadioMember5();
	afx_msg void OnBnClickedRadioMember6();
	CVIECheckBox m_chkAceptJiebai;
	afx_msg void OnBnClickedCheckAceptJiebai();
	CVIECheckBox m_chkAloneExitTeam;
	CVIECheckBox m_chkAloneCheckTeamTarget;
	CVIEComboBox m_cbAloneTime;
	afx_msg void OnBnClickedCheckExitTeam();
	afx_msg void OnBnClickedCheckTeamTarget();
	afx_msg void OnCbnSelchangeComboAloneTime();
	afx_msg void OnBnClickedRadioTeammodeIntelligence();
	CVIECheckBox m_chkKeepTeam;
	afx_msg void OnBnClickedCheckAcceptFriendInvite();
	CVIECheckBox m_chkInviteFriends;
	afx_msg void OnBnClickedCheckInviteFriends();
	afx_msg void OnBnClickedCheckKeepTeam();
	CVIECheckBox m_chkAcceptFriend;
	afx_msg void OnBnClickedCheckAceptFriend();
};
