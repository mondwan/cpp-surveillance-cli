// NetServerUPNP.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerUPNP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerUPNP dialog


CNetServerUPNP::CNetServerUPNP(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerUPNP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerUPNP)
	m_nHtppPort = 0;
	m_nMobilePort = 0;
	m_nTcpPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerUPNP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerUPNP)
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_HTTP_PORT, m_nHtppPort);
	DDV_MinMaxInt(pDX, m_nHtppPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_MOBILE_Port, m_nMobilePort);
	DDV_MinMaxInt(pDX, m_nMobilePort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_TCP_PORT, m_nTcpPort);
	DDV_MinMaxInt(pDX, m_nTcpPort, 0, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerUPNP, CDialog)
	//{{AFX_MSG_MAP(CNetServerUPNP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerUPNP message handlers

BOOL CNetServerUPNP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE; 
}

void CNetServerUPNP::InitDlgInfo(SDK_NetUPNPConfig *pNetUPNPCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netUPNPCfg,pNetUPNPCfg,sizeof(SDK_NetUPNPConfig));
	if (m_netUPNPCfg.bState && m_netUPNPCfg.bEnable)
	{
		m_nHtppPort = m_netUPNPCfg.iHTTPPort;
		m_nMobilePort = m_netUPNPCfg.iMobliePort;
		m_nTcpPort = m_netUPNPCfg.iMediaPort;
	}
	else
	{
		m_nHtppPort = 0;
		m_nMobilePort = 0;
		m_nTcpPort =0;
	}
	m_checkEnable.SetCheck(m_netUPNPCfg.bEnable);
	UpdateData(FALSE);
}

void CNetServerUPNP::OnOK() 
{
	m_ensure = TRUE;
	SaveConfig();
	CDialog::OnOK();
}

void CNetServerUPNP::SaveConfig()
{
	UpdateData();
	m_netUPNPCfg.bEnable = m_checkEnable.GetCheck();
}


