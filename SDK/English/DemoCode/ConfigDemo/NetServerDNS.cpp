// NetServerDNS.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerDNS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerDNS dialog


CNetServerDNS::CNetServerDNS(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerDNS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerDNS)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNetServerDNS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerDNS)
	DDX_Control(pDX, IDC_IPADDRESS2, m_IP2);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerDNS, CDialog)
	//{{AFX_MSG_MAP(CNetServerDNS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerDNS message handlers

BOOL CNetServerDNS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE; 
}

void CNetServerDNS::InitDlgInfo(SDK_NetDNSConfig *pNetDNSCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netDNSCfg,pNetDNSCfg,sizeof(SDK_NetDNSConfig));
	m_IP1.SetAddress(m_netDNSCfg.PrimaryDNS.c[0],
					 m_netDNSCfg.PrimaryDNS.c[1],
					 m_netDNSCfg.PrimaryDNS.c[2],
					 m_netDNSCfg.PrimaryDNS.c[3]);
	m_IP2.SetAddress(m_netDNSCfg.SecondaryDNS.c[0],
					 m_netDNSCfg.SecondaryDNS.c[1],
					 m_netDNSCfg.SecondaryDNS.c[2],
					 m_netDNSCfg.SecondaryDNS.c[3]);
	UpdateData(FALSE);
}

void CNetServerDNS::OnOK() 
{
	m_ensure = TRUE;
	UpdateData();
	BYTE field1;
	BYTE field2;
	BYTE field3;
	BYTE field4;

	m_IP1.GetAddress(field1,field2,field3,field4);
	m_netDNSCfg.PrimaryDNS.c[0] = field1;
	m_netDNSCfg.PrimaryDNS.c[1] = field2;
	m_netDNSCfg.PrimaryDNS.c[2] = field3;
	m_netDNSCfg.PrimaryDNS.c[3] = field4;

	m_IP2.GetAddress(field1,field2,field3,field4);
	m_netDNSCfg.SecondaryDNS.c[0] = field1;
	m_netDNSCfg.SecondaryDNS.c[1] = field2;
	m_netDNSCfg.SecondaryDNS.c[2] = field3;
	m_netDNSCfg.SecondaryDNS.c[3] = field4;
	CDialog::OnOK();
}
