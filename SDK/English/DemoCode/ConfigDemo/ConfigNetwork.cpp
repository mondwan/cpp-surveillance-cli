// ConfigNetwork.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigNetwork.h"
#include "NetPre.h"
#include "ClientDemo5Dlg.h"
#include <string>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigNetwork dialog
#include <string>

CConfigNetwork::CConfigNetwork(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigNetwork::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigNetwork)
	m_bDHCP = FALSE;
	m_bHightLoadDown = FALSE;
	m_EditMac1 = _T("");
	m_EditMac2 = _T("");
	m_EditMac3 = _T("");
	m_EditMac4 = _T("");
	m_EditMac5 = _T("");
	m_EditMac6 = _T("");
	//}}AFX_DATA_INIT
}


void CConfigNetwork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigNetwork)
	DDX_Control(pDX, IDC_CHECK_HIGHTLOADDOWN, m_HightLoaddown);
	DDX_Control(pDX, IDC_COMBO_NETCARD, m_ctlNetCard);
	DDX_Control(pDX, IDC_COMBO_TRANSFERPOLICY, m_ctlTransferPolicy);
	DDX_Control(pDX, IDC_IPADDRESS_SECONDARYDNS, m_ctlSecondaryDNS);
	DDX_Control(pDX, IDC_IPADDRESS_PRIMARYDNS, m_ctlPrimaryDNS);
	DDX_Control(pDX, IDC_IPADDRESS_NETGATEWAY, m_ctlNetGateWay);
	DDX_Control(pDX, IDC_IPADDRESS_NETIPMASK, m_ctlNetIPMask);
	DDX_Control(pDX, IDC_IPADDRESS_NETIP, m_ctlNetIP);
	DDX_Check(pDX, IDC_CHECK_DHCPEnable, m_bDHCP);
	DDX_Check(pDX, IDC_CHECK_HIGHTLOADDOWN, m_bHightLoadDown);
	DDX_Text(pDX, IDC_EDIT_MAC1, m_EditMac1);
	DDX_Text(pDX, IDC_EDIT_MAC2, m_EditMac2);
	DDX_Text(pDX, IDC_EDIT_MAC3, m_EditMac3);
	DDX_Text(pDX, IDC_EDIT_MAC4, m_EditMac4);
	DDX_Text(pDX, IDC_EDIT_MAC5, m_EditMac5);
	DDX_Text(pDX, IDC_EDIT_MAC6, m_EditMac6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigNetwork, CDialog)
	//{{AFX_MSG_MAP(CConfigNetwork)	
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_BN_CLICKED(IDC_CHECK_DHCPEnable, OnCHECKDHCPEnable)
	ON_EN_KILLFOCUS(IDC_EDIT_MAC6, OnKillfocusEditMac6)
	ON_EN_CHANGE(IDC_EDIT_MAC6, OnChangeEditMac6)
	ON_EN_CHANGE(IDC_EDIT_TCPPORT, OnChangeEditTcpport)
	ON_EN_CHANGE(IDC_EDIT_HTTPPORT, OnChangeEditHttpport)
	ON_BN_CLICKED(IDC_BUTTON_NETPRE, OnButtonNetpre)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigNetwork message handlers

BOOL CConfigNetwork::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	CleanAll();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigNetwork::InitDlgInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP,SDK_NetOrderConfig *pNetOrder,SDK_NetOrderFunction *pNetOrderFunc)
{
	m_ctlNetCard.ResetContent();
	int nIndex = m_ctlNetCard.AddString(_CS("ConfigNet.Wirecard"));
	m_ctlNetCard.SetItemData(nIndex,0);
	m_ctlNetCard.SetCurSel(0);
	
	m_ctlTransferPolicy.ResetContent();
	nIndex = m_ctlTransferPolicy.AddString(_CS("ConfigNet.Adaptive"));
	m_ctlTransferPolicy.SetItemData(nIndex,0);
	nIndex = m_ctlTransferPolicy.AddString(_CS("ConfigNet.QualityPre"));
	m_ctlTransferPolicy.SetItemData(nIndex,1);
	nIndex = m_ctlTransferPolicy.AddString(_CS("ConfigNet.FluencyPre"));
	m_ctlTransferPolicy.SetItemData(nIndex,2);
	m_ctlTransferPolicy.SetCurSel(pNetCommon->TransferPlan);
	memcpy(&m_pNetCommon,pNetCommon,sizeof(SDK_CONFIG_NET_COMMON));
	memcpy(&m_pNetDHCP,pNetDHCP,sizeof(SDK_NetDHCPConfigAll));
	memcpy(&m_pNetDNS,pNetDNS,sizeof(SDK_NetDNSConfig));
	memcpy(&m_pNetOrder,pNetOrder,sizeof(SDK_NetOrderConfig));
	memcpy(&m_pNetOrderFunc,pNetOrderFunc,sizeof(SDK_NetOrderFunction));
	m_bHightLoadDown = pNetCommon->bUseHSDownLoad;
	m_HightLoaddown.SetCheck(m_bHightLoadDown);
	m_bDHCP = pNetDHCP->vNetDHCPConfig[0].bEnable;
	OnCHECKDHCPEnable();
	m_ctlNetIP.SetAddress(pNetCommon->HostIP.c[0],pNetCommon->HostIP.c[1],pNetCommon->HostIP.c[2],pNetCommon->HostIP.c[3]);
	m_ctlNetIPMask.SetAddress(pNetCommon->Submask.c[0],pNetCommon->Submask.c[1],pNetCommon->Submask.c[2],pNetCommon->Submask.c[3]);
	m_ctlNetGateWay.SetAddress(pNetCommon->Gateway.c[0],pNetCommon->Gateway.c[1],pNetCommon->Gateway.c[2],pNetCommon->Gateway.c[3]);
	m_ctlPrimaryDNS.SetAddress(pNetDNS->PrimaryDNS.c[0],pNetDNS->PrimaryDNS.c[1],pNetDNS->PrimaryDNS.c[2],pNetDNS->PrimaryDNS.c[3]);
	m_ctlSecondaryDNS.SetAddress(pNetDNS->SecondaryDNS.c[0],pNetDNS->SecondaryDNS.c[1],pNetDNS->SecondaryDNS.c[2],pNetDNS->SecondaryDNS.c[3]);
	SetDlgItemInt(IDC_EDIT_TCPPORT,pNetCommon->TCPPort);
	SetDlgItemInt(IDC_EDIT_HTTPPORT,pNetCommon->HttpPort);

	//mac
	CString strTemp=pNetCommon->sMac;
    string sMac0(strTemp.GetBuffer(strTemp.GetLength()));
    sMac0.erase(2,sMac0.length()-2);
	SetDlgItemText(IDC_EDIT_MAC1,(LPCSTR)(LPSTR)sMac0.c_str());
	strTemp.ReleaseBuffer();
	
	string sMac1(strTemp.GetBuffer(strTemp.GetLength()));
	sMac1.erase(0,3);
	sMac1.erase(2,sMac1.length()-2);
	SetDlgItemText(IDC_EDIT_MAC2,(LPCSTR)(LPSTR)sMac1.c_str());
	strTemp.ReleaseBuffer();
	
	string sMac2(strTemp.GetBuffer(strTemp.GetLength()));
	sMac2.erase(0,6);
	sMac2.erase(2,sMac2.length()-2);
	SetDlgItemText(IDC_EDIT_MAC3,(LPCSTR)(LPSTR)sMac2.c_str());
	strTemp.ReleaseBuffer();
	
	string sMac3(strTemp.GetBuffer(strTemp.GetLength()));
	sMac3.erase(0,9);
	sMac3.erase(2,sMac3.length()-2);
	SetDlgItemText(IDC_EDIT_MAC4,(LPCSTR)(LPSTR)sMac3.c_str());
	strTemp.ReleaseBuffer();
	
	string sMac4(strTemp.GetBuffer(strTemp.GetLength()));
	sMac4.erase(0,12);
	sMac4.erase(2,sMac4.length()-2);
	SetDlgItemText(IDC_EDIT_MAC5,(LPCSTR)(LPSTR)sMac4.c_str());
	strTemp.ReleaseBuffer();
	
	string sMac5(strTemp.GetBuffer(strTemp.GetLength()));
	sMac5.erase(0,15);
	SetDlgItemText(IDC_EDIT_MAC6,(LPCSTR)(LPSTR)sMac5.c_str());
	m_EditMac6 = sMac5.c_str();
	strTemp.ReleaseBuffer();
	if ( !m_pNetOrderFunc.bNetOrder)
	{
		GetDlgItem(IDC_STATIC_NETPRE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_NETPRE)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CConfigNetwork::CleanAll()
{
	m_ctlTransferPolicy.ResetContent();
	m_ctlNetCard.ResetContent();
	SetDlgItemText(IDC_EDIT_TCPPORT,_T(""));
	SetDlgItemText(IDC_EDIT_HTTPPORT,_T(""));
	SetDlgItemText(IDC_EDIT_MAC1,_T(""));
	SetDlgItemText(IDC_EDIT_MAC2,_T(""));
	SetDlgItemText(IDC_EDIT_MAC3,_T(""));
	SetDlgItemText(IDC_EDIT_MAC4,_T(""));
	SetDlgItemText(IDC_EDIT_MAC5,_T(""));
	SetDlgItemText(IDC_EDIT_MAC6,_T(""));
	m_HightLoaddown.SetCheck(FALSE);
	m_bDHCP = FALSE;
	OnCHECKDHCPEnable();
	m_ctlNetIP.SetAddress(0,0,0,0);
	m_ctlNetGateWay.SetAddress(0,0,0,0);
	m_ctlNetIPMask.SetAddress(0,0,0,0);
	m_ctlPrimaryDNS.SetAddress(0,0,0,0);
	m_ctlSecondaryDNS.SetAddress(0,0,0,0);
	UpdateData(FALSE);
}

void CConfigNetwork::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	if (-1 != m_ctlNetCard.GetCurSel())
	{
		SaveNetCfgInfo();
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetNetWorkConfigInfo(&m_pNetCommon,&m_pNetDNS,&m_pNetDHCP);
	}
}

void CConfigNetwork::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetNetWorkConfigInfo();
}

void CConfigNetwork::OnCHECKDHCPEnable() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	BOOL nEnable = m_bDHCP;
	m_ctlNetIP.EnableWindow(!nEnable);
	m_ctlNetIPMask.EnableWindow(!nEnable);
	m_ctlNetGateWay.EnableWindow(!nEnable);
}

#define swap_long(x) (((((unsigned long)(x)) & 0xff000000) >> 24) | \
	((((unsigned long)(x)) & 0x00ff0000) >> 8) | \
	((((unsigned long)(x)) & 0x0000ff00) << 8) | \
	((((unsigned long)(x)) & 0x000000ff) << 24)\
	)
void CConfigNetwork::SaveNetCfgInfo()
{
	UpdateData();
	m_pNetCommon.bUseHSDownLoad = m_bHightLoadDown;
	m_pNetDHCP.vNetDHCPConfig[0].bEnable = m_bDHCP;
	m_pNetCommon.TCPPort = GetDlgItemInt(IDC_EDIT_TCPPORT);
	m_pNetCommon.HttpPort = GetDlgItemInt(IDC_EDIT_HTTPPORT);
	m_pNetCommon.TransferPlan = m_ctlTransferPolicy.GetCurSel();
	DWORD dwIP;
	m_ctlNetIP.GetAddress(dwIP);
	m_pNetCommon.HostIP.l = swap_long(dwIP);
	DWORD dwIPMask;
	m_ctlNetIPMask.GetAddress(dwIPMask);
	m_pNetCommon.Submask.l = swap_long(dwIPMask);
	DWORD dwGateway;
	m_ctlNetGateWay.GetAddress(dwGateway);
	m_pNetCommon.Gateway.l = swap_long(dwGateway);
	DWORD dwPrimary;
	m_ctlPrimaryDNS.GetAddress(dwPrimary);
	m_pNetDNS.PrimaryDNS.l = swap_long(dwPrimary);
	DWORD dwSecondary;
	m_ctlSecondaryDNS.GetAddress(dwSecondary);
	m_pNetDNS.SecondaryDNS.l = swap_long(dwSecondary);

	CString strMac;
	strMac = m_EditMac1 + ":" + m_EditMac2 + ":" + m_EditMac3 
		+ ":" + m_EditMac4 + ":" + m_EditMac5 + ":" + m_EditMac6;
	strcpy(m_pNetCommon.sMac,strMac.GetBuffer(0));
}
// void CConfigNetwork::SaveNetCfgInfo(SDK_NetOrderConfig *pNetOrder)
// {
// 	memcpy(&m_pNetOrder,pNetOrder,sizeof(SDK_NetOrderConfig));
// }
void CConfigNetwork::OnKillfocusEditMac6() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int slen=m_EditMac6.GetLength();
	if ( slen == 0)return;
	char *ch ={0};
	ch = m_EditMac6.GetBuffer(m_EditMac6.GetLength());
	
	for(int i = 0;i < slen; i ++ )
	{
		if((m_EditMac6[i] < '0')||(m_EditMac6[i] > '9'))
		{
			if((m_EditMac6[i] < 'a')||(m_EditMac6[i]> 'f' ))
			{
				if((m_EditMac6[i]<'A')||(m_EditMac6[i]>'F'))
				{
					m_EditMac6 = m_pNetCommon.sMac;
					string strtemp;
					strtemp.assign(m_EditMac6.GetBuffer(m_EditMac6.GetLength()));
					strtemp.erase(0,15);
					m_EditMac6 = strtemp.c_str();
					m_EditMac6.ReleaseBuffer();
					UpdateData(FALSE);
					break;
				}
			}
		}
		
		if((m_EditMac6[i] >= 'A')&&(m_EditMac6[i] <= 'F'))
		{
			ch[i]=m_EditMac6[i] + 32;
		}
	}
	
	ch[slen] = '\0';
	m_EditMac6 = ch;
	
	m_EditMac6.ReleaseBuffer();
	
	if(slen != 2)
	{
		m_EditMac6 = m_pNetCommon.sMac;
		string str;
		str.assign(m_EditMac6.GetBuffer(m_EditMac6.GetLength()));
		str.erase(0,15);
		m_EditMac6 = str.c_str();
		m_EditMac6.ReleaseBuffer();
		UpdateData(FALSE);
	}
}

void CConfigNetwork::OnChangeEditMac6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int slen=m_EditMac6.GetLength();
	if(slen > 2)
	{
		m_EditMac6 = m_pNetCommon.sMac;
		string strtemp(m_EditMac6.GetBuffer(m_EditMac6.GetLength()));
		strtemp.erase(0,15);
		m_EditMac6 = strtemp.c_str();
		m_EditMac6.ReleaseBuffer();
		UpdateData(FALSE);
	}	
	GetDlgItem(IDC_EDIT_MAC6)->SetFocus();
}

void CConfigNetwork::OnChangeEditTcpport() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int TcpPort = GetDlgItemInt(IDC_EDIT_TCPPORT);
	if ( TcpPort > 65535 )
	{
		SetDlgItemInt(IDC_EDIT_TCPPORT,65535);
		UpdateData(FALSE);
	}
}

void CConfigNetwork::OnChangeEditHttpport() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	int HttpPort = GetDlgItemInt(IDC_EDIT_HTTPPORT);
	if ( HttpPort > 65535 )
	{
		SetDlgItemInt(IDC_EDIT_HTTPPORT,65535);
		UpdateData(FALSE);
	}
}

void CConfigNetwork::OnButtonNetpre() 
{
	// TODO: Add your control notification handler code here
	CNetPre m_NetPre(&m_pNetOrder);
	m_NetPre.DoModal();
}

void CConfigNetwork::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
