// LogInfoDlg.cpp : implementation file
//


#include "stdafx.h"
#include "clientdemo5.h"
#include "LogInfoDlg.h"
#include "ClientDemo5Dlg.h"
#include <string>


#define snprintf _snprintf
#define MAX_BUF_LEN (64 * 1024)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogInfoDlg dialog


CLogInfoDlg::CLogInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogInfoDlg)
	m_bData = 0;
	m_bTime = 0;
	m_eData = 0;
	m_eTime = 0;
	//}}AFX_DATA_INIT
}


void CLogInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogInfoDlg)
	DDX_Control(pDX, IDC_LIST1, m_listLog);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbLogType);
	DDX_DateTimeCtrl(pDX, IDC_BEGIN_DATE, m_bData);
	DDX_DateTimeCtrl(pDX, IDC_BEGIN_TIME, m_bTime);
	DDX_DateTimeCtrl(pDX, IDC_END_DATE, m_eData);
	DDX_DateTimeCtrl(pDX, IDC_END_TIME, m_eTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CLogInfoDlg)
	ON_BN_CLICKED(IDC_BUTTTON_SEARCH, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_NEXT, OnBnClickedBtnNext)
	ON_BN_CLICKED(ID_BTN_EXPORT_LOG, OnBtnExportLog)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEALL, OnButtonRemoveall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogInfoDlg message handlers

BOOL CLogInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_cmbLogType.AddString(_CS("LogInfo.All"));
	m_cmbLogType.AddString(_CS("LogInfo.SystemManager"));
	m_cmbLogType.AddString(_CS("LogInfo.ConfigOperation"));
	m_cmbLogType.AddString(_CS("LogInfo.StorageManager"));
	m_cmbLogType.AddString(_CS("LogInfo.AlarmEvent"));
	m_cmbLogType.AddString(_CS("LogInfo.RecordOperation"));
	m_cmbLogType.AddString(_CS("LogInfo.UserManager"));
	m_cmbLogType.AddString(_CS("LogInfo.FileAccess"));
	m_cmbLogType.SetCurSel(0);
	
	
	m_listLog.InsertColumn(0, _CS( "InfoLog.No" ), LVCFMT_LEFT, 40, 0);
	m_listLog.InsertColumn(1, _CS( "InfoLog.LogTime" ), LVCFMT_LEFT, 130, 3);
	m_listLog.InsertColumn(2, _CS( "InfoLog.LogInfo" ), LVCFMT_LEFT, 300, 3);

	
	CTime cur_time = CTime::GetCurrentTime();
	CTime btime = CTime(cur_time.GetYear(),
		cur_time.GetMonth(), 
		cur_time.GetDay(),
		0,
		0,
		0);
	
	CTime etime = CTime(cur_time.GetYear(),
		cur_time.GetMonth(), 
		cur_time.GetDay(),
		23,
		59,
		59);
	m_bData = btime;
	m_bTime = btime;
	m_eData = etime;
	m_eTime = etime;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogInfoDlg::OnBnClickedOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	//查询条t
	memset( &m_searchConfig, 0, sizeof(SDK_LogSearchCondition) );

	m_searchConfig.nType = m_cmbLogType.GetCurSel();
	m_searchConfig.stBeginTime.year = m_bData.GetYear();
	m_searchConfig.stBeginTime.month = m_bData.GetMonth();
	m_searchConfig.stBeginTime.day = m_bData.GetDay();
	m_searchConfig.stBeginTime.hour = m_bTime.GetHour();
	m_searchConfig.stBeginTime.minute = m_bTime.GetMinute();
	m_searchConfig.stBeginTime.second = m_bTime.GetSecond();
	
	m_searchConfig.stEndTime.year = m_eData.GetYear();
	m_searchConfig.stEndTime.month = m_eData.GetMonth();
	m_searchConfig.stEndTime.day = m_eData.GetDay();
	m_searchConfig.stEndTime.hour = m_eTime.GetHour();
	m_searchConfig.stEndTime.minute = m_eTime.GetMinute(); 
	m_searchConfig.stEndTime.second = m_eTime.GetSecond();
	
	
	//判断开始时间与结束时间
	COleDateTime beginTime(m_bData.GetYear(), m_bData.GetMonth(), m_bData.GetDay(),
		m_bTime.GetHour(), m_bTime.GetMinute(), m_bTime.GetSecond());
	COleDateTime endTime(m_eData.GetYear(), m_eData.GetMonth(), m_eData.GetDay(),
		m_eTime.GetHour(), m_eTime.GetMinute(), m_eTime.GetSecond());
	
	if(beginTime >= endTime)
	{
		MessageBox(_CS("PlayBack.InvalidTime"),_CS("OneClick.Prompt"));
		return;
	} 
	
	
	m_listLog.DeleteAllItems();
	CString strMsg;
	
	SDK_LogList logList;
	memset( &logList, 0, sizeof(SDK_LogList) );

//	unsigned long dwReturn;
    long lLoginID = ((CClientDemo5Dlg*)AfxGetMainWnd())->m_LoginID;
	if (lLoginID <= 0)
	{
		return;
	}
	int nRet = H264_DVR_FindDVRLog(lLoginID,&m_searchConfig,&logList,sizeof(SDK_LogList));

                                                                                                                  		
	if ( nRet > 0 )
	{
		for ( int i = 0; i < logList.iNumLog; i ++ )
		{
			CString strType("LogType.");
			strMsg.Format( "%d" , i + 1);
			m_listLog.InsertItem( i , strMsg );	
			
			strMsg.Format("%04d-%02d-%02d %02d:%02d:%02d", 
				logList.Logs[i].stLogTime.year, logList.Logs[i].stLogTime.month,
				logList.Logs[i].stLogTime.day, logList.Logs[i].stLogTime.hour,
				logList.Logs[i].stLogTime.minute, logList.Logs[i].stLogTime.second);
			m_listLog.SetItemText( i, 1, strMsg );
			
			strType += logList.Logs[i].sType;
			strMsg.Format("%s", _CS(strType));
			
			//翻译DATA语言
			char buf[512];
			memset( buf, 0, sizeof(buf) );
			translate( logList.Logs[i].sType, logList.Logs[i].sData, buf, 512 );	
			
			if ( strcmp( buf, "") )
			{
				CString strTemp("");
				strTemp.Format("%s%s%s", "[", buf, "]");
				strMsg += strTemp;
			}
			m_listLog.SetItemText( i, 2, strMsg );
			m_listLog.SetItemText( i, 3, logList.Logs[i].sUser );
		}
	}
	else
	{
	    CString strMsg = ((CClientDemo5Dlg *)AfxGetMainWnd())->GetSdkErrorInfo(nRet ); //获取错误信息

	    MessageBox(strMsg, _CS("OneClick.Prompt"));
	    return;
	}

	//说明可能存在下一页
	if ( logList.iNumLog >= NET_MAX_RETURNED_LOGLIST )
	{
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(TRUE);
		
		//记录查询条件
		m_searchConfig.iLogPosition = logList.Logs[NET_MAX_RETURNED_LOGLIST - 1].iLogPosition;
	}
	else
	{
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
	}
}

void CLogInfoDlg::OnBnClickedBtnNext() 
{
 	// TODO: Add your control notification handler code here
	m_listLog.DeleteAllItems();
	CString strMsg;
	
	SDK_LogList logList;
	memset( &logList, 0, sizeof(SDK_LogList) );
	long lLoginID = ((CClientDemo5Dlg*)AfxGetMainWnd())->m_LoginID;
	if (lLoginID <= 0)
	{
		return;
	}
	int nRet = H264_DVR_FindDVRLog(lLoginID,&m_searchConfig,&logList,sizeof(SDK_LogList));
		
	if ( nRet > 0 )
	{
		for ( int i = 0; i < logList.iNumLog; i ++ )
		{
			CString strType("LogType.");
			strMsg.Format( "%d" , i + 1);
			m_listLog.InsertItem( i , strMsg );	
			
			strMsg.Format("%04d-%02d-%02d %02d:%02d:%02d", 
				logList.Logs[i].stLogTime.year, logList.Logs[i].stLogTime.month,
				logList.Logs[i].stLogTime.day, logList.Logs[i].stLogTime.hour,
				logList.Logs[i].stLogTime.minute, logList.Logs[i].stLogTime.second);
			m_listLog.SetItemText( i, 1, strMsg );
			
			strType += logList.Logs[i].sType;
			strMsg.Format("%s", _CS(strType));
			
			//翻译DATA语言
			char buf[512];
			memset( buf, 0, sizeof(buf) );
			translate( logList.Logs[i].sType, logList.Logs[i].sData, buf, 512 );	
			
			if ( strcmp( buf, "") )
			{
				CString strTemp("");
				strTemp.Format("%s%s%s", "[", buf, "]");
				strMsg += strTemp;
			}
			m_listLog.SetItemText( i, 2, strMsg );
			m_listLog.SetItemText( i, 3, logList.Logs[i].sUser );
		}
	}
	
	
	//说明可能存在下一页
	if ( logList.iNumLog < NET_MAX_RETURNED_LOGLIST )
	{
		GetDlgItem(IDC_BTN_NEXT)->EnableWindow(FALSE);
	}
	else
	{
		m_searchConfig.iLogPosition = logList.Logs[NET_MAX_RETURNED_LOGLIST - 1].iLogPosition;
	}

}

void CLogInfoDlg::translate(const char *type, const char *data, char *buf, int len)
{
	//char lang[128];
	char key[128];

	if (!type || !data || !buf || !len)
	{
		return;
	}

	if (!strcmp(type, "ShutDown"))
	{
		const char *pdata = strstr(data, "[");

		if (!pdata)
		{
			goto transFailed;
		}
		strncpy(buf, data, pdata - data);
		buf += pdata - data;
		len -= pdata - data;
		if (strstr(data, "Abnormal"))
		{
			snprintf(buf, len, ",(%s)", _CS("InfoLog.Abnormal"));
		}
		else
		{
			buf[0] = '\0';
		}
	}
	else if (!strcmp(type, "SaveConfig"))
	{
		snprintf(key, sizeof(key), "InfoLog.%s", data);
		snprintf(buf, len, "%s", _CS(key));
	}
	else if (!strcmp(type, "FileAccessError"))
	{
		if (data[0] == 'R')
		{
			snprintf(buf, len, _CS("InfoLog.ReadFileFailed"), data + 2);
		}
		else if (data[0] == 'W')
		{
			snprintf(buf, len, _CS("InfoLog.WriteFileFailed"), data + 2);
		}
		else if (data[0] == 'D')
		{
			snprintf(buf, len, _CS("InfoLog.DeleteFileFailed"), data + 2);
		}
		else 
		{
			goto transFailed;
		}
	}
	else if (!strcmp(type, "SetDriverType"))
	{
		const char *pdata = strstr(data, ",");

		if (pdata)
		{
			char dir[64];

			snprintf(key, sizeof(key), "InfoLog.%s", pdata + 1);
		//	assert(pdata-data < 64);
			strncpy(dir, data, pdata-data);
			dir[pdata-data] = '\0';
			snprintf(buf, len, _CS(key), dir);
		}
		else
		{
			goto transFailed;
		}
	}
	else if(!strcmp(type, "NatServer"))
	{
		const char *types[] ={
						"Reboot for update host ip",
						"Update host ip",
						"Register Status switch"};
		memset(key, 0, sizeof(key));
			size_t i;
			for (i = 0; i < sizeof(types)/sizeof(types[0]); i++)
			{
				if (!strncmp(data, types[i], min(strlen(types[i]), strlen(data))))
				{
					snprintf(key, sizeof(key), "&InfoLog.%s", types[i]);
					break;
				}
			}
			
			if (i != sizeof(types)/sizeof(types[0]))
			{
				snprintf(buf, len,  _CS(key));
			}
			else
			{
				goto transFailed;
			}
	}
	else if (!strcmp(type, "EventStart") 
			|| !strcmp(type, "EventStop")
			|| !strcmp(type, "EventLatch"))
	{
		int i;
		const char *pdata1 = strstr(data, ",");
		const char *types[] = {
						"LocalAlarm",
						"AlarmNet",
						"AlarmManual",
						"MotionDetect",
						"LossDetect",
						"BlindDetect",
						"VideoSplit",
						"StorageFailure",
						"StorageLowSpace",
						"NetAbort",
						"StorageNotExist",
						"NetIPConflict"};
		memset(key, 0, sizeof(key));
		for (i = 0; i < sizeof(types)/sizeof(types[0]); i++)
		{
			if (!strncmp(data, types[i], min(strlen(data), strlen(types[i]))))
			{
				snprintf(key, sizeof(key), "InfoLog.%s", types[i]);
				break;
			}
		}
		if (i != sizeof(types)/sizeof(types[0]))
		{
			if (i <= 5)
			{
				snprintf(buf, len, "%s%s %s", _CS(key), data + strlen(types[i]), _CS("InfoLog.Channel"));
			}
			else
			{
				snprintf(buf, len,  _CS(key));
			}
		}
		else
		{
			goto transFailed;
		}
	}
	else if (!strcmp(type, "LogIn"))
	{
		const char *pdata = strstr(data, ",");

		if (pdata)
		{
			std::string loginType = "Manager-UserLoginType.";
			
			strncpy(key, data, pdata - data);
			key[pdata - data] = '\0';
			loginType += pdata + 1;
			snprintf(buf, len, _CS("InfoLog.LogIn"), key, _CS(loginType.c_str()));
		}
		else
		{
			goto transFailed;
		}
	}
	else if (!strcmp(type, "LogOut"))
	{
		const char *pdata = strstr(data, ",");

		if (pdata)
		{
			std::string loginType = "Manager-UserLoginType.";
			
			strncpy(key, data, pdata - data);
			key[pdata - data] = '\0';
			loginType += pdata + 1;
			snprintf(buf, len, _CS("InfoLog.LogOut"), key, _CS(loginType.c_str()));
		}
		else
		{
			goto transFailed;
		}
	}
	else if (!strcmp(type, "FileSearch"))
	{
		int year, month, day, hour, minute, second;
		int channel;
		char type;

		if (sscanf(data, "%d-%d-%d %d:%d:%d, %d, %c", &year, &month, &day, &hour, &minute, &second,
				&channel, &type) == 8)
		{
			switch (type)
			{
			case 'M':
				snprintf(buf, len, _CS("InfoLog.SearchDetect"),
					year,month, day, hour, minute, second,
					channel);
				break;
			case 'H':
				snprintf(buf, len, _CS("InfoLog.SearchHand"),
					year, month, day, hour, minute, second,
					channel);
				break;
			case 'A':
				snprintf(buf, len, _CS("InfoLog.SearchAlarm"),
					year, month, day, hour, minute, second,
					channel);
				break;
			case '?':
			case '*':
				snprintf(buf, len, _CS("InfoLog.SearchAll"),
					year, month, day, hour, minute, second,
					channel);
				break;
			default:
				goto transFailed;
			}
		}
		else
		{
			goto transFailed;
		}

	}
	else if (!strcmp(type, "FileAccess"))
	{
		const char *pdata = strstr(data, ",");
		const char *ptype[] = {"Backup", "PlayBack", "Download"};
		int i;

		if (pdata)
		{
			for (i = 0; i < sizeof(ptype)/sizeof(ptype[0]); i++)
			{
				if (!strncmp(ptype[i], data, min(strlen(ptype[i]), strlen(data))))
				{
					snprintf(key, sizeof(key), "InfoLog.%s", ptype[i]);
					break;
				}
			}
			if (i == sizeof(ptype)/sizeof(ptype[0]))
			{
				goto transFailed;
			}
			snprintf(buf, len, _CS(key), pdata + 1);
		}
		else
		{
			goto transFailed;
		}
	}
	else if (!strcmp(type, "Record"))
	{
		const char *pdata = strstr(data, ",");
		const char *ptype[] = {"Manual", "Timing", "Close"};
		int i;

		if (pdata)
		{
			for (i = 0; i < sizeof(ptype)/sizeof(ptype[0]); i++)
			{
				if (!strncmp(ptype[i], data, min(strlen(ptype[i]), strlen(data))))
				{
					snprintf(key, sizeof(key), "InfoLog.%s", ptype[i]);
					break;
				}
			}
			if (i == sizeof(ptype)/sizeof(ptype[0]))
			{
				goto transFailed;
			}
			snprintf(buf, len, _CS(key), pdata + 1);
		}
		else
		{
			goto transFailed;
		}
	}
	else if (!strcmp(type, "Update"))
	{
		snprintf(buf, len, _CS("InfoLog.UpdateFailed"), data);
	}
	else if ( !strcmp(type, "DiskOver"))
	{
		snprintf(buf, len, _CS("InfoLog.DiskOver"), data);
	}
	else if ( !strcmp(type, "TimeChanged"))
	{
		snprintf(buf, len, _CS("InfoLog.TimeChanged"), data);
	}
	else if ( !strcmp(type, "AccountRestore") ) //处理账号恢复默认
	{
		snprintf(buf, len, _CS("InfoLog.AccountManual"), data);
	}
	else if ( !strcmp(type, "RecoverTime") )  //恢复时间
	{
		snprintf(buf, len, _CS("LogType.RecoverTime"), data );
	}
	else 
	{
		goto transFailed;
	}
	return;
transFailed:
	snprintf(buf, len, data);
}

void CLogInfoDlg::OnBtnExportLog() 
{
	// TODO: Add your control notification handler code here
	long lLoginID = ((CClientDemo5Dlg*)AfxGetMainWnd())->m_LoginID;
	if (lLoginID <= 0)
	{
		return;
	}

	CString strPath = _T("");
	strPath = BrowseForFolder(GetSafeHwnd());
	if ( strPath == _T("") )
	{
		return;
	}
	
	strPath += "\\DVRLog.zip";
	
	DWORD iLen = 0;
	char *pBuf = new char[MAX_BUF_LEN];
	if (NULL == pBuf)
	{
		return;
	}
	memset(pBuf, 0, MAX_BUF_LEN);
	// 获取配置
	int nRet = UpdateParam(E_SDK_LOG_EXPORT, pBuf, MAX_BUF_LEN, -1, FALSE, FALSE, &iLen);
	if (nRet > 0)
	{
		FileWrite(strPath, pBuf, iLen);
		
		MessageBox(_CS(_T("AccountMSG.ExportOK")), _CS(_T("OneClick.Prompt")));
	}
	else
	{
		MessageBox(_CS(_T("AccountMSG.ExportFail")), _CS(_T("OneClick.Prompt")));
	}
	delete [] pBuf;
}

CString CLogInfoDlg::BrowseForFolder(HWND hWnd)
{
	TCHAR szTitle[] = _T("Select a folder");
	TCHAR szDisplayName[MAX_PATH] = _T("");
	TCHAR szPath[MAX_PATH] = _T("");
	BROWSEINFO bi;
	
	bi.hwndOwner= hWnd;
	bi.pidlRoot= NULL;
	//bi.lpszTitle= szTitle;
	bi.lpszTitle = _T("");
	bi.pszDisplayName = szDisplayName;
	bi.ulFlags= BIF_RETURNONLYFSDIRS;
	bi.lpfn= NULL;
	bi.lParam= 0;
	
	LPITEMIDLIST pItemIDList = SHBrowseForFolder( &bi );
	if( pItemIDList )
	{
		SHGetPathFromIDList(pItemIDList,szPath);
		
		IMalloc *pMalloc;
		if( SHGetMalloc( &pMalloc ) != NOERROR )
		{
			//TRACE( "Failed to get pointer to shells task allocator" ) ;
			return szPath;
		}
		pMalloc->Free( pItemIDList );
		if( pMalloc )
			pMalloc->Release();
	}
	return szPath;
}

int CLogInfoDlg::UpdateParam(SDK_CONFIG_TYPE configType, char *pBuf, long lLength, int nChannel, BOOL bSaveAndValidate, BOOL bCheck, DWORD *lpRet)
{

	
	int nRet = FALSE;
	long lLoginID = ((CClientDemo5Dlg*)AfxGetMainWnd())->m_LoginID;
	//保存配置
	if (bSaveAndValidate)
	{
 
		nRet = H264_DVR_SetDevConfig(lLoginID,configType,nChannel,pBuf,lLength);
		if ( nRet > 0 )
		{
			//	if ( configType != E_SDK_CONFIG_SYSNET )
			//		MessageBox(_CS("Save conifg to device successful!"), _CS("Prompt") );  
		}
		else
		{
			if ( nRet != H264_DVR_OPT_REBOOT )
			{
				switch(nRet)
				{
				case H264_DVR_NOPOWER:
					{
						CString strMsg;
						strMsg.Format("%s", _CS("Error.NoPower") );
						MessageBox(strMsg, _CS("OneClick.Prompt"));
					}
					break;
				default:
					MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt"));
					break;
				}
			}
		}
 
		return nRet;
	}
	else
	{
		if (1) 
		{
		    nRet = H264_DVR_GetDevConfig(lLoginID,configType,-1,pBuf,lLength,lpRet);
			
			if ( 1 == nRet || 2 == nRet )
			{
			}
			else
			{
				if ( -1 == nRet )
				{
					MessageBox(_CS("Error.GetConfigFail"), _CS("OneClick.Prompt") );
				}
				else if ( -2 == nRet )
				{
					MessageBox(_CS("Error.SelectDevice"), _CS("OneClick.Prompt") );
				}
				else
				{
					//根据错误类型提示
					switch( nRet )
					{
					case H264_DVR_NOPOWER:	//没有权限
					{
							CString strMsg("");
							strMsg.Format("%s %s", _CS("Error.GetConfigFail") , _CS("Error.NoPower"));
							MessageBox(strMsg, _CS("OneClick.Prompt") );
						}
						break;
					case H264_DVR_SDK_TIMEOUT:
						{
							CString strMsg("");
							strMsg.Format("%s %s", _CS("Error.GetConfigFail") , _CS("Error.Timeout"));
							MessageBox(strMsg, _CS("OneClick.Prompt") );
							break;;
						}
					default:
						MessageBox(_CS("Error.GetConfigFail"), _CS("OneClick.Prompt") );
						break;
					}	
				}
				
				ShowWindow(SW_MINIMIZE);
				SetTimer(10, 0, NULL);
			}
		}
	}
	
	return nRet; 

}

bool CLogInfoDlg::FileWrite(CString strFileName, char *pBuf, int iLen)
{
	CFile file;	
	if(!file.Open(strFileName, CFile::modeCreate | CFile::modeWrite))
	{
		return false;
	}
	file.Write(pBuf, iLen);
	file.Close();
	return true;
}

void CLogInfoDlg::OnButtonRemoveall() 
{
	// TODO: Add your control notification handler code here
	long lLoginID = ((CClientDemo5Dlg*)AfxGetMainWnd())->m_LoginID;
	if (lLoginID <= 0)
	{
		return;
	}

	if ( IDYES != MessageBox(_CS("LogInfo.SureToClear"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION  ) )
	{
		return;
	}
	BOOL bRet = FALSE;

    int nRet = H264_DVR_ControlDVR(lLoginID,1);   // 0 重启  1 清除
	if ( nRet > 0 )
	{
		m_listLog.DeleteAllItems();
		MessageBox(_CS("LogInfo.ClearSuccess"), _CS("OneClick.Prompt") );  
	}
	else
	{
		switch(nRet)
		{
		case H264_DVR_NOPOWER:
			{
				CString strMsg;
				strMsg.Format("%s %s", _CS("LogInfo.ClearFail"), _CS("Error.NoPower") );
				MessageBox(strMsg, _CS("OneClick.Prompt"));
			}
			break;
		default:
			MessageBox(_CS("LogInfo.ClearFail"), _CS("OneClick.Prompt"));
			break;
		}
	}
}

void CLogInfoDlg::ClearAll()
{
	m_listLog.DeleteAllItems();
}
