#include "main.h"
#include "GameClasses.h"


#pragma region CGameClasses
CGameClasses::CGameClasses(void){}
CGameClasses::~CGameClasses(void){}	

CUIManager* CUIManager::Intance()
{
	//static CUIManager* m_Instance = NULL;
	//if(m_Instance) return m_Instance;
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIManager","Instance");
	if (!pfn) return NULL;
	return (CUIManager* )pfn->Invoke();
	//m_Instance = (CUIManager* )pfn->Invoke();
	//return m_Instance;
}
CUIRoot* CUIManager::get_UIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","uiRoot");
	if (!pField) return NULL;
	return (CUIRoot*)pField->GetValueObject();	
}
CUE_Transform* CUIManager::get_UIRootTrans()
{
	CUIRoot *pRoot = get_UIRoot();
	if(!pRoot) return NULL;
	return pRoot->get_Trans();
}
CUE_Transform* CUIManager::get_baseUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_baseUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);	
}
CUE_Transform* CUIManager::get_popUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_popUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);	
}

CUE_Transform* CUIManager::get_storyUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_storyUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CUE_Transform* CUIManager::get_tipUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_tipUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CUE_Transform* CUIManager::get_messageUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_messageUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CUE_Transform* CUIManager::get_deathUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_deathUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CUE_Transform* CUIManager::get_FloatUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_FloatUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CUE_Transform* CUIManager::get_storyMessageUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIManager","m_storyMessageUIRoot");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CUE_Transform* CUIManager::get_UICameraTransform(){
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIManager","get_UICameraTransform");
	if (!pfn) return NULL;
	return (CUE_Transform*)pfn->Invoke(this);	

}

BOOL CUIManager::IsPopUIShow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIManager","IsPopUIShow");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke();
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

void CUIManager::CloseAllPopUI( BOOL bChangeScene /*= FALSE*/, CSYS_Object *pObject /*= NULL*/ )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIManager","CloseAllPopUI");
	if (!pfn) return;
	void* agrs[] = {&bChangeScene, pObject};
	pfn->Invoke(this, agrs);
}

void CUIManager::CloseAllTipUI()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIManager","CloseAllTipUI");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIButton::CUIButton(void)
{

}

CUIButton::~CUIButton(void)
{

}

void CUIButton::OnClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIButton","OnClick");
	if (!pfn) return;
	pfn->Invoke(this);
	
}

BOOL CUIButton::get_isEnabled()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIButton","get_isEnabled");
	if (!pfn) return NULL;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CMissionItem::CMissionItem(void)
{

}

CMissionItem::~CMissionItem(void)
{

}

void CMissionItem::OnMisClick()
{	
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MissionItem","OnMisClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

int CMissionItem::get_misType()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionItem","m_misType");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

CStdStringU CMissionItem::get_NameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionItem","m_NameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CMissionItem::get_TypeLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionItem","m_TypeLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CMissionItem::get_CircleLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionItem","m_CircleLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}	

CUE_Display::CUE_Display(void):CSYS_Object(){};
CUE_Display::~CUE_Display(void){};

CUE_Display* CUE_Display::get_current()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Display","_mainDisplay");
	if (!pField) return NULL;
	return (CUE_Display*)pField->GetValueObject();
}

int CUE_Display::get_systemWidth()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Display","get_systemWidth");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();

}

int CUE_Display::get_systemHeight()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Display","get_systemHeight");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

int CUE_Display::get_renderingWidth()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Display","get_renderingWidth");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

int CUE_Display::get_renderingHeight()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Display","get_renderingHeight");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

CUE_Camera::CUE_Camera(void):CUE_Component(){};
CUE_Camera::~CUE_Camera(void){};
CUE_Camera* CUE_Camera::get_main()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Camera","get_main");
	if (!pfn) return NULL;
	return (CUE_Camera*)pfn->Invoke();
}

float CUE_Camera::get_orthographicSize()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Camera","get_orthographicSize");
	if (!pfn) return 1.0f;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return 1.0f;
	return pObj->GetFloat();
}
int CUE_Camera::get_pixelHeight()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Camera","get_pixelHeight");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

int CUE_Camera::get_pixelWidth()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Camera","get_pixelWidth");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}
CUIRoot::CUIRoot(void)
{

}

CUIRoot::~CUIRoot(void)
{

}

CUE_Transform * CUIRoot::get_Trans()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIRoot","mTrans");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CSYS_List * CUIRoot::get_ListUIRoot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIRoot","list");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject();
}

CUILabel::CUILabel(void)
{

}

CUILabel::~CUILabel(void)
{

}

CSYS_String* CUILabel::get_text()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UILabel","get_text");
	if (!pfn) return NULL;
	return (CSYS_String*)pfn->Invoke(this);	
}

CServerChooseWindow::CServerChooseWindow(void)
{

}

CServerChooseWindow::~CServerChooseWindow(void)
{

}

CServerChooseWindow* CServerChooseWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ServerChooseWindow","Instance");
	if (!pfn) return NULL;
	return (CServerChooseWindow*)pfn->Invoke();		
}

CStdString CServerChooseWindow::GetSelServerID()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ServerChooseWindow","labelSelServerID");
	if (!pField) return CStdString("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdString("");
	return CStdString(_U2A(pLabel->get_text()->GetText()).c_str());
}
int CServerChooseWindow::get_curSelectServer()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ServerChooseWindow","m_curSelectServer");
	if (!pField) return 0;
	CMonoObject* pValue = (CMonoObject*)pField->GetValueObject(this);
	return (int)pValue->GetUInt();
}


void CServerChooseWindow::OnClickChooseServer(){
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ServerChooseWindow","OnClickChooseServer");
	if (!pfn) return;
	pfn->Invoke(this);	
}

void CServerChooseWindow::OnClickEnterGame()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ServerChooseWindow","OnClickEnterGame");
	if (!pfn) return;
	pfn->Invoke(this);	
}

void CServerChooseWindow::SetSelectServer(int serverId){
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ServerChooseWindow","SetSelectServer");
	if (!pfn) return;
	void* agrs[] = {&serverId};
	pfn->Invoke(this,agrs);
}

CUIToggle* CServerChooseWindow::get_PrivacyToggle()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ServerChooseWindow","m_PrivacyToggle");
	if (!pField) return NULL;
	return (CUIToggle*)pField->GetValueObject(this);	
}

CServerListItem::CServerListItem(void)
{

}

CServerListItem::~CServerListItem(void)
{

}

void CServerListItem::OnClickItem()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ServerListItem","OnClickItem");
	if (!pfn) return;
	pfn->Invoke(this);
}

CRoleChooseWindow::CRoleChooseWindow(void)
{

}

CRoleChooseWindow::~CRoleChooseWindow(void)
{

}

CRoleChooseWindow* CRoleChooseWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleChooseWindow","Instance");
	if (!pfn) return NULL;
	return (CRoleChooseWindow*)pfn->Invoke();
}

void CRoleChooseWindow::OnEnterGameClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleChooseWindow","OnEnterGameClick");
	if (!pfn) return;
	pfn->Invoke(this);	
}

void CRoleChooseWindow::OnClickBack()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleChooseWindow","OnClickBack");
	if (!pfn) return;
	pfn->Invoke(this);	
}

int CRoleChooseWindow::m_curSelectItemIndex()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","RoleChooseWindow","m_curSelectItemIndex");
	if (!pField) return FALSE;
	int value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return value;
}

void CRoleChooseWindow::OnRoleSelectItemClick( CRoleSelectItem*  RoleSelectItem )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleChooseWindow","OnRoleSelectItemClick");
	if (!pfn) return;
	void* agrs[] = {RoleSelectItem};
	pfn->Invoke(this,agrs);
}

CPickUpBtnLogic::CPickUpBtnLogic( void )
{

}

CPickUpBtnLogic::~CPickUpBtnLogic( void )
{

}

CPickUpBtnLogic * CPickUpBtnLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PickUpBtnLogic","Instance");
	if (!pfn) return NULL;
	return (CPickUpBtnLogic*)pfn->Invoke();
}

void CPickUpBtnLogic::ExecPickBtn()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PickUpBtnLogic","ExecPickBtn");
	if (!pfn) return;
	pfn->Invoke(this);
}

BOOL CPickUpBtnLogic::GetPickBtnActive()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PickUpBtnLogic","GetPickBtnActive");
	if (!pfn) return NULL;
	CMonoObject* pObj = pfn->Invoke();
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CStdStringU CPickUpBtnLogic::m_Label()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PickUpBtnLogic","m_Label");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CDialogController::CDialogController( void )
{

}

CDialogController::~CDialogController( void )
{

}

CDialogController * CDialogController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DialogController","Instance");
	if (!pfn) return NULL;
	return (CDialogController*)pfn->Invoke();
}

void CDialogController::AidButtonClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DialogController","AidButtonClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CDialogController::OnClickCloseMis()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DialogController","OnClickCloseMis");
	if (!pfn) return;
	pfn->Invoke(this);
}

int CDialogController::get_DialogID()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DialogController","get_DialogID");
	if (!pfn) return NULL;
	CMonoObject* pObj = pfn->Invoke();
	if (!pObj) return FALSE;
	return (pObj->GetUInt());
}

void CDialogController::OnOpt_1()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DialogController","OnOpt_1");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CDialogController::OnClickMisButton0()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DialogController","OnClickMisButton0");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CDialogController::ClickEnterCopyScene()
{	
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DialogController","ClickEnterCopyScene");
	if (!pfn) return;
	pfn->Invoke(this);
}


CRoleSelectItem::CRoleSelectItem(void)
{

}

CRoleSelectItem::~CRoleSelectItem(void)
{

}

CUILabel* CRoleSelectItem::get_labelName()
{
	static CField* pField= NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","RoleSelectItem","labelName");
	if (!pField) return NULL;
	return (CUILabel*)pField->GetValueObject(this);		
}

CStdString CRoleSelectItem::get_roleName()
{
	CUILabel *pLabel = get_labelName();
	if(!pLabel)	return CStdString("");
	return CStdString(_U2A(pLabel->get_text()->GetText()));
}

void CRoleSelectItem::OnClickItem()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleSelectItem","OnClickItem");
	if (!pfn) return;
	pfn->Invoke(this);
}

CRoleSelectItem* CRoleSelectItem::GetRoleData()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleSelectItem","GetRoleData");
	if (!pfn) return NULL;
	return (CRoleSelectItem*)pfn->Invoke(this);
}



CMiniGameLogic_Erase::CMiniGameLogic_Erase( void )
{

}

CMiniGameLogic_Erase::~CMiniGameLogic_Erase( void )
{

}

void CMiniGameLogic_Erase::AutoErase()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MiniGameLogic_Erase","AutoErase");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CMiniGameLogic_Erase::OnCloseBtnClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MiniGameLogic_Erase","OnCloseBtnClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CShiJiaoSetting::CShiJiaoSetting( void )
{

}

CShiJiaoSetting::~CShiJiaoSetting( void )
{

}

void CShiJiaoSetting::Set3D()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ShiJiaoSetting","Set3D");
	if (!pfn) return;
	pfn->Invoke(this);
}

CMiniGameBaseLogic::CMiniGameBaseLogic( void )
{

}

CMiniGameBaseLogic::~CMiniGameBaseLogic( void )
{

}

CMiniGameBaseLogic * CMiniGameBaseLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MiniGameBaseLogic","Instance");
	if (!pfn) return NULL;
	return (CMiniGameBaseLogic*)pfn->Invoke();
}

CItemPromptSkillLogic::CItemPromptSkillLogic( void )
{

}

CItemPromptSkillLogic::~CItemPromptSkillLogic( void )
{

}

CItemPromptSkillLogic * CItemPromptSkillLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ItemPromptSkillLogic","Instance");
	if (!pfn) return NULL;
	return (CItemPromptSkillLogic*)pfn->Invoke();
}

void CItemPromptSkillLogic::OnPromptSkillBtnClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ItemPromptSkillLogic","OnPromptSkillBtnClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CGameSceneLogic::CGameSceneLogic( void )
{

}

CGameSceneLogic::~CGameSceneLogic( void )
{

}

CGameSceneLogic * CGameSceneLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameSceneLogic","Instance");
	if (!pfn) return NULL;
	return (CGameSceneLogic*)pfn->Invoke();
}

BOOL CGameSceneLogic::get_IsMovingToDoor()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameSceneLogic","get_IsMovingToDoor");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameSceneLogic::get_bIsTransDoor()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameSceneLogic","get_bIsTransDoor");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameSceneLogic::get_m_bInitUI()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","GameSceneLogic","m_bInitUI");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

BOOL CGameSceneLogic::get_bIsHideUI()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","GameSceneLogic","m_bIsHideUI");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

CNewGuideLogic::CNewGuideLogic( void )
{

}

CNewGuideLogic::~CNewGuideLogic( void )
{

}

CNewGuideLogic * CNewGuideLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NewGuideLogic","Instance");
	if (!pfn) return NULL;
	return (CNewGuideLogic*)pfn->Invoke();
}

int CNewGuideLogic::get_GuideType()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","NewGuideLogic","m_GuideType");
	if (!pField) return FALSE;
	int value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return value;
}

int CNewGuideLogic::get_GuideStep()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","NewGuideLogic","m_GuideStep");
	if (!pField) return FALSE;
	int value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return value;
}

CChatFrameController::CChatFrameController( void )
{

}

CChatFrameController::~CChatFrameController( void )
{

}

CChatFrameController * CChatFrameController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","Instance");
	if (!pfn) return NULL;
	return (CChatFrameController*)pfn->Invoke();
}

BOOL CChatFrameController::IsShow_ButtonAutoFight()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","m_nIsOpenClickAutoFightBtn");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}	

void CChatFrameController::OnClickAutoFight()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","OnClickAutoFight");
	if (!pfn) return;
	pfn->Invoke();
}

void CChatFrameController::OnClickStopAutoFight()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","OnClickStopAutoFight");
	if (!pfn) return;
	pfn->Invoke();
}

void CChatFrameController::OnClickOpenFriend()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","OnClickOpenFriend");
	if (!pfn) return;
	pfn->Invoke(this);
}

BOOL CChatFrameController::IsbHPEmpty()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","m_bHPEmpty");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetStaticValue(&value);
	return (value == 1);
}

BOOL CChatFrameController::IsbHPLack()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","m_bHPLack");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetStaticValue(&value);
	return (value == 1);
}

BOOL CChatFrameController::IsbMPEmpty()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","m_bMPEmpty");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetStaticValue(&value);
	return (value == 1);
}

BOOL CChatFrameController::IsbMPLack()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","m_bMPLack");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetStaticValue(&value);
	return (value == 1);
}

void CChatFrameController::OnChatInfoClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatFrameController","OnChatInfoClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CMessageBoxController::CMessageBoxController( void )
{

}

CMessageBoxController::~CMessageBoxController( void )
{

}

CMessageBoxController * CMessageBoxController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxController","Instance");
	if (!pfn) return NULL;
	return (CMessageBoxController*)pfn->Invoke();
}

CStdStringU CMessageBoxController::getText()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxController","m_TextLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CMessageBoxController::MessageBoxCancel()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxController","MessageBoxCancel");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CMessageBoxController::MessageBoxOK()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxController","MessageBoxOK");
	if (!pfn) return;
	pfn->Invoke(this);
}

CStoryPlayerController::CStoryPlayerController( void )
{

}

CStoryPlayerController::~CStoryPlayerController( void )
{

}

CStoryPlayerController * CStoryPlayerController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StoryPlayerController","Instance");
	if (!pfn) return NULL;
	return (CStoryPlayerController*)pfn->Invoke();
}

void CStoryPlayerController::ButtonNext()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StoryPlayerController","ButtonNext");
	if (!pfn) return;
	pfn->Invoke(this);
}

CRadarWindow::CRadarWindow( void )
{

}

CRadarWindow::~CRadarWindow( void )
{

}

CRadarWindow * CRadarWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RadarWindow","Instance");
	if (!pfn) return NULL;
	return (CRadarWindow*)pfn->Invoke();
}

CStdStringU CRadarWindow::getSceneName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","RadarWindow","LabelSceneName");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CRadarWindow::ShowSceneMap()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RadarWindow","ShowSceneMap");
	if (!pfn) return;
	pfn->Invoke(this);
}

CStdStringU CRadarWindow::labelLine()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","RadarWindow","labelLine");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CFunctionButtonController::CFunctionButtonController( void )
{
	
}

CFunctionButtonController::~CFunctionButtonController( void )
{

}

CFunctionButtonController * CFunctionButtonController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","Instance");
	if (!pfn) return NULL;
	return (CFunctionButtonController*)pfn->Invoke();
}

void CFunctionButtonController::OnFuLiClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnFuLiClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CFunctionButtonController::OnClickHuoDong()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickHuoDong");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CFunctionButtonController::OnClickDWBackHomeBtn()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickDWBackHomeBtn");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CFunctionButtonController::OnClickBackPack()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickBackPack");
	if (!pfn) return;
	pfn->Invoke(this);
}

BOOL CFunctionButtonController::isDaZaoRedDot()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","isDaZaoRedDot");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CFunctionButtonController::isSkillRedDot()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","isSkillRedDot");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CFunctionButtonController::IsNeedBagRedDot()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","IsNeedBagRedDot");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

void CFunctionButtonController::OnClickAchievement()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickAchievement");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CFunctionButtonController::OnCliskShowLimitTimePushActivityTips()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnCliskShowLimitTimePushActivityTips");
	if (!pfn)return;
	pfn->Invoke(this);
}

BOOL CFunctionButtonController::IsShow_ExitCopySceneButton()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","m_bShowExitCopySceneButton");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

void CFunctionButtonController::OnNewClickSetting()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnNewClickSetting");
	if (!pfn)return;
	pfn->Invoke(this);
}

CSYS_List * CFunctionButtonController::getList_YLTXRemainNPCData()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","m_YLTXRemainNpcDataList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CFunctionButtonController::OnClickImmortality()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickImmortality");
	if (!pfn)return;
	pfn->Invoke(this);
}

BOOL CFunctionButtonController::IsShowGrowWayBtn()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","IsShowGrowWayBtn");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

BOOL CFunctionButtonController::IsNeedImmortaityRedDot()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","IsNeedImmortaityRedDot");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

void CFunctionButtonController::OnClickGuildConvoyGo()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickGuildConvoyGo");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CFunctionButtonController::OnClickGuildConvoyCall()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickGuildConvoyCall");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CFunctionButtonController::OnClickHome()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnClickHome");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CFunctionButtonController::OnNewClickShop()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FunctionButtonController","OnNewClickShop");
	if (!pfn)return;
	pfn->Invoke(this);
}

CActivityHuoDongItem::CActivityHuoDongItem( void )
{

}

CActivityHuoDongItem::~CActivityHuoDongItem( void )
{

}

void CActivityHuoDongItem::OnItemClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongItem","OnItemClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CStdStringU CActivityHuoDongItem::get_ActivityName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongItem","m_ActivityNameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CActivityHuoDongItem::get_ActivityCountLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongItem","m_ActivityCountLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

int CActivityHuoDongItem::get_ActivityID()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongItem","m_nActivityId");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

CTransform::CTransform( void )
{

}

CTransform::~CTransform( void )
{

}

CUE_Transform * CTransform::Find(CStdStringU czU)
{	
	CSYS_String* sysStr = CSYS_String::CreateString(czU);
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod("UnityEngine.CoreModule", IMAGE_UNITY_ENGINE, "Transform", "Find");
	if (!pfn) return NULL;
	if (!sysStr) return NULL;
	void* args[] = {sysStr};
	return (CUE_Transform*)pfn->Invoke(this,args);
}

CUE_Vector3 * CTransform::get_position()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod("UnityEngine.CoreModule", IMAGE_UNITY_ENGINE, "Transform", "get_position");
	if (!pfn) return NULL;
	return (CUE_Vector3*)pfn->Invoke();
}

CPickItemProgressController::CPickItemProgressController( void )
{

}

CPickItemProgressController::~CPickItemProgressController( void )
{

}

CPickItemProgressController * CPickItemProgressController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PickItemProgressController","Instance");
	if (!pfn) return NULL;
	return (CPickItemProgressController*)pfn->Invoke();
}

BOOL CPickItemProgressController::IsRunning()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PickItemProgressController","IsRunning");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CStdStringU CPickItemProgressController::m_OptDecLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PickItemProgressController","m_OptDecLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CPickItemProgressController::CloseProgress()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PickItemProgressController","CloseProgress");
	if (!pfn)return;
	pfn->Invoke(this);
}

CGameManager::CGameManager( void )
{

}

CGameManager::~CGameManager( void )
{

}

BOOL CGameManager::get_LoadingScene()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameManager","get_LoadingScene");
	if (!pfn) return NULL;
	CMonoObject* pObj = pfn->Invoke();
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CPlayerData * CGameManager::get_PlayerDataPool()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameManager","get_PlayerDataPool");
	if (!pfn) return NULL;
	return (CPlayerData*)pfn->Invoke();
}

CActiveSceneLogic * CGameManager::get_CurActiveScene()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameManager","get_CurActiveScene");
	if (!pfn) return NULL;
	return (CActiveSceneLogic*)pfn->Invoke();
}

BOOL CGameManager::get_WaitForLoadAllBlock()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameManager","get_WaitForLoadAllBlock");
	if (!pfn) return NULL;
	CMonoObject* pObj = pfn->Invoke();
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameManager::get_IsUseLoadingEffect()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameManager","get_IsUseLoadingEffect");
	if (!pfn) return NULL;
	CMonoObject* pObj = pfn->Invoke();
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameManager::IsInGameScene()
{	
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameManager","IsInGameScene");
	if (!pfn) return NULL;
	CMonoObject* pObj = pfn->Invoke();
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

int CGameManager::m_RunningScene()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","GameManager","m_RunningScene");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject();
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

void CGameManager::set_WaitForLoadAllBlock()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GameManager","set_WaitForLoadAllBlock");
	if (!pfn) return;
	BOOL bValue = FALSE;
	void* agrs[] = {&bValue};
	pfn->Invoke(NULL, agrs);
}

float CGameManager::m_SavedCurValue()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","CopySceneProgress","m_SavedCurValue");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject();
	if(!pValue) return -1;
	return (float)pValue->GetFloat();
}

CCopySceneSettlementController::CCopySceneSettlementController( void )
{
	
}

CCopySceneSettlementController::~CCopySceneSettlementController( void )
{

}

CCopySceneSettlementController * CCopySceneSettlementController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","CopySceneSettlementController","Instance");
	if (!pfn) return NULL;
	return (CCopySceneSettlementController*)pfn->Invoke();
}

void CCopySceneSettlementController::OnClickTowerNext()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","CopySceneSettlementController","OnClickTowerNext");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CCopySceneSettlementController::OnExitCopyScene()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","CopySceneSettlementController","OnExitCopyScene");
	if (!pfn)return;
	pfn->Invoke(this);
}

CSkillProgressController::CSkillProgressController( void )
{

}

CSkillProgressController::~CSkillProgressController( void )
{

}

CSkillProgressController * CSkillProgressController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SkillProgressController","Instance");
	if (!pfn) return NULL;
	return (CSkillProgressController*)pfn->Invoke();
}

CStdStringU CSkillProgressController::getText()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SkillProgressController","m_TextLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CUIProgressBar * CSkillProgressController::get_UIProgressBar()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SkillProgressController","m_Progress");
	if (!pField) return NULL;
	return (CUIProgressBar*)pField->GetValueObject(this);
	
}


CUIProgressBar::CUIProgressBar( void )
{

}

CUIProgressBar::~CUIProgressBar( void )
{

}


BOOL CUIProgressBar::get_mIsDirty()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIProgressBar","mIsDirty");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

CActivityHuoDongWindow::CActivityHuoDongWindow( void )
{

}

CActivityHuoDongWindow::~CActivityHuoDongWindow( void )
{

}

CActivityHuoDongWindow * CActivityHuoDongWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","Instance");
	if (!pfn) return NULL;
	return (CActivityHuoDongWindow*)pfn->Invoke();
}

void CActivityHuoDongWindow::OnClickExamDaily()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickExamDaily");
	if (!pfn) return;
	pfn->Invoke();
}

void CActivityHuoDongWindow::OnClickGuildMission()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickGuildMission");
	if (!pfn) return;
	pfn->Invoke();
}

void CActivityHuoDongWindow::OnClickBangHuaBtn()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickBangHuaBtn");
	if (!pfn) return;
	pfn->Invoke();
}

void CActivityHuoDongWindow::OnClickAsynPVP()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickAsynPVP");
	if (!pfn) return;
	pfn->Invoke();
}

void CActivityHuoDongWindow::OnClickBattleField()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickBattleField");
	if (!pfn) return;
	pfn->Invoke();
}

void CActivityHuoDongWindow::OnClickTower()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickTower");
	if (!pfn) return;
	pfn->Invoke();
}

CSYS_List * CActivityHuoDongWindow::get_ActivityitemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","m_ActivityHuoDongItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CActivityHuoDongWindow::OnClickGoActivityBtnByActivityId( int iActivityID, BOOL bOpenUI )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickGoActivityBtnByActivityId");
	if (!pfn) return;
	BOOL bValue = FALSE;
	void* agrs[] = {&iActivityID, &bOpenUI, &bValue};
	pfn->Invoke(NULL, agrs);

}

BOOL CActivityHuoDongWindow::CheckIsCanJion( int iActivityID )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","CheckIsCanJion");
	if (!pfn) return NULL;
	void* agrs[] = {&iActivityID}; 
	CMonoObject* pObj = pfn->Invoke(NULL, agrs);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

int CActivityHuoDongWindow::GetActivityId( int iActivityID )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","GetActivityId");
	if (!pfn)return 0;void* agrs[] = {&iActivityID}; 
	CMonoObject* pObj = pfn->Invoke(NULL, agrs);
	return (int)pObj->GetUInt();
}

void CActivityHuoDongWindow::OnClickExamKeju()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","OnClickExamKeju");
	if (!pfn) return;
	pfn->Invoke();
}

CStdStringU CActivityHuoDongWindow::GetActivityCountByActivityId( int iActivityID )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityHuoDongWindow","GetActivityCountByActivityId");
	if (!pfn) return u"";
	void* agrs[] = {&iActivityID};
	CSYS_String* pstr = (CSYS_String*)pfn->Invoke(NULL, agrs);
	return (CStdStringU)pstr->GetText();
}

CTeam::CTeam( void )
{

}

CTeam::~CTeam( void )
{

}

int CTeam::GetTeamMemberCount()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Team","GetTeamMemberCount");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

BOOL CTeam::IsFull()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Team","IsFull");
	if (!pfn)return 0;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

int CTeam::get_TeamID()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Team","get_TeamID");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

int CTeam::get_TargetID()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Team","get_TargetId()");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

CTeamMember * CTeam::GetTeamMember( int iMember )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->FindMethod(IMAGE_ASSEMBLY_CSHARP,"","Team","GetTeamMember(System.Int32)");
	if (!pfn) { LOG_WRITE("!pfn"); return NULL;}
	void* agrs[] = {&iMember};
	return (CTeamMember*)pfn->Invoke(this ,agrs);
}

CTeamMember * CTeam::GetTeamMember( ULONGLONG uGuild )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->FindMethod(IMAGE_ASSEMBLY_CSHARP,"","Team","GetTeamMember(System.UInt64)");
	if (!pfn) { LOG_WRITE("!pfn"); return NULL;}
	void* agrs[] = {&uGuild};
	return (CTeamMember*)pfn->Invoke(this ,agrs);
}

CGuild::CGuild( void )
{

}

CGuild::~CGuild( void )
{

}

CStdStringU CGuild::get_GuildName()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Guild","get_GuildName");
	if (!pfn) return u"";
	CSYS_String* pstr = (CSYS_String*)pfn->Invoke(this);
	return (CStdStringU)pstr->GetText();

}

BOOL CGuild::get_IsInGroup()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Guild","get_IsInGroup");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

int CGuild::get_GuildSceneID()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Guild","get_GuildSceneID");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

CPlayerData::CPlayerData( void )
{

}

CPlayerData::~CPlayerData( void )
{

}

CGuild * CPlayerData::GuildInfo()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","m_GuildInfo");
	if (!pField) return NULL;
	return (CGuild*)pField->GetValueObject(this);
}

BOOL CPlayerData::IsAutoCombat()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","m_bAutoComabat");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

BOOL CPlayerData::IsHaveTeam()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","IsHaveTeam");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CPlayerData::PlayerIsTeamLeader()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","PlayerIsTeamLeader");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CTeam* CPlayerData::get_TeamInfo()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","get_TeamInfo");
	if (!pfn) return FALSE;
	return (CTeam*)pfn->Invoke(this);
}

BOOL CPlayerData::IsOpenAutoCombat()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","m_IsOpenAutoCombat");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

CItemPack * CPlayerData::get_BackPack()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","get_BackPack");
	if (!pfn) return FALSE;
	return (CItemPack*)pfn->Invoke(this);
}

CRelationList * CPlayerData::get_FriendList()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","get_FriendList");
	if (!pfn) return FALSE;
	return (CRelationList*)pfn->Invoke(this);
}

void CPlayerData::AddTeamInviteIgnore( ULONGLONG uGuid )
{
	LOG_WRITE("AddTeamInviteIgnore......");
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","AddTeamInviteIgnore");
	if (!pfn)return;
	void* agrs[] = {&uGuid};
	pfn->Invoke(this, agrs);
}

CBrotherhood * CPlayerData::get_BrotherhoodInfo()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","get_BrotherhoodInfo");
	if (!pfn) return NULL;
	return (CBrotherhood*)pfn->Invoke(this);
}

CFairyPack * CPlayerData::get_FairyPack()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PlayerData","get_FairyPack");
	if (!pfn) return NULL;
	return (CFairyPack*)pfn->Invoke(this);
}

CReliveController::CReliveController( void )
{

}

CReliveController::~CReliveController( void )
{

}

CReliveController * CReliveController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReliveController","Instance");
	if (!pfn) return NULL;
	return (CReliveController*)pfn->Invoke();
}

void CReliveController::OnClickCityRelive()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReliveController","OnClickCityRelive");
	if (!pfn) return;
	pfn->Invoke();
}

void CReliveController::OnClickNearRelive()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReliveController","OnClickNearRelive");
	if (!pfn) return;
	pfn->Invoke();
}

void CReliveController::OnClickEntry()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReliveController","OnClickEntry");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CReliveController::OnClickYuanBaoOriginal()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReliveController","OnClickYuanBaoOriginal");
	if (!pfn) return;
	pfn->Invoke(this);
}

CAsynPVPItem::CAsynPVPItem( void )
{

}

CAsynPVPItem::~CAsynPVPItem( void )
{

}

void CAsynPVPItem::OnFightClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPItem","OnFightClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CStdStringU CAsynPVPItem::get_CombatValue()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPItem","LabelCombat");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}



CAsynPVPRewardLogic::CAsynPVPRewardLogic( void )
{

}

CAsynPVPRewardLogic::~CAsynPVPRewardLogic( void )
{

}

CAsynPVPRewardLogic * CAsynPVPRewardLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPRewardLogic","Instance");
	if (!pfn) return NULL;
	return (CAsynPVPRewardLogic *)pfn->Invoke();
}

void CAsynPVPRewardLogic::ChallengeOkCallBack()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPRewardLogic","ChallengeOkCallBack");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CAsynPVPRewardLogic::ChallengeAgain()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPRewardLogic","ChallengeAgain");
	if (!pfn) return;
	pfn->Invoke(this);
}

CAsynPVPMatchWindow::CAsynPVPMatchWindow( void )
{

}

CAsynPVPMatchWindow::~CAsynPVPMatchWindow( void )
{

}

CAsynPVPMatchWindow * CAsynPVPMatchWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPMatchWindow","Instance");
	if (!pfn) return NULL;
	return (CAsynPVPMatchWindow *)pfn->Invoke();
}

CStdStringU CAsynPVPMatchWindow::get_ChallengeCount()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPMatchWindow","m_ChallengeCount");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CSYS_List * CAsynPVPMatchWindow::get_FightList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","AsynPVPMatchWindow","OpList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CBattleFieldSignupItem::CBattleFieldSignupItem( void )
{

}

CBattleFieldSignupItem::~CBattleFieldSignupItem( void )
{

}

CBattleFieldSignupItem * CBattleFieldSignupItem::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BattleFieldSignupItem","Instance");
	if (!pfn) return NULL;
	return (CBattleFieldSignupItem *)pfn->Invoke();
}

void CBattleFieldSignupItem::OnClickSignup()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BattleFieldSignupItem","OnClickSignup");
	if (!pfn) return;
	pfn->Invoke(this);
}

CTeamList::CTeamList(void)
{

}
CTeamList::~CTeamList( void )
{

}
CTeamList* CTeamList::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamList","Instance");
	if (!pfn)return NULL;
	return (CTeamList*)pfn->Invoke();	
}

int CTeamList::get_MemberCountInUI()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamList","get_MemberCountInUI");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

void CTeamList::OnCreateTeam()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamList","OnCreateTeam");
	if (!pfn)return;
	//neu team da co, -> open TeamController
	pfn->Invoke(this);	
}

CStdStringU CTeamList::get_FollowLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamList","m_FollowLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CTeamList::OnFollow()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamList","OnFollow");
	if (!pfn)return;
	pfn->Invoke(this);	
}

CTeamMenuFast* CTeamList::get_TeamMenuFast()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamList","m_TeamMenuFast");
	if (!pField) return NULL;
	return (CTeamMenuFast*)pField->GetValueObject(this);
}

CTeamMemberUIInfo* CTeamList::get_curSelectItem()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamList","m_curSelectItem");
	if (!pField) return NULL;
	return (CTeamMemberUIInfo*)pField->GetValueObject(this);
}

CSYS_Array * CTeamList::m_TeamMemberUI()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamList","m_TeamMemberUI");
	if (!pField) return NULL;
	return (CSYS_Array *)pField->GetValueObject(this);
}

CTeamMemberUIInfo::CTeamMemberUIInfo(void)
{

}

CTeamMemberUIInfo::~CTeamMemberUIInfo(void)
{

}

int CTeamMemberUIInfo::MemberType()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberUIInfo","MemberType");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

CStdStringU CTeamMemberUIInfo::get_PlayerName()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberUIInfo","get_PlayerName");
	if (!pfn)return CStdStringU(u"");
	CSYS_String *pStr = (CSYS_String *)pfn->Invoke(this);
	return CStdStringU(pStr->GetText());
}

void CTeamMemberUIInfo::OnClickInvite()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberUIInfo","OnClickInvite");
	if (!pfn)	return;
	pfn->Invoke(this);
}

void CTeamMemberUIInfo::OnItemClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberUIInfo","OnItemClick");
	if (!pfn)	return;
	pfn->Invoke(this);
}
BOOL CTeamMemberUIInfo::GetCurSelLight()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberUIInfo","GetCurSelLight");
	if (!pfn)	return FALSE;
	CMonoObject *pObj = pfn->Invoke(this);
	if(!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CTeamMemberUIInfo::m_bIsHalfShow()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberUIInfo","m_bIsHalfShow");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

BOOL CTeamMemberUIInfo::buttonEnable()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberUIInfo","GetCurSelLight");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}	

CTeamFriendItem::CTeamFriendItem(void)
{

}

CTeamFriendItem::~CTeamFriendItem(void)
{

}
CStdString CTeamFriendItem::GetName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamFriendItem","LabelName");
	if (!pField) return CStdString("");
	CUILabel *pLabel = (CUILabel *)pField->GetValueObject(this);
	if(!pLabel)return CStdString("");
	return CStdString(_U2A(pLabel->get_text()->GetText()).c_str());
}

void CTeamFriendItem::OnInviteClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamFriendItem","OnInviteClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTeamInvite* CTeamInvite::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamInvite","Instance");
	if (!pfn)return NULL;
	return (CTeamInvite*)pfn->Invoke();
}

void CTeamInvite::OnClose()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamInvite","OnClose");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CTeamInvite::ChangeInviteTab(int tab)
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamInvite","ChangeInviteTab");
	if (!pfn)return;
	void *agrs[] = {&tab};
	pfn->Invoke(this,agrs);
}

CMessageBoxWithCheckBox::CMessageBoxWithCheckBox(void)
{
	
}

CMessageBoxWithCheckBox::~CMessageBoxWithCheckBox(void)
{

}

CMessageBoxWithCheckBox* CMessageBoxWithCheckBox::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxWithCheckBox","Instance");
	if (!pfn)return NULL;
	return (CMessageBoxWithCheckBox*)pfn->Invoke();
}

void CMessageBoxWithCheckBox::MessageBoxOK()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxWithCheckBox","MessageBoxOK");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CMessageBoxWithCheckBox::MessageBoxCancel()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxWithCheckBox","MessageBoxCancel");
	if (!pfn)return;
	pfn->Invoke(this);
}

CUILabel * CMessageBoxWithCheckBox::get_TextLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxWithCheckBox","m_TextLabel");
	if (!pField) return NULL;
	return (CUILabel *)pField->GetValueObject(this);
}

BOOL CMessageBoxWithCheckBox::IsTeamInviteBy(LPCSTR czName)
{
	CMessageBoxWithCheckBox *pInstance = Instance();
	if(!pInstance) return FALSE;
	CUILabel *pLabel = pInstance->get_TextLabel();
	if(!pLabel) return FALSE;
	LOG_WRITE("[%s] IsTeamInviteBy",czName);
 	CStdStringU czText(pLabel->get_text()->GetText());
	if(czText.Find(u"mời bạn vào đội") > 0){
		CStdString czTextA(_U2A(czText.c_str()));
		if(czTextA.Find(czName) > 0) return TRUE;
	}
	return FALSE;
}

CStdStringU CMessageBoxWithCheckBox::get_Content()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MessageBoxWithCheckBox","m_TextLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CMyTeamController::CMyTeamController(void)
{

}

CMyTeamController::~CMyTeamController(void)
{

}

CMyTeamController* CMyTeamController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","Instance");
	if (!pfn)return NULL;
	return (CMyTeamController*)pfn->Invoke();
}

void CMyTeamController::OnClickTeam()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","OnClickTeam");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CMyTeamController::onClickTarget()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","onClickTarget");
	if (!pfn)return;
	pfn->Invoke(this);
}

CStdStringU CMyTeamController::get_TargetLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","m_TargetLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CMyTeamController::OnEnterSceneClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","OnEnterSceneClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTeamMenu* CMyTeamController::get_Menu()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","m_Menu");
	if (!pField) return NULL;
	return (CTeamMenu*)pField->GetValueObject(this);
}

CTeamMemberItem* CMyTeamController::get_curSelectItem()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","m_curSelectItem");
	if (!pField) return NULL;
	return (CTeamMemberItem*)pField->GetValueObject(this);
}

CStdStringU CMyTeamController::get_AutoTeamLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","m_AutoTeamLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CMyTeamController::OnHanHuaGuild()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","OnHanHuaGuild");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CMyTeamController::OnHanHuaNomal()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","OnHanHuaNomal");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CMyTeamController::OnHanHuaWorld()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","OnHanHuaWorld");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CMyTeamController::OnHanHuaZhaomu()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","OnHanHuaZhaomu");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CMyTeamController::StartAutoTeam()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MyTeamController","StartAutoTeam");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTowerWindow::CTowerWindow( void )
{

}

CTowerWindow::~CTowerWindow( void )
{

}

CTowerWindow * CTowerWindow::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TowerWindow","Instance");
	if (!pfn)return NULL;
	return (CTowerWindow*)pfn->Invoke();
}

void CTowerWindow::OnClickTowerFight()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TowerWindow","OnClickTowerFight");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CTowerWindow::OnClickTowerSweep()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TowerWindow","OnClickTowerSweep");
	if (!pfn)return;
	pfn->Invoke(this);
}

CStdStringU CTowerWindow::get_LeftFightCount()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TowerWindow","m_LeftFightCount");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CTowerWindow::get_LeftSweepCount()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TowerWindow","m_LeftSweepCount");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CUIButton * CTowerWindow::get_TowerSweepBtn()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TowerWindow","m_TowerSweepBtn");
	if (!pField) return NULL;
	return (CUIButton*)pField->GetValueObject(this);
}

void CTowerWindow::OnClickClose()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TowerWindow","OnClickClose");
	if (!pfn)return;
	pfn->Invoke(this);
}

CUIStartWorkGiftController::CUIStartWorkGiftController( void )
{

}

CUIStartWorkGiftController::~CUIStartWorkGiftController( void )
{

}

CUIStartWorkGiftController * CUIStartWorkGiftController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIStartWorkGiftController","Instance");
	if (!pfn)return NULL;
	return (CUIStartWorkGiftController*)pfn->Invoke();
}

void CUIStartWorkGiftController::OnStartDrawGiftClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIStartWorkGiftController","OnStartDrawGiftClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CUIWelfareQianDao::CUIWelfareQianDao( void )
{

}

CUIWelfareQianDao::~CUIWelfareQianDao( void )
{

}

CUIWelfareQianDao * CUIWelfareQianDao::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIWelfareQianDao","Instance");
	if (!pfn)return NULL;
	return (CUIWelfareQianDao*)pfn->Invoke();
}

void CUIWelfareQianDao::OnClickGetReWard()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIWelfareQianDao","OnClickGetReWard");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTabController::CTabController(void)
{

}

CTabController::~CTabController(void)
{

}

void CTabController::DoChangeTab(CUE_Component *pTab)
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TabController","DoChangeTab");
	if (!pfn)return;
	void* agrs[] = {pTab};
	pfn->Invoke(this, agrs);
}

void CTabController::ChangeTab( int iTab )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TabController","ChangeTab(System.Int32)");
	if (!pfn)return;
	void* agrs[] = {&iTab};
	pfn->Invoke(this, agrs);
}

CCopySceneReady::CCopySceneReady( void )
{

}

CCopySceneReady::~CCopySceneReady( void )
{

}

CCopySceneReady * CCopySceneReady::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","CopySceneReady","Instance");
	if (!pfn)return NULL;
	return (CCopySceneReady*)pfn->Invoke();
}

void CCopySceneReady::OnClickConfirm()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","CopySceneReady","OnClickConfirm");
	if (!pfn)return;
	pfn->Invoke(this);
}

CSYS_Object* CCopySceneReady::get_m_LastTeamGuids()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","CopySceneReady","m_LastTeamGuids");
	if (!pfield)return NULL;
	return (CSYS_Object*)pfield->GetValueObject();
}

CUICopySceneLowLevelTips::CUICopySceneLowLevelTips( void )
{

}

CUICopySceneLowLevelTips::~CUICopySceneLowLevelTips( void )
{
	
}

CUICopySceneLowLevelTips * CUICopySceneLowLevelTips::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UICopySceneLowLevelTips","Instance");
	if (!pfn)return NULL;
	return (CUICopySceneLowLevelTips*)pfn->Invoke();
}

void CUICopySceneLowLevelTips::OnConfirmBtnClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UICopySceneLowLevelTips","OnConfirmBtnClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CUICopySceneLowLevelTips::OnCheckBtnClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UICopySceneLowLevelTips","OnCheckBtnClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTeamController::CTeamController(void)
{

}

CTeamController::~CTeamController(void)
{

}

CTeamController* CTeamController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamController","Instance");
	if (!pfn)return NULL;
	return (CTeamController*)pfn->Invoke();
}

void CTeamController::OnClose()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamController","OnClose");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTeamMemberItem::CTeamMemberItem(void)
{

}

CTeamMemberItem::~CTeamMemberItem(void)
{

}

CStdStringU CTeamMemberItem::get_PlayerName()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberItem","get_PlayerName");
	if (!pfn)return CStdStringU(u"");
	CSYS_String *pStr = (CSYS_String *)pfn->Invoke(this);
	return CStdStringU(pStr->GetText());
}

void CTeamMemberItem::OnItemClick(){
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMemberItem","OnItemClick");
	if (!pfn)return;
	pfn->Invoke(this);

}

CGameItem::CGameItem( void )
{

}

CGameItem::~CGameItem( void )
{

}

CStdStringU CGameItem::GetName()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetName");
	if (!pfn)return CStdStringU(u"");
	CSYS_String *pStr = (CSYS_String *)pfn->Invoke(this);
	return CStdStringU(pStr->GetText());
}

CStdStringU CGameItem::GetTipsClassDesc()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetTipsClassDesc");
	if (!pfn)return CStdStringU(u"");
	CSYS_String *pStr = (CSYS_String *)pfn->Invoke(this);
	return CStdStringU(pStr->GetText());
}

int CGameItem::GetColor()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetColor");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

int CGameItem::GetEquipLevel()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetEquipLevel");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

BOOL CGameItem::IsCanInStall()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","IsCanInStall");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameItem::IsCanAutoOrOnceDecompose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","IsCanAutoOrOnceDecompose");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

int CGameItem::GetQuality()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetQuality");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

BOOL CGameItem::IsCanEquip()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","IsCanEquip");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameItem::IsEquipMent()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","IsEquipMent");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CStdStringU CGameItem::GetEquipQualityStr()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetEquipQualityStr");
	if (!pfn)return CStdStringU(u"");
	CSYS_String *pStr = (CSYS_String *)pfn->Invoke(this);
	return CStdStringU(pStr->GetText());
}

CStdStringU CGameItem::GetEquipQualityIcon()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetEquipQualityIcon");
	if (!pfn)return CStdStringU(u"");
	CSYS_String *pStr = (CSYS_String *)pfn->Invoke(this);
	return CStdStringU(pStr->GetText());
}

CStdStringU CGameItem::GetColorTextStr()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","GetColorTextStr");
	if (!pfn)return CStdStringU(u"");
	CSYS_String *pStr = (CSYS_String *)pfn->Invoke(this);
	return CStdStringU(pStr->GetText());
}

BOOL CGameItem::IsEquiped()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","IsEquiped");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameItem::CanSell()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","CanSell");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CGameItem::CanUse()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","CanUse");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

int CGameItem::get_StackCount()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","Item","get_StackCount");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

CKnapsackItem::CKnapsackItem( void )
{

}

CKnapsackItem::~CKnapsackItem( void )
{

}

void CKnapsackItem::OnItemClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","OnItemClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CGameItem * CKnapsackItem::GetGameItem()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","GetGameItem");
	if (!pfn)return NULL;
	return (CGameItem*)pfn->Invoke(this);
}

CStdStringU CKnapsackItem::get_Count()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","m_Count");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CUISprite * CKnapsackItem::m_QualityBg()
{	
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","m_QualityBg");
	if (!pField) return NULL;
	return (CUISprite *)pField->GetValueObject(this);
}

CUISprite * CKnapsackItem::m_Up()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","m_Up");
	if (!pField) return NULL;
	return (CUISprite *)pField->GetValueObject(this);
}

CUISprite * CKnapsackItem::m_Disable()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","m_Disable");
	if (!pField) return NULL;
	return (CUISprite *)pField->GetValueObject(this);
}

CUISprite * CKnapsackItem::m_Lock()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","m_Lock");
	if (!pField) return NULL;
	return (CUISprite *)pField->GetValueObject(this);
}

CStdStringU CKnapsackItem::m_Level()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","m_Level");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

int CKnapsackItem::GetDataId()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackItem","GetDataId");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}



CNumericKeyboardWindow * CNumericKeyboardWindow::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NumericKeyboardWindow","Instance");
	if (!pfn)return NULL;
	return (CNumericKeyboardWindow*)pfn->Invoke();
}

void CNumericKeyboardWindow::OnClickSumbit()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NumericKeyboardWindow","OnClickSumbit");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CNumericKeyboardWindow::OnMaxClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NumericKeyboardWindow","OnMaxClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CNumericKeyboardWindow::OnCloseUI()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NumericKeyboardWindow","OnCloseUI");
	if (!pfn)return;
	pfn->Invoke(this);
}

CFirmSell::CFirmSell( void )
{

}

CFirmSell::~CFirmSell( void )
{

}

CFirmSell * CFirmSell::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirmSell","Instance");
	if (!pfn)return NULL;
	return (CFirmSell*)pfn->Invoke();
}

void CFirmSell::DoSellClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirmSell","DoSellClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CFirmSell::OnInputCountOver( int iNum )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirmSell","OnInputCountOver");
	if (!pfn)return;
	void *agrs[] = {&iNum};
	pfn->Invoke(this,agrs);
}

CGameItem * CFirmSell::GetGameItem()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","FirmSell","m_CurItem");
	if (!pField) return NULL;
	return (CGameItem*)pField->GetValueObject(this);
}

CSYS_List * CFirmSell::m_Items()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","FirmSell","m_Items");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CKnapsackWindow::CKnapsackWindow( void )
{

}

CKnapsackWindow::~CKnapsackWindow( void )
{

}

CKnapsackWindow * CKnapsackWindow::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","Instance");
	if (!pfn)return NULL;
	return (CKnapsackWindow*)pfn->Invoke();
}	

void CKnapsackWindow::OnClickNeaten()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","OnClickNeaten");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CKnapsackWindow::OnClickOpenDecompose()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","OnClickOpenDecompose");
	if (!pfn)return;
	pfn->Invoke(this);
}

CSYS_List * CKnapsackWindow::get_KnapsackList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","m_BackPackItemObjects");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}	

CUE_GameObject * CKnapsackWindow::m_FilterList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","m_FilterList");
	if (!pField) return NULL;
	return (CUE_GameObject*)pField->GetValueObject(this);
}

int CKnapsackWindow::m_FilterType()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","m_FilterType");
	if (!pField) {LOG_WRITE("bbbb");return -1;}
	//return (int)pField->GetValueObject(this);
	CMonoObject *pValue = pField->GetValueObject(this);

	if(!pValue) {LOG_WRITE("aaaa");return -1;}
	return (int)pValue->GetUInt();
}

CSYS_List * CKnapsackWindow::m_FilterItemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","m_FilterItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CSYS_List * CKnapsackWindow::filterItemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","filterItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CKnapsackWindow::Click_Item_BelongBackPack( CGameItem *pGameItem )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackWindow","Click_Item_BelongBackPack");
	if (!pfn)return;
	void* agrs[] = {pGameItem};
	pfn->Invoke(this,agrs);
}

CBrotherhoodPanelMy::CBrotherhoodPanelMy( void )
{

}

CBrotherhoodPanelMy::~CBrotherhoodPanelMy( void )
{

}

CBrotherhoodPanelMy * CBrotherhoodPanelMy::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BrotherhoodPanelMy","Instance");
	if (!pfn)return NULL;
	return (CBrotherhoodPanelMy*)pfn->Invoke();
}

int CBrotherhoodPanelMy::get_itemCount()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","BrotherhoodPanelMy","ITEM_COUNT");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject();
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

void CBrotherhoodPanelMy::OnClickTeamup()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BrotherhoodPanelMy","OnClickTeamup");
	if (!pfn)return;
	pfn->Invoke(this);
}

CActivityRaidWindow::CActivityRaidWindow( void )
{

}

CActivityRaidWindow::~CActivityRaidWindow( void )
{

}

CActivityRaidWindow * CActivityRaidWindow::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidWindow","Instance");
	if (!pfn)return NULL;
	return (CActivityRaidWindow*)pfn->Invoke();
}

CSYS_List * CActivityRaidWindow::get_RaidMenuItemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidWindow","m_RaidMenuItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CActivityRaidWindow::OnEnterClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidWindow","OnEnterClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CStdStringU CActivityRaidWindow::get_ActivityNameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidWindow","m_ActivityNameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CActivityRaidMenuItem::CActivityRaidMenuItem( void )
{

}

CActivityRaidMenuItem::~CActivityRaidMenuItem( void )
{

}

CStdStringU CActivityRaidMenuItem::get_NorItemNameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidMenuItem","m_NorItemNameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CActivityRaidMenuItem::get_SelItemNameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidMenuItem","m_SelItemNameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CSYS_List * CActivityRaidMenuItem::get_SecondaryItemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidMenuItem","m_SecondaryItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CActivityRaidMenuItem::ClickRaidMenuItem()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityRaidMenuItem","ClickRaidMenuItem");
	if (!pfn)return;
	pfn->Invoke(this);
}

CLeftInfoController::CLeftInfoController( void )
{

}

CLeftInfoController::~CLeftInfoController( void )
{

}

CLeftInfoController * CLeftInfoController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","LeftInfoController","Instance");
	if (!pfn)return NULL;
	return (CLeftInfoController*)pfn->Invoke();
}

void CLeftInfoController::OnTeamClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","LeftInfoController","OnTeamClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTeamTargetAdjust::CTeamTargetAdjust( void )
{

}

CTeamTargetAdjust::~CTeamTargetAdjust( void )
{

}

CSYS_List * CTeamTargetAdjust::get_SubClassList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamTargetAdjust","m_SubClassList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CTeamTargetAdjust::OnOK()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamTargetAdjust","OnOK");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTeamTargetAdjust* CTeamTargetAdjust::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamTargetAdjust","Instance");
	if (!pfn)return NULL;
	return (CTeamTargetAdjust*)pfn->Invoke();
}

CJoinTeamSubItem::CJoinTeamSubItem( void )
{

}

CJoinTeamSubItem::~CJoinTeamSubItem( void )
{

}

CStdStringU CJoinTeamSubItem::get_secondNameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","JoinTeamSubItem","secondNameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CJoinTeamSubItem::OnItemClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","JoinTeamSubItem","OnItemClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CStdStringU CJoinTeamSubItem::get_NormalNameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","JoinTeamSubItem","NormalNameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CJoinTeamSubItem::get_NameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","JoinTeamSubItem","NameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

BOOL CJoinTeamSubItem::get_AutoTeam()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","JoinTeamSubItem","get_AutoTeam");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CTargetWindow::CTargetWindow( void )
{

}

CTargetWindow::~CTargetWindow( void )
{

}

CStdStringU CTargetWindow::get_HPLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TargetWindow","m_HPLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CTargetWindow::get_NameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TargetWindow","m_NameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CTargetWindow::get_LevelLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TargetWindow","m_LevelLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CSYS_List * CTargetWindow::get_BuffList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TargetWindow","m_BuffList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CStdStringU CTargetWindow::get_TarName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TargetWindow","m_TarName");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CTargetWindow::UpdateTarget()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TargetWindow","UpdateTarget");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CTargetWindow::UpdateTargetSelected( CObj_Char *pNPC )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TargetWindow","UpdateTargetSelected");
	if (!pfn) return;
	void* agrs[] = {pNPC};
	pfn->Invoke(this,agrs);
}

CTargetFrameControllerNew * CTargetFrameControllerNew::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TargetFrameControllerNew","Instance");
	if (!pfn)return NULL;
	return (CTargetFrameControllerNew*)pfn->Invoke();
}

CTargetWindow * CTargetFrameControllerNew::get_TargetBoss()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TargetFrameControllerNew","m_TargetBoss");
	if (!pField) return NULL;
	return (CTargetWindow*)pField->GetValueObject(this);
}

CTargetWindow * CTargetFrameControllerNew::get_TargetNormal()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TargetFrameControllerNew","m_TargetNormal");
	if (!pField) return NULL;
	return (CTargetWindow*)pField->GetValueObject(this);
}

CBuffInfo::CBuffInfo( void )
{

}

CBuffInfo::~CBuffInfo( void )
{

}

BOOL CBuffInfo::get_DisableMove()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BuffInfo","get_DisableMove");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CBuffInfo::get_DisableSkill()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BuffInfo","get_DisableSkill");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

void CBuffInfo::set_DisableMove( BOOL bValue )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BuffInfo","set_DisableMove");
	if (!pfn) return;
	void* agrs[] = {&bValue};
	pfn->Invoke(this,agrs);
}

void CBuffInfo::set_DisableSkill( BOOL bValue )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BuffInfo","set_DisableSkill");
	if (!pfn) return;
	void* agrs[] = {&bValue};
	pfn->Invoke(this,agrs);
}

CSceneMapController::CSceneMapController( void )
{

}

CSceneMapController::~CSceneMapController( void )
{

}

CSceneMapController * CSceneMapController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SceneMapController","Instance");
	if (!pfn) return NULL;
	return (CSceneMapController *)pfn->Invoke();
}

CStdStringU CSceneMapController::get_SceneNameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SceneMapController","m_SceneNameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CSceneMapController::OnCloseWindow()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SceneMapController","OnCloseWindow");
	if (!pfn)return;
	pfn->Invoke(this);
}

CAutoSearchPointLogic::CAutoSearchPointLogic( void )
{

}

CAutoSearchPointLogic::~CAutoSearchPointLogic( void )
{

}

CStdStringU CAutoSearchPointLogic::get_LabelName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","AutoSearchPointLogic","m_LabelName");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CAutoSearchPointLogic::OnTransmitPointClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AutoSearchPointLogic","OnTransmitPointClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CUIJianMuXBSlot::CUIJianMuXBSlot( void )
{

}

CUIJianMuXBSlot::~CUIJianMuXBSlot( void )
{

}

BOOL CUIJianMuXBSlot::get_BEnough()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBSlot","get_BEnough");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CUIJianMuXBSlot::IsSelect()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBSlot","IsSelect");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CStdStringU CUIJianMuXBSlot::get_ItemName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBSlot","lbl_Name");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CUIJianMuXBPanel::CUIJianMuXBPanel( void )
{

}

CUIJianMuXBPanel::~CUIJianMuXBPanel( void )
{

}

CUIJianMuXBPanel * CUIJianMuXBPanel::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","Instance");
	if (!pfn) return NULL;
	return (CUIJianMuXBPanel *)pfn->Invoke();
}

CStdStringU CUIJianMuXBPanel::get_SelectName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","lbl_SelectName");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());

}

CUIJianMuXBSlot * CUIJianMuXBPanel::get_selectSlot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","scp_selectSlot");
	if (!pField) return NULL;
	return (CUIJianMuXBSlot*)pField->GetValueObject(this);	
}

CUIJianMuXBSlot * CUIJianMuXBPanel::get_CurSelectSlot()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","m_CurSelectSlot");
	if (!pField) return NULL;
	return (CUIJianMuXBSlot*)pField->GetValueObject(this);	
}

void CUIJianMuXBPanel::OnClickFill()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","OnClickFill");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CUIJianMuXBPanel::OnClickReward()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","OnClickReward");
	if (!pfn)return;
	pfn->Invoke(this);
}

BOOL CUIJianMuXBPanel::get_bCanGetReward()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","m_bCanGetReward");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}	

void CUIJianMuXBPanel::OnSelectItem( int iItem )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","OnSelectItem");
	if (!pfn)return;
	void *agrs[] = {&iItem};
	pfn->Invoke(this,agrs);
}

void CUIJianMuXBPanel::OnClickClose()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIJianMuXBPanel","OnClickClose");
	if (!pfn)return;
	pfn->Invoke(this);
}

CStallMultiBuyConfirm::CStallMultiBuyConfirm( void )
{

}

CStallMultiBuyConfirm::~CStallMultiBuyConfirm( void )
{

}

void CStallMultiBuyConfirm::BuyItem()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","BuyItem");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CStallMultiBuyConfirm::OnInputCountOver( int iAmountOf )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","OnInputCountOver");
	if (!pfn)return;
	void *agrs[] = {&iAmountOf};
	pfn->Invoke(this,agrs);
}

CStdStringU CStallMultiBuyConfirm::get_ItemName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","m_ItemName");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStallMultiBuyConfirm * CStallMultiBuyConfirm::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","Instance");
	if (!pfn) return NULL;
	return (CStallMultiBuyConfirm  *)pfn->Invoke();
}

int CStallMultiBuyConfirm::get_NowMonney()
{	
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","m_NowMoney");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

CSYS_List * CStallMultiBuyConfirm::get_ListCount()
{	
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","m_StackCount");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CSYS_List * CStallMultiBuyConfirm::get_ListPrice()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","m_Price");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CStdStringU CStallMultiBuyConfirm::get_NumText()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiBuyConfirm","m_NumText");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}	

	

CSystemShopWindow::CSystemShopWindow( void )
{

}

CSystemShopWindow::~CSystemShopWindow( void )
{

}

CSystemShopWindow * CSystemShopWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SystemShopWindow","Instance");
	if (!pfn) return NULL;
	return (CSystemShopWindow  *)pfn->Invoke();
}

void CSystemShopWindow::Buy()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SystemShopWindow","Buy");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CSystemShopWindow::OnItemNumChoose( int iNumber )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SystemShopWindow","OnItemNumChoose");
	if (!pfn)return;
	void *agrs[] = {&iNumber};
	pfn->Invoke(this,agrs);
}

CStdStringU CSystemShopWindow::get_InputNumber()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SystemShopWindow","m_InputNumber");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CSystemShopWindow * CSystemShopWindow::m_curShowPage()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SystemShopWindow","m_curShowPage");
	if (!pField) return NULL;
	return (CSystemShopWindow *)pField->GetValueObject(this);
}

CStdStringU CSystemShopWindow::LabelItemName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SystemShopWindow","LabelItemName");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU("");
	return CStdStringU(pLabel->get_text()->GetText());
}

CFirmBuy::CFirmBuy( void )
{

}

CFirmBuy::~CFirmBuy( void )
{

}

CFirmBuy * CFirmBuy::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirmBuy","Instance");
	if (!pfn)return NULL;
	return (CFirmBuy*)pfn->Invoke();
}

void CFirmBuy::ConfirmBuy()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirmBuy","ConfirmBuy");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CFirmBuy::OnInputCountOver( int iNum )
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirmBuy","OnInputCountOver");
	if (!pfn)return;
	void *agrs[] = {&iNum};
	pfn->Invoke(this,agrs);
}

CTeamMenuFast::CTeamMenuFast(void)
{

}

CTeamMenuFast::~CTeamMenuFast(void)
{

}

void CTeamMenuFast::OnClickKick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMenuFast","OnClickKick");
	if (!pfn)return;
	pfn->Invoke(this);	
}

CTeamMenu::CTeamMenu(void)
{

}

CTeamMenu::~CTeamMenu(void)
{

}

void CTeamMenu::OnClickKickBtn()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMenu","OnClickKickBtn");
	if (!pfn)return;
	pfn->Invoke(this);
}

CGuildConvoyFillPanel::CGuildConvoyFillPanel( void )
{

}

CGuildConvoyFillPanel::~CGuildConvoyFillPanel( void )
{

}

CGuildConvoyFillPanel * CGuildConvoyFillPanel::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildConvoyFillPanel","Instance");
	if (!pfn) return NULL;
	return (CGuildConvoyFillPanel  *)pfn->Invoke();
}

void CGuildConvoyFillPanel::OnClickConfirm()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildConvoyFillPanel","OnClickConfirm");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CGuildConvoyFillPanel::OnClickRandom()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildConvoyFillPanel","OnClickRandom");
	if (!pfn)return;
	pfn->Invoke(this);
}

CUIToggle::CUIToggle( void )
{

}

CUIToggle::~CUIToggle( void )
{

}

BOOL CUIToggle::get_isChecked()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIToggle","get_isChecked");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CMissionTrack::CMissionTrack( void )
{

}

CMissionTrack::~CMissionTrack( void )
{

}

CMissionTrack * CMissionTrack::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","Instance");
	if (!pfn) return NULL;
	return (CMissionTrack  *)pfn->Invoke();
}

CSYS_List * CMissionTrack::get_MainAceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_MainAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::get_MainCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_MainCompletedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_ChuanQiAceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_MainUnAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_ChuanQiCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_OtherUnAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_BranchAceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_BranchAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_BranchCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_BranchCompletedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_SurpriseAceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_DigTreasureAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_SurpriseCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_DigTreasureCompletedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_CircleAceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_PaperClipAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_CircleCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_PaperClipCompletedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_NewGuideAceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_NewGuideAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_NewGuideCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_NewGuideCompletedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_QiYuAceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_QiYuAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_QiYuCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_QiYuCompletedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_ApprenticeAcceptedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_CatchGhostAceptedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CSYS_List * CMissionTrack::m_ApprenticeCompletedList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","MissionTrack","m_CatchGhostCompletedList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject(this);
}

CAchievementRecordItem::CAchievementRecordItem( void )
{

}

CAchievementRecordItem::~CAchievementRecordItem( void )
{

}

void CAchievementRecordItem::OnClickGetReward()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AchievementRecordItem","OnClickGetReward");
	if (!pfn)return;
	pfn->Invoke(this);
}

CNpcHeadInfoLogic::CNpcHeadInfoLogic( void )
{

}

CNpcHeadInfoLogic::~CNpcHeadInfoLogic( void )
{

}

CStdStringU CNpcHeadInfoLogic::get_NameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic","m_NameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

BOOL CNpcHeadInfoLogic::IsShow()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic","isShow");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

CObj_Char* CNpcHeadInfoLogic::get_NPC()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic","m_BindNpc");
	if (!pField) return 0;
	return (CObj_Char*)pField->GetValueObject(this);
}

CStdStringU CNpcHeadInfoLogic::get_TitleLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","NpcHeadInfoLogic","m_TitleLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CPlayerHeadInfoLogic::CPlayerHeadInfoLogic( void )
{

}

CPlayerHeadInfoLogic::~CPlayerHeadInfoLogic( void )
{

}

CObj_MainPlayer* CPlayerHeadInfoLogic::get_MainPlayer()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PlayerHeadInfoLogic","m_BindPlayer");
	if (!pField) return 0;
	return (CObj_MainPlayer*)pField->GetValueObject(this);
}

CStdStringU CPlayerHeadInfoLogic::get_NameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PlayerHeadInfoLogic","m_NameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CObj_MainPlayer::CObj_MainPlayer( void )
{

}

CObj_MainPlayer::~CObj_MainPlayer( void )
{

}

void CObj_MainPlayer::MoveToTarget( CObj_Char *pObjChar/*Games.LogicObj.Obj_Char,System.Single*/ )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","MoveToTarget");
	if (!pfn) return;
	int i = 0;
	void* agrs[] = {pObjChar ,&i};
	pfn->Invoke(this,agrs);
}

void CObj_MainPlayer::LeaveTeamOk()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","LeaveTeamOk");
	if (!pfn)return;
	pfn->Invoke(this);
}

int CObj_MainPlayer::get_LastLevel()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","get_LastLevel");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

void CObj_MainPlayer::AskLeaveTeamFollow()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","AskLeaveTeamFollow");
	if (!pfn)return;
	pfn->Invoke(this);
}

BOOL CObj_MainPlayer::get_IsInTeamFollow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","get_IsInTeamFollow");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

void CObj_MainPlayer::set_SelectTarget( CObj_Char *pNPC )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","set_SelectTarget");
	if (!pfn) return;
	void* agrs[] = {pNPC};
	pfn->Invoke(this,agrs);
}

void CObj_MainPlayer::ReqJoinTeam( ULONGLONG uGuid )
{
	LOG_WRITE("ReqJoinTeam......");
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","ReqJoinTeam");
	if (!pfn)return;
	void* agrs[] = {&uGuid};
	pfn->Invoke(this, agrs);
}

void CObj_MainPlayer::ReqChangeTeamLeader( ULONGLONG uGuid )
{
	LOG_WRITE("ReqChangeTeamLeader......");
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","ReqChangeTeamLeader");
	if (!pfn)return;
	void* agrs[] = {&uGuid};
	pfn->Invoke(this, agrs);
}

void CObj_MainPlayer::AddNewFriendGuid( ULONGLONG uGuid )
{
	LOG_WRITE("AddNewFriendGuid.........");
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","AddNewFriendGuid");
	if (!pfn)return;
	void* agrs[] = {&uGuid};
	pfn->Invoke(this, agrs);
}

void CObj_MainPlayer::ReqAllowJoin( ULONGLONG uGuid )
{
	LOG_WRITE("ReqAllowJoin.........");
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","ReqAllowJoin");
	if (!pfn)return;
	void* agrs[] = {&uGuid};
	pfn->Invoke(this, agrs);
}

void CObj_MainPlayer::ReqInviteTeam( ULONGLONG uGuid )
{
	LOG_WRITE("ReqInviteTeam.........");
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->FindMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","ReqInviteTeam(System.UInt64,System.Int32,System.Int32)");
	if (!pfn)return;
	int x = 0;
	int y = 0;
	void* agrs[] = {&uGuid, &x, &y};
	pfn->Invoke(this, agrs);
}

void CObj_MainPlayer::ReqInviteTeam( LPVOID list, int inviteType, int targetId )
{
	LOG_WRITE("ReqAllowJoinList.........");
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->FindMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","ReqInviteTeam(System.Collections.Generic.List<System.UInt64>,System.Int32,System.Int32)");
	if (!pfn)return;
	void* agrs[] = {list,&inviteType, &targetId};
	pfn->Invoke(this, agrs);
}

CSYS_List* CObj_MainPlayer::get_AttackList()
{
	static CField* pfield= NULL;
	if (!pfield) pfield = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","AttackList");
	if (!pfield)return NULL;
	return (CSYS_List*) pfield->GetValueObject();
}

void CObj_MainPlayer::StopMoveAndSync()
{

	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_MainPlayer","StopMoveAndSync");
	if (!pfn)return;
	pfn->Invoke(this);
}

CLimitTimePushTipsItem::CLimitTimePushTipsItem( void )
{

}

CLimitTimePushTipsItem::~CLimitTimePushTipsItem( void )
{

}

CStdStringU CLimitTimePushTipsItem::get_ActivityName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsItem","m_ActivityName");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CStdStringU CLimitTimePushTipsItem::get_Count()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsItem","m_Count");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CLimitTimePushTipsItem::OnClickGoBtn()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsItem","OnClickGoBtn");
	if (!pfn)return;
	pfn->Invoke(this);
}

CGuildThiefSettlementController::CGuildThiefSettlementController( void )
{

}

CGuildThiefSettlementController::~CGuildThiefSettlementController( void )
{

}

CGuildThiefSettlementController * CGuildThiefSettlementController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildThiefSettlementController","Instance");
	if (!pfn) return NULL;
	return (CGuildThiefSettlementController*)pfn->Invoke();	
}

void CGuildThiefSettlementController::OnClose()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildThiefSettlementController","OnClose");
	if (!pfn)return;
	pfn->Invoke(this);
}

CMisChooseLogic::CMisChooseLogic( void )
{

}

CMisChooseLogic::~CMisChooseLogic( void )
{

}

CMisChooseLogic * CMisChooseLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MisChooseLogic","Instance");
	if (!pfn) return NULL;
	return (CMisChooseLogic*)pfn->Invoke();
}

void CMisChooseLogic::ClickLeft()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MisChooseLogic","ClickLeft");
	if (!pfn)return;
	pfn->Invoke(this);
}

CTeamPlatformWindow::CTeamPlatformWindow( void )
{

}

CTeamPlatformWindow::~CTeamPlatformWindow( void )
{

}

CTeamPlatformWindow * CTeamPlatformWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamPlatformWindow","Instance");
	if (!pfn) return NULL;
	return (CTeamPlatformWindow*)pfn->Invoke();
}


void CTeamPlatformWindow::OnAutoTeam()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamPlatformWindow","OnAutoTeam");
	if (!pfn)return;
	pfn->Invoke(this);
}

void CTeamPlatformWindow::OnAutoTeamClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamPlatformWindow","OnAutoTeamClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CSYS_List* CTeamPlatformWindow::get_SubClassList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamPlatformWindow","m_SubClassList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CJoinTeamSubItem* CTeamPlatformWindow::get_CurSelecItem()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","TeamPlatformWindow","m_CurSelecItem");
	if (!pField) return NULL;
	return (CJoinTeamSubItem*)pField->GetValueObject(this);
}



CGuildConvoyConfirm::CGuildConvoyConfirm( void )
{

}

CGuildConvoyConfirm::~CGuildConvoyConfirm( void )
{

}

CGuildConvoyConfirm * CGuildConvoyConfirm::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildConvoyConfirm","Instance");
	if (!pfn) return NULL;
	return (CGuildConvoyConfirm*)pfn->Invoke();
}

void CGuildConvoyConfirm::OnClickYes()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildConvoyConfirm","OnClickYes");
	if (!pfn)return;
	pfn->Invoke(this);
}

CWorldMapController::CWorldMapController( void )
{

}

CWorldMapController::~CWorldMapController( void )
{

}
void CWorldMapController::SceneMapOpenMap()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","WorldMapController","SceneMapOpenMap");
	if (!pfn) return;
	pfn->Invoke();
}

CSYS_List * CWorldMapController::m_SmallMapItemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","WorldMapController","m_SmallMapItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CWorldMapController::OnMapItemBtnClick( CSmallMapItem *pItem )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","WorldMapController","OnMapItemBtnClick");
	if (!pfn) return;
	void* agrs[] = {pItem};
	pfn->Invoke(this,agrs);
}

void CWorldMapController::OnCloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"WorldMapController","OnCloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}

CWorldMapController * CWorldMapController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","WorldMapController","Instance");
	if (!pfn) return NULL;
	return (CWorldMapController*)pfn->Invoke();
}

CActiveSceneLogic::CActiveSceneLogic( void )
{

}

CActiveSceneLogic::~CActiveSceneLogic( void )
{

}

float CActiveSceneLogic::get_CurFPS()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Scene","ActiveSceneLogic","get_CurFPS");
	if (!pfn) return 0;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return 0;
	return (float)pObj->GetFloat();
}

CUE_Transform * CActiveSceneLogic::get_CharRoot()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Scene","ActiveSceneLogic","get_CharRoot");
	if (!pfn) return NULL;
	return (CUE_Transform*)pfn->Invoke(this);
}

CUE_GameObject * CActiveSceneLogic::get_AirWallRoot()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Scene","ActiveSceneLogic","get_AirWallRoot");
	if (!pfn) return NULL;
	return (CUE_GameObject*)pfn->Invoke(this);
}

CApplication::CApplication( void )
{

}

CApplication::~CApplication( void )
{

}

void CApplication::set_targetFrameRate( int iFrame )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_UNITY_ENGINE_COREMODULE,IMAGE_UNITY_ENGINE,"Application","set_targetFrameRate");
	if (!pfn) return;
	void* agrs[] = {&iFrame};
	pfn->Invoke(NULL ,agrs);
}

CUIBounty_Main::CUIBounty_Main( void )
{

}

CUIBounty_Main::~CUIBounty_Main( void )
{

}

CUIBounty_Main * CUIBounty_Main::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_Main","Instance");
	if (!pfn) return NULL;
	return (CUIBounty_Main*)pfn->Invoke();
}

CSYS_List * CUIBounty_Main::get_UIBounty_DetailInfo()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_Main","m_DetailList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CSYS_List * CUIBounty_Main::get_UIBounty_BossItem()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_Main","m_BossItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CStdStringU CUIBounty_Main::get_CombatValue()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_Main","m_CombatValue");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CUIBounty_Main::OnClickClose()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_Main","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIBounty_BossItem::CUIBounty_BossItem( void )
{

}

CUIBounty_BossItem::~CUIBounty_BossItem( void )
{

}

CStdStringU CUIBounty_BossItem::get_NameLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_BossItem","m_NameLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CUIBounty_BossItem::OnClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_BossItem","OnClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CStdStringU CUIBounty_BossItem::get_LevelLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_BossItem","m_LevelLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

CUIBounty_DetailInfo::CUIBounty_DetailInfo( void )
{

}

CUIBounty_DetailInfo::~CUIBounty_DetailInfo( void )
{

}

CStdStringU CUIBounty_DetailInfo::get_PosLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_DetailInfo","m_PosLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CUIBounty_DetailInfo::OnClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIBounty_DetailInfo","OnClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CObj_NPC::CObj_NPC( void )
{

}

CObj_NPC::~CObj_NPC( void )
{

}

CStdStringU CObj_NPC::get_szNpcTitle()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","m_szNpcTitle");
	if (!pfn) return CStdStringU(u"No pfn");
	CSYS_String* pText = (CSYS_String *)pfn->Invoke(this);
	if (!pText) return CStdStringU(u"NO pText");
	return pText->GetText();
	//return u"aaaa";
}

CNpcHeadInfoLogic * CObj_NPC::get_NpcHeadInfoLogic()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","m_NpcHeadInfoLogic");
	if (!pField) return NULL;
	return (CNpcHeadInfoLogic*)pField->GetValueObject(this);
}

BOOL CObj_NPC::get_IsBornCreate()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","get_IsBornCreate");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

int CObj_NPC::get_BelongTeamID()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","get_BelongTeamID");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

int CObj_NPC::get_OwnTeamId()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","get_OwnTeamId");
	if (!pfn)return -1;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

CNPCDialog * CObj_NPC::m_Dialog()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","m_Dialog");
	if (!pField) return NULL;
	return (CNPCDialog*)pField->GetValueObject(this);
}

int CObj_NPC::get_BelongObjID()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","get_BelongObjID");
	if (!pfn)return -1;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

int CObj_NPC::get_NPCType()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","get_NPCType");
	if (!pfn)return -1;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

BOOL CObj_NPC::get_CanBeSeleByClient()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_NPC","get_CanBeSeleByClient");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}



CObj_Char::CObj_Char( void )
{

}

CObj_Char::~CObj_Char( void )
{

}

CStdStringU CObj_Char::get_RoleName()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Char","get_RoleName");
	if (!pfn) return CStdStringU(u"No pfn");
	CSYS_String* pText = (CSYS_String *)pfn->Invoke(this);
	if (!pText) return CStdStringU(u"NO pText");
	return pText->GetText();
}

BOOL CObj_Char::get_IsInCombat()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Char","get_IsInCombat");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CObj_Char::get_IsMoving()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Char","get_IsMoving");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CUE_Transform * CObj_Char::get_HeadInfoTran()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Char","get_HeadInfoTran");
	if (!pfn) return NULL;
	return (CUE_Transform*)pfn->Invoke(this);
}

BOOL CObj_Char::IsDie()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj_Char","IsDie");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CObj::CObj( void )
{

}

CObj::~CObj( void )
{

}

CUE_Vector3 * CObj::get_Position()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj","get_Position");
	if (!pfn) return NULL;
	return (CUE_Vector3*)pfn->Invoke(this);
}

void CObj::set_Position(CUE_Vector3 *pVt3)
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj","set_Position");
	if (!pfn) return;
	void* agrs[] = {pVt3};
	pfn->Invoke(this,agrs);
}

BOOL CObj::IsNpc()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.LogicObj","Obj","IsNpc");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CPlayerImpactShowController::CPlayerImpactShowController( void )
{

}

CPlayerImpactShowController::~CPlayerImpactShowController( void )
{

}

CBuffInfo* CPlayerImpactShowController::get_ImpactInfo()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","PlayerImpactShowController","m_BuffInfo");
	if (!pField) return NULL;
	return (CBuffInfo*)pField->GetValueObject(this);
}

CChatLinkItem::CChatLinkItem( void )
{

}

CChatLinkItem::~CChatLinkItem( void )
{

}

void CChatLinkItem::OnBtnClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatLinkItem","OnBtnClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CChatInfoController::CChatInfoController( void )
{

}

CChatInfoController::~CChatInfoController( void )
{

}

CChatInfoController * CChatInfoController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatInfoController","Instance");
	if (!pfn) return NULL;
	return (CChatInfoController*)pfn->Invoke();
}

void CChatInfoController::OnCloseClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ChatInfoController","OnCloseClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CQianKunDaiWindow::CQianKunDaiWindow( void )
{

}

CQianKunDaiWindow::~CQianKunDaiWindow( void )
{

}

CQianKunDaiWindow * CQianKunDaiWindow::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","QianKunDaiWindow","Instance");
	if (!pfn) return NULL;
	return (CQianKunDaiWindow*)pfn->Invoke();
}

CSYS_List * CQianKunDaiWindow::get_QianKunDaiStuff()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","QianKunDaiWindow","m_QianKunDaiStuff");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CSYS_List * CQianKunDaiWindow::get_QianKunDaiFilter()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","QianKunDaiWindow","m_QianKunDaiFilter");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CQianKunDaiWindow::OnCombineClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","QianKunDaiWindow","OnCombineClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CQianKunDaiWindow::OnBackItemClick( CGameItem *pGameItem )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","QianKunDaiWindow","OnBackItemClick");
	if (!pfn) return;
	void* agrs[] = {pGameItem};
	pfn->Invoke(this ,agrs);
}

CGameItem * CQianKunDaiWindow::get_SuccessItem()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","QianKunDaiWindow","m_SucessItem");
	if (!pField) return NULL;
	return (CGameItem*)pField->GetValueObject(this);
}

CWorldBossController::CWorldBossController( void )
{

}

CWorldBossController::~CWorldBossController( void )
{

}

void CWorldBossController::OnGoBtClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","WorldBossController","OnGoBtClick");
	if (!pfn) return;
	pfn->Invoke();
}

CHomeRootController::CHomeRootController( void )
{

}

CHomeRootController::~CHomeRootController( void )
{

}

CHomeRootController * CHomeRootController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","HomeRootController","Instance");
	if (!pfn) return NULL;
	return (CHomeRootController*)pfn->Invoke();
}

CTabController * CHomeRootController::get_TabController()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","HomeRootController","m_TabBtnController");
	if (!pField) return NULL;
	return (CTabController*)pField->GetValueObject(this);
}

void CHomeRootController::OnOpenHomeGeo()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP, "", "HomeRootController", "OnOpenHomeGeo");
	if (!pfn)return;
	BOOL bShow = TRUE;
	CSYS_Object *pObj = NULL;
	void* agrs[] = {&bShow, pObj};
	pfn->Invoke(NULL, agrs);
}

CHomeGeoController::CHomeGeoController( void )
{

}

CHomeGeoController::~CHomeGeoController( void )
{

}

CHomeGeoController * CHomeGeoController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","HomeGeoController","Instance");
	if (!pfn) return NULL;
	return (CHomeGeoController*)pfn->Invoke();
}

void CHomeGeoController::OnClickCloseFortunePack()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","HomeGeoController","OnClickCloseFortunePack");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CHomeGeoController::OnClickOpenArchaeology()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","HomeGeoController","OnClickOpenArchaeology");
	if (!pfn) return;
	pfn->Invoke(this);
}

CItemPack::CItemPack( void )
{

}

CItemPack::~CItemPack( void )
{

}

int CItemPack::GetEmptySize()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Item","ItemPack","GetEmptySize");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

CSocialRootController::CSocialRootController( void )
{

}

CSocialRootController::~CSocialRootController( void )
{

}

CSocialRootController * CSocialRootController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SocialRootController","Instance");
	if (!pfn) return NULL;
	return (CSocialRootController*)pfn->Invoke();
}

CTabController * CSocialRootController::get_TabController()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SocialRootController","m_tablecontroller");
	if (!pField) return NULL;
	return (CTabController*)pField->GetValueObject(this);
}

void CSocialRootController::OnClickCloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SocialRootController","OnClickCloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}

CSettingController::CSettingController( void )
{

}

CSettingController::~CSettingController( void )
{

}

CSettingController * CSettingController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SettingController","Instance");
	if (!pfn) return NULL;
	return (CSettingController*)pfn->Invoke();
}

void CSettingController::OnCloseClick()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SettingController","OnCloseClick");
	if (!pfn)return;
	pfn->Invoke(this);
}

CAchievementRewardItem::CAchievementRewardItem( void )
{

}

CAchievementRewardItem::~CAchievementRewardItem( void )
{

}

void CAchievementRewardItem::OnClickGetReward()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AchievementRewardItem","OnClickGetReward");
	if (!pfn)return;
	pfn->Invoke(this);
}

BOOL CAchievementRewardItem::get_bHaveReward()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AchievementRewardItem","get_bHaveReward");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CTeamMember::CTeamMember( void )
{

}

CTeamMember::~CTeamMember( void )
{

}

CStdStringU CTeamMember::get_MemberName()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMember","get_MemberName");
	if (!pfn) return u"";
	CSYS_String* pstr = (CSYS_String*)pfn->Invoke(this);
	return (CStdStringU)pstr->GetText();
}

BOOL CTeamMember::get_AutoCombat()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMember","get_AutoCombat");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CTeamMember::IsValid()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeamMember","IsValid");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CGuildBanghuaResultController::CGuildBanghuaResultController( void )
{

}

CGuildBanghuaResultController::~CGuildBanghuaResultController( void )
{

}

CGuildBanghuaResultController * CGuildBanghuaResultController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildBanghuaResultController","Instance");
	if (!pfn) return NULL;
	return (CGuildBanghuaResultController*)pfn->Invoke();
}

void CGuildBanghuaResultController::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildBanghuaResultController","CloseWindow");
	if (!pfn) return;
	pfn->Invoke();
}

CReadMailLogic::CReadMailLogic( void )
{

}

CReadMailLogic::~CReadMailLogic( void )
{

}

CReadMailLogic * CReadMailLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReadMailLogic","Instance");
	if (!pfn) return NULL;
	return (CReadMailLogic*)pfn->Invoke();
}

void CReadMailLogic::DoDeleteAll()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReadMailLogic","DoDeleteAll");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CReadMailLogic::OnClickExtractAll()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReadMailLogic","OnClickExtractAll");
	if (!pfn) return;
	pfn->Invoke(this);
}

BOOL CReadMailLogic::IsAllMailsHaveItem()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ReadMailLogic","IsAllMailsHaveItem");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CActivenessBonusItem::CActivenessBonusItem( void )
{

}

CActivenessBonusItem::~CActivenessBonusItem( void )
{

}

BOOL CActivenessBonusItem::get_IsCanReceived()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ActivenessBonusItem","m_bIsCanGain");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

void CActivenessBonusItem::ClickItem()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivenessBonusItem","ClickItem");
	if (!pfn) return;
	pfn->Invoke(this);
}	

CLimitTimePushTipsController::CLimitTimePushTipsController( void )
{

}

CLimitTimePushTipsController::~CLimitTimePushTipsController( void )
{

}

CSYS_List * CLimitTimePushTipsController::get_ListYLTX()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsController","m_YLTXSceneList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject();
}

CLimitTimePushTipsController* CLimitTimePushTipsController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsController","Instance");
	if (!pfn) return NULL;
	return (CLimitTimePushTipsController*)pfn->Invoke();
}

CLimitActivityYLTX * CLimitTimePushTipsController::get_LimitActivityYLTX()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsController","m_YLTXWindow");
	if (!pField) return NULL;
	return (CLimitActivityYLTX*)pField->GetValueObject(this);
}

void CLimitTimePushTipsController::ShowYLTXWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->FindMethod(IMAGE_ASSEMBLY_CSHARP,"","LimitTimePushTipsController","ShowYLTXWindow()");
	if (!pfn) return;
	pfn->Invoke(this);
}

CYLTXSceneData::CYLTXSceneData( void )
{

}

CYLTXSceneData::~CYLTXSceneData( void )
{

}

int CYLTXSceneData::get_NpcNum()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","YLTXSceneData","get_NpcNum");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

int CYLTXSceneData::get_SceneId()
{	
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","YLTXSceneData","get_SceneId");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

CYLTXRemainNpcData::CYLTXRemainNpcData( void )
{

}

CYLTXRemainNpcData::~CYLTXRemainNpcData( void )
{

}

int CYLTXRemainNpcData::get_NpcPosId()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","YLTXRemainNpcData","get_NpcPosId");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

int CYLTXRemainNpcData::get_ObjId()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","YLTXRemainNpcData","get_ObjId");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

CMilitaryDonationWindow::CMilitaryDonationWindow( void )
{

}

CMilitaryDonationWindow::~CMilitaryDonationWindow( void )
{

}

CMilitaryDonationWindow * CMilitaryDonationWindow::Instance()
{	
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MilitaryDonationWindow","Instance");
	if (!pfn) return NULL;
	return (CMilitaryDonationWindow*)pfn->Invoke();
}

void CMilitaryDonationWindow::OnClickDonate()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MilitaryDonationWindow","OnClickDonate");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CMilitaryDonationWindow::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MilitaryDonationWindow","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CRelationList::CRelationList( void )
{

}

CRelationList::~CRelationList( void )
{

}

CSYS_List * CRelationList::get_sortedList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","RelationList","m_sortedList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

int CRelationList::GetRelationNum()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RelationList","GetRelationNum");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

CRelation::CRelation( void )
{

}

CRelation::~CRelation( void )
{

}

CStdStringU CRelation::get_Name()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Relation","get_Name");
	if (!pfn) return u"";
	CSYS_String* pstr = (CSYS_String*)pfn->Invoke(this);
	return (CStdStringU)pstr->GetText();
}

ULONGLONG CRelation::get_Guid()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Relation","get_Guid");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (ULONGLONG)pObj->GetUInt64();
}

int CRelation::get_State()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Relation","get_State");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

int CRelation::get_TeamID()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","Relation","get_TeamID");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

CObjManager::CObjManager( void )
{

}

CObjManager::~CObjManager( void )
{

}

CObj_MainPlayer * CObjManager::get_MainPlayer()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ObjManager","get_MainPlayer");
	if (!pfn) return NULL;
	return (CObj_MainPlayer*)pfn->Invoke();	
}

CLimitActivityYLTX::CLimitActivityYLTX( void )
{

}

CLimitActivityYLTX::~CLimitActivityYLTX( void )
{

}

void CLimitActivityYLTX::OnClickSyncYLTXData()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","LimitActivityYLTX","OnClickSyncYLTXData");
	if (!pfn) return;
	pfn->Invoke(this);
}

#pragma region mscorlib

CClass* CSYS_Array::_class = NULL;
BOOL CSYS_Array::_GetClass()
{
	if (_class) return TRUE;
	_class = g_pMono->FindClass("mscorlib","System","Array");
	return (_class != NULL);
}

CSYS_Array* CSYS_Array::CreateInstance( CSYS_Type *pType, int length )
{
	static CMethod* _pfn = NULL;
	if (!_GetClass()) return NULL;
	if (!_pfn) _pfn = _class->FindMethod("CreateInstance(System.Type,System.Int32)");
	if (!_pfn) return NULL;
	void* agrs[] = {pType, &length};
	return (CSYS_Array*)_pfn->Invoke(NULL, agrs);
}

void CSYS_Array::SetValue( CSYS_Object* pObj, int index )
{
	static CMethod* _pfn = NULL;
	if (!_GetClass()) return;
	if (!_pfn) _pfn = _class->FindMethod("SetValue(System.Object,System.Int32)");
	if (!_pfn) return;
	void* agrs[] = {pObj, &index};
	_pfn->Invoke(this, agrs);
}

CSYS_Object* CSYS_Array::GetValue( int index )
{
	static CMethod* _pfn = NULL;
	if (!_GetClass()) return NULL;
	if (!_pfn) _pfn = _class->FindMethod("GetValue(System.Int32)");
	if (!_pfn) return NULL;
	void* agrs[] = {&index};
	return (CSYS_Object*)_pfn->Invoke(this, agrs);
}

int CSYS_Array::get_Length()
{	
	static CMethod* _pfn = NULL;
	if (!_GetClass()) return 0;
	if (!_pfn) _pfn = _class->GetMethod("get_Length");
	if (!_pfn) return 0;
	CMonoObject* pValue = _pfn->Invoke(this);
	if(!pValue) return 0;
	return (int)pValue->GetUInt();
}

CSYS_TypeEx::CSYS_TypeEx( void )
{

}

CSYS_TypeEx::~CSYS_TypeEx( void )
{
	
}

CSYS_Object* CSYS_TypeEx::get_EmptyTypes()
{
	static CField* pfield = NULL;
	if (!pfield) pfield = g_pMono->GetField("mscorlib","System","Type","EmptyTypes");
	if (!pfield) return NULL;
	return (CSYS_Object*)pfield->GetValueObject();
}

CSYS_Type* CSYS_TypeEx::MakeGenericType( CSYS_Type *pGenericTypeDef, CSYS_Array* pGenericTypeParams )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->FindMethod("mscorlib","System","Type","MakeGenericType(System.Type,System.Type[])");
	if (!pfn) return NULL;
	void* agrs[] = {pGenericTypeDef, pGenericTypeParams};
	return (CSYS_Type*)pfn->Invoke(NULL, agrs);
}

CSYS_Object* Activator::CreateInstance( CSYS_Type *pType )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->FindMethod("mscorlib","System","Activator","CreateInstance(System.Type)");
	if (!pfn) return NULL;
	void* agrs[] = {pType};
	return (CSYS_Object*)pfn->Invoke(NULL ,agrs);
}

CSYS_Object * CSYS_ListEx::get_Item( int index )
{
	CMethod* pfn = NULL;
	CClass* pInflated_Class = g_pMono->object_get_class((CMonoObject*)this);
	if(!pInflated_Class) return 0;
	if (!pfn) pfn = pInflated_Class->GetMethod("get_Item");
	if (!pfn) return NULL;
	void* agrs[] = {&index};
	return (CSYS_Object*)pfn->Invoke(this ,agrs);
}


int CSYS_ListEx::get_Count()
{
	CMethod* pfn = NULL;
	CClass* pInflated_Class = g_pMono->object_get_class((CMonoObject*)this);
	//LOGA_DEBUG("pInflated_Class %p",pInflated_Class);
	if(!pInflated_Class) return 0;
	if (!pfn) pfn = pInflated_Class->GetMethod("get_Count");
	if (!pfn) return 0;
	CMonoObject* pValue = pfn->Invoke(this);
	return (int)pValue->GetUInt();
}

void CSYS_ListEx::Add( CSYS_Object *pObj )
{
	 CMethod* pfn = NULL;
	CClass* pInflated_Class = g_pMono->object_get_class((CMonoObject*)this);
	//LOGA_DEBUG("pInflated_Class %p",pInflated_Class);
	if(!pInflated_Class) return;
	if (!pfn) pfn = pInflated_Class->GetMethod("Add");
	if (!pfn) return;
	void * agrs[] = {pObj};
	pfn->Invoke(this, agrs);	
}

void CSYS_ListEx::Add_UInt64( ULONGLONG value )
{
	 CMethod* pfn = NULL;
	CClass* pInflated_Class = g_pMono->object_get_class((CMonoObject*)this);
	//LOGA_DEBUG("pInflated_Class %p",pInflated_Class);
	if(!pInflated_Class) return;
	if (!pfn) pfn = pInflated_Class->GetMethod("Add");
	if (!pfn) return;
	void * agrs[] = {&value};
	LOG_WRITE("Add_UInt64(%08X)", value);
	pfn->Invoke(this, agrs);
}


#pragma endregion System_Collections_Generic

CTowerSweepResult::CTowerSweepResult( void )
{

}

CTowerSweepResult::~CTowerSweepResult( void )
{

}

CTowerSweepResult * CTowerSweepResult::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TowerSweepResult","Instance");
	if (!pfn) return NULL;
	return (CTowerSweepResult*)pfn->Invoke();
}

void CTowerSweepResult::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TowerSweepResult","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CImmortalityViewLogic::CImmortalityViewLogic( void )
{

}

CImmortalityViewLogic::~CImmortalityViewLogic( void )
{

}

CImmortalityViewLogic * CImmortalityViewLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityViewLogic","Instance");
	if (!pfn) return NULL;
	return (CImmortalityViewLogic*)pfn->Invoke();
}

CSYS_List * CImmortalityViewLogic::m_ResourceWayItemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityViewLogic","m_ResourceWayItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CSYS_Array * CImmortalityViewLogic::m_BottomnImmortalityButtons()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityViewLogic","m_BottomnImmortalityButtons");
	if (!pField) return NULL;
	return (CSYS_Array*)pField->GetValueObject(this);
}

CImmortalityActivityButton * CImmortalityViewLogic::m_CurSelectActivityButton()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityViewLogic","m_CurSelectActivityButton");
	if (!pField) return NULL;
	return (CImmortalityActivityButton*)pField->GetValueObject(this);
}

void CImmortalityViewLogic::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityViewLogic","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CImmortalityActivityButton::CImmortalityActivityButton( void )
{

}

CImmortalityActivityButton::~CImmortalityActivityButton( void )
{

}

BOOL CImmortalityActivityButton::get_ImmortalityActivityActivate()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityActivityButton","get_ImmortalityActivityActivate");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CImmortalityActivityButton::get_UnAcceptReward()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityActivityButton","get_UnAcceptReward");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

void CImmortalityActivityButton::OnClickActivityButton()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityActivityButton","OnClickActivityButton");
	if (!pfn) return;
	pfn->Invoke(this);
}

CImmortalityWayItem::CImmortalityWayItem( void )
{

}

CImmortalityWayItem::~CImmortalityWayItem( void )
{

}

BOOL CImmortalityWayItem::m_bActivate()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityWayItem","m_bActivate");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

void CImmortalityWayItem::OnClickAcceptBtn()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityWayItem","OnClickAcceptBtn");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUE_GameObject * CImmortalityWayItem::m_AccpetGameObject()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ImmortalityWayItem","m_AccpetGameObject");
	if (!pField) return NULL;
	return (CUE_GameObject*)pField->GetValueObject(this);
}

CUISprite::CUISprite( void )
{

}

CUISprite::~CUISprite( void )
{

}

CStdStringU CUISprite::mSpriteName()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UISprite","mSpriteName");
	if (!pField) return CStdStringU("");
	CSYS_String* pStr = (CSYS_String*)pField->GetValueObject(this);
	if (!pStr) return CStdStringU(u"");
	return CStdStringU(pStr->GetText());
}

BOOL CUISprite::mFillCenter()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UISprite","mFillCenter");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

BOOL CUISprite::mSpriteSet()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UISprite","mSpriteSet");
	if (!pField) return FALSE;
	BYTE value = 0;
	pField->GetValue((CMonoObject*)this,&value);
	return (value == 1);
}

CUISprite * CUISprite::mSprite()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UISprite","mSprite");
	if (!pField) return NULL;
	return (CUISprite *)pField->GetValueObject(this);
}

CUE_Transform * CUISprite::get_TransformUIRect()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIRect","mTrans");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

CLimitActivityYLTXItem::CLimitActivityYLTXItem( void )
{

}

CLimitActivityYLTXItem::~CLimitActivityYLTXItem( void )
{

}

CStdStringU CLimitActivityYLTXItem::m_NpcNumLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","LimitActivityYLTXItem","m_NpcNumLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}

void CLimitActivityYLTXItem::OnClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","LimitActivityYLTXItem","OnClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CStdStringU CLimitActivityYLTXItem::m_SceneLabel()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","LimitActivityYLTXItem","m_SceneLabel");
	if (!pField) return CStdStringU("");
	CUILabel* pLabel = (CUILabel*)pField->GetValueObject(this);
	if (!pLabel) return CStdStringU(u"");
	return CStdStringU(pLabel->get_text()->GetText());
}



CRecoverySettingLogic::CRecoverySettingLogic( void )
{

}

CRecoverySettingLogic::~CRecoverySettingLogic( void )
{

}

CRecoverySettingLogic * CRecoverySettingLogic::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RecoverySettingLogic","Instance");
	if (!pfn) return NULL;
	return (CRecoverySettingLogic*)pfn->Invoke();
}

CSYS_Array * CRecoverySettingLogic::m_HPFoodList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","RecoverySettingLogic","m_HPFoodList");
	if (!pField) return NULL;
	return (CSYS_Array *)pField->GetValueObject(this);
}

CSYS_Array * CRecoverySettingLogic::m_MPFoodList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","RecoverySettingLogic","m_MPFoodList");
	if (!pField) return NULL;
	return (CSYS_Array *)pField->GetValueObject(this);
}

void CRecoverySettingLogic::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RecoverySettingLogic","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CKnapsackController::CKnapsackController( void )
{

}

CKnapsackController::~CKnapsackController( void )
{

}

CKnapsackController * CKnapsackController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackController","Instance");
	if (!pfn)return NULL;
	return (CKnapsackController*)pfn->Invoke();
}

void CKnapsackController::OnClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","KnapsackController","OnClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIActivityBuyback::CUIActivityBuyback( void )
{

}

CUIActivityBuyback::~CUIActivityBuyback( void )
{

}

CUIActivityBuyback * CUIActivityBuyback::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIActivityBuyback","Instance");
	if (!pfn)return NULL;
	return (CUIActivityBuyback*)pfn->Invoke();
}

CItemTipsController::CItemTipsController( void )
{

}

CItemTipsController::~CItemTipsController( void )
{

}

CGameItem * CItemTipsController::m_SeletItem()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","ItemTipsController","m_curItem");
	if (!pField) return NULL;
	return (CGameItem *)pField->GetValueObject();
}

CItemTipsController * CItemTipsController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ItemTipsController","Instance");
	if (!pfn)return NULL;
	return (CItemTipsController*)pfn->Invoke();
}

CDeviceStatusWindow::CDeviceStatusWindow( void )
{

}

CDeviceStatusWindow::~CDeviceStatusWindow( void )
{

}

CDeviceStatusWindow * CDeviceStatusWindow::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DeviceStatusWindow","Instance");
	if (!pfn)return NULL;
	return (CDeviceStatusWindow*)pfn->Invoke();
}

int CDeviceStatusWindow::get_Hour()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","DeviceStatusWindow","hour");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

int CDeviceStatusWindow::get_Minute()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","DeviceStatusWindow","minute");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

CSmallMapItem::CSmallMapItem( void )
{

}

CSmallMapItem::~CSmallMapItem( void )
{

}

int CSmallMapItem::m_nSceneId()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","SmallMapItem","m_nSceneId");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

CNPCDialog::CNPCDialog( void )
{

}

CNPCDialog::~CNPCDialog( void )
{

}

void CNPCDialog::ShowDialog()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NPCDialog","ShowDialog");
	if (!pfn) return;
	pfn->Invoke(this);
}

BOOL CNPCDialog::ShowMission()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NPCDialog","ShowMission");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

BOOL CNPCDialog::ShowOption()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","NPCDialog","ShowOption");
	if (!pfn) return FALSE;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return FALSE;
	return (pObj->GetByte() == 1);
}

CUIScrollExchangeController::CUIScrollExchangeController( void )
{

}

CUIScrollExchangeController::~CUIScrollExchangeController( void )
{

}

CUIScrollExchangeController* CUIScrollExchangeController::Instance()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIScrollExchangeController","Instance");
	if (!pfn) return NULL;
	return (CUIScrollExchangeController*)pfn->Invoke();
}

void CUIScrollExchangeController::OnClickCloseBtn()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIScrollExchangeController","OnClickCloseBtn");
	if (!pfn) return;
	pfn->Invoke(this);
}

COptionLogic::COptionLogic( void )
{

}

COptionLogic::~COptionLogic( void )
{

}

void COptionLogic::GuildConvoyFinish()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","OptionLogic","GuildConvoyFinish");
	if (!pfn) return;
	pfn->Invoke();
}

void COptionLogic::GuildConvoyTransNext()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","OptionLogic","GuildConvoyTransNext");
	if (!pfn) return;
	pfn->Invoke();
}

CBrotherhood::CBrotherhood( void )
{

}

CBrotherhood::~CBrotherhood( void )
{
	
}



CSYS_List * CBrotherhood::m_BrotherhoodMemberList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","Brotherhood","m_BrotherhoodMemberList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CBrotherhoodMember::CBrotherhoodMember( void )
{

}

CBrotherhoodMember::~CBrotherhoodMember( void )
{

}
ULONGLONG CBrotherhoodMember::get_BrotherhoodGuid()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BrotherhoodMember","get_Guid");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (ULONGLONG)pObj->GetUInt64();
}

CStdStringU CBrotherhoodMember::get_MemberName()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","BrotherhoodMember","get_MemberName");
	if (!pfn) return u"";
	CSYS_String* pstr = (CSYS_String*)pfn->Invoke(this);
	return (CStdStringU)pstr->GetText();
}

CFairyPack::CFairyPack( void )
{

}

CFairyPack::~CFairyPack( void )
{

}

int CFairyPack::get_DefaultSize()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"Games.Fairy","FairyPack","DEFAULT_SIZE");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject();
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

int CFairyPack::GetFairyCount()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"Games.Fairy","FairyPack","GetFairyCount");
	if (!pfn)return 0;
	CMonoObject *pObj = (CMonoObject *)pfn->Invoke(this);
	return (int)pObj->GetUInt();
}

CFuLiRootController * CFuLiRootController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FuLiRootController","Instance");
	if (!pfn)return NULL;
	return (CFuLiRootController*)pfn->Invoke();
}

void CFuLiRootController::Close()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FuLiRootController","Close");
	if (!pfn) return;
	pfn->Invoke(this);
}

CRoleViewWindow * CRoleViewWindow::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleViewWindow","Instance");
	if (!pfn)return NULL;
	return (CRoleViewWindow*)pfn->Invoke();
}

void CRoleViewWindow::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RoleViewWindow","CloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}

CMisInfoController * CMisInfoController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MisInfoController","Instance");
	if (!pfn)return NULL;
	return (CMisInfoController*)pfn->Invoke();
}

void CMisInfoController::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MisInfoController","CloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}


CFirstCharge * CFirstCharge::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirstCharge","Instance");
	if (!pfn)return NULL;
	return (CFirstCharge*)pfn->Invoke();
}

void CFirstCharge::CloseClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","FirstCharge","CloseClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CTeHuiRootController * CTeHuiRootController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeHuiRootController","Instance");
	if (!pfn)return NULL;
	return (CTeHuiRootController*)pfn->Invoke();
}

void CTeHuiRootController::Close()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TeHuiRootController","Close");
	if (!pfn) return;
	pfn->Invoke(this);
}

CShoppingMallController * CShoppingMallController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ShoppingMallController","Instance");
	if (!pfn)return NULL;
	return (CShoppingMallController*)pfn->Invoke();
}

void CShoppingMallController::Close()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ShoppingMallController","Close");
	if (!pfn) return;
	pfn->Invoke(this);
}

CGrowWayViewLogic * CGrowWayViewLogic::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GrowWayViewLogic","Instance");
	if (!pfn)return NULL;
	return (CGrowWayViewLogic*)pfn->Invoke();
}

void CGrowWayViewLogic::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GrowWayViewLogic","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}


CArtifactProveController * CArtifactProveController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ArtifactProveController","Instance");
	if (!pfn)return NULL;
	return (CArtifactProveController*)pfn->Invoke();
}

void CArtifactProveController::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ArtifactProveController","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CActivityRootLogic * CActivityRootLogic::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityRootLogic","Instance");
	if (!pfn)return NULL;
	return (CActivityRootLogic*)pfn->Invoke();
}

void CActivityRootLogic::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ActivityRootLogic","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CEquipBuildWindowController * CEquipBuildWindowController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","EquipBuildWindowController","Instance");
	if (!pfn)return NULL;
	return (CEquipBuildWindowController*)pfn->Invoke();
}

void CEquipBuildWindowController::OnClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","EquipBuildWindowController","OnClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CSkillRootController * CSkillRootController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SkillRootController","Instance");
	if (!pfn)return NULL;
	return (CSkillRootController*)pfn->Invoke();
}

void CSkillRootController::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","SkillRootController","CloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}

CGuildController * CGuildController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildController","Instance");
	if (!pfn)return NULL;
	return (CGuildController*)pfn->Invoke();
}

void CGuildController::OnClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","GuildController","OnClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CAchievementControl * CAchievementControl::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AchievementControl","Instance");
	if (!pfn)return NULL;
	return (CAchievementControl*)pfn->Invoke();
}

void CAchievementControl::OnClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","AchievementControl","OnClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIXiuZhenController * CUIXiuZhenController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIXiuZhenController","Instance");
	if (!pfn)return NULL;
	return (CUIXiuZhenController*)pfn->Invoke();
}

void CUIXiuZhenController::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIXiuZhenController","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIServant * CUIServant::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIServant","Instance");
	if (!pfn)return NULL;
	return (CUIServant*)pfn->Invoke();
}

void CUIServant::ClickCloseButton()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIServant","ClickCloseButton");
	if (!pfn) return;
	pfn->Invoke(this);
}

CMentorRootController * CMentorRootController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MentorRootController","Instance");
	if (!pfn)return NULL;
	return (CMentorRootController*)pfn->Invoke();
}

void CMentorRootController::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","MentorRootController","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIFairy * CUIFairy::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIFairy","Instance");
	if (!pfn)return NULL;
	return (CUIFairy*)pfn->Invoke();
}

void CUIFairy::ClickCloseButton()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIFairy","ClickCloseButton");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIPetRoot * CUIPetRoot::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIPetRoot","Instance");
	if (!pfn)return NULL;
	return (CUIPetRoot*)pfn->Invoke();
}

void CUIPetRoot::OnClickClose()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIPetRoot","OnClickClose");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CRankWindow::OnCloseClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RankWindow","OnCloseClick");
	if (!pfn) return;
	pfn->Invoke(this);
}

CRankWindow * CRankWindow::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RankWindow","Instance");
	if (!pfn)return NULL;
	return (CRankWindow*)pfn->Invoke();
}

CTianshuRootController * CTianshuRootController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TianshuRootController","Instance");
	if (!pfn)return NULL;
	return (CTianshuRootController*)pfn->Invoke();
}

void CTianshuRootController::Close()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TianshuRootController","Close");
	if (!pfn) return;
	pfn->Invoke(this);
}

CExamController * CExamController::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ExamController","Instance");
	if (!pfn)return NULL;
	return (CExamController*)pfn->Invoke();
}

void CExamController::OnClickCloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","ExamController","OnClickCloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}

CPopManyCharMenu * CPopManyCharMenu::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PopManyCharMenu","Instance");
	if (!pfn)return NULL;
	return (CPopManyCharMenu*)pfn->Invoke();
}

void CPopManyCharMenu::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","PopManyCharMenu","CloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}

CDomainXuanZhanMap * CDomainXuanZhanMap::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DomainXuanZhanMap","Instance");
	if (!pfn)return NULL;
	return (CDomainXuanZhanMap*)pfn->Invoke();
}

void CDomainXuanZhanMap::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","DomainXuanZhanMap","CloseUI");
	if (!pfn) return;
	pfn->Invoke();
}

CUE_Transform * CUIRect::get_transform()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","UIRect","mTrans");
	if (!pField) return NULL;
	return (CUE_Transform*)pField->GetValueObject(this);
}

void CRecoveryFoodItem::OnClickitemResource()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","RecoveryFoodItem","OnClickitemResource");
	if (!pfn) return;
	pfn->Invoke(this);
}

CUIArchaeologyPoint * CUIArchaeologyPoint::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyPoint","Instance");
	if (!pfn)return NULL;
	return (CUIArchaeologyPoint*)pfn->Invoke();
}

void CUIArchaeologyPoint::OnClickAnalysisInfo()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyPoint","OnClickAnalysisInfo");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CUIArchaeologyPoint::OnClickArchaeology()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyPoint","OnClickArchaeology");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CUIArchaeologyPoint::OnClickCollectClue()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyPoint","OnClickCollectClue");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CUIArchaeologyPoint::OnClickSellClue()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyPoint","OnClickSellClue");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CUIArchaeologyPoint::OnCollectInfo()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyPoint","OnCollectInfo");
	if (!pfn) return;
	pfn->Invoke(this);
}

int CUIArchaeologyClue::GetNo()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyClue","GetNo");
	if (!pfn) return -1;
	CMonoObject* pObj = pfn->Invoke(this);
	if (!pObj) return -1;
	return (int)pObj->GetUInt();
}

void CUIArchaeologyClue::OnClickItem()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","UIArchaeologyClue","OnClickItem");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CTabButton::OnTabClick()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","TabButton","OnTabClick");
	if (!pfn) return;
	pfn->Invoke(this);
}



CSYS_List * CStallSell::m_StallSellListItemList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallSell","m_StallSellListItemList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

CSYS_List * CStallSell::m_ItemPackList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallSell","m_ItemPackList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

void CStallSell::ConfirmSellItem( CGameItem *pItem )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallSell","ConfirmSellItem");
	if (!pfn) return;
	void* agrs[] = {pItem};
	pfn->Invoke(this ,agrs);
}

CStallSell * CStallSell::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallSell","Instance");
	if (!pfn)return NULL;
	return (CStallSell*)pfn->Invoke();
}



CStallMultiSellConfirm::CStallMultiSellConfirm( void )
{

}

CStallMultiSellConfirm::~CStallMultiSellConfirm( void )
{

}

CStallMultiSellConfirm * CStallMultiSellConfirm::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","Instance");
	if (!pfn)return NULL;
	return (CStallMultiSellConfirm*)pfn->Invoke();
}

int CStallMultiSellConfirm::m_StepIdx()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","m_StepIdx");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

void CStallMultiSellConfirm::OnInputCountOver( int iNum )
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","OnInputCountOver");
	if (!pfn) return;
	void* agrs[] = {&iNum};
	pfn->Invoke(this ,agrs);
}

void CStallMultiSellConfirm::SellItem()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","SellItem");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CStallMultiSellConfirm::AddMoneyByStep()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","AddMoneyByStep");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CStallMultiSellConfirm::MinusMoneyByStep()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","MinusMoneyByStep");
	if (!pfn) return;
	pfn->Invoke(this);
}

CKnapsackItem * CStallMultiSellConfirm::m_Item()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","m_Item");
	if (!pField) return NULL;
	return (CKnapsackItem*)pField->GetValueObject(this);
}

CSYS_List * CStallMultiSellConfirm::m_LeftDataList()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","m_LeftDataList");
	if (!pField) return NULL;
	return (CSYS_List*)pField->GetValueObject(this);
}

int CStallMultiSellConfirm::m_NowMoney()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","m_NowMoney");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

void CStallMultiSellConfirm::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallMultiSellConfirm","CloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}

CStallSingleSellConfirm::CStallSingleSellConfirm( void )
{

}


CStallSingleSellConfirm::~CStallSingleSellConfirm( void )
{

}

CStallSingleSellConfirm * CStallSingleSellConfirm::Instance()
{
	static CMethod* pfn= NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","Instance");
	if (!pfn)return NULL;
	return (CStallSingleSellConfirm*)pfn->Invoke();
}

int CStallSingleSellConfirm::m_StepCount()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","m_StepCount");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}


void CStallSingleSellConfirm::SellItem()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","SellItem");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CStallSingleSellConfirm::AddMoneyByStep()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","AddMoneyByStep");
	if (!pfn) return;
	pfn->Invoke(this);
}

void CStallSingleSellConfirm::MinusMoneyByStep()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","MinusMoneyByStep");
	if (!pfn) return;
	pfn->Invoke(this);
}

CKnapsackItem * CStallSingleSellConfirm::m_Item()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","m_Item");
	if (!pField) return NULL;
	return (CKnapsackItem*)pField->GetValueObject(this);
}

int CStallSingleSellConfirm::m_NowMoney()
{
	static CField* pField = NULL;
	if (!pField) pField = g_pMono->GetField(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","m_NowMoney");
	if (!pField) return -1;
	CMonoObject *pValue = pField->GetValueObject(this);
	if(!pValue) return -1;
	return (int)pValue->GetUInt();
}

void CStallSingleSellConfirm::CloseWindow()
{
	static CMethod* pfn = NULL;
	if (!pfn) pfn = g_pMono->GetMethod(IMAGE_ASSEMBLY_CSHARP,"","StallSingleSellConfirm","CloseWindow");
	if (!pfn) return;
	pfn->Invoke(this);
}
