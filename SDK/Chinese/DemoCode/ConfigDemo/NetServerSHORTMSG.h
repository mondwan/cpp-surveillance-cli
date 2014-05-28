#if !defined(AFX_NETSERVERSHORTMSG_H__D74C9E99_26C4_47FC_8B0C_A3F8E2BBB09B__INCLUDED_)
#define AFX_NETSERVERSHORTMSG_H__D74C9E99_26C4_47FC_8B0C_A3F8E2BBB09B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerSHORTMSG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerSHORTMSG dialog

class CNetServerSHORTMSG : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_NetShortMsgCfg *pNetShortMsgCfg);
	CNetServerSHORTMSG(CWnd* pParent = NULL);   // standard constructor
	BOOL m_ensure;
	SDK_NetShortMsgCfg m_netShortMsgCfg;
// Dialog Data
	//{{AFX_DATA(CNetServerSHORTMSG)
	enum { IDD = IDD_CONFIG_NETSERVER_SHORT_MESSAGE };
	CEdit	m_editSendTimes;
	CEdit	m_editPhone3;
	CEdit	m_editPhone2;
	CEdit	m_editPhone1;
	CButton	m_checkEnable;
	CString	m_sPhoneNum1;
	CString	m_sPhoneNum2;
	CString	m_sPhoneNum3;
	int		m_nSendTimes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerSHORTMSG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerSHORTMSG)
	afx_msg void OnCheckEnable();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERSHORTMSG_H__D74C9E99_26C4_47FC_8B0C_A3F8E2BBB09B__INCLUDED_)
