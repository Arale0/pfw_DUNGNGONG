#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionBayBanTheoDeNghi : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionBayBanTheoDeNghi)

public:
	COptionBayBanTheoDeNghi(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionBayBanTheoDeNghi();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_BAYBANTHEODENGHI};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIEComboBox m_cbTBD;
	CVIEComboBox m_cbThienCoTai;
	CVIEComboBox m_cbVang59;
	afx_msg void OnCbnSelchangeComboTbd();
	afx_msg void OnCbnSelchangeComboTct();
	afx_msg void OnCbnSelchangeComboTbivang59();
	CVIECheckBox m_chkTinhLinh;
	CVIECheckBox m_chkBiKip;
	CVIEComboBox m_cbTinhLinh;
	CVIEComboBox m_cbBiKip;
	afx_msg void OnBnClickedCheckTinhlinh();
	afx_msg void OnCbnSelchangeComboTinhlinh();
	afx_msg void OnBnClickedCheckBikip();
	afx_msg void OnCbnSelchangeComboBikip();
};
