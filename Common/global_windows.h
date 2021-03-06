#pragma once
#include "global.h"

#define	TAB_INDEX_GAMECONTROL	0
#define	TAB_INDEX_EMULATOR		1
#define	TAB_INDEX_GAMESTATUS	2
#define	TAB_INDEX_GAMEHIDE		3

#define	WM_MSG_EMULATOR_EVENT	(WM_USER + 0x1001)
#define	EVENT_MANAGER_INIT		1
#define	EVENT_EMULATOR_INIT		2

#define MAX_ACTIVITY_PERIOD			7
#define DAY_SUNDAY		0x01 
#define DAY_MONDAY		DAY_SUNDAY << 1
#define DAY_TUESDAY		DAY_SUNDAY << 2
#define DAY_WEDNESDAY	DAY_SUNDAY << 3
#define DAY_THURSDAY	DAY_SUNDAY << 4
#define DAY_FRIDAY		DAY_SUNDAY << 5
#define DAY_SATURDAY	DAY_SUNDAY << 6

typedef struct _ACTIVITY_PERIOD{
	//khoang thoi gian hoat dong trong ngay	
	int		bChecked;
	int		iFrom;
	int		iTo;
}ACTIVITY_PERIOD;


typedef struct _ACTIVITYINFO : public _ACTIVITY_BASE
{
	BOOL			bChecked;		//Check hoạt động
	WCHAR			szName[128];	//Tên hoạt động
	char			szAlias[128];	//Bí danh hoạt động
	WCHAR			szStatus[16];	
	ActivityType	iType;			//Kiểu hoạt động
	UINT			uIDD;			//IDD_DIALOG thiết lập chức năng
	DWORD			dwDelayAt;
	DWORD			dwDelayIn;
	
	BYTE			week;						//dung khi iType = atp_fixedtime, ngay hoat dong trong tuan,					
	ACTIVITY_PERIOD time[MAX_ACTIVITY_PERIOD];	//dung khi iType = atp_fixedtime, gio hoat dong trong ngay, 
}ACTIVITYINFO;


typedef struct _ACTIVITYTAB {
	ACTIVITYINFO	lstActivity[MAX_NUM_ACTIVITY];
	int				lstDictionary[MAX_NUM_ACTIVITY];
	int				iCurActivity;
	BOOL			bUpdateControlNow;
	BOOL			bDebug;
	ACTIVITYINFOEX	lstActivityEx[MAX_NUM_ACTIVITYEX];
}ACTIVITYTAB;


typedef enum _Sync_Again{
	SYNC_CURRENT_NONE = 0,
	SYNC_CURRENT_ACTIVITY,
	SYNC_CURRENT_ACTIVITY_OPTION,
	SYNC_CURRENT_ACTIVITYEX,
	SYNC_CURRENT_OPTION
}SyncCurrentAgain;

//Các flag dùng để kiểm tra đồng bộ tại hàm CDeviceManagerEx::Sync_xxx()
typedef struct _GAME_SYNC_FLAGS{
	BOOL	bControl;
	BOOL	bLogined;
	int		iCurrentActivity;
	BOOL	bCurrentActivityOption;	
	LOGIN_ACCOUNT loginAccount;
	_LIST_GIAODICH	lstGiaoDich;
	UINT	 uTimeUpdateTeam;
}GAME_SYNC_FLAGS;


#define  ACCOUNTMODE_INLIST		1
#define  ACCOUNTMODE_FIXED		0
#define  MAXNUM_SERVERINDEX		50
typedef struct _LOGINTAB{
	int				iAccountMode;
	LOGIN_ACCOUNT	accountFixed;

}LOGINTAB;