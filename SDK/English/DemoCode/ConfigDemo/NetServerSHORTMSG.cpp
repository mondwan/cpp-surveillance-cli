// NetServerSHORTMSG.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerSHORTMSG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerSHORTMSG dialog


CNetServerSHORTMSG::CNetServerSHORTMSG(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerSHORTMSG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerSHORTMSG)
	m_sPhoneNum1 = _T("");
	m_sPhoneNum2 = _T("");
	m_sPhoneNum3 = _T("");
	m_nSendTimes = 0;
	//}}AFX_DATA_INIT
}


void CNetServerSHORTMSG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerSHORTMSG)
	DDX_Control(pDX, IDC_EDIT_SEND_TIMES, m_editSendTimes);
	DDX_Control(pDX, IDC_EDIT_PHONE3, m_editPhone3);
	DDX_Control(pDX, IDC_EDIT_PHONE2, m_editPhone2);
	DDX_Control(pDX, IDC_EDIT_PHONE1, m_editPhone1);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT_PHONE1, m_sPhoneNum1);
	DDX_Text(pDX, IDC_EDIT_PHONE2, m_sPhoneNum2);
	DDX_Text(pDX, IDC_EDIT_PHONE3, m_sPhoneNum3);
	DDX_Text(pDX, IDC_EDIT_SEND_TIMES, m_nSendTimes);
	DDV_MinMaxInt(pDX, m_nSendTimes, 0, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerSHORTMSG, CDialog)
	//{{AFX_MSG_MAP(CNetServerSHORTMSG)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerSHORTMSG message handlers

void CNetServerSHORTMSG::OnCheckEnable() 
{
	// TODO: Add your control notification handler code here
	BOOL bEnable = m_checkEnable.GetCheck();
	m_editPhone1.EnableWindow(bEnable);
	m_editPhone2.EnableWindow(bEnable);
	m_editPhone3.EnableWindow(bEnable);
	m_editSendTimes.EnableWindow(bEnable);
}

void CNetServerSHORTMSG::InitDlgInfo(SDK_NetShortMsgCfg *pNetShortMsgCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netShortMsgCfg,pNetShortMsgCfg,sizeof(SDK_NetShortMsgCfg));
	m_checkEnable.SetCheck(m_netShortMsgCfg.bEnable);
	m_sPhoneNum1 = m_netShortMsgCfg.pDesPhoneNum[0];
	m_sPhoneNum2 = m_netShortMsgCfg.pDesPhoneNum[1];
	m_sPhoneNum3 = m_netShortMsgCfg.pDesPhoneNum[2];
	m_nSendTimes = m_netShortMsgCfg.sendTimes; 
	UpdateData(FALSE);
	OnCheckEnable();
}

BOOL CNetServerSHORTMSG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	_CWndCS(this);
	return TRUE;  
}

void CNetServerSHORTMSG::OnOK() 
{
	// TODO: Add extra validation here
	m_ensure = TRUE;
	UpdateData();
	m_netShortMsgCfg.bEnable = m_checkEnable.GetCheck();
	m_netShortMsgCfg.sendTimes = m_nSendTimes;
	strncpy(m_netShortMsgCfg.pDesPhoneNum[0],m_sPhoneNum1,sizeof(m_netShortMsgCfg.pDesPhoneNum[0]));
	strncpy(m_netShortMsgCfg.pDesPhoneNum[1],m_sPhoneNum2,sizeof(m_netShortMsgCfg.pDesPhoneNum[1]));
	strncpy(m_netShortMsgCfg.pDesPhoneNum[2],m_sPhoneNum3,sizeof(m_netShortMsgCfg.pDesPhoneNum[2]));
	CDialog::OnOK();
}
