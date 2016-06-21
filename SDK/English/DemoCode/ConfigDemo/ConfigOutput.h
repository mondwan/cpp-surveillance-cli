#if !defined(AFX_CONFIGOUTPUT_H__FAE70234_97A4_4FC0_A809_52CE31966939__INCLUDED_)
#define AFX_CONFIGOUTPUT_H__FAE70234_97A4_4FC0_A809_52CE31966939__INCLUDED_

#include "CoverSetDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigOutput.h : header file
//
#define iWndAlphaSlideMin   128	
#define iWndAlphaSlideMax   255
#define IDC_BTN_OUTPUT_COVER	WM_USER + 200
/////////////////////////////////////////////////////////////////////////////
// CConfigOutput dialog

class CConfigOutput : public CDialog
{
// Construction
public:
	void CleanAll();
	CCoverSetDlg m_dlgCoverSet;
	int m_nLastChanItem;
	OUTPUTCONFIGALL m_outputCfgAll;
	int m_nbyChanNum;
	void InitDlgInfo(OUTPUTCONFIGALL* pOutputCfgAll,int nbyChanNum);
	CConfigOutput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigOutput)
	enum { IDD = IDD_CONFIG_OUTPUT };
	CComboBox	m_ctlChannel;
	CButton	m_ctlTimeTitle;
	CButton	m_ctlChanTitle;
	CButton	m_ctlCover;
	CButton	m_ctlAlmStatusD;
	CButton	m_ctlChanTitleD;
	CButton	m_ctlTimeTitleD;
	CSliderCtrl	m_ctlTransparD;
	CButton	m_ctlResitWiteD;
	CButton	m_ctlRecordStatusD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigOutput)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnChanNS();
	afx_msg void OnBtnRefresh();
	afx_msg void OnCheckCoverBtns();
	afx_msg void OnCusdraSliderTransparDvr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnTitleset();
	afx_msg void OnBtnApply();
	afx_msg void OnBtnCovset();
	afx_msg void OnSelchangeComboChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetBtns();
	void GetBtns();
	CButton* m_pBtnsCover[NET_COVERNUM];

	void InitVidWdgCfgInfo();
	void InitGUISetCfgInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGOUTPUT_H__FAE70234_97A4_4FC0_A809_52CE31966939__INCLUDED_)
