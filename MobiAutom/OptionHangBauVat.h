#pragma once
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionHangBauVat : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionHangBauVat)

public:
	COptionHangBauVat(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionHangBauVat();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_HANGBAUVAT};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
};
