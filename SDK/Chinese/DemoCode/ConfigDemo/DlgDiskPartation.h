#if !defined(AFX_DLGDISKPARTATION_H__22E3C751_A134_4880_A3A3_07EA05BB6A48__INCLUDED_)
#define AFX_DLGDISKPARTATION_H__22E3C751_A134_4880_A3A3_07EA05BB6A48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiskPartation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDiskPartation dialog

class CDlgDiskPartation : public CDialog
{
// Construction
public:
	CDlgDiskPartation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDiskPartation)
	enum { IDD = IDD_DLG_PARTATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDiskPartation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDiskPartation)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_nRecord;
	int m_nSnap;
	int m_nTotal;
private:
	afx_msg void OnEnChangeEditRecord();
	afx_msg void OnEnChangeEditSnap();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDISKPARTATION_H__22E3C751_A134_4880_A3A3_07EA05BB6A48__INCLUDED_)
