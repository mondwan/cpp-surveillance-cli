// ConfigDigitalChannel.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigDigitalChannel.h"
#include "ClientDemo5Dlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDigitalChannel dialog


CConfigDigitalChannel::CConfigDigitalChannel(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDigitalChannel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDigitalChannel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nLastItem = -1;
}


void CConfigDigitalChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDigitalChannel)
	DDX_Control(pDX, IDC_TAB_DIGITAL, m_ctlTabDigital);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDigitalChannel, CDialog)
	//{{AFX_MSG_MAP(CConfigDigitalChannel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DIGITAL, OnSelchangeTabDigital)
	ON_BN_CLICKED(IDC_BTN_REFRUSH, OnBtnRefrush)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDigitalChannel message handlers

BOOL CConfigDigitalChannel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
    
	InitTabControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDigitalChannel::InitTabControl()
{
     CRect childRect;
	 m_ctlTabDigital.GetClientRect(childRect);
	 
	 childRect.top += 4;
	 childRect.bottom -= 4;
	 childRect.left += 4;
	 childRect.right -= 30;
	 
	 m_dlgDigitalChannel.Create(CDigitalChannelDlg::IDD, &m_ctlTabDigital);
	 m_dlgDigitalChannel.MoveWindow(&childRect);

	 m_dlgChannelMode.Create(CDlgChannelMode::IDD, &m_ctlTabDigital);
	 m_dlgChannelMode.MoveWindow(&childRect);


	 m_dlgChannelStatus.Create(CDlgChannelStatus::IDD, &m_ctlTabDigital);
	 m_dlgChannelStatus.MoveWindow(&childRect);
	 

	 m_ctlTabDigital.InsertItem(0, _CS("DigitalChannel.DigitalChannel"));
     m_ctlTabDigital.InsertItem(1, _CS("DigitalChannel.ChannelMode"));
	 m_ctlTabDigital.InsertItem(2, _CS("DigitalChannel.ChannelStatus"));

	 m_ctlTabDigital.SetCurSel(0);
 	 DoTab(0);
	 m_nLastItem = 0;

}

void CConfigDigitalChannel::DoTab(int nTab)
{
	if (nTab > 3)
	{
		nTab = 3;
	}
	else if(nTab < 0)
	{
		nTab = 0;
	}

	BOOL bTab[4];
	bTab[0] = bTab[1] = bTab[2]= bTab[3] = FALSE;
	bTab[nTab] = TRUE;
	
	SetDlgState(&m_dlgDigitalChannel, bTab[0]);
	SetDlgState(&m_dlgChannelMode, bTab[1]);
	SetDlgState(&m_dlgChannelStatus, bTab[2]);
	m_nLastItem = nTab;
}	

void CConfigDigitalChannel::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if(bShow)
	{  
	    pWnd->ShowWindow(SW_SHOW);
	}
    else
	{
	    pWnd->ShowWindow(SW_HIDE);
	}
}

void CConfigDigitalChannel::OnSelchangeTabDigital(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_ctlTabDigital.GetCurSel();
	if(nSelect >= 0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

void CConfigDigitalChannel::OnBtnRefrush() 
{
	// TODO: Add your control notification handler code here
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetNetDecorderCfg();
}

void CConfigDigitalChannel::OnOK() 
{
	// TODO: Add extra validation here

	if (0 == m_nLastItem)
	{
		m_dlgDigitalChannel.SaveDigitalChnCfg();
	}
	else if (1 == m_nLastItem)
	{
		m_dlgChannelMode.SaveChnModeCfg();
		
	}
    
//	CDialog::OnOK();
}

void CConfigDigitalChannel::ClearAll()
{
	m_dlgChannelMode.ClearAll();
	m_dlgChannelStatus.ClearAll();
	m_dlgDigitalChannel.ClearAll();
}
