#if !defined(AFX_CONFIGNETWORK_H__386A72F1_6728_48A2_926F_08B2F2575673__INCLUDED_)
#define AFX_CONFIGNETWORK_H__386A72F1_6728_48A2_926F_08B2F2575673__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigNetwork.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigNetwork dialog

class CConfigNetwork : public CDialog
{
// Construction
public:
//	void SaveNetCfgInfo(SDK_NetOrderConfig *pNetOrder);
	void SaveNetCfgInfo();
	SDK_CONFIG_NET_COMMON m_pNetCommon;
	SDK_NetDNSConfig m_pNetDNS;
	SDK_NetDHCPConfigAll m_pNetDHCP;
	SDK_NetOrderConfig m_pNetOrder;
	SDK_NetOrderFunction m_pNetOrderFunc;
	void CleanAll();
	void InitDlgInfo(SDK_CONFIG_NET_COMMON *pNetCommon,SDK_NetDNSConfig *pNetDNS,SDK_NetDHCPConfigAll *pNetDHCP,SDK_NetOrderConfig *pNetOrder,SDK_NetOrderFunction *pNetOrderFunc);
	CConfigNetwork(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigNetwork)
	enum { IDD = IDD_CONFIG_NETWORK };
	CButton	m_HightLoaddown;
	CComboBox	m_ctlNetCard;
	CComboBox	m_ctlTransferPolicy;
	CIPAddressCtrl	m_ctlSecondaryDNS;
	CIPAddressCtrl	m_ctlPrimaryDNS;
	CIPAddressCtrl	m_ctlNetGateWay;
	CIPAddressCtrl	m_ctlNetIPMask;
	CIPAddressCtrl	m_ctlNetIP;
	BOOL	m_bDHCP;
	BOOL	m_bHightLoadDown;
	CString	m_EditMac1;
	CString	m_EditMac2;
	CString	m_EditMac3;
	CString	m_EditMac4;
	CString	m_EditMac5;
	CString	m_EditMac6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigNetwork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigNetwork)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	afx_msg void OnCHECKDHCPEnable();
	afx_msg void OnKillfocusEditMac6();
	afx_msg void OnChangeEditMac6();
	afx_msg void OnChangeEditTcpport();
	afx_msg void OnChangeEditHttpport();
	afx_msg void OnButtonNetpre();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGNETWORK_H__386A72F1_6728_48A2_926F_08B2F2575673__INCLUDED_)
