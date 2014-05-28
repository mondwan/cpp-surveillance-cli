#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// CUserAddDlg 对话框

class CUserAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserAddDlg)

public:
	CUserAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserAddDlg();

// 对话框数据
	enum { IDD = IDD_DLG_USER_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkReuseable;
public:
	CComboBox m_cmbGroup;
public:
	CEdit m_editConfirm;
public:
	CString m_strConfirm;
public:
	CEdit m_editDescribe;
public:
	CString m_strDescribe;
public:
	CEdit m_editPsw;
public:
	CString m_strPsw;
public:
	CEdit m_editName;
public:
	CString m_strName;
public:
	CListCtrl m_listAuthority;

	int m_nType;

public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnCbnSelchangeComboGroup();
public:
	afx_msg void OnBnClickedOk();
public:
	CString m_strGroupName;

	void UpdateAuthorityList(CString strGroup);
	USER_MANAGE_INFO *m_userinfo;		//用户信息
	USER_GROUP_INFO* GetGroupInfo(char * strName);
	bool FindUserName(char *szUserName);
	CString GetSdkErrorInfo(int nError);
	int SaveuserInfo(USER_INFO *pUserinfo);
	long m_loginID;
};
