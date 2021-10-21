
// vlvAutomDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define Arale			0
#define trungNguyenTran 1
#define HaiAnh			2
#define HaiAnh1May		3
#define BiBonBa			4
#define TuanDongNat		5
#define	DungNgong		6
#define KhanhSpirit		7
#define TuanDongNat1May 8
#define HoangMinhTa		9
#define userTest		10
#define NguyenThach		11
#define HuyHoang		12
#define TuanDongNat6may 13
#define Jim				14
#define trungNguyenTran1may 15
#define user_LongNguyen		 16
#define userFreedom		17
#define user_TienDung	18


// CAutoDlg dialog
class CAutoDlg : public CVIEDialog
{
// Construction
public:
	CAutoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VLVAUTOM_DIALOG };

	afx_msg LRESULT OnEmulatorEvents(WPARAM wParam, LPARAM lParam);
	void OnEventManagerInit();
	void OnEventEmulatorInit(CEmulatorProcess* p);

	void AddNewEmulator(CGameInfo* pGame);

	static VOID CALLBACK _TimeEmulatorUpdate(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	void OnTimeEmulatorUpdate(CGameInfo* pGame);
	void			ShowEmulator();

	CGameInfo*		m_pGameSelected;
	DWORD			m_dwStartTime_RunAuto;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CVIEListCtrl m_lstEmulator;
	CMainTabCtrl m_tabMain;

	afx_msg void OnClose();

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);

	afx_msg void OnGameXoagialap();
	afx_msg void OnGameTurnOnAll();
	afx_msg void OnGameTurnOffAll();
	afx_msg void OnGameCopyGame();
	afx_msg void ResetActivityAllEmulator();

	afx_msg void OnLvnItemchangedListEmulator(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListEmulator(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListEmulator(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemCheckListGame(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnListGameItemMove(NMHDR *pNMHDR, LRESULT *pResult);
	void UpdateActivityOption(int actId,ACTIVITYINFOEX *pActEx);
	afx_msg void OnBnClickedButtonLic();
	int GetCurrentLeaderActivity(CGameInfo *pGame);
	CVIEButton m_btnLic;

	BOOL	CheckDlgInsideScreenDesktop(CRect &pRect);
	void ShowOptionDlg(CWnd* pShowDlg,CWnd* pDlgParent, int iDisTop = 30);

	void	OnChangeUI(int sel);
	void	checkMacAddress();
	void	checkTime();
	void	checkTimeTrungNguyenTran();
	void	checkTimeHaiAnh();
	void	checkTimeHaiAnh1May();
	void	checkTimeBiBonBa();
	void	checkTimeTuanDongNat();
	void	checkTimeDungNgong();
	void	checkTimeTest();

	void	checkTime(int iUser);
	void	checkTimeAgain();

	CString get_UserName(int iUser);
	afx_msg void OnBnClickedButtonSave();
	CVIEButton m_btnSave;

	void	check(int user = -1);
	void	checkMac(int iUser);
	void	checkTime(int iUser, int dayStart, int monthStart);
	void	showExpiryTime(int userID, int expiryDay, int expiryMonth);

	BOOL	m_bShowExpiryTime;
	CString czMacAddr[10];
};
