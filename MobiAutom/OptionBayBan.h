#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionBayBan : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionBayBan)

public:
	COptionBayBan(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionBayBan();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_BAYBAN};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chkOrangeFood;
	CVIECheckBox m_chkOrangeEquips;
	CVIECheckBox m_chkLV59;
	CVIECheckBox m_chkLV69;
	CVIECheckBox m_chkLV79;
	CVIECheckBox m_chkLV89;
	afx_msg void OnBnClickedCheckOrangeFood();
	afx_msg void OnBnClickedCheckOrangeEquips();
	afx_msg void OnBnClickedCheckLv59();
	afx_msg void OnBnClickedCheckLv69();
	afx_msg void OnBnClickedCheckLv79();
	afx_msg void OnBnClickedCheckLv89();
	afx_msg void OnBnClickedButton30l();
	afx_msg void OnBnClickedButton20l();
	afx_msg void OnBnClickedButton10l();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton10r();
	afx_msg void OnBnClickedButton20r();
	afx_msg void OnBnClickedButton30r();

	CVIEButton m_btnSellPercent[7];
	void UpdateUI_SellPercent_SelectIndex(int idx);
	void UpdateUI_Reset_SellPercent_Color();
};
