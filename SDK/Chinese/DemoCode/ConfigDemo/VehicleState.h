#if !defined(AFX_VEHICLESTATE_H__0640B1EC_6B4B_4507_8DBE_85CCDE30DD5E__INCLUDED_)
#define AFX_VEHICLESTATE_H__0640B1EC_6B4B_4507_8DBE_85CCDE30DD5E__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VehicleState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVehicleState dialog
#define IDC_VEHICLESTATE	WM_USER + 5600
#define StateCount SDK_CAR_STATUS_NR
class CVehicleState : public CDialog
{
// Construction
public:
	CVehicleState(CWnd* pParent = NULL);   // standard constructor
	BOOL SaveVehicleStInfo();
	void CleanAll();
	void InitDlgInfo(SDK_CarStatusExchangeAll *pCarStaExg,int nAlarmInNum);
	SDK_CarStatusExchangeAll mCarStaExg;
	int m_nAlarmInNum;
	void InitWindow();
	CButton *mCheckBox[StateCount];
	CStatic *mStatic[StateCount];
	CComboBox *mInputCB[StateCount];
	CComboBox *mStyleCB[StateCount];
// Dialog Data
	//{{AFX_DATA(CVehicleState)
	enum { IDD = IDD_DLG_VEHICLE_STATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVehicleState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVehicleState)
	afx_msg void OnSelectBtn();
	afx_msg void OnBtnCheck();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChanged(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLESTATE_H__0640B1EC_6B4B_4507_8DBE_85CCDE30DD5E__INCLUDED_)
