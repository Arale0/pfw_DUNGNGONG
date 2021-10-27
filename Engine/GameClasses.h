#pragma once
#include "Il2cppEx.h"
#include "SYS_UInt64.h"
#define IMAGE_UNITY_ENGINE_COREMODULE "UnityEngine.CoreModule"
#define TYPE_UIButton					"UIButton"
#define TYPE_UILabel					"UILabel"
#define TYPE_MissionItem				"MissionItem"
#define TYPE_TeamMemberUIInfo			"TeamMemberUIInfo"
#define TYPE_TeamInvite					"TeamInvite"
#define TYPE_TeamFriendItem				"TeamFriendItem"
#define TYPE_TeamMemberItem					"TeamMemberItem"
#define TYPE_TabController				"TabController"
#define TYPE_TabButton					"TabButton"
#define TYPE_MessageBoxWithCheckBox		"MessageBoxWithCheckBox"
#define TYPE_Camera						"UnityEngine.Camera"
#define TYPE_ServerListItem				"ServerListItem"
#define TYPE_RoleSelectItem				"RoleSelectItem"
#define TYPE_ShiJiaoSetting				"ShiJiaoSetting"
#define TYPE_ActivityHuoDongItem		"ActivityHuoDongItem"
#define TYPE_AsynPVPItem				"AsynPVPItem"
#define TYPE_KnapsackItem				"KnapsackItem"
#pragma region CGameClasses
class CGameClasses
{
protected:
	CGameClasses(void);
	~CGameClasses(void);
public:
	
};
#pragma endregion


#pragma region mscorlib
class CSYS_Array:public CSYS_Object{
public:
	static BOOL	_GetClass();
	static CClass* _class;

	static CSYS_Array* CreateInstance(CSYS_Type *pType, int length);
	void	SetValue(CSYS_Object* pObj, int index);
	CSYS_Object* GetValue(int index);
	int		get_Length();
};

class CSYS_TypeEx:public CSYS_Type{
protected:
	CSYS_TypeEx(void);
	~CSYS_TypeEx(void);
public:
	static CSYS_Object* get_EmptyTypes();
	static CSYS_Type* MakeGenericType(CSYS_Type *pGenericTypeDef, CSYS_Array* pGenericTypeParams);//System.Type,System.Type[]
};

class Activator:public CSYS_Object{
public:
	static CSYS_Object* CreateInstance(CSYS_Type *pType);
};


class CSYS_ListEx: public CSYS_Object{
public:
	CSYS_Array*	_item;
	int			_size;
	int			_version;
public:
	CSYS_Object *get_Item(int index);
	void  Add(CSYS_Object *pObj);
	void  Add_UInt64(ULONGLONG value);

	int get_Count();

};


#pragma endregion mscorlib



#pragma region UNITY_ENGINE

class CUE_Display : public CSYS_Object
{
public:
	static CUE_Display*	get_current();
	int		get_systemWidth();
	int		get_systemHeight();
	int		get_renderingWidth();
	int		get_renderingHeight();
protected:
	CUE_Display(void);
	~CUE_Display(void);
};

class CUE_Camera : public CUE_Component
{
public:
	static CUE_Camera*	get_main();
	float get_orthographicSize();
	int get_pixelHeight();
	int get_pixelWidth();
protected:
	CUE_Camera(void);
	~CUE_Camera(void);
	
};

#pragma endregion

#pragma region ASSEMBLY_CSHARP

class CUIButton:public CUE_MonoBehaviour
{
protected:
	CUIButton(void);
	~CUIButton(void);
public:
	void OnClick();
	BOOL get_isEnabled();
};


class CUILabel:public CUE_MonoBehaviour
{
protected:
	CUILabel(void);
	~CUILabel(void);
public:
	CSYS_String* get_text();
};

class CRecoveryFoodItem:public CUE_MonoBehaviour
{
public:
	void OnClickitemResource();
};

class CUIRoot:public CUE_MonoBehaviour
{
protected:
	CUIRoot(void);
	~CUIRoot(void);
public:	
	CUE_Transform *get_Trans();
	static CSYS_List *get_ListUIRoot();
};

class CUIManager:public CUE_MonoBehaviour
{
protected:
	CUIManager(void);
	~CUIManager(void);
public:
	static CUIManager* Intance();
	CUIRoot* get_UIRoot();
	CUE_Transform* get_UIRootTrans();
	CUE_Transform* get_baseUIRoot();
	CUE_Transform* get_popUIRoot();
	CUE_Transform* get_storyUIRoot();
	CUE_Transform* get_tipUIRoot();
	CUE_Transform* get_messageUIRoot();
	CUE_Transform* get_deathUIRoot();
	CUE_Transform* get_FloatUIRoot();
	CUE_Transform* get_storyMessageUIRoot();
	CUE_Transform* get_UICameraTransform();
	void	CloseAllPopUI(BOOL bChangeScene = FALSE, CSYS_Object *pObject = NULL);
	void CloseAllTipUI();
	static BOOL IsPopUIShow();
};

class CMissionItem:public CUE_MonoBehaviour
{
protected:
	CMissionItem(void);
	~CMissionItem(void);
public:
	void OnMisClick();
	int  get_misType();
	CStdStringU get_NameLabel();
	CStdStringU get_TypeLabel();
	CStdStringU get_CircleLabel();

};

class CUIToggle:public CUE_MonoBehaviour
{
protected:
	CUIToggle(void);
	~CUIToggle(void);
public:
	BOOL get_isChecked();
};


class CServerChooseWindow:public CUE_MonoBehaviour
{
protected:
	CServerChooseWindow(void);
	~CServerChooseWindow(void);
public:
	static CServerChooseWindow* Instance();

public:
	CStdString	GetSelServerID();
	int			get_curSelectServer();
	void		OnClickChooseServer();
	void		OnClickEnterGame();
	
	void SetSelectServer(int serverId);
	CUIToggle* get_PrivacyToggle();
};

class CServerListItem:public CUE_MonoBehaviour
{
protected:
	CServerListItem(void);
	~CServerListItem(void);
public:
	void OnClickItem();
};

class CRoleSelectItem:public CUE_MonoBehaviour
{
protected:
	CRoleSelectItem(void);
	~CRoleSelectItem(void);
public:
	CUILabel*	get_labelName();
	CStdString  get_roleName();
	void		OnClickItem();
	CRoleSelectItem*		GetRoleData();
};

class CRoleChooseWindow:public CUE_MonoBehaviour
{
protected:
	CRoleChooseWindow(void);
	~CRoleChooseWindow(void);
public:
	static CRoleChooseWindow* Instance();

public:
	void		OnEnterGameClick();
	void		OnClickBack();
	int			m_curSelectItemIndex();
	void		OnRoleSelectItemClick(CRoleSelectItem* RoleSelectItem);
};




class CPickUpBtnLogic:public CUE_MonoBehaviour
{
protected:
	CPickUpBtnLogic(void);
	~CPickUpBtnLogic(void);
public:
	static CPickUpBtnLogic * Instance();
	void ExecPickBtn();
	static BOOL GetPickBtnActive();
	CStdStringU m_Label();
};

class CDialogController:public CUE_MonoBehaviour
{
protected:
	CDialogController(void);
	~CDialogController(void);
public:
	static CDialogController * Instance();
	void AidButtonClick();
	void OnClickCloseMis();
	static int get_DialogID();
	void OnOpt_1();
	void OnClickMisButton0();
	void ClickEnterCopyScene();
};


class CMiniGameBaseLogic:public CUE_MonoBehaviour
{
protected:
	CMiniGameBaseLogic(void);
	~CMiniGameBaseLogic(void);
public:
	static CMiniGameBaseLogic * Instance();
};

class CMiniGameLogic_Erase:public CMiniGameBaseLogic
{
protected:
	CMiniGameLogic_Erase(void);
	~CMiniGameLogic_Erase(void);
public:
	void AutoErase();
	void OnCloseBtnClick();
};


class CShiJiaoSetting:public CUE_MonoBehaviour
{
protected:
	CShiJiaoSetting(void);
	~CShiJiaoSetting(void);
public:
	void Set3D();
};

class CItemPromptSkillLogic:public CUE_MonoBehaviour
{
protected:
	CItemPromptSkillLogic(void);
	~CItemPromptSkillLogic(void);
public:
	static CItemPromptSkillLogic * Instance();
	void OnPromptSkillBtnClick();
};

class CGameSceneLogic:public CUE_MonoBehaviour
{
protected:
	CGameSceneLogic(void);
	~CGameSceneLogic(void);
public:
	static CGameSceneLogic * Instance();
	BOOL get_IsMovingToDoor();
	BOOL get_bIsTransDoor();
	BOOL get_m_bInitUI();
	BOOL get_bIsHideUI();
};

class CNewGuideLogic:public CUE_MonoBehaviour
{
protected:
	CNewGuideLogic(void);
	~CNewGuideLogic(void);
public:
	static CNewGuideLogic * Instance();
	int get_GuideType();
	int get_GuideStep();
};

class CChatFrameController:public CUE_MonoBehaviour
{
protected:
	CChatFrameController(void);
	~CChatFrameController(void);
public:
	static CChatFrameController * Instance();
	BOOL IsShow_ButtonAutoFight();
	static void OnClickAutoFight();
	static void OnClickStopAutoFight();
	void OnClickOpenFriend();
	static BOOL IsbHPEmpty();
	static BOOL IsbHPLack();
	static BOOL IsbMPEmpty();
	static BOOL IsbMPLack();
	void OnChatInfoClick();
};

class CRecoverySettingLogic:public CUE_MonoBehaviour
{
protected:
	CRecoverySettingLogic(void);
	~CRecoverySettingLogic(void);
public:
	static CRecoverySettingLogic * Instance();
	CSYS_Array *m_HPFoodList();
	CSYS_Array *m_MPFoodList();
	void OnClickClose();
};

class CMessageBoxController:public CUE_MonoBehaviour
{
protected:
	CMessageBoxController(void);
	~CMessageBoxController(void);
public:
	static CMessageBoxController * Instance();
	CStdStringU getText();
	void MessageBoxCancel();
	void MessageBoxOK();
};

class CStoryPlayerController:public CUE_MonoBehaviour
{
protected:
	CStoryPlayerController(void);
	~CStoryPlayerController(void);
public:
	static CStoryPlayerController * Instance();
	void ButtonNext();
};

class CRadarWindow:public CUE_MonoBehaviour
{
protected:
	CRadarWindow(void);
	~CRadarWindow(void);
public:
	static CRadarWindow * Instance();
	CStdStringU getSceneName();
	void ShowSceneMap();
	CStdStringU labelLine();
};

class CSettingController:public CUE_MonoBehaviour
{
protected:
	CSettingController(void);
	~CSettingController(void);
public:
	static CSettingController * Instance();
	void OnCloseClick();
};

class CFunctionButtonController:public CUE_MonoBehaviour
{
protected:
	CFunctionButtonController(void);
	~CFunctionButtonController(void);
public:
	static CFunctionButtonController * Instance();
	void OnFuLiClick(); //phuc loi
	void OnClickHuoDong(); //hoat dong
	void OnClickDWBackHomeBtn(); //ve thanh
	void OnClickBackPack(); //tui
	void OnCliskShowLimitTimePushActivityTips();
	BOOL isDaZaoRedDot();
	BOOL isSkillRedDot();
	BOOL IsNeedBagRedDot();
	void OnClickAchievement();
	BOOL IsShow_ExitCopySceneButton();
	void OnNewClickSetting();
	CSYS_List *getList_YLTXRemainNPCData();
	void OnClickImmortality();
	BOOL IsShowGrowWayBtn();
	BOOL IsNeedImmortaityRedDot();
	void OnClickGuildConvoyGo();
	void OnClickGuildConvoyCall();
	void OnClickHome();
	void OnNewClickShop();

};


class CTransform:public CUE_Component
{
protected:
	CTransform(void);
	~CTransform(void);
public:
	CUE_Transform *Find(CStdStringU czU);
	CUE_Vector3 *get_position();

};

class CPickItemProgressController:public CUE_MonoBehaviour
{
protected:
	CPickItemProgressController(void);
	~CPickItemProgressController(void);
public:
	static CPickItemProgressController * Instance();
	BOOL IsRunning();
	CStdStringU m_OptDecLabel();
	void CloseProgress();
};

class CImmortalityWayItem:public CUE_MonoBehaviour
{
protected:
	CImmortalityWayItem(void);
	~CImmortalityWayItem(void);
public:
	BOOL m_bActivate();
	void OnClickAcceptBtn();
	CUE_GameObject *m_AccpetGameObject();
};


class CImmortalityActivityButton:public CUE_MonoBehaviour
{
protected:
	CImmortalityActivityButton(void);
	~CImmortalityActivityButton(void);
public:
	BOOL get_ImmortalityActivityActivate();
	BOOL get_UnAcceptReward();
	void OnClickActivityButton();
};

class CImmortalityViewLogic:public CUE_MonoBehaviour
{
protected:
	CImmortalityViewLogic(void);
	~CImmortalityViewLogic(void);
public:
	static CImmortalityViewLogic * Instance();
	CSYS_List *m_ResourceWayItemList();
	CSYS_Array *m_BottomnImmortalityButtons();
	CImmortalityActivityButton *m_CurSelectActivityButton();
	void OnClickClose();
};


class CTeamMember:public CUE_Object
{
protected:
	CTeamMember(void);
	~CTeamMember(void);
public:
	CStdStringU get_MemberName();
	BOOL get_AutoCombat();
	BOOL IsValid();
};

class CTeam:public CUE_Object
{
protected:
	CTeam(void);
	~CTeam(void);
public:
	int  GetTeamMemberCount();
	BOOL IsFull();
	int get_TeamID();
	int get_TargetID();
	CTeamMember *GetTeamMember(int iMember);
	CTeamMember *GetTeamMember(ULONGLONG uGuild);

};

class CGuild:public CUE_Object
{
protected:
	CGuild(void);
	~CGuild(void);
public:
	CStdStringU get_GuildName();
	BOOL get_IsInGroup();
	int get_GuildSceneID();
};

class CItemPack  :public CUE_Object
{
protected:
	CItemPack(void);
	~CItemPack(void);
public:
	int GetEmptySize();
};


class CRelation:public CUE_Object
{
protected:
	CRelation(void);
	~CRelation(void);
public:
	CStdStringU get_Name();
	ULONGLONG get_Guid();
	int get_State();
	int get_TeamID();
};


class CRelationList:public CUE_Object
{
protected:
	CRelationList(void);
	~CRelationList(void);
public:
	CSYS_List *get_sortedList();
	int GetRelationNum();
};

class CBrotherhoodMember:public CUE_Object
{
protected:
	CBrotherhoodMember(void);
	~CBrotherhoodMember(void);
public:
	ULONGLONG get_BrotherhoodGuid();
	CStdStringU get_MemberName();
};

class CBrotherhood:public CUE_Object
{
protected:
	CBrotherhood(void);
	~CBrotherhood(void);
public:
	CSYS_List *m_BrotherhoodMemberList();
};

class CFairyPack:public CUE_Object
{
protected:
	CFairyPack(void);
	~CFairyPack(void);
public:
	static int get_DefaultSize();
	int GetFairyCount();
};

class CPlayerData:public CUE_Object
{
protected:
	CPlayerData(void);
	~CPlayerData(void);
public:
	CGuild * GuildInfo();
	BOOL IsAutoCombat();
	BOOL IsOpenAutoCombat();
	BOOL IsHaveTeam();
	BOOL PlayerIsTeamLeader();
	CTeam* get_TeamInfo();
	CItemPack *get_BackPack();
	CRelationList* get_FriendList();
	void AddTeamInviteIgnore(ULONGLONG uGuid);
	CBrotherhood *get_BrotherhoodInfo();
	CFairyPack *get_FairyPack();

};

class CActiveSceneLogic:public CUE_MonoBehaviour
{
protected:
	CActiveSceneLogic(void);
	~CActiveSceneLogic(void);
public:
	float get_CurFPS();
	CUE_Transform *get_CharRoot();
	CUE_GameObject *get_AirWallRoot();
};

class CTabButton  :public CUE_MonoBehaviour
{
public:
	void OnTabClick();
};

class CGameManager:public CUE_Object
{
protected:
	CGameManager(void);
	~CGameManager(void);
public:
	static BOOL get_LoadingScene();
	static CPlayerData *get_PlayerDataPool();
	static CActiveSceneLogic *get_CurActiveScene();
	static BOOL get_WaitForLoadAllBlock();
	static BOOL get_IsUseLoadingEffect();
	static void set_WaitForLoadAllBlock();
	static BOOL IsInGameScene();
	static int m_RunningScene();
	static float m_SavedCurValue();


};

class CCopySceneSettlementController:public CUE_MonoBehaviour
{
protected:
	CCopySceneSettlementController(void);
	~CCopySceneSettlementController(void);
public:
	static CCopySceneSettlementController * Instance();
	void OnClickTowerNext();
	void OnExitCopyScene();
};

class CUIProgressBar:public CUE_MonoBehaviour
{
protected:
	CUIProgressBar(void);
	~CUIProgressBar(void);
public:
	BOOL get_mIsDirty();
};


class CSkillProgressController:public CUE_MonoBehaviour
{
protected:
	CSkillProgressController(void);
	~CSkillProgressController(void);
public:
	static CSkillProgressController * Instance();
	CStdStringU getText();
	CUIProgressBar * get_UIProgressBar();
};

class CActivityHuoDongWindow:public CUE_MonoBehaviour
{
protected:
	CActivityHuoDongWindow(void);
	~CActivityHuoDongWindow(void);
public:
	static CActivityHuoDongWindow * Instance();
	static void OnClickExamDaily();
	static void OnClickGuildMission();
	static void OnClickBangHuaBtn();
	static void OnClickAsynPVP();
	static void OnClickBattleField();
	static void OnClickTower();
	static void OnClickExamKeju();
	CSYS_List *get_ActivityitemList();
	static void OnClickGoActivityBtnByActivityId(int iActivityID, BOOL bOpenUI);
	static BOOL CheckIsCanJion(int iActivityID);
	static int GetActivityId(int iActivityID);
	static CStdStringU GetActivityCountByActivityId(int iActivityID);
};

class CActivityHuoDongItem:public CUE_MonoBehaviour
{
protected:
	CActivityHuoDongItem(void);
	~CActivityHuoDongItem(void);
public:
	CStdStringU get_ActivityName();
	CStdStringU get_ActivityCountLabel();
	void	OnItemClick();
	int get_ActivityID();
};

class CReliveController:public CUE_MonoBehaviour
{
protected:
	CReliveController(void);
	~CReliveController(void);
public:
	static CReliveController * Instance();
	static void OnClickCityRelive();
	static void OnClickNearRelive();
	void OnClickEntry();
	void OnClickYuanBaoOriginal();
};

class CAsynPVPMatchWindow:public CUE_MonoBehaviour
{
protected:
	CAsynPVPMatchWindow(void);
	~CAsynPVPMatchWindow(void);
public:
	static CAsynPVPMatchWindow * Instance();
	CStdStringU get_ChallengeCount();
	CSYS_List *get_FightList();

};


class CAsynPVPItem:public CUE_MonoBehaviour
{
protected:
	CAsynPVPItem(void);
	~CAsynPVPItem(void);
public:
	void OnFightClick();
	CStdStringU get_CombatValue();
};

class CAsynPVPRewardLogic:public CUE_MonoBehaviour
{
protected:
	CAsynPVPRewardLogic(void);
	~CAsynPVPRewardLogic(void);
public:
	static CAsynPVPRewardLogic * Instance();
	void ChallengeOkCallBack();
	void ChallengeAgain();
};

class CBattleFieldSignupItem:public CUE_MonoBehaviour
{
protected:
	CBattleFieldSignupItem(void);
	~CBattleFieldSignupItem(void);
public:
	static CBattleFieldSignupItem * Instance();
	void OnClickSignup();
};


class CAutoSearchPointLogic:public CUE_MonoBehaviour
{
protected:
	CAutoSearchPointLogic(void);
	~CAutoSearchPointLogic(void);
public:
	CStdStringU get_LabelName();
	void OnTransmitPointClick();
};

class CSceneMapController:public CUE_MonoBehaviour
{
protected:
	CSceneMapController(void);
	~CSceneMapController(void);
public:
	static CSceneMapController * Instance();
	CStdStringU get_SceneNameLabel();
	void OnCloseWindow();
};

class CTeamMenuFast:public CUE_MonoBehaviour
{
protected:
	CTeamMenuFast(void);
	~CTeamMenuFast(void);
public:
	void OnClickKick();
};

class CTeamMemberUIInfo:public CUE_MonoBehaviour
{
protected:
	CTeamMemberUIInfo(void);
	~CTeamMemberUIInfo(void);
public:
	int MemberType();
	CStdStringU get_PlayerName();
	void OnClickInvite();
	void OnItemClick();
	BOOL GetCurSelLight();
	BOOL m_bIsHalfShow();
	BOOL buttonEnable();
};

class CTeamList:public CUE_MonoBehaviour
{
protected:
	CTeamList(void);
	~CTeamList(void);
public:
	
	static CTeamList* Instance();
	int		get_MemberCountInUI();
	void	OnCreateTeam();
	CStdStringU get_FollowLabel();
	void OnFollow();
	CTeamMenuFast* get_TeamMenuFast();
	CTeamMemberUIInfo* get_curSelectItem();
	CSYS_Array *m_TeamMemberUI();
};



class CTeamInvite:public CUE_MonoBehaviour
{
protected:
	CTeamInvite(void);
	~CTeamInvite(void);
public:
	static CTeamInvite* Instance();
	void OnClose();
	void ChangeInviteTab(int tab);
};

class CTeamFriendItem:public CUE_MonoBehaviour
{
protected:
	CTeamFriendItem(void);
	~CTeamFriendItem(void);
public:
	CStdString GetName();
	void OnInviteClick();
};

class CMessageBoxWithCheckBox:public CUE_MonoBehaviour
{
protected:
	CMessageBoxWithCheckBox(void);
	~CMessageBoxWithCheckBox(void);
public:
	static CMessageBoxWithCheckBox* Instance();
	void MessageBoxOK();
	void MessageBoxCancel();
	CUILabel *get_TextLabel();
	CStdStringU get_Content();
	static BOOL	IsTeamInviteBy(LPCSTR czName);

};


class CTeamController:public CUE_MonoBehaviour
{
protected:
	CTeamController(void);
	~CTeamController(void);
public:
	static CTeamController* Instance();
	void OnClose();
};


class CTeamTargetAdjust:public CUE_MonoBehaviour
{
protected:
	CTeamTargetAdjust(void);
	~CTeamTargetAdjust(void);
public:

	static CTeamTargetAdjust* Instance();
	CSYS_List *get_SubClassList();
	void OnOK();
};
class CTeamMenu:public CUE_MonoBehaviour
{
protected:
	CTeamMenu(void);
	~CTeamMenu(void);
public:
	void OnClickKickBtn();
};
class CTeamMemberItem:public CUE_MonoBehaviour
{
protected:
	CTeamMemberItem(void);
	~CTeamMemberItem(void);
public:
	CStdStringU get_PlayerName();
	void OnItemClick();
};

class CMyTeamController:public CUE_MonoBehaviour
{
protected:
	CMyTeamController(void);
	~CMyTeamController(void);
public:
	static CMyTeamController* Instance();
	void OnClickTeam();
	void onClickTarget();
	CStdStringU get_TargetLabel();
	void OnEnterSceneClick();
	CTeamMenu * get_Menu();
	CTeamMemberItem* get_curSelectItem();
	CStdStringU get_AutoTeamLabel();
	void OnHanHuaGuild();
	void OnHanHuaNomal();
	void OnHanHuaWorld();
	void OnHanHuaZhaomu();
	void StartAutoTeam();
};



class CTowerWindow:public CUE_MonoBehaviour
{
protected:
	CTowerWindow(void);
	~CTowerWindow(void);
public:
	static CTowerWindow * Instance();
	void OnClickTowerFight();
	void OnClickTowerSweep();
	CStdStringU get_LeftFightCount();
	CStdStringU get_LeftSweepCount();
	CUIButton *get_TowerSweepBtn();
	void OnClickClose();
};

class CUIStartWorkGiftController :public CUE_MonoBehaviour
{
protected:
	CUIStartWorkGiftController(void);
	~CUIStartWorkGiftController(void);
public:
	static CUIStartWorkGiftController * Instance();
	void OnStartDrawGiftClick();
};

class CUIWelfareQianDao  :public CUE_MonoBehaviour
{
protected:
	CUIWelfareQianDao(void);
	~CUIWelfareQianDao(void);
public:
	static CUIWelfareQianDao * Instance();
	void OnClickGetReWard();
};

class CCopySceneReady  :public CUE_MonoBehaviour
{
protected:
	CCopySceneReady(void);
	~CCopySceneReady(void);
public:
	static CCopySceneReady * Instance();
	void OnClickConfirm();
	static CSYS_Object* get_m_LastTeamGuids();
};

class CUICopySceneLowLevelTips  :public CUE_MonoBehaviour
{
protected:
	CUICopySceneLowLevelTips(void);
	~CUICopySceneLowLevelTips(void);
public:
	static CUICopySceneLowLevelTips * Instance();
	void OnConfirmBtnClick();
	void OnCheckBtnClick();
};


class CTabController  :public CUE_MonoBehaviour
{
protected:
	CTabController(void);
	~CTabController(void);
public:
	void DoChangeTab(CUE_Component *pTab);
	void ChangeTab(int iTab);
};

class CGameItem  :public CUE_Object
{
protected:
	CGameItem(void);
	~CGameItem(void);
public:
	CStdStringU GetName();
	CStdStringU GetTipsClassDesc();
	int GetColor();
	int GetEquipLevel();
	int GetQuality();
	BOOL IsCanEquip();
	BOOL IsEquipMent();
	BOOL IsCanInStall();
	BOOL IsEquiped();
	BOOL IsCanAutoOrOnceDecompose();
	BOOL CanSell();
	BOOL CanUse();

	CStdStringU GetEquipQualityStr();
	CStdStringU GetEquipQualityIcon();
	CStdStringU GetColorTextStr();
	int get_StackCount();
};

class CNumericKeyboardWindow  :public CUE_MonoBehaviour
{
protected:
	CNumericKeyboardWindow(void);
	~CNumericKeyboardWindow(void);
public:
	static CNumericKeyboardWindow * Instance();
	void OnClickSumbit();
	void OnMaxClick();
	void OnCloseUI();
};

class CItemTipsController  :public CUE_MonoBehaviour
{
protected:
	CItemTipsController(void);
	~CItemTipsController(void);
public:

	static CItemTipsController * Instance();
	CGameItem *m_SeletItem();
};

class CUISprite  :public CUE_MonoBehaviour
{
protected:
	CUISprite(void);
	~CUISprite(void);
public:
	CStdStringU mSpriteName();
	BOOL mFillCenter();
	BOOL mSpriteSet();
	CUISprite *mSprite();
	CUE_Transform *get_TransformUIRect();
};


class CKnapsackItem  :public CUE_MonoBehaviour
{
protected:
	CKnapsackItem(void);
	~CKnapsackItem(void);
public:
	void OnItemClick();
	CGameItem * GetGameItem();
	CStdStringU get_Count();
	CUISprite *m_QualityBg();
	CUISprite *m_Up();
	CUISprite *m_Disable();
	CUISprite *m_Lock();
	CStdStringU m_Level();
	int GetDataId();
};

class CStallMultiSellConfirm  :public CUE_MonoBehaviour
{
protected:
	CStallMultiSellConfirm(void);
	~CStallMultiSellConfirm(void);
public:
	static CStallMultiSellConfirm *Instance();
	int m_StepIdx();
	void OnInputCountOver(int iNum);
	void SellItem();
	void AddMoneyByStep();
	void MinusMoneyByStep();
	CKnapsackItem *m_Item();
	CSYS_List * m_LeftDataList();
	int m_NowMoney();
	void CloseWindow();
};


class CStallSingleSellConfirm  :public CUE_MonoBehaviour
{
protected:
	CStallSingleSellConfirm(void);
	~CStallSingleSellConfirm(void);
public:
	static CStallSingleSellConfirm *Instance();
	int m_StepCount();
	//void OnInputCountOver(int iNum);
	void SellItem();
	void AddMoneyByStep();
	void MinusMoneyByStep();
	CKnapsackItem *m_Item();

	int m_NowMoney();
	CStdStringU m_NumText();
	void CloseWindow();
};


class CKnapsackController  :public CUE_MonoBehaviour
{
protected:
	CKnapsackController(void);
	~CKnapsackController(void);
public:
	static CKnapsackController * Instance();
	void OnClose();
};

class CKnapsackWindow  :public CUE_MonoBehaviour
{
protected:
	CKnapsackWindow(void);
	~CKnapsackWindow(void);
public:
	static CKnapsackWindow * Instance();
	void OnClickNeaten();
	void Click_Item_BelongBackPack(CGameItem *pGameItem);
	void OnClickOpenDecompose();
	CSYS_List *get_KnapsackList();
	CSYS_List *m_FilterItemList();
	CSYS_List *filterItemList();
	CUE_GameObject *m_FilterList();
	int m_FilterType();
};	


class CFirmSell  :public CUE_MonoBehaviour
{
protected:
	CFirmSell(void);
	~CFirmSell(void);
public:
	static CFirmSell * Instance();
	void DoSellClick();
	void OnInputCountOver(int iNum);
	CGameItem * GetGameItem();
	CSYS_List *m_Items();
};

class CFirmBuy  :public CUE_MonoBehaviour
{
protected:
	CFirmBuy(void);
	~CFirmBuy(void);
public:
	static CFirmBuy * Instance();
	void ConfirmBuy();
	void OnInputCountOver(int iNum);
};

class CBrotherhoodPanelMy  :public CUE_MonoBehaviour
{
protected:
	CBrotherhoodPanelMy(void);
	~CBrotherhoodPanelMy(void);
public:
	static CBrotherhoodPanelMy * Instance();
	static int get_itemCount();
	void OnClickTeamup();
};

class CActivityRaidMenuItem  :public CUE_MonoBehaviour
{
protected:
	CActivityRaidMenuItem(void);
	~CActivityRaidMenuItem(void);
public:
	CStdStringU get_NorItemNameLabel();
	CStdStringU get_SelItemNameLabel();
	CSYS_List *get_SecondaryItemList();
	void ClickRaidMenuItem();
};	

class CActivityRaidWindow  :public CUE_MonoBehaviour
{
protected:
	CActivityRaidWindow(void);
	~CActivityRaidWindow(void);
public:
	static CActivityRaidWindow * Instance();
	CSYS_List *get_RaidMenuItemList();
	void OnEnterClick();
	CStdStringU get_ActivityNameLabel();
};

class CLeftInfoController  :public CUE_MonoBehaviour
{
protected:
	CLeftInfoController(void);
	~CLeftInfoController(void);
public:
	static CLeftInfoController * Instance();
	void OnTeamClick();
};

class CJoinTeamSubItem  :public CUE_MonoBehaviour
{
protected:
	CJoinTeamSubItem(void);
	~CJoinTeamSubItem(void);
public:
	CStdStringU get_secondNameLabel();
	CStdStringU get_NormalNameLabel();
	CStdStringU get_NameLabel();
	BOOL get_AutoTeam();
	void OnItemClick();
};

class CObj  :public CUE_MonoBehaviour
{
protected:
	CObj(void);
	~CObj(void);
public:
	CUE_Vector3 *get_Position();
	void set_Position(CUE_Vector3 *pVt3);
	BOOL IsNpc();
};

class CObj_Char  :public CObj
{
protected:
	CObj_Char(void);
	~CObj_Char(void);
public:
	CStdStringU get_RoleName();
	BOOL get_IsInCombat();
	BOOL get_IsMoving();
	CUE_Transform *get_HeadInfoTran();
	BOOL IsDie();
};


class CTargetWindow  :public CUE_MonoBehaviour
{
protected:
	CTargetWindow(void);
	~CTargetWindow(void);
public:
	CStdStringU get_HPLabel();
	CStdStringU get_NameLabel();
	CStdStringU get_LevelLabel();
	CStdStringU get_TarName();
	CSYS_List *get_BuffList();
	void UpdateTarget();
	void UpdateTargetSelected(CObj_Char *pNPC);
};


class CTargetFrameControllerNew  :public CUE_MonoBehaviour
{
protected:
	CTargetFrameControllerNew(void);
	~CTargetFrameControllerNew(void);
public:
	static CTargetFrameControllerNew * Instance();
	CTargetWindow *get_TargetBoss();
	CTargetWindow *get_TargetNormal();
};

class CUIJianMuXBSlot  :public CUE_MonoBehaviour
{
protected:
	CUIJianMuXBSlot(void);
	~CUIJianMuXBSlot(void);
public:
	BOOL get_BEnough();
	BOOL IsSelect();
	CStdStringU get_ItemName();
};

class CUIJianMuXBPanel  :public CUE_MonoBehaviour
{
protected:
	CUIJianMuXBPanel(void);
	~CUIJianMuXBPanel(void);
public:
	static CUIJianMuXBPanel * Instance();
	CStdStringU get_SelectName();
	CUIJianMuXBSlot * get_selectSlot();
	CUIJianMuXBSlot *get_CurSelectSlot();
	void OnClickFill();
	void OnClickReward();
	BOOL get_bCanGetReward();
	void OnSelectItem(int iItem);
	void OnClickClose();

};

class CStallMultiBuyConfirm  :public CUE_MonoBehaviour
{
protected:
	CStallMultiBuyConfirm(void);
	~CStallMultiBuyConfirm(void);
public:
	static CStallMultiBuyConfirm * Instance();
	void BuyItem();
	void OnInputCountOver(int iAmountOf);
	CStdStringU get_ItemName();
	int get_NowMonney();
	CSYS_List *get_ListCount();
	CSYS_List *get_ListPrice();
	CStdStringU get_NumText();
};

class CSystemShopWindow  :public CUE_MonoBehaviour
{
protected:
	CSystemShopWindow(void);
	~CSystemShopWindow(void);
public:
	static CSystemShopWindow * Instance();
	void Buy();
	void OnItemNumChoose(int iNumber);
	CStdStringU get_InputNumber();
	CSystemShopWindow * m_curShowPage();
	CStdStringU	LabelItemName();	
};

class CBuffInfo  :public CUE_Object
{
protected:
	CBuffInfo(void);
	~CBuffInfo(void);
public:
	BOOL get_DisableMove();
	BOOL get_DisableSkill();
	void set_DisableMove(BOOL bValue);
	void set_DisableSkill(BOOL bValue);
};

class CGuildConvoyFillPanel  :public CUE_MonoBehaviour
{
protected:
	CGuildConvoyFillPanel(void);
	~CGuildConvoyFillPanel(void);
public:
	static CGuildConvoyFillPanel * Instance();
	void OnClickConfirm();
	void OnClickRandom();
};


class CMissionTrack  :public CUE_MonoBehaviour
{
protected:
	CMissionTrack(void);
	~CMissionTrack(void);
public:
	static CMissionTrack * Instance();
	CSYS_List *get_MainAceptedList();
	CSYS_List *get_MainCompletedList();
	CSYS_List *m_ChuanQiAceptedList();
	CSYS_List *m_ChuanQiCompletedList();
	CSYS_List *m_BranchAceptedList();
	CSYS_List *m_BranchCompletedList();
	CSYS_List *m_SurpriseAceptedList();
	CSYS_List *m_SurpriseCompletedList();
	CSYS_List *m_CircleAceptedList();
	CSYS_List *m_CircleCompletedList();
	CSYS_List *m_NewGuideAceptedList();
	CSYS_List *m_NewGuideCompletedList();
	CSYS_List *m_QiYuAceptedList();
	CSYS_List *m_QiYuCompletedList();
	CSYS_List *m_ApprenticeAcceptedList();
	CSYS_List *m_ApprenticeCompletedList();
};

class CAchievementRecordItem  :public CUE_MonoBehaviour
{
protected:
	CAchievementRecordItem(void);
	~CAchievementRecordItem(void);
public:
	void OnClickGetReward();
};

class CAchievementRewardItem  :public CUE_MonoBehaviour
{
protected:
	CAchievementRewardItem(void);
	~CAchievementRewardItem(void);
public:
	void OnClickGetReward();
	BOOL get_bHaveReward();
};


class CNPCDialog  :public CUE_Object
{
protected:
	CNPCDialog(void);
	~CNPCDialog(void);
public:
	void ShowDialog();
	BOOL ShowMission();
	BOOL ShowOption();
};


class CNpcHeadInfoLogic  :public CUE_MonoBehaviour
{
protected:
	CNpcHeadInfoLogic(void);
	~CNpcHeadInfoLogic(void);
public:
	CStdStringU get_NameLabel();
	CStdStringU get_TitleLabel();
	BOOL IsShow();
	CObj_Char* get_NPC();
};

class CObj_NPC  :public CObj
{
protected:
	CObj_NPC(void);
	~CObj_NPC(void);
public:
	CStdStringU get_szNpcTitle();
	CNpcHeadInfoLogic *get_NpcHeadInfoLogic();
	BOOL get_IsBornCreate();
	int get_BelongTeamID();
	int get_OwnTeamId();
	int get_BelongObjID();
	CNPCDialog *m_Dialog();
	int get_NPCType();
	BOOL get_CanBeSeleByClient();
};

class CObj_MainPlayer  :public CObj
{
protected:
	CObj_MainPlayer(void);
	~CObj_MainPlayer(void);
public:
	void SwitchTarget();
	void MoveToTarget(CObj_Char *pObjChar/*Games.LogicObj.Obj_Char,System.Single*/);
	void LeaveTeamOk();
	int get_LastLevel();
	void AskLeaveTeamFollow();
	BOOL get_IsInTeamFollow();
	void set_SelectTarget(CObj_Char *pNPC);

	void ReqJoinTeam(ULONGLONG uGuid);
	void ReqChangeTeamLeader(ULONGLONG uGuid);
	void AddNewFriendGuid(ULONGLONG uGuid);
	void ReqAllowJoin(ULONGLONG uGuid);
	void ReqInviteTeam(ULONGLONG uGuid);
	void ReqInviteTeam(LPVOID list, int inviteType, int targetId );
	void StopMoveAndSync();

	static CSYS_List* get_AttackList();
};

class CObjManager  :public CSYS_Object
{
protected:
	CObjManager(void);
	~CObjManager(void);
public:
	static CObj_MainPlayer *get_MainPlayer();
};

class CPlayerHeadInfoLogic  :public CUE_MonoBehaviour
{
protected:
	CPlayerHeadInfoLogic(void);
	~CPlayerHeadInfoLogic(void);
public:
	CObj_MainPlayer* get_MainPlayer();
	CStdStringU get_NameLabel();
};

class CLimitActivityYLTXItem  :public CUE_MonoBehaviour
{
protected:
	CLimitActivityYLTXItem(void);
	~CLimitActivityYLTXItem(void);
public:
	CStdStringU m_NpcNumLabel();
	CStdStringU m_SceneLabel();
	void OnClick();
};

class CUIScrollExchangeController  :public CUE_MonoBehaviour
{
protected:
	CUIScrollExchangeController(void);
	~CUIScrollExchangeController(void);
public:
	static CUIScrollExchangeController* Instance();
	void OnClickCloseBtn();
};


class CLimitActivityYLTX  :public CUE_MonoBehaviour
{
protected:
	CLimitActivityYLTX(void);
	~CLimitActivityYLTX(void);
public:
	void OnClickSyncYLTXData();
};


class CLimitTimePushTipsController  :public CUE_MonoBehaviour
{
protected:
	CLimitTimePushTipsController(void);
	~CLimitTimePushTipsController(void);
public:
	static CSYS_List *get_ListYLTX();
	static CLimitTimePushTipsController* Instance();
	CLimitActivityYLTX *get_LimitActivityYLTX();
	void ShowYLTXWindow();
};


class CLimitTimePushTipsItem  :public CUE_MonoBehaviour
{
protected:
	CLimitTimePushTipsItem(void);
	~CLimitTimePushTipsItem(void);
public:
	CStdStringU get_ActivityName();
	CStdStringU get_Count();
	void OnClickGoBtn();
};


class CGuildThiefSettlementController  :public CUE_MonoBehaviour
{
protected:
	CGuildThiefSettlementController(void);
	~CGuildThiefSettlementController(void);
public:
	static CGuildThiefSettlementController * Instance();
	void OnClose();
};

class CUIActivityBuyback  :public CUE_MonoBehaviour
{
protected:
	CUIActivityBuyback(void);
	~CUIActivityBuyback(void);
public:
	static CUIActivityBuyback * Instance();
};

class CMisChooseLogic  :public CUE_MonoBehaviour
{
protected:
	CMisChooseLogic(void);
	~CMisChooseLogic(void);
public:
	static CMisChooseLogic * Instance();
	void ClickLeft();
};


class CTeamPlatformWindow  :public CUE_MonoBehaviour
{
protected:
	CTeamPlatformWindow(void);
	~CTeamPlatformWindow(void);
public:
	static CTeamPlatformWindow * Instance();

	CSYS_List* get_SubClassList();
	CJoinTeamSubItem* get_CurSelecItem();
	void OnAutoTeam();
	void OnAutoTeamClick();
};

class CGuildConvoyConfirm  :public CUE_MonoBehaviour
{
protected:
	CGuildConvoyConfirm(void);
	~CGuildConvoyConfirm(void);
public:
	static CGuildConvoyConfirm * Instance();
	void OnClickYes();
};

class CSmallMapItem  :public CUE_MonoBehaviour
{
protected:
	CSmallMapItem(void);
	~CSmallMapItem(void);
public:
	int m_nSceneId();
};


class CWorldMapController  :public CUE_MonoBehaviour
{
protected:
	CWorldMapController(void);
	~CWorldMapController(void);
public:
	static void SceneMapOpenMap();
	CSYS_List *m_SmallMapItemList();
	void OnMapItemBtnClick(CSmallMapItem *pItem);
	void OnCloseWindow();
	static CWorldMapController * Instance();
	
};

class CApplication  :public CUE_Object
{
protected:
	CApplication(void);
	~CApplication(void);
public:
	static void set_targetFrameRate(int iFrame);
};

class CUIBounty_BossItem  :public CUE_MonoBehaviour
{
protected:
	CUIBounty_BossItem(void);
	~CUIBounty_BossItem(void);
public:
	CStdStringU get_NameLabel();
	CStdStringU get_LevelLabel();
	void OnClick();
};

class CUIBounty_DetailInfo  :public CUE_MonoBehaviour
{
protected:
	CUIBounty_DetailInfo(void);
	~CUIBounty_DetailInfo(void);
public:
	CStdStringU get_PosLabel();
	void OnClick();
};

class CUIBounty_Main  :public CUE_MonoBehaviour
{
protected:
	CUIBounty_Main(void);
	~CUIBounty_Main(void);
public:
	static CUIBounty_Main * Instance();
	CSYS_List *get_UIBounty_DetailInfo();
	CSYS_List *get_UIBounty_BossItem();
	CStdStringU get_CombatValue();
	void OnClickClose();
};

//class CBuffInfo  :public CUE_Object
//{
//protected:
//	CBuffInfo(void);
//	~CBuffInfo(void);
//public:
//	BOOL get_IsDisableMove();
//	BOOL get_IsDisableSkill();
//};

class CPlayerImpactShowController  :public CUE_MonoBehaviour
{
protected:
	CPlayerImpactShowController(void);
	~CPlayerImpactShowController(void);
public:
	CBuffInfo* get_ImpactInfo();
};

class CChatLinkItem  :public CUE_MonoBehaviour
{
protected:
	CChatLinkItem(void);
	~CChatLinkItem(void);
public:
	void OnBtnClick();
};

class CChatInfoController  :public CUE_MonoBehaviour
{
protected:
	CChatInfoController(void);
	~CChatInfoController(void);
public:
	static CChatInfoController * Instance();
	void OnCloseClick();
};

class CQianKunDaiWindow  :public CUE_MonoBehaviour
{
protected:
	CQianKunDaiWindow(void);
	~CQianKunDaiWindow(void);
public:
	static CQianKunDaiWindow * Instance();
	CSYS_List *get_QianKunDaiStuff();
	CSYS_List *get_QianKunDaiFilter();
	void OnCombineClick();
	void OnBackItemClick(CGameItem *pGameItem);
	CGameItem *get_SuccessItem();
};

class CWorldBossController  :public CUE_MonoBehaviour
{
protected:
	CWorldBossController(void);
	~CWorldBossController(void);
public:
	static void OnGoBtClick();
};

//class CWorldBossController  :public CUE_MonoBehaviour
//{
//protected:
//	CWorldBossController(void);
//	~CWorldBossController(void);
//public:
//	static void OnGoBtClick();
//};

class CSocialRootController  :public CUE_MonoBehaviour
{
protected:
	CSocialRootController(void);
	~CSocialRootController(void);
public:
	static CSocialRootController * Instance();
	CTabController *get_TabController();
	void OnClickCloseWindow();
};


class CHomeRootController  :public CUE_MonoBehaviour
{
protected:
	CHomeRootController(void);
	~CHomeRootController(void);
public:
	static CHomeRootController * Instance();
	CTabController *get_TabController();
	static void OnOpenHomeGeo();
};

class CHomeGeoController  :public CUE_MonoBehaviour
{
protected:
	CHomeGeoController(void);
	~CHomeGeoController(void);
public:
	static CHomeGeoController * Instance();
	void OnClickCloseFortunePack();
	void OnClickOpenArchaeology();
};

class CHomeGeoFortuneEquipController  :public CUE_MonoBehaviour
{
protected:
	CHomeGeoFortuneEquipController(void);
	~CHomeGeoFortuneEquipController(void);
public:
	static CHomeGeoFortuneEquipController * Instance();
	void OnClickFortuneEquipGenrate10();
};



class CGuildBanghuaResultController  :public CUE_MonoBehaviour
{
protected:
	CGuildBanghuaResultController(void);
	~CGuildBanghuaResultController(void);
public:
	static CGuildBanghuaResultController * Instance();

	static void CloseWindow();
};

class CReadMailLogic  :public CUE_MonoBehaviour
{
protected:
	CReadMailLogic(void);
	~CReadMailLogic(void);
public:
	static CReadMailLogic * Instance();
	void DoDeleteAll();
	void OnClickExtractAll();
	BOOL IsAllMailsHaveItem();
};


class CActivenessBonusItem  :public CUE_MonoBehaviour
{
protected:
	CActivenessBonusItem(void);
	~CActivenessBonusItem(void);
public:
	BOOL get_IsCanReceived();
	void ClickItem();
};

class CYLTXRemainNpcData  :public CUE_Object
{
protected:
	CYLTXRemainNpcData(void);
	~CYLTXRemainNpcData(void);
public:
	int get_NpcPosId();
	int get_ObjId();
};

class CYLTXSceneData  :public CUE_Object
{
protected:
	CYLTXSceneData(void);
	~CYLTXSceneData(void);
public:
	int get_NpcNum();
	int get_SceneId();
};

class CMilitaryDonationWindow  :public CUE_MonoBehaviour
{
protected:
	CMilitaryDonationWindow(void);
	~CMilitaryDonationWindow(void);
public:
	static CMilitaryDonationWindow *Instance();
	void  OnClickDonate();
	void OnClickClose();
};

class CTowerSweepResult  :public CUE_MonoBehaviour
{
protected:
	CTowerSweepResult(void);
	~CTowerSweepResult(void);
public:
	static CTowerSweepResult *Instance();
	void OnClickClose();
};

class CDeviceStatusWindow  :public CUE_MonoBehaviour
{
protected:
	CDeviceStatusWindow(void);
	~CDeviceStatusWindow(void);
public:
	static CDeviceStatusWindow *Instance();
	int get_Hour();
	int get_Minute();
};

class COptionLogic  :public CUE_Object
{
protected:
	COptionLogic(void);
	~COptionLogic(void);
public:
	static void GuildConvoyFinish();
	static void GuildConvoyTransNext();
};

class CFuLiRootController  :public CUE_MonoBehaviour
{
public:
	static CFuLiRootController *Instance();
	void Close();
};

class CRoleViewWindow  :public CUE_MonoBehaviour
{
public:
	static CRoleViewWindow *Instance();
	void CloseWindow();
};



class CUIArchaeologyClue  :public CUE_MonoBehaviour
{
public:
	int GetNo();
	void OnClickItem();
};


class CUIArchaeologyPoint  :public CUE_MonoBehaviour
{
public:
	static CUIArchaeologyPoint *Instance();
	void OnClickAnalysisInfo();
	void OnClickArchaeology();
	void OnClickCollectClue();
	void OnClickSellClue();
	void OnCollectInfo();

};

class CMisInfoController  :public CUE_MonoBehaviour
{
public:
	static CMisInfoController *Instance();
	void CloseWindow();
};

class CFirstCharge  :public CUE_MonoBehaviour
{
public:
	static CFirstCharge *Instance();
	void CloseClick();
};
class CTeHuiRootController  :public CUE_MonoBehaviour
{
public:
	static CTeHuiRootController *Instance();
	void Close();
};

class CShoppingMallController  :public CUE_MonoBehaviour
{
public:
	static CShoppingMallController *Instance();
	void Close();
};

class CGrowWayViewLogic  :public CUE_MonoBehaviour
{
public:
	static CGrowWayViewLogic *Instance();
	void OnClickClose();
};

class CArtifactProveController  :public CUE_MonoBehaviour
{
public:
	static CArtifactProveController *Instance();
	void OnClickClose();
};

class CActivityRootLogic  :public CUE_MonoBehaviour
{
public:
	static CActivityRootLogic *Instance();
	void OnClickClose();
};

class CEquipBuildWindowController  :public CUE_MonoBehaviour
{
public:
	static CEquipBuildWindowController *Instance();
	void OnClose();
};

class CSkillRootController  :public CUE_MonoBehaviour
{
public:
	static CSkillRootController *Instance();
	void CloseWindow();
};

class CGuildController  :public CUE_MonoBehaviour
{
public:
	static CGuildController *Instance();
	void OnClose();
};

class CAchievementControl  :public CUE_MonoBehaviour
{
public:
	static CAchievementControl *Instance();
	void OnClose();
};

class CUIXiuZhenController  :public CUE_MonoBehaviour
{
public:
	static CUIXiuZhenController *Instance();
	void OnClickClose();
};

class CUIServant  :public CUE_MonoBehaviour
{
public:
	static CUIServant *Instance();
	void ClickCloseButton();
};

class CMentorRootController  :public CUE_MonoBehaviour
{
public:
	static CMentorRootController *Instance();
	void OnClickClose();
};

class CUIFairy  :public CUE_MonoBehaviour
{
public:
	static CUIFairy *Instance();
	void ClickCloseButton();
};

class CUIPetRoot  :public CUE_MonoBehaviour
{
public:
	static CUIPetRoot *Instance();
	void OnClickClose();
};

class CRankWindow  :public CUE_MonoBehaviour
{
public:
	static CRankWindow *Instance();
	void OnCloseClick();
};

class CTianshuRootController  :public CUE_MonoBehaviour
{
public:
	static CTianshuRootController *Instance();
	void Close();
};

class CExamController  :public CUE_MonoBehaviour
{
public:
	static CExamController *Instance();
	void OnClickCloseWindow();
};

class CPopManyCharMenu  :public CUE_MonoBehaviour
{
public:
	static CPopManyCharMenu *Instance();
	void CloseWindow();
};

class CDomainXuanZhanMap  :public CUE_MonoBehaviour
{
public:
	static CDomainXuanZhanMap *Instance();
	static void CloseWindow();
};

class CUIRect  :public CUE_MonoBehaviour
{
public:
	CUE_Transform *get_transform();

};

class CStallSell  :public CUE_MonoBehaviour
{
public:
	static CStallSell *Instance();
	CSYS_List *m_StallSellListItemList();
	CSYS_List *m_ItemPackList();
	void ConfirmSellItem(CGameItem *pItem);
};



#pragma endregion

