#if !defined(AFX_LOCALPLAYBACK_H__5A1EAD15_DB1C_4E10_9CA3_CB013781AA1A__INCLUDED_)
#define AFX_LOCALPLAYBACK_H__5A1EAD15_DB1C_4E10_9CA3_CB013781AA1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalPlayback.h : header file
//

//play status
typedef enum PLAYSTATUS
{
	STATUS_PLAY=0,
	STATUS_STOP=1,
	STATUS_PAUSE=2,
	STATUS_RECOVER=3,
	STATUS_FAST=4,
	STATUS_SLOW=5,
	STATUS_READY=6
};

/////////////////////////////////////////////////////////////////////////////
// CLocalPlayback dialog

class CLocalPlayback : public CDialog
{
// Construction
public:
	DWORD m_PreTime;
	void SetSliderPos(float nplaypos);
	time_t m_TotalTime;
	int m_nFileLen;
	int m_SliderPos;
	int m_SlowSpeed;
	int m_FastSpeed;
	int m_PlayerStatus;
	bool m_bplaythread;
	FILE* m_pFile;
	HANDLE m_hPlayThread;
	CString m_FilePathName;
	int m_nPort;
	static unsigned int StartPlay(LPVOID parm);
	static void __stdcall SDKPlayFileEndCallback(LONG nPort,LONG nUser);
	static void __stdcall InfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser);

	void PlayEndCallback(int nPort);
	void drawOSD(LONG nPort,HDC hDc);

	CString m_strInfoFrame[100];
	CLocalPlayback(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLocalPlayback)
	enum { IDD = IDD_DLG_LOCALPLAYBACK };
	CSliderCtrl	m_ctrlSlider;
    CStatic	m_playwindow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalPlayback)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLocalPlayback)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonFast();
	afx_msg void OnButtonSlow();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnReleasedcaptureSliderfile(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALPLAYBACK_H__5A1EAD15_DB1C_4E10_9CA3_CB013781AA1A__INCLUDED_)
