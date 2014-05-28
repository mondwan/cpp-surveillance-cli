#if !defined(AFX_CONFIGPTZ_H__35E169FA_9A1B_4D41_9060_67C74222454B__INCLUDED_)
#define AFX_CONFIGPTZ_H__35E169FA_9A1B_4D41_9060_67C74222454B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigPtz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigPtz dialog

class CConfigPtz : public CDialog
{
// Construction
public:
	void CleanAll();
	void SavePtzInfo();
	void ShowPtzInfo(int nIndex);
	int m_nChannelNum;
	int m_nLastChannel;
	SDK_PTZPROTOCOLFUNC m_PtzProtocol;
	SDK_STR_PTZCONFIG_ALL m_PtzCfgAll;

	SDK_STR_RS485CONFIG_ALL m_RS485;
	void InitDlgInfo(SDK_STR_PTZCONFIG_ALL *pPtzCfgAll, int nChannel, SDK_PTZPROTOCOLFUNC *pPtzProtocol,SDK_STR_RS485CONFIG_ALL *pRS485);
	CConfigPtz(CWnd* pParent = NULL);   // standard constructor
	void ShowRS485(int nShow);
	bool m_bSupport485;
// Dialog Data
	//{{AFX_DATA(CConfigPtz)
	enum { IDD = IDD_DLG_SYS_PTZ };
	CComboBox	m_cmbBaundrate485;
	CComboBox	m_cmbConfirm485;
	CComboBox	m_cmbProtocol485;
	CComboBox	m_cmbData485;
	CComboBox	m_cmbStoppos485;
	CEdit	m_editAddress485;
	CComboBox	m_cmbConfirm;
	CComboBox	m_cmbStoppos;
	CComboBox	m_cmbData;
	CComboBox	m_cmbBaundrate;
	CEdit	m_editAddress;
	CComboBox	m_cmbProtocol;
	CComboBox	m_cmbChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigPtz)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigPtz)
	afx_msg void OnBtnUpgrade();
	virtual void OnOK();
	afx_msg void OnSelchangeComboChannel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditAddress();
	afx_msg void OnChangeEditAddressRs485();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGPTZ_H__35E169FA_9A1B_4D41_9060_67C74222454B__INCLUDED_)
