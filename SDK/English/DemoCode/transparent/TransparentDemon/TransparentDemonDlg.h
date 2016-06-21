// TransparentDemonDlg.h : header file
//

#if !defined(AFX_TRANSPARENTDEMONDLG_H__A4C5F386_3A3A_43CA_90D1_E2815348317A__INCLUDED_)
#define AFX_TRANSPARENTDEMONDLG_H__A4C5F386_3A3A_43CA_90D1_E2815348317A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTransparentDemonDlg dialog

class CTransparentDemonDlg : public CDialog
{
// Construction
public:
	CTransparentDemonDlg(CWnd* pParent = NULL);	// standard constructor
	~CTransparentDemonDlg();
	long m_loginID;

// Dialog Data
	//{{AFX_DATA(CTransparentDemonDlg)
	enum { IDD = IDD_TRANSPARENTDEMON_DIALOG };
	CComboBox	m_cmbStopposRS;
	CComboBox	m_cmbBaundrateRS;
	CComboBox	m_cmbDataRS;
	CComboBox	m_cmbConfirmRS;
	CString	m_ip;
	CString	m_passWord;
	int		m_port;
	CString	m_userName;
	CString	m_strRead;
	CString	m_strWrite;
	BOOL	m_b485;
	BOOL    m_hex;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentDemonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTransparentDemonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONLogin();
	afx_msg void OnBUTTONOpen();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonWrite();
	afx_msg void OnBUTTONClean();
	afx_msg void OnCheckHex();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int Str2Hex(CString str, char* data);
	char HexChar(char c);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTDEMONDLG_H__A4C5F386_3A3A_43CA_90D1_E2815348317A__INCLUDED_)
