 // MotionDetect.cpp : implementation file
//

#include "stdafx.h"
#include "AreaSelectDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotionDetect


CMotionDetect::CMotionDetect()
{
	m_clfSelect = SELECTCOLOR;
	m_clfUnselect = UNSELECTCOLOR;
	m_clfBack = BKCOLOR;
	m_clfText = TEXTCOLOR;

	m_bMsDown = FALSE;

	m_nRgnColNum = 16; 
	m_nRgnRowNum = 12;
	memset(&m_ayRgnMask_mp4, 0, sizeof(m_ayRgnMask_mp4));
	memset(&m_ayRgn, 0, sizeof(m_ayRgn));

}

CMotionDetect::~CMotionDetect()
{
}


BEGIN_MESSAGE_MAP(CMotionDetect, CWnd)
	//{{AFX_MSG_MAP(CMotionDetect)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMotionDetect message handlers

BOOL CMotionDetect::OnEraseBkgnd(CDC* pDC) 
{

	CBrush brush(m_clfBack);
	CBrush *pOldBrush=pDC->SelectObject(&brush);

	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldBrush);
	
	return TRUE;
}

void CMotionDetect::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pos=HitTest(point);

	if (pos.y >= m_nRgnRowNum || pos.x >= m_nRgnColNum )
	{
		return;
	}

	m_LButtonDownPos = pos;

	BOOL bSel = m_ayRgn[pos.y][pos.x];
	m_ayRgn[pos.y][pos.x] = !bSel;

	CDC *pDC = GetWindowDC();
	DrawGrid(pos.y,pos.x,!bSel,pDC);
	ReleaseDC(pDC);	
	//得到屏幕的大小
	int x,y;
	
	CRect rect;
	GetClientRect(&rect);
	
	//起始top、left
	x = pos.x * m_ptGridSize.x;
	y = pos.y * m_ptGridSize.y;
	
	int x_right,y_bottom;
	if(pos.x == m_nRgnColNum -1)
	{
		x_right = rect.right;
	}
	else
	{
		x_right = x+m_ptGridSize.x;
	}
	
	if(pos.y == m_nRgnRowNum -1)
	{
		y_bottom = rect.bottom;
	}
	else
	{
		y_bottom = y+m_ptGridSize.y;
	}
	CRect rtInvalidate;
	rtInvalidate.left = x;
	rtInvalidate.right = x_right;
	rtInvalidate.top = y;
	rtInvalidate.bottom = y_bottom;
	InvalidateRect(rtInvalidate);

	m_bLBtnDownSel = !bSel;	

	m_bMsDown = TRUE;	

	CWnd::OnLButtonDown(nFlags, point);
}

void CMotionDetect::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((nFlags&MK_LBUTTON)) 
	{
		CPoint pos = HitTest(point);
		if (pos.y >= m_nRgnRowNum || pos.x >= m_nRgnColNum 
			|| pos.y < 0 || pos.x < 0 
			|| m_LButtonDownPos.x < 0 || m_LButtonDownPos.y < 0
			|| m_LButtonDownPos.x >= m_nRgnColNum || m_LButtonDownPos.y >= m_nRgnRowNum
			|| !m_bMsDown) 
		{
			return;
		}

		int bx,by,ex,ey;
		if(pos.x > m_LButtonDownPos.x)
		{
			bx = m_LButtonDownPos.x;
			ex = pos.x;
		}
		else
		{
			bx = pos.x;
			ex = m_LButtonDownPos.x;
		}

		if(pos.y > m_LButtonDownPos.y)
		{
			by = m_LButtonDownPos.y;
			ey = pos.y;
		}
		else
		{
			by = pos.y;
			ey = m_LButtonDownPos.y;
		}

		CDC *pDC=GetWindowDC();

		DWORD w=1;
		for(int i = by; i< ey+1; i++)
		{
			for(int j = bx;j < ex+1; j++)
			{
				m_ayRgn[i][j] = m_bLBtnDownSel;
				DrawGrid(i,j,m_bLBtnDownSel,pDC);
				
				if (!m_bLBtnDownSel)
				{
					int x,y;

					CRect rect;
					GetClientRect(&rect);


					x = j * m_ptGridSize.x;
					y = i * m_ptGridSize.y;

					int x_right,y_bottom;
					if(j == m_nRgnColNum -1)
					{
						x_right = rect.right;
					}
					else
					{
						x_right = x+m_ptGridSize.x;
					}

					if(i == m_nRgnRowNum -1)
					{
						y_bottom = rect.bottom;
					}
					else
					{
						y_bottom = y+m_ptGridSize.y;
					}
					CRect rtInvalidate;
					rtInvalidate.left = x;
					rtInvalidate.right = x_right;
					rtInvalidate.top = y;
					rtInvalidate.bottom = y_bottom;
					InvalidateRect(rtInvalidate);
				}
			}
		}

		ReleaseDC(pDC);
	}
	
	CWnd::OnMouseMove(nFlags, point);
}
void CMotionDetect::SetBackImgFile(const char* filename)
{
	m_filePath = filename;
}
void CMotionDetect::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if ( m_filePath.length() > 0 )
	{
		HBITMAP   hbitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),m_filePath.c_str(),
			IMAGE_BITMAP,352,228,LR_CREATEDIBSECTION|LR_LOADFROMFILE);    
		
		if(hbitmap==NULL) 
		{
			return ;   
		}
		CBitmap       bitmap;      
		bitmap.Attach(hbitmap);  
		
		CRect rtPic;
		GetClientRect(&rtPic);
		BITMAP bitMap;//位图结构体
		bitmap.GetBitmap(&bitMap);//获得原图片尺寸
		
		CDC dcMem;  //目标DC
		dcMem.CreateCompatibleDC(&dc); //创建与dc兼容的内存DC
		dcMem.SelectObject(&bitmap);//将位图对象m_bmpBK选入内存DC
		dc.StretchBlt(0,0,rtPic.Width(),rtPic.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
	}	
	///////////////////////////////////////

	CalcGridSize();
	
	TRACE("row:%d,col:%d\n", m_nRgnRowNum, m_nRgnColNum);

	BOOL bSel;
	for (int i = 0; i < m_nRgnRowNum; i++)
	{
		for(int j = 0; j < m_nRgnColNum; j++)
		{
			bSel = m_ayRgn[i][j];
			DrawGrid(i,j,bSel,&dc);
		}
	}
}

void CMotionDetect::DrawGrid(int nRow,int nCol,BOOL bSel,CDC *pDC)
{
	if(!IsWindowVisible()||IsIconic())
	{
		return;
	}


	int x,y;

	CRect rect;
	GetClientRect(&rect);
	

	x = nCol * m_ptGridSize.x;
	y = nRow * m_ptGridSize.y;

	int x_right,y_bottom;
	if(nCol == m_nRgnColNum -1)
	{
		x_right = rect.right;
	}
	else
	{
		x_right = x+m_ptGridSize.x;
	}
	
	if(nRow == m_nRgnRowNum -1)
	{
		y_bottom = rect.bottom;
	}
	else
	{
		y_bottom = y+m_ptGridSize.y;
	}


	CPen pen(PS_SOLID,1,m_clfBack);
	CBrush brushUnSelect,*pBrushSelect = NULL;
	
	CBrush *pOldBrush = NULL;
	if (!bSel) 
	{
		pBrushSelect = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		pOldBrush = pDC->SelectObject(pBrushSelect);
	}
	else
	{
		brushUnSelect.CreateSolidBrush(m_clfUnselect);
		pOldBrush = pDC->SelectObject(&brushUnSelect);
	}
	
	CPen *pOldPen = pDC->SelectObject(&pen);
	//CBrush *pOldBrush = pDC->SelectObject(&brush);

	pDC->Rectangle(x, y, x_right, y_bottom);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

BOOL CMotionDetect::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~WS_BORDER;
	
	return CWnd::PreCreateWindow(cs);
}

int CMotionDetect::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_bFullScreen = FALSE;
	return 0;
}

CPoint CMotionDetect::HitTest(CPoint point)
{

	CPoint pos;
	if (point.x < 0)
	{
		point.x = 0;
	}

	if (point.y < 0)
	{
		point.y = 0;
	}

	pos.x = point.x / m_ptGridSize.x;
	pos.y = point.y / m_ptGridSize.y;


	return pos;
}




void CMotionDetect::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( !m_bFullScreen )
	{
		FullScreen(TRUE);
	}
	else
	{
		FullScreen(FALSE);
	}
	CWnd::OnRButtonDblClk(nFlags, point);
	
}



void CMotionDetect::CalcGridSize()
{
	if(!IsWindowVisible()||IsIconic())
	{
		return;
	}

	CRect rt;
	GetClientRect(&rt);

	m_ptGridSize.x = rt.Width() / m_nRgnColNum;
	m_ptGridSize.y = rt.Height() / m_nRgnRowNum;
}



void CMotionDetect::FullScreen(BOOL bFull)
{
	CWnd * pWnd;
	pWnd = GetParent();
	if( bFull )
	{

		int cx=GetSystemMetrics(SM_CXSCREEN);
		int cy=GetSystemMetrics(SM_CYSCREEN);

	
		pWnd->GetWindowPlacement(&_temppl);

		m_pParentWnd = pWnd->GetParent();
	
		m_pParentWnd->ShowWindow(SW_HIDE);
		_tempparent=pWnd->SetParent(NULL);
		
		
		//MoveWindow(0,0,cx,cy);
		pWnd->SetWindowPos(&wndTopMost,0,0,cx,cy,0);
		RECT rect;
		pWnd->GetClientRect(&rect);
		MoveWindow(&rect);
		
		::ShowWindow(::FindWindow("Shell_TrayWnd",NULL),SW_HIDE);   

	}
	else
	{
		
		
		m_pParentWnd->ShowWindow(SW_SHOW);
		pWnd->SetParent(_tempparent);

		
		pWnd->SetWindowPlacement(&_temppl);
		RECT rect;
		pWnd->GetClientRect(&rect);
		MoveWindow(&rect);
		
		::ShowWindow(::FindWindow("Shell_TrayWnd",NULL),SW_SHOW);
	}
	m_bFullScreen = bFull;

}


BOOL MyModifyStyle(HWND hWnd, int nStyleOffset, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	ASSERT(hWnd != NULL);
	DWORD dwStyle = ::GetWindowLong(hWnd, nStyleOffset);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle == dwNewStyle)
		return FALSE;

	::SetWindowLong(hWnd, nStyleOffset, dwNewStyle);
	if (nFlags != 0)
	{
		::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
	}
	return TRUE;
}


BOOL CMotionDetect::GetGridValue(long nRow, long nCol) 
{
	if(nCol >= 36 || nCol < 0 )
	{
		return FALSE;
	}

	if(nRow >= 36 || nRow < 0 )
	{
		return FALSE;
	}
	return m_ayRgn[nRow][nCol];
}

void CMotionDetect::SetWindowRGB(short nRed, short nGreen, short nBlue) 
{
	m_clfUnselect = RGB(nRed, nGreen, nBlue);
}

BOOL CMotionDetect::SetGridRowCol(short nRow, short nCol) 
{

	if(nRow <= 0 || nRow > 36)
	{
		return FALSE;
	}


	if(nCol <= 0 || nCol > 36)
	{
		return FALSE;
	}

	m_nRgnColNum = nCol;
	m_nRgnRowNum = nRow;
	return TRUE;
}

void CMotionDetect::SetGridValue(long nRow, long nCol, BOOL bValue) 
{
	if(nCol >= 36 || nCol < 0)
	{
		return;
	}
	
	if(nRow >= 36 || nRow < 0)
	{
		return;
	}

	m_ayRgn[nRow][nCol] = bValue;
	
	CDC* pDC = GetDC();
	DrawGrid(nRow, nCol, bValue, pDC);
	ReleaseDC(pDC);						
	
}
