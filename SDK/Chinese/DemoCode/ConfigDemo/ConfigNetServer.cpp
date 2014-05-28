// ConfigNetServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigNetServer.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigNetServer dialog


CConfigNetServer::CConfigNetServer(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigNetServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigNetServer)
		// NOTE: the ClassWizard will add member initialization here
	memset( &m_bChange, 0, sizeof(m_bChange) );
	//}}AFX_DATA_INIT
}


void CConfigNetServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigNetServer)
	DDX_Control(pDX, IDC_LIST_NETSERVER, m_listNetServer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigNetServer, CDialog)
	//{{AFX_MSG_MAP(CConfigNetServer)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NETSERVER, OnDblclkListNetserver)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigNetServer message handlers

BOOL CConfigNetServer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ipFilterDlg.Create(IDD_CONFIG_NETSERVER_IPFILTER);
	m_ddnsDlg.Create(IDD_CONFIG_NETSERVER_DDNS);
	m_emailDlg.Create(IDD_CONFIG_NETSERVER_EMAIL);
	m_ntpDlg.Create(IDD_CONFIG_NETSERVER_NTP);
	m_pppoeDlg.Create(IDD_CONFIG_NETSERVER_PPPOE);
	m_arspDlg.Create(IDD_CONFIG_NETSERVER_ARSP);
	m_3gDlg.Create(IDD_CONFIG_NETSERVER_3G);
	m_mobileDlg.Create(IDD_CONFIG_NETSERVER_MOBILE);
	m_upnpDlg.Create(IDD_CONFIG_NETSERVER_UPNP);
	m_ftpDlg.Create(IDD_CONFIG_NETSERVER_FTP);
	m_wifiDlg.Create(IDD_CONFIG_NETSERVER_WIFI);
	m_alarmDlg.Create(IDD_CONFIG_NETSERVER_ALARM_CENTER);
	m_rtspDlg.Create(IDD_CONFIG_NETSERVER_RTSP);
	m_shortMsgDlg.Create(IDD_CONFIG_NETSERVER_SHORT_MESSAGE);
	m_dasDlg.Create(IDD_CONFIG_NETSERVER_DAS);
	m_multiMdeiaDlg.Create(IDD_CONFIG_NETSERVER_MULTIMEDIA);
	m_dnsDlg.Create(IDD_CONFIG_NETSERVER_DNS);
	m_vveyeDlg.Create(IDD_CONFIG_NETSERVER_VVEye);
	m_shisouDlg.Create(IDD_CONFIG_NETSERVER_SHISOU);
	m_xingwangDlg.Create(IDD_CONFIG_NETSERVER_XINGWANG);
	m_godeyeDlg.Create(IDD_CONFIG_NETSERVER_GODEYE);
	m_netInfoDlg.Create(IDD_CONFIG_NETSERVER_NETIFNO);
	m_natDlg.Create(IDD_CONFIG_NETSERVER_NAT);
	_CWndCS(this);
	return TRUE;  
}

void CConfigNetServer::InitDlgInfo(SDK_SystemFunction *SysFunc)
{
	m_listNetServer.DeleteAllItems();
	int nRet = 0;
	int nIndex = 0;
	for ( int i =0 ; i < SDK_NET_SERVER_TYPES_NR; i ++ )
	{
		if ( SysFunc->vNetServerFunction[i] )
		{
			switch( i )
			{
			case SDK_NET_SERVER_TYPES_IPFILTER:	//白黑名单
				nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.IPSetting") );
				m_listNetServer.SetItemData(nRet, i);
				break;
			case SDK_NET_SERVER_TYPES_DDNS:		//DDNS功能
				nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.DDNS") );
				m_listNetServer.SetItemData(nRet, i);
				break;
			case SDK_NET_SERVER_TYPES_EMAIL:	//Email功能
				nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.EmailConfig") );
				m_listNetServer.SetItemData(nRet, i);
				break;
			case SDK_NET_SERVER_TYPES_MULTICAST:	//多播功能
				nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.MulticastConfig") );
				m_listNetServer.SetItemData(nRet, i);
				break;	
			case SDK_NET_SERVER_TYPES_NTP:		//NTP功能
				nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.NtpConfig") );
				m_listNetServer.SetItemData(nRet, i);
				
				break;
			case SDK_NET_SERVER_TYPES_PPPOE:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.PPPoE") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_ARSP:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.ARSPConfig") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_MOBILE:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.MobileConfig") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_3G:
				{		
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.Wireless") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_UPNP:
				{		
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.UPNP") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_FTP:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.FTP") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_WIFI:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.Wifi") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_ALARM_CENTER:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.AlarmCenter") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_NETPLAT_VVEYE:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.VVEye") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break; 
			case SDK_NET_SERVER_TYPES_NETPLAT_SHISOU:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.ShiSou") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break; 
			case SDK_NET_SERVER_TYPES_NETPLAT_XINWANG:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.XingWang") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break; 
// 			case SDK_NET_SERVER_TYPES_DNS:
// 				{
// 					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("DNS") );
// 					m_listNetServer.SetItemData(nRet, i);
// 					pData->GetRemoteSysConfig(E_SDK_CONFIG_NET_DNS, -1,  (char *)&m_NetDNS, sizeof(m_NetDNS), false );
// 
// 					m_bSetCheck = true;
// 					m_listNetServer.SetCheck(nRet, TRUE);
// 					m_bSetCheck =false;
// 				}
// 				break;
			case SDK_NET_SERVER_TYPES_RTSP:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.RTSP") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_PHONEMSG:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.ShortMsg") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.MultiMedia") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_DAS:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.DAS") );
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM:
				{
					nRet = m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.NetInfo"));
					m_listNetServer.SetItemData(nRet,i);
				}
				break;
			case SDK_NET_SERVER_TYPES_GOD_EYE:
				{
					nRet =m_listNetServer.InsertItem( nIndex ++, _CS("ConfigNet.GodEye"));
					m_listNetServer.SetItemData(nRet, i);
				}
				break;
			case SDK_NET_SERVER_TYPES_NAT:
				{
					nRet = m_listNetServer.InsertItem(nIndex++,_CS("ConfigNet.NAT"));
					m_listNetServer.SetItemData(nRet,i);
				}
				break;
			default:
				break;
			}
		}
	}
}

void CConfigNetServer::OnOK() 
{
	CDialog::OnOK();
}

void CConfigNetServer::OnDblclkListNetserver(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CClientDemo5Dlg* pMainDlg = ((CClientDemo5Dlg*)AfxGetMainWnd());
	int nIndex = m_listNetServer.GetSelectionMark();
	if ( nIndex < 0 )
	{
		return;
	}
	int nRet = 1;
	int nData = m_listNetServer.GetItemData(nIndex);
	switch(nData)
	{
	case SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG:
		{
			//手机彩信
			pMainDlg->GetMultimediaConfigInfo();
			m_bChange[SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG] = true;
 			m_multiMdeiaDlg.ShowWindow(SW_SHOW);
			break;
		}
		
	case SDK_NET_SERVER_TYPES_PHONEMSG:
		{
			//手机短信
			pMainDlg->GetShortMsgConfigInfo();
			m_bChange[SDK_NET_SERVER_TYPES_PHONEMSG] = true;
 			m_shortMsgDlg.ShowWindow(SW_SHOW);
		}
		break;
	case SDK_NET_SERVER_TYPES_IPFILTER:
		{
			//获取黑名单配置
			pMainDlg->GetIPFilterConfigInfo();
			m_bChange[SDK_NET_SERVER_TYPES_IPFILTER] = true;
			m_ipFilterDlg.ShowWindow(SW_SHOW);
		}
		break;
	case SDK_NET_SERVER_TYPES_DDNS:
		{
			pMainDlg->GetDDNSConfigInfo();
			m_ddnsDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_DDNS] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_EMAIL:
		{
			pMainDlg->GetEmailConfigInfo();
			m_bChange[SDK_NET_SERVER_TYPES_EMAIL] = true;
 			m_emailDlg.ShowWindow(SW_SHOW);	
		}
		break;
	case SDK_NET_SERVER_TYPES_MULTICAST:
		break;
	case SDK_NET_SERVER_TYPES_NTP:
		{
			pMainDlg->GetNTPConfigInfo();
 			m_ntpDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_NTP] = true;
		}
		break;
	case  SDK_NET_SERVER_TYPES_PPPOE:
		{
			pMainDlg->GetPPPOEConfigInfo();		
			m_pppoeDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_PPPOE] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_ARSP:
		{
			pMainDlg->GetARSPConfigInfo();
 			m_arspDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_ARSP] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_MOBILE:
		{
			pMainDlg->GetMobileConfigInfo();
 			m_mobileDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_MOBILE] = true;			
		}
		break;
	case SDK_NET_SERVER_TYPES_3G:
		{
			pMainDlg->Get3GConfigInfo();
 			m_3gDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_3G] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_UPNP:
		{
			pMainDlg->GetUPNPConfigInfo();
 			m_upnpDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_UPNP] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_FTP:
		{
			pMainDlg->GetFTPConfigInfo();
 			m_ftpDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_FTP] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_WIFI:
		{
			int nWaitTime = 10000;
			DWORD dwRetLen = 0;
			H264_DVR_DEVICEINFO deviceInfo;
			bool bSuccess = H264_DVR_GetDevConfig(pMainDlg->m_LoginID, E_SDK_CONFIG_SYSINFO ,0, 
				(char *)&deviceInfo ,sizeof(H264_DVR_DEVICEINFO), &dwRetLen,nWaitTime);
			CString time;
			time.Format("%04d-%02d-%02d %02d:%02d:%02d", 
				deviceInfo.tmBuildTime.year,
				deviceInfo.tmBuildTime.month,
				deviceInfo.tmBuildTime.day,
				deviceInfo.tmBuildTime.hour,
				deviceInfo.tmBuildTime.minute,
				deviceInfo.tmBuildTime.second);
			
			int nRet=0;
			CString okTime("2012-06-22");//设备那端这个时间之后的才支持wifi的dhcp
				m_wifiDlg.m_bDhcpVisible = FALSE;
			if(time > okTime)
			{
				pMainDlg->GetDHCPConfigInfo(&m_NetDHCP);
				m_wifiDlg.m_bDhcpVisible = TRUE;
				m_wifiDlg.m_bDhcp = m_NetDHCP.vNetDHCPConfig[2].bEnable;
			}
			pMainDlg->GetWIFIConfigInfo();
 			m_wifiDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_DHCP]=true;
		}
		break;
	case SDK_NET_SERVER_TYPES_ALARM_CENTER:
		{
			pMainDlg->GetAlarmCenterConfigInfo();
 			m_alarmDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_ALARM_CENTER] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_NETPLAT_VVEYE:
		{
			pMainDlg->GetVVEyeConfigInfo();
 			m_vveyeDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_NETPLAT_VVEYE] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_NETPLAT_SHISOU:
		{
			pMainDlg->GetSHISOUConfigInfo();
 			m_shisouDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_NETPLAT_SHISOU] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_NETPLAT_XINWANG:
		{
			pMainDlg->GetXINGWANGConfigInfo();
 			m_xingwangDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_NETPLAT_XINWANG] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_RTSP:
		{
			pMainDlg->GetRTSPConfigInfo();
 			m_rtspDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_RTSP] = true;	
		}
		break;
	case SDK_NET_SERVER_TYPES_DAS:
		{
			pMainDlg->GetDASConfigInfo();
 			m_dasDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_DAS] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM:
		{
			pMainDlg->GetNetInfo();
			m_netInfoDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_GOD_EYE:
		{
			pMainDlg->GetGodEyeConfigInfo();
 			m_godeyeDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_GOD_EYE] = true;
		}
		break;
	case SDK_NET_SERVER_TYPES_NAT:
		{
			pMainDlg->GetNatInfo();
			m_natDlg.ShowWindow(SW_SHOW);
			m_bChange[SDK_NET_SERVER_TYPES_NAT] = true;
		}
	default:
		break;
	}	
}
void CConfigNetServer::CleanAll()
{
	m_listNetServer.DeleteAllItems();
	UpdateData(FALSE);
}

void CConfigNetServer::OnButtonApply() 
{
	CClientDemo5Dlg* pMainDlg = ((CClientDemo5Dlg*)AfxGetMainWnd());
	CString strMsg[] = {"ConfigNet.IPSetting", "ConfigNet.DHCP", "ConfigNet.DDNS", "ConfigNet.EmailConfig", "ConfigNet.MulticastConfig", 
		"ConfigNet.NtpConfig", "ConfigNet.PPPoE", "ConfigNet.DNSConfig", "ConfigNet.ARSPConfig", "ConfigNet.Wireless", "ConfigNet.MobileConfig",
	    "ConfigNet.UPNP", "ConfigNet.FTP", "ConfigNet.Wifi", "ConfigNet.AlarmCenter",
		"ConfigNet.Mega", "ConfigNet.XingWang", "ConfigNet.ShiSou", "ConfigNet.VVEye",
		"ConfigNet.RTSP", "ConfigNet.ShortMsg", "ConfigNet.MultiMedia", "ConfigNet.DAS",
		"ConfigNet.NetInfo" , "ConfigNet.GodEye"};

	bool bReboot = false;
	int nRet[SDK_NET_SERVER_TYPES_NR] = {0};
	int i;
	for (  i =0; i < SDK_NET_SERVER_TYPES_NR; i ++ )
	{
		if ( m_bChange[i] )
		{	
			switch(i)
			{
			case SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG:
				if (m_multiMdeiaDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG] = pMainDlg->SetMultimediaConfigInfo(&m_multiMdeiaDlg.m_netMultimediaMsgCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_PHONEMSG:
				if (m_shortMsgDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_PHONEMSG] = pMainDlg->SetShortMsgConfigInfo(&m_shortMsgDlg.m_netShortMsgCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_PHONEMSG] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_PHONEMSG] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_IPFILTER:
				if (m_ipFilterDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_IPFILTER] = pMainDlg->SetIPFilterConfigInfo(&m_ipFilterDlg.m_NetIPFitCfg);	
					if ( nRet[SDK_NET_SERVER_TYPES_IPFILTER] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_IPFILTER] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_DDNS:
				if (m_ddnsDlg.m_ensure)
				{
					 nRet[SDK_NET_SERVER_TYPES_DDNS] = pMainDlg->SetDDNSConfigInfo(&m_ddnsDlg.m_netDDNSCfg);	
					if (nRet[SDK_NET_SERVER_TYPES_DDNS] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_DDNS] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_EMAIL:
				if (m_emailDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_EMAIL] = pMainDlg->SetEmailConfigInfo(&m_emailDlg.m_netEmailCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_EMAIL] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_EMAIL] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_MULTICAST:
				break;
			case SDK_NET_SERVER_TYPES_NTP:
				if (m_ntpDlg.m_ensure)
				{
					 nRet[SDK_NET_SERVER_TYPES_NTP] = pMainDlg->SetNTPConfigInfo(&m_ntpDlg.m_netNTPCfg);
					if (nRet[SDK_NET_SERVER_TYPES_NTP] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_NTP] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_PPPOE:
				if (m_pppoeDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_PPPOE] = pMainDlg->SetPPPOEConfigInfo(&m_pppoeDlg.m_netPPPOECfg);
					if ( nRet[SDK_NET_SERVER_TYPES_PPPOE] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_PPPOE] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_ARSP:
				if (m_arspDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_ARSP] = pMainDlg->SetARSPConfigInfo(&m_arspDlg.m_netARSPCfg);	
					if ( nRet[SDK_NET_SERVER_TYPES_ARSP] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_ARSP] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_MOBILE:
				if (m_mobileDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_MOBILE] = pMainDlg->SetMobileConfigInfo(&m_mobileDlg.m_netMobileCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_MOBILE] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_MOBILE] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_3G:			
				if (m_3gDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_3G] = pMainDlg->Set3GConfigInfo(&m_3gDlg.m_net3GCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_3G] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_3G] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_UPNP:
				if (m_upnpDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_UPNP] = pMainDlg->SetUPNPConfigInfo(&m_upnpDlg.m_netUPNPCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_UPNP] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_UPNP] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_FTP:
				if (m_ftpDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_FTP] = pMainDlg->SetFTPConfigInfo(&m_ftpDlg.m_ftpCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_FTP] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_FTP] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_WIFI:
				if (m_wifiDlg.m_ensure)
				{
					m_NetDHCP.vNetDHCPConfig[2].bEnable=m_wifiDlg.m_bDhcp;
					nRet[SDK_NET_SERVER_TYPES_WIFI] = pMainDlg->SetWIFIConfigInfo(&m_wifiDlg.m_netWIFICfg);	
					if ( nRet[SDK_NET_SERVER_TYPES_WIFI] == H264_DVR_OPT_REBOOT  
						|| nRet[SDK_NET_SERVER_TYPES_WIFI] == H264_DVR_SDK_TIMEOUT )  //超时状态下也默认为成功，需要重启
					{
						nRet[SDK_NET_SERVER_TYPES_WIFI] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_ALARM_CENTER:
				if (m_alarmDlg.m_ensure)
				{	
					nRet[SDK_NET_SERVER_TYPES_ALARM_CENTER] = pMainDlg->SetAlarmCenterConfigInfo(&m_alarmDlg.m_netAlarmCenterCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_ALARM_CENTER] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_ALARM_CENTER] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_NETPLAT_VVEYE:
				if (m_vveyeDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_NETPLAT_VVEYE] = nRet[SDK_NET_SERVER_TYPES_NETPLAT_VVEYE] = pMainDlg->SetVVEyeConfigInfo(&m_vveyeDlg.m_netVVEyeCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_NETPLAT_VVEYE] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_NETPLAT_VVEYE] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_NETPLAT_SHISOU:
				if (TRUE == m_shisouDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_NETPLAT_SHISOU] = pMainDlg->SetSHISOUConfigInfo(&m_shisouDlg.m_netSHISOUCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_NETPLAT_SHISOU] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_NETPLAT_SHISOU] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_NETPLAT_XINWANG:
				if (TRUE == m_xingwangDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_NETPLAT_XINWANG] = pMainDlg->SetXINGWANGConfigInfo(&m_xingwangDlg.m_netXIANGWANGCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_NETPLAT_XINWANG] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_NETPLAT_XINWANG] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_DNS:
// 				if (m_dnsDlg.m_ensure)
// 				{
// 					nRet[SDK_NET_SERVER_TYPES_DNS] = pMainDlg->SetDNSConfigInfo(&m_dnsDlg.m_netDNSCfg);	
// 					if ( nRet[SDK_NET_SERVER_TYPES_DNS] == H264_DVR_OPT_REBOOT )
// 					{
// 						nRet[SDK_NET_SERVER_TYPES_DNS] = 1;
// 						bReboot = true;
// 					}
// 				}
				break;
			case SDK_NET_SERVER_TYPES_RTSP:
				if (m_rtspDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_RTSP] = pMainDlg->SetRTSPConfigInfo(&m_rtspDlg.m_netRTSPCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_RTSP] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_RTSP] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_DAS:
				if (m_dasDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_DAS] = pMainDlg->SetDASConfigInfo(&m_dasDlg.m_netDASCfg);
					if ( nRet[SDK_NET_SERVER_TYPES_DAS] == H264_DVR_OPT_REBOOT )
					{
						nRet[SDK_NET_SERVER_TYPES_DAS] = 1;
						bReboot = true;
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM:
				if (m_netInfoDlg.m_ensure)
				{
					nRet[SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM] = pMainDlg->SetNetInfo(&m_netInfoDlg.m_LocSdkNetPC);
					 if ( nRet[SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM] == H264_DVR_OPT_REBOOT )
					 {
						 nRet[SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM] = 1;
						 bReboot = true;
					 }
				}
				break;
			case SDK_NET_SERVER_TYPES_GOD_EYE:
				{
					if (m_godeyeDlg.m_ensure)
					{
						nRet[SDK_NET_SERVER_TYPES_GOD_EYE] = pMainDlg->SetCGodEyeConfigInfo(&m_godeyeDlg.m_netGodEyeCfg);
						if ( nRet[SDK_NET_SERVER_TYPES_GOD_EYE] == H264_DVR_OPT_REBOOT )
						{
							nRet[SDK_NET_SERVER_TYPES_GOD_EYE] = 1;
							bReboot = true;
						}
					}
				}
				break;
			case SDK_NET_SERVER_TYPES_DHCP:
				{
					break;
				}
			case SDK_NET_SERVER_TYPES_NAT:
				{
					if (m_natDlg.m_ensure)
					{
						nRet[SDK_NET_SERVER_TYPES_NAT] = pMainDlg->SetNatInfo(&m_natDlg.m_natCfg);
						if (nRet[SDK_NET_SERVER_TYPES_NAT] == H264_DVR_OPT_REBOOT)
						{
							nRet[SDK_NET_SERVER_TYPES_NAT] = 1;
							bReboot = true;
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}

	
	if ( bReboot )
	{
		if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
		{
			pMainDlg->SetReBootDev();
		}
		return;
	}

	CString strPrompt(_CS("Error.SetConfigFail"));

	bool bfirst = true;	
	for (i = 0; i < SDK_NET_SERVER_TYPES_NR; i ++ )
	{
		if ( nRet[i] < 0 )
		{
			if ( !bfirst )
			{
				strPrompt += ",";
			}	
			strPrompt += _CS(strMsg[i]);

			bfirst = false;
		}
	}

	if ( bfirst )
	{
		MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );  
	}
	else
	{
		MessageBox(strPrompt, _CS("OneClick.Prompt") );  
	}
	memset( &m_bChange, 0, sizeof(m_bChange) );
}

void CConfigNetServer::OnButtonReadall() 
{
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetNetServerConfigInfo();	
}




