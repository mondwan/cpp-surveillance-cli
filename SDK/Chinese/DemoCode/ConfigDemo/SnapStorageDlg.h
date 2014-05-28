#if !defined(AFX_SNAPSTORAGEDLG_H__2425A513_B0DF_49E6_82C4_3CF3C3E5271A__INCLUDED_)
#define AFX_SNAPSTORAGEDLG_H__2425A513_B0DF_49E6_82C4_3CF3C3E5271A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnapStorageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSnapStorageDlg dialog

class CSnapStorageDlg : public CDialog
{
// Construction
public:
	CSnapStorageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSnapStorageDlg)
	enum { IDD = IDD_DLG_SNAPSHOT };
	CButton	m_ctlALM4;
	CButton	m_ctlALM3;
	CButton	m_ctlALM2;
	CButton	m_ctlALM1;
	CButton	m_ctlDTT4;
	CButton	m_ctlDTT3;
	CButton	m_ctlDTT2;
	CButton	m_ctlDTT1;
	CButton	m_ctlPRD4;
	CButton	m_ctlPRD3;
	CButton	m_ctlPRD2;
	CButton	m_ctlPRD1;
	CComboBox	m_ctlRecordWeek;
	CComboBox	m_ctlChannel;
	UINT	m_prd1StartHour;
	UINT	m_prd2StartHour;
	UINT	m_prd3StartHour;
	UINT	m_prd4StartHour;
	UINT	m_prd1StartMinute;
	UINT	m_prd2StartMinute;
	UINT	m_prd3StartMinute;
	UINT	m_prd4StartMinute;
	UINT	m_prd4EndHour;
	UINT	m_prd4EndMinute;
	UINT	m_prd1EndHour;
	UINT	m_prd2EndHour;
	UINT	m_prd3EndHour;
	UINT	m_prd1EndMinute;
	UINT	m_prd2EndMinute;
	UINT	m_prd3EndMinute;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnapStorageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation

protected:

	// Generated message map functions
	//{{AFX_MSG(CSnapStorageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnRadio0();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnEditchangeComboWeek();
	afx_msg void OnEditchangeComboChannel();
	virtual void OnOK();
	afx_msg void OnBTBUpDate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		void InitDlgInfo(SDK_SnapshotConfigAll *precordSet,int nChannelNum);
		int m_nLastWeek;
		int m_nLastChannel;
		int m_nChannelNum;
		SDK_SnapshotConfigAll m_SnapCfg;
		void ShowWindow(int nChannel);
		void ShowPeriodInfo(SDK_TIMESECTION *pTime,int nNum ,UINT typeMask);
		void ShowTime(BOOL bRet);
		SDK_TIMESECTION	*m_pTimeSectValue[NET_N_TSECT];
		void CleanAll();
		void SaveWeekInfo(int nWeek);
		void SaveSnapInfo(int nIndex);
		void SaveWeekAll();
		void SaveRecordAll();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNAPSTORAGEDLG_H__2425A513_B0DF_49E6_82C4_3CF3C3E5271A__INCLUDED_)
