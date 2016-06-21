// ClientDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "ClientDemoDlg.h"
#include "RemotePlaybackDlg.h"
#include "DeviceEdit.h"
#include "Markup.h"
#include "DeviceEditDlg.h"
#include "PTZDlg.h"
#include "CruiseEdit.h"
#include "TabPlayback.h"
/*#include "..\\bin\\NetSdk.h"*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
SocketStyle g_connectType=TCPSOCKET;
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
// CClientDemoDlg dialog

CClientDemoDlg::CClientDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDemoDlg)
	m_bActiveConnect = FALSE;
	m_bUdpConnect = FALSE;	
	m_bTcpConnect = true;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nCurIndex = -1;
	m_nTotalWnd = 4;	//the default number of windows is 4
	memset(&m_devInfo, 0, sizeof(DEV_INFO));
	
}

void CClientDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemoDlg)
	DDX_Control(pDX, IDC_COMBOWNDNUM, m_cmbWnd);
	DDX_Check(pDX, IDC_CHECK_ACTIVE_CONNECT, m_bActiveConnect);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DEVICE, OnBtnDevice)
	ON_BN_CLICKED(IDC_BTN_PTZ, OnBtnPtz)
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK, OnBtnPlayback)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_CAPTURE, OnBtnCapture)
	ON_CBN_SELCHANGE(IDC_COMBOWNDNUM, OnSelchangeCombowndnum)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_DEV_KEYBOARD, OnBtnDevKeyboard)
	ON_BN_CLICKED(IDC_BTN_NET_ALARM, OnBtnNetAlarm)
	ON_BN_CLICKED(IDC_CHECK_ACTIVE_CONNECT, OnCheckActiveConnect)

	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemoDlg message handlers

BOOL CClientDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	Dlg.Create(IDD_CRUISEEDIT,this);
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

	m_devDLg.Create(CDeviceEditDlg::IDD, this);
	m_devDLg.ShowWindow(SW_SHOW);
	m_colorDLg.Create(CColorDlg::IDD, this);
	m_ptzDLg.Create(CPTZDlg::IDD, this);
	m_kbDLg.Create(CDialogKeyBoard::IDD, this);
	m_NetAlarmDlg.Create(CNetAlarmDlg::IDD, this);
	m_cmbWnd.SetCurSel(1);

	for ( int i = 0; i < MAXWNDNUM; i ++ )
	{
		m_videoWnd[i].Create(CVideoWnd::IDD, this);
		m_videoWnd[i].SetWndIndex(i);
	}

	//initialize the SDK
	InitSDK();

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int width2 = height * 4 / 3;
	if (width2 < width)
	{
		MoveWindow(0, 0, width2, height-30);
	}
	else if(width2 > width)
	{
		int height2 = width * 3 / 4;
		MoveWindow(0, 0, width, height2-30);
	}
	else
	{
		MoveWindow(0, 0, width, height);
	}

	ArrayWindow(4);
	SetActiveWnd(0);

	CRect rect;
	GetClientRect(&rect);
	
	CRect btnRect;
	GetDlgItem(IDC_BTN_DEVICE)->GetClientRect(&btnRect);
	int nBtnWidth = btnRect.Width();
	int nBtnHeigth = btnRect.Height();

	CRect moveRect, tmpRect; 
	moveRect.top = rect.bottom - (int)rect.Height()*0.198;
	moveRect.left = rect.right - (int)rect.Width()*0.234375;
	moveRect.bottom = moveRect.top + nBtnHeigth;
	moveRect.right = moveRect.left + nBtnWidth;
	GetDlgItem(IDC_BTN_DEVICE)->MoveWindow(moveRect);

	tmpRect = moveRect;
	tmpRect.left += nBtnWidth;
	tmpRect.right += nBtnWidth;
	GetDlgItem(IDC_BTN_PTZ)->MoveWindow(tmpRect);

	moveRect.top += nBtnHeigth;
	moveRect.bottom += nBtnHeigth;
	GetDlgItem(IDC_BTN_COLOR)->MoveWindow(moveRect);
	
	tmpRect = moveRect;
	tmpRect.left += nBtnWidth;
	tmpRect.right += nBtnWidth;
	GetDlgItem(IDC_BTN_PLAYBACK)->MoveWindow(tmpRect);

	moveRect.top += nBtnHeigth;
 	moveRect.bottom += nBtnHeigth;
	GetDlgItem(IDC_BTN_DEV_KEYBOARD)->MoveWindow(moveRect);

	tmpRect = moveRect;
	tmpRect.left += nBtnWidth;
 	tmpRect.right += nBtnWidth;
	GetDlgItem(IDC_BTN_NET_ALARM)->MoveWindow(tmpRect);

	tmpRect = moveRect;
	tmpRect.left += nBtnWidth;
	tmpRect.right += nBtnWidth;
	


	CRect dlgRect;
	dlgRect.top = 0;
	dlgRect.left = tmpRect.left-btnRect.Width() ;
	dlgRect.bottom = rect.bottom - (int)rect.Height()*0.205;
	dlgRect.right = rect.right;

	m_devDLg.MoveWindow(dlgRect);
	m_colorDLg.MoveWindow(dlgRect);
	m_ptzDLg.MoveWindow(dlgRect);
	m_kbDLg.MoveWindow(dlgRect);
	m_NetAlarmDlg.MoveWindow(dlgRect);

	moveRect.top = rect.bottom - 54;
	moveRect.bottom = rect.bottom-30;
	moveRect.left = 10;
	moveRect.right = moveRect.left + 60;
	GetDlgItem(IDC_STATIC_CMBWND)->MoveWindow(moveRect);

 	moveRect.left = moveRect.right;
 	moveRect.right += nBtnWidth;
	GetDlgItem(IDC_COMBOWNDNUM)->MoveWindow(moveRect);

	moveRect.left = moveRect.right;
	moveRect.right += nBtnWidth;
	GetDlgItem(IDC_BTN_CAPTURE)->MoveWindow(moveRect);

	moveRect.left = moveRect.right;
	moveRect.right += nBtnWidth;
	GetDlgItem(IDC_BTN_SAVE)->MoveWindow(moveRect);

	moveRect.left = moveRect.right+5;
	moveRect.right += nBtnWidth;
	GetDlgItem(IDC_CHECK_ACTIVE_CONNECT)->MoveWindow(moveRect);
	

	CRect rectt;      
	GetClientRect(&rect);     //取客户区大小    
	old.x=rect.right-rect.left;  
	old.y=rect.bottom-rect.top;  

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDemoDlg::OnPaint() 
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
HCURSOR CClientDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//message callback function
bool __stdcall MessCallBack(long lLoginID, char *pBuf,
							unsigned long dwBufLen, long dwUser)
{
		CClientDemoDlg *pThis = (CClientDemoDlg *)dwUser;
			pThis->DealwithAlarm(lLoginID, pBuf, dwBufLen);
		return true;
}

//device disconnect callback
void __stdcall DisConnectBackCallFunc(LONG lLoginID, char *pchDVRIP, 
									  LONG nDVRPort, DWORD dwUser)
{
	CClientDemoDlg* pThis = (CClientDemoDlg*)dwUser;
	if (pThis == NULL)
	{
		ASSERT( FALSE );
		return ;
	}
	pThis->ReConnect(lLoginID, pchDVRIP, nDVRPort);
}

//initialize the SDK
BOOL CClientDemoDlg::InitSDK()
{
	//initialize
	BOOL bResult = H264_DVR_Init((fDisConnect)DisConnectBackCallFunc,(DWORD)this);

	//he messages received in SDK from DVR which need to upload， such as alarm information，diary information，may do through callback function
		H264_DVR_SetDVRMessCallBack(MessCallBack,(DWORD)this);
		 
	H264_DVR_SetConnectTime(5000, 3);

	return bResult;
}

BOOL CClientDemoDlg::ExitSDk()
{
	H264_DVR_Cleanup();

	return true;
}

void CClientDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	ExitSDk();
}



//Device Config Window 
void CClientDemoDlg::OnBtnDevice() 
{
	m_devDLg.ShowWindow(SW_SHOW);
	m_colorDLg.ShowWindow(SW_HIDE);
	m_ptzDLg.ShowWindow(SW_HIDE);
	m_kbDLg.ShowWindow(SW_HIDE);
	m_NetAlarmDlg.ShowWindow(SW_HIDE);
}

//PTZ Config Window
void CClientDemoDlg::OnBtnPtz() 
{
	m_devDLg.ShowWindow(SW_HIDE);
	m_colorDLg.ShowWindow(SW_HIDE);
	m_ptzDLg.ShowWindow(SW_SHOW);
	m_kbDLg.ShowWindow(SW_HIDE);
	m_NetAlarmDlg.ShowWindow(SW_HIDE);
}


//Color Config Window
void CClientDemoDlg::OnBtnColor() 
{
	m_devDLg.ShowWindow(SW_HIDE);
	m_colorDLg.ShowWindow(SW_SHOW);
	m_ptzDLg.ShowWindow(SW_HIDE);
	m_kbDLg.ShowWindow(SW_HIDE);
	m_NetAlarmDlg.ShowWindow(SW_HIDE);
}

void CClientDemoDlg::OnBtnDevKeyboard() 
{
	// TODO: Add your control notification handler code here
	m_devDLg.ShowWindow(SW_HIDE);
	m_colorDLg.ShowWindow(SW_HIDE);
	m_ptzDLg.ShowWindow(SW_HIDE);
	m_kbDLg.ShowWindow(SW_SHOW);
	m_NetAlarmDlg.ShowWindow(SW_HIDE);
}

void CClientDemoDlg::OnBtnNetAlarm() 
{
	// TODO: Add your control notification handler code here
	m_devDLg.ShowWindow(SW_HIDE);
	m_colorDLg.ShowWindow(SW_HIDE);
	m_ptzDLg.ShowWindow(SW_HIDE);
	m_kbDLg.ShowWindow(SW_HIDE);
	m_NetAlarmDlg.m_pDevInfo = &m_devInfo;
	m_NetAlarmDlg.ShowWindow(SW_SHOW);	
}

//Playback Config Window
void CClientDemoDlg::OnBtnPlayback() 
{
	CTabPlayback dlg;
	dlg.DoModal();
}


void CClientDemoDlg::ArrayWindow(WORD iNumber)
{
	m_nTotalWnd = iNumber;

	int i = 0;
	CRect Rect;
	GetClientRect(&Rect);
	WORD iWidth,iHeight;

	int nFullWidth=Rect.Width();
	int nFullHeight=Rect.Height();
	iWidth = (int) nFullWidth*0.75515625;
	iHeight = (int)nFullHeight*0.91;
	for (i = 0;i < MAXWNDNUM;i++)
	{
		m_videoWnd[i].ShowWindow(SW_HIDE);
	}
	
	int nNull = 3;	

	switch(iNumber)
	{
	case 1:
		m_videoWnd[0].MoveWindow(3 + 0, 0, iWidth, iHeight);
		m_videoWnd[0].ShowWindow(SW_SHOW);
		break;
	case 4:
		for(i = 0; i < 2; i++)
		{
			m_videoWnd[i].MoveWindow( 3 + i * (iWidth / 2) + i * nNull , 0, (iWidth / 2), iHeight / 2);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		for(i = 2; i < 4; i++)
		{
			m_videoWnd[i].MoveWindow(3 + (i - 2) * (iWidth / 2) + (i - 2) * nNull, iHeight / 2 + nNull, (iWidth / 2), iHeight / 2);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		break;
	case 9:
		for (i=0;i<3;i++)
		{
			m_videoWnd[i].MoveWindow(3 + i * (iWidth / 3) + i * nNull, 0, (iWidth / 3), iHeight / 3);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		for (i=3;i<6;i++)
		{
			m_videoWnd[i].MoveWindow(3 +(i - 3) * (iWidth / 3) + (i - 3) * nNull, iHeight / 3 + nNull, (iWidth / 3), iHeight / 3);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		for (i=6;i<9;i++)
		{
			m_videoWnd[i].MoveWindow(3 + (i - 6) * (iWidth / 3) + (i - 6) * nNull, 2 * iHeight / 3 + 2 * nNull ,(iWidth / 3), iHeight / 3);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		break;
	case 16:
		for(i = 0; i < 4; i++)
		{
			m_videoWnd[i].MoveWindow(3 + i * (iWidth / 4) + (i) * nNull, 0, (iWidth / 4), iHeight / 4);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		for(i = 4; i < 8; i++)
		{
			m_videoWnd[i].MoveWindow(3 +(i - 4) * (iWidth / 4) + (i - 4) * nNull, iHeight / 4 + nNull, (iWidth / 4), iHeight / 4);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		for(i = 8; i < 12; i++)
		{
			m_videoWnd[i].MoveWindow(3 +(i - 8) * (iWidth / 4) + (i - 8) * nNull, iHeight / 2 + 2 * nNull, (iWidth / 4), iHeight / 4);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		for(i = 12; i < 16; i++)
		{
			m_videoWnd[i].MoveWindow(3 +(i - 12) * (iWidth / 4) + (i - 12) * nNull, 3 * iHeight / 4 + 3 * nNull, (iWidth / 4), iHeight / 4);
			m_videoWnd[i].ShowWindow(SW_SHOW);
		}
		break;
	default:
		break;
	}
}

// void CClientDemoDlg::OnSize(UINT nType, int cx, int cy)             
// {
// 	CDialog::OnSize(nType, cx, cy);
// }

void CClientDemoDlg::SetActiveWnd(int nIndex)
{
	if ( -1 != m_nCurIndex )
	{
		DrawActivePage(FALSE);  //InvalidateRect
	}

	m_nCurIndex = nIndex;

	DrawActivePage(TRUE);
	
	SetColor(m_nCurIndex);
}

void CClientDemoDlg::SetColor( int nIndex )
{
	long nBright = 0;
	long nHue = 0;
	long nSaturation = 0;
	long nContrast = 0;

	long lPlayHandle = m_videoWnd[m_nCurIndex].GetHandle();
	if ( lPlayHandle <= 0 )
	{
		return;
	}
	m_videoWnd[nIndex].GetColor(&nBright, &nContrast, &nSaturation, &nHue);
	m_colorDLg.SetColor(nBright, nContrast, nSaturation, nHue);
}

void CClientDemoDlg::SetColor(DWORD nBright, DWORD nContrast, DWORD nSaturation, DWORD nHue)
{
	long lPlayHandle = m_videoWnd[m_nCurIndex].GetHandle();
	if ( lPlayHandle <= 0 )
	{
		return;
	}
	m_videoWnd[m_nCurIndex].SetColor(nBright, nContrast, nSaturation, nHue);
	SetDevChnColor(nBright, nContrast, nSaturation, nHue);
}

void CClientDemoDlg::DrawActivePage(BOOL bActive)
{
	CRect rt;
	m_videoWnd[m_nCurIndex].GetWindowRect(&rt);
	ScreenToClient(&rt);
	
	if ( !bActive )
		InvalidateRect(&rt);		
	else
	{
		CDC *pDC = NULL;	
		pDC=GetDC();
		if (!pDC) 
		{
			return;
		}
		
		pDC->Draw3dRect(&rt, RGB(255,255,0), RGB(255,255,0)); 
		ReleaseDC(pDC);
	}
}



void CClientDemoDlg::OnBtnCapture() 
{
	//get handle of current playing window
	long lPlayHandle = m_videoWnd[m_nCurIndex].GetHandle();
	if ( lPlayHandle <= 0 )
	{
		return;
	}

	char cFilename[256];

#if 1
	CTime time = CTime::GetCurrentTime();
	sprintf(cFilename, "%s\\Picture\\%4d%02d%02d_%02d%02d%02d.bmp", 
		"c:", 
		time.GetYear(), 
		time.GetMonth(), 
		time.GetDay(), 
		time.GetHour(), 
		time.GetMinute(), 
		time.GetSecond());

	
	if ( H264_DVR_LocalCatchPic(m_videoWnd[m_nCurIndex].m_iPlayhandle, cFilename) )		
	{
		Sleep(50);
		HINSTANCE hinstance=ShellExecute(m_hWnd, "open" ,cFilename, 
			NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		MessageBox(_CS("Desktop.SnapshotFail"));
	}
#else
	CTime time = CTime::GetCurrentTime();
	sprintf(cFilename, "%s\\Picture\\%4d%02d%02d_%02d%02d%02d.jpg", 
		"c:", 
		time.GetYear(), 
		time.GetMonth(), 
		time.GetDay(), 
		time.GetHour(), 
		time.GetMinute(), 
		time.GetSecond());
	if ( H264_DVR_CatchPic(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel, cFilename) )
	{
		Sleep(50);
		HINSTANCE hinstance=ShellExecute(m_hWnd, "open" ,cFilename, 
			NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		MessageBox(_CS("Desktop.SnapshotFail"));
	}
#endif
}

void CClientDemoDlg::OnSelchangeCombowndnum() 
{
	UpdateData();

	int nWndNum = 4;
	if ( m_cmbWnd.GetCurSel() == 0 )
	{
		nWndNum = 1;
	}
	else if ( m_cmbWnd.GetCurSel() == 1 )
	{
		nWndNum = 4;
	}
	else if ( m_cmbWnd.GetCurSel() == 2 )
	{
		nWndNum = 9;
	}
	else if ( m_cmbWnd.GetCurSel() == 3 )
	{
		nWndNum = 16;
	}
	ArrayWindow(nWndNum);
}


int CClientDemoDlg::Connect(DEV_INFO *pDev, int nChannel, int nWndIndex /* = -1 */)
{
	int nRet = 0;

	if ( !pDev )
	{
		return nRet;
	}

	//if device did not login,login first
	if ( pDev->lLoginID <= 0 )
	{
		H264_DVR_DEVICEINFO OutDev;
		int nError = 0;
		//设置尝试连接设备次数和等待时间
		H264_DVR_SetConnectTime(3000, 1);//设置尝试连接1次，等待时间3s
//		H264_DVR_SetLocalBindAddress("10.2.55.25");	
		UpdateData();
		long lLogin=0;
		
		lLogin = H264_DVR_Login(pDev->szIpaddress, pDev->nPort, pDev->szUserName, pDev->szPsw,
			&OutDev, &nError,(SocketStyle)pDev->devctype);
		
		
		if ( lLogin <= 0 )
		{
			CString sTemp;	
			int nErr = H264_DVR_GetLastError();  
			if(nErr == H264_DVR_PASSWORD_NOT_VALID)
			{
				MessageBox(_CS("Error.PwdErr"));
			}
			else
			{
				MessageBox(_CS("Error.NotFound"));
			}

			return nRet;
		}

		pDev->lLoginID = lLogin;
		H264_DVR_SetupAlarmChan(lLogin);
	}

	int nWnd = m_nCurIndex;
	if ( nWndIndex >= 0 )
	{
		nWnd = nWndIndex;
	}
	
	if ( nWnd >= m_nTotalWnd )
	{
		return nRet ;
	}
		
		return m_videoWnd[nWnd].ConnectRealPlay(pDev, nChannel);	
	
}


void CClientDemoDlg::PtzControl(DWORD dwBtn, bool dwStop, int nSpeed)
{
	//get handle of current playing window
	long lPlayHandle = m_videoWnd[m_nCurIndex].GetHandle();
	if ( lPlayHandle <= 0 )
	{
		return;
	}

	// TODO: Add your message handler code here and/or call default
	switch(dwBtn)
	{
	case 0:        //PTZ up
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel, TILT_UP, dwStop,nSpeed))
		{
			AfxMessageBox(_CS("AccountMSG.Failed"));
		}
		break;
	case 1:			//PTZ down
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,TILT_DOWN,dwStop,nSpeed))
			AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 2:			//PTZ left
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,PAN_LEFT,dwStop,nSpeed))
			AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 3:			//PTZ right
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,PAN_RIGHT,dwStop,nSpeed))
			AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 4:         //Zoom In
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,ZOOM_IN_1,dwStop,nSpeed))
			//AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 5:			//Zoom Out
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,ZOOM_OUT_1,dwStop,nSpeed))
		{}
			//AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 6:			//Focus Near
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,FOCUS_NEAR,dwStop,nSpeed))
		{}
			//AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 7:			//Focus Far
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,FOCUS_FAR,dwStop,nSpeed))
		{}
			//AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 8:			//Iris Open
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,IRIS_OPEN,dwStop,nSpeed))
		{}
			//AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 9:			//Iris Close
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,IRIS_CLOSE,dwStop,nSpeed))
		{}
			//AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 10:			//PTZ right top
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,PAN_RIGTHTOP,dwStop,nSpeed))
			AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 11:			//PTZ left down
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,PAN_LEFTDOWN,dwStop,nSpeed))
			AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 12:			//PTZ left top
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,PAN_LEFTTOP,dwStop,nSpeed))
			AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 13:			//PTZ right down
		if(!H264_DVR_PTZControl(m_videoWnd[m_nCurIndex].m_lLogin, 
			m_videoWnd[m_nCurIndex].m_iChannel,PAN_RIGTHDOWN,dwStop,nSpeed))
			AfxMessageBox(_CS("AccountMSG.Failed"));
		break;
	case 14:			//Point Move 
		{
			long num=m_ptzDLg.m_present.GetCurSel();
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin,m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_POINT_MOVE_CONTROL,num+1,2, 3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
			break;
		}
		
	case 15:			//Point Set 
		{
			long num=m_ptzDLg.m_present.GetCurSel();
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin, m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_POINT_SET_CONTROL,num+1,2,3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
			break;
		}
	case 16:			//Point Delete
		{
			long num=m_ptzDLg.m_present.GetCurSel();
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin, m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_POINT_DEL_CONTROL,num+1,2,3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
			break;
		}
	case 17:			//Begin Point Loop
		{
			
			long num=Dlg.cruise_edit;
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin, m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_POINT_LOOP_CONTROL,num,1,3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
				break;
		}
	case 18:			//Stop Point Loop
		{
			long num=m_ptzDLg.m_ComboCruise.GetCurSel();
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin, m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_POINT_STOP_LOOP_CONTROL,num+1,2,3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
			break;
		}
	case 19:			//Show the Cruise Edit Dialog
		{	
			Dlg.cruise_edit=m_ptzDLg.m_ComboCruise.GetCurSel()+1;
			CString temp;
			temp.Format("%d",m_ptzDLg.m_ComboCruise.GetCurSel()+1);
			Dlg.m_edit_cruise.SetWindowText(temp);
			Dlg.ShowWindow(SW_SHOW);
			break;
		}

	case 86:			//Add Point To Loop
		{
			long num=Dlg.m_cruisepresent.GetCurSel()+1;
			long num2=Dlg.cruise_edit;
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin, m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_ADDTOLOOP,num2,num,3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
			break;
		}
	case 87:			//Delete Point From Loop
		{
			long num=Dlg.m_cruisepresent.GetCurSel()+1;
			long num2=Dlg.cruise_edit;
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin, m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_DELFROMLOOP,num2,num,3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
			break;
		}
	case 88:			//Close Loop
		{
			long num2=Dlg.cruise_edit;
			if(!H264_DVR_PTZControlEx(m_videoWnd[m_nCurIndex].m_lLogin, m_videoWnd[m_nCurIndex].m_iChannel, 
				EXTPTZ_CLOSELOOP,num2,2,3, dwStop))
				AfxMessageBox(_CS("AccountMSG.Failed"));
			break;
		}
	default:
		break;
	}
}

void CClientDemoDlg::KeyBoardMsg(DWORD dwValue, DWORD dwState)
{
	//get handle of current playing window
	long lPlayHandle = m_videoWnd[m_nCurIndex].GetHandle();
	if ( lPlayHandle <= 0 )
	{
		return;
	}

	SDK_NetKeyBoardData vKeyBoardData;
	vKeyBoardData.iValue = dwValue;
	vKeyBoardData.iState = dwState;
	m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
	if(!H264_DVR_ClickKey(m_videoWnd[m_nCurIndex].m_lLogin, &vKeyBoardData))
			AfxMessageBox(_CS("AccountMSG.Failed"));
}

void CClientDemoDlg::OnBtnSave() 
{
	m_videoWnd[m_nCurIndex].SaveRecord();
}

Devc_Map *CClientDemoDlg::GetDeviceMap()
{
	return m_devDLg.GetDeviceMap();
}

void CClientDemoDlg::OnBtnDevConfig() 
{
// 	CDeviceConfigDlg dlg;
// 	dlg.DoModal();f
}

void CClientDemoDlg::SetDevInfo(DEV_INFO *pDev)
{
	if (pDev)
	{
		memcpy(&m_devInfo, pDev, sizeof(DEV_INFO));
	}
}

void CClientDemoDlg::NetAlarmMsg(DWORD dwValue, DWORD dwState)
{
	if (m_devInfo.lLoginID > 0)
	{
		SDK_NetAlarmInfo vAlarmInfo;
		vAlarmInfo.iEvent = 0;
		vAlarmInfo.iState = dwState << dwValue;
		m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
		if(!H264_DVR_SendNetAlarmMsg(m_devInfo.lLoginID, &vAlarmInfo))
				AfxMessageBox(_CS("AccountMSG.Failed"));
	}
}

void CClientDemoDlg::ReConnect(LONG lLoginID, char *pchDVRIP,  LONG nDVRPort)
{
	//clear all play window of this device
	for (int i = 0; i < MAXWNDNUM; i++)
	{
		if (lLoginID == m_videoWnd[i].GetLoginHandle())
		{
			m_videoWnd[i].OnDisconnct();
		}	
	}
	//do reconnect
	m_devDLg.ReConnect(lLoginID, pchDVRIP, nDVRPort);
}


//Video Color:modify by fanguanggao 2011.7.12
BOOL CClientDemoDlg::SetDevChnColor(DWORD nBright, DWORD nContrast, DWORD nSaturation, DWORD nHue)
{
	SDK_CONFIG_VIDEOCOLOR videocolor;
	
	for ( int i = 0 ;i < 2 ; i ++)
	{
		videocolor.dstVideoColor[i].tsTimeSection.enable = 1;
		videocolor.dstVideoColor[i].tsTimeSection.startHour = 0;
		videocolor.dstVideoColor[i].tsTimeSection.startMinute = 0;
		videocolor.dstVideoColor[i].tsTimeSection.startSecond = 0;
		videocolor.dstVideoColor[i].tsTimeSection.endHour = 24;
		videocolor.dstVideoColor[i].tsTimeSection.endMinute = 0;
		videocolor.dstVideoColor[i].tsTimeSection.endSecond = 0;
		videocolor.dstVideoColor[i].iEnable = 1;
		videocolor.dstVideoColor[i].dstColor.nBrightness = nBright * 100 / 128;
		videocolor.dstVideoColor[i].dstColor.nHue = nHue * 100 / 128;
		videocolor.dstVideoColor[i].dstColor.nSaturation =nSaturation * 100 /128;
		videocolor.dstVideoColor[i].dstColor.nContrast = nContrast * 100 / 128;
		videocolor.dstVideoColor[i].dstColor.mGain = 0;
		videocolor.dstVideoColor[i].dstColor.mWhitebalance = 0;
	}
	
	m_videoWnd[m_nCurIndex].SetDevChnColor(&videocolor);

	return TRUE;
}
bool CClientDemoDlg::DealwithAlarm(long lDevcID,  char* pBuf , DWORD dwLen)
{
		SDK_AlarmInfo alarmInfo;
		memcpy ( &alarmInfo, pBuf, dwLen );		
	if ( (SDK_EVENT_CODE_NET_ALARM == alarmInfo.iEvent 
		|| SDK_EVENT_CODE_MANUAL_ALARM == alarmInfo.iEvent 
		|| SDK_EVENT_CODE_LOCAL_ALARM == alarmInfo.iEvent)&& !alarmInfo.iStatus )
	{
		char str[100] = {0};
		sprintf(str,"IP:%s,%s:%d,%s",m_devInfo.szIpaddress, _CS("Log.Channel"), 
			alarmInfo.nChannel + 1,_CS("AccountMSG.Externalalarm"));
		AfxMessageBox(str);
	}
	else if ( SDK_EVENT_CODE_VIDEO_MOTION == alarmInfo.iEvent  && !alarmInfo.iStatus) 
	{
		char str[100] = {0};
		sprintf(str,"IP:%s,%s:%d,%s",m_devInfo.szIpaddress, _CS("Log.Channel"), 
			alarmInfo.nChannel + 1,_CS("AccountMSG.MotionAlarm"));
		AfxMessageBox(str); 
	}
	else if ( SDK_EVENT_CODE_VIDEO_LOSS == alarmInfo.iEvent && !alarmInfo.iStatus )
	{
		char str[100] = {0};
		CString strIP;
		sprintf(str,"IP:%s,%s:%d,%s",m_devInfo.szIpaddress, _CS("Log.Channel"), 
			alarmInfo.nChannel + 1,_CS("AccountMSG.LossAlarm"));
		AfxMessageBox(str);
	}
	else if ( SDK_EVENT_CODE_VIDEO_BLIND == alarmInfo.iEvent && !alarmInfo.iStatus )
	{
		char str[100] = {0};
		sprintf(str,"IP:%s,%s:%d,%s",m_devInfo.szIpaddress, _CS("Log.Channel"), 
			alarmInfo.nChannel + 1,_CS("AccountMSG.BlindAlarm"));
		AfxMessageBox(str); 
	}
	else if ( SDK_EVENT_CODE_STORAGE_FAILURE == alarmInfo.iEvent && !alarmInfo.iStatus)
	{
		char str[100] = {0};
		sprintf(str,"IP:%s,%s:%d,%s",m_devInfo.szIpaddress, _CS("Log.Channel"), 
			alarmInfo.nChannel + 1,_CS("AccountMSG.StorageFailureAlarm"));
		AfxMessageBox(str); 
	}
	else if ( SDK_EVENT_CODE_LOW_SPACE == alarmInfo.iEvent  && !alarmInfo.iStatus)
	{
		char str[100] = {0};
		sprintf(str,"IP:%s,%s:%d,%s",m_devInfo.szIpaddress, _CS("Log.Channel"), 
			alarmInfo.nChannel + 1,_CS("AccountMSG.LowSpaceAlarm"));
		AfxMessageBox(str); 
	}

	return TRUE;
}

bool WINAPI DevicCallBack(long lLoginID, char *pBuf,unsigned long dwBufLen, long dwUser)
{
	H264_DVR_ACTIVEREG_INFO *info=(H264_DVR_ACTIVEREG_INFO *)pBuf;
	CClientDemoDlg *dlg=(CClientDemoDlg *)dwUser;
	HTREEITEM hAddItem=dlg->m_devDLg.m_deviceTree.InsertItem(info->deviceSarialID);

	DEV_INFO *pDev = new DEV_INFO;
	pDev->lLoginID=lLoginID;
	memset(pDev->szIpaddress,0,15);
	pDev->bSerialID=false;
	memcpy(pDev->szDevName,info->deviceSarialID,60);
	pDev->devctype=100;
	dlg->m_devDLg.m_deviceTree.SetItemData(hAddItem, (DWORD)pDev);
	
	pDev->lID = (long)pDev;
	dlg->m_devDLg.m_devMap[pDev->lID] = pDev;
	pDev->nTotalChannel=info->deviceInfo.byChanNum+info->deviceInfo.iDigChannel;

	CString strName("");
	for ( int i = 0; i < info->deviceInfo.byChanNum+info->deviceInfo.iDigChannel;i ++ )
	{
		strName.Format("CAM %d", i + 1);
		HTREEITEM item = dlg->m_devDLg.m_deviceTree.InsertItem( strName, 0, 0, hAddItem );
		dlg->m_devDLg.m_deviceTree.SetItemData(item, i);
	}
	dlg->m_devDLg.m_deviceTree.SelectItem(hAddItem);
	dlg->m_devDLg.m_deviceTree.Expand(hAddItem, TVE_EXPAND);

	return 1;
}

void CClientDemoDlg::OnCheckActiveConnect() 
{
	// TODO: Add your control notification handler code here
	bool g_Actice = false;
	UpdateData();
	if(m_bActiveConnect)
	{
 		if (g_Actice)
// 		{
// 			return;
// 		}
		bool ret =H264_DVR_StartActiveRigister(9400,DevicCallBack,(unsigned long )this);
		g_Actice = true;
	}	
	else
	{
		H264_DVR_StopActiveRigister();
		HTREEITEM hItem=m_devDLg.m_deviceTree.GetFirstVisibleItem();
		HTREEITEM nextHItem = m_devDLg.m_deviceTree.GetNextItem(hItem,TVGN_NEXT);
		if(hItem==NULL)
		{
			return;
		}
		DEV_INFO *pDev = (DEV_INFO *)m_devDLg.m_deviceTree.GetItemData(hItem);
		if(pDev->devctype==100)
		{
			m_devDLg.m_deviceTree.DeleteItem(hItem);
			Devc_Map::iterator bIter = m_devDLg.m_devMap.find( pDev->lID );
			if ( bIter != m_devDLg.m_devMap.end() )
			{
				m_devDLg.m_devMap.erase(bIter);
			}
		}

		while(1)
		{
			if(NULL == nextHItem)
			{
				return;
			}

			hItem = nextHItem ;
			nextHItem=m_devDLg.m_deviceTree.GetNextItem(hItem,TVGN_NEXT);
			if(hItem==NULL)
			{
				return;
			}
			DEV_INFO *pDev = (DEV_INFO *)m_devDLg.m_deviceTree.GetItemData(hItem);
			if(pDev->devctype==100)
			{
				m_devDLg.m_deviceTree.DeleteItem(hItem);
				Devc_Map::iterator bIter = m_devDLg.m_devMap.find( pDev->lID );
				if ( bIter != m_devDLg.m_devMap.end() )
				{
					m_devDLg.m_devMap.erase(bIter);
				}
			}
		}
	}
}

void CClientDemoDlg::OnSize(UINT nType, int cx, int cy)   
{  
    CDialog::OnSize(nType, cx, cy);  
    // TODO: Add your message handler code here  
    if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
    {  
        ReSize();  
    }  
}  
void CClientDemoDlg::ReSize()  
{  
    float fsp[2];  
    POINT Newp; //获取现在对话框的大小  
    CRect recta;      
    GetClientRect(&recta);     //取客户区大小    
    Newp.x=recta.right-recta.left;  
    Newp.y=recta.bottom-recta.top;  
    fsp[0]=(float)Newp.x/old.x;  
    fsp[1]=(float)Newp.y/old.y;  
    CRect Rect;  
    int woc;  
    CPoint OldTLPoint,TLPoint; //左上角  
    CPoint OldBRPoint,BRPoint; //右下角  
    HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件    
    while(hwndChild)      
    {      
        woc=::GetDlgCtrlID(hwndChild);//取得ID  
        GetDlgItem(woc)->GetWindowRect(Rect);    
        ScreenToClient(Rect);    
        OldTLPoint = Rect.TopLeft();    
        TLPoint.x = long(OldTLPoint.x*fsp[0]);    
        TLPoint.y = long(OldTLPoint.y*fsp[1]);    
        OldBRPoint = Rect.BottomRight();    
        BRPoint.x = long(OldBRPoint.x *fsp[0]);    
        BRPoint.y = long(OldBRPoint.y *fsp[1]);    
        Rect.SetRect(TLPoint,BRPoint);    
        GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
        hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
    }  
    old=Newp;  
}  


