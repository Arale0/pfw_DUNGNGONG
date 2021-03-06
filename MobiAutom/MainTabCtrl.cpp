#include "StdAfx.h"
#include "mobiAuto.h"
#include "MainTabCtrl.h"

BEGIN_MESSAGE_MAP(CMainTabCtrl, CVIETabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMainTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()


CMainTabCtrl::CMainTabCtrl(void)
{
}

CMainTabCtrl::~CMainTabCtrl(void)
{
}

void CMainTabCtrl::OnTcnSelchange( NMHDR *pNMHDR, LRESULT *pResult )
{
	*pResult = 0;
	CVIETabCtrl::OnSelchange(pNMHDR,pResult);


	UpdateTabDialogs(g_pMainDlg->m_pGameSelected);
}

void CMainTabCtrl::InitTabDialogs()
{
	SetItemSize(CSize(85,22));
	SetOverBkColor(RGB(250,250,250));

	AddTab(IDD_DIALOG_ACTIVITY, &m_ActivityDlg, L"H.động");
	AddTab(IDD_DIALOG_OPTION, &m_OptionDlg, L"T.chọn");
	AddTab(IDD_DIALOG_TEAM, &m_TeamDlg,		L"T.đội");
	AddTab(IDD_DIALOG_LOGIN_, &m_LoginDlg,		L"Đ.nhập");
	AddTab(IDD_DIALOG_HELP, &m_HelpDlg,		L"G.đỡ");
	AddInvisibleTab(IDD_DIALOG_ACCOUNT, &m_AccountDlg,	L"T.khoản");
	//AddTab(IDD_DIALOG_FILTER, &m_OptionFilterDlg, L"Lọc vật phẩm");
	//AddTab(IDD_DIALOG_SKILL, &m_OptionSkill, L"Skill");
	//AddInvisibleTab(IDD_DIALOG_OPTION_MAINQUEST, &m_OptionMainquestDlg,	L"Hoạt động*");
	
	AddInvisibleTab(IDD_DIALOG_OPTION_NVBANG, &m_pOptionNVBang,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_VANDAPNGAY, &m_pOptionVanDapNgay,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_KEPGIAYDOIBIETTHU, &m_pOptionKepGiayDoiBietThu,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_QUYETDAUDINHCAO, &m_pOptionQuyetDauDinhCao,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_TRUTHIENPHUDO, &m_pOptionTruThienPhuDo,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_PHUONGDEGIAN, &m_pOptionPhuongDeGian,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_PHUONGMINHCOC, &m_pOptionPhuongMinhCoc,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_TANGBAODO, &m_pOptionTangBaoDo,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_THUONGTHIENPHATAC, &m_pOptionThuongThienPhatAc,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_PBHOANGHON, &m_pOptionPBHoangHon,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_PBTUCHAN, &m_pOptionPBTuChan,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_DANGONGCUONG, &m_pOptionDaNgongCuong,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_VANTIEUBANG, &m_pOptionVanTieuBang,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_TRANHDOATSONCOC, &m_pOptionTranhDoatSonCoc,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_CHIENTUBANG, &m_pOptionChienTuBang,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_TRUONGLAOTUTIEN, &m_pOptionTruongLaoTuTien,	L"Tùy chỉnh");
	//AddInvisibleTab(IDD_DIALOG_OPTION_TRUCDIETACLINH, &m_pOptionTrucDietAcLinh,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_THOSANTIENTHUONG, &m_pOptionThoSanTienThuong,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_GHEPPHULINH, &m_pOptionGhepPhuLinh,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_SONCOCDATLINH, &m_pOptionSonCocDatLinh,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_HUNGVANQUAN, &m_pOptionHungVanQuan,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_BAYBAN, &m_pOptionBayBan,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_KHOACUVANDAP, &m_pOptionKhoaCuVanDap,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_GTIENMAKIEP, &m_pOptionGTienMaKiep,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_HANGBAUVAT, &m_pOptionHangBauVat,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_NVHUONGDAN, &m_pOptionNVHuongDan,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_NVTUCHAN, &m_pOptionNVTuChan,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_NVAN, &m_pOptionNVAn,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_NVPHU, &m_pOptionNVPhu,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_NVTHAN, &m_pOptionNVThan,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_NVTRUYEN, &m_pOptionNVTruyen,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_KHAOCO, &m_pOptionKhaoCo,	L"Tùy chỉnh");
	AddInvisibleTab(IDD_DIALOG_OPTION_BAYBANTHEODENGHI, &m_pOptionBayBanTheoDeNghi,	L"Tùy chỉnh");
	SetTextColor(RGB(0,0,0));
	EnableTabs(FALSE);
	SetTabReadOnly(ID_LOGIN_DLG,FALSE);
	SetTabReadOnly(ID_HELP_DLG,FALSE);

}

void CMainTabCtrl::EnableTabs( BOOL bEnable )
{
	for (INT i =0; i < GetItemCount(); ++i)
	{
		SetTabReadOnly(i,!bEnable);
	}
}

void CMainTabCtrl::SetGameActive( CGameInfo* pGame )
{
	if (!pGame) return;
	EnableTabs(TRUE);	
	UpdateTabDialogs(pGame);
}

void CMainTabCtrl::SetDefaultTabs()
{
	EnableTabs(FALSE);
}

void CMainTabCtrl::UpdateTabDialogs( CGameInfo* pGame )
{
	if (!pGame) return;
	int iCurTab = GetCurSel();
	LogWriteA("UpdateTabDialogs(%d) [%08X][%X]",iCurTab,pGame,pGame->m_hWnd);

	switch (iCurTab)
	{
	case ID_ACTIVITY_DLG://Activity
		m_ActivityDlg.UpdateControls(pGame);
		//m_OptionMainquestDlg.UpdateControls(pGame);		
		m_pOptionNVBang.UpdateControls(pGame);
		m_pOptionVanDapNgay.UpdateControls(pGame);
		m_pOptionKepGiayDoiBietThu.UpdateControls(pGame);
		m_pOptionQuyetDauDinhCao.UpdateControls(pGame);
		m_pOptionTruThienPhuDo.UpdateControls(pGame);
		m_pOptionPhuongDeGian.UpdateControls(pGame);
		m_pOptionPhuongMinhCoc.UpdateControls(pGame);
		m_pOptionTangBaoDo.UpdateControls(pGame);
		m_pOptionThuongThienPhatAc.UpdateControls(pGame);
		m_pOptionPBHoangHon.UpdateControls(pGame);
		m_pOptionPBTuChan.UpdateControls(pGame);
		m_pOptionDaNgongCuong.UpdateControls(pGame);
		m_pOptionVanTieuBang.UpdateControls(pGame);
		m_pOptionTranhDoatSonCoc.UpdateControls(pGame);
		m_pOptionChienTuBang.UpdateControls(pGame);
		m_pOptionTruongLaoTuTien.UpdateControls(pGame);
		//m_pOptionTrucDietAcLinh.UpdateControls(pGame);
		m_pOptionThoSanTienThuong.UpdateControls(pGame);
		m_pOptionGhepPhuLinh.UpdateControls(pGame);
		m_pOptionSonCocDatLinh.UpdateControls(pGame);
		m_pOptionHungVanQuan.UpdateControls(pGame);
		m_pOptionBayBan.UpdateControls(pGame);
		m_pOptionKhoaCuVanDap.UpdateControls(pGame);
		m_pOptionGTienMaKiep.UpdateControls(pGame);
		m_pOptionHangBauVat.UpdateControls(pGame);
		m_pOptionNVHuongDan.UpdateControls(pGame);
		m_pOptionNVTuChan.UpdateControls(pGame);
		m_pOptionNVAn.UpdateControls(pGame);
		m_pOptionNVPhu.UpdateControls(pGame);
		m_pOptionNVThan.UpdateControls(pGame);
		m_pOptionNVTruyen.UpdateControls(pGame);
		m_pOptionKhaoCo.UpdateControls(pGame);
		m_pOptionBayBanTheoDeNghi.UpdateControls(pGame);
		break;
	case ID_OPTION_DLG:
		m_OptionDlg.UpdateControls(pGame);
	case ID_TEAM_DLG:
		m_TeamDlg.UpdateControls(pGame);
		break;
	case ID_LOGIN_DLG:
		m_LoginDlg.UpdateControls(pGame);
		break;
	case ID_HELP_DLG://Help
		//m_HelpDlg.UpdateControls(pGame);
		break;
	}	

	if(m_OptionDlg.m_OptionCleanBag->IsWindowVisible())
		m_OptionDlg.m_OptionCleanBag->UpdateControls(pGame);
}

