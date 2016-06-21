// PeriodTimeSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "PeriodTimeSetDlg.h"

extern   CClientDemo5App   theApp;
#define RGB_REC		RGB(46,139,87)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeriodTimeSetDlg dialog


CPeriodTimeSetDlg::CPeriodTimeSetDlg(SDK_CONFIG_WORKSHEET *pPeriod /*= NULL*/,CWnd* pParent /*=NULL*/)
	: CDialog(CPeriodTimeSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPeriodTimeSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	OldResourceHanlde= AfxGetResourceHandle();  
	AfxSetResourceHandle(theApp.m_hInstance);
	if ( NULL != pPeriod )
	{
		memcpy( &m_period, pPeriod, sizeof( SDK_CONFIG_WORKSHEET ) );
	}
	else
	{
		ZeroMemory( &m_period, sizeof( SDK_CONFIG_WORKSHEET ) );
	}
	
	for (int i = 0; i < NET_N_TSECT; ++i)
	{
		m_pTimeSectValue[i] = m_period.tsSchedule[0] + i;
	}
}


void CPeriodTimeSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPeriodTimeSetDlg)
	DDX_Control(pDX, IDC_COMBO1, m_weekChoose);
	//}}AFX_DATA_MAP
	for (int i = 0; i < NET_N_TSECT; ++i)
	{
		int nID = IDC_B_TIME1_1 + i * 4;
		
		DDX_Text(pDX, nID, m_pTimeSectValue[i]->startHour);
		DDX_Text(pDX, nID + 1, m_pTimeSectValue[i]->startMinute);
		DDX_Text(pDX, nID + 2, m_pTimeSectValue[i]->endHour);
		DDX_Text(pDX, nID + 3, m_pTimeSectValue[i]->endMinute);
		
		int nIDCheck = IDC_CHECK1 + i;
		
		DDX_Check(pDX, nIDCheck, m_pTimeSectValue[i]->enable);
		
	}
}


BEGIN_MESSAGE_MAP(CPeriodTimeSetDlg, CDialog)
	//{{AFX_MSG_MAP(CPeriodTimeSetDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelChangeWeek)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK1, IDC_CHECK6, OnBnClickedCheck)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_B_TIME1_1, IDC_E_TIME6_2, OnEditChanged)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_B_TIME1_1, IDC_E_TIME6_2, OnEditKillFous)
	ON_BN_CLICKED(IDOK, CPeriodTimeSetDlg::OnOK)
	ON_BN_CLICKED(IDCANCEL,CPeriodTimeSetDlg::OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeriodTimeSetDlg message handlers

void CPeriodTimeSetDlg::OnOK()
{
	// TODO: Add extra validation here
	int nData = m_weekChoose.GetItemData( m_weekChoose.GetCurSel() );
	
	if ( 7 == nData )
	{
		for (int i = 1; i < 7; ++i)
		{
			memcpy ( &m_period.tsSchedule[i], m_period.tsSchedule[0], sizeof(m_period.tsSchedule[i]) );
		}
	}

	CDialog::OnOK();
}

void CPeriodTimeSetDlg::DrowLineInfo(int nWeek, int nSect)
{
	int nDayMinute = 24 * 60;
	
	//用于画图
	int nBeginMinute;//开始分
	int nEndMinute;//结束分
	
	int ni,nj;
	for (ni = 0; ni < NET_N_WEEKS ; ni++)
	{
		if ( !m_TimeLineDraw[ni].GetSafeHwnd() )
		{
			continue;
		}
		m_TimeLineDraw[ni].CleanAllSpace();
		
		for (nj = 0 ;nj < NET_N_TSECT ; nj++)
		{
			if (m_period.tsSchedule[ni][nj].enable == TRUE)
			{
				nBeginMinute = m_period.tsSchedule[ni][nj].startHour * 60 + m_period.tsSchedule[ni][nj].startMinute;
				nEndMinute	 = m_period.tsSchedule[ni][nj].endHour * 60 + m_period.tsSchedule[ni][nj].endMinute;
				
				if (nBeginMinute <= nEndMinute)
				{
					m_TimeLineDraw[ni].InsertDrawSpace(nBeginMinute / 2, nEndMinute / 2 , RGB_REC);
				}
			}
		}
		
		m_TimeLineDraw[ni].Draw();
	}
}

void CPeriodTimeSetDlg::UpdateTime(int nPeriod, int nTime)
{
	UpdateData();
	
	if ( 0 == nTime || 2 == nTime )
	{
		if ( *m_Time[nPeriod][nTime] > 24 )
		{
			*m_Time[nPeriod][nTime] = 24;
			*m_Time[nPeriod][nTime + 1] = 0;
			
			UpdateData(FALSE);
		}
	}
	else if ( 1 == nTime || 3 == nTime )
	{
		if ( *m_Time[nPeriod][nTime - 1] == 24 )
		{
			*m_Time[nPeriod][nTime] = 0;
			UpdateData(FALSE);
		}
		else if ( *m_Time[nPeriod][nTime] > 59 )
		{
			*m_Time[nPeriod][nTime] = 59;
			UpdateData(FALSE);
		}
	}
}

void CPeriodTimeSetDlg::OnCbnSelChangeWeek() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	int nData = m_weekChoose.GetItemData( m_weekChoose.GetCurSel()  );
	
	if ( 7 == nData )
	{
		for (int i = 0; i < NET_N_TSECT; ++i)
		{
			m_pTimeSectValue[i] = m_period.tsSchedule[0] + i;
		}
	}
	else
	{
		for (int i = 0; i < NET_N_TSECT; ++i)
		{
			m_pTimeSectValue[i] = m_period.tsSchedule[nData] + i;
		}
	}
	
	UpdateData(FALSE);
	
	DrowLineInfo( 0, 0 );
}

void CPeriodTimeSetDlg::OnEditChanged(UINT nID) 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	int nNum = nID - IDC_B_TIME1_1;
	int nSect = nNum / 4;	//组别
	
	int nWitch = nNum % 4;	//0开始时间小时. 1开始时间分钟 2结束时间小时. 3结束时间分钟


	BOOL bChange = FALSE; ;

	int &StartHour = m_pTimeSectValue[nSect]->startHour;
	int &StartMin = m_pTimeSectValue[nSect]->startMinute;
	int &EndHour = m_pTimeSectValue[nSect]->endHour;
	int &EndMin = m_pTimeSectValue[nSect]->endMinute;

	if ( 0 == nWitch || 2 == nWitch )//小时检查
	{
		if ( 0 == nWitch )
		{
			if ( StartHour < 0)
			{
				StartHour = 0;
				bChange = TRUE;
			}
			else if ( StartHour > 24)
			{
				StartHour = 24;
				bChange = TRUE;
			}

		}
		else
		{
			if ( EndHour < 0 )
			{
				EndHour = 0;
				bChange = TRUE;
			}
			else if ( EndHour > 24 )
			{
				EndHour = 24;
				bChange = TRUE;
			}
		}
	}
	else//分钟查检
	{
		if ( 1 == nWitch )
		{
			if ( StartMin < 0)
			{
				StartMin = 0;
				bChange = TRUE;
			}
			else if ( StartMin > 59)
			{
				StartMin = 59;
				bChange = TRUE;
			}

		}
		else
		{			
			if ( EndMin < 0 )
			{
				EndMin = 0;
				bChange = TRUE;
			}
			else if ( EndMin > 59 )
			{
				EndMin = 59;
				bChange = TRUE;
			}

		}
	}

	if (StartHour == 24)
	{
		StartMin = 0;
		bChange = TRUE;
	}	

	if (EndHour == 24)
	{
		EndMin = 0;
		bChange = TRUE;
	}	

	if (bChange)
	{
		GetDlgItem(nID)->SetFocus();
		UpdateData(FALSE);
	}
	
	int nWeek = m_weekChoose.GetItemData( m_weekChoose.GetCurSel() );
	if ( 7 == nWeek )
	{
		for (int i = 1; i < 7; ++i)
		{
			memcpy ( &m_period.tsSchedule[i], m_period.tsSchedule[0], sizeof(m_period.tsSchedule[i]) );
		}
	}

	DrowLineInfo( nWeek, nSect );
}

void CPeriodTimeSetDlg::OnEditKillFous(UINT nID) 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	int nNum = nID - IDC_B_TIME1_1;
	int nSect = nNum / 4;	//组别
	int nWitch = nNum % 4;	//0开始时间小时. 1开始时间分钟 2结束时间小时. 3结束时间分钟
	
	BOOL bChange = FALSE; ;
	
	int &StartHour = m_pTimeSectValue[nSect]->startHour;
	int &StartMin = m_pTimeSectValue[nSect]->startMinute;
	int &EndHour = m_pTimeSectValue[nSect]->endHour;
	int &EndMin = m_pTimeSectValue[nSect]->endMinute;
	
	if ( 0 == nWitch || 2 == nWitch )//小时检查
	{
		if ( EndHour < StartHour )
		{
			EndHour = StartHour;
			bChange = TRUE;
		}
	}
	else//分钟查检
	{
		if ( StartHour == EndHour && EndMin < StartMin )
		{
			EndMin = StartMin;
			bChange = TRUE;
		}
	}
	
	if (bChange)
	{
		UpdateData(FALSE);
	}
	
	int nWeek = m_weekChoose.GetItemData( m_weekChoose.GetCurSel() );
	if ( 7 == nWeek )
	{
		for (int i = 1; i < 7; ++i)
		{
			memcpy ( &m_period.tsSchedule[i], m_period.tsSchedule[0], sizeof(m_period.tsSchedule[i]) );
		}
	}
	DrowLineInfo( nWeek, nSect );
}

void CPeriodTimeSetDlg::OnBnClickedCheck(UINT nID) 
{
	// TODO: Add your control notification handler code here
	int nSect = nID - IDC_CHECK1;
	int nWeek = m_weekChoose.GetItemData( m_weekChoose.GetCurSel());
	
	int nTemp = nWeek;
	if ( 7 == nWeek )
	{
		nTemp = 0;
	}
	if ( ( (CButton *)GetDlgItem(nID) )->GetCheck() )
	{
		m_period.tsSchedule[nTemp][nSect].enable = TRUE;
	}
	else 
	{
		m_period.tsSchedule[nTemp][nSect].enable = FALSE;
	}
	
	if ( 7 == nWeek )
	{
		for (int i = 1; i < 7; ++i)
		{
			memcpy ( &m_period.tsSchedule[i], m_period.tsSchedule[0], sizeof(m_period.tsSchedule[i]) );
		}
	}
	
	DrowLineInfo( nTemp, nSect );
}

SDK_CONFIG_WORKSHEET *CPeriodTimeSetDlg::GetConfigWorkSheet()
{
	return &m_period;
}

BOOL CPeriodTimeSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	AfxSetResourceHandle(OldResourceHanlde);
	// TODO: Add extra initialization here
	CString strWeek[] = { "OneClick.Sun", "OneClick.Mon", "OneClick.Tue", "OneClick.Wed",
		"OneClick.Thu", "OneClick.Fri", "OneClick.Sat", "OneClick.All", "OneClick.WorkDay", "OneClick.FreeDay" };
	int nInsert = 0;
	for ( int i = 0; i < 8; ++i )
	{
		nInsert = m_weekChoose.AddString( _CS( strWeek[i] ) );
		m_weekChoose.SetItemData(nInsert, i);
	}
	
	if ( m_weekChoose.GetCount() > 0 )
	{
		CTime time = CTime::GetCurrentTime();
		m_weekChoose.SetCurSel(time.GetDayOfWeek() - 1);
	}
	
	int nWeek;
	
	CRect rectFrame(80, 80, 380, 102);
	for (nWeek = 0; nWeek < NET_N_WEEKS ; nWeek++)
	{
		rectFrame.top += 22;
		rectFrame.bottom += 22;
		
		m_TimeLineDraw[nWeek].Create(NULL, NULL, WS_VISIBLE | WS_BORDER, rectFrame, this, ID_TIME_DRAW + nWeek);
		
		m_TimeLineDraw[nWeek].SetMiddleText("");
		m_TimeLineDraw[nWeek].CleanAllSpace();
	}
	
	OnCbnSelChangeWeek();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPeriodTimeSetDlg::OnCancel()
{
	CDialog::OnCancel();
}
