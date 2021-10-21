#pragma once


// CLoginAddServerDlg dialog
#include "AccountList2.h"
#include "afxwin.h"
class CLoginAddServerDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginAddServerDlg)

public:
	CLoginAddServerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginAddServerDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboServer();
	CVIEComboBox m_cbServer;
	CGameAccount* m_pAccount;
	afx_msg void OnBnClickedOk();
	CVIELabel m_lblStatus;
};
