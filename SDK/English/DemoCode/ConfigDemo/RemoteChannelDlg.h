#if !defined(AFX_REMOTECHANNELDLG_H__8955FB02_F2C5_482F_AD01_B1D930E289CC__INCLUDED_)
#define AFX_REMOTECHANNELDLG_H__8955FB02_F2C5_482F_AD01_B1D930E289CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemoteChannelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRemoteChannelDlg dialog

class CRemoteChannelDlg : public CDialog
{
// Construction
public:
	CRemoteChannelDlg(SDK_NetDecorderConfigV3 *pNetConfig = NULL,int nDevNum = 0, CWnd* pParent = NULL);   // standard constructor
	void GetData(SDK_CONFIG_NET_COMMON *pNetCommon);
	// Dialog Data
	//{{AFX_DATA(CRemoteChannelDlg)
	enum { IDD = IDD_DLG_REMOTECHANNEL };
	CEdit	m_EditPWD;
	CComboBox	m_cmbDevType;
	CComboBox	m_cmbProc;
	CComboBox	m_cmbStream;
	CEdit	m_EditCfgName;
	CEdit	m_EditPort;
	CEdit	m_EditRemoteChannel;
	CEdit	m_EditUsername;
	CEdit	m_CtrlIPAddress;
	CListCtrl	m_CtrlListDev;
	UINT	m_nPort;
	UINT	m_nRemoteChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteChannelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRemoteChannelDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnSearch();
	afx_msg void OnClickListDev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditPort();
	afx_msg void OnKillfocusEditPort();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HINSTANCE OldResourceHanlde;
	SDK_NetDecorderConfigV3 m_pNetConfig;
	SDK_CONFIG_NET_COMMON m_Device[100];
	int m_nDevNum;
	HANDLE m_hSearch;
	int m_nNum;
	std::map<int , SDK_CONFIG_NET_COMMON> m_mapDev;
	SDK_CONFIG_NET_COMMON m_Netcomm;
	BOOL GetRemoteChannel(SDK_NetDecorderConfigV3* pNetCfg);
	SDK_NetDevList m_Devlist;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMOTECHANNELDLG_H__8955FB02_F2C5_482F_AD01_B1D930E289CC__INCLUDED_)
