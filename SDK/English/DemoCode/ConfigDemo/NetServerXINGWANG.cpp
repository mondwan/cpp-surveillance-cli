// NetServerXINGWANG.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerXINGWANG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerXINGWANG dialog


CNetServerXINGWANG::CNetServerXINGWANG(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerXINGWANG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerXINGWANG)
	m_bSubStream = FALSE;
	m_bTimeSync = FALSE;
	m_sPwd = _T("");
	m_nDownLoadPort = 0;
	m_nPort = 0;
	m_sSSID = _T("");
	//}}AFX_DATA_INIT
}


void CNetServerXINGWANG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerXINGWANG)
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddr);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Check(pDX, IDC_CHECK_SUBSTREAM, m_bSubStream);
	DDX_Check(pDX, IDC_CHECK_TIMESYNC, m_bTimeSync);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sPwd);
	DDX_Text(pDX, IDC_EDIT_DOWNLOAD_PORT, m_nDownLoadPort);
	DDV_MinMaxInt(pDX, m_nDownLoadPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_SSID, m_sSSID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerXINGWANG, CDialog)
	//{{AFX_MSG_MAP(CNetServerXINGWANG)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerXINGWANG message handlers

BOOL CNetServerXINGWANG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CEdit*)GetDlgItem(IDC_EDIT_PORT))->SetLimitText(5);
	((CEdit*)GetDlgItem(IDC_EDIT_SSID))->SetLimitText(sizeof(m_netXIANGWANGCfg.szSID));
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetLimitText(sizeof(m_netXIANGWANGCfg.sPasswd));
	((CEdit*)GetDlgItem(IDC_EDIT_DOWNLOAD_PORT))->SetLimitText(5);
	CenterWindow();
	_CWndCS(this);
	return TRUE;  
}

void CNetServerXINGWANG::InitDlgInfo(SDK_CONFIG_NET_XINGWANG *pNetXIANGWANGCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netXIANGWANGCfg,pNetXIANGWANGCfg,sizeof(SDK_CONFIG_NET_XINGWANG));
	m_checkEnable.SetCheck(m_netXIANGWANGCfg.bEnable);
	m_bSubStream = m_netXIANGWANGCfg.bSubStream;
	m_bTimeSync = m_netXIANGWANGCfg.bSyncTime;
	m_nPort = m_netXIANGWANGCfg.iServerPort;
	m_nDownLoadPort = m_netXIANGWANGCfg.iDownLoadPort;
	m_sPwd = m_netXIANGWANGCfg.sPasswd;
	m_sSSID = m_netXIANGWANGCfg.szSID;
	m_IPAddr.SetAddress(m_netXIANGWANGCfg.ServerIP.c[0],
						m_netXIANGWANGCfg.ServerIP.c[1],
						m_netXIANGWANGCfg.ServerIP.c[2],
						m_netXIANGWANGCfg.ServerIP.c[3]);
	UpdateData(FALSE);
	OnCheckEnable();
}

void CNetServerXINGWANG::OnCheckEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	((CButton*)GetDlgItem(IDC_CHECK_SUBSTREAM))->EnableWindow(bEnable);
	((CButton*)GetDlgItem(IDC_CHECK_TIMESYNC))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_PORT))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_SSID))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_DOWNLOAD_PORT))->EnableWindow(bEnable);
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS))->EnableWindow(bEnable);
}

void CNetServerXINGWANG::OnOK() 
{
	m_ensure = TRUE;
	UpdateData();
	m_netXIANGWANGCfg.bEnable = m_checkEnable.GetCheck();
	m_netXIANGWANGCfg.bSubStream = m_bSubStream;
	m_netXIANGWANGCfg.bSyncTime = m_bTimeSync;
	m_netXIANGWANGCfg.iServerPort = m_nPort;
	m_netXIANGWANGCfg.iDownLoadPort = m_nDownLoadPort;
	strncpy(m_netXIANGWANGCfg.szSID,m_sSSID.GetBuffer(0),sizeof(m_netXIANGWANGCfg.szSID));
	strncpy(m_netXIANGWANGCfg.sPasswd,m_sPwd.GetBuffer(0),sizeof(m_netXIANGWANGCfg.sPasswd));
	BYTE field1;
	BYTE field2;
	BYTE field3;
	BYTE field4;
	m_IPAddr.GetAddress(field1,field2,field3,field4);
	m_netXIANGWANGCfg.ServerIP.c[0] = field1;
	m_netXIANGWANGCfg.ServerIP.c[1] = field2;
	m_netXIANGWANGCfg.ServerIP.c[2] = field3;
	m_netXIANGWANGCfg.ServerIP.c[3] = field4;
	CDialog::OnOK();
}
