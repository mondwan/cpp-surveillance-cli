// NetAlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "NetAlarmDlg.h"
#include "ClientDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetAlarmDlg dialog


CNetAlarmDlg::CNetAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetAlarmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNetAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetAlarmDlg)
	DDX_Control(pDX, IDC_CMB_CHANNEL, m_cmbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CNetAlarmDlg)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetAlarmDlg message handlers
BOOL CNetAlarmDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_CWndCS(this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetAlarmDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
	int nChannel = m_cmbChannel.GetCurSel();
	if ( pParent && nChannel != -1)
	{
		
		pParent->NetAlarmMsg(nChannel, 1);
	}
}

void CNetAlarmDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
	int nChannel = m_cmbChannel.GetCurSel();
	if ( pParent )
	{
		pParent->NetAlarmMsg(nChannel, 0);
	}
}

void CNetAlarmDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	int nTotalChn = 16;
	if (m_pDevInfo)
	{
		nTotalChn = m_pDevInfo->nTotalChannel;
	}
	int i = 0;
	for (i = 0; i < nTotalChn; i++)
	{
		CString strChn;
		strChn.Format("%02d", i + 1);
		m_cmbChannel.AddString(strChn);
	}
	m_cmbChannel.SetCurSel(0);
}
