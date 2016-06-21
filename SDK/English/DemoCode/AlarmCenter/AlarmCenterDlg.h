// AlarmCenterDlg.h : header file
//

#if !defined(AFX_ALARMCENTERDLG_H__0E7F17ED_1C2D_442B_8335_0EA745753B92__INCLUDED_)
#define AFX_ALARMCENTERDLG_H__0E7F17ED_1C2D_442B_8335_0EA745753B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\bin\\NetSdk.h"

/////////////////////////////////////////////////////////////////////////////
// CAlarmCenterDlg dialog

class CAlarmCenterDlg : public CDialog
{
// Construction
public:
	CAlarmCenterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmCenterDlg)
	enum { IDD = IDD_ALARMCENTER_DIALOG };
	CListCtrl	m_LogList;
	int		m_nPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmCenterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAlarmCenterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnStart();
	afx_msg void OnDestroy(); 
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL m_bStart;
public:
	void InsertData(SDK_NetAlarmCenterMsg *pMsg);
	void Resize();
	POINT old;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMCENTERDLG_H__0E7F17ED_1C2D_442B_8335_0EA745753B92__INCLUDED_)
