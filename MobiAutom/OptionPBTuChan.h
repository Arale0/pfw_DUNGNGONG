#pragma once
#include "afxwin.h"
//copyright: AIGO Technology
//developer: Nguyễn Thành Huy 

// COptionEmpty dialog

class COptionPBTuChan : public CVIETabDialog
{
	DECLARE_DYNAMIC(COptionPBTuChan)

public:
	COptionPBTuChan(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionPBTuChan();
	void UpdateControls( CGameInfo* pGame );
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_PBTUCHAN};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	ActivityId m_activity;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CVIEButton m_btnBack;
public:
	afx_msg void OnBnClickedButtonBack();
	CVIEComboBox m_cbDifficult;
	afx_msg void OnCbnSelchangeComboDifficult();
	afx_msg void OnBnClickedRadioLv35();
	afx_msg void OnBnClickedRadioLv59();
	afx_msg void OnBnClickedRadioLv69();
	afx_msg void OnCbnSelchangeComboTcDifficult();

	CVIERadioButton m_radLV29;
	CVIERadioButton m_radLV35;
	CVIERadioButton m_radLV59;
	CVIERadioButton m_radLV69;
	CVIERadioButton m_radLV89;
	CVIEComboBox m_cbCountTime;
	afx_msg void OnBnClickedRadioLv29();
	CVIECheckBox m_chkLeaderSkip;
	afx_msg void OnBnClickedCheckLeaderSkip();
	afx_msg void OnBnClickedRadioLv89();
	afx_msg void OnBnClickedCheckMemAutosearch();
	CVIECheckBox m_chkMemAutoSearch;
	afx_msg void OnBnClickedCheck2Time();
	CVIECheckBox m_chk2TimeToFinished;
	CVIELabel m_lblCountTime;
	afx_msg void OnStnClickedStaticCounttime();
};
