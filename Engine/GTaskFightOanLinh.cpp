#include "main.h"
#include "GTaskFightOanLinh.h"
#include "GSleep.h"

CGTaskFightOanLinh::CGTaskFightOanLinh() :CGoalComposite()
{
	LOG_WRITE("NEW - CGTaskFightOanLinh()");
}

CGTaskFightOanLinh::~CGTaskFightOanLinh()
{
	LOG_WRITE("DEL - CGTaskFightOanLinh()");
}

int CGTaskFightOanLinh::Process()
{
 
	int nSubGoalStatus = ProcessSubGoals();
	if (nSubGoalStatus != COMPLETED) return m_nStatus;
	LOG_WRITE("CGTaskFightOanLinh::Process()");
	if (!IsTask(u"Diệt Oán Linh Cản Trở") && !IsTask(u"Đánh bại Chúa Tể")) return Finished();
	ClickedSkillButton();
	return LoopNextSleep();
}


void CGTaskFightOanLinh::ClickedSkillButton()
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (!g_pGameControl->IsShowTransform(pBaseUIRoot)) return;
	CUE_Transform *pSkillBarRoot = pBaseUIRoot->GetChildByName(u"SkillBarRoot");
	if (!g_pGameControl->IsShowTransform(pSkillBarRoot)) return;
	CUE_Transform *pOtherBtn = pSkillBarRoot->GetChildByPath(u"SkillBar:Offset_New:OtherBtn");
	if (!g_pGameControl->IsShowTransform(pOtherBtn)) return;
	CUE_Transform *pListSkill = pOtherBtn->GetChildByPath(u"NormalSkill:Page01:Rotate01");
	if (!g_pGameControl->IsShowTransform(pListSkill)) return;
	int iAllChild = pListSkill->get_childCount();
	if (iAllChild <= 0) return;
		
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

void CGTaskFightOanLinh::CheckCDSkill( CUE_Transform *p )
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

void CGTaskFightOanLinh::ClickedNormalSkill()
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (!g_pGameControl->IsShowTransform(pBaseUIRoot)) return;
	CUE_Transform *pNormalSkil = pBaseUIRoot->GetChildByPath(u"SkillBarRoot:SkillBar:Offset_New:GeneralBtn:Skill00");
	if (!pNormalSkil) return;
	g_pGameControl->Tap(pNormalSkil);
}

BOOL CGTaskFightOanLinh::IsTask( CStdStringU czUNameTask )
{
	CUE_Transform *pBaseUIRoot = g_pGameControl->m_pBaseUIRoot;
	if (!g_pGameControl->IsShowTransform(pBaseUIRoot)) return FALSE;

	CUE_Transform *pLable0 = pBaseUIRoot->GetChildByPath(u"LeftInfoRoot:OffsetNew:Container:Offset:MissionTrack:Grid:0:Offest:Label0");
	if (!pLable0) return FALSE;
	CStdStringU czULabel = g_pGameControl->GetTextU(pLable0);
	if (czULabel.Compare(u"") == 0) return FALSE;
	if (czULabel.Find(czULabel) < 0) return FALSE;
	LOG_WRITE("CGTaskMainQuest::IsTask() ");
	return TRUE;
}

int CGTaskFightOanLinh::LoopNextSleep( int delay /*= 1000*/ )
{
	_theApp->NextTimer(delay);
	return LoopNext();
}
