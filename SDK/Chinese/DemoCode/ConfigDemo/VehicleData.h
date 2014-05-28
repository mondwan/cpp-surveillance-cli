#if !defined(AFX_VEHICLEDATA_H__C2128311_B847_4319_942E_48F727DD61B2__INCLUDED_)
#define AFX_VEHICLEDATA_H__C2128311_B847_4319_942E_48F727DD61B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VehicleData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVehicleData dialog

class CVehicleData : public CDialog
{
// Construction
public:
	CVehicleData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVehicleData)
	enum { IDD = IDD_DLG_VEHICLE_DATA };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVehicleData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVehicleData)
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void __stdcall UploadDataCallBack(long lLongID,long UpLoadType,char *pBuffer,unsigned long dwBufSize,unsigned long  dwUser);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLEDATA_H__C2128311_B847_4319_942E_48F727DD61B2__INCLUDED_)
