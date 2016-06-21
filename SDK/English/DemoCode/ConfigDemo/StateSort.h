#if !defined(AFX_STATESORT_H__A3EAE62C_8A6A_4768_87A5_95620E5B0B38__INCLUDED_)
#define AFX_STATESORT_H__A3EAE62C_8A6A_4768_87A5_95620E5B0B38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StateSort.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStateSort dialog
#define StateCount SDK_CAR_STATUS_NR
#include "VehicleState.h"
class CStateSort : public CDialog
{
// Construction
public:
	CStateSort(SDK_CarStatusExchangeAll *pCarStaExg,CWnd* pParent = NULL);   // standard constructor
	int nStateCount;
	BOOL mState[StateCount];
	BOOL n_update;
	void InitDlgInfo();
	SDK_CarStatusExchangeAll mStaSortExg;
	SDK_CarDelayTimeConfig mStaSortCf;
// Dialog Data
	//{{AFX_DATA(CStateSort)
	enum { IDD = IDD_DLG_STATESORT };
	CButton	m_ctrlCheck8;
	CButton	m_ctrlCheck7;
	CButton	m_ctrlCheck6;
	CButton	m_ctrlCheck5;
	CButton	m_ctrlCheck4;
	CButton	m_ctrlCheck3;
	CButton	m_ctrlCheck2;
	CButton	m_ctrlCheck1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStateSort)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStateSort)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATESORT_H__A3EAE62C_8A6A_4768_87A5_95620E5B0B38__INCLUDED_)
