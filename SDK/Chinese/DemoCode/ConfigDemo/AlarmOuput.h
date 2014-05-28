#if !defined(AFX_ALARMOUPUT_H__98D32A8F_1505_4C5B_88FC_BE2E668F4509__INCLUDED_)
#define AFX_ALARMOUPUT_H__98D32A8F_1505_4C5B_88FC_BE2E668F4509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlarmOuput.h : header file
//

#define IDC_BTN_ALARMOUT_SET	WM_USER + 120
#define IDC_BTN_ALARMOUT_STATUS	(WM_USER + 120 + (4 * NET_MAX_CHANNUM))

/////////////////////////////////////////////////////////////////////////////
// CAlarmOuput dialog

class CAlarmOuput : public CDialog
{
// Construction
public:
	CAlarmOuput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmOuput)
	enum { IDD = IDD_CONFIG_ALARM_OUTPUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmOuput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmOuput)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioAuto();
	afx_msg void OnRadioMan();
	afx_msg void OnRadioClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL InitWndShow();
	void InitDlgInfo(SDK_AlarmOutConfigAll* pAlarmOutAll, int nAlarmOutNum);
	void Clear();
	BOOL SaveAlarmOutputInfo();

	SDK_AlarmOutConfigAll m_AlarmOutAll;
private:
	CButton *m_pBtnsAlarmOutAuto[NET_MAX_CHANNUM];
	CButton *m_pBtnsAlarmOutMan[NET_MAX_CHANNUM];
	CButton *m_pBtnsAlarmOutClose[NET_MAX_CHANNUM];
	CButton *m_pBtnsAlarmOutState[NET_MAX_CHANNUM];
	CStatic *m_pStaticAlarm[NET_MAX_CHANNUM];

	int m_nAlarmOutNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMOUPUT_H__98D32A8F_1505_4C5B_88FC_BE2E668F4509__INCLUDED_)
