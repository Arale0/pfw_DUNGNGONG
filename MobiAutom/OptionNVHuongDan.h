#pragma once
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionNVHuongDan : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionNVHuongDan)

public:
	COptionNVHuongDan(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionNVHuongDan();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_NVHUONGDAN};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
};
