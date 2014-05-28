// TestWebDlg.h : header file
//
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

#if !defined(AFX_TESTWEBDLG_H__258C7D8B_09F9_42A0_93A3_BCA998AEDB44__INCLUDED_)
#define AFX_TESTWEBDLG_H__258C7D8B_09F9_42A0_93A3_BCA998AEDB44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestWebDlg dialo
#include "PTZCtrl.h"
#include "webctrl1.h"



class CTestWebDlg : public CDialog
{
// Construction
public:
	CPTZCtrl PTZCtrlButton[17];
	CTestWebDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestWebDlg)
	enum { IDD = IDD_TESTWEB_DIALOG };
	CComboBox	m_ChannelNameCMB;
	CComboBox	m_RemotRecordCMB;
	CComboBox	m_ctrlPTZSpeed;
	CButton	m_captRoad;
	CString	m_translateWord;
	long	m_screenNumb;
	long	m_playNumb;
	CString	m_recordRoad;
	CString	m_captureRoad;
	CString	m_loginTip;
	CString	m_IP;
	long	m_port;
	CString	m_NAME;
	CString	m_PASSWORD;
	long	m_TourNumb;
	long	m_dbd;
	long	m_ld;
	long	m_sd;
	long	m_bhd;
	int		m_nSplid;
	int		m_nPreview;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestWebDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestWebDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnBtnConfig();
	afx_msg void OnBtnClientConfig();
	afx_msg void OnBtnLog();
	afx_msg void OnBtnFullScreen();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDownWebctrl1(long nFlag, long x, long y);
	afx_msg void OnBtnMoreScreen();
	afx_msg void OnBtnPlay();
	afx_msg void OnBtnPlaystop();
	afx_msg void OnBtnRecord();
	afx_msg void OnBtnStoprecord();
	afx_msg void OnBtnCapture();
	afx_msg void OnBtnStartsound();
	afx_msg void OnBtnStopSound();
	afx_msg void OnChangeEditRecordRoad();
	afx_msg void OnBtnStarttalk();
	afx_msg void OnBtnStoptalk();
	afx_msg void OnButtonPreset();
	afx_msg void OnButtonGopreset();
	afx_msg void OnButtonTour();
	afx_msg void OnButtonEditTour();
	afx_msg void OnButtonGetcolor();
	afx_msg void OnButtonSetcolor();
	afx_msg void OnLogout();
	afx_msg void OnButtonPlayall();
	afx_msg void OnButtonStopallplay();
	afx_msg void OnButtonRecordall();
	afx_msg void OnButtonStoprecordall();
	afx_msg void OnBtnRecordbychannel();
	afx_msg void OnBtnStopRecordbychannel();
	afx_msg void OnAllChannelCtrlWebctrl1(BOOL bPlay, BOOL bStopPlay, BOOL bRecord, BOOL bStopRecord);
	afx_msg void OnReboot();
	afx_msg void OnBtnPlayback();
	afx_msg void OnBtStartRemotRecord();
	afx_msg void OnBtStopRemotRecord();
	afx_msg void OnBtGetchannelname();
	afx_msg void OnButtonDeletePreset();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:	
	




	CWebctrl1 m_ocx;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTWEBDLG_H__258C7D8B_09F9_42A0_93A3_BCA998AEDB44__INCLUDED_)
