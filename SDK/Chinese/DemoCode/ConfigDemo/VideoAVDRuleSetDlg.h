#if !defined(AFX_VIDEOAVDRULESETDLG_H__5A4E7485_8B20_43EE_BEAA_806904FE9E19__INCLUDED_)
#define AFX_VIDEOAVDRULESETDLG_H__5A4E7485_8B20_43EE_BEAA_806904FE9E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoAVDRuleSetDlg.h : header file


/////////////////////////////////////////////////////////////////////////////
// CVideoAVDRuleSetDlg dialog

class CVideoAVDRuleSetDlg : public CDialog
{
// Construction
public:
	CVideoAVDRuleSetDlg(SDK_AVD_RULE_S *pAvdRule,int nChannelNum,CWnd* pParent = NULL);   // standard constructor
	SDK_AVD_RULE_S m_rule;
	int m_nChannelNum;
	HINSTANCE OldResourceHanlde;
// Dialog Data
	//{{AFX_DATA(CVideoAVDRuleSetDlg)
	enum { IDD = IDD_DLG_ALARM_AVDRULE_SET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoAVDRuleSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoAVDRuleSetDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOAVDRULESETDLG_H__5A4E7485_8B20_43EE_BEAA_806904FE9E19__INCLUDED_)
