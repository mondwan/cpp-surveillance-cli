#if !defined(AFX_NETSERVERFTP_H__3FD2AC25_3973_46DE_B3EC_EC95408562ED__INCLUDED_)
#define AFX_NETSERVERFTP_H__3FD2AC25_3973_46DE_B3EC_EC95408562ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerFTP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerFTP dialog

class CNetServerFTP : public CDialog
{
// Construction
public:
	void SaveConfig();
	BOOL m_ensure;
	SDK_FtpServerConfig m_ftpCfg;
	void InitDlgInfo(SDK_FtpServerConfig *ftpCfg);
	CNetServerFTP(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CNetServerFTP)
	enum { IDD = IDD_CONFIG_NETSERVER_FTP };
	CEdit	m_editUserName;
	CEdit	m_editServerName;
	CEdit	m_editPSW;
	CEdit	m_editPort;
	CEdit	m_editPath;
	CEdit	m_editMAXFileLen;
	CButton	m_checkFTPEnable;
	CButton	m_checkANONYEnable;
	CIPAddressCtrl	m_IPAddr;
	CString	m_sUserName;
	CString	m_sServerName;
	CString	m_sPassword;
	int		m_nPort;
	CString	m_sPath;
	int		m_nMaxFileLen;
	BOOL	m_bANONYEnable;
	BOOL	m_bFTPEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerFTP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerFTP)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckFtpEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERFTP_H__3FD2AC25_3973_46DE_B3EC_EC95408562ED__INCLUDED_)
