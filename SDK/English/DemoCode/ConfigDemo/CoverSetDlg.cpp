// CoverSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "CoverSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoverSetDlg dialog


CCoverSetDlg::CCoverSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoverSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoverSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCoverSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoverSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoverSetDlg, CDialog)
	//{{AFX_MSG_MAP(CCoverSetDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoverSetDlg message handlers

BOOL CCoverSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	
	// TODO: Add extra initialization here

	m_dlgCoverArea.Create(CCoverAreaDlg::IDD,this);
	m_dlgCoverArea.ModifyStyle(WS_POPUP,WS_CHILD,0);
	m_dlgCoverArea.SetParent(this);

	CRect rect;
	GetClientRect(&rect);
	CRect BtnRect,CoverAreaRect;
    GetDlgItem(IDOK)->GetWindowRect(&BtnRect);
	ScreenToClient(BtnRect);
	CoverAreaRect.SetRect(rect.left,rect.top,rect.right,BtnRect.top - 10);
	m_dlgCoverArea.m_nWidth = CoverAreaRect.Width();
	m_dlgCoverArea.m_nHeight = CoverAreaRect.Height();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCoverSetDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	RECT rect;
	GetClientRect(&rect);
	
	CRect BtnRect,CoverAreaRect;
	GetDlgItem(IDOK)->GetWindowRect(&BtnRect);
	ScreenToClient(BtnRect);
	CoverAreaRect.SetRect(rect.left,rect.top,rect.right,BtnRect.top - 10);

	m_dlgCoverArea.MoveWindow(&CoverAreaRect);
    m_dlgCoverArea.ShowWindow(SW_SHOW);
	
	// Do not call CDialog::OnPaint() for painting messages
}
