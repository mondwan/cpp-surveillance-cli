#if !defined(AFX_DLGFORBIDDIRECTION_H__D1CBDE60_C9BB_4F46_A79D_EFD9623CCA19__INCLUDED_)
#define AFX_DLGFORBIDDIRECTION_H__D1CBDE60_C9BB_4F46_A79D_EFD9623CCA19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgForbidDirection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgForbidDirection dialog

class CDlgForbidDirection : public CDialog
{
// Construction
public:
	CDlgForbidDirection(int nRule,int nDirection=0,int iIsDoubleDirection = 0,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgForbidDirection)
	enum { IDD = IDD_DIG_FORBIDDIRECTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	int m_nDirection;
	int   m_iIsDoubleDirection;
	int m_nRule;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgForbidDirection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgForbidDirection)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioDirection1();
	afx_msg void OnBnClickedRadioDirection2();
	afx_msg void OnBnClickedRadioDirection3();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFORBIDDIRECTION_H__D1CBDE60_C9BB_4F46_A79D_EFD9623CCA19__INCLUDED_)
