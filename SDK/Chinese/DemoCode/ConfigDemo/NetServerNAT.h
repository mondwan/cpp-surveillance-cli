#if !defined(AFX_NETSERVERNAT_H__4600FD2D_FB77_4DC1_A85D_DC14341F2980__INCLUDED_)
#define AFX_NETSERVERNAT_H__4600FD2D_FB77_4DC1_A85D_DC14341F2980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerNAT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerNAT dialog

class CNetServerNAT : public CDialog
{
// Construction
public:
	CNetServerNAT(CWnd* pParent = NULL);   // standard constructor
	void InitDlgInfo(SDK_NatConfig *pNatCfg);
	SDK_NatConfig m_natCfg;
	BOOL m_ensure;
	void SaveConfig();
// Dialog Data
	//{{AFX_DATA(CNetServerNAT)
	enum { IDD = IDD_CONFIG_NETSERVER_NAT };
	CButton	m_checkEnable;
	int		m_iMTU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerNAT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerNAT)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERNAT_H__4600FD2D_FB77_4DC1_A85D_DC14341F2980__INCLUDED_)
