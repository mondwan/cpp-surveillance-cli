// NetServerDDNS.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerDDNS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerDDNS dialog


CNetServerDDNS::CNetServerDDNS(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerDDNS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerDDNS)
	m_nPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerDDNS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerDDNS)
	DDX_Control(pDX, IDC_CHECK_INUSING, m_checkInUsing);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUserName);
	DDX_Control(pDX, IDC_EDIT_SERVER_DOMAIN, m_editServerDomain);
	DDX_Control(pDX, IDC_EDIT_PSW, m_editPsw);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_LOCAL_DOMAIN, m_editLocalDomain);
	DDX_Control(pDX, IDC_COMBO_DDNS_TYPE, m_cmbDDNSType);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerDDNS, CDialog)
	//{{AFX_MSG_MAP(CNetServerDDNS)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_DDNS_TYPE, OnSelchangeComboDdnsType)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerDDNS message handlers

BOOL CNetServerDDNS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	_CWndCS(this);
	m_editLocalDomain.SetLimitText( NET_NAME_PASSWORD_LEN );
	m_editServerDomain.SetLimitText( NET_NAME_PASSWORD_LEN );
	m_editUserName.SetLimitText( NET_NAME_PASSWORD_LEN );
	m_editPsw.SetLimitText( NET_NAME_PASSWORD_LEN );
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetServerDDNS::InitDlgInfo(SDK_NetDDNSConfigALL *pNetDDNSCfg,SDK_DDNSServiceFunction *pDDNSFunc)
{
	m_cmbDDNSType.ResetContent();
	m_ensure = FALSE;
	memcpy(&m_netDDNSCfg,pNetDDNSCfg,sizeof(SDK_NetDDNSConfigALL));
	memcpy(&m_DDNSFunc,pDDNSFunc,sizeof(SDK_DDNSServiceFunction));
	int i =0;
	CString key;
	for (i = 0; i < m_DDNSFunc.nTypeNum; ++i)
	{
		if (m_DDNSFunc.vDDNSType[i])
		{
			m_cmbDDNSType.AddString(m_DDNSFunc.vDDNSType[i]);
		}
	}
	m_cmbDDNSType.SetCurSel(0);
	m_nOldSelect = 0;
	UpdataDDNStype(0);
}



void CNetServerDDNS::OnCheckEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();

	m_editUserName.EnableWindow(bEnable);
	m_editServerDomain.EnableWindow(bEnable);
	m_editPsw.EnableWindow(bEnable);
	m_editPort.EnableWindow(bEnable);
	m_editLocalDomain.EnableWindow(bEnable);
}

void CNetServerDDNS::OnOK() 
{
	// TODO: Add extra validation here
	m_ensure = TRUE;
	SaveConfig(m_nOldSelect);
	CDialog::OnOK();
}

void CNetServerDDNS::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_ensure = FALSE;
	CDialog::OnCancel();
}

void CNetServerDDNS::UpdataDDNStype(int nType)
{
	//显示页面
	if ( strcmp( m_netDDNSCfg.ddnsConfig[nType].DDNSKey , "Elive") == 0)  //如果是Elive
	{
		GetDlgItem(IDC_STATIC_ISONLINE)->ShowWindow(SW_SHOW);
		m_checkInUsing.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DOMAIN)->ShowWindow(SW_HIDE);
		m_editLocalDomain.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PWD)->ShowWindow(SW_HIDE);
		m_editPsw.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SERVERNAME)->ShowWindow(SW_SHOW);
		m_editServerDomain.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		m_editPort.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_HIDE);
		
		//GetDlgItem(IDC_STATIC_NAME)->SetWindowText(_CS(_T("ConfigNet.DevID")));
		
		CRect rect0, rect1, rect2, rect3;
		GetDlgItem(IDC_CHECK_ENABLE)->GetWindowRect(&rect0);
		ScreenToClient(&rect0);
		
		GetDlgItem(IDC_COMBO_DDNS_TYPE)->GetWindowRect(&rect1);
		ScreenToClient(&rect1);
		
		int nHeight = rect0.top - rect1.bottom;
		
		//GetDlgItem(IDC_STATIC_NAME)->GetWindowRect(&rect1);
		//ScreenToClient(&rect1);
		//int iHeight = rect1.Height();
		//rect1.top = rect0.bottom + nHeight;
		//rect1.bottom = rect1.top + iHeight;
		//GetDlgItem(IDC_STATIC_NAME)->MoveWindow(rect1);
		//
		//GetDlgItem(IDC_EDIT_USERNAME)->GetWindowRect(&rect1);
		//ScreenToClient(&rect1);
		//iHeight = rect1.Height();
		//rect1.top = rect0.bottom + nHeight;
		//rect1.bottom = rect1.top + iHeight;
		//GetDlgItem(IDC_EDIT_USERNAME)->MoveWindow(rect1);
		
		GetDlgItem(IDC_STATIC_SERVERNAME)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		int iHeight = rect2.Height();
		rect2.top = rect0.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_STATIC_SERVERNAME)->MoveWindow(rect2);
		
		GetDlgItem(IDC_EDIT_SERVER_DOMAIN)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		iHeight = rect2.Height();
		rect2.top = rect0.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_EDIT_SERVER_DOMAIN)->MoveWindow(rect2);
		
		GetDlgItem(IDC_STATIC_PORT)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_STATIC_PORT)->MoveWindow(rect3);
		
		GetDlgItem(IDC_EDIT_PORT)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_EDIT_PORT)->MoveWindow(rect3);	
	}
	else if ( strcmp(m_netDDNSCfg.ddnsConfig[nType].DDNSKey , "Private DDNS") == 0 )
	{
		GetDlgItem(IDC_STATIC_ISONLINE)->ShowWindow(SW_HIDE);
		m_checkInUsing.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DOMAIN)->ShowWindow(SW_SHOW);
		m_editLocalDomain.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PWD)->ShowWindow(SW_SHOW);
		m_editPsw.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SERVERNAME)->ShowWindow(SW_SHOW);
		m_editServerDomain.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		m_editPort.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_SHOW);

		CRect rect0, rect1, rect2, rect3;
		GetDlgItem(IDC_CHECK_ENABLE)->GetWindowRect(&rect0);
		ScreenToClient(&rect0);

		GetDlgItem(IDC_COMBO_DDNS_TYPE)->GetWindowRect(&rect1);
		ScreenToClient(&rect1);

		int nHeight = rect0.top - rect1.bottom;

		GetDlgItem(IDC_STATIC_DOMAIN)->GetWindowRect(&rect1);
		ScreenToClient(&rect1);
		int iHeight = rect1.Height();
		rect1.top = rect0.bottom + nHeight;
		rect1.bottom = rect1.top + iHeight;
		GetDlgItem(IDC_STATIC_DOMAIN)->MoveWindow(rect1);

		m_editLocalDomain.GetWindowRect(&rect1);
		ScreenToClient(&rect1);
		iHeight = rect1.Height();
		rect1.top = rect0.bottom + nHeight;
		rect1.bottom = rect1.top + iHeight;
		m_editLocalDomain.MoveWindow(rect1);

		GetDlgItem(IDC_STATIC_NAME)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		iHeight = rect2.Height();
		rect2.top = rect1.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_STATIC_NAME)->MoveWindow(rect2);

		GetDlgItem(IDC_EDIT_USERNAME)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		iHeight = rect2.Height();
		rect2.top = rect1.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_EDIT_USERNAME)->MoveWindow(rect2);

		GetDlgItem(IDC_STATIC_PWD)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_STATIC_PWD)->MoveWindow(rect3);

		GetDlgItem(IDC_EDIT_PSW)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_EDIT_PSW)->MoveWindow(rect3);

		GetDlgItem(IDC_STATIC_SERVERNAME)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		iHeight = rect2.Height();
		rect2.top = rect3.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_STATIC_SERVERNAME)->MoveWindow(rect2);

		GetDlgItem(IDC_EDIT_SERVER_DOMAIN)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		iHeight = rect2.Height();
		rect2.top = rect3.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_EDIT_SERVER_DOMAIN)->MoveWindow(rect2);

		GetDlgItem(IDC_STATIC_PORT)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_STATIC_PORT)->MoveWindow(rect3);

		GetDlgItem(IDC_EDIT_PORT)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_EDIT_PORT)->MoveWindow(rect3);
	}
	else
	{
		GetDlgItem(IDC_STATIC_ISONLINE)->ShowWindow(SW_HIDE);
		m_checkInUsing.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DOMAIN)->ShowWindow(SW_SHOW);
		m_editLocalDomain.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PWD)->ShowWindow(SW_SHOW);
		m_editPsw.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SERVERNAME)->ShowWindow(SW_HIDE);
		m_editServerDomain.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
		m_editPort.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_SHOW);
		
		//GetDlgItem(IDC_STATIC_NAME)->SetWindowText(_CS(_T("ConfigNet.DDNSName")));
		
		CRect rect0, rect1, rect2, rect3;
		GetDlgItem(IDC_CHECK_ENABLE)->GetWindowRect(&rect0);
		ScreenToClient(&rect0);
		
		GetDlgItem(IDC_COMBO_DDNS_TYPE)->GetWindowRect(&rect1);
		ScreenToClient(&rect1);
		
		int nHeight = rect0.top - rect1.bottom;
		
		GetDlgItem(IDC_STATIC_DOMAIN)->GetWindowRect(&rect1);
		ScreenToClient(&rect1);
		int iHeight = rect1.Height();
		rect1.top = rect0.bottom + nHeight;
		rect1.bottom = rect1.top + iHeight;
		GetDlgItem(IDC_STATIC_DOMAIN)->MoveWindow(rect1);
		
		m_editLocalDomain.GetWindowRect(&rect1);
		ScreenToClient(&rect1);
		iHeight = rect1.Height();
		rect1.top = rect0.bottom + nHeight;
		rect1.bottom = rect1.top + iHeight;
		m_editLocalDomain.MoveWindow(rect1);
		
		GetDlgItem(IDC_STATIC_NAME)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		iHeight = rect2.Height();
		rect2.top = rect1.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_STATIC_NAME)->MoveWindow(rect2);
		
		GetDlgItem(IDC_EDIT_USERNAME)->GetWindowRect(&rect2);
		ScreenToClient(&rect2);
		iHeight = rect2.Height();
		rect2.top = rect1.bottom + nHeight;
		rect2.bottom = rect2.top + iHeight;
		GetDlgItem(IDC_EDIT_USERNAME)->MoveWindow(rect2);
		
		GetDlgItem(IDC_STATIC_PWD)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_STATIC_PWD)->MoveWindow(rect3);
		
		GetDlgItem(IDC_EDIT_PSW)->GetWindowRect(&rect3);
		ScreenToClient(&rect3);
		iHeight = rect3.Height();
		rect3.top = rect2.bottom + nHeight;
		rect3.bottom = rect3.top + iHeight;
		GetDlgItem(IDC_EDIT_PSW)->MoveWindow(rect3);
	}
	
	for ( int i = 0; i < NET_MAX_DDNS_TYPE; i ++ )
	{
		if ( !strcmp( m_netDDNSCfg.ddnsConfig[i].DDNSKey, m_DDNSFunc.vDDNSType[nType] ) )
		{
			m_checkEnable.SetCheck(m_netDDNSCfg.ddnsConfig[i].Enable);
			m_editLocalDomain.SetWindowText(m_netDDNSCfg.ddnsConfig[i].HostName );
			m_editServerDomain.SetWindowText(m_netDDNSCfg.ddnsConfig[i].Server.ServerName );
			m_editUserName.SetWindowText( m_netDDNSCfg.ddnsConfig[i].Server.UserName );
			m_editPsw.SetWindowText( m_netDDNSCfg.ddnsConfig[i].Server.Password );
			
			CString strPort;
			strPort.Format("%d", m_netDDNSCfg.ddnsConfig[i].Server.Port );
			m_editPort.SetWindowText( strPort );

			if ( strcmp(   m_netDDNSCfg.ddnsConfig[i].DDNSKey , "Elive") == 0)  //如果是Elive
			m_checkInUsing.SetCheck(m_netDDNSCfg.ddnsConfig[i].Online);

			OnCheckEnable();
			break;
		}
	}
}

void CNetServerDDNS::SaveConfig(int nType)
{
	CString strText;
	
	for ( int i = 0; i < NET_MAX_DDNS_TYPE; i ++ )
	{
		if ( !strcmp( m_netDDNSCfg.ddnsConfig[i].DDNSKey, m_DDNSFunc.vDDNSType[nType] ) )
		{
			m_netDDNSCfg.ddnsConfig[i].Enable = m_checkEnable.GetCheck();
			
			m_editLocalDomain.GetWindowText( strText );
			strcpy ( m_netDDNSCfg.ddnsConfig[i].HostName, strText.GetBuffer(0) );
			
			m_editServerDomain.GetWindowText( strText );
			strcpy ( m_netDDNSCfg.ddnsConfig[i].Server.ServerName, strText.GetBuffer(0) );
			
			m_editUserName.GetWindowText( strText );
			strcpy ( m_netDDNSCfg.ddnsConfig[i].Server.UserName, strText.GetBuffer(0) );
			
			m_editPsw.GetWindowText( strText );
			strcpy ( m_netDDNSCfg.ddnsConfig[i].Server.Password, strText.GetBuffer(0) );
			
			m_editPort.GetWindowText( strText );
			m_netDDNSCfg.ddnsConfig[i].Server.Port = atoi( strText.GetBuffer(0) );
			
			break;
		}
	}
}

void CNetServerDDNS::OnSelchangeComboDdnsType() 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_cmbDDNSType.GetCurSel();
	//先保存原先的配置
	if ( m_nOldSelect != nSelect )
	{
		SaveConfig(m_nOldSelect);
	}
	
	m_nOldSelect = nSelect;
	
	UpdataDDNStype( nSelect );
}

void CNetServerDDNS::OnKillfocusEditPort() 
{
	UpdateData(TRUE);
	if ( m_nPort< 0 || m_nPort > 65535)
	{
		m_nPort = 0;
		UpdateData(FALSE);
	}
}
