// NetServer3G.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServer3G.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServer3G dialog


CNetServer3G::CNetServer3G(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServer3G::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServer3G)
	//}}AFX_DATA_INIT
}


void CNetServer3G::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServer3G)
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddr);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_DIAL_NUM, m_editDialNum);
	DDX_Control(pDX, IDC_EDIT_APN, m_editAPN);
	DDX_Control(pDX, IDC_COMBO_NET_TYPE, m_cmbNetType);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServer3G, CDialog)
	//{{AFX_MSG_MAP(CNetServer3G)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServer3G message handlers

void CNetServer3G::OnOK() 
{
	m_ensure = TRUE;
	SaveConfig();
	CDialog::OnOK();
}

BOOL CNetServer3G::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	_CWndCS(this);
	return TRUE;  
}

void CNetServer3G::InitDlgInfo(SDK_Net3GConfig *pNet3GCfg)
{
	m_cmbNetType.ResetContent();
	m_ensure = FALSE;
	memcpy(&m_net3GCfg,pNet3GCfg,sizeof(SDK_Net3GConfig));
	m_editAPN.SetLimitText(32);
	m_editDialNum.SetLimitText(32);
	m_editPassword.SetLimitText(32);
	m_editUserName.SetLimitText(32);
	
	m_checkEnable.SetCheck(m_net3GCfg.bEnable);
	m_editAPN.SetWindowText(m_net3GCfg.sAPN);
	m_editDialNum.SetWindowText(m_net3GCfg.sDialNum);
	m_editUserName.SetWindowText(m_net3GCfg.sUserName);
	m_editPassword.SetWindowText(m_net3GCfg.sPassword);
	
	m_cmbNetType.InsertString(0,_CS("NetServer.AUTO"));
	m_cmbNetType.InsertString(1,_CS("NetServer.TD-SCDMA"));
	m_cmbNetType.InsertString(2,_CS("NetServer.WCDMA"));
	m_cmbNetType.InsertString(3,_CS("NetServer.CDMA1X"));
	m_cmbNetType.InsertString(4,_CS("NetServer.GPRS"));
	m_cmbNetType.InsertString(5,_CS("NetServer.EVDO"));
	m_cmbNetType.SetCurSel(m_net3GCfg.iNetType);

	m_IPAddr.SetAddress(m_net3GCfg.addr.c[0],
						m_net3GCfg.addr.c[1],
						m_net3GCfg.addr.c[2],
						m_net3GCfg.addr.c[3]);
	m_IPAddr.EnableWindow(FALSE);
	UpdateData(FALSE);
	
	OnCheckEnable();
}

void CNetServer3G::OnCheckEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	m_cmbNetType.EnableWindow(bEnable);
	m_editAPN.EnableWindow(bEnable);
	m_editDialNum.EnableWindow(bEnable);
	m_editPassword.EnableWindow(bEnable);
	m_editUserName.EnableWindow(bEnable);
}

void CNetServer3G::SaveConfig()
{
	UpdateData(TRUE);
	m_net3GCfg.bEnable = m_checkEnable.GetCheck();
	m_net3GCfg.iNetType = m_cmbNetType.GetCurSel();

	CString strText;
	m_editAPN.GetWindowText(strText);
	strncpy(m_net3GCfg.sAPN,strText.GetBuffer(0),sizeof(m_net3GCfg.sAPN));
	
	m_editDialNum.GetWindowText(strText);
	strncpy(m_net3GCfg.sDialNum,strText.GetBuffer(0),sizeof(m_net3GCfg.sDialNum));	
	
	m_editPassword.GetWindowText(strText);
	strncpy(m_net3GCfg.sPassword,strText,sizeof(m_net3GCfg.sPassword));

	m_editUserName.GetWindowText(strText);
	strncpy(m_net3GCfg.sUserName,strText,sizeof(m_net3GCfg.sUserName));
}
