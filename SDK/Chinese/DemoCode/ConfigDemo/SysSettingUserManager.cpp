// SysSettingUserManager.cpp : 实现文件
//

#include "stdafx.h"
#include "SysSettingUserManager.h"
#include "UserAddDlg.h"
#include "UserModifyDlg.h"
#include "UserAddGroupDlg.h"
#include "UserModifyPswDlg.h"
#include "UserDeleteGroupDlg.h"

IMPLEMENT_DYNAMIC(CSysSettingUserManager, CDialog)
CSysSettingUserManager::CSysSettingUserManager(CWnd* pParent /*=NULL*/)
{
	m_LoginID=0;
	
	ClearData();
}

CSysSettingUserManager::~CSysSettingUserManager()
{
}

void CSysSettingUserManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
}


BEGIN_MESSAGE_MAP(CSysSettingUserManager, CDialog)
	ON_BN_CLICKED(IDC_ADD_USER, CSysSettingUserManager::OnBnClickedAddUser)
	ON_BN_CLICKED(IDC_MD_USER, CSysSettingUserManager::OnBnClickedMdUser)
	ON_BN_CLICKED(IDC_ADD_GROUP, CSysSettingUserManager::OnBnClickedAddGroup)
	ON_BN_CLICKED(IDC_MD_GROUP, CSysSettingUserManager::OnBnClickedMdGroup)
	ON_BN_CLICKED(IDC_MD_PSW, CSysSettingUserManager::OnBnClickedMdPsw)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_REFUSH, CSysSettingUserManager::OnBnClickedBtnRefush)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_USER, CSysSettingUserManager::OnNMRclickListUser)

	ON_BN_CLICKED(IDC_BTN_DEL_USER, CSysSettingUserManager::OnBnClickedDeleteUser)
	ON_BN_CLICKED(IDC_DELETE_GROUP, CSysSettingUserManager::OnBnClickedDeleteGroup)
END_MESSAGE_MAP()


BOOL CSysSettingUserManager::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	m_listUser.SetExtendedStyle(m_listUser.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	m_listUser.InsertColumn(0, _CS("UserManager.No"), LVCFMT_LEFT, 50);
	m_listUser.InsertColumn(1, _CS("UserManager.User"),LVCFMT_LEFT, 150);
	m_listUser.InsertColumn(2, _CS("UserManager.Group"),LVCFMT_LEFT, 150);

	return TRUE;  // return TRUE unless you set the focus to a control
	
}

void CSysSettingUserManager::OnBnClickedAddUser()
{
	if(!m_LoginID)
	{
		return;
	}

	CUserAddDlg addDlg;	
	addDlg.m_loginID=m_LoginID;
	addDlg.m_userinfo=&m_userinfo;
	addDlg.DoModal();//1.保存配置到设备，2.保存数据到内存
	{
		//保存成功，更新列表数据
		ClearData();	
		ShowUserInfo();
	}
}

void CSysSettingUserManager::OnBnClickedMdUser()
{
	if(!m_LoginID)
	{
		return;
	}

	CUserModifyDlg modDlg;
	modDlg.m_userinfo=&m_userinfo;
	modDlg.m_loginID=m_LoginID;	
	if(IDOK==modDlg.DoModal())//1.保存配置到设备，2.保存数据到内存
	{
		//保存成功，更新列表数据
		ClearData();
		ShowUserInfo();
	}
}

void CSysSettingUserManager::OnBnClickedAddGroup()
{
	if(!m_LoginID)
	{
		return;
	}

	CUserAddGroupDlg dlg;
	dlg.m_loginID=m_LoginID;
	dlg.m_userinfo=&m_userinfo;
	dlg.DoModal();//1.保存配置到设备，2.保存数据到内存
	{

		ClearData();
		ShowUserInfo();
	}
}

void CSysSettingUserManager::OnBnClickedMdGroup()
{
	if(!m_LoginID)
	{
		return;
	}

	CUserAddGroupDlg dlg;
	dlg.m_loginID=m_LoginID;
	dlg.m_userinfo=&m_userinfo;
	dlg.m_ntype = 1;
	dlg.DoModal();//1.保存配置到设备，2.保存数据到内存
	{
		ClearData();
		ShowUserInfo();
	}
}

void CSysSettingUserManager::OnBnClickedMdPsw()
{
	if(!m_LoginID)
	{
		return;
	}

	CUserModifyPswDlg dlg;
	dlg.m_loginID=m_LoginID;
	dlg.m_userinfo=&m_userinfo;
	if ( IDOK == dlg.DoModal() )//1.保存配置到设备，2.保存数据到内存
	{
			
	}
}


bool CSysSettingUserManager::WinDataToStruct()
{
	return true;
}

bool CSysSettingUserManager::StructToWinData()
{
	//重新刷新数据，首先删除原先存在的内容
	ClearData();

	//获取成功刷新数据，失败则不用处理
	ShowUserInfo();

	return true;
}	

void CSysSettingUserManager::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	/*
	//获取各自配置
	if ( bShow&&m_LoginID )			
	{
		DWORD nReturn=0;
		int nRet = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_USER,-1, (char *)&m_userinfo, sizeof(m_userinfo),&nReturn);
		if ( 1 == nRet || 2 == nRet )
		{
			StructToWinData();
			UpdateData(FALSE);


			if ( IsIconic() )
			{
				ShowWindow(SW_NORMAL);
			}
		}
	}	
	*/
}


void CSysSettingUserManager::ClearData()
{
	if ( m_listUser.GetSafeHwnd() )
		m_listUser.DeleteAllItems();
}

//显示用户列表
bool CSysSettingUserManager::ShowUserInfo()
{
	bool bRet =false;
	
	int nIndex = 0;

	for ( int i = 0; i < m_userinfo.userNum; i ++ )
	{
		char szIndex[5];
		sprintf(szIndex, "%d", i + 1);
		m_listUser.InsertItem(i, szIndex );
		m_listUser.SetItemText(i, 1, m_userinfo.userList[i].name );
		m_listUser.SetItemText(i, 2, m_userinfo.userList[i].Groupname );
	}

	return bRet;
}

void CSysSettingUserManager::OnBnClickedBtnRefush()
{
	DWORD dwReturn;
	int nRet = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_USER,-1, (char *)&m_userinfo, sizeof(m_userinfo), &dwReturn);

	if ( nRet > 0 )
		StructToWinData();
}

void CSysSettingUserManager::OnNMRclickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
//	GetParent()->SendMessage(ON_WM_HIDE_SUBITEM, (DWORD)this, (DWORD)this);

	*pResult = 0;

//	ShowWindow(SW_HIDE);
}

int CSysSettingUserManager::DeleteuserInfo(USER_INFO *pUserinfo)
{
	int bRet = false;		

		bRet = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_DELETE_USER, 0, (char *)pUserinfo, sizeof(USER_INFO));
		
		if ( bRet > 0 )
		{
			//找到原先的用户
			for ( int i = 0 ; i < m_userinfo.userNum; i ++ )
			{
				if ( !strcmp( pUserinfo->name, m_userinfo.userList[i].name ) )
				{
					//将后面的用户信息全部前移
					if ( i == m_userinfo.userNum - 1 )
					{
						m_userinfo.userNum --;
					}
					else
					{
						memcpy( &m_userinfo.userList[i], &m_userinfo.userList[i + 1], sizeof(USER_INFO) * (m_userinfo.userNum - i - 1) );
						m_userinfo.userNum --;
					}
					break;
				}
			}
		}

	
	return bRet;
}
USER_INFO* CSysSettingUserManager::GetUserInfo(char * strName)
{
	for ( int i = 0; i < m_userinfo.userNum; i ++ )
	{
		if ( !strcmp(strName, m_userinfo.userList[i].name) )
		{
			return &m_userinfo.userList[i];
		}
	}
	
	return NULL;
}
void CSysSettingUserManager::OnBnClickedDeleteUser()
{
	int nIndex = m_listUser.GetSelectionMark();

	if ( nIndex == -1 )
	{
		MessageBox(_CS(_T("User.SelectOneUser")), _CS(_T("OneClick.Prompt")));
		return;
	}
	if ( nIndex >= 0 )
	{
		CString strName;
		strName = m_listUser.GetItemText( nIndex, 1 );

		//获取用户信息
		
			USER_INFO *pUserInfo = GetUserInfo(strName.GetBuffer(0));
			if ( pUserInfo )
			{
				if ( pUserInfo->reserved || 0 == strcmp(pUserInfo->name, "default"))
				{
					MessageBox(_CS("AccountMSG.TryDeleteResvUser"), _CS("OneClick.Prompt"));
					m_listUser.SetSelectionMark( -1 ); //取消选择List
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
						else if ( nRet == H264_DVR_ACCOUNT_OBJECT_IN_USE )
						{
							strError.Format("%s", _CS("Error.InUsing"));
						}
						else
						{
							strError.Format("%s", _CS("Error.UnkownErr"));
						}

						m_listUser.SetSelectionMark( -1 ); //取消选择List

						strMsg += strError;
						MessageBox( strMsg, _CS("OneClick.Prompt") );
						
						return;
					}
					
					m_listUser.DeleteItem(nIndex);
					MessageBox(_CS("AccountMSG.DeleteUserSuccess"), _CS("OneClick.Prompt"));
				}	
			
		}	
	}
}

void CSysSettingUserManager::OnBnClickedDeleteGroup()
{
	if(!m_LoginID)
	{
		return;
	}
	CUserDeleteGroupDlg deleGroup;
	deleGroup.m_loginID=m_LoginID;		
	deleGroup.m_userinfo=&m_userinfo;

	deleGroup.DoModal();//1.保存配置到设备，
	{
		//更新最新数据，	
		USER_MANAGE_INFO *pUserInfo =&m_userinfo;
		memcpy( &m_userinfo, pUserInfo, sizeof(USER_MANAGE_INFO) );		
		ClearData();
		ShowUserInfo();
	}
}


//modify by zhouhao
void CSysSettingUserManager::InitDlgInfo()
{
	if (m_LoginID)			
	{
		DWORD nReturn=0;
		int nRet = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_USER,-1, (char *)&m_userinfo, sizeof(m_userinfo),&nReturn);
		if ( 1 == nRet || 2 == nRet )
		{
			StructToWinData();
			UpdateData(FALSE);
		}
	}	
}

void CSysSettingUserManager::ClearAll()
{
	m_listUser.DeleteAllItems();
}
