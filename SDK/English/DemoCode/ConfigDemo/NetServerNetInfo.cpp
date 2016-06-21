// NetServerNetInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerNetInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerNetInfo dialog


CNetServerNetInfo::CNetServerNetInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerNetInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerNetInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNetServerNetInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerNetInfo)
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_ctrlIpAddress);
	DDX_Control(pDX, IDC_COMBO_NETISP, m_ctrlNetIsp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerNetInfo, CDialog)
	//{{AFX_MSG_MAP(CNetServerNetInfo)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_EN_CHANGE(IDC_EDIT_PORT, OnChangeEditPort)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerNetInfo message handlers

void CNetServerNetInfo::OnCheckEnable() 
{
	BOOL m_bflag = ((CButton *)GetDlgItem(IDC_CHECK_ENABLE))->GetCheck();
	GetDlgItem(IDC_STATIC_NETISP)->EnableWindow(m_bflag);
	GetDlgItem(IDC_COMBO_NETISP)->EnableWindow(m_bflag);
	GetDlgItem(IDC_STATIC_NETSERVICE)->EnableWindow(m_bflag);
	GetDlgItem(IDC_EDIT_NETSERVICE)->EnableWindow(m_bflag);
	GetDlgItem(IDC_STATIC_ID)->EnableWindow(m_bflag);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(m_bflag);
	GetDlgItem(IDC_STATIC_USERNAME)->EnableWindow(m_bflag);
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(m_bflag);
	GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(m_bflag);
	GetDlgItem(IDC_EDIT_PWD)->EnableWindow(m_bflag);
	
	GetDlgItem(IDC_STATIC_IP)->EnableWindow(m_bflag);
	GetDlgItem(IDC_IPADDRESS_IP)->EnableWindow(m_bflag);
	GetDlgItem(IDC_STATIC_PORT)->EnableWindow(m_bflag);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(m_bflag);
	
}

void CNetServerNetInfo::OnOK() 
{
	m_ensure = TRUE;
	UpdateData();
	CString m_Value;
	m_LocSdkNetPC.nISP = m_ctrlNetIsp.GetCurSel();
	m_LocSdkNetPC.Enable =((CButton *)GetDlgItem(IDC_CHECK_ENABLE))->GetCheck();
	GetDlgItem(IDC_EDIT_NETSERVICE)->GetWindowText(m_Value);
	strncpy(m_LocSdkNetPC.sServerName,m_Value.GetBuffer(0),sizeof(m_LocSdkNetPC.sServerName));
	
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(m_Value);
	strncpy(m_LocSdkNetPC.ID,m_Value.GetBuffer(0),sizeof(m_LocSdkNetPC.ID));
	
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(m_Value);
	strncpy(m_LocSdkNetPC.sUserName,m_Value.GetBuffer(0),sizeof(m_LocSdkNetPC.sUserName));
	
	GetDlgItem(IDC_EDIT_PWD)->GetWindowText(m_Value);
	strncpy(m_LocSdkNetPC.sPassword,m_Value.GetBuffer(0),sizeof(m_LocSdkNetPC.sPassword));
	
	
	m_ctrlIpAddress.GetAddress(m_LocSdkNetPC.HostIP.c[0],m_LocSdkNetPC.HostIP.c[1],
		m_LocSdkNetPC.HostIP.c[2],m_LocSdkNetPC.HostIP.c[3]);
	m_Value.Format("%d",m_LocSdkNetPC.port);
	
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(m_Value);
	m_LocSdkNetPC.port = atoi(m_Value);
	CDialog::OnOK();
}

void CNetServerNetInfo::OnChangeEditPort() 
{
	
}

void CNetServerNetInfo::OnKillfocusEditPort() 
{
	UpdateData();
	CString  m_strValue;
	int m_intValue;
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(m_strValue);
	m_intValue = atoi(m_strValue);
	if ( m_intValue > 655356 )
	{
		GetDlgItem(IDC_EDIT_PORT)->SetWindowText("655356");
	}
	if ( m_intValue < 0 )
	{
		GetDlgItem(IDC_EDIT_PORT)->SetWindowText("80");//Ä¬ÈÏ80¶Ë¿Ú£¬modify by fanguanggao 2011.7.1
	}	
}

BOOL CNetServerNetInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CEdit*)GetDlgItem(IDC_EDIT_NETSERVICE))->SetLimitText(16);
	((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetLimitText(16);
	((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetLimitText(16);
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetLimitText(16);
	m_ctrlNetIsp.ResetContent();
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetServerNetInfo::InitDlgInfo(SDK_LocalSdkNetPlatformConfig *pLocSdkNetPC)
{
	m_ensure = FALSE;
	memcpy(&m_LocSdkNetPC,pLocSdkNetPC,sizeof(SDK_LocalSdkNetPlatformConfig));
	CString mNetIsp[6] = 
	{
		_CS("ConfigNet.ISP_AUTO"),
			_CS("ConfigNet.ISP_TELCOM"),
			_CS("ConfigNet.ISP_UNIONCOM"),
			_CS("ConfigNet.ISP_CNC"),
			_CS("ConfigNet.ISP_MOBILE"),
			_CS("ConfigNet.ISP_USER"),
	};
	for ( int i = 0; i < 6; ++i)
	{
		m_ctrlNetIsp.AddString(mNetIsp[i]);
	}
	int m_nflag,m_bflag;
	CString m_Value;
	m_nflag = m_LocSdkNetPC.nISP;
	m_bflag = m_LocSdkNetPC.Enable;
	m_ctrlNetIsp.SetCurSel(m_nflag);
	((CButton *)GetDlgItem(IDC_CHECK_ENABLE))->SetCheck(m_bflag);
	OnCheckEnable();
	GetDlgItem(IDC_EDIT_NETSERVICE)->SetWindowText(m_LocSdkNetPC.sServerName);
	GetDlgItem(IDC_EDIT_ID)->SetWindowText(m_LocSdkNetPC.ID);
	GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(m_LocSdkNetPC.sUserName);
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(m_LocSdkNetPC.sPassword);
	m_ctrlIpAddress.SetAddress(m_LocSdkNetPC.HostIP.c[0],m_LocSdkNetPC.HostIP.c[1],
		m_LocSdkNetPC.HostIP.c[2],m_LocSdkNetPC.HostIP.c[3]);
	m_Value.Format("%d",m_LocSdkNetPC.port);
	GetDlgItem(IDC_EDIT_PORT)->SetWindowText(m_Value);
	UpdateData(FALSE);
}
