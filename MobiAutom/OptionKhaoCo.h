#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionKhaoCo : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionKhaoCo)

public:
	COptionKhaoCo(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionKhaoCo();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_KHAOCO};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIEComboBox m_cb1;
	CVIEComboBox m_cb2;
	CVIEComboBox m_cb3;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
};
