#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "OptionCleanBag.h"
// COptionDlg dialog

class COptionDlg : public CVIEChildDlg
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckTest();
	CGameInfo* m_pGame;
	void	UpdateControls(CGameInfo* pGame);

	COptionCleanBag * m_OptionCleanBag;

	CVIECheckBox m_chkTest;
	
	CVIECheckBox m_chkFuli;
	CVIECheckBox m_chkAchievement;
	afx_msg void OnBnClickedCheckFuli();
	afx_msg void OnBnClickedCheckAchievement();
	CVIECheckBox m_chkDeWhite;
	CVIECheckBox m_chkDeBlue;
	CVIECheckBox m_chkDeViolet;
	CVIETextBox m_edtMinute;
	CVIECheckBox m_chkUseEquips;
	CVIECheckBox m_chkSellStone;
	CVIECheckBox m_chkClrBagInFb;
	CVIECheckBox m_chkCleanBag;
	afx_msg void OnBnClickedCheckCleanbag();
	void updateCleanBagControl();
	afx_msg void OnBnClickedRadSize5();
	afx_msg void OnBnClickedRadSize10();
	afx_msg void OnBnClickedRadSize15();
	CVIECheckBox m_chkTachTrangBiKhoa;
	CVIECheckBox m_chkDungTrangBi;
	CVIECheckBox m_chkTachTrangBiLcCao;
	CVIECheckBox m_chkDaAoTien;
	CVIECheckBox m_chkBua;
	CVIECheckBox m_chkDaCanKhon;
	CVIEButton m_btnCleanBagOption;
	afx_msg void OnBnClickedButtonCleanbagOption();
	CVIECheckBox m_chkOptimizeCPU;
	afx_msg void OnBnClickedCheckOptimizeCpuGpu();
	CVIERadioButton m_radfpsMedium;
	CVIERadioButton m_radfpsLow;
	CVIERadioButton m_radfpsVeryLow;
	afx_msg void OnBnClickedRadioFpsMedium();
	afx_msg void OnBnClickedRadioFpsLow();
	afx_msg void OnBnClickedRadioFpsVerylow();
	CVIECheckBox m_chkAutoBuyPatch;
	afx_msg void OnBnClickedAutoBuyPatch();
	CVIEComboBox m_cbHp;
	CVIEComboBox m_cbMP;
	afx_msg void OnCbnSelchangeComboHp();
	afx_msg void OnCbnSelchangeComboMp();
	CVIECheckBox m_chkGetSilverBox;
	afx_msg void OnBnClickedCheckGetSilverbox();
	CVIECheckBox m_chkBuyPatch2;
	CVIEComboBox m_cbHPLevel;
	CVIEComboBox m_cbMPLevel;
	afx_msg void OnBnClickedAutoBuyPatch2();
	afx_msg void OnCbnSelchangeComboHpLevel();
	afx_msg void OnCbnSelchangeComboMpLevel();
	CVIECheckBox m_chkRunGameWCrash;
	afx_msg void OnBnClickedCheck();
	CVIECheckBox m_chkRecDynamic;
	afx_msg void OnBnClickedCheckDynamic();
	CVIECheckBox m_chkOptimizeCPUAct;
	afx_msg void OnBnClickedCheckOptimizeCpuAct();
	CVIECheckBox m_chkMail;
	afx_msg void OnBnClickedCheckMail();
	CVIECheckBox m_chkCdTuChan;
	afx_msg void OnBnClickedCheckCdtuchan();
	CVIECheckBox m_chkTradePiority;
	afx_msg void OnBnClickedTradePriority();
	
	CVIELabel m_lblCurrentID;
	void	updateCurrentID(CGameInfo* pGame);
	CVIELabel m_lblNameUtility;
	CVIECheckBox m_chkUsePacthRelive;
	afx_msg void OnBnClickedCheckUsepatchRelive();
};
