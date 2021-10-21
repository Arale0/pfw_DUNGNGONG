// HelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mobiAuto.h"
#include "HelpDlg.h"


// CHelpDlg dialog

IMPLEMENT_DYNAMIC(CHelpDlg, CVIEChildDlg)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CVIEChildDlg(CHelpDlg::IDD, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CVIEChildDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_WEBSITE, m_btnWebsite);
	DDX_Control(pDX, IDC_BUTTON_FACEBOOK, m_btnFacebook);
	DDX_Control(pDX, IDC_BUTTON_FORUM, m_btnForum);
	DDX_Control(pDX, IDC_BUTTON_YOUTUBE, m_btnYoutube);
}


BOOL CHelpDlg::OnInitDialog()
{
	CVIEChildDlg::OnInitDialog();
	m_btnWebsite.SetIcon(IDI_ICON_ARROW,4,6,17,17);
	m_btnFacebook.SetIcon(IDI_ICON_ARROW,4,6,17,17);
	m_btnForum.SetIcon(IDI_ICON_ARROW,4,6,17,17);
	m_btnYoutube.SetIcon(IDI_ICON_ARROW,4,6,17,17);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CHelpDlg, CVIEChildDlg)
	ON_BN_CLICKED(IDC_BUTTON_WEBSITE, &CHelpDlg::OnBnClickedButtonWebsite)
	ON_BN_CLICKED(IDC_BUTTON_FACEBOOK, &CHelpDlg::OnBnClickedButtonFacebook)
	ON_BN_CLICKED(IDC_BUTTON_FORUM, &CHelpDlg::OnBnClickedButtonForum)
	ON_BN_CLICKED(IDC_BUTTON_YOUTUBE, &CHelpDlg::OnBnClickedButtonYoutube)
END_MESSAGE_MAP()


// CHelpDlg message handlers

void CHelpDlg::OnBnClickedButtonWebsite()
{
	ShellExecute(0, L"open", TEXT("http://aigato.vn"),0,0,SW_SHOW);
}

void CHelpDlg::OnBnClickedButtonFacebook()
{
	ShellExecute(0, L"open", TEXT("https://www.facebook.com/autogamemobile"),0,0,SW_SHOW);
}

void CHelpDlg::OnBnClickedButtonForum()
{
	ShellExecute(0, L"open", TEXT("http://forum.aigato.vn"),0,0,SW_SHOW);
}

void CHelpDlg::OnBnClickedButtonYoutube()
{
	ShellExecute(0, L"open", TEXT("https://www.youtube.com/channel/UCmYSoG-uvJTGBnqDed0ILBQ"),0,0,SW_SHOW);
}
