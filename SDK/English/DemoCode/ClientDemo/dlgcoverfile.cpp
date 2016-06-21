// DlgCoverFile.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCoverFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCoverFile dialog


CDlgCoverFile::CDlgCoverFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCoverFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCoverFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCoverFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCoverFile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCoverFile, CDialog)
	//{{AFX_MSG_MAP(CDlgCoverFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCoverFile message handlers
/////////////////////////////////////////////////////////////////////////////
// Cdlgcoverfile dialog


Cdlgcoverfile::Cdlgcoverfile(CWnd* pParent /*=NULL*/)
	: CDialog(Cdlgcoverfile::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdlgcoverfile)
	m_strDesPath = _T("");
	m_strSrcpath = _T("");
	//}}AFX_DATA_INIT
}


void Cdlgcoverfile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlgcoverfile)
	DDX_Text(pDX, IDC_EDIT_DesPath, m_strDesPath);
	DDX_Text(pDX, IDC_EDIT_SrcPath, m_strSrcpath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdlgcoverfile, CDialog)
	//{{AFX_MSG_MAP(Cdlgcoverfile)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDCANCEL, &Cdlgcoverfile::OnBnClickedCancel)
	//ON_EN_CHANGE(IDC_EDIT_SrcPath, &Cdlgcoverfile::OnEnChangeEditSrcpath)
	//ON_BN_CLICKED(IDOK, &Cdlgcoverfile::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_SrcPath, &Cdlgcoverfile::OnEnChangeEditSrcpath)
	ON_BN_CLICKED(IDOK, &Cdlgcoverfile::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlgcoverfile message handlers

void Cdlgcoverfile::OnOK() 
{
	
	UpdateData();

	if ( m_strSrcpath == "" || m_strDesPath =="")
	{
		if(m_strSrcpath == "")
			MessageBox(_CS("PlayBack.SrcCoverSelect"));
		if(m_strDesPath == "")
			MessageBox(_CS("PlayBack.DesCoverSelect"));
		return;
	}
	
	if (strstr(m_strSrcpath.GetBuffer(0), ".h264") || strstr(m_strSrcpath.GetBuffer(0), ".H264"))
	{
		
	}
	else
	{
		//MessageBox(_CS("PlayBack.PlayWrongt"));
		MessageBox(_CS("PlayBack.SrcFormatError"));
		return;
	}
	if (strstr(m_strDesPath.GetBuffer(0), ".avi") || strstr(m_strDesPath.GetBuffer(0), ".AVI"))
	{

	}
	else
	{
		//MessageBox(_CS("PlayBack.PlayWrongt"));
		MessageBox(_CS("PlayBack.DesFormatError"));
		return;
	}
	int Ret = H264_PLAY_ConvertFile((const char*)m_strSrcpath.GetBuffer(0),(const char*)m_strDesPath.GetBuffer(0),MEDIA_FILE_AVI,NULL,NULL);
	if ( Ret > 0)
	{
		MessageBox(_CS("PlayBack.CovertOk"));
	}
	else
	{
		MessageBox(_CS("PlayBack.CovertFailed"));
	}
	
}

void Cdlgcoverfile::OnButton1()
{
	// TODO: Add your control notification handler code here
	CString str("");
	char szFilter[] = _T("Video files (*.h264)|*.*||");	
	
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,szFilter, this);
	if ( dlg.DoModal() == IDOK)
	{
		m_strSrcpath = dlg.GetPathName();
	}
	UpdateData(FALSE);
}

void Cdlgcoverfile::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_strSrcpath == "")
	{
		return;
	}
//	CString strFileName = _T("TestCover.avi");
//	CFileDialog dlg( FALSE , _T("h264"), strFileName , OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
//		"All File(*.avi)|*.*||" , this );
//	if ( dlg.DoModal() == IDOK )
//	{
//		m_strDesPath = dlg.GetPathName();
//	}
	CString strSaveName("");
	//strSaveName.Format("c:\\record");
	strSaveName = BrowseForFolder(GetSafeHwnd()) ;
	CString strFileName = _T("TestCover.avi");
	m_strDesPath = strSaveName + _T("\\")+strFileName;
	UpdateData(FALSE);
}

BOOL Cdlgcoverfile::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString Cdlgcoverfile::BrowseForFolder(HWND hWnd)
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

void Cdlgcoverfile::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
	m_strSrcpath = "" ;
	m_strDesPath ="";
	UpdateData(FALSE);
}

/*
void Cdlgcoverfile::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//if(IDYES==::MessageBox(NULL,"真的要退出？","OK",MB_YESNO));
		OnCancel();
}

void Cdlgcoverfile::OnEnChangeEditSrcpath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void Cdlgcoverfile::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}*/


void Cdlgcoverfile::OnEnChangeEditSrcpath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void Cdlgcoverfile::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
