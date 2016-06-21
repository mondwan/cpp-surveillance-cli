// NetServerPPPOE.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerPPPOE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerPPPOE dialog


CNetServerPPPOE::CNetServerPPPOE(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerPPPOE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerPPPOE)
	m_password = _T("");
	m_userName = _T("");
	//}}AFX_DATA_INIT
}


void CNetServerPPPOE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerPPPOE)
	DDX_Control(pDX, IDC_IPADDRESS, m_ipAddr);
	DDX_Control(pDX, IDC_CHECK_PPPOE_ENABLE, m_ctlPPPOEEnable);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_userName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerPPPOE, CDialog)
	//{{AFX_MSG_MAP(CNetServerPPPOE)
	ON_BN_CLICKED(IDC_CHECK_PPPOE_ENABLE, OnCheckPppoeEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerPPPOE message handlers

void CNetServerPPPOE::OnOK() 
{
	m_ensure = TRUE;
	SaveConfig();
	CDialog::OnOK();
}

BOOL CNetServerPPPOE::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_IP2)->ShowWindow(SW_HIDE);
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerPPPOE::InitDlgInfo(SDK_NetPPPoEConfig *pNetPPPOECfg)
{	
	m_ensure = FALSE;
	memcpy(&m_netPPPOECfg,pNetPPPOECfg,sizeof(SDK_NetPPPoEConfig));
	m_ctlPPPOEEnable.SetCheck(m_netPPPOECfg.Enable);
	m_userName = m_netPPPOECfg.Server.UserName;
	m_password = m_netPPPOECfg.Server.Password;
	BYTE c[4];
	memcpy(c,m_netPPPOECfg.addr.c,sizeof(m_netPPPOECfg.addr.c));
	m_ipAddr.SetAddress(c[0],c[1],c[2],c[3]);
	OnCheckPppoeEnable();
	UpdateData(FALSE);
}

void CNetServerPPPOE::OnCheckPppoeEnable() 
{
	BOOL bEnable = m_ctlPPPOEEnable.GetCheck();
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(bEnable);
}

void CNetServerPPPOE::SaveConfig()
{
	UpdateData();
	strcpy(m_netPPPOECfg.Server.UserName,m_userName);
	strcpy(m_netPPPOECfg.Server.Password,m_password);
	m_netPPPOECfg.Enable = m_ctlPPPOEEnable.GetCheck();
	BYTE c[4];
	m_ipAddr.GetAddress(c[0],c[1],c[2],c[3]);
	memcpy(m_netPPPOECfg.addr.c,c,sizeof(c));
}
