#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionTruongLaoTuTien : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionTruongLaoTuTien)

public:
	COptionTruongLaoTuTien(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionTruongLaoTuTien();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_TRUONGLAOTUTIEN};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chkNoCheckCountTime;
	afx_msg void OnBnClickedCheckNocheck();
	CVIECheckBox m_chkOpenSetting;
	CVIECheckBox m_chkGotoBossTime;
	CVIEComboBox m_cbTimeToBoss;
	CVIECheckBox m_chkPlayerCheck;
	afx_msg void OnBnClickedCheckOpenSetting();
	afx_msg void OnBnClickedCheckSettime();
	afx_msg void OnCbnSelchangeComboTime();
	afx_msg void OnBnClickedCheckNotautoChoose();
};
