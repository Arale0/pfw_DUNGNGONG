#pragma once

#define  ACCOUNTFORM_MODE_ADD	0
#define  ACCOUNTFORM_MODE_EDIT	1

// CLoginAddAccount dialog

class CLoginAddAccount : public CDialog
{
	DECLARE_DYNAMIC(CLoginAddAccount)

public:
	CLoginAddAccount(CWnd* pParent = NULL, int iMode = ACCOUNTFORM_MODE_ADD);   // standard constructor
	virtual ~CLoginAddAccount();
	int m_iMode;
// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CVIETextBox m_txtUsername;
	CVIETextBox m_txtPassword;
	afx_msg void OnBnClickedButtonAdd();
	CVIEButton m_btnSubmit;
	CVIEButton m_btnShowPassword;
	CVIELabel  m_lblWarning;
	afx_msg void OnBnClickedButtonShowpassword();
};
