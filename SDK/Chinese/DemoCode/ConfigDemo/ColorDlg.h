#if !defined(AFX_COLORDLG_H__02249CB8_DF73_4E39_B928_29816073C428__INCLUDED_)
#define AFX_COLORDLG_H__02249CB8_DF73_4E39_B928_29816073C428__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog

class CColorDlg : public CDialog
{
// Construction
public:
	CColorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorDlg)
	enum { IDD = IDD_COLOR_DLG };
	CSliderCtrl	m_ucSaturation;
	CSliderCtrl	m_ucHue;
	CSliderCtrl	m_ucContrast;
	CSliderCtrl	m_ucBright;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSliderbhd(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderdbd(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderld(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlidersd(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlideryl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonpoll();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_Bright;       //bright	
	int m_Contrast;     //contrast
	int m_Hue;          //hue
	int m_Saturation;   //saturation

public:
	void SetColor(int nBright, int nContrast, int nSaturation, int nHue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORDLG_H__02249CB8_DF73_4E39_B928_29816073C428__INCLUDED_)
