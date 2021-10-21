#pragma once


// CAccountDlg dialog
#include "VIETreeListCtrlEx.h"
class CAccountDlg : public CVIEChildDlg
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CImageList	m_ImageList;
	CVIEMenu	m_mnuAccount;
	CVIEMenu	m_mnuServer;
	CVIEMenu	m_mnuRole;
	CAccountDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAccountDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_ACCOUNT };
	void UpdateControls(CGameInfo* pGame);
	//void DefaultMenuState( CVIEMenu* pMenu );
	CRoleAccount* m_pRoleSelected;
	CServerAccount* m_pServerSelected;
	CGameAccount* m_pAccountSelected;
	void UpdateList();
	void UpdateTree();
protected:
	virtual BOOL OnInitDialog();


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	//CVIEComboBox m_cboServername;

	CVIETreeListCtrlEx m_treeAccount;
	afx_msg void OnTvnSelchangedTreeAccount(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAccountAddserver();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pt);
	afx_msg void OnAccountAddaccount();
	afx_msg void OnAccountEditAccount();
	afx_msg void OnAccountAddRole();
	afx_msg void OnAccountDelete();
	afx_msg void OnRemoveServer();

	afx_msg void OnEditRole();
	afx_msg void OnRemoveRole();
	afx_msg void OnBnClickedButtonSaveaccount();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnRoleSelect();
};
