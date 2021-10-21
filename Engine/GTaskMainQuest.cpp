#include "main.h"
#include "GTaskMainQuest.h"
#include "GSleep.h"
#include "GTaskFightOanLinh.h"


CGTaskMainQuest::CGTaskMainQuest() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskMainQuest()");	
	m_bCheckTeam = FALSE;
	m_bEquip = FALSE;
	m_iDelayClicked = -1;
	m_uTemp = 0;
	g_pGame->m_iCurrentID = 107;
}

CGTaskMainQuest::~CGTaskMainQuest()
{
	LOG_WRITE("DEL - CGTaskMainQuest()");
	g_pGame->m_iCurrentID = -1;
}

int CGTaskMainQuest::Process()
{
 
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;

	if (g_pGameControl->IsPickUpBtn()) g_pGameControl->GetExecPickBtn();
	if (IsTask(u"Đạt Lv")) return Finished();
	if (g_pGameControl->IsSetSceneUI()) return LoopNextSleep();
	if (IsMagicEraser()) {m_iDelayClicked = -1;return LoopNextSleep();}
	if (IsAnswer()) return LoopNextSleep();
	if (IsSynopsisselect()) return LoopNextSleep();
	if (IsMessageUIRoot()) return LoopNextSleep();
	if (IsFilterChoose()) return LoopNextSleep();
	if (IsPrompt_xinshouben()) return LoopNextSleep();
	if (IsStoryUIRoot()) {m_iDelayClicked = -1;return LoopNextSleep(500);}
	if (IsFriend()) return LoopNextSleep();
	//if (IsDeathUI()) return LoopNextSleep();
	if (g_pGameControl->IsReliveWnd()) return m_nStatus;
	if (g_pGameControl->IsButtonExitFuben()) processTask();
	if (IsTask(u"Diệt Oán Linh Cản Trở") || IsTask(u"Đánh bại Chúa Tể")) {
		AddSubGoal(new CGTaskFightOanLinh());
		return LoopNextSleep();
	}

	if (ProcessMainTask()) return LoopNextSleep();

	return m_nStatus;
}

int CGTaskMainQuest::ProcessMainTask()
{
	static CStdStringU czTemp;
	CUE_Transform *p = g_pGameControl->m_pBaseUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pQuestGrid = p->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid");
		CUE_Transform *pQuest0 = pQuestGrid->GetChildByName(u"0");
		if (pQuest0) {

			CUE_Transform *pLabel0 = pQuest0->GetChildByPath(u"Offest:Label0");
			CStdStringU czLabel = g_pGameControl->GetTextU(pLabel0);

			if (czTemp != czLabel) {
				czTemp = czLabel;
				g_pGameControl->MissionClicked(pQuest0);
			}
			
			if (g_pGameControl->IsMoving()) return LoopNextSleep();
			//if (g_pGameControl->AutoFightIsOn()) return LoopNextSleep();
			g_pGameControl->MissionClicked(pQuest0);

			/*m_iDelayClicked ++;
			if (m_iDelayClicked <= 0) g_pGameControl->MissionClicked(pQuest0);
			if (m_iDelayClicked >= 7) {m_iDelayClicked = -1;}
			LOG_WRITE("m_iDelayClicked = [%d]", m_iDelayClicked);*/
			return m_nStatus;
		}
	}

	g_pGameControl->CloseDialog();
	return m_nStatus;
}


BOOL CGTaskMainQuest::IsStoryUIRoot()
{
	CUE_Transform *p = g_pGameControl->m_pStoryUIRoot;
	if (g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pDialog = p->GetChildByName(u"synopsis.taskdialog");
		if (g_pGameControl->IsShowTransform(pDialog)) {




			/*CUE_Transform *pBtnNext = pDialog->GetChildByPath(u"Offset:dialogLarge:btn_next:btn_next");
			if (pBtnNext) g_pGameControl->Clicked(pBtnNext);*/
			g_pGameControl->CloseNPCTalk();
			return TRUE;
		}

		CUE_Transform *pSecneDialog = p->GetChildByName(u"synopsis.cutscenedialog");
		if (g_pGameControl->IsShowTransform(pSecneDialog)) {
			CUE_Transform *pSkipBtn = pSecneDialog->GetChildByPath(u"Offset:Top:SkikBtn");
			if (g_pGameControl->IsShowTransform(pSkipBtn)) {
				static int i = 0;
				if (i >= 3) {
					i = 0;
					g_pGameControl->Clicked(pSkipBtn->GetChildByName(u"Label"));
				}
				i ++;
				return LoopNextSleep();
			}
			else LOG_WRITE("Is Cut Scene Dialog..................");
			return TRUE;
		}

		CUE_Transform *pSynopsis = p->GetChildByName(u"Synopsis");
		if (g_pGameControl->IsShowTransform(pSynopsis)) {
			CUE_Transform *pSkipBtn = pSynopsis->GetChildByPath(u"Offset:dialogLarge:btn_next");
			if (g_pGameControl->IsShowTransform(pSkipBtn)) g_pGameControl->Tap(pSkipBtn);
			else LOG_WRITE("Is Cut Scene Dialog..................");
			return TRUE;
		}
	}
	return FALSE;
}

int CGTaskMainQuest::LoopNextSleep( int delay /*= 1000*/ )
{
	//AddSubGoal(new CGSleep(delay));
	_theApp->NextTimer(delay);
	return LoopNext();
}

BOOL CGTaskMainQuest::IsMessageUIRoot()
{
	CUE_Transform *p = g_pGameControl->m_pMessageUIRoot;
	if ( g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pSaveBattery = p->GetChildByName(u"mainbaseui.shengdian");
		if (g_pGameControl->IsBatterySaver()) return TRUE;
		if (g_pGameControl->IsMessageBox(u"Xác nhận chọn ngựa", ON)) return TRUE;
		if (g_pGameControl->IsMessageBox(u"Điểm đến tạm không thể tự tìm", OFF)) return TRUE;
		if (g_pGameControl->IsMessageBox(u"mời bạn vào đội,", OFF)) return LoopNextSleep();
		if (g_pGameControl->IsMessageBox(u"Thoát phó bản?", ON)) return LoopNextSleep();
		
		CUE_Transform *pNewbieGuide = p->GetChildByName(u"newbieguide");
		if (g_pGameControl->IsShowTransform(pNewbieGuide)) {
			CUE_Transform *pOffset = pNewbieGuide->GetChildByName(u"Offset");
			if (g_pGameControl->IsShowTransform(pOffset)) {
				LOG_WRITE("IsShowTransform(pNewbieGuide)");
				CNewGuideLogic *pInstance = CNewGuideLogic::Instance();
				if (pInstance) {
					int iGuidType = pInstance->get_GuideType();
					int iGuidStep = pInstance->get_GuideStep();

					if (iGuidType == 18 || iGuidType == 19) {
						if (iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:Yincang"));
						if (iGuidStep == 2) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:RightBottom:No.1:Grid_01:Dazao"));
						if (iGuidStep == 3) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"enhancement.enhancement_frame:Offset:List Of Top:Grid:tabGem"));
						if (iGuidStep == 4) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"enhancement.enhancement_frame:Offset:Gem_GemOperateView(Clone):Offset:View:EquipSlotView:Scroll View:Grid:Equipment(Clone)"));
						if (iGuidStep == 5 && iGuidType == 18) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"enhancement.enhancement_frame:Offset:Gem_GemOperateView(Clone):Offset:View:GemSlotView:GemListItem:Gem_GemSlotItem1"));
						if (iGuidStep == 5 && iGuidType == 19) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"enhancement.enhancement_frame:Offset:Gem_GemOperateView(Clone):Offset:View:GemSlotView:GemListItem:Gem_GemSlotItem2"));
						if (iGuidStep == 6) {
							CUE_Transform *pTable = g_pGameControl->m_pPopUIRoot->GetChildByPath(u"enhancement.enhancement_frame:Offset:Gem_GemOperateView(Clone):Offset:View:GemListView:Scroll View:Table");
							if (pTable) {
								int iAllChild = pTable->get_childCount();
								for (int i = 0; i < iAllChild; i++ ) {
									CUE_Transform *pChild = pTable->GetChild(i);
									if (g_pGameControl->IsShowTransform(pChild)) {
										CUE_Transform *pGrid = pChild->GetChildByPath(u"ExpandStateNew:offset:Grid");
										LOG_WRITE("0");
										int iAllChild1 = pGrid->get_childCount();
										for (int j = 0; j < iAllChild1; j++) {
											CUE_Transform *pChild1 = pGrid->GetChild(j);
											if (g_pGameControl->IsShowTransform(pChild1)) {
												LOG_WRITE("1");
												g_pGameControl->Clicked(pChild1);//:
												break;
											}
										}

										break;
									}
								}
							}

						}
						if (iGuidStep == 7) g_pGameControl->CloseDialog();
						iGuidType = 0;
						return TRUE;
					}


					if (iGuidType == 17 || iGuidType == 151) {
						if (iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:Yincang"));
						if (iGuidStep == 2) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:RightBottom:No.1:Grid_01:Dazao"));
						if (iGuidStep == 3) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"enhancement.enhancement_frame:Offset:Left:List_equipInBag:Grid:0"));
						if (iGuidStep == 4) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"enhancement.enhancement_frame:Offset:jinglian(Clone):Offset:operate:jinglian Button"));
						if (iGuidStep == 5) g_pGameControl->CloseDialog();
						iGuidType = 0;
						return TRUE;

					}

					if (iGuidType == 21) {
						if (iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:Yincang"));
						if (iGuidStep == 2) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:RightBottom:No.1:Grid_01:Jineng"));
						if (iGuidStep == 3) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"skillsystem.skillroot:Offset:TabContent:SkilInfoRoot(Clone):offset:SkillInfoLeft:RecommendButton"));
						if (iGuidStep == 4) g_pGameControl->Clicked(g_pGameControl->m_pMessageUIRoot->GetChildByPath(u"messageboxroot:Offset:Sprite:Buttons:03OKButton"));
						if (iGuidStep == 5) g_pGameControl->CloseDialog();
						iGuidType = 0;
						return TRUE;

					}

					if (iGuidType == 4 && iGuidStep == 1) {
						m_iDelayClicked = 1;
						processSecondQuest();
						return TRUE;

					}

					if (iGuidType == 171) {
						if (iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"jingjiexz.jingjiexzroot:ZhuanZhouOffset:juanzhou:Clip:Detail:BtnList:BtnList02"));
						if (iGuidStep == 2) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"jingjiexz.jingjiexzroot:JingjieXZInfoOffset:CenterInfo:SkillBtnList:Grid:Skill02"));
						if (iGuidStep == 3) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"jingjiexz.jingjiexzroot:JingjiePracticeInfoOffset:Button"));
						if (iGuidStep == 4) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"jingjiexz.jingjiexzroot:JingjiePracticeInfoOffset:CloseButton"));
						if (iGuidStep == 5) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"jingjiexz.jingjiexzroot:ZhuanZhouOffset:juanzhou:Clip:btn:CloseButton"));
						iGuidType = 0;
						return TRUE;
					} 

					if (iGuidType == 15 || iGuidType == 11) {
						if (iGuidStep <= 4) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"SkillBarRoot:SkillBar:Offset_New:GeneralBtn:JumpSwimNode:Jump"));

						return TRUE;
					}

					if ((iGuidType == 109 && iGuidStep == 1) || (iGuidType == 178 && iGuidStep == 2)) {
						IsPickUpBtn();
						return TRUE;
					}

					if (iGuidType == 39 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pMessageUIRoot->GetChildByPath(u"item.prompt:Offset:PromptButton"));
					if (iGuidType == 51 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pMessageUIRoot->GetChildByPath(u"prompt.prompt_xinshouben:Offset:PromptButton"));
					if (iGuidType == 64 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"SkillBarRoot:SkillBar:Offset_New:GeneralBtn:ChangeTarget"));
					if (iGuidType == 178 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"SkillBarRoot:SkillBar:Offset_New:GeneralBtn:ChangeTarget"));
					if (iGuidType == 169 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pMessageUIRoot->GetChildByPath(u"item.prompt:Offset:PromptButton"));
					if (iGuidType == 164 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pMessageUIRoot->GetChildByPath(u"mainbaseui.flyroot:Offset:Task:Task02"));
					if (iGuidType == 68 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pPopUIRoot->GetChildByPath(u"mainbaseui.selectstyle:bg:Panel:Grid:list"));
					if (iGuidType == 54 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"SkillBarRoot:SkillBar:Offset_New:GeneralBtn:Skill00"));
					if (iGuidType == 53 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"SkillBarRoot:SkillBar:Offset_New:OtherBtn:NormalSkill:Page01:Rotate01:Skill01"));
					if (iGuidType == 165 && iGuidStep == 1) g_pGameControl->Clicked(g_pGameControl->m_pMessageUIRoot->GetChildByPath(u"mainbaseui.flyroot:Offset:Btn_Get"));

					CStdString czString;
					czString.Format("NewGuideNode(%d_%d)",iGuidType, iGuidStep);
					//LOG_WRITE("iGuidType = [%d] iGuidStep [%d] - string [%s]", iGuidType, iGuidStep, czString.c_str());
					//CUE_Transform *pString =g_pGameControl->getTransformFromString(czString);
					//if (pString) LOG_WRITE("------------------>pTransform [%s]",_U2A(pString->GetPath()).c_str());
				}
			}	
		}
		
	}
	return FALSE;
}

BOOL CGTaskMainQuest::IsDeathUI()
{
	CUE_Transform *p = g_pGameControl->m_pDeathUIRoot->GetChildByName(u"DeathUIRoot:ReliveRoot");
	if ( g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pBtn = p->GetChildByPath(u"Offset:ButtonFrame:Sprite:Grid:ReliveRookieButton");
		g_pGameControl->Clicked(pBtn); //hoi sinh tan thu
		return TRUE;
	}
	return FALSE;
}

BOOL CGTaskMainQuest::IsMessageBox()
{
	CUE_Transform *p = g_pGameControl->m_pMessageUIRoot;
	if ( g_pGameControl->IsShowTransform(p)) {
		CUE_Transform *pMsgBox = p->GetChildByName(u"messageboxroot");
		if (g_pGameControl->IsShowTransform(pMsgBox)) {
			CUE_Transform *pContent = pMsgBox->GetChildByPath(u"Offset:Sprite:Content");
			if (pContent) {
				CStdStringU czUContent = g_pGameControl->GetTextU(pContent);
				if (czUContent.Find(u"Xác nhận chọn ngựa") >= 0) {
					g_pGameControl->Tap(pMsgBox->GetChildByPath(u"Offset:Sprite:Buttons:03OKButton"));
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void CGTaskMainQuest::ClickedSkillButton()
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (!g_pGameControl->IsShowTransform(pBaseUIRoot)) return;
	CUE_Transform *pSkillBarRoot = pBaseUIRoot->GetChildByName(u"SkillBarRoot");
	if (!g_pGameControl->IsShowTransform(pSkillBarRoot)) return;
	CUE_Transform *pOtherBtn = pSkillBarRoot->GetChildByPath(u"SkillBar:Offset_New:OtherBtn");
	if (!g_pGameControl->IsShowTransform(pOtherBtn)) return;
	CUE_Transform *pChangeSkill = pOtherBtn->GetChildByName(u"ChangeSkill");
	CUE_Transform *pListSkill = pOtherBtn->GetChildByPath(u"NormalSkill:Page01:Rotate01");
	if (!g_pGameControl->IsShowTransform(pListSkill)) return;
	int iAllChild = pListSkill->get_childCount();
	if (iAllChild <= 0) return;
	
	CheckCDSkill(pChangeSkill);
	CUE_Transform *pChild0 = pListSkill->GetChild(0);
	CheckCDSkill(pChild0);
	CUE_Transform *pChild1 = pListSkill->GetChild(1);
	CheckCDSkill(pChild1);
	CUE_Transform *pChild2 = pListSkill->GetChild(2);
	CheckCDSkill(pChild2);
	CUE_Transform *pChild3 = pListSkill->GetChild(3);
	CheckCDSkill(pChild3);
	ClickedNormalSkill();

}

void CGTaskMainQuest::CheckCDSkill( CUE_Transform *p )
{
	if (!p) return;
	CUE_Transform *pLock = p->GetChildByPath(u"SkillButton:Lock");
	if (!g_pGameControl->IsShowTransform(pLock)) {// co skill nay
		CUE_Transform *pCDText = p->GetChildByPath(u"SkillButton:CdText");
		if (pCDText) {
			CStdStringU czUText = g_pGameControl->GetTextU(pCDText);
			if (czUText.Compare(u"") == 0) {//khong co thoi gian cho hoi skill
				LOG_WRITE("Click Skill This");
				g_pGameControl->Tap(p);
				return;
			}
		}
	}
}

void CGTaskMainQuest::ClickedNormalSkill()
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (!g_pGameControl->IsShowTransform(pBaseUIRoot)) return;
	CUE_Transform *pNormalSkil = pBaseUIRoot->GetChildByPath(u"SkillBarRoot:SkillBar:Offset_New:GeneralBtn:Skill00");
	if (!pNormalSkil) return;
	g_pGameControl->Tap(pNormalSkil);
}

BOOL CGTaskMainQuest::IsTask( CStdStringU czUNameTask )
{ 
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (g_pGameControl->IsShowTransform(pBaseUIRoot)) {
		CUE_Transform *pLable0 = pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid:0:Offest:Label0");
		if (pLable0) {
			CStdStringU czULabel = g_pGameControl->GetTextU(pLable0);

			if (czULabel.Compare(u"") == 0) return FALSE;
			if (czULabel.Find(czUNameTask) >= 0) {
				CUE_Transform *pProcess0 = pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid:0:Offest:LabelProgress0");
				if (g_pGameControl->IsShowTransform(pProcess0)) {
					LOG_WRITE("CGTaskMainQuest::IsTask()");
					return TRUE;
				}
			}
		}

		CUE_Transform *pLable0Grid1 = pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid:1:Offest:Label0");
		if (pLable0) {
			CStdStringU czULabel = g_pGameControl->GetTextU(pLable0Grid1);

			if (czULabel.Compare(u"") == 0) return FALSE;
			if (czULabel.Find(czUNameTask) >= 0) {
				LOG_WRITE("CGTaskMainQuest::IsTask()");
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CGTaskMainQuest::IsMagicEraser()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"synopsis.synopsisshuxin");
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	CMiniGameBaseLogic *pMiniGameLogic = CMiniGameBaseLogic::Instance();
	if (!pMiniGameLogic) return FALSE;
	CMiniGameLogic_Erase *pEraser = (CMiniGameLogic_Erase*)pMiniGameLogic;
	if (!pEraser) return FALSE;

	LOG_WRITE("Auto Eraser");
	pEraser->AutoErase();
	pEraser->OnCloseBtnClick();
	return TRUE;
}

BOOL CGTaskMainQuest::IsItemPromptSkillLogic()
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (!pBaseUIRoot) return FALSE;
	LOG_WRITE("pBaseUIRoot");
	CUE_Transform *p = g_pGameControl->m_pMessageUIRoot;
	if (!p) return FALSE;
	LOG_WRITE("p");
	CUE_Transform *p1 = p->GetChildByName(u"prompt.prompt_xinshouben");
	if (!p1) return FALSE;
	LOG_WRITE("p1");
	CItemPromptSkillLogic *pInstance = CItemPromptSkillLogic::Instance();
	if (!pInstance) return FALSE;
	LOG_WRITE("IsItemPromptSkillLogic::OnPromptSkillBtnClick()");
	pInstance->OnPromptSkillBtnClick();
	return TRUE;
}

void CGTaskMainQuest::processSecondQuest()
{
	if (g_pGameControl->IsMoving()) return;
	//if (g_pGameControl->AutoFightIsOn()) return;
	g_pGameControl->MissionClicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid:1"));
	LoopNextSleep();
	/*static int i = -1;
	if (i <= 0) g_pGameControl->MissionClicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid:1"));
	if (i >= 5) i = -1;
	i++;*/
}

BOOL CGTaskMainQuest::IsFilterChoose()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"mainbaseui.selectstyle");
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	LOG_WRITE("SELECT FILTER");
	g_pGameControl->Clicked(p1->GetChildByPath(u"bg:btn_close"));
	return TRUE;
}

BOOL CGTaskMainQuest::IsPickUpBtn()
{
	CUE_Transform *p = g_pGameControl->m_pBaseUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"PickUpBtn");
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	LOG_WRITE("CGameControl::IsPickUpBtn............");
	LoopNextSleep(3000);
	g_pGameControl->GetExecPickBtn();
	return TRUE;
}

int CGTaskMainQuest::processTask()
{

	if (IsTask(u"Nghiên Cứu Võ") ||
		IsTask(u"Đánh bại Thiên") ||
		IsTask(u"Đẩy lui kẻ địch") ||
		IsTask(u"Đẩy lui Cửu Tử") ||
		IsTask(u"Hoa Tà Ác-")) {
			ClickedSkillButton();
			return LoopNextSleep();
	}

	if (IsTask(u"Tìm Thợ Rèn") ||
		IsTask(u"Đánh bại Thiết")) {
			if (ProcessMainTask()) return LoopNextSleep();
			return LoopNextSleep();
	}
	g_pGameControl->SwitchAutoFight(TRUE);
	if (g_pGameControl->IsMap(u"Tháp Quy Tông")) g_pGameControl->Clicked(g_pGameControl->m_pBaseUIRoot->GetChildByPath(u"FunctionButtonRoot:Offset:RightButtons:Especial_TopRightButtons:ExitCopyScene"));
	
	///if (g_pGameControl->AutoFightIsOn()) return LoopNextSleep(3000);
	return m_nStatus;
}

BOOL CGTaskMainQuest::IsPrompt_xinshouben()
{
	CUE_Transform *p = g_pGameControl->m_pMessageUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"prompt.prompt_xinshouben");
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	CUE_Transform *pBtn = p1->GetChildByPath(u"Offset:PromptButton");
	if (!g_pGameControl->IsShowTransform(pBtn)) return FALSE;
	LOG_WRITE("CLICKED PROMPT BUTTON");
	g_pGameControl->Clicked(pBtn);
	return TRUE;
}

BOOL CGTaskMainQuest::IsAnswer()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"synopsis.synopsisqa"); 
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	CUE_Transform *pBtn = p1->GetChildByPath(u"Offset:choice4:Grid:Answer1:Label");
	if (!pBtn) return FALSE;
	LOG_WRITE("Answerrrrrrrrrrrr");
	g_pGameControl->Clicked(pBtn);
	return TRUE;
}

BOOL CGTaskMainQuest::IsSynopsisselect()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"synopsis.synopsisselect"); 
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	CUE_Transform *pBtn = p1->GetChildByPath(u"Offset:Grid:SelectOneFrame:Label");
	if (!pBtn) return FALSE;
	LOG_WRITE("CGTaskMainQuest::IsSynopsisselect()");
	g_pGameControl->Clicked(pBtn);
	return TRUE;
}

BOOL CGTaskMainQuest::IsFriend()
{
	CUE_Transform *p = g_pGameControl->m_pPopUIRoot;
	if (!g_pGameControl->IsShowTransform(p)) return FALSE;
	CUE_Transform *p1 = p->GetChildByName(u"friends.popmanypeople"); 
	if (!g_pGameControl->IsShowTransform(p1)) return FALSE;
	CUE_Transform *pBtn = p1->GetChildByPath(u"Offset:Background:Grid:0");
	if (!pBtn) return FALSE;
	LOG_WRITE("CGTaskMainQuest::IsSynopsisselect()");
	g_pGameControl->Clicked(pBtn);
	return TRUE;
}
