#pragma once
#include <viecontrols\vietabctrl.h>

#include "ActivityDlg.h"
#include "HelpDlg.h"
#include "OptionDlg.h"
#include "LoginDlg.h"
#include "TeamDlg.h"
#include "AccountDlg.h"
//#include "OptionMainQuestDlg.h"

#define ID_ACTIVITY_DLG	0
#define ID_OPTION_DLG (ID_ACTIVITY_DLG + 1)
#define ID_TEAM_DLG	(ID_ACTIVITY_DLG + 2)
#define ID_LOGIN_DLG (ID_ACTIVITY_DLG + 3)
#define ID_HELP_DLG	(ID_ACTIVITY_DLG + 4)
#define ID_LAST_DLG ID_HELP_DLG

#include "OptionNVBang.h"
#include "OptionVanDapNgay.h"
#include "OptionKepGiayDoiBietThu.h"
#include "OptionQuyetDauDinhCao.h"
#include "OptionTruThienPhuDo.h"
#include "OptionPhuongDeGian.h"
#include "OptionPhuongMinhCoc.h"
#include "OptionTangBaoDo.h"
#include "OptionThuongThienPhatAc.h"
#include "OptionPBHoangHon.h"
#include "OptionPBTuChan.h"
#include "OptionDaNgongCuong.h"
#include "OptionVanTieuBang.h"
#include "OptionTranhDoatSonCoc.h"
#include "OptionChienTuBang.h"
#include "OptionTruongLaoTuTien.h"
//#include "OptionTrucDietAcLinh.h"
#include "OptionThoSanTienThuong.h"
#include "OptionGhepPhuLinh.h"
#include "OptionSonCocDatLinh.h"
#include "OptionHungVanQuan.h"
#include "OptionBayBan.h"
#include "OptionKhoaCuVanDap.h"
#include "OptionGTienMaKiep.h"
#include "OptionHangBauVat.h"
#include "OptionNVHuongDan.h"
#include "OptionNVTuChan.h"
#include "OptionNVAn.h"
#include "OptionNVPhu.h"
#include "OptionNVThan.h"
#include "OptionNVTruyen.h"
#include "OptionKhaoCo.h"
#include "OptionBayBanTheoDeNghi.h"
class CMainTabCtrl : public CVIETabCtrl
{
public:
	CActivityDlg		m_ActivityDlg;
	CHelpDlg			m_HelpDlg;
	COptionDlg			m_OptionDlg;
	CTeamDlg			m_TeamDlg;
	CLoginDlg			m_LoginDlg;
	CAccountDlg			m_AccountDlg;

	//COptionMainQuestDlg m_OptionMainquestDlg;
	
	COptionNVBang	m_pOptionNVBang;
	COptionVanDapNgay	m_pOptionVanDapNgay;
	COptionKepGiayDoiBietThu	m_pOptionKepGiayDoiBietThu;
	COptionQuyetDauDinhCao	m_pOptionQuyetDauDinhCao;
	COptionTruThienPhuDo	m_pOptionTruThienPhuDo;
	COptionPhuongDeGian	m_pOptionPhuongDeGian;
	COptionPhuongMinhCoc	m_pOptionPhuongMinhCoc;
	COptionTangBaoDo	m_pOptionTangBaoDo;
	COptionThuongThienPhatAc	m_pOptionThuongThienPhatAc;
	COptionPBHoangHon	m_pOptionPBHoangHon;
	COptionPBTuChan	m_pOptionPBTuChan;
	COptionDaNgongCuong	m_pOptionDaNgongCuong;
	COptionVanTieuBang	m_pOptionVanTieuBang;
	COptionTranhDoatSonCoc	m_pOptionTranhDoatSonCoc;
	COptionChienTuBang	m_pOptionChienTuBang;
	COptionTruongLaoTuTien	m_pOptionTruongLaoTuTien;
	//COptionTrucDietAcLinh	m_pOptionTrucDietAcLinh;
	COptionThoSanTienThuong	m_pOptionThoSanTienThuong;
	COptionGhepPhuLinh	m_pOptionGhepPhuLinh;
	COptionSonCocDatLinh	m_pOptionSonCocDatLinh;
	COptionHungVanQuan	m_pOptionHungVanQuan;
	COptionBayBan	m_pOptionBayBan;
	COptionKhoaCuVanDap	m_pOptionKhoaCuVanDap;
	COptionGTienMaKiep	m_pOptionGTienMaKiep;
	COptionHangBauVat	m_pOptionHangBauVat;
	COptionNVHuongDan	m_pOptionNVHuongDan;
	COptionNVTuChan	m_pOptionNVTuChan;
	COptionNVAn	m_pOptionNVAn;
	COptionNVPhu	m_pOptionNVPhu;
	COptionNVThan	m_pOptionNVThan;
	COptionNVTruyen	m_pOptionNVTruyen;
	COptionKhaoCo	m_pOptionKhaoCo;
	COptionBayBanTheoDeNghi	m_pOptionBayBanTheoDeNghi;
	void InitTabDialogs();
	void EnableTabs(BOOL bEnable);
	void SetGameActive(CGameInfo* pGame);
	void SetDefaultTabs();
	void UpdateTabDialogs(CGameInfo* pGame);

public:
	CMainTabCtrl(void);
	~CMainTabCtrl(void);
	
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
};
