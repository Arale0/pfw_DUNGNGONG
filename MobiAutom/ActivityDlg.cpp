// ActivityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "ActivityDlg.h"


// CActivityDlg dialog

IMPLEMENT_DYNAMIC(CActivityDlg, CVIEChildDlg)

CActivityDlg::CActivityDlg(CWnd* pParent /*=NULL*/)
	: CVIEChildDlg(CActivityDlg::IDD, pParent)
{

}

CActivityDlg::~CActivityDlg()
{
}

void CActivityDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACTIVITY, m_lstCtrlActivity);
	
}


BEGIN_MESSAGE_MAP(CActivityDlg, CVIEChildDlg)
		ON_NOTIFY(LVN_EX_ITEMCHECK, IDC_LIST_ACTIVITY, &CActivityDlg::OnItemCheckListActivity)
		ON_NOTIFY(NM_CLICK, IDC_LIST_ACTIVITY, &CActivityDlg::OnNMClickListActivity)
		ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACTIVITY, &CActivityDlg::OnNMDblclkListActivity)
		ON_NOTIFY(LVN_EX_ITEMMOVE, IDC_LIST_ACTIVITY, &CActivityDlg::OnLvnActivityItemMove)
		ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ACTIVITY, &CActivityDlg::OnLvnItemchangedListActivity)
		ON_WM_CONTEXTMENU()
		ON_COMMAND(ID_ACTIVITY_RESET, &CActivityDlg::OnActivityReset)
		ON_COMMAND(ID_ACTIVITY_CHECKALL, &CActivityDlg::OnActivityCheckall)
		ON_COMMAND(ID_ACTIVITY_UNCHECKALL, &CActivityDlg::OnActivityUncheckall)
		ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ACTIVITY, &CActivityDlg::OnLvnItemchangedListActivity)
END_MESSAGE_MAP()


// CActivityDlg message handlers

BOOL CActivityDlg::OnInitDialog()
{
	CVIEChildDlg::OnInitDialog();

	m_lstCtrlActivity.InsertColumn(ACTLIST_INDEX_CONTROL, L"#", LVCFMT_LEFT, 20);
	//m_lstCtrlActivity.InsertColumn(ACTLIST_INDEX_LICENSE, TEXT("License"), LVCFMT_CENTER, 48);
	m_lstCtrlActivity.InsertColumn(ACTLIST_INDEX_NAME, TEXT("Hoạt động"), LVCFMT_LEFT, 113);
	m_lstCtrlActivity.InsertColumn(ACTLIST_INDEX_STATUS, TEXT("Trạng thái"), LVCFMT_CENTER, 70);
	m_lstCtrlActivity.InsertColumn(ACTLIST_INDEX_SETTING, TEXT(" "), LVCFMT_CENTER, 20);

	m_lstCtrlActivity.SetRowAutoBkColor(RGB(255,255,255), RGB(250, 250, 255));
	m_lstCtrlActivity.SetItemsHeight(18);
	m_lstCtrlActivity.EnableDragDropItem(TRUE);
	m_lstCtrlActivity.SetBorderColor(RGB(255,255,255));//(RGB(169,175,185));


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CActivityDlg::UpdateControls( CGameInfo* pGame )
{
	LOGA_DEBUG("UpdateControls...");
	if (!pGame) return;
	m_lstCtrlActivity.DeleteAllItems();

	ACTIVITYTAB *pActivityTab = pGame->GetActivityTab();
	if(!pActivityTab) return;

	theApp.UpdateLicenseActivityList(pGame);
	for(int i = 0; i < MAX_NUM_ACTIVITY; i++)
	{
		int iActId = pActivityTab->lstDictionary[i];
		//LogWrite(L"%d %d . [%s] [%d]",i, iActId, pActivityTab->lstActivity[iActId].szName,pActivityTab->lstActivity[iActId].iStatus);
		if(pActivityTab->lstActivity[iActId].szName[0]!=NULL)
		{
			int iIndex = m_lstCtrlActivity.InsertItem(i, L"");

			m_lstCtrlActivity.SetCheck(iIndex, BST_UNCHECKED);

			/*Kiểm tra trạng thái license theo từng chức năng*/
			if(!pGame->CheckLicenseByActivity(iActId)) {
				pActivityTab->lstActivity[iActId].bChecked = BST_UNCHECKED;
				m_lstCtrlActivity.SetItemTextColor(iIndex,ACTLIST_INDEX_NAME,RGB(255,0,0));
			}
			else m_lstCtrlActivity.SetItemTextColor(iIndex,ACTLIST_INDEX_NAME,RGB(0,0,255));

			m_lstCtrlActivity.SetCheck(iIndex, pActivityTab->lstActivity[iActId].bChecked);
			
			m_lstCtrlActivity.SetItemText(iIndex, ACTLIST_INDEX_NAME, pActivityTab->lstActivity[iActId].szName);

			switch(pActivityTab->lstActivity[iActId].iStatus)
			{
			case ast_donot:
				m_lstCtrlActivity.SetItemBkColor(iIndex, ACTLIST_INDEX_STATUS, RGB(215, 220, 234));  
				m_lstCtrlActivity.SetItemText(iIndex, ACTLIST_INDEX_STATUS, L"Chưa làm");
				break;
			case ast_doing:
				m_lstCtrlActivity.SetItemBkColor(iIndex, ACTLIST_INDEX_STATUS, RGB(143, 198, 103));
				m_lstCtrlActivity.SetItemText(iIndex, ACTLIST_INDEX_STATUS, L"Đang làm");
				
				break;
			case ast_suspend:
			case ast_waiting:
				m_lstCtrlActivity.SetItemBkColor(iIndex, ACTLIST_INDEX_STATUS, RGB(198, 158, 103));
				m_lstCtrlActivity.SetItemText(iIndex, ACTLIST_INDEX_STATUS, L"Đang chờ");
				break;
			case ast_done:
			case ast_unknown:
				m_lstCtrlActivity.SetItemBkColor(iIndex, ACTLIST_INDEX_STATUS, RGB(103, 163, 198));
				m_lstCtrlActivity.SetItemText(iIndex, ACTLIST_INDEX_STATUS, L"Hoàn thành");
				break;
			}
			if(pActivityTab->lstActivity[iActId].uIDD != NULL) m_lstCtrlActivity.SetItemIcon(iIndex, ACTLIST_INDEX_SETTING, IDI_ICON_SETTING);
		}
	}
}


void CActivityDlg::OnItemCheckListActivity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if(lpItem->iItem < 0)   return;
	CGameInfo* pGame = g_pMainDlg->m_pGameSelected;
	if (!pGame) return;
	ACTIVITYTAB* pActivityTab = pGame->GetActivityTab();
	int iActId = pActivityTab->lstDictionary[lpItem->iItem];
	if (lpItem->iSubItem == 0)
	{
		//int iChecked = m_lstCtrlActivity.GetCheck(lpItem->iItem);
		int iChecked = lpItem->uChanged;
		if(iChecked) 
		{
			/*Kiểm tra trạng thái license theo từng chức năng*/
			if(!pGame->CheckLicenseByActivity(iActId)) {
				m_lstCtrlActivity.SetCheck(lpItem->iItem, BST_UNCHECKED);
				pActivityTab->lstActivity[iActId].bChecked = BST_UNCHECKED;
				UpdateControls(pGame);
				theApp.LimitedLicenseAlert();
				return;
			}

			/*Kiểm tra các vấn đề thiết lập chức năng*/
			if(FALSE)//!CheckActivitySetting(iActId))
			{
				m_lstCtrlActivity.SetCheck(lpItem->iItem, BST_UNCHECKED);
				pActivityTab->lstActivity[iActId].bChecked = BST_UNCHECKED;
				return;
			}
		}

		pActivityTab->lstActivity[iActId].bChecked = iChecked;
		
		LOGW_INFO(L"ID=[%d] Index=[%d] Checked=[%d]", iActId, lpItem->iItem, iChecked);
	}
}
void CActivityDlg::OnNMClickListActivity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if(lpItem->iItem < 0)   return;

	CGameInfo* pGame = g_pMainDlg->m_pGameSelected;
	if (!pGame) return;

	ACTIVITYTAB* pActivityTab = pGame->GetActivityTab();

	int iActId = pActivityTab->lstDictionary[lpItem->iItem];

	//Kiểm tra click vào thiết lập
	if(lpItem->iSubItem == ACTLIST_INDEX_SETTING)
	{
		LOGW_INFO(L"pControlTab->lstActivity[%d].uIDD=%d", iActId, pActivityTab->lstActivity[iActId].uIDD);
		g_pMainDlg->m_tabMain.SwapCurrentTab(pActivityTab->lstActivity[iActId].uIDD);
		g_pMainDlg->m_tabMain.ActivateTabDialogs();
		g_pMainDlg->m_tabMain.UpdateTabDialogs(pGame);
	}
}
void CActivityDlg::OnNMDblclkListActivity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if(lpItem->iItem < 0)   return;

	CGameInfo* pGame = g_pMainDlg->m_pGameSelected;
	if (!pGame) return;

	ACTIVITYTAB* pActivityTab = pGame->GetActivityTab();

	int iActId = pActivityTab->lstDictionary[lpItem->iItem];

	//Kiểm tra click vào thiết lập
	if(lpItem->iSubItem == ACTLIST_INDEX_STATUS)
	{
		pGame->SetStatusByActivity(iActId, ast_donot);
	}
}

void CActivityDlg::OnLvnActivityItemMove( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMLVITEMMOVE pTLCIM = reinterpret_cast<LPNMLVITEMMOVE>(pNMHDR);
	*pResult = 0;

	CGameInfo* pGame = g_pMainDlg->m_pGameSelected;
	if (!pGame) return;

	ACTIVITYTAB* pActivityTab = pGame->GetActivityTab();

	int idx1 = pTLCIM->iItem;  // Vị trí cũ
	int idx2 = pTLCIM->iToIndex; // Vị trí mới

	int iTemp = pActivityTab->lstDictionary[idx1];
	if (idx1 > idx2) {
		for (int i = idx1 - 1; i >= idx2; i--) {
			pActivityTab->lstDictionary[i+1] = pActivityTab->lstDictionary[i];
		}
	}
	else {
		for(int i= idx1 + 1 ; i <= idx2; i++) {
			pActivityTab->lstDictionary[i-1] = pActivityTab->lstDictionary[i];
		}
	}
	pActivityTab->lstDictionary[idx2] = iTemp;
}

void CActivityDlg::OnLvnItemchangedListActivity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CActivityDlg::OnContextMenu( CWnd* /*pWnd*/, CPoint point )
{
	CListCtrl *pLV;
	pLV = reinterpret_cast<CListCtrl *>(GetDlgItem(IDC_LIST_ACTIVITY));
	// Find the rectangle around the control
	CRect rect;
	pLV->GetWindowRect(&rect);
	if(rect.PtInRect(point))
	{
		/*
		int pos = (int)m_lstActivity.GetFirstSelectedItemPosition();
		if(pos == 0) return;
		*/

		CMenu mnuPopup;
		mnuPopup.LoadMenuW(IDR_MENU_ACTIVITY);
		// Get a pointer to the first item of the menu
		CMenu *mnu1= mnuPopup.GetSubMenu(0);
		ASSERT(mnu1);
		if(!mnu1) 
		{
			return;
		}
		// Find out if the user right-clicked a button
		if( rect.PtInRect(point) ) // Since the user right-clicked a button, display its context menu
			mnu1->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		return;
	}
}

void CActivityDlg::OnActivityReset()
{
	CGameInfo* pGame = g_pMainDlg->m_pGameSelected;
	if(pGame == NULL) return;
	pGame->ResetActivityStatus();
}

void CActivityDlg::OnActivityCheckall()
{
	CGameInfo* pGame = g_pMainDlg->m_pGameSelected;
	if(pGame == NULL) return;
	pGame->CheckAllActivity(TRUE);
}

void CActivityDlg::OnActivityUncheckall()
{
	CGameInfo* pGame = g_pMainDlg->m_pGameSelected;
	if(pGame == NULL) return;
	pGame->CheckAllActivity(FALSE);
}
