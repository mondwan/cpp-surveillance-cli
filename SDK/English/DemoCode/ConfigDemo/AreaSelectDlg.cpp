// AreaSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "AreaSelectDlg.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaSelectDlg dialog
extern   CClientDemo5App   theApp;

IMPLEMENT_DYNAMIC(CAreaSelectDlg, CDialog)


CAreaSelectDlg::CAreaSelectDlg( short nRow, short nCol, unsigned int *mRegion, CWnd* pParent )
: CDialog(CAreaSelectDlg::IDD, pParent),
m_nCurChannel(0),
m_bFullScreen(FALSE),
m_nRow(0),
m_nCol(0)
{
	OldResourceHanlde= AfxGetResourceHandle();   
	AfxSetResourceHandle(theApp.m_hInstance);    	
	
	if (NULL != mRegion)
	{
		SetRowCol(mRegion, nRow, nCol);
	}
	else
	{
		m_nCol = nCol;
		m_nRow = nRow;
		ZeroMemory( m_mRegion, sizeof(m_mRegion) );
	}

}

CAreaSelectDlg::~CAreaSelectDlg()
{

}
void CAreaSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaSelectDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAreaSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CAreaSelectDlg)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaSelectDlg message handlers

BOOL CAreaSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	AfxSetResourceHandle(OldResourceHanlde);
	
	_CWndCS(this);
	
	CRect dlgRect, areaRect;
	GetClientRect(&dlgRect);
	
	int nWidth = dlgRect.Width();
	nWidth = nWidth / m_wndMotionDetect.m_nRgnColNum * m_wndMotionDetect.m_nRgnColNum;
	
	int nHeight = dlgRect.Height() - 32; 
	nHeight = nHeight / m_wndMotionDetect.m_nRgnRowNum * m_wndMotionDetect.m_nRgnRowNum;
	
	areaRect.left = dlgRect.left + (dlgRect.Width() - nWidth) / 2;
	areaRect.right = dlgRect.right - (dlgRect.Width() - nWidth)/2;
	areaRect.top = dlgRect.top;
	areaRect.bottom = dlgRect.top + nHeight;

	m_wndMotionDetect.MoveWindow(&areaRect);

	ShowInformation();


	GetDlgItem(IDC_STATIC_TXT_UNSELECT)->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAreaSelectDlg::SetChannelInfo(int nChannel)
{
	m_nCurChannel = nChannel;
}

void CAreaSelectDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	StartPre(true);
	CatchPic();
	StartPre(false);
}

bool CAreaSelectDlg::StartPre(bool bPre)
{

	if (bPre)
	{
		H264_DVR_CLIENTINFO clientInfo;
		clientInfo.nChannel = m_nCurChannel;
		clientInfo.hWnd = m_hWnd;
		m_lRealHandle = H264_DVR_RealPlay(((CClientDemo5Dlg*)m_pMainDlg)->m_LoginID, &clientInfo);
	}else
	{
		H264_DVR_StopRealPlay(m_lRealHandle);
	}

	return 1;
}

bool CAreaSelectDlg::CatchPic()
{
	int i = 0;
	
	while( i < 3)
	{
		
		
		Sleep(1000);
		i++;
	}	
	Sleep(1000);
	H264_PLAY_CatchPic(1,"c:\\test.bmp");
	m_wndMotionDetect.SetBackImgFile("c:\\test.bmp");
	return 1;
}

void CAreaSelectDlg::SetRowCol(unsigned int *mRegion, short nRow, short nCol)
{
	ZeroMemory( m_mRegion, sizeof(m_mRegion) );
	memcpy(m_mRegion, mRegion, sizeof(unsigned int) * nRow );

	m_nRow = nRow;
	m_nCol = nCol;
}


const unsigned int * CAreaSelectDlg::GetSetData()
{
	int ni = 0;
	int nj = 0;

	ZeroMemory(&m_mRegion, sizeof(m_mRegion) );

	for (ni = 0 ; ni < m_nRow ; ni ++)
	{
		for (nj = 0 ; nj < m_nCol ; nj ++)
		{
			if ( m_wndMotionDetect.GetGridValue(ni,nj) )
			{
				m_mRegion[ni] = m_mRegion[ni] | ( 1 << nj ); 
			}	
		}
	}	

	return m_mRegion;
}

void CAreaSelectDlg::ShowInformation()
{
	m_wndMotionDetect.SetGridRowCol(m_nRow,m_nCol);

	int ni = 0;
	int nj = 0;

	for (ni = 0 ; ni < m_nRow ; ni ++)
	{
		for (nj = 0 ; nj < m_nCol ; nj ++)
		{
			m_wndMotionDetect.SetGridValue(ni,nj, ( m_mRegion[ni] & ( 1 << nj ) ) );
		}
	}
}


BOOL CAreaSelectDlg::DestroyWindow() 
{	
	return CDialog::DestroyWindow();
}

int CAreaSelectDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndMotionDetect.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,ID_MOTION_DETECT);	
	return 0;
}

void CAreaSelectDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect selRect, unSelRect;
	GetDlgItem(IDC_STATIC_TXT_SELECT)->GetWindowRect(&selRect);
	ScreenToClient(&selRect);
	selRect.left = selRect.left - 20;
	selRect.right = selRect.left + 16;

	GetDlgItem(IDC_STATIC_TXT_UNSELECT)->GetWindowRect(&unSelRect);
	ScreenToClient(&unSelRect);
	unSelRect.left = unSelRect.left - 20;
	unSelRect.right = unSelRect.left + 16;
	
	dc.FillRect(&selRect,&CBrush(SELECTCOLOR));
	//dc.FillRect(&unSelRect,&CBrush(UNSELECTCOLOR));

}
void CAreaSelectDlg::OnOk()
{
	CDialog::OnOK();
}

void CAreaSelectDlg::OnCancel()
{
	CDialog::OnCancel();
}
