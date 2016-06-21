#if !defined(AFX_NETSERVERPMS_H__F0CD8B8A_B52C_4271_940E_6C461EEEF931__INCLUDED_)
#define AFX_NETSERVERPMS_H__F0CD8B8A_B52C_4271_940E_6C461EEEF931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerPMS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerPMS dialog

class CNetServerPMS : public CDialog
{
// Construction
public:
	CNetServerPMS(CWnd* pParent = NULL);   // standard constructor
	void InitDlgInfo(SDK_PMSConfig *pNetPMSCfg,SDK_PhoneInfoNum *pNetPHCfg);
	SDK_PMSConfig m_netPMSCfg;
	SDK_PhoneInfoNum m_netPhCfg;
	BOOL m_ensure;
// Dialog Data
	//{{AFX_DATA(CNetServerPMS)
	enum { IDD = IDD_CONFIG_NETSERVER_PMS };
	CButton	m_btnEnable;
	CButton	m_btnClear;
	CString	m_strAddr;
	CString	m_strBox;
	int		m_nNum;
	int		m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerPMS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerPMS)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnCheckEnable();
	afx_msg void OnBtnClear();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERPMS_H__F0CD8B8A_B52C_4271_940E_6C461EEEF931__INCLUDED_)
