// NetServerEmail.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerEmail.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerEmail dialog


CNetServerEmail::CNetServerEmail(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerEmail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerEmail)
	m_smtp = _T("");
	m_sendAddr = _T("");
	m_recAddr = _T("");
	m_password = _T("");
	m_port = 0;
	m_title = _T("");
	m_userName = _T("");
	m_TestPrompt = _T("");
	//}}AFX_DATA_INIT
}


void CNetServerEmail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerEmail)
	DDX_Control(pDX, IDC_CHECK_SSL_ENABLE, m_ctlEnableSSL);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_ctlEnableEmail);
	DDX_Control(pDX,IDC_BUTTON_TEST,m_btnMaintest);
	DDX_Text(pDX, IDC_EDIT_SMTP, m_smtp);
	DDX_Text(pDX, IDC_EDIT_SEND_ADDR, m_sendAddr);
	DDX_Text(pDX, IDC_EDIT_REC_ADDR, m_recAddr);
	DDX_Text(pDX, IDC_EDIT_PSW, m_password);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_title);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_userName);
	DDX_Text(pDX, IDC_EDIT_PROMPT, m_TestPrompt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerEmail, CDialog)
	//{{AFX_MSG_MAP(CNetServerEmail)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_BN_CLICKED(IDC_CHECK_SSL_ENABLE, OnCheckSslEnable)
	ON_BN_CLICKED(IDC_BUTTON_TEST,OnCheckTest)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerEmail message handlers

BOOL CNetServerEmail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	//m_bBusy = FALSE;
	//m_TestPrompt = "";
	return TRUE;  
}

void CNetServerEmail::InitDlgInfo(SDK_NetEmailConfig *pNetEmailCfg,long LoginID)
{
	m_ensure = FALSE;
	m_bBusy = FALSE;
	memcpy(&m_netEmailCfg,pNetEmailCfg,sizeof(SDK_NetEmailConfig));
	m_ctlEnableEmail.SetCheck(m_netEmailCfg.Enable);
	m_smtp = m_netEmailCfg.Server.ServerName;
	m_port = m_netEmailCfg.Server.Port;
	m_ctlEnableSSL.SetCheck(m_netEmailCfg.bUseSSL);
	m_userName = m_netEmailCfg.Server.UserName;
	m_password = m_netEmailCfg.Server.Password;
	m_sendAddr = m_netEmailCfg.SendAddr;
	m_recAddr = "";
	m_TestPrompt = "";
	for (int i = 0; i < NET_MAX_EMAIL_RECIEVERS; ++i)
	{
		CString temp = m_netEmailCfg.Recievers[i];
		if (temp != "none")
			m_recAddr = m_recAddr + m_netEmailCfg.Recievers[i] + ";";
	}
	m_title = m_netEmailCfg.Title;
	m_LoginID = LoginID;
	OnCheckEnable();
	UpdateData(FALSE);
}

void CNetServerEmail::OnCheckEnable() 
{
	bool enableEmail = m_ctlEnableEmail.GetCheck();
	if (true == enableEmail)
	{
		GetDlgItem(IDC_EDIT_SMTP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
		m_ctlEnableSSL.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PSW)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SEND_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_REC_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TITLE)->EnableWindow(TRUE);	
		GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE);
		m_netEmailCfg.Enable = true;
	}
	else
	{
		GetDlgItem(IDC_EDIT_SMTP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
		m_ctlEnableSSL.EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PSW)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SEND_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_REC_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TITLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);
		m_netEmailCfg.Enable = false;
	}
}

DWORD WINAPI AddProc(PVOID pvParam) 
{ 
    int j=0; 
	//CNetServerEmail *pThis = (CNetServerEmail*)pvParam;
    for(int i=0; i<50000; i++)
    { 
		j += i; 
		TRACE(TEXT("%d\n"), j);
    } 
	
    PostMessage((HWND)pvParam, WM_APP + 1, 0, 0); 
    return j;  
}

void CNetServerEmail::OnCheckTest()
{
	SaveConfig();
	m_bBusy = TRUE;
    BeginWaitCursor();
    HANDLE hThread = CreateThread(NULL, 0, AddProc, (PVOID)(HWND)*this, 0, NULL); 
	long lRet = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CFG_MAIL_TEST,-1,
		(char*)&m_netEmailCfg,sizeof(SDK_NetEmailConfig),10000);
	Sleep(3000);
	if (lRet>0)
	{
		m_TestPrompt = _CS("ConfigNet.SendSuccess");
	}else
	{
		m_TestPrompt = _CS("ConfigNet.SendFail");
	}
	UpdateData(FALSE);
	CloseHandle(hThread);
	UpdateData();
}

LRESULT CNetServerEmail::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    if(message == (WM_APP + 1))  
	{
		m_bBusy = FALSE; 
		EndWaitCursor();
	} 
	return CDialog::WindowProc(message, wParam, lParam);
} 
BOOL CNetServerEmail::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{ 
	if(m_bBusy) 
		return TRUE; 
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CNetServerEmail::OnCheckSslEnable() 
{
	bool enableSSL = m_ctlEnableSSL.GetCheck();
	if (true == enableSSL)
		m_netEmailCfg.bUseSSL = true;
	else
		m_netEmailCfg.bUseSSL = false;
}


void CNetServerEmail::GetRecAddr() 
{
	UpdateData(TRUE);
	int i = 0;
	if (m_recAddr != "")
	{
		int nIndex =0,length;
		CString recAddr = m_recAddr;
		length = recAddr.GetLength();
		for (i = 0 ;; ++i)
		{
			if (i == NET_MAX_EMAIL_RECIEVERS)			//添加过多
			{
				if (recAddr == "")						//最后一个分号处理
					break;
				MessageBox(_CS("NetServer.RecAddrError"));
				m_recAddr = "";
				UpdateData(FALSE);
				break;
			}
			if (recAddr != "")
			{
				nIndex = recAddr.Find(";");
				if (nIndex == -1)
				{
					strcpy(m_netEmailCfg.Recievers[i],recAddr);
					break;
				}
				else
				{
					strcpy(m_netEmailCfg.Recievers[i],recAddr.Left(nIndex));
					length -=nIndex + 1;
					recAddr = recAddr.Right(length);
				}
			}
			else
				break;
		}
	}
	else
	{
		CString temp = "none";
		for (i = 0; i < NET_MAX_EMAIL_RECIEVERS; ++i)
			memcpy(m_netEmailCfg.Recievers[i],temp,sizeof(temp));
	}
}


void CNetServerEmail::OnOK() 
{
	m_ensure = TRUE;
	SaveConfig();
	CDialog::OnOK();
}

void CNetServerEmail::SaveConfig()
{
	UpdateData();
	strncpy(m_netEmailCfg.Server.UserName,m_userName,sizeof(m_netEmailCfg.Server.UserName));
	strncpy(m_netEmailCfg.Title,m_title,sizeof(m_netEmailCfg.Title));
	strncpy(m_netEmailCfg.Server.ServerName,m_smtp,sizeof(m_netEmailCfg.Server.ServerName));
	strncpy(m_netEmailCfg.SendAddr,m_sendAddr,sizeof(m_netEmailCfg.SendAddr));
	strncpy(m_netEmailCfg.Server.Password,m_password,sizeof(m_netEmailCfg.Server.Password));
	m_netEmailCfg.Server.Port = m_port;
	m_netEmailCfg.bUseSSL = m_ctlEnableSSL.GetCheck();
	m_netEmailCfg.Enable = m_ctlEnableEmail.GetCheck();
	GetRecAddr();
}


void CNetServerEmail::OnKillfocusEditPort() 
{
	UpdateData(TRUE);
	if (m_port < 0 || m_port > 65535)
	{
		m_port = 0;
		UpdateData(FALSE);
	}
}
