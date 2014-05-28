#if !defined(AFX_CONFIGVEHICLE_H__91733B80_CD10_4A7A_8F28_77BF8DC799D5__INCLUDED_)
#define AFX_CONFIGVEHICLE_H__91733B80_CD10_4A7A_8F28_77BF8DC799D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VehicleState.h"
#include "TimeLapseSet.h"
#include "VehicleData.h"

// ConfigVehicle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigVehicle dialog

class CConfigVehicle : public CDialog
{
// Construction
public:
	CConfigVehicle(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CConfigVehicle)
	enum { IDD = IDD_DLG_VEHICLE };
	CTabCtrl	m_ctrlVehicle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigVehicle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void DoTab(int nTab);
	void InitTabControl();
	CVehicleState m_TabVehicleSt;
	CTimeLapseSet m_TabTimeLS;
	CVehicleData  m_TabVehicleDa;
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	
public:
		void InitDlgInfo(SDK_CarStatusExchangeAll *pCarStaExg,SDK_CarDelayTimeConfig *pCarDelayTimeCfg,SDK_SystemFunction *pSysFunc,int nAlarmInNum);
		void CleanAll();
		SDK_CarStatusExchangeAll m_CarStaExg;
		SDK_CarDelayTimeConfig m_CarDelayTiemCfg;

protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigVehicle)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabVehicle(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGVEHICLE_H__91733B80_CD10_4A7A_8F28_77BF8DC799D5__INCLUDED_)
