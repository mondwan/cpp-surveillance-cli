#if !defined(AFX_DIALOGKEYBOARD_H__24118AA1_7491_482E_864E_256D310DF164__INCLUDED_)
#define AFX_DIALOGKEYBOARD_H__24118AA1_7491_482E_864E_256D310DF164__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogKeyBoard.h : header file
//
#include "ColorButton.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogKeyBoard dialog

class CDialogKeyBoard : public CDialog
{
// Construction
public:
	CDialogKeyBoard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogKeyBoard)
	enum { IDD = IDD_KEYBOARD_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogKeyBoard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogKeyBoard)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CColorButton m_btKey0;
	CColorButton m_btKey1;
	CColorButton m_btKey2;
	CColorButton m_btKey3;
	CColorButton m_btKey4;
	CColorButton m_btKey5;
	CColorButton m_btKey6;
	CColorButton m_btKey7;
	CColorButton m_btKey8;
	CColorButton m_btKey9;
	CColorButton m_btKey10;
	CColorButton m_btKey11;
	CColorButton m_btKey12;
	CColorButton m_btKey13;
	CColorButton m_btKey14;
	CColorButton m_btKey15;
	CColorButton m_btKey16;
	CColorButton m_btKey10plus;
	CColorButton m_btSplit;
	CColorButton m_btSplit1;
	CColorButton m_btSplit4;
	CColorButton m_btSplit8;
	CColorButton m_btSplit9;
	CColorButton m_btSplit16;
	CColorButton m_btAlarm;
	CColorButton m_btBack;
	CColorButton m_btBackup;
	CColorButton m_btEnter;
	CColorButton m_btEsc;
	CColorButton m_btFast;
	CColorButton m_btInfo;
	CColorButton m_btLeft;
	CColorButton m_btMenu;
	CColorButton m_btNext;
	CColorButton m_btPause;
	CColorButton m_btPlay;
	CColorButton m_btPrev;
	CColorButton m_btRecord;
	CColorButton m_btRight;
	CColorButton m_btSearch;
	CColorButton m_btShutdown;
	CColorButton m_btSlow;
	CColorButton m_btStop;
	CColorButton m_btUp;
	CColorButton m_btDown;

	CColorButton m_btPtz;
	CColorButton m_btPtzUp;
	CColorButton m_btPtzDown;
	CColorButton m_btPtzRight;
	CColorButton m_btPtzLeft;
	CColorButton m_btZoomTele;
	CColorButton m_btZoomWide;
	CColorButton m_btIrisLarge;
	CColorButton m_btIrisSmall;
	CColorButton m_btFocusFar;
	CColorButton m_btFocusNear;
	CColorButton m_btFunc;
	CColorButton m_btShift;

	CColorButton m_btSPreset;
	CColorButton m_btGPreset;
	CColorButton m_btDelPreset;
	CColorButton m_btAutoTour;
	CColorButton m_btPanOn;
	CColorButton m_btPanOff;
	CColorButton m_btScanOn;
	CColorButton m_btScanOff;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGKEYBOARD_H__24118AA1_7491_482E_864E_256D310DF164__INCLUDED_)
