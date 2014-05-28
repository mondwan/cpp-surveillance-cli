

#include "stdafx.h"
#include "ClientDemo.h"
#include "TabPlayback.h"


// CTabPlayback dialog

IMPLEMENT_DYNAMIC(CTabPlayback, CDialog)

CTabPlayback::CTabPlayback(CWnd* pParent /*=NULL*/)
	: CDialog(CTabPlayback::IDD, pParent)
{

}

CTabPlayback::~CTabPlayback()
{
}

void CTabPlayback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CTabPlayback, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, CTabPlayback::OnTcnSelchangeTab1)
END_MESSAGE_MAP()



BOOL CTabPlayback::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Tab.InsertItem(0,_CS("PlayBack.NetworkPlayback"));
	m_Tab.InsertItem(1,_CS("PlayBack.LocalPlayback"));

	m_Tab.InsertItem(2,_CS("PlayBack.CovertFile"));

	m_remoteplayback.Create(IDD_REMOTE_PLAYBACK,&m_Tab);
	m_localplayback.Create(IDD_DLG_LOCALPLAYBACK,&m_Tab);

	m_testCovertFile.Create(IDD_DLG_TESTCOVER,&m_Tab);
	
	CRect rs;
	m_Tab.GetClientRect(&rs);
	rs.top+=20; 
	m_remoteplayback.MoveWindow(&rs);
	m_localplayback.MoveWindow(&rs);
	
	m_testCovertFile.MoveWindow(&rs);

	m_remoteplayback.ShowWindow(SW_SHOW);
	m_pTabDlg[0]=&m_remoteplayback;
	m_pTabDlg[1]=&m_localplayback;

	m_pTabDlg[2]=&m_testCovertFile;
	
	m_CurSelTab=0;
	return TRUE;
}
void CTabPlayback::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pTabDlg[m_CurSelTab]->ShowWindow(SW_HIDE);
	m_CurSelTab=m_Tab.GetCurSel();
	m_pTabDlg[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}
