#if !defined(AFX_DIGITALCHANNELDLG_H__14823570_6582_43C5_B500_5FEF53E01E82__INCLUDED_)
#define AFX_DIGITALCHANNELDLG_H__14823570_6582_43C5_B500_5FEF53E01E82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DigitalChannelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDigitalChannelDlg dialog

class CDigitalChannelDlg : public CDialog
{
// Construction
public:
	void ClearAll();
	void SaveDigitalChnCfg();
	CDigitalChannelDlg(CWnd* pParent = NULL);   // standard constructor
	void InitDlgInfo(SDK_NetDecorderConfigAll_V3* pNetDigitChnConfig,int niDigChannel);	
	void StructToWinData(int nChannel);
	BOOL WinDataToStruct(int nChannel);
	void SaveNetConfig(int nMode);
// Dialog Data
	//{{AFX_DATA(CDigitalChannelDlg)
	enum { IDD = IDD_DLG_DIGITALCHANNEL };
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbMode;
	CButton	m_CheckEnable;
	CButton	m_CheckSync;
	CEdit	m_editTourTime;
	CListCtrl	m_CtrList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitalChannelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDigitalChannelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboConnmode();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnItemchangingListNetcfg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListNetcfg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditTourtime();
	afx_msg void OnKillfocusEditTourtime();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheckEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SDK_NetDecorderConfigAll_V3 m_NetDigitChnConfig;
//	SDK_NetDecorderConfigV3 m_pNetCfg[];
	int m_nChannelLast;
	int m_nHavCheck;   //区分单连接和多连接时选择设备的限制
	int m_nLastMode;
	bool m_bDel;
	int m_niDigChannel;
private:
	BOOL InitWndShow();
	void OnRefrush();
	
	bool m_bSetcheck;	//是否
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITALCHANNELDLG_H__14823570_6582_43C5_B500_5FEF53E01E82__INCLUDED_)
