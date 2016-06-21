#if !defined(AFX_TITLESETDLG_H__2F2D5B73_5712_46E9_B576_71D6CCCF5AF3__INCLUDED_)
#define AFX_TITLESETDLG_H__2F2D5B73_5712_46E9_B576_71D6CCCF5AF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TitleSetDlg.h : header file
//
#define IDC_NEWCTRL_SHOWIFO 	WM_USER + 220
#include "NewCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CTitleSetDlg dialog

class CTitleSetDlg : public CDialog
{
// Construction
public:
	CTitleSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTitleSetDlg)
	enum { IDD = IDD_DLG_TITLE_SET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
	int m_nwidth;
	int m_nheight;
	SDK_CONFIG_VIDEOWIDGET m_Videowidget;
	CRect m_crMove;
	CNewCtrl m_ncTime;
	CNewCtrl m_ncChannel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitleSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTitleSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCcancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLESETDLG_H__2F2D5B73_5712_46E9_B576_71D6CCCF5AF3__INCLUDED_)
