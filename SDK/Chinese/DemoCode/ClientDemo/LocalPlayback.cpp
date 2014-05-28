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
	/*m_pFile = NULL;*/
	/*m_hPlayThread = NULL;*/
	
	
	m_playHandle=NULL;
	m_bPause=false;
	m_bAudioOpen=false;	
	m_bSlowType=0;
	m_bFastType=0;
	
}
CLocalPlayback::~CLocalPlayback()
{
	if(m_playHandle)
		H264_DVR_StopLocalPlay(m_playHandle);
	KillTimer(1);	
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
ON_BN_CLICKED(IDC_BUTTON_AUDIO, OnButtonAudio)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalPlayback message handlers

BOOL CLocalPlayback::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	
	// 	m_nPort = 90;
	// 	m_bplaythread = false;
	m_ctrlSlider.SetRange(0,1000);
	m_SliderPos = 0;
	m_ctrlSlider.SetPos(0);
	
	m_PreTime = 0;

    GetDlgItem(IDC_SLIDERFILE)->EnableWindow(FALSE); //HW
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CALLBACK PlaybackdrawOSDCall(LONG playHandle,HDC hDc,LONG nUser)
{
	CLocalPlayback *pThis = (CLocalPlayback*)nUser;
	pThis->drawOSD(playHandle,hDc);
}
void CLocalPlayback::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK)
	{
		m_FilePathName=dlg.GetPathName();		
		if(m_playHandle!=NULL)
		{
			H264_DVR_StopLocalPlay(m_playHandle);
		}		
		GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast"));
		GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow"));
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_CS("PlayBack.Pause"));
		SetDlgItemText(IDC_BUTTON_AUDIO,_CS("PlayBack.OpenAudio"));
		m_bAudioOpen=false;
		m_playHandle=H264_DVR_StartLocalPlay(m_FilePathName.GetBuffer(0),m_playwindow.m_hWnd,PlaybackdrawOSDCall,(long)this);
		if(m_playHandle)
		{	
			m_bPause=false;
			m_bSlowType=false;
			m_bFastType=false;
			H264_DVR_SetFileEndCallBack(m_playHandle,SDKPlayFileEndCallback,(long)this);
			H264_DVR_SetInfoFrameCallBack(m_playHandle,InfoFramCallback,(DWORD)this);	
		}
		else
		{
			AfxMessageBox("Playwrong");
		}
	  
		GetDlgItem(IDC_SLIDERFILE)->EnableWindow(TRUE); //HW
		SetTimer(1,1000,NULL);
	}
}

void __stdcall CLocalPlayback::SDKPlayFileEndCallback(LONG playHandle,LONG nUser)
{
	CLocalPlayback * p = (CLocalPlayback*)nUser;
	if ( NULL == p )
	{
		return;
	}
	
	p->PlayEndCallback(playHandle);
}
void CLocalPlayback::PlayEndCallback(int playHandle)
{
	CRect rect;
	m_playHandle=0;
	SetDlgItemText(IDC_BUTTON_AUDIO,_CS("PlayBack.OpenAudio"));
	m_bAudioOpen=false;
	m_ctrlSlider.SetPos( 0 * 1000 );
	GetClientRect(&rect);
	InvalidateRect(rect);
	
}
void CALLBACK FileRefDone(LONG nReserved,LONG nUser)
{
}
void __stdcall CLocalPlayback::InfoFramCallback(LONG playHandle, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser)
{
	CLocalPlayback *pThis = (CLocalPlayback*)nUser;
	//收到信息帧, 0x03 代表GPRS信息
	if ( nType == 0x03 )
	{
		pThis->m_strInfoFrame[playHandle] = pBuf;
	}
}



void CLocalPlayback::drawOSD(LONG playHandle,HDC hDc)
{
    //HW//m_strInfoFrame[playHandle]="asfasf";
	if ( m_strInfoFrame[playHandle] != "" )
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
		TextOut( hDc, 10, 10, m_strInfoFrame[playHandle], m_strInfoFrame[playHandle].GetLength() );		
		::SelectObject( hDc, oldfont );
	}
}

void CLocalPlayback::OnButtonPlay() 
{		
	if(m_bPause)
	{
		H264_DVR_LocalPlayCtrl(m_playHandle,SDK_Local_PLAY_CONTINUE,0);	
		m_bPause=false;
	}
	
	if(m_bSlowType)
	{
		H264_DVR_LocalPlayCtrl(m_playHandle,SDK_Local_PLAY_SLOW,0);	
	}
	if(m_bFastType)
	{
		H264_DVR_LocalPlayCtrl(m_playHandle,SDK_Local_PLAY_FAST,0);	
	}
	m_bSlowType=0;
	m_bFastType=0;
	
    GetDlgItem(IDC_SLIDERFILE)->EnableWindow(TRUE); //HW
	
}

void CLocalPlayback::OnButtonStop() 
{
	SetDlgItemText(IDC_BUTTON_AUDIO,_CS("PlayBack.OpenAudio"));
	m_bAudioOpen=false;		
	m_ctrlSlider.SetPos( 0 * 1000 );
	if(H264_DVR_StopLocalPlay(m_playHandle))
	{
		m_playHandle=NULL;
		
	}	
	GetDlgItem(IDC_BUTTON_FAST)->SetWindowText(_CS("PlayBack.Fast"));	
	GetDlgItem(IDC_BUTTON_SLOW)->SetWindowText(_CS("PlayBack.Slow"));
	GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_CS("PlayBack.Pause"));				
	KillTimer(1);
	Invalidate(TRUE);

	GetDlgItem(IDC_SLIDERFILE)->EnableWindow(FALSE); //HW
}

void CLocalPlayback::OnButtonPause() 
{
	if(!m_bPause)
	{
		if(H264_DVR_LocalPlayCtrl(m_playHandle,SDK_Local_PLAY_PAUSE,0))
		{
			m_bPause=TRUE;
		}
	}
	
}

void CLocalPlayback::OnButtonFast() 
{
	if (++m_bFastType > 4)
	{
		m_bFastType = 1;
	}
	m_bSlowType = 0;
	H264_DVR_LocalPlayCtrl(m_playHandle,SDK_Local_PLAY_FAST,m_bFastType);	
}

void CLocalPlayback::OnButtonSlow() 
{	
	
	if (++m_bSlowType > 4)
	{
		m_bSlowType = 1;
	}
	m_bFastType = 0;
	H264_DVR_LocalPlayCtrl(m_playHandle,SDK_Local_PLAY_SLOW,m_bSlowType);	
}


unsigned int CLocalPlayback::StartPlay(LPVOID parm)
{	
	return 1;
}

void CLocalPlayback::OnClose() 
{
	
	if(m_playHandle)
	{		
		H264_DVR_StopLocalPlay(m_playHandle);		
	}
	KillTimer(1);	
	CDialog::OnClose();
}
void CLocalPlayback::OnTimer(UINT nIDEvent) 
{	
	float pos =H264_DVR_GetPlayPos(m_playHandle);
	SetSliderPos(pos);
	CDialog::OnTimer(nIDEvent);
}

void CLocalPlayback::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
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
	H264_DVR_SetPlayPos( m_playHandle , (float)m_SliderPos / 1000.0);
	*pResult = 0;
}

void CLocalPlayback::OnButtonAudio() 
{
	// TODO: Add your control notification handler code here
	if(m_playHandle)
	{
		if(!m_bAudioOpen)
		{
			if(H264_DVR_OpenSound(m_playHandle))
			{
				SetDlgItemText(IDC_BUTTON_AUDIO,_CS("PlayBack.CloseAudio"));
				m_bAudioOpen=true;
			}
			
		}
		else
		{
			if(H264_DVR_CloseSound(m_playHandle))
			{
				SetDlgItemText(IDC_BUTTON_AUDIO,_CS("PlayBack.OpenAudio"));
				m_bAudioOpen=false;
			}
			
		}
		
	}
	
	
}
