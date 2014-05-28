// UserModifyDlg.cpp : 实现文件
//

#include "stdafx.h"

#include "UserModifyDlg.h"





// CUserModifyDlg 对话框

IMPLEMENT_DYNAMIC(CUserModifyDlg, CDialog)

CUserModifyDlg::CUserModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserModifyDlg::IDD, pParent)
	, m_strGroup(_T(""))
	, m_strUserName(_T(""))
	, m_strDescribe(_T(""))
	, m_strName(_T(""))
{
	 	
	m_pUserinfo = NULL;
}

CUserModifyDlg::~CUserModifyDlg()
{
}

void CUserModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_REUSEABLE, m_checkReuseable);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_cmbGroup);
	DDX_CBString(pDX, IDC_COMBO_GROUP, m_strGroup);
	DDX_Control(pDX, IDC_COMBO_USER, m_cmbUserName);
	DDX_CBString(pDX, IDC_COMBO_USER, m_strUserName);
	DDX_Control(pDX, IDC_EDIT_DESCRIBE, m_editDescribe);
	DDX_Text(pDX, IDC_EDIT_DESCRIBE, m_strDescribe);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strName);
	DDX_Control(pDX, IDC_LIST1, m_listAuthrioty);
}


BEGIN_MESSAGE_MAP(CUserModifyDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_USER, CUserModifyDlg::OnCbnSelchangeComboUser)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, CUserModifyDlg::OnCbnSelchangeComboGroup)
	ON_BN_CLICKED(IDOK, CUserModifyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_DELETE, CUserModifyDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CUserModifyDlg 消息处理程序

BOOL CUserModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	m_editName.SetLimitText(8);
	m_editDescribe.SetLimitText(31);

	m_listAuthrioty.SetExtendedStyle(m_listAuthrioty.GetExtendedStyle() | LVS_EX_CHECKBOXES );
	m_listAuthrioty.InsertColumn(0, _CS("UserManager.No"), LVCFMT_LEFT, 50);
	m_listAuthrioty.InsertColumn(1, _CS("UserManager.Authority"),LVCFMT_LEFT, 200 );

	//获取用户信息
	
		USER_MANAGE_INFO *pUser = m_userinfo;
		int i = 0;
		for ( ; i < pUser->groupNum; i ++ )
		{
			if ( strcmp(pUser->groupList[i].name, "") != 0)
			{
				m_cmbGroup.AddString( pUser->groupList[i].name);
			}
		}
	


		
		for ( i = 0; i < pUser->userNum; i ++ )
		{
			if ( strcmp(pUser->userList[i].name, "") != 0 )
			{
				m_cmbUserName.AddString( pUser->userList[i].name );
			}		
		}

	m_cmbUserName.SetCurSel(0);
	
	m_cmbUserName.GetWindowText(m_strUserName);
	//默认选择第一个用户
	UpdateUserInfo(m_strUserName);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUserModifyDlg::UpdateUserInfo(CString strUser)
{
	//获取当前用户信息

		m_pUserinfo = GetUserInfo(strUser.GetBuffer(0));

		if ( m_pUserinfo )
		{
			m_editName.SetWindowText(strUser);
			m_checkReuseable.SetCheck(m_pUserinfo->shareable);
			m_editDescribe.SetWindowText(m_pUserinfo->memo);
			m_cmbGroup.SelectString(-1, m_pUserinfo->Groupname);
			
			m_bresverved = m_pUserinfo->reserved;
			//更新权限
			m_listAuthrioty.DeleteAllItems();
			//找到当前用户组的组权限
			USER_GROUP_INFO *pGroup = GetGroupInfo( (char *)m_pUserinfo->Groupname);
			if ( pGroup )
			{
				int nIndex = 0;
				char szIndex[5];

				for ( int i = 0; i < pGroup->rigthNum; i ++ )
				{
					CString strRigths("Authority.");
					strRigths += pGroup->rights[i];

					sprintf(szIndex, "%d", i +  1);
					m_listAuthrioty.InsertItem(i,szIndex );
					m_listAuthrioty.SetItemText(i, 1, _CS(strRigths) );
					
					m_listAuthrioty.SetItemData(i, (long)pGroup->rights[i] );
					//判断当前权限用户是否有，如果有则打勾
					if ( CheckRight(pGroup->rights[i], m_pUserinfo ) )
					{
						m_listAuthrioty.SetCheck(i);
					}
				}

// 				sprintf(szIndex, "%d", pGroup->rigthNum );
// 				LVCOLUMN count;
// 				count.cx = 50;
// 				count.pszText = szIndex;
// 				m_listAuthrioty.SetColumn(0, &count);
			}
		}

}

bool CUserModifyDlg::FindUserName(char *szUserName)
{
	for ( int i = 0 ; i < m_userinfo->userNum; i ++ )
	{
		if ( !strcmp(szUserName, m_userinfo->userList[i].name ) )
		{
			return true;
		}
	}
	
	return false;	
}
void CUserModifyDlg::OnCbnSelchangeComboUser()
{
	UpdateData();
	
	m_pUserinfo = NULL;

	UpdateUserInfo(m_strUserName);
}

bool CUserModifyDlg::CheckRight(const char *szright, USER_INFO *pUser )
{
	for ( int i = 0; i < pUser->rigthNum; i ++ )
	{
		if ( !strcmp( szright, pUser->rights[i]) )
		{
			return true;
		}
	}

	return false;
}

void CUserModifyDlg::OnCbnSelchangeComboGroup()
{
	UpdateData();

	//获取当前组权限信息
	//更新权限
	m_listAuthrioty.DeleteAllItems();

	
		//找到当前用户组的组权限
		USER_GROUP_INFO *pGroup = GetGroupInfo(m_strGroup.GetBuffer(0));
		if ( pGroup )
		{
			int nIndex = 0;
			char szIndex[5];
			for ( int i = 0; i < pGroup->rigthNum; i ++ )
			{
				CString strRigths("Authority.");
				strRigths += pGroup->rights[i];

				sprintf(szIndex, "%d", i +  1);
				m_listAuthrioty.InsertItem(i,szIndex );
				m_listAuthrioty.SetItemText(i, 1, _CS(strRigths) );
				m_listAuthrioty.SetItemData(i, (long)pGroup->rights[i]);
				if ( m_pUserinfo )
				{
					//判断当前权限用户是否有，如果有则打勾
					if ( CheckRight(pGroup->rights[i], m_pUserinfo ) )
					{
						m_listAuthrioty.SetCheck(i);
					}
				}
			}

// 			sprintf(szIndex, "%d", pGroup->rigthNum );
// 			LVCOLUMN count;
// 			count.cx = 50;
// 			count.pszText = szIndex;
// 			m_listAuthrioty.SetColumn(0, &count);
		}
	
}

int CUserModifyDlg::ModifyuserInfo(CONF_MODIFYUSER *pUserinfo)
{
	int bRet = false;
	

		bRet = H264_DVR_SetDevConfig(m_loginID,E_SDK_CONFIG_MODIFY_USER, 0, (char *)pUserinfo, sizeof(CONF_MODIFYUSER));
		
		if ( bRet > 0 )
		{
			//找到原先的用户
			for ( int i = 0; i < m_userinfo->userNum; i ++ )
			{
				if ( !strcmp(pUserinfo->UserName, m_userinfo->userList[i].name) )
				{
					m_userinfo->userList[i].reserved = pUserinfo->User.reserved;
					m_userinfo->userList[i].shareable = pUserinfo->User.shareable;
					strcpy(m_userinfo->userList[i].Groupname, pUserinfo->User.Groupname);
					strcpy(m_userinfo->userList[i].memo, pUserinfo->User.memo);
					strcpy(m_userinfo->userList[i].name, pUserinfo->User.name);
					
					//复制权限
					m_userinfo->userList[i].rigthNum = 0;
					
					for ( int j = 0; j < pUserinfo->User.rigthNum; j ++ )
					{
						strcpy(m_userinfo->userList[i].rights[j], pUserinfo->User.rights[j]);
					}
					m_userinfo->userList[i].rigthNum = pUserinfo->User.rigthNum;
					break;
				}
			}
		}

	
	return bRet;
}
void CUserModifyDlg::OnBnClickedOk()
{
	UpdateData();

	//验证输入的数据是否合法
	m_strName.TrimLeft();
	m_strName.TrimRight();

	if ( "" == m_strName )
	{
		MessageBox(_CS("AccountMSG.EmptyName"), _CS("OneClick.Prompt"));
		return;
	}
	if(m_strName[0]=='&')
	{
		
		MessageBox(_CS("AccountMSG.ErrorName"), _CS("OneClick.Prompt"));
		
		return;
	}
	if(m_strName.Find('.')!=-1||m_strName.Find('[')!=-1||m_strName.Find(']') != -1 || m_strName.Find('%') != -1)
	{
		
		MessageBox(_CS("AccountMSG.ErrorName"), _CS("OneClick.Prompt"));
		return;
	}

	if ( m_strName != m_strUserName )
	{
		//验证用户名是否已经存在
	
			if ( FindUserName(m_strName.GetBuffer(0)) )
			{
				MessageBox(_CS("AccountMSG.AddUserExist"), _CS("OneClick.Prompt"));
				return;
			}
		
	}

	CONF_MODIFYUSER userinfo;
	strcpy(userinfo.UserName, m_strUserName.GetBuffer(0) );

	//获取选择的权限列表
	int nIndex = 0;
	int nSize = m_listAuthrioty.GetItemCount();
	for ( int i = 0; i < nSize; i ++ )
	{
		if ( m_listAuthrioty.GetCheck(i) )
		{
			CString strName("");
			strName = (char *)m_listAuthrioty.GetItemData(i);
			strcpy ( userinfo.User.rights[nIndex ++], strName.GetBuffer(0) );
		} 
	}
	userinfo.User.rigthNum = nIndex;

	if ( nIndex <= 0 )
	{
		MessageBox(_CS("AccountMSG.EmptyAuthority"), _CS("OneClick.Prompt"));

		return;
	}

	userinfo.User.reserved = m_bresverved;
	userinfo.User.shareable = m_checkReuseable.GetCheck();
	strcpy ( userinfo.User.name, m_strName.GetBuffer(0) );
	strcpy ( userinfo.User.memo, m_strDescribe.GetBuffer(0) );
	strcpy ( userinfo.User.Groupname, m_strGroup.GetBuffer(0) );
	


		//保存用户	
		int nRet = ModifyuserInfo( &userinfo );
		if ( nRet <= 0 )
		{
			CString strMsg(_CS("User.ModUserFailed"));
			//CString strError = pDate->GetSdkErrorInfo( nRet );
			//strMsg += strError;
			MessageBox(strMsg, _CS("OneClick.Prompt"));

			return;
		}
	

	MessageBox(_CS("AccountMSG.ModUserSuccess"), _CS("OneClick.Prompt"));

	OnOK();
	//CDialog::OnOK();
}

void CUserModifyDlg::OnBnClickedBtnDelete()
{
	UpdateData();

	int nIndex = m_cmbUserName.GetCurSel();

	if ( nIndex == -1 )
	{
		return;
	}
	//获取用户信息

		USER_INFO *pUserInfo = GetUserInfo(m_strUserName.GetBuffer(0));
		if ( pUserInfo )
		{
			if ( pUserInfo->reserved )
			{
				MessageBox(_CS("AccountMSG.TryDeleteResvUser"), _CS("OneClick.Prompt"));

				return;
			}

			if ( IDYES == MessageBox(_CS("AccountMSG.SureToDelete"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) )
			{
				//删除用户	
				int nRet = DeleteuserInfo( pUserInfo );
				if ( nRet <= 0 )
				{
					CString strError;
					CString strMsg;
					strMsg.Format("%s ", _CS("AccountMSG.Failed") );
					if ( nRet == H264_DVR_USER_HAS_USED ) 
					{
						strError.Format("%s", _CS("Error.InUsing"));
					}
					else if ( nRet == H264_DVR_NOPOWER )
					{
						strError.Format("%s", _CS("Error.NoPower"));
					}
					else
					{
						strError.Format("%s", _CS("Error.UnkownErr"));
					}
					
					strMsg += strError;
					MessageBox( strMsg, _CS("OneClick.Prompt") );
					return;
				}

				m_cmbUserName.DeleteString(nIndex);
				MessageBox(_CS("AccountMSG.DeleteUserSuccess"), _CS("OneClick.Prompt"));
			}	
		}


	OnOK();
}
int CUserModifyDlg::DeleteuserInfo(USER_INFO *pUserinfo)
{
	int bRet = false;
	

		bRet = H264_DVR_SetDevConfig(m_loginID,E_SDK_CONFIG_DELETE_USER, 0, (char *)pUserinfo, sizeof(USER_INFO));
		
		if ( bRet > 0 )
		{
			//找到原先的用户
			for ( int i = 0 ; i < m_userinfo->userNum; i ++ )
			{
				if ( !strcmp( pUserinfo->name, m_userinfo->userList[i].name ) )
				{
					//将后面的用户信息全部前移
					if ( i == m_userinfo->userNum - 1 )
					{
						m_userinfo->userNum --;
					}
					else
					{
						memcpy( &m_userinfo->userList[i], &m_userinfo->userList[i + 1], sizeof(USER_INFO) * (m_userinfo->userNum - i - 1) );
						m_userinfo->userNum --;
					}
					break;
				}
			}
		}

	
	return bRet;
}

USER_GROUP_INFO* CUserModifyDlg::GetGroupInfo(char * strName)
{
	for ( int i = 0 ; i < m_userinfo->groupNum; i ++ )
	{
		if ( !strcmp(strName , m_userinfo->groupList[i].name) )
		{
			return &m_userinfo->groupList[i];
		}
	}
	
	return NULL;
}


USER_INFO* CUserModifyDlg::GetUserInfo(char * strName)
{
	for ( int i = 0; i < m_userinfo->userNum; i ++ )
	{
		if ( !strcmp(strName, m_userinfo->userList[i].name) )
		{
			return &m_userinfo->userList[i];
		}
	}
	
	return NULL;
}
