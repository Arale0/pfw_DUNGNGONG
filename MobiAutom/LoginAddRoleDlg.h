#pragma once

#define ADDROLE_MODE_ADD 0 
#define ADDROLE_MODE_EDIT 1

// CLoginAddRoleDlg dialog

class CLoginAddRoleDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginAddRoleDlg)

public:
	int m_iMode;
	CLoginAddRoleDlg(CWnd* pParent = NULL, int mode = ADDROLE_MODE_ADD);   // standard constructor
	virtual ~CLoginAddRoleDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_ROLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CVIETextBox m_txtRolename;
	CServerAccount *m_pServerSelected;
	CVIELabel m_lblStatus;
	afx_msg void OnBnClickedButtonAddrole();
	CVIEButton m_btnAdd;
};
