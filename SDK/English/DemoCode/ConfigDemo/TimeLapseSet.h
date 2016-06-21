#if !defined(AFX_TIMELAPSESET_H__8B489AA3_E1AA_4E5C_9D26_C1B3F9F91097__INCLUDED_)
#define AFX_TIMELAPSESET_H__8B489AA3_E1AA_4E5C_9D26_C1B3F9F91097__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeLapseSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeLapseSet dialog

class CTimeLapseSet : public CDialog
{
// Construction
public:
	CTimeLapseSet(CWnd* pParent = NULL);   // standard constructor
	void InitDlgInfo(SDK_CarDelayTimeConfig *pCarDelayTimeCfg, bool bShow =true);
	SDK_CarDelayTimeConfig m_CarDelayTiemCfg;
	BOOL SaveTimeLapseInfo();
// Dialog Data
	//{{AFX_DATA(CTimeLapseSet)
	enum { IDD = IDD_DLG_TIME_LAPSE };
	CButton	m_ctrlEnableC;
	CEdit	m_ctrlDelayC;
	CEdit	m_ctrlDelayO;
	CButton	m_ctrlEnableO;
	int		m_DelayC;
	int		m_DelayO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeLapseSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeLapseSet)
	afx_msg void OnEnableOpen();
	afx_msg void OnEnableClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMELAPSESET_H__8B489AA3_E1AA_4E5C_9D26_C1B3F9F91097__INCLUDED_)
