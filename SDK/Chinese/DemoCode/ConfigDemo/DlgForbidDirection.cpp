// DlgForbidDirection.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DlgForbidDirection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgForbidDirection dialog


CDlgForbidDirection::CDlgForbidDirection(int nRule,int nDirection,int iIsDoubleDirection,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgForbidDirection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgForbidDirection)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iIsDoubleDirection = iIsDoubleDirection;
	m_nDirection = nDirection;
	if (nRule == SDK_ANALYSE_PERIMETER)
	{
			m_nDirection = nDirection+1;
	}
	
	m_nRule = nRule;
}


void CDlgForbidDirection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgForbidDirection)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgForbidDirection, CDialog)
	//{{AFX_MSG_MAP(CDlgForbidDirection)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_DIRECTION1, CDlgForbidDirection::OnBnClickedRadioDirection1)
	ON_BN_CLICKED(IDC_RADIO_DIRECTION2, CDlgForbidDirection::OnBnClickedRadioDirection2)
	ON_BN_CLICKED(IDC_RADIO_DIRECTION3, CDlgForbidDirection::OnBnClickedRadioDirection3)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgForbidDirection message handlers

void CDlgForbidDirection::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		if (m_nRule == SDK_ANALYSE_PERIMETER)
		{
			if (m_nDirection>0)
			{
				((CButton*)GetDlgItem(IDC_RADIO_DIRECTION1+m_nDirection-1))->SetCheck(BST_CHECKED);
			}
			
		}
		else if (m_nRule == SDK_ANALYSE_TRIPWIRE)
		{
			if (m_iIsDoubleDirection)
			{
				((CButton*)GetDlgItem(IDC_RADIO_DIRECTION3))->SetCheck(BST_CHECKED); 
			}
			else
			{
				((CButton*)GetDlgItem(IDC_RADIO_DIRECTION1+(m_nDirection+1)%2))->SetCheck(BST_CHECKED);
			}
			
		}	
	}
	// TODO: 在此处添加消息处理程序代码
}

BOOL CDlgForbidDirection::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	if (m_nRule == SDK_ANALYSE_TRIPWIRE)
	{
		if (m_nDirection <= 1)
		{
			((CButton*)GetDlgItem(IDC_RADIO_DIRECTION1))->SetWindowText(_CS("CA.LeftToRight"));
			((CButton*)GetDlgItem(IDC_RADIO_DIRECTION2))->SetWindowText(_CS("CA.RightToLeft"));
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_DIRECTION1))->SetWindowText(_CS("CA.UpToDown"));
			((CButton*)GetDlgItem(IDC_RADIO_DIRECTION2))->SetWindowText(_CS("CA.DownToUp"));
		}
		
		((CButton*)GetDlgItem(IDC_RADIO_DIRECTION3))->SetWindowText(_CS("CA.DoubleDirection"));
	}
	else if (m_nRule == SDK_ANALYSE_PERIMETER)
	{
		((CButton*)GetDlgItem(IDC_RADIO_DIRECTION1))->SetWindowText(_CS("CA.DoubleDirection"));
		((CButton*)GetDlgItem(IDC_RADIO_DIRECTION2))->SetWindowText(_CS("CA.Inter"));
		((CButton*)GetDlgItem(IDC_RADIO_DIRECTION3))->SetWindowText(_CS("CA.Leave"));
	}
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgForbidDirection::OnBnClickedRadioDirection1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nDirection = 1;
	m_iIsDoubleDirection = 0;
}

void CDlgForbidDirection::OnBnClickedRadioDirection2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nDirection = 2;
	m_iIsDoubleDirection = 0;
}

void CDlgForbidDirection::OnBnClickedRadioDirection3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nDirection = 3;
	m_iIsDoubleDirection = 1;
}
