#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// COptionCleanBag dialog

class COptionCleanBag : public CVIEDialog
{
	DECLARE_DYNAMIC(COptionCleanBag)
public:
	CGameInfo*	m_pGame;
	void	UpdateControls(CGameInfo* pGame);

public:
	COptionCleanBag(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionCleanBag();

	// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION_CLEANBAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	

	CVIECheckBox m_chkDeWhite;
	CVIECheckBox m_chkDeBlue;
	CVIECheckBox m_chkDeViolet;
	CVIETextBox m_edtMinute;
	CVIECheckBox m_chkUseEquips;
	CVIECheckBox m_chkSellStone;
	CVIECheckBox m_chkClrBagInFb;
	CVIECheckBox m_chkTachTrangBiKhoa;
	CVIECheckBox m_chkDungTrangBi;
	CVIECheckBox m_chkTachTrangBiLcCao;
	CVIECheckBox m_chkDaAoTien;
	CVIECheckBox m_chkBua;
	CVIECheckBox m_chkDaCanKhon;
	afx_msg void OnBnClickedCheckTachTrangbikhoa();
	afx_msg void OnBnClickedCheckDungTrangbiTach2();
	afx_msg void OnBnClickedCheckTachTrang();
	afx_msg void OnBnClickedCheckTachLam();
	afx_msg void OnBnClickedCheckTachTim();
	afx_msg void OnBnClickedCheckDungTrangbi();
	afx_msg void OnBnClickedCheckUseEquip();
	afx_msg void OnBnClickedCheckSellStone();
	afx_msg void OnBnClickedCheckSellAotien();
	afx_msg void OnBnClickedCheckSellBua();
	afx_msg void OnBnClickedCheckSellCankhon();
	afx_msg void OnBnClickedCheckClrbagInfb();
	afx_msg void OnEnChangeEditMinute();
	void updateCleanBagControl();
	CVIECheckBox m_chkSellCertification;
	afx_msg void OnBnClickedCheckSellCertification();
	CButton m_chkBagFull;
	afx_msg void OnBnClickedCheckBagFull();
	CVIECheckBox m_chkGop;
	afx_msg void OnBnClickedCheckGop();
	CVIECheckBox m_chkTachTrangBiVang;
	CVIECheckBox m_chkBanNglieuCam59;
	afx_msg void OnBnClickedCheckSellNglieucam59();
	afx_msg void OnBnClickedCheckTachTrangbi59();
	CVIECheckBox m_chkTachGold59;
	CVIECheckBox m_chkTachGold69;
	CVIECheckBox m_chkTachGold79;
	CVIECheckBox m_chkTachGold89;
	afx_msg void OnBnClickedCheckGold59();
	afx_msg void OnBnClickedCheckGold69();
	afx_msg void OnBnClickedCheckGold79();
	afx_msg void OnBnClickedCheckGold89();
	CVIECheckBox m_chkTachGoldAllLv;
	afx_msg void OnBnClickedCheckGoldAlllv();
	CVIECheckBox m_chkPhuLinh;
	afx_msg void OnBnClickedCheckSellPhulinh();
	CVIECheckBox m_chkSellOther;
	afx_msg void OnBnClickedCheckSellOther();
	CVIECheckBox m_chkUseFairyEgg;
	afx_msg void OnBnClickedCheckUseFairyEgg();
	CVIECheckBox m_chkBiQuyenCoDai;
	CVIECheckBox m_chkDaThienCanh;
	afx_msg void OnBnClickedCheckBiquyencodai();
	afx_msg void OnBnClickedCheckDathiencanh();
	CVIECheckBox m_chkAnhHon;
	afx_msg void OnBnClickedCheckAnhhon();
	CVIECheckBox m_chkCleanByPoint1;
	CVIECheckBox m_chkCleanByPoint2;
	CVIETextBox m_edtMinuteP1;
	CVIETextBox m_edtMinuteP2;

	CVIERadioButton m_radCleanByPointTime;
	CVIERadioButton m_radCleanByDistanceTime;
	afx_msg void OnBnClickedRadioCleanbypoint();
	afx_msg void OnBnClickedRadioCleanbydistance();
	afx_msg void OnBnClickedCheckClrbagPoint1();
	afx_msg void OnBnClickedCheckClrbagPoint2();
	afx_msg void OnEnChangeEditMinuteP1();
	afx_msg void OnEnChangeEditMinuteP2();
	CVIECheckBox m_chkSellSoul;
	afx_msg void OnBnClickedCheckSoul();
	CVIECheckBox m_chkChangeMapYuanLing;
	afx_msg void OnBnClickedCheckBagChangemapYuanling();
};
