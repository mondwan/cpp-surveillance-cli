// NetServerMobile.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerMobile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerMobile dialog


CNetServerMobile::CNetServerMobile(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerMobile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerMobile)
	m_iPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerMobile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerMobile)
	DDX_Control(pDX, IDC_CHECK_MOBILE_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	DDV_MinMaxInt(pDX, m_iPort, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerMobile, CDialog)
	//{{AFX_MSG_MAP(CNetServerMobile)
	ON_BN_CLICKED(IDC_CHECK_MOBILE_ENABLE, OnCheckMobileEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerMobile message handlers

BOOL CNetServerMobile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerMobile::InitDlgInfo(SDK_NetMoblieConfig *pNetMobileCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netMobileCfg,pNetMobileCfg,sizeof(SDK_NetMoblieConfig));
	m_iPort = m_netMobileCfg.Server.Port;

	m_checkEnable.SetCheck(m_netMobileCfg.bEnable);
	UpdateData(FALSE);
	OnCheckMobileEnable();

}

void CNetServerMobile::OnOK() 
{
	SaveConfig();
	m_ensure = TRUE;
	CDialog::OnOK();
}

void CNetServerMobile::SaveConfig()
{
	UpdateData(TRUE);
	m_netMobileCfg.bEnable = m_checkEnable.GetCheck();
	m_netMobileCfg.Server.Port = m_iPort;
}

void CNetServerMobile::OnCheckMobileEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(bEnable);
}


