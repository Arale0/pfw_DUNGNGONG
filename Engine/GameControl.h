#pragma once
#include "GameClasses.h"
#include "SysTypes.h"
//#include <map>
#define WAIT_WND_OPENED		1
#define WAIT_WND_CLOSED		2
#define WAIT_WND_EXIST		3

#define MSG_OK				1
#define MSG_CANCEL			2

#define SCENEID_HOTHONGTHIEN  4
#define SCENEID_BENTAMMONG	  92
#define SCENEID_NGTHANHTOLONG 34

#define Jiebai		1
#define Friends		2
#define NameLeader  3

class CGameControl
{
public:
	CUIManager	  *m_pUIManager;
	CUE_Transform *m_pUIRoot;

	CUE_Transform *m_pBaseUIRoot;
	CUE_Transform *m_pPopUIRoot;
	CUE_Transform *m_pStoryUIRoot;
	CUE_Transform *m_pTipUIRoot;
	CUE_Transform *m_pMessageUIRoot;
	CUE_Transform *m_pDeathUIRoot;
	CUE_Transform *m_pFloatUIRoot;
	CUE_Transform *m_pStoryMessageUIRoot;

	CPlayerData *m_pPlayerData;
	CDeviceStatusWindow *m_pDeviceStatus;

	CSysTypes*			m_gameSysTypes;
	CSysTypes*			m_ueuiSysTypes;
	CSysTypes*			m_uecoreSysTypes;
	DWORD				m_dwVAF_ListUint64;
	DWORD				m_dwVAF_ArrUint64;
	//Tinh toan toa do
	float				m_system_render_rateWidth;
	float				m_system_render_rateHeight;
	float				m_othorgraphicSize;
	int					m_renderWidth;
	int					m_renderHeight;
	float				m_renderRate;
	float		m_renderWidthHalf;
	float		m_renderHeightHalf;
	int					m_systemWidth;
	int					m_systemHeight;
public:
	BOOL InitUnity();
	BOOL IsInitBaseTransform();
	void InitBaseTransform();
	BOOL IsShowTransform(CUE_Transform *p);
	BOOL GetPixelCenter( CUE_Transform* p, POINT& pt );
	BOOL Tap( CUE_Transform* p );
	BOOL Tap( int x, int y );
	BOOL Clicked( CUE_Transform* p );
	BOOL ClickServerListItem(CUE_Transform *pChooseList, int iServer);
	CStdString GetTextA( CUE_Transform* p );
	CStdStringU GetTextU( CUE_Transform* p );

	BOOL MissionClicked( CUE_Transform* p );
	CStdString U2A( LPCUSTR czU );
	BOOL Process_FirstLogout();
	BOOL Process_FirstLogined();
	BOOL UpdateLoginState();
	BOOL UpdateAccountInfo();
	BOOL UpdateRoleInfo();
	BOOL IsUIServerChoose();
	BOOL IsUIRoleChoose();
	BOOL IsPickUpBtn();
	BOOL IsBagFull();
	BOOL IsFuliRedDot();
	BOOL IsAchievementRedDot();
	BOOL IsNewMail();
	BOOL IsShowFuliWnd();
	BOOL IsAchievementWnd();
	
	BOOL IsPVPResultWnd();
	BOOL GetExecPickBtn();
	BOOL IsButtonExitFuben();
	BOOL IsSetSceneUI();
	BOOL IsLoading();
	BOOL IsMessageBox(CStdStringU czU, BOOL bSwicth = FALSE);
	BOOL IsActivity(CStdStringU czU, BOOL &bFinished, BOOL bOnlyCheck = FALSE);
	BOOL IsActivityWithName(CStdStringU czU, BOOL &bFinished);
	BOOL IsMap(CStdStringU czU);
	BOOL IsMissionTrack(CStdStringU czU, UINT &uTransform);
	BOOL IsCenterNotice(CStdStringU czU);
	BOOL IsStoryUIRoot();
	BOOL IsBatterySaver();
	BOOL IsProcessing();
	BOOL get_LoadingScene();
	BOOL get_WaitForLoadAllBlock();
	BOOL IsMoving(BOOL bStopMove = FALSE);
	BOOL IsMovingXYZ();
	BOOL IsMoving_Transform();
	BOOL IsShowPopUI();
	BOOL IsShowTransformKnapsack();
	BOOL AutoFightIsOn();
	BOOL IsLowerLevel(int iNeedLevel);
	BOOL IsGuildName(CStdStringU czU);
	BOOL IsReliveWnd();
	BOOL IsShowReliveWnd();
	BOOL IsCopyFinishedFubenWnd();
	BOOL IsUILevelUpWnd(); //dialog thăng cap
	BOOL IsYingFuPopup();//exp chuc phuc
	BOOL IsFBResultWnd();
	BOOL IsFightFb(CStdStringU czUNameFb, int iLevelDifficult);
	BOOL IsTeamTarget(CStdStringU czUName, BOOL bIsLeader = TRUE);
	BOOL IsLowerLevelWnd();
	BOOL IsNPCHeadInfo(CStdStringU czName, UINT &uObj_NPC);
	BOOL IsCopySceneReady();
	BOOL IsConvoyConfirm();
	BOOL IsItem_qbzroot();
	BOOL IsWorldMap(UINT &uParent);
	BOOL IsRoleviewReserve();
	BOOL IsNearPlayer(CStdStringU czNamePlayer);
	BOOL IsSingleActivity();
	BOOL IsNPC(CUE_Transform *p);
	BOOL IsEnableButton(CUE_Transform *p);

	BOOL IsShowTargetBar(CStdStringU czNameBoss = u"");
	BOOL IsImmortalRedot();
	BOOL IsNoticeWnd();
	BOOL IsHaveGuild();
	BOOL ButtonCloseIsShow(CUE_Transform *p);
	
	//Team Ability
	BOOL			TeamCreate();
	BOOL			TeamInvite(LPCSTR szName);
	BOOL			TeamInvite(MEMBER *pMembers);
	void			OpenInvite();
	BOOL			TeamInviteAccept(LPCSTR szName);
	BOOL			MemberAccept(int iFrom = Jiebai);
	BOOL			IsHaveTeam();
	BOOL			CanLeaveTeam();
	void			TeamLeave();
	void			SwitchTeamTab();
	BOOL			ProcessMessageBox(LPCUSTR czTxt,int iID);
	BOOL			IsLeader();
	BOOL			IsRightLeader(LPCSTR szName);
	BOOL			IsFullMemberInController(MEMBER* pMembers);
	BOOL			IsFullMember(MEMBER* pMembers);
	BOOL			IsMemberInTeam(CStdStringU czName);
	BOOL			KickMemberInController(MEMBER* pMembers);
	BOOL			KickMember(MEMBER* pMembers);	
	BOOL			IsTeamEnoughMembers(int iSLTV);
	BOOL			IsNotEnoughMembers();
	BOOL			IsMember();
	BOOL			IsTeamLeader();
	BOOL			IsMemberSet();
	BOOL			IsLeaderSet();
	BOOL			IsTeamAloneSet();
	BOOL			IsTeamAvailableSet(BOOL bIsLeader = TRUE);
	BOOL			IsFollowLeader();
	BOOL			IsHasTeam();
	BOOL			IsFullTeam();
	void			FollowLeader(BOOL bFollow = TRUE);
	void			LeaveTeam();
	void			TeamWnd();
	void			InviteAllFriends();
	void			ReqJoinTeam(CStdStringU czNameLeader);
	void			set_teamTarget(CStdStringU czName);
	BOOL			processIfReqJoinTeam();
	void			CloseTeamWnd();
	BOOL			exitTeamIfAloneTeamSet();
	CStdStringU		get_NameMemberOnUIAuto(MEMBER *pMembers, int idx);
	void	ClickTab(CUE_Transform *p);
	

	CStdStringU get_NameLeader();
	CStdStringU get_NameMember(int iMember);
	CStdStringU get_NameMap();
	CStdStringU get_LineMap();
	CStdStringU getCurrentNameLine();
	CStdStringU getNameMember(CTeam* pTeam, int iMember);
	
	void	SwitchAutoFight(BOOL bSwicth = FALSE);
	void	CloseDialog();
	void	ClickButtonHuDong();
	void	ShowLimitTips();
	void	ShowMap();
	void	CloseNPCTalk();
	void	ExitFB();
	void	CancelAcceptMessageBoxWithCheckBox();
	void	OnClickButtonManaLack();
	void	show_WorldMap();
	void	skipTrailer();
	void	get_PositionWithEmulatorSize(CUE_Transform *p, int &x, int &y);
	void	AskTeamFollow();
	void	OnTeamTabClick();
	void	ClickNPCInMaple(CStdStringU czNPCName);
	void	CheckSilverBox();
	void	ShowSettingWnd();
	void	ReceivedBonusItem();
	void	ShowFuliWnd();
	void	ShowTaskAchievementWnd();
	BOOL	checkCanJoinActivity(ActivityId iActivityID, BOOL &bFinished);
	void	ChangeScene(int sceneId);
	void	ClosePopManyChar();
	void	OnOffSettingWnd();
	void	MoveToTarget(CObj_Char *pChar);
	void	SetCurrentID(int iIdSet);

	int		get_GoldCoin();
	int		get_Level();
	int		get_haveTeamCount();
	int		getPos(int iPos);
	int		getCurrentLine();
	int getTime(int iTypeTime);


	CUE_Transform * getTransformFromString(CUE_Transform *p, CStdString czString);

	CPlayerData		*get_PlayerData();

	CUE_Transform *get_Transform(UINT uTemp);
	CObj_MainPlayer *get_MainPlayer();
	CObj_Char	*getNPC(CStdStringU czName);
	CObj_Char *getNPC(CUE_Transform *p, CStdString czObjName = "Obj_NPC");
	CObj_Char *getPlayer(CStdStringU czName);

	CUE_Transform *get_NPCHeadInfoLogic(CUE_Transform *p);
	CUE_Transform *get_CharRoot();

	CSYS_List *get_BrotherhoodList();
	CSYS_List *get_FriendsList();

	void Test();
	void Test1();
	void showAllActivity();
	void showAllNPC(BOOL bShowed = FALSE);

	void FindNameASSEMBLY();
	void TestTeam();
	void TestQuest();
	void TestObjectArray();
	void TestQuest1(CSYS_List *pList);
	void TestBag();
	void TestYLTX();
	void TestPatch();
	void TestTimeYLTX();
	void ShowListNPC();
	
public:
	CGameControl(void);
	~CGameControl(void);

};
