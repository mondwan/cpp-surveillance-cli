#if !defined(AFX_NETSERVER3G_H__8BABA30C_6EC5_40C9_BDCE_049EB3F3CC2D__INCLUDED_)
#define AFX_NETSERVER3G_H__8BABA30C_6EC5_40C9_BDCE_049EB3F3CC2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServer3G.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServer3G dialog

class CNetServer3G : public CDialog
{
// Construction
public:
	void SaveConfig();
	BOOL m_ensure;
	SDK_Net3GConfig m_net3GCfg;
	void InitDlgInfo(SDK_Net3GConfig *pNet3GCfg);
	CNetServer3G(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServer3G)
	enum { IDD = IDD_CONFIG_NETSERVER_3G };
	CIPAddressCtrl	m_IPAddr;
	CEdit	m_editUserName;
	CEdit	m_editPassword;
	CEdit	m_editDialNum;
	CEdit	m_editAPN;
	CComboBox	m_cmbNetType;
	CButton	m_checkEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServer3G)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServer3G)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVER3G_H__8BABA30C_6EC5_40C9_BDCE_049EB3F3CC2D__INCLUDED_)
