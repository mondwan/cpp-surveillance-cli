// TransparentDemonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TransparentDemon.h"
#include "TransparentDemonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CTransparentDemonDlg dialog

CTransparentDemonDlg::CTransparentDemonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransparentDemonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransparentDemonDlg)
	m_ip = _T("10.6.4.55");
	m_passWord = _T("");
	m_port = 34567;
	m_userName = _T("admin");
	m_strRead = _T("");
	m_strWrite = _T("abc123");
	m_b485 = true;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	H264_DVR_Init(NULL,NULL);
	m_loginID=0;
}
CTransparentDemonDlg::~CTransparentDemonDlg()
{
	H264_DVR_Cleanup();
}

void CTransparentDemonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransparentDemonDlg)
	DDX_Control(pDX, IDC_COMBO_STOP, m_cmbStopposRS);
	DDX_Control(pDX, IDC_COMBO_RATE, m_cmbBaundrateRS);
	DDX_Control(pDX, IDC_COMBO_DATA, m_cmbDataRS);
	DDX_Control(pDX, IDC_COMBO_CHECK, m_cmbConfirmRS);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_passWord);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_userName);
	DDX_Text(pDX, IDC_EDIT_READ, m_strRead);
	DDX_Text(pDX, IDC_EDIT_WRITE, m_strWrite);
	DDX_Check(pDX, IDC_CHECK_485, m_b485);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTransparentDemonDlg, CDialog)
	//{{AFX_MSG_MAP(CTransparentDemonDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Login, OnBUTTONLogin)
	ON_BN_CLICKED(IDC_BUTTON_Open, OnBUTTONOpen)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_Clean, OnBUTTONClean)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentDemonDlg message handlers

BOOL CTransparentDemonDlg::OnInitDialog()
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
	//停止位
	m_cmbStopposRS.AddString("1");
	m_cmbStopposRS.AddString("2");
	m_cmbStopposRS.SetCurSel(0);

	
	//数据位
	m_cmbDataRS.AddString("5");
	m_cmbDataRS.AddString("6");
	m_cmbDataRS.AddString("7");
	m_cmbDataRS.AddString("8");
	m_cmbDataRS.SetCurSel(3);
	
	//检验位
	m_cmbConfirmRS.AddString(_CS("TransParent.None"));
	m_cmbConfirmRS.AddString(_CS("TransParent.Odd"));
	m_cmbConfirmRS.AddString(_CS("TransParent.Even"));
	m_cmbConfirmRS.AddString(_CS("TransParent.Mark"));
	m_cmbConfirmRS.AddString(_CS("TransParent.Space"));
	m_cmbConfirmRS.SetCurSel(0);
	
	m_cmbBaundrateRS.AddString("1200");
	m_cmbBaundrateRS.AddString("2400");
	m_cmbBaundrateRS.AddString("4800");
	m_cmbBaundrateRS.AddString("9600");
	m_cmbBaundrateRS.AddString("19200");
	m_cmbBaundrateRS.AddString("38400");
	m_cmbBaundrateRS.AddString("57600");
	m_cmbBaundrateRS.AddString("115200");
	m_cmbBaundrateRS.SetCurSel(3);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransparentDemonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTransparentDemonDlg::OnPaint() 
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
HCURSOR CTransparentDemonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTransparentDemonDlg::OnBUTTONLogin() 
{
	UpdateData();
	H264_DVR_DEVICEINFO OutDev;
	int nError = 0;
	m_loginID=H264_DVR_Login(m_ip.GetBuffer(0),m_port,m_userName.GetBuffer(0),m_passWord.GetBuffer(0),&OutDev,&nError);
	if(m_loginID<=0)
	{
		MessageBox(_CS("TransParent.loginErr"));
	}
	else
	{
		MessageBox(_CS("TransParent.loginOK"));
	}
	
}
void __stdcall  MyCallBack (long lLoginID, long lTransComType, char *pBuffer, unsigned long dwBufSize, unsigned long dwUser)
{
		CTransparentDemonDlg * dlg=(CTransparentDemonDlg * )dwUser;
		char *buf=new char[dwBufSize+1];
		memset(buf,0,dwBufSize+1);
		memcpy(buf,pBuffer,dwBufSize);
		dlg->m_strRead+=buf;
		SetTimer(dlg->m_hWnd,1,0,NULL);
}

void CTransparentDemonDlg::OnBUTTONOpen() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	long i=sizeof(long);
	long i2=sizeof(int);
	
	
	TransComChannel param;
	CString tempStr;
	m_cmbBaundrateRS.GetWindowText(tempStr);
	param.baudrate=atoi(tempStr.GetBuffer(0));
	m_cmbDataRS.GetWindowText(tempStr);
	param.databits=atoi(tempStr.GetBuffer(0));
	m_cmbStopposRS.GetWindowText(tempStr);
	param.stopbits=atoi(tempStr.GetBuffer(0));	
	param.parity=m_cmbConfirmRS.GetCurSel();
	if(m_b485)
	{
		param.TransComType=RS485;
	}
	else
	{
		param.TransComType=RS232;
	}
	
	if(H264_DVR_OpenTransComChannel(m_loginID,&param,(fTransComCallBack)MyCallBack,(long)this))
	{
		MessageBox(_CS("TransParent.OpenOK"));
	}
	else
	{
		MessageBox(_CS("TransParent.OpenErr"));
	}

	
}

void CTransparentDemonDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	bool ret=false;
	if (m_b485)
	{
			ret=H264_DVR_CloseTransComChannel(m_loginID,RS485);
	}
	else
	{
			ret=H264_DVR_CloseTransComChannel(m_loginID,RS232);
	}

	if(ret)
	{
	MessageBox(_CS("TransParent.CloseOK"));
	}
	else
	{
		MessageBox(_CS("TransParent.CloseErr"));
	}
	
}

void CTransparentDemonDlg::OnButtonWrite() 
{
	// TODO: Add your control notification handler code here
// 	char buf[5]={'1','2','3','4','5'};
//  	buf[0]=0xff;
//  	buf[1]=0x10;	
		UpdateData(TRUE);
		if(m_b485)
		{
			H264_DVR_SerialWrite(m_loginID,RS485,m_strWrite.GetBuffer(0),m_strWrite.GetLength()+1);
		}
		else
		{
			H264_DVR_SerialWrite(m_loginID,RS232,m_strWrite.GetBuffer(0),m_strWrite.GetLength()+1);
		}
	
	
}

void CTransparentDemonDlg::OnBUTTONClean() 
{
	// TODO: Add your control notification handler code here
	m_strRead.Empty();
	UpdateData(FALSE);	
}

void CTransparentDemonDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
		UpdateData(FALSE);
		KillTimer(1);
	}
	
	
	CDialog::OnTimer(nIDEvent);
}
