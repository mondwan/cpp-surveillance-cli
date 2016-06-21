// NetServerPMS.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerPMS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerPMS dialog


CNetServerPMS::CNetServerPMS(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerPMS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerPMS)
	m_strAddr = _T("");
	m_strBox = _T("");
	m_nNum = 0;
	m_nPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerPMS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerPMS)
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btnClear);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_btnEnable);
	DDX_Text(pDX, IDC_EDIT_ADDR1, m_strAddr);
	DDX_Text(pDX, IDC_EDIT_BOXID, m_strBox);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nNum);
	DDV_MinMaxInt(pDX, m_nNum, 0, 500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerPMS, CDialog)
	//{{AFX_MSG_MAP(CNetServerPMS)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerPMS message handlers
void CNetServerPMS::OnCheckEnable() 
{
	// TODO: Add your control notification handler code here
	BOOL bEnable = m_btnEnable.GetCheck();
	if (true == bEnable)
	{
		(char*)GetDlgItem(IDC_EDIT_ADDR1)->EnableWindow(TRUE);
		(char*)GetDlgItem(IDC_EDIT_BOXID)->EnableWindow(TRUE);
		(char*)GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
		(char*)GetDlgItem(IDC_EDIT_NUM)->EnableWindow(TRUE);
		m_netPMSCfg.Enable = true;
	}
	else
	{
		(char*)GetDlgItem(IDC_EDIT_ADDR1)->EnableWindow(FALSE);
		(char*)GetDlgItem(IDC_EDIT_BOXID)->EnableWindow(FALSE);
		(char*)GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
		(char*)GetDlgItem(IDC_EDIT_NUM)->EnableWindow(FALSE);
		m_netPMSCfg.Enable = false;
	}
	
}

void CNetServerPMS::OnBtnClear()
{
	bool bClear = m_btnClear.GetCheck();
	if(bClear)
	{
		m_nNum = 0;
	}
}

void CNetServerPMS::InitDlgInfo(SDK_PMSConfig *pNetPMSCfg,SDK_PhoneInfoNum *pNetPHCfg)
{
	m_ensure = FALSE;
	memcpy(&m_netPMSCfg,pNetPMSCfg,sizeof(SDK_PMSConfig));
	memcpy(&m_netPhCfg,pNetPHCfg,sizeof(SDK_PhoneInfoNum));
	m_btnEnable.SetCheck(m_netPMSCfg.Enable);
	m_nPort = m_netPMSCfg.port;
	m_strBox = m_netPMSCfg.boxid;
	CString strAddr;
	m_strAddr=m_netPMSCfg.servname;
	m_nNum = m_netPhCfg.nNum;
	OnCheckEnable();
	UpdateData(FALSE);
}


BOOL CNetServerPMS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNetServerPMS::OnOK() 
{
	// TODO: Add extra validation here
	//UpdateData();
	m_ensure = TRUE;
	UpdateData();
	m_netPMSCfg.Enable = m_btnEnable.GetCheck();
	m_netPMSCfg.port = m_nPort;
	strcpy(m_netPMSCfg.boxid,m_strBox.GetBuffer(0));
	strcpy(m_netPMSCfg.servname,m_strAddr);
	m_netPhCfg.nNum = m_nNum;
	CDialog::OnOK();
}

void CNetServerPMS::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
