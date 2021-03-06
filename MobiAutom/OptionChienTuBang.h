#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionChienTuBang : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionChienTuBang)

public:
	COptionChienTuBang(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionChienTuBang();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_CHIENTUBANG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chk13;
	CVIECheckBox m_chk14;
	CVIECheckBox m_chk15;
	CVIECheckBox m_chk16;
	CVIECheckBox m_chk17;
	CVIECheckBox m_chk18;
	CVIECheckBox m_chk19;
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck14();
	afx_msg void OnBnClickedCheck15();
	afx_msg void OnBnClickedCheck16();
	afx_msg void OnBnClickedCheck17();
	afx_msg void OnBnClickedCheck18();
	afx_msg void OnBnClickedCheck19();
};
