#if !defined(AFX_VIDEOOSCRULESETDLG_H__D35EF0C3_59DF_4A8B_963F_D716B4A8D4DE__INCLUDED_)
#define AFX_VIDEOOSCRULESETDLG_H__D35EF0C3_59DF_4A8B_963F_D716B4A8D4DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoOSCRuleSetDlg.h : header file
//
#include "DlgOscRuleArea.h"
/////////////////////////////////////////////////////////////////////////////
// CVideoOSCRuleSetDlg dialog

class CVideoOSCRuleSetDlg : public CDialog
{
// Construction
public:
	CVideoOSCRuleSetDlg(/*SDK_OSC_RULE_S* pRule,int nChannelNum,CWnd* pParent = NULL*/);   // standard constructor
	HINSTANCE OldResourceHanlde;
	int m_nChannelNum;
	SDK_OSC_RULE_S m_Rule;
	void SetValue(SDK_OSC_RULE_S* pRule,int nChannelNum);
// Dialog Data
	//{{AFX_DATA(CVideoOSCRuleSetDlg)
	enum { IDD = IDD_DLG_ALARM_OSCRULE_SET };
	CSliderCtrl	m_sliderRangeMin;
	//}}AFX_DATA
	CDlgOscRuleArea dlgAvdRuleArea;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoOSCRuleSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoOSCRuleSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnReleasedcaptureSliderRangeMin(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnBtnRuleSet();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOOSCRULESETDLG_H__D35EF0C3_59DF_4A8B_963F_D716B4A8D4DE__INCLUDED_)
