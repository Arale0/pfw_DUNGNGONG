// OptionCleanBag.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionCleanBag.h"

// COptionCleanBag dialog

IMPLEMENT_DYNAMIC(COptionCleanBag, CVIEDialog)

COptionCleanBag::COptionCleanBag(CWnd* pParent /*=NULL*/)
	: CVIEDialog(COptionCleanBag::IDD, pParent)
{
	m_pGame = NULL;
}

COptionCleanBag::~COptionCleanBag()
{
}

void COptionCleanBag::DoDataExchange(CDataExchange* pDX)
{
	CVIEDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_TACH_TRANGBIKHOA, m_chkTachTrangBiKhoa);
	DDX_Control(pDX, IDC_CHECK_TACH_TRANG, m_chkDeWhite);
	DDX_Control(pDX, IDC_CHECK_TACH_LAM, m_chkDeBlue);
	DDX_Control(pDX, IDC_CHECK_TACH_TIM, m_chkDeViolet);
	DDX_Control(pDX, IDC_EDIT_MINUTE, m_edtMinute);
	DDX_Control(pDX, IDC_CHECK_USE_EQUIP, m_chkUseEquips);
	DDX_Control(pDX, IDC_CHECK_SELL_STONE, m_chkSellStone);
	DDX_Control(pDX, IDC_CHECK_CLRBAG_INFB, m_chkClrBagInFb);
	DDX_Control(pDX, IDC_CHECK_DUNG_TRANGBI, m_chkDungTrangBi);
	DDX_Control(pDX, IDC_CHECK_DUNG_TRANGBI_TACH2, m_chkTachTrangBiLcCao);
	DDX_Control(pDX, IDC_CHECK_SELL_AOTIEN, m_chkDaAoTien);
	DDX_Control(pDX, IDC_CHECK_SELL_BUA, m_chkBua);
	DDX_Control(pDX, IDC_CHECK_SELL_CANKHON, m_chkDaCanKhon);

	DDX_Control(pDX, IDC_CHECK_SELL_CERTIFICATION, m_chkSellCertification);
	DDX_Control(pDX, IDC_CHECK_BAG_FULL, m_chkBagFull);
	DDX_Control(pDX, IDC_CHECK_GOP, m_chkGop);
	DDX_Control(pDX, IDC_CHECK_TACH_TRANGBI_59, m_chkTachTrangBiVang);
	DDX_Control(pDX, IDC_CHECK_SELL_NGLIEUCAM_59, m_chkBanNglieuCam59);
	DDX_Control(pDX, IDC_CHECK_GOLD_59, m_chkTachGold59);
	DDX_Control(pDX, IDC_CHECK_GOLD_69, m_chkTachGold69);
	DDX_Control(pDX, IDC_CHECK_GOLD_79, m_chkTachGold79);
	DDX_Control(pDX, IDC_CHECK_GOLD_89, m_chkTachGold89);
	DDX_Control(pDX, IDC_CHECK_GOLD_ALLLV, m_chkTachGoldAllLv);
	DDX_Control(pDX, IDC_CHECK_SELL_PHULINH, m_chkPhuLinh);
	DDX_Control(pDX, IDC_CHECK_SELL_OTHER, m_chkSellOther);
	DDX_Control(pDX, IDC_CHECK_USE_FAIRY_EGG, m_chkUseFairyEgg);
	DDX_Control(pDX, IDC_CHECK_BIQUYENCODAI, m_chkBiQuyenCoDai);
	DDX_Control(pDX, IDC_CHECK_DATHIENCANH, m_chkDaThienCanh);
	DDX_Control(pDX, IDC_CHECK_ANHHON, m_chkAnhHon);
	DDX_Control(pDX, IDC_CHECK_CLRBAG_POINT1, m_chkCleanByPoint1);
	DDX_Control(pDX, IDC_CHECK_CLRBAG_POINT2, m_chkCleanByPoint2);
	DDX_Control(pDX, IDC_EDIT_MINUTE_P1, m_edtMinuteP1);
	DDX_Control(pDX, IDC_EDIT_MINUTE_P2, m_edtMinuteP2);

	DDX_Control(pDX, IDC_RADIO_CLEANBYPOINT, m_radCleanByPointTime);
	DDX_Control(pDX, IDC_RADIO_CLEANBYDISTANCE, m_radCleanByDistanceTime);
	DDX_Control(pDX, IDC_CHECK_SOUL, m_chkSellSoul);
	DDX_Control(pDX, IDC_CHECK_BAG_CHANGEMAP_YUANLING, m_chkChangeMapYuanLing);
}


BEGIN_MESSAGE_MAP(COptionCleanBag, CVIEDialog)
	
	ON_BN_CLICKED(IDC_CHECK_TACH_TRANGBIKHOA, &COptionCleanBag::OnBnClickedCheckTachTrangbikhoa)
	ON_BN_CLICKED(IDC_CHECK_DUNG_TRANGBI_TACH2, &COptionCleanBag::OnBnClickedCheckDungTrangbiTach2)
	ON_BN_CLICKED(IDC_CHECK_TACH_TRANG, &COptionCleanBag::OnBnClickedCheckTachTrang)
	ON_BN_CLICKED(IDC_CHECK_TACH_LAM, &COptionCleanBag::OnBnClickedCheckTachLam)
	ON_BN_CLICKED(IDC_CHECK_TACH_TIM, &COptionCleanBag::OnBnClickedCheckTachTim)
	ON_BN_CLICKED(IDC_CHECK_DUNG_TRANGBI, &COptionCleanBag::OnBnClickedCheckDungTrangbi)
	ON_BN_CLICKED(IDC_CHECK_USE_EQUIP, &COptionCleanBag::OnBnClickedCheckUseEquip)
	ON_BN_CLICKED(IDC_CHECK_SELL_STONE, &COptionCleanBag::OnBnClickedCheckSellStone)
	ON_BN_CLICKED(IDC_CHECK_SELL_AOTIEN, &COptionCleanBag::OnBnClickedCheckSellAotien)
	ON_BN_CLICKED(IDC_CHECK_SELL_BUA, &COptionCleanBag::OnBnClickedCheckSellBua)
	ON_BN_CLICKED(IDC_CHECK_SELL_CANKHON, &COptionCleanBag::OnBnClickedCheckSellCankhon)
	ON_BN_CLICKED(IDC_CHECK_CLRBAG_INFB, &COptionCleanBag::OnBnClickedCheckClrbagInfb)
	ON_EN_CHANGE(IDC_EDIT_MINUTE, &COptionCleanBag::OnEnChangeEditMinute)
	ON_BN_CLICKED(IDC_CHECK_SELL_CERTIFICATION, &COptionCleanBag::OnBnClickedCheckSellCertification)
	ON_BN_CLICKED(IDC_CHECK_BAG_FULL, &COptionCleanBag::OnBnClickedCheckBagFull)
	ON_BN_CLICKED(IDC_CHECK_GOP, &COptionCleanBag::OnBnClickedCheckGop)
	ON_BN_CLICKED(IDC_CHECK_SELL_NGLIEUCAM_59, &COptionCleanBag::OnBnClickedCheckSellNglieucam59)
	ON_BN_CLICKED(IDC_CHECK_TACH_TRANGBI_59, &COptionCleanBag::OnBnClickedCheckTachTrangbi59)
	ON_BN_CLICKED(IDC_CHECK_GOLD_59, &COptionCleanBag::OnBnClickedCheckGold59)
	ON_BN_CLICKED(IDC_CHECK_GOLD_69, &COptionCleanBag::OnBnClickedCheckGold69)
	ON_BN_CLICKED(IDC_CHECK_GOLD_79, &COptionCleanBag::OnBnClickedCheckGold79)
	ON_BN_CLICKED(IDC_CHECK_GOLD_89, &COptionCleanBag::OnBnClickedCheckGold89)
	ON_BN_CLICKED(IDC_CHECK_GOLD_ALLLV, &COptionCleanBag::OnBnClickedCheckGoldAlllv)
	ON_BN_CLICKED(IDC_CHECK_SELL_PHULINH, &COptionCleanBag::OnBnClickedCheckSellPhulinh)
	ON_BN_CLICKED(IDC_CHECK_SELL_OTHER, &COptionCleanBag::OnBnClickedCheckSellOther)
	ON_BN_CLICKED(IDC_CHECK_USE_FAIRY_EGG, &COptionCleanBag::OnBnClickedCheckUseFairyEgg)
	ON_BN_CLICKED(IDC_CHECK_BIQUYENCODAI, &COptionCleanBag::OnBnClickedCheckBiquyencodai)
	ON_BN_CLICKED(IDC_CHECK_DATHIENCANH, &COptionCleanBag::OnBnClickedCheckDathiencanh)
	ON_BN_CLICKED(IDC_CHECK_ANHHON, &COptionCleanBag::OnBnClickedCheckAnhhon)
	ON_BN_CLICKED(IDC_RADIO_CLEANBYPOINT, &COptionCleanBag::OnBnClickedRadioCleanbypoint)
	ON_BN_CLICKED(IDC_RADIO_CLEANBYDISTANCE, &COptionCleanBag::OnBnClickedRadioCleanbydistance)
	ON_BN_CLICKED(IDC_CHECK_CLRBAG_POINT1, &COptionCleanBag::OnBnClickedCheckClrbagPoint1)
	ON_BN_CLICKED(IDC_CHECK_CLRBAG_POINT2, &COptionCleanBag::OnBnClickedCheckClrbagPoint2)
	ON_EN_CHANGE(IDC_EDIT_MINUTE_P1, &COptionCleanBag::OnEnChangeEditMinuteP1)
	ON_EN_CHANGE(IDC_EDIT_MINUTE_P2, &COptionCleanBag::OnEnChangeEditMinuteP2)
	ON_BN_CLICKED(IDC_CHECK_SOUL, &COptionCleanBag::OnBnClickedCheckSoul)
	ON_BN_CLICKED(IDC_CHECK_BAG_CHANGEMAP_YUANLING, &COptionCleanBag::OnBnClickedCheckBagChangemapYuanling)
END_MESSAGE_MAP()


// COptionCleanBag message handlers

BOOL COptionCleanBag::OnInitDialog()
{
	CVIEDialog::OnInitDialog();

	SetWindowText(L"Dọn túi");
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void COptionCleanBag::UpdateControls(CGameInfo* pGame)
{
	m_pGame = pGame;
	if (!m_pGame) return;
	LOGA_DEBUG("m_pGame:%8X", m_pGame);
	OPTIONTAB *pTab = m_pGame->GetOptionTab();
	m_chkDeWhite.SetCheck(pTab->bDeWhite);
	m_chkDeBlue.SetCheck(pTab->bDeBlue);
	m_chkDeViolet.SetCheck(pTab->bDeViolet);
	m_chkSellStone.SetCheck(pTab->bBagSellStone);
	m_chkUseEquips.SetCheck(pTab->bBagUseEquips);
	m_chkClrBagInFb.SetCheck(pTab->bBagInFb);
	m_chkTachTrangBiKhoa.SetCheck(pTab->bTachTrangBiKhoa);
	m_chkDungTrangBi.SetCheck(pTab->bDungTrangBi);
	m_chkTachTrangBiLcCao.SetCheck(pTab->bTachTrangBiLcCao);
	m_chkDaAoTien.SetCheck(pTab->bBanDaAoTien);
	m_chkBua.SetCheck(pTab->bBanBua);
	m_chkDaCanKhon.SetCheck(pTab->bBanDaCanKhon);
	m_chkSellCertification.SetCheck(pTab->bSellCertification);;
	m_chkGop.SetCheck(pTab->bGop);
	m_chkBanNglieuCam59.SetCheck(pTab->bBanNgLieuCam59);
	m_chkTachTrangBiVang.SetCheck(pTab->bTachTrangBiVang);
	m_chkTachGold59.SetCheck(pTab->bTachGold59);
	m_chkTachGold69.SetCheck(pTab->bTachGold69);
	m_chkTachGold79.SetCheck(pTab->bTachGold79);
	m_chkTachGold89.SetCheck(pTab->bTachGold89);
	m_chkTachGoldAllLv.SetCheck(pTab->bTachGoldAllLV);
	m_chkPhuLinh.SetCheck(pTab->bBanPhuLinh);
	m_chkSellOther.SetCheck(pTab->bSellOther);
	m_chkUseFairyEgg.SetCheck(pTab->bUseFairyEgg);
	m_chkBiQuyenCoDai.SetCheck(pTab->bSell_BiQuyenCoDai);
	m_chkDaThienCanh.SetCheck(pTab->bSell_DaThienCanh);
	m_chkAnhHon.SetCheck(pTab->bBagAnhHon);
	m_chkSellSoul.SetCheck(pTab->bBagSellSoul);
	m_chkChangeMapYuanLing.SetCheck(pTab->bBagChangeMapYuanLing);

	m_radCleanByPointTime.SetCheck(pTab->iBagCleanType == 1);
	m_radCleanByDistanceTime.SetCheck(pTab->iBagCleanType == 0);

	m_chkCleanByPoint1.SetCheck(pTab->bBagCleanPoint1);
	m_chkCleanByPoint2.SetCheck(pTab->bBagCleanPoint2);

	CString szMinuteP1;
	szMinuteP1.Format(L"%d",pTab->iBagCleanPoint1);
	m_edtMinuteP1.SetText(szMinuteP1);

	CString szMinuteP2;
	szMinuteP2.Format(L"%d",pTab->iBagCleanPoint2);
	m_edtMinuteP2.SetText(szMinuteP2);

	CString szMinute;
	szMinute.Format(L"%d",pTab->iDeMinute);
	m_edtMinute.SetText(szMinute);
	updateCleanBagControl();
	pGame->m_bSyncOptionTab = TRUE;


}
void COptionCleanBag::OnBnClickedCheckTachTrangbikhoa()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachTrangBiKhoa		= m_chkTachTrangBiKhoa.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckDungTrangbiTach2()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachTrangBiLcCao		= m_chkTachTrangBiLcCao.GetCheck();
	updateCleanBagControl();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckTachTrang()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bDeWhite		= m_chkDeWhite.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckTachLam()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bDeBlue		= m_chkDeBlue.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckTachTim()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bDeViolet		= m_chkDeViolet.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckDungTrangbi()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bDungTrangBi		= m_chkDungTrangBi.GetCheck();
	updateCleanBagControl();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckUseEquip()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagUseEquips		= m_chkUseEquips.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSellStone()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagSellStone		= m_chkSellStone.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSellAotien()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBanDaAoTien		= m_chkDaAoTien.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSellBua()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBanBua		= m_chkBua.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSellCankhon()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBanDaCanKhon		= m_chkDaCanKhon.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckClrbagInfb()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagInFb		= m_chkClrBagInFb.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnEnChangeEditMinute()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	CString szText = m_edtMinute.GetText();
	int iMinute = _wtoi(szText.GetBuffer());
	if (iMinute <= 0){
		iMinute = 1;
		m_edtMinute.SetText(L"1");
	}

	OPTIONTAB *pTab		= pGame->GetOptionTab();
	pTab->iDeMinute		= iMinute;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::updateCleanBagControl()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	if (pTab->bCleanBag) {
		m_chkDeWhite.EnableWindow(TRUE);
		m_chkDeBlue.EnableWindow(TRUE);
		m_chkDeViolet.EnableWindow(TRUE);
		m_chkUseEquips.EnableWindow(TRUE);
		m_chkSellStone.EnableWindow(TRUE);
		m_chkClrBagInFb.EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_TEXT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_TEXT2)->EnableWindow(TRUE);
		m_edtMinute.EnableWindow(TRUE);
		m_chkTachTrangBiKhoa.EnableWindow(TRUE);
		//m_chkDungTrangBi.EnableWindow(TRUE);
		//m_chkTachTrangBiLcCao.EnableWindow(TRUE);
		m_chkDaAoTien.EnableWindow(TRUE);
		m_chkBua.EnableWindow(TRUE);
		m_chkDaCanKhon.EnableWindow(TRUE);
		m_chkSellCertification.EnableWindow(TRUE);
		m_chkPhuLinh.EnableWindow(TRUE);
		m_chkSellOther.EnableWindow(TRUE);
		m_chkUseFairyEgg.EnableWindow(TRUE);
		m_chkDaThienCanh.EnableWindow(TRUE);
		m_chkBiQuyenCoDai.EnableWindow(TRUE);
		m_chkAnhHon.EnableWindow(TRUE);

		if (m_chkTachTrangBiLcCao.GetCheck() == 1) {
			m_chkDungTrangBi.EnableWindow(FALSE);
		}

		if (m_chkTachTrangBiLcCao.GetCheck() == 0) {
			m_chkDungTrangBi.EnableWindow(TRUE);
		}

		if (m_chkDungTrangBi.GetCheck() == 1) {
			m_chkTachTrangBiLcCao.EnableWindow(FALSE);
		}

		if (m_chkDungTrangBi.GetCheck() == 0) {
			m_chkTachTrangBiLcCao.EnableWindow(TRUE);
		}


		m_chkBanNglieuCam59.EnableWindow(TRUE);
		m_chkTachTrangBiVang.EnableWindow(TRUE);
		
		if (m_chkTachTrangBiVang.GetCheck() == 0) {
			m_chkTachGold59.EnableWindow(FALSE);
			m_chkTachGold69.EnableWindow(FALSE);
			m_chkTachGold79.EnableWindow(FALSE);
			m_chkTachGold89.EnableWindow(FALSE);
			m_chkTachGoldAllLv.EnableWindow(FALSE);
		}

		if (m_chkTachTrangBiVang.GetCheck() == 1) {
			m_chkTachGold59.EnableWindow(TRUE);
			m_chkTachGold69.EnableWindow(TRUE);
			m_chkTachGold79.EnableWindow(TRUE);
			m_chkTachGold89.EnableWindow(TRUE);
			m_chkTachGoldAllLv.EnableWindow(TRUE);
		}

	}

	if (!pTab->bCleanBag) {
		m_chkDeWhite.EnableWindow(FALSE);
		m_chkDeBlue.EnableWindow(FALSE);
		m_chkDeViolet.EnableWindow(FALSE);
		m_chkUseEquips.EnableWindow(FALSE);
		m_chkSellStone.EnableWindow(FALSE);
		m_chkClrBagInFb.EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_TEXT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_TEXT2)->EnableWindow(FALSE);
		m_chkPhuLinh.EnableWindow(FALSE);
		m_chkUseFairyEgg.EnableWindow(FALSE);
		m_edtMinute.EnableWindow(FALSE);
		m_chkSellOther.EnableWindow(FALSE);
		m_chkTachTrangBiKhoa.EnableWindow(FALSE);
		m_chkDungTrangBi.EnableWindow(FALSE);
		m_chkTachTrangBiLcCao.EnableWindow(FALSE);
		m_chkDaAoTien.EnableWindow(FALSE);
		m_chkBua.EnableWindow(FALSE);
		m_chkDaCanKhon.EnableWindow(FALSE);
		m_chkSellCertification.EnableWindow(FALSE);
		m_chkBanNglieuCam59.EnableWindow(FALSE);
		m_chkTachTrangBiVang.EnableWindow(FALSE);
		m_chkTachGold59.EnableWindow(FALSE);
		m_chkTachGold69.EnableWindow(FALSE);
		m_chkTachGold79.EnableWindow(FALSE);
		m_chkTachGold89.EnableWindow(FALSE);
		m_chkTachGoldAllLv.EnableWindow(FALSE);
		m_chkDaThienCanh.EnableWindow(FALSE);
		m_chkBiQuyenCoDai.EnableWindow(FALSE);
		m_chkAnhHon.EnableWindow(FALSE);
	}
}

void COptionCleanBag::OnBnClickedCheckSellCertification()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellCertification		= m_chkSellCertification.GetCheck();
	updateCleanBagControl();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckBagFull()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellCertification		= m_chkSellCertification.GetCheck();
	updateCleanBagControl();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckGop()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bGop		= m_chkGop.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSellNglieucam59()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBanNgLieuCam59		= m_chkBanNglieuCam59.GetCheck();
	updateCleanBagControl();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckTachTrangbi59()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachTrangBiVang		= m_chkTachTrangBiVang.GetCheck();
	updateCleanBagControl();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckGold59()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachGold59		= m_chkTachGold59.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckGold69()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachGold69		= m_chkTachGold69.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckGold79()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachGold79		= m_chkTachGold79.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckGold89()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachGold89		= m_chkTachGold89.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckGoldAlllv()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bTachGoldAllLV		= m_chkTachGoldAllLv.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSellPhulinh()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBanPhuLinh		= m_chkPhuLinh.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSellOther()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSellOther	= m_chkSellOther.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckUseFairyEgg()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bUseFairyEgg	= m_chkUseFairyEgg.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckBiquyencodai()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSell_BiQuyenCoDai	= m_chkBiQuyenCoDai.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckDathiencanh()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bSell_DaThienCanh	= m_chkDaThienCanh.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckAnhhon()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagAnhHon	= m_chkAnhHon.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedRadioCleanbypoint()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pOptionTab = pGame->GetOptionTab();
	int iCleanType = 1;
	pOptionTab->iBagCleanType = iCleanType;
	LOGW_DEBUG(L"pOptionTab->iBagCleanType == %d", pOptionTab->iBagCleanType);
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedRadioCleanbydistance()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pOptionTab = pGame->GetOptionTab();
	int iCleanType = 0;
	pOptionTab->iBagCleanType = iCleanType;
	LOGW_DEBUG(L"pOptionTab->iBagCleanType == %d", pOptionTab->iBagCleanType);
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckClrbagPoint1()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagCleanPoint1	= m_chkCleanByPoint1.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckClrbagPoint2()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagCleanPoint2	= m_chkCleanByPoint2.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnEnChangeEditMinuteP1()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	CString szText = m_edtMinuteP1.GetText();
	int iMinute = _wtoi(szText.GetBuffer());
	

	OPTIONTAB *pTab				= pGame->GetOptionTab();
	pTab->iBagCleanPoint1		= iMinute;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnEnChangeEditMinuteP2()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	CString szText = m_edtMinuteP2.GetText();
	int iMinute = _wtoi(szText.GetBuffer());


	OPTIONTAB *pTab				= pGame->GetOptionTab();
	pTab->iBagCleanPoint2		= iMinute;
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckSoul()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagSellSoul	= m_chkSellSoul.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}

void COptionCleanBag::OnBnClickedCheckBagChangemapYuanling()
{
	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame) return;
	OPTIONTAB *pTab = pGame->GetOptionTab();
	pTab->bBagChangeMapYuanLing	= m_chkChangeMapYuanLing.GetCheck();
	pGame->m_bSyncOptionTab = TRUE;
}
