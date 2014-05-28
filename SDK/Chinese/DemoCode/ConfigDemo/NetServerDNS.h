#if !defined(AFX_NETSERVERDNS_H__297ACC71_F744_45CB_BEE8_5D3BAEE3BBCD__INCLUDED_)
#define AFX_NETSERVERDNS_H__297ACC71_F744_45CB_BEE8_5D3BAEE3BBCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerDNS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerDNS dialog

class CNetServerDNS : public CDialog
{
// Construction
public:
	BOOL m_ensure;
	SDK_NetDNSConfig m_netDNSCfg;
	void InitDlgInfo(SDK_NetDNSConfig* pNetDNSCfg);
	CNetServerDNS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerDNS)
	enum { IDD = IDD_CONFIG_NETSERVER_DNS };
	CIPAddressCtrl	m_IP2;
	CIPAddressCtrl	m_IP1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerDNS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerDNS)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERDNS_H__297ACC71_F744_45CB_BEE8_5D3BAEE3BBCD__INCLUDED_)
