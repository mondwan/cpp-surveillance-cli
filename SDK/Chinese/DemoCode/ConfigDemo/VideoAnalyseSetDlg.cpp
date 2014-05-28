// AlarmVideoAnalyseSet.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "VideoAnalyseSetDlg.h"

// CVideoAnalyseSetDlg 对话框

IMPLEMENT_DYNAMIC(CVideoAnalyseSetDlg, CDialog)
extern   CClientDemo5App   theApp;
CVideoAnalyseSetDlg::CVideoAnalyseSetDlg(/*SDK_RULECONFIG* pRule,int nChannelNum,int nModuleType,CWnd* pParent*/ /*=NULL*/) : CDialog(CVideoAnalyseSetDlg::IDD/*, pParent*/)
{
	OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
	AfxSetResourceHandle(theApp.m_hInstance);//设置新的模块  
	
	
}

void CVideoAnalyseSetDlg::SetValue(SDK_RULECONFIG* pRule,int nChannelNum,int nModuleType)
{
	m_nChannelNum = nChannelNum;
	m_nModuleType = nModuleType;
	if ( pRule!= NULL)
	{
		memcpy(&m_Rule,pRule,sizeof(m_Rule));
		memcpy(&m_oldRule,pRule,sizeof(m_oldRule));
	}
	else
	{
		memset(&m_Rule,0,sizeof(m_Rule));
		memset(&m_oldRule,0,sizeof(m_oldRule));
	} 
}

CVideoAnalyseSetDlg::~CVideoAnalyseSetDlg()
{

}

void CVideoAnalyseSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_RANGE_MIN, m_sliderRangeMin);
	DDX_Control(pDX, IDC_SLIDER_TIME_MIN, m_sliderTimeMin);
	m_sliderRangeMin.SetRange(0,30);
	m_sliderTimeMin.SetRange(0,60);
}

BEGIN_MESSAGE_MAP(CVideoAnalyseSetDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_RULE_SET, CVideoAnalyseSetDlg::OnBnClickedBtnRuleSet)
	ON_BN_CLICKED(IDOK, CVideoAnalyseSetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_SHOWTRACE, CVideoAnalyseSetDlg::OnBnClickedCheckShowtrace)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSITIVITY_LEVEL, CVideoAnalyseSetDlg::OnCbnSelchangeComboSensitivityLevel)
	ON_BN_CLICKED(IDC_RADIO_URP_TRIPWIRE, CVideoAnalyseSetDlg::OnBnClickedRadioUrpTripwire)
	ON_BN_CLICKED(IDC_RADIO_URP_PERIMETER, CVideoAnalyseSetDlg::OnBnClickedRadioUrpPerimeter)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RANGE_MIN,CVideoAnalyseSetDlg::OnNMReleasedcaptureSliderRangeMin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIME_MIN,CVideoAnalyseSetDlg::OnNMReleasedcaptureSliderTimeMin)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()
// CVideoAnalyseSetDlg 消息处理程序

BOOL CVideoAnalyseSetDlg::OnInitDialog()
{
	_CWndCS(this);
	CString strText;
	CComboBox *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_SENSITIVITY_LEVEL);
	strText.Format("%s", _CS("ConfigVideo.High") );
	int nInsert = pComboBox->AddString(strText);
	pComboBox->SetItemData(nInsert, 0);

	strText.Format("%s", _CS("ConfigVideo.Middle") );
	nInsert = pComboBox->AddString(strText);
	pComboBox->SetItemData(nInsert, 1);

	strText.Format("%s", _CS("ConfigVideo.Lower") );
	nInsert = pComboBox->AddString(strText);
	pComboBox->SetItemData(nInsert, 2);

	pComboBox->SetCurSel(m_oldRule.stRulePea.iLevel);
	
	CButton* pCheck = (CButton*)GetDlgItem(IDC_CHECK_SHOWTRACE);
	if (m_oldRule.stRulePea.iShowTrack!=0)
	{
		pCheck->SetCheck(BST_CHECKED);
	}
	else
	{
		pCheck->SetCheck(BST_UNCHECKED);
	}
	return CDialog::OnInitDialog();
}

void CVideoAnalyseSetDlg::OnBnClickedBtnRuleSet()
{
	// TODO: 在此添加控件通知处理程序代码
	//ShowWindow(SW_HIDE);
 // 	CDlgOscRuleArea dlgRuleArea;

 	dlgRuleArea.InitDlgInfo(&m_oldRule,m_nRule,m_nChannelNum);
  	if (IDOK==dlgRuleArea.DoModal())
  	{
  		if (m_nRule == SDK_ANALYSE_TRIPWIRE)
  		{
  			for (int i=0 ; i < SDK_URP_MAX_TRIPWIRE_CNT ; i++)
  			{
  				 SDK_URP_LINE_S lineTemp;
  				if (dlgRuleArea.m_curTripwireRule.astLines[i].iValid)
  				{
  					lineTemp = dlgRuleArea.m_curTripwireRule.astLines[i].stLine;
  					dlgRuleArea.m_curTripwireRule.astLines[i].stLine.stStartPt.X = (short)(lineTemp.stStartPt.X*(8192/(double)dlgRuleArea.m_nPicWidth));
  					dlgRuleArea.m_curTripwireRule.astLines[i].stLine.stStartPt.Y = (short)(lineTemp.stStartPt.Y*(8192/(double)dlgRuleArea.m_nPicHeight));
  					dlgRuleArea.m_curTripwireRule.astLines[i].stLine.stEndPt.X = (short)(lineTemp.stEndPt.X*(8192/(double)dlgRuleArea.m_nPicWidth));
  					dlgRuleArea.m_curTripwireRule.astLines[i].stLine.stEndPt.Y = (short)(lineTemp.stEndPt.Y*(8192/(double)dlgRuleArea.m_nPicHeight));
  				}
  			}
  			memcpy(&m_oldRule.stRulePea.stTripwireRulePara,&dlgRuleArea.m_curTripwireRule,sizeof(SDK_URP_TRIPWIRE_RULE_PARA_S));
  		}
  		else if (m_nRule == SDK_ANALYSE_PERIMETER)
  		{
  			URP_SDK_POINT_S ptTemp;
  			for (int i=0 ; i<dlgRuleArea.m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum; i++)
  			{
  				ptTemp = dlgRuleArea.m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[i];
  				dlgRuleArea.m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[i].X = (short)(ptTemp.X*(8192/(double)dlgRuleArea.m_nPicWidth));
  				dlgRuleArea.m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[i].Y = (short)(ptTemp.Y*(8192/(double)dlgRuleArea.m_nPicHeight));
  			}	
  			memcpy(&m_oldRule.stRulePea.stPerimeterRulePara,&dlgRuleArea.m_curPerimeterRule,sizeof(SDK_URP_PERIMETER_RULE_PARA_S));
  		}		
  	}
  	ShowWindow(SW_SHOW);
}	

void CVideoAnalyseSetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	memcpy(&m_Rule,&m_oldRule,sizeof(SDK_RULECONFIG));
	OnOK();
}

void CVideoAnalyseSetDlg::OnBnClickedCheckShowtrace()
{
	UpdateData();
	m_oldRule.stRulePea.iShowTrack = ((CButton*)GetDlgItem(IDC_CHECK_SHOWTRACE))->GetCheck();
	// TODO: 在此添加控件通知处理程序代码
}

void CVideoAnalyseSetDlg::OnCbnSelchangeComboSensitivityLevel()
{
	UpdateData();
	m_oldRule.stRulePea.iLevel = ((CComboBox*)GetDlgItem(IDC_COMBO_SENSITIVITY_LEVEL))->GetCurSel();
	// TODO: 在此添加控件通知处理程序代码
}

void CVideoAnalyseSetDlg::OnBnClickedRadioUrpTripwire()
{
	m_nRule = SDK_ANALYSE_TRIPWIRE;
	m_oldRule.stRulePea.iPerimeterEnable = 0;
	m_oldRule.stRulePea.iTripWireEnable = 1;


	// TODO: 在此添加控件通知处理程序代码
}

void CVideoAnalyseSetDlg::OnBnClickedRadioUrpPerimeter()
{
	m_nRule = SDK_ANALYSE_PERIMETER;
	m_oldRule.stRulePea.iPerimeterEnable = 1;
	m_oldRule.stRulePea.iTripWireEnable = 0;
	// TODO: 在此添加控件通知处理程序代码
}

void CVideoAnalyseSetDlg::OnNMReleasedcaptureSliderRangeMin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
	
	int Slider = m_sliderRangeMin.GetPos();
	m_oldRule.stRulePea.stPerimeterRulePara.stLimitPara.iMinDist = Slider;
	m_oldRule.stRulePea.stTripwireRulePara.stLimitPara.iMinDist = Slider;
	CString str;
	str.Format("%d",Slider);
	str+="%";
	GetDlgItem(IDC_STATIC_SLIDER_MIN)->SetWindowText(str);

	CRect rc;
	GetDlgItem(IDC_STATIC_SLIDER_MIN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	InvalidateRect(rc);
}

void CVideoAnalyseSetDlg::OnNMReleasedcaptureSliderTimeMin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;

	int Slider = m_sliderTimeMin.GetPos();
	m_oldRule.stRulePea.stPerimeterRulePara.stLimitPara.iMinTime = Slider;
	m_oldRule.stRulePea.stTripwireRulePara.stLimitPara.iMinTime = Slider;
	CString str;
	str.Format("%d",Slider);
	str+=_CS("OneClick.Min") ;
	GetDlgItem(IDC_STATIC_SLIDER_MAX)->SetWindowText(str);

	CRect rc;
	GetDlgItem(IDC_STATIC_SLIDER_MAX)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	InvalidateRect(rc);
}

void CVideoAnalyseSetDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		if (m_oldRule.stRulePea.iTripWireEnable)
		{
			((CButton*)GetDlgItem(IDC_RADIO_URP_TRIPWIRE))->SetCheck(BST_CHECKED);
			m_nRule = SDK_ANALYSE_TRIPWIRE;
		}
		else if (m_oldRule.stRulePea.iPerimeterEnable)
		{
			((CButton*)GetDlgItem(IDC_RADIO_URP_PERIMETER))->SetCheck(BST_CHECKED);
			m_nRule = SDK_ANALYSE_PERIMETER;
		}
		m_sliderRangeMin.SetPos(m_oldRule.stRulePea.stPerimeterRulePara.stLimitPara.iMinDist);
		m_sliderTimeMin.SetPos(m_oldRule.stRulePea.stPerimeterRulePara.stLimitPara.iMinTime);
		OnNMReleasedcaptureSliderRangeMin(0,0);
		OnNMReleasedcaptureSliderTimeMin(0,0);
	}

	// TODO: 在此处添加消息处理程序代码
}
