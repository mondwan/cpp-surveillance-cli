// PTZCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "PTZCtrl.h"
#include "TestWeb.h"
#include "TestWebDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTestWebDlg	*g_TestWebDlg;
/////////////////////////////////////////////////////////////////////////////
// CPTZCtrl

CPTZCtrl::CPTZCtrl()
{
}

CPTZCtrl::~CPTZCtrl()
{
}


BEGIN_MESSAGE_MAP(CPTZCtrl, CButton)
	//{{AFX_MSG_MAP(CPTZCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTZCtrl message handlers

void CPTZCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//TRACE("g_TestWebDlg->m_iOCXIndex = %d",g_TestWebDlg->m_iOCXIndex);
	g_TestWebDlg->UpdateData(TRUE);	

		switch(m_iTypeButton)
		{
		case 0:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 0, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 1:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 1, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 2:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 2, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 3:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 3, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 4:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 4, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 5:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 5, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 6:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 6, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 7:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 7, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 8:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 8, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 9:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 9, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 10:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 10, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 11:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 11, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 12:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 12, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 13:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 13, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 14:
			g_TestWebDlg->m_ocx.PTZCtrlStart(g_TestWebDlg->m_playNumb, 14, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		default:
			break;
		}

	CButton::OnLButtonDown(nFlags, point);
}

void CPTZCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	g_TestWebDlg->UpdateData(TRUE);

		switch(m_iTypeButton)
		{
		case 0:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 0, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 1:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 1, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 2:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 2, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 3:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 3, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 4:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 4, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 5:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 5, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 6:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 6, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 7:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 7, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 8:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 8, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 9:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 9, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 10:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 10, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 11:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 11, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 12:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 12, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 13:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 13, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		case 14:
			g_TestWebDlg->m_ocx.PTZCtrlStop(g_TestWebDlg->m_playNumb, 14, g_TestWebDlg->m_ctrlPTZSpeed.GetCurSel());
			break;
		default:
			break;
		}

	CButton::OnLButtonUp(nFlags, point);
}
