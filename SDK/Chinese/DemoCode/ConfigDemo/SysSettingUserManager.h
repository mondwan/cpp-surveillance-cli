
#pragma once
#include "Resource.h"
#include "afxcmn.h"

class CSysSettingUserManager : public CDialog
{
	DECLARE_DYNAMIC(CSysSettingUserManager)

public:
	CSysSettingUserManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysSettingUserManager();

// 对话框数据
	enum { IDD = IDD_DLG_USER_MANAGER };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddUser();
	afx_msg void OnBnClickedMdUser();
	afx_msg void OnBnClickedAddGroup();
	afx_msg void OnBnClickedMdGroup();
	afx_msg void OnBnClickedMdPsw();
	afx_msg void OnBnClickedDeleteUser();
	afx_msg void OnBnClickedDeleteGroup();

private:	
	USER_MANAGE_INFO m_userinfo;		//用户信息
	bool m_bGetSuccess;					//记录是否成功获取了当前配置，也表示是不是要重新获取数据
private:
	void ClearData();
	bool ShowUserInfo();
public:
	//设置获取状态，是不是要重新获取
	void SetGetStatus( bool bGet )
	{
		m_bGetSuccess = bGet;
	}
public:
	void ClearAll();
	void InitDlgInfo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CListCtrl m_listUser;

	virtual bool WinDataToStruct();
	virtual bool StructToWinData();
	afx_msg void OnBnClickedBtnRefush();
	afx_msg void OnNMRclickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	long m_LoginID;
	int DeleteuserInfo(USER_INFO *pUserinfo);
	USER_INFO*	GetUserInfo(char * strName);
};
