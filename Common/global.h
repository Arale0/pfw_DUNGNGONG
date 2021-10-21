#pragma once

#define BUILD_FLAG_DEBUG

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if(x != NULL) { delete (x); (x) = NULL; } }
#endif

#define ONE_DAY_TIMER			(1000 * 60 * 60 * 24)

#define TXT_GAME_APP			"com.pg1.tghmm"


#define TXT_AUTO_EXE			TEXT("pwmAutom.exe")	//ztAutom
#define TXT_LICENSE_AIG			TEXT("License.aig")
#define TXT_AUTO_DLL			TEXT("Engine.dll")
#define UINT_ENTRY_ENCODE		0x20200528
typedef enum _NetCommands{
	NET_CMD_AUTH = 1,
	NET_CMD_EXIT_AUTO,
	NET_CMD_CONTROL,			//check control from auto
	NET_CMD_ACCOUNT_INFO,		
	NET_CMD_LOGINED,			//game lo/gined
	NET_CMD_LOGINED_PLAYER,		//player name logined
	NET_CMD_LOGINED_MAP,		//map name
	NET_CMD_LOGINED_MAPPOS,		//x,y of map
	NET_CMD_LOGIN_INFO,			//user, pass, server 
	NET_CMD_ACTIVITY_CURRENT,
	NET_CMD_ACTIVITY_STATUS,
	NET_CMD_ACTIVITY_OPTION,
	NET_CMD_ACTIVITY_STT_BYLEADER,
	NET_CMD_GAME_REQUESTACCOUNT,
	NET_CMD_LOGIN_ACCOUNT,
	NET_CMD_TEAM,
	NET_CMD_TEAM_OPTION,
	NET_CMD_OPTIONTAB,
	NET_CMD_GIAODICH,
	NET_CMD_CURRENTID,
	NET_CMD_STOPGAME
}NetCommands;

enum ActivityId{
	act_none = -1,act_trucdietaclinh,act_thuongthienphatac,
	act_pbhoanghon,act_pbtuchan,
	act_nvbang,
	act_kepgiaydoibietthu,
	act_quyetdaudinhcao,
	act_mainquest,act_baybantheodenghi,act_LAST, 
	act_phuongdegian,act_phuongminhcoc,act_vandapngay,act_tangbaodo,act_dangongcuong,act_vantieubang,act_truonglaotutien,act_chientubang,act_phutuyen,act_thosantienthuong,act_ghepphulinh,act_soncocdatlinh,act_hungvanquan,act_khoacuvandap,act_gtienmakiep,act_nvhuongdan,act_nvtuchan,act_nvan,act_nvphu,act_nvthan,act_nvtruyen,act_khaoco,act_truthienphudo,
	actex_1,
	actex_LAST
};
#define MAX_NUM_ACTIVITY			(act_LAST)
#define MAX_NUM_ACTIVITYEX			(actex_LAST - act_LAST - 1)
#define MAX_NUM_TEAMMEMBER			6

#define  TEAMMODE_MATCH			0
#define  TEAMMODE_LEADER		1
#define  TEAMMODE_MEMBER		2
#define  TEAMMODE_ALONE			3
#define  TEAMMODE_INTELLIGENCE	4
enum ActivityType{
	atp_normal = 0, //Chức năng thông thường
	atp_fixedtime,  //Hoạt động theo thời gian cố định
	atp_unstable,	  //Hoạt động không cố định (theo thời gian chờ)
	atp_behavior
};  //Hoạt động theo hành vi

enum ActPriority{
	priority_0 = 0,  //Mức ưu tiên chức năng
	priority_1, 
	priority_2, 
	priority_3, 
	priority_4, 
	priority_5
};

enum ActivityStatus{
	ast_donot = 0, //Chưa làm
	ast_doing,	   //Đang làm
	ast_waiting,   //Đang chờ
	ast_done,	   //Xong lượt
	ast_suspend,   //Bị chèn
	ast_destroy,   //Hủy toàn bộ
	ast_unknown
};  //Không rõ	


//Dùng để gửi và nhận Window => Android
typedef struct _ACTIVITY_BASE{
	ActivityId		iId;			//ID hoạt động
	ActivityStatus	iStatus;		//Trạng thái hoạt động
	UINT			uFuncId;		//id lấy từ DB trong CAIGFunction
	BOOL			bLicensed;		//Xác nhận uFuncId là okie.
	BOOL			bStatusByLeader; //
}ACTIVITY_BASE;

typedef struct _ACTIVITYINFOEX_MAINQUEST
{
	int				iLevelLimit;
}ACTIVITYINFOEX_MAINQUEST;


typedef struct _ACTIVITYINFOEX		// hoat dong mo rong (ngoai danh sach hoat dong chinh)
{
	BOOL			bChecked;		//Check hoạt động
	ActivityId		activity;		//Các hoạt động phía sau act_LAST

	UINT			uFuncId;		//id lấy từ DB trong CAIGFunction
	BOOL			bLicensed;		//Xác nhận uFuncId là okie.
	union {
		ACTIVITYINFOEX_MAINQUEST	mainquest;


	};

}ACTIVITYINFOEX;

typedef struct _ACCOUNT_INFO{
	//char		czUserID[32];
	char		czUsername[64];
	//char		czSocialID[32];
	UINT		uTypeLogin;

	//char		czRoleId[64];
	//UINT		uRoleLevel;
	char		czRoleName[64];	
	//char		czRoleInfo[64];
	UINT		uServerId;
	char		czServerName[64];	
}ACCOUNT_INFO;

typedef struct _OPTIONTAB {
	int		bTest;
	BOOL	bFuli;
	BOOL	bAchievement;
	BOOL	bDeWhite;
	BOOL	bDeBlue;
	BOOL	bDeViolet;
	int		iDeMinute;
	BOOL	bBagSellStone;
	BOOL	bBagUseEquips;
	BOOL	bBagInFb;
	BOOL	bCleanBag;
	BOOL	bSellCertification;
	BOOL	bDungTrangBi;
	BOOL	bTachTrangBiKhoa;
	BOOL	bTachTrangBiLcCao;
	BOOL	bBanDaAoTien;
	BOOL	bBanBua;
	BOOL	bBanDaCanKhon;
	BOOL	bOptimizeCPU;
	int		iOptionFPS;
	BOOL	bAutoBuyPatch;
	int		iAmountOfPatchHP;
	int		iAmountOfPatchMP;
	BOOL	bAutoBuyPatch2;
	int		iHPLevel;
	int		iMPLevel;
	BOOL	bGop;
	BOOL	bTachTrangBiVang;
	BOOL	bBanNgLieuCam59;
	BOOL	bTachGold59;
	BOOL	bTachGold69;
	BOOL	bTachGold79;
	BOOL	bTachGold89;
	BOOL	bTachGoldAllLV;
	BOOL	bBanPhuLinh;
	BOOL	bSellOther;
	BOOL	bUseFairyEgg;
	BOOL	bSell_BiQuyenCoDai;
	BOOL	bSell_DaThienCanh;
	BOOL	bBagAnhHon;
	int		iBagCleanType;
	BOOL	bBagCleanPoint1;
	BOOL	bBagCleanPoint2;
	int		iBagCleanPoint1;
	int		iBagCleanPoint2;
	BOOL	bBagSellSoul;
	BOOL	bBagChangeMapYuanLing;

	BOOL	bGetSilverBox;
	BOOL	bRunGameWhenCrash;
	BOOL	bRecDynamic;
	BOOL	bOptimizeCPUAct;
	BOOL	bCheckMail;
	BOOL	bBagFull;
	BOOL	bCdTuChan;
	BOOL	bTradePriority;
	
	//relive
	BOOL	bUsePatchRelive;
	
	//ap tieu
	BOOL	bVTCleanBag;
	BOOL	bTVNotFollow;
	
	//Tru thien phu do
	BOOL bTruThienGoAllTime;
	BOOL bTruThienSweepOnly;

	//pbhoanghon
	int iHHDifficult;
	int iHHCountTime;
	BOOL bHHLeaderSkip;
	BOOL bHHMemAutoSearch;
	//pb tu chan
	int iTCDifficult;
	int iTCCountTime;
	BOOL bTCLeaderSkip;
	BOOL bTCMemAutoSearch;
	BOOL bTC2TimeToFinished;

	//da ngong cuong
	BOOL bDNCBuyByGold;
	int iDNCAmountOf;

	//truc diet ac linh
	BOOL bTDALPlayerSet;
	BOOL bTDALFollowLeader;
	BOOL bTDALNotCheckCountTime;
	BOOL bTDALOpenSetting;
	BOOL bTDALTimeGotoBoss;
	int	 iTDALTime;

	//tho san tien thuong
	int iTSTTBossLevel;

	//quyet dau dinh cao
	BOOL bQDDCRandom;

	//bay ban
	BOOL bSellOrangeFood;
	BOOL bSellOrangeEquips;
	BOOL bSellLV59;
	BOOL bSellLV69;
	BOOL bSellLV79;
	BOOL bSellLV89;
	int iSellPercent;

	//TBD
	BOOL	bTBDGiaoDich;
	BOOL	bTBDTrung;
	BOOL	bTBDCao;

	//khao co
	int		iKhaoCoNo1;
	int		iKhaoCoNo2;
	int		iKhaoCoNo3;

	int iPercentGdTBD;
	int iPercentGdThienCoTai;
	int iPercentGdVang59;

}OPTIONTAB;


typedef struct _LIST_GIAODICH{
	char	czItem1[100];
	char	czItem2[100];
	char	czItem3[100];
	char	czItem4[100];
	char	czItem5[100];
	char	czItem6[100];
	char	czItem7[100];
	char	czItem8[100];
	char	czItem9[100];
	char	czItem10[100];
	char	czItem11[100];
	char	czItem12[100];
	char	czItem13[100];
	BOOL bSellOrangeFood;
	BOOL bSellOrangeEquips;
	BOOL bSellLV59;
	BOOL bSellLV69;
	BOOL bSellLV79;
	BOOL bSellLV89;
	BOOL bTradeSkip;
	int iSellPercent;
	int iSellByLevel;
	int iCostMode;

}_LIST_GIAODICH;

typedef struct _SYNCVALUES {
	//team
	BOOL	bUpdateActivityStatusByLeader;
	BOOL	bActivityStatus; 
	char	czLeader;
}SYNCVALUES;


typedef struct _MEMBER {
	char	czTeamName[64];
}MEMBER;
typedef struct _TEAMOPTION {
	BOOL	bJiebai;
	BOOL	bKickMembers;
	BOOL	bMemberAcceptJiebai;
	int		iTeamType;
	int		iSLTV;
	BOOL	bAloneCheckTeamTarget;
	BOOL	bAloneExitTeam;
	int		iAloneCheckTime;
	BOOL	iMemberKeepTeam;
	BOOL	bInviteFriends;
	BOOL	bMemAcceptFriendsInvite;
}TEAMOPTION;
typedef struct _TEAMTAB {
	int		iTeamId;
	int		iTeamMode;
	MEMBER	members[MAX_NUM_TEAMMEMBER];
	MEMBER	membersInLeaderMode[MAX_NUM_TEAMMEMBER];
	char	czLeaderInMemberMode[64];
	UINT	uTimeUpdate;//use to sync
	BOOL	bUpdateNow;//use to update UI
	//BOOL	bJiebai;
	BOOL	bSyncTeamOption;
	TEAMOPTION teamOption;
}TEAMTAB;

typedef struct _ACTIVITY_STATUS {
	BOOL bPhuongMinhCoc;
	BOOL bPhuongDeGian;
	BOOL bSyncActivityStatus;
}ACTIVITY_STATUS;

typedef struct _PUBLISHER_ACCOUNT{
	char	czUsername[64];
	char	czPassword[32];	
}PUBLISHER_ACCOUNT;
typedef struct _ROLE_LOGIN{
	int		iServer;
	int		idxPlayer;
	char	czRoleName[64];
	int		iRoleNo;
}ROLE_LOGIN;
typedef struct _LOGIN_ACCOUNT{
	PUBLISHER_ACCOUNT	publisherAccount;
	ROLE_LOGIN			roleLogin;
}LOGIN_ACCOUNT;
