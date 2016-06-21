// TimeLapseSet.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "TimeLapseSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeLapseSet dialog


CTimeLapseSet::CTimeLapseSet(CWnd* pParent /*=NULL*/)
: CDialog(CTimeLapseSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeLapseSet)
	m_DelayC = 0;
	m_DelayO = 0;
	//}}AFX_DATA_INIT
	memset(&m_CarDelayTiemCfg,0,sizeof(m_CarDelayTiemCfg));
	
}


void CTimeLapseSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeLapseSet)
	DDX_Control(pDX, IDC_ENABLE_CLOSE, m_ctrlEnableC);
	DDX_Control(pDX, IDC_DELAY_CLOSE, m_ctrlDelayC);
	DDX_Control(pDX, IDC_DELAY_OPEN, m_ctrlDelayO);
	DDX_Control(pDX, IDC_ENABLE_OPEN, m_ctrlEnableO);
	DDX_Text(pDX, IDC_DELAY_CLOSE, m_DelayC);
	DDX_Text(pDX, IDC_DELAY_OPEN, m_DelayO);
	//}}AFX_DATA_MAP
}
BOOL CTimeLapseSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CTimeLapseSet::InitDlgInfo(SDK_CarDelayTimeConfig *pCarDelayTimeCfg, bool bShow)
{
	memcpy(&m_CarDelayTiemCfg,pCarDelayTimeCfg,sizeof(SDK_CarDelayTimeConfig));
	
	bool njudge;
	njudge = m_CarDelayTiemCfg.bStartDelay;
	m_ctrlEnableO.SetCheck(njudge);
	njudge = m_CarDelayTiemCfg.bCloseDelay;
	m_ctrlEnableC.SetCheck(njudge);
	
	CString  str;
	str.Format(_T("%d"),m_CarDelayTiemCfg.timeStartDelay);
	m_ctrlDelayO.SetWindowText(str);
	
	str.Format(_T("%d"),m_CarDelayTiemCfg.timeCloseDelay);
	m_ctrlDelayC.SetWindowText(str);
	
	OnEnableOpen();
	OnEnableClose();
	if (!bShow)
	{
	}
}

BOOL CTimeLapseSet::SaveTimeLapseInfo()
{
	
	if (sizeof(m_CarDelayTiemCfg) != 0)
	{
		m_CarDelayTiemCfg.bStartDelay = m_ctrlEnableO.GetCheck();
		m_CarDelayTiemCfg.bCloseDelay = m_ctrlEnableC.GetCheck();
		CString str ;
		m_ctrlDelayO.GetWindowText(str);
		m_CarDelayTiemCfg.timeStartDelay = atoi(str);
		m_ctrlDelayC.GetWindowText(str);
		m_CarDelayTiemCfg.timeCloseDelay = atoi(str);
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

BEGIN_MESSAGE_MAP(CTimeLapseSet, CDialog)
//{{AFX_MSG_MAP(CTimeLapseSet)
ON_BN_CLICKED(IDC_ENABLE_OPEN, OnEnableOpen)
ON_BN_CLICKED(IDC_ENABLE_CLOSE, OnEnableClose)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeLapseSet message handlers

void CTimeLapseSet::OnEnableOpen() 
{
	// TODO: Add your control notification handler code here
	bool judge;
	judge = m_ctrlEnableO.GetCheck();
	m_ctrlDelayO.EnableWindow(judge);
}

void CTimeLapseSet::OnEnableClose() 
{
	// TODO: Add your control notification handler code here
	bool judge;
	judge = m_ctrlEnableC.GetCheck();
	m_ctrlDelayC.EnableWindow(judge);
	
}
