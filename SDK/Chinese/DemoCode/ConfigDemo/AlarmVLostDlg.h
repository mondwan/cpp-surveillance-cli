#if !defined(AFX_ALARMVLOSTDLG_H__5C0379AA_5DDE_4795_872D_897BA01B170B__INCLUDED_)
#define AFX_ALARMVLOSTDLG_H__5C0379AA_5DDE_4795_872D_897BA01B170B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmVLostDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmVLostDlg dialog

class CAlarmVLostDlg : public CDialog
{
// Construction
public:
	SDK_VIDEOLOSSCONFIG_ALL m_VLossCfgAll;
	void CleanAll();
	BOOL SaveVlossInfo();
	void InitDlgInfo(SDK_VIDEOLOSSCONFIG_ALL *pVLossCfgAll, int nChannelNum, int nAlarmInNum, int nAlarmOutNum,SDK_SystemFunction *pSysFunc);
	CAlarmVLostDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmVLostDlg)
	enum { IDD = IDD_CONFIG_ALARM_VIDEOLOST };
	CComboBox	m_ctlChannel;
	CButton	m_ctlScreenTip;
	CButton	m_ctlFtp;
	CButton	m_ctlEnableAlarm;
	CButton	m_ctlEmail;
	CButton	m_ctlBeep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmVLostDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmVLostDlg)
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
	void InitWndShow();
	int m_nChannelNum;
	CButton *m_pBtnsRecord[NET_MAX_CHANNUM];
	CButton *m_pBtnsTour[NET_MAX_CHANNUM];
	CButton *m_pBtnsAlarmOut[NET_MAX_CHANNUM];
	CButton *m_pBtnsSnap[NET_MAX_CHANNUM];
	SDK_SystemFunction m_SysFunc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMVLOSTDLG_H__5C0379AA_5DDE_4795_872D_897BA01B170B__INCLUDED_)
