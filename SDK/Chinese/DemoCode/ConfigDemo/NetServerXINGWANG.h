#if !defined(AFX_NETSERVERXINGWANG_H__A7BFA189_06FB_4EAE_BBA0_368CBEC3FCDC__INCLUDED_)
#define AFX_NETSERVERXINGWANG_H__A7BFA189_06FB_4EAE_BBA0_368CBEC3FCDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerXINGWANG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerXINGWANG dialog

class CNetServerXINGWANG : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_CONFIG_NET_XINGWANG *pNetXIANGWANGCfg);
	CNetServerXINGWANG(CWnd* pParent = NULL);   // standard constructor
	BOOL m_ensure;
	SDK_CONFIG_NET_XINGWANG m_netXIANGWANGCfg;
// Dialog Data
	//{{AFX_DATA(CNetServerXINGWANG)
	enum { IDD = IDD_CONFIG_NETSERVER_XINGWANG };
	CIPAddressCtrl	m_IPAddr;
	CButton	m_checkEnable;
	BOOL	m_bSubStream;
	BOOL	m_bTimeSync;
	CString	m_sPwd;
	int		m_nDownLoadPort;
	int		m_nPort;
	CString	m_sSSID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerXINGWANG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerXINGWANG)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnable();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERXINGWANG_H__A7BFA189_06FB_4EAE_BBA0_368CBEC3FCDC__INCLUDED_)
