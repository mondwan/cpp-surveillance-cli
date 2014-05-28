#if !defined(AFX_NETSERVERMOBILE_H__A8E04314_A645_4CD7_98C7_7235B9BFD61A__INCLUDED_)
#define AFX_NETSERVERMOBILE_H__A8E04314_A645_4CD7_98C7_7235B9BFD61A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerMobile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerMobile dialog

class CNetServerMobile : public CDialog
{
// Construction
public:
	void SaveConfig();
	void InitDlgInfo(SDK_NetMoblieConfig *pNetMobileCfg);
	SDK_NetMoblieConfig m_netMobileCfg;
	BOOL m_ensure;
	CNetServerMobile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerMobile)
	enum { IDD = IDD_CONFIG_NETSERVER_MOBILE };
	CButton	m_checkEnable;
	int		m_iPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerMobile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerMobile)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckMobileEnable();
	afx_msg void OnKillfocusEditPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERMOBILE_H__A8E04314_A645_4CD7_98C7_7235B9BFD61A__INCLUDED_)
