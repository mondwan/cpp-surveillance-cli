// NetServerFTP.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerFTP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerFTP dialog


CNetServerFTP::CNetServerFTP(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerFTP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerFTP)
	m_sUserName = _T("");
	m_sServerName = _T("");
	m_sPassword = _T("");
	m_nPort = 0;
	m_sPath = _T("");
	m_nMaxFileLen = 0;
	m_bANONYEnable = FALSE;
	m_bFTPEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CNetServerFTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerFTP)
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUserName);
	DDX_Control(pDX, IDC_EDIT_SERVER_NAME, m_editServerName);
	DDX_Control(pDX, IDC_EDIT_PSW, m_editPSW);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
	DDX_Control(pDX, IDC_EDIT_MAX_LENGTH, m_editMAXFileLen);
	DDX_Control(pDX, IDC_CHECK_FTP_ENABLE, m_checkFTPEnable);
	DDX_Control(pDX, IDC_CHECK_ANONY, m_checkANONYEnable);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddr);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_sUserName);
	DDX_Text(pDX, IDC_EDIT_SERVER_NAME, m_sServerName);
	DDX_Text(pDX, IDC_EDIT_PSW, m_sPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_PATH, m_sPath);
	DDX_Text(pDX, IDC_EDIT_MAX_LENGTH, m_nMaxFileLen);
	DDV_MinMaxInt(pDX, m_nMaxFileLen, 0, 65535);
	DDX_Check(pDX, IDC_CHECK_ANONY, m_bANONYEnable);
	DDX_Check(pDX, IDC_CHECK_FTP_ENABLE, m_bFTPEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerFTP, CDialog)
	//{{AFX_MSG_MAP(CNetServerFTP)
	ON_BN_CLICKED(IDC_CHECK_FTP_ENABLE, OnCheckFtpEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerFTP message handlers

void CNetServerFTP::OnOK() 
{
	m_ensure = TRUE;
	SaveConfig();
	CDialog::OnOK();
}

BOOL CNetServerFTP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerFTP::InitDlgInfo(SDK_FtpServerConfig *ftpCfg)
{
	m_ensure = FALSE;
	m_editPort.SetLimitText(5);
	m_editUserName.SetLimitText(31);
	m_editPSW.SetLimitText(31);
	m_editMAXFileLen.SetLimitText(5);
	m_editPath.SetLimitText(256);
	m_editServerName.SetLimitText(63);
	memcpy(&m_ftpCfg,ftpCfg,sizeof(SDK_FtpServerConfig));
	m_checkFTPEnable.SetCheck(m_ftpCfg.bEnable);
	m_sServerName = m_ftpCfg.Server.ServerName;
	m_nPort = m_ftpCfg.Server.Port;
	m_sUserName = m_ftpCfg.Server.UserName;
	m_sPassword = m_ftpCfg.Server.Password;
	m_nMaxFileLen = m_ftpCfg.iMaxFileLen;
	m_sPath = m_ftpCfg.cRemoteDir;
	m_checkANONYEnable.SetCheck(m_ftpCfg.Server.Anonymity);
	UpdateData(FALSE);
	OnCheckFtpEnable();
}

void CNetServerFTP::SaveConfig()
{
	UpdateData();
	m_ftpCfg.bEnable = m_checkFTPEnable.GetCheck();
	m_ftpCfg.Server.Anonymity = m_checkANONYEnable.GetCheck();
	strncpy(m_ftpCfg.Server.UserName,m_sUserName.GetBuffer(0),sizeof(m_ftpCfg.Server.UserName));
	strncpy(m_ftpCfg.Server.Password,m_sPassword.GetBuffer(0),sizeof(m_ftpCfg.Server.Password));
	strncpy(m_ftpCfg.Server.ServerName,m_sServerName.GetBuffer(0),sizeof(m_ftpCfg.Server.ServerName));
	strncpy(m_ftpCfg.cRemoteDir,m_sPath.GetBuffer(0),sizeof(m_ftpCfg.cRemoteDir));
	m_ftpCfg.iMaxFileLen = m_nMaxFileLen;
	m_ftpCfg.Server.Port = m_nPort;
}

void CNetServerFTP::OnCheckFtpEnable() 
{
	BOOL bEnable = m_checkFTPEnable.GetCheck();
	m_editMAXFileLen.EnableWindow(bEnable);
	m_checkANONYEnable.EnableWindow(bEnable);
	m_editPath.EnableWindow(bEnable);
	m_editPort.EnableWindow(bEnable);
	m_editPSW.EnableWindow(bEnable);
	m_editServerName.EnableWindow(bEnable);
	m_editUserName.EnableWindow(bEnable);
	m_IPAddr.EnableWindow(bEnable);
}
