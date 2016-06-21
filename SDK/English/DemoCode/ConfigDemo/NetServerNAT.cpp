// NetServerNAT.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerNAT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerNAT dialog


CNetServerNAT::CNetServerNAT(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerNAT::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerNAT)
	m_iMTU = 0;
	//}}AFX_DATA_INIT
}


void CNetServerNAT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerNAT)
	DDX_Control(pDX, IDC_CHECK1, m_checkEnable);
	DDX_Text(pDX, IDC_EDIT1, m_iMTU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerNAT, CDialog)
	//{{AFX_MSG_MAP(CNetServerNAT)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerNAT message handlers

void CNetServerNAT::OnOK() 
{
	// TODO: Add extra validation here
	SaveConfig();
	m_ensure = TRUE;
	CDialog::OnOK();
}
void CNetServerNAT::InitDlgInfo(SDK_NatConfig *pNatCfg)
{
	m_ensure = FALSE;
	memcpy(&m_natCfg,pNatCfg,sizeof(SDK_NatConfig));
	m_iMTU = m_natCfg.nMTU;
	m_checkEnable.SetCheck(m_natCfg.bEnable);
	UpdateData(FALSE);
	OnCheck1();
	return;
}

BOOL CNetServerNAT::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetServerNAT::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	BOOL bEnable = m_checkEnable.GetCheck();
	GetDlgItem(IDC_EDIT1)->EnableWindow(bEnable);
}

void CNetServerNAT::SaveConfig()
{
	UpdateData(TRUE);
	m_natCfg.bEnable = m_checkEnable.GetCheck();
	m_natCfg.nMTU = m_iMTU;
}