// NetServerGodEye.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerGodEye.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerGodEye dialog


CNetServerGodEye::CNetServerGodEye(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerGodEye::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerGodEye)
	m_nExtraPort = 0;
	m_sExtraAddr = _T("");
	m_sMainAddr = _T("");
	m_nMianPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerGodEye::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerGodEye)
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_EXTRAPORT, m_nExtraPort);
	DDV_MinMaxInt(pDX, m_nExtraPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_EXTRAADDR, m_sExtraAddr);
	DDX_Text(pDX, IDC_EDIT_MAINADDR, m_sMainAddr);
	DDX_Text(pDX, IDC_EDIT_MAINPORT, m_nMianPort);
	DDV_MinMaxInt(pDX, m_nMianPort, 0, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerGodEye, CDialog)
	//{{AFX_MSG_MAP(CNetServerGodEye)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerGodEye message handlers

BOOL CNetServerGodEye::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CEdit*)GetDlgItem(IDC_EDIT_EXTRAADDR))->SetLimitText(sizeof(m_netGodEyeCfg.ExSeverName));
	((CEdit*)GetDlgItem(IDC_EDIT_MAINADDR))->SetLimitText(sizeof(m_netGodEyeCfg.MainSeverName));
	((CEdit*)GetDlgItem(IDC_EDIT_EXTRAPORT))->SetLimitText(5);
	((CEdit*)GetDlgItem(IDC_EDIT_MAINPORT))->SetLimitText(5);
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerGodEye::InitDlgInfo(SDK_GodEyeConfig *pNetGodEyeCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netGodEyeCfg,pNetGodEyeCfg,sizeof(pNetGodEyeCfg));
	m_checkEnable.SetCheck(m_netGodEyeCfg.bEnable);
	m_nExtraPort = m_netGodEyeCfg.ExPort;
	m_nMianPort = m_netGodEyeCfg.MainPort;
	m_sExtraAddr = m_netGodEyeCfg.ExSeverName;
	m_sMainAddr = m_netGodEyeCfg.MainSeverName;
	UpdateData(FALSE);	
}

void CNetServerGodEye::OnOK() 
{
	m_ensure = TRUE;
	UpdateData();
	m_netGodEyeCfg.bEnable = m_checkEnable.GetCheck();
	m_netGodEyeCfg.ExPort = m_nExtraPort;
	m_netGodEyeCfg.MainPort = m_nMianPort;
	strncpy(m_netGodEyeCfg.MainSeverName,m_sMainAddr.GetBuffer(0),
		sizeof(m_netGodEyeCfg.MainSeverName));
	strncpy(m_netGodEyeCfg.ExSeverName,m_sExtraAddr.GetBuffer(0),
		sizeof(m_netGodEyeCfg.ExSeverName));
	CDialog::OnOK();
}
