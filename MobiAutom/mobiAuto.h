
// vlvAutom.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include <VIEControls/VIECtrl.h>
#include <Log.h>
#include <Utils.h>

#include <Crypto\JWT.h>
#include <Crypto\AES.h>
#include <Crypto\MD5.h>

#include <AIGLicense/AIGLicense.h>

#include "resource.h"		// main symbols

#include "../Common/global_windows.h"

#include "AutoManagerEx.h"

#include "ActivitySetting.h"
#include "MainTabCtrl.h"
#include "GameManager.h"

#include "mobiAutoDlg.h"

// CAutoApp:
// See vlvAutom.cpp for the implementation of this class
//


#define g_pMainDlg		theApp.m_pMainDlg
#define g_pAutoManager	theApp.m_pAutoManager
#define g_pGameManager	theApp.m_pGameManager
#define g_pGame			theApp.m_pGame
class CAutoApp : public CWinAppEx
{
public:
	CAutoDlg*		m_pMainDlg;
	CAutoManagerEx*	m_pAutoManager;	
	CGameManager*	m_pGameManager;

	CVIEToolTip*	m_pUnregisterToolTip;
	INFOLIST		m_InfoList;	//thong tin dua vao cho License.aig
	BOOL InitLicense();

	static BOOL		_ApiCallback( APICBType cbType, LPVOID lParam );
public:
	CAutoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

	BOOL			CheckLicense(LICType licType,LPCWSTR lpName,LPCWSTR lpServer,UINT uFuncId);
	BOOL			CheckLicense(CGameInfo *pGame);
	void			UpdateLicenseActivityList(CGameInfo *pGame);
	void			UpdateLicenseActivityExList(CGameInfo *pGame);

	static UINT		_ThreadLimitedLicenseAlert(LPVOID lpParam);
	void			LimitedLicenseAlert();
	void			DisplayUnregisterToolTip(int x, int y);
	
	void			UpdateAllLicenses();
// Implementation

	DECLARE_MESSAGE_MAP()

	
};

extern CAutoApp theApp;