// NetServerRtsp.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerRtsp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerRtsp dialog


CNetServerRtsp::CNetServerRtsp(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerRtsp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerRtsp)
	m_nPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerRtsp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerRtsp)
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerRtsp, CDialog)
	//{{AFX_MSG_MAP(CNetServerRtsp)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerRtsp message handlers

void CNetServerRtsp::OnCheckEnable() 
{
	// TODO: Add your control notification handler code here
	m_editPort.EnableWindow(m_checkEnable.GetCheck());
}

void CNetServerRtsp::OnOK() 
{
	// TODO: Add extra validation here
	m_ensure = TRUE;
	UpdateData();
	m_netRTSPCfg.Server.Port = m_nPort;
	m_netRTSPCfg.bServer = m_checkEnable.GetCheck();
	CDialog::OnOK();
}

void CNetServerRtsp::InitDlgInfo(SDK_NetRTSPConfig *pNetRTSPCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netRTSPCfg,pNetRTSPCfg,sizeof(SDK_NetRTSPConfig));
	m_nPort = m_netRTSPCfg.Server.Port;
	m_checkEnable.SetCheck(m_netRTSPCfg.bServer);
	UpdateData(FALSE);
	OnCheckEnable();
}

BOOL CNetServerRtsp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	m_editPort.SetLimitText(5);
	CenterWindow();
	return TRUE;  
}
