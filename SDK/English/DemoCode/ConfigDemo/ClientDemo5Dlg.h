// ClientDemo5Dlg.h : header file
#include "ConfigServer.h"
#include "ConfigComm.h"	// Added by ClassView
#include "ConfigChannel.h"	// Added by ClassView
#include "ConfigAlarm.h"	// Added by ClassView
#include "ConfigRecord.h"	// Added by ClassView
#include "ConfigNetwork.h"	// Added by ClassView
#include "ConfigPtz.h"
#include "SysSettingCamera.h"
#include "SysSettingUserManager.h"
#include "ChannelNameSet.h"
#include "ConfigVehicle.h"
#include "DigitalChannelDlg.h"
#include "RemoteChannelDlg.h"
#include "afxwin.h"
#include "ConfigOutput.h"	// Added by ClassView
#include "LogInfoDlg.h"
#include "ConfigDigitalChannel.h"	// Added by ClassView
#include "ConfigNetServer.h"
#include "ToolManagerHardDisk.h"
#include "AlarmVideoAnalyse.h"
#include "SysInfoVersion.h"
#include "SnapStorageDlg.h"
#if !defined(AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_)
#define AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg dialog

class CClientDemo5Dlg : public CDialog
{
// Construction
public:
	//Callback function when device disconnected
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
	
	CClientDemo5Dlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CClientDemo5Dlg();

// Dialog Data
	//{{AFX_DATA(CClientDemo5Dlg)
	enum { IDD = IDD_CLIENTDEMO5_DIALOG };
	CTabCtrl	m_ctlMainTab;
	CIPAddressCtrl	m_ctlDvrIP;
	UINT	m_nPort;
	CString	m_strUserName;
	CString	m_strPwd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL AddPage(CString strTitle, CDialog* dlgPage, UINT uID);
	BOOL DeletePage();
	afx_msg void OnBtnLogin();
//	enum PAGETYPE{NONE, IPC, DVR};
//	PAGETYPE FromDeviceType(NET_DEVICE_TYPE eDeviceType);
	//end add
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemo5Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	afx_msg void OnBtnLogout();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeComboType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ExitSDk();
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void DoTab(int nTab);
	CDialog*	m_dlgDeviceType;

	void InitTabControl();
	void ShowLoginErrorReason(int nError);

	
	BOOL InitNetSDK();
	BOOL AlarmCfg_SC;
	BOOL AlarmExp_SC;
	BOOL AlarmCfg_RB;
	BOOL AlarmExp_RB;
	
public:
	void SetHardDiskInfo(SDK_StorageDeviceControl *pDiskCtl);
	void GetHardDiskInfo();
	void SetReBootDev();
	int SetNetInfo(SDK_LocalSdkNetPlatformConfig *pNetInfoCfg);
	void GetNetInfo();
	int SetCGodEyeConfigInfo(SDK_GodEyeConfig *pNetGodEyeCfg);
	void GetGodEyeConfigInfo();
	int SetXINGWANGConfigInfo(SDK_CONFIG_NET_XINGWANG *pNetXIANGWANGCfg);
	void GetXINGWANGConfigInfo();
	int SetSHISOUConfigInfo(SDK_CONFIG_NET_SHISOU *pNetSHISOUCfg);
	void GetSHISOUConfigInfo();
	int SetVVEyeConfigInfo(SDK_CONFIG_NET_VVEYE *pNetVVEyeCfg);
	void GetVVEyeConfigInfo();
	int SetDNSConfigInfo(SDK_NetDNSConfig *pNetDNSCfg);
	void GetDNSConfigInfo();
	void GetMultimediaConfigInfo();
	int SetMultimediaConfigInfo(SDK_NetMultimediaMsgCfg* pNetMultimediaMsgCfg);
	int SetDASConfigInfo(SDK_DASSerInfo *pNetDASCfg);
	void GetDASConfigInfo();
	int SetShortMsgConfigInfo(SDK_NetShortMsgCfg *pNetShortMsgCfg);
	void GetShortMsgConfigInfo();
	int SetRTSPConfigInfo(SDK_NetRTSPConfig *pNetRTSPCfg);
	void GetRTSPConfigInfo();
	int SetAlarmCenterConfigInfo(SDK_NetAlarmServerConfigAll *pNetAlarmCfg);
	void GetAlarmCenterConfigInfo();
	bool GetDHCPConfigInfo(SDK_NetDHCPConfigAll *pNetDHCPCfg);
	bool GetWIFIDeviceALLInfo(SDK_NetWifiDeviceAll *pNetWifiDeviceAll);
	int SetWIFIConfigInfo(SDK_NetWifiConfig *pNetWifiCfg);
	void GetWIFIConfigInfo();
	int SetFTPConfigInfo(SDK_FtpServerConfig *pFtpCfg);
	void GetFTPConfigInfo();
	void GetUPNPConfigInfo();
	int SetUPNPConfigInfo(SDK_NetUPNPConfig *pNetUPNPCfg);
	int SetMobileConfigInfo(SDK_NetMoblieConfig *pNetMobileCfg);
	void GetMobileConfigInfo();
	int Set3GConfigInfo(SDK_Net3GConfig *pNet3GCfg);
	void Get3GConfigInfo();
	int SetARSPConfigInfo(SDK_NetARSPConfigAll *pNetARSP);
	void GetARSPConfigInfo();
	int SetPPPOEConfigInfo(SDK_NetPPPoEConfig *pNetPPPOE);
	void GetPPPOEConfigInfo();
	//int SetMultiCastConfigInfo(SDK_NetMultiCastConfig *pNetMulticast);
	//void GetMultiCastConfigInfo();
	int SetPMSConfigInfo(SDK_PMSConfig *pNetPMS); 
	void GetPMSConfigInfo();
	//int SetPHConfigInfo(SDK_PhoneInfoNum *pNetPH);
	//void GetPHConfigInfo();

	void SetChnModeConfig(SDK_NetDecorderChnModeConfig*  pNetChnModeCfg);
	CString GetSdkErrorInfo(int nError);
	void GetLogInfo();
	void LocalCatPic(TCHAR* strFileName,int nChannelNum,CWnd* wnd);
	BOOL m_bOutputCfg[3];
	void SetOutputConfigInfo(OUTPUTCONFIGALL* outputCfgInfo);
	void GetOutputConfigInfo();

	long m_LoginID;
	void SetCameraPara(SDK_AllCameraParam* pCameraParaAll);
	void GetCameraPara();
	void SetPtzConfigInfo(SDK_STR_PTZCONFIG_ALL *pPtzConfigAll,SDK_STR_RS485CONFIG_ALL *pRSConfigALL);
	void GetPTZConfigInfo();
	void SetAlarmConfigInfo(ALARMCONFIGALL *pAlarmCfgAll);
	void GetAlarmConfigInfo();
	void SetNetWorkConfigInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP);
	void SetNetWorkConfigInfo(SDK_NetOrderConfig *pNetOrder);
	void GetNetWorkConfigInfo();
	void SetRecordConfigInfo(SDK_RECORDCONFIG_ALL* pRecordInfo);
	void GetRecordConfigInfo();
	void SetCommConfigInfo(SDK_CommConfigAll *pCommCfg);
	void GetCommConfigInfo();
	void SetChannelConfigInfo( SDK_EncodeConfigAll_SIMPLIIFY *pEncodeCfg,SDK_CombineEncodeConfigAll *pCmbEncodeCfg,SDK_CombEncodeModeAll *pCmbEncodeMode,SDK_EncodeStaticParamAll *pEncodeStatic);
	void GetNetServerConfigInfo();
	void GetIPFilterConfigInfo();
	int SetIPFilterConfigInfo(SDK_NetIPFilterConfig *pNetIPFitCfg);
	void GetDDNSConfigInfo();
	int SetDDNSConfigInfo(SDK_NetDDNSConfigALL* pNetDDNSCfg);
	void GetEmailConfigInfo();
	int SetEmailConfigInfo(SDK_NetEmailConfig* pNetEmail);
	void GetNTPConfigInfo();
	int SetNTPConfigInfo(SDK_NetNTPConfig *pNetNTP);
	int m_nChannelNum;
	int m_nAlarmInNum;
	int m_nAlarmOutNum;
	int m_nbyChanNum;
	int m_niDigChannel;
	void GetChannelConfigInfo();
	void SetDeviceConfigInfo(DEV_ATTRIBUTE *pDevAttribute);
	void GetDeviceConfigInfo();
	CLogInfoDlg m_logInfoDlg;
	CConfigOutput m_outputDlg;
	CConfigServer m_serverDlg;
	CConfigNetwork m_networkDlg;
	CConfigRecord m_recordDlg;
	CConfigAlarm m_alarmDlg;
	CConfigChannel m_channelDlg;
	CConfigComm m_commDlg;
	CConfigPtz m_Ptz;
	CSysSettingCamera m_SysCamera;
	//by zhouhao
	CConfigNetServer m_netServerDlg;
	
	CSysSettingUserManager *m_userManager;

	CAlarmVideoAnalyse *m_alarmVideoAnalyse;
	CSysInfoVersion m_InfoVersion;

	CChannelNameSet m_channelNS;
    CConfigVehicle m_vehicleDlg;
	CConfigDigitalChannel* m_cfgDigitalChannel;
    CToolManagerHardDisk m_toolManagerHardDiskDlg;
	
	CSnapStorageDlg  m_SnapStorageDlg;
	void GetSnapStorageDlg();
	void SetSnapStorageDlg(SDK_SnapshotConfigAll *pSnapCfg);
	void GetAlarmVideoAnalyseInfo();
	void GetUserInfo();
	void GetAlarmException();
	void SetAlarmException(SDK_VIDEOLOSSCONFIG *pStorageNE,SDK_VIDEOLOSSCONFIG *pStorageFL,SDK_VIDEOLOSSCONFIG *pNetipCfg,SDK_VIDEOLOSSCONFIG *pNetaBort,SDK_StorageLowSpaceConfig *pStorageLSCfg);
	
	void GetChannelNS();
	void setChannelNS(SDK_ChannelNameConfigAll *pChannelName);
	void GetVehicleDlg();
	void setVehicleDlg(SDK_CarStatusExchangeAll *pCarStaExg,SDK_CarDelayTimeConfig *pCarDelayTimeCfg);
	void setVehicleDlg(SDK_CarStatusExchangeAll *pCarStaExg);
	void GetNetDecorderCfg();
	void GetNetCommon();
	int SetNatInfo(SDK_LocalSdkNetPlatformConfig *pNetInfoCfg);
	void GetNatInfo();
	int SetNatInfo(SDK_NatConfig *pNatInfoCfg);
	BOOL SetNetDecorderCfg(SDK_NetDigitChnConfig *pNetDigitChnConfig,int nDigChannelNum);
	void GetInfoVersion();
	
//	CDigitalChannelDlg m_DigChannelDlg;
	CRemoteChannelDlg m_RemoteChanDlg;

	DEV_ATTRIBUTE   m_DevAttribute;   //Device Attribute
	CComboBox m_typeComboBox;
	CString m_addrStr;
	afx_msg void OnCbnSelchangeComboType();

	byte* m_pBuf;	//记录点阵信息
	int m_nWidth;	//点阵的宽度
	int m_nHeigth;	//点阵的高度
	bool m_typeIPC;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_)
