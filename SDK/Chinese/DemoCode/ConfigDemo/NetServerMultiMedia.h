#if !defined(AFX_NETSERVERMULTIMEDIA_H__5BD60E1E_94B8_4D92_BBB4_3ED07EDD3D6B__INCLUDED_)
#define AFX_NETSERVERMULTIMEDIA_H__5BD60E1E_94B8_4D92_BBB4_3ED07EDD3D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetServerMultiMedia.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetServerMultiMedia dialog

class CNetServerMultiMedia : public CDialog
{
// Construction
public:
	BOOL m_ensure;
	SDK_NetMultimediaMsgCfg m_netMultimediaMsgCfg;
	void InitDlgInfo(SDK_NetMultimediaMsgCfg *pNetMultimediaMsgCfg);
	CNetServerMultiMedia(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetServerMultiMedia)
	enum { IDD = IDD_CONFIG_NETSERVER_MULTIMEDIA };
	CButton	m_checkEnable;
	CString	m_sGateWay;
	int		m_nGateWayPort;
	CString	m_sMmsc;
	int		m_nMmscPort;
	CString	m_sPhone1;
	CString	m_sPhone3;
	CString	m_sPhone2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetServerMultiMedia)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetServerMultiMedia)
	afx_msg void OnCheckEnable();
	afx_msg void OnChangeEditGateway();
	afx_msg void OnChangeEditGatewayPort();
	afx_msg void OnChangeEditMmsc();
	afx_msg void OnChangeEditMmscPort();
	afx_msg void OnChangeEditPhone1();
	afx_msg void OnChangeEditPhone2();
	afx_msg void OnChangeEditPhone3();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSERVERMULTIMEDIA_H__5BD60E1E_94B8_4D92_BBB4_3ED07EDD3D6B__INCLUDED_)
