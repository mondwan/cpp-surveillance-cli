#if !defined(AFX_STATICEX_H__61809936_FD26_11D5_9614_00E04C5720D7__INCLUDED_)
#define AFX_STATICEX_H__61809936_FD26_11D5_9614_00E04C5720D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticEx window

class CStaticEx : public CStatic
{
// Construction
public:
	CStaticEx();

// Attributes
public:
private:
	COLORREF m_TextColor;
	COLORREF m_BackColor;
	CString m_strCaption;
	CFont m_Font;
	bool	m_bBackcolor;	//是否刷新背景，不刷则透明
// Operations
public:
	void SetTextColor(COLORREF clfText);
	void SetBackColor(COLORREF clfBack);
	void SetWindowText(CString strText);
	void SetTextFont(CFont& font);      //设置静态框的字体 zhaoqy
	void SetBackFlush(bool bValide);	//设置是否刷新背景色
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticEx)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICEX_H__61809936_FD26_11D5_9614_00E04C5720D7__INCLUDED_)
