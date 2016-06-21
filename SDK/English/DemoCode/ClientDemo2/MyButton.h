#if !defined(AFX_MYBUTTON_H__6089C707_7041_4DBC_9666_0B41EEDF581F__INCLUDED_)
#define AFX_MYBUTTON_H__6089C707_7041_4DBC_9666_0B41EEDF581F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyButton window

#define WM_SLIDER_LBUTDOWN		(WM_USER + 5425)
#define WM_SLIDER_LBUTUP		(WM_USER + 5426)
#define WM_SLIDER_MOUSEMOVE		(WM_USER + 5427)

class CMyButton : public CButton
{
// Construction
public:
	CMyButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyButton)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	BOOL CreateRgnFromMask(CBitmap &bmp, const COLORREF &maskColor, CRgn &rgn);
	CSize StringToSize(CString str);
	CRect StringToRect(CString str);
	void SetLabelPosition(int nTop, int nLeft, int nWidth)
	{
		m_nLabelTop = nTop;
		m_nLabelLeft = nLeft;
		m_nWidth = nWidth;
	}
	void SetBtnType(int nType)
	{
		m_nType = nType;
	}
	CBitmap m_bmpSkin;
private:
	
	void    MoveThumb(UINT nFlags,CPoint point);
	
	int m_nLabelTop;
	int m_nLabelLeft;
	int m_nWidth;

	int m_nType;
	CRgn CurrentRegion;
	CPoint m_point;
	bool m_button_down;
	CRgn m_Rgn;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__6089C707_7041_4DBC_9666_0B41EEDF581F__INCLUDED_)
