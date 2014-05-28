// PTZDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PTZDlg.h"
#include "CRUISEEDIT.h"
#include "ClientDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPTZDlg dialog


CPTZDlg::CPTZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTZDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPTZDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPTZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPTZDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO1, m_present);
	DDX_Control(pDX, IDC_COMBO2, m_ComboCruise);
}


BEGIN_MESSAGE_MAP(CPTZDlg, CDialog)
	//{{AFX_MSG_MAP(CPTZDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTZDlg message handlers

BOOL CPTZDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_CWndCS(this);


	
	m_mybuttonup.SubclassDlgItem(IDC_BUTTONUP,this);
	m_mybuttonup.SetType(1000);
	m_mybuttondown.SubclassDlgItem(IDC_BUTTONDOWN,this);
	m_mybuttondown.SetType(1000);
	m_mybuttonleft.SubclassDlgItem(IDC_BUTTONLEFT,this);
	m_mybuttonleft.SetType(1000);
	m_mybuttonright.SubclassDlgItem(IDC_BUTTONRIGHT,this);
	m_mybuttonright.SetType(1000);
	m_mybuttontjright.SubclassDlgItem(IDC_BUTTONTJRIGHT,this);
	m_mybuttontjright.SetType(1000);
	m_mybuttontjleft.SubclassDlgItem(IDC_BUTTONTJLEFT,this);
	m_mybuttontjleft.SetType(1000);
	m_mybuttonjjleft.SubclassDlgItem(IDC_BUTTONJJLEFT,this);
	m_mybuttonjjleft.SetType(1000);
	m_mybuttonjjright.SubclassDlgItem(IDC_BUTTONJJRIGHT,this);
	m_mybuttonjjright.SetType(1000);
	m_mybuttongqleft.SubclassDlgItem(IDC_BUTTONGQLEFT,this);
	m_mybuttongqleft.SetType(1000);
	m_mybuttongqright.SubclassDlgItem(IDC_BUTTONGQRIGHT,this);
	m_mybuttongqright.SetType(1000);
	m_mybuttonrighttop.SubclassDlgItem(IDC_BUTTONRIGHTUP,this);
	m_mybuttonrighttop.SetType(1000);
	m_mybuttonleftdown.SubclassDlgItem(IDC_BUTTONLEFTDOWN,this);
	m_mybuttonleftdown.SetType(1000);
	m_mybuttonlefttop.SubclassDlgItem(IDC_BUTTONLEFTUP,this);
	m_mybuttonlefttop.SetType(1000);
	m_mybuttonrightdown.SubclassDlgItem(IDC_BUTTONRIGHTDOWN,this);
	m_mybuttonrightdown.SetType(1000);
	m_mybuttonusepresent.SubclassDlgItem(IDC_UsePresent,this);
	m_mybuttonusepresent.SetType(1000);
	m_mybuttonaddpresent.SubclassDlgItem(IDC_ADDPRESENT,this);
	m_mybuttonaddpresent.SetType(1000);
	m_mybuttondeletepresent.SubclassDlgItem(IDC_PRESENTDELETE,this);
	m_mybuttondeletepresent.SetType(1000);
	m_mybuttoncruiseplay.SubclassDlgItem(IDC_CRUISEPLAY,this);
	m_mybuttoncruiseplay.SetType(1000);
	m_mybuttoncruisestop.SubclassDlgItem(IDC_CRUISESTOP,this);
	m_mybuttoncruisestop.SetType(1000);
	m_mybuttoncruiseedit.SubclassDlgItem(IDC_CRUISEEDIT,this);
	m_mybuttoncruiseedit.SetType(1000);


	//m_present.ResetContent();
	UINT i;
	CString temp="";
	for (i=1;i<65;i++)
	{
		temp.Format("%d",i);
		m_present.AddString(temp);	
		
	}
	m_present.SetCurSel(0);
	
	for (i=1;i<33;i++)
	{
		temp.Format("%d",i);
		m_ComboCruise.AddString(temp);
	}
	m_ComboCruise.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

