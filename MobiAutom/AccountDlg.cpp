// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "AccountDlg.h"
#include "LoginAddServerDlg.h"
#include "LoginAddAccount.h"
#include "LoginAddRoleDlg.h"
// CAccountDlg dialog

IMPLEMENT_DYNAMIC(CAccountDlg, CVIEChildDlg)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CVIEChildDlg(CAccountDlg::IDD, pParent)
{

}

CAccountDlg::~CAccountDlg()
{
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEChildDlg::DoDataExchange(pDX);


	//DDX_Control(pDX,IDC_COMBO_SERVERNAME, m_cboServername);
	DDX_Control(pDX, IDC_TREE_ACCOUNT , m_treeAccount);
	
}


BEGIN_MESSAGE_MAP(CAccountDlg, CVIEChildDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ACCOUNT, &CAccountDlg::OnTvnSelchangedTreeAccount)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ACCOUNT_ADDACCOUNT, &CAccountDlg::OnAccountAddaccount)
	ON_COMMAND(ID_ACCOUNT_EDITACCOUNT, &CAccountDlg::OnAccountEditAccount)
	ON_COMMAND(ID_ACCOUNT_DELETE, &CAccountDlg::OnAccountDelete)
	ON_COMMAND(ID_ACCOUNT_ADDSERVER, &CAccountDlg::OnAccountAddserver)
	ON_COMMAND(ID_ACCOUNT_NEWSERVER, &CAccountDlg::OnAccountAddserver)
	ON_COMMAND(ID_ACCOUNT_REMOVESERVER, &CAccountDlg::OnRemoveServer)
	
	ON_COMMAND(ID_ROLE_NEWROLE, &CAccountDlg::OnAccountAddRole)//
	ON_COMMAND(ID_ROLE_EDITROLE, &CAccountDlg::OnEditRole)
	ON_COMMAND(ID_ACCOUNT_REMOVEROLE, &CAccountDlg::OnRemoveRole)
	
	ON_COMMAND(ID_ACCOUNT_ADDROLE, &CAccountDlg::OnAccountAddRole)
	ON_BN_CLICKED(IDC_BUTTON_SAVEACCOUNT, &CAccountDlg::OnBnClickedButtonSaveaccount)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CAccountDlg::OnBnClickedButtonBack)
	ON_COMMAND(ID_ROLE_SELECT, &CAccountDlg::OnRoleSelect)
END_MESSAGE_MAP()



BOOL CAccountDlg::OnInitDialog()
{
	CVIEChildDlg::OnInitDialog();
	m_pRoleSelected = NULL;
	m_pServerSelected = NULL;
	m_pAccountSelected = NULL;
	
	m_ImageList.Create(16, 16, ILC_COLOR32, 10, 10);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_ACCOUNT));		//0
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_EMAIL));			//1
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_SERVER));		//2
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CHARACTER));		//3
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_PASSWORD));		//4
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_INFO));			//5

	m_treeAccount.SetImageList(&m_ImageList, TVSIL_NORMAL);
	m_treeAccount.InsertColumn(0, L"Tài khoản game", 0, 115);
	m_treeAccount.InsertColumn(1, L"Thông tin", 0, 115);

	
	m_mnuAccount.LoadMenu(IDR_MENU_ACCOUNT);
	CVIEMenu* menuAccount = m_mnuAccount.GetSubMenu(0);

	menuAccount->SetMenuItemIcon(0,IDI_ICON_ACCOUNT,TRUE);
	menuAccount->SetMenuItemIcon(1,IDI_ICON_EDIT,TRUE);
	menuAccount->SetMenuItemIcon(2,IDI_ICON_REMOVE,TRUE);
	menuAccount->SetMenuItemIcon(4,IDI_ICON_SERVER,TRUE);
	
	m_mnuServer.LoadMenu(IDR_MENU_SERVER);
	CVIEMenu* menuServer = m_mnuServer.GetSubMenu(0);
	menuServer->SetMenuItemIcon(0,IDI_ICON_SERVER,TRUE);
	menuServer->SetMenuItemIcon(1,IDI_ICON_REMOVE,TRUE);
	menuServer->SetMenuItemIcon(3,IDI_ICON_CHARACTER,TRUE);

	m_mnuRole.LoadMenu(IDR_MENU_ROLE);
	CVIEMenu* menuRole = m_mnuRole.GetSubMenu(0);
	menuRole->SetMenuItemIcon(0,IDI_ICON_CHARACTER,TRUE);
	menuRole->SetMenuItemIcon(1,IDI_ICON_EDIT,TRUE);
	menuRole->SetMenuItemIcon(2,IDI_ICON_REMOVE,TRUE);

	return TRUE;
}
void CAccountDlg::UpdateTree(){
	LOGA_DEBUG("...");
	m_treeAccount.DeleteAllItems();
	HTREEITEM hItem,hParent = TVI_ROOT;
	CPtrList* lstAccount = &g_pAutoManager->m_AccountList2;
	for(POSITION pos = lstAccount->GetHeadPosition(); pos != NULL;){
		CGameAccount *pAcc = (CGameAccount *)lstAccount->GetNext(pos);
		hParent =TVI_ROOT;
		hItem = m_treeAccount.InsertItem(L"T.Khoản",0,0,hParent);
		m_treeAccount.SetItemText(hItem,1,CUtils::_A2W(pAcc->publisherAccount.czUsername));
	
		pAcc->hItem = hItem;
		//LOGW_INFO(L"pAcc->hItem [%08x]",pAcc->hItem);

		hParent = hItem;

		for(POSITION posServer = pAcc->lstServer.GetHeadPosition(); posServer != NULL;){
			CServerAccount *pServer = (CServerAccount *)pAcc->lstServer.GetNext(posServer);
			CString szServer;
			szServer.Format(L"S%d",pServer->iServer);
			hItem = m_treeAccount.InsertItem(L"Server",2,2,hParent);
			m_treeAccount.SetItemText(hItem,1,szServer.GetBuffer());

			//
			pServer->hItem = hItem;

			HTREEITEM hParentServer  = hItem;
			for(POSITION posRole = pServer->lstRole.GetHeadPosition(); posRole != NULL;){
				CRoleAccount *pRole = (CRoleAccount *)pServer->lstRole.GetNext(posRole);
				hItem = m_treeAccount.InsertItem(L"N.Vật",3,3,hParentServer);
				m_treeAccount.SetItemText(hItem,1,CUtils::_A2W(pRole->czRoleName));
				pRole->hItem = hItem;
				//LOGA_INFO("pRole->bRunning %d pRole->bFinished %d",pRole->bRunning,pRole->bFinished);

				if(pRole->bFinished)
					m_treeAccount.SetItemBkColor(hItem, 0, RGB(103, 163, 198));
				else if(pRole->bRunning)
					m_treeAccount.SetItemBkColor(hItem, 0, RGB(143, 198, 103));
			}

		}

	}
	/*
	if(m_pRoleSelected){
		m_treeAccount.Expand(m_pRoleSelected->hItem,TVE_EXPAND);
		m_treeAccount.EnsureVisible(m_pRoleSelected->hItem);
	}else {
		if(m_pServerSelected){
			m_treeAccount.Expand(m_pServerSelected->hItem,TVE_EXPAND);
			m_treeAccount.EnsureVisible(m_pServerSelected->hItem);
		}
		else {
			if(m_pAccountSelected){
				m_treeAccount.Expand(m_pAccountSelected->hItem,TVE_EXPAND);
				//m_treeAccount.EnsureVisible(m_pAccountSelected->hItem);
			}

		}
	}
	*/
}

void CAccountDlg::UpdateControls(CGameInfo* pGame){
	if(!pGame) return;
	LOGA_DEBUG("UpdateControls...");
	UpdateTree();
	//UpdateList();
	

}




void CAccountDlg::OnTvnSelchangedTreeAccount(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	HTREEITEM hItemServer = hItem;
	HTREEITEM hItemAccount = hItem;

	//LOGA_DEBUG("hItem %08x",hItem);
	if(!hItem)   return;
	CRoleAccount* pRole  = g_pAutoManager->m_AccountList2.GetRoleByTreeItem(hItem);
	m_pRoleSelected = pRole;
	//LOGA_DEBUG("pRole %08x",pRole);
	if(m_pRoleSelected) hItemServer = m_treeAccount.GetParentItem(hItem);

	CServerAccount* pServer  = g_pAutoManager->m_AccountList2.GetServerByTreeItem(hItemServer);
	m_pServerSelected = pServer;
	if(m_pServerSelected){
		hItemAccount = m_treeAccount.GetParentItem(hItemServer);
	}

	CGameAccount* pAccount  = g_pAutoManager->m_AccountList2.GetAccountByTreeItem(hItemAccount);
	m_pAccountSelected = pAccount;
	
}

void CAccountDlg::OnAccountAddserver()
{
	LOGA_DEBUG("%08x m_pAccountSelected",m_pAccountSelected);
	if(m_pAccountSelected){
		CLoginAddServerDlg* pDlg = new CLoginAddServerDlg();
		if(pDlg->DoModal() == IDOK){
			UpdateTree();
		}	
		delete pDlg;
	}
}
void CAccountDlg::OnAccountAddaccount()
{
	CLoginAddAccount* pDlg = new CLoginAddAccount(NULL, ACCOUNTFORM_MODE_ADD);
	if(pDlg->DoModal() == IDOK){
		UpdateTree();
	}	
	delete pDlg;
}

void CAccountDlg::OnAccountEditAccount()
{
	CLoginAddAccount* pDlg = new CLoginAddAccount(NULL, ACCOUNTFORM_MODE_EDIT);
	if(pDlg->DoModal() == IDOK){
		UpdateTree();
	}	
	delete pDlg;
}

void CAccountDlg::OnAccountAddRole()
{
	CLoginAddRoleDlg* pDlg = new CLoginAddRoleDlg(NULL, ADDROLE_MODE_ADD);
	if(pDlg->DoModal() == IDOK){
		UpdateTree();
	}	
	delete pDlg;
}
void CAccountDlg::OnContextMenu(CWnd* pWnd, CPoint pt)
{
	if (pWnd != &m_treeAccount) return;
	
	if(m_pRoleSelected){
		CVIEMenu *pMenuRole = m_mnuRole.GetSubMenu(0);
		LogWriteA(" [%X]pMenuServer pt(%d,%d)",pMenuRole,pt.x,pt.y);
		if (!pMenuRole) return;
		
		CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
		if(pGame){
			if(pGame->GetLoginTab()->iAccountMode == ACCOUNTMODE_FIXED){
				pMenuRole->EnableMenuItem(3,TRUE,TRUE);
				pMenuRole->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
				return;
			}
		}
		pMenuRole->EnableMenuItem(3,TRUE,FALSE);
		pMenuRole->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
		return;
	}

	if(m_pServerSelected){
		CVIEMenu *pMenuServer = m_mnuServer.GetSubMenu(0);
		LogWriteA(" [%X]pMenuServer pt(%d,%d)",pMenuServer,pt.x,pt.y);
		if (!pMenuServer) return;
		pMenuServer->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
		return;
	}

	if(m_pAccountSelected){
		CVIEMenu *pMenuAccount = m_mnuAccount.GetSubMenu(0);
		LogWriteA(" [%X]pMenuAccount pt(%d,%d)",pMenuAccount,pt.x,pt.y);
		if (!pMenuAccount) return;
		pMenuAccount->EnableMenuItem(0,TRUE,TRUE);
		pMenuAccount->EnableMenuItem(1,TRUE,TRUE);
		pMenuAccount->EnableMenuItem(2,TRUE,TRUE);
		pMenuAccount->EnableMenuItem(4,TRUE,TRUE);
		pMenuAccount->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
		return;
	}
	
	CVIEMenu *pMenuAccount = m_mnuAccount.GetSubMenu(0);
	LogWriteA(" [%X]pMenuAccount pt(%d,%d)",pMenuAccount,pt.x,pt.y);
	if (!pMenuAccount) return;
	pMenuAccount->EnableMenuItem(0,TRUE,TRUE);
	pMenuAccount->EnableMenuItem(1,TRUE,FALSE);
	pMenuAccount->EnableMenuItem(2,TRUE,FALSE);
	pMenuAccount->EnableMenuItem(4,TRUE,FALSE);
	pMenuAccount->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	return;
}

void CAccountDlg::OnRemoveServer()
{
	CString szMsg;
	if(m_pAccountSelected && m_pServerSelected){
		szMsg.Format(L"Xóa server S%d cùng tất cả nhân vật?", m_pServerSelected->iServer);
		if(MessageBox(szMsg, L"Delete Server", MB_YESNO) == IDYES){
			if(!m_pAccountSelected->DeleteServer(m_pServerSelected))
				LOGA_DEBUG("Xóa thất bại!");
			else  LOGA_DEBUG("Xóa thành công!");

			m_pServerSelected = NULL;
			UpdateTree();
		}
		return;
	}	
}

void CAccountDlg::OnEditRole()
{
	CLoginAddRoleDlg* pDlg = new CLoginAddRoleDlg(NULL, ADDROLE_MODE_EDIT);
	if(pDlg->DoModal() == IDOK){
		UpdateTree();
		
	}	
	delete pDlg;
}

void CAccountDlg::OnRemoveRole()
{
	CString szMsg;
	if(m_pServerSelected && m_pRoleSelected){
		szMsg.Format(L"Xóa nhân vật %s?", CUtils::_A2W(m_pRoleSelected->czRoleName));
		if(MessageBox(szMsg, L"Xóa nhân vật", MB_YESNO) == IDYES){
			if(!m_pServerSelected->DeleteRole(m_pRoleSelected))
				LOGA_DEBUG("Xóa thành công!");
			else  LOGA_DEBUG("Xóa thất bại!");

			m_pRoleSelected = NULL;
			UpdateTree();
		}
		return;
	}	

}

void CAccountDlg::OnAccountDelete()
{
	CString szMsg;
	if(m_pAccountSelected){
		szMsg.Format(L"Xóa tài khoản %s cùng tất cả server và nhân vật?",CUtils::_A2W(m_pAccountSelected->publisherAccount.czUsername));
		if(MessageBox(szMsg, L"Xóa tài khoản", MB_YESNO) == IDYES){
			if(!g_pAutoManager->m_AccountList2.DeleteAccount(m_pAccountSelected))
				LOGA_DEBUG("Xóa thành công!");
			else  LOGA_DEBUG("Xóa thất bại!");

			m_pAccountSelected = NULL;
			UpdateTree();
		}
		return;
	}
	
	
}


void CAccountDlg::OnBnClickedButtonSaveaccount()
{
	g_pAutoManager->SaveAccountList();
}

void CAccountDlg::OnBnClickedButtonBack()
{
	g_pMainDlg->m_tabMain.SwapCurrentTab(IDD_DIALOG_LOGIN_);
}

void CAccountDlg::OnRoleSelect()
{
	LOGA_DEBUG("OnRoleSelect %08X %08X %08X",m_pRoleSelected,m_pServerSelected,m_pAccountSelected);
	if(!m_pRoleSelected) return;
	if(!m_pServerSelected) return;
	if(!m_pAccountSelected) return;

	CGameInfo *pGame = g_pMainDlg->m_pGameSelected;
	if(!pGame){
		MessageBox(L"Chưa có giả lập được chọn!",L"Chọn nhân vật", MB_OK);
		return;
	}

	CString szMsg;
	szMsg.Format(L"Thiết lập thông tin đăng nhập đang chọn cho giả lập [%s]",pGame->m_czVMName);
	if(MessageBox(szMsg,L"Chọn nhân vật", MB_YESNO) == IDYES){
		LOGW_DEBUG(L"Selected this role...");
		LOGIN_ACCOUNT* pAcc = &pGame->GetLoginTab()->accountFixed;
		memcpy(&pAcc->publisherAccount, &m_pAccountSelected->publisherAccount, sizeof(PUBLISHER_ACCOUNT));
		strcpy_s(pAcc->roleLogin.czRoleName, 64, m_pRoleSelected->czRoleName);
		pAcc->roleLogin.idxPlayer = m_pRoleSelected->idxPlayer;
		pAcc->roleLogin.iServer = m_pServerSelected->iServer;
		g_pMainDlg->m_tabMain.m_LoginDlg.UpdateControls(pGame);
		memcpy(&pGame->m_loginAccount, pAcc, sizeof(LOGIN_ACCOUNT));
		OnBnClickedButtonBack();
	}	
}
