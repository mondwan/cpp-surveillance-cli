// RecLineShowWnd.cpp: implementation of the CRecLineShowWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClientDemo5.h"
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
{
	m_pclRecColor = new COLORREF[COLOURNUM];

	ASSERT(m_pclRecColor);

	m_MidText = "";
	m_MidTextColor = RGB(0,0,0);

	m_bShowScale = TRUE;

	for (int n = 0 ; n < COLOURNUM ; n++)
	{
		m_pclRecColor[n] = RGB(255,255,255);
	}
}

CTimeLineShowWnd::~CTimeLineShowWnd()
{
	if ( m_pclRecColor )
	{
		delete m_pclRecColor;
		m_pclRecColor = NULL;
	}
}

BEGIN_MESSAGE_MAP(CTimeLineShowWnd, CWnd)
	//{{AFX_MSG_MAP(CVideoWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CTimeLineShowWnd::InsertDrawSpace(DWORD dwBgSpace , DWORD dwEdSpace ,COLORREF clDrawColor)
{
	if ( dwBgSpace >= 0 && dwBgSpace <= COLOURNUM &&
		 dwEdSpace >= 0 && dwEdSpace <= COLOURNUM && 
		 clDrawColor != RGB(255,255,255))
	{
		DWORD n;
		if (dwBgSpace < dwEdSpace)
		{
			for (n = dwBgSpace ; n < dwEdSpace ; n++)
			{
				m_pclRecColor[n] = clDrawColor;
			}		
		}
		else
		{
			for (n = dwEdSpace ; n <= dwBgSpace ; n++)
			{
				m_pclRecColor[n] = clDrawColor;
			}
		}
	}
}

void CTimeLineShowWnd::DeleteDrawSpace(DWORD dwBgSpace , DWORD dwEdSpace)
{
	if ( dwBgSpace >= 0 && dwBgSpace <= COLOURNUM &&
		 dwEdSpace >= 0 && dwEdSpace <= COLOURNUM )
	{
		DWORD n;
		if (dwBgSpace < dwEdSpace)
		{
			for (n = dwBgSpace ; n < dwEdSpace ; n++)
			{
				m_pclRecColor[n] = RGB(255,255,255);
			}		
		}
		else
		{
			for (n = dwEdSpace ; n <= dwBgSpace ; n++)
			{
				m_pclRecColor[n] = RGB(255,255,255);
			}
		}
	}	
}
	

void CTimeLineShowWnd::DrawAllSpace(COLORREF clDrawColor)
{
	for (int n = 0 ; n < COLOURNUM ; n++)
	{
		m_pclRecColor[n] = clDrawColor;
	}
	Draw();
}

void CTimeLineShowWnd::CleanAllSpace()
{
	for (int n = 0 ; n < COLOURNUM ; n++)
	{
		m_pclRecColor[n] = RGB(255,255,255);
	}
	Draw();
}


DWORD  CTimeLineShowWnd::GetColorPercent(COLORREF clDrawColor)
{
	DWORD dwNum = 0;
	for (int n = 0 ; n < COLOURNUM ; n++)
	{
		if (m_pclRecColor[n] ==  clDrawColor)
		{
			dwNum ++;
		}
	}
	
	return dwNum;
}


COLORREF CTimeLineShowWnd::GetSpaceColor(DWORD dwGetSpace)
{
	return m_pclRecColor[dwGetSpace];
}

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
	dc.SetBkMode(TRANSPARENT);
	
	RECT Rect;
	GetClientRect(&Rect);
	LONG lHight = Rect.bottom;
	LONG lLength = Rect.right;


	COLORREF cl;
	COLORREF sc;

	DWORD bg;
	DWORD ed;
	
	int n ;
	for (n = 0 ; n < COLOURNUM ; n++)
	{
		if (n == 0)
		{
			bg = 0;
			cl = m_pclRecColor[n];
		} 

		sc = m_pclRecColor[n];

		if (cl != sc || n == COLOURNUM - 1)
		{
			ed = n + 1;

			Rect.left = lLength * bg / COLOURNUM ;
			Rect.right = lLength * ed / COLOURNUM ;

			dc.FillRect(&Rect,&CBrush(cl));
					
			cl = sc;
			bg = ed;
		}	
	}
	
	dc.TextOut(lLength/2-10,4,m_MidText);
	dc.SetTextColor(m_MidTextColor);
	
	if (m_bShowScale)
	{
		for (n = 60 ; n < COLOURNUM ; n+=60)
		{
			Rect.left = lLength * n / COLOURNUM;
			Rect.right = Rect.left + 1;
			//Rect.right = lLength * (n + 2) / COLOURNUM;
			Rect.bottom = 3;
			dc.FillRect(&Rect,&CBrush(m_MidTextColor));
		}
	}

/*
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(RGB(255,255,255)));*/

//	CWnd::OnPaint();// for painting messages
}


void CTimeLineShowWnd::Draw()
{
	Invalidate();
}
