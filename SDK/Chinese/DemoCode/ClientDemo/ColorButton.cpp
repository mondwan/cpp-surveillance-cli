// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "ColorButton.h"
#include "ClientDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD inumber = 0;

CColorButton::KeyPair KeyBoarPair[] = {
	{ID_KEY_0, SDK_NET_KEY_0},
	{ID_KEY_1, SDK_NET_KEY_1},
	{ID_KEY_2, SDK_NET_KEY_2},
	{ID_KEY_3, SDK_NET_KEY_3},
	{ID_KEY_4, SDK_NET_KEY_4},
	{ID_KEY_5, SDK_NET_KEY_5},
	{ID_KEY_6, SDK_NET_KEY_6},
	{ID_KEY_7, SDK_NET_KEY_7},
	{ID_KEY_8, SDK_NET_KEY_8},
	{ID_KEY_9, SDK_NET_KEY_9},
	{ID_KEY_10, SDK_NET_KEY_10},
	{ID_KEY_11, SDK_NET_KEY_11},
	{ID_KEY_12, SDK_NET_KEY_12},
	{ID_KEY_13, SDK_NET_KEY_13},
	{ID_KEY_14, SDK_NET_KEY_14},
	{ID_KEY_15, SDK_NET_KEY_15},
	{ID_KEY_16, SDK_NET_KEY_16},
	{ID_KEY_10PlUS, SDK_NET_KEY_10PLUS},
	{IDC_KEY_SPLIT, SDK_NET_KEY_SPLIT},
	{IDC_KEY_SPLIT_1, SDK_NET_KEY_SPLIT1},
	{IDC_KEY_SPLIT_4, SDK_NET_KEY_SPLIT4},
	{IDC_KEY_SPLIT_8, SDK_NET_KEY_SPLIT8},
	{IDC_KEY_SPLIT_9, SDK_NET_KEY_SPLIT9},
	{IDC_KEY_SPLIT_16, SDK_NET_KEY_SPLIT16},
	{IDC_KEY_ALARM, SDK_NET_KEY_ALARM},
	{IDC_KEY_BACK, SDK_NET_KEY_BACK},
	{IDC_KEY_BACKUP, SDK_NET_KEY_BACKUP},
	{IDC_KEY_ENTER, SDK_NET_KEY_RET},
	{IDC_KEY_ESC, SDK_NET_KEY_ESC},
	{IDC_KEY_FAST, SDK_NET_KEY_FAST},
	{IDC_KEY_INFO, SDK_NET_KEY_INFO},
	{IDC_KEY_LEFT, SDK_NET_KEY_LEFT},
	{IDC_KEY_MENU, SDK_NET_KEY_MENU},
	{IDC_KEY_NEXT, SDK_NET_KEY_NEXT},
	{IDC_KEY_PLAY, SDK_NET_KEY_PLAY},
	{IDC_KEY_PREV, SDK_NET_KEY_PREV},
	{IDC_KEY_RECORD, SDK_NET_KEY_REC},
	{IDC_KEY_RIGHT, SDK_NET_KEY_RIGHT},
	{IDC_KEY_SEARCH, SDK_NET_KEY_SEARCH},
	{IDC_KEY_SHUTDOWN, SDK_NET_KEY_SHUT},
	{IDC_KEY_SLOW, SDK_NET_KEY_SLOW},
	{IDC_KEY_STOP, SDK_NET_KEY_STOP},
	{IDC_KEY_UP, SDK_NET_KEY_UP},
	{IDC_KEY_DOWN, SDK_NET_KEY_DOWN},
	{IDC_KEY_PTZ, SDK_NET_KEY_PTZ},
	{IDC_KEY_PTZ_UP, SDK_NET_KEY_UP},
	{IDC_KEY_PTZ_DOWN, SDK_NET_KEY_DOWN},
	{IDC_KEY_PTZ_RIGHT, SDK_NET_KEY_RIGHT},
	{IDC_KEY_PTZ_LEFT, SDK_NET_KEY_LEFT},
	{IDC_KEY_ZOOM_TELE, SDK_NET_KEY_TELE},
	{IDC_KEY_ZOOM_WIDE, SDK_NET_KEY_WIDE},
	{IDC_KEY_IRIS_LARGE, SDK_NET_KEY_IRIS_LARGE},
	{IDC_KEY_IRIS_SMALL, SDK_NET_KEY_IRIS_SMALL},
	{IDC_KEY_FOCUS_FAR, SDK_NET_KEY_FOCUS_FAR},
	{IDC_KEY_FOCUS_NEAR, SDK_NET_KEY_FOCUS_NEAR},
	{IDC_KEY_SHIFT, SDK_NET_KEY_SHIFT},
	{IDC_KEY_FUNC, SDK_NET_KEY_FUNC},
	{IDC_KEY_SET_PRESET, SDK_NET_KEY_SPRESET},
	{IDC_KEY_GO_PRESET, SDK_NET_KEY_GPRESET},
	{IDC_KEY_DEL_PRESET, SDK_NET_KEY_DPRESET},
	{IDC_KEY_AUTO_TOUR, SDK_NET_KEY_AUTOTOUR},
	{IDC_KEY_AUTO_PAN, SDK_NET_KEY_AUTOPAN},
	{IDC_KEY_AUTO_SCAN, SDK_NET_KEY_AUTOSCAN},
	{0, 0}
};
/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
	m_iSubButtonNum = inumber++;
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers
void CColorButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDemoDlg *pMain = (CClientDemoDlg *)AfxGetApp()->m_pMainWnd;
	if ( pMain )
	{                           
		int iID = GetDlgCtrlID();
		if (m_nBtnType == 1000)
		{
					pMain->PtzControl(m_iSubButtonNum, 0);
		}
		else
		{
			for (int i = 0; i < sizeof(KeyBoarPair) / sizeof(KeyPair); i++)
			{
				if (iID == KeyBoarPair[i].iKey)
				{
					pMain->KeyBoardMsg(KeyBoarPair[i].iValue, 0);
					break;
				}
			}
		}
	}
	CButton::OnLButtonDown(nFlags, point);
}

void CColorButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CClientDemoDlg *pMain = (CClientDemoDlg *)AfxGetApp()->m_pMainWnd;
	if ( pMain )
	{
		int iID = GetDlgCtrlID();
		if (m_nBtnType == 1000)
		{
			pMain->PtzControl(m_iSubButtonNum, 1);
		}
		else
		{
			for (int i = 0; i < sizeof(KeyBoarPair) / sizeof(KeyPair); i++)
			{
				if (iID == KeyBoarPair[i].iKey)
				{
					pMain->KeyBoardMsg(KeyBoarPair[i].iValue, 1);
					break;
				}
			}
		}
	}
	
	CButton::OnLButtonUp(nFlags, point);
}
