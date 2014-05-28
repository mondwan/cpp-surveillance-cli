// TransparentDemon.h : main header file for the TRANSPARENTDEMON application
//

#if !defined(AFX_TRANSPARENTDEMON_H__5310C49E_C793_4BB4_B91C_83412309EA21__INCLUDED_)
#define AFX_TRANSPARENTDEMON_H__5310C49E_C793_4BB4_B91C_83412309EA21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransparentDemonApp:
// See TransparentDemon.cpp for the implementation of this class
//
const ModuleFileInfomations&    GetModuleFileInformations();
#define GET_MODULE_FILE_INFO    (GetModuleFileInformations())

class CTransparentDemonApp : public CWinApp
{
public:
	CTransparentDemonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentDemonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTransparentDemonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTDEMON_H__5310C49E_C793_4BB4_B91C_83412309EA21__INCLUDED_)
