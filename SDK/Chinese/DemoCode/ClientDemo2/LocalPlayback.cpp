// LocalPlayback.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "LocalPlayback.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalPlayback dialog


CLocalPlayback::CLocalPlayback(CWnd* pParent /*=NULL*/)
	: CDialog(CLocalPlayback::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocalPlayback)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pFile = NULL;
	m_hPlayThread = NULL;

	for ( int i = 0; i < 100; i ++)
	{
		m_strInfoFrame[i] = "";
	}
}


void CLocalPlayback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalPlayback)
	DDX_Control(pDX, IDC_SLIDERFILE, m_ctrlSlider);
	DDX_Control(pDX, IDC_STATIC_PLAYWINDOW, m_playwindow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalPlayback, CDialog)
	//{{AFX_MSG_MAP(CLocalPlayback)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_FAST, OnButtonFast)
	ON_BN_CLICKED(IDC_BUTTON_SLOW, OnButtonSlow)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERFILE, OnReleasedcaptureSliderfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalPlayback message handlers

BOOL CLocalPlayback::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);

	m_nPort = 90;
	m_bplaythread = false;
	m_PlayerStatus =STATUS_READY;
	m_FastSpeed = 0;
	m_SlowSpeed = 0;
	m_nFileLen = 0;

	m_ctrlSlider.SetRange(0,1000);
	m_SliderPos = 0;
	m_ctrlSlider.SetPos(0);

	m_PreTime = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLocalPlayback::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK)
	{
		m_FilePathName=dlg.GetPathName();
		m_PlayerStatus=STATUS_STOP;
		m_bplaythread=false;
		H264_PLAY_CloseFile(m_nPort);
		H264_PLAY_CloseStream(m_nPort);
		H264_PLAY_Stop(m_nPort);
		m_FastSpeed=0;
		GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast"));
		m_SlowSpeed=0;
		GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow"));
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_CS("PlayBack.Pause"));
		OnButtonPlay();
	}
}

void __stdcall CLocalPlayback::SDKPlayFileEndCallback(LONG nPort,LONG nUser)
{
	CLocalPlayback * p = (CLocalPlayback*)nUser;
	if ( NULL == p )
	{
		return;
	}
	
	p->PlayEndCallback(nPort);
}
void CLocalPlayback::PlayEndCallback(int nPort)
{
	CRect rect;
	KillTimer(1);
	m_ctrlSlider.SetPos(0);
	GetClientRect(&rect);
	InvalidateRect(rect);
}
void CALLBACK FileRefDone(LONG nReserved,LONG nUser)
{
}
void __stdcall CLocalPlayback::InfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser)
{
	CLocalPlayback *pThis = (CLocalPlayback*)nUser;
	//收到信息帧, 0x03 代表GPRS信息
	if ( nType == 0x03 )
	{
		pThis->m_strInfoFrame[nPort] = pBuf;
	}
}

void CALLBACK PlaybackdrawOSDCall(LONG nPort,HDC hDc,LONG nUser)
{
	CLocalPlayback *pThis = (CLocalPlayback*)nUser;
	pThis->drawOSD(nPort,hDc);
}

void CLocalPlayback::drawOSD(LONG nPort,HDC hDc)
{
	if ( m_strInfoFrame[nPort] != "" )
	{
		HFONT oldfont;
		oldfont = (HFONT)::GetCurrentObject( hDc, OBJ_FONT );
		
		
		//改变字体颜色
		::SetTextColor( hDc, RGB(255,0,0) );
		
		//更改字体
		LOGFONT lf;
		::GetObject( oldfont, sizeof(lf), &lf );
		strcpy( lf.lfFaceName, "Arial" );
		lf.lfWeight = FW_BOLD;
		HFONT out_ft;		//创建的字体对象
		out_ft = ::CreateFontIndirect( &lf );
		
		::SelectObject( hDc, out_ft );
		
		TextOut( hDc, 10, 10, m_strInfoFrame[nPort], m_strInfoFrame[nPort].GetLength() );
		
		::SelectObject( hDc, oldfont );
	}
}

void CLocalPlayback::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
	if(m_PlayerStatus==STATUS_STOP)
	{
		m_bplaythread=true;

		H264_PLAY_SetFileRefCallBack(m_nPort, FileRefDone, (DWORD)this);
		
		if(H264_PLAY_OpenFile(m_nPort, m_FilePathName))
		{
			H264_PLAY_SetInfoFrameCallBack(m_nPort, InfoFramCallback,(DWORD)this);

			m_TotalTime = H264_PLAY_GetFileTime( m_nPort); // Total play time
			
			H264_PLAY_SetFileEndCallBack(m_nPort,SDKPlayFileEndCallback,(DWORD)this);
			
			H264_PLAY_RigisterDrawFun(m_nPort, PlaybackdrawOSDCall, (DWORD)this);
			if(H264_PLAY_Play(m_nPort,m_playwindow.m_hWnd)==false)
			{
				MessageBox(_CS("Error.PlayFailed"));
				return;
			}

			GetDlgItem(IDC_SLIDERFILE)->EnableWindow(TRUE);
		}
		else
		{
			int nErr=H264_PLAY_GetLastError(m_nPort);
			if(nErr == H264_PLAY_CHECK_FILE_ERROR)
			{
				MessageBox(_CS("Error.CheckFileError"));
			}
			else
			{
				MessageBox(_CS("Error.OpenFileFail"));
			}
			return;
		}

	/*	DWORD dwThreadID;
		if ( m_hPlayThread )
		{
			CloseHandle(m_hPlayThread); //close the Thread
			m_hPlayThread = NULL;
		}

		m_hPlayThread = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)StartPlay, this , 0, &dwThreadID );
		if ( m_hPlayThread == NULL )
		{
			return;
		}*/

		m_PlayerStatus=STATUS_PLAY;
	}
	else if(m_PlayerStatus==STATUS_FAST||m_PlayerStatus==STATUS_SLOW)
	{
		H264_PLAY_Play(m_nPort,m_playwindow.m_hWnd);
		m_PlayerStatus=STATUS_PLAY;
		m_FastSpeed=0;
		GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast"));
		m_SlowSpeed=0;
		GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow"));
	}
	else if(m_PlayerStatus==STATUS_PAUSE)
	{
		H264_PLAY_Pause(m_nPort,FALSE);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_CS("PlayBack.Pause"));
		m_PlayerStatus=STATUS_PLAY;
	}
	
	SetTimer(1,1000,NULL);
}

void CLocalPlayback::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bplaythread=false;
	m_PlayerStatus=STATUS_STOP;
	H264_PLAY_CloseFile(m_nPort);
	H264_PLAY_CloseStream(m_nPort);
	H264_PLAY_Stop(m_nPort);
	m_FastSpeed=0;
	GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast"));
	m_SlowSpeed=0;
	GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow"));
	GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_CS("PlayBack.Pause"));

	if ( m_hPlayThread )
	{
		CloseHandle(m_hPlayThread); //close the Thread
	}

	KillTimer(1);
	GetDlgItem(IDC_SLIDERFILE)->EnableWindow(FALSE);
	Invalidate(TRUE);
}

void CLocalPlayback::OnButtonPause() 
{
	// TODO: Add your control notification handler code here
	if(m_PlayerStatus==STATUS_PLAY||m_PlayerStatus==STATUS_SLOW||m_PlayerStatus==STATUS_FAST)
	{
		H264_PLAY_Pause(m_nPort,TRUE);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_CS("PlayBack.Recover"));
		m_PlayerStatus=STATUS_PAUSE;
		GetDlgItem(IDC_SLIDERFILE)->EnableWindow(FALSE);
	}
	else if(m_PlayerStatus==STATUS_PAUSE)
	{
		H264_PLAY_Pause(m_nPort,FALSE);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_CS("PlayBack.Pause"));
		m_PlayerStatus=STATUS_PLAY;
		GetDlgItem(IDC_SLIDERFILE)->EnableWindow(TRUE);
	}
}

void CLocalPlayback::OnButtonFast() 
{
	// TODO: Add your control notification handler code here
	if(m_PlayerStatus==STATUS_PLAY||m_PlayerStatus==STATUS_FAST||m_PlayerStatus==STATUS_SLOW)
	{
		if(m_PlayerStatus==STATUS_SLOW)
		{
			H264_PLAY_Play(m_nPort,m_playwindow.m_hWnd);
			m_SlowSpeed=0;
			GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow"));
		}
		if(m_FastSpeed<4)
		{
			H264_PLAY_Fast(m_nPort);
			m_FastSpeed++;
			CString temp;
			temp.Format("%d",m_FastSpeed);
			GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast")+_T(temp));
			m_PlayerStatus=STATUS_FAST;
		}
		else
		{
			m_FastSpeed=0;
			H264_PLAY_Play(m_nPort,m_playwindow.m_hWnd);
			H264_PLAY_Fast(m_nPort);
			m_FastSpeed++;
			CString temp;
			temp.Format("%d",m_FastSpeed);
			GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast")+_T(temp));
			m_PlayerStatus=STATUS_FAST;
		}
		GetDlgItem(IDC_SLIDERFILE)->EnableWindow(TRUE);
	}
}

void CLocalPlayback::OnButtonSlow() 
{
	// TODO: Add your control notification handler code here
	if(m_PlayerStatus==STATUS_PLAY||m_PlayerStatus==STATUS_SLOW||m_PlayerStatus==STATUS_FAST)
	{
		if(m_PlayerStatus==STATUS_FAST)
		{
			H264_PLAY_Play(m_nPort,m_playwindow.m_hWnd);
			m_FastSpeed=0;
			GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast"));
		}
		if(m_SlowSpeed<4)
		{
			H264_PLAY_Slow(m_nPort);
			m_PlayerStatus=STATUS_SLOW;
			m_SlowSpeed++;
			CString temp;
			temp.Format("%d",m_SlowSpeed);
			GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow")+_T(temp));
		}
		else
		{
			m_SlowSpeed=0;
			H264_PLAY_Play(m_nPort,m_playwindow.m_hWnd);
			H264_PLAY_Slow(m_nPort);
			m_PlayerStatus=STATUS_SLOW;
			m_SlowSpeed++;
			CString temp;
			temp.Format("%d",m_SlowSpeed);
			GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow")+_T(temp));
			
		}
		GetDlgItem(IDC_SLIDERFILE)->EnableWindow(TRUE);
	}
}


unsigned int CLocalPlayback::StartPlay(LPVOID parm)
{
	CLocalPlayback *pThis = ( CLocalPlayback* ) parm;
	H264_PLAY_SetFileRefCallBack(pThis->m_nPort, FileRefDone, (DWORD)parm);

	if(H264_PLAY_OpenFile(pThis->m_nPort,pThis->m_FilePathName))
	{
		pThis->m_TotalTime = H264_PLAY_GetFileTime( pThis->m_nPort); // Total play time
		
		H264_PLAY_SetFileEndCallBack(pThis->m_nPort,SDKPlayFileEndCallback,(DWORD)parm);

		if(H264_PLAY_Play(pThis->m_nPort,pThis->m_playwindow.m_hWnd)==false)
		{
			pThis->MessageBox(_CS("Error.PlayFailed"));
			return 0;
		}
	}
	else
	{
		int nErr=H264_PLAY_GetLastError(pThis->m_nPort);
		if(nErr == H264_PLAY_CHECK_FILE_ERROR)
		{
			pThis->MessageBox(_CS("Error.CheckFileError"));
		}
		else
		{
			pThis->MessageBox(_CS("Error.OpenFileFail"));
		}
		return 0;
	}
	//start:modify by fanguanggao 2011.7.4
//	pThis->m_pFile = fopen(pThis->m_FilePathName, "rb");
//	
//	if ( pThis->m_pFile )
//	{
//	}else{
//		return 0;
//	}
//	fseek(pThis->m_pFile, 0, SEEK_END);
//	pThis->m_nFileLen = ftell(pThis->m_pFile);  //the file's length
//	fseek(pThis->m_pFile, pThis->m_SliderPos * pThis->m_nFileLen / 100, SEEK_SET);
//	//fseek(pThis->m_pFile, 0, SEEK_SET);
//	
//	BYTE pBuf[32 * 1024];
//	while (pThis->m_bplaythread)
//	{
//		int len = fread(pBuf, 1, 32 * 1024, pThis->m_pFile);
//		if (len <= 0)
//		{
//			break;
//		}
//		while(H264_PLAY_InputData(pThis->m_nPort, pBuf, len) == FALSE)
//		{
//			Sleep(40);
//		}
//	}
//	
//	fclose(pThis->m_pFile);
//	pThis->m_pFile = NULL;

	//end:modify by fanguanggao 2011.7.4
	return 1;
}

void CLocalPlayback::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_bplaythread=false;
	m_PlayerStatus=STATUS_STOP;
	H264_PLAY_CloseFile(m_nPort);
	H264_PLAY_CloseStream(m_nPort);
	
	KillTimer(1);
	CloseHandle(m_hPlayThread);
	CDialog::OnClose();
}

//modify by fanguanggao 2011.7.4
void CLocalPlayback::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	time_t pos = H264_PLAY_GetPlayedTime( m_nPort );
//	if ( pos == m_TotalTime )
//	{
//		long lBufVal = H264_PLAY_GetSourceBufferRemain(m_nPort);
//		long lYuvVal = H264_PLAY_GetBufferValue(m_nPort, BUF_VIDEO_RENDER);
//		if ( 0 == lBufVal && 0 == lYuvVal)
//		{
//			//m_ctrlSlider.SetPos(0);
//			SetSliderPos(0);
//			//Invalidate();
//		}
//	}else
//	{
//		//m_ctrlSlider.SetPos( pos * 1000 / m_TotalTime );
//		SetSliderPos(pos);
//	}

	float pos = H264_PLAY_GetPlayPos( m_nPort );
	//m_ctrlSlider.SetPos( pos * 100);

	int nTime = H264_PLAY_GetPlayedTimeEx( m_nPort );
	CString strTmp;
	strTmp.Format("time = %d", nTime);
	OutputDebugString(strTmp);

	SetSliderPos(pos);
	CDialog::OnTimer(nIDEvent);
}

void CLocalPlayback::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
/*	m_SliderPos = m_ctrlSlider.GetPos();
	m_PreTime = GetTickCount();
	
	H264_PLAY_ResetBuffer(m_nPort, BUF_VIDEO_RENDER);
	H264_PLAY_ResetBuffer(m_nPort, BUF_VIDEO_SRC);
	H264_PLAY_ResetSourceBuffer(m_nPort);
	
//	Sleep(40);
	
	if ( m_pFile )
	{
		fseek( m_pFile , m_SliderPos * m_nFileLen /100 ,SEEK_SET);
	}else
	{
		m_bplaythread=false;
		m_PlayerStatus=STATUS_STOP;
		H264_PLAY_CloseFile(m_nPort);
		H264_PLAY_CloseStream(m_nPort);
		H264_PLAY_Stop(m_nPort);
		if ( m_hPlayThread )
		{
			CloseHandle( m_hPlayThread );
			m_hPlayThread = NULL;
		}
		
		DWORD dwThreadID;
		m_bplaythread=true;
		m_hPlayThread = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)StartPlay, this , 0, &dwThreadID );
		if ( m_hPlayThread == NULL)
		{
			return;
		}
	}*/

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CLocalPlayback::SetSliderPos(float nplaypos)
{
	if ( m_PreTime > 0 )
	{
		DWORD dwTime = GetTickCount();
		if ( (dwTime - m_PreTime) >= 2000 )
		{
			m_ctrlSlider.SetPos( nplaypos * 1000 );
			
			m_PreTime = 0;
		}
	}
	else
	{
		m_ctrlSlider.SetPos( nplaypos * 1000 );
	}
}

void CLocalPlayback::OnReleasedcaptureSliderfile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_SliderPos = m_ctrlSlider.GetPos();
	m_PreTime = GetTickCount();
	
//	H264_PLAY_ResetBuffer(m_nPort, BUF_VIDEO_RENDER);
//	H264_PLAY_ResetBuffer(m_nPort, BUF_VIDEO_SRC);
//	H264_PLAY_ResetSourceBuffer(m_nPort);
//	
//	if ( m_pFile )
//	{
//		fseek( m_pFile , m_SliderPos * m_nFileLen /1000 ,SEEK_SET);
//	}else
//	{
//		m_bplaythread=false;
//		m_PlayerStatus=STATUS_STOP;
//		H264_PLAY_CloseFile(m_nPort);
//		H264_PLAY_CloseStream(m_nPort);
//		H264_PLAY_Stop(m_nPort);
//		if ( m_hPlayThread )
//		{
//			CloseHandle( m_hPlayThread );
//			m_hPlayThread = NULL;
//		}
//		
//		DWORD dwThreadID;
//		m_bplaythread=true;
//		m_hPlayThread = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)StartPlay, this , 0, &dwThreadID );
//		if ( m_hPlayThread == NULL)
//		{
//			return;
//		}
//	}

	H264_PLAY_SetPlayPos( m_nPort , (float)m_SliderPos / 1000.0);
	*pResult = 0;
}
