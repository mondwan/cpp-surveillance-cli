#if !defined(AFX_NETSERVERNETINFO_H__D05EFDDC_758E_4FCF_853B_585D263D1A0C__INCLUDED_)
#define AFX_NETSERVERNETINFO_H__D05EFDDC_758E_4FCF_853B_585D263D1A0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerNetInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerNetInfo dialog

class CNetServerNetInfo : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_LocalSdkNetPlatformConfig *pLocSdkNetPC);
	CNetServerNetInfo(CWnd* pParent = NULL);   // standard constructor
	BOOL m_ensure;
	SDK_LocalSdkNetPlatformConfig m_LocSdkNetPC;
// Dialog Data
	//{{AFX_DATA(CNetServerNetInfo)
	enum { IDD = IDD_CONFIG_NETSERVER_NETIFNO };
	CButton	m_checkEnable;
	CIPAddressCtrl	m_ctrlIpAddress;
	CComboBox	m_ctrlNetIsp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerNetInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerNetInfo)
	afx_msg void OnCheckEnable();
	virtual void OnOK();
	afx_msg void OnChangeEditPort();
	afx_msg void OnKillfocusEditPort();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERNETINFO_H__D05EFDDC_758E_4FCF_853B_585D263D1A0C__INCLUDED_)
