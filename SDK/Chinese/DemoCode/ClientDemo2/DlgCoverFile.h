#if !defined(AFX_DLGCOVERFILE_H__F520D894_6354_43BB_A1B7_2FE23E252008__INCLUDED_)
#define AFX_DLGCOVERFILE_H__F520D894_6354_43BB_A1B7_2FE23E252008__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCoverFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCoverFile dialog

class CDlgCoverFile : public CDialog
{
// Construction
public:
	CDlgCoverFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCoverFile)
	enum { IDD = IDD_DLG_TESTCOVER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCoverFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCoverFile)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Cdlgcoverfile dialog

class Cdlgcoverfile : public CDialog
{
// Construction
public:
	Cdlgcoverfile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdlgcoverfile)
	enum { IDD = IDD_DLG_TESTCOVER };
	CString	m_strDesPath;
	CString	m_strSrcpath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlgcoverfile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdlgcoverfile)
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString BrowseForFolder(HWND hWnd);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOVERFILE_H__F520D894_6354_43BB_A1B7_2FE23E252008__INCLUDED_)
