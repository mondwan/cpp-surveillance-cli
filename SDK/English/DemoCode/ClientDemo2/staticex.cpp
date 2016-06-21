// StaticEx.cpp : implementation file
//

#include "stdafx.h"
#include "StaticEx.h"
//#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticEx

CStaticEx::CStaticEx()
{
	m_TextColor=RGB(0,255,0);
	m_BackColor=RGB(0,0,0);
	m_bBackcolor = false;
}

CStaticEx::~CStaticEx()
{
}

BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	//{{AFX_MSG_MAP(CStaticEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

void CStaticEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	
	if(!m_Font.m_hObject)
	{
		LOGFONT lf;
		memset(&lf,0,sizeof(LOGFONT));
		CFont *pParentFont=GetParent()->GetFont();
	//	pParentFont->GetLogFont(&lf);
	//	lf.lfHeight=rect.Height()/*-2*/;
		VERIFY(m_Font.CreateFontIndirect(&lf));
	}


	CFont *pOldFont=dc.SelectObject(&m_Font);
	dc.SetTextColor(m_TextColor);
	if ( !m_bBackcolor )
		dc.SetBkMode(TRANSPARENT);    
	else
		dc.SetBkColor(m_BackColor);

//	CString strCaption=m_strCaption;
//	strCaption+="                          ";
//	dc.ExtTextOut(0,0,ETO_CLIPPED,&rect,strCaption,strCaption.GetLength(),NULL);

	CString strCaption=m_strCaption;
	SIZE size;
	size.cx = 0;
	size.cy = 0;

	CDC *pDC = GetDC();
	if (!pDC)
	{
		return;
	}
	::GetTextExtentPoint32(pDC->GetSafeHdc(), m_strCaption, m_strCaption.GetLength(), &size);
	int nxpos = ((rect.Width() - size.cx) / 2);
	int nypos = ((rect.Height() - size.cy) / 2);
	dc.ExtTextOut(1,nypos + 1,ETO_CLIPPED,&rect,m_strCaption,m_strCaption.GetLength(),NULL);

	dc.SelectObject(pOldFont);
	
	ReleaseDC(pDC);
	// Do not call CStatic::OnPaint() for painting messages
}

void CStaticEx::SetTextColor(COLORREF clfText)
{
	m_TextColor=clfText;
	Invalidate(FALSE);				
}

void CStaticEx::SetTextFont(CFont& font)
{
	LOGFONT lf;

	if (font.GetLogFont (&lf))
	{
		m_Font.DeleteObject();
		m_Font.CreateFontIndirect (&lf);
	}
}

void CStaticEx::SetBackFlush(bool bValide)
{
	m_bBackcolor=bValide;
	Invalidate(FALSE);			
}

void CStaticEx::SetBackColor(COLORREF clfBack)
{
	m_BackColor=clfBack;
	Invalidate(FALSE);				
}

BOOL CStaticEx::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CStaticEx::SetWindowText(CString strText)
{
	m_strCaption=strText;
	Invalidate();
}

int CStaticEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}
