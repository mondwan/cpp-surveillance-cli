#if !defined(AFX_COVERSETDLG_H__214E22F1_B94A_4EF9_B5E2_F85889EE7D99__INCLUDED_)
#define AFX_COVERSETDLG_H__214E22F1_B94A_4EF9_B5E2_F85889EE7D99__INCLUDED_

#include "CoverAreaDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoverSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoverSetDlg dialog

class CCoverSetDlg : public CDialog
{
// Construction
public:
	CCoverAreaDlg m_dlgCoverArea;
	CCoverSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCoverSetDlg)
	enum { IDD = IDD_DLG_COVER_SET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoverSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoverSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COVERSETDLG_H__214E22F1_B94A_4EF9_B5E2_F85889EE7D99__INCLUDED_)
