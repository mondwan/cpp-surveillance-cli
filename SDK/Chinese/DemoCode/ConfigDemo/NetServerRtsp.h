#if !defined(AFX_NETSERVERRTSP_H__51C58454_FC0A_4C35_B843_E2F344CE4B3F__INCLUDED_)
#define AFX_NETSERVERRTSP_H__51C58454_FC0A_4C35_B843_E2F344CE4B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerRtsp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerRtsp dialog

class CNetServerRtsp : public CDialog
{
// Construction
public:
	void InitDlgInfo(SDK_NetRTSPConfig *pNetRTSPCfg);
	CNetServerRtsp(CWnd* pParent = NULL);   // standard constructor
	SDK_NetRTSPConfig m_netRTSPCfg;
	BOOL m_ensure;
// Dialog Data
	//{{AFX_DATA(CNetServerRtsp)
	enum { IDD = IDD_CONFIG_NETSERVER_RTSP };
	CEdit	m_editPort;
	CButton	m_checkEnable;
	int		m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerRtsp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerRtsp)
	afx_msg void OnCheckEnable();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERRTSP_H__51C58454_FC0A_4C35_B843_E2F344CE4B3F__INCLUDED_)
