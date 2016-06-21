// RecordPeriodDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RecordPeriodDlg.h"
#include "RemotePlaybackDlg.h"

#define RGB_REC_NORMAL	RGB(0,255,0)
#define RGB_REC_DETECT  RGB(100,100,100)
#define RGB_REC_ALARM  RGB(255,0,0)
#define RGB_REC_HAND   RGB(0,0,255)

#define ID_TIME_DRAW		(WM_USER + 1100)
#define ID_TIME_HOUR		(WM_USER + 1132)

const unsigned int COLOR[]={0, RGB_REC_NORMAL, RGB_REC_ALARM, RGB_REC_DETECT, 0, RGB_REC_HAND};
// CRecordPeriodDlg 对话框

//IMPLEMENT_DYNAMIC(CRecordPeriodDlg, CDialog)

CRecordPeriodDlg::CRecordPeriodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordPeriodDlg::IDD, pParent)
{
	m_nCurHour = 0 ;
	m_nCurMin = 0;
	m_nCurSec = 0;
	m_bDown = false;
	m_bShow = false;
	memset( &m_recTime, 0, sizeof(m_recTime) );
}

CRecordPeriodDlg::~CRecordPeriodDlg()
{
}

void CRecordPeriodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecordPeriodDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_SLIDER_MOUSEMOVE, OnSliderMouseMove)
	ON_MESSAGE(WM_SLIDER_LBUTDOWN, OnSliderLButtonDown)
	ON_MESSAGE(WM_SLIDER_LBUTUP, OnSliderLButtonUp)
	ON_MESSAGE(WM_LBUTUP, OnTimeLineLButtonUp)
	ON_MESSAGE(WM_LDBUTUP, OnTimeLineDblClk)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CRecordPeriodDlg 消息处理程序

BOOL CRecordPeriodDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	//CRect WndRect;
	//GetClientRect( &WndRect );
	//获取滑动条和滑动块的位置信息
	//m_rectHourSlider.SetRect(17,30, WndRect.Width() - 31, 38 );
	//m_rectDaySlider.SetRect( 17, 80, WndRect.Width() - 19, 92);
	//m_sizeThumb.cx = 9;
	//m_sizeThumb.cy = 8;
	CString strText;
	CRect drawRect;
	drawRect.left = 0;
	drawRect.right = 0;
	drawRect.top = 0;
	drawRect.bottom = 0;
	strText = _CS(_T("Playback.Minutes"));
	m_StaticMin.Create(strText, WS_VISIBLE, drawRect,this, ID_TIME_HOUR + 1 );
	strText = _CS(_T("Playback.Hours"));
	m_StaticHour.Create(strText, WS_VISIBLE, drawRect,this, ID_TIME_HOUR );
	
	CRect RectStatic;
	RectStatic.left = 0;
	RectStatic.right = 0;
	RectStatic.top = 0;
	RectStatic.bottom = 0;
	for (int i = 0; i <= 24; i ++)
	{
		CString strHour;
		strHour.Format(_T("%d"), i);
		m_StaticH[i].Create(strHour, WS_VISIBLE, RectStatic,this, ID_STATIC_HOUR + i );
	}
	for ( int j = 0; j <= 12; j ++)
	{
		CString strMin;
		strMin.Format(_T("%d"), j * 5 );
		m_StaticM[j].Create(strMin, WS_VISIBLE, RectStatic,this, ID_STATIC_MINUTE + j );
	}
	
	m_TimeHourDraw.Create(NULL, NULL, WS_VISIBLE | WS_BORDER , m_rectHourSlider, this, ID_TIME_DRAW);
	//	m_TimeHourDraw.InitColourNum(60*60);
	//以分钟计算，暂时不计算到秒
	m_TimeHourDraw.InitColourNum(60);
	
	m_TimeDayDraw.Create(NULL, NULL, WS_VISIBLE | WS_BORDER , m_rectDaySlider, this, ID_TIME_DRAW + 1);
	//m_TimeDayDraw.InitColourNum(24 * 60 * 60);
	m_TimeDayDraw.InitColourNum(24 * 60);
	
	
	//24小时的滑动块
	//CRect rectThum(m_rectDaySlider.left - m_sizeThumb.cx / 2, m_rectDaySlider.bottom, 
	//	m_rectDaySlider.left + m_sizeThumb.cx / 2, m_rectDaySlider.bottom + m_sizeThumb.cy);
	CRect rectThum;
	m_DayThum.Create( _T(""), WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, rectThum, this, ID_BTN_THUM );
	//m_DayThum.SetLabelPosition( m_rectDaySlider.bottom, m_rectDaySlider.left, m_rectDaySlider.right - m_rectDaySlider.left );
	
	//1小时的滑动块
	//CRect rectThum2(m_rectHourSlider.left - m_sizeThumb.cx / 2, m_rectHourSlider.bottom, 
	//	m_rectHourSlider.left + m_sizeThumb.cx / 2, m_rectHourSlider.bottom + m_sizeThumb.cy);
	CRect rectThum2;
	m_HourThum.Create( _T(""), WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, rectThum2, this, ID_BTN_THUM + 1 );
	//m_HourThum.SetLabelPosition( m_rectHourSlider.bottom, m_rectHourSlider.left, m_rectHourSlider.right - m_rectHourSlider.left );
	
	
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	CFont *pFont = GetFont();
	pFont->GetLogFont(&lf);
	lf.lfHeight = 12;	
	m_font.CreateFontIndirect(&lf);
	///CRect staticRect(rectThum2.right + 5, rectThum2.top + 2, rectThum2.right + 50, rectThum2.top + 14);
	CRect staticRect;
	m_timeCaption.Create(_T(""), WS_CHILD|WS_VISIBLE, staticRect, this, ID_CAPTION_STATIC);
	m_timeCaption.SetFont(&m_font);
	
	m_timeCaption.SetTextColor(RGB(255,255,255));
	m_timeCaption.SetBackFlush(true);
	m_timeCaption.SetBackColor(RGB(34,34,34));
	m_timeCaption.SetWindowText(_T("00:00:00"));  //以小时和分钟显示，暂时不显示秒
	
	m_bShow = true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRecordPeriodDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}

void CRecordPeriodDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}

//滑动块移动事件
LRESULT CRecordPeriodDlg::OnSliderMouseMove(WPARAM wParam, LPARAM lParam)
{
	CRect wndRect;
	GetClientRect(&wndRect);
	//24小时滑动块
	if ( wParam == ID_BTN_THUM )
	{	
		//移动1小时滑动块		
		int nUnit = m_rectDaySlider.right - m_rectDaySlider.left;

		int nTime = ((24 * 3600) * (int)lParam) / nUnit;

		int nSecond = 	nTime % 3600;

		int nMin = nSecond / 60;
		int nSec = nSecond % 60;

		if ( nMin == 60 )
		{
			nMin = 59;
			nSec = 59;
		}
		m_nCurMin = nMin;
		m_nCurSec = nSec;

		int nHourUnit = m_rectHourSlider.right - m_rectHourSlider.left;
		int nHourPos = (nSecond * nHourUnit) / (3600);

		CRect rectHourThum(m_rectHourSlider.left + nHourPos - m_sizeThumb.cx / 2, 
			m_rectHourSlider.bottom, 
			m_rectHourSlider.left + nHourPos + m_sizeThumb.cx / 2, 
			m_rectHourSlider.bottom + m_sizeThumb.cy);
		m_HourThum.MoveWindow(rectHourThum);
		m_HourThum.Invalidate();

		int nHour = nTime / 3600;
		//由于滑动块的移动，1小时的录像时间显示条需要变化，不同的小时有不同的录像时间段
		if ( m_nCurHour != nHour && nHour != 24 )
		{
			m_TimeHourDraw.SetPeriod( (COLORREF *)m_recTime[nHour] );
			m_TimeHourDraw.Draw();

			m_nCurHour = nHour;	
			m_HourThum.Invalidate();
		}

		CString strCaption;
		strCaption.Format(_T("%02d:%02d:%02d"), m_nCurHour, nMin, nSec);
		//如果提示框位置超过对话框范围
		if ( rectHourThum.right + 5 + STATIC_WIDTH > wndRect.Width())
		{
			CRect staticRect(rectHourThum.left - 55, rectHourThum.top + 2, rectHourThum.left - 5, rectHourThum.top + 14);
			m_timeCaption.MoveWindow(staticRect);
		}
		else
		{
			CRect staticRect(rectHourThum.right + 5, rectHourThum.top + 2, rectHourThum.right + 55, rectHourThum.top + 14);
			m_timeCaption.MoveWindow(staticRect);
		}
		m_timeCaption.SetWindowText(strCaption);
	}
	//1小时的滑动块
	else if ( wParam == ID_BTN_THUM + 1 )
	{
		//移动24小时滑动块
		int nHourUnit =  m_rectHourSlider.right - m_rectHourSlider.left;
		int nTime = (3600 * (int)lParam) / nHourUnit;

		DWORD lSecond = m_nCurHour * 3600 + nTime;

		//计算有多少个象素点，滑动条就多少等份
		int nUnit = m_rectDaySlider.right - m_rectDaySlider.left;

		int nPos = (lSecond * nUnit) / (24 * 3600);

		//得到滑动块位置
		CRect rectThum(m_rectDaySlider.left + nPos - m_sizeThumb.cx / 2, 
			m_rectDaySlider.bottom, 
			m_rectDaySlider.left + nPos + m_sizeThumb.cx / 2,
			m_rectDaySlider.bottom + m_sizeThumb.cy);
		m_DayThum.MoveWindow(rectThum);
		m_DayThum.Invalidate();


		CRect rectHourThum;
		m_HourThum.GetWindowRect(&rectHourThum);
		ScreenToClient(rectHourThum);
		int nMin = nTime / 60;
		int nSec = nTime % 60;
		if ( nMin == 60 )
		{
			nMin = 59;
			nSec = 59;
		}

		m_nCurMin = nMin;
		m_nCurSec = nSec;

		CString strCaption;
		strCaption.Format(_T("%02d:%02d:%02d"), m_nCurHour, nMin, nSec);
		//如果提示框位置超过对话框范围
		if ( rectHourThum.right + 5 + STATIC_WIDTH > wndRect.Width() )
		{
			CRect staticRect(rectHourThum.left - 55, rectHourThum.top + 2, rectHourThum.left - 5, rectHourThum.top + 14);
			m_timeCaption.MoveWindow(staticRect);
		}
		else
		{
			CRect staticRect(rectHourThum.right + 5, rectHourThum.top + 2, rectHourThum.right + 55, rectHourThum.top + 14);
			m_timeCaption.MoveWindow(staticRect);
		}
		m_timeCaption.SetWindowText(strCaption);

	}
	//开始时间线
	else if ( wParam == ID_BTN_THUM + 2 )
	{

	}
	//结束时间线
	else if ( wParam == ID_BTN_THUM + 3 )
	{

	}

	m_bShow = true;
	return 0;
}

/************************************************************************/
/*      
设置播放进度
SetSliderPos（char *pTime）
参数：pTime 时间结构体
进度以时间为准，送入当前播放的时间，内部计算pos                                                                
*/
/************************************************************************/
void CRecordPeriodDlg::SetSliderPos(short nHour, short nMin, short nSec) 
{
	if ( m_bDown )
	{
		return;
	}
	DWORD lSecond = nHour * 3600 + nMin * 60 + nSec;

	//是否非法值
	if ( lSecond > 24 * 3600 )
	{
		return;
	}

	//计算有多少个象素点，滑动条就多少等份
	int nUnit = m_rectDaySlider.right - m_rectDaySlider.left;

	int nPos = (lSecond * nUnit) / (24 * 3600);

	//得到滑动块位置
	CRect rectThum(m_rectDaySlider.left + nPos - m_sizeThumb.cx / 2, 
		m_rectDaySlider.bottom, 
		m_rectDaySlider.left + nPos + m_sizeThumb.cx / 2, 
		m_rectDaySlider.bottom + m_sizeThumb.cy);

	m_DayThum.MoveWindow(rectThum);

	//由于滑动块的移动，1小时的录像时间显示条需要变化，不同的小时有不同的录像时间段
	if ( m_nCurHour != nHour )
	{
		m_TimeHourDraw.SetPeriod( (COLORREF *)m_recTime[nHour] );
		m_TimeHourDraw.Draw();

		m_HourThum.Invalidate();
		m_nCurHour = nHour ;
	}

	//下面处理1小时的滑动块位置
	int nHourUnit = m_rectHourSlider.right - m_rectHourSlider.left;

	DWORD lHourSecond = nMin * 60 + nSec;
	int nHourPos = (lHourSecond * nHourUnit) / (3600);

	CRect rectHourThum(m_rectHourSlider.left + nHourPos - m_sizeThumb.cx / 2, 
		m_rectHourSlider.bottom, 
		m_rectHourSlider.left + nHourPos + m_sizeThumb.cx / 2, 
		m_rectHourSlider.bottom + m_sizeThumb.cy);
	m_HourThum.MoveWindow(rectHourThum);


	CString strCaption;
	strCaption.Format(_T("%02d:%02d:%02d"), nHour, nMin, nSec);

	CRect WndRect;
	GetClientRect(&WndRect);
	//如果提示框位置超过对话框范围
	if ( rectHourThum.right + 5 + STATIC_WIDTH > WndRect.Width() )
	{
		CRect staticRect(rectHourThum.left - 55, rectHourThum.top + 2, rectHourThum.left -5, rectHourThum.top + 14);
		m_timeCaption.MoveWindow(staticRect);
	}
	else
	{
		CRect staticRect(rectHourThum.right + 5, rectHourThum.top + 2, rectHourThum.right + 55, rectHourThum.top + 14);
		m_timeCaption.MoveWindow(staticRect);
	}
	m_timeCaption.SetWindowText(strCaption);
}

short CRecordPeriodDlg::GetSelectTime(short * nStartHour, short * nStartMin, short * nEndHour, short * nEndMin) 
{
	*nStartHour = m_nCurHour;
	*nStartMin = m_nCurMin;

	//根据结束时间线位置，计算结束时间	
	*nEndHour = 23;
	*nEndMin = 59;

	return 1;
}

LRESULT CRecordPeriodDlg::OnTimeLineLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByTime)
	{
		((CRemotePlaybackDlg*)GetParent())->OnStop();
	}
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByName)
	{
		((CRemotePlaybackDlg*)GetParent())->OnStop();
	}
	int nHour = 0;
	int nMin  = 0;
	int nSec  = 0;
	//小时时间条
	if ( wParam == ID_TIME_DRAW )
	{
		nHour = m_rectHourSlider.right - m_rectHourSlider.left;
		int nTime = (3600 * (int)lParam) / nHour;
		//换算成小时，分，秒
		nMin = nTime / 60;
		nSec = nTime % 60; 
		nHour = m_nCurHour;
	//	if ( g_pispView->IsSyncMode() )
		{
		//	for ( int i = 0; i < MAXWNDTOTAL; i ++)
			{
			//	g_pispView->SeekPlay(i, m_nCurHour, nMin, nSec);
			}
		}
	//	else
		{
			//g_pispView->SeekPlay(-1, m_nCurHour, nMin, nSec);
		}

		//主要是为了移动滑动块
		SetSliderPos( m_nCurHour, nMin, nSec);

		m_nCurMin = nMin;
	}
	//24小时时间条
	else if ( wParam == ID_TIME_DRAW + 1 )
	{
		nHour = m_rectDaySlider.right - m_rectDaySlider.left;

		//得到当前位置的时间
		int nTime = ((24 * 3600) * (int)lParam) / nHour;
		//换算成小时，分，秒
		nHour = nTime / 3600;
		nMin = ( nTime % 3600) / 60;
		nSec = (nTime % 3600) % 60; 

	//	if ( g_pispView->IsSyncMode() )
		{
		//	for ( int i = 0; i < MAXWNDTOTAL; i ++)
			{
			//	g_pispView->SeekPlay(i, nHour, nMin, nSec);
			}
		}
	//	else
		{
		//	g_pispView->SeekPlay(-1, nHour, nMin, nSec);
		}

		//g_pispView->SeekPlay(-1, nHour, nMin, nSec);

		//主要是为了移动滑动块
		SetSliderPos( nHour, nMin, nSec);

		m_nCurHour = nHour;
		m_nCurMin = nMin;
		m_nCurSec = nSec;
	}
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByTime)
	{
		SDK_SYSTEM_TIME sTime;
		sTime.hour = nHour;
		sTime.minute = nMin;
		sTime.second = nSec;
		((CRemotePlaybackDlg*)GetParent())->OnPlayByTime((char*)&sTime,false);
	}
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByName)
	{
		SDK_SYSTEM_TIME sTime;
		sTime.hour = nHour;
		sTime.minute = nMin;
		sTime.second = nSec;
		((CRemotePlaybackDlg*)GetParent())->OnPlayByName((char*)&sTime,false);
	}
	return 0;
}

LRESULT CRecordPeriodDlg::OnSliderLButtonDown(WPARAM wParam, LPARAM lParam)
{
	m_bDown = true;	

	return 0;
}

LRESULT CRecordPeriodDlg::OnSliderLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByTime)
	{
		((CRemotePlaybackDlg*)GetParent())->OnStop();
	}
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByName)
	{
		((CRemotePlaybackDlg*)GetParent())->OnStop();
	}
	int nHour = 0;
	int nMin = 0;
	int nSec = 0;
	//24小时滑动块
	if ( wParam == ID_BTN_THUM )
	{
		int nUnit = m_rectDaySlider.right - m_rectDaySlider.left;

		//得到当前位置的时间
		int nTime = ((24 * 3600) * (int)lParam) / nUnit;
		//换算成小时，分，秒
		nHour = nTime / 3600;
		nMin = ( nTime % 3600) / 60;
		nSec = (nTime % 3600) % 60; 

		//if ( g_pispView->IsSyncMode() )
		{
		//	for ( int i = 0; i < MAXWNDTOTAL; i ++)
			{
			//	g_pispView->SeekPlay(i, nHour, nMin,nSec);
			}
		}
		//else
		{
		//	g_pispView->SeekPlay(-1, nHour, nMin,nSec);
		}
		
	}
	//1小时的滑动块
	else if ( wParam == ID_BTN_THUM + 1 )
	{
		int nHourUnit = m_rectHourSlider.right - m_rectHourSlider.left;
		int nTime = (3600 * (int)lParam) / nHourUnit;
		//换算成小时，分，秒
		nMin = nTime / 60;
		nSec = nTime % 60; 
		nHour = m_nCurHour;
	//	if ( g_pispView->IsSyncMode() )
		{
			//for ( int i = 0; i < MAXWNDTOTAL; i ++)
			{
			//	g_pispView->SeekPlay(i, m_nCurHour, nMin, nSec);
			}
		}
	//	else
		{
			//g_pispView->SeekPlay(-1, m_nCurHour, nMin, nSec);
		}
	}
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByTime)
	{
		SDK_SYSTEM_TIME sTime;
		sTime.hour = nHour;
		sTime.minute = nMin;
		sTime.second = nSec;
		((CRemotePlaybackDlg*)GetParent())->OnPlayByTime((char*)&sTime,false);
	}
	if (((CRemotePlaybackDlg*)GetParent())->m_bDownloadByName)
	{
		SDK_SYSTEM_TIME sTime;
		sTime.hour = nHour;
		sTime.minute = nMin;
		sTime.second = nSec;
		((CRemotePlaybackDlg*)GetParent())->OnPlayByName((char*)&sTime,false);
	}
	m_bDown = false;

	return 0;
}

LRESULT CRecordPeriodDlg::OnTimeLineDblClk(WPARAM wParam, LPARAM lParam)
{

	m_bDown = true;
	SetTimer(1, 1000, NULL);

	m_bDown = false;
	return 0;
}

void CRecordPeriodDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//属于小时条范围
	if ( point.x > m_rectHourSlider.left && point.x < m_rectHourSlider.right
		&& point.y >= m_rectHourSlider.top - 5 && point.y <= m_rectHourSlider.bottom + 5 )
	{
		OnTimeLineLButtonUp(ID_TIME_DRAW, point.x - m_rectHourSlider.left);	
	}
	else if ( point.x > m_rectDaySlider.left && point.x < m_rectDaySlider.right
		&& point.y >= m_rectDaySlider.top - 5 && point.y <= m_rectDaySlider.bottom + 5 )
	{
		OnTimeLineLButtonUp(ID_TIME_DRAW + 1, point.x - m_rectDaySlider.left);	
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CRecordPeriodDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bDown = true;
	//属于小时条范围
	if ( point.x > m_rectHourSlider.left && point.x < m_rectHourSlider.right
		&& point.y >= m_rectHourSlider.top - 5 && point.y <= m_rectHourSlider.bottom + 5 )
	{
		SetTimer(1, 1000, NULL);
	}
	else if ( point.x > m_rectDaySlider.left && point.x < m_rectDaySlider.right
		&& point.y >= m_rectDaySlider.top - 5 && point.y <= m_rectDaySlider.bottom + 5 )
	{
		SetTimer(1, 1000, NULL);
	}
	m_bDown = false;
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CRecordPeriodDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nHour = 0;
	int nMin = 0;
	int nSec = 0;

	//CTime tim;

	time_t timestamp = H264_PLAY_GetCurTimeStamp(40);

	tm *newtime = localtime( &timestamp ); 

	if (newtime)
	{
		SetSliderPos( newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
	}
	CDialog::OnTimer(nIDEvent);
}

//更新录象信息
void CRecordPeriodDlg::UpdateTimeSect(const unsigned char cRecordBitMap[720])
{
	//处理录象信息
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			int nIndex = (i * 60 + j) / 2;
			if ((i * 60 + j) % 2)
			{
				m_nTimeSect[i][j] = (cRecordBitMap[nIndex] >> 4) & 0xF;
			}
			else
			{
				m_nTimeSect[i][j] = cRecordBitMap[nIndex] & 0xF;
			}
			//保存录象类型到m_recTime
			switch ( m_nTimeSect[i][j] )
			{
			case 0:
				m_recTime[i][j] = 0;
				break;
			case 1:
				m_recTime[i][j] = RGB_REC_NORMAL;  //普通录象
				break;
			case 2:
				m_recTime[i][j] = RGB_REC_ALARM;   //报警录象
				break;
			case 3:
				m_recTime[i][j] = RGB_REC_DETECT;   //检测录象
				break;
			case 4:
				m_recTime[i][j] = RGB_REC_HAND;   //手动录象
				break;
			case 5:
				m_recTime[i][j] = RGB_REC_HAND;   //手动录象
				break;
			default:
				m_recTime[i][j] = 0;   
				break;
			}
		}
	}

	//绘制刻度
	m_TimeDayDraw.SetPeriod( (COLORREF* )m_recTime );
	m_TimeDayDraw.Draw();

	m_TimeHourDraw.SetPeriod( m_recTime[m_nCurHour] );
	m_TimeHourDraw.Draw();

	SetTimer(1, 1000, NULL);
}
void CRecordPeriodDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if ( !m_bShow )
	{
		return;
	}

	CRect WndRect;
	GetClientRect(&WndRect);
	CRect StaticHour,staticMin;
	staticMin.SetRect( 17,0, 60, 20 );
	StaticHour.SetRect( 17, 50, 60, 70);
	m_StaticHour.MoveWindow(StaticHour);
	m_StaticMin.MoveWindow(staticMin);

	//获取滑动条和滑动块的位置信息
	m_rectHourSlider.SetRect( 17,20, WndRect.Width() - 31, 28 );
	m_rectDaySlider.SetRect( 17, 70, WndRect.Width() - 19, 82);
	m_TimeHourDraw.MoveWindow(m_rectHourSlider);
	m_TimeDayDraw.MoveWindow(m_rectDaySlider);
	m_sizeThumb.cx = 9;
	m_sizeThumb.cy = 8;
	CRect rectThum, rectThum2;
	int npos,nHourPos;
	int nHourUnit = m_rectHourSlider.right - m_rectHourSlider.left;
	nHourPos = m_nCurMin * nHourUnit / 60;
	int nDayUnit = m_rectDaySlider.right - m_rectDaySlider.left;
	npos = ( m_nCurHour * 60 + m_nCurMin ) * nDayUnit / ( 24 * 60 );
	rectThum.SetRect(m_rectDaySlider.left + npos - m_sizeThumb.cx / 2, m_rectDaySlider.bottom, 
	m_rectDaySlider.left + npos + m_sizeThumb.cx / 2, m_rectDaySlider.bottom + m_sizeThumb.cy);
	m_DayThum.MoveWindow(rectThum);
	m_DayThum.SetLabelPosition( m_rectDaySlider.bottom, m_rectDaySlider.left, m_rectDaySlider.right - m_rectDaySlider.left );
	rectThum2.SetRect(m_rectHourSlider.left + nHourPos - m_sizeThumb.cx / 2, m_rectHourSlider.bottom,
	m_rectHourSlider.left + nHourPos + m_sizeThumb.cx / 2, m_rectHourSlider.bottom + m_sizeThumb.cy);
	m_HourThum.MoveWindow(rectThum2);
	m_HourThum.SetLabelPosition( m_rectHourSlider.bottom, m_rectHourSlider.left, m_rectHourSlider.right - m_rectHourSlider.left );
	CRect staticRect;
	staticRect.SetRect(rectThum2.right + 5, rectThum2.top + 2, rectThum2.right + 55, rectThum2.top + 14);
	m_timeCaption.MoveWindow(staticRect);

	int VWidth = (float)nDayUnit / 24.0;
	//标注小时
	for ( int i = 0 ; i <= 24; i ++)
	{
		CRect SRect;
		SRect.SetRect(i * VWidth + 17, 83, ( i + 1 ) * VWidth + 17, 103);
		m_StaticH[i].MoveWindow(SRect);
	}
	VWidth = (float)nHourUnit / 12;
	//标注分钟
	for ( int j = 0 ; j<= 12 ; j ++)
	{
		CRect SRect;
		SRect.SetRect(j * VWidth + 17, 29, ( j + 1 ) * VWidth + 30, 49);
		m_StaticM[j].MoveWindow(SRect);
	}

	//m_HourThum.CreateRgnFromMask(RGB(255, 0, 255), m_Rgn);
	//if (m_Rgn.m_hObject != NULL)
	//{
	//	SetWindowRgn(m_Rgn, TRUE);
	//}

	//圆角
	CRgn rgn;
	rgn.CreateRoundRectRgn(WndRect.left, WndRect.top, WndRect.right, WndRect.bottom,  25, 25);
	SetWindowRgn(rgn, true);
	rgn.DeleteObject();
}

HBRUSH CRecordPeriodDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	int nId = pWnd->GetDlgCtrlID();

	if ( nId == ID_TIME_HOUR || nId == ID_TIME_HOUR + 1
		|| (nId >= ID_STATIC_HOUR && nId <= ID_STATIC_HOUR + 24)
		|| (nId >= ID_STATIC_MINUTE && nId <= ID_STATIC_MINUTE + 12))
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_Brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

int CRecordPeriodDlg::OnCreate(LPCREATESTRUCT lpCreateStruct )
{
	// TODO:  在此添加额外的初始化

	return CDialog::OnCreate(lpCreateStruct);
}
