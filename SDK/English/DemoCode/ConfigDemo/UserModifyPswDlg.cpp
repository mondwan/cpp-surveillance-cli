// UserModifyPswDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UserModifyPswDlg.h"
#include "Security.h"




// CUserModifyPswDlg 对话框

IMPLEMENT_DYNAMIC(CUserModifyPswDlg, CDialog)

CUserModifyPswDlg::CUserModifyPswDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserModifyPswDlg::IDD, pParent)
	, m_strUser(_T(""))
	, m_strConfirm(_T(""))
	, m_strNewpsw(_T(""))
	, m_strOldpsw(_T(""))
{
   	
}

CUserModifyPswDlg::~CUserModifyPswDlg()
{
}

void CUserModifyPswDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USER, m_cmbUser);
	DDX_CBString(pDX, IDC_COMBO_USER, m_strUser);
	DDX_Control(pDX, IDC_EDIT_CONFIRM, m_editCofirm);
	DDX_Text(pDX, IDC_EDIT_CONFIRM, m_strConfirm);
	DDX_Control(pDX, IDC_EDIT_NEWPSW, m_editNewpsw);
	DDX_Text(pDX, IDC_EDIT_NEWPSW, m_strNewpsw);
	DDX_Control(pDX, IDC_EDIT_OLDPSW, m_editOldpsw);
	DDX_Text(pDX, IDC_EDIT_OLDPSW, m_strOldpsw);
}


BEGIN_MESSAGE_MAP(CUserModifyPswDlg, CDialog)
	ON_BN_CLICKED(IDOK, CUserModifyPswDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserModifyPswDlg 消息处理程序

BOOL CUserModifyPswDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);

	m_editCofirm.SetLimitText(6);
	m_editNewpsw.SetLimitText(6);
	m_editOldpsw.SetLimitText(6);

	//获取用户信息

		USER_MANAGE_INFO *pUser = m_userinfo;
		for ( int i = 0; i < pUser->userNum; i ++ )
		{
			if ( strcmp(pUser->userList[i].name, "") != 0)
			{
				m_cmbUser.AddString( pUser->userList[i].name );
			}
		}

	m_cmbUser.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUserModifyPswDlg::OnBnClickedOk()
{
	UpdateData();

	//获取当前用户信息

		USER_INFO*pUserinfo = GetUserInfo(m_strUser.GetBuffer(0));
		if ( pUserinfo )
		{
			signed char szMD5[100] = {0};
			MD5Encrypt( szMD5, (unsigned char*)m_strOldpsw.GetBuffer(0));
			//验证密码
			if ( strcmp((char *)szMD5, pUserinfo->passWord) )
			{
				MessageBox(_CS("Error.PwdErr"), _CS("OneClick.Prompt"));
				return;
			}

			if ( m_strNewpsw != m_strConfirm )
			{
				MessageBox(_CS("Error.PasswordMismatch"), _CS("OneClick.Prompt"));
				return;
			}
		}

		signed char szMD5[100] = {0};
		MD5Encrypt( szMD5, (unsigned char*)m_strNewpsw.GetBuffer(0));

		_CONF_MODIFY_PSW psw;
		strcpy ( psw.sUserName, m_strUser.GetBuffer(0) );
		strcpy ( psw.Password, pUserinfo->passWord );
		strcpy ( psw.NewPassword, (char *)szMD5 );

	
			//保存用户	
			int bRet = Modifypsw(&psw);
			if ( bRet <= 0 )
			{
				CString strMsg(_CS("Error.SetConfigFail"));
				CString strError = GetSdkErrorInfo( bRet );
				strMsg += strError;
				MessageBox(strMsg, _CS("OneClick.Prompt"));
				return;
			}
			else
			{
				MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt"));
			}
		


	OnOK();
}
USER_INFO* CUserModifyPswDlg::GetUserInfo(char * strName)
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
//根据错误码解析成具体的错误信息
CString CUserModifyPswDlg::GetSdkErrorInfo(int nError)
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
int CUserModifyPswDlg::Modifypsw(_CONF_MODIFY_PSW *pPsw)
{
	int bRet = false;
	

		bRet = H264_DVR_SetDevConfig(m_loginID,E_SDK_CONFIG_MODIFY_PSW, 0, (char *)pPsw, sizeof(_CONF_MODIFY_PSW));
		if ( bRet > 0 )
		{
			//找到原先的用户
			for ( int i = 0; i < m_userinfo->userNum; i ++ )
			{
				if ( !strcmp(pPsw->sUserName, m_userinfo->userList[i].name) )
				{
					strcpy(m_userinfo->userList[i].passWord, pPsw->NewPassword);
					break;
				}
			}
		}

	
	return bRet;
}