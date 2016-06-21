// NetServerMultiMedia.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerMultiMedia.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerMultiMedia dialog


CNetServerMultiMedia::CNetServerMultiMedia(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerMultiMedia::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerMultiMedia)
	m_sGateWay = _T("");
	m_nGateWayPort = 0;
	m_sMmsc = _T("");
	m_nMmscPort = 0;
	m_sPhone1 = _T("");
	m_sPhone3 = _T("");
	m_sPhone2 = _T("");
	//}}AFX_DATA_INIT
}


void CNetServerMultiMedia::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerMultiMedia)
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_GATEWAY, m_sGateWay);
	DDX_Text(pDX, IDC_EDIT_GATEWAY_PORT, m_nGateWayPort);
	DDV_MinMaxInt(pDX, m_nGateWayPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_MMSC, m_sMmsc);
	DDX_Text(pDX, IDC_EDIT_MMSC_PORT, m_nMmscPort);
	DDV_MinMaxInt(pDX, m_nMmscPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PHONE1, m_sPhone1);
	DDX_Text(pDX, IDC_EDIT_PHONE3, m_sPhone3);
	DDX_Text(pDX, IDC_EDIT_PHONE2, m_sPhone2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerMultiMedia, CDialog)
	//{{AFX_MSG_MAP(CNetServerMultiMedia)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_EN_CHANGE(IDC_EDIT_GATEWAY, OnChangeEditGateway)
	ON_EN_CHANGE(IDC_EDIT_GATEWAY_PORT, OnChangeEditGatewayPort)
	ON_EN_CHANGE(IDC_EDIT_MMSC, OnChangeEditMmsc)
	ON_EN_CHANGE(IDC_EDIT_MMSC_PORT, OnChangeEditMmscPort)
	ON_EN_CHANGE(IDC_EDIT_PHONE1, OnChangeEditPhone1)
	ON_EN_CHANGE(IDC_EDIT_PHONE2, OnChangeEditPhone2)
	ON_EN_CHANGE(IDC_EDIT_PHONE3, OnChangeEditPhone3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerMultiMedia message handlers

BOOL CNetServerMultiMedia::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	CenterWindow();
	return TRUE;  
}

void CNetServerMultiMedia::InitDlgInfo(SDK_NetMultimediaMsgCfg *pNetMultimediaMsgCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netMultimediaMsgCfg,pNetMultimediaMsgCfg,sizeof(SDK_NetMultimediaMsgCfg));
	m_checkEnable.SetCheck(m_netMultimediaMsgCfg.bEnable);
	m_sPhone1 = m_netMultimediaMsgCfg.pDesPhoneNum[0];
	m_sPhone2 = m_netMultimediaMsgCfg.pDesPhoneNum[1];
	m_sPhone3 = m_netMultimediaMsgCfg.pDesPhoneNum[2];
	m_sGateWay = m_netMultimediaMsgCfg.pGateWayDomain;
	m_sMmsc = m_netMultimediaMsgCfg.pMmscDomain;
	m_nGateWayPort = m_netMultimediaMsgCfg.gateWayPort;
	m_nMmscPort = m_netMultimediaMsgCfg.mmscPort;
	UpdateData(FALSE);
	OnCheckEnable();
}

void CNetServerMultiMedia::OnCheckEnable() 
{
	BOOL bEnable = m_checkEnable.GetCheck();
	((CEdit*)GetDlgItem(IDC_EDIT_PHONE1))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_PHONE2))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_PHONE3))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_GATEWAY))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_GATEWAY_PORT))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_MMSC))->EnableWindow(bEnable);
	((CEdit*)GetDlgItem(IDC_EDIT_MMSC_PORT))->EnableWindow(bEnable);
}

void CNetServerMultiMedia::OnChangeEditGateway() 
{
	UpdateData();
	if (m_sGateWay.GetLength() > 40)
	{
		m_sGateWay = m_sGateWay.Left(40);
		UpdateData(FALSE);
	}
}

void CNetServerMultiMedia::OnChangeEditGatewayPort() 
{
	UpdateData();
	if (m_nGateWayPort < 0)
	{
		m_nGateWayPort = 0;
		UpdateData(FALSE);
	}
}

void CNetServerMultiMedia::OnChangeEditMmsc() 
{
	UpdateData();
	if (m_sMmsc.GetLength() > 40)
	{
		m_sMmsc = m_sMmsc.Left(40);
		UpdateData(FALSE);
	}
}

void CNetServerMultiMedia::OnChangeEditMmscPort() 
{
	UpdateData();
	if (m_nMmscPort < 0)
	{
		m_nMmscPort = 0;
		UpdateData(FALSE);
	}
}

void CNetServerMultiMedia::OnChangeEditPhone1() 
{
	UpdateData();
	if (m_sPhone1.GetLength() > 16)
	{
		m_sPhone1 = m_sPhone1.Left(16);
		UpdateData(FALSE);
	}
}

void CNetServerMultiMedia::OnChangeEditPhone2() 
{
	UpdateData();
	if (m_sPhone2.GetLength() > 16)
	{
		m_sPhone2 = m_sPhone2.Left(16);
		UpdateData(FALSE);
	}
}

void CNetServerMultiMedia::OnChangeEditPhone3() 
{
	UpdateData();
	if (m_sPhone3.GetLength() > 16)
	{
		m_sPhone3 = m_sPhone3.Left(16);
		UpdateData(FALSE);
	}
}

void CNetServerMultiMedia::OnOK() 
{
	m_ensure = TRUE;
	UpdateData();
	m_netMultimediaMsgCfg.bEnable = m_checkEnable.GetCheck();
	m_netMultimediaMsgCfg.gateWayPort = m_nGateWayPort;
	m_netMultimediaMsgCfg.mmscPort = m_nMmscPort;
	memcpy(m_netMultimediaMsgCfg.pDesPhoneNum[0],m_sPhone1.GetBuffer(0),sizeof(m_sPhone1.GetLength()));	
	memcpy(m_netMultimediaMsgCfg.pDesPhoneNum[1],m_sPhone2.GetBuffer(0),sizeof(m_sPhone2.GetLength()));	
	memcpy(m_netMultimediaMsgCfg.pDesPhoneNum[2],m_sPhone3.GetBuffer(0),sizeof(m_sPhone3.GetLength()));	
	memcpy(m_netMultimediaMsgCfg.pGateWayDomain,m_sGateWay, sizeof(m_sGateWay.GetLength()));
	memcpy(m_netMultimediaMsgCfg.pMmscDomain,m_sMmsc,sizeof(m_sMmsc.GetLength()));
	CDialog::OnOK();
}



