#include "StdAfx.h"
#include "mobiAuto.h"
#include "ActivitySetting.h"
#include "OptionVanTieuBang.h"

CActivitySetting* CActivitySetting::m_pActivitySetting = NULL;

CActivitySetting* CActivitySetting::GetInstance()
{
	if(m_pActivitySetting == NULL) m_pActivitySetting = new CActivitySetting();
	return m_pActivitySetting;
}

void CActivitySetting::InitActivity(CGameInfo* pGame)
{
	if(!pGame) return;
	m_pActivityTab = pGame->GetActivityTab();
	if(!m_pActivityTab) return;
	/*Khởi tạo danh sách chức năng trên ActivityTab theo cú pháp:
	  - ID hoạt động
	  - Tên hoạt động
	  - Bí danh hoạt động - chuỗi MultiByte
	  - IDD_DIALOG thiết lập chức năng nếu có
	  - Loại module license cần kiểm tra theo từng chức năng*/
	/*Code here*/
	/*
	CString s;
	CStringA sA;
	for (int i = 0; i < MAX_NUM_ACTIVITY; ++i)
	{
		sA.Format("nvchinhtuyen_%d",i);
		s.Format(L"Chính tuyến_%d",i);
		AddActivity(i,	s,		sA);
	}
	*/
	AddActivity(act_mainquest,	L"Main Quest",		"mainquest",NULL, 246);//, IDD_DIALOG_OPTION_MAINTASK,	182);	
	AddActivity(act_nvbang,L"Nhiệm Vụ Bang","nvbang",NULL,246);
	//AddActivity(act_vandapngay,L"Vấn Đáp Ngày","vandapngay",NULL,246);
	AddActivity(act_kepgiaydoibietthu,L"Kẹp Giấy Đổi Biệt Thự","kepgiaydoibietthu",NULL,246);
	AddActivity(act_quyetdaudinhcao,L"Quyết Đấu Đỉnh Cao","quyetdaudinhcao",IDD_DIALOG_OPTION_QUYETDAUDINHCAO,246);
	//AddActivity(act_truthienphudo,L"Tru Thiên Phù Đồ","truthienphudo",IDD_DIALOG_OPTION_TRUTHIENPHUDO,246);
	//AddActivity(act_phuongdegian,L"Phượng Đề Giản","phuongdegian",NULL,246);
	//AddActivity(act_phuongminhcoc,L"Phượng Minh Cốc","phuongminhcoc",NULL,246);
	//AddActivity(act_tangbaodo,L"Tàng Bảo Đồ","tangbaodo",IDD_DIALOG_OPTION_TANGBAODO,246);
	AddActivity(act_thuongthienphatac,L"Thưởng Thiện Phạt Ác","thuongthienphatac",NULL,246);
	AddActivity(act_pbhoanghon,L"PB Hoàng Hôn","pbhoanghon",IDD_DIALOG_OPTION_PBHOANGHON,246);
	AddActivity(act_pbtuchan,L"PB Tu Chân","pbtuchan",IDD_DIALOG_OPTION_PBTUCHAN,246);
	//AddActivity(act_dangongcuong,L"Đá Ngông Cuồng","dangongcuong",IDD_DIALOG_OPTION_DANGONGCUONG,246);
	//AddActivity(act_vantieubang,L"Vận Tiêu Bang","vantieubang",IDD_DIALOG_OPTION_VANTIEUBANG,246);
	
	//AddActivity(act_chientubang,L"Chiến Tu Bang ","chientubang",IDD_DIALOG_OPTION_CHIENTUBANG,246);//IDD_DIALOG_OPTION_CHIENTUBANG
	//AddActivity(act_truonglaotutien,L"Trưởng Lão Tu Tiên","truonglaotutien",NULL,246);
	//AddActivity(act_phutuyen, L"NV Phụ Tuyến","nvphutuyen",NULL,246);
	AddActivity(act_trucdietaclinh,L"Trục Diệt Ác Linh","trucdietaclinh",IDD_DIALOG_OPTION_TRUONGLAOTUTIEN,246);
	//AddActivity(act_thosantienthuong,L"Thợ Săn Tiền Thưởng","thosantienthuong",IDD_DIALOG_OPTION_THOSANTIENTHUONG,246);
	//AddActivity(act_ghepphulinh,L"Ghép Phụ Linh","ghepphulinh",NULL ,246);//IDD_DIALOG_OPTION_GHEPPHULINH
	//AddActivity(act_soncocdatlinh,L"Sơn Cốc Dật Linh","soncocdatlinh",IDD_DIALOG_OPTION_SONCOCDATLINH,246);
	//AddActivity(act_hungvanquan,L"Hùng Vạn Quân - Xuân","hungvanquan",IDD_DIALOG_OPTION_HUNGVANQUAN,246);
	//AddActivity(act_mainquest,L"Bày Bán","bayban",IDD_DIALOG_OPTION_BAYBAN,0);
	//AddActivity(act_khoacuvandap,L"Khoa Cử Vấn Đáp","khoacuvandap",IDD_DIALOG_OPTION_KHOACUVANDAP,0);
	//AddActivity(act_gtienmakiep,L"Tiên Ma Kiếp","gtienmakiep",IDD_DIALOG_OPTION_GTIENMAKIEP,0);
	//AddActivity(act_hangbauvat,L"Hang Báu Vật","hangbauvat",IDD_DIALOG_OPTION_HANGBAUVAT,0);
	//AddActivity(act_nvhuongdan,L"Nhiệm vụ hướng dẫn","nvhuongdan",IDD_DIALOG_OPTION_NVHUONGDAN,0);
	//AddActivity(act_nvtuchan,L"NV Tu Chân","nvtuchan",IDD_DIALOG_OPTION_NVTUCHAN,0);
	//AddActivity(act_nvan,L"NV Ẩn","nvan",IDD_DIALOG_OPTION_NVAN,0);
	//AddActivity(act_nvphu,L"NV Phụ","nvphu",IDD_DIALOG_OPTION_NVPHU,0);
	//AddActivity(act_nvthan,L"NV Thần","nvthan",IDD_DIALOG_OPTION_NVTHAN,0);
	//AddActivity(act_nvtruyen,L"NV Truyền Kỳ","nvtruyen",IDD_DIALOG_OPTION_NVTRUYEN,0);
	//AddActivity(act_khaoco,L"Khảo Cổ","khaoco",IDD_DIALOG_OPTION_KHAOCO,0);
	AddActivity(act_baybantheodenghi,L"Bày bán theo % đề nghị","baybantheodenghi",IDD_DIALOG_OPTION_BAYBANTHEODENGHI,0);
}
void CActivitySetting::AddActivity(int iId, CString szName, CStringA szAlias, UINT uIDD /*= NULL*/, UINT uFuncId /*= MAXUINT*/)
{
	if(iId >= MAX_NUM_ACTIVITY) return;
	m_pActivityTab->lstDictionary[iId] = iId;
	ACTIVITYINFO *pActInfo = &m_pActivityTab->lstActivity[iId];
	pActInfo->iId = (ActivityId)iId;
	wcscpy_s(pActInfo->szName, 128, szName.GetBuffer());
	strcpy_s(pActInfo->szAlias, 128, szAlias.GetBuffer());
	pActInfo->uIDD = uIDD;
	pActInfo->uFuncId = uFuncId;
	pActInfo->iType = atp_normal;
	memset(pActInfo->time, 0 , sizeof(ACTIVITY_PERIOD) * MAX_ACTIVITY_PERIOD);
	pActInfo->week = 0xFF;
	
	if(pActInfo->iId == act_trucdietaclinh){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(12);			//18:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(23, 50);			//21:00
	}

	if(pActInfo->iId == act_soncocdatlinh){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(12);			//18:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(12, 55);			//21:00
		pActInfo->time[1].bChecked = TRUE;
		pActInfo->time[1].iFrom =	CUtils::GetTimeLine(21);			//18:00
		pActInfo->time[1].iTo =		CUtils::GetTimeLine(21, 55);			//21:00
	}

	if(pActInfo->iId == act_vandapngay){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(18);			//18:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(21);			//21:00
	}

	if(pActInfo->iId == act_hungvanquan){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(19, 30);			//18:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(20);			//21:00
		pActInfo->week = 0x00;
		pActInfo->week = DAY_SUNDAY; 
	}


	if(pActInfo->iId == act_phuongdegian){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(0);				//00:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(23,59,59);		//23:59:59
		//gan ngay hoat dong trong tuan
		pActInfo->week = 0x00;
		pActInfo->week = DAY_TUESDAY | DAY_THURSDAY | DAY_SATURDAY;
	}

	if(pActInfo->iId == act_phuongminhcoc){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(0);				//00:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(23,59,59);		//23:59:59
		//gan ngay hoat dong trong tuan
		pActInfo->week = 0x00;
		pActInfo->week = DAY_MONDAY | DAY_WEDNESDAY | DAY_FRIDAY | DAY_SUNDAY;
	}

	if(pActInfo->iId == act_vantieubang){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(19);				//00:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(20,59,59);		//23:59:59
		//gan ngay hoat dong trong tuan
		pActInfo->week = 0x00;
		pActInfo->week =  DAY_WEDNESDAY | DAY_FRIDAY;
	}

	if(pActInfo->iId == act_truonglaotutien){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(19,29,59);				//00:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(19,45,00);		//23:59:59
		//gan ngay hoat dong trong tuan
		pActInfo->week = 0x00;
		pActInfo->week =  DAY_TUESDAY | DAY_THURSDAY;
	}


	if(pActInfo->iId == act_chientubang){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		int timeIndex = 0;
		pActInfo->time[timeIndex].bChecked = TRUE;
		pActInfo->time[timeIndex].iFrom =	CUtils::GetTimeLine(13);				//00:00
		pActInfo->time[timeIndex].iTo =		CUtils::GetTimeLine(13,19,59);		//23:59:59

		timeIndex++;	
		pActInfo->time[timeIndex].bChecked = TRUE;
		pActInfo->time[timeIndex].iFrom =	CUtils::GetTimeLine(14);				//00:00
		pActInfo->time[timeIndex].iTo =		CUtils::GetTimeLine(14,19,59);		//23:59:59

		timeIndex++;
		pActInfo->time[timeIndex].bChecked = TRUE;
		pActInfo->time[timeIndex].iFrom =	CUtils::GetTimeLine(15);				//00:00
		pActInfo->time[timeIndex].iTo =		CUtils::GetTimeLine(15,19,59);		//23:59:59

		timeIndex++;
		pActInfo->time[timeIndex].bChecked = TRUE;
		pActInfo->time[timeIndex].iFrom =	CUtils::GetTimeLine(16);				//00:00
		pActInfo->time[timeIndex].iTo =		CUtils::GetTimeLine(16,19,59);		//23:59:59

		timeIndex++;
		pActInfo->time[timeIndex].bChecked = TRUE;
		pActInfo->time[timeIndex].iFrom =	CUtils::GetTimeLine(17);				//00:00
		pActInfo->time[timeIndex].iTo =		CUtils::GetTimeLine(17,19,59);		//23:59:59


		timeIndex++;
		pActInfo->time[timeIndex].bChecked = TRUE;
		pActInfo->time[timeIndex].iFrom =	CUtils::GetTimeLine(18);				//00:00
		pActInfo->time[timeIndex].iTo =		CUtils::GetTimeLine(18,19,59);		//23:59:59

		timeIndex++;
		pActInfo->time[timeIndex].bChecked = TRUE;
		pActInfo->time[timeIndex].iFrom =	CUtils::GetTimeLine(19);				//00:00
		pActInfo->time[timeIndex].iTo =		CUtils::GetTimeLine(19,19,59);		//23:59:59

		//gan ngay hoat dong trong tuan
		pActInfo->week = 0x00;
		pActInfo->week =  DAY_TUESDAY | DAY_THURSDAY;
	}

	if(pActInfo->iId == act_thosantienthuong){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(10,30);				//00:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(22,59,59);		//23:59:59
		//gan ngay hoat dong trong tuan
		pActInfo->week = 0x00;
		pActInfo->week = DAY_MONDAY | DAY_FRIDAY;
	}

	if(pActInfo->iId == act_gtienmakiep){
		pActInfo->iType = atp_fixedtime;
		//gan thoi gian hoat dong trong ngay
		pActInfo->time[0].bChecked = TRUE;
		pActInfo->time[0].iFrom =	CUtils::GetTimeLine(19,28);				//00:00
		pActInfo->time[0].iTo =		CUtils::GetTimeLine(19,40);		//23:59:59
		//gan ngay hoat dong trong tuan
		pActInfo->week = 0x00;
		pActInfo->week = DAY_MONDAY;
	}
}

