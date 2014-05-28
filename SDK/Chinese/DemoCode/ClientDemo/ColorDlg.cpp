// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "ColorDlg.h"
#include "ClientDemoDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog


CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorDlg)
	//}}AFX_DATA_INIT


	m_Bright = 128;       //bright	
	m_Contrast = 128;     //contrast
	m_Hue = 128;          //hue
	m_Saturation = 128;   //saturation
}


void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorDlg)
	DDX_Control(pDX, IDC_SLIDERBHD, m_ucSaturation);
	DDX_Control(pDX, IDC_SLIDERSD, m_ucHue);
	DDX_Control(pDX, IDC_SLIDERDBD, m_ucContrast);
	DDX_Control(pDX, IDC_SLIDERLD, m_ucBright);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	//{{AFX_MSG_MAP(CColorDlg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERBHD, OnReleasedcaptureSliderbhd)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERDBD, OnReleasedcaptureSliderdbd)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERLD, OnReleasedcaptureSliderld)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERSD, OnReleasedcaptureSlidersd)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERYL, OnReleasedcaptureSlideryl)
	ON_BN_CLICKED(IDC_BUTTONPOLL, OnButtonpoll)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorDlg message handlers

BOOL CColorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_CWndCS(this);
	
	m_ucSaturation.SetRange( 0 , 128);
	m_ucSaturation.SetPos(64);

	m_ucHue.SetRange( 0 , 128);
	m_ucHue.SetPos(64);

	m_ucContrast.SetRange( 0 , 128);
	m_ucContrast.SetPos(64);

	m_ucBright.SetRange(0 , 128);
	m_ucBright.SetPos(64);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CColorDlg::OnReleasedcaptureSliderbhd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_Saturation = m_ucSaturation.GetPos();
	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();

	if ( pParent )
	{
		pParent->SetColor(m_Bright, m_Contrast, m_Saturation, m_Hue);
	}
	
	*pResult = 0;
}

void CColorDlg::OnReleasedcaptureSliderdbd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_Contrast = m_ucContrast.GetPos();
	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
	
	if ( pParent )
	{
		pParent->SetColor(m_Bright, m_Contrast, m_Saturation, m_Hue);
	}

	*pResult = 0;
}

void CColorDlg::OnReleasedcaptureSliderld(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	m_Bright = m_ucBright.GetPos();
	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
	
	if ( pParent )
	{
		pParent->SetColor(m_Bright, m_Contrast, m_Saturation, m_Hue);
	}

	*pResult = 0;
}

void CColorDlg::OnReleasedcaptureSlidersd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_Hue = m_ucHue.GetPos();

	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
	
	if ( pParent )
	{
		pParent->SetColor(m_Bright, m_Contrast, m_Saturation, m_Hue);
	}
	*pResult = 0;
}

void CColorDlg::OnReleasedcaptureSlideryl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CColorDlg::SetColor(int nBright, int nContrast, int nSaturation, int nHue)
{
	m_ucSaturation.SetPos(nSaturation);
	m_ucHue.SetPos(nHue);
	m_ucContrast.SetPos(nContrast);
	m_ucBright.SetPos(nBright);

	m_Bright = nBright;
	m_Contrast = nContrast;
	m_Saturation =nSaturation;
	m_Hue = nHue;
}


void CColorDlg::OnButtonpoll() 
{
	m_Bright = 64;
	m_Contrast = 64;
	m_Saturation = 64;
	m_Hue = 64;
	m_ucSaturation.SetPos(64);
	m_ucHue.SetPos(64);
	m_ucContrast.SetPos(64);
	m_ucBright.SetPos(64);

	CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
	
	if ( pParent )
	{
		pParent->SetColor(m_Bright, m_Contrast, m_Saturation, m_Hue);
	}
}

void CColorDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
}
