// TestWebDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestWeb.h"
#include "TestWebDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CTestWebDlg	*g_TestWebDlg;
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
// CTestWebDlg dialog

CTestWebDlg::CTestWebDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestWebDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestWebDlg)
	m_translateWord = _T("");
	m_screenNumb = 0;
	m_playNumb = 0;
	m_recordRoad = _T("C:\\Record");
	m_captureRoad = _T("C:\\BMP");
	m_loginTip = _T("");
	m_IP = _T("10.6.2.35");
	m_port = 34567;
	m_NAME = _T("admin");
	m_PASSWORD = _T("");
	m_TourNumb = 0;
	m_dbd = 64;
	m_ld = 64;
	m_sd = 64;
	m_bhd = 64;
	m_playNumb = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32



	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestWebDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestWebDlg)
	DDX_Control(pDX, IDC_CMB_NAME_CHANNEL, m_ChannelNameCMB);
	DDX_Control(pDX, IDC_CMB_REMOTE_CHANNEL, m_RemotRecordCMB);
	DDX_Control(pDX, IDC_STEMP_SPEED, m_ctrlPTZSpeed);
	DDX_Text(pDX, IDC_EDIT1, m_translateWord);
	DDX_Text(pDX, IDC_EDIT2, m_screenNumb);
	DDX_Text(pDX, IDC_EDIT_PLAYNUMB, m_playNumb);
	DDV_MinMaxLong(pDX, m_playNumb, 0, 32);
	DDX_Text(pDX, IDC_EDIT_RECORD_ROAD, m_recordRoad);
	DDX_Text(pDX, IDC_EDIT_CAPT_ROAD, m_captureRoad);
	DDX_Text(pDX, IDC_STATI_LOGIN_TIP, m_loginTip);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_NAME, m_NAME);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_PASSWORD);
	DDX_Text(pDX, IDC_EDIT_TOUR_LOARD, m_TourNumb);
	DDX_Text(pDX, IDC_EDIT_DBD, m_dbd);
	DDX_Text(pDX, IDC_EDIT_LD, m_ld);
	DDX_Text(pDX, IDC_EDIT_SD, m_sd);
	DDX_Text(pDX, IDC_EDIT_BHD, m_bhd);
	//}}AFX_DATA_MAP


	DDX_Control(pDX, IDC_WEBCTRL1, m_ocx);
}

BEGIN_MESSAGE_MAP(CTestWebDlg, CDialog)
	//{{AFX_MSG_MAP(CTestWebDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfig)
	ON_BN_CLICKED(IDC_BTN_CLIENT_CONFIG, OnBtnClientConfig)
	ON_BN_CLICKED(IDC_BTN_LOG, OnBtnLog)
	ON_BN_CLICKED(IDC_BTN_FULL_SCREEN, OnBtnFullScreen)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_MORE_SCREEN, OnBtnMoreScreen)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PLAYSTOP, OnBtnPlaystop)
	ON_BN_CLICKED(IDC_BTN_RECORD, OnBtnRecord)
	ON_BN_CLICKED(IDC_BTN_STOPRECORD, OnBtnStoprecord)
	ON_BN_CLICKED(IDC_BTN_CAPTURE, OnBtnCapture)
	ON_BN_CLICKED(IDC_BTN_STARTSOUND, OnBtnStartsound)
	ON_BN_CLICKED(IDC_BTN_STOP_SOUND, OnBtnStopSound)
	ON_EN_CHANGE(IDC_EDIT_RECORD_ROAD, OnChangeEditRecordRoad)
	ON_BN_CLICKED(IDC_BTN_STARTTALK, OnBtnStarttalk)
	ON_BN_CLICKED(IDC_BTN_STOPTALK, OnBtnStoptalk)
	ON_BN_CLICKED(IDC_BUTTON_PRESET, OnButtonPreset)
	ON_BN_CLICKED(IDC_BUTTON_GOPRESET, OnButtonGopreset)
	ON_BN_CLICKED(IDC_BUTTON_TOUR, OnButtonTour)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_TOUR, OnButtonEditTour)
	ON_BN_CLICKED(IDC_BUTTON_GETCOLOR, OnButtonGetcolor)
	ON_BN_CLICKED(IDC_BUTTON_SETCOLOR, OnButtonSetcolor)
	ON_BN_CLICKED(IDC_LOGOUT, OnLogout)
	ON_BN_CLICKED(IDC_BUTTON_PLAYALL, OnButtonPlayall)
	ON_BN_CLICKED(IDC_BUTTON_STOPALLPLAY, OnButtonStopallplay)
	ON_BN_CLICKED(IDC_BUTTON_RECORDALL, OnButtonRecordall)
	ON_BN_CLICKED(IDC_BUTTON_STOPRECORDALL, OnButtonStoprecordall)
	ON_BN_CLICKED(IDC_BTN_RECORDBYCHANNEL, OnBtnRecordbychannel)
	ON_BN_CLICKED(IDC_BTN_STOP_RECORDBYCHANNEL, OnBtnStopRecordbychannel)
	ON_BN_CLICKED(IDC_REBOOT, OnReboot)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK, OnBtnPlayback)
	ON_BN_CLICKED(IDC_BT_START_REMOT_RECORD, OnBtStartRemotRecord)
	ON_BN_CLICKED(IDC_BT_STOP_REMOT_RECORD, OnBtStopRemotRecord)
	ON_BN_CLICKED(IDC_BT_GETCHANNELNAME, OnBtGetchannelname)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_DELETE_PRESET, OnButtonDeletePreset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestWebDlg message handlers

BOOL CTestWebDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	
	//m_ocx.SetPassPort(1234);
	
	UpdateData(FALSE);

	g_TestWebDlg=this;
	// TODO: Add extra initialization here
	VERIFY(PTZCtrlButton[0].SubclassDlgItem(IDC_BT_UP, this));
	PTZCtrlButton[0].m_iTypeButton = 0;
	VERIFY(PTZCtrlButton[1].SubclassDlgItem(IDC_BT_DOWN, this));
	PTZCtrlButton[1].m_iTypeButton = 1;
	VERIFY(PTZCtrlButton[2].SubclassDlgItem(IDC_BT_LEFT, this));
	PTZCtrlButton[2].m_iTypeButton = 2;
	VERIFY(PTZCtrlButton[3].SubclassDlgItem(IDC_BT_RIGHT, this));
	PTZCtrlButton[3].m_iTypeButton = 3;
	VERIFY(PTZCtrlButton[13].SubclassDlgItem(IDC_BT_LEFTUP, this));
	PTZCtrlButton[13].m_iTypeButton = 4;
	VERIFY(PTZCtrlButton[15].SubclassDlgItem(IDC_BT_LEFTDOWN, this));
	PTZCtrlButton[15].m_iTypeButton = 5;
	VERIFY(PTZCtrlButton[14].SubclassDlgItem(IDC_BT_RIGHTUP, this));
	PTZCtrlButton[14].m_iTypeButton = 6;
	VERIFY(PTZCtrlButton[16].SubclassDlgItem(IDC_BT_RIGHTDOWN, this));
	PTZCtrlButton[16].m_iTypeButton = 7;
	VERIFY(PTZCtrlButton[5].SubclassDlgItem(IDC_BT_ZOOMOUT, this));
	PTZCtrlButton[5].m_iTypeButton = 8;
	VERIFY(PTZCtrlButton[4].SubclassDlgItem(IDC_BT_ZOOMIN, this));
	PTZCtrlButton[4].m_iTypeButton = 9;
	VERIFY(PTZCtrlButton[7].SubclassDlgItem(IDC_BT_FOCUSFAR, this));
	PTZCtrlButton[7].m_iTypeButton = 10;
	VERIFY(PTZCtrlButton[6].SubclassDlgItem(IDC_BT_FOCUSNEAR, this));
	PTZCtrlButton[6].m_iTypeButton = 11;
	VERIFY(PTZCtrlButton[8].SubclassDlgItem(IDC_BT_IRISOPEN, this));
	PTZCtrlButton[8].m_iTypeButton = 12;
	VERIFY(PTZCtrlButton[9].SubclassDlgItem(IDC_BT_IRISCLOSE, this));
	PTZCtrlButton[9].m_iTypeButton = 13;
	
	


	int i = 0;
	for(; i < 32; i++)
	{
		CString tempStr;
		tempStr.Format("通道%02d",i + 1);
		m_RemotRecordCMB.AddString(tempStr);
		m_ChannelNameCMB.AddString(tempStr);	
	}
	for(i=1;i<=8;i++)
	{
		CString str;
		str.Format("%d",i);
		m_ctrlPTZSpeed.AddString(str);
	}
	m_ctrlPTZSpeed.SetCurSel(0);
	m_RemotRecordCMB.SetCurSel(0);
	m_ChannelNameCMB.SetCurSel(0);
	UpdateData(FALSE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestWebDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestWebDlg::OnPaint() 
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
HCURSOR CTestWebDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestWebDlg::OnOK() 
{
	// TODO: Add extra validation here
		UpdateData();
		if(0!=m_ocx.Login(m_IP,m_port,m_NAME,m_PASSWORD))
		{
			m_loginTip="Login success";
		}
	//CDialog::OnOK();
}

void CTestWebDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString str=m_ocx.Translate(m_translateWord);
	MessageBox(str);
	
}

void CTestWebDlg::OnBtnConfig() 
{
	// TODO: Add your control notification handler code here
	m_ocx.ShowDeviceConfig();
	
}

void CTestWebDlg::OnBtnClientConfig() 
{
	// TODO: Add your control notification handler code here
	m_ocx.ShowClientConfig();
	
}

void CTestWebDlg::OnBtnLog() 
{
	// TODO: Add your control notification handler code here
	m_ocx.ShowLog();
	
}

void CTestWebDlg::OnBtnFullScreen() 
{
	// TODO: Add your control notification handler code here
	m_ocx.Fullscreen(TRUE);
	//SetTimer(101,3000,NULL);

}

void CTestWebDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(101);
	m_ocx.Fullscreen(FALSE);
	
	CDialog::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CTestWebDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTestWebDlg)
	ON_EVENT(CTestWebDlg, IDC_WEBCTRL1, 1 /* RButtonDown */, OnRButtonDownWebctrl1, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CTestWebDlg, IDC_WEBCTRL1, 3 /* AllChannelCtrl */, OnAllChannelCtrlWebctrl1, VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTestWebDlg::OnRButtonDownWebctrl1(long nFlag, long x, long y) 
{
	// TODO: Add your control notification handler code here
	m_ocx.Fullscreen(FALSE);
	
}

void CTestWebDlg::OnBtnMoreScreen() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_ocx.ChangeShowWndNum(m_screenNumb,true,0,0);
	
}

void CTestWebDlg::OnBtnPlay() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_ocx.StartRealPlay(m_playNumb,0,0);
	
}

void CTestWebDlg::OnBtnPlaystop() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_ocx.StopChannelRealPlay(m_playNumb);
	
}

void CTestWebDlg::OnBtnRecord() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	long nChannel=m_ocx.GetCurChannel();
	m_ocx.StartChannelRecord(nChannel,m_recordRoad,2);
	
}

void CTestWebDlg::OnBtnStoprecord() 
{
	// TODO: Add your control notification handler code here
	long nChannel=m_ocx.GetCurChannel();
	m_ocx.StopChannelRecord(nChannel);
	
}

void CTestWebDlg::OnBtnCapture() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int nChannel=m_ocx.GetCurChannel();
	m_ocx.BMPChannelCapturePicture(nChannel,m_captureRoad);

}

void CTestWebDlg::OnBtnStartsound() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_ocx.OpenChannelSound(m_playNumb,1);
	
}

void CTestWebDlg::OnBtnStopSound() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_ocx.CloseChannelSound(m_playNumb,1);
	
}

void CTestWebDlg::OnChangeEditRecordRoad() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CTestWebDlg::OnBtnStarttalk() 
{
	// TODO: Add your control notification handler code here
	m_ocx.StartTalk();
	
}

void CTestWebDlg::OnBtnStoptalk() 
{
	// TODO: Add your control notification handler code here
	m_ocx.StopTalk();
	
}
// static int index=0;
// void CTestWebDlg::OnButtonPtzup() 
// {
// 	// TODO: Add your control notification handler code here
// 
// 	m_ocx.PTZCtrlStart(-1,index++,5);
// 	if(index>14)
// 		index=0;
// 
// 	
// }
// 
// void CTestWebDlg::OnButtonPtzdown() 
// {
// 	// TODO: Add your control notification handler code here
// 	int nChannel=m_ocx.GetCurChannel();
// 	m_ocx.PTZCtrlStop(nChannel,index++,5);
// 	if(index>14)
// 		index=0;
// 	
// }

void CTestWebDlg::OnButtonPreset() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int nChannel=m_ocx.GetCurChannel();
	m_ocx.PTZCtrlSetPreset(nChannel,m_TourNumb,true);
	
}

void CTestWebDlg::OnButtonGopreset() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int nChannel=m_ocx.GetCurChannel();
	m_ocx.PTZCtrlGotoPreset(nChannel,m_TourNumb);
	
}
bool gtour=true;
void CTestWebDlg::OnButtonTour() 
{
	UpdateData();
	int nChannel=m_ocx.GetCurChannel();
	m_ocx.PTZCtrlTour(nChannel,m_TourNumb,gtour);
	if(gtour)
	{
		MessageBox("开始巡航");
		gtour=false;
	}
	else
	{
		MessageBox("停止巡航");
		gtour=true;
	}
	// TODO: Add your control notification handler code here
	
}

void CTestWebDlg::OnButtonEditTour() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_ocx.PTZEditTure(m_TourNumb);
	
}

void CTestWebDlg::OnButtonGetcolor() 
{
	// TODO: Add your control notification handler code here
	CString color=m_ocx.GetColor();
	MessageBox(color);

	int i=0;
	int j=0;
	CString temp=color.Left(j=color.Find(','));
	m_ld=atoi(temp.GetBuffer(0));
	i=j;
	

	temp=color.Left(j=color.Find(',',i+1));
	temp=temp.Right(temp.GetLength()-temp.ReverseFind(',')-1);
	m_dbd=atoi(temp.GetBuffer(0));
	i=j;
	

	temp=color.Left(j=color.Find(',',i+1));
	temp=temp.Right(temp.GetLength()-temp.ReverseFind(',')-1);
	m_bhd=atoi(temp.GetBuffer(0));
	
	temp=color.Right(color.GetLength()-color.ReverseFind(',')-1);
	m_sd=atoi(temp.GetBuffer(0));
	


	UpdateData(FALSE);
}

void CTestWebDlg::OnButtonSetcolor() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int nChannel=m_ocx.GetCurChannel();
	if(m_ocx.SetColor(nChannel,m_ld,m_dbd,m_bhd,m_sd))
	{
		MessageBox("set Ok!");
	}

	
}

void CTestWebDlg::OnLogout() 
{
	// TODO: Add your control notification handler code here
	if(m_ocx.Logout())
	{
		m_loginTip="";
	}
	UpdateData(FALSE);
	
}

void CTestWebDlg::OnButtonPlayall() 
{
	// TODO: Add your control notification handler code here
	m_ocx.StartPlayAll();
	
}

void CTestWebDlg::OnButtonStopallplay() 
{
	// TODO: Add your control notification handler code here
	m_ocx.StopRealPlayAll();
	
}

void CTestWebDlg::OnButtonRecordall() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	//m_ocx.StartRecordAll(m_recordRoad,2);
	m_ocx.StartRecordAllChannel(m_recordRoad,2);
}

void CTestWebDlg::OnButtonStoprecordall() 
{
	// TODO: Add your control notification handler code here
	m_ocx.StopRecordAllChannel();
	
}

void CTestWebDlg::OnBtnRecordbychannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_ocx.StartChannelRecord(m_playNumb,m_recordRoad,2);
	
}

void CTestWebDlg::OnBtnStopRecordbychannel() 
{
	UpdateData();
	m_ocx.StopChannelRecord(m_playNumb);
	// TODO: Add your control notification handler code here
	
}

void CTestWebDlg::OnAllChannelCtrlWebctrl1(BOOL bPlay, BOOL bStopPlay, BOOL bRecord, BOOL bStopRecord) 
{
	// TODO: Add your control notification handler code here
	if(bPlay)
	{
		MessageBox("allPlay");
	}
	if(bStopPlay)
	{
		MessageBox("stopPlay");
	}
	if(bRecord)
	{
		MessageBox("startRecord");
	}
	if(bStopRecord)
	{
		MessageBox("stopRecord");
	}
	
	
}

void CTestWebDlg::OnReboot() 
{
	// TODO: Add your control notification handler code here
	m_ocx.RebootServer();
	
}


void CTestWebDlg::OnBtnPlayback() 
{
	// TODO: Add your control notification handler code here
	m_ocx.ShowPlayBack();
	
}



void CTestWebDlg::OnBtStartRemotRecord() 
{
	// TODO: Add your control notification handler code here
	m_ocx.StartRemoteRecord(m_RemotRecordCMB.GetCurSel());
	
}

void CTestWebDlg::OnBtStopRemotRecord() 
{
	// TODO: Add your control notification handler code here
	m_ocx.StopRemoteRecord(m_RemotRecordCMB.GetCurSel());
	
}

void CTestWebDlg::OnBtGetchannelname() 
{
	UpdateData();
	CString allNameStr=m_ocx.GetChannelName();
	int nChannel=m_ChannelNameCMB.GetCurSel();

	char buff[600];
	memset(buff,0,600);
	memcpy(buff,allNameStr.GetBuffer(0),allNameStr.GetLength()+1);

	char name[40];
	memset(name,0,40);
	int keyindex=0;
	bool key=false;
	int ChannelNumCount=0;

	for(int i=0;i<allNameStr.GetLength();i++)
	{
		if(buff[i]==16)
		{
			if(true==key)
			{
				break;
			}		

		}
		if(buff[i]==9)
		{
			
			if(ChannelNumCount==nChannel)
			{
				key=true;
			}
			ChannelNumCount++;
			continue;
		}
		if(key==true)
		{
			name[keyindex++]=buff[i];
		}
	}
	MessageBox(name);


	
}



void CTestWebDlg::OnButtonDeletePreset() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int nChannel=m_ocx.GetCurChannel();
	m_ocx.PTZCtrlSetPreset(nChannel,m_TourNumb,false);
	
}
