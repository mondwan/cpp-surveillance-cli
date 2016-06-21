// NetServerVVEye.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerVVEye.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerVVEye dialog


CNetServerVVEye::CNetServerVVEye(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerVVEye::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerVVEye)
	m_sDevName = _T("");
	m_sPwd = _T("");
	m_sServerIP = _T("");
	m_nPort = 0;
	m_sUserName = _T("");
	//}}AFX_DATA_INIT
}


void CNetServerVVEye::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerVVEye)
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Control(pDX, IDC_CHECK_CORP, m_checkCorp);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_sDevName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_sPwd);
	DDX_Text(pDX, IDC_EDIT_SERVER_IP, m_sServerIP);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_sUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerVVEye, CDialog)
	//{{AFX_MSG_MAP(CNetServerVVEye)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_BN_CLICKED(IDC_CHECK_CORP, OnCheckCorp)
	ON_EN_CHANGE(IDC_EDIT_DEVICE_NAME, OnChangeEditDeviceName)
	ON_EN_CHANGE(IDC_EDIT_PWD, OnChangeEditPwd)
	ON_EN_CHANGE(IDC_EDIT_SERVER_IP, OnChangeEditServerIp)
	ON_EN_CHANGE(IDC_EDIT_SERVER_PORT, OnChangeEditServerPort)
	ON_EN_CHANGE(IDC_EDIT_USERNAME, OnChangeEditUsername)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerVVEye message handlers



BOOL CNetServerVVEye::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE; 
	              
}

void CNetServerVVEye::InitDlgInfo(SDK_CONFIG_NET_VVEYE *pNetVVEyeCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netVVEyeCfg,pNetVVEyeCfg,sizeof(SDK_CONFIG_NET_VVEYE));
	m_checkEnable.SetCheck(m_netVVEyeCfg.bEnable);
	m_checkCorp.SetCheck(m_netVVEyeCfg.bCorpEnable);
	m_nPort = m_netVVEyeCfg.Server.Port;
	m_sDevName = m_netVVEyeCfg.szDeviceName;
	m_sPwd = m_netVVEyeCfg.Server.Password;
	m_sServerIP = m_netVVEyeCfg.Server.ServerName;
	m_sUserName = m_netVVEyeCfg.Server.UserName;
	UpdateData(FALSE);
	OnCheckEnable();
	OnCheckCorp();
}

void CNetServerVVEye::OnCheckEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	BOOL bEnableCorp = m_checkCorp.GetCheck();
	((CEdit*)GetDlgItem(IDC_EDIT_SERVER_PORT))->EnableWindow(bEnable && bEnableCorp);
	((CEdit*)GetDlgItem(IDC_EDIT_SERVER_NAME))->EnableWindow(bEnable && bEnableCorp);
	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_DEVICE_NAME))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_PWD))->EnableWindow(bEnable);
	m_checkCorp.EnableWindow(bEnable);
}

void CNetServerVVEye::OnCheckCorp() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	BOOL bEnableCorp = m_checkCorp.GetCheck();
	((CEdit*)GetDlgItem(IDC_EDIT_SERVER_PORT))->EnableWindow(bEnable && bEnableCorp);
	((CEdit*)GetDlgItem(IDC_EDIT_SERVER_NAME))->EnableWindow(bEnable && bEnableCorp);
}

void CNetServerVVEye::OnChangeEditDeviceName() 
{
	UpdateData();
	if (m_sDevName.GetLength() > 40)
	{
		m_sDevName = m_sDevName.Left(40);
		UpdateData(FALSE);
	}
}

void CNetServerVVEye::OnChangeEditPwd() 
{
	UpdateData();
	if (m_sPwd.GetLength() > 40)
	{
		m_sPwd = m_sPwd.Left(40);
		UpdateData(FALSE);
	}
}

void CNetServerVVEye::OnChangeEditServerIp() 
{
	UpdateData();
	if (m_sServerIP.GetLength() > 40)
	{
		m_sServerIP = m_sServerIP.Left(40);
		UpdateData(FALSE);
	}
}

void CNetServerVVEye::OnChangeEditServerPort() 
{
	UpdateData();
	if (m_nPort > 65535)
	{
		m_nPort = 65535;
		UpdateData(FALSE);
	}
	else if (m_nPort < 0)
	{
		m_nPort = 0;
		UpdateData(FALSE);
	}
}

void CNetServerVVEye::OnChangeEditUsername() 
{
	UpdateData();
	if (m_sUserName.GetLength() > 40)
	{
		m_sUserName = m_sUserName.Left(40);
		UpdateData(FALSE);
	}
}

void CNetServerVVEye::OnOK() 
{
	m_ensure = TRUE;
	UpdateData();
	m_netVVEyeCfg.bCorpEnable = m_checkCorp.GetCheck();
	m_netVVEyeCfg.bEnable = m_checkEnable.GetCheck();
	strncpy(m_netVVEyeCfg.szDeviceName,m_sDevName.GetBuffer(0),sizeof(m_netVVEyeCfg.szDeviceName));
	strncpy(m_netVVEyeCfg.Server.ServerName,m_sServerIP.GetBuffer(0),sizeof(m_netVVEyeCfg.Server.ServerName));
	strncpy(m_netVVEyeCfg.Server.Password,m_sPwd.GetBuffer(0),sizeof(m_netVVEyeCfg.Server.Password));
	strncpy(m_netVVEyeCfg.Server.UserName,m_sUserName.GetBuffer(0),sizeof(m_netVVEyeCfg.Server.UserName));
	m_netVVEyeCfg.Server.Port = m_nPort;
	CDialog::OnOK();
}
