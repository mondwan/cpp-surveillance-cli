// RemoteChannelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "RemoteChannelDlg.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteChannelDlg dialog


CRemoteChannelDlg::CRemoteChannelDlg(SDK_NetDecorderConfigV3 *pNetConfig /*= NULL*/,int nDevNum/* = 0 */, CWnd* pParent/* = NULL*/)
	: CDialog(CRemoteChannelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemoteChannelDlg)
	m_nPort = 0;
	m_nRemoteChannel = 0;
	//}}AFX_DATA_INIT
// 	m_nPort = 0;
// 	//}}AFX_DATA_INIT
	if ( pNetConfig )
	{
		memcpy( &m_pNetConfig, pNetConfig ,sizeof(SDK_NetDecorderConfigV3));
		m_nNum = -1;
	}else
	{
		memset (&m_pNetConfig, 0 ,sizeof(SDK_NetDecorderConfigV3));
		m_nNum = nDevNum;
	}
	m_nDevNum = 0;
	m_hSearch = NULL;
	
	memset(&m_Netcomm, 0 ,sizeof(SDK_CONFIG_NET_COMMON));
	
}


void CRemoteChannelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemoteChannelDlg)
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_EditPWD);
	DDX_Control(pDX, IDC_COMBO_DEVTYPE, m_cmbDevType);
	DDX_Control(pDX, IDC_COMBO_PROC, m_cmbProc);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_cmbStream);
	DDX_Control(pDX, IDC_EDIT_CFGNAME, m_EditCfgName);
	DDX_Control(pDX, IDC_EDIT_PORT, m_EditPort);
	DDX_Control(pDX, IDC_EDIT_REMOTECHANNEL, m_EditRemoteChannel);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_EditUsername);
	DDX_Control(pDX, IDC_EDIT_IPADDR, m_CtrlIPAddress);
	DDX_Control(pDX, IDC_LIST_DEV, m_CtrlListDev);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_REMOTECHANNEL, m_nRemoteChannel);
	DDV_MinMaxUInt(pDX, m_nRemoteChannel, 1, 4294967295);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemoteChannelDlg, CDialog)
	//{{AFX_MSG_MAP(CRemoteChannelDlg)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEV, OnClickListDev)
	ON_EN_CHANGE(IDC_EDIT_PORT, OnChangeEditPort)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteChannelDlg message handlers

void CRemoteChannelDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CString str;
	m_EditCfgName.GetWindowText(str);
	strcpy( m_pNetConfig.ConfName, str.GetBuffer(0));
	m_pNetConfig.DevType = m_cmbDevType.GetCurSel();
	m_pNetConfig.Protocol = m_cmbProc.GetCurSel();
	m_EditRemoteChannel.GetWindowText(str);//获取设备通道 不能为负数
	m_pNetConfig.Channel = atoi(str) - 1;
	m_pNetConfig.StreamType = m_cmbStream.GetCurSel();
	m_CtrlIPAddress.GetWindowText(str);
	strcpy(m_pNetConfig.Address, str.GetBuffer(0));
	m_EditPort.GetWindowText(str);//获取设备端口号  端口号不能为0
	m_pNetConfig.Port = atoi(str);
	m_EditUsername.GetWindowText(str);
	strcpy(m_pNetConfig.UserName, str.GetBuffer(0));
	m_EditPWD.GetWindowText(str);
	strcpy(m_pNetConfig.PassWord, str.GetBuffer(0));
	CDialog::OnOK();
}

BOOL CRemoteChannelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_CWndCS(this);
	
	//AfxSetResourceHandle(OldResourceHanlde);//对话框已创建，设置回原来的模块
	
	SetWindowText(_CS(_T("DigitalChannel.RemoteChannel")));
	
	m_cmbDevType.ResetContent();
	m_cmbStream.ResetContent();
	m_cmbProc.ResetContent();
	
	m_cmbDevType.AddString(_CS(_T("DigitalChannel.IPC")));
	m_cmbDevType.AddString(_CS(_T("DigitalChannel.DVR")));
	m_cmbDevType.AddString(_CS(_T("DigitalChannel.HVR")));
	m_cmbDevType.SetCurSel(0);
	
	m_cmbProc.AddString(_CS(_T("DigitalChannel.TCP")));
	m_cmbProc.SetCurSel(0);
	m_cmbProc.EnableWindow(FALSE);
	
	m_cmbStream.AddString(_CS(_T("Desktop.MainStream")));
	m_cmbStream.AddString(_CS(_T("Desktop.ExtStream")));
	m_cmbStream.SetCurSel(0);
	
	m_EditRemoteChannel.SetWindowText(_T("1"));
	if ( m_nNum >= 0)
	{
		CString str;
		str.Format(_T("chConfig%d"),m_nNum + 1);
		m_EditCfgName.SetWindowText(str);
	}
	m_EditUsername.SetWindowText(_T("admin"));
	m_EditPort.SetWindowText(_T("34567"));
	
	//setting list item
	m_CtrlListDev.InsertColumn(0, _CS(_T("Upgrade.NO")), LVCFMT_LEFT, 50);
	m_CtrlListDev.InsertColumn(1, _CS(_T("ConfigNet.DeviceName")), LVCFMT_LEFT, 80);
	m_CtrlListDev.InsertColumn(2, _CS(_T("ConfigNet.MAC")), LVCFMT_LEFT, 80);
	m_CtrlListDev.InsertColumn(3, _CS(_T("DeviceManage.IPAddress")), LVCFMT_LEFT, 80);
	m_CtrlListDev.InsertColumn(4, _CS(_T("DeviceManage.PortNum")), LVCFMT_LEFT,80);
	m_CtrlListDev.SetExtendedStyle( m_CtrlListDev.GetExtendedStyle() | LVS_EX_FULLROWSELECT );	 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRemoteChannelDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	// TODO: Add your message handler code here
	if ( bShow )
	{
		//CUserDataManager* pData = CUserDataManager::instance();
		//int nRet = pData->GetRemoteSysConfig(E_SDK_CONFIG_SYSNET, -1, (char *)&m_Netcomm,sizeof(m_Netcomm),FALSE,NULL);
		((CClientDemo5Dlg *)AfxGetMainWnd())->GetNetCommon();
		if ( strcmp(m_pNetConfig.Address, "") != 0 )
		{
			CString str;
			str = m_pNetConfig.ConfName;
			m_EditCfgName.SetWindowText( str );
			str = m_pNetConfig.UserName;
			m_EditUsername.SetWindowText( str );
			str = m_pNetConfig.PassWord;
			m_EditPWD.SetWindowText( str );
			str.Format(_T("%d"),m_pNetConfig.Port);
			m_EditPort.SetWindowText(str);
			str.Format(_T("%d"),m_pNetConfig.Channel + 1);
			m_EditRemoteChannel.SetWindowText(str);
			str = m_pNetConfig.Address;
			m_CtrlIPAddress.SetWindowText(str);
			m_cmbDevType.SetCurSel(m_pNetConfig.DevType);
			m_cmbStream.SetCurSel(m_pNetConfig.StreamType);
			m_cmbProc.SetCurSel(m_pNetConfig.Protocol);
		}
		
		UpdateData(FALSE);
	}
}
ULONG __stdcall SearchDevice(LPVOID parm)
{
	CRemoteChannelDlg* pThis = (CRemoteChannelDlg*)parm;
	int bResult = TRUE;
	DWORD dwReturned = 0;
	bResult = H264_DVR_SearchDevice((char*)pThis->m_Device, sizeof(pThis->m_Device), (int *)&dwReturned,5000);
	//	int bRet = pData->GetRemoteSysConfig(E_SDK_CONFIG_REMOTECHANNEL, 0, (char*)pThis->m_Device,sizeof(pThis->m_Device),FALSE,(DWORD*)(&nRetLength));
		if ( bResult > 0 && dwReturned > 0 )
		{
			pThis->m_nDevNum = sizeof(pThis->m_Device) / sizeof(SDK_CONFIG_NET_COMMON);	
		}
		CloseHandle(pThis->m_hSearch);
		pThis->m_hSearch = NULL;
		pThis->SetTimer(2, 0, NULL);

	return 0;
}

void CRemoteChannelDlg::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
	m_nDevNum = 0;
	int count = m_CtrlListDev.GetItemCount(); 
	
	for ( int i = 0; i < count; i ++ )
	{
		SDK_CONFIG_NET_COMMON *pData = (SDK_CONFIG_NET_COMMON *)m_CtrlListDev.GetItemData(i);
		if ( pData )
		{
			//delete pData;
			pData = NULL;
		}
	}
	m_CtrlListDev.DeleteAllItems();
	
	//清除Map
	m_mapDev.clear();
	
	memset( m_Device, 0 ,sizeof(SDK_CONFIG_NET_COMMON));
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(FALSE);
	
	DWORD ThreadeID;
	if ( m_hSearch == NULL )
	{
		m_hSearch = CreateThread( NULL, 0, SearchDevice, this, NULL, &ThreadeID);
	}
	
	//设置鼠标状态
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	CWnd::SetCapture();
}

void CRemoteChannelDlg::OnClickListDev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	int nIndex = m_CtrlListDev.GetSelectionMark();
	if ( nIndex >= 0 )
	{
		SDK_CONFIG_NET_COMMON* pNetConfig = (SDK_CONFIG_NET_COMMON*)m_CtrlListDev.GetItemData( nIndex );
		if ( pNetConfig )
		{
			//m_CtrlIPAddress.SetAddress(pNetConfig->HostIP.c[0],pNetConfig->HostIP.c[1],pNetConfig->HostIP.c[2],pNetConfig->HostIP.c[3]);
			CString strAddr;
			strAddr.Format(_T("%d.%d.%d.%d"), pNetConfig->HostIP.c[0],pNetConfig->HostIP.c[1],pNetConfig->HostIP.c[2],pNetConfig->HostIP.c[3]);
			m_CtrlIPAddress.SetWindowText(strAddr);
			m_nPort = pNetConfig->TCPPort;
		}
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CRemoteChannelDlg::OnChangeEditPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strPort;
	m_EditPort.GetWindowText(strPort);
	
	if ( atoi(strPort) > 655356 )
	{
		m_EditPort.SetWindowText(_T("655356"));
	}
	
	m_EditPort.SetFocus();
}

void CRemoteChannelDlg::OnKillfocusEditPort() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strPort;
	m_EditPort.GetWindowText(strPort);
	
	if ( atoi(strPort) > 655356 )
	{
		m_EditPort.SetWindowText(_T("655356"));
	}
	
	if ( atoi(strPort) < 1 )
	{
		m_EditPort.SetWindowText(_T("34567"));
	}
}

void CRemoteChannelDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == 2 )
	{
		GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(TRUE);
		KillTimer(2);
		
		int nIndex = 0;
		int i = 0;
		int count = m_CtrlListDev.GetItemCount();
		for ( i = 0; i < count; i ++ )
		{
			CString strIp;
			CString strIp2;
			int nPort;
			int nPort2;
			strIp.Format(_T("%d.%d.%d.%d"), m_Device[i].HostIP.c[0], m_Device[i].HostIP.c[1],m_Device[i].HostIP.c[2], m_Device[i].HostIP.c[3]);
			nPort=m_Device[i].TCPPort;
			
			for ( int j = i + 1; j < count; j ++ )
			{
				strIp2.Format(_T("%d.%d.%d.%d"), m_Device[j].HostIP.c[0], m_Device[j].HostIP.c[1],
					m_Device[j].HostIP.c[2], m_Device[j].HostIP.c[3]);
				nPort2 = m_Device[j].TCPPort;
				
				if ( strIp2 == strIp && nPort2 == nPort )
				{
					memset( &m_Device[j], 0 ,sizeof(SDK_CONFIG_NET_COMMON));
				}
			}
		}
		
		for (i = 0 ; i < m_nDevNum; i ++ )	
		{
			if ( m_Device[i].TCPPort == 0 || m_Device[i].HostIP.l == 0 )
			{
				continue;
			}
			
			CString strIP1,strIP2;
			strIP1.Format(_T("%d.%d.%d.%d"), m_Netcomm.HostIP.c[0], m_Netcomm.HostIP.c[1],
				m_Netcomm.HostIP.c[2], m_Netcomm.HostIP.c[3]);
			strIP2.Format(_T("%d.%d.%d.%d"), m_Device[i].HostIP.c[0], m_Device[i].HostIP.c[1],
				m_Device[i].HostIP.c[2], m_Device[i].HostIP.c[3]);
			if ( !strcmp( m_Netcomm.sMac, m_Device[i].sMac ) &&  (strIP1 == strIP2 ) )   //搜索列表中排除本机地址
			{
				continue;
			}
			//过滤已经存在设备，防止网关数不止一个，导致重复出现
			int nFlag = 0;
			if ( strcmp(m_mapDev[0].sMac, "") )   //当mac存在时
			{
				int j = 0;
				std::map<int, SDK_CONFIG_NET_COMMON>::iterator iter = m_mapDev.begin();
				for ( ; iter != m_mapDev.end(); iter ++)
				{
					SDK_CONFIG_NET_COMMON pDevInfo;
					memset( &pDevInfo, 0 ,sizeof(SDK_CONFIG_NET_COMMON));
					memcpy( &pDevInfo ,&m_mapDev[j],sizeof(SDK_CONFIG_NET_COMMON));
					//CString strIP1,strIP2;
					strIP1.Format(_T("%d.%d.%d.%d"), pDevInfo.HostIP.c[0], pDevInfo.HostIP.c[1],
						pDevInfo.HostIP.c[2], pDevInfo.HostIP.c[3]);
					strIP2.Format(_T("%d.%d.%d.%d"), m_Device[i].HostIP.c[0], m_Device[i].HostIP.c[1],
						m_Device[i].HostIP.c[2], m_Device[i].HostIP.c[3]);
					if ( strIP1 == strIP2 && !strcmp( pDevInfo.sMac , m_Device[i].sMac))
					{
						nFlag = 1; //存在相同设备，IP和Mac相同
						break;
					}
					j ++;
				}
			}
			
			if ( nFlag )
			{
				continue;
			}else
			{
				CString strTemp(_T(""));
				strTemp.Format(_T("%d"), count + nIndex + 1);
				m_CtrlListDev.InsertItem(count + nIndex, strTemp);
				
				strTemp.Format(_T("%s"), m_Device[i].HostName);
				m_CtrlListDev.SetItemText(count + nIndex, 1, strTemp);
				strTemp.Format(_T("%s"),m_Device[i].sMac);
				m_CtrlListDev.SetItemText(count + nIndex, 2, strTemp);
				strTemp.Format(_T("%d.%d.%d.%d"), m_Device[i].HostIP.c[0], m_Device[i].HostIP.c[1],m_Device[i].HostIP.c[2], m_Device[i].HostIP.c[3]);
				m_CtrlListDev.SetItemText(count + nIndex, 3, strTemp);
				strTemp.Format(_T("%ld"), m_Device[i].TCPPort );
				m_CtrlListDev.SetItemText(count + nIndex, 4, strTemp );
				
				m_CtrlListDev.SetItemData(count + nIndex,(long)(&m_Device[i]) );
				
				memcpy( &m_mapDev[nIndex], &m_Device[i], sizeof(SDK_CONFIG_NET_COMMON));
				
				nIndex ++;
			}
		}
		
		ReleaseCapture(); //释放
	}
	CDialog::OnTimer(nIDEvent);
}

void CRemoteChannelDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	int nCount = m_CtrlListDev.GetItemCount();
	for ( int i = 0; i < nCount; i++)
	{
		SDK_CONFIG_NET_COMMON* pNetConfig = (SDK_CONFIG_NET_COMMON* )m_CtrlListDev.GetItemData(i);
		if ( pNetConfig )
		{
			//	delete pNetConfig;
			pNetConfig = NULL;
		}
	}
	
}
BOOL CRemoteChannelDlg::GetRemoteChannel(SDK_NetDecorderConfigV3 *pNetCfg)
{
	memcpy( pNetCfg, &m_pNetConfig, sizeof(SDK_NetDecorderConfigV3));
	return TRUE;
}

void CRemoteChannelDlg::GetData(SDK_CONFIG_NET_COMMON *pNetCommon)
{
	memcpy(&m_Netcomm,pNetCommon,sizeof(SDK_CONFIG_NET_COMMON));

}
