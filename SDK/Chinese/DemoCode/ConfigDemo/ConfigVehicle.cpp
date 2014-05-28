// ConfigVehicle.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigVehicle.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigVehicle dialog


CConfigVehicle::CConfigVehicle(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigVehicle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigVehicle)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigVehicle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigVehicle)
	DDX_Control(pDX, IDC_TAB_VEHICLE, m_ctrlVehicle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigVehicle, CDialog)
	//{{AFX_MSG_MAP(CConfigVehicle)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_VEHICLE, OnSelchangeTabVehicle)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigVehicle message handlers

BOOL CConfigVehicle::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTabControl();
	// TODO: Add extra initialization here
	_CWndCS(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CConfigVehicle::InitTabControl()
{
	CRect childRect;
	m_ctrlVehicle.GetClientRect(childRect);
	childRect.top += 4;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 30;
	
	m_TabVehicleDa.Create(IDD_DLG_VEHICLE_DATA,&m_ctrlVehicle);
	m_TabVehicleDa.MoveWindow(childRect);
	
	m_TabVehicleSt.Create(IDD_DLG_VEHICLE_STATE,&m_ctrlVehicle);
	m_TabVehicleSt.MoveWindow(childRect);

	m_TabTimeLS.Create(IDD_DLG_TIME_LAPSE,&m_ctrlVehicle);
	m_TabTimeLS.MoveWindow(childRect);
 

	m_ctrlVehicle.InsertItem(0, _CS("CarFunc.CarStatus"));
	m_ctrlVehicle.InsertItem(1, _CS("CarFunc.DelaySet"));
    m_ctrlVehicle.InsertItem(2, _CS("数据上传"));

	DoTab(0);
}

void CConfigVehicle::DoTab(int nTab)
{
	if(nTab>2)
	{
		nTab=2;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[3];
	bTab[0]=bTab[1]=bTab[2]=FALSE;
	bTab[nTab]=TRUE;

	SetDlgState(&m_TabVehicleSt,bTab[0]);
	SetDlgState(&m_TabTimeLS,bTab[1]);
	SetDlgState(&m_TabVehicleDa,bTab[2]);

}

void CConfigVehicle::SetDlgState(CWnd *pWnd, BOOL bShow)
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

void CConfigVehicle::OnSelchangeTabVehicle(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_ctrlVehicle.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

void CConfigVehicle::InitDlgInfo(SDK_CarStatusExchangeAll *pCarStaExg,SDK_CarDelayTimeConfig *pCarDelayTimeCfg,	SDK_SystemFunction *pSysFunc,int nAlarmInNum)
{
	if ( pSysFunc->vMobileCarFunction[SDK_MOBILEDVR_STATUS_EXCHANGE] && pSysFunc->vMobileCarFunction[SDK_MOBILEDVR_DELAY_SET])
	{
		m_TabVehicleSt.InitDlgInfo(pCarStaExg,nAlarmInNum);
		m_TabTimeLS.InitDlgInfo(pCarDelayTimeCfg);
		m_ctrlVehicle.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ctrlVehicle.ShowWindow(SW_HIDE);
// 		m_TabTimeLS.EnableWindow(FALSE);
// 		m_TabVehicleSt.EnableWindow(FALSE);
	}
	
}

void CConfigVehicle::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_TabTimeLS.SaveTimeLapseInfo()&&m_TabVehicleSt.SaveVehicleStInfo())
	{
		m_CarStaExg = m_TabVehicleSt.mCarStaExg;
		m_CarDelayTiemCfg = m_TabTimeLS.m_CarDelayTiemCfg;
		((CClientDemo5Dlg*)AfxGetMainWnd())->setVehicleDlg(&m_CarStaExg,&m_CarDelayTiemCfg);
	}

}

void CConfigVehicle::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetVehicleDlg();
}

void CConfigVehicle::CleanAll()
{
	//m_TabTimeLS.CleanAll();
	m_TabVehicleSt.CleanAll();
}
