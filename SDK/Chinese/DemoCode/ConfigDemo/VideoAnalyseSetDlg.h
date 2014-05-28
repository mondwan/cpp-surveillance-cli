#if !defined(AFX_VIDEOANALYSESETDLG_H__5A4E7485_8B20_43EE_BEAA_806904FE9E19__INCLUDED_)
#define AFX_VIDEOANALYSESETDLG_H__5A4E7485_8B20_43EE_BEAA_806904FE9E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
//#include "Interface/DlgSetBase.h"
// #include "DlgRuleArea.h"
#include "afxcmn.h"
#include "DlgRuleArea.h"
// CVideoAnalyseSetDlg 对话框

class CVideoAnalyseSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CVideoAnalyseSetDlg)

public:
	CVideoAnalyseSetDlg(/*SDK_RULECONFIG* pRule,int nChannelNum,int nModuleType,CWnd* pParent = NULL*/);   // 标准构造函数
	virtual ~CVideoAnalyseSetDlg();
	void SetValue(SDK_RULECONFIG* pRule,int nChannelNum,int nModuleType);
	SDK_RULECONFIG m_Rule;
	SDK_RULECONFIG m_oldRule;
	int m_nChannelNum;
	int m_nRule;
	int m_nModuleType;
	CSliderCtrl m_sliderRangeMin;
	CSliderCtrl m_sliderTimeMin;	
	HINSTANCE OldResourceHanlde;
	CDlgRuleArea dlgRuleArea;
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_DLG_ALARM_PEARULE_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRuleSet();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckShowtrace();
	afx_msg void OnCbnSelchangeComboSensitivityLevel();
	afx_msg void OnBnClickedRadioUrpTripwire();
	afx_msg void OnBnClickedRadioUrpPerimeter();
	afx_msg void OnNMReleasedcaptureSliderRangeMin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderTimeMin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//CDlgRuleArea dlgRuleArea;
};
#endif