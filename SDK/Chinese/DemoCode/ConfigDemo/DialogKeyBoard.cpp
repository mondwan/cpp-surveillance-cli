// DialogKeyBoard.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DialogKeyBoard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogKeyBoard dialog


CDialogKeyBoard::CDialogKeyBoard(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogKeyBoard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogKeyBoard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogKeyBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogKeyBoard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogKeyBoard, CDialog)
	//{{AFX_MSG_MAP(CDialogKeyBoard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogKeyBoard message handlers

BOOL CDialogKeyBoard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_btKey0.SubclassDlgItem(ID_KEY_0,this);
	m_btKey1.SubclassDlgItem(ID_KEY_1,this);
	m_btKey2.SubclassDlgItem(ID_KEY_2,this);
	m_btKey3.SubclassDlgItem(ID_KEY_3,this);	
	m_btKey4.SubclassDlgItem(ID_KEY_4,this);
	m_btKey5.SubclassDlgItem(ID_KEY_5,this);
	m_btKey6.SubclassDlgItem(ID_KEY_6,this);
	m_btKey7.SubclassDlgItem(ID_KEY_7,this);
	m_btKey8.SubclassDlgItem(ID_KEY_8,this);
	m_btKey9.SubclassDlgItem(ID_KEY_9,this);
	m_btKey10.SubclassDlgItem(ID_KEY_10,this);
	m_btKey11.SubclassDlgItem(ID_KEY_11,this);
	m_btKey12.SubclassDlgItem(ID_KEY_12,this);
	m_btKey13.SubclassDlgItem(ID_KEY_13,this);	
	m_btKey14.SubclassDlgItem(ID_KEY_14,this);
	m_btKey15.SubclassDlgItem(ID_KEY_15,this);
	m_btKey16.SubclassDlgItem(ID_KEY_16,this);
	m_btKey10plus.SubclassDlgItem(ID_KEY_10PlUS,this);
	
	m_btSplit.SubclassDlgItem(IDC_KEY_SPLIT,this);
	m_btSplit1.SubclassDlgItem(IDC_KEY_SPLIT_1,this);
	m_btSplit4.SubclassDlgItem(IDC_KEY_SPLIT_4,this);
	m_btSplit8.SubclassDlgItem(IDC_KEY_SPLIT_8,this);
	m_btSplit9.SubclassDlgItem(IDC_KEY_SPLIT_9,this);
	m_btSplit16.SubclassDlgItem(IDC_KEY_SPLIT_16,this);

	m_btDown.SubclassDlgItem(IDC_KEY_DOWN,this);
	m_btAlarm.SubclassDlgItem(IDC_KEY_ALARM,this);
	m_btBack.SubclassDlgItem(IDC_KEY_BACK,this);	
	m_btBackup.SubclassDlgItem(IDC_KEY_BACKUP,this);
	m_btEnter.SubclassDlgItem(IDC_KEY_ENTER,this);
	m_btEsc.SubclassDlgItem(IDC_KEY_ESC,this);
	m_btFast.SubclassDlgItem(IDC_KEY_FAST,this);
	m_btInfo.SubclassDlgItem(IDC_KEY_INFO,this);
	m_btLeft.SubclassDlgItem(IDC_KEY_LEFT,this);

	m_btMenu.SubclassDlgItem(IDC_KEY_MENU,this);
	m_btNext.SubclassDlgItem(IDC_KEY_NEXT,this);
	m_btPlay.SubclassDlgItem(IDC_KEY_PLAY,this);	
	m_btPrev.SubclassDlgItem(IDC_KEY_PREV,this);
	m_btRecord.SubclassDlgItem(IDC_KEY_RECORD,this);
	m_btRight.SubclassDlgItem(IDC_KEY_RIGHT,this);
	m_btSearch.SubclassDlgItem(IDC_KEY_SEARCH,this);
	m_btShutdown.SubclassDlgItem(IDC_KEY_SHUTDOWN,this);
	m_btSlow.SubclassDlgItem(IDC_KEY_SLOW,this);
	m_btStop.SubclassDlgItem(IDC_KEY_STOP,this);
	m_btUp.SubclassDlgItem(IDC_KEY_UP,this);

	m_btPtz.SubclassDlgItem(IDC_KEY_PTZ,this);
	m_btPtzUp.SubclassDlgItem(IDC_KEY_PTZ_UP,this);
	m_btPtzDown.SubclassDlgItem(IDC_KEY_PTZ_DOWN,this);
	m_btPtzRight.SubclassDlgItem(IDC_KEY_PTZ_RIGHT,this);	
	m_btPtzLeft.SubclassDlgItem(IDC_KEY_PTZ_LEFT,this);
	m_btZoomTele.SubclassDlgItem(IDC_KEY_ZOOM_TELE,this);
	m_btZoomWide.SubclassDlgItem(IDC_KEY_ZOOM_WIDE,this);
	m_btIrisLarge.SubclassDlgItem(IDC_KEY_IRIS_LARGE,this);
	m_btIrisSmall.SubclassDlgItem(IDC_KEY_IRIS_SMALL,this);
	m_btFocusFar.SubclassDlgItem(IDC_KEY_FOCUS_FAR,this);
	m_btFocusNear.SubclassDlgItem(IDC_KEY_FOCUS_NEAR,this);
	m_btFunc.SubclassDlgItem(IDC_KEY_FUNC,this);
	m_btShift.SubclassDlgItem(IDC_KEY_SHIFT,this);
	
	m_btSPreset.SubclassDlgItem(IDC_KEY_SET_PRESET,this);
	m_btGPreset.SubclassDlgItem(IDC_KEY_GO_PRESET,this);
	m_btDelPreset.SubclassDlgItem(IDC_KEY_DEL_PRESET,this);
	m_btAutoTour.SubclassDlgItem(IDC_KEY_AUTO_TOUR,this);
	//m_btPanOn.SubclassDlgItem(IDC_KEY_PAN_ON,this);
	//m_btPanOff.SubclassDlgItem(IDC_KEY_PAN_OFF,this);
	//m_btScanOn.SubclassDlgItem(IDC_KEY_SCAN_ON,this);
	//m_btScanOff.SubclassDlgItem(IDC_KEY_SCAN_OFF,this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
