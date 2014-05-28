// RemotePlaybackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "RemotePlaybackDlg.h"
#include "ClientDemoDlg.h"
#include <vector>
#include <IO.H>

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int CRemotePlaybackDlg::s_sSlowType = 0;
int CRemotePlaybackDlg::s_sFastType = 0;

/////////////////////////////////////////////////////////////////////////////
// CRemotePlaybackDlg dialog
//SDK download position callback
void __stdcall CRemotePlaybackDlg::SDKDownLoadPosCallback ( long lPlayHandle, 
														   long lTotalSize, 
														   long lDownLoadSize, 
														   long dwUser)
{	
	CRemotePlaybackDlg * pDeviceChannel = (CRemotePlaybackDlg*)dwUser;
	
	if ( NULL== pDeviceChannel)
	{
		ASSERT(FALSE);
		
		return;
	}
	
	if ( 0xffffffff == lDownLoadSize )
	{
		// data callback finished
		//	pDeviceChannel->SetPlayPos(1);
	}
}

int __stdcall 
CRemotePlaybackDlg::NetDataCallBack( long lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,long dwUser)
{	
	BOOL bResult = TRUE;
	try
	{
		CRemotePlaybackDlg *pDataChnl = (CRemotePlaybackDlg*)dwUser;
		
		if ( 0 == dwDataType )
		{
			if ( pDataChnl->m_nPlaybackDecHandle >= 0 )
			{
				return H264_PLAY_InputData( pDataChnl->m_nPlaybackDecHandle ,pBuffer, lbufsize );
			}	
		}
	}
	catch (...)
	{
		TRACE("\n the input data to decoder is abnormal\n");
	}
	
	// it must return TRUE if decode successfully,or the SDK will consider the decode is failed
	return bResult;
	
}

CFile g_file;
int __stdcall 
CRemotePlaybackDlg::NetDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, unsigned int dwUser)
{	
	BOOL bResult = TRUE;
	try
	{
		CRemotePlaybackDlg *pDataChnl = (CRemotePlaybackDlg*)dwUser;
		if ( pDataChnl->m_nPlaybackDecHandle >= 0 )
		{
			bResult = H264_PLAY_InputData( pDataChnl->m_nPlaybackDecHandle , (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);
			CString str("c:\\test.jpg");
			
					g_file.Write((unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);
			if (bResult)
			{
#if 0
				TRACE("timestamp: %d, year: %d, nMonth: %d, nDay: %d, nHour: %d, nMinute: %d, nSecond: %d\n",
					pFrame->dwTimeStamp, pFrame->nYear, pFrame->nMonth,
					pFrame->nDay, pFrame->nHour, pFrame->nMinute, pFrame->nSecond);
				
				if (pFrame->nPacketType == AUDIO_PACKET)
				{
					fwrite(pFrame->pPacketBuffer, pFrame->dwPacketSize, 1, fp);
					fclose(fp);
				}
			}
			else
			{
				char filename[256];
				static int index = 0;
				static int iFrame = 0;
				
				FILE *fp = NULL;
				if (pFrame->nPacketType == VIDEO_I_FRAME)
				{
					sprintf(filename, "stream/stream_%02d.idx", index++);
					fp = fopen(filename, "ab+");
					if (fp)
					{
						fwrite(pFrame->pPacketBuffer, pFrame->dwPacketSize, 1, fp);
						fclose(fp);
					}
					char filename[256];
					static int index = 0;
					
					sprintf(filename, "stream/Audio%02d.idx", index++);
					fp = fopen(filename, "ab+");
					if (fp)
					{
						fwrite(pFrame->pPacketBuffer, pFrame->dwPacketSize, 1, fp);
						fclose(fp);
					}
				}
				else
				{
					char filename[256];
					static int index = 0;
					static int iFrame = 0;
					
					FILE *fp = NULL;
					if (pFrame->nPacketType == VIDEO_I_FRAME)
					{
						sprintf(filename, "stream/stream_%02d.idx", index++);
						fp = fopen(filename, "ab+");
						if (fp)
						{
							fwrite(pFrame->pPacketBuffer, pFrame->dwPacketSize, 1, fp);
							fclose(fp);
						}
						iFrame = 1;
					}
					
					if (iFrame == 1)
					{
						fp = fopen("stream/StreamTotal.h264", "ab+");
						if (fp)
						{
							fwrite(pFrame->pPacketBuffer, pFrame->dwPacketSize, 1, fp);
							fclose(fp);
						}
					}
				}
#endif
			}
			return bResult;
		}	
	}
	catch (...)
	{
		TRACE("\n the input data to decoder is abnormal\n");
	}
	
	// it must return TRUE if decode successfully,or the SDK will consider the decode is failed
	return bResult;
	
}

CRemotePlaybackDlg::CRemotePlaybackDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRemotePlaybackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemotePlaybackDlg)
	m_endData = 0;
	m_begData = 0;
	m_begTime = 0;
	m_endTime = 0;
	m_bDownloadByTime = FALSE;
	m_bDownloadByName = TRUE;
	//}}AFX_DATA_INIT
	
	m_nPlaybackDecHandle = -1;
	m_lSaveHandle = -1;
	m_nPlayHandle = -1;
	m_lFileHandle = -1;
	m_hFileThread = NULL;
	m_bPause = FALSE;
	m_nCurRecNum=0;	
	m_mapNum=0;
	
}


void CRemotePlaybackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemotePlaybackDlg)
	DDX_Control(pDX, IDC_LIST1, m_fileList);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_videoWnd);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_cmbDevice);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_endData);
	DDX_DateTimeCtrl(pDX, IDC_DATE_BEGIN, m_begData);
	DDX_DateTimeCtrl(pDX, IDC_TIME_BEGIN, m_begTime);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_endTime);
	DDX_Check(pDX, IDC_CHECK_TIME, m_bDownloadByTime);
	DDX_Check(pDX, IDC_CHECK_NAME, m_bDownloadByName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemotePlaybackDlg, CDialog)
//{{AFX_MSG_MAP(CRemotePlaybackDlg)
ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, OnSelchangeComboDevice)
ON_BN_CLICKED(IDC_SEARCH, OnSearch)
ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
ON_BN_CLICKED(IDC_PLAY, OnPlay)
ON_BN_CLICKED(IDC_STOP, OnStop)
ON_BN_CLICKED(IDC_FAST, OnFast)
ON_BN_CLICKED(IDC_SLOW, OnSlow)
ON_BN_CLICKED(IDC_PAUSE, OnPause)
ON_WM_DESTROY()
ON_WM_TIMER()
ON_BN_CLICKED(IDC_CHECK_NAME, OnCheckDownLoadByName)
ON_BN_CLICKED(IDC_CHECK_TIME, OnCheckDownLoadByTime)
ON_BN_CLICKED(IDC_PAGE_UP, OnPageUp)
ON_BN_CLICKED(IDC_PAGE_DOWN, OnPageDown)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_Audio, OnBUTTONAudio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemotePlaybackDlg message handlers

BOOL CRemotePlaybackDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_CWndCS(this);
	
	m_fileList.SetExtendedStyle( m_fileList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	GetDlgItem(IDC_PAGE_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAGE_DOWN)->EnableWindow(FALSE);
	
	int nIndex = m_cmbDevice.AddString(_CS("PlayBack.SelectDevice"));
	m_cmbDevice.SetItemData(nIndex, 1);
	
	//get device info
	CClientDemoDlg *pMain = (CClientDemoDlg *)AfxGetApp()->m_pMainWnd;
	if ( pMain )
	{
		Devc_Map *pMap = pMain->GetDeviceMap();
		if ( pMap )
		{
			Devc_Map::iterator bIter;
			for ( bIter = pMap->begin(); bIter != pMap->end(); bIter ++ )
			{
				DEV_INFO *pDev = bIter->second;
				if ( pDev )
				{
					nIndex = m_cmbDevice.AddString(pDev->szDevName);
					m_cmbDevice.SetItemData(nIndex, (DWORD)pDev );
				}
			}
		}
	}	
	if (m_cmbDevice.GetCount() > 1)
	{
		m_cmbDevice.SetCurSel(1);
	}
	else
	{
		m_cmbDevice.SetCurSel(0);
	}
	OnSelchangeComboDevice();
	
	m_cmbType.AddString(_CS("PlayBack.ALL"));
	m_cmbType.AddString(_CS("PlayBack.AlarmRecordFile"));
	m_cmbType.AddString(_CS("PlayBack.DetectRecordfile"));
	m_cmbType.AddString(_CS("PlayBack.GeneralRecordFile"));
	m_cmbType.AddString(_CS("PlayBack.HandRecordFile"));
	m_cmbType.SetCurSel(0);
	
	CTime cur_time = CTime::GetCurrentTime();
	CTime time = CTime(cur_time.GetYear(),cur_time.GetMonth(), cur_time.GetDay(),
		cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
	
	m_begData = m_endData = m_endTime = time;
	
	CTime bTime = CTime( cur_time.GetYear(),cur_time.GetMonth(), cur_time.GetDay(), 0 , 0 , 0 );
	m_begTime = bTime;
	
	UpdateData( FALSE );
	
	m_fileList.InsertColumn(0, _CS("PlayBack.NO"),  LVCFMT_LEFT, 80,-1 );
	m_fileList.InsertColumn(1, _CS("PlayBack.File"), LVCFMT_LEFT,200,-1);
	
	m_progress.SetRange(0,100);
	
	
	m_nGetPage=0;
	m_nCurPage=-1;
	m_nTotalPage=-1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRemotePlaybackDlg::OnSelchangeComboDevice() 
{
	int nSelectedIndex = m_cmbDevice.GetCurSel();
	if ( nSelectedIndex <= 0 )
	{
		return;
	}
	
	DEV_INFO *pDev = (DEV_INFO *)m_cmbDevice.GetItemData(nSelectedIndex);
	if ( pDev )
	{
		m_cmbChannel.ResetContent();
		
		CString strChannel("");
		for ( int i = 0; i < pDev->nTotalChannel; i ++ )
		{
			strChannel.Format("%d", i + 1);
			m_cmbChannel.AddString(strChannel);
		}
		m_lLoginID = pDev->lLoginID;
	}
	m_cmbChannel.SetCurSel(0);
}

void CRemotePlaybackDlg::OnSearch() 
{
	m_nGetPage=0;
	m_nCurPage=-1;
	m_nTotalPage=-1;
	
	UpdateData();
	
	OnStop();  //查询之前先关闭所有的播放

	int nSelectedIndex = m_cmbDevice.GetCurSel();
	if ( nSelectedIndex <= 0)
	{
		MessageBox(_CS("PlayBack.SelectDevice"));
		return;
	}
	
	ClearResult();
	
	ClearMapResult();
	
	int nChannel = m_cmbChannel.GetCurSel();	//channel No.
	int nFileType = m_cmbType.GetCurSel();		//file type
	
	H264_DVR_TIME StartTime;
	H264_DVR_TIME StopTime;
	
	StartTime.dwYear = (WORD)m_begData.GetYear();
	StartTime.dwMonth = (WORD)m_begData.GetMonth();
	StartTime.dwDay = (WORD)m_begData.GetDay();
	StartTime.dwHour = (char)m_begTime.GetHour();
	StartTime.dwMinute = (char)m_begTime.GetMinute();
	StartTime.dwSecond = (char)m_begTime.GetSecond();
	StopTime.dwYear = (WORD)m_endData.GetYear();
	StopTime.dwMonth = (WORD)m_endData.GetMonth();
	StopTime.dwDay = (WORD)m_endData.GetDay();
	StopTime.dwHour = (char)m_endTime.GetHour();
	StopTime.dwMinute = (char)m_endTime.GetMinute();
	StopTime.dwSecond = (char)m_endTime.GetSecond();
	
	DEV_INFO *pDevTemp=(DEV_INFO*)m_cmbDevice.GetItemData(nSelectedIndex);
	
	H264_DVR_FILE_DATA *szSend=new H264_DVR_FILE_DATA[100];
	
	
	if (pDevTemp)
	{
		m_lLoginID=pDevTemp->lLoginID;
		
		int nMaxLen = 100 * sizeof(H264_DVR_FILE_DATA);
		
		const int WAITTIME = 4000;   //waitting time
		int nNum = 0; //number of files return
		
		H264_DVR_FINDINFO searchInfo;
		searchInfo.nChannelN0 = nChannel;
		searchInfo.nFileType = nFileType;
		memcpy( &searchInfo.startTime, &StartTime, sizeof(searchInfo.startTime));
		memcpy( &searchInfo.endTime, &StopTime, sizeof(searchInfo.endTime));
		
		GetDlgItem(IDC_SEARCH)->EnableWindow(FALSE);
		
        int nRet=H264_DVR_FindFile(m_lLoginID,&searchInfo,szSend,100,&nNum);
		
		m_nCurRecNum=nNum;
		
		memcpy(&m_mapTemp[m_mapNum++],&searchInfo,sizeof(H264_DVR_FINDINFO));
		
		if ( nRet > 0 && nNum > 0)  //处理没有录象的情况下
		{
			m_nGetPage ++;
			m_nCurPage = 1;
			
			m_pstrFileVector.reserve(m_nCurRecNum);
			
			for(int i=0;i<m_nCurRecNum;i++)
			{
				m_pstrFileVector.push_back(szSend+i);
			} 
			
			m_nSearchInfo.nChannelN0=nChannel;
			m_nSearchInfo.nFileType=nFileType;
			m_nSearchInfo.startTime.dwYear=szSend[m_nCurRecNum-1].stEndTime.year;
			m_nSearchInfo.startTime.dwMonth=szSend[m_nCurRecNum-1].stEndTime.month;
			m_nSearchInfo.startTime.dwDay=szSend[m_nCurRecNum-1].stEndTime.day;
			m_nSearchInfo.startTime.dwHour=szSend[m_nCurRecNum-1].stEndTime.hour;
			m_nSearchInfo.startTime.dwMinute=szSend[m_nCurRecNum-1].stEndTime.minute;
			m_nSearchInfo.startTime.dwSecond=szSend[m_nCurRecNum-1].stEndTime.second;
			memcpy(&m_nSearchInfo.endTime,&searchInfo.endTime,sizeof(m_nSearchInfo.endTime));
			
			if(nNum<PLAYBACK_MAX_FILE_NUM)
			{
				m_nTotalPage=m_nGetPage;
			}
            
			AddFileListInfo(m_nCurRecNum);//add list item
			SetPageBtnState();
		}else
		{
			if (szSend)
			{
				delete szSend;
				szSend = NULL;
			}
			MessageBox(_CS("PlayBack.SearchFail"));
		}
		GetDlgItem(IDC_SEARCH)->EnableWindow(TRUE);
	}
}

void CRemotePlaybackDlg::OnDownload()
{
	UpdateData();
	
	int nSelectedIndex = m_cmbDevice.GetCurSel();
	if ( nSelectedIndex <= 0 )
	{
		MessageBox(_CS("PlayBack.SelectDevice"));
		return;
	}
	
	if (m_bDownloadByTime)
	{
		OnDownloadByTime();
	}
	else
	{
		OnDownloadByName();
	}
}

void CRemotePlaybackDlg::OnDownloadByName() 
{
	UpdateData(TRUE);
	
	if ( m_lSaveHandle > 0 )
	{
		KillTimer(1);
		H264_DVR_StopGetFile(m_lSaveHandle);
		m_lSaveHandle = -1;
		m_progress.SetPos(0);
		
		GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Download"));
		
		return;
	}
	
	CString csFileName;
	
	int nSelectedIndex = m_fileList.GetSelectionMark();
	if ( nSelectedIndex < 0 )
	{
		MessageBox(_CS("PlayBack.SelectFile"));
		return;
	}
	
	H264_DVR_FILE_DATA *pstrFileInfo = (H264_DVR_FILE_DATA *)m_fileList.GetItemData(nSelectedIndex);
	if (  !pstrFileInfo )
	{
		return;
	}
	
	CString strSaveName("");
	//strSaveName.Format("c:\\record\\record.h264");
	nSelectedIndex = m_cmbDevice.GetCurSel();
	if ( nSelectedIndex <= 0)
	{
		MessageBox(_CS("PlayBack.SelectDevice"));
		return;
	}
    DEV_INFO *pDevTemp=(DEV_INFO*)m_cmbDevice.GetItemData(nSelectedIndex);
	
	CString strInitDir;
	
	strInitDir = GET_MODULE_FILE_INFO.strPath;
	if (strInitDir.Right(1) == '\\') 
	{
		strInitDir += "Download";
	}
	else
	{
		strInitDir += "\\Download";
	}	
	if (-1 == _access(strInitDir, 0)) 
	{
		CreateDirectory(strInitDir, NULL);
	}
	
	CString strFileTpye("h264");
	CString strFileName("");
	if (strstr(pstrFileInfo->sFileName, ".h264"))
	{
		strFileTpye = _T("h264");
	}
	else
	{
		strFileTpye = _T("jpg");
	}
	strFileName.Format("%s_%02d_%04d%02d%02d_%02d%02d%02d.%s", 
		pDevTemp->szDevName, pstrFileInfo->ch + 1, 
		pstrFileInfo->stBeginTime.year, pstrFileInfo->stBeginTime.month,
		pstrFileInfo->stBeginTime.day, pstrFileInfo->stBeginTime.hour,
		pstrFileInfo->stBeginTime.minute, pstrFileInfo->stBeginTime.second, strFileTpye);
	
	CFileDialog dlg( FALSE , strFileTpye, strFileName , OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"All File(*.h264;*.jpg)|*.*||" , this );
	dlg.m_ofn.lpstrInitialDir = strInitDir;		//默认路径
	if( dlg.DoModal() == IDOK )
	{
		strSaveName = dlg.GetPathName();
		//m_lSaveHandle = H264_DVR_GetFileByName(m_lLoginID, pstrFileInfo,strSaveName.GetBuffer(0),SDKDownLoadPosCallback,(DWORD)this);
		m_lSaveHandle = H264_DVR_GetFileByName(m_lLoginID, pstrFileInfo,strSaveName.GetBuffer(0));
		if(m_lSaveHandle >= 0)
		{
			m_progress.SetPos(0);
			GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Stop"));
			//update the progress control
			SetTimer(1,0,NULL);
		}
		else
		{
		CString sTemp;
		sTemp.Format("dowload fail ERROR = %d",H264_DVR_GetLastError());
		AfxMessageBox(sTemp);
		}
	}
}

void CRemotePlaybackDlg::OnDownloadByTime() 
{
	UpdateData(TRUE);
	
	if ( m_lSaveHandle > 0 )
	{
		KillTimer(1);
		H264_DVR_StopGetFile(m_lSaveHandle);
		m_lSaveHandle = -1;
		m_progress.SetPos(0);
		
		GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Download"));
		
		return;
	}
	
	CString strSaveName("");
	//strSaveName.Format("c:\\record");
	strSaveName = BrowseForFolder(GetSafeHwnd()) ;
	
	if ( strSaveName == _T(""))  //未选择路径时退出
	{
		return;
	}
	H264_DVR_FINDINFO info;
	
	memset(&info, 0, sizeof(info));
	info.nChannelN0 = m_cmbChannel.GetCurSel();	//channel No.
	info.nFileType = m_cmbType.GetCurSel();		//file type
	info.startTime.dwYear = (WORD)m_begData.GetYear();
	info.startTime.dwMonth = (WORD)m_begData.GetMonth();
	info.startTime.dwDay = (WORD)m_begData.GetDay();
	info.startTime.dwHour = (char)m_begTime.GetHour();
	info.startTime.dwMinute = (char)m_begTime.GetMinute();
	info.startTime.dwSecond = (char)m_begTime.GetSecond();
	info.endTime.dwYear = (WORD)m_endData.GetYear();
	info.endTime.dwMonth = (WORD)m_endData.GetMonth();
	info.endTime.dwDay = (WORD)m_endData.GetDay();
	info.endTime.dwHour = (char)m_endTime.GetHour();
	info.endTime.dwMinute = (char)m_endTime.GetMinute();
	info.endTime.dwSecond = (char)m_endTime.GetSecond();
	int nRecordFileType = m_cmbType.GetCurSel();
	info.nFileType = (nRecordFileType <= SDK_RECORD_MANUAL) ?  nRecordFileType : (SDK_PIC_ALL + nRecordFileType - SDK_RECORD_MANUAL - 1);
	
	m_lSaveHandle = H264_DVR_GetFileByTime(m_lLoginID, &info, strSaveName.GetBuffer(0));
	if(m_lSaveHandle > 0)
	{
		m_progress.SetPos(0);
		
		GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Stop"));
		
		//update the progress control
		SetTimer(1,0,NULL);
	}
	else
	{
		CString sTemp;
		sTemp.Format("dowload fail ERROR = %d",H264_DVR_GetLastError());
		AfxMessageBox(sTemp);
	}
}

void CRemotePlaybackDlg::OnPlay() 
{
	UpdateData();
	
	int nSelectedIndex = m_cmbDevice.GetCurSel();
	if ( nSelectedIndex <= 0 )
	{
		MessageBox(_CS("PlayBack.SelectDevice"));
		return;
	}
	
	if (m_bDownloadByTime)
	{
		OnPlayByTime();
	}
	else
	{
		OnPlayByName();
	}
}

void CRemotePlaybackDlg::OnPlayByTime() 
{
	if(m_nPlayHandle == -1)
	{
		H264_DVR_FINDINFO info;
		
		memset(&info, 0, sizeof(info));
		info.nChannelN0 = m_cmbChannel.GetCurSel();	//channel No.
		info.nFileType = m_cmbType.GetCurSel();		//file type
		info.startTime.dwYear = (WORD)m_begData.GetYear();
		info.startTime.dwMonth = (WORD)m_begData.GetMonth();
		info.startTime.dwDay = (WORD)m_begData.GetDay();
		
		info.startTime.dwHour = (char)m_begTime.GetHour();
		info.startTime.dwMinute = (char)m_begTime.GetMinute();
		info.startTime.dwSecond = (char)m_begTime.GetSecond();
		info.endTime.dwYear = (WORD)m_endData.GetYear();
		info.endTime.dwMonth = (WORD)m_endData.GetMonth();
		info.endTime.dwDay = (WORD)m_endData.GetDay();
		info.endTime.dwHour = (char)m_endTime.GetHour();
		info.endTime.dwMinute = (char)m_endTime.GetMinute();
		info.endTime.dwSecond = (char)m_endTime.GetSecond();
		
		//open decode channel
		if ( m_nPlaybackDecHandle == -1 )
		{
			BYTE byFileHeadBuf;
			if (H264_PLAY_OpenStream(40, &byFileHeadBuf, 1, SOURCE_BUF_MIN*50))
			{	
				H264_PLAY_SetStreamOpenMode(40, STREAME_FILE);	
				H264_PLAY_Play(40, m_videoWnd.m_hWnd);
				
				m_nPlaybackDecHandle = 40;
			}	
		}
		if ( m_nPlaybackDecHandle < 0 )
		{
			return;
		}
		
		// 		m_nPlayHandle = H264_DVR_PlayBackByTimeEx(m_lLoginID, info.nChannelN0, 
		// 			&info.startTime, &info.endTime,
		// 			NetDataCallBack, (DWORD)this, SDKDownLoadPosCallback, (DWORD)this);
		m_nPlayHandle = H264_DVR_PlayBackByTime(m_lLoginID, &info, 
			SDKDownLoadPosCallback, NetDataCallBack, (DWORD)this);
		
		if(m_nPlayHandle <= 0 )
		{
			AfxMessageBox(_CS("Playback fail"));
			m_nPlayHandle = -1;
			return;
		}
	}
	else
	{
		//if in pause, normal it
		if (m_bPause)
		{
			H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_CONTINUE, 0 );
			H264_PLAY_Pause(m_nPlaybackDecHandle, !m_bPause);
			m_bPause = !m_bPause;
		}
		//set play speed to normal
		H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_FAST, 0);
		//set decode speed to normal
		H264_PLAY_Play(m_nPlaybackDecHandle, m_videoWnd.m_hWnd);
		s_sFastType = 0;
		s_sSlowType = 0;
	}
}
void CRemotePlaybackDlg::OnPlayByName() 
{
	if(m_nPlayHandle == -1)
	{
		CString csFileName;
		
		int nSelectedIndex = m_fileList.GetSelectionMark();
		if ( nSelectedIndex < 0 )
		{
			MessageBox(_CS("PlayBack.SelectFile"));
			return;
		}
		
		H264_DVR_FILE_DATA *pstrFileInfo = (H264_DVR_FILE_DATA *)m_fileList.GetItemData(nSelectedIndex);
		if (  !pstrFileInfo )
		{
			return;
		}
		
		//open decode channel
		if ( m_nPlaybackDecHandle == -1 )
		{
			BYTE byFileHeadBuf;
			if (H264_PLAY_OpenStream(40, &byFileHeadBuf, 1, SOURCE_BUF_MIN*50))
			{	
				H264_PLAY_SetStreamOpenMode(40, STREAME_FILE);	
				H264_PLAY_Play(40, m_videoWnd.m_hWnd);
				
				m_nPlaybackDecHandle = 40;
			}	
		}
		if ( m_nPlaybackDecHandle < 0 )
		{
			return;
		}		
		//m_nPlayHandle = H264_DVR_PlayBackByName(m_lLoginID, pstrFileInfo, SDKDownLoadPosCallback, NetDataCallBack, (DWORD)this );
		m_nPlayHandle = H264_DVR_PlayBackByName_V2(m_lLoginID, pstrFileInfo, SDKDownLoadPosCallback, NetDataCallBack_V2, (DWORD)this );
		if(m_nPlayHandle <= 0 )
		{
			AfxMessageBox(_CS("Playback fail"));
			return;
		}
		CString str("c:\\AudioTest.h264");
		g_file.Open(str, CFile::modeCreate | CFile::modeReadWrite);
	}
	else
	{
		//if in pause, normal it
		if (m_bPause)
		{
			H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_CONTINUE, 0 );
			H264_PLAY_Pause(m_nPlaybackDecHandle, !m_bPause);
			m_bPause = !m_bPause;
		}
		//set play speed to normal
		H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_FAST, 0);
		//set decode speed to normal
		H264_PLAY_Play(m_nPlaybackDecHandle, m_videoWnd.m_hWnd);
		s_sFastType = 0;
		s_sSlowType = 0;
	}
}

void CRemotePlaybackDlg::OnStop() 
{
	if(m_nPlayHandle >= 0)
	{
		H264_DVR_StopPlayBack(m_nPlayHandle);
		m_nPlayHandle = -1;
	}
	if ( m_nPlaybackDecHandle)
	{
		H264_PLAY_CloseStream(m_nPlaybackDecHandle);
		H264_PLAY_Stop(m_nPlaybackDecHandle);
		m_nPlaybackDecHandle = -1;
	}
	Invalidate();
}

void CRemotePlaybackDlg::OnFast() 
{
	if (++s_sFastType > 4)
	{
		s_sFastType = 1;
	}
	s_sSlowType = 0;
	H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_FAST, s_sFastType);
	H264_PLAY_Fast(m_nPlaybackDecHandle);
}

void CRemotePlaybackDlg::OnSlow() 
{
	if (++s_sSlowType > 4)
	{
		s_sSlowType = 1;
	}
	s_sFastType = 0;
	H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_SLOW, s_sSlowType);
	H264_PLAY_Slow(m_nPlaybackDecHandle);
}

void CRemotePlaybackDlg::OnPause() 
{
	if (!m_bPause)
		H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_PAUSE, 0 );
	else
		H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_CONTINUE, 0 );
	H264_PLAY_Pause(m_nPlaybackDecHandle, !m_bPause);
	m_bPause = !m_bPause;
}

void CRemotePlaybackDlg::OnDestroy() 
{
	
	vector<H264_DVR_FILE_DATA*>::iterator p=m_pstrFileVector.begin();
	while( p!=m_pstrFileVector.end())
	{
		H264_DVR_FILE_DATA* pData = (*p);
		delete pData;
		p++;		
	}
	
	ClearResult();
	ClearMapResult();
	KillTimer(1);
	OnStop();
	g_file.Close();
	CDialog::OnDestroy();
}

void CRemotePlaybackDlg::ClearResult()
{
	m_fileList.DeleteAllItems();
	
	int nTotal = m_cmbChannel.GetCount();
	
	for ( int i = 0; i < nTotal; i ++ )
	{
		DEV_INFO *pInfo = (DEV_INFO *)m_cmbChannel.GetItemData(i);
		if ( pInfo )
		{
			delete pInfo;
			pInfo = NULL;
		}
	}
	m_cmbChannel.Clear();
	m_pstrFileVector.clear();
}


void CRemotePlaybackDlg::OnTimer(UINT nIDEvent) 
{
	if( m_lSaveHandle > 0 )
	{
		int nPos = H264_DVR_GetDownloadPos(m_lSaveHandle);
		if(nPos < 0)		//fail
		{
			H264_DVR_StopGetFile(m_lSaveHandle);
			m_progress.SetPos(0);
			m_lSaveHandle = -1;
			GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Download"));
			AfxMessageBox("get download process fail");
		}
		if(nPos == 100)		//download end
		{
			H264_DVR_StopGetFile(m_lSaveHandle);
			m_lSaveHandle = -1;
			KillTimer(1);
			m_progress.SetPos(0);
			GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Download"));
			AfxMessageBox(_CS("PlayBack.DownloadFinish"));
		}
		if(nPos > 100)		//abnormal
		{
			H264_DVR_StopGetFile(m_lSaveHandle);
			m_lSaveHandle = -1;
			m_progress.SetPos(0);
			GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Download"));
			AfxMessageBox(_CS("PlayBack.DownloadError"));
		}
		else
		{
			m_progress.SetPos(nPos);
		}
	}
	//KillTimer(1);
	//UpdateProgressCtrl(m_dwDownSize,m_dwTotalSize);
	CDialog::OnTimer(nIDEvent);
}

void CRemotePlaybackDlg::OnCheckDownLoadByName() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_bDownloadByName)
	{
		m_bDownloadByTime = FALSE;
	}
	UpdateData(FALSE);
}

void CRemotePlaybackDlg::OnCheckDownLoadByTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_bDownloadByTime)
	{
		m_bDownloadByName = FALSE;
	}
	UpdateData(FALSE);
}

void CRemotePlaybackDlg::OnPageUp() 
{
	
	// TODO: Add your control notification handler code here	
	if ( m_nGetPage <= 1 || m_nCurPage <= 1)
	{
		return;
	}
	
	m_nCurPage --;
	m_nGetPage --;
	
	ClearResult();
	
	m_mapNum=m_mapNum-1;
	
	if(GetNextPageInfo(&m_mapTemp[--m_mapNum]))
	{
		H264_DVR_FILE_DATA *szSend = new H264_DVR_FILE_DATA[100];
		
		int nNum=0;
		
		int nRet=H264_DVR_FindFile(m_lLoginID,&m_mapTemp[m_mapNum],szSend,100,&nNum);
		
		m_nCurRecNum=nNum;
		
		if(nRet > 0 && nNum > 0) //处理没有录象的情况
		{
			m_pstrFileVector.reserve(m_nCurRecNum);
			
			for ( int i = 0; i < m_nCurRecNum; i ++)
			{
				m_pstrFileVector.push_back(szSend+i);
			}
			m_nSearchInfo.nChannelN0=m_nSearchInfo.nChannelN0;
			m_nSearchInfo.nFileType=m_nSearchInfo.nFileType;
			m_nSearchInfo.startTime.dwYear=szSend[m_nCurRecNum-1].stEndTime.year;
			m_nSearchInfo.startTime.dwMonth=szSend[m_nCurRecNum-1].stEndTime.month;
			m_nSearchInfo.startTime.dwDay=szSend[m_nCurRecNum-1].stEndTime.day;
			m_nSearchInfo.startTime.dwHour=szSend[m_nCurRecNum-1].stEndTime.hour;
			m_nSearchInfo.startTime.dwMinute=szSend[m_nCurRecNum-1].stEndTime.minute;
			m_nSearchInfo.startTime.dwSecond=szSend[m_nCurRecNum-1].stEndTime.second;
			memcpy(&m_nSearchInfo.endTime,&m_mapTemp[m_mapNum].endTime,sizeof(m_nSearchInfo.endTime));
			
			m_mapNum++;
		}else
		{
			if (szSend)
			{
				delete szSend;
				szSend = NULL;
			}
		}
		AddFileListInfo(m_nCurRecNum);
		SetPageBtnState();
	}
}

void CRemotePlaybackDlg::OnPageDown() 
{
	
	// TODO: Add your control notification handler code here
	if ( m_nGetPage <= 0 )
	{
		return;
	}
	
	if((m_nTotalPage!=-1)&&(m_nCurPage == m_nTotalPage))
	{
		SetPageBtnState();
		return;
	}
	
	ClearResult();
	
	if ( GetNextPageInfo(&m_nSearchInfo)&&(m_nCurPage == m_nGetPage))
	{
		H264_DVR_FILE_DATA *szSend = new H264_DVR_FILE_DATA[100];
		
		int nNum=0;
		
		int nRet=H264_DVR_FindFile(m_lLoginID,&m_nSearchInfo,szSend,100,&nNum);
		
		m_nCurRecNum=nNum;
		
		if (nRet> 0 && nNum > 0)  //处理没有录象的情况
		{
			m_nGetPage ++;
			
			memcpy(&m_mapTemp[m_mapNum++],&m_nSearchInfo,sizeof(H264_DVR_FINDINFO));
			
			m_pstrFileVector.reserve(m_nCurRecNum);
			
			for ( int i = 0; i < m_nCurRecNum; i ++ )
			{
				m_pstrFileVector.push_back(szSend+i);
			}
			
			m_nSearchInfo.nChannelN0=m_nSearchInfo.nChannelN0;
			m_nSearchInfo.nFileType=m_nSearchInfo.nFileType;
			m_nSearchInfo.startTime.dwYear=szSend[m_nCurRecNum-1].stEndTime.year;
			m_nSearchInfo.startTime.dwMonth=szSend[m_nCurRecNum-1].stEndTime.month;
			m_nSearchInfo.startTime.dwDay=szSend[m_nCurRecNum-1].stEndTime.day;
			m_nSearchInfo.startTime.dwHour=szSend[m_nCurRecNum-1].stEndTime.hour;
			m_nSearchInfo.startTime.dwMinute=szSend[m_nCurRecNum-1].stEndTime.minute;
			m_nSearchInfo.startTime.dwSecond=szSend[m_nCurRecNum-1].stEndTime.second;
			memcpy(&m_nSearchInfo.endTime,&m_nSearchInfo.endTime,sizeof(m_nSearchInfo.endTime));
			
			if ( m_nCurRecNum <PLAYBACK_MAX_FILE_NUM)
			{
				m_nTotalPage = m_nGetPage;
			}
			
			m_nCurPage ++;
			
			AddFileListInfo(m_nCurRecNum);
			
			SetPageBtnState();
		}
		else
		{
			if (szSend)
			{
				delete szSend;
				szSend = NULL;
			}
		}
	}
}
void CRemotePlaybackDlg::AddFileListInfo(int iNum)
{
	if ( m_bDownloadByTime )
	{
		iNum = 1;
		m_nCurPage=1;
	    m_nTotalPage=1;
	}
	
	for ( int i = 0; i < iNum ; i++)
	{
		CString tempstring;
		tempstring.Format("%d", i + 1);
		m_fileList.InsertItem(i,tempstring);
		
		CString strBtme,strEtime;
		if ( m_bDownloadByTime )
		{
			strBtme.Format("%04d-%02d-%02d-%02d:%02d:%02d",m_begData.GetYear(), 
				m_begData.GetMonth(),
				m_begData.GetDay(),
				m_begTime.GetHour(),
				m_begTime.GetMinute(),
				m_begTime.GetSecond());
			
			strEtime.Format("%04d-%02d-%02d-%02d:%02d:%02d",m_endData.GetYear(), 
				m_endData.GetMonth(),
				m_endData.GetDay(),
				m_endTime.GetHour(),
				m_endTime.GetMinute(),
				m_endTime.GetSecond());
			
			tempstring.Format("%s-%s", strBtme, strEtime);
		}else
		{
			strBtme.Format("%04d-%02d-%02d-%02d:%02d:%02d",m_pstrFileVector[i]->stBeginTime.year, 
				m_pstrFileVector[i]->stBeginTime.month,
				m_pstrFileVector[i]->stBeginTime.day,
				m_pstrFileVector[i]->stBeginTime.hour,
				m_pstrFileVector[i]->stBeginTime.minute,
				m_pstrFileVector[i]->stBeginTime.second);
			
			strEtime.Format("%04d-%02d-%02d-%02d:%02d:%02d",
				m_pstrFileVector[i]->stEndTime.year, 
				m_pstrFileVector[i]->stEndTime.month,
				m_pstrFileVector[i]->stEndTime.day,
				m_pstrFileVector[i]->stEndTime.hour,
				m_pstrFileVector[i]->stEndTime.minute,
				m_pstrFileVector[i]->stEndTime.second);
			
			tempstring.Format("%s-%s(%dKB)", strBtme, strEtime, m_pstrFileVector[i]->size);
		}
		
		m_fileList.SetItemText(i, 1, tempstring);
		
		DWORD addr=(DWORD)(m_pstrFileVector[i]);
		
		m_fileList.SetItemData(i,addr);
	}
}

void CRemotePlaybackDlg::SetPageBtnState()
{
	if ( m_nTotalPage == -1 || m_nGetPage < m_nTotalPage)
	{
		GetDlgItem(IDC_PAGE_DOWN)->EnableWindow(TRUE);
	}
	else
	{
		if ( m_nCurPage < m_nGetPage )
		{
			GetDlgItem(IDC_PAGE_DOWN)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_PAGE_DOWN)->EnableWindow(FALSE);
		}
	}
	
	if ( m_nCurPage > 1 )
	{
		GetDlgItem(IDC_PAGE_UP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_PAGE_UP)->EnableWindow(FALSE);
	}
}


int CRemotePlaybackDlg::GetNextPageInfo(H264_DVR_FINDINFO* searchInfo)
{
	H264_DVR_FILE_DATA *szSend = new H264_DVR_FILE_DATA[100];
	int nNum=0;
	
	if (!searchInfo)
	{
		return 0;
	}
	
	int ret = H264_DVR_FindFile(m_lLoginID,searchInfo,szSend,100,&nNum);
	
	delete []szSend;
	
	return ( ret > 0 );
}

void CRemotePlaybackDlg::ClearMapResult()
{
	m_mapTemp.clear();
	m_mapNum=0;
}

void CRemotePlaybackDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here	
	*pResult = 0;
	if(m_nPlayHandle >= 0)
	{
		H264_DVR_StopPlayBack(m_nPlayHandle);
		m_nPlayHandle = -1;
	}
	if (m_nPlaybackDecHandle)
	{
		H264_PLAY_CloseStream(m_nPlaybackDecHandle);
		H264_PLAY_Stop(m_nPlaybackDecHandle);
		m_nPlaybackDecHandle = -1;
	}
	Invalidate();
	OnPlay();
}

CString CRemotePlaybackDlg::BrowseForFolder(HWND hWnd)
{
	TCHAR szTitle[] = _T("Select a folder");
	TCHAR szDisplayName[MAX_PATH] = _T("");
	TCHAR szPath[MAX_PATH] = _T("");
	BROWSEINFO bi;
	
	bi.hwndOwner= hWnd;
	bi.pidlRoot= NULL;
	bi.lpszTitle= szTitle;
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

void CRemotePlaybackDlg::OnBUTTONAudio() 
{
	// TODO: Add your control notification handler code here
	H264_PLAY_PlaySoundShare(40);
	
}
