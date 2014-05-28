#if !defined(AFX_NETSERVERDDNS_H__9014C33E_E931_4289_87B8_C739B3A2480C__INCLUDED_)
#define AFX_NETSERVERDDNS_H__9014C33E_E931_4289_87B8_C739B3A2480C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerDDNS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerDDNS dialog

class CNetServerDDNS : public CDialog
{
// Construction
public:
	void SaveConfig( int nType );
	void UpdataDDNStype(int nType);
	BOOL m_ensure;
	SDK_NetDDNSConfigALL m_netDDNSCfg;
	SDK_DDNSServiceFunction m_DDNSFunc;		//DDNS支持类型
	int m_nOldSelect;
	void InitDlgInfo(SDK_NetDDNSConfigALL* pNetDDNSCfg,SDK_DDNSServiceFunction *pDDNSFunc);
	CNetServerDDNS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerDDNS)
	enum { IDD = IDD_CONFIG_NETSERVER_DDNS };
	CButton	m_checkInUsing;
	CEdit	m_editUserName;
	CEdit	m_editServerDomain;
	CEdit	m_editPsw;
	CEdit	m_editPort;
	CEdit	m_editLocalDomain;
	CComboBox	m_cmbDDNSType;
	CButton	m_checkEnable;
	int		m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerDDNS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerDDNS)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDdnskey();
	virtual void OnOK();
	afx_msg void OnCheckEnable();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboDdnsType();
	afx_msg void OnKillfocusEditPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERDDNS_H__9014C33E_E931_4289_87B8_C739B3A2480C__INCLUDED_)
