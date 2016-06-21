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
		//pDeviceChannel->Invalidate(TRUE);	
	//	pDeviceChannel->m_sliderbackplay.SetPos( 0 * 1000 );
	//	pDeviceChannel->KillTimer(2);
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
	m_sliderPos=0;
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

	m_strPath = "";
	m_strSaveName = "";
}


void CRemotePlaybackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemotePlaybackDlg)
	DDX_Control(pDX, IDC_SLIDER_BACKPLAY, m_sliderbackplay);
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
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BACKPLAY, OnReleasedcaptureSliderBackplay)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CRemotePlaybackDlg::OnNMCustomdrawProgress1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BACKPLAY, &CRemotePlaybackDlg::OnNMCustomdrawSliderBackplay)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CRemotePlaybackDlg::OnLvnItemchangedList1)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CRemotePlaybackDlg::OnCbnSelchangeComboType)
	ON_WM_PAINT()
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

	m_cmbType.AddString(_CS("PlayBack.AllPic"));
	m_cmbType.AddString(_CS("PlayBack.AlarmRecordPic"));
	m_cmbType.AddString(_CS("PlayBack.DetectRecordPic"));
	m_cmbType.AddString(_CS("PlayBack.GeneralRecordPic"));
	m_cmbType.AddString(_CS("PlayBack.HandRecordPic"));

	m_cmbType.SetCurSel(0);
	
	CTime cur_time = CTime::GetCurrentTime();
	CTime time = CTime(cur_time.GetYear(),cur_time.GetMonth(), cur_time.GetDay(),
		cur_time.GetHour(),cur_time.GetMinute(),cur_time.GetSecond());
	
	m_begData = m_endData = m_endTime = time;
	
	CTime bTime = CTime( cur_time.GetYear(),cur_time.GetMonth(), cur_time.GetDay(), 0 , 0 , 0 );
	m_begTime = bTime;
	
	UpdateData( FALSE );
	
	m_fileList.InsertColumn(0, _CS("PlayBack.NO"),  LVCFMT_LEFT, 50,-1 );
	m_fileList.InsertColumn(1, _CS("PlayBack.File"), LVCFMT_LEFT,450,-1);
	
	m_progress.SetRange(0,100);
	
	
	m_nGetPage=0;
	m_nCurPage=-1;
	m_bOpenAudio = false;
	m_nTotalPage=-1;
	
	m_sliderbackplay.SetPos(0);	
	
	// EXCEPTION: OCX Property Pages should return FALSE
	GetDlgItem(IDC_SLIDER_BACKPLAY)->EnableWindow(FALSE);
	
	m_TimeReplayerView.Create(IDD_DLG_RECORDPERIOD, this);
	m_TimeReplayerView.ShowWindow(SW_SHOW);
	CRect rectTimeReplayer;
	CRect rectSlider;
	m_sliderbackplay.GetWindowRect(&rectSlider);
	ScreenToClient(&rectSlider);
	

	CRect rtWnd;
	GetClientRect(&rtWnd);

	rectTimeReplayer.left = rectSlider.left;
	rectTimeReplayer.top = rectSlider.bottom;
	rectTimeReplayer.right = rectSlider.right;
	rectTimeReplayer.bottom = rtWnd.bottom;
	
	m_TimeReplayerView.MoveWindow(&rectTimeReplayer);	

	
	
	return TRUE;
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
	if (m_Bitmap.m_hObject)
	{
		DeleteObject(m_Bitmap.m_hObject);
	}
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

	if (m_cmbType.GetCurSel()>=5)
	{
		nFileType += 5;
	}
	
	H264_DVR_TIME StartTime;
	H264_DVR_TIME StopTime;
	
	COleDateTime beginTime(m_begData.GetYear(), m_begData.GetMonth(), m_begData.GetDay(),
		m_begTime.GetHour(), m_begTime.GetMinute(), m_begTime.GetSecond());
	COleDateTime endTime(m_endData.GetYear(), m_endData.GetMonth(), m_endData.GetDay(),
		m_endTime.GetHour(), m_endTime.GetMinute(), m_endTime.GetSecond());
	
	if(beginTime >= endTime)//时间错了
	{
		MessageBox(_CS("PlayBack.TimeERROR"));
		return ;
	} 
	
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
		
		GetDlgItem(IDC_SEARCH)->EnableWindow(FALSE);
		H264_DVR_FINDINFO searchInfo;

		int nRet = 0;
		if ( m_bDownloadByTime )
		{
			SDK_SearchByTime searchInfo;
			searchInfo.iSync = FALSE;
			searchInfo.nFileType = nFileType;
			searchInfo.nHighChannel = 0;
			searchInfo.nLowChannel = (0xff & 1 << nChannel);
			searchInfo.stBeginTime.day = StartTime.dwDay;
			searchInfo.stBeginTime.hour = StartTime.dwHour;
			searchInfo.stBeginTime.minute = StartTime.dwMinute;
			searchInfo.stBeginTime.month = StartTime.dwMonth;
			searchInfo.stBeginTime.second = StartTime.dwSecond;
			searchInfo.stBeginTime.year = StartTime.dwYear;
			searchInfo.stEndTime.day = StopTime.dwDay;
			searchInfo.stEndTime.hour = StopTime.dwHour;
			searchInfo.stEndTime.minute = StopTime.dwMinute;
			searchInfo.stEndTime.month = StopTime.dwMonth;
			searchInfo.stEndTime.second = StopTime.dwSecond;
			searchInfo.stEndTime.year = StopTime.dwYear;
			
			SDK_SearchByTimeResult result;
			nRet = H264_DVR_FindFileByTime(m_lLoginID,&searchInfo, &result);

 			if ( nRet > 0 )
 			{
 				m_TimeReplayerView.UpdateTimeSect(result.ByTimeInfo[nChannel].cRecordBitMap);
 			}
							
			nNum = result.nInfoNum;
		}
		else
		{
			unsigned char cRecordBitMap[720] = {0};
			m_TimeReplayerView.UpdateTimeSect(cRecordBitMap);
			searchInfo.nChannelN0 = nChannel;
			searchInfo.nFileType = nFileType;
			memcpy( &searchInfo.startTime, &StartTime, sizeof(searchInfo.startTime));
			memcpy( &searchInfo.endTime, &StopTime, sizeof(searchInfo.endTime));

			nRet = H264_DVR_FindFile(m_lLoginID,&searchInfo,szSend,100,&nNum);
		}
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
			char ch[100]={0};
// 			sprintf(ch,"%s,Error:%d\n",_CS("PlayBack.SearchFail"),
// 				H264_DVR_GetLastError());
			sprintf(ch, "%s,%s\n",_CS("PlayBack.SearchFail"),_CS("PlayBack.NoVideo"));

			MessageBox(ch);
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

void CRemotePlaybackDlg::OnDownloadByName(bool bDown) 
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
	
	m_strSaveName = "";
	//m_strSaveName.Format("c:\\record\\record.h264");
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
	
	if (!bDown)
	{
		CFileDialog dlg( FALSE , strFileTpye, strFileName , OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
			"All File(*.h264;*.jpg)|*.*||" , this );
		dlg.m_ofn.lpstrInitialDir = strInitDir;		//默认路径
		if( dlg.DoModal() == IDOK )
		{
			m_strSaveName = dlg.GetPathName();
			//pstrFileInfo->stBeginTime.second =33;
			//pstrFileInfo->stEndTime.second = 59;
			//m_lSaveHandle = H264_DVR_GetFileByName(m_lLoginID, pstrFileInfo,m_strSaveName.GetBuffer(0),SDKDownLoadPosCallback,(DWORD)this);
			m_lSaveHandle = H264_DVR_GetFileByName(m_lLoginID, pstrFileInfo,m_strSaveName.GetBuffer(0));
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
				if (H264_DVR_GetLastError() < 0)
				{
					AfxMessageBox(_CS("PlayBack.DownloadErro"));
				}
			}
		}
	}else
	{
		m_strPath ="c:\\temp.jpg";
		m_lSaveHandle = H264_DVR_GetFileByName(m_lLoginID, pstrFileInfo,(char*)m_strPath);
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
			//AfxMessageBox(sTemp);
			if(H264_DVR_GetLastError < 0 )
			{
				AfxMessageBox(_CS("PlayBack.DownloadErro"));
			}
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
	if (m_cmbType.GetCurSel()>=5)
	{
		info.nFileType += 5;
	}
	info.startTime.dwYear = 2015;
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
		//AfxMessageBox(sTemp);
		if (H264_DVR_GetLastError() < 0)
		{
			AfxMessageBox(_CS("PlayBack.DownloadError"));
		}
	}
}

void CRemotePlaybackDlg::OnPlay() 
{
	UpdateData();
	
	s_sSlowType = 0;
	s_sFastType = 0;
	GetDlgItem(IDC_SLOW)->SetWindowText(_CS("PlayBack.slow"));
	H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_SLOW, s_sSlowType);
	GetDlgItem(IDC_FAST)->SetWindowText(_CS("PlayBack.Fast"));
	H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_FAST, s_sFastType);

	int nSelectedIndex = m_cmbDevice.GetCurSel();
	if ( nSelectedIndex <= 0 )
	{
		MessageBox(_CS("PlayBack.SelectDevice"));
		return;
	}
	
	if (m_bDownloadByTime)
	{
		
		OnPlayByTime(NULL);
	}
	else
	{
		if (m_cmbType.GetCurSel() < 5)
		{
			OnPlayByName(NULL);
		}
		else
		{
			OnPlayPic();
		}	
	}
	GetDlgItem(IDC_SLIDER_BACKPLAY)->EnableWindow(TRUE);
}

bool static GetBitmapFromPicture(LPCTSTR strFilePath, CBitmap* lpBitmap)
{
	//open file
	HANDLE hFile  =  CreateFile(strFilePath, GENERIC_READ, 0, NULL,
													OPEN_EXISTING, 0 , NULL);
	_ASSERTE(INVALID_HANDLE_VALUE   !=   hFile);   
	
	//   get   file   size   
	DWORD   dwFileSize   =   GetFileSize(hFile,   NULL);   
	_ASSERTE(-1   !=   dwFileSize);   
	
	LPVOID   pvData   =   NULL;   
	//   alloc   memory   based   on   file   size   
	HGLOBAL   hGlobal   =   GlobalAlloc(GMEM_MOVEABLE,   dwFileSize);   
	_ASSERTE(NULL   !=   hGlobal);   
	
	pvData   =   GlobalLock(hGlobal);   
	_ASSERTE(NULL   !=   pvData);   
	
	DWORD   dwBytesRead   =   0;   
	//   read   file   and   store   in   global   memory   
	BOOL   bRead   =   ReadFile(hFile,   pvData,   dwFileSize,   &dwBytesRead,   NULL);   
	_ASSERTE(FALSE   !=   bRead);   
	GlobalUnlock(hGlobal);   
	CloseHandle(hFile);   
	
	LPSTREAM   pstm   =   NULL;   
	//   create   IStream*   from   global   memory   
	HRESULT   hr   =   CreateStreamOnHGlobal(hGlobal,   TRUE,   &pstm);   
	_ASSERTE(SUCCEEDED(hr)   &&   pstm);   
	if ( pstm == NULL )
		return FALSE;

	//   Create   IPicture   from   image   file   
	LPPICTURE   gpPicture;   
	
	hr   =   ::OleLoadPicture(pstm,   dwFileSize,   FALSE,   IID_IPicture,   (LPVOID   *)&gpPicture);   
	if ( gpPicture == NULL )
		return FALSE;

	_ASSERTE(SUCCEEDED(hr)   &&   gpPicture);   
	pstm->Release();   
	
	OLE_HANDLE   m_picHandle;   
	/*   
	long   hmWidth,   hmHeight;   
	gpPicture->get_Width(&hmWidth);   
	gpPicture->get_Height(&hmHeight);   
	int   nWidth =   MulDiv(hmWidth,   GetDeviceCaps(hdc,   LOGPIXELSX),   HIMETRIC_INCH);   
	int   nHeight =   MulDiv(hmHeight,   GetDeviceCaps(hdc,   LOGPIXELSY),   HIMETRIC_INCH);   
	*/   
	gpPicture->get_Handle(&m_picHandle); 
	if (lpBitmap->m_hObject)
	{
		lpBitmap->DeleteObject();  
	}
	
	 
	lpBitmap->Attach((HGDIOBJ)m_picHandle);    

	return TRUE;

}
void CRemotePlaybackDlg::OnPlayPic()
{
	if (m_Bitmap.m_hObject)
	{
		DeleteObject(m_Bitmap.m_hObject);
	}
	OnDownloadByName(true);
}

void  CRemotePlaybackDlg::OnPlayByTime(char* sTime, bool bAgain) 
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
		info.endTime.dwYear = (WORD)m_endData.GetYear();
		info.endTime.dwMonth = (WORD)m_endData.GetMonth();
		info.endTime.dwDay = (WORD)m_endData.GetDay();
		if (bAgain)//第一次回放
		{
			info.startTime.dwHour = (char)m_begTime.GetHour();
			info.startTime.dwMinute = (char)m_begTime.GetMinute();
			info.startTime.dwSecond = (char)m_begTime.GetSecond();

			
		}else
		{
			if (sTime)
			{
				SDK_SYSTEM_TIME* s1 = (SDK_SYSTEM_TIME*)sTime;

				info.startTime.dwHour = s1->hour;
				info.startTime.dwMinute = s1->minute;
				info.startTime.dwSecond = s1->second;
			}
		}
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
			AfxMessageBox(_CS("PlayBack.Fail"));
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
void CRemotePlaybackDlg::OnPlayByName(char* sTime , bool bAgain) 
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
		if (bAgain)//第一次回放
		{
			pstrFileInfo->stBeginTime.hour = (char)m_begTime.GetHour();
			pstrFileInfo->stBeginTime.minute = (char)m_begTime.GetMinute();
			pstrFileInfo->stBeginTime.second = (char)m_begTime.GetSecond();


		}else
		{
			if (sTime)
			{
				SDK_SYSTEM_TIME* s1 = (SDK_SYSTEM_TIME*)sTime;

				pstrFileInfo->stBeginTime.hour = s1->hour;
				pstrFileInfo->stBeginTime.minute = s1->minute;
				pstrFileInfo->stBeginTime.second = s1->second;
			}
		}
		int nitem=m_fileList.GetSelectionMark();
		pstrFileInfo->stEndTime.hour = m_pstrFileVector[nitem]->stEndTime.hour;//(char)m_endTime.GetHour();
		pstrFileInfo->stEndTime.minute = m_pstrFileVector[nitem]->stEndTime.minute;//(char)m_endTime.GetMinute();
		pstrFileInfo->stEndTime.second =m_pstrFileVector[nitem]->stEndTime.second; //(char)m_endTime.GetSecond();
		
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
	SetTimer(2,1000,NULL);
}

void CRemotePlaybackDlg::OnStop() 
{
	KillTimer(2);
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
	m_sliderbackplay.SetPos( 0 * 1000 );
 	m_bPause=FALSE;
	m_bOpenAudio=false;
	SetDlgItemText(IDC_BUTTON_Audio,_CS("PlayBack.OpenAudio"));
	Invalidate();

	GetDlgItem(IDC_SLIDER_BACKPLAY)->EnableWindow(FALSE);
	UpdateWindow();
}

void CRemotePlaybackDlg::OnFast() 
{
	s_sSlowType = 0;
	GetDlgItem(IDC_SLOW)->SetWindowText(_CS("PlayBack.slow"));
	H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_SLOW, s_sSlowType);
	if (++s_sFastType > 4)
	{
		s_sFastType = 1;
	}
	CString temp;
	temp.Format("%d",s_sFastType);
	GetDlgItem(IDC_FAST)->SetWindowText(_CS("PlayBack.Fast") + _CS(temp));
	H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_FAST, s_sFastType);
	H264_PLAY_Fast(m_nPlaybackDecHandle);
}

void CRemotePlaybackDlg::OnSlow() 
{
	s_sFastType = 0;
	GetDlgItem(IDC_FAST)->SetWindowText(_CS("PlayBack.Fast"));
	H264_DVR_PlayBackControl(m_nPlayHandle, SDK_PLAY_BACK_FAST, s_sFastType);
	if (++s_sSlowType > 4)
	{
		s_sSlowType = 1;
	}
	CString temp;
	temp.Format("%d",s_sSlowType);
	GetDlgItem(IDC_SLOW)->SetWindowText(_CS("PlayBack.Slow") + _CS(temp));
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
	
	//vector<H264_DVR_FILE_DATA*>::iterator p=m_pstrFileVector.begin();
// 	while( p!=m_pstrFileVector.end())
// 	{
// 		H264_DVR_FILE_DATA* pData = (*p);
// 		if(pData)
// 			delete pData;
// 		pData = NULL;
// 		p++;		
// 	}
	vector<H264_DVR_FILE_DATA*>::iterator p=m_pstrFileVector.begin();
	if ( p!=m_pstrFileVector.end())
	{
		H264_DVR_FILE_DATA* pData = (*p);
		delete pData;
		pData = NULL;
	}
	if (m_nPlayHandle)
	{
		H264_DVR_StopPlayBack(m_nPlayHandle);
		m_nPlayHandle=-1;
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
	if(nIDEvent==2)
	{	
		if(m_nPlayHandle == -1)
			exit;
		float pos = H264_DVR_GetPlayPos(m_nPlayHandle);
		SetSliderPos(pos);
		if(pos == 1)
			KillTimer(2);
		DWORD playtime=H264_PLAY_GetPlayedTime(40);
		
		if ( m_preTime > 0 )
		{
			DWORD dwTime = GetTickCount();
			if ( (dwTime - m_preTime) >= 2000 )
			{
				m_sliderbackplay.SetPos( playtime );
				
				m_preTime = 0;
			}
		}
		else
		{
			m_sliderbackplay.SetPos( playtime);
		}
		CDialog::OnTimer(nIDEvent);
	}
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
		else if(nPos == 100)		//download end
		{
			H264_DVR_StopGetFile(m_lSaveHandle);
			m_lSaveHandle = -1;
			KillTimer(1);
			m_progress.SetPos(0);
			GetDlgItem(IDC_DOWNLOAD)->SetWindowText(_CS("PlayBack.Download"));
			if (!m_bDown)
			{
					AfxMessageBox(_CS("PlayBack.DownloadFinish"));
			}else
			{
					GetBitmapFromPicture(m_strPath, &m_Bitmap);
					RedrawWindow();
			}

			//exit;
		}
		else if(nPos > 100)		//abnormal
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
	SetDlgItemText(IDC_BUTTON_Audio,_CS("PlayBack.OpenAudio"));
	m_bOpenAudio=false;
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
	if (m_cmbType.GetCurSel() >= 5)
	{
		m_bDown = true;
	}else
	{
		m_bDown = false;
	}
	OnPlay();
	//得到录像总时间，单位/s
	int nitem=m_fileList.GetSelectionMark();//
	int byear=m_pstrFileVector[nitem]->stBeginTime.year;
	int bmonth=m_pstrFileVector[nitem]->stBeginTime.month;
	int bday=m_pstrFileVector[nitem]->stBeginTime.day;
	int bhour=m_pstrFileVector[nitem]->stBeginTime.hour;
	int bminute=m_pstrFileVector[nitem]->stBeginTime.minute;
	int bsecond=m_pstrFileVector[nitem]->stBeginTime.second;

	int nyear=m_pstrFileVector[nitem]->stEndTime.year;
	int nmonth=m_pstrFileVector[nitem]->stEndTime.month;
	int nday=m_pstrFileVector[nitem]->stEndTime.day;
	int nhour=m_pstrFileVector[nitem]->stEndTime.hour;
	int nminute=m_pstrFileVector[nitem]->stEndTime.minute;
	int nsecond=m_pstrFileVector[nitem]->stEndTime.second;
	
	totaltime=(nyear-byear)*365*24*3600+(nmonth-bmonth)*30*24*3600+(nday-bday)*24*3600
              +(nhour-bhour)*3600+(nminute-bminute)*60+(nsecond-bsecond);	       
	m_sliderbackplay.SetRange(0,totaltime);
	unsigned char cRecordBitMap[720] = {0};
	if (m_bDownloadByName)
	{
		int ibyte = 0;
		if (nhour == 0 & nminute == 0)
		{
			ibyte = 0;
		}
		else	
			ibyte = (bhour * 60 + bminute) / 2 ;
		for (int i =0;i < totaltime/120;++i )
		{
			cRecordBitMap[ibyte] = 85;
			++ibyte;			   
		}

		m_TimeReplayerView.UpdateTimeSect(cRecordBitMap);
	}

// 	if (m_bDownloadByTime)
// 	{
// 		int ibyte = 0;
// 		if (nhour == 0 & nminute == 0)
// 		{
// 			ibyte = 0;
// 		}
// 		else	
// 			ibyte = (bhour * 60 + bminute) / 2 ;
// 		for (int i =0;i < totaltime/120;++i )
// 		{
// 			cRecordBitMap[ibyte] = 85;
// 			++ibyte;			   
// 		}
// 	}
	
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
	//H264_PLAY_PlaySoundShare(40);
	if(m_nPlayHandle)
	{
		if (!m_bOpenAudio)
		{
			if(	H264_PLAY_PlaySoundShare(40))
			{

				SetDlgItemText(IDC_BUTTON_Audio,_CS("PlayBack.CloseAudio"));
				m_bOpenAudio=true;
			}
		}
		else
		{
			if(	H264_PLAY_StopSoundShare(40))
			{
				SetDlgItemText(IDC_BUTTON_Audio,_CS("PlayBack.OpenAudio"));
				m_bOpenAudio=false;
			}
		}
	}
}

void CRemotePlaybackDlg::OnReleasedcaptureSliderBackplay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_sliderPos=m_sliderbackplay.GetPos();
	
	m_preTime=GetTickCount();
	float a=(float)(((float)m_sliderPos)/((float)totaltime));
	H264_DVR_SetPlayPos( m_nPlayHandle ,a);
	H264_PLAY_SetPlayPos(40, a);
	*pResult = 0;
}

void CRemotePlaybackDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CRemotePlaybackDlg::OnNMCustomdrawSliderBackplay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
// 	m_sliderPos = m_sliderbackplay.GetPos();
// 	m_preTime = GetTickCount();
// 	H264_DVR_SetPlayPos(m_nPlayHandle,(float)m_sliderPos / 1000.0);
	*pResult = 0;
}

void CRemotePlaybackDlg::SetSliderPos(float nplaypos)
{
	if(m_preTime > 0)
	{
		DWORD dwTime = GetTickCount();
		if((dwTime - m_preTime) > 2000)
		{
			m_sliderbackplay.SetPos(nplaypos * 1000);
			m_preTime = 0;
		}
		else
		{
			m_sliderbackplay.SetPos(nplaypos * 1000);
		}
	}
}
void CRemotePlaybackDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CRemotePlaybackDlg::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CRemotePlaybackDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	if (m_Bitmap.m_hObject)
	{
		CRect rt;
		m_videoWnd.GetWindowRect(&rt);
		ScreenToClient(&rt);
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);//创建与内存中表面相关联的DC
		CBitmap * oldBitmap = memDC.SelectObject(&m_Bitmap);//选择对象到memDC
		BITMAP bp;
		GetObject(m_Bitmap.m_hObject, sizeof(bp), &bp);
		dc.StretchBlt(rt.left, rt.top + 10, rt.Width()-10, rt.Height() - 10,&memDC,
			0, 0, bp.bmWidth, bp.bmHeight, SRCCOPY);
		memDC.SelectObject(oldBitmap);
		DeleteDC(memDC);
	}
}
