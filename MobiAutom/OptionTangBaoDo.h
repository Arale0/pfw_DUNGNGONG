#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionTangBaoDo : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionTangBaoDo)

public:
	COptionTangBaoDo(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionTangBaoDo();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_TANGBAODO};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chkTBDKhoa;
	afx_msg void OnBnClickedCheckTdbKhoa();
	CVIECheckBox m_chkTBDTrung;
	CVIECheckBox m_chkTBDCao;
	afx_msg void OnBnClickedCheckTdbTrung();
	afx_msg void OnBnClickedCheckTdbCao();
};
