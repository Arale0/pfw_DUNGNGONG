#pragma once
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionThoSanTienThuong : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionThoSanTienThuong)

public:
	COptionThoSanTienThuong(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionThoSanTienThuong();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_THOSANTIENTHUONG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	CVIERadioButton m_rd60;
	CVIERadioButton m_rd70;
	CVIERadioButton m_rd80;
	CVIERadioButton m_rd90;
	CVIERadioButton m_rd100;

	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedRadioLv60();
	afx_msg void OnBnClickedRadioLv70();
	afx_msg void OnBnClickedRadioLv80();
	afx_msg void OnBnClickedRadioLv90();
	afx_msg void OnBnClickedRadioLv100();
};
