#pragma once
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionSonCocDatLinh : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionSonCocDatLinh)

public:
	COptionSonCocDatLinh(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionSonCocDatLinh();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_SONCOCDATLINH};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
};
