#if !defined(AFX_NETSERVERNTP_H__0C45F705_4610_42EE_B555_783BADA83740__INCLUDED_)
#define AFX_NETSERVERNTP_H__0C45F705_4610_42EE_B555_783BADA83740__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerNTP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerNTP dialog

class CNetServerNTP : public CDialog
{
// Construction
public:
	void SaveConfig();
	BOOL m_ensure;
	void InitDlgInfo(SDK_NetNTPConfig* pNetNTPCfg);
	CNetServerNTP(CWnd* pParent = NULL);   // standard constructor
	SDK_NetNTPConfig m_netNTPCfg;
// Dialog Data
	//{{AFX_DATA(CNetServerNTP)
	enum { IDD = IDD_CONFIG_NETSERVER_NTP };
	CButton	m_ctlEnableNTP;
	CComboBox	m_ctlTimezone;
	int		m_port;
	CString	m_serverName;
	int		m_updatePeriod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerNTP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerNTP)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckNtpEnable();
	afx_msg void OnKillfocusEditUpdatePeriod();
	afx_msg void OnKillfocusEditPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERNTP_H__0C45F705_4610_42EE_B555_783BADA83740__INCLUDED_)
