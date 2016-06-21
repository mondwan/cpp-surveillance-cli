// NetServerSHISOU.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerSHISOU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerSHISOU dialog


CNetServerSHISOU::CNetServerSHISOU(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerSHISOU::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerSHISOU)
	m_sDevID = _T("");
	m_sServerIP = _T("");
	m_nPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerSHISOU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerSHISOU)
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_DEV_ID, m_sDevID);
	DDX_Text(pDX, IDC_EDIT_SERVER_IP, m_sServerIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 0, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerSHISOU, CDialog)
	//{{AFX_MSG_MAP(CNetServerSHISOU)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerSHISOU message handlers

BOOL CNetServerSHISOU::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CEdit*)GetDlgItem(IDC_EDIT_SERVER_IP))->SetLimitText(NET_NAME_PASSWORD_LEN);
	((CEdit*)GetDlgItem(IDC_EDIT_DEV_ID))->SetLimitText(NET_NAME_PASSWORD_LEN);
	((CEdit*)GetDlgItem(IDC_EDIT_PORT))->SetLimitText(5);
	CenterWindow();
	return TRUE;  
}

void CNetServerSHISOU::InitDlgInfo(SDK_CONFIG_NET_SHISOU *pNetSHISOUCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netSHISOUCfg,pNetSHISOUCfg,sizeof(SDK_CONFIG_NET_SHISOU));
	m_checkEnable.SetCheck(m_netSHISOUCfg.bEnable);
	m_nPort = m_netSHISOUCfg.Server.Port;
	m_sDevID = m_netSHISOUCfg.szSID;
	m_sServerIP = m_netSHISOUCfg.Server.ServerName;
	UpdateData(FALSE);
	OnCheckEnable();
}

void CNetServerSHISOU::OnCheckEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	((CEdit*)GetDlgItem(IDC_EDIT_SERVER_IP))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_DEV_ID))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_PORT))->EnableWindow(bEnable);
}

void CNetServerSHISOU::OnOK() 
{
	m_ensure = TRUE;
	UpdateData();
	m_netSHISOUCfg.bEnable = m_checkEnable.GetCheck();
	m_netSHISOUCfg.Server.Port = m_nPort;
	strncpy(m_netSHISOUCfg.Server.ServerName,m_sServerIP.GetBuffer(0),sizeof(m_netSHISOUCfg.Server.ServerName));
	strncpy(m_netSHISOUCfg.szSID,m_sDevID.GetBuffer(0),sizeof(m_netSHISOUCfg.szSID));
	CDialog::OnOK();
}
