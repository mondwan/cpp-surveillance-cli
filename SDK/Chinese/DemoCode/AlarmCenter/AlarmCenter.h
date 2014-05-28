// AlarmCenter.h : main header file for the ALARMCENTER application
//

#if !defined(AFX_ALARMCENTER_H__B961B4D9_8F36_4060_8045_F9E9159EF585__INCLUDED_)
#define AFX_ALARMCENTER_H__B961B4D9_8F36_4060_8045_F9E9159EF585__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlarmCenterApp:
// See AlarmCenter.cpp for the implementation of this class
//
const ModuleFileInfomations&    GetModuleFileInformations();
#define GET_MODULE_FILE_INFO    (GetModuleFileInformations())

class CAlarmCenterApp : public CWinApp
{
public:
	CAlarmCenterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmCenterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAlarmCenterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMCENTER_H__B961B4D9_8F36_4060_8045_F9E9159EF585__INCLUDED_)
