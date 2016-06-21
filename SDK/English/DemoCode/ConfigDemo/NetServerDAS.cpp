// NetServerDAS.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerDAS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerDAS dialog


CNetServerDAS::CNetServerDAS(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerDAS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerDAS)
	m_sAddr = _T("");
	m_sDASID = _T("");
	m_sDASName = _T("");
	m_nPort = 0;
	m_sDASPwd = _T("");
	//}}AFX_DATA_INIT
}


void CNetServerDAS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerDAS)
	DDX_Control(pDX, IDC_IPADDRESS_DAS, m_IPAddr);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_DASPWD, m_editPWD);
	DDX_Control(pDX, IDC_EDIT_DASNAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_DASID, m_editID);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_editAddr);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_sAddr);
	DDX_Text(pDX, IDC_EDIT_DASID, m_sDASID);
	DDX_Text(pDX, IDC_EDIT_DASNAME, m_sDASName);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_DASPWD, m_sDASPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerDAS, CDialog)
	//{{AFX_MSG_MAP(CNetServerDAS)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerDAS message handlers

void CNetServerDAS::OnCheckEnable() 
{
	// TODO: Add your control notification handler code here
	BOOL bEnable = m_checkEnable.GetCheck();
	m_editAddr.EnableWindow(bEnable);
	m_editID.EnableWindow(bEnable);
	m_editName.EnableWindow(bEnable);
	m_editPort.EnableWindow(bEnable);
	m_editPWD.EnableWindow(bEnable);
}

void CNetServerDAS::InitDlgInfo(SDK_DASSerInfo *pNetDASCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netDASCfg,pNetDASCfg,sizeof(SDK_DASSerInfo));
	m_IPAddr.ShowWindow(SW_HIDE);
	m_checkEnable.SetCheck(m_netDASCfg.enable);
	m_sDASID = m_netDASCfg.devID;
	m_sDASName = m_netDASCfg.userName;
	m_sDASPwd = m_netDASCfg.passwd;
	m_nPort = m_netDASCfg.port;
	CString strAddr;
	m_sAddr=m_netDASCfg.serAddr;


	UpdateData(FALSE);
	OnCheckEnable();
}

BOOL CNetServerDAS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetServerDAS::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_ensure = TRUE;
	m_netDASCfg.enable = m_checkEnable.GetCheck();
	strcpy(m_netDASCfg.devID, m_sDASID.GetBuffer(0));
	strcpy(m_netDASCfg.userName, m_sDASName.GetBuffer(0));
	strcpy(m_netDASCfg.passwd, m_sDASPwd.GetBuffer(0));
	m_netDASCfg.port = m_nPort;
//	DWORD dwAddress;
	//m_IPAddr.GetAddress(dwAddress);
//	CString strAddr;
	//strAddr.Format("%d.%d.%d.%d",(0xFF000000&dwAddress)>>24,(0xFF0000&dwAddress)>>16,(0xFF00&dwAddress)>>8,0xFF&dwAddress);
	//strcpy(m_NetDASSerInfo.serAddr, strAddr.GetBuffer(0));
	strcpy(m_netDASCfg.serAddr,m_sAddr);
	CDialog::OnOK();
}
