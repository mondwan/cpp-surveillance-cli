#if !defined(AFX_PTZCTRL_H__63C2F88A_C69D_43C0_BAEE_2D2F24D97CFA__INCLUDED_)
#define AFX_PTZCTRL_H__63C2F88A_C69D_43C0_BAEE_2D2F24D97CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PTZCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPTZCtrl window

class CPTZCtrl : public CButton
{
// Construction
public:
	int	m_iTypeButton;
	CPTZCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPTZCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPTZCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPTZCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZCTRL_H__63C2F88A_C69D_43C0_BAEE_2D2F24D97CFA__INCLUDED_)
