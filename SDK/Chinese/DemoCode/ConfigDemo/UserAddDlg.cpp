// UserAddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserAddDlg.h"


// CUserAddDlg 对话框



IMPLEMENT_DYNAMIC(CUserAddDlg, CDialog)

CUserAddDlg::CUserAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAddDlg::IDD, pParent)
	, m_strConfirm(_T(""))
	, m_strDescribe(_T(""))
	, m_strPsw(_T(""))
	, m_strName(_T(""))
	, m_strGroupName(_T(""))
{
   	
}

CUserAddDlg::~CUserAddDlg()
{
}

void CUserAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_REUSEABLE, m_checkReuseable);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_cmbGroup);
	DDX_Control(pDX, IDC_EDIT_CONFIRM, m_editConfirm);
	DDX_Text(pDX, IDC_EDIT_CONFIRM, m_strConfirm);
	DDX_Control(pDX, IDC_EDIT_DESCRIBE, m_editDescribe);
	DDX_Text(pDX, IDC_EDIT_DESCRIBE, m_strDescribe);
	DDX_Control(pDX, IDC_EDIT_PSW, m_editPsw);
	DDX_Text(pDX, IDC_EDIT_PSW, m_strPsw);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strName);
	DDX_Control(pDX, IDC_LIST1, m_listAuthority);
	DDX_CBString(pDX, IDC_COMBO_GROUP, m_strGroupName);
}


BEGIN_MESSAGE_MAP(CUserAddDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, CUserAddDlg::OnCbnSelchangeComboGroup)
	ON_BN_CLICKED(IDOK, CUserAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserAddDlg 消息处理程序
BOOL CUserAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	_CWndCS(this);
	
	//显示字符个数，实际上现在和设备的交互是以字符串方式，所以也没太大必要限制
	m_editName.SetLimitText(8);
	m_editPsw.SetLimitText(6);
	m_editConfirm.SetLimitText(6);
	m_editDescribe.SetLimitText(31);
	m_listAuthority.SetExtendedStyle(m_listAuthority.GetExtendedStyle() | LVS_EX_CHECKBOXES );
	m_listAuthority.InsertColumn(0, _CS("UserManager.No"), LVCFMT_LEFT, 50);
	m_listAuthority.InsertColumn(1, _CS("UserManager.Authority"), LVCFMT_LEFT, 200);
	
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
	m_cmbGroup.GetWindowText(m_strGroupName);
	UpdateAuthorityList(m_strGroupName);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

USER_GROUP_INFO* CUserAddDlg::GetGroupInfo(char * strName)
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
void CUserAddDlg::UpdateAuthorityList(CString strGroup)
{
	
		char szIndex[5];

		int nIndex = 0;
		USER_GROUP_INFO *pGroup = GetGroupInfo(strGroup.GetBuffer(0));
		if ( pGroup )
		{
			for ( int i = 0; i < pGroup->rigthNum; i ++ )
			{
				CString strRigths("Authority.");

				strRigths += pGroup->rights[i];
				sprintf(szIndex, "%d", i +  1);
				m_listAuthority.InsertItem(i,szIndex );
				m_listAuthority.SetItemText(i, 1, _CS(strRigths) );
				m_listAuthority.SetItemData(i, long(pGroup->rights[i]) );
				m_listAuthority.SetCheck(i, true);
			}

// 			sprintf(szIndex, "%d", pGroup->rigthNum );
// 			LVCOLUMN count;
// 			count.cx = 50;
// 			count.pszText = szIndex;
// 			m_listAuthority.SetColumn(0, &count);
		}
				
}

void CUserAddDlg::OnCbnSelchangeComboGroup()
{
	m_listAuthority.DeleteAllItems();

	UpdateData();
	CString strGroup;
	m_cmbGroup.GetWindowText(strGroup);

	UpdateAuthorityList(strGroup);
}

bool CUserAddDlg::FindUserName(char *szUserName)
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
void CUserAddDlg::OnBnClickedOk()
{
	UpdateData();

	m_strName.TrimLeft();
	m_strName.TrimRight();
	m_strGroupName.TrimLeft();
	m_strGroupName.TrimRight();
	
	//验证输入的数据是否合法
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
	if(m_strName.Find('.')!=-1||m_strName.Find('[')!=-1||m_strName.Find(']')!=-1 || m_strName.Find('%') != -1)
	{
		
		MessageBox(_CS("AccountMSG.ErrorName"), _CS("OneClick.Prompt"));
		return;
	}

	//验证密码是否匹配
	if ( m_strPsw != m_strConfirm )
	{
		MessageBox(_CS("Error.PwdErr"), _CS("OneClick.Prompt"));
		return;
	}
	
	//验证用户名是否已经存在

	if ( FindUserName(m_strName.GetBuffer(0)) )
	{
		MessageBox(_CS("AccountMSG.AddUserExist"), _CS("OneClick.Prompt"));
		return;
	}

	USER_INFO userInfo;

	//获取选择的权限列表
	int nIndex = 0;
	int nSize = m_listAuthority.GetItemCount();
	for ( int i = 0; i < nSize; i ++ )
	{
		if ( m_listAuthority.GetCheck(i) )
		{
			CString strName = (char *)m_listAuthority.GetItemData(i);
			strcpy( userInfo.rights[nIndex ++], strName.GetBuffer(0) );
		}
	}
	userInfo.rigthNum = nIndex;
	if ( nIndex <= 0 )
	{
		MessageBox(_CS("AccountMSG.EmptyAuthority"), _CS("OneClick.Prompt"));

		return;
	}

	userInfo.reserved = false;
	userInfo.shareable = m_checkReuseable.GetCheck();
	strcpy ( userInfo.Groupname, m_strGroupName.GetBuffer(0) );
	strcpy ( userInfo.memo, m_strDescribe.GetBuffer(0) );
	strcpy ( userInfo.name, m_strName.GetBuffer(0) );
	strcpy ( userInfo.passWord, m_strPsw.GetBuffer(0) );
	
		//保存用户	
		int bRet = SaveuserInfo(&userInfo);
		if ( bRet <= 0 )
		{
			CString strMsg(_CS("User.AddUserFailed"));
			CString strError = GetSdkErrorInfo( bRet );
			strMsg += strError;
			MessageBox(strMsg, _CS("OneClick.Prompt"));

			return;
		}
	

	MessageBox(_CS("AccountMSG.AddUserSuccess"), _CS("OneClick.Prompt"));
	OnOK();
}
//根据错误码解析成具体的错误信息
CString CUserAddDlg::GetSdkErrorInfo(int nError)
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
	case H264_DVR_USER_HAS_USED:			// 该用户以登陆
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
int CUserAddDlg::SaveuserInfo(USER_INFO *pUserinfo)
{
	int bRet = 0;
		

		bRet = H264_DVR_SetDevConfig(m_loginID,E_SDK_CONFIG_ADD_USER, 0, (char *)pUserinfo, sizeof(USER_INFO));

	if ( bRet > 0 && m_userinfo)
	{
		//重新更新内存数据
		memcpy( &m_userinfo->userList[m_userinfo->userNum], pUserinfo, sizeof(USER_INFO) );
		m_userinfo->userNum ++;		
	}
	return bRet;
}
