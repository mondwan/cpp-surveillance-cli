#if !defined(AFX_USERDELETEGROUPDLG_H__6ED42EC9_D6F5_4016_AD2F_C8DD4CB0E48A__INCLUDED_)
#define AFX_USERDELETEGROUPDLG_H__6ED42EC9_D6F5_4016_AD2F_C8DD4CB0E48A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDeleteGroupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDeleteGroupDlg dialog

class CUserDeleteGroupDlg : public CDialog
{
// Construction
public:
	CUserDeleteGroupDlg(CWnd* pParent = NULL);   // standard constructor
	USER_MANAGE_INFO *m_userinfo;		//用户信息
	USER_GROUP_INFO* GetGroupInfo(char * strName);
	bool HasUser(CString strGroup);
	long m_loginID;
	CString GetSdkErrorInfo(int nError);
	int DeleteGroupInfo(USER_GROUP_INFO *pGroupinfo);
// Dialog Data
	//{{AFX_DATA(CUserDeleteGroupDlg)
	enum { IDD = IDD_DLG_USER_DELETE_GROUP };
	CEdit	m_editName;
	CEdit	m_editDescribe;
	CComboBox	m_cmbGroup;
	CString	m_strGroup;
	CString	m_strDescribe;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDeleteGroupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDeleteGroupDlg)
	afx_msg void OnSelchangeComboGroup();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


		HINSTANCE OldResourceHanlde;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDELETEGROUPDLG_H__6ED42EC9_D6F5_4016_AD2F_C8DD4CB0E48A__INCLUDED_)
