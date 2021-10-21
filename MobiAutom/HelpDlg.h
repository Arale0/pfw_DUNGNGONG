#pragma once


// CHelpDlg dialog

class CHelpDlg : public CVIEChildDlg
{
	DECLARE_DYNAMIC(CHelpDlg)

public:
	CHelpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHelpDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonWebsite();
	CVIESelectButton m_btnWebsite;
	CVIESelectButton m_btnFacebook;
	CVIESelectButton m_btnForum;
	CVIESelectButton m_btnYoutube;
	afx_msg void OnBnClickedButtonFacebook();
	afx_msg void OnBnClickedButtonForum();
	afx_msg void OnBnClickedButtonYoutube();
};
