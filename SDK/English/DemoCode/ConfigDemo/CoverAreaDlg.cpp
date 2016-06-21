// CoverAreaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "CoverAreaDlg.h"
#include "ClientDemo5Dlg.H"
#include "IO.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoverAreaDlg dialog

DWORD StaticID[NET_COVERNUM] = 
{
	IDC_STATIC_COVER1,IDC_STATIC_COVER2,IDC_STATIC_COVER3,IDC_STATIC_COVER4,
    IDC_STATIC_COVER5,IDC_STATIC_COVER6,IDC_STATIC_COVER7, IDC_STATIC_COVER8
};


CCoverAreaDlg::CCoverAreaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoverAreaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoverAreaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_nCoverNum = 0;
}


void CCoverAreaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoverAreaDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_STATIC_COVER1, m_ctrlCover1);
	DDX_Control(pDX, IDC_STATIC_COVER2, m_ctrlCover2);
	DDX_Control(pDX, IDC_STATIC_COVER3, m_ctrlCover3);
	DDX_Control(pDX, IDC_STATIC_COVER4, m_ctrlCover4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoverAreaDlg, CDialog)
	//{{AFX_MSG_MAP(CCoverAreaDlg)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoverAreaDlg message handlers

void CCoverAreaDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	CRect rcStatic[NET_COVERNUM];
	CRect rcWnd;
	
	this->GetWindowRect(&rcWnd);
	ScreenToClient(&rcWnd);

	int top,left,right,bottom;
	memset(rcStatic,0,sizeof(rcStatic));
	CRect rcTemp;
	//for (int i = 0;i < 4;i++)
	for (int i = 0; i < m_nCoverNum; i++)
	{
		if (!m_Videowidget.dstCovers[i].bEncodeBlend)
		{
			GetDlgItem(StaticID[i])->ShowWindow(SW_HIDE);
		}
		else
		{
			GetDlgItem(StaticID[i])->ShowWindow(SW_SHOW);	 
		}

		top = (int)((((double)m_Videowidget.dstCovers[i].rcRelativePos.top)/8192)*m_nHeight);
		bottom = (int)((((double)m_Videowidget.dstCovers[i].rcRelativePos.bottom)/8192)*m_nHeight);
		left = (int)((((double)m_Videowidget.dstCovers[i].rcRelativePos.left)/8192)*m_nWidth);
		right = (int)((((double)m_Videowidget.dstCovers[i].rcRelativePos.right)/8192)*m_nWidth);
	
		GetDlgItem(StaticID[i])->MoveWindow(CRect(left,top,right,bottom));
	}	

}

void CCoverAreaDlg::InitDlgInfo()
{
	// show static 
	CString strNum;
	for (int i = 0; i< NET_COVERNUM; i++)
	{
		if ( i < m_nCoverNum )
		{
			GetDlgItem(StaticID[i])->ShowWindow(SW_SHOW);
			strNum.Format("%d",i + 1);
			GetDlgItem(StaticID[i])->SetWindowText(strNum);
		}else
		{
			
			GetDlgItem(StaticID[i])->ShowWindow(SW_HIDE);
		}
	}

	// picture path
	CString FileName,FilePath;
	COleDateTime dtDateTime = COleDateTime::GetCurrentTime();		
	CString strDateTime = dtDateTime.Format(_T("%Y%m%d_%H%M%S"));

	char lpstrConstring[256];
	memset(lpstrConstring,0,sizeof(lpstrConstring));
	BOOL bResult = GetAppPath(lpstrConstring);
	
	char szPath[256];
	memset( szPath , 0 , sizeof(szPath));
	sprintf(szPath,"%sPicture",lpstrConstring);
	FilePath = szPath;

	if (-1 == _access(szPath,0))  
	{
		CreateDirectory(szPath,NULL);
	}

	char szName[256];
	memset( szName, 0 , sizeof(szName));
	sprintf(szName,_T("%s\\%s.bmp"),FilePath,strDateTime.GetBuffer(0));
	strcpy(m_strFileName , szName);

	((CClientDemo5Dlg*)AfxGetMainWnd())->LocalCatPic(m_strFileName,m_nChannelNum,this);

}

BOOL CCoverAreaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
    InitDlgInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

SDK_CONFIG_VIDEOWIDGET * CCoverAreaDlg::GetCover()
{
	CRect rcStatic[NET_COVERNUM];
	memset(rcStatic,0,sizeof(rcStatic));
	
	//for (int i = 0 ;i < 4;i++)
	for (int i = 0; i< m_nCoverNum; i++)
	{
	    GetDlgItem(StaticID[i])->GetWindowRect(&rcStatic[i]);
		ScreenToClient(&rcStatic[i]);
		m_Videowidget.dstCovers[i].rcRelativePos.top = (int)(((double)rcStatic[i].top/(double)m_nHeight)*8192);
		m_Videowidget.dstCovers[i].rcRelativePos.bottom = (int)(((double)rcStatic[i].bottom/(double)m_nHeight)*8192);
		m_Videowidget.dstCovers[i].rcRelativePos.left = (int)(((double)rcStatic[i].left/(double)m_nWidth)*8192);
		m_Videowidget.dstCovers[i].rcRelativePos.right = (int)(((double)rcStatic[i].right/(double)m_nWidth)*8192);
	}	
	
	return &m_Videowidget;
}

void CCoverAreaDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	GetCover();

}

void CCoverAreaDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	HBITMAP   hbitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),m_strFileName,
		IMAGE_BITMAP,352,288,LR_CREATEDIBSECTION|LR_LOADFROMFILE);    
	
	if(hbitmap==NULL)  
		return ;     
	CBitmap  bitmap;      
	bitmap.Attach(hbitmap);  

	CRect rect;
	GetClientRect(&rect); //获得目标尺寸，即窗口客户区的坐标

	BITMAP bitMap;//位图结构体
	bitmap.GetBitmap(&bitMap);//获得原图片尺寸

	CDC dcMem;  //目标DC
	dcMem.CreateCompatibleDC(&dc); //创建与dc兼容的内存DC
	dcMem.SelectObject(&bitmap);//将位图对象m_bmpBK选入内存DC
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
	// Do not call CDialog::OnPaint() for painting messages
}


BOOL CCoverAreaDlg::GetAppPath(char *szPath)
{
	try
	{	
		CString strCurdir;
		strCurdir = GET_MODULE_FILE_INFO.strPath ;
		
		strcat( szPath , strCurdir.GetBuffer(0) );	
	}
	catch(...)
	{	
		return FALSE;
	}
	return TRUE;
}

