#if !defined(AFX_COVERAREADLG_H__8AEBF58F_4410_4D48_8C0C_A817E843D22B__INCLUDED_)
#define AFX_COVERAREADLG_H__8AEBF58F_4410_4D48_8C0C_A817E843D22B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoverAreaDlg.h : header file
//
#include "NewCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CCoverAreaDlg dialog

class CCoverAreaDlg : public CDialog
{
// Construction
public:
	SDK_CONFIG_VIDEOWIDGET * GetCover();
	int m_nCoverNum;
	int m_nChannelNum;
	void InitDlgInfo();
	CNewCtrl m_ctrlCover1;
	CNewCtrl m_ctrlCover2;
	CNewCtrl m_ctrlCover3;
	CNewCtrl m_ctrlCover4;
	SDK_CONFIG_VIDEOWIDGET m_Videowidget;
	int m_nWidth;
	int m_nHeight;
	CCoverAreaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCoverAreaDlg)
	enum { IDD = IDD_DLG_COVER_AREA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoverAreaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoverAreaDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	TCHAR m_strFileName[256];
	BOOL GetAppPath(char *szPath);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COVERAREADLG_H__8AEBF58F_4410_4D48_8C0C_A817E843D22B__INCLUDED_)
