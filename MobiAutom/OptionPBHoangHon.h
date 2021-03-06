#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionPBHoangHon : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionPBHoangHon)

public:
	COptionPBHoangHon(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionPBHoangHon();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_PBHOANGHON};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIEComboBox m_cbDifficult;
	CVIEComboBox m_cbCount;
	afx_msg void OnCbnSelchangeComboDifficult();
	afx_msg void OnCbnSelchangeComboTime();
	CVIECheckBox m_chkLeaderSkip;
	afx_msg void OnBnClickedCheckLeaderSkip();
	afx_msg void OnBnClickedCheckMemAutosearch();
	CVIECheckBox m_chkMemAutoSearch;
};
