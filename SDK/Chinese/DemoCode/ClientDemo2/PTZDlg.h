#if !defined(AFX_PTZDLG_H__9FEFA55E_6A0F_42FD_BC40_5B49AE883B7C__INCLUDED_)
#define AFX_PTZDLG_H__9FEFA55E_6A0F_42FD_BC40_5B49AE883B7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PTZDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPTZDlg dialog
#include "ColorButton.h"
#include "afxwin.h"
#include "CruiseEdit.h"


class CPTZDlg : public CDialog
{
// Construction
public:
	CPTZDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPTZDlg)
	enum { IDD = IDD_PTZ_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPTZDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPTZDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	CColorButton m_mybuttonup;
	CColorButton m_mybuttondown;
	CColorButton m_mybuttonleft;
	CColorButton m_mybuttonright;
	/*CColorButton m_mybuttonlefttop;
	CColorButton m_mybuttonleftdown;
	CColorButton m_mybuttonrighttop;
	CColorButton m_mybuttonrightdown;*/
	
	CColorButton m_mybuttontjleft;
	CColorButton m_mybuttontjright;
	CColorButton m_mybuttonjjleft;
	CColorButton m_mybuttonjjright;
	CColorButton m_mybuttongqleft;
	CColorButton m_mybuttongqright;
	CColorButton m_mybuttonrighttop;
	CColorButton m_mybuttonleftdown;
	CColorButton m_mybuttonlefttop;
	CColorButton m_mybuttonrightdown;
	CColorButton m_mybuttonusepresent;
	CColorButton m_mybuttonaddpresent;
	CColorButton m_mybuttondeletepresent;
	CColorButton m_mybuttoncruiseplay;
	CColorButton m_mybuttoncruisestop;
	CColorButton m_mybuttoncruiseedit;



public:
	afx_msg void OnBnClickedStatic4();
	afx_msg void OnBnClickedButtontjright();
	CComboBox m_present;
	CComboBox m_ComboCruise;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZDLG_H__9FEFA55E_6A0F_42FD_BC40_5B49AE883B7C__INCLUDED_)
