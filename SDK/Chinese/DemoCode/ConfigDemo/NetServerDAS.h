#if !defined(AFX_NETSERVERDAS_H__76D966AB_F7FA_433A_B6F0_9C9C9A540F0D__INCLUDED_)
#define AFX_NETSERVERDAS_H__76D966AB_F7FA_433A_B6F0_9C9C9A540F0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerDAS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerDAS dialog

class CNetServerDAS : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_DASSerInfo *pNetDASCfg);
	CNetServerDAS(CWnd* pParent = NULL);   // standard constructor
	SDK_DASSerInfo m_netDASCfg;
	BOOL m_ensure;
// Dialog Data
	//{{AFX_DATA(CNetServerDAS)
	enum { IDD = IDD_CONFIG_NETSERVER_DAS };
	CIPAddressCtrl	m_IPAddr;
	CEdit	m_editPort;
	CEdit	m_editPWD;
	CEdit	m_editName;
	CEdit	m_editID;
	CEdit	m_editAddr;
	CButton	m_checkEnable;
	CString	m_sAddr;
	CString	m_sDASID;
	CString	m_sDASName;
	int		m_nPort;
	CString	m_sDASPwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerDAS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerDAS)
	afx_msg void OnCheckEnable();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERDAS_H__76D966AB_F7FA_433A_B6F0_9C9C9A540F0D__INCLUDED_)
