#pragma once
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionVanDapNgay : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionVanDapNgay)

public:
	COptionVanDapNgay(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionVanDapNgay();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_VANDAPNGAY};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
};
