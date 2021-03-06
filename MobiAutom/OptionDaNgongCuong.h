#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionDaNgongCuong : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionDaNgongCuong)

public:
	COptionDaNgongCuong(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionDaNgongCuong();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_DANGONGCUONG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chkBuyByGoldDrg;
	CVIEComboBox m_cbAmountOf;
	afx_msg void OnBnClickedCheckBuyBygolddragon();
	afx_msg void OnCbnSelchangeComboAmount();
	void InitControls();
};
