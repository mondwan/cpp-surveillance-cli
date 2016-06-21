// NetServerNTP.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerNTP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerNTP dialog


CNetServerNTP::CNetServerNTP(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerNTP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerNTP)
	m_port = 0;
	m_serverName = _T("");
	m_updatePeriod = 0;
	//}}AFX_DATA_INIT
}


void CNetServerNTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerNTP)
	DDX_Control(pDX, IDC_CHECK_NTP_ENABLE, m_ctlEnableNTP);
	DDX_Control(pDX, IDC_COMBO_TIMEZONE, m_ctlTimezone);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_SERVER_NAME, m_serverName);
	DDX_Text(pDX, IDC_EDIT_UPDATE_PERIOD, m_updatePeriod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerNTP, CDialog)
	//{{AFX_MSG_MAP(CNetServerNTP)
	ON_BN_CLICKED(IDC_CHECK_NTP_ENABLE, OnCheckNtpEnable)
	ON_EN_KILLFOCUS(IDC_EDIT_UPDATE_PERIOD, OnKillfocusEditUpdatePeriod)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerNTP message handlers

BOOL CNetServerNTP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ctlTimezone.InsertString(0,"GMT+00:00");
	m_ctlTimezone.InsertString(1,"GMT+01:00");
	m_ctlTimezone.InsertString(2,"GMT+02:00");
	m_ctlTimezone.InsertString(3,"GMT+03:00");
	m_ctlTimezone.InsertString(4,"GMT+03:30");
	m_ctlTimezone.InsertString(5,"GMT+04:00");
	m_ctlTimezone.InsertString(6,"GMT+04:30");
	m_ctlTimezone.InsertString(7,"GMT+05:00");
	m_ctlTimezone.InsertString(8,"GMT+05:30");
	m_ctlTimezone.InsertString(9,"GMT+05:45");
	m_ctlTimezone.InsertString(10,"GMT+06:00");
	m_ctlTimezone.InsertString(11,"GMT+06:30");
	m_ctlTimezone.InsertString(12,"GMT+07:00");
	m_ctlTimezone.InsertString(13,"GMT+08:00");
	m_ctlTimezone.InsertString(14,"GMT+09:00");
	m_ctlTimezone.InsertString(15,"GMT+09:30");
	m_ctlTimezone.InsertString(16,"GMT+10:00");
	m_ctlTimezone.InsertString(17,"GMT+11:00");
	m_ctlTimezone.InsertString(18,"GMT+12:00");
	m_ctlTimezone.InsertString(19,"GMT+13:00");
	m_ctlTimezone.InsertString(20,"GMT-01:00");
	m_ctlTimezone.InsertString(21,"GMT-02:00");
	m_ctlTimezone.InsertString(22,"GMT-03:00");
	m_ctlTimezone.InsertString(23,"GMT-03:30");
	m_ctlTimezone.InsertString(24,"GMT-04:00");
	m_ctlTimezone.InsertString(25,"GMT-05:00");
	m_ctlTimezone.InsertString(26,"GMT-06:00");
	m_ctlTimezone.InsertString(27,"GMT-07:00");
	m_ctlTimezone.InsertString(28,"GMT-08:00");
	m_ctlTimezone.InsertString(29,"GMT-09:00");
	m_ctlTimezone.InsertString(30,"GMT-10:00");
	m_ctlTimezone.InsertString(31,"GMT-11:00");
	m_ctlTimezone.InsertString(32,"GMT-12:00");
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerNTP::OnOK() 
{
	m_ensure = TRUE;
	SaveConfig();
	CDialog::OnOK();
}


void CNetServerNTP::InitDlgInfo(SDK_NetNTPConfig *pNetNTPCfg)
{
	m_ensure = FALSE;
 	memcpy(&m_netNTPCfg,pNetNTPCfg,sizeof(SDK_NetNTPConfig));
	m_ctlEnableNTP.SetCheck(m_netNTPCfg.Enable);
 	m_serverName = m_netNTPCfg.Server.ServerName;
 	m_port = m_netNTPCfg.Server.Port;
 	m_ctlTimezone.SetCurSel(m_netNTPCfg.TimeZone);
 	m_updatePeriod = m_netNTPCfg.UpdatePeriod;
	OnCheckNtpEnable();
	UpdateData(FALSE);
}

void CNetServerNTP::OnCheckNtpEnable() 
{
	BOOL bEnable = m_ctlEnableNTP.GetCheck();	
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SERVER_NAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_PERIOD)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIMEZONE)->EnableWindow(bEnable);	
}

void CNetServerNTP::SaveConfig()
{
	UpdateData();
	m_netNTPCfg.UpdatePeriod = m_updatePeriod;
	strcpy(m_netNTPCfg.Server.ServerName,m_serverName);
	m_netNTPCfg.Server.Port = m_port;
	m_netNTPCfg.TimeZone = m_ctlTimezone.GetCurSel();
	m_netNTPCfg.Enable = m_ctlEnableNTP.GetCheck();
}

void CNetServerNTP::OnKillfocusEditUpdatePeriod() 
{
	UpdateData(TRUE);
	if (m_updatePeriod < 0 || m_updatePeriod > 65535)
	{
		m_port = 0;
		UpdateData(FALSE);
	}
}

void CNetServerNTP::OnKillfocusEditPort() 
{
	UpdateData(TRUE);
	if (m_port < 0 || m_port > 65535)
	{
		m_port = 0;
		UpdateData(FALSE);
	}
}
