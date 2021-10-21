#pragma once
#include "afxwin.h"


// COptionMainQuestDlg dialog

class COptionMainQuestDlg : public CVIEChildDlg
{
	DECLARE_DYNAMIC(COptionMainQuestDlg)

public:
	COptionMainQuestDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionMainQuestDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_MAINQUEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkLevelLimited;
	afx_msg void OnBnClickedCheckLevelLimited();
public:
	void	UpdateControls(CGameInfo* pGame);
	afx_msg void OnBnClickedButtonBack();
};
