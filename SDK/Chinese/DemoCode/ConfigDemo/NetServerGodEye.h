#if !defined(AFX_NETSERVERGODEYE_H__762913D5_F659_446E_9EA4_CE1263210EDB__INCLUDED_)
#define AFX_NETSERVERGODEYE_H__762913D5_F659_446E_9EA4_CE1263210EDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerGodEye.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerGodEye dialog

class CNetServerGodEye : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_GodEyeConfig *pNetGodEyeCfg);
	CNetServerGodEye(CWnd* pParent = NULL);   // standard constructor
	BOOL m_ensure;
	SDK_GodEyeConfig m_netGodEyeCfg;
// Dialog Data
	//{{AFX_DATA(CNetServerGodEye)
	enum { IDD = IDD_CONFIG_NETSERVER_GODEYE };
	CButton	m_checkEnable;
	int		m_nExtraPort;
	CString	m_sExtraAddr;
	CString	m_sMainAddr;
	int		m_nMianPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerGodEye)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerGodEye)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERGODEYE_H__762913D5_F659_446E_9EA4_CE1263210EDB__INCLUDED_)
