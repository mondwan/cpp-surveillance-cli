#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"

// CUserAddGroupDlg 对话框

class CUserAddGroupDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserAddGroupDlg)

public:
	CUserAddGroupDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserAddGroupDlg();

// 对话框数据
	enum { IDD = IDD_DLG_USER_ADD_GROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CComboBox m_cmbGroup;
public:
	CString m_strGroup;
public:
	CEdit m_editDescribe;
public:
	CString m_strDescribe;
public:
	CEdit m_editName;
public:
	CString m_strName;
public:
	CListCtrl m_listAuthority;
	int m_ntype;
public:
	afx_msg void OnCbnSelchangeComboGroup();
public:
	virtual BOOL OnInitDialog();

	bool CheckRight(const char *szright, USER_GROUP_INFO *pUser);
	void UpdateAuthority(CString strGroup);
public:
	afx_msg void OnBnClickedBtnDelete();
	USER_MANAGE_INFO *m_userinfo;		//用户信息
	bool FindGroupName(char *szUserName);
	int ModifyGroupInfo(CONF_MODIFYGROUP *pGroupinfo);
	long m_loginID;
	int AddGroupInfo(USER_GROUP_INFO *pGroupinfo);
	USER_GROUP_INFO* GetGroupInfo(char * strName);
	CString GetSdkErrorInfo(int nError);
	int DeleteGroupInfo(USER_GROUP_INFO *pGroupinfo);
	bool HasUser(CString strGroup);
};
