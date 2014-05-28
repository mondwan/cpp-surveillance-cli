// VideoOSCRuleSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "VideoOSCRuleSetDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoOSCRuleSetDlg dialog

extern   CClientDemo5App   theApp;

CVideoOSCRuleSetDlg::CVideoOSCRuleSetDlg(/*SDK_OSC_RULE_S* pRule,int nChannelNum,CWnd* pParent*/ /*=NULL*/)
	: CDialog(CVideoOSCRuleSetDlg::IDD/*, pParent*/)
{
	OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
	AfxSetResourceHandle(theApp.m_hInstance);//设置新的模块  
// 	m_nChannelNum = nChannelNum;
// 	if ( pRule!= NULL)
// 	{
// 		memcpy(&m_Rule,pRule,sizeof(m_Rule));
// 	}
// 	else
// 	{
// 		memset(&m_Rule,0,sizeof(m_Rule));
// 	} 
}
void CVideoOSCRuleSetDlg::SetValue(SDK_OSC_RULE_S* pRule,int nChannelNum)
{
	m_nChannelNum = nChannelNum;
	if ( pRule!= NULL)
	{
		memcpy(&m_Rule,pRule,sizeof(m_Rule));
	}
	else
	{
		memset(&m_Rule,0,sizeof(m_Rule));
	} 
}

void CVideoOSCRuleSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoOSCRuleSetDlg)
	DDX_Control(pDX, IDC_SLIDER_RANGE_MIN, m_sliderRangeMin);
	//}}AFX_DATA_MAP
	m_sliderRangeMin.SetRange(0,30);
}


BEGIN_MESSAGE_MAP(CVideoOSCRuleSetDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoOSCRuleSetDlg)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RANGE_MIN, OnReleasedcaptureSliderRangeMin)
	ON_BN_CLICKED(IDC_BTN_RULE_SET, OnBtnRuleSet)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoOSCRuleSetDlg message handlers

BOOL CVideoOSCRuleSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
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
	
	pComboBox->SetCurSel(m_Rule.iLevel);

	CButton* pCheck = (CButton*)GetDlgItem(IDC_CHECK_SHOWTRACE);
	if (m_Rule.iShowTrack!=0)
	{
		pCheck->SetCheck(BST_CHECKED);
	}
	else
	{
		pCheck->SetCheck(BST_UNCHECKED);
	}

	if (m_Rule.iAbandumEnable)
	{
		((CButton*)GetDlgItem(IDC_RADIO_ABANDUM))->SetCheck(BST_CHECKED);
	}
	else if (m_Rule.iStolenEnable)
	{
		((CButton*)GetDlgItem(IDC_RADIO_STOLEN))->SetCheck(BST_CHECKED);
	}
	else if (m_Rule.iNoParkingEnable)
	{
		((CButton*)GetDlgItem(IDC_RADIO_NOPARKING))->SetCheck(BST_CHECKED);
		
	}
	m_sliderRangeMin.SetPos(m_Rule.stNoParkingRulePara.stOscPara.nSizeMin);//显示其中一个最小像素，保存时，保存所有
	OnReleasedcaptureSliderRangeMin(0,0);
	return TRUE;  
}

void CVideoOSCRuleSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_Rule.iAbandumEnable = ((CButton*)GetDlgItem(IDC_RADIO_ABANDUM))->GetCheck();
	m_Rule.iStolenEnable = ((CButton*)GetDlgItem(IDC_RADIO_STOLEN))->GetCheck();
	m_Rule.iNoParkingEnable = ((CButton*)GetDlgItem(IDC_RADIO_NOPARKING))->GetCheck();
	m_Rule.iShowTrack = ((CButton*)GetDlgItem(IDC_CHECK_SHOWTRACE))->GetCheck();
	m_Rule.iLevel = ((CComboBox*)GetDlgItem(IDC_COMBO_SENSITIVITY_LEVEL))->GetCurSel();
	int Slider = m_sliderRangeMin.GetPos();
	m_Rule.stNoParkingRulePara.stOscPara.nSizeMin = Slider;
	m_Rule.stObjAbandumRulePara.stOscPara.nSizeMin = Slider;
	m_Rule.stObjStolenRulePara.stOscPara.nSizeMin = Slider;
	//警戒方式在每次设置完后保存
	CDialog::OnOK();
}

void CVideoOSCRuleSetDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		
	}
}

void CVideoOSCRuleSetDlg::OnReleasedcaptureSliderRangeMin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int Slider = m_sliderRangeMin.GetPos();

	CString str;
	str.Format("%d",Slider);
	str+="%";
	GetDlgItem(IDC_STATIC_SLIDER_MIN)->SetWindowText(str);
	
	CRect rc;
	GetDlgItem(IDC_STATIC_SLIDER_MIN)->GetWindowRect(&rc);//异步（局部改变）
	ScreenToClient(&rc);
	InvalidateRect(rc);
//	*pResult = 0;
}


void CVideoOSCRuleSetDlg::OnBtnRuleSet() 
{
	// TODO: Add your control notification handler code here
	
	RulePara rulePara;
	m_Rule.iAbandumEnable = ((CButton*)GetDlgItem(IDC_RADIO_ABANDUM))->GetCheck();
	m_Rule.iStolenEnable = ((CButton*)GetDlgItem(IDC_RADIO_STOLEN))->GetCheck();
	m_Rule.iNoParkingEnable = ((CButton*)GetDlgItem(IDC_RADIO_NOPARKING))->GetCheck();
	if (m_Rule.iAbandumEnable)
	{
		rulePara = ABANDUM;
	}
	else if(m_Rule.iStolenEnable)
	{
		rulePara = STOLEN;
	}
	else if (m_Rule.iNoParkingEnable)
	{
		rulePara = NOPARKING;
	}
	switch (rulePara)
	{
	case ABANDUM:
		dlgAvdRuleArea.initDlgInfo(&m_Rule.stObjAbandumRulePara,ABANDUM,m_nChannelNum);
		break;
	case STOLEN:
		dlgAvdRuleArea.initDlgInfo(&m_Rule.stObjStolenRulePara,STOLEN,m_nChannelNum);
		break;
	case NOPARKING:
		dlgAvdRuleArea.initDlgInfo(&m_Rule.stNoParkingRulePara,NOPARKING,m_nChannelNum);
		break;
	}
	if (IDOK == dlgAvdRuleArea.DoModal())
	{
		URP_SDK_POINT_S ptTemp;
		for (int i = 0; i < NET_MAX_OSC_NUM; i++ )
		{
			for (int j = 0 ; j < dlgAvdRuleArea.m_curRule.astSpclRgs[i].stOscRg.iPointNum; j++)
			{
				ptTemp = dlgAvdRuleArea.m_curRule.astSpclRgs[i].stOscRg.astPoint[j];
				dlgAvdRuleArea.m_curRule.astSpclRgs[i].stOscRg.astPoint[j].X = (short)(ptTemp.X*(8192/(double)dlgAvdRuleArea.m_nPicWidth));
				dlgAvdRuleArea.m_curRule.astSpclRgs[i].stOscRg.astPoint[j].Y = (short)(ptTemp.Y*(8192/(double)dlgAvdRuleArea.m_nPicHeight));
			}	
		}
		switch (rulePara)
		{
		case ABANDUM:
			memcpy(&m_Rule.stObjAbandumRulePara,&dlgAvdRuleArea.m_curRule,sizeof(SDK_URP_OSC_RULE_PARA_S));
			break;
		case STOLEN:
			memcpy(&m_Rule.stObjStolenRulePara,&dlgAvdRuleArea.m_curRule,sizeof(SDK_URP_OSC_RULE_PARA_S));
			break;
		case NOPARKING:
			memcpy(&m_Rule.stNoParkingRulePara,&dlgAvdRuleArea.m_curRule,sizeof(SDK_URP_OSC_RULE_PARA_S));
			break;
		}
	}	
}


void CVideoOSCRuleSetDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if( pScrollBar->GetDlgCtrlID() == IDC_SLIDER_RANGE_MIN )
	{
		// nPos就是此时滑杆的位置，显示到 CEdit 就可以了
		int Slider = ((CSliderCtrl*)pScrollBar)->GetPos();
		CString str;
		str.Format("%d",Slider);
		str+="%";
		GetDlgItem(IDC_STATIC_SLIDER_MIN)->SetWindowText(str);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
