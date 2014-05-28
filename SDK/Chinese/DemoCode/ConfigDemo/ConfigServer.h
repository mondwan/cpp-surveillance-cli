#if !defined(AFX_CONFIGSERVER_H__699AD959_0E44_462B_BD8D_22877DACAF70__INCLUDED_)
#define AFX_CONFIGSERVER_H__699AD959_0E44_462B_BD8D_22877DACAF70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigServer dialog

class CConfigServer : public CDialog
{
// Construction
public:
	void CleanAll();
	void InitDlgInfo(DEV_ATTRIBUTE *pDevAttribute,SDK_MultiLangFunction *PLang);
	CConfigServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigServer)
	enum { IDD = IDD_CONFIG_SERVER };
	CComboBox	m_SelectLanguage;
	CComboBox	m_ctlTimeFormat;
	CComboBox	m_ctlDateSpr;
	CComboBox	m_ctlDateFormat;
	CComboBox	m_ctlVideoFormat;
	CComboBox	m_ctlDiskFull;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigServer)
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReadall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsValid();
	void InitComboBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGSERVER_H__699AD959_0E44_462B_BD8D_22877DACAF70__INCLUDED_)
