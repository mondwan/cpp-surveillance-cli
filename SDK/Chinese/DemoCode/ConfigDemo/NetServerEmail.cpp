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
	//}}AFX_DATA_INIT
}


void CNetServerEmail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerEmail)
	DDX_Control(pDX, IDC_CHECK_SSL_ENABLE, m_ctlEnableSSL);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_ctlEnableEmail);
	DDX_Text(pDX, IDC_EDIT_SMTP, m_smtp);
	DDX_Text(pDX, IDC_EDIT_SEND_ADDR, m_sendAddr);
	DDX_Text(pDX, IDC_EDIT_REC_ADDR, m_recAddr);
	DDX_Text(pDX, IDC_EDIT_PSW, m_password);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_title);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_userName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerEmail, CDialog)
	//{{AFX_MSG_MAP(CNetServerEmail)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_BN_CLICKED(IDC_CHECK_SSL_ENABLE, OnCheckSslEnable)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerEmail message handlers

BOOL CNetServerEmail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerEmail::InitDlgInfo(SDK_NetEmailConfig *pNetEmailCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netEmailCfg,pNetEmailCfg,sizeof(SDK_NetEmailConfig));
	m_ctlEnableEmail.SetCheck(m_netEmailCfg.Enable);
	m_smtp = m_netEmailCfg.Server.ServerName;
	m_port = m_netEmailCfg.Server.Port;
	m_ctlEnableSSL.SetCheck(m_netEmailCfg.bUseSSL);
	m_userName = m_netEmailCfg.Server.UserName;
	m_password = m_netEmailCfg.Server.Password;
	m_sendAddr = m_netEmailCfg.SendAddr;
	m_recAddr = "";
	for (int i = 0; i < NET_MAX_EMAIL_RECIEVERS; ++i)
	{
		CString temp = m_netEmailCfg.Recievers[i];
		if (temp != "none")
			m_recAddr = m_recAddr + m_netEmailCfg.Recievers[i] + ";";
	}
	m_title = m_netEmailCfg.Title;
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
		m_netEmailCfg.Enable = false;
	}
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
