#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionTruThienPhuDo : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionTruThienPhuDo)

public:
	COptionTruThienPhuDo(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionTruThienPhuDo();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_TRUTHIENPHUDO};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chkGoAll;
	afx_msg void OnBnClickedCheckGoAll();
	CVIECheckBox m_chkSweepOnly;
	afx_msg void OnBnClickedCheckSweeponly();
	void setupControls();
};
