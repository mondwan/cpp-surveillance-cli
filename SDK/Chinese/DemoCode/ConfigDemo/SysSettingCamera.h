#if !defined(AFX_SYSSETTINGCAMERA_H__7F52C5CF_B2A7_4E85_952C_E3E91B436BD9__INCLUDED_)
#define AFX_SYSSETTINGCAMERA_H__7F52C5CF_B2A7_4E85_952C_E3E91B436BD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysSettingCamera.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysSettingCamera dialog

class CSysSettingCamera : public CDialog
{
// Construction
public:
	void CleanAll();
	void InitDlgInfo(SDK_AllCameraParam* pCameraParaAll, SDK_CameraAbility* pCameraAbility, int nTotalNum);
	CSysSettingCamera(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysSettingCamera)
	enum { IDD = IDD_DLG_CAMERAPARA };
	CComboBox	m_ctrlNTLevel;
	CButton	m_ctrlTime;
	CButton	m_ctrlIcrSwap;
	CEdit	m_editDebug;
	CSliderCtrl	m_ctrlDnc;
	CSliderCtrl	m_ctrlSensitivity;
	CButton	m_ctrlFilcker;
	CEdit	m_editGainMost;
	CComboBox	m_ctrShutter;
	CComboBox	m_ctrlAutoGain;
	CEdit	m_editDefault;
	CEdit	m_editAE;
	CComboBox	m_ctrlIRCUT;
	CEdit	m_editMosttime;
	CEdit	m_EditLeasttime;
	CButton	m_ctrlroll;
	CButton	m_ctrlMirror;
	CComboBox	m_ctrlAuto;
	CComboBox	m_ctrlBackLight;
	CComboBox	m_ctrlType;
	CComboBox	m_ctrlExposure;
	CComboBox	m_ctrlDayNight;
	CComboBox	m_ctrlBalance;
	CComboBox	m_ctrlChannel;
	BOOL	m_bMirror;
	BOOL	m_bRoll;
	BOOL	m_bFlicker;
	BOOL	m_bIcrSwap;
	int		m_nTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysSettingCamera)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSysSettingCamera)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboExposure();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnBtnUpgrade();
	afx_msg void OnSelchangeComboAutogain();
	afx_msg void OnCustomdrawSliderDnc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderSensitivity(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditLeasttime();
	afx_msg void OnEnKillfocusEditLeasttime();
	afx_msg void OnEnChangeEditMosttime();
	afx_msg void OnEnKillfocusEditMosttime();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnEnChangeEditAe();
	afx_msg void OnEnKillfocusEditAe();
	afx_msg void OnEnChangeEditGainmost();
	afx_msg void OnEnKillfocusEditGainmost();
	afx_msg void OnDestroy();
	afx_msg void OnRadioDay();
	afx_msg void OnRadioNight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveCameraAll();
	void ShowCamera(int nChannel);
	void SaveCamera(int nChannel);
	SDK_CameraAbility m_CameraAbility;
	SDK_AllCameraParam m_AllCameraPara;
	int m_nLastNum;
	int m_nTotalNum;
	int nSliderDncMin;
	int nSliderDncMax;
	int nSliderSstMin;
	int nSliderSstMax;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSSETTINGCAMERA_H__7F52C5CF_B2A7_4E85_952C_E3E91B436BD9__INCLUDED_)
