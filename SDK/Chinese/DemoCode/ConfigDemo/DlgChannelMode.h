#if !defined(AFX_DLGCHANNELMODE_H__A7828246_1775_4C74_B5A0_6FECF150DF56__INCLUDED_)
#define AFX_DLGCHANNELMODE_H__A7828246_1775_4C74_B5A0_6FECF150DF56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChannelMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChannelMode dialog

class CDlgChannelMode : public CDialog
{
// Construction
public:
	void ClearAll();
	void SaveChnModeCfg();
	bool WinDataToStruct();
	bool StructToWinData();
	SDK_NetDecorderChnModeConfig m_ChnModeCfg;
	void InitDlgInfo(SDK_NetDecorderChnModeConfig* pNetChnModeConfig);
	CDlgChannelMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChannelMode)
	enum { IDD = IDD_DIG_CHANNELMODE };
	CListCtrl	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChannelMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChannelMode)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListChannelmode(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_bSetCheck;
	int m_nCheckItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANNELMODE_H__A7828246_1775_4C74_B5A0_6FECF150DF56__INCLUDED_)
