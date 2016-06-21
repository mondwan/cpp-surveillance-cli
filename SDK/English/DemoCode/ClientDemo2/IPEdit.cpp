/////////////////////////////////////////////////////////////////////////////
// CIPEdit message handlers
// IPEdit.cpp : 
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "IPEdit.h"




IMPLEMENT_DYNAMIC(CIPEdit, CDialog)

CIPEdit::CIPEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CIPEdit::IDD, pParent)
	, m_nHttpPort(0)
	, m_nTCPPort(0)
	, m_strMac(_T(""))
	, m_User(_T(""))
	, m_Passwd(_T(""))
{
	
}

CIPEdit::~CIPEdit()
{
}

void CIPEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Http, m_nHttpPort);
	DDV_MinMaxInt(pDX, m_nHttpPort, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_Tcp, m_nTCPPort);
	DDV_MinMaxInt(pDX, m_nTCPPort, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_Mac, m_strMac);
	DDV_MaxChars(pDX, m_strMac, 32);
	DDX_Text(pDX,IDC_EDIT_User,m_User);
	DDX_Text(pDX,IDC_EDIT_Passwd,m_Passwd);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_IPAddrCtrl);
	DDX_Control(pDX, IDC_IPADDRESS_Mask, m_MaskCtrl);
	DDX_Control(pDX, IDC_IPADDRESS_Gateway, m_GateCtrl);
}


BEGIN_MESSAGE_MAP(CIPEdit, CDialog)
	ON_BN_CLICKED(IDOK, CIPEdit::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL CIPEdit::OnInitDialog()
{
    CDialog::OnInitDialog();
	_CWndCS(this);
	m_nHttpPort = m_NetComm.HttpPort;
	m_nTCPPort = m_NetComm.TCPPort;
	m_strMac = m_NetComm.sMac;
	unsigned char *pIP = (unsigned char*)&m_NetComm.HostIP.l;   
	m_IPAddrCtrl.SetAddress(*pIP,   *(pIP+1),   *(pIP+2),   *(pIP+3));

	pIP = (unsigned char*)&m_NetComm.Submask.l; 
	m_MaskCtrl.SetAddress(*pIP,   *(pIP+1),   *(pIP+2),   *(pIP+3));

	pIP = (unsigned char*)&m_NetComm.Gateway.l; 
	m_GateCtrl.SetAddress(*pIP,   *(pIP+1),   *(pIP+2),   *(pIP+3));
	UpdateData(FALSE);
	return TRUE;
}

void CIPEdit::OnBnClickedOk()
{
	
	UpdateData(TRUE);

	m_NetComm.HttpPort = m_nHttpPort;
	m_NetComm.TCPPort = m_nTCPPort;
	BYTE byIP[4];
	m_IPAddrCtrl.GetAddress(byIP[0], byIP[1], byIP[2], byIP[3]);
	m_NetComm.HostIP.c[0] = byIP[0];
	m_NetComm.HostIP.c[1] = byIP[1];
	m_NetComm.HostIP.c[2] = byIP[2];
	m_NetComm.HostIP.c[3] = byIP[3];

	m_MaskCtrl.GetAddress(byIP[0], byIP[1], byIP[2], byIP[3]);
	m_NetComm.Submask.c[0] = byIP[0];
	m_NetComm.Submask.c[1] = byIP[1];
	m_NetComm.Submask.c[2] = byIP[2];
	m_NetComm.Submask.c[3] = byIP[3];

	m_GateCtrl.GetAddress(byIP[0], byIP[1], byIP[2], byIP[3]);
	m_NetComm.Gateway.c[0] = byIP[0];
	m_NetComm.Gateway.c[1] = byIP[1];
	m_NetComm.Gateway.c[2] = byIP[2];
	m_NetComm.Gateway.c[3] = byIP[3];

	/*IP_ADAPTER_INFO adapter[5];  //Maximum 5 adapters
	
	DWORD buflen=sizeof(adapter);
	
	DWORD status=GetAdaptersInfo(adapter,&buflen);
	
	BYTE s[8];
	char LocalMac[100];
	if(status==ERROR_SUCCESS)
	{
		
		PIP_ADAPTER_INFO painfo=adapter;
		memcpy(s,painfo->Address,6);
		sprintf(LocalMac,"%02X-%02X-%02X-%02X-%02X-%02X",s[0],s[1],s[2],s[3],s[4],s[5]);
		
	}
	strcpy(m_NetComm.LocalMac,LocalMac);
	
	strcpy(m_NetComm.UserName,m_User.GetBuffer(0));
	strcpy(m_NetComm.Password,m_Passwd.GetBuffer(0));
	m_NetComm.nPasswordType =1;*/
	
	if ((m_NetComm.HostIP.l & m_NetComm.Submask.l) != (m_NetComm.Gateway.l & m_NetComm.Submask.l))
	{
		MessageBox(_CS(_T("ConfigNet.SetGatewayFailed")), _CS(_T("Upgrade.Prompt")));
		return;
	}

	OnOK();
}
