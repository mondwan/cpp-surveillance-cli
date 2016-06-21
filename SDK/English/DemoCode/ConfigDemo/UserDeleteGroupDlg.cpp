// UserDeleteGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "UserDeleteGroupDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDeleteGroupDlg dialog


CUserDeleteGroupDlg::CUserDeleteGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDeleteGroupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDeleteGroupDlg)
	m_strGroup = _T("");
	m_strDescribe = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT

	OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
	     	
}


void CUserDeleteGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDeleteGroupDlg)
	DDX_Control(pDX, IDC_EDIT_GROUPNAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_DESCRIBE, m_editDescribe);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_cmbGroup);
	DDX_CBString(pDX, IDC_COMBO_GROUP, m_strGroup);
	DDX_Text(pDX, IDC_EDIT_DESCRIBE, m_strDescribe);
	DDX_Text(pDX, IDC_EDIT_GROUPNAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDeleteGroupDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDeleteGroupDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, OnSelchangeComboGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDeleteGroupDlg message handlers

void CUserDeleteGroupDlg::OnSelchangeComboGroup() 
{
	UpdateData();
	
	m_editName.SetWindowText(m_strGroup);


	//获取当前组信息

		USER_GROUP_INFO *pGroupinfo = GetGroupInfo(m_strGroup.GetBuffer(0));
		if ( pGroupinfo )
		{
			m_editDescribe.SetWindowText(pGroupinfo->memo);
		}
	

}

void CUserDeleteGroupDlg::OnOK() 
{
	UpdateData();
	
	int nIndex = m_cmbGroup.GetCurSel();
	
	//获取用户信息

		if ( HasUser(m_strGroup) )
		{
			MessageBox(_CS("AccountMSG.DeleteInuseGroup"), _CS("OneClick.Prompt"));
			return;
		}
		
		USER_GROUP_INFO *pGroupInfo = GetGroupInfo(m_strGroup.GetBuffer(0));
		if ( pGroupInfo )
		{
			if ( IDYES == MessageBox(_CS("AccountMSG.SureToDelete"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) )
			{
				//删除用户	
				int bRet = DeleteGroupInfo( pGroupInfo );
				if ( bRet <= 0 )
				{
					CString strMsg(_CS("AccountMSG.Failed"));
					CString strError = GetSdkErrorInfo( bRet );
					strMsg += strError;
					MessageBox(strMsg, _CS("OneClick.Prompt"));

					return;
				}
				
				m_cmbGroup.DeleteString(nIndex);
				MessageBox(_CS("AccountMSG.DeleteGroupSuccess"), _CS("OneClick.Prompt"));


				m_cmbGroup.SetCurSel(0);

				OnSelchangeComboGroup();
			}	
		}
	
	
	//CDialog::OnOK();
}

BOOL CUserDeleteGroupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_CWndCS(this);
	
	//获取组信息

		USER_MANAGE_INFO *pUser = m_userinfo;
		for ( int i = 0; i < pUser->groupNum; i ++ )
		{
			if ( strcmp(pUser->groupList[i].name, "") != 0 )
			{
				m_cmbGroup.AddString(pUser->groupList[i].name);
			}		
		}

	m_cmbGroup.SetCurSel(0);
	
	m_cmbGroup.GetWindowText(m_strGroup);
	m_editName.SetWindowText(m_strGroup);

	//获取当前组信息
	
	USER_GROUP_INFO *pGroupinfo = GetGroupInfo(m_strGroup.GetBuffer(0));
	if ( pGroupinfo )
	{
		m_editDescribe.SetWindowText(pGroupinfo->memo);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
USER_GROUP_INFO* CUserDeleteGroupDlg::GetGroupInfo(char * strName)
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
bool CUserDeleteGroupDlg::HasUser(CString strGroup)
{
	for ( int i = 0 ; i < m_userinfo->userNum; i ++ )
	{
		if ( !strcmp(m_userinfo->userList[i].Groupname, strGroup.GetBuffer(0)) )
		{
			return true;
		}
	}
	
	return false;
}
int CUserDeleteGroupDlg::DeleteGroupInfo(USER_GROUP_INFO *pGroupinfo)
{
	int bRet = false;
	
	
		bRet = H264_DVR_SetDevConfig(m_loginID,E_SDK_COFIG_DELETE_GROUP, 0, (char *)pGroupinfo,  sizeof(USER_GROUP_INFO));
		
		if ( bRet > 0 )
		{
			//找到原先的用户
			for ( int i = 0 ; i < m_userinfo->groupNum; i ++ )
			{
				if ( !strcmp(pGroupinfo->name, m_userinfo->groupList[i].name) )
				{
					//将后面的用户信息全部前移
					memcpy( &m_userinfo->groupList[i], &m_userinfo->groupList[i + 1], sizeof(USER_GROUP_INFO) * (m_userinfo->groupNum - i - 1) );
					m_userinfo->groupNum --;
					break;
				}
			}
		}
	
	
	return bRet;
}
//根据错误码解析成具体的错误信息
CString CUserDeleteGroupDlg::GetSdkErrorInfo(int nError)
{
	CString strMsg(_CS("Error.UnkownErr"));
	switch(nError)
	{
	case H264_DVR_SDK_NOTVALID:			//非法请求
		strMsg = _CS("Error.ReqErr");
		break;
	case H264_DVR_NO_INIT:				//SDK未经初始化
		strMsg = _CS("Error.NoInit");
		break;
	case H264_DVR_ILLEGAL_PARAM:			//用户参数不合法
		strMsg = _CS("Error.ParamInvalid");
	    break;
	case H264_DVR_INVALID_HANDLE:		//句柄无效
		strMsg = _CS("Error.HandleInvalid");
	    break;
	case H264_DVR_SDK_UNINIT_ERROR:		//SDK清理出错
		strMsg = _CS("Error.ClearSDKError");
		break;
	case H264_DVR_SDK_TIMEOUT:			//等待超时
		strMsg = _CS("Error.Timeout");
		break;
	case H264_DVR_SDK_MEMORY_ERROR:		//内存错误，创建内存失败
		strMsg = _CS("Error.MallocErr");
	    break;
	case H264_DVR_SDK_NET_ERROR:			//网络错误
		strMsg = _CS("Error.NetErr");
	    break;
	case H264_DVR_DEV_VER_NOMATCH:		//收到数据不正确，可能版本不匹配
		strMsg = _CS("Error.VerUnmatch");
	    break;
	case H264_DVR_SDK_NOTSUPPORT:		//版本不支持
		strMsg = _CS("Error.Unsupport");
	    break;
	case H264_DVR_OPEN_CHANNEL_ERROR:	//打开通道失败
		strMsg = _CS("Error.OpenChnErr");
	    break;
	case H264_DVR_CLOSE_CHANNEL_ERROR:	//关闭通道失败
		strMsg = _CS("Error.CloseChnErr");
	    break;
	case H264_DVR_SUB_CONNECT_ERROR:		//建立媒体子连接失败
		strMsg = _CS("Error.SubConErr");
	    break;
	case H264_DVR_SUB_CONNECT_SEND_ERROR://媒体子连接通讯失败
		strMsg = _CS("Error.SubConSendErr");
	    break;
	case H264_DVR_NOPOWER:				//无权限
		strMsg = _CS("Error.NoPower");
	    break;
	case H264_DVR_PASSWORD_NOT_VALID:	// 账号密码不对
		strMsg = _CS("Error.PwdErr");
	    break;
	case H264_DVR_LOGIN_USER_NOEXIST:	//用户不存在
		strMsg = _CS("Error.UserNotExisted");
	    break;
	case H264_DVR_USER_LOCKED:			// 该用户被锁定
		strMsg = _CS("Error.UserLock");
	    break;
	case H264_DVR_USER_IN_BLACKLIST:		// 该用户不允许访问(在黑名单中)
		strMsg = _CS("Error.InBlackList");
	    break;
	case H264_DVR_USER_HAS_USED:			// 该用户已登陆
		strMsg = _CS("Error.HasLogined");
	    break;
	case H264_DVR_USER_NOT_LOGIN	:		// 该用户没有登陆
		strMsg = _CS("Error.NoLogin");
	    break;
	case H264_DVR_CONNECT_DEVICE_ERROR:	//可能设备不存在
		strMsg = _CS("Error.NotFound");
	    break;
	case H264_DVR_ACCOUNT_INPUT_NOT_VALID:	//用户管理输入不合法
		strMsg = _CS("Error.InputError");
	    break;
	case H264_DVR_ACCOUNT_OVERLAP:			//索引重复
		strMsg = _CS("AccountMSG.AccountUsed");
	    break;
	case H264_DVR_ACCOUNT_OBJECT_NONE:		//不存在对象, 用于查询时
		strMsg = _CS("AccountMSG.EmptyName");
	    break;
	case H264_DVR_ACCOUNT_OBJECT_NOT_VALID:	//不存在对象
		strMsg = _CS("Error.NotFound");
	    break;
	case H264_DVR_ACCOUNT_OBJECT_IN_USE:		//对象正在使用
		strMsg = _CS("Error.InUsing");
	    break;
	case H264_DVR_ACCOUNT_SUBSET_OVERLAP:	//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
		strMsg = _CS("AccountMSG.TooLargeAuthority");
	    break;
	case H264_DVR_ACCOUNT_PWD_NOT_VALID:		//密码不正确
		strMsg = _CS("Error.PwdErr");
	    break;
	case H264_DVR_ACCOUNT_PWD_NOT_MATCH:		//密码不匹配
		strMsg = _CS("AccountMSG.PasswordMismatch");
	    break;
	case H264_DVR_ACCOUNT_RESERVED:			//保留帐号
		strMsg = _CS("AccountMSG.TryModifyResvUser");
	    break;		
	case H264_DVR_OPT_FILE_ERROR:			// 写文件出错
		strMsg = _CS("Error.SetConfigFail");
	    break;	
	case H264_DVR_OPT_CAPS_ERROR:			// 配置特性不支持
		strMsg = _CS("Error.ConfigCharsetUnsupport");
	    break;
	case H264_DVR_OPT_VALIDATE_ERROR:		// 配置校验失败
		strMsg = _CS("Error.ConfigVerifyFail");
	    break;
	case H264_DVR_OPT_CONFIG_NOT_EXIST:		// 请求或者设置的配置不存在
		strMsg = _CS("Error.ConfigNotFound");
	    break;	
	case H264_DVR_CTRL_PAUSE_ERROR:			//暂停失败
		strMsg = _CS("Error.PauseFail");
	    break;
	default:
		{
			//如果没有，则返回设备端错误码
			CString strError;
			strError.Format(_T("(%d)"),  nError * ( -1 ) ); //根据原来的返回值的相反值取原来的返回值
			strMsg += strError;
		}
	    break;
	}

	return strMsg;
}
