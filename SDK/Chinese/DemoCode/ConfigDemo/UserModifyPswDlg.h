#pragma once
#define   SECURITY_WIN32
#include "afxwin.h"
#include "afxcmn.h"

#include "Resource.h"


// CUserModifyPswDlg 对话框

class CUserModifyPswDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserModifyPswDlg)

public:
	CUserModifyPswDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserModifyPswDlg();
	USER_MANAGE_INFO *m_userinfo;		//用户信息
	USER_INFO* GetUserInfo(char * strName);
	CString GetSdkErrorInfo(int nError);
// 对话框数据
	enum { IDD = IDD_DLG_MODIFY_PSW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CComboBox m_cmbUser;
public:
	CString m_strUser;
public:
	CEdit m_editCofirm;
public:
	CString m_strConfirm;
public:
	CEdit m_editNewpsw;
public:
	CString m_strNewpsw;
public:
	CEdit m_editOldpsw;
public:
	CString m_strOldpsw;
public:
	afx_msg void OnBnClickedOk();
	int Modifypsw(_CONF_MODIFY_PSW *pPsw);

	long m_loginID;
	HINSTANCE OldResourceHanlde;
};
