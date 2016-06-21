// NetServerARSP.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerARSP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerARSP dialog


CNetServerARSP::CNetServerARSP(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerARSP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerARSP)
	//}}AFX_DATA_INIT
}


void CNetServerARSP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerARSP)
	DDX_Control(pDX, IDC_EDIT_LOCAL_DOMAIN1, m_editLocalDomain);
	DDX_Control(pDX, IDC_CHECK_ARSP_ENABLE, m_checkEnable);
	DDX_Control(pDX, IDC_COMBO_DDNS_TYPE, m_cmbDDNSType);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUserName);
	DDX_Control(pDX, IDC_EDIT_SERVER_NAME, m_editSvrDomain);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_editInterval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerARSP, CDialog)
	//{{AFX_MSG_MAP(CNetServerARSP)
	ON_BN_CLICKED(IDC_CHECK_ARSP_ENABLE, OnCheckArspEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_DDNS_TYPE, OnSelchangeComboDdnsType)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerARSP message handlers

void CNetServerARSP::OnOK() 
{
	SaveConfig(m_nOldSelect);
	m_ensure = TRUE;
	CDialog::OnOK();
}

BOOL CNetServerARSP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerARSP::InitDlgInfo(SDK_NetARSPConfigAll *pNetARSPCfg)
{
	m_ensure = FALSE;
	m_cmbDDNSType.ResetContent();
	memcpy(&m_netARSPCfg,pNetARSPCfg,sizeof(SDK_NetARSPConfigAll));
	for ( int i = 0; i < NET_MAX_ARSP_TYPE; i++ )
	{
		if ( strcmp(m_netARSPCfg.vNetARSPConfigAll[i].sARSPKey, "None") )
		{
			m_cmbDDNSType.AddString( m_netARSPCfg.vNetARSPConfigAll[i].sARSPKey);
			protocolList.push_back(m_netARSPCfg.vNetARSPConfigAll[i].sARSPKey);
		}
	}
	
	if ( protocolList.size() )
	{
		m_editUserName.SetLimitText(32);
		m_editPassword.SetLimitText(32);
		m_editInterval.SetLimitText(2);
		m_editPort.SetLimitText(5);
		m_editLocalDomain.EnableWindow(FALSE);
		m_cmbDDNSType.SetCurSel(0);
		m_nOldSelect= 0;
		OnSelchangeComboDdnsType();
	}
}

void CNetServerARSP::OnCheckArspEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	m_editLocalDomain.EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SERVER_NAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(bEnable);
}

void CNetServerARSP::OnSelchangeComboDdnsType() 
{
	int nSelect = m_cmbDDNSType.GetCurSel();
	//先保存原先的配置
	if (m_nOldSelect != nSelect	)
	{
		SaveConfig(m_nOldSelect);
	}
	m_nOldSelect = nSelect;
	UpdateDDNSTYPE(nSelect);
}

void CNetServerARSP::UpdateDDNSTYPE(int nType)
{
	if (protocolList.size() <= 0 || protocolList.size() < nType + 1)
		return;
	for (int i = 0; i < NET_MAX_DDNS_TYPE; ++i)
	{
		if (!strcmp(m_netARSPCfg.vNetARSPConfigAll[i].sARSPKey,protocolList[nType].c_str()))
		{
			m_checkEnable.SetCheck(m_netARSPCfg.vNetARSPConfigAll[i].bEnable);
			m_editSvrDomain.SetWindowText(m_netARSPCfg.vNetARSPConfigAll[i].Server.ServerName);
			CString str;
			str.Format(_T("%d"),m_netARSPCfg.vNetARSPConfigAll[i].Server.Port);
			m_editPort.SetWindowText(str);
			str.Format(_T("%d"),m_netARSPCfg.vNetARSPConfigAll[i].iInterval);
			m_editInterval.SetWindowText(str);
			m_editPassword.SetWindowText(m_netARSPCfg.vNetARSPConfigAll[i].Server.Password);
			m_editUserName.SetWindowText(m_netARSPCfg.vNetARSPConfigAll[i].Server.UserName);
			//m_editLocalDomain.SetWindowText(m_netARSPCfg.vNetARSPConfigAll[i].sDDNSURL);
			break;
		}
	}
	UpdateData(FALSE);
}

void CNetServerARSP::SaveConfig(int nType)
{
	if ( protocolList.size() <= 0 || protocolList.size() < nType + 1)  //Vector为空，则退出
		return;
	CString strText;
	UpdateData();
	for ( int i = 0; i < NET_MAX_DDNS_TYPE; i ++ )
	{
		if ( !strcmp(m_netARSPCfg.vNetARSPConfigAll[i].sARSPKey, protocolList[nType].c_str()) )
		{
			m_netARSPCfg.vNetARSPConfigAll[i].bEnable = m_checkEnable.GetCheck();		
			m_editPort.GetWindowText(strText);
			m_netARSPCfg.vNetARSPConfigAll[i].Server.Port = atoi(strText);
			m_editInterval.GetWindowText(strText);
			m_netARSPCfg.vNetARSPConfigAll[i].iInterval = atoi(strText);
			CString strSvr;
			m_editSvrDomain.GetWindowText(strSvr);
			strncpy(m_netARSPCfg.vNetARSPConfigAll[i].Server.ServerName, strSvr.GetBuffer(0), sizeof(m_netARSPCfg.vNetARSPConfigAll[i].Server.ServerName));
			m_editUserName.GetWindowText(strSvr);
			strncpy(m_netARSPCfg.vNetARSPConfigAll[i].Server.UserName, strSvr.GetBuffer(0), sizeof(m_netARSPCfg.vNetARSPConfigAll[i].Server.UserName));
			m_editPassword.GetWindowText(strSvr);
			strncpy(m_netARSPCfg.vNetARSPConfigAll[i].Server.Password, strSvr.GetBuffer(0), sizeof(m_netARSPCfg.vNetARSPConfigAll[i].Server.Password));
			break;
		}
	}
}

void CNetServerARSP::OnKillfocusEditPort() 
{
	UpdateData(TRUE);
	CString strText;
	m_editPort.GetWindowText(strText);
	if (atoi(strText) < 0 || atoi(strText) > 65535)
	{
		m_editPort.SetWindowText(0);
		UpdateData(FALSE);
	}
}

void CNetServerARSP::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	GetDlgItem(IDC_STATIC_ARSPTIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DOMAIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_LOCAL_DOMAIN1)->ShowWindow(SW_HIDE);
	UpdateData(FALSE);
#ifdef OEM_ControlBr
	{
		GetDlgItem(IDC_STATIC_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_DDNS_TYPE)->ShowWindow(SW_HIDE);
		CRect rcStaticEnable, rcCtrlEnable;
		GetDlgItem(IDC_STATIC_ENABLE)->GetWindowRect(rcStaticEnable);
		ScreenToClient(rcStaticEnable);
		GetDlgItem(IDC_CHECK1)->GetWindowRect(rcCtrlEnable);
		ScreenToClient(rcCtrlEnable);
		
		GetDlgItem(IDC_STATIC_IPADDR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SVR_DOMAIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INTERVAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INTERVAL)->ShowWindow(SW_HIDE);
		CRect rcStaticUsername, rcEditUsername;
		GetDlgItem(IDC_STATIC_USERNAME)->GetWindowRect(rcStaticUsername);
		ScreenToClient(rcStaticUsername);
		int nHeight = rcStaticUsername.Height();
		rcStaticUsername.top = rcStaticEnable.bottom + nHeight;//行间距为nHeight
		rcStaticUsername.bottom = rcStaticUsername.top + nHeight;
		GetDlgItem(IDC_STATIC_USERNAME)->MoveWindow(rcStaticUsername);
		GetDlgItem(IDC_EDIT_USERNAME)->GetWindowRect(rcEditUsername);
		ScreenToClient(rcEditUsername);
		nHeight = rcEditUsername.Height();
		rcEditUsername.top = rcCtrlEnable.bottom + nHeight;//行间距为nHeight
		rcEditUsername.bottom = rcEditUsername.top + nHeight;
		GetDlgItem(IDC_EDIT_USERNAME)->MoveWindow(rcEditUsername);
		
		CRect rcStaticPwd, rcEditPwd;
		GetDlgItem(IDC_STATIC_PWD)->GetWindowRect(rcStaticPwd);
		ScreenToClient(rcStaticPwd);
		nHeight = rcStaticPwd.Height();
		rcStaticPwd.top = rcStaticUsername.bottom + nHeight;//行间距为nHeight
		rcStaticPwd.bottom = rcStaticPwd.top + nHeight;
		GetDlgItem(IDC_STATIC_PWD)->MoveWindow(rcStaticPwd);
		GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowRect(rcEditPwd);
		ScreenToClient(rcEditPwd);
		nHeight = rcEditPwd.Height();
		rcEditPwd.top = rcEditUsername.bottom +nHeight;//行间距为nHeight
		rcEditPwd.bottom = rcEditPwd.top + nHeight;
		GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow(rcEditPwd);
	}
#endif
	
	
}
