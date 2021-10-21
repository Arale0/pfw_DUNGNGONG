#include "StdAfx.h"
#include "mobiAuto.h"
#include "AutoManagerEx.h"
#include "DeviceManagerEx.h"


#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#include "document.h"
#include "writer.h"
using namespace rapidjson;


IMPLEMENT_DYNCREATE(CAutoManagerEx, CAutoManager)

CAutoManagerEx::CAutoManagerEx(void)
{
}

CAutoManagerEx::~CAutoManagerEx(void)
{

}

void CAutoManagerEx::SaveEmulators()
{
	CString szFile;
	szFile.Format(L"%s\\emulators.json", m_szPathSettings);
	if (PathFileExists(szFile)) _wrename(szFile, szFile + L".bk");

	Document json;
	Document::AllocatorType& alt = json.GetAllocator();
	Value& oRoot = json.SetObject();
	Value sValue(kStringType);

	//Value oGameApp(kObjectType);
	//oGameApp.AddMember("iGameApp", g_pDataShared->m_pShared->iGameApp, alt);
	//oGameApp.AddMember("chkSaveGameApp", g_pDataShared->m_pShared->chkSaveGameApp, alt);
	//oRoot.AddMember("GameApp", oGameApp, alt);


	if (!lstPath.IsEmpty()) {
		Value aTypes(kArrayType);
		for (POSITION pos = lstPath.GetHeadPosition(); pos != NULL;)
		{
			CEmulatorPath* p = lstPath.GetNext(pos);
			Value oType(kObjectType);
			oType.AddMember("t", p->emulType, alt);
			sValue.SetString(CUtils::_W2A(p->emulExecute), alt);
			oType.AddMember("e", sValue, alt);
			sValue.SetString(CUtils::_W2A(p->emulHandle), alt);
			oType.AddMember("h", sValue, alt);

			aTypes.PushBack(oType, alt);
		}
		oRoot.AddMember("types", aTypes, alt);
	}

	CPtrList* plstGame = g_pGameManager->GetListGame();
	if (!plstGame->IsEmpty()) {
		Value aNames(kArrayType);
		for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
		{
			CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
			Value oName(kObjectType);
			oName.AddMember("t", pGame->m_eType, alt);
			sValue.SetString(CUtils::_W2A(pGame->m_czVMName), alt);
			oName.AddMember("n", sValue, alt);
			sValue.SetString(pGame->_czFakeName, alt);
			oName.AddMember("f", sValue, alt);
			aNames.PushBack(oName, alt);

			SaveGameConfig(pGame);
		}

		oRoot.AddMember("names", aNames, alt);
	}
	
	LOGA_DEBUG("Save emulator.....");

	StringBuffer buff;
	Writer<StringBuffer> writer(buff);
	json.Accept(writer);

	CFile f;
	if (f.Open(szFile, CFile::modeCreate | CFile::modeReadWrite)) {
		f.Write(buff.GetString(), buff.GetSize());
		f.Close();
	}
}

void CAutoManagerEx::SaveGameConfig( CGameInfo* pGame )
{
	if (!pGame) return;
	WCHAR* czVMName = pGame->m_czVMName;
	if (czVMName[0] == 0) return;
	CMD5 md5;
	CString szFile;
	szFile.Format(L"%s\\%s.json", m_szPathSettings, md5.FromStringW(czVMName).MakeUpper());

	Document json;
	Document::AllocatorType& alt = json.GetAllocator();
	Value& oRoot = json.SetObject();
	Value sValue(kStringType);

	//SAVE CONTROL/////////////////////////////////////
	Value arrActivities(kArrayType);
	ACTIVITYTAB* pActivityTab = pGame->GetActivityTab();
	for (int i = 0; i < MAX_NUM_ACTIVITY; ++i)
	{
		Value oActivity(kObjectType);
		sValue.SetString(pActivityTab->lstActivity[i].szAlias, alt);
		oActivity.AddMember("alias", sValue, alt);
		oActivity.AddMember("check", pActivityTab->lstActivity[i].bChecked, alt);
		oActivity.AddMember("index", pGame->GetDictionaryItemIndex(pActivityTab->lstActivity[i].iId), alt);

		arrActivities.PushBack(oActivity, alt);
	}
	oRoot.AddMember("activities", arrActivities, alt);
	
	LOGINTAB* pLoginTab = pGame->GetLoginTab();
	Value oLogin(kObjectType);
	//oLogin.AddMember("accountmode", pLoginTab->iAccountMode, alt);
	sValue.SetString(pLoginTab->accountFixed.publisherAccount.czUsername, alt);
	oLogin.AddMember("username", sValue, alt);
	sValue.SetString(pLoginTab->accountFixed.publisherAccount.czPassword, alt);
	oLogin.AddMember("password", sValue, alt);
	sValue.SetString(pLoginTab->accountFixed.roleLogin.czRoleName, alt);
	oLogin.AddMember("rolename", sValue, alt);
	oLogin.AddMember("roleindex", pLoginTab->accountFixed.roleLogin.idxPlayer, alt);
	oLogin.AddMember("serverindex", pLoginTab->accountFixed.roleLogin.iServer, alt);
	oLogin.AddMember("iRoleNo", pLoginTab->accountFixed.roleLogin.iRoleNo, alt);

	oRoot.AddMember("login", oLogin, alt);


	_LIST_GIAODICH* pGiaoDich = pGame->GetGiaoDich();
	Value oGiaodich(kObjectType);
	sValue.SetString(pGiaoDich->czItem1, alt);
	oGiaodich.AddMember("czItem1", sValue, alt);
	sValue.SetString(pGiaoDich->czItem2, alt);
	oGiaodich.AddMember("czItem2", sValue, alt);
	sValue.SetString(pGiaoDich->czItem3, alt);
	oGiaodich.AddMember("czItem3", sValue, alt);
	sValue.SetString(pGiaoDich->czItem4, alt);
	oGiaodich.AddMember("czItem4", sValue, alt);
	sValue.SetString(pGiaoDich->czItem5, alt);
	oGiaodich.AddMember("czItem5", sValue, alt);
	sValue.SetString(pGiaoDich->czItem6, alt);
	oGiaodich.AddMember("czItem6", sValue, alt);
	sValue.SetString(pGiaoDich->czItem7, alt);
	oGiaodich.AddMember("czItem7", sValue, alt);
	sValue.SetString(pGiaoDich->czItem8, alt);
	oGiaodich.AddMember("czItem8", sValue, alt);
	sValue.SetString(pGiaoDich->czItem9, alt);
	oGiaodich.AddMember("czItem9", sValue, alt);
	sValue.SetString(pGiaoDich->czItem10, alt);
	oGiaodich.AddMember("czItem10", sValue, alt);
	sValue.SetString(pGiaoDich->czItem11, alt);
	oGiaodich.AddMember("czItem11", sValue, alt);
	sValue.SetString(pGiaoDich->czItem12, alt);
	oGiaodich.AddMember("czItem12", sValue, alt);
	sValue.SetString(pGiaoDich->czItem13, alt);
	oGiaodich.AddMember("czItem13", sValue, alt);

	oGiaodich.AddMember("bSellOrangeEquips", pGiaoDich->bSellOrangeEquips, alt);
	oGiaodich.AddMember("iSellPercent", pGiaoDich->iSellPercent, alt);
	oGiaodich.AddMember("iSellByLevel", pGiaoDich->iSellByLevel, alt);
	oGiaodich.AddMember("iCostMode", pGiaoDich->iCostMode, alt);
	oGiaodich.AddMember("bTradeSkip", pGiaoDich->bTradeSkip, alt);

	oRoot.AddMember("giaodich", oGiaodich, alt);

	//SAVE OPTIONTAB/////////////////////////////////////
	OPTIONTAB* pOptionTab = pGame->GetOptionTab();
	Value oOptionTab(kObjectType);
	//tuy chon
	oOptionTab.AddMember("bFuli", pOptionTab->bFuli, alt);
	oOptionTab.AddMember("bAchievement", pOptionTab->bAchievement, alt);

	//tui
	oOptionTab.AddMember("bDeWhite", pOptionTab->bDeWhite, alt);
	oOptionTab.AddMember("bDeBlue", pOptionTab->bDeBlue, alt);
	oOptionTab.AddMember("bDeViolet", pOptionTab->bDeViolet, alt);
	oOptionTab.AddMember("iDeMinute", pOptionTab->iDeMinute, alt);
	oOptionTab.AddMember("bBagUseEquips", pOptionTab->bBagUseEquips, alt);
	oOptionTab.AddMember("bBagSellStone", pOptionTab->bBagSellStone, alt);
	oOptionTab.AddMember("bBagInFb", pOptionTab->bBagInFb, alt);
	oOptionTab.AddMember("bCleanBag", pOptionTab->bCleanBag, alt);
	oOptionTab.AddMember("bTachTrangBiKhoa", pOptionTab->bTachTrangBiKhoa, alt);
	oOptionTab.AddMember("bDungTrangBi", pOptionTab->bDungTrangBi, alt);
	oOptionTab.AddMember("bTachTrangBiLcCao", pOptionTab->bTachTrangBiLcCao, alt);
	oOptionTab.AddMember("bBanDaAoTien", pOptionTab->bBanDaAoTien, alt);
	oOptionTab.AddMember("bBanBua", pOptionTab->bBanBua, alt);
	oOptionTab.AddMember("bBanDaCanKhon", pOptionTab->bBanDaCanKhon, alt);
	oOptionTab.AddMember("bOptimizeCPU", pOptionTab->bOptimizeCPU, alt);
	oOptionTab.AddMember("iOptionFPS", pOptionTab->iOptionFPS, alt);
	oOptionTab.AddMember("iAmountOfPatchHP", pOptionTab->iAmountOfPatchHP, alt);
	oOptionTab.AddMember("iAmountOfPatchMP", pOptionTab->iAmountOfPatchMP, alt);
	oOptionTab.AddMember("bAutoBuyPatch", pOptionTab->bAutoBuyPatch, alt);
	oOptionTab.AddMember("iHPLevel", pOptionTab->iHPLevel, alt);
	oOptionTab.AddMember("iMPLevel", pOptionTab->iMPLevel, alt);
	oOptionTab.AddMember("bAutoBuyPatch2", pOptionTab->bAutoBuyPatch2, alt);
	oOptionTab.AddMember("bRunGameWhenCrash", pOptionTab->bRunGameWhenCrash, alt);
	oOptionTab.AddMember("bSellCertification", pOptionTab->bSellCertification, alt);
	oOptionTab.AddMember("bRecDynamic", pOptionTab->bRecDynamic, alt);
	oOptionTab.AddMember("bOptimizeCPUAct", pOptionTab->bOptimizeCPUAct, alt);
	oOptionTab.AddMember("bCheckMail", pOptionTab->bCheckMail, alt);
	oOptionTab.AddMember("bGop", pOptionTab->bGop, alt);
	oOptionTab.AddMember("bBanNgLieuCam59", pOptionTab->bBanNgLieuCam59, alt);
	oOptionTab.AddMember("bTachTrangBiCam59", pOptionTab->bTachTrangBiVang, alt);
	oOptionTab.AddMember("bCdTuChan", pOptionTab->bCdTuChan, alt);
	oOptionTab.AddMember("bTachGold59", pOptionTab->bTachGold59, alt);
	oOptionTab.AddMember("bTachGold69", pOptionTab->bTachGold69, alt);
	oOptionTab.AddMember("bTachGold79", pOptionTab->bTachGold79, alt);
	oOptionTab.AddMember("bTachGold89", pOptionTab->bTachGold89, alt);
	oOptionTab.AddMember("bTachGoldAllLV", pOptionTab->bTachGoldAllLV, alt);
	oOptionTab.AddMember("bBanPhuLinh", pOptionTab->bBanPhuLinh, alt);
	oOptionTab.AddMember("bSellOther", pOptionTab->bSellOther, alt);
	oOptionTab.AddMember("bUseFairyEgg", pOptionTab->bUseFairyEgg, alt);
	oOptionTab.AddMember("bSell_BiQuyenCoDai", pOptionTab->bSell_BiQuyenCoDai, alt);
	oOptionTab.AddMember("bSell_DaThienCanh", pOptionTab->bSell_DaThienCanh, alt);
	oOptionTab.AddMember("bBagAnhHon", pOptionTab->bBagAnhHon, alt);
	oOptionTab.AddMember("bTradePriority", pOptionTab->bTradePriority, alt);
	oOptionTab.AddMember("iBagCleanType", pOptionTab->iBagCleanType, alt);
	oOptionTab.AddMember("iBagCleanPoint1", pOptionTab->iBagCleanPoint1, alt);
	oOptionTab.AddMember("iBagCleanPoint2", pOptionTab->iBagCleanPoint2, alt);
	oOptionTab.AddMember("bBagCleanPoint1", pOptionTab->bBagCleanPoint1, alt);
	oOptionTab.AddMember("bBagCleanPoint2", pOptionTab->bBagCleanPoint2, alt);
	oOptionTab.AddMember("bBagSellSoul", pOptionTab->bBagSellSoul, alt);
	oOptionTab.AddMember("bBagChangeMapYuanLing", pOptionTab->bBagChangeMapYuanLing, alt);
	oOptionTab.AddMember("bUsePatchRelive", pOptionTab->bUsePatchRelive, alt);


	oOptionTab.AddMember("bGetSilverBox", pOptionTab->bGetSilverBox, alt);

	//tru thien phu do
	oOptionTab.AddMember("bTruThienGoAllTime", pOptionTab->bTruThienGoAllTime, alt);
	oOptionTab.AddMember("bTruThienSweepOnly", pOptionTab->bTruThienSweepOnly, alt);
	
	//pb hoang hon
	oOptionTab.AddMember("iHHDifficult", pOptionTab->iHHDifficult, alt);
	oOptionTab.AddMember("iHHCountTime", pOptionTab->iHHCountTime, alt);
	oOptionTab.AddMember("bHHLeaderSkip", pOptionTab->bHHLeaderSkip, alt);
	oOptionTab.AddMember("bHHMemAutoSearch", pOptionTab->bHHMemAutoSearch, alt);

	//ap tieu
	oOptionTab.AddMember("bTVNotFollow", pOptionTab->bTVNotFollow, alt);
	oOptionTab.AddMember("bVTCleanBag", pOptionTab->bVTCleanBag, alt);

	//pb tu chan
	oOptionTab.AddMember("iTCDifficult", pOptionTab->iTCDifficult, alt);
	oOptionTab.AddMember("iTCCountTime", pOptionTab->iTCCountTime, alt);
	oOptionTab.AddMember("bTCLeaderSkip", pOptionTab->bTCLeaderSkip, alt);
	oOptionTab.AddMember("bTCMemAutoSearch", pOptionTab->bTCMemAutoSearch , alt);
	oOptionTab.AddMember("bTC2TimeToFinished", pOptionTab->bTC2TimeToFinished , alt);

	//da ngong cuong
	oOptionTab.AddMember("bDNCBuyByGold", pOptionTab->bDNCBuyByGold, alt);
	oOptionTab.AddMember("iDNCAmountOf", pOptionTab->iDNCAmountOf, alt);

	//truc diet ac linh
	oOptionTab.AddMember("bTDALPlayerSet", pOptionTab->bTDALPlayerSet, alt);
	oOptionTab.AddMember("bTDALFollowLeader", pOptionTab->bTDALFollowLeader, alt);
	oOptionTab.AddMember("bTDALNotCheckCountTime", pOptionTab->bTDALNotCheckCountTime, alt);
	oOptionTab.AddMember("bTDALOpenSetting", pOptionTab->bTDALOpenSetting, alt);
	oOptionTab.AddMember("bTDALTimeGotoBoss", pOptionTab->bTDALTimeGotoBoss, alt);
	oOptionTab.AddMember("iTDALTime", pOptionTab->iTDALTime, alt);

	//quyet dau dinh cao
	oOptionTab.AddMember("bQDDCRandom", pOptionTab->bQDDCRandom, alt);

	//tho san tien thuong
	oOptionTab.AddMember("iTSTTBossLevel", pOptionTab->iTSTTBossLevel, alt);

	//tang bao do
	oOptionTab.AddMember("bTBDGiaoDich", pOptionTab->bTBDGiaoDich, alt);
	oOptionTab.AddMember("bTBDTrung", pOptionTab->bTBDTrung, alt);
	oOptionTab.AddMember("bTBDCao", pOptionTab->bTBDCao, alt);


	oOptionTab.AddMember("iKhaoCoNo1", pOptionTab->iKhaoCoNo1, alt);
	oOptionTab.AddMember("iKhaoCoNo2", pOptionTab->iKhaoCoNo2, alt);
	oOptionTab.AddMember("iKhaoCoNo3", pOptionTab->iKhaoCoNo3, alt);

	oOptionTab.AddMember("iPercentGdTBD", pOptionTab->iPercentGdTBD, alt);
	oOptionTab.AddMember("iPercentGdThienCoTai", pOptionTab->iPercentGdThienCoTai, alt);
	oOptionTab.AddMember("iPercentGdVang59", pOptionTab->iPercentGdVang59, alt);

	oRoot.AddMember("option", oOptionTab, alt);

	//SAVE TEAMTAB
	TEAMTAB* pTeamTab = pGame->GetTeamTab();
	Value oTeamTab(kObjectType);
	sValue.SetString(pTeamTab->czLeaderInMemberMode, alt);
	oTeamTab.AddMember("czLeaderInMemberMode", sValue, alt);
	Value arrMembers(kArrayType);
	for(int i =0 ; i < MAX_NUM_TEAMMEMBER; i++){
		Value oMembers(kObjectType);
		sValue.SetString(pTeamTab->membersInLeaderMode[i].czTeamName, alt);
		oMembers.AddMember("czTeamName", sValue, alt);
		arrMembers.PushBack(oMembers, alt);
	}
	oTeamTab.AddMember("iTeamMode", pTeamTab->iTeamMode, alt);
	oTeamTab.AddMember("members", arrMembers, alt);

	oTeamTab.AddMember("bJiebai", pTeamTab->teamOption.bJiebai, alt);
	oTeamTab.AddMember("bKickMembers", pTeamTab->teamOption.bKickMembers, alt);
	oTeamTab.AddMember("bMemberAcceptJiebai", pTeamTab->teamOption.bMemberAcceptJiebai, alt);
	oTeamTab.AddMember("bMemAcceptFriendsInvite", pTeamTab->teamOption.bMemAcceptFriendsInvite, alt);
	oTeamTab.AddMember("bInviteFriends", pTeamTab->teamOption.bInviteFriends, alt);
	oTeamTab.AddMember("iSLTV", pTeamTab->teamOption.iSLTV, alt);
	oTeamTab.AddMember("iTeamType", pTeamTab->teamOption.iTeamType, alt);

	oTeamTab.AddMember("bAloneCheckTeamTarget", pTeamTab->teamOption.bAloneCheckTeamTarget, alt);
	oTeamTab.AddMember("bAloneExitTeam", pTeamTab->teamOption.bAloneExitTeam, alt);
	oTeamTab.AddMember("iAloneCheckTime", pTeamTab->teamOption.iAloneCheckTime, alt);
	oRoot.AddMember("team", oTeamTab, alt);

	LOGA_DEBUG("Save game config.....");
	StringBuffer buff;
	Writer<StringBuffer> writer(buff);
	json.Accept(writer);

	CFile f;
	if (f.Open(szFile, CFile::modeCreate | CFile::modeReadWrite)) {
		f.Write(buff.GetString(), buff.GetSize());
		f.Close();
	}
}

void CAutoManagerEx::LoadEmulators()
{
	CString szFile;
	szFile.Format(L"%s\\emulators.json", m_szPathSettings);

	CFile f;
	if (!f.Open(szFile, CFile::modeRead | CFile::shareDenyWrite)) return;

	UINT uSize = (UINT)f.GetLength();
	CStringA szContextA('0', uSize);
	char* lpText = szContextA.GetBuffer();
	f.Read(lpText, uSize);
	f.Close();

	Document d;
	d.Parse(szContextA);
	if (d.HasParseError()) {
		LOGA_ERROR("ERROR Parse: %d", d.GetParseError());
		return;
	}

	if (d.HasMember("types")) {
		Value& aTypes = d["types"];
		int iCount = (int)aTypes.Size();
		for (int i = 0; i < iCount; i++) {
			Value& oType = aTypes[i];
			if (oType.IsNull()) continue;
			if (!oType.HasMember("t")) continue;
			if (!oType.HasMember("e")) continue;
			if (!oType.HasMember("h")) continue;
			EmulatorType eType = (EmulatorType)oType["t"].GetUint();
			if (GetEmulatorPath(eType)) continue;
			CEmulatorPath* pPath = new CEmulatorPath();
			pPath->emulType = eType;
			pPath->emulHandle = CUtils::_A2W(oType["h"].GetString());
			pPath->emulExecute = CUtils::_A2W(oType["e"].GetString());
			lstPath.AddTail(pPath);
		}
	}
	if (d.HasMember("names")) {
		Value& aNames = d["names"];
		int index;
		int iCount = (int)aNames.Size();
		for (int i = 0; i < iCount; i++)
		{
			Value& oName = aNames[i];
			if (oName.IsNull()) continue;
			if (!oName.HasMember("t")) continue;
			if (!oName.HasMember("n")) continue;
			if (!oName.HasMember("f")) continue;
			CString szVMName = CUtils::_A2W(oName["n"].GetString());
			CStringA szFakeNameA(oName["f"].GetString());
			CGameInfo* pGame = g_pGameManager->FindGameByVMName(szVMName, index);
			if (pGame) continue;
			pGame = g_pGameManager->GetFreeSlot();
			if (!pGame) return;
			wcscpy_s(pGame->m_czVMName, MAX_VMNAME_SIZE, szVMName);
			strcpy_s(pGame->_czFakeName, 64, szFakeNameA);
			//pGame->m_eType = (EmulatorType)oName["t"].GetUint();
			pGame->SetEmulType((EmulatorType)oName["t"].GetUint());
			pGame->SetGameStatus(gs_emulatorinactive);
			LOGA_ERROR("LoadEmulators :: AddNewEmulator .............");
			g_pMainDlg->AddNewEmulator(pGame);
			LoadGameConfig(pGame);
		}
	}
}

void CAutoManagerEx::LoadGameConfig( CGameInfo* pGame )
{
	if (!pGame) return;
	WCHAR* czVMName = pGame->m_czVMName;
	if (czVMName[0] == 0) return;
	CMD5 md5;
	CString szFile;
	szFile.Format(L"%s\\%s.json", m_szPathSettings, md5.FromStringW(czVMName).MakeUpper());

	CFile f;
	if (!f.Open(szFile, CFile::modeRead | CFile::shareDenyWrite)) return;

	UINT uSize = (UINT)f.GetLength();
	CStringA szContextA('0', uSize);
	char* lpText = szContextA.GetBuffer();
	f.Read(lpText, uSize);
	f.Close();

	Document d;
	d.Parse(szContextA);
	if (d.HasParseError()) {
		LOGA_ERROR("ERROR Parse: %d", d.GetParseError());
		return;
	}

	//ACTIVITYTAB
	if (d.HasMember("activities") && d["activities"].IsArray()) {
		ACTIVITYTAB* pActivityTab = pGame->GetActivityTab();
		int iCount = d["activities"].Size();
		//"activities":[{"alias":"nvchinhtuyen","check":0,"index":0}]
		for (int i = 0; i < iCount; ++i) {
			if (!d["activities"][i].HasMember("alias")) continue;
			CStringA szAlias = d["activities"][i]["alias"].GetString();
			ACTIVITYINFO* pai = pGame->GetActivityByAlias(szAlias);
			if (!pai) continue;
			Value& oActivity = d["activities"][i];
			if (oActivity.HasMember("check")) pai->bChecked = oActivity["check"].GetInt();

			if (oActivity.HasMember("index")) {
				int idx = oActivity["index"].GetInt();
				if (idx < MAX_NUM_ACTIVITY) pActivityTab->lstDictionary[idx] = pai->iId;
			}
		}
	}//if (d.HasMember("activities")) {
	if (d.HasMember("login")){
		LOGINTAB* pLoginTab = pGame->GetLoginTab();
		Value& oLogin = d["login"];
		CStringA szUsername("");
		CStringA szPassword("");
		CStringA szRoleName("");
		if(oLogin.HasMember("accountmode")) pLoginTab->iAccountMode = oLogin["accountmode"].GetInt();
		if(oLogin.HasMember("username")) szUsername = oLogin["username"].GetString();
		if(oLogin.HasMember("password")) szPassword = oLogin["password"].GetString();
		if(oLogin.HasMember("rolename")) szRoleName = oLogin["rolename"].GetString();
		if(oLogin.HasMember("roleindex")) pLoginTab->accountFixed.roleLogin.idxPlayer = oLogin["roleindex"].GetInt();
		if(oLogin.HasMember("serverindex")) pLoginTab->accountFixed.roleLogin.iServer = oLogin["serverindex"].GetInt();
		if(oLogin.HasMember("iRoleNo")) pLoginTab->accountFixed.roleLogin.iRoleNo = oLogin["iRoleNo"].GetInt();
		strcpy_s(pLoginTab->accountFixed.publisherAccount.czUsername, 64,szUsername.GetBuffer());
		strcpy_s(pLoginTab->accountFixed.publisherAccount.czPassword, 64,szPassword.GetBuffer());
		strcpy_s(pLoginTab->accountFixed.roleLogin.czRoleName, 64,szRoleName.GetBuffer());
		memcpy(&pGame->m_loginAccount, &pLoginTab->accountFixed, sizeof(LOGIN_ACCOUNT));
	}

	if (d.HasMember("giaodich")){
		_LIST_GIAODICH* pGiaodich = pGame->GetGiaoDich();
		Value& oGiaodich = d["giaodich"];
		CStringA szItem1("");
		CStringA szItem2("");
		CStringA szItem3("");
		CStringA szItem4("");
		CStringA szItem5("");
		CStringA szItem6("");
		CStringA szItem7("");
		CStringA szItem8("");
		CStringA szItem9("");
		CStringA szItem10("");
		CStringA szItem11("");
		CStringA szItem12("");
		CStringA szItem13("");

		if(oGiaodich.HasMember("czItem1")) szItem1 = oGiaodich["czItem1"].GetString();
		if(oGiaodich.HasMember("czItem2")) szItem2 = oGiaodich["czItem2"].GetString();
		if(oGiaodich.HasMember("czItem3")) szItem3 = oGiaodich["czItem3"].GetString();
		if(oGiaodich.HasMember("czItem4")) szItem4 = oGiaodich["czItem4"].GetString();
		if(oGiaodich.HasMember("czItem5")) szItem5 = oGiaodich["czItem5"].GetString();
		if(oGiaodich.HasMember("czItem6")) szItem6 = oGiaodich["czItem6"].GetString();
		if(oGiaodich.HasMember("czItem7")) szItem7 = oGiaodich["czItem7"].GetString();
		if(oGiaodich.HasMember("czItem8")) szItem8 = oGiaodich["czItem8"].GetString();
		if(oGiaodich.HasMember("czItem9")) szItem9 = oGiaodich["czItem9"].GetString();
		if(oGiaodich.HasMember("czItem10")) szItem10 = oGiaodich["czItem10"].GetString();
		if(oGiaodich.HasMember("czItem11")) szItem11 = oGiaodich["czItem11"].GetString();
		if(oGiaodich.HasMember("czItem12")) szItem12 = oGiaodich["czItem12"].GetString();
		if(oGiaodich.HasMember("czItem13")) szItem13 = oGiaodich["czItem13"].GetString();

		if(oGiaodich.HasMember("bSellOrangeEquips")) pGiaodich->bSellOrangeEquips = oGiaodich["bSellOrangeEquips"].GetInt();
		if(oGiaodich.HasMember("iSellByLevel")) pGiaodich->iSellByLevel = oGiaodich["iSellByLevel"].GetInt();
		if(oGiaodich.HasMember("iSellPercent")) pGiaodich->iSellPercent = oGiaodich["iSellPercent"].GetInt();
		if(oGiaodich.HasMember("bTradeSkip")) pGiaodich->bTradeSkip = oGiaodich["iSellPercent"].GetInt();

		strcpy_s(pGiaodich->czItem1, 100, szItem1.GetBuffer());
		strcpy_s(pGiaodich->czItem2, 100, szItem2.GetBuffer());
		strcpy_s(pGiaodich->czItem3, 100, szItem3.GetBuffer());
		strcpy_s(pGiaodich->czItem4, 100, szItem4.GetBuffer());
		strcpy_s(pGiaodich->czItem5, 100, szItem5.GetBuffer());
		strcpy_s(pGiaodich->czItem6, 100, szItem6.GetBuffer());
		strcpy_s(pGiaodich->czItem7, 100, szItem7.GetBuffer());
		strcpy_s(pGiaodich->czItem8, 100, szItem8.GetBuffer());
		strcpy_s(pGiaodich->czItem9, 100, szItem9.GetBuffer());
		strcpy_s(pGiaodich->czItem10, 100, szItem10.GetBuffer());
		strcpy_s(pGiaodich->czItem11, 100, szItem11.GetBuffer());
		strcpy_s(pGiaodich->czItem12, 100, szItem12.GetBuffer());
		strcpy_s(pGiaodich->czItem13, 100, szItem13.GetBuffer());

		//pGame->m_bSyncGiaoDich = TRUE;
	}

	if (d.HasMember("option") && d["option"].IsObject()) {
		Value& oOption = d["option"];
		OPTIONTAB* pOptionTab = pGame->GetOptionTab();
		
		//tuy chon
		if (oOption.HasMember("bFuli")) pOptionTab->bFuli		= oOption["bFuli"].GetInt();
		if (oOption.HasMember("bAchievement")) pOptionTab->bAchievement	= oOption["bAchievement"].GetInt();
		if (oOption.HasMember("bDeWhite")) pOptionTab->bDeWhite		= oOption["bDeWhite"].GetInt();
		if (oOption.HasMember("bDeBlue")) pOptionTab->bDeBlue	= oOption["bDeBlue"].GetInt();
		if (oOption.HasMember("bDeViolet")) pOptionTab->bDeViolet		= oOption["bDeViolet"].GetInt();
		if (oOption.HasMember("iDeMinute")) pOptionTab->iDeMinute	= oOption["iDeMinute"].GetInt();

		if (oOption.HasMember("bBagUseEquips")) pOptionTab->bBagUseEquips	= oOption["bBagUseEquips"].GetInt();
		if (oOption.HasMember("bBagSellStone")) pOptionTab->bBagSellStone	= oOption["bBagSellStone"].GetInt();
		if (oOption.HasMember("bBagInFb")) pOptionTab->bBagInFb	= oOption["bBagInFb"].GetInt();
		if (oOption.HasMember("bCleanBag")) pOptionTab->bCleanBag	= oOption["bCleanBag"].GetInt();
		if (oOption.HasMember("bTachTrangBiKhoa")) pOptionTab->bTachTrangBiKhoa	= oOption["bTachTrangBiKhoa"].GetInt();
		if (oOption.HasMember("bDungTrangBi")) pOptionTab->bDungTrangBi	= oOption["bDungTrangBi"].GetInt();
		if (oOption.HasMember("bTachTrangBiLcCao")) pOptionTab->bTachTrangBiLcCao	= oOption["bTachTrangBiLcCao"].GetInt();
		if (oOption.HasMember("bBanDaAoTien")) pOptionTab->bBanDaAoTien	= oOption["bBanDaAoTien"].GetInt();
		if (oOption.HasMember("bBanBua")) pOptionTab->bBanBua	= oOption["bBanBua"].GetInt();
		if (oOption.HasMember("bBanDaCanKhon")) pOptionTab->bBanDaCanKhon	= oOption["bBanDaCanKhon"].GetInt();
		if (oOption.HasMember("bOptimizeCPU")) pOptionTab->bOptimizeCPU	= oOption["bOptimizeCPU"].GetInt();
		if (oOption.HasMember("iOptionFPS")) pOptionTab->iOptionFPS	= oOption["iOptionFPS"].GetInt();
		if (oOption.HasMember("iAmountOfPatchHP")) pOptionTab->iAmountOfPatchHP	= oOption["iAmountOfPatchHP"].GetInt();
		if (oOption.HasMember("iAmountOfPatchMP")) pOptionTab->iAmountOfPatchMP	= oOption["iAmountOfPatchMP"].GetInt();
		if (oOption.HasMember("bAutoBuyPatch")) pOptionTab->bAutoBuyPatch	= oOption["bAutoBuyPatch"].GetInt();
		if (oOption.HasMember("iHPLevel")) pOptionTab->iHPLevel	= oOption["iHPLevel"].GetInt();
		if (oOption.HasMember("iMPLevel")) pOptionTab->iMPLevel	= oOption["iMPLevel"].GetInt();
		if (oOption.HasMember("bAutoBuyPatch2")) pOptionTab->bAutoBuyPatch2	= oOption["bAutoBuyPatch2"].GetInt();
		if (oOption.HasMember("bRunGameWhenCrash")) pOptionTab->bRunGameWhenCrash	= oOption["bRunGameWhenCrash"].GetInt();
		if (oOption.HasMember("bSellCertification")) pOptionTab->bSellCertification	= oOption["bSellCertification"].GetInt();
		if (oOption.HasMember("bRecDynamic")) pOptionTab->bRecDynamic	= oOption["bRecDynamic"].GetInt();
		if (oOption.HasMember("bOptimizeCPUAct")) pOptionTab->bOptimizeCPUAct	= oOption["bOptimizeCPUAct"].GetInt();
		if (oOption.HasMember("bCheckMail")) pOptionTab->bCheckMail	= oOption["bCheckMail"].GetInt();
		if (oOption.HasMember("bGop")) pOptionTab->bGop	= oOption["bGop"].GetInt();
		if (oOption.HasMember("bBanNgLieuCam59")) pOptionTab->bBanNgLieuCam59	= oOption["bBanNgLieuCam59"].GetInt();
		if (oOption.HasMember("bTachTrangBiCam59")) pOptionTab->bTachTrangBiVang	= oOption["bTachTrangBiCam59"].GetInt();
		if (oOption.HasMember("bCdTuChan")) pOptionTab->bCdTuChan	= oOption["bCdTuChan"].GetInt();
		if (oOption.HasMember("bTachGold59")) pOptionTab->bTachGold59	= oOption["bTachGold59"].GetInt();
		if (oOption.HasMember("bTachGold69")) pOptionTab->bTachGold69	= oOption["bTachGold69"].GetInt();
		if (oOption.HasMember("bTachGold79")) pOptionTab->bTachGold79	= oOption["bTachGold79"].GetInt();
		if (oOption.HasMember("bTachGold89")) pOptionTab->bTachGold89	= oOption["bTachGold89"].GetInt();
		if (oOption.HasMember("bTachGoldAllLV")) pOptionTab->bTachGoldAllLV	= oOption["bTachGoldAllLV"].GetInt();
		if (oOption.HasMember("bBanPhuLinh")) pOptionTab->bBanPhuLinh	= oOption["bBanPhuLinh"].GetInt();
		if (oOption.HasMember("bSellOther")) pOptionTab->bSellOther	= oOption["bSellOther"].GetInt();
		if (oOption.HasMember("bUseFairyEgg")) pOptionTab->bUseFairyEgg	= oOption["bUseFairyEgg"].GetInt();
		if (oOption.HasMember("bSell_BiQuyenCoDai")) pOptionTab->bSell_BiQuyenCoDai	= oOption["bSell_BiQuyenCoDai"].GetInt();
		if (oOption.HasMember("bSell_DaThienCanh")) pOptionTab->bSell_DaThienCanh	= oOption["bSell_DaThienCanh"].GetInt();
		if (oOption.HasMember("bBagAnhHon")) pOptionTab->bBagAnhHon	= oOption["bBagAnhHon"].GetInt();
		if (oOption.HasMember("bTradePriority")) pOptionTab->bTradePriority	= oOption["bTradePriority"].GetInt();
		if (oOption.HasMember("iBagCleanType")) pOptionTab->iBagCleanType	= oOption["iBagCleanType"].GetInt();
		if (oOption.HasMember("iBagCleanPoint1")) pOptionTab->iBagCleanPoint1	= oOption["iBagCleanPoint1"].GetInt();
		if (oOption.HasMember("iBagCleanPoint2")) pOptionTab->iBagCleanPoint2	= oOption["iBagCleanPoint2"].GetInt();
		if (oOption.HasMember("bBagCleanPoint1")) pOptionTab->bBagCleanPoint1	= oOption["bBagCleanPoint1"].GetInt();
		if (oOption.HasMember("bBagCleanPoint2")) pOptionTab->bBagCleanPoint2	= oOption["bBagCleanPoint2"].GetInt();
		if (oOption.HasMember("bBagSellSoul")) pOptionTab->bBagSellSoul	= oOption["bBagSellSoul"].GetInt();
		if (oOption.HasMember("bBagChangeMapYuanLing")) pOptionTab->bBagChangeMapYuanLing	= oOption["bBagChangeMapYuanLing"].GetInt();
		if (oOption.HasMember("bUsePatchRelive")) pOptionTab->bUsePatchRelive	= oOption["bUsePatchRelive"].GetInt();


		if (oOption.HasMember("bGetSilverBox")) pOptionTab->bGetSilverBox	= oOption["bGetSilverBox"].GetInt();

		//tru thien phu do
		if (oOption.HasMember("bTruThienGoAllTime")) pOptionTab->bTruThienGoAllTime	= oOption["bTruThienGoAllTime"].GetInt();
		if (oOption.HasMember("bTruThienSweepOnly")) pOptionTab->bTruThienSweepOnly	= oOption["bTruThienSweepOnly"].GetInt();
		
		//pb hoang hon
		if (oOption.HasMember("iHHDifficult")) pOptionTab->iHHDifficult	= oOption["iHHDifficult"].GetInt();
		if (oOption.HasMember("iHHCountTime")) pOptionTab->iHHCountTime	= oOption["iHHCountTime"].GetInt();
		if (oOption.HasMember("bHHMemAutoSearch")) pOptionTab->bHHMemAutoSearch	= oOption["bHHMemAutoSearch"].GetInt();
		if (oOption.HasMember("bHHLeaderSkip")) pOptionTab->bHHLeaderSkip	= oOption["bHHLeaderSkip"].GetInt();

		//ap tieu
		if (oOption.HasMember("bTVNotFollow")) pOptionTab->bTVNotFollow	= oOption["bTVNotFollow"].GetInt();
		if (oOption.HasMember("bVTCleanBag")) pOptionTab->bVTCleanBag	= oOption["bVTCleanBag"].GetInt();


		//pb tu chan
		if (oOption.HasMember("iTCDifficult")) pOptionTab->iTCDifficult	= oOption["iTCDifficult"].GetInt();
		if (oOption.HasMember("iTCCountTime")) pOptionTab->iTCCountTime	= oOption["iTCCountTime"].GetInt();
		if (oOption.HasMember("bTCLeaderSkip")) pOptionTab->bTCLeaderSkip	= oOption["bTCLeaderSkip"].GetInt();
		if (oOption.HasMember("bTCMemAutoSearch")) pOptionTab->bTCMemAutoSearch	= oOption["bTCMemAutoSearch"].GetInt();
		if (oOption.HasMember("bTC2TimeToFinished")) pOptionTab->bTC2TimeToFinished	= oOption["bTC2TimeToFinished"].GetInt();


		//da ngong cuong
		if (oOption.HasMember("bDNCBuyByGold")) pOptionTab->bDNCBuyByGold	= oOption["bDNCBuyByGold"].GetInt();
		if (oOption.HasMember("iDNCAmountOf")) pOptionTab->iDNCAmountOf	= oOption["iDNCAmountOf"].GetInt();

		//truc diet ac linh
		if (oOption.HasMember("bTDALPlayerSet")) pOptionTab->bTDALPlayerSet	= oOption["bTDALPlayerSet"].GetInt();
		if (oOption.HasMember("bTDALFollowLeader")) pOptionTab->bTDALFollowLeader	= oOption["bTDALFollowLeader"].GetInt();
		if (oOption.HasMember("bTDALNotCheckCountTime")) pOptionTab->bTDALNotCheckCountTime	= oOption["bTDALNotCheckCountTime"].GetInt();
		if (oOption.HasMember("bTDALOpenSetting")) pOptionTab->bTDALOpenSetting	= oOption["bTDALOpenSetting"].GetInt();
		if (oOption.HasMember("bTDALTimeGotoBoss")) pOptionTab->bTDALTimeGotoBoss	= oOption["bTDALTimeGotoBoss"].GetInt();
		if (oOption.HasMember("iTDALTime")) pOptionTab->iTDALTime	= oOption["iTDALTime"].GetInt();

		//quyet dau dinh cao
		if (oOption.HasMember("bQDDCRandom")) pOptionTab->bQDDCRandom = oOption["bQDDCRandom"].GetInt();
		
		//tho san tien thuong
		if (oOption.HasMember("iTSTTBossLevel")) pOptionTab->iTSTTBossLevel = oOption["iTSTTBossLevel"].GetInt();

		//tang bao do
		if (oOption.HasMember("bTBDGiaoDich")) pOptionTab->bTBDGiaoDich = oOption["bTBDGiaoDich"].GetInt();
		if (oOption.HasMember("bTBDTrung")) pOptionTab->bTBDTrung = oOption["bTBDTrung"].GetInt();
		if (oOption.HasMember("bTBDCao")) pOptionTab->bTBDCao = oOption["bTBDCao"].GetInt();


		if (oOption.HasMember("iKhaoCoNo1")) pOptionTab->iKhaoCoNo1 = oOption["iKhaoCoNo1"].GetInt();

		if (oOption.HasMember("iKhaoCoNo2")) pOptionTab->iKhaoCoNo2 = oOption["iKhaoCoNo2"].GetInt();

		if (oOption.HasMember("iKhaoCoNo3")) pOptionTab->iKhaoCoNo3 = oOption["iKhaoCoNo3"].GetInt();

		if (oOption.HasMember("iPercentGdTBD")) pOptionTab->iPercentGdTBD = oOption["iPercentGdTBD"].GetInt();
		if (oOption.HasMember("iPercentGdThienCoTai")) pOptionTab->iPercentGdThienCoTai = oOption["iPercentGdThienCoTai"].GetInt();
		if (oOption.HasMember("iPercentGdVang59")) pOptionTab->iPercentGdVang59 = oOption["iPercentGdVang59"].GetInt();


		//pGame->m_bSyncOptionTab = TRUE;

	}

	if(d.HasMember("team")){
		Value& oTeamTab = d["team"];
		TEAMTAB *pTeamTab = pGame->GetTeamTab();
		if(oTeamTab.HasMember("iTeamMode")) pTeamTab->iTeamMode = oTeamTab["iTeamMode"].GetInt();
		if (oTeamTab.HasMember("bJiebai")) pTeamTab->teamOption.bJiebai	= oTeamTab["bJiebai"].GetInt();
		if (oTeamTab.HasMember("bKickMembers")) pTeamTab->teamOption.bKickMembers	= oTeamTab["bKickMembers"].GetInt();
		if (oTeamTab.HasMember("bMemberAcceptJiebai")) pTeamTab->teamOption.bMemberAcceptJiebai	= oTeamTab["bMemberAcceptJiebai"].GetInt();
		if (oTeamTab.HasMember("bMemAcceptFriendsInvite")) pTeamTab->teamOption.bMemAcceptFriendsInvite	= oTeamTab["bMemAcceptFriendsInvite"].GetInt();
		if (oTeamTab.HasMember("bInviteFriends")) pTeamTab->teamOption.bInviteFriends	= oTeamTab["bInviteFriends"].GetInt();
		if (oTeamTab.HasMember("iSLTV")) pTeamTab->teamOption.iSLTV	= oTeamTab["iSLTV"].GetInt();
		if (oTeamTab.HasMember("iTeamType")) pTeamTab->teamOption.iTeamType	= oTeamTab["iTeamType"].GetInt(); 

		if (oTeamTab.HasMember("bAloneCheckTeamTarget")) pTeamTab->teamOption.bAloneCheckTeamTarget	= oTeamTab["bAloneCheckTeamTarget"].GetInt();
		if (oTeamTab.HasMember("bAloneExitTeam")) pTeamTab->teamOption.bAloneExitTeam	= oTeamTab["bAloneExitTeam"].GetInt();
		if (oTeamTab.HasMember("iAloneCheckTime")) pTeamTab->teamOption.iAloneCheckTime	= oTeamTab["iAloneCheckTime"].GetInt();

		CStringA czLeader("");
		if(oTeamTab.HasMember("czLeaderInMemberMode")) czLeader = oTeamTab["czLeaderInMemberMode"].GetString();
		strcpy_s(pTeamTab->czLeaderInMemberMode, 64,czLeader.GetBuffer());
		if(oTeamTab.HasMember("members") && oTeamTab["members"].IsArray()){
			int countMembers = oTeamTab["members"].Size();
			for (int i = 0; i < countMembers; ++i) {
				Value& oMember = oTeamTab["members"][i];
				CStringA czMember("");
				if(oMember.HasMember("czTeamName"))		czMember = oMember["czTeamName"].GetString();
				if(i <MAX_NUM_TEAMMEMBER)
					strcpy_s(pTeamTab->membersInLeaderMode[i].czTeamName, 64,czMember.GetBuffer());
					
			}
		}

		//pTeamTab->uTimeUpdate = GetTickCount();
		pGame->UpdateTeam();
		pTeamTab->bUpdateNow = TRUE;
		pTeamTab->bSyncTeamOption = TRUE;
	}
	
}

CEmulatorPath* CAutoManagerEx::GetEmulatorPath( EmulatorType eType )
{
	for (POSITION pos = lstPath.GetHeadPosition(); pos != NULL;)
	{
		CEmulatorPath* p = lstPath.GetNext(pos);
		if (p->emulType == eType) return p;
	}
	return NULL;
}

BOOL CAutoManagerEx::SetRunEmulator( CGameInfo* pGameTmp )
{
	BOOL bReady = FALSE;
	CGameInfo* pGame = g_pGameManager->GetOrderRunEmulator();
	if (pGame) {
		if (!m_pRunEmulator) {
			bReady = pGame->m_bControl;
			m_pRunEmulator = pGame;
		}
		else {
			if (m_pRunEmulator == pGame) {
				if (!pGame->m_bControl) m_pRunEmulator = NULL;
			}
			else {
				int gs = m_pRunEmulator->GetGameStatus();
				if (gs == gs_none || gs > gs_calledemulator) {
					bReady = pGame->m_bControl;
					m_pRunEmulator = pGame;
				}
			}
		}
	}
	return bReady;
}

void CAutoManagerEx::RunEmulator( CGameInfo* pGame )
{
	if (!pGame->m_bControl) return;
	if (pGame->IsWindowActivated()) return;
	if (pGame->GetGameStatus() != gs_runemulator) return;
	//if (pGame->m_eType == EmulType_BlueStacks) {
	//	LOGW_WARNING(L"BlueStacks cannot auto run emulator");
	//	return;
	//}
	CEmulatorPath* pPath = GetEmulatorPath(pGame->m_eType);
	if (!pPath) return;
	CString szExe = pPath->emulExecute;
	LogWriteW(L"CEmulatorManagerEx::RunEmulator...[%s]", szExe);
	if (szExe.IsEmpty()) return;
	CString szPath = CUtils::GetPath(szExe);

	CString szAuto, szArgs;
	szAuto.Format(L"%s", szExe);

	switch (pGame->m_eType) {
	case EmulType_NoxPlayer:
		szArgs.Format(L" -clone:%s", pGame->m_czVMName);
		break;
	case EmulType_KOPlayer:
		szArgs.Format(L"KOPLAYER.exe -n %s", pGame->m_czVMName);
		break;
	case EmulType_LDPlayer:
	case EmulType_LDPlayer4:{
		CString szVMName(pGame->m_czVMName);
		CString szNum = szVMName.Mid(7);
		int idx = _wtoi(szNum.GetBuffer());
		LOGW_DEBUG(L"[%s][%s] = %d",szVMName,szNum,idx);
		szArgs.Format(L" index=%d|", idx);
						   }
		break;
	case EmulType_BlueStacks:
	case EmulType_BlueStacks64:
		szArgs.Format(L" -vmname %s", pGame->m_czVMName);							 
		break;
	case EmulType_BlueStacks5:
		szArgs.Format(L" --vmname %s", pGame->m_czVMName);							 
		break;
	default:
		szArgs.Format(L" %s", pGame->m_czVMName);
	}
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	CString msg;
	if (!CreateProcess(szAuto, szArgs.GetBuffer(), NULL, NULL, TRUE, 0, NULL, szPath, &si, &pi))
	{
		msg.Format(L"Không tìm thấy giả lập tại thư mục [%s], không thể mở giả lập.",szAuto);
		//msg.Format(L"Error: %d", GetLastError());
		AfxMessageBox(msg);
	}
	else {
		CloseHandle(pi.hProcess);  
		CloseHandle(pi.hThread);
		pGame->SetGameStatus(gs_calledemulator); 
	}
}

void CAutoManagerEx::ClearRunEmulator( CGameInfo* pGame )
{
	if (m_pRunEmulator && m_pRunEmulator == pGame) m_pRunEmulator = NULL;
}

void CAutoManagerEx::OnInitManager()
{
	CAutoManager::OnInitManager();
	m_pRunEmulator = NULL;
	m_szNameHook = "libautor.so";	
	

	AddFilter(new CEmulatorFilter(EMUL_HANDLE_LDPLAYER,		EmulType_LDPlayer));
	AddFilter(new CEmulatorFilter(EMUL_HANDLE_NOXPLAYER,	EmulType_NoxPlayer));
	AddFilter(new CEmulatorFilter(EMUL_HANDLE_MEMUPLAYER,	EmulType_MemuPlayer));
	AddFilter(new CEmulatorFilter(EMUL_HANDLE_PEAK,			EmulType_PeakPlayer));
	AddFilter(new CEmulatorFilter(EMUL_HANDLE_LDPLAYER4,	EmulType_LDPlayer4));
	AddFilter(new CEmulatorFilter(EMUL_HANDLE_BLUESTACKS,	EmulType_BlueStacks));
	AddFilter(new CEmulatorFilter(EMUL_HANDLE_BLUESTACKS64,	EmulType_BlueStacks64));
	AddFilter(new CEmulatorFilter(EMUL_HANDLE_BLUESTACKS5,	EmulType_BlueStacks5));

	LoadEmulators();

#ifdef BUILD_FLAG_DEBUG
	m_bBuildRelase = FALSE;
#else
	m_bBuildRelase = TRUE;
#endif

	g_pMainDlg->SendMessage(WM_MSG_EMULATOR_EVENT, EVENT_MANAGER_INIT, NULL);
	LOGA_INFO("SIZE OF GAMEINFO:%d",sizeof(CGameInfo));
	LoadAccountList();
}

void CAutoManagerEx::OnExitManager()
{
	LOGA_INFO("");
	SaveEmulators();

	CPtrList* plstGame = g_pGameManager->GetListGame();
	for (POSITION pos = plstGame->GetHeadPosition(); pos != NULL;)
	{
		CGameInfo* pGame = (CGameInfo*)plstGame->GetNext(pos);
		g_pMainDlg->KillTimer((UINT_PTR)pGame);//(pGame->uiTimerID);
		//LOGW_DEBUG(L"AUTO EXIT - [%s] KillTimer!", pGame->m_czVMName);
	}
	while (!lstPath.IsEmpty())
	{
		CEmulatorPath* p = lstPath.RemoveHead();
		delete p;
	}

	CAutoManager::OnExitManager();
}

void CAutoManagerEx::OnError( CONST CString& szError,CDeviceManager* pDevice )
{
	if (!pDevice){
		VIEMsgBox(szError,L"Thông báo lỗi",MB_OK|MB_ICONSTOP);
		ExitProcess(-1);
	}
	else{
		LOGW_ERROR(L"%s",szError);
	}
}

BOOL CAutoManagerEx::OnInitEmulator( CEmulatorProcess* pProcess )
{
	LOGA_INFO("");

	CAutoManager::OnInitEmulator(pProcess);
	EmulatorType eType = pProcess->GetType();
	//Kiem tra LDPlayer0
	if (pProcess->GetType() == EmulType_LDPlayer){
		if (pProcess->szVMName.Compare(L"leidian0") == 0){
			int iCount = GetCountEmulator(EmulType_LDPlayer);
			LogWrite(L" [%s] PID:%d COUNT:%d",pProcess->szVMName, pProcess->GetPID(),iCount );
			if (iCount > 0) return FALSE; 
		}
	}

	int index;
	//CGameInfo* pGame = g_pGameManager->FindGameByVMName(pProcess->szVMName, index);
	CGameInfo* pGame = g_pGameManager->FindGameByVMName(eType,pProcess->szVMName, index);
	BOOL bAddNew = FALSE;
	if (pGame == NULL) {
		pGame = g_pGameManager->GetFreeSlot();
		bAddNew = TRUE;
		if (!pGame) {
			CString s;
			s.Format(L"Maximum Games : %d", MAX_CLIENT_GAMEINFO);
			VIEMsgBox(s, L"Full Games!");
			ExitProcess(0);
			return FALSE;
		}
		else pGame->Reset();
	}//if (pGame == NULL){
	
	
	pGame->SetEmulType(pProcess->GetType());
	pGame->m_hWnd = pProcess->GetWndRoot();
	pGame->m_hWndControl = pProcess->GetWndControl(pGame->m_hWnd);

	pGame->m_uPortListen = pProcess->GetPortListening();
	pGame->m_dwEmulatorPID = pProcess->GetPID();
	pGame->m_dwEnginePID = pProcess->GetPlayerProcess()->GetPID();
	pGame->m_bHidden = pGame->m_hWnd != NULL ? !::IsWindowVisible(pGame->m_hWnd) : FALSE;
	pGame->m_chkHidden = pGame->m_bHidden;

	CEmulatorPath* pPath = GetEmulatorPath(pGame->m_eType);
	if (!pPath) {
		pPath = new CEmulatorPath();
		pPath->emulType = pGame->m_eType;
		pPath->emulHandle = pProcess->GetProcessFullName();
		pPath->emulExecute = pProcess->GetPlayerProcess()->GetProcessFullName();
		lstPath.AddTail(pPath);
	}

	BOOL bNewFakename = FALSE;
	if (IsWindow(pGame->m_hWnd)) {
		WCHAR czFakename[MAX_PATH];
		GetWindowText(pGame->m_hWnd, czFakename, MAX_PATH);
		CStringA szFakeNameA = CUtils::_W2A(czFakename);
		if (szFakeNameA.Compare(pGame->_czFakeName) != 0) bNewFakename = TRUE;
		strcpy_s(pGame->_czFakeName, 64, szFakeNameA);
		LOGA_WARNING("FAKE NAME:%s", pGame->_czFakeName);
	}

	pProcess->SetGameInfo(pGame);

	pProcess->pDevice = (CDeviceManagerEx*)AfxBeginThread(RUNTIME_CLASS(CDeviceManagerEx),0,0,CREATE_SUSPENDED);
	if (!pProcess->pDevice){
		LOGW_ERROR(L"???? pProcess->pDevice == NULL");
		return FALSE;
	}

	pProcess->pDevice->SetProcess(pProcess);
	pProcess->pDevice->SetAppName(TXT_GAME_APP);

	pProcess->pDevice->ResumeThread();

	WaitForSingleObject(pProcess->pDevice->m_hThread, 100);
	//SwitchToThread();	

	if (bAddNew) {
		LOGA_WARNING("bAddNew.........................");
		wcscpy_s(pGame->m_czVMName, MAX_VMNAME_SIZE, pProcess->szVMName);
		g_pMainDlg->SendMessage(WM_MSG_EMULATOR_EVENT, EVENT_EMULATOR_INIT, (LPARAM)pProcess);
	}
	//if (pGame->m_chkHidden) g_pMainDlg->m_lstEmulator.SetItemIcon(index, TAB_INDEX_GAMEHIDE, IDI_ICON_HIDE);	
	//if (bNewFakename) g_pMainDlg->m_lstEmulator.SetItemText(index, TAB_INDEX_EMULATOR, CUtils::_A2W(pGame->_czFakeName));
	
	if (pGame->GetGameStatus() <= gs_emulatorinactive) {
		pGame->SetGameStatus(gs_emulatorinit);
	}
	static int i = 0;

	LOGA_WARNING("log o day ........%d", i + 1);
	return TRUE;
}

void CAutoManagerEx::OnExitEmulator( CEmulatorProcess* pProcess )
{
	LOGA_INFO("");
	CGInfo* pGame = pProcess->GetGameInfo();
	if (pGame) pGame->SetGameStatus(gs_emulatorexit);
	if (pProcess->pDevice) pProcess->pDevice->ExitThread();

	CAutoManager::OnExitEmulator(pProcess);
}

void CAutoManagerEx::RemoveGame( int idx )
{
	CGameInfo *pGame = g_pGameManager->GetGameInfo(idx);
	if(pGame)
	{
		if(!pGame->IsWindowActivated()){ 
			g_pGameManager->RemoveGame(pGame);
			g_pMainDlg->KillTimer(pGame->uiTimerID);
			g_pMainDlg->m_lstEmulator.DeleteItem(idx);
		}
		else
		{
			MessageBox(NULL, L"Giả lập đang chạy, không thể xóa", L"Thông báo", MB_OK);
		}

	}
}

void CAutoManagerEx::RunEmulatorOrder()
{	
	if (m_pRunEmulator){		
		if (!m_pRunEmulator->IsWindowActivated()) return;

		GameStatus gs = m_pRunEmulator->GetGameStatus();
		if (gs == gs_gamenotrunning) return;
		if (gs == gs_none || gs >= gs_monoinited ) m_pRunEmulator = NULL;
		return;
	}

	CGameInfo* pGame = g_pGameManager->GetOrderRunEmulator();
	if (!pGame) {
		m_pRunEmulator = NULL; 
		return;
	}

	m_pRunEmulator = pGame;
	RunEmulator(pGame);
	if (pGame->GetGameStatus() != gs_calledemulator) m_pRunEmulator = NULL;
}

BOOL CAutoManagerEx::RunGameOrder(CGameInfo* pGame)
{
	//return TRUE;	//bo qua ham nay
	if (m_pRunEmulator == pGame) return TRUE;
	CGameInfo* p = g_pGameManager->GetOrderRunEmulator();
	if (p == pGame) return TRUE;	//emulator dang mo
	if (p) return FALSE;			//dang runEmulator

	p = g_pGameManager->GetOrderRunGame();
	if (pGame != p) return FALSE;

	//khong co RunEmulator nao dang mo
	if (m_pRunEmulator){
		GameStatus gs = m_pRunEmulator->GetGameStatus();
		if (gs != gs_gamenotrunning) {
			if (gs == gs_none || gs >= gs_monoinited ) m_pRunEmulator = NULL;	
		}				
		return FALSE;
	}

	m_pRunEmulator = pGame;
	return TRUE;
}

void CAutoManagerEx::LoadAccountList(){
	CString szFile;
	
	szFile.Format(L"%s\\Users\\accounts.json", m_szCurrentPath);
	m_AccountList2.LoadAccount(szFile);

}
void CAutoManagerEx::SaveAccountList(){

	CString szFolder;
	szFolder.Format(L"%s\\Users", m_szCurrentPath);
	if (!PathFileExists(szFolder)) CreateDirectory(szFolder,NULL);

	CString szFile;
	szFile.Format(L"%s\\Users\\accounts.json", m_szCurrentPath);
	m_AccountList2.SaveAccount(szFile);
}