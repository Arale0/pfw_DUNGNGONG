#pragma once
#include "afxcmn.h"

#define		ACTLIST_INDEX_CONTROL		0
#define		ACTLIST_INDEX_NAME			1
#define		ACTLIST_INDEX_STATUS		2
#define		ACTLIST_INDEX_SETTING		3

// CActivityDlg dialog

class CActivityDlg : public CVIEChildDlg
{
	DECLARE_DYNAMIC(CActivityDlg)
public:
	void	UpdateControls(CGameInfo* pGame);
public:
	CActivityDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CActivityDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ACTIVITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CVIEListCtrl m_lstCtrlActivity;
	virtual BOOL OnInitDialog();
	afx_msg void OnItemCheckListActivity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListActivity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListActivity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnActivityItemMove(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListActivity(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnActivityReset();
	afx_msg void OnActivityCheckall();
	afx_msg void OnActivityUncheckall();
};
