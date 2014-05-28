#if !defined(AFX_NETPRE_H__A0E68E6F_339B_40F1_8631_A7B1B8784437__INCLUDED_)
#define AFX_NETPRE_H__A0E68E6F_339B_40F1_8631_A7B1B8784437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetPre.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetPre dialog

class CNetPre : public CDialog
{
// Construction
public:
	CNetPre(SDK_NetOrderConfig* pNetOrder,CWnd* pParent = NULL);   // standard constructor
	int m_netCount;
	int IndexInFieldList;
	SDK_NetOrderConfig m_pNetOrder;
// Dialog Data
	//{{AFX_DATA(CNetPre)
	enum { IDD = IDD_CONFIG_NETPRE };
	CListCtrl	m_listctrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetPre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetPre)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDowm();
	virtual void OnOK();
	afx_msg void OnClickListNetpre(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckNetpre();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETPRE_H__A0E68E6F_339B_40F1_8631_A7B1B8784437__INCLUDED_)
