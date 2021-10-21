#pragma once
#include "afxwin.h"


// CLoginDlg dialog

class CLoginDlg : public CVIEChildDlg
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();
	void UpdateControls(CGameInfo* pGame);
// Dialog Data
	enum { IDD = IDD_DIALOG_LOGIN_ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CVIEGroupManager	m_groupAccountMgr;
	
	CStatic			m_groupAccount;
	CVIERadioButton m_radAccountInlist;
	CVIERadioButton m_radAccountFixed;
	CVIEButton		m_btnOpenAccountList;
	CVIEButton		m_btnOpenAccountList2;

	CVIETextBox		m_txtUsername;
	CVIETextBox		m_txtPassword;
	CVIETextBox		m_txtRole;
	CVIEComboBox	m_cboServer;
	CVIEButton		m_btnShowPassword;
	CVIEButton		m_btnSave;
	
	CVIELabel		m_lblUsername;
	CVIELabel		m_lblPassword;
	CVIELabel		m_lblServer;
	CVIELabel		m_lblRole;
	CVIELabel		m_lblWarning;
	afx_msg void OnBnClickedRadAccountInlist();
	afx_msg void OnBnClickedRadAccountFixed();

	void UpdateUIByMode(int iMode);
	afx_msg void OnBnClickedButtonOpenAccountlist();
	afx_msg void OnBnClickedButtonOpenAccountlist2();
	afx_msg void OnBnClickedButtonAccountinfoSave();
	afx_msg void OnBnClickedButtonAccountinfoShowpass();
	afx_msg void OnEnSetfocusEditAccountinfoUsername();
	afx_msg void OnEnSetfocusEditAccountinfoPassword();
	afx_msg void OnCbnSetfocusCboAccountinfoServer();
	afx_msg void OnEnSetfocusEditAccountinfoRole();
	CVIEComboBox m_cbRole;
	afx_msg void OnCbnSelchangeCboRole();
	afx_msg void OnCbnSelchangeCboAccountinfoServer();
};
