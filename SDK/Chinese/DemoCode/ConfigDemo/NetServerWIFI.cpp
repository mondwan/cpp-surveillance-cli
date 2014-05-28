// NetServerWIFI.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerWIFI.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerWIFI dialog


CNetServerWIFI::CNetServerWIFI(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerWIFI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerWIFI)
	m_sPassword = _T("");
	m_sSSID = _T("");
	m_bDhcp = FALSE;
	//}}AFX_DATA_INIT
}


void CNetServerWIFI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerWIFI)
	DDX_Control(pDX, IDC_EDIT_SSID, m_editSSID);
	DDX_Control(pDX, IDC_EDIT_PSW, m_editPSW);
	DDX_Control(pDX, IDC_IPADDRESS_MASK, m_IPMask);
	DDX_Control(pDX, IDC_IPADDRESS_GATEWAY, m_IPGateWay);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddr);
	DDX_Control(pDX, IDC_COMBO_KEYTYPE, m_cmbKeyType);
	DDX_Control(pDX, IDC_COMBO_ENCRYP, m_cmbEncryp);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkWIFI);
	DDX_Control(pDX, IDC_CHECK_DHCP, m_checkDHCP);
	DDX_Control(pDX, IDC_AP_LIST, m_listAP);
	DDX_Text(pDX, IDC_EDIT_PSW, m_sPassword);
	DDX_Text(pDX, IDC_EDIT_SSID, m_sSSID);
	DDX_Check(pDX, IDC_CHECK_DHCP, m_bDhcp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerWIFI, CDialog)
	//{{AFX_MSG_MAP(CNetServerWIFI)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_BN_CLICKED(IDC_CHECK_DHCP, OnCheckDhcp)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_AP_LIST, OnItemchangedApList)
	ON_CBN_SELCHANGE(IDC_COMBO_KEYTYPE, OnSelchangeComboKeytype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerWIFI message handlers

BOOL CNetServerWIFI::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	m_editPSW.SetLimitText(64);
	m_editSSID.SetLimitText(35);
	
	m_listAP.InsertColumn(0, _CS("ConfigNet.SSID"), LVCFMT_LEFT, 150);
	m_listAP.InsertColumn(1, _CS("ConfigNet.AuthMode"),LVCFMT_LEFT, 85);
	m_listAP.InsertColumn(2, _CS("ConfigNet.Signal"),LVCFMT_LEFT, 85);
	m_listAP.SetExtendedStyle(m_listAP.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	CenterWindow();
	_CWndCS(this);
	return TRUE;  
}

void CNetServerWIFI::InitDlgInfo(SDK_NetWifiConfig *pNetWIFICfg)
{
	m_listAP.DeleteAllItems();
	m_ensure = FALSE;
	memcpy(&m_netWIFICfg,pNetWIFICfg,sizeof(SDK_NetWifiConfig));

	m_checkWIFI.SetCheck(m_netWIFICfg.bEnable);
	m_checkDHCP.SetCheck(m_bDhcpVisible);
	
	m_sSSID = m_netWIFICfg.sSSID;
	
	m_IPAddr.SetAddress(m_netWIFICfg.HostIP.c[0], m_netWIFICfg.HostIP.c[1], 
		m_netWIFICfg.HostIP.c[2], m_netWIFICfg.HostIP.c[3]);
	m_IPMask.SetAddress(m_netWIFICfg.Submask.c[0], m_netWIFICfg.Submask.c[1], 
		m_netWIFICfg.Submask.c[2], m_netWIFICfg.Submask.c[3]);
	m_IPGateWay.SetAddress(m_netWIFICfg.Gateway.c[0], m_netWIFICfg.Gateway.c[1], 
		m_netWIFICfg.Gateway.c[2], m_netWIFICfg.Gateway.c[3]);


	m_sPassword = m_netWIFICfg.sKeys;
	UpdateData(FALSE);

	m_pCurAP = NULL;

	m_cmbKeyType.ResetContent();
	m_cmbKeyType.AddString(_CS(_T("ConfigNet.Hex")));
	m_cmbKeyType.AddString(_CS(_T("ConfigNet.ASCII")));

	
	m_cmbEncryp.ResetContent();
	if ( strcmp(m_netWIFICfg.sEncrypType, _T("")) != 0)
	{
		m_cmbEncryp.ResetContent();
		CString strEncryp;
		strEncryp = m_netWIFICfg.sEncrypType;
		m_cmbEncryp.AddString(strEncryp);
	}
	
	if( strcmp(m_netWIFICfg.sEncrypType, "WEP") != 0 )
	{
		m_cmbKeyType.SetCurSel(1);  //WPA加密方式中采用的加密类型为ASCII
		m_nLastKey = 1;
		
		m_cmbKeyType.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(SW_HIDE);
	}else
	{
		m_cmbKeyType.SetCurSel( m_netWIFICfg.nKeyType); //WEP的加密类型分为Hex和ASCII，0为Hex，1为ASCII
		m_nLastKey = m_netWIFICfg.nKeyType;
		
		//选择的是WEP加密方式
		m_cmbKeyType.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(SW_SHOW);
	}
	m_cmbEncryp.SetCurSel(0);

	OnCheckEnable();
	OnCheckDhcp();
	
	m_editPSW.SetWindowText(m_netWIFICfg.sKeys);

	if (!m_bDhcpVisible)
	{
		GetDlgItem(IDC_CHECK_DHCP)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);

}


void CNetServerWIFI::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
	m_listAP.DeleteAllItems();
	bool bSuccess =  ((CClientDemo5Dlg*)AfxGetMainWnd())->GetWIFIDeviceALLInfo(&m_WifiDevAll);
	if (bSuccess)
	{
		for (int i = 0; i < m_WifiDevAll.nDevNumber; i++)
		{
			m_listAP.InsertItem(i, m_WifiDevAll.vNetWifiDeviceAll[i].sSSID);
			m_listAP.SetItemText(i, 1, m_WifiDevAll.vNetWifiDeviceAll[i].sAuth);
			CString strRSSI;
			switch(m_WifiDevAll.vNetWifiDeviceAll[i].nRSSI)
			{
			case SDK_RSSI_NO_SIGNAL:
				strRSSI = _CS("ConfigNet.NoSignal");
				break;
			case SDK_RSSI_VERY_LOW:
				strRSSI = _CS("ConfigNet.VeryLow");
				break;
			case SDK_RSSI_LOW:
				strRSSI = _CS("ConfigNet.Low");
				break;
			case SDK_RSSI_GOOD:
				strRSSI = _CS("ConfigNet.Good");
				break;
			case SDK_RSSI_VERY_GOOD:
				strRSSI = _CS("ConfigNet.VeryGood");
				break;
			case SDK_RSSI_EXCELLENT:
				strRSSI = _CS("ConfigNet.Excellent");
				break;
			default:
				strRSSI = _CS("ConfigNet.NoSignal");
				break;
			}
			m_listAP.SetItemText(i, 2, strRSSI);
		}
	}
	else
	{
		MessageBox(_CS("Error.GetConfigFail"), _CS("OneClick.Prompt") );
	}
	
}

void CNetServerWIFI::OnCheckEnable() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	BOOL bEnable = m_checkWIFI.GetCheck();
	
	m_IPAddr.EnableWindow(bEnable);
	m_IPGateWay.EnableWindow(bEnable);
	m_IPMask.EnableWindow(bEnable);
	m_editPSW.EnableWindow(bEnable);
	
	m_cmbKeyType.EnableWindow(bEnable);
	m_cmbEncryp.EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ENCRYP)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_KEYTYPE)->EnableWindow(bEnable);
}

void CNetServerWIFI::OnCheckDhcp() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_IPAddr.EnableWindow(!m_bDhcp);
	m_IPMask.EnableWindow(!m_bDhcp);
	m_IPGateWay.EnableWindow(!m_bDhcp);
}

void CNetServerWIFI::OnItemchangedApList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int nSelectIndex = pNMListView->iItem ;
	if ( nSelectIndex < 0 || nSelectIndex > m_WifiDevAll.nDevNumber)
	{
		m_pCurAP = NULL;
		return;
	}
	m_pCurAP = &m_WifiDevAll.vNetWifiDeviceAll[nSelectIndex];
	m_cmbKeyType.ResetContent();
	if ( m_pCurAP )
	{
		m_cmbEncryp.AddString(m_pCurAP->sEncrypType);
		m_cmbEncryp.SetCurSel(0);
		if ( strcmp(m_pCurAP->sEncrypType, _T("WEP")) )
		{
			m_cmbEncryp.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(SW_HIDE);
		}else
		{
			m_cmbEncryp.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(SW_SHOW);
			m_cmbEncryp.SetCurSel(0); 
		}
		
	}
	m_editSSID.SetWindowText(m_WifiDevAll.vNetWifiDeviceAll[nSelectIndex].sSSID);
	*pResult = 0;
}


void CNetServerWIFI::OnOK() 
{
	// TODO: Add extra validation here
	m_ensure = TRUE;
	UpdateData();
	m_netWIFICfg.bEnable = m_checkWIFI.GetCheck();
	
	strncpy(m_netWIFICfg.sSSID, m_sSSID.GetBuffer(0), sizeof(m_netWIFICfg.sSSID));

	strncpy(m_netWIFICfg.sKeys, m_sPassword.GetBuffer(0), sizeof(m_netWIFICfg.sKeys));

	m_netWIFICfg.nKeyType = 1;  //默认是ASCII
	
	//对WEP加密方式，限制条件
	if (( strcmp(m_netWIFICfg.sEncrypType, _T("WEP")) == 0) && ( m_cmbKeyType.GetCurSel() == 0) && ( m_checkWIFI.GetCheck()))
	{
		////选择为Hex
		//if ( strPasswd.GetLength() != 10 && strPasswd.GetLength() != 26 && strPasswd.GetLength() != 32 )
		//{
		//	MessageBox(_CS("ConfigNet.WifiPWDNoMatchHex"), _CS("OneClick.Prompt"));
		//	return;
		//}
		m_netWIFICfg.nKeyType = 0;
	}else if ( ( strcmp(m_netWIFICfg.sEncrypType, _T("WEP")) == 0 ) && ( m_cmbKeyType.GetCurSel() == 1) && ( m_checkWIFI.GetCheck() ) )
	{
		////选择为ASCII
		//if ( strPasswd.GetLength() != 5 && strPasswd.GetLength() != 13 && strPasswd.GetLength() != 16 )
		//{
		//	MessageBox(_CS("ConfigNet.WifiPWDNoMatchASCII"), _CS("OneClick.Prompt"));
		//	return;
		//}
		m_netWIFICfg.nKeyType = 1;
	}
	

	
	m_IPAddr.GetAddress(m_netWIFICfg.HostIP.c[0], m_netWIFICfg.HostIP.c[1], 
		m_netWIFICfg.HostIP.c[2], m_netWIFICfg.HostIP.c[3]);
	m_IPMask.GetAddress(m_netWIFICfg.Submask.c[0], m_netWIFICfg.Submask.c[1], 
		m_netWIFICfg.Submask.c[2], m_netWIFICfg.Submask.c[3]);
	m_IPGateWay.GetAddress(m_netWIFICfg.Gateway.c[0], m_netWIFICfg.Gateway.c[1], 
		m_netWIFICfg.Gateway.c[2], m_netWIFICfg.Gateway.c[3]);
	
	if ((m_netWIFICfg.HostIP.l & m_netWIFICfg.Submask.l) != (m_netWIFICfg.Gateway.l & m_netWIFICfg.Submask.l))
	{
		MessageBox(_CS("ConfigNet.SetGatewayFailed"), _CS("OneClick.Prompt"));
		return;
	}
	
	if (m_pCurAP) //有修改
	{
		////目前只支持WEP加密
		//if (strcmp(m_pCurAP->sAuth, "OPEN") != 0 && strcmp(m_pCurAP->sAuth, "SHARED") !=0)
		//{
		//	MessageBox(_CS("ConfigNet.WifiNotSupport"), _CS("OneClick.Prompt"));
		//	return;
		//}
		
		//m_netWIFICfg.nKeyType = 0;
		if ( strcmp(m_pCurAP->sEncrypType, "WEP") == 0 )
		{
			m_netWIFICfg.nKeyType = m_cmbKeyType.GetCurSel();
		}else
		{
			m_netWIFICfg.nKeyType = 1;  //默认是ASCII
		}
		//m_netWIFICfg.nKeyType = m_ctrKeyType.GetCurSel();
		memset(m_netWIFICfg.sEncrypType, 0 , sizeof(m_netWIFICfg.sEncrypType));
		m_netWIFICfg.nChannel = 0;
		strncpy(m_netWIFICfg.sAuth, m_pCurAP->sAuth, sizeof(m_netWIFICfg.sAuth));
		strncpy(m_netWIFICfg.sEncrypType, m_pCurAP->sEncrypType, sizeof(m_netWIFICfg.sEncrypType));
		strncpy(m_netWIFICfg.sSSID, m_pCurAP->sSSID, sizeof(m_netWIFICfg.sSSID));
		strncpy(m_netWIFICfg.sNetType, m_pCurAP->sNetType, sizeof(m_netWIFICfg.sNetType));
	}
	CDialog::OnOK();
}

void CNetServerWIFI::OnSelchangeComboKeytype() 
{
	// TODO: Add your control notification handler code here
	if ( m_cmbKeyType.GetCurSel() != m_nLastKey )
	{
		m_editPSW.SetWindowText(_T(""));
		m_nLastKey = m_cmbKeyType.GetCurSel();
	}
}
