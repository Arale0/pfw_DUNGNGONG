#pragma once
#include <Autom\AutoManager.h>
#include "GameInfo.h"
#include "AccountList2.h"
#include "TeamList.h"
class CEmulatorPath {
public:
	CEmulatorPath() {};
	~CEmulatorPath() {};

	EmulatorType emulType;
	CString emulHandle;
	CString emulExecute;
};

class CAutoManagerEx : public CAutoManager
{
public:
	DECLARE_DYNCREATE(CAutoManagerEx)

	CAutoManagerEx(void);
	~CAutoManagerEx(void);

	void			SaveEmulators();
	void			SaveGameConfig(CGameInfo* pGame);
	void			LoadEmulators();
	void			LoadGameConfig(CGameInfo* pGame);
	CEmulatorPath*	GetEmulatorPath(EmulatorType eType);
	BOOL			SetRunEmulator(CGameInfo* pGame);
	void			RunEmulator(CGameInfo* pGame);	
	void			ClearRunEmulator(CGameInfo* pGame);
	void RemoveGame( int idx );
	void			RunEmulatorOrder();
	BOOL			RunGameOrder(CGameInfo* pGame);
protected:
	virtual void	OnInitManager();
	virtual void	OnExitManager();
	virtual void	OnError(CONST CString& szError,CDeviceManager* pDevice);
	virtual BOOL	OnInitEmulator(CEmulatorProcess* pProcess);
	virtual void	OnExitEmulator(CEmulatorProcess* pProcess);
		

	CList<CEmulatorPath*, CEmulatorPath*> lstPath;
	CGameInfo*		m_pRunEmulator;
public:
	CAccountList2	m_AccountList2;
	CTeamList		m_TeamList;
	void LoadAccountList();
	void SaveAccountList();
};
