#if !defined(AFX_DLGCHANNELSTATUS_H__E5347F82_C5E8_42A8_8929_A383F540A6CC__INCLUDED_)
#define AFX_DLGCHANNELSTATUS_H__E5347F82_C5E8_42A8_8929_A383F540A6CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChannelStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChannelStatus dialog

class CDlgChannelStatus : public CDialog
{
// Construction
public:
	void ClearAll();
	bool StructToWinData();
	SDK_NetDecorderChnStatusAll m_ChnStatusAll;
	void InitDlgInfo(SDK_NetDecorderChnStatusAll* pNetChnStatusConfigAll);
	CDlgChannelStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChannelStatus)
	enum { IDD = IDD_DIG_CHANNELSTATUS };
	CListCtrl	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChannelStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChannelStatus)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANNELSTATUS_H__E5347F82_C5E8_42A8_8929_A383F540A6CC__INCLUDED_)
