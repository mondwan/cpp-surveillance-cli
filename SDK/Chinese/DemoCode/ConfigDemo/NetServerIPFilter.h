#if !defined(AFX_NETSERVERIPFILTER_H__B9A66F6D_7988_4DA7_BA61_FABFF5148EE6__INCLUDED_)
#define AFX_NETSERVERIPFILTER_H__B9A66F6D_7988_4DA7_BA61_FABFF5148EE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerIPFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerIPFilter dialog

class CNetServerIPFilter : public CDialog
{ 
// Construction
public:
	void Update();
	int IsIPRepeat();
	void InitListCtrl();
	SDK_NetIPFilterConfig m_NetIPFitCfg;
	int m_iBanIPCount;
	int m_iTruIPCount;
	BOOL m_ensure;
	void InitDlgInfo(SDK_NetIPFilterConfig *pNetIPFitCfg);
	CNetServerIPFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerIPFilter)
	enum { IDD = IDD_CONFIG_NETSERVER_IPFILTER };
	CListCtrl	m_listIP;
	CButton	m_delButton;
	CButton	m_addButton;
	CButton	m_enable;
	CComboBox	m_constrainType;
	CIPAddressCtrl	m_ipAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerIPFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerIPFilter)
	afx_msg void OnButtonAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnable();
	afx_msg void OnSelchangeComboConstrainttype();
	afx_msg void OnButtonDel();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERIPFILTER_H__B9A66F6D_7988_4DA7_BA61_FABFF5148EE6__INCLUDED_)
