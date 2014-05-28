#if !defined(AFX_CONFIGRECORD_H__F2950F1C_EA8C_4477_BFAE_3510D6AF7D8C__INCLUDED_)
#define AFX_CONFIGRECORD_H__F2950F1C_EA8C_4477_BFAE_3510D6AF7D8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigRecord.h : header file
//
#define		WM_TIMESECT_CTRL	(WM_USER + 100)
/////////////////////////////////////////////////////////////////////////////
// CConfigRecord dialog

class CConfigRecord : public CDialog
{
// Construction
public:
	void SetEditText(UINT nID, unsigned int nText, CString strFormat );
	void SetEditText(UINT nID, int nText, CString strFormat);
	void SetEditText(UINT nID, double fText, CString strFormat);
	void SetEditText(UINT nID, CString strText);
	void SaveRecordAll();
	void SaveWeekAll();
	void SaveWeekInfo(int nWeek);
	void InitDlgInfo(SDK_RECORDCONFIG_ALL *pRecordCfg,int nChannelNum);
	void ShowPeriodInfo(SDK_TIMESECTION *pTime,int nNum ,UINT typeMask);
	void CleanAll();
	CConfigRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigRecord)
	enum { IDD = IDD_CONFIG_RECORD };
	CButton	m_ctlPRD6;
	CButton	m_ctlPRD5;
	CButton	m_ctlDTT6;
	CButton	m_ctlDTT5;
	CButton	m_ctlALM6;
	CButton	m_ctlALM5;
	CButton	m_ctlPRD4;
	CButton	m_ctlPRD3;
	CButton	m_ctlPRD2;
	CButton	m_ctlPRD1;
	CButton	m_ctlDTT4;
	CButton	m_ctlDTT3;
	CButton	m_ctlDTT2;
	CButton	m_ctlDTT1;
	CButton	m_ctlALM4;
	CButton	m_ctlALM3;
	CButton	m_ctlALM2;
	CButton	m_ctlALM1;
	CButton	m_ctlRedundancy;
	CComboBox	m_ctlChannel;
	CComboBox	m_ctlRecordWeek;
	UINT	m_prd1EndHour;
	UINT	m_prd1EndMinute;
	UINT	m_prd1StartHour;
	UINT	m_prd1StartMinute;
	UINT	m_prd2EndHour;
	UINT	m_prd2StartHour;
	UINT	m_prd2StartMinute;
	UINT	m_prd2EndMinute;
	UINT	m_prd3EndHour;
	UINT	m_prd3EndMinute;
	UINT	m_prd3StartHour;
	UINT	m_prd3StartMinute;
	UINT	m_prd4EndHour;
	UINT	m_prd4EndMinute;
	UINT	m_prd4StartHour;
	UINT	m_prd4StartMinute;
	UINT	m_prd5EndHour;
	UINT	m_prd5EndMinute;
	UINT	m_prd5StartHour;
	UINT	m_prd5StartMinute;
	UINT	m_prd6EndHour;
	UINT	m_prd6EndMinute;
	UINT	m_prd6StartHour;
	UINT	m_prd6StartMinute;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigRecord)
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnSelchangeComboRecordweek();
	afx_msg void OnRadio0();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnChangeEdit(UINT nID);
	afx_msg void OnKillfocusEdit(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowTime(BOOL bRet);
	void ShowWindow(int nChannel);
	void SaveRecordInfo(int nIndex);
	int m_nLastChannel;
	SDK_RECORDCONFIG_ALL m_RecordCfg;
	int m_nLastWeek;
	int m_nChannelNum;
	SDK_TIMESECTION	*m_pTimeSectValue[NET_N_TSECT];
	BOOL m_bCheckEdit;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGRECORD_H__F2950F1C_EA8C_4477_BFAE_3510D6AF7D8C__INCLUDED_)
