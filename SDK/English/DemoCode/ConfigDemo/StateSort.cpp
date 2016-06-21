// StateSort.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "StateSort.h"
#include "VehicleState.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define AMOUNT 2
#define IDC_STATE_SORT	WM_USER + 7000
/////////////////////////////////////////////////////////////////////////////
// CStateSort dialog


CStateSort::CStateSort(SDK_CarStatusExchangeAll *pCarStaExg,CWnd* pParent /*=NULL*/)
: CDialog(CStateSort::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStateSort)
	//}}AFX_DATA_INIT
	nStateCount = StateCount;
	memset(mState,0,sizeof(mState));
	memcpy(&mStaSortExg,pCarStaExg,sizeof(SDK_CarStatusExchangeAll));
	/*	memset(&mStaSortCf,0,sizeof(SDK_CarDelayTimeConfig));*/
	n_update = FALSE;
	
	//mCarStaExg = (CDialog)GetParent()->mCarStaExg;
	
	
}


void CStateSort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStateSort)
	DDX_Control(pDX, IDC_CHECK_8, m_ctrlCheck8);
	DDX_Control(pDX, IDC_CHECK_7, m_ctrlCheck7);
	DDX_Control(pDX, IDC_CHECK_6, m_ctrlCheck6);
	DDX_Control(pDX, IDC_CHECK_5, m_ctrlCheck5);
	DDX_Control(pDX, IDC_CHECK_4, m_ctrlCheck4);
	DDX_Control(pDX, IDC_CHECK_3, m_ctrlCheck3);
	DDX_Control(pDX, IDC_CHECK_2, m_ctrlCheck2);
	DDX_Control(pDX, IDC_CHECK_1, m_ctrlCheck1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStateSort, CDialog)
//{{AFX_MSG_MAP(CStateSort)
ON_WM_SHOWWINDOW()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_CHECK_1, OnCheck1)
ON_BN_CLICKED(IDC_CHECK_2, OnCheck2)
ON_BN_CLICKED(IDC_CHECK_3, OnCheck3)
ON_BN_CLICKED(IDC_CHECK_4, OnCheck4)
ON_BN_CLICKED(IDC_CHECK_5, OnCheck5)
ON_BN_CLICKED(IDC_CHECK_6, OnCheck6)
ON_BN_CLICKED(IDC_CHECK_7, OnCheck7)
ON_BN_CLICKED(IDC_CHECK_8, OnCheck8)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStateSort message handlers

BOOL CStateSort::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	InitDlgInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStateSort::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
void CStateSort::InitDlgInfo()
{
	UpdateData(FALSE);
	int i;
	//	memcpy(&mStaSortExg,((CVehicleState*)GetParent())->mCarStaExg)
	//	mStaSortExg =;
	/*	mStaSortCf = ((CTimeLapseSet*)GetParent())->m_CarDelayTiemCfg;*/
	/*memcpy(&mStaSortExg,pCarStaExg,sizeof(mStaSortExg));*/
	for ( i =0; i<nStateCount; ++i)
	{
		if (mStaSortExg.exchangeAll[i].bExist)
		{
			
			switch (i)
			{
			case 0:
				m_ctrlCheck1.SetCheck(TRUE);
				break;
			case 1:
				m_ctrlCheck2.SetCheck(TRUE);
				break;
			case 2:
				m_ctrlCheck3.SetCheck(TRUE);
				break;
			case 3:
				m_ctrlCheck4.SetCheck(TRUE);
				break;
			case 4:
				m_ctrlCheck5.SetCheck(TRUE);
				break;
			case 5:
				m_ctrlCheck6.SetCheck(TRUE);
				break;
			case 6:
				m_ctrlCheck7.SetCheck(TRUE);
				break;
			case 7:
				m_ctrlCheck8.SetCheck(TRUE);
				break;
			}
			
		}
		else
		{
			switch (i)
			{
			case 0:
				m_ctrlCheck1.SetCheck(FALSE);
				break;
			case 1:
				m_ctrlCheck2.SetCheck(FALSE);
				break;
			case 2:
				m_ctrlCheck3.SetCheck(FALSE);
				break;
			case 3:
				m_ctrlCheck4.SetCheck(FALSE);
				break;
			case 4:
				m_ctrlCheck5.SetCheck(FALSE);
				break;
			case 5:
				m_ctrlCheck6.SetCheck(FALSE);
				break;
			case 6:
				m_ctrlCheck7.SetCheck(FALSE);
				break;
			case 7:
				m_ctrlCheck8.SetCheck(FALSE);
				break;
			}
			
		}
		
	}
}
void CStateSort::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CStateSort::OnOK() 
{
	// TODO: Add extra validation here
	if ( n_update == TRUE )
	{
		((CClientDemo5Dlg*)AfxGetMainWnd())->setVehicleDlg(&mStaSortExg);
		
	}
	CDialog::OnOK();
}

void CStateSort::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[0].bExist = m_ctrlCheck1.GetCheck();
	UpdateData(FALSE);
}

void CStateSort::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[1].bExist = m_ctrlCheck2.GetCheck();
}

void CStateSort::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[2].bExist = m_ctrlCheck3.GetCheck();
}

void CStateSort::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[3].bExist = m_ctrlCheck4.GetCheck();
}

void CStateSort::OnCheck5() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[4].bExist = m_ctrlCheck5.GetCheck();
}

void CStateSort::OnCheck6() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[5].bExist = m_ctrlCheck6.GetCheck();
}

void CStateSort::OnCheck7() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[6].bExist = m_ctrlCheck7.GetCheck();
}

void CStateSort::OnCheck8() 
{
	// TODO: Add your control notification handler code here
	n_update = TRUE;
	mStaSortExg.exchangeAll[7].bExist = m_ctrlCheck8.GetCheck();
}
