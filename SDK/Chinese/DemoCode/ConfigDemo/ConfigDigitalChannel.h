#if !defined(AFX_CONFIGDIGITALCHANNEL_H__990F99E8_1AC2_49A5_A971_F5DBE96BE8AF__INCLUDED_)
#define AFX_CONFIGDIGITALCHANNEL_H__990F99E8_1AC2_49A5_A971_F5DBE96BE8AF__INCLUDED_

#include "DigitalChannelDlg.h"	// Added by ClassView
#include "DlgChannelMode.h"
#include "DlgChannelStatus.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDigitalChannel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDigitalChannel dialog

class CConfigDigitalChannel : public CDialog
{
// Construction
public:
	void ClearAll();
	int m_nLastItem;
	CDlgChannelMode m_dlgChannelMode;
	CDlgChannelStatus m_dlgChannelStatus;

	CDigitalChannelDlg m_dlgDigitalChannel;
	CConfigDigitalChannel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDigitalChannel)
	enum { IDD = IDD_CONFIG_DIGITALCHANNEL };
	CTabCtrl	m_ctlTabDigital;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDigitalChannel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDigitalChannel)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabDigital(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnRefrush();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetDlgState(CWnd* pWnd, BOOL bShow);
	void DoTab(int nTab);
	void InitTabControl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDIGITALCHANNEL_H__990F99E8_1AC2_49A5_A971_F5DBE96BE8AF__INCLUDED_)
