
// ClientDemo5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ClientDemo5Dlg.h"
#include "ConfigDigitalChannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
long loginID;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg dialog

CClientDemo5Dlg::CClientDemo5Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CClientDemo5Dlg::IDD, pParent)
, m_addrStr(_T(""))
{
	//{{AFX_DATA_INIT(CClientDemo5Dlg)
	m_nPort = 34567;
	m_strUserName = _T("admin");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_LoginID = 0;
	m_dlgDeviceType = NULL;
	m_userManager=NULL;
	m_alarmVideoAnalyse=NULL;
	AlarmCfg_RB=FALSE;
	AlarmExp_RB=FALSE;
	AlarmCfg_SC=FALSE;
	AlarmExp_SC=FALSE;
	
 	m_cfgDigitalChannel = new CConfigDigitalChannel;
}

CClientDemo5Dlg::~CClientDemo5Dlg()
{
    delete m_cfgDigitalChannel;

}
void CClientDemo5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemo5Dlg)
	DDX_Control(pDX, IDC_TAB_MAIN, m_ctlMainTab);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_DVRPWD, m_strPwd);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_TYPE, m_typeComboBox);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_addrStr);
}

BEGIN_MESSAGE_MAP(CClientDemo5Dlg, CDialog)
//{{AFX_MSG_MAP(CClientDemo5Dlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
ON_WM_DESTROY()
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, OnSelchangeTabMain)
ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	//}}AFX_MSG_MAP
ON_CBN_SELCHANGE(IDC_COMBO_TYPE, CClientDemo5Dlg::OnCbnSelchangeComboType)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg message handlers

BOOL CClientDemo5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//Device default IP
	
	//Initialize TabControl control
	InitTabControl();
	//Initialize SDK
	InitNetSDK();
	
	m_nAlarmOutNum = 0;
	m_nChannelNum = 0;
	m_nAlarmInNum = 0;
	m_nbyChanNum=0;
	m_niDigChannel = 0;
	m_typeComboBox.AddString("TCP");
	m_typeComboBox.AddString("UDP");
	
	//m_typeComboBox.AddString("DAS");
	m_typeComboBox.SetCurSel(0);
	//	SetTimer(1, 10000, NULL);
	m_addrStr="";
	m_alarmVideoAnalyse->dlgVideoOscRuleSet.dlgAvdRuleArea.m_lDlg=(long)this;
	m_alarmVideoAnalyse->dlgVideoAnalyseSet.dlgRuleArea.m_lDlg=(long)this;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemo5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDemo5Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDemo5Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
BOOL CClientDemo5Dlg::AddPage(CString strTitle, CDialog* dlgPage, UINT uID)
{
	if(NULL == dlgPage)
	{
		return FALSE;
	}
	
	DeletePage();
	
	m_dlgDeviceType = dlgPage;
	
	CRect childRect;
	m_ctlMainTab.GetClientRect(childRect);
	childRect.top += 20;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 4;
	
	m_dlgDeviceType->Create(uID, &m_ctlMainTab);
	m_dlgDeviceType->MoveWindow(childRect);
	m_ctlMainTab.InsertItem(8, strTitle);
	
	return TRUE;
}
BOOL CClientDemo5Dlg::DeletePage()
{
	if(NULL != m_dlgDeviceType)
	{
		int nSel = m_ctlMainTab.GetCurSel();
		m_dlgDeviceType->ShowWindow(FALSE);
		m_dlgDeviceType->CloseWindow();
		m_ctlMainTab.DeleteItem(8);
		delete m_dlgDeviceType;
		m_dlgDeviceType = NULL;
		
		if(nSel == 9)
		{
			m_ctlMainTab.SetCurSel(8);
			DoTab(8);
		}
		else
		{
			DoTab(nSel);
		}
		Invalidate(TRUE);
		return TRUE;
	}
	
	return FALSE;
}

bool WINAPI DevicCallBack(long lLoginID, char *pBuf,unsigned long dwBufLen, long dwUser)
{
	H264_DVR_ACTIVEREG_INFO *info=(H264_DVR_ACTIVEREG_INFO *)pBuf;
	CClientDemo5Dlg *dlg=(CClientDemo5Dlg *)dwUser;
	
	
	dlg->m_LoginID = lLoginID;
	memcpy(&dlg->m_DevAttribute.deviveInfo,&info->deviceInfo,sizeof(info->deviceInfo));
	
	dlg->GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);	
	
		dlg->m_nChannelNum = info->deviceInfo.byChanNum+info->deviceInfo.iDigChannel;
		dlg->m_nAlarmInNum = info->deviceInfo.byAlarmInPortNum;
		dlg->m_nAlarmOutNum = info->deviceInfo.byAlarmOutPortNum;
		dlg->m_nbyChanNum =info->deviceInfo.byChanNum;
		dlg->m_niDigChannel = info->deviceInfo.iDigChannel;

		dlg->GetDeviceConfigInfo();
	return 1;
}
//Register user to device 
#define TYPEMAP(a,b) case a:return (b)

void CClientDemo5Dlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int err=0;	//Stroage the returned error value
		char *pchDVRIP;
		CString strDvrIP=m_addrStr;
		pchDVRIP = (LPSTR)(LPCSTR)strDvrIP;
		WORD wDVRPort=(WORD)m_nPort;
		char *pchUserName=(LPSTR)(LPCSTR)m_strUserName;
		char *pchPassword=(LPSTR)(LPCSTR)m_strPwd;
		//Device informaiton
		H264_DVR_DEVICEINFO deviceInfo;
		//Call log in interface
		//设置连接次数
		int type=m_typeComboBox.GetCurSel();
		long lRet=0;
	
		
			H264_DVR_SetConnectTime(3000, 1);//设置尝试连接1次，等待时间3s
			lRet= H264_DVR_Login(pchDVRIP,wDVRPort,pchUserName,pchPassword,&deviceInfo,&err,(SocketStyle)type);
		
		if(lRet>0)
		{
			m_LoginID = lRet;
			loginID=m_LoginID;
			strcpy(m_alarmVideoAnalyse->dlgVideoOscRuleSet.dlgAvdRuleArea.deviceInfo.szDevIP,pchDVRIP);
			m_alarmVideoAnalyse->dlgVideoOscRuleSet.dlgAvdRuleArea.deviceInfo.dwPort=wDVRPort;
			strcpy(m_alarmVideoAnalyse->dlgVideoOscRuleSet.dlgAvdRuleArea.deviceInfo.szUserName,pchUserName);
			strcpy(m_alarmVideoAnalyse->dlgVideoOscRuleSet.dlgAvdRuleArea.deviceInfo.szPassWord,pchPassword);
			
			strcpy(m_alarmVideoAnalyse->dlgVideoAnalyseSet.dlgRuleArea.deviceInfo.szDevIP,pchDVRIP);
			m_alarmVideoAnalyse->dlgVideoAnalyseSet.dlgRuleArea.deviceInfo.dwPort=wDVRPort;
			strcpy(m_alarmVideoAnalyse->dlgVideoAnalyseSet.dlgRuleArea.deviceInfo.szUserName,pchUserName);
			strcpy(m_alarmVideoAnalyse->dlgVideoAnalyseSet.dlgRuleArea.deviceInfo.szPassWord,pchPassword);

			memcpy(&m_DevAttribute.deviveInfo,&deviceInfo,sizeof(deviceInfo));
			
			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(TRUE);
			
			m_nChannelNum = deviceInfo.byChanNum+deviceInfo.iDigChannel;
			m_nAlarmInNum = deviceInfo.byAlarmInPortNum;
			m_nAlarmOutNum = deviceInfo.byAlarmOutPortNum;
			m_nbyChanNum =deviceInfo.byChanNum;
			m_niDigChannel = deviceInfo.iDigChannel;
			if(deviceInfo.deviceTye == SDK_DEVICE_TYPE_IPC)
			{
				m_typeIPC = TRUE;
			}
			//by zhouhao
			int nSelect = m_ctlMainTab.GetCurSel();
			if(nSelect>=0)
			{
				DoTab(nSelect);
			}
			//Device property 
//		    GetDeviceConfigInfo();	
//			//Video channel property 
//			GetChannelConfigInfo();
//			//COM property 
//			GetCommConfigInfo();
//			//Record configuration 
//			GetRecordConfigInfo();
//			
//			//Network configuration 
//			GetNetWorkConfigInfo();
//			
//			//Alarm property 
//			GetAlarmConfigInfo();
//			
//			//PTZ
//			GetPTZConfigInfo();
		}
		else
		{
			m_LoginID = 0;
			//Display log in failure reason 
			ShowLoginErrorReason(err);
		}
	}
}

//Logout device user 
void CClientDemo5Dlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	DeletePage();
	BOOL bRet = H264_DVR_Logout(m_LoginID);
	//Clear handle as o after logout 
	if(bRet)
	{
		m_LoginID=0;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
		//Device property 
		m_serverDlg.CleanAll();
		//Video channel property 
		m_channelDlg.CleanAll();
		//COM property 
		m_commDlg.CleanAll();
		//Record configuration 
		m_recordDlg.CleanAll();
		//Network configuration 
		m_networkDlg.CleanAll();
		//Alarm property 
		m_alarmDlg.CleanAll();
		//Ptz
		m_Ptz.CleanAll();
		//Camera Parameters
		m_SysCamera.CleanAll();
		m_channelNS.CleanAll();
		m_vehicleDlg.CleanAll();
		m_netServerDlg.CleanAll();
		//by zhouhao
		//user manage
		m_userManager->ClearAll();
		//log
		m_logInfoDlg.ClearAll();
		//digital
		m_cfgDigitalChannel->ClearAll();
        m_outputDlg.CleanAll();
	}
}

//message callback function
bool __stdcall MessCallBack(long lLoginID, char *pBuf,
							unsigned long dwBufLen, long dwUser)
{
	return TRUE;
}

//device disconnect callback
void __stdcall DisConnectBackCallFunc(LONG lLoginID, char *pchDVRIP, 
									  LONG nDVRPort, DWORD dwUser)
{
	CClientDemo5Dlg* pThis = (CClientDemo5Dlg*)dwUser;
	if (pThis == NULL)
	{
		ASSERT( FALSE );
		return ;
	}
}

//Initialize SDK
BOOL CClientDemo5Dlg::InitNetSDK()
{
	//initialize
	BOOL bResult = H264_DVR_Init((fDisConnect)DisConnectBackCallFunc,(DWORD)this);
	
	//he messages received in SDK from DVR which need to upload， such as alarm information，diary information，may do through callback function
	H264_DVR_SetDVRMessCallBack(MessCallBack,(DWORD)this);
	H264_DVR_SetConnectTime(5000, 3);
	
	return bResult;
}

void CClientDemo5Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	// Logout 
	if(0 != m_LoginID)
	{
		DeletePage();
		BOOL bLogout = H264_DVR_Logout(m_LoginID);
	}
	//Clear SDK, release resources  
	if(m_userManager)
	{
		delete m_userManager;
	}
	ExitSDk();
}


//Display log in failure reason 
void CClientDemo5Dlg::ShowLoginErrorReason(int nError)
{
	int nErr = H264_DVR_GetLastError();  
	string strErr;
	switch (nError)
	{
	case H264_DVR_PASSWORD_NOT_VALID:
			strErr = _CS("Error.PwdErr");
		break;
	case H264_DVR_NOPOWER:
			strErr = _CS("Error.NoPower");
		break;
	case H264_DVR_LOGIN_USER_NOEXIST:
			strErr = _CS("Error.UserNotExisted");
		break;
	case H264_DVR_USER_LOCKED:
			strErr = _CS("Login.Locked");
		break;
	case H264_DVR_USER_IN_BLACKLIST:
		strErr = _CS("Error.InBlackList");
		break;
	case H264_DVR_USER_HAS_USED:
		strErr = _CS("Error.HasLogined");
		break;
	case H264_DVR_CONNECT_DEVICE_ERROR:
		strErr = _CS("Error.NotFound");
		break;
	default:
		{
			char ch[10];
			itoa(nErr, ch, 10);
			strErr = _CS("Log.Error") + ch;
		}
	
		break;
	}
	MessageBox(strErr.c_str());
	
}

//Initialize TabControl control
void CClientDemo5Dlg::InitTabControl()
{
	CRect childRect;
	m_ctlMainTab.GetClientRect(childRect);
	childRect.top += 20;	
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 4;
	
	//Create non-mode dialogue box. Specified tag is non-mode dialogue box father window.
	m_serverDlg.Create(IDD_CONFIG_SERVER, &m_ctlMainTab);
	m_serverDlg.MoveWindow(childRect);
	
	m_channelDlg.Create(IDD_CONFIG_CHANNEL, &m_ctlMainTab);
	m_channelDlg.MoveWindow(childRect);
	m_commDlg.Create(IDD_CONFIG_COMM, &m_ctlMainTab);
	m_commDlg.MoveWindow(childRect);
	m_alarmDlg.Create(IDD_CONFIG_ALARM, &m_ctlMainTab);
	m_alarmDlg.MoveWindow(childRect);

	m_alarmDlg.m_TabMotion.m_pMainDlg = (long)this;
	
	m_recordDlg.Create(IDD_CONFIG_RECORD, &m_ctlMainTab);
	m_recordDlg.MoveWindow(childRect);
	m_networkDlg.Create(IDD_CONFIG_NETWORK, &m_ctlMainTab);
	m_networkDlg.MoveWindow(childRect);
	m_Ptz.Create(IDD_DLG_SYS_PTZ,&m_ctlMainTab);
	m_Ptz.MoveWindow(childRect);
	m_SysCamera.Create(IDD_DLG_CAMERAPARA, &m_ctlMainTab);
	m_SysCamera.MoveWindow(childRect);
	m_userManager=new  CSysSettingUserManager();
 	m_userManager->Create(IDD_DLG_USER_MANAGER, &m_ctlMainTab);
 	m_userManager->MoveWindow(childRect);
	
	m_channelNS.Create(IDD_CHANNELNAME,&m_ctlMainTab);
	m_channelNS.MoveWindow(childRect);
	m_vehicleDlg.Create(IDD_DLG_VEHICLE,&m_ctlMainTab);
	m_vehicleDlg.MoveWindow(childRect);
	
//	m_DigChannelDlg.Create(IDD_DLG_DIGITALCHANNEL, &m_ctlMainTab);
//	m_DigChannelDlg.MoveWindow(childRect);
	m_cfgDigitalChannel->Create(IDD_CONFIG_DIGITALCHANNEL,&m_ctlMainTab);
	m_cfgDigitalChannel->MoveWindow(childRect);

	m_outputDlg.Create(IDD_CONFIG_OUTPUT,&m_ctlMainTab);
	m_outputDlg.MoveWindow(childRect);
    
	m_logInfoDlg.Create(IDD_DLG_LOGINFO,&m_ctlMainTab);
    m_logInfoDlg.MoveWindow(childRect);

	m_netServerDlg.Create(IDD_CONFIG_NETSERVER,&m_ctlMainTab);
	m_netServerDlg.MoveWindow(childRect);
   
	m_toolManagerHardDiskDlg.Create(IDD_DLG_TOOL_HARDDISK,&m_ctlMainTab);
	m_toolManagerHardDiskDlg.MoveWindow(childRect);
	m_alarmVideoAnalyse = new CAlarmVideoAnalyse();
	m_alarmVideoAnalyse->Create(IDD_DLG_ALARM_VIDEOANALYSE,&m_ctlMainTab);
	m_alarmVideoAnalyse->MoveWindow(childRect);

	m_InfoVersion.Create(IDD_DLG_SYSINFO_VERSION,&m_ctlMainTab);
	m_InfoVersion.MoveWindow(childRect);

	m_SnapStorageDlg.Create(IDD_DLG_SNAPSHOT,&m_ctlMainTab);
	m_SnapStorageDlg.MoveWindow(childRect);
	m_ctlMainTab.InsertItem(0, _CS("Title.GeneralConfig"));
	m_ctlMainTab.InsertItem(1, _CS("Title.EncodeConfig"));
	m_ctlMainTab.InsertItem(2, _CS("Title.CommConfig"));
	m_ctlMainTab.InsertItem(3, _CS("Title.RecordConfig"));
	m_ctlMainTab.InsertItem(4, _CS("Title.NetCommonConfig"));
	m_ctlMainTab.InsertItem(5, _CS("Title.AlarmConfig"));
	m_ctlMainTab.InsertItem(6,_CS("Title.PtzConfig"));
	m_ctlMainTab.InsertItem(7, _CS("Title.CameraPara"));
	m_ctlMainTab.InsertItem(8, _CS("Title.UserManager"));
	m_ctlMainTab.InsertItem(9,_CS("Title.ChannelName"));
	m_ctlMainTab.InsertItem(10,_CS("Title.CarFunc"));
    m_ctlMainTab.InsertItem(11,_CS("Title.DigitalChannel"));
	m_ctlMainTab.InsertItem(12,_CS("Title.DisplayConfig"));
	m_ctlMainTab.InsertItem(13,_CS("Title.LogInfo"));
	//by zhouhao
	m_ctlMainTab.InsertItem(14,_CS("Title.NetService"));
	m_ctlMainTab.InsertItem(15,_CS("Title.HDDManager"));
	m_ctlMainTab.InsertItem(16,_CS("Title.VideoAnalyse"));
	m_ctlMainTab.InsertItem(17,_CS("Title.Version"));
	m_ctlMainTab.InsertItem(18,_CS("Title.SnapShot"));
	m_ctlMainTab.SetCurSel(0);
	DoTab(0);
}
void CClientDemo5Dlg::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}

void CClientDemo5Dlg::DoTab(int nTab)
{
	//Check nTab value is within the threshold
	if(nTab>18)
	{
		nTab=18;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[19];
	bTab[0]=bTab[1]=bTab[2]=bTab[3]=bTab[4]=bTab[5]=bTab[6]=bTab[7]=bTab[8]=bTab[9]=bTab[10]=bTab[11]=bTab[12]=bTab[13]=bTab[14]=bTab[15]=bTab[16]=bTab[17]=bTab[18]=FALSE;
	bTab[nTab]=TRUE;
	if ( m_LoginID > 0 )
	{
		if ( nTab == 0)
		{
			GetDeviceConfigInfo();
		}else if ( nTab == 1)
		{
			GetChannelConfigInfo();
		}else if ( nTab == 2)
		{
			GetCommConfigInfo();
		}else if ( nTab == 3)
		{
			GetRecordConfigInfo();
		}else if ( nTab == 4)
		{
			GetNetWorkConfigInfo();
		}else if ( nTab == 5)
		{
			GetAlarmConfigInfo();
			GetAlarmException();
		}else if ( nTab == 6)
		{
			GetPTZConfigInfo();
		}else if ( nTab == 7 )
		{
			//摄象机参数
			GetCameraPara();
		}
		else if ( nTab == 8 )
		{
			//用户信息
			GetUserInfo();
		}
		else if (nTab ==9)
		{
			GetChannelNS();
			//
		}
		else if (nTab == 10)
		{
			GetVehicleDlg();
			//
		}
		else if (nTab == 11)
		{
			GetNetDecorderCfg();
		}
		else if (nTab == 12)
		{
	    	GetOutputConfigInfo();
		}
		else if (nTab == 13)
		{
           GetLogInfo();
		}
		else if (nTab == 14)
		{
			GetNetServerConfigInfo();
		}
		else if (nTab == 15)
		{
             GetHardDiskInfo();
		}
		else if (nTab == 16 )
		{
			GetAlarmVideoAnalyseInfo();
		}
		else if (nTab == 17)
		{
			//CSysInfoVersion
			GetInfoVersion();
		}
		else if (nTab == 18)
		{
			GetSnapStorageDlg();
		}
	}
	
	//Display or hide dialogue box 
	
	SetDlgState(&m_serverDlg,bTab[0]);
	SetDlgState(&m_channelDlg,bTab[1]);
	SetDlgState(&m_commDlg,bTab[2]);
	SetDlgState(&m_recordDlg,bTab[3]);
	SetDlgState(&m_networkDlg,bTab[4]);
	SetDlgState(&m_alarmDlg,bTab[5]);
	SetDlgState(&m_Ptz,bTab[6]);
	SetDlgState(&m_SysCamera, bTab[7]);
	SetDlgState(m_userManager, bTab[8]);
	SetDlgState(&m_channelNS,bTab[9]);

	SetDlgState(&m_vehicleDlg,bTab[10]);
	SetDlgState(m_cfgDigitalChannel,bTab[11]);

	SetDlgState(&m_outputDlg,bTab[12]);
    SetDlgState(&m_logInfoDlg,bTab[13]);
	SetDlgState(&m_netServerDlg,bTab[14]);
    SetDlgState(&m_toolManagerHardDiskDlg,bTab[15]);
	SetDlgState(m_alarmVideoAnalyse,bTab[16]);
	SetDlgState(&m_InfoVersion,bTab[17]);
	SetDlgState(&m_SnapStorageDlg,bTab[18]);
	if(NULL != m_dlgDeviceType)
	{
		SetDlgState(m_dlgDeviceType,bTab[16]);
	}
}


void CClientDemo5Dlg::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_ctlMainTab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

BOOL g_bSignal = TRUE;
void CClientDemo5Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (g_bSignal)
	{
		g_bSignal = FALSE;
	}
	else
	{
		g_bSignal = TRUE;
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CClientDemo5Dlg::ExitSDk()
{
	H264_DVR_Cleanup();
	
	return true;
}

void CClientDemo5Dlg::GetDeviceConfigInfo()
{
	if (0 != m_LoginID)
	{

		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NORMAL NormalConfig = {0};
		SDK_MultiLangFunction m_langfunc={0};
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL ,0, 
			(char *)&NormalConfig ,sizeof(SDK_CONFIG_NORMAL), &dwRetLen,nWaitTime);
		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			//memcpy(&m_DevAttribute.NormalConfig, &NormalConfig,sizeof(SDK_CONFIG_NORMAL));
			//nRet = m_getCallback(E_SDK_CONFIG_ABILITY_LANG, 0, (char *)&m_langfunc, sizeof(m_langfunc), m_dwUser, NULL);
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_LANG,0,(char *)&m_langfunc,
				sizeof(SDK_MultiLangFunction),&dwRetLen,nWaitTime);
			if(bSuccess &&dwRetLen == sizeof(SDK_MultiLangFunction))
			{
				m_DevAttribute.NormalConfig = NormalConfig;
				m_serverDlg.InitDlgInfo(&m_DevAttribute,&m_langfunc);
			}

		}
	}else
	{
		MessageBox(_CS("Login.LoginFail"));
	}
}

void CClientDemo5Dlg::SetDeviceConfigInfo(DEV_ATTRIBUTE *pDevAttribute)
{
	DWORD dwRetLen = 0;
	int nWaitTime = 10000;
	if (0 != m_LoginID && pDevAttribute != NULL)
	{
		SDK_CONFIG_NORMAL NormalConfig = {0};
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL ,0, 
			(char *)&NormalConfig ,sizeof(SDK_CONFIG_NORMAL), &dwRetLen,nWaitTime);
		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			NormalConfig.iLocalNo = pDevAttribute->NormalConfig.iLocalNo;
			NormalConfig.iOverWrite = pDevAttribute->NormalConfig.iOverWrite;
			NormalConfig.iAutoLogout = pDevAttribute->NormalConfig.iAutoLogout;
			NormalConfig.iVideoFormat = pDevAttribute->NormalConfig.iVideoFormat;
			NormalConfig.iDateFormat = pDevAttribute->NormalConfig.iDateFormat;
			NormalConfig.iDateSeparator = pDevAttribute->NormalConfig.iDateSeparator;
			NormalConfig.iTimeFormat = pDevAttribute->NormalConfig.iTimeFormat;
			strcpy(NormalConfig.sMachineName,pDevAttribute->NormalConfig.sMachineName);
			NormalConfig.iLanguage = pDevAttribute->NormalConfig.iLanguage;
			
			BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNORMAL,0,(char *)&NormalConfig,sizeof(SDK_CONFIG_NORMAL),nWaitTime);
			if ( bSuccess == H264_DVR_OPT_REBOOT )
			{
				if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
				{
					bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
					if (bSuccess)
					{
						OnBtnLogout();
					}else
					{
						MessageBox(_CS("Error.RebootFail"));
					}
				}
			}else if ( bSuccess > 0)
			{
				MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
			}else{
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
			}
		}
	}
}

void CClientDemo5Dlg::GetChannelConfigInfo()
{
	if (0 !=m_LoginID )
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NORMAL NormalConfig = {0};
		SDK_EncodeStaticParamAll EncodeStatic = {0};
		//编码
		BOOL nStaticCparam = false;
		BOOL  bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_ENCODE_STATICPARAM ,-1, 
					(char *)&EncodeStatic ,sizeof(SDK_EncodeStaticParamAll), &dwRetLen,nWaitTime);

		if (bSuccess && sizeof(SDK_EncodeStaticParamAll) == dwRetLen )
		{
			nStaticCparam = true;
		}

		 bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL ,0, 
			(char *)&NormalConfig ,sizeof(SDK_CONFIG_NORMAL), &dwRetLen,nWaitTime);
		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			SDK_SystemFunction SysFunc;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,0,
				(char *)&SysFunc,sizeof(SDK_SystemFunction),&dwRetLen,nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_SystemFunction))
			{
				SDK_EncodeConfigAll_SIMPLIIFY CfgEncode = {0};
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, -1,
					(char *)&CfgEncode,sizeof(SDK_EncodeConfigAll_SIMPLIIFY),&dwRetLen,nWaitTime);
				if (bSuccess && dwRetLen == sizeof(SDK_EncodeConfigAll_SIMPLIIFY))
				{
					CONFIG_EncodeAbility EncodeAbility = {0};
					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILTY_ENCODE,-1,
						(char *)&EncodeAbility,sizeof(CONFIG_EncodeAbility),&dwRetLen,nWaitTime);
					if (bSuccess && dwRetLen == sizeof(CONFIG_EncodeAbility))
					{
						SDK_CombineEncodeConfigAll CombineEncodeCfg;
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODE,-1,
							(char*)&CombineEncodeCfg,sizeof(SDK_CombineEncodeConfigAll),&dwRetLen,nWaitTime);
						if (bSuccess && dwRetLen == sizeof(SDK_CombineEncodeConfigAll))
						{
							SDK_CombEncodeModeAll CmbEncodeMode;
							bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODEMODE,-1,
								(char *)&CmbEncodeMode,sizeof(SDK_CombEncodeModeAll),&dwRetLen,nWaitTime);
							if (bSuccess && dwRetLen == sizeof(SDK_CombEncodeModeAll))
							{
								if (nStaticCparam)
								{
									m_channelDlg.InitDlgInfo(m_nChannelNum,&CfgEncode,&NormalConfig,&EncodeAbility,&CombineEncodeCfg,&SysFunc,&m_DevAttribute,&CmbEncodeMode,&EncodeStatic);
								}
								else
								{
									m_channelDlg.InitDlgInfo(m_nChannelNum,&CfgEncode,&NormalConfig,&EncodeAbility,&CombineEncodeCfg,&SysFunc,&m_DevAttribute,&CmbEncodeMode,NULL);
								}
								
							}
						}
					}
				}
			}
		}
	}
}

void CClientDemo5Dlg::SetChannelConfigInfo( SDK_EncodeConfigAll_SIMPLIIFY *pEncodeCfg,
										   SDK_CombineEncodeConfigAll *pCmbEncodeCfg,
										   SDK_CombEncodeModeAll *pCmbEncodeMode,
										   SDK_EncodeStaticParamAll *pEncodeStatic)
{
	DWORD dwRetLen = 0;
	int nWaitTime = 10000;
	BOOL bReboot = FALSE;
	if (0 != m_LoginID)
	{
		BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SYSENCODE_SIMPLIIFY,-1,
			(char *)pEncodeCfg,sizeof(SDK_EncodeConfigAll_SIMPLIIFY),nWaitTime);
		if(bSuccess)
		{
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODE,-1,
				(char *)pCmbEncodeCfg,sizeof(SDK_CombineEncodeConfigAll),nWaitTime);
			if (bSuccess)
			{
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
				bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODEMODE,-1,
					(char *)pCmbEncodeMode,sizeof(SDK_CombEncodeModeAll),nWaitTime);
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
				BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID, E_SDK_CONFIG_ENCODE_STATICPARAM ,-1, 
					(char *)pEncodeStatic ,sizeof(SDK_EncodeStaticParamAll),nWaitTime);
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
 				}
				if ( bReboot == TRUE)
				{
					if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
					{
						bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
						if (bSuccess)
						{
							OnBtnLogout();
						}else
						{
							MessageBox(_CS("Error.RebootFail"));
						}
					}
				}
				if ( bSuccess > 0)
				{
					MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
				}
				else if ( bSuccess < 0 && bSuccess != H264_DVR_OPT_REBOOT )
				{
					MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
				}
			}
		}
	}
}

void CClientDemo5Dlg::GetCommConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CommConfigAll CfgComm;
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMM,-1,
			(char *)&CfgComm,sizeof(SDK_CommConfigAll),&dwRetLen,nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_CommConfigAll))
		{
			SDK_COMMFUNC CommFunc;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_COMFIG_ABILITY_COMMPRO,0,
				(char *)&CommFunc,sizeof(SDK_COMMFUNC),&dwRetLen,nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_COMMFUNC))
			{
				m_commDlg.InitDlgInfo(&CfgComm,&CommFunc);
			}
		}
	}
}

void CClientDemo5Dlg::SetCommConfigInfo(SDK_CommConfigAll *pCommCfg)
{
	int nWaitTime = 10000;
	if( 0 != m_LoginID && pCommCfg != NULL )
	{
		BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_COMM,-1,
			(char *)pCommCfg,sizeof(SDK_CommConfigAll),nWaitTime);
		if (bSuccess == H264_DVR_OPT_REBOOT)
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( bSuccess > 0 )
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}
		else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}

void CClientDemo5Dlg::GetRecordConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_RECORDCONFIG_ALL *RecordCfgAll = new SDK_RECORDCONFIG_ALL;
		if(!RecordCfgAll)
			return;
		int i =0;
		for(;i<m_nChannelNum;i++)
		{
			BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_RECORD,i,
				(char *)&(RecordCfgAll->vRecordConfigAll[i]),sizeof(SDK_RECORDCONFIG),&dwRetLen,nWaitTime);
			if (dwRetLen !=sizeof(SDK_RECORDCONFIG) && !bSuccess)break;
		}
		if (i == m_nChannelNum)
		{
			m_recordDlg.InitDlgInfo(RecordCfgAll,m_nChannelNum);
		}
	//	delete RecordCfgAll;
	//	RecordCfgAll= NULL;
	}
}

void CClientDemo5Dlg::SetRecordConfigInfo(SDK_RECORDCONFIG_ALL *pRecordInfo)
{
	if (0 != m_LoginID && pRecordInfo != NULL)
	{
		int nWaitTime = 10000;
		int i = 0;
		BOOL bSuccess = FALSE;
		BOOL bReboot = FALSE;
		for (; i<m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_RECORD,i,
				(char *)pRecordInfo,sizeof(SDK_RECORDCONFIG),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot =TRUE;
			}
		}
		if (i == m_nChannelNum && bReboot == TRUE)
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( i == m_nChannelNum && bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}

void CClientDemo5Dlg::GetNetWorkConfigInfo()
{
	if ( 0 !=m_LoginID)
	{
		DWORD dwRetLen = 0;
 		int nWaitTime = 10000;
		SDK_CONFIG_NET_COMMON NetWorkCfg;  //普通网络设置

		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNET,0,
			(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),&dwRetLen,nWaitTime);
		long longtest=sizeof(SDK_CONFIG_NET_COMMON);
		if (bSuccess && dwRetLen == sizeof(SDK_CONFIG_NET_COMMON))
		{
			SDK_NetDNSConfig NetDNSCfg;   //DNS设置
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DNS,0,
				(char *)&NetDNSCfg,sizeof(SDK_NetDNSConfig),&dwRetLen,nWaitTime);
			
			if (bSuccess && dwRetLen == sizeof(SDK_NetDNSConfig))
			{
				SDK_NetDHCPConfigAll NetDHPCfg;   //所有的DHCP的设置
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DHCP,0,
					(char *)&NetDHPCfg,sizeof(SDK_NetDHCPConfigAll),&dwRetLen,nWaitTime);
				if (bSuccess && dwRetLen == sizeof(SDK_NetDHCPConfigAll))
				{
					SDK_NetOrderConfig NetOrder;  //网络优先级
					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_ORDER,0,
						(char *)&NetOrder,sizeof(SDK_NetOrderConfig),&dwRetLen,nWaitTime);
					if (bSuccess)//&& dwRetLen == sizeof(SDK_NetOrderConfig)
					{
						SDK_NetOrderFunction NetOrderFunc;   //网络优先级能力
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_NETORDER,0,
							(char *)&NetOrderFunc,sizeof(SDK_NetOrderFunction),&dwRetLen,nWaitTime);
						if (bSuccess)
						{
							m_networkDlg.InitDlgInfo(&NetWorkCfg,&NetDNSCfg,&NetDHPCfg,&NetOrder,&NetOrderFunc);
						}
						
					}
					
				}
			}
		}
	}
}

void CClientDemo5Dlg::SetNetWorkConfigInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP)
{
	if (0 != m_LoginID && pNetCommon != NULL && pNetDNS != NULL && pNetDHCP != NULL)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NET_COMMON NetWorkCfg;
		BOOL bReboot = FALSE;
		int nOldHttp = 0,nOldTCP = 0;
		char cOldIP[100]={0},cOldGate[100]={0},cOldSub[100]={0},cNewIP[100]={0},cNewGate[100]={0},cNewSub[100]={0};
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNET,0,
			(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),&dwRetLen,nWaitTime);
		if (bSuccess && dwRetLen == sizeof (SDK_CONFIG_NET_COMMON))
		{
			nOldHttp = NetWorkCfg.HttpPort;
			nOldTCP = NetWorkCfg.TCPPort;
			sprintf(cOldIP,"%d.%d.%d.%d",NetWorkCfg.HostIP.c[0],NetWorkCfg.HostIP.c[1],NetWorkCfg.HostIP.c[2]
				,NetWorkCfg.HostIP.c[3]);
			sprintf(cOldGate,"%d.%d.%d.%d",NetWorkCfg.Gateway.c[0],NetWorkCfg.Gateway.c[1],NetWorkCfg.Gateway.c[2]
				,NetWorkCfg.Gateway.c[3]);
			sprintf(cOldSub,"%d.%d.%d.%d",NetWorkCfg.Submask.c[0],NetWorkCfg.Submask.c[1],NetWorkCfg.Submask.c[2]
				,NetWorkCfg.Submask.c[3]);

			memcpy(&NetWorkCfg.HostIP,&pNetCommon->HostIP,sizeof(CONFIG_IPAddress));
			memcpy(&NetWorkCfg.Gateway,&pNetCommon->Gateway,sizeof(CONFIG_IPAddress));
			memcpy(&NetWorkCfg.Submask,&pNetCommon->Submask,sizeof(CONFIG_IPAddress));
			NetWorkCfg.TCPPort = pNetCommon->TCPPort;
			NetWorkCfg.HttpPort = pNetCommon->HttpPort;
			strcpy(NetWorkCfg.sMac,pNetCommon->sMac);
			NetWorkCfg.bUseHSDownLoad = pNetCommon->bUseHSDownLoad;
			NetWorkCfg.TransferPlan = pNetCommon->TransferPlan;

			sprintf(cNewIP,"%d.%d.%d.%d",NetWorkCfg.HostIP.c[0],NetWorkCfg.HostIP.c[1],NetWorkCfg.HostIP.c[2]
				,NetWorkCfg.HostIP.c[3]);
			sprintf(cNewGate,"%d.%d.%d.%d",NetWorkCfg.Gateway.c[0],NetWorkCfg.Gateway.c[1],NetWorkCfg.Gateway.c[2]
				,NetWorkCfg.Gateway.c[3]);
			sprintf(cNewSub,"%d.%d.%d.%d",NetWorkCfg.Submask.c[0],NetWorkCfg.Submask.c[1],NetWorkCfg.Submask.c[2]
				,NetWorkCfg.Submask.c[3]);
		
			//DHCP
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DHCP,0,
				(char *)pNetDHCP,sizeof(SDK_NetDHCPConfigAll),nWaitTime);
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}else if (bSuccess<0)
			{
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
				return;
			}
					
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DNS,0,
					(char *)pNetDNS,sizeof(SDK_NetDNSConfig),nWaitTime);
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}else if (bSuccess<0)
			{
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
				return;
			}
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNET,0,
				(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),nWaitTime);
			if (bSuccess)
			{	
				
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
				if ( bReboot == TRUE )
				{
					if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
					{
						bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
						if (bSuccess)
						{
							OnBtnLogout();
						}else
						{
							MessageBox(_CS("Error.RebootFail"));
						}
					}
				}
				if ( bSuccess > 0)
				{
					MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
				}else if ( bSuccess < 0 && bSuccess != H264_DVR_OPT_REBOOT)
				{
					if (nOldHttp != NetWorkCfg.HttpPort || nOldTCP != NetWorkCfg.TCPPort)
					{
						MessageBox(_CS("ConfigNet.PortModify"), _CS("OneClick.Prompt") );
						return;
					}else if (!strcmp(cOldIP, cNewIP) || !strcmp(cOldGate, cNewGate) || !strcmp(cOldSub,cNewSub))
					{
						MessageBox(_CS("ConfigNet.HaveModify"), _CS("OneClick.Prompt") );
						return;
					}
					MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
				}
				
			
			}
		}

	}
	
}
void CClientDemo5Dlg::SetNetWorkConfigInfo(SDK_NetOrderConfig *pNetOrder)
{
	if (0 != m_LoginID &&pNetOrder!=NULL)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bReboot = FALSE;
		BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_ORDER,0,
			(char *)pNetOrder,sizeof(SDK_NetOrderConfig),nWaitTime);
		if (bSuccess)
		{
			if (bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
			if ( bReboot == TRUE )
			{
				if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
				{
					bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
					if (bSuccess)
					{
						OnBtnLogout();
					}else
					{
						MessageBox(_CS("Error.RebootFail"));
					}
				}
			}
			if ( bSuccess > 0)
			{
				MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
			}else if ( bSuccess < 0 && bSuccess != H264_DVR_OPT_REBOOT)
			{
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
			}
		}
	}
}
void CClientDemo5Dlg::GetAlarmConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		ALARMCONFIGALL *AlarmCfgAll=new ALARMCONFIGALL;
		BOOL bSuccess = FALSE;
		int i = 0;
		for (;i  < m_nChannelNum; i++)
		{
			
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_MOTION,i,
			(char *)&AlarmCfgAll->MotionCfgAll.vMotionDetectAll[i],sizeof(SDK_MOTIONCONFIG),&dwRetLen,nWaitTime);
			if ( (!bSuccess) && (dwRetLen != sizeof(SDK_MOTIONCONFIG)) )break;
		}

		if ( i == m_nChannelNum )
		{
			for ( i = 0;i < m_nChannelNum; i++)
			{
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SHELTER,i,
				(char *)&AlarmCfgAll->DectectCfgAll.vBlindDetectAll[i],sizeof(SDK_BLINDDETECTCONFIG),&dwRetLen,nWaitTime);
				if ( (!bSuccess) && (dwRetLen != sizeof(SDK_BLINDDETECTCONFIG)) )break;
			}

			if ( i== m_nChannelNum )
			{
				for ( i= 0; i < m_nChannelNum; i++)
				{
					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_VIDEO_LOSS,i,
					(char *)&AlarmCfgAll->VideoLossCfgAll.vGenericEventConfig[i],sizeof(SDK_VIDEOLOSSCONFIG),&dwRetLen,nWaitTime);
					if ( (!bSuccess) && (dwRetLen != sizeof(SDK_VIDEOLOSSCONFIG)) )break;
				}

			
				if ( i == m_nChannelNum )
				{
					for ( i = 0; i < m_nAlarmInNum; i++)
					{	
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_IN,i,
						(char *)&AlarmCfgAll->AlarmInCfgAll.vAlarmConfigAll[i],sizeof(SDK_ALARM_INPUTCONFIG),&dwRetLen,nWaitTime);
						if ( (!bSuccess) && (dwRetLen != sizeof(SDK_ALARM_INPUTCONFIG)) )break;
					}
				
					if ( i== m_nAlarmInNum )
					{
						SDK_MotionDetectFunction MotionDectFuc;
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_MOTION_FUNC,0,
							(char *)&MotionDectFuc,sizeof(SDK_MotionDetectFunction),&dwRetLen,nWaitTime);
						if (bSuccess && dwRetLen == sizeof(SDK_MotionDetectFunction))
						{
							SDK_AlarmOutConfigAll AlarmOutputConfig;
							bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_OUT,-1,
							(char *)&AlarmOutputConfig,sizeof(SDK_AlarmOutConfigAll),&dwRetLen,nWaitTime);
				

							if(bSuccess&&dwRetLen == sizeof(SDK_AlarmOutConfigAll))
							{
								SDK_SystemFunction SysFunc;
								bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,0,
									(char *)&SysFunc,sizeof(SDK_SystemFunction),&dwRetLen,nWaitTime);
						
								
								if ( bSuccess && dwRetLen == sizeof(SDK_SystemFunction))
								{
									m_alarmDlg.InitDlgInfo(AlarmCfgAll,m_nChannelNum,m_nAlarmInNum,m_nAlarmOutNum,&MotionDectFuc,&SysFunc, &AlarmOutputConfig);
								}
							}
						}
					}
				}
			}
		}

		delete AlarmCfgAll;
	}
}

void CClientDemo5Dlg::SetAlarmConfigInfo(ALARMCONFIGALL *pAlarmCfgAll)
{
	if ( 0 != m_LoginID && pAlarmCfgAll != NULL)
	{
		int i = 0;
		int nWaitTime = 10000;
// 		BOOL bSuccess =FALSE;
// 		BOOL bReboot = FALSE;
		for (i = 0;i<m_nChannelNum;i++)
		{
			AlarmCfg_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_MOTION,i,
				(char *)&pAlarmCfgAll->MotionCfgAll.vMotionDetectAll[i],sizeof(SDK_MOTIONCONFIG),nWaitTime);
			if (!AlarmCfg_SC)break;
			if ( AlarmCfg_SC == H264_DVR_OPT_REBOOT)
			{
				AlarmCfg_RB = TRUE;
			}
		}
		if (i == m_nChannelNum)
		{
			for (i = 0;i<m_nAlarmInNum;i++)
			{
				
				AlarmCfg_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_IN,i,
					(char *)&pAlarmCfgAll->AlarmInCfgAll.vAlarmConfigAll[i],sizeof(SDK_ALARM_INPUTCONFIG),nWaitTime);
				if (!AlarmCfg_SC)break;
				if ( AlarmCfg_SC == H264_DVR_OPT_REBOOT)
				{
					AlarmCfg_RB = TRUE;
				}
			}
			if ( i == m_nAlarmInNum)
			{
				for (i = 0;i<m_nChannelNum;i++)
				{
					AlarmCfg_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SHELTER,i,
						(char *)&pAlarmCfgAll->DectectCfgAll.vBlindDetectAll[i],sizeof(SDK_BLINDDETECTCONFIG),nWaitTime);
					if (!AlarmCfg_SC)break;
					if ( AlarmCfg_SC == H264_DVR_OPT_REBOOT)
					{
						AlarmCfg_RB = TRUE;
					}
				}
				if (i == m_nChannelNum)
				{
					for (i = 0;i<m_nChannelNum;i++)
					{
						AlarmCfg_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_VIDEO_LOSS,i,
							(char *)&pAlarmCfgAll->VideoLossCfgAll.vGenericEventConfig[i],sizeof(SDK_VIDEOLOSSCONFIG),nWaitTime);
						if (!AlarmCfg_SC)break;
						if ( AlarmCfg_SC == H264_DVR_OPT_REBOOT)
						{
							AlarmCfg_RB = TRUE;
						}
					}

					AlarmCfg_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_OUT,-1,
						(char *)&pAlarmCfgAll->AlarmOutCfgAll,sizeof(SDK_AlarmOutConfigAll),nWaitTime);
					if ( AlarmCfg_SC == H264_DVR_OPT_REBOOT)
					{
						AlarmCfg_RB = TRUE;
					}
				
					
					if ( AlarmCfg_RB == TRUE && AlarmExp_RB==TRUE &&i == m_nChannelNum)
					{
						if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
						{
							
							if (H264_DVR_ControlDVR(m_LoginID,0,nWaitTime))
							{
								OnBtnLogout();
							}else
							{
								MessageBox(_CS("Error.RebootFail"));
							}
						}
					}else if ( i == m_nChannelNum && AlarmCfg_RB == FALSE&&AlarmExp_RB==FALSE)
					{
						MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
					}else
					{
						MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
					}
				}
			}
		}
	}
}

void CClientDemo5Dlg::GetPTZConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		SDK_STR_PTZCONFIG_ALL PtzCfgAll;
		
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_PTZ,-1,
			(char *)&PtzCfgAll,sizeof(SDK_STR_PTZCONFIG_ALL),&dwRetLen,nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_STR_PTZCONFIG_ALL))
		{
			SDK_PTZPROTOCOLFUNC PtzProtocol;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_PTZPRO,0,
				(char *)&PtzProtocol,sizeof(SDK_PTZPROTOCOLFUNC),&dwRetLen,nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_PTZPROTOCOLFUNC))
			{
				//m_Ptz.InitDlgInfo(&PtzCfgAll,m_nChannelNum,&PtzProtocol);
// 				SDK_STR_RS485CONFIG_ALL RsCfgAll;
// 				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMM485,-1,
// 					(char *)&RsCfgAll,sizeof(SDK_STR_RS485CONFIG_ALL),&dwRetLen,nWaitTime);
// 				if (bSuccess && dwRetLen == sizeof(SDK_STR_RS485CONFIG_ALL))
// 				{
					SDK_STR_RS485CONFIG_ALL RsCfgAll;
					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMM485,-1,
						(char *)&RsCfgAll,sizeof(SDK_STR_RS485CONFIG_ALL),&dwRetLen,nWaitTime);	
					if(bSuccess && dwRetLen ==  sizeof(SDK_STR_RS485CONFIG_ALL))
					{
						m_Ptz.InitDlgInfo(&PtzCfgAll,m_nChannelNum,&PtzProtocol,&RsCfgAll);
					}
				else
				{
					m_Ptz.InitDlgInfo(&PtzCfgAll,m_nChannelNum,&PtzProtocol,NULL);
				}
			}
		}
	}
}

void CClientDemo5Dlg::SetPtzConfigInfo(SDK_STR_PTZCONFIG_ALL *pPtzConfigAll,SDK_STR_RS485CONFIG_ALL *pRSConfigALL)
{
	if ( 0 != m_LoginID && pPtzConfigAll != NULL)
	{
		int nWaitTime = 10000;
		BOOL bSuccess =FALSE;
		BOOL bReboot = FALSE;
		int i = 0;
		for (;i< m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_PTZ,i,
				(char *)&pPtzConfigAll->ptzAll[i],sizeof(SDK_STR_CONFIG_PTZ),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
		}
		if (pRSConfigALL != NULL)
		{
				bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_COMM485,-1,
					(char *)pRSConfigALL,sizeof(SDK_STR_RS485CONFIG_ALL),nWaitTime);
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
			
		}

		if ( i == m_nChannelNum && bReboot == TRUE )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( i == m_nChannelNum && bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}

void CClientDemo5Dlg::GetCameraPara()
{
	if (!m_typeIPC)
	{
		m_typeIPC = false;
		MessageBox(_CS("Error.EquipmentParametersToFail"));
		return;
	}
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		int i = 0;
		SDK_AllCameraParam CameraParaAll;
		SDK_CameraAbility CameraAbility;

		bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_ABILITY_CAMERA, -1,
			(char *)&CameraAbility, sizeof(SDK_CameraAbility), &dwRetLen, nWaitTime);
		if ( bSuccess && ( dwRetLen == sizeof(SDK_CameraAbility)))
		{	
			for ( ; i< m_nChannelNum; i++)
			{
				bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_CAMERA, i,
					(char *)&CameraParaAll.vCameraParamAll[i], sizeof(SDK_CameraParam), &dwRetLen, nWaitTime);
				if ( (!bSuccess) || (dwRetLen != sizeof(SDK_CameraParam)) )
				{
					break;
				}
			}
			if ( i == m_nChannelNum )
			{
				m_SysCamera.InitDlgInfo(&CameraParaAll, &CameraAbility, m_nChannelNum);
			}
		}
		else
			MessageBox(_CS("Error.EquipmentParametersToFail"));
	}
}


void CClientDemo5Dlg::SetCameraPara(SDK_AllCameraParam* pCameraParaAll)
{
	if ( 0 != m_LoginID && pCameraParaAll != NULL)
	{
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		BOOL bReboot = FALSE;
		int i = 0;
		for (;i< m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_CAMERA,i,
				(char *)&pCameraParaAll->vCameraParamAll[i],sizeof(SDK_CameraParam),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}

		}
		
		if ( i == m_nChannelNum && bReboot == TRUE )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( i == m_nChannelNum && bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}

void CClientDemo5Dlg::GetUserInfo()
{
	if ( 0 != m_LoginID&&m_userManager)
	{		
		m_userManager->m_LoginID=m_LoginID;
		//by zhouhao
		m_userManager->InitDlgInfo();
	}
}
void  CClientDemo5Dlg::SetAlarmException(SDK_VIDEOLOSSCONFIG *pStorageNE,SDK_VIDEOLOSSCONFIG *pStorageFL,SDK_VIDEOLOSSCONFIG *pNetipCfg,SDK_VIDEOLOSSCONFIG *pNetaBort,SDK_StorageLowSpaceConfig *pStorageLSCfg)
{

	if ( 0 != m_LoginID && pStorageNE != NULL&& pStorageLSCfg !=NULL&&pStorageFL!=NULL&&pNetipCfg!=NULL &&pNetaBort!=NULL )
	{
		int i = 0;
		int nWaitTime = 10000;
// 		BOOL bSuccess =FALSE;
// 		BOOL bReboot = FALSE;
		AlarmExp_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_STORAGENOTEXIST,-1,
			(char *)pStorageNE,sizeof(SDK_VIDEOLOSSCONFIG),nWaitTime);

			if ( AlarmExp_SC == H264_DVR_OPT_REBOOT)
			{
				AlarmExp_RB = TRUE;
			}

		AlarmExp_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_STORAGEFAILURE,-1,
			(char *)pStorageFL,sizeof(SDK_VIDEOLOSSCONFIG),nWaitTime);

			if ( AlarmExp_SC == H264_DVR_OPT_REBOOT)
			{
				AlarmExp_RB = TRUE;
			}
		AlarmExp_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CFG_NETIPCONFLICT,-1,
				(char *)pNetipCfg,sizeof(SDK_VIDEOLOSSCONFIG),nWaitTime);

			if ( AlarmExp_SC == H264_DVR_OPT_REBOOT)
			{
				AlarmExp_RB = TRUE;
			}
		AlarmExp_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CFG_NETABORT,-1,
				(char *)pNetaBort,sizeof(SDK_VIDEOLOSSCONFIG),nWaitTime);
			if ( AlarmExp_SC == H264_DVR_OPT_REBOOT)
			{
				AlarmExp_RB = TRUE;
			}
		AlarmExp_SC = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_STORAGELOWSPACE,-1,
				(char *)pStorageLSCfg,sizeof(SDK_StorageLowSpaceConfig),nWaitTime);
	
			if ( AlarmExp_SC == H264_DVR_OPT_REBOOT)
			{
				AlarmExp_RB = TRUE;
			}
	}
}
void CClientDemo5Dlg::GetAlarmException()
{
	if(0!=m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		int i = 0;
		SDK_VIDEOLOSSCONFIG *StorageNE=new SDK_VIDEOLOSSCONFIG;
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_STORAGENOTEXIST,-1,
			(char *)StorageNE,sizeof(SDK_VIDEOLOSSCONFIG),&dwRetLen,nWaitTime);

		if (bSuccess&&dwRetLen==sizeof(SDK_VIDEOLOSSCONFIG))
		{
			SDK_SystemFunction SysFunc;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,-1,
				(char *)&SysFunc,sizeof(SDK_SystemFunction),&dwRetLen,nWaitTime);
			if (bSuccess&&dwRetLen==sizeof(SDK_SystemFunction))
			{
				SDK_VIDEOLOSSCONFIG *StorageFL=new SDK_VIDEOLOSSCONFIG;
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_STORAGEFAILURE,-1,
				(char *)StorageFL,sizeof(SDK_VIDEOLOSSCONFIG),&dwRetLen,nWaitTime);
				if (bSuccess&&dwRetLen==sizeof(SDK_VIDEOLOSSCONFIG))
				{
					SDK_VIDEOLOSSCONFIG *NetipCfg=new SDK_VIDEOLOSSCONFIG;
					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CFG_NETIPCONFLICT,-1,
					(char *)NetipCfg,sizeof(SDK_VIDEOLOSSCONFIG),&dwRetLen,nWaitTime);
					if (bSuccess&&dwRetLen==sizeof(SDK_VIDEOLOSSCONFIG))
					{
						SDK_VIDEOLOSSCONFIG *NetaBort=new SDK_VIDEOLOSSCONFIG;;
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CFG_NETABORT,-1,
						(char *)NetaBort,sizeof(SDK_VIDEOLOSSCONFIG),&dwRetLen,nWaitTime);
						if (bSuccess&&dwRetLen==sizeof(SDK_VIDEOLOSSCONFIG))
						{
							SDK_StorageLowSpaceConfig *StorageLSCfg=new SDK_StorageLowSpaceConfig;
							bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_STORAGELOWSPACE,-1,
							(char *)StorageLSCfg,sizeof(SDK_StorageLowSpaceConfig),&dwRetLen,nWaitTime);
							if (bSuccess&&dwRetLen==sizeof(SDK_StorageLowSpaceConfig))
							{
								m_alarmDlg.InitDlgInfo(StorageNE,StorageFL,NetipCfg,NetaBort,&SysFunc,StorageLSCfg);
							}
							delete StorageLSCfg;
						}
						delete NetaBort;
					}
					delete NetipCfg;
				}
				
			delete StorageFL;
			
			}
		}
		delete StorageNE;
	}
}

void CClientDemo5Dlg:: GetChannelNS()
{
	if (0!=m_LoginID)
	{
		SDK_ChannelNameConfigAll pChannelName;
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;

		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_CHANNEL_NAME,-1,
				(char *)&pChannelName,sizeof(SDK_ChannelNameConfigAll),&dwRetLen,nWaitTime	);
		/*	if ((!bSuccess)||dwRetLen!=sizeof(SDK_ChannelNameConfigAll))break;	*/	
		if (bSuccess&&dwRetLen==sizeof(SDK_ChannelNameConfigAll))
		{
			m_channelNS.InitDlgInfo(&pChannelName,m_nbyChanNum+m_niDigChannel);
		}
			
		
	}
}
void CClientDemo5Dlg::setChannelNS(SDK_ChannelNameConfigAll *pChannelName)
{
	if (0 != m_LoginID)
	{
		int nWaitTime = 10000;
		BOOL bSuccess =FALSE;
		BOOL bReboot = FALSE;
	

		bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_CHANNEL_NAME,-1,
			(char *)pChannelName,sizeof(SDK_ChannelNameConfigAll),nWaitTime);

		if(bSuccess&&m_nChannelNum + m_niDigChannel == 1&&m_pBuf != NULL)
		{
			H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_CHANNELTILE_DOT,0,
			(char *)m_pBuf, m_nWidth*m_nHeigth/8,nWaitTime);
		}

		if (bSuccess == H264_DVR_OPT_REBOOT)
		{
			bReboot = TRUE;
		}
		if (bReboot == TRUE )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
} 
void CClientDemo5Dlg::GetVehicleDlg()
{
	if (0!=m_LoginID)
	{
		SDK_CarStatusExchangeAll pCarStaExg;
		SDK_CarDelayTimeConfig pCarDelayTimeCfg;
		SDK_SystemFunction pSysFunc;
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;

		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_CAR_INPUT_EXCHANGE,-1,
			(char *)&pCarStaExg,sizeof(SDK_CarStatusExchangeAll),&dwRetLen,nWaitTime	);
		/*	if ((!bSuccess)||dwRetLen!=sizeof(SDK_ChannelNameConfigAll))break;	*/	
		
		if (bSuccess&&dwRetLen==sizeof(SDK_CarStatusExchangeAll))
		{
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_DELAY_TIME,-1,
			(char *)&pCarDelayTimeCfg,sizeof(SDK_CarDelayTimeConfig),&dwRetLen,nWaitTime	);
			if (bSuccess&&dwRetLen==sizeof(SDK_CarDelayTimeConfig))
			{
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,-1,
				(char *)&pSysFunc,sizeof(SDK_SystemFunction),&dwRetLen,nWaitTime);
				if (bSuccess&&dwRetLen == sizeof(SDK_SystemFunction))
				{
					m_vehicleDlg.InitDlgInfo(&pCarStaExg,&pCarDelayTimeCfg,&pSysFunc,m_nAlarmInNum);
				}
			
			}
		
		}
		
		
		
	}
}

void CClientDemo5Dlg::setVehicleDlg(SDK_CarStatusExchangeAll *pCarStaExg,SDK_CarDelayTimeConfig *pCarDelayTimeCfg)
{
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		BOOL bSuccess =FALSE;
		BOOL bReboot = FALSE;
		bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_CAR_INPUT_EXCHANGE,-1,
			(char *)pCarStaExg,sizeof(SDK_CarStatusExchangeAll),nWaitTime);
		if (bSuccess)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_DELAY_TIME,-1,
			(char *)pCarDelayTimeCfg,sizeof(SDK_CarDelayTimeConfig),nWaitTime);

			if (bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
			if (bReboot == TRUE )
			{
				if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
				{
					bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
					if (bSuccess)
					{
						OnBtnLogout();
					}else
					{
						MessageBox(_CS("Error.RebootFail"));
					}
				}
			}else if ( bReboot == FALSE)
			{
				MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
			}else
			{
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
			}
		}
	
	}
}

void CClientDemo5Dlg::setVehicleDlg(SDK_CarStatusExchangeAll *pCarStaExg)
{
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		BOOL bSuccess =FALSE;
		BOOL bReboot = FALSE;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_CAR_INPUT_EXCHANGE,-1,
			(char *)pCarStaExg,sizeof(SDK_CarStatusExchangeAll),nWaitTime);
		if ( bSuccess )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}

		else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
			
	}

}

void CClientDemo5Dlg::GetNetDecorderCfg()
{


	m_niDigChannel;
	if (0 != m_LoginID)
	{   //数字通道
		SDK_NetDecorderConfigAll_V3 *pNetDigitChnConfig=new SDK_NetDecorderConfigAll_V3;
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		int i = 0 ;
		for ( ; i < m_niDigChannel ; i++)
		{
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DECODER_V3,i,
			(char *)&pNetDigitChnConfig->DigitChnConf[i],sizeof(SDK_NetDigitChnConfig),&dwRetLen,nWaitTime);
//	    	if ( (!bSuccess) || (dwRetLen != sizeof(SDK_NetDigitChnConfig)) )
//	 		{
//				break;
//			}
		}
//		if ( i == m_niDigChannel )
//		{
	    
		m_cfgDigitalChannel->m_dlgDigitalChannel.InitDlgInfo(pNetDigitChnConfig,m_niDigChannel);
//		}
		delete pNetDigitChnConfig;

        // 通道模式
		SDK_NetDecorderChnModeConfig *pNetChnModeConfig = new SDK_NetDecorderChnModeConfig;
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_CHNMODE,-1,(char*)pNetChnModeConfig,
		        	sizeof(SDK_NetDecorderChnModeConfig),&dwRetLen,nWaitTime);
         
		m_cfgDigitalChannel->m_dlgChannelMode.InitDlgInfo(pNetChnModeConfig);
		delete pNetChnModeConfig;
 
		// 通道状态
		SDK_NetDecorderChnStatusAll *pNetChnStatusConfigAll = new SDK_NetDecorderChnStatusAll;
        bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_CHNSTATUS,-1,(char*)pNetChnStatusConfigAll,
			        sizeof(SDK_NetDecorderChnStatusAll),&dwRetLen,nWaitTime);

		m_cfgDigitalChannel->m_dlgChannelStatus.InitDlgInfo(pNetChnStatusConfigAll);
		delete pNetChnStatusConfigAll;

	}
 
}

void CClientDemo5Dlg::GetNetCommon()
{

	if (0!=m_LoginID)
	{
		SDK_CONFIG_NET_COMMON pNetCommon;
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNET,-1,
				(char *)&pNetCommon,sizeof(SDK_CONFIG_NET_COMMON),&dwRetLen,nWaitTime);
		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NET_COMMON) )
		{
			
			m_RemoteChanDlg.GetData(&pNetCommon);
			
		}
			
	}

}
BOOL CClientDemo5Dlg::SetNetDecorderCfg(SDK_NetDigitChnConfig *pNetDigitChnConfig,int nDigChannelNum)
{
	if (0 != m_LoginID)
	{
		int nWaitTime = 10000;
		BOOL bSuccess =FALSE;
		BOOL bReboot = FALSE;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DECODER_V3,nDigChannelNum,
			(char *)pNetDigitChnConfig,sizeof(SDK_NetDigitChnConfig),nWaitTime);
		if (bSuccess == H264_DVR_OPT_REBOOT)
		{
			bReboot = TRUE;
		}
		if (bReboot == TRUE )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( bReboot == FALSE && bSuccess )
		{
			//MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
			return true;
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
			return false;
		}
		return false;
	}
	return false;
}
void CClientDemo5Dlg::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int type=m_typeComboBox.GetCurSel();
}

void CClientDemo5Dlg::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	if(2==m_typeComboBox.GetCurSel())
	{
		H264_DVR_StartActiveRigister(9400,DevicCallBack,(unsigned long )this);
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DVRPWD)->EnableWindow(FALSE);
		
	}
	else
	{
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);	
		SetDlgItemText(IDC_STATIC_ADDR,_CS("DeviceManage.IPAddress"));			
		if(H264_DVR_StopActiveRigister())
		{
			
			GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(TRUE);
    		GetDlgItem(IDC_EDIT_DVRPWD)->EnableWindow(TRUE);
			m_LoginID=0;
			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
			//Device property 
			m_serverDlg.CleanAll();
			//Video channel property 
			m_channelDlg.CleanAll();
			//COM property 
			m_commDlg.CleanAll();
			//Record configuration 
			m_recordDlg.CleanAll();
			//Network configuration 
			m_networkDlg.CleanAll();
			//Alarm property 
			m_alarmDlg.CleanAll();
			//Ptz
			m_Ptz.CleanAll();
			//Camera Parameters
			m_SysCamera.CleanAll();
			m_channelNS.CleanAll();
			m_vehicleDlg.CleanAll();
		}
	}
}

void CClientDemo5Dlg::GetOutputConfigInfo()
{
     if (0 != m_LoginID)
     {
          DWORD dwRetLen = 0;
		  int nWaitTime = 10000;
		  OUTPUTCONFIGALL* OutputCfgAll = new OUTPUTCONFIGALL();
         // 针对个别设备配置不同		
		  BOOL bSuccess = FALSE;
		  bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_CHANNEL_NAME,-1,
			              (char*)&OutputCfgAll->ChanNameCfgAll,sizeof(SDK_ChannelNameConfigAll),&dwRetLen,nWaitTime);
		
		  if(TRUE == bSuccess && sizeof(SDK_ChannelNameConfigAll) == dwRetLen&&0 <m_nbyChanNum)
		  {
			  m_bOutputCfg[0] = TRUE;
		  }
		  else
		  { 
              m_bOutputCfg[0] = FALSE;
		  }
 	       
		  bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_GUISET,-1,(char*)&OutputCfgAll->GUISetCfg,
 				             sizeof(SDK_GUISetConfig),&dwRetLen,nWaitTime); 
		  if (TRUE == bSuccess && sizeof(SDK_GUISetConfig) == dwRetLen)
		  {
			  m_bOutputCfg[1] = TRUE;
		  }
		  else
		  {
			  m_bOutputCfg[1] = FALSE;
		  }


		  bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_OUT_MODE,-1,(char*)&OutputCfgAll->VideoWdtCfgAll,
					     sizeof(SDK_VideoWidgetConfigAll),&dwRetLen,nWaitTime);
		  
		  if (TRUE == bSuccess && sizeof(SDK_VideoWidgetConfigAll) == dwRetLen )
		  {
			  int i = 0;
			  for ( ; i < m_nbyChanNum; ++i)
			  {
				  bSuccess =H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_BLIND_FUNC,i,(char*)&(OutputCfgAll->BlindDetFunc[i]),
					  sizeof(SDK_BlindDetectFunction),&dwRetLen,nWaitTime);
                   
				   
				  if(TRUE == bSuccess && sizeof(SDK_BlindDetectFunction) == dwRetLen)
				  {
			           m_bOutputCfg[2] = TRUE;
				  }
				  else
				  {
					  m_bOutputCfg[2] = FALSE;
				  }
			  } 
		  }
		  else
		  {
			  m_bOutputCfg[2] = FALSE;	  
		  }

		  for (int i = 0;i < 3;++ i)
		  {
			  if (m_bOutputCfg[i])
			  {
				  m_outputDlg.InitDlgInfo(OutputCfgAll,m_nbyChanNum + m_niDigChannel);
			  }
		  }

			   
		 
		  delete OutputCfgAll;
     }
}

void CClientDemo5Dlg::SetOutputConfigInfo(OUTPUTCONFIGALL *outputCfgInfo)
{
	  int nWaitTime = 10000;
	  BOOL bSuccess = FALSE;
	  BOOL bReboot;

	  if (m_bOutputCfg[1])
	  {
		  bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_GUISET,-1,(char*)&outputCfgInfo->GUISetCfg,sizeof(SDK_GUISetConfig),nWaitTime);
	  }
	  
	  if (m_bOutputCfg[2])
	  {

	       if (!H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_OUT_MODE,-1,(char*)&outputCfgInfo->VideoWdtCfgAll,sizeof(SDK_VideoWidgetConfigAll),nWaitTime))
		   {
              if ( bSuccess )
              {
				  bSuccess = TRUE;
              }
		   }
		   else
		   {
			   bSuccess = TRUE;
		   }
	  }
	  if (bSuccess)
	  {
			if (bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
			if ( bReboot == TRUE )
			{
				if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
				{
					bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
					if (bSuccess)
					{
						OnBtnLogout();
					}
					else
					{
						MessageBox(_CS("Error.RebootFail"));
					}
				}
			}
			if ( bSuccess > 0)
			{
				MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
			}else if ( bSuccess < 0 && bSuccess != H264_DVR_OPT_REBOOT)
			{
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
			}
		}
}

void CClientDemo5Dlg::LocalCatPic(TCHAR* strFileName,int nChannelNum,CWnd* wnd)
{
	H264_DVR_CLIENTINFO playstru;
	
	playstru.nChannel = nChannelNum;
	playstru.nStream = 0;
	playstru.nMode = 0;
	playstru.hWnd =  wnd;
	
	long lPlayhandle = -1;

	lPlayhandle = H264_DVR_RealPlay(((CClientDemo5Dlg* )AfxGetMainWnd())->m_LoginID, &playstru);
	
	if (lPlayhandle <= 0)
	{
		AfxMessageBox("Error.HandleIsIllegal!");
	    return;
	}
	
	BOOL bRet;
	Sleep(5000);  //wait for bmp
    bRet = H264_DVR_LocalCatchPic(lPlayhandle,strFileName);
	
	if (TRUE != bRet)
	{
		DWORD dwEr = H264_DVR_GetLastError();
		AfxMessageBox("Error.Fail!!");
		return;
	}	
	H264_DVR_StopRealPlay(lPlayhandle);
}

void CClientDemo5Dlg::GetLogInfo()
{

}

CString CClientDemo5Dlg::GetSdkErrorInfo(int nError)
{
	CString strMsg(_CS("Error.UnkownErr"));
	switch(nError)
	{
	case H264_DVR_SDK_NOTVALID:			//非法请求
		strMsg = _CS("Error.ReqErr");
		break;
	case H264_DVR_NO_INIT:				//SDK未经初始化
		strMsg = _CS("Error.NoInit");
		break;
	case H264_DVR_ILLEGAL_PARAM:			//用户参数不合法
		strMsg = _CS("Error.ParamInvalid");
	    break;
	case H264_DVR_INVALID_HANDLE:		//句柄无效
		strMsg = _CS("Error.HandleInvalid");
	    break;
	case H264_DVR_SDK_UNINIT_ERROR:		//SDK清理出错
		strMsg = _CS("Error.ClearSDKError");
		break;
	case H264_DVR_SDK_TIMEOUT:			//等待超时
		strMsg = _CS("Error.Timeout");
		break;
	case H264_DVR_SDK_MEMORY_ERROR:		//内存错误，创建内存失败
		strMsg = _CS("Error.MallocErr");
	    break;
	case H264_DVR_SDK_NET_ERROR:			//网络错误
		strMsg = _CS("Error.NetErr");
	    break;
	case H264_DVR_DEV_VER_NOMATCH:		//收到数据不正确，可能版本不匹配
		strMsg = _CS("Error.VerUnmatch");
	    break;
	case H264_DVR_SDK_NOTSUPPORT:		//版本不支持
		strMsg = _CS("Error.Unsupport");
	    break;
	case H264_DVR_OPEN_CHANNEL_ERROR:	//打开通道失败
		strMsg = _CS("Error.OpenChnErr");
	    break;
	case H264_DVR_CLOSE_CHANNEL_ERROR:	//关闭通道失败
		strMsg = _CS("Error.CloseChnErr");
	    break;
	case H264_DVR_SUB_CONNECT_ERROR:		//建立媒体子连接失败
		strMsg = _CS("Error.SubConErr");
	    break;
	case H264_DVR_SUB_CONNECT_SEND_ERROR://媒体子连接通讯失败
		strMsg = _CS("Error.SubConSendErr");
	    break;
	case H264_DVR_NOPOWER:				//无权限
		strMsg = _CS("Error.NoPower");
	    break;
	case H264_DVR_PASSWORD_NOT_VALID:	// 账号密码不对
		strMsg = _CS("Error.PwdErr");
	    break;
	case H264_DVR_LOGIN_USER_NOEXIST:	//用户不存在
		strMsg = _CS("Error.UserNotExisted");
	    break;
	case H264_DVR_USER_LOCKED:			// 该用户被锁定
		strMsg = _CS("Error.UserLock");
	    break;
	case H264_DVR_USER_IN_BLACKLIST:		// 该用户不允许访问(在黑名单中)
		strMsg = _CS("Error.InBlackList");
	    break;
	case H264_DVR_USER_HAS_USED:			// 该用户以登陆
		strMsg = _CS("Error.HasLogined");
	    break;
	case H264_DVR_USER_NOT_LOGIN	:		// 该用户没有登陆
		strMsg = _CS("Error.NoLogin");
	    break;
	case H264_DVR_CONNECT_DEVICE_ERROR:	//可能设备不存在
		strMsg = _CS("Error.NotFound");
	    break;
	case H264_DVR_ACCOUNT_INPUT_NOT_VALID:	//用户管理输入不合法
		strMsg = _CS("Error.InputError");
	    break;
	case H264_DVR_ACCOUNT_OVERLAP:			//索引重复
		strMsg = _CS("AccountMSG.AccountUsed");
	    break;
	case H264_DVR_ACCOUNT_OBJECT_NONE:		//不存在对象, 用于查询时
		strMsg = _CS("AccountMSG.EmptyName");
	    break;
	case H264_DVR_ACCOUNT_OBJECT_NOT_VALID:	//不存在对象
		strMsg = _CS("Error.NotFound");
	    break;
	case H264_DVR_ACCOUNT_OBJECT_IN_USE:		//对象正在使用
		strMsg = _CS("Error.InUsing");
	    break;
	case H264_DVR_ACCOUNT_SUBSET_OVERLAP:	//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
		strMsg = _CS("AccountMSG.TooLargeAuthority");
	    break;
	case H264_DVR_ACCOUNT_PWD_NOT_VALID:		//密码不正确
		strMsg = _CS("Error.PwdErr");
	    break;
	case H264_DVR_ACCOUNT_PWD_NOT_MATCH:		//密码不匹配
		strMsg = _CS("AccountMSG.PasswordMismatch");
	    break;
	case H264_DVR_ACCOUNT_RESERVED:			//保留帐号
		strMsg = _CS("AccountMSG.TryModifyResvUser");
	    break;		
	case H264_DVR_OPT_FILE_ERROR:			// 写文件出错
		strMsg = _CS("Error.SetConfigFail");
	    break;	
	case H264_DVR_OPT_CAPS_ERROR:			// 配置特性不支持
		strMsg = _CS("Error.ConfigCharsetUnsupport");
	    break;
	case H264_DVR_OPT_VALIDATE_ERROR:		// 配置校验失败
		strMsg = _CS("Error.ConfigVerifyFail");
	    break;
	case H264_DVR_OPT_CONFIG_NOT_EXIST:		// 请求或者设置的配置不存在
		strMsg = _CS("Error.ConfigNotFound");
	    break;	
	case H264_DVR_CTRL_PAUSE_ERROR:			//暂停失败
		strMsg = _CS("Error.PauseFail");
	    break;
	default:
		{
			//如果没有，则返回设备端错误码
			CString strError;
			strError.Format(_T("(%d)"),  nError * ( -1 ) ); //根据原来的返回值的相反值取原来的返回值
			strMsg += strError;
		}
	    break;
	}

	return strMsg;
}
 

void CClientDemo5Dlg::SetChnModeConfig(SDK_NetDecorderChnModeConfig *pNetChnModeCfg)
{
	
	int nRet = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_CHNMODE,-1, (char*)pNetChnModeCfg,
		sizeof(SDK_NetDecorderChnModeConfig),5000);
	if ( nRet > 0 || nRet == H264_DVR_OPT_REBOOT )
	{
		if ( nRet == H264_DVR_OPT_REBOOT )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				if (H264_DVR_ControlDVR(m_LoginID,0))
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );  
		}
	}
	else
	{
		
	}
}



//by zhouhao
void CClientDemo5Dlg::GetNetServerConfigInfo()
{
	//by zhouhao
	SDK_SystemFunction SysFunc;
	DWORD dwRetLen = 0;
	int nWaitTime = 10000;
	BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,-1,
		(char*)&SysFunc,sizeof(SDK_SystemFunction),&dwRetLen,nWaitTime);
	if (bSuccess && sizeof(SDK_SystemFunction) == dwRetLen)
				m_netServerDlg.InitDlgInfo(&SysFunc);
}

void CClientDemo5Dlg::GetIPFilterConfigInfo()
{
	SDK_NetIPFilterConfig *pNetIPFitCfg = new SDK_NetIPFilterConfig;
	DWORD dwRetLen = 0;
	int nWaitTime = 10000;
	BOOL bSuccess = FALSE;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_IPFILTER,-1,
		(char*)pNetIPFitCfg,sizeof(SDK_NetIPFilterConfig),&dwRetLen,nWaitTime);
	if (bSuccess && sizeof(SDK_NetIPFilterConfig) == dwRetLen)
		m_netServerDlg.m_ipFilterDlg.InitDlgInfo(pNetIPFitCfg);
	delete pNetIPFitCfg;
}

int CClientDemo5Dlg::SetIPFilterConfigInfo(SDK_NetIPFilterConfig *pNetIPFitCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
	
		bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_IPFILTER,-1,
			(char *)pNetIPFitCfg,sizeof(SDK_NetIPFilterConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetDDNSConfigInfo()
{
	SDK_NetDDNSConfigALL *pNetDDNSCfg = new SDK_NetDDNSConfigALL;
	SDK_DDNSServiceFunction *pDDNSFunc = new SDK_DDNSServiceFunction;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DDNS,-1,
			(char*)pNetDDNSCfg,sizeof(SDK_NetDDNSConfigALL),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetDDNSConfigALL))
	{
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_DDNS_SERVER,-1,
			(char*)pDDNSFunc,sizeof(SDK_DDNSServiceFunction),&dwRetlen,nWaitTime);
		if (bSuccess && dwRetlen == sizeof(SDK_DDNSServiceFunction))
		{
				m_netServerDlg.m_ddnsDlg.InitDlgInfo(pNetDDNSCfg,pDDNSFunc);
		}
	}
	delete pNetDDNSCfg;
	delete pDDNSFunc;
}

int CClientDemo5Dlg::SetDDNSConfigInfo(SDK_NetDDNSConfigALL *pNetDDNSCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DDNS,-1,
			(char *)pNetDDNSCfg,sizeof(SDK_NetDDNSConfigALL),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetEmailConfigInfo()
{
	SDK_NetEmailConfig *pNetEmail = new SDK_NetEmailConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	//m_netServerDlg.m_emailDlg.m_LoginID = m_LoginID;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_EMAIL,-1,
		(char*)pNetEmail,sizeof(SDK_NetEmailConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetEmailConfig))
	{
		m_netServerDlg.m_emailDlg.InitDlgInfo(pNetEmail,m_LoginID);
		//m_netServerDlg.m_emailDlg.m_LoginID = m_LoginID;
	}
	delete pNetEmail;
}



int CClientDemo5Dlg::SetEmailConfigInfo(SDK_NetEmailConfig *pNetEmail)
{	
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_EMAIL,-1,
			(char *)pNetEmail,sizeof(SDK_NetEmailConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetNTPConfigInfo()
{
	GetPPPOEConfigInfo();//临时
	SDK_NetNTPConfig *pNetNTP = new SDK_NetNTPConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_NTP,-1,
		(char*)pNetNTP,sizeof(SDK_NetNTPConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetNTPConfig))
	{
		m_netServerDlg.m_ntpDlg.InitDlgInfo(pNetNTP);
	}
	delete pNetNTP;
}

int CClientDemo5Dlg::SetNTPConfigInfo(SDK_NetNTPConfig *pNetNTP)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_NTP,-1,
			(char *)pNetNTP,sizeof(SDK_NetNTPConfig),nWaitTime);
	}
	return bSuccess;
}	

void CClientDemo5Dlg::GetPPPOEConfigInfo()
{
	SDK_NetPPPoEConfig *pNetPPPOE = new SDK_NetPPPoEConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_PPPOE,-1,
		(char*)pNetPPPOE,sizeof(SDK_NetPPPoEConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetPPPoEConfig))
	{
		m_netServerDlg.m_pppoeDlg.InitDlgInfo(pNetPPPOE);
	}
	delete pNetPPPOE;
}

int CClientDemo5Dlg::SetPPPOEConfigInfo(SDK_NetPPPoEConfig *pNetPPPOE)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_PPPOE,-1,
			(char *)pNetPPPOE,sizeof(SDK_NetPPPoEConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetARSPConfigInfo()
{
	SDK_NetARSPConfigAll *pNetARSP = new SDK_NetARSPConfigAll;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_ARSP,-1,
		(char*)pNetARSP,sizeof(SDK_NetARSPConfigAll),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetARSPConfigAll))
	{
		m_netServerDlg.m_arspDlg.InitDlgInfo(pNetARSP);
	}
	delete pNetARSP;
}

int CClientDemo5Dlg::SetARSPConfigInfo(SDK_NetARSPConfigAll *pNetARSP)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;		
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_ARSP,-1,
			(char *)pNetARSP,sizeof(SDK_NetARSPConfigAll),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::Get3GConfigInfo()
{
	SDK_Net3GConfig *pNet3GCfg = new SDK_Net3GConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_3G,-1,
		(char*)pNet3GCfg,sizeof(SDK_Net3GConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_Net3GConfig))
	{
		m_netServerDlg.m_3gDlg.InitDlgInfo(pNet3GCfg);
	}
	delete pNet3GCfg;
}

int CClientDemo5Dlg::Set3GConfigInfo(SDK_Net3GConfig *pNet3GCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_3G,-1,
			(char *)pNet3GCfg,sizeof(SDK_Net3GConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetMobileConfigInfo()
{
	SDK_NetMoblieConfig *pNetMobileCfg = new SDK_NetMoblieConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_MOBILE,-1,
		(char*)pNetMobileCfg,sizeof(SDK_NetMoblieConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetMoblieConfig))
	{
		m_netServerDlg.m_mobileDlg.InitDlgInfo(pNetMobileCfg);
	}
	delete pNetMobileCfg;
}

int CClientDemo5Dlg::SetMobileConfigInfo(SDK_NetMoblieConfig *pNetMobileCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;	
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_MOBILE,-1,
			(char *)pNetMobileCfg,sizeof(SDK_NetMoblieConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetUPNPConfigInfo()
{
	SDK_NetUPNPConfig *pNetUPNPCfg = new SDK_NetUPNPConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_UPNP,-1,
		(char*)pNetUPNPCfg,sizeof(SDK_NetUPNPConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetUPNPConfig))
	{
		m_netServerDlg.m_upnpDlg.InitDlgInfo(pNetUPNPCfg);
	}
	delete pNetUPNPCfg;
}

int CClientDemo5Dlg::SetUPNPConfigInfo(SDK_NetUPNPConfig *pNetUPNPCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;	
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_UPNP,-1,
			(char *)pNetUPNPCfg,sizeof(SDK_NetUPNPConfig),nWaitTime);
	}
	return bSuccess;
}



void CClientDemo5Dlg::GetFTPConfigInfo()
{
	SDK_FtpServerConfig *pFtpCfg = new SDK_FtpServerConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_FTPSERVER,-1,
		(char*)pFtpCfg,sizeof(SDK_FtpServerConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_FtpServerConfig))
	{
		m_netServerDlg.m_ftpDlg.InitDlgInfo(pFtpCfg);
	}
	delete pFtpCfg;
}

int CClientDemo5Dlg::SetFTPConfigInfo(SDK_FtpServerConfig *pFtpCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_FTPSERVER,-1,
			(char *)pFtpCfg,sizeof(SDK_FtpServerConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetWIFIConfigInfo()
{
	SDK_NetWifiConfig *pNetWifiCfg = new SDK_NetWifiConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_WIFI,-1,
		(char*)pNetWifiCfg,sizeof(SDK_NetWifiConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetWifiConfig))
	{
		m_netServerDlg.m_wifiDlg.InitDlgInfo(pNetWifiCfg);
	}
	delete pNetWifiCfg;
}

int CClientDemo5Dlg::SetWIFIConfigInfo(SDK_NetWifiConfig *pNetWifiCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_WIFI,-1,
			(char *)pNetWifiCfg,sizeof(SDK_NetWifiConfig),nWaitTime);
	}
	return bSuccess;
}

bool CClientDemo5Dlg::GetWIFIDeviceALLInfo(SDK_NetWifiDeviceAll *pNetWifiDeviceAll)
{
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_WIFI_AP_LIST,-1,
		(char*)pNetWifiDeviceAll,sizeof(SDK_NetWifiDeviceAll),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetWifiDeviceAll))
	{
		return true;
	}
	return false;
}

bool CClientDemo5Dlg::GetDHCPConfigInfo(SDK_NetDHCPConfigAll *pNetDHCPCfg)
{
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DHCP,-1,
		(char*)pNetDHCPCfg,sizeof(SDK_NetDHCPConfigAll),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetDHCPConfigAll))
	{
		return true;
	}
	return false;
}

void CClientDemo5Dlg::GetAlarmCenterConfigInfo()
{
	SDK_NetAlarmServerConfigAll *pNetAlarmCfg = new SDK_NetAlarmServerConfigAll;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_CENTER,-1,
		(char*)pNetAlarmCfg,sizeof(SDK_NetAlarmServerConfigAll),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetAlarmServerConfigAll))
	{
		m_netServerDlg.m_alarmDlg.InitDlgInfo(pNetAlarmCfg);
	}
	delete pNetAlarmCfg;
}

int CClientDemo5Dlg::SetAlarmCenterConfigInfo(SDK_NetAlarmServerConfigAll *pNetAlarmCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_CENTER,-1,
			(char *)pNetAlarmCfg,sizeof(SDK_NetAlarmServerConfigAll),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetRTSPConfigInfo()
{
	SDK_NetRTSPConfig *pNetRTSPCfg = new SDK_NetRTSPConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_RTSP,-1,
		(char*)pNetRTSPCfg,sizeof(SDK_NetRTSPConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetRTSPConfig))
	{
		m_netServerDlg.m_rtspDlg.InitDlgInfo(pNetRTSPCfg);
	}
	delete pNetRTSPCfg;
}

int CClientDemo5Dlg::SetRTSPConfigInfo(SDK_NetRTSPConfig *pNetRTSPCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_RTSP,-1,
			(char *)pNetRTSPCfg,sizeof(SDK_NetRTSPConfig),nWaitTime);
	}
	return bSuccess;
}	

void CClientDemo5Dlg::GetShortMsgConfigInfo()
{
	SDK_NetShortMsgCfg *pNetShortMsgCfg = new SDK_NetShortMsgCfg;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_PHONEMSG,-1,
		(char*)pNetShortMsgCfg,sizeof(SDK_NetShortMsgCfg),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetShortMsgCfg))
	{
		m_netServerDlg.m_shortMsgDlg.InitDlgInfo(pNetShortMsgCfg);
	}
	delete pNetShortMsgCfg;
}

int CClientDemo5Dlg::SetShortMsgConfigInfo(SDK_NetShortMsgCfg *pNetShortMsgCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_PHONEMSG,-1,
			(char *)pNetShortMsgCfg,sizeof(SDK_NetShortMsgCfg),nWaitTime);
	}
	return bSuccess;
}


void CClientDemo5Dlg::GetDASConfigInfo()
{
	SDK_DASSerInfo *pNetDASCfg = new SDK_DASSerInfo;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DAS,-1,
		(char*)pNetDASCfg,sizeof(SDK_DASSerInfo),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_DASSerInfo))
	{
		m_netServerDlg.m_dasDlg.InitDlgInfo(pNetDASCfg);
	}
	delete pNetDASCfg;
}

int CClientDemo5Dlg::SetDASConfigInfo(SDK_DASSerInfo *pNetDASCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DAS,-1,
			(char *)pNetDASCfg,sizeof(SDK_DASSerInfo),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetPMSConfigInfo()
{
	SDK_PMSConfig *pNetPMSCfg = new SDK_PMSConfig;
	SDK_PhoneInfoNum *pNetNumCfg = new SDK_PhoneInfoNum;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CFG_PMS,-1,
		(char*)pNetPMSCfg,sizeof(SDK_PMSConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof (SDK_PMSConfig))
	{
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CFG_PMS_MSGNUM,-1,
				(char*)pNetNumCfg,sizeof(SDK_PhoneInfoNum),&dwRetlen,nWaitTime);

		//if (bSuccess && dwRetlen == sizeof (SDK_PMSConfig))
		//{
				m_netServerDlg.m_pmsDlg.InitDlgInfo(pNetPMSCfg,pNetNumCfg);
		//}
	}

	delete pNetPMSCfg;
	delete pNetNumCfg;
}

int CClientDemo5Dlg::SetPMSConfigInfo(SDK_PMSConfig *pNetPMSCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CFG_PMS,-1,
			(char *)pNetPMSCfg,sizeof(SDK_PMSConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetMultimediaConfigInfo()
{
	SDK_NetMultimediaMsgCfg *pNetMultimediaMsgCfg = new SDK_NetMultimediaMsgCfg;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_PHONEMEDIAMSG,-1,
		(char*)pNetMultimediaMsgCfg,sizeof(SDK_NetMultimediaMsgCfg),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetMultimediaMsgCfg))
	{
		m_netServerDlg.m_multiMdeiaDlg.InitDlgInfo(pNetMultimediaMsgCfg);
	}
	delete pNetMultimediaMsgCfg;
}

int CClientDemo5Dlg::SetMultimediaConfigInfo(SDK_NetMultimediaMsgCfg *pNetMultimediaMsgCfg)
{	
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_PHONEMEDIAMSG,-1,
			(char *)pNetMultimediaMsgCfg,sizeof(SDK_NetMultimediaMsgCfg),nWaitTime);
	}
	return bSuccess;
}



void CClientDemo5Dlg::GetDNSConfigInfo()
{
	SDK_NetDNSConfig *pNetDNSCfg = new SDK_NetDNSConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DNS,-1,
		(char*)pNetDNSCfg,sizeof(SDK_NetDNSConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_NetDNSConfig))
	{
		m_netServerDlg.m_dnsDlg.InitDlgInfo(pNetDNSCfg);
	}
	delete pNetDNSCfg;
}

int CClientDemo5Dlg::SetDNSConfigInfo(SDK_NetDNSConfig *pNetDNSCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
	
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DNS,-1,
			(char *)pNetDNSCfg,sizeof(SDK_NetDNSConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetVVEyeConfigInfo()
{
	SDK_CONFIG_NET_VVEYE *pNetVVEyeCfg = new SDK_CONFIG_NET_VVEYE;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_VVEYE,-1,
		(char*)pNetVVEyeCfg,sizeof(SDK_CONFIG_NET_VVEYE),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_CONFIG_NET_VVEYE))
	{
		m_netServerDlg.m_vveyeDlg.InitDlgInfo(pNetVVEyeCfg);
	}
	delete pNetVVEyeCfg;
}

int CClientDemo5Dlg::SetVVEyeConfigInfo(SDK_CONFIG_NET_VVEYE *pNetVVEyeCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_VVEYE,-1,
			(char *)pNetVVEyeCfg,sizeof(SDK_CONFIG_NET_VVEYE),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetSHISOUConfigInfo()
{
	SDK_CONFIG_NET_SHISOU *pNetSHISOUCfg = new SDK_CONFIG_NET_SHISOU;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_SHISOU,-1,
		(char*)pNetSHISOUCfg,sizeof(SDK_CONFIG_NET_VVEYE),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_CONFIG_NET_VVEYE))
	{
		m_netServerDlg.m_shisouDlg.InitDlgInfo(pNetSHISOUCfg);
	}
	delete pNetSHISOUCfg;
}

int CClientDemo5Dlg::SetSHISOUConfigInfo(SDK_CONFIG_NET_SHISOU *pNetSHISOUCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_SHISOU,-1,
			(char *)pNetSHISOUCfg,sizeof(SDK_CONFIG_NET_SHISOU),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetXINGWANGConfigInfo()
{
	SDK_CONFIG_NET_XINGWANG *pNetXIANGWANGCfg = new SDK_CONFIG_NET_XINGWANG;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_XINGWANG,-1,
		(char*)pNetXIANGWANGCfg,sizeof(SDK_CONFIG_NET_XINGWANG),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_CONFIG_NET_XINGWANG))
	{
		m_netServerDlg.m_xingwangDlg.InitDlgInfo(pNetXIANGWANGCfg);
	}
	delete pNetXIANGWANGCfg;
}

int CClientDemo5Dlg::SetXINGWANGConfigInfo(SDK_CONFIG_NET_XINGWANG *pNetXIANGWANGCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_XINGWANG,-1,
			(char *)pNetXIANGWANGCfg,sizeof(SDK_CONFIG_NET_XINGWANG),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetGodEyeConfigInfo()
{
	SDK_GodEyeConfig *pNetGodEyeCfg = new SDK_GodEyeConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_GODEYE_ALARM,-1,
		(char*)pNetGodEyeCfg,sizeof(SDK_GodEyeConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_GodEyeConfig))
	{
			m_netServerDlg.m_godeyeDlg.InitDlgInfo(pNetGodEyeCfg);
	}
	delete pNetGodEyeCfg;
}

int CClientDemo5Dlg::SetCGodEyeConfigInfo(SDK_GodEyeConfig *pNetGodEyeCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_GODEYE_ALARM,-1,
			(char *)pNetGodEyeCfg,sizeof(SDK_GodEyeConfig),nWaitTime);
	}
	return bSuccess;
}



void CClientDemo5Dlg::GetNetInfo()
{
	SDK_LocalSdkNetPlatformConfig *pNetInfoCfg = new SDK_LocalSdkNetPlatformConfig;
	BOOL bSuccess = FALSE;
	DWORD dwRetlen = 0;
	int nWaitTime = 10000;
	bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_LOCALSDK_NET_PLATFORM,-1,
		(char*)pNetInfoCfg,sizeof(SDK_LocalSdkNetPlatformConfig),&dwRetlen,nWaitTime);
	if (bSuccess && dwRetlen == sizeof(SDK_LocalSdkNetPlatformConfig))
	{
		m_netServerDlg.m_netInfoDlg.InitDlgInfo(pNetInfoCfg);
	}
	delete pNetInfoCfg;
}


int CClientDemo5Dlg::SetNetInfo(SDK_LocalSdkNetPlatformConfig *pNetInfoCfg)
{	
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_LOCALSDK_NET_PLATFORM,-1,
			(char *)pNetInfoCfg,sizeof(SDK_LocalSdkNetPlatformConfig),nWaitTime);
	}
	return bSuccess;
}

void CClientDemo5Dlg::GetNatInfo()
{
	BOOL bSuccess = FALSE;
	SDK_NatConfig *pNatInfoCfg = new SDK_NatConfig;
	if (0 != m_LoginID)
	{
		int nWaitTime = 1000;
		DWORD dwRetlen = 0;
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NAT,-1,(char*)pNatInfoCfg,sizeof(SDK_NatConfig),&dwRetlen,nWaitTime);
		if (bSuccess && dwRetlen == sizeof(SDK_NatConfig))
		{
			m_netServerDlg.m_natDlg.InitDlgInfo(pNatInfoCfg);
		
		delete pNatInfoCfg;
		}
	}
}

int CClientDemo5Dlg::SetNatInfo(SDK_NatConfig *pNatInfoCfg)
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 10000;
		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NAT,-1,
			(char *)pNatInfoCfg,sizeof(SDK_NatConfig),nWaitTime);
	}
	return bSuccess;
}
void CClientDemo5Dlg::SetReBootDev()
{
	BOOL bSuccess =FALSE;
	if (0!=m_LoginID)
	{
		int nWaitTime = 3000;
// 		bSuccess =H264_DVR_SetDevConfig(m_LoginID,E_SDK_REBOOT_DEV,-1,
// 			0,0,nWaitTime);
		bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
	}
}

void CClientDemo5Dlg::GetHardDiskInfo()
{
   if (0 != m_LoginID)
   {
	   BOOL bSuccess = FALSE;
	   DWORD dwRet;
	   SDK_SystemFunction* pSysFunc = new SDK_SystemFunction;
	   H264_DVR_DEVICEINFO* pDeviceInfo = new H264_DVR_DEVICEINFO;
       int nWaitTime = 5000;
	   bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,-1,(char*)pSysFunc,sizeof(SDK_SystemFunction),&dwRet,nWaitTime);

	   if (TRUE == bSuccess && sizeof(SDK_SystemFunction) == dwRet)
	   {
             bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSINFO,-1,(char*)pDeviceInfo,sizeof(H264_DVR_DEVICEINFO),&dwRet,nWaitTime);
			 if (TRUE == bSuccess && sizeof(H264_DVR_DEVICEINFO) == dwRet )
			 {
				 m_toolManagerHardDiskDlg.InitDlgInfo(pSysFunc,pDeviceInfo);
			 }
	   }

	   delete pDeviceInfo;
	   delete pSysFunc;
   }
}

void CClientDemo5Dlg::SetHardDiskInfo(SDK_StorageDeviceControl *pDiskCtl)
{   

	    int nWaitTime = 60000*5;
        
		int nRet = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_DISK_MANAGER, -1, (char *)pDiskCtl, sizeof(SDK_StorageDeviceControl),nWaitTime);
		if ( nRet >= 0)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );  
			m_toolManagerHardDiskDlg.OnUpdate();
		}
		else
		{
			switch(nRet)
			{
			case H264_DVR_NOPOWER:
				MessageBox(_CS("Error.NoPower"), _CS("OneClick.Prompt"));
				break;
			case H264_DVR_OPT_REBOOT:
				{
					CString strMsg;
					if ( pDiskCtl->iAction == SDK_STORAGE_DEVICE_CONTROL_PARTITIONS )  //分区时提示分区成功，直接重启
					{
						strMsg = _CS(_T("HDDManager.PartitionNeedReboot"));
					}else
					{
						strMsg = _CS(_T("Error.SaveSuccess"));
					}
					MessageBox(strMsg, _CS("OneClick.Prompt") );
					//if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES) //对于硬盘分区，格式化等操作需要重启时直接提示成功并且默认重启
					{
                        BOOL bSuccess = H264_DVR_ControlDVR(m_LoginID,0,5000);
						if (bSuccess)
						{
							OnBtnLogout();
						}else
						{
							MessageBox(_CS("Error.RebootFail"));
						}
					}
				}
				break;
			case H264_DVR_SDK_TIMEOUT:   //返回时如果超时，则提示超时
				{
					MessageBox(_CS("Error.Timeout"), _CS("OneClick.Prompt"));
				}
				break;
			default:
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt"));
				break;
			}
		}

}
void CClientDemo5Dlg::GetAlarmVideoAnalyseInfo()
{
	if ( 0 != m_LoginID&&m_alarmVideoAnalyse)
	{		
		m_alarmVideoAnalyse->m_LoginID=m_LoginID;
		//by dengxuefei
		m_alarmVideoAnalyse->InitWndShow();
	}
}

void CClientDemo5Dlg::GetInfoVersion()
{
	BOOL bSuccess = FALSE;
	H264_DVR_DEVICEINFO *pSysInfo = new H264_DVR_DEVICEINFO;
	if (0 != m_LoginID)
	{
		int nWaitTime = 1000;
		DWORD dwRetlen = 0;
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSINFO,-1,(char*)pSysInfo,sizeof(H264_DVR_DEVICEINFO),&dwRetlen,nWaitTime);
		if (bSuccess && dwRetlen == sizeof(H264_DVR_DEVICEINFO))
		{
			//m_netServerDlg.m_natDlg.InitDlgInfo(pNatInfoCfg);
			//InitDlgInfo
			m_InfoVersion.InitDlgInfo(pSysInfo,m_LoginID);
			delete pSysInfo;
		}
	}
}

void CClientDemo5Dlg::GetSnapStorageDlg()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_SnapshotConfigAll  *SnapshotCfgAll = new SDK_SnapshotConfigAll;
		if (!SnapshotCfgAll)
		{
			return;
		}
		int i =0;
		for(;i<m_nChannelNum;i++)
		{
			BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SNAP_STORAGE,i,
				(char *)&(SnapshotCfgAll->vSnapshotConfigAll[i]),sizeof(SDK_SnapshotConfig),&dwRetLen,nWaitTime);
			if (dwRetLen !=sizeof(SDK_SnapshotConfig) && !bSuccess)break;
		}
		if (i == m_nChannelNum)
		{
			m_SnapStorageDlg.InitDlgInfo(SnapshotCfgAll,m_nChannelNum);
		}
		if (SnapshotCfgAll)
		{
			delete SnapshotCfgAll;
			SnapshotCfgAll = NULL;
		}
	}
}

void CClientDemo5Dlg::SetSnapStorageDlg(SDK_SnapshotConfigAll *pSnapCfg)
{
	if (0 != m_LoginID && pSnapCfg != NULL)
	{
		int nWaitTime = 10000;
		int i = 0;
		BOOL bSuccess = FALSE;
		BOOL bReboot = FALSE;
		for (; i<m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SNAP_STORAGE,i,
				(char *)pSnapCfg,sizeof(SDK_SnapshotConfig),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot =TRUE;
			}
		}
		if (i == m_nChannelNum && bReboot == TRUE)
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( i == m_nChannelNum && bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}
