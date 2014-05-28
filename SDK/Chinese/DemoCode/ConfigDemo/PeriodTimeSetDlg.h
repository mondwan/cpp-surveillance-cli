#if !defined(AFX_PERIODTIMESETDLG_H__BAE52624_909C_467A_B29C_3C9CB0384BF3__INCLUDED_)
#define AFX_PERIODTIMESETDLG_H__BAE52624_909C_467A_B29C_3C9CB0384BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PeriodTimeSetDlg.h : header file
//
#include "Resource.h"
#include "afxwin.h"
#include "TimeLineShowWnd.h"

#define ID_TIME_DRAW	(WM_USER + 6600)

/////////////////////////////////////////////////////////////////////////////
// CPeriodTimeSetDlg dialog

class CPeriodTimeSetDlg : public CDialog
{
// Construction
public:
	SDK_CONFIG_WORKSHEET *GetConfigWorkSheet();
	CPeriodTimeSetDlg(SDK_CONFIG_WORKSHEET *pPeriod = NULL,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPeriodTimeSetDlg)
	enum { IDD = IDD_DLG_TIME_SET };
	CComboBox	m_weekChoose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeriodTimeSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateTime(int nPeriod, int nTime);
	void DrowLineInfo( int nWeek, int nSect );

	// Generated message map functions
	//{{AFX_MSG(CPeriodTimeSetDlg)
	afx_msg void OnCancel();
	afx_msg void OnOK();
	afx_msg void  OnBnClickedCheck( UINT nID );
	afx_msg void OnEditKillFous( UINT nID );
	afx_msg void OnEditChanged( UINT nID );
	afx_msg void OnCbnSelChangeWeek();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HINSTANCE OldResourceHanlde;
	SDK_CONFIG_WORKSHEET m_period;
	SDK_TIMESECTION * m_pTimeSectValue[NET_N_TSECT];
	CTimeLineShowWnd m_TimeLineDraw[NET_N_WEEKS];
	UINT * m_Time[NET_N_TSECT][4];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERIODTIMESETDLG_H__BAE52624_909C_467A_B29C_3C9CB0384BF3__INCLUDED_)
