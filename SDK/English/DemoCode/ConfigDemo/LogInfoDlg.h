#if !defined(AFX_LOGINFODLG_H__E6703456_4601_4D73_B87A_905F02D75309__INCLUDED_)
#define AFX_LOGINFODLG_H__E6703456_4601_4D73_B87A_905F02D75309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogInfoDlg dialog

class CLogInfoDlg : public CDialog
{
// Construction
public:
	void ClearAll();
	SDK_LogSearchCondition m_searchConfig;
	CLogInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogInfoDlg)
	enum { IDD = IDD_DLG_LOGINFO };
	CListCtrl	m_listLog;
	CComboBox	m_cmbLogType;
	CTime	m_bData;
	CTime	m_bTime;
	CTime	m_eData;
	CTime	m_eTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBtnExportLog();
	afx_msg void OnButtonRemoveall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool FileWrite(CString strFileName, char *pBuf, int iLen);
	int UpdateParam(SDK_CONFIG_TYPE configType, char *pBuf, long lLength, int nChannel, BOOL bSaveAndValidate, BOOL bCheck, DWORD *lpRet);
	CString BrowseForFolder(HWND hWnd);
	void translate(const char* type,const char* data,char* buf,int len);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINFODLG_H__E6703456_4601_4D73_B87A_905F02D75309__INCLUDED_)
