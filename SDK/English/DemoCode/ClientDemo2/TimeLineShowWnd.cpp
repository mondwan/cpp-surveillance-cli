// RecLineShowWnd.cpp: implementation of the CRecLineShowWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TimeLineShowWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeLineShowWnd::CTimeLineShowWnd()
:m_pclRecColor(NULL)
{
	m_lColourNum = 24 * 60;

	m_MidText = "";
	m_MidTextColor = RGB(0,0,0);

	m_bShowScale = TRUE;
	m_dwTickcount = 0;
	m_penColour = RGB(62, 62, 62);
	m_unColour = RGB(0,0,0);
	m_colour = RGB(0,255,255);
}

void CTimeLineShowWnd::InitColourNum(int num)
{
	m_lColourNum = num;
	m_pclRecColor = new COLORREF[m_lColourNum];

	for (int n = 0 ; n < m_lColourNum ; n++)
	{
		m_pclRecColor[n] = m_unColour;
	}
}

CTimeLineShowWnd::~CTimeLineShowWnd()
{
	if ( m_pclRecColor )
	{
		delete[] m_pclRecColor;
		m_pclRecColor = NULL;
	}
}

BEGIN_MESSAGE_MAP(CTimeLineShowWnd, CWnd)
	//{{AFX_MSG_MAP(CVideoWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



void CTimeLineShowWnd::SetMiddleText(char * pchText , COLORREF clText)
{
	m_MidText = pchText;
	m_MidTextColor = clText;
}

void CTimeLineShowWnd::SetShowScale(BOOL bShow)
{
	m_bShowScale = bShow;
}


void CTimeLineShowWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	/*CRect Rect;
	GetClientRect(&Rect);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, Rect.Width(), Rect.Height());
	memDC.SelectObject(&bitmap);

	return;

	memDC.SetBkMode(TRANSPARENT);

	LONG lHight = Rect.bottom;
	LONG lLength = Rect.right;

	//为了减少画刷次数,进行相同颜色一起画
	COLORREF cl;
	COLORREF sc;

	DWORD bg;
	DWORD ed;

	int n ;
	for (n = 0 ; n < m_lColourNum ; n++)
	{
		if (n == 0)//一开始设置基准
		{
			bg = 0;
			cl = m_pclRecColor[n];
		} 

		sc = m_pclRecColor[n];

		if (cl != sc || n == m_lColourNum - 1)//发现颜色跟上次不同开始画图
		{
			ed = n + 1;

			Rect.left = lLength * bg / m_lColourNum ;
			Rect.right = lLength * ed / m_lColourNum ;

			memDC.FillRect(&Rect,&CBrush(cl));

			cl = sc;//把新的颜色赋予基准
			bg = ed;
		}	
	}

	//	dc.TextOut(lLength/2-5,4,m_MidText);
	//	dc.SetTextColor(m_MidTextColor);

	if (0)//画刻度
	{
		CPoint beginPoint;
		CPoint endPoint;

		CPen Pen(PS_SOLID, 1, m_penColour);
		CPen* pOldPen = memDC.SelectObject(&Pen);

		if ( m_lColourNum == 60 )
		{
			for (n = 1 ; n < m_lColourNum ; n ++)
			{
				Rect.left = lLength * n / m_lColourNum;

				beginPoint = CPoint(Rect.left, Rect.top);
				endPoint = CPoint(Rect.left, Rect.bottom);

				memDC.MoveTo(beginPoint);
				memDC.LineTo(endPoint);	
			}	
		}
		else
		{
			for (n = 60 ; n < m_lColourNum ; n+=60)
			{
				Rect.left = lLength * n / m_lColourNum;

				beginPoint = CPoint(Rect.left, Rect.top);
				endPoint = CPoint(Rect.left, Rect.bottom);

				memDC.MoveTo(beginPoint);
				memDC.LineTo(endPoint);	
			}
		}

		memDC.SelectObject(pOldPen);
	}

	memDC.FillRect(&Rect, &CBrush(RGB(255,0,0)) );
	dc.BitBlt(0, 0, Rect.Width(), Rect.Height(), &memDC, 0, 0, SRCCOPY);

*/
	CRect Rect;
	GetClientRect(&Rect);

	dc.SetBkMode(TRANSPARENT);

	LONG lHight = Rect.bottom;
	LONG lLength = Rect.right;

	//为了减少画刷次数,进行相同颜色一起画
	COLORREF cl;
	COLORREF sc;

	DWORD bg;
	DWORD ed;

	int n ;
	for (n = 0 ; n < m_lColourNum ; n++)
	{
		if (n == 0)//一开始设置基准
		{
			bg = 0;
			cl = m_pclRecColor[n];
		} 

		sc = m_pclRecColor[n];

		if (cl != sc || n == m_lColourNum - 1)//发现颜色跟上次不同开始画图
		{
			ed = n + 1;

			Rect.left = lLength * bg / m_lColourNum ;
			Rect.right = lLength * ed / m_lColourNum ;

			dc.FillRect(&Rect,&CBrush(cl));

			cl = sc;//把新的颜色赋予基准
			bg = ed;
		}	
	}

	//	dc.TextOut(lLength/2-5,4,m_MidText);
	//	dc.SetTextColor(m_MidTextColor);

	if (1)//画刻度
	{
		CPoint beginPoint;
		CPoint endPoint;

		CPen Pen(PS_SOLID, 1, m_penColour);
		CPen* pOldPen = dc.SelectObject(&Pen);

		if ( m_lColourNum == 60 )
		{
			//for (n = 1 ; n < m_lColourNum ; n ++)
			for ( n = 5; n < m_lColourNum; n += 5)
			{
				Rect.left = lLength * n / m_lColourNum;

				beginPoint = CPoint(Rect.left, Rect.top);
				endPoint = CPoint(Rect.left, Rect.bottom);

				dc.MoveTo(beginPoint);
				dc.LineTo(endPoint);
			}	
		}
		else
		{
			for (n = 60 ; n < m_lColourNum ; n+=60 )
			{
				Rect.left = lLength * n / m_lColourNum;

				beginPoint = CPoint(Rect.left, Rect.top);
				endPoint = CPoint(Rect.left, Rect.bottom);

				dc.MoveTo(beginPoint);
				dc.LineTo(endPoint);	
			}
		}

		dc.SelectObject(pOldPen);
	}
}

//刷新界面
void CTimeLineShowWnd::Draw()
{
	Invalidate();
}

void CTimeLineShowWnd::SetPeriod(COLORREF *pPeriod)
{
	//根据划分的内存快赋值颜色
	for ( int i = 0; i < m_lColourNum; i ++ )
	{
		m_pclRecColor[i] = pPeriod[i];
	}
}



void CTimeLineShowWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ( m_dwTickcount > 0 )
	{
		if ( (GetTickCount() - m_dwTickcount) < 800 )
		{
			CWnd::OnLButtonUp(nFlags, point);
			return;
		}
	}
	m_dwTickcount = GetTickCount();

	::SendMessage(
		GetParent()->GetSafeHwnd(),	WM_LBUTUP,
		GetDlgCtrlID(), point.x );
		
	CWnd::OnLButtonUp(nFlags, point);
}

void CTimeLineShowWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	::SendMessage(
		GetParent()->GetSafeHwnd(),	WM_LDBUTUP,
		GetDlgCtrlID(), point.x );

	CWnd::OnLButtonDblClk(nFlags, point);
}
