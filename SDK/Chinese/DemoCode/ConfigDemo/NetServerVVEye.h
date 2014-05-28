#if !defined(AFX_NETSERVERVVEYE_H__02DF8B21_B2AC_4D8E_BC7F_FA92F9B5444C__INCLUDED_)
#define AFX_NETSERVERVVEYE_H__02DF8B21_B2AC_4D8E_BC7F_FA92F9B5444C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerVVEye.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerVVEye dialog

class CNetServerVVEye : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_CONFIG_NET_VVEYE *pNetVVEyeCfg);
	CNetServerVVEye(CWnd* pParent = NULL);   // standard constructor
	BOOL m_ensure;
	SDK_CONFIG_NET_VVEYE m_netVVEyeCfg;
// Dialog Data
	//{{AFX_DATA(CNetServerVVEye)
	enum { IDD = IDD_CONFIG_NETSERVER_VVEye };
	CButton	m_checkEnable;
	CButton	m_checkCorp;
	CString	m_sDevName;
	CString	m_sPwd;
	CString	m_sServerIP;
	int		m_nPort;
	CString	m_sUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerVVEye)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerVVEye)
	afx_msg void OnCheckEnable();
	afx_msg void OnCheckCorp();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditDeviceName();
	afx_msg void OnChangeEditPwd();
	afx_msg void OnChangeEditServerIp();
	afx_msg void OnChangeEditServerPort();
	afx_msg void OnChangeEditUsername();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERVVEYE_H__02DF8B21_B2AC_4D8E_BC7F_FA92F9B5444C__INCLUDED_)
