// TitleSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "TitleSetDlg.h"
#include "ClientDemo5Dlg.h"

#define TITLE_HEIGTH 24

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleSetDlg dialog


CTitleSetDlg::CTitleSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTitleSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTitleSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTitleSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTitleSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_STATIC_CHANNELNAME, m_ncChannel);
	DDX_Control(pDX, IDC_STATIC_TIME, m_ncTime);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTitleSetDlg, CDialog)
	//{{AFX_MSG_MAP(CTitleSetDlg)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDCCANCEL, OnCcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitleSetDlg message handlers

BOOL CTitleSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
    int nLastItem = ((CClientDemo5Dlg *)AfxGetMainWnd())->m_outputDlg.m_nLastChanItem;

	m_Videowidget = ((CClientDemo5Dlg *)AfxGetMainWnd())->
		       m_outputDlg.m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[nLastItem];

	m_ncChannel.m_nFlags = NOMODIFY_SIZE;
	m_ncTime.m_nFlags = NOMODIFY_SIZE;
	CRect crClient;
	GetClientRect(&crClient);

	m_crMove.SetRect(crClient.left+10,crClient.top + 10,crClient.right-10,
		             crClient.bottom - 50);
	m_ncChannel.SetMoveRect(m_crMove);
	m_ncTime.SetMoveRect(m_crMove);

/*	CRect crTime;
	CRect crChannel;
    crTime.left = wdgTimeTitle.rcRelativePos.left;
	crTime.right = wdgTimeTitle.rcRelativePos.right;
	crTime.top = wdgTimeTitle.rcRelativePos.top;	
	crTime.bottom = wdgTimeTitle.rcRelativePos.bottom;
    GetDlgItem(IDC_EDIT_TIME)->GetWindowRect(crChannel);
	ScreenToClient(crChannel);


	GetDlgItem(IDC_EDIT_TIME)->MoveWindow(crTime);
	


    CRect crTime; //= new CRect(350,35,550,60);
    CRect crChannel;
	CRect crCurrent;
	GetClientRect(crCurrent);
*/	/*
	GetDlgItem(IDC_EDIT_TIME)->GetWindowRect(crTime);
	ScreenToClient(crTime);
	GetDlgItem(IDC_EDIT_CHANNELNAME)->GetWindowRect(crChannel);
    ScreenToClient(crChannel);


	crTime.bottom = wdgTimeTitle.rcRelativePos.bottom;
	crTime.left = wdgTimeTitle.rcRelativePos.left;
	crTime.top = wdgTimeTitle.rcRelativePos.top;
	crTime.right = wdgTimeTitle.rcRelativePos.right;
	ScreenToClient(crTime);
	m_ncTime.Create(NULL,"time",WS_CHILD|WS_VISIBLE|WS_BORDER |WS_EX_CLIENTEDGE,crTime,this,IDC_NEWCTRL_SHOWIFO + 1);
    m_ncChannel.Create(NULL,"Channel",WS_CHILD|WS_VISIBLE|WS_THICKFRAME,crChannel,this,IDC_NEWCTRL_SHOWIFO + 2);
 //	GetDlgItem(IDC_NEWCTRL_SHOWIFO+1)->SetWindowText("11");
    GetDlgItem(IDC_EDIT_TIME)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_CHANNELNAME)->ShowWindow(SW_HIDE);
*/	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTitleSetDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	HCURSOR i = GetCursor();
	
	CRect rcChannelName;
	GetDlgItem(IDC_STATIC_CHANNELNAME)->GetWindowRect(&rcChannelName);
    ScreenToClient(&rcChannelName);
	
	m_Videowidget.ChannelTitle.rcRelativePos.top = (int)(((double)rcChannelName.top/(double)m_nheight)*8192);
	m_Videowidget.ChannelTitle.rcRelativePos.left = (int)(((double)rcChannelName.left/(double)m_nwidth)*8192);
	
	CRect rcTime;
	GetDlgItem(IDC_STATIC_TIME)->GetWindowRect(&rcTime);
	ScreenToClient(&rcTime);
	
	m_Videowidget.TimeTitle.rcRelativePos.top = (int)(((double)rcTime.top/(double)m_nheight)*8192);
	m_Videowidget.TimeTitle.rcRelativePos.left = (int)(((double)rcTime.left/(double)m_nwidth)*8192);

    int nLastItem =((CClientDemo5Dlg*)AfxGetMainWnd())->m_outputDlg.m_nLastChanItem;
	((CClientDemo5Dlg*)AfxGetMainWnd())->m_outputDlg.m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[nLastItem].ChannelTitle
		          = m_Videowidget.ChannelTitle;
	((CClientDemo5Dlg*)AfxGetMainWnd())->m_outputDlg.m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[nLastItem].TimeTitle
		          = m_Videowidget.TimeTitle;
	// TODO: Add your message handler code here
}

void CTitleSetDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if (!m_Videowidget.ChannelTitle.bEncodeBlend)
		GetDlgItem(IDC_STATIC_CHANNELNAME)->ShowWindow(SW_HIDE);
	if (!m_Videowidget.TimeTitle.bEncodeBlend)
		
		GetDlgItem(IDC_STATIC_TIME)->ShowWindow(SW_HIDE);
	
	CRect rcChannelName;
	CRect rcWnd;
	int height,width;
	//GetClientRect(&rcWnd);
	//m_WndRect = rcWnd; 
	rcWnd.SetRect(m_crMove.TopLeft(),m_crMove.BottomRight());
	
	height = rcWnd.bottom - rcWnd.top;
	width = rcWnd.right - rcWnd.left;
	
	m_nwidth = width;
	m_nheight = height;
	
	int top,left,right,bottom;
	top = (int)((((double)m_Videowidget.ChannelTitle.rcRelativePos.top)/8192.0)*m_nheight);
	left = (int)((((double)m_Videowidget.ChannelTitle.rcRelativePos.left)/8192.0)*m_nwidth);
	
	SetDlgItemText(IDC_STATIC_CHANNELNAME,m_Videowidget.ChannelName.strName);
	int strLen = strlen(m_Videowidget.ChannelName.strName)*16;
	
	if ( rcWnd.right - left <= strLen )
	{
		right = rcWnd.right;
		left = rcWnd.right - strLen;
	}
	if ( rcWnd.bottom - top <= TITLE_HEIGTH )
	{
		bottom = rcWnd.bottom;
		top = rcWnd.bottom - TITLE_HEIGTH;
	}
	
	GetDlgItem(IDC_STATIC_CHANNELNAME)->MoveWindow(left,top,strLen,TITLE_HEIGTH,TRUE);
	
	
	CRect rcTime;
	top = (int)((((double)m_Videowidget.TimeTitle.rcRelativePos.top)/8192.0)*m_nheight);
	left = (int)((((double)m_Videowidget.TimeTitle.rcRelativePos.left)/8192.0)*m_nwidth);
	
	CTime cur_time = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("%04d-%02d-%02d  %02d:%02d:%02d"), cur_time.GetYear() , cur_time.GetMonth(), cur_time.GetDay() ,cur_time.GetHour() , cur_time.GetMinute(), cur_time.GetSecond());
	SetDlgItemText(IDC_STATIC_TIME,strTime);
	strLen = strTime.GetLength()*8;
	
	if ( rcWnd.right - left <= strLen )
	{
		right = rcWnd.right;
		left = rcWnd.right - strLen;
	}
	if ( rcWnd.bottom - top <= TITLE_HEIGTH )
	{
		bottom = rcWnd.bottom;
		top = rcWnd.bottom - TITLE_HEIGTH;
	}
	
	GetDlgItem(IDC_STATIC_TIME)->MoveWindow(left,top,strLen,TITLE_HEIGTH,TRUE);

}

BOOL CTitleSetDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
    switch(pWnd->GetDlgCtrlID()) 
	{
	case IDC_STATIC_CHANNELNAME:
		{
			SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			return TRUE;
		}
		break;
	case IDC_STATIC_TIME:
		{
			SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			return TRUE;
		}
		break;
	default:
		break;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CTitleSetDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}

void CTitleSetDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CTitleSetDlg::OnCcancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CTitleSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
