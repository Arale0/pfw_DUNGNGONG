#pragma once
class CTeam
{
public:
	CTeam(void);
	~CTeam(void);
public:
	int			iTeamID;
	int			iServer;
	int			iActivity;
	CGameInfo*	pMembers[MAX_NUM_TEAMMEMBER];
	BOOL		IsFull();
	BOOL		IsEmpty();
	void		AddGame(CGameInfo *pGame);
	void		RemoveGame(CGameInfo *pGame);
	void		UpdateGame();
	void		UpdateTeamMembers(CGameInfo *pGame);
	int			GetMembers();
	void LogInfo();
};
class CTeamList:CPtrList
{
public:
	int		m_iLastID;
	CTeamList(void);
	~CTeamList(void);
	void UpdateTeamList();
	void MatchTeamList(CPtrList* lstGame);
	void Clear();
	BOOL MatchTeam(CGameInfo *pGame);
	void LogInfo();
	CGameInfo* GetGameNeedTeamMatch();
	CGameInfo* GetGameNeedTeamMatch(CPtrList* lstGame);
	CTeam*		GetTeam(int teamid);
};
