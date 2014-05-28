#if !defined(AFX_ALARMEXCEPTION_H__59B7B94E_76FF_4347_BC82_49A069EB97BF__INCLUDED_)
#define AFX_ALARMEXCEPTION_H__59B7B94E_76FF_4347_BC82_49A069EB97BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmException.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmException dialog

typedef enum
{
	STORAGE_NOEXIT = 0,
		STORAGE_LOWSPACE,
		STORAGE_FAILURE,
		NET_IPCONFLICT,
		NET_NETABORT,
		STORAGE_NR
};
class CAlarmException : public CDialog
{
	// Construction
public:
	CAlarmException(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CAlarmException)
	enum { IDD = IDD_DLG_ALARM_EXCEPTION };
	CEdit	m_editPercentage;
	CButton	m_checkScreenTip;
	CButton	m_checkBeep;
	CButton	m_checkEable;
	CComboBox	m_ctrlEvent;
	int		m_edit;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmException)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CAlarmException)
	afx_msg void OnBtnRefresh();
	afx_msg void OnSelchangeComboEvent();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangeEditPercentage();
	afx_msg void OnCheckScreenTip();
	afx_msg void OnCheckBeep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL InitWndShow();
	void InitDlgInfo(SDK_VIDEOLOSSCONFIG *pStorageNE,SDK_VIDEOLOSSCONFIG *pStorageFL,SDK_VIDEOLOSSCONFIG *pNetipCfg,SDK_VIDEOLOSSCONFIG *pNetaBort,SDK_SystemFunction *pSysFunc,SDK_StorageLowSpaceConfig *pStorageLSCfg);
	BOOL SaveAlarmExceptionInfo();
	void ShowInfo();
	void CleanAll();
	SDK_VIDEOLOSSCONFIG m_OldExceptionNoExist;
	SDK_VIDEOLOSSCONFIG m_OldExceptionFailed;
	SDK_VIDEOLOSSCONFIG m_OldExceptionIpConflict;
	SDK_VIDEOLOSSCONFIG m_ExceptionNoExist;
	SDK_VIDEOLOSSCONFIG m_ExceptionFailed;
	SDK_StorageLowSpaceConfig m_ExceptionLowSpace;
	SDK_StorageLowSpaceConfig m_OldExceptionLowSpace;
	SDK_VIDEOLOSSCONFIG m_OldExceptionNetAbort;
private:

	int m_nLastEvent;
	bool m_bGet[STORAGE_NR];
	
	
	SDK_VIDEOLOSSCONFIG m_ExceptionIpConflict;
	
	SDK_VIDEOLOSSCONFIG m_ExceptionNetAbort;

	
	SDK_SystemFunction *m_pSysFucAll;
	
public:
//	CComboBox m_ctrlEvent;
//	CButton m_checkEable;
//	CButton m_checkBeep;
//	CButton m_checkScreenTip;
//	CEdit m_editPercentage;
	afx_msg void OnBnClickedCheckEnable();
// 	afx_msg void OnEnChangeEditPercentage();
// 	afx_msg void OnEnKillfocusEditPercentage();
private:
	bool m_bNetIP;
	bool m_bNetAbort;
	bool m_bStorageFailed;
	bool m_bStorageLess;
	bool m_bStorageNoExist;
public:
	void ReInit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMEXCEPTION_H__59B7B94E_76FF_4347_BC82_49A069EB97BF__INCLUDED_)
