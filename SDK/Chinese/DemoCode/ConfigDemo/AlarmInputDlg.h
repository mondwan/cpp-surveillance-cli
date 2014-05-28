#if !defined(AFX_ALARMINPUTDLG_H__ABD824E1_D9E2_47B1_9011_CC04A8CE3162__INCLUDED_)
#define AFX_ALARMINPUTDLG_H__ABD824E1_D9E2_47B1_9011_CC04A8CE3162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmInputDlg.h : header file
//
#define IDC_BTN_RECORD	WM_USER + 10
#define IDC_BTN_TOUR	WM_USER + 50
#define IDC_BTN_ALARMOUT	WM_USER + 90
/////////////////////////////////////////////////////////////////////////////
// CAlarmInputDlg dialog

class CAlarmInputDlg : public CDialog
{
// Construction
public:
	SDK_ALARM_INPUTCONFIG_ALL m_AlarmInputCfgAll;
	static BOOL SetButtonsCheck(CButton **pBtn, DWORD dwValue, int nSize);
	static DWORD GetButtonsCheck(CButton **pBtn, int nSize);
	void CleanAll();
	BOOL SaveAlarmInputInfo();
	void InitDlgInfo(SDK_ALARM_INPUTCONFIG_ALL *pAlarmInCfgAll,int nChannelNum,int nAlarmInNum,int nAlarmOutNum,SDK_SystemFunction *pSysFunc);
	CAlarmInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmInputDlg)
	enum { IDD = IDD_CONFIG_ALARM_INPUT };
	CButton	m_ctlScreenTip;
	CButton	m_ctlBeep;
	CButton	m_ctlEmail;
	CButton	m_ctlFtp;
	CButton	m_ctlEnableAlarm;
	CComboBox	m_ctlDevType;
	CComboBox	m_ctlChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmInputDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboChannelnum();
	afx_msg void OnCheckEnablealarm();
	afx_msg void OnBtnPtzlink();
	afx_msg void OnBtnAlarmCtrlPeriod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SDK_SystemFunction m_SysFunc;
	void Clear();
	int m_nAlarmOutNum;
	int m_nLastChannel;
	void ShowInfo(int nIndex);
	void InitWndShow();
	int m_nChannelNum;
	CButton *m_pBtnsRecord[NET_MAX_CHANNUM];
	CButton *m_pBtnsTour[NET_MAX_CHANNUM];
	CButton *m_pBtnsAlarmOut[NET_MAX_CHANNUM];
	CButton *m_pBtnsSnap[NET_MAX_CHANNUM];
	int m_nAlarmInNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMINPUTDLG_H__ABD824E1_D9E2_47B1_9011_CC04A8CE3162__INCLUDED_)
