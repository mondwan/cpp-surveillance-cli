#if !defined(AFX_CONFIGNETSERVER_H__B588D409_608B_4C80_BA15_C38729305CE0__INCLUDED_)
#define AFX_CONFIGNETSERVER_H__B588D409_608B_4C80_BA15_C38729305CE0__INCLUDED_

#include "NetServerIPFilter.h"	// Added by ClassView
#include "NetServerDDNS.h"
#include "NetServerEmail.h"
#include "NetServerNTP.h"
#include "NetServerPPPOE.h"
#include "NetServerARSP.h"
#include "NetServer3G.h"
#include "NetServerMobile.h"
#include "NetServerUPNP.h"
#include "NetServerFTP.h"
#include "NetServerWIFI.h"
#include "NetServerALARM.h"
#include "NetServerRtsp.h"
#include "NetServerSHORTMSG.h"
#include "NetServerDAS.h"
#include "NetServerMultiMedia.h"
#include "NetServerDNS.h"
#include "NetServerVVEye.h"
#include "NetServerSHISOU.h"
#include "NetServerXINGWANG.h"
#include "NetServerGodEye.h"
#include "NetServerNetInfo.h"
#include "NetServerNAT.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigNetServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigNetServer dialog

class CConfigNetServer : public CDialog
{
// Construction
public:
	SDK_NetDHCPConfigAll m_NetDHCP;
	void CleanAll();
	/*
	SDK_NetIPFilterConfig m_netIPFitCfg;
	SDK_NetDDNSConfigALL m_netDDNSCfg;
	SDK_NetEmailConfig m_netEmailCfg;
	SDK_NetNTPConfig m_netNTPCfg;
	SDK_NetPPPoEConfig m_netPPPOECfg;
	SDK_NetARSPConfigAll m_netARSPCfg;
	SDK_Net3GConfig m_net3GCfg;
	SDK_NetMoblieConfig m_netMobileCfg;
	SDK_NetUPNPConfig m_netUPNPCfg;
	SDK_FtpServerConfig m_ftpCfg;
	SDK_NetWifiConfig m_netWIFICfg;
	SDK_NetAlarmServerConfigAll m_netAlarmCfg;
	SDK_NetRTSPConfig m_netRTSPCfg;
	SDK_NetShortMsgCfg m_netShortMsgCfg;
	SDK_DASSerInfo m_netDASCfg;
	SDK_NetMultimediaMsgCfg m_netMultimediaCfg;
	SDK_NetDNSConfig m_netDNSCfg;
	SDK_CONFIG_NET_VVEYE m_netVVEyeCfg;
	SDK_CONFIG_NET_SHISOU m_netSHISOUCfg;
	SDK_CONFIG_NET_XINGWANG m_netXINGWANGCfg;
	SDK_GodEyeConfig m_netGodEyeCfg;
	SDK_LocalSdkNetPlatformConfig m_netInfoCfg;
	*/
	CNetServerGodEye m_godeyeDlg;
	CNetServerXINGWANG m_xingwangDlg;
	CNetServerSHISOU m_shisouDlg;
	CNetServerVVEye m_vveyeDlg;
	CNetServerDNS m_dnsDlg;
	CNetServerMultiMedia m_multiMdeiaDlg;
	CNetServerDAS m_dasDlg;
	CNetServerSHORTMSG m_shortMsgDlg;
	CNetServerRtsp m_rtspDlg;
	CNetServerALARM m_alarmDlg;
	CNetServerWIFI m_wifiDlg;
	CNetServerFTP m_ftpDlg;
	CNetServerUPNP m_upnpDlg;
	CNetServerMobile m_mobileDlg;
	CNetServer3G m_3gDlg;
	CNetServerARSP m_arspDlg;
	CNetServerPPPOE m_pppoeDlg;
	CNetServerIPFilter m_ipFilterDlg;
	CNetServerDDNS m_ddnsDlg;
	CNetServerEmail m_emailDlg;
	CNetServerNTP m_ntpDlg;
	CNetServerNetInfo m_netInfoDlg;
	CNetServerNAT m_natDlg;

	bool m_bChange[SDK_NET_SERVER_TYPES_NR];	//记录网络服务是否更改
	void InitDlgInfo(SDK_SystemFunction *SysFunc);
	CConfigNetServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigNetServer)
	enum { IDD = IDD_CONFIG_NETSERVER };
	CListCtrl	m_listNetServer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigNetServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigNetServer)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkListNetserver(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGNETSERVER_H__B588D409_608B_4C80_BA15_C38729305CE0__INCLUDED_)
