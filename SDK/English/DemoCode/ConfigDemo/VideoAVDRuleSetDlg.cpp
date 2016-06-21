// VideoAVDRuleSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "VideoAVDRuleSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoAVDRuleSetDlg dialog
extern   CClientDemo5App   theApp;

CVideoAVDRuleSetDlg::CVideoAVDRuleSetDlg(SDK_AVD_RULE_S *pAvdRule,int nChannelNum,CWnd* pParent /*=NULL*/)
	: CDialog(CVideoAVDRuleSetDlg::IDD, pParent)
{
	OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
	AfxSetResourceHandle(theApp.m_hInstance);//设置新的模块  
	m_nChannelNum = nChannelNum;
	if ( pAvdRule!= NULL)
	{
		memcpy(&m_rule,pAvdRule,sizeof(m_rule));
	}
	else
	{
		memset(&m_rule,0,sizeof(m_rule));
	} 
}


void CVideoAVDRuleSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoAVDRuleSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoAVDRuleSetDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoAVDRuleSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoAVDRuleSetDlg message handlers

BOOL CVideoAVDRuleSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strText;
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_SENSITIVITY_LEVEL);
	strText.Format("%s", _CS("ConfigVideo.High") );
	pComboBox->InsertString(0,strText);
//	int nInsert = pComboBox->AddString(strText);
//	pComboBox->SetItemData(nInsert, 0);
	
	strText.Format("%s", _CS("ConfigVideo.Middle") );
	pComboBox->InsertString(1,strText);
//	nInsert = pComboBox->AddString(strText);
//	pComboBox->SetItemData(nInsert, 1);
	
	strText.Format("%s", _CS("ConfigVideo.Lower") );
	pComboBox->InsertString(2,strText);
//	nInsert = pComboBox->AddString(strText);
//	pComboBox->SetItemData(nInsert, 2);
	
	pComboBox->SetCurSel(5 - m_rule.iLevel); //高中低分别为5,4,3

	((CButton*)GetDlgItem(IDC_CHECK_BRIGHTABNML))->SetCheck(m_rule.itBrightAbnmlEnable);
	((CButton*)GetDlgItem(IDC_CHECK_NOISE))->SetCheck(m_rule.iNoiseEnable);
	((CButton*)GetDlgItem(IDC_CHECK_FREEZE))->SetCheck(m_rule.iFreezeEnable);
	((CButton*)GetDlgItem(IDC_CHECK_INTERFERE))->SetCheck(m_rule.iInterfereEnable);
	((CButton*)GetDlgItem(IDC_CHECK_CLARITY))->SetCheck(m_rule.iClarityEnable);
	((CButton*)GetDlgItem(IDC_CHECK_COLOR))->SetCheck(m_rule.iColorEnable);
	((CButton*)GetDlgItem(IDC_CHECK_CHANGE))->SetCheck(m_rule.iChangeEnable);
	((CButton*)GetDlgItem(IDC_CHECK_PTZLOSECTL))->SetCheck(m_rule.iPtzLoseCtlEnable);
	_CWndCS(this);
	UpdateData(FALSE);
	return TRUE;  
}

void CVideoAVDRuleSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_SENSITIVITY_LEVEL);
	m_rule.iLevel =5 - pComboBox->GetCurSel();
	
	m_rule.itBrightAbnmlEnable = ((CButton*)GetDlgItem(IDC_CHECK_BRIGHTABNML))->GetCheck();
	m_rule.iNoiseEnable = ((CButton*)GetDlgItem(IDC_CHECK_NOISE))->GetCheck();
	m_rule.iFreezeEnable = ((CButton*)GetDlgItem(IDC_CHECK_FREEZE))->GetCheck();
	m_rule.iInterfereEnable = ((CButton*)GetDlgItem(IDC_CHECK_INTERFERE))->GetCheck();
	m_rule.iClarityEnable = ((CButton*)GetDlgItem(IDC_CHECK_CLARITY))->GetCheck();
	m_rule.iColorEnable = ((CButton*)GetDlgItem(IDC_CHECK_COLOR))->GetCheck();
	m_rule.iChangeEnable = ((CButton*)GetDlgItem(IDC_CHECK_CHANGE))->GetCheck();
	m_rule.iPtzLoseCtlEnable = ((CButton*)GetDlgItem(IDC_CHECK_PTZLOSECTL))->GetCheck();
	CDialog::OnOK();
}
