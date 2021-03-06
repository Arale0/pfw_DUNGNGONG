#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionVanTieuBang : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionVanTieuBang)

public:
	COptionVanTieuBang(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionVanTieuBang();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_VANTIEUBANG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIECheckBox m_chkCleanBag;
	CVIECheckBox m_chkTVNotFollow;
	afx_msg void OnBnClickedCheckvtCleanBag();
	afx_msg void OnBnClickedCheckTvNotfollow();
};
