
// vlvAutomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "mobiAutoDlg.h"
#include "VerInfo.h"
#include "OptionCopyGame.h"

#include <WinInet.h>

#pragma comment(lib, "wininet.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAutoDlg dialog




CAutoDlg::CAutoDlg(CWnd* pParent /*=NULL*/)
	: CVIEDialog(CAutoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMULATOR, m_lstEmulator);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tabMain);
	DDX_Control(pDX, IDC_BUTTON_LIC, m_btnLic);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
}

BEGIN_MESSAGE_MAP(CAutoDlg, CVIEDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_WM_CLOSE()
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(WM_MSG_EMULATOR_EVENT, OnEmulatorEvents)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EMULATOR, &CAutoDlg::OnLvnItemchangedListEmulator)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EMULATOR, &CAutoDlg::OnNMClickListEmulator)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_EMULATOR, &CAutoDlg::OnNMRClickListEmulator)
	ON_NOTIFY(LVN_EX_ITEMCHECK, IDC_LIST_EMULATOR, &CAutoDlg::OnLvnItemCheckListGame)
	ON_NOTIFY(LVN_EX_ITEMMOVE, IDC_LIST_EMULATOR, &CAutoDlg::OnLvnListGameItemMove)	
	ON_BN_CLICKED(IDC_BUTTON_LIC, &CAutoDlg::OnBnClickedButtonLic)

	ON_COMMAND(ID_GAME_REMOVE, &CAutoDlg::OnGameXoagialap)
	ON_COMMAND(ID_GAME_TURNON_ALL, &CAutoDlg::OnGameTurnOnAll)
	ON_COMMAND(ID_GAME_TURNOFF_ALL, &CAutoDlg::OnGameTurnOffAll)
	ON_COMMAND(ID_GAME_COPY_GAME, &CAutoDlg::OnGameCopyGame)
	ON_COMMAND(ID_GAME_RESET_ACTIVITY_ALL_EMULATOR, &CAutoDlg::ResetActivityAllEmulator)

	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CAutoDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CAutoDlg message handlers

BOOL CAutoDlg::OnInitDialog()
{
	CVIEDialog::OnInitDialog();

	m_bShowExpiryTime = FALSE;

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//toanbo
	//check(Arale);
	//check(HuyHoang);
	check(DungNgong);
	//check(TuanDongNat1May);
	//check(tienDung);
	//check(NguyenThach);
	//check(HoangMinhTa);
	//check(userTest);
	//check(Jim);
	//check(BiBonBa);
	//check(userFreedom);
	//check(trungNguyenTran1may);
	//check(HaiAnh);
	//check(user_TienDung);

	m_pGameSelected = NULL;

	m_lstEmulator.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP);//|LVS_EX_AUTOAUTOARRANGE
	m_lstEmulator.InsertColumn(TAB_INDEX_GAMECONTROL, TEXT("#"), 0, 21);		
	m_lstEmulator.InsertColumn(TAB_INDEX_EMULATOR, TEXT("Nhân vật"), 0, 95);
	m_lstEmulator.InsertColumn(TAB_INDEX_GAMESTATUS, TEXT("Trạng thái"), 0, 80);	
	m_lstEmulator.InsertColumn(TAB_INDEX_GAMEHIDE, TEXT("Ẩn"), LVCFMT_CENTER, 30);

	m_lstEmulator.SetRowAutoBkColor(RGB(255,255,255), RGB(255,255,255));
	m_lstEmulator.SetBorderColor(RGB(161, 178, 201));//RGB(169,175,185));
	m_lstEmulator.SetItemsHeight(18);
	m_lstEmulator.EnableDragDropItem(TRUE);

	m_btnSave.SetIcon(IDI_ICON_SAVE,17,17);
	m_btnSave.SetFlatStyle(TRUE,FALSE);
	m_btnSave.SetTextColor(RGB(	255, 0, 0));
	m_btnSave.SetBorderColor(RGB(0,128,192),RGB(255, 0, 0));
	SetToolTips(&m_btnSave, L"Luu thiết lập.");

	m_btnLic.SetWindowText(L"End task");

	
	m_tabMain.InitTabDialogs();
	m_dwStartTime_RunAuto = GetTickCount();

	int iWidthScreen = GetSystemMetrics(SM_CXSCREEN);
	int iHeightScreen = GetSystemMetrics(SM_CYSCREEN);

	CRect rc;
	GetWindowRect(&rc);
	int cx = iWidthScreen - rc.Width() - 1;
	SetWindowPos(NULL,cx,1,0,0,SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);


	CString szTitle,szVerEXE = L"";
	CFileVersionInfo version;
	if (version.Open((HINSTANCE)NULL)){
		szVerEXE.Format(L"%d.%d.%d.%d",version.GetFileVersionMajor(),version.GetFileVersionMinor(),version.GetFileVersionBuild(),version.GetFileVersionQFE());
		version.Close();
	}

	szTitle.Format(L"Perfect World Mobile %s",szVerEXE);
	SetWindowText(szTitle);
	
	Sleep(100);
	g_pAutoManager = (CAutoManagerEx*)AfxBeginThread(RUNTIME_CLASS(CAutoManagerEx));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAutoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CVIEDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAutoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




LRESULT CAutoDlg::OnEmulatorEvents( WPARAM wParam, LPARAM lParam )
{
	UINT uEvent = (UINT)wParam;
	switch (uEvent) {
	case EVENT_MANAGER_INIT:
		OnEventManagerInit();
		break;
	case EVENT_EMULATOR_INIT:
		OnEventEmulatorInit((CEmulatorProcess*)lParam);
		break;
	}
	return 0;
}

void CAutoDlg::OnEventManagerInit()
{
	if (g_pGameManager->GetListGame()->IsEmpty())
		m_tabMain.SetCurSel(0);//Tab About
	else {
		m_tabMain.SetCurSel(0);//Tab Activity
		m_lstEmulator.SetSelectedItem(0);
		m_pGameSelected = g_pGameManager->GetGameInfo(0);
	}
	m_tabMain.ActivateTabDialogs();
	m_tabMain.SetGameActive(m_pGameSelected);
}

void CAutoDlg::OnEventEmulatorInit( CEmulatorProcess* p )
{
	if (!p) return;
	CGameInfo* pGame = (CGameInfo*)p->GetGameInfo();
	if (pGame == NULL) return;
	LOGA_ERROR("OnEventEmulatorInit :: AddNewEmulator............");
	AddNewEmulator(pGame);
}

void CAutoDlg::AddNewEmulator( CGameInfo* pGame )
{
	if (g_pGameManager->GetGameIndex(pGame) != -1) return;
	CPtrList* plstGame = g_pGameManager->GetListGame();
	int index = plstGame->GetCount();
	m_lstEmulator.InsertItem(index, L"");

	if (pGame->_czFakeName[0] != 0)
		m_lstEmulator.SetItemText(index, TAB_INDEX_EMULATOR, CUtils::_A2W(pGame->_czFakeName));
	else m_lstEmulator.SetItemText(index, TAB_INDEX_EMULATOR, pGame->m_czVMName);

	m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Checking ...");

	if (pGame->IsWindowActivated()) {
		if (pGame->m_chkHidden) m_lstEmulator.SetItemIcon(index, TAB_INDEX_GAMEHIDE, IDI_ICON_HIDE);
		else m_lstEmulator.SetItemIcon(index, TAB_INDEX_GAMEHIDE, pGame->m_iconEmulator);
	}
	else {
		if (pGame->GetGameStatus() != gs_emulatorinactive) pGame->SetGameStatus(gs_emulatorexit);
		m_lstEmulator.SetItemIcon(index, TAB_INDEX_GAMEHIDE, pGame->m_iconEmulator);
	}

	m_lstEmulator.SetCheck(index, pGame->m_bControl);

	/*if (!theApp.CheckLicense(pGame))
		m_lstEmulator.SetRowTextColor(index, RGB(255, 0, 0));
	else*/

	m_lstEmulator.SetRowTextColor(index, RGB(0, 0, 255));
	CActivitySetting::GetInstance()->InitActivity(pGame);

	plstGame->AddTail(pGame);

	LogWriteW(L"Add New Game %08X [%s] index:%d COUNT:%d, m_chkHidden:%d", pGame, pGame->m_czVMName, index, plstGame->GetCount(),pGame->m_chkHidden);
	pGame->uiTimerID = SetTimer((UINT_PTR)pGame, 1000, _TimeEmulatorUpdate);
	if (!pGame->uiTimerID){
		LOGW_ERROR(L"[%s] index:%d TIMER ERROR",pGame->m_czVMName, index);
	}
}

VOID CALLBACK CAutoDlg::_TimeEmulatorUpdate( HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	 g_pMainDlg->OnTimeEmulatorUpdate((CGameInfo*)idEvent);
}

void CAutoDlg::OnTimeEmulatorUpdate( CGameInfo* pGame )
{
	int index = g_pGameManager->GetGameIndex(pGame);
	GameStatus gs = pGame->GetGameStatus();
	//LOGW_DEBUG(L"[%s] -- gs[%d]",pGame->m_czVMName, (int)gs/*, pGame->IsWindowActivated()/* IsWindowActivated:%d*/);
	
	//LOGW_DEBUG(L"%d...m_bControl, m_lstEmulator.getcheck = %d, bRunGAme = %d", pGame->m_bControl, m_lstEmulator.GetCheck(index), pGame->m_OptionTab.bRunGameWhenCrash);

	switch (gs) {
	case gs_none: {
		break;
				  }
	case gs_emulatorinactive: {
		
		if (pGame->IsGameStatusChanged()) {
			LOGW_ERROR(L"[%s] OFFLINE..1", pGame->m_czVMName);
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"OFFLINE");
			if(pGame->m_pAccountInlist){
				pGame->m_pAccountInlist->bRunning = FALSE;
				pGame->m_pAccountInlist = NULL;
				pGame->ResetLoginAccount();
				//g_pMainDlg->m_tabMain.m_AccountDlg.UpdateTree();

			}
		}
		//else 
		//{
		//	LOGW_ERROR(L"[%s] OFFLINE..0", pGame->m_czVMName);
		//	//pGame->SetGameStatus(gs_runemulator);
		//}
		break;
							  }
	case gs_emulatorexit: {
		if (pGame->IsGameStatusChanged()) {
			pGame->Reset();
			m_lstEmulator.SetCheck(index, FALSE);
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"OFFLINE");
			if(pGame->m_pAccountInlist){
				pGame->m_pAccountInlist->bRunning = FALSE;
				pGame->m_pAccountInlist = NULL;
				pGame->ResetLoginAccount();
				//g_pMainDlg->m_tabMain.m_AccountDlg.UpdateTree();
			}
		}
		break;
						  }
	case gs_runemulator: {
		LOGW_INFO(L"[%s] gs_runemulator.........!", pGame->m_czVMName);
		g_pAutoManager->RunEmulatorOrder();
		//if (!g_pAutoManager->SetRunEmulator(pGame)) break;
		//if (pGame->IsGameStatusChanged()) {
		//	LogWriteW(L"[%s] GAME STATUS RUNEMULATOR ...", pGame->m_czVMName);
		//	g_pAutoManager->RunEmulator(pGame);
		//}
		break;
						 }
	case gs_calledemulator: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Đang mở giả lập");
		}
		return;
							}
	case gs_emulatorinit: {
		if (pGame->IsGameStatusChanged()) {
			LOGW_INFO(L"[%s] Connected!", pGame->m_czVMName);
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Ðã kết nối");
			if (pGame->m_chkHidden) m_lstEmulator.SetItemIcon(index, TAB_INDEX_GAMEHIDE, IDI_ICON_HIDE);				
			if (pGame->_czFakeName[0] != 0) m_lstEmulator.SetItemText(index, TAB_INDEX_EMULATOR, CUtils::_A2W(pGame->_czFakeName));
		}
		break;
						  }
	case gs_rungame: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Đang mở Game");
		}
		break;
					 }
	case gs_runengine: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Engine Loading");
		}
		break;
					   }
	case gs_calledengine: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Engine Loaded");
		}
		break;
						  }
	case gs_enginechecking: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Engine Checking");
		}
		break;
							}
	case gs_gameinit: 
	case gs_monoinited:{
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Chờ vào Game");
			if (pGame->_czFakeName[0] != 0)
				m_lstEmulator.SetItemText(index, TAB_INDEX_EMULATOR, CUtils::_A2W(pGame->_czFakeName));
			else
				m_lstEmulator.SetItemText(index, TAB_INDEX_EMULATOR, pGame->m_czVMName);
		}
		break;
					  }
	case gs_selectserver: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Chọn máy chủ");
		}
		break;
						  }
	case gs_selectplayer: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Chọn nhân vật");
		}
		break;
						  }
						  /*
	case gs_getplayername: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Lấy nhân vật");
		}
		break;
						   }
						   */
	case gs_logined: {
		if (pGame->IsGameStatusChanged()) {
			static BOOL bFirst = FALSE;
			if (m_lstEmulator.GetCheck(index) == 1) pGame->m_bControl = TRUE;
			pGame->m_flagSyncAgain = SYNC_CURRENT_ACTIVITY;
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Online");			
			m_lstEmulator.SetItemText(index, TAB_INDEX_EMULATOR, CUtils::_A2W(pGame->m_accountInfo.czRoleName));
			if (m_lstEmulator.GetCheck(index) == 0 && !bFirst) {
				bFirst = TRUE;
				pGame->m_bSyncOptionTab = TRUE;

			}
			//set teamleader
			TEAMTAB *pTeamTab = pGame->GetTeamTab();
			pTeamTab->bSyncTeamOption = TRUE;
			if(pTeamTab->iTeamMode == TEAMMODE_LEADER){
				strcpy_s(pTeamTab->members[0].czTeamName, 64, pGame->m_accountInfo.czRoleName);
				pTeamTab->uTimeUpdate = GetTickCount();
				pTeamTab->bUpdateNow = TRUE;

			}
		}
		theApp.UpdateLicenseActivityList(pGame);
		break;
					 }
	case gs_lostfocus: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Lost Focus");
		}
		break;
					   }
	case gs_gameexit: {
		if (pGame->IsGameStatusChanged()) {
			//if (pGame->m_eType == EmulType_BlueStacks) m_lstEmulator.SetCheck(index, FALSE);
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Game đang đóng");
			if(pGame->m_pAccountInlist){
				pGame->m_pAccountInlist->bRunning = FALSE;
				pGame->m_pAccountInlist = NULL;
				pGame->ResetLoginAccount();
				//g_pMainDlg->m_tabMain.m_AccountDlg.UpdateTree();
			}
			pGame->Reset();
		}
		break;
					  }
	case gs_androidnosupport: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Chưa hỗ trợ");
			pGame->m_bExitGameNow = TRUE;
		}
		if (pGame->m_bControl) {
			pGame->m_bControl = FALSE;
			m_lstEmulator.SetCheck(index, FALSE);
		}
		return;
							  }
	case gs_gamenotinstalled: {
		if (pGame->IsGameStatusChanged()) { 
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Trò chơi đâu");
		}
		if (pGame->m_bControl) {
			pGame->m_bControl = FALSE;
			m_lstEmulator.SetCheck(index, FALSE); 
		}
		return;
							  }
	case gs_gamenotrunning: {
		if (pGame->m_OptionTab.bRunGameWhenCrash) {
			if (m_lstEmulator.GetCheck(index) == 1) pGame->m_bControl = TRUE;
		}

		if (!pGame->m_OptionTab.bRunGameWhenCrash) {
			if (!pGame->m_bControl) 	m_lstEmulator.SetCheck(index, FALSE);
		}

		if (pGame->IsGameStatusChanged()) { 
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Mở Game");
		}
		break;
							}
	case gs_mononosupport: {
		if (pGame->IsGameStatusChanged()) {
			pGame->m_bExitGameNow = TRUE;
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"MONO None!");
		}
		if (pGame->m_bControl) {
			pGame->m_bControl = FALSE;
			m_lstEmulator.SetCheck(index, FALSE); 
		}
		return;
						   }
	case gs_errorsize: {
		if (pGame->IsGameStatusChanged()) {
			m_lstEmulator.SetItemText(index, TAB_INDEX_GAMESTATUS, L"Sai kích thước");
		}
		break;
					   }
	case gs_engineexit: {
		//if (pGame->IsGameStatusChanged()) {
		//	pGame->m_bControl = NULL;
		//	m_lstEmulator.SetCheck(index, FALSE);
		//	pGame->m_dwEnginePID = MAXUINT;
		//	pGame->SetGameStatus(gs_emulatorinit);
		//	return;
		//}
		break;
						}
	case gs_error: {
		break;
				   }
	}//switch (gs) 


	if (g_pMainDlg->m_pGameSelected == pGame) {
		if(pGame->bUpdateUINow){
			g_pMainDlg->m_tabMain.m_ActivityDlg.UpdateControls(pGame);		
			pGame->bUpdateUINow = FALSE;
		}
		if(pGame->bUpdateLoginDlgNow){
			g_pMainDlg->m_tabMain.m_LoginDlg.UpdateControls(pGame);		
			pGame->bUpdateLoginDlgNow = FALSE;
		}
	}

	DWORD dwCurTime = GetTickCount();
	if (dwCurTime - m_dwStartTime_RunAuto > ONE_DAY_TIMER)
	{
		m_dwStartTime_RunAuto = dwCurTime;
		theApp.UpdateAllLicenses();
	}
	
	//if (pGame->IsWindowActivated()) LogWriteW(L"m_bControl ====== %d", pGame->m_bControl);
	
	//LogWriteW(L"%s IsWindowActivated == %d, m_chkHidden %d",pGame->m_czVMName, pGame->IsWindowActivated(), pGame->m_chkHidden);

	/*if(pGame->GetTeamTab()->iTeamMode == TEAMMODE_MEMBER){
		pGame->m_iCurrentActivity  = GetCurrentLeaderActivity(pGame);
	}
	else*/ 
		pGame->UpdateCurrentActivity();
	
	pGame->RecheckDoingAcitivity();

	//m_tabMain.m_OptionDlg.updateCurrentID(pGame);
}


void CAutoDlg::ShowEmulator()
{
	if (!m_pGameSelected) return;
	if (::IsWindowVisible(m_pGameSelected->m_hWnd)) 
	{
		LogWriteA("ShowGameClient....");
		if (::IsIconic(m_pGameSelected->m_hWnd)) ::ShowWindow(m_pGameSelected->m_hWnd,SW_RESTORE);				
		int i=0;
		while (i < 10)
		{
			Sleep(20);
			if (::GetForegroundWindow() != m_pGameSelected->m_hWnd) ::SetForegroundWindow(m_pGameSelected->m_hWnd);	
			else break;
		}						
		SetForegroundWindow();
	}
}

void CAutoDlg::OnClose()
{
	//BOOL bExit =  g_pGameManager->AnyGameActivated();

	//CString txt = L"Bạn muốn thoát auto phải không?";
	///*
	//if (bHasInfo && g_pDataShared->iLoginChecked == BST_UNCHECKED)
	//{
	//	bExit = TRUE;
	//	txt = L"Bạn chưa chọn lưu tài khoản mật khẩu trên máy này.\r\nBạn muốn thoát Auto?";
	//}	
	//*/
	//if (bExit && VIEMsgBox(txt,L"Thông báo!",MB_YESNO|MB_ICONWARNING) == IDNO) return;

	

	g_pAutoManager->ExitThread();
	
	//MessageBox(L"EXIT APPLICATION");
	CVIEDialog::OnClose();
}
void CAutoDlg::OnLvnItemchangedListEmulator(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW lpItem = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	if (lpItem->iItem < 0) return;
	if (lpItem->uNewState == 3)//LVIS_SELECTED LVIS_FOCUSED
	{						
		m_pGameSelected = g_pGameManager->GetGameInfo(lpItem->iItem);
		LogWriteA("Selected item: %d", lpItem->iItem);
		m_tabMain.SetGameActive(m_pGameSelected);
		return; 
	}
}

void CAutoDlg::OnNMClickListEmulator(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if (lpItem->iItem < 0) return;
	CGameInfo* pGame = g_pGameManager->GetGameInfo(lpItem->iItem);
	if (!pGame) return;

	switch (lpItem->iSubItem)
	{
	case TAB_INDEX_GAMEHIDE:
		{//click Hiden
			if (!pGame->IsWindowActivated()) break;
			BOOL bHideNow = pGame->m_chkHidden;
			if (pGame->IsWindowActivated()) bHideNow = pGame->m_bHidden;

			if (bHideNow) // da hiden -> show
			{
				pGame->m_chkHidden = FALSE;
				m_lstEmulator.SetItemIcon(lpItem->iItem,TAB_INDEX_GAMEHIDE,pGame->m_iconEmulator);

			}
			else // dang show -> hidden
			{				
				pGame->m_chkHidden = TRUE;
				m_lstEmulator.SetItemIcon(lpItem->iItem,TAB_INDEX_GAMEHIDE,IDI_ICON_HIDE);

			}			
		}
		break;
	default:
		if (lpItem->iSubItem > 0 && m_pGameSelected == pGame) ShowEmulator();		
	}
}

void CAutoDlg::OnNMRClickListEmulator(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CAutoDlg::OnLvnItemCheckListGame( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMITEMACTIVATE lpItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;	
	CGameInfo* pGame = g_pGameManager->GetGameInfo(lpItem->iItem);
	if (!pGame) return;
	int iChecked = m_lstEmulator.GetCheck(lpItem->iItem);

	if (!theApp.CheckLicense(pGame)){
		pGame->m_bControl = FALSE;
		m_lstEmulator.SetCheck(lpItem->iItem,BST_UNCHECKED);
		RECT rect;
		m_lstEmulator.GetWindowRect(&rect);
		theApp.DisplayUnregisterToolTip(rect.left,rect.top);
		return;

	}

	pGame->m_bControl = m_lstEmulator.GetCheck(lpItem->iItem);
	
	if (pGame->m_eType == EmulType_BlueStacks){
		if (pGame->GetGameStatus() >= gs_emulatorinit) return;
	}

	if (!pGame->IsWindowActivated()) {
		if (pGame->m_bControl) {
			pGame->SetGameStatus(gs_runemulator);
		}
		else {
			if (pGame->GetGameStatus() == gs_runemulator) {
				LOGW_INFO(L"pGame->GetGameStatus() == gs_runemulator .......");
				pGame->SetGameStatus(gs_emulatorexit);
				g_pAutoManager->ClearRunEmulator(pGame);
			}
		}
	}
}

void CAutoDlg::OnLvnListGameItemMove( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMLVITEMMOVE pLVIM = reinterpret_cast<LPNMLVITEMMOVE>(pNMHDR);
	*pResult = 0;
	int idx1 = pLVIM->iItem;  // Vị trí cũ
	int idx2 = pLVIM->iToIndex; // Vị trí mới

	CGameInfo* pTemp = g_pGameManager->GetGameInfo(idx1);
	if (idx1 > idx2)
	{//Up
		for (int i = idx1 - 1; i >= idx2; i--) g_pGameManager->SwapPosition(i + 1, i);
	}
	else if (idx1 < idx2)
	{//Down
		for (int i = idx1 + 1; i <= idx2; i++) g_pGameManager->SwapPosition(i - 1, i);
	}
	g_pGameManager->SetPosition(idx2, pTemp);
}



void CAutoDlg::OnBnClickedButtonLic()
{
	OnOK();
}


int CAutoDlg::GetCurrentLeaderActivity(CGameInfo *pGame){

	if(!pGame) return -1;
	CGameInfo *pLeader =  g_pGameManager->GetGameInfoByRoleName(pGame->GetTeamTab()->members[0].czTeamName);
	if(!pLeader) return -1;
	if (!pLeader->m_bControl) return -1;
	//CString czName;
	//czName.Format("%s",  pGame->GetTeamTab()->members[0].czTeamName);
	LOGA_DEBUG("czName ...........%s", pGame->GetTeamTab()->members[0].czTeamName);
	
	return pLeader->m_iCurrentActivity;
}

void CAutoDlg::OnContextMenu( CWnd* /*pWnd*/, CPoint point )
{
	CListCtrl *pLV;
	pLV = reinterpret_cast<CListCtrl *>(GetDlgItem(IDC_LIST_EMULATOR));
	// Find the rectangle around the control
	CRect rect;
	pLV->GetWindowRect(&rect);
	if (rect.PtInRect(point))
	{
		/*
		int pos = (int)m_lstActivity.GetFirstSelectedItemPosition();
		if(pos == 0) return;
		*/

		CMenu mnuPopup;
		mnuPopup.LoadMenuW(IDR_MENU_GAME);
		// Get a pointer to the first item of the menu
		CMenu *mnu1 = mnuPopup.GetSubMenu(0);
		ASSERT(mnu1);
		if (!mnu1)
		{
			return;
		}

		// Find out if the user right-clicked a button
		if (rect.PtInRect(point)) // Since the user right-clicked a button, display its context menu
			mnu1->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		return;
	}
}

void CAutoDlg::OnGameXoagialap()
{
	int idx = m_lstEmulator.GetSelectedItem();
	if (idx >= 0) {
		g_pAutoManager->RemoveGame(idx);
		LOGA_WARNING("Remove game %d", idx);
	}
}

void CAutoDlg::OnGameTurnOnAll()
{
	CPtrList* plstGame = g_pGameManager->GetListGame();
	int index = 0;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		m_lstEmulator.SetCheck(index, TRUE);

		++index;

	}
}

void CAutoDlg::OnGameTurnOffAll()
{
	CPtrList* plstGame = g_pGameManager->GetListGame();
	int i = 0;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		pGame->m_bControl = FALSE;
		m_lstEmulator.SetCheck(i, FALSE);
		++i;
	}
}

void CAutoDlg::OnGameCopyGame()
{
	COptionCopyGame* pCopyGame = new COptionCopyGame(NULL, m_pGameSelected);
	pCopyGame->DoModal();
	delete pCopyGame;
}

void CAutoDlg::OnChangeUI( int sel )
{
	int i = sel;

	RECT rc;
	::GetWindowRect(this->m_hWnd, &rc);
	int x = rc.left;
	int y = rc.top;
	int origin;
	if (i == 0) origin = 595;
	else origin = 580;
	int w = rc.right - rc.left;
	int h = origin + (i * 100);
	LOGA_INFO("rc:%d,%d,%d,%d", x, y, rc.right, rc.bottom);
	LOGA_INFO("Height:%d", rc.bottom - rc.top);
	LOGA_INFO("Width:%d", rc.right - rc.left);
	//RECT rcCtrl;
	//::GetWindowRect(m_btnLogo.GetSafeHwnd(), &rcCtrl);
	//int hCtrl = rcCtrl.top + (i * 200);
	//LOGA_INFO("btnLogo.pos:%d,%d,%d,%d", rc.left,rc.top,rc.right, rc.bottom);

	//origin height:579
	this->SetWindowPos(NULL, x, y, w, h, SWP_SHOWWINDOW | SWP_NOZORDER);
}

void CAutoDlg::ResetActivityAllEmulator()
{
	CPtrList* plstGame = g_pGameManager->GetListGame();
	int i = 0;
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		pGame->ResetActivityStatus();
	}
}

void CAutoDlg::ShowOptionDlg( CWnd* pShowDlg,CWnd* pDlgParent, int iDisTop /*= 30*/ )
{
	if(!pDlgParent || !pShowDlg) return;

	CRect pRectDlg,pRectDlgParent;
	pDlgParent->GetWindowRect(&pRectDlgParent);
	pShowDlg->GetWindowRect(&pRectDlg);

	pShowDlg->ShowWindow(!pShowDlg->IsWindowVisible());


	// ki?m tra có b? ?n bên trái hay ko??
	if (pShowDlg->IsWindowVisible()) {
		if (!CheckDlgInsideScreenDesktop(pRectDlg)) 
			pShowDlg->SetWindowPos(NULL, pRectDlg.left, pRectDlgParent.top/*- iDisTop*/, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);

	}
}

BOOL CAutoDlg::CheckDlgInsideScreenDesktop( CRect &pRect )
{	
	RECT desktop;
	CWnd* cDesktop = GetDesktopWindow();
	cDesktop->GetWindowRect(&desktop);
	CRect rectThis;
	this->GetWindowRect(&rectThis);
	//LOGA_DEBUG("GetDesktopWindow(%d,%d,%d,%d) pRect(%d,%d,%d,%d) W:H(%d,%d)", desktop.left, desktop.top, desktop.right, desktop.bottom, pRect.left, pRect.top, pRect.right, pRect.bottom, pRect.Width(), pRect.Height());

	if(desktop.right - (rectThis.left + pRect.Width()) < (desktop.right - rectThis.Width() - pRect.Width()))
		pRect.left = rectThis.left - pRect.Width();

	return FALSE;
}

void CAutoDlg::checkMacAddress()
{
	//CString czMac1 = L"08-8F-C3-03-ED-52"; 

	////boi bon ba
	//CString czBibonba1 = L"00-25-90-62-28-17";
	//CString czBibonba2 = L"E4-11-5B-E6-F7-65";
	//CString czBibonba3 = L"00-E0-81-BE-B2-F3";
	//CString czBibonba4 = L"00-E0-81-BE-B2-F4";

	////dung ngong
	//CString czDungNgong3 = L"0A-E0-AF-A7-24-E1";
	//CString czDungNgong2 = L"0A-E0-AF-A1-0E-D5";
	//CString czDungNgong1 = L"0A-E0-AF-B3-12-0A";
	//CString czDungNgong7 = L"0A-E0-AF-D2-29-E5";
	//CString czDungNgong4 = L"0A-E0-AF-D2-33-B9";
	//CString czDungNgong6 = L"0A-E0-AF-A5-16-7E"; //0A-E0-AF-D2-29-E5
	//CString czDungNgong5 = L"0A-E0-AF-B3-41-6C";
	//CString czDungNgong8 = L"20-31-11-1A-02-10";
	//CString czDungNgong9 = L"20-12-11-0A-07-51";
	//CString czDungNgong10 = L"20-12-11-0A-07-52";

	//////hai anh
	//CString czHaiAnh = L"0A-E0-AF-A7-42-A5";
	//CString czHaiAnh1 = L"5E-D1-8E-B1-93-F1";
	//CString czHaiAnh2 = L"0A-E0-AF-B3-5E-6E";

	//////tuan dong nat
	////CString czTuanDongNat1 = L"0A-E0-AF-B7-2C-59";
	////CString czTuanDongNat2 = L"00-E0-4C-03-81-26";
	////CString czTuanDongNat3 = L"0A-E0-AF-B3-9A-37";
	//CString czTuanDongNat4 = L"0A-E0-AF-B1-1E-81";
	//CString czTuanDongNat5 = L"00-E0-4A-68-02-AB";

	////1may
	//CString czTuanDongNat6 = L"0A-E0-AF-B3-9A-93";

	////3may
	//CString czTuanDongNat7 = L"20-33-11-1A-12-A9";
	//CString czTuanDongNat8 = L"00-FF-36-71-F6-53";
	//CString czTuanDongNat9 = L"0A-E0-AF-A7-4E-F7";

	//CString czKhanh1 = L"20-05-22-00-02-6A";
	//CString czKhanh2 = L"20-07-11-1A-03-00";

	//CString czTrungNguyenTran1 = L"2A-04-4C-30-0A-E6";
	

	//CString strGateWay = _T("");
	//CString strMACAddress = _T("");
	//IP_ADAPTER_INFO ipAdapterInfo[16];
	//DWORD dwBuflen = sizeof(ipAdapterInfo);

	//DWORD dwStatus = GetAdaptersInfo(ipAdapterInfo, &dwBuflen);
	//if (dwStatus != ERROR_SUCCESS)
	//{
	//	strMACAddress.Format(_T("Error for GetAdaptersInfo : %d"), dwStatus);
	//	AfxMessageBox(strMACAddress);
	//}
	//PIP_ADAPTER_INFO pIpAdapterInfo = ipAdapterInfo;

	//for (int i = 0; i < 10; i++) {
	//	if (pIpAdapterInfo) {
	//		strMACAddress.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),
	//			pIpAdapterInfo->Address[0], 
	//			pIpAdapterInfo->Address[1], 
	//			pIpAdapterInfo->Address[2], 
	//			pIpAdapterInfo->Address[3], 
	//			pIpAdapterInfo->Address[4], 
	//			pIpAdapterInfo->Address[5] 
	//		);

	//		czMacAddr[i] = strMACAddress;
	//		pIpAdapterInfo = pIpAdapterInfo->Next;
	//	}
	//}

	//CString czText;
	//CString czTextFull;

	//TCHAR szBuffer[256];
	//DWORD dwSize = 256;
	//GetComputerName(szBuffer, &dwSize); //Get the computer name
	//czTextFull.Format(L"%s\r\n", szBuffer);

	//
	//int j = 0;
	//for (j; j < 10; j++) {

	//	czText.Format(L"%s", czMacAddr[j]);
	//	czTextFull = czTextFull + czText + L"\r\n";

	//	//ngoc anh kim ngoc
	//	if (czMacAddr[j] == czMac1) {
	//		MessageBox(L"Is My PC -> check Mac is Yes", L"Hello", MB_OK);
	//		break;
	//	}


	//}

	//if (j >= 10) {
	//	CString czTxtFailed;
	//	czTxtFailed.Format(L"Máy tính này chưa được đăng ký!\r\n%s", czTextFull);
	//	MessageBox(czTxtFailed, L"Error", MB_OK);
	//	OnOK();
	//	return;
	//}
	//Khanh Spirit
	/*if (czKhanh1 != strMACAddress &&
	czKhanh2 != strMACAddress && 
	czMac1 != strMACAddress ) {
			MessageBox(L"Máy tính này chưa được đăng ký!", L"Error", MB_OK);
			OnOK();
			return;
	}*/

	//Trung nguyen tran 1
	/*if (czTrungNguyenTran1 != strMACAddress && 
		czMac1 != strMACAddress) {
			MessageBox(L"Máy tính này chưa được đăng ký!", L"Error", MB_OK);
			OnOK();
			return;
	}*/

	

	//HaiAnh
	/*if (czHaiAnh != strMACAddress  &&
	czHaiAnh2 != strMACAddress && 
	czMac1 != strMACAddress) {
			MessageBox(L"Máy tính này chưa được đăng ký!", L"Error", MB_OK);
			OnOK();
			return;
	}*/

	
	//HaiAnh 1 may
	/*if (czHaiAnh1 != strMACAddress && 
	czMac1 != strMACAddress) {
			MessageBox(L"Máy tính này chưa được đăng ký!", L"Error", MB_OK);
			OnOK();
			return;
	}*/
	
	//Bi bon ba
	/*if (czBibonba1 != strMACAddress  &&
		czBibonba2 != strMACAddress  &&
		czBibonba3 != strMACAddress && 
		czBibonba4 != strMACAddress && 
		czMac1 != strMACAddress) {
			MessageBox(L"Máy tính này chưa được đăng ký!", L"Error", MB_OK);
			OnOK();
			return;
	}*/

	//tuan dong nat
	/*if (czTuanDongNat4 != strMACAddress  &&
		czTuanDongNat5 != strMACAddress  &&
		czTuanDongNat6 != strMACAddress && 
		czMac1 != strMACAddress) {
			MessageBox(L"Máy tính này chưa được đăng ký!", L"Error", MB_OK);
			OnOK();
			return;
	}*/

	//dung ngong
	/*if (czDungNgong1 != strMACAddress &&
		czDungNgong2 != strMACAddress &&
		czDungNgong3 != strMACAddress &&
		czDungNgong4 != strMACAddress &&
		czDungNgong5 != strMACAddress &&
		czDungNgong6 != strMACAddress &&
		czDungNgong7 != strMACAddress &&
		czDungNgong8 != strMACAddress &&
		czDungNgong9 != strMACAddress &&
		czDungNgong10 != strMACAddress && 
		czMac1 != strMACAddress) {
			MessageBox(L"Máy tính này chưa được đăng ký!", L"Error", MB_OK);
			OnOK();
			return;
	}*/

}

void CAutoDlg::checkTime()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	 if (gio + 7 >= 24) {
		 gio = gio + 7 - 24;
		 ngay = ngay + 1;
	 }
	
	//bi bon ba
	 /*if (ngay < 1 && thang <= 8) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 if (ngay == 1 && thang == 9) {
		 MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	 }

	 if (ngay >= 2  && thang >= 9) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }*/


	 //longtran 3 4

	 /*if (ngay < 28 && thang <= 6) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 if (ngay == 31) {
		 MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	 }

	 if (ngay >= 1  && thang >= 8) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }*/


	//hai anh

	 /*if (ngay < 11 && thang <= 7) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 if (ngay == 11 && thang == 8) {
		 MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);
	 }

	 if (ngay >= 12  && thang >= 8) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }*/

	 //longtran 3 4
	 /*if (ngay < 4 && thang <= 7) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 if (ngay == 31 && thang == 7) {
		 MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	 }

	 if (ngay >= 5  && thang >= 8) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }*/

	//viet anh
	
	/*if (ngay < 5 && thang <= 7) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay == 31 && thang == 7) {
		MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	}

	if (ngay >= 6  && thang >= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}*/

	 //dung ngong
	
	/*if (ngay < 11 && thang <= 7) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay == 11 && thang == 8) {
		MessageBox(L"Auto hôm nay hết hạn, vui lòng gia hạn để tiếp tục sử dụng !", NULL, MB_OK);
	}

	if (ngay >= 12  && thang >= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}*/

	//tuan dong nat
	/*if (ngay < 19 && thang <= 7) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay == 19 && thang == 8) {
		MessageBox(L"Auto hôm nay hết hạn, vui lòng gia hạn để tiếp tục sử dụng !", NULL, MB_OK);
	}

	if (ngay >= 20  && thang >= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}*/

	//khanh spirit
	/*if (ngay < 2 && thang <= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay == 1 && thang == 9) {
		MessageBox(L"Auto hôm nay hết hạn, vui lòng gia hạn để tiếp tục sử dụng !", NULL, MB_OK);
	}

	if (ngay >= 2  && thang >= 9) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}*/

	//test
	
}

void CAutoDlg::checkTimeTrungNguyenTran()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	 if (gio + 7 >= 24) {
		 gio = gio + 7 - 24;
		 ngay = ngay + 1;
	 }
	
	 if (ngay < 5 && thang <= 8) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 if (ngay == 5 && thang == 9) {
		 MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	 }

	 if (ngay >= 6  && thang >= 9) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }
	
	 
	 
}

void CAutoDlg::checkTimeHaiAnh()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	 if (gio + 7 >= 24) {
		 gio = gio + 7 - 24;
		 ngay = ngay + 1;
	 }
	//hai anh

	 if (ngay < 6 && thang <= 8) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 if (ngay == 6 && thang == 9) {
		 MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);
	 }

	 if (ngay >= 7  && thang >= 9) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }


	 
	
}

void CAutoDlg::checkTimeBiBonBa()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	if (gio + 7 >= 24) {
		gio = gio + 7 - 24;
		ngay = ngay + 1;
	}
	
	if (ngay < 1 && thang <= 8) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 if (ngay == 1 && thang == 9) {
		 MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	 }

	 if (ngay >= 2  && thang >= 9) {
		 MessageBox(L"out Of Date!", NULL, MB_OK);
		 OnOK();
		 return;
	 }

	 
}

void CAutoDlg::checkTimeTuanDongNat()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	if (gio + 7 >= 24) {
		gio = gio + 7 - 24;
		ngay = ngay + 1;
	}

	if (ngay < 7 && thang <= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay == 7 && thang == 9) {
		MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	}

	if (ngay >= 8  && thang >= 9) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	
}

void CAutoDlg::checkTimeHaiAnh1May()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	if (gio + 7 >= 24) {
		gio = gio + 7 - 24;
		ngay = ngay + 1;
	}
	//hai anh

	if (ngay < 11 && thang <= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay == 11 && thang == 9) {
		MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);
	}

	if (ngay >= 12  && thang >= 9) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	

}

void CAutoDlg::checkTimeDungNgong()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	if (gio + 7 >= 24) {
		gio = gio + 7 - 24;
		ngay = ngay + 1;
	}

	if (ngay < 11 && thang <= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay == 11 && thang == 9) {
		MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);
	}

	if (ngay >= 12  && thang >= 9) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	

}

void CAutoDlg::checkTimeTest()
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, ngay);

	if (gio + 7 >= 24) {
		gio = gio + 7 - 24;
		ngay = ngay + 1;
	}

	if (ngay < 12 && thang <= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	if (ngay >= 15  && thang >= 8) {
		MessageBox(L"out Of Date!", NULL, MB_OK);
		OnOK();
		return;
	}

	
}


void CAutoDlg::OnBnClickedButtonSave()
{
	g_pAutoManager->SaveEmulators();
	CString czMBox;
	czMBox.Format(L"Ðã lưu thiết lập!");
	MessageBox(czMBox, L"Thông báo", MB_OK);
}

void CAutoDlg::checkMac( int iUser )
{
	//kiem tra dia chi
	CString czMac1									= L"08-8F-C3-03-ED-52"; 
	//boi bon ba
	CString czBibonba1								= L"00-25-90-62-28-17";
	CString czBibonba2								= L"E4-11-5B-E6-F7-65";
	CString czBibonba3								= L"00-E0-81-BE-B2-F3";
	CString czBibonba4								= L"00-E0-81-BE-B2-F4";
	//dung ngong
	CString czDungNgong3							= L"0A-E0-AF-A7-24-E1";
	CString czDungNgong2							= L"0A-E0-AF-A1-0E-D5";
	CString czDungNgong1							= L"0A-E0-AF-B3-12-0A";
	CString czDungNgong7							= L"0A-E0-AF-D2-29-E5";
	CString czDungNgong4							= L"0A-E0-AF-D2-33-B9";
	CString czDungNgong6							= L"0A-E0-AF-A5-16-7E";
	CString czDungNgong5							= L"0A-E0-AF-B3-41-6C";
	CString czDungNgong8							= L"20-31-11-1A-02-10";
	CString czDungNgong9							= L"20-12-11-0A-07-51";
	CString czDungNgong10							= L"20-12-11-0A-07-52";
	CString czDungNgong11							= L"00-E0-3A-68-02-83";
	CString czDungNgong12							= L"0A-E0-AF-B3-60-48";
	CString czDungNgong13							= L"0A-E0-AF-A7-05-4B";
	CString czDungNgong14							= L"0A-E0-AF-D7-00-F2";

	CString czDungNgong15							= L"00-FF-FB-1B-86-FE";
	CString czDungNgong16							= L"00-FF-06-DB-AE-82";

	//hai anh
	CString czHaiAnh								= L"0A-E0-AF-A7-42-A5";

	//hai anh may sau
	CString czHaiAnh2								= L"0A-E0-AF-B3-5E-6E";
	CString czHaiAnh1								= L"5E-D1-8E-B1-93-F1"; //0A-E0-AF-A7-42-A5
	//tuan dong nat						= L"00-E0-4C-03-81-26";
	CString czTuanDongNat3							= L"0A-E0-AF-B3-9A-37";
	CString czTuanDongNat4							= L"0A-E0-AF-B1-1E-81";
	CString czTuanDongNat5							= L"00-E0-4A-68-02-AB";
	CString czTuanDongNat6							= L"0A-E0-AF-B3-9A-93";
	CString czTuanDongNat7_1may						= L"00-E0-4A-68-02-B5";
	CString czTuanDongNat7							= L"20-33-11-1A-12-A9";
	CString czTuanDongNat8							= L"00-FF-36-71-F6-53";
	//CString czTuanDongNat9							= L"2A-04-4C-37-02-7B"; 
	CString czTuanDongNat10							= L"00-E0-4C-03-81-26"; 
	CString czTuanDongNat11							= L"0A-E0-AF-B7-2C-59"; 
	CString czTuanDongNat12							= L"00-FF-B7-8E-98-10"; 

	//khanh
	CString czKhanh1								= L"20-05-22-00-02-6A";
	CString czKhanh2								= L"20-07-11-1A-03-00";
	//trung nguyen tran
	CString czTrungNguyenTran1						= L"2A-04-4C-30-0A-E6";
	CString czTrungNguyenTran1_1					= L"2A-04-4C-46-0A-11";
	CString czTrungNguyenTran2						= L"38-60-77-56-2C-0D";
	//HoangMinhTa
	CString czHoangMinhTa1							= L"18-C0-4D-3E-83-3F";
	CString czHoangMinhTa2							= L"00-E0-4C-A3-0A-21";

	//NGuyenThach
	CString czNguyenThach1							= L"0A-E0-AF-A2-4A-34";
	CString czNguyenThach2							= L"0A-E0-AF-D2-06-95";
	CString czNguyenThach3							= L"00-E0-1A-68-0E-81";
	CString czNguyenThach4							= L"00-81-BE-DD-05-ED";
	CString czNguyenThach5							= L"0A-E0-AF-B3-6A-05";
	CString czNguyenThach6							= L"00-E0-4C-62-A1-2D";
	CString czNguyenThach7							= L"00-E0-1A-68-06-BC";
	CString czNguyenThach8							= L"0A-E0-AF-B1-59-A0";
	CString czNguyenThach9							= L"00-E0-4C-03-81-23";
	CString czNguyenThach10							= L"00-E0-1A-68-0E-33";
	CString czNguyenThach11							= L"20-33-11-1A-15-B9";

	//HuyHoang
	CString czHuyHoang								= L"E4-B3-18-2B-BA-A0";
	
	//jim
	CString czJim									= L"7C-10-C9-24-8F-0A";

	//tiendung 3 thang //long nguyen ban tien dung
	CString czLongNguyen								= L"00-AC-F0-E6-2C-81";

	CString czTienDung								= L"00-E0-2A-68-06-20";

	//freedom 2 thang
	CString czFreedom								= L"0A-E0-AF-A7-44-35";

	CString strGateWay = _T("");
	CString strMACAddress = _T("");
	IP_ADAPTER_INFO ipAdapterInfo[16];
	DWORD dwBuflen = sizeof(ipAdapterInfo);
	DWORD dwStatus = GetAdaptersInfo(ipAdapterInfo, &dwBuflen);
	if (dwStatus != ERROR_SUCCESS)
	{
		strMACAddress.Format(_T("Error for GetAdaptersInfo : %d"), dwStatus);
		AfxMessageBox(strMACAddress);
	}

	PIP_ADAPTER_INFO pIpAdapterInfo = ipAdapterInfo;
	for (int i = 0; i < 10; i++) {
		if (pIpAdapterInfo) {
			strMACAddress.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),
				pIpAdapterInfo->Address[0], 
				pIpAdapterInfo->Address[1], 
				pIpAdapterInfo->Address[2], 
				pIpAdapterInfo->Address[3], 
				pIpAdapterInfo->Address[4], 
				pIpAdapterInfo->Address[5] 
			);

			czMacAddr[i] = strMACAddress;
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}

	CString czText;
	CString czTextFull;
	TCHAR szBuffer[256];
	DWORD dwSize = 256;
	GetComputerName(szBuffer, &dwSize); //Get the computer name
	czTextFull.Format(L"%s\r\n", szBuffer);


	//duyet danh sach mac tim thay va so sanh voi dia chi mac truyen vao
	int j = 0;
	for (j; j < 10; j++) {

		czText.Format(L"%s", czMacAddr[j]);
		czTextFull = czTextFull + czText + L"\r\n";

		if (iUser == trungNguyenTran) {
			if (czMacAddr[j] == czTrungNguyenTran1) break;
			if (czMacAddr[j] == czTrungNguyenTran1_1) break;
		}

		if (iUser == trungNguyenTran1may) {
			if (czMacAddr[j] == czTrungNguyenTran2) break;
			if (czMacAddr[j] == czTrungNguyenTran1_1) break;
		}

		if (iUser == HaiAnh) {
			if (czMacAddr[j] == czHaiAnh) break;
			//if (czMacAddr[j] == czHaiAnh2) break;
		}

		if (iUser == HaiAnh1May) {
			if (czMacAddr[j] == czHaiAnh1) break;
		}

		if (iUser == BiBonBa) {
			if (czMacAddr[j] == czBibonba1) break;
			if (czMacAddr[j] == czBibonba2) break;
			if (czMacAddr[j] == czBibonba3) break;
			if (czMacAddr[j] == czBibonba4) break;
		}

		if (iUser == DungNgong) {
			if (czMacAddr[j] == czDungNgong1) break;
			if (czMacAddr[j] == czDungNgong2) break;
			if (czMacAddr[j] == czDungNgong3) break;
			if (czMacAddr[j] == czDungNgong4) break;
			if (czMacAddr[j] == czDungNgong5) break;
			if (czMacAddr[j] == czDungNgong6) break;
			if (czMacAddr[j] == czDungNgong7) break;
			if (czMacAddr[j] == czDungNgong8) break;
			if (czMacAddr[j] == czDungNgong9) break;
			if (czMacAddr[j] == czDungNgong10) break;
			if (czMacAddr[j] == czDungNgong11) break;
			if (czMacAddr[j] == czDungNgong12) break;
			if (czMacAddr[j] == czDungNgong13) break;
			if (czMacAddr[j] == czDungNgong14) break;
			if (czMacAddr[j] == czDungNgong15) break;
			if (czMacAddr[j] == czDungNgong16) break;
		}

		if (iUser == KhanhSpirit) {
			if (czMacAddr[j] == czKhanh1) break;
			if (czMacAddr[j] == czKhanh2) break;
		}

		if (iUser == TuanDongNat1May) {
			if (czMacAddr[j] == czTuanDongNat7_1may) break;
			if (czMacAddr[j] == czTuanDongNat4) break;
			if (czMacAddr[j] == czTuanDongNat5) break;
			if (czMacAddr[j] == czTuanDongNat6) break;
			if (czMacAddr[j] == czTuanDongNat7) break;
			if (czMacAddr[j] == czTuanDongNat8) break;
			if (czMacAddr[j] == czTuanDongNat10) break;
			if (czMacAddr[j] == czTuanDongNat11) break;
			if (czMacAddr[j] == czTuanDongNat12) break;
			if (czMacAddr[j] == czTuanDongNat3) break;
		}

		if (iUser == HoangMinhTa) {
			//if (czMacAddr[j] == czHoangMinhTa1) break;
			if (czMacAddr[j] == czHoangMinhTa2) break;
		}

		if (iUser == userTest) {
			m_bShowExpiryTime = TRUE;
			break;
		}

		if (iUser == NguyenThach) {
			if (czMacAddr[j] == czNguyenThach1) break;
			if (czMacAddr[j] == czNguyenThach2) break;
			if (czMacAddr[j] == czNguyenThach3) break;
			if (czMacAddr[j] == czNguyenThach4) break;
			if (czMacAddr[j] == czNguyenThach5) break;
			if (czMacAddr[j] == czNguyenThach6) break;
			if (czMacAddr[j] == czNguyenThach7) break;
			if (czMacAddr[j] == czNguyenThach8) break;
			if (czMacAddr[j] == czNguyenThach9) break;
			if (czMacAddr[j] == czNguyenThach10) break;
			if (czMacAddr[j] == czNguyenThach11) break;
		}

		if (iUser == HuyHoang) {
			if (czMacAddr[j] == czHuyHoang) break;
		}

		if (iUser == Jim) {
			if (czMacAddr[j] == czJim) break;
		}

		if (iUser == user_LongNguyen) {
			if (czMacAddr[j] == czLongNguyen) break;
		}

		if (iUser == userFreedom) {
			if (czMacAddr[j] == czFreedom) break;
		}

		if (iUser == user_TienDung) {
			if (czMacAddr[j] == czTienDung) break;
		}

		//ngoc anh kim ngoc
		CString czNotice;
		if (czMacAddr[j] == czMac1) {
			czNotice.Format(L"current user index %d", iUser);
			m_bShowExpiryTime = TRUE;
			MessageBox(L"Is My PC -> check Mac is Yes", czNotice, MB_OK);
			break;
		}
	}

	if (j >= 10) {
		CString czTxtFailed;
		czTxtFailed.Format(L"Máy tính này chưa được đăng ký!\r\n%s", czTextFull);
		MessageBox(czTxtFailed, L"Error", MB_OK);
		OnOK();
		return;
	}
}


void CAutoDlg::checkTime( int iUser )
{
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"https://time.is/", 0, 0,  
		INTERNET_FLAG_NO_UI | INTERNET_FLAG_NO_CACHE_WRITE, 0);


	if (!hInternetFile)
	{
		LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, ngay, thang;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	ngay = sysTime.wDay;
	thang = sysTime.wMonth;

	if (gio + 7 >= 24) {
		gio = gio + 7 - 24;
		ngay = ngay + 1;
	}

	if (iUser == trungNguyenTran) {
		if (ngay < 5 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 5 && thang == 9) MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);
		
		if (ngay >= 6 && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}
		
	}

	if (iUser == HaiAnh) {
		if (ngay < 6 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 5 && thang == 9) MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);

		if (ngay >= 7  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}
		
	}

	if (iUser == BiBonBa) {
		if (ngay < 1 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 1 && thang == 9) MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);

		if (ngay >= 2  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}
		
	}

	if (iUser == TuanDongNat) {
		if (ngay < 7 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 7 && thang == 9) MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);

		if (ngay >= 8  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}
	
	if (iUser == HaiAnh1May) {
		if (ngay < 11 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 11 && thang == 9) {
			MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);
		}

		if (ngay >= 12  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}

	if (iUser == DungNgong) {
		if (ngay < 11 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 11 && thang == 9) {
			MessageBox(L"Auto hôm nay hết hạn!", NULL, MB_OK);
		}

		if (ngay >= 12  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}

	if (iUser == KhanhSpirit) {
		if (ngay < 2 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 1 && thang == 9) {
			MessageBox(L"Auto hôm nay hết hạn, vui lòng gia hạn để tiếp tục sử dụng !", NULL, MB_OK);
		}

		if (ngay >= 2  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}

	if (iUser == TuanDongNat1May) {
		if (ngay < 14 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 14 && thang == 9) {
			MessageBox(L"Auto hôm nay hết hạn, vui lòng gia hạn để tiếp tục sử dụng !", NULL, MB_OK);
		}

		if (ngay >= 15  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}

	if (iUser == HoangMinhTa) {
		if (ngay < 15 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 15 && thang == 9) {
			MessageBox(L"Auto hôm nay hết hạn, vui lòng gia hạn để tiếp tục sử dụng !", NULL, MB_OK);
		}

		if (ngay >= 16  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}

	if (iUser == userTest) {
		if (ngay < 16 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay >= 18  && thang >= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}

	if (iUser == NguyenThach) {
		if (ngay < 16 && thang <= 8) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		if (ngay == 16 && thang == 9) {
			MessageBox(L"Auto hôm nay hết hạn, vui lòng gia hạn để tiếp tục sử dụng !", NULL, MB_OK);
		}

		if (ngay >= 17  && thang >= 9) {
			MessageBox(L"out Of Date!", NULL, MB_OK);
			OnOK();
			return;
		}

		
	}

	CString czUserName = get_UserName(iUser);


}

void CAutoDlg::checkTime( int iUser, int dayStart, int monthStart )
{
	//kiem tra
	SYSTEMTIME sysTime;
	SecureZeroMemory(&sysTime, sizeof(SYSTEMTIME));
	// Open connection
	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternetSession) {
		//LogWriteW(L"can not open connection..");
		MessageBox(L"Error!", NULL, MB_OK);
		OnOK();
		return;
	}

	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		L"http://aigato.vn/", 0, 0,  
		INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_COOKIES, 0);


	if (!hInternetFile)
	{
		//LogWriteW(L"can not found hInternetFile..");
		MessageBox(L"No Internet!", NULL, MB_OK);
		InternetCloseHandle(hInternetSession);
		OnOK();
		return;
	}

	// Query date time in format systemtime
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
		HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
		InternetCloseHandle(hInternetSession);
		InternetCloseHandle(hInternetFile);
		LogWriteW(L"can not query date time in format systemtime..");
		OnOK();
		return;
	}

	// Clean up ...
	InternetCloseHandle(hInternetFile);
	InternetCloseHandle(hInternetSession);

	int gio, phut, currentDay, currentMonth;
	gio = sysTime.wHour;
	phut = sysTime.wMinute;
	currentDay = sysTime.wDay;
	currentMonth = sysTime.wMonth;
	LOGA_DEBUG("%d, %d, %d", gio, phut, currentDay);

	if (gio + 7 >= 24) {
		gio = gio + 7 - 24;
		currentDay = currentDay + 1;
	}

	int iExpiryDay = -1;
	int iExpiryMonth = -1;
	int iNotifyDay = -1;

	if (iUser == userTest) {
		iExpiryDay = dayStart + 2;
		iExpiryMonth = monthStart;
	}

	else if (iUser == user_LongNguyen) {
		iExpiryDay = dayStart + 1;
		iExpiryMonth = monthStart + 3;
		iNotifyDay = dayStart;
	}

	else if (iUser == userFreedom ||
		iUser == Jim) {
		iExpiryDay = dayStart + 1;
		iExpiryMonth = monthStart + 2;
		iNotifyDay = dayStart;
	}

	else {
		iExpiryDay = dayStart + 1;
		iExpiryMonth = monthStart + 1;
		iNotifyDay = dayStart;
	}

	/*if (currentDay < dayStart && currentMonth <= monthStart) {
		MessageBox(L"out Of Date Before!", NULL, MB_OK);
		OnOK();
		return;
	}*/

	if (currentDay == dayStart  && currentMonth == iExpiryMonth && iUser != userTest) {
		MessageBox(L"Auto sắp hết hạn!", NULL, MB_OK);
	}

	if (currentDay >= iExpiryDay  && currentMonth >= iExpiryMonth) {
		MessageBox(L"out Of Date After!", NULL, MB_OK);
		OnOK();
		return;
	}

	showExpiryTime(iUser, iExpiryDay, iExpiryMonth);
}

CString CAutoDlg::get_UserName( int iUser )
{
	CString czUserName = L"none";
	if (iUser == 1) czUserName = L"trungNguyenTran";
	if (iUser == 2) czUserName = L"HaiAnh";
	if (iUser == 3) czUserName = L"HaiAanh1May";
	if (iUser == 4) czUserName = L"BiBonBa";
	if (iUser == 5) czUserName = L"TuanDongNat";
	if (iUser == 6) czUserName = L"DungNgong";
	if (iUser == 7) czUserName = L"KhanhSpirit";
	if (iUser == 8) czUserName = L"TuanDongNat1May";
	if (iUser == 9) czUserName = L"HoangMinhTa";
	if (iUser == 10) czUserName = L"userTest";
	if (iUser == 11) czUserName = L"NguyenThach";
	if (iUser == 12) czUserName = L"HuyHoang";
	if (iUser == 13) czUserName = L"TuanDongNat6May";
	if (iUser == 14) czUserName = L"Jim";
	if (iUser == 15) czUserName = L"Trung nguyen tran 1 may";
	if (iUser == 16) czUserName = L"Long Nguyen 3 thang - ban tien dung";
	if (iUser == 17) czUserName = L"Freedom";
	if (iUser == 18) czUserName = L"Tien Dung";
	return czUserName;

}

void CAutoDlg::check( int user /*= -1*/ )
{
	//kiem tra
	if (user == -1) {
		MessageBox(L"Unknown PC", L"Error", MB_OK);
		OnOK();
		return;
	}

	checkMac(user);

	//nhap vao ngay thang bat dau
	//arale
	if (user == DungNgong)				checkTime(user, 11, 10);
	if (user == NguyenThach)			checkTime(user, 17, 10);
	if (user == HoangMinhTa)			checkTime(user, 16, 9);
	if (user == userTest)				checkTime(user, 20, 8);
	if (user == Jim)					checkTime(user, 20, 9); //2 tháng
	if (user == BiBonBa)				checkTime(user, 1, 10);
	if (user == trungNguyenTran1may)	checkTime(user, 21, 9);
	if (user == user_LongNguyen)		checkTime(user, 21, 8); //3 thang
	if (user == userFreedom)			checkTime(user, 22, 8); //2 thang
	if (user == TuanDongNat1May)		checkTime(user, 13, 10);  //11may
	if (user == user_TienDung)			checkTime(user, 6, 10);
}

void CAutoDlg::showExpiryTime( int userID, int expiryDay, int expiryMonth )
{
	CString czUserName = get_UserName(userID);
	if (czUserName.Compare(L"none") == 0) {
		MessageBox(L"Unknown PC!", L"Error", MB_OK);
		OnOK();
		return;
	}

	if (expiryDay <= 0 || expiryMonth <= 0) {
		MessageBox(L"Unknown Expiry!", L"Error", MB_OK);
		OnOK();
		return;
	}

	//arale
	if (m_bShowExpiryTime) {
		CString czText;
		czText.Format(L"User Name: %s -- Ngay Het Han: Ngay %d Thang %d", czUserName, expiryDay, expiryMonth);
		MessageBox(czText, L"Success!", MB_OK);
		//OnOK();
	}
}
