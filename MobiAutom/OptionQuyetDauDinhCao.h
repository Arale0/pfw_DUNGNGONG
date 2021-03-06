#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionQuyetDauDinhCao : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionQuyetDauDinhCao)

public:
	COptionQuyetDauDinhCao(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionQuyetDauDinhCao();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_QUYETDAUDINHCAO};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chkRandom;
	afx_msg void OnBnClickedCheckRandom();
};
