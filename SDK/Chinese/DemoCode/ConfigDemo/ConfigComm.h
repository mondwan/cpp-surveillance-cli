#if !defined(AFX_CONFIGCOMM_H__9D9281E6_50C5_46B7_9297_D7F1AE6F29AC__INCLUDED_)
#define AFX_CONFIGCOMM_H__9D9281E6_50C5_46B7_9297_D7F1AE6F29AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigComm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigComm dialog

class CConfigComm : public CDialog
{
// Construction
public:
	void ShowComm();
	void SaveComm();
	SDK_CommConfigAll m_CommConfigAll;
	void CleanAll();
	void InitDlgInfo(SDK_CommConfigAll *pCommCfg,SDK_COMMFUNC *pCommFunc);
	CConfigComm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigComm)
	enum { IDD = IDD_CONFIG_COMM };
	CComboBox	m_ctlCommFun;
	CComboBox	m_ctlCommData;
	CComboBox	m_ctlCommStopBit;
	CComboBox	m_ctlCommBaud;
	CComboBox	m_ctlCommParity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigComm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigComm)
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReadall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitCombo();
	SDK_COMMFUNC m_CommFunc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCOMM_H__9D9281E6_50C5_46B7_9297_D7F1AE6F29AC__INCLUDED_)
