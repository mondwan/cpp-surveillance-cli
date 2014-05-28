#if !defined(AFX_NETSERVERPPPOE_H__86ECEF93_CF30_4A64_8828_BBE13AA123CF__INCLUDED_)
#define AFX_NETSERVERPPPOE_H__86ECEF93_CF30_4A64_8828_BBE13AA123CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerPPPOE.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerPPPOE dialog

class CNetServerPPPOE : public CDialog
{
// Construction
public:
	void SaveConfig();
	BOOL m_ensure;
	SDK_NetPPPoEConfig m_netPPPOECfg;
	void InitDlgInfo(SDK_NetPPPoEConfig *pNetPPPOECfg);
	CNetServerPPPOE(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerPPPOE)
	enum { IDD = IDD_CONFIG_NETSERVER_PPPOE };
	CIPAddressCtrl	m_ipAddr;
	CButton	m_ctlPPPOEEnable;
	CString	m_password;
	CString	m_userName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerPPPOE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerPPPOE)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckPppoeEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERPPPOE_H__86ECEF93_CF30_4A64_8828_BBE13AA123CF__INCLUDED_)
