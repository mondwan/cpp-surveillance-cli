// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "MyButton.h"
#include "multilanguage.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

BOOL CMyButton::CreateRgnFromMask(CBitmap &bmp, const COLORREF &maskColor, CRgn &rgn)
{
	if (bmp.m_hObject == NULL)
	{
		return FALSE;
	}
	
	CDC dc;
	dc.CreateCompatibleDC(NULL);
	CBitmap *pOldBmp = dc.SelectObject(&bmp);

	BITMAP bitMap;
	bmp.GetBitmap(&bitMap);
	
	int w = bitMap.bmWidth;
	int h = bitMap.bmHeight;

	rgn.DeleteObject();
	rgn.CreateRectRgn(0, 0, 0, 0);
	
	for (int x = 0; x < w; x++)
	{
		for (int y1 = 0; y1 < h;)
		{
			COLORREF clr1 = dc.GetPixel(x, y1);
			while (y1 < h && clr1 == maskColor)
			{
				y1++;
				clr1 = dc.GetPixel(x, y1);
			}
			
			if (y1 == h)
			{
				break;
			}
			
			int y2 = y1;
			COLORREF clr2 = dc.GetPixel(x, y2);
			while (y2 < h && clr2 != maskColor)
			{
				y2++;
				clr2 = dc.GetPixel(x, y2);
			}
			
			CRgn rgnDiff;
			rgnDiff.CreateRectRgn(x, y1, x+1, y2);
			rgn.CombineRgn(&rgn, &rgnDiff, RGN_OR);
			
			y1 = y2;
		}
	}
	
	dc.SelectObject(pOldBmp);
	
	return TRUE;
}

CSize CMyButton::StringToSize(CString str)
{
	if (str.GetLength() == 0)
	{
		return CSize(0, 0);
	}

	CSize size;
	CString val;
	int nFirst = 0;
	int nNext = 0;
	str.TrimLeft();
	str.TrimRight();

	//取 Size.cx
	nNext = str.Find(',', nFirst);
	val = str.Mid(nFirst, nNext - nFirst);
	val.TrimLeft();
	val.TrimRight();
	size.cx = atoi(val.GetBuffer(0));

	//取 Size.cy
	val = str.Mid(nNext + 1);
	val.TrimLeft();
	val.TrimRight();
	size.cy = atoi(val.GetBuffer(0));

	return size;
}

CRect CMyButton::StringToRect(CString str)
{
	if (str.GetLength() == 0)
	{
		return CRect(0, 0, 0, 0);
	}

	CRect rect;
	CString val;
	int nFirst = 0;
	int nNext = 0;
	str.TrimLeft();
	str.TrimRight();

	//取 Rect.left
	nNext = str.Find(',', nFirst);
	val = str.Mid(nFirst, nNext - nFirst);
	val.TrimLeft();
	val.TrimRight();
	rect.left = atoi(val.GetBuffer(0));

	//取 Rect.top
	nFirst = nNext + 1;
	nNext = str.Find(',', nFirst);
	val = str.Mid(nFirst, nNext - nFirst);
	val.TrimLeft();
	val.TrimRight();
	rect.top = atoi(val.GetBuffer(0));

	//取 Rect.Right
	nFirst = nNext + 1;
	nNext = str.Find(',', nFirst);
	val = str.Mid(nFirst, nNext - nFirst);
	val.TrimLeft();
	val.TrimRight();
	rect.right = atoi(val.GetBuffer(0));

	//取 Rect.Bottom
	nFirst = nNext + 1;
	val = str.Mid(nFirst);
	val.TrimLeft();
	val.TrimRight();
	rect.bottom = atoi(val.GetBuffer(0));

	return rect;
}


CMyButton::CMyButton()
{
	m_nLabelTop = 0;
	m_nLabelLeft = 0;
	m_nWidth = 0;
	
	m_nType = 0;
	m_button_down = false;
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rcParent;
	GetParent()->GetWindowRect(rcParent);
	
	CRect rect;
	GetWindowRect(rect);

	int nWide=rect.right-rect.left;
	int x=rect.left-rcParent.left - m_nLabelLeft + nWide/ 2;


	::PostMessage(
		GetParent()->GetSafeHwnd(),	WM_SLIDER_LBUTUP,
		GetDlgCtrlID(), x );

	CButton::OnLButtonUp(nFlags, point);
}

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_button_down = true;
	m_point=point;

	::PostMessage(
		GetParent()->GetSafeHwnd(),	WM_SLIDER_LBUTDOWN,
		GetDlgCtrlID(), 0 );

	CButton::OnLButtonDown(nFlags, point);
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((m_button_down) && (::GetCapture() == m_hWnd)) 
	{
		POINT p2 = point;
        ::ClientToScreen(m_hWnd, &p2);
        HWND mouse_wnd = ::WindowFromPoint(p2);
		
        bool pressed = ((GetState() & BST_PUSHED) == BST_PUSHED);
        bool need_pressed = (mouse_wnd == m_hWnd);
        if (pressed != need_pressed) 
		{
            SetState(need_pressed ? TRUE : FALSE);
            Invalidate();
        }
		MoveThumb(nFlags, point);
    } 
	
	CButton::OnMouseMove(nFlags, point);
}

void CMyButton::MoveThumb(UINT nFlags,CPoint point)
{
	CRect rcParent;
	GetParent()->GetWindowRect(rcParent);
	
	CRect rect;
	GetWindowRect(rect);
	int nHeight=rect.bottom-rect.top;
	int nWide=rect.right-rect.left;
	
	int nMinX = (m_nLabelLeft - nWide/ 2);
	int nMaxX = nMinX + m_nWidth;

	int oldx=rect.left-rcParent.left;

	if( oldx < nMinX || oldx > nMaxX )
	{
		return;
	}
	
	int newx=((point.x-m_point.x)>=0)?(oldx+(point.x-m_point.x)):(oldx-(m_point.x-point.x));

	if(newx < nMinX)
	{
		newx = nMinX;
	}
	else if( newx > nMaxX )
	{
		newx = nMaxX;
	}
	
	MoveWindow(newx,m_nLabelTop,nWide,nHeight);


	::PostMessage(
		GetParent()->GetSafeHwnd(),	WM_SLIDER_MOUSEMOVE,
		GetDlgCtrlID(), newx - m_nLabelLeft + nWide/ 2  );
}

int GetBitmapWidth (HBITMAP hBitmap)
{ 
	BITMAP bm; 
	GetObject(hBitmap,sizeof(BITMAP),(PSTR)&bm); return bm.bmWidth;
}
/////////////////////////////////////////////////////////////////////////////
int GetBitmapHeight (HBITMAP hBitmap)
{ 
	BITMAP bm; 
	GetObject(hBitmap,sizeof(BITMAP),(PSTR)&bm); return bm.bmHeight;
}

void DrawBitmap(CDC* dc, HBITMAP hbmp, RECT r, int DrawMode)
{
	if(!hbmp) return;	//safe check
	
	int cx=r.right  - r.left;
	int cy=r.bottom - r.top;
	CDC dcBmp,dcMask;
	dcBmp.CreateCompatibleDC(dc);
	dcBmp.SelectObject(hbmp);
	
	if(!DrawMode)
	{
		dc->BitBlt(r.left,r.top,cx,cy,&dcBmp,0,0,SRCCOPY);
	} 
	else 
	{
		int bx=GetBitmapWidth(hbmp);
		int by=GetBitmapHeight(hbmp);
		dc->StretchBlt(r.left,r.top,cx,cy,&dcBmp,0,0,bx,by,SRCCOPY);
	}

	if(dcBmp)
		DeleteDC(dcBmp);
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);	// get device context
	
	pDC->SetBkMode(TRANSPARENT);

	RECT r=lpDrawItemStruct->rcItem;					// context rectangle

	DrawBitmap(pDC,(HBITMAP)m_bmpSkin, r,0);

/*	CDC ImageDC;
	ImageDC.CreateCompatibleDC(pDC);
	CBitmap *pOldImageBMP = ImageDC.SelectObject(&m_bmpSkin);

	int cx=r.right  - r.left;
	int cy=r.bottom - r.top;
	BOOL bRet = TransparentBlt(pDC->m_hDC, 0, 0, cx, cy, ImageDC.m_hDC, 0, 0, cx, cy, RGB(17,17,17));

	ImageDC.SelectObject(pOldImageBMP);*/
}

void CMyButton::OnKillFocus(CWnd* pNewWnd) 
{
	if (::GetCapture() == m_hWnd) {
        ::ReleaseCapture();
        m_button_down = false;
    }

	CButton::OnKillFocus(pNewWnd);
}

HBRUSH CMyButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CButton::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

int CMyButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	TCHAR buf[64];
	CString strBmpPath;

	//if ( 0 == m_nType )
	//{
	//	DWORD dwNum = 0;	
	//	dwNum = GetPrivateProfileString(_T("MainSettings"), _T("Thumb_Up"), _T(""), buf, 64, strFile);
	//	strBmpPath.Format(_T("%s%s\\%s"), , strSolutionDir, buf);
	//}
	//else if ( 1 == m_nType )
	//{
	//	DWORD dwNum = 0;	
	//	dwNum = GetPrivateProfileString(_T("MainSettings"), _T("StartLine_BackImage"), _T(""), buf, 64, strFile);
	//	strBmpPath.Format(_T("%s%s\\%s"), strDir, strSolutionDir, buf);
	//}
	//else if ( 2 == m_nType )
	//{	
	//	DWORD dwNum = 0;	
	//	dwNum = GetPrivateProfileString(_T("MainSettings"), _T("EndLine_BackImage"), _T(""), buf, 64, strFile);
	//	strBmpPath.Format(_T("%s%s\\%s"), strDir, strSolutionDir, buf);
	//}
	//加载标尺浮标图片

	m_bmpSkin.LoadBitmap(IDB_BMP_THUM);

/*	CRect rect;
	GetClientRect(rect);

	CPoint Head, RightLeg, LeftLeg;

	Head.x = rect.right / 2; Head.y = 0;
	RightLeg.x = rect.right; RightLeg.y = rect.bottom;
	LeftLeg.x = 0; LeftLeg.y = rect.bottom;

	CPoint points[3];
	points[0] = Head; points[1] = RightLeg; points[2] = LeftLeg;

	CRgn CurrentRegion;
	CurrentRegion.CreatePolygonRgn(points, 3, ALTERNATE);
	SetWindowRgn(CurrentRegion, TRUE);
	*/
	
/*	DWORD dwError = 0;
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE)^0x80000 );
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	if ( hInst )
	{
		typedef BOOL (WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);
		//取得setlyaerwindowattribes函数指针
		MYFUNC pFunc = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if ( pFunc != NULL )
		{
			pFunc(m_hWnd, 0, 50,  2);
		}
		
		dwError = GetLastError();
		FreeLibrary(hInst);
		hInst = NULL;
	}*/

	return 0;
}

void CMyButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
}
