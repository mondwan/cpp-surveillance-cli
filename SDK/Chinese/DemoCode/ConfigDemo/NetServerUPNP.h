#if !defined(AFX_NETSERVERUPNP_H__6E1CD4BD_438C_425F_A0D2_09DC70B1F184__INCLUDED_)
#define AFX_NETSERVERUPNP_H__6E1CD4BD_438C_425F_A0D2_09DC70B1F184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerUPNP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerUPNP dialog

class CNetServerUPNP : public CDialog
{
// Construction
public:
	void SaveConfig();
	void InitDlgInfo(SDK_NetUPNPConfig *pNetUPNPCfg);
	SDK_NetUPNPConfig m_netUPNPCfg;
	BOOL m_ensure;
	CNetServerUPNP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerUPNP)
	enum { IDD = IDD_CONFIG_NETSERVER_UPNP };
	CButton	m_checkEnable;
	int		m_nHtppPort;
	int		m_nMobilePort;
	int		m_nTcpPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerUPNP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerUPNP)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERUPNP_H__6E1CD4BD_438C_425F_A0D2_09DC70B1F184__INCLUDED_)
