#if !defined(AFX_NETSERVERWIFI_H__8E8270BF_B0BA_42CC_B900_278F8B05EC3A__INCLUDED_)
#define AFX_NETSERVERWIFI_H__8E8270BF_B0BA_42CC_B900_278F8B05EC3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerWIFI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerWIFI dialog

class CNetServerWIFI : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_NetWifiConfig *pNetWIFICfg);
	SDK_NetWifiConfig m_netWIFICfg;
	BOOL m_ensure;
	BOOL m_bDhcpVisible;
	int m_nLastKey;
	SDK_NetWifiDevice *m_pCurAP;
	SDK_NetWifiDeviceAll m_WifiDevAll;
	CNetServerWIFI(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CNetServerWIFI)
	enum { IDD = IDD_CONFIG_NETSERVER_WIFI };
	CEdit	m_editSSID;
	CEdit	m_editPSW;
	CIPAddressCtrl	m_IPMask;
	CIPAddressCtrl	m_IPGateWay;
	CIPAddressCtrl	m_IPAddr;
	CComboBox	m_cmbKeyType;
	CComboBox	m_cmbEncryp;
	CButton	m_checkWIFI;
	CButton	m_checkDHCP;
	CListCtrl	m_listAP;
	CString	m_sPassword;
	CString	m_sSSID;
	BOOL	m_bDhcp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerWIFI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerWIFI)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearch();
	afx_msg void OnCheckEnable();
	afx_msg void OnCheckDhcp();
	afx_msg void OnItemchangedApList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnSelchangeComboKeytype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERWIFI_H__8E8270BF_B0BA_42CC_B900_278F8B05EC3A__INCLUDED_)
