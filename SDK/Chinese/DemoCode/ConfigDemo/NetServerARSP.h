#if !defined(AFX_NETSERVERARSP_H__FE7B8868_EC1D_48F5_859F_FF519ED68ED8__INCLUDED_)
#define AFX_NETSERVERARSP_H__FE7B8868_EC1D_48F5_859F_FF519ED68ED8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <vector>
#endif // _MSC_VER > 1000
// NetServerARSP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerARSP dialog

class CNetServerARSP : public CDialog
{
// Construction
public:
	SDK_NetARSPConfigAll m_netARSPCfg;
	void InitDlgInfo(SDK_NetARSPConfigAll *pNetARSPCfg);
	BOOL m_ensure;
	CNetServerARSP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerARSP)
	enum { IDD = IDD_CONFIG_NETSERVER_ARSP };
	CEdit	m_editLocalDomain;
	CButton	m_checkEnable;
	CComboBox	m_cmbDDNSType;
	CEdit	m_editUserName;
	CEdit	m_editSvrDomain;
	CEdit	m_editPort;
	CEdit	m_editPassword;
	CEdit	m_editInterval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerARSP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
private:
	std::vector<std::string> protocolList;
	int m_nOldSelect;
// Implementation
protected:
	void UpdateDDNSTYPE(int nType);
	void SaveConfig(int nType);
	// Generated message map functions
	//{{AFX_MSG(CNetServerARSP)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckArspEnable();
	afx_msg void OnSelchangeComboDdnsType();
	afx_msg void OnKillfocusEditPort();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERARSP_H__FE7B8868_EC1D_48F5_859F_FF519ED68ED8__INCLUDED_)
