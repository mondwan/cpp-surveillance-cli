#if !defined(AFX_ALARMMOTION_H__02E0B60A_4DF4_49AF_8898_AEA80E0F8181__INCLUDED_)
#define AFX_ALARMMOTION_H__02E0B60A_4DF4_49AF_8898_AEA80E0F8181__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmMotion.h : header file
#include "afxwin.h"

//

/////////////////////////////////////////////////////////////////////////////
// CAlarmMotion dialog

class CAlarmMotion : public CDialog
{
// Construction
public:
	BOOL SaveMotionInfo();
	void CleanAll();
	SDK_MOTIONCONFIG_ALL m_MotionCfgAll;
	void InitDlgInfo(SDK_MOTIONCONFIG_ALL *pMotionCfgAll,int nChannelNum,int nAlarmInNum,int nAlarmOutNum,SDK_MotionDetectFunction *pMotionDectFuc,SDK_SystemFunction *pSysFunc);
	CAlarmMotion(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CAlarmMotion)
	enum { IDD = IDD_CONFIG_ALARM_MOTION };
	CButton	m_ctlEnableAlarm;
	CButton	m_ctlScreenTip;
	CButton	m_ctlFtp;
	CButton	m_ctlEmail;
	CButton	m_ctlBeep;
	CComboBox	m_ctlChannelNum;
	CComboBox	m_ctrlDelicacy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmMotion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmMotion)
	afx_msg void OnButtonSetarea();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboChannelnum();
	afx_msg void OnCheckEnablealarm();
	afx_msg void OnBtnPtzlink();
	afx_msg void OnBtnAlarmCtrlPeriod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Clear();
	int m_nAlarmOutNum;
	void ShowInfo(int nIndex);
	int m_nLastChannel;
	int m_nChannelNum;
	void InitWndShow();
	CButton *m_pBtnsRecord[NET_MAX_CHANNUM];
	CButton *m_pBtnsTour[NET_MAX_CHANNUM];
	CButton *m_pBtnsAlarmOut[NET_MAX_CHANNUM];
	CButton *m_pBtnsSnap[NET_MAX_CHANNUM];
	int m_nRow;
	int m_nCol;
	SDK_SystemFunction m_SysFunc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMMOTION_H__02E0B60A_4DF4_49AF_8898_AEA80E0F8181__INCLUDED_)
