// VideoWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "VideoWnd.h"
#include "ClientDemoDlg.h"
#include <direct.h>
#include <IO.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoWnd dialog


CVideoWnd::CVideoWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nIndex = -1;
	m_iPlayhandle = -1;	
	m_bRecord = FALSE;
	m_bSound=false;

	for ( int i = 0; i < 100; i ++)
	{
		m_strInfoFrame[i] = "";
	}
}


void CVideoWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoWnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoWnd, CDialog)
	//{{AFX_MSG_MAP(CVideoWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_DISCONNECT, OnDisconnct)
	ON_COMMAND(ID_DEVICE_OPENSOUND, OnOpenSound)
	ON_COMMAND(ID_DEVICE_CLOSESOUND, OnCloseSound)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoWnd message handlers
int __stdcall RealDataCallBack(long lRealHandle, 
							   long dwDataType, unsigned char *pBuffer,
												long lbufsize,long dwUser)
{
	CVideoWnd *pDataChnl = (CVideoWnd*)dwUser;
	

	return 1;
}

int __stdcall RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, unsigned int dwUser)
{
	CVideoWnd *pDataChnl = (CVideoWnd*)dwUser;
	

#if 0
	if (pFrame->nPacketType == AUDIO_PACKET)
	{
		FILE *fp = fopen("stream/AudioTotal.pcm", "ab+");
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
	return 1;
}

void CVideoWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	

}

void CVideoWnd::OnDisconnct()
{
	if (m_iPlayhandle > 0)
	{
		
		H264_DVR_StopRealPlay(m_iPlayhandle,m_hWnd);
		m_iPlayhandle = -1;
		
	}
	if(m_bSound)
	{
		OnCloseSound();
	}	
	m_lLogin = -1;
}

void CVideoWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
	if ( pParent  )
	{
		SoundChangeWnd(pParent->m_nCurIndex,&pParent->m_videoWnd[pParent->m_nCurIndex]);
		pParent->SetActiveWnd(m_nIndex);
	}
	CDialog::OnLButtonDown(nFlags, point);
}


void CVideoWnd::drawOSD(LONG nPort,HDC hDc)
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

		TextOut( hDc, 10, 10, "testtesttest", strlen("testtesttest") );

		::SelectObject( hDc, oldfont );
	}
}

void __stdcall CVideoWnd::videoInfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser)
{
 	CVideoWnd *pThis = (CVideoWnd*)nUser;
 	//收到信息帧, 0x03 代表GPRS信息
 	if ( nType == 0x03 )
 	{
 		pThis->m_strInfoFrame[nPort] = pBuf;
 	}
}

int CVideoWnd::ConnectRealPlay(DEV_INFO *pDev, int nChannel)
{
	if(m_iPlayhandle != -1)
	{			
		
		if(!H264_DVR_StopRealPlay(m_iPlayhandle,m_hWnd))
		{
			TRACE("H264_DVR_StopRealPlay fail m_iPlayhandle = %d", m_iPlayhandle);
		}
		if(m_bSound)
		{
			OnCloseSound();
		}
	}

	H264_DVR_CLIENTINFO playstru;

	playstru.nChannel = nChannel;
	playstru.nStream = 0;
	playstru.nMode = 0;
	playstru.hWnd=this->m_hWnd;
	m_iPlayhandle = H264_DVR_RealPlay(pDev->lLoginID, &playstru);	
	if(m_iPlayhandle <= 0 )
	{
		DWORD dwErr = H264_DVR_GetLastError();	
			CString sTemp("");
			sTemp.Format("access %s channel%d fail, dwErr = %d",pDev->szDevName,nChannel, dwErr);
			MessageBox(sTemp);
	}
	else
	{		
		//H264_DVR_MakeKeyFrame(pDev->lLoginID, nChannel, 0);		
	}
	m_lLogin = pDev->lLoginID;
	m_iChannel = nChannel;
	return m_iPlayhandle;
}


void CVideoWnd::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(m_iPlayhandle != -1)
	{			
		
		if(!H264_DVR_StopRealPlay(m_iPlayhandle,m_hWnd))
		{
			TRACE("H264_DVR_StopRealPlay fail m_iPlayhandle = %d", m_iPlayhandle);
		}
		if(m_bSound)
		{
			OnCloseSound();
		}
	}

	m_bRecord = FALSE;
}

void CVideoWnd::GetColor(long *nBright, long *nContrast, long *nSaturation, long *nHue)
{
	if(m_iPlayhandle <= 0 )
	{
		return;
	}
	long nRegionNum = 0;
	H264_DVR_LocalGetColor(m_iPlayhandle, nRegionNum,nBright, nContrast, nSaturation, nHue);
}

void CVideoWnd::SetColor(long nBright, long nContrast, long nSaturation, long nHue)
{
	H264_DVR_LocalSetColor(m_iPlayhandle, 0, nBright, nContrast, nSaturation, nHue );
}

BOOL CVideoWnd::SaveRecord()
{
	//获取当前窗口播放句柄
	if ( m_iPlayhandle <= 0 )
	{
		return FALSE;
	}
	
	CString  cFilename;
	
	CTime time = CTime::GetCurrentTime();
	cFilename.Format("%s\\record\\%4d%02d%02d_%02d%02d%02d.h264", 	
		"c:", 
		time.GetYear(), 
		time.GetMonth(), 
		time.GetDay(), 
		time.GetHour(), 
		time.GetMinute(), 
		time.GetSecond());

	if (-1 == _access("c:\\record",0))
	{
		CreateDirectory("c:\\record",NULL);
	}

	if ( m_bRecord )
	{
		if ( H264_DVR_StopLocalRecord(m_iPlayhandle) )
		{
			m_bRecord = FALSE;
			MessageBox(_CS("Desktop.StopRecordOk"));
		}
	}
	else
	{
		/**************************///hw
		
		CString strFileType(".h264");
		CString strFileName("");
        if (strstr(cFilename,".h264"))
        {
			strFileType = _T("h264");
        } 
        else
        {
			MessageBox("Type Error!");
			return FALSE;
        }

		int iNum = cFilename.ReverseFind('\\');
		if( -1 == iNum){
             return FALSE;
		}
		else
		{
             strFileName = cFilename.Right(cFilename.GetLength()-(iNum +1) );
		}
		
		CFileDialog dlg( FALSE , strFileType, strFileName , OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
			"All File(*.h264;)|*.*||" , this );
		dlg.m_ofn.lpstrInitialDir = cFilename.Left(iNum);

		CString strSaveName;
		if (dlg.DoModal() == IDOK)
		{
			cFilename = dlg.GetPathName();

			int nTemp = 0;
			for(;;)
			{
				int nIndex = cFilename.Find('\\',nTemp);
				if (nIndex == -1) 
				{
					break;
				}
				CString str = cFilename.Left(nIndex);
				nTemp = nIndex+1;
				_mkdir(str);
			}
			

			if ( H264_DVR_StartLocalRecord(m_iPlayhandle, cFilename.GetBuffer(0), MEDIA_FILE_NONE))
			{
				m_bRecord = TRUE;
				MessageBox(_CS("Desktop.StartRecordOk"));
			}
			else
			{
				MessageBox(_CS("Desktop.StartRecordFail"));
			}
		}

		/*********************/
	
	}

	return TRUE;
}


void CVideoWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_iPlayhandle > 0 )
	{
		CMenu Menu;
		Menu.CreatePopupMenu();
		
		Menu.AppendMenu(MF_STRING , ID_DISCONNECT, _CS("Desktop.CloseWindow"));
		if(m_bSound)
		{
			Menu.AppendMenu(MF_STRING , ID_DEVICE_CLOSESOUND, _CS("Desktop.CloseAudio"));
			
		}
		else
		{
			Menu.AppendMenu(MF_STRING , ID_DEVICE_OPENSOUND, _CS("Desktop.OpenAudio"));
			
		}
		
		
		CPoint pt;
		::GetCursorPos(&pt);
		Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
	}

	CDialog::OnRButtonDown(nFlags, point);
}

long CVideoWnd::GetLoginHandle()
{
	return m_lLogin;
}

long CVideoWnd::SetDevChnColor(SDK_CONFIG_VIDEOCOLOR* pVideoColor)
{
	return H264_DVR_SetDevConfig(m_lLogin,E_SDK_VIDEOCOLOR,m_iChannel,(char*)pVideoColor,sizeof(SDK_CONFIG_VIDEOCOLOR),3000);
}
void CVideoWnd::OnOpenSound()
{
	/***************///hw
	CClientDemoDlg* pParent = (CClientDemoDlg*) GetParent();

	if (pParent->m_nCurIndex != m_nIndex)
	{
		m_bSound = true;
		return;
	}
	/***************/
	if(	H264_DVR_OpenSound(m_iPlayhandle))
	{
		m_bSound = true;
		
	}
	
}
void CVideoWnd::OnCloseSound()
{
	/***************/ //hw
	CClientDemoDlg* pParent = (CClientDemoDlg*) GetParent();

	if (pParent->m_nCurIndex != m_nIndex)
	{
		m_bSound = false;
	}
	/****************/
	if( H264_DVR_CloseSound(m_iPlayhandle))
	{
		m_bSound=false;
	}
	
	
}

void CVideoWnd::SoundChangeWnd(int pCurIndex,CVideoWnd*preVideoWnd)
{
	if (pCurIndex != m_nIndex)
	{
		if (true == preVideoWnd->m_bSound) //pre VideoWnd
		{	
			H264_DVR_CloseSound(preVideoWnd->m_iPlayhandle);
		}

		if (true == m_bSound) //cur VideoWnd
		{
		    H264_DVR_OpenSound(m_iPlayhandle); 
		}
	} 
}
