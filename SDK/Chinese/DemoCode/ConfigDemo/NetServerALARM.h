#if !defined(AFX_NETSERVERALARM_H__A83459B0_1A4C_4FAF_9A55_800BF5A0AE68__INCLUDED_)
#define AFX_NETSERVERALARM_H__A83459B0_1A4C_4FAF_9A55_800BF5A0AE68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerALARM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerALARM dialog

class CNetServerALARM : public CDialog
{
// Construction
public:
	void SaveConfig(int nType);
	void UpdateAlarmCenterType(int nType);
	void InitDlgInfo(SDK_NetAlarmServerConfigAll *pNetAlarmCfg);
	CNetServerALARM(CWnd* pParent = NULL);   // standard constructor
	BOOL m_ensure;
	int m_nOldSelect;
	SDK_NetAlarmServerConfigAll m_netAlarmCenterCfg;
// Dialog Data
	//{{AFX_DATA(CNetServerALARM)
	enum { IDD = IDD_CONFIG_NETSERVER_ALARM_CENTER };
	CEdit	m_editSVR;
	CEdit	m_editPort;
	CComboBox	m_cmbType;
	CButton	m_checkLog;
	CButton	m_checkEnable;
	CButton	m_checkAlarm;
	CString	m_sServerName;
	int		m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerALARM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerALARM)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboType();
	virtual void OnOK();
	afx_msg void OnCheckEanble();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERALARM_H__A83459B0_1A4C_4FAF_9A55_800BF5A0AE68__INCLUDED_)
