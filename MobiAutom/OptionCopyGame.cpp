// OptionCopyGame.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "OptionCopyGame.h"

// COptionCopyGame dialog

IMPLEMENT_DYNAMIC(COptionCopyGame, CVIEDialog)

COptionCopyGame::COptionCopyGame(CWnd* pParent /*=NULL*/, CGameInfo* pGame)
	: CVIEDialog(COptionCopyGame::IDD, pParent)
{
	m_pGame = pGame;
}

COptionCopyGame::~COptionCopyGame()
{
}

void COptionCopyGame::DoDataExchange(CDataExchange* pDX)
{
	CVIEDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_GAME, m_lstGame);
	DDX_Control(pDX, IDC_CHECK_COPY_ALL, m_chkCopyAll);
	DDX_Control(pDX, IDC_CHECK_COPY_TAB_ACC, m_chkCpyTabAct);
	DDX_Control(pDX, IDC_CHECK_COPY_TEAM, m_chkCpyTabTeam);
	DDX_Control(pDX, IDC_CHECK_COPY_OPTION_TOOLS, m_chkCpyTabOption);
	DDX_Control(pDX, IDC_BUTTON_CHECKALL, m_btnSltAll);
	DDX_Control(pDX, IDC_BUTTON_UNCHECKALL, m_btnUnsltAll);
	DDX_Control(pDX, IDC_BUTTON_COPY, m_btnCopy);
	DDX_Control(pDX, IDC_STATIC_TEXT_SUCESS, m_lblNote);
}


BEGIN_MESSAGE_MAP(COptionCopyGame, CVIEDialog)
	
	ON_NOTIFY(LVN_EX_ITEMCHECK, IDC_LIST_GAME, &COptionCopyGame::OnItemCheckListGame)
	ON_BN_CLICKED(IDC_CHECK_COPY_ALL, &COptionCopyGame::OnBnClickedCheckCopyAll)
	ON_BN_CLICKED(IDC_CHECK_COPY_TAB_ACC, &COptionCopyGame::OnBnClickedCheckCopyTabAcc)
	ON_BN_CLICKED(IDC_CHECK_COPY_TEAM, &COptionCopyGame::OnBnClickedCheckCopyTeam)
	ON_BN_CLICKED(IDC_CHECK_COPY_OPTION_TOOLS, &COptionCopyGame::OnBnClickedCheckCopyOptionTools)
	ON_BN_CLICKED(IDC_BUTTON_CHECKALL, &COptionCopyGame::OnBnClickedButtonCheckall)
	ON_BN_CLICKED(IDC_BUTTON_UNCHECKALL, &COptionCopyGame::OnBnClickedButtonUncheckall)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &COptionCopyGame::OnBnClickedButtonCopy)
END_MESSAGE_MAP()


// COptionCopyGame message handlers



BOOL COptionCopyGame::OnInitDialog()
{
	CVIEDialog::OnInitDialog();
	m_lstGame.InsertColumn(TAB_INDEX_GAMECONTROL, TEXT("#"), LVCFMT_CENTER, 30);
	m_lstGame.InsertColumn(TAB_INDEX_EMULATOR, TEXT("Tên nhân vật"), 0, 180);

	m_lstGame.SetRowAutoBkColor(RGB(255, 255, 255), RGB(250, 250, 255));
	m_lstGame.SetItemsHeight(18);


	CPtrList* plstGame = g_pGameManager->GetListGame();
	int iCount = plstGame->GetCount();
	int index = 0;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		m_lstGame.InsertItem(index, L"");
		m_lstGame.SetCheck(index, FALSE);
		if(pGame->m_accountInfo.czRoleName[0] != 0)
			m_lstGame.SetItemText(index, 1, CUtils::_A2W(pGame->m_accountInfo.czRoleName));
		else if (pGame->m_czWndName[0] != 0)
			m_lstGame.SetItemText(index, 1, pGame->m_czWndName);
		else
			m_lstGame.SetItemText(index, 1, pGame->m_czVMName);
		index++;
	}
	
	m_lblNote.SetFont(L"Tahoma", 8, FALSE);
	m_lblNote.SetTextColor(RGB(255, 0, 0));
	m_lblNote.ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void COptionCopyGame::OnItemCheckListGame(NMHDR * pNMHDR, LRESULT * pResult)
{
	LPNMITEMACTIVATE lpItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if (lpItem->iItem < 0)   return;
	if (lpItem->iSubItem == 0)
	{
		
		//LOGW_INFO(L"Index=[%d] Checked=[%d]", lpItem->iItem, lpItem->uChanged);
	}
}




void COptionCopyGame::OnBnClickedCheckCopyAll()
{
	// TODO: Add your control notification handler code here
}

void COptionCopyGame::OnBnClickedCheckCopyTabAcc()
{
	// TODO: Add your control notification handler code here
}

void COptionCopyGame::OnBnClickedCheckCopyTeam()
{
	// TODO: Add your control notification handler code here
}

void COptionCopyGame::OnBnClickedCheckCopyOptionTools()
{
	// TODO: Add your control notification handler code here
}

void COptionCopyGame::OnBnClickedButtonCheckall()
{
	int iCount = m_lstGame.GetItemCount();
	for ( int i = 0; i < iCount;  i++)
	{
		m_lstGame.SetCheck(i, TRUE);
	}
}

void COptionCopyGame::OnBnClickedButtonUncheckall()
{
	int iCount = m_lstGame.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{
		m_lstGame.SetCheck(i, FALSE);
	}
}

void COptionCopyGame::OnBnClickedButtonCopy()
{
	int iCount = m_lstGame.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{

		if (m_lstGame.GetCheck(i) == 1) {
			CGameInfo* pGame = g_pGameManager->GetGameInfo(i);
			if (m_pGame != pGame) {
				if (m_chkCopyAll.GetCheck() == 1) {
					memcpy(&pGame->m_OptionTab, &m_pGame->m_OptionTab, sizeof(OPTIONTAB));
					memcpy(&pGame->m_TeamTab, &m_pGame->m_TeamTab, sizeof(TEAMTAB));
					memcpy(&pGame->m_TeamTab.teamOption, &m_pGame->m_TeamTab.teamOption, sizeof(TEAMOPTION));
					
					for(int i = 0; i < MAX_NUM_ACTIVITY; i++)
					{
						int iActId = pGame->GetActivityTab()->lstDictionary[i];
						pGame->GetActivityTab()->lstActivity[iActId].bChecked = m_pGame->GetActivityTab()->lstActivity[iActId].bChecked;
					}
			
				}

				if (m_chkCpyTabAct.GetCheck() == 1) {
					for(int i = 0; i < MAX_NUM_ACTIVITY; i++)
					{
						int iActId = pGame->GetActivityTab()->lstDictionary[i];
						pGame->GetActivityTab()->lstActivity[iActId].bChecked = m_pGame->GetActivityTab()->lstActivity[iActId].bChecked;
					}
			
				}

				if (m_chkCpyTabOption.GetCheck() == 1) memcpy(&pGame->m_OptionTab, &m_pGame->m_OptionTab, sizeof(OPTIONTAB));

				if (m_chkCpyTabTeam.GetCheck() == 1) {
					memcpy(&pGame->m_TeamTab, &m_pGame->m_TeamTab, sizeof(TEAMTAB));
					memcpy(&pGame->m_TeamTab.teamOption, &m_pGame->m_TeamTab.teamOption, sizeof(TEAMOPTION));
				}
				
				pGame->m_TeamTab.uTimeUpdate = GetTickCount();
				pGame->m_TeamTab.bSyncTeamOption = TRUE;
				pGame->m_bSyncOptionTab = TRUE;
			}
		}
	}
	m_lblNote.ShowWindow(TRUE);
	
	// TODO: Add your control notification handler code here
}
