#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// COptionCopyGame dialog

class COptionCopyGame : public CVIEDialog
{
	DECLARE_DYNAMIC(COptionCopyGame)
public:

public:
	COptionCopyGame(CWnd* pParent = NULL, CGameInfo* pGame = NULL);   // standard constructor
	virtual ~COptionCopyGame();
	CGameInfo* m_pGame;

	// Dialog Data
	enum { IDD = IDD_DIALOG_COPYGAME};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CVIEToolTip*	m_pToolTip;
	afx_msg void OnItemCheckListGame(NMHDR *pNMHDR, LRESULT *pResult);
	CVIEListCtrl m_lstGame;
	CVIECheckBox m_chkCopyAll;
	CVIECheckBox m_chkCpyTabAct;
	CVIECheckBox m_chkCpyTabTeam;
	CVIECheckBox m_chkCpyTabOption;
	CVIEButton m_btnSltAll;
	CVIEButton m_btnUnsltAll;
	CVIEButton m_btnCopy;
	CVIELabel m_lblNote;
	afx_msg void OnBnClickedCheckCopyAll();
	afx_msg void OnBnClickedCheckCopyTabAcc();
	afx_msg void OnBnClickedCheckCopyTeam();
	afx_msg void OnBnClickedCheckCopyOptionTools();
	afx_msg void OnBnClickedButtonCheckall();
	afx_msg void OnBnClickedButtonUncheckall();
	afx_msg void OnBnClickedButtonCopy();
};
