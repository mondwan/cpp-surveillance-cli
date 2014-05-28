#if !defined(AFX_NETSERVERSHISOU_H__0C719190_8334_43F9_B2B9_F28070503A08__INCLUDED_)
#define AFX_NETSERVERSHISOU_H__0C719190_8334_43F9_B2B9_F28070503A08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerSHISOU.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerSHISOU dialog

class CNetServerSHISOU : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_CONFIG_NET_SHISOU *pNetSHISOUCfg);
	CNetServerSHISOU(CWnd* pParent = NULL);   // standard constructor
	BOOL m_ensure;
	SDK_CONFIG_NET_SHISOU m_netSHISOUCfg;
// Dialog Data
	//{{AFX_DATA(CNetServerSHISOU)
	enum { IDD = IDD_CONFIG_NETSERVER_SHISOU };
	CButton	m_checkEnable;
	CString	m_sDevID;
	CString	m_sServerIP;
	int		m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerSHISOU)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerSHISOU)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnable();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERSHISOU_H__0C719190_8334_43F9_B2B9_F28070503A08__INCLUDED_)
