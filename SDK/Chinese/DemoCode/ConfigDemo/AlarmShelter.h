#if !defined(AFX_ALARMSHELTER_H__2CE1D082_0DCF_4416_B9E1_B2F44CBD2156__INCLUDED_)
#define AFX_ALARMSHELTER_H__2CE1D082_0DCF_4416_B9E1_B2F44CBD2156__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmShelter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmShelter dialog

class CAlarmShelter : public CDialog
{
// Construction
public:
	SDK_BLINDDETECTCONFIG_ALL m_ShelterCfgAll;
	void CleanAll();
	BOOL SaveShelterInfo();
	void InitDlgInfo(SDK_BLINDDETECTCONFIG_ALL*pDetectCfgAll, int nChannelNum, int nAlarmInNum, int nAlarmOutNum,SDK_SystemFunction *pSysFunc);
	CAlarmShelter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmShelter)
	enum { IDD = IDD_CONFIG_ALARM_SHELTER };
	CComboBox	m_ctlDelicacy;
	CComboBox	m_ctlChannel;
	CButton	m_ctlScreenTip;
	CButton	m_ctlFtp;
	CButton	m_ctlEnableAlarm;
	CButton	m_ctlEmail;
	CButton	m_ctlBeep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmShelter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmShelter)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnablealarm();
	afx_msg void OnSelchangeComboChannelnum();
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
	SDK_SystemFunction m_SysFunc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMSHELTER_H__2CE1D082_0DCF_4416_B9E1_B2F44CBD2156__INCLUDED_)
