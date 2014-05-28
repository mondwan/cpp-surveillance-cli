// AlarmMotion.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "AlarmMotion.h"
#include "AlarmInputDlg.h"
#include "AreaSelectDlg.h"
#include "PtzLinkDlg.h"
#include "PeriodTimeSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmMotion dialog


CAlarmMotion::CAlarmMotion(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmMotion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmMotion)
	//}}AFX_DATA_INIT
	memset(m_pBtnsRecord, 0, sizeof(m_pBtnsRecord));
	memset(m_pBtnsTour, 0, sizeof(m_pBtnsTour));
	memset(m_pBtnsAlarmOut, 0, sizeof(m_pBtnsAlarmOut));
	memset(m_pBtnsSnap, 0, sizeof(m_pBtnsSnap));
}


void CAlarmMotion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmMotion)
	DDX_Control(pDX, IDC_CHECK_ENABLEALARM, m_ctlEnableAlarm);
	DDX_Control(pDX, IDC_CHECK_SCREEN_TIP, m_ctlScreenTip);
	DDX_Control(pDX, IDC_CHECK_FTP, m_ctlFtp);
	DDX_Control(pDX, IDC_CHECK_EMAIL, m_ctlEmail);
	DDX_Control(pDX, IDC_CHECK_BEEP, m_ctlBeep);
	DDX_Control(pDX, IDC_COMBO_CHANNELNUM, m_ctlChannelNum);
	DDX_Control(pDX, IDC_COMBO_DELICACY, m_ctrlDelicacy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmMotion, CDialog)
	//{{AFX_MSG_MAP(CAlarmMotion)
	ON_BN_CLICKED(IDC_BUTTON_SETAREA, OnButtonSetarea)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNELNUM, OnSelchangeComboChannelnum)
	ON_BN_CLICKED(IDC_CHECK_ENABLEALARM, OnCheckEnablealarm)
	ON_BN_CLICKED(IDC_BTN_PTZLINK, OnBtnPtzlink)
	ON_BN_CLICKED(IDC_BTN_ALARM_CTRL_PERIOD, OnBtnAlarmCtrlPeriod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmMotion message handlers

void CAlarmMotion::OnButtonSetarea() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannelNum.GetCurSel();
	if (nIndex < 0)
	{
		return;
	}
	if ( nIndex == m_nChannelNum)
	{
		nIndex = 0;
	}
	CAreaSelectDlg dlg(m_nRow,m_nCol,m_MotionCfgAll.vMotionDetectAll[nIndex].mRegion);
	dlg.SetChannelInfo(nIndex);
	if ( IDOK == dlg.DoModal())
	{
		memcpy(m_MotionCfgAll.vMotionDetectAll[nIndex].mRegion,dlg.GetSetData(),
			sizeof(m_MotionCfgAll.vMotionDetectAll[nIndex].mRegion));
	}
}

BOOL CAlarmMotion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_nRow = 0;
	m_nCol = 0;
	CString strText;
	strText.Format("%s", _CS("ConfigVideo.Lowest") );
	int nInsert = m_ctrlDelicacy.AddString(strText);
	m_ctrlDelicacy.SetItemData(nInsert, 1);
	
	strText.Format("%s", _CS("ConfigVideo.Lower") );
	nInsert = m_ctrlDelicacy.AddString(strText);
	m_ctrlDelicacy.SetItemData(nInsert, 2);
	
	strText.Format("%s", _CS("ConfigVideo.Middle") );
	nInsert = m_ctrlDelicacy.AddString(strText);
	m_ctrlDelicacy.SetItemData(nInsert, 3);
	
	strText.Format("%s", _CS("ConfigVideo.High") );
	nInsert = m_ctrlDelicacy.AddString(strText);
	m_ctrlDelicacy.SetItemData(nInsert, 4);
	
	strText.Format("%s", _CS("ConfigVideo.Higher") );
	nInsert = m_ctrlDelicacy.AddString(strText);
	m_ctrlDelicacy.SetItemData(nInsert, 5);
	
	strText.Format("%s", _CS("ConfigVideo.Highest") );
	nInsert = m_ctrlDelicacy.AddString(strText);
	m_ctrlDelicacy.SetItemData(nInsert, 6);

	m_nLastChannel = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmMotion::InitWndShow()
{
	Clear();
	//m_nLastChannelNum = -1;

	CString strBtnTitle;
	int nVideoOutChannel = m_nAlarmOutNum;
	ZeroMemory( m_pBtnsAlarmOut, sizeof(m_pBtnsAlarmOut) );

	int i = 0, j = 0;
	CRect rcOffSet;
	CRect rcAlarmOut;
	GetDlgItem(IDC_STATIC_ALARM_OUT)->GetWindowRect(rcAlarmOut);
	ScreenToClient(rcAlarmOut);
	if (nVideoOutChannel > 0)
	{
		rcAlarmOut.left = rcAlarmOut.right;
		rcAlarmOut.right = rcAlarmOut.left + 20;

		for ( i = 0; i < nVideoOutChannel; ++i )
		{
			strBtnTitle.Format("%d", i + 1);

			m_pBtnsAlarmOut[i] = new CButton();
			m_pBtnsAlarmOut[i]->Create(strBtnTitle, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE, rcAlarmOut, this, IDC_BTN_ALARMOUT + i);

			rcAlarmOut.left  += 20;
			rcAlarmOut.right += 20;
		}
		GetDlgItem(IDC_STATIC_ALARM_OUT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ALARMOUT_LATCH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_IGNORE_TIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SEC2)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_TIMESECT)->GetWindowRect(rcOffSet);
		ScreenToClient(rcOffSet);
		rcOffSet.top = rcAlarmOut.bottom + 8;
	}
	else
	{
		GetDlgItem(IDC_STATIC_ALARM_OUT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ALARMOUT_LATCH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_IGNORE_TIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SEC2)->ShowWindow(SW_HIDE);
		rcOffSet.bottom = rcAlarmOut.bottom;
		rcOffSet.top = rcAlarmOut.top;
	}

	bool bSnap = false;
	if ( 1 )
	{
		bSnap = m_SysFunc.vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM];
		if (false == bSnap)
		{
			GetDlgItem(IDC_STATIC_MOTION_SNAP)->ShowWindow(SW_HIDE);
		}
		else
		{
			GetDlgItem(IDC_STATIC_MOTION_SNAP)->ShowWindow(SW_SHOW);
		}
	}

	bool bFtp = false;
	if ( 1 )
	{
		bFtp =  m_SysFunc.vNetServerFunction[SDK_NET_SERVER_TYPES_FTP];
		if (false == bFtp)
		{
			GetDlgItem(IDC_CHECK_FTP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_FTP)->ShowWindow(SW_HIDE);
		}
		else
		{
			GetDlgItem(IDC_CHECK_FTP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_FTP)->ShowWindow(SW_SHOW);
		}
	}
#define MAX_CHANNEL_PER_LINE 16

	int nChanneCount = m_nChannelNum;
	int nBlank = (nChanneCount - 1) / MAX_CHANNEL_PER_LINE;
	int iHeight, iWidth;

	ZeroMemory( m_pBtnsRecord, sizeof(m_pBtnsRecord) );
	ZeroMemory( m_pBtnsTour, sizeof(m_pBtnsTour) );
	ZeroMemory(m_pBtnsSnap, sizeof(m_pBtnsSnap));

	CRect rcRecord, rcTour, rcSnap;
	GetDlgItem(IDC_STATIC_RECORD_CHANNEL)->GetWindowRect(rcRecord);
	ScreenToClient(rcRecord);
	iHeight = rcRecord.bottom - rcRecord.top;
	rcRecord.top = rcOffSet.top;
	rcRecord.bottom = rcRecord.top + iHeight;
	GetDlgItem(IDC_STATIC_RECORD_CHANNEL)->MoveWindow(&rcRecord);
	
	//GetDlgItem(IDC_STATIC_TOUR)->GetWindowRect(rcTour);
	//ScreenToClient(rcTour);
	//iHeight = rcTour.bottom - rcTour.top;
	rcTour.top = rcRecord.bottom + 8 + nBlank * iHeight;
	rcTour.bottom = rcTour.top + iHeight;
	rcTour.left = rcRecord.left;
	rcTour.right = rcRecord.right;
	GetDlgItem(IDC_STATIC_TOUR)->MoveWindow(&rcTour);

	//GetDlgItem(IDC_STATIC_MOTION_SNAP)->GetWindowRect(rcSnap);
	//ScreenToClient(rcSnap);
	//iHeight = rcSnap.bottom - rcSnap.top;
	rcSnap.top = rcTour.bottom + 8 + nBlank * iHeight;
	rcSnap.bottom = rcSnap.top + iHeight;
	rcSnap.left = rcRecord.left;
	rcSnap.right = rcRecord.right;
	GetDlgItem(IDC_STATIC_MOTION_SNAP)->MoveWindow(&rcSnap);

	rcRecord.left = rcRecord.right;
	rcRecord.right = rcRecord.left + 20;
	rcTour.left = rcTour.right;
	rcTour.right = rcTour.left + 20;
	rcSnap.left = rcSnap.right;
	rcSnap.right = rcSnap.left + 20;

	int nSect = nChanneCount / MAX_CHANNEL_PER_LINE;
	int nOffset = nChanneCount % MAX_CHANNEL_PER_LINE;
	for (j = 0; j < nSect; j++)
	{
		CRect orgrcRecord = rcRecord;
		CRect orgrcTour = rcTour;
		CRect orgrcSnap = rcSnap;
		for ( i = 0; i < MAX_CHANNEL_PER_LINE; ++i )
		{
			strBtnTitle.Format("%d", i + 1 + j * MAX_CHANNEL_PER_LINE);

			m_pBtnsRecord[i + j * MAX_CHANNEL_PER_LINE] = new CButton();
			m_pBtnsTour[i + j * MAX_CHANNEL_PER_LINE] = new CButton();
			m_pBtnsSnap[i + j * MAX_CHANNEL_PER_LINE] = new CButton();

			m_pBtnsRecord[i + j * MAX_CHANNEL_PER_LINE]->Create(strBtnTitle, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE,
				orgrcRecord, this, IDC_BTN_RECORD + i + j * MAX_CHANNEL_PER_LINE);
			m_pBtnsTour[i + j * MAX_CHANNEL_PER_LINE]->Create(strBtnTitle, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE,
				orgrcTour, this, IDC_BTN_RECORD + i  + j * MAX_CHANNEL_PER_LINE);
			m_pBtnsSnap[i + j * MAX_CHANNEL_PER_LINE]->Create(strBtnTitle, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE,
				orgrcSnap, this, IDC_BTN_RECORD + i + j * MAX_CHANNEL_PER_LINE);
			m_pBtnsSnap[i + j * MAX_CHANNEL_PER_LINE]->ShowWindow(bSnap);

			orgrcRecord.left += 20;
			orgrcRecord.right+= 20;
			orgrcTour.left += 20;
			orgrcTour.right+= 20;	
			orgrcSnap.left += 20;
			orgrcSnap.right+= 20;
		}

		if (j < nSect - 1)
		{
			rcRecord.top += 20;
			rcRecord.bottom += 20;
			rcTour.top += 20;
			rcTour.bottom+= 20;	
			rcSnap.top += 20;
			rcSnap.bottom+= 20;
		}
	}
	if (nOffset)
	{
		if (nSect) 
		{

			rcRecord.top += 20;
			rcRecord.bottom += 20;
			rcTour.top += 20;
			rcTour.bottom+= 20;	
			rcSnap.top += 20;
			rcSnap.bottom+= 20;
		}
	
		for ( i = 0; i < nOffset; ++i )
		{
			strBtnTitle.Format("%d", i + 1 + nSect * MAX_CHANNEL_PER_LINE);

			m_pBtnsRecord[i + nSect * MAX_CHANNEL_PER_LINE] = new CButton();
			m_pBtnsTour[i + nSect * MAX_CHANNEL_PER_LINE] = new CButton();
			m_pBtnsSnap[i + nSect * MAX_CHANNEL_PER_LINE] = new CButton();
			m_pBtnsRecord[i + nSect * MAX_CHANNEL_PER_LINE]->Create(strBtnTitle, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE, 
				rcRecord, this, IDC_BTN_RECORD + i + nSect * MAX_CHANNEL_PER_LINE);
			m_pBtnsTour[i + nSect * MAX_CHANNEL_PER_LINE]->Create(strBtnTitle, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE,
				rcTour, this, IDC_BTN_RECORD + i + nSect * MAX_CHANNEL_PER_LINE);
			m_pBtnsSnap[i + nSect * MAX_CHANNEL_PER_LINE]->Create(strBtnTitle, BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE,
				rcSnap, this, IDC_BTN_RECORD + i + nSect * MAX_CHANNEL_PER_LINE);
		    m_pBtnsSnap[i + nSect * MAX_CHANNEL_PER_LINE]->ShowWindow(bSnap);
			rcRecord.left += 20;
			rcRecord.right+= 20;
			rcTour.left += 20;
			rcTour.right+= 20;	
			rcSnap.left += 20;
			rcSnap.right+= 20;
		}
	}
	if(true == bSnap)
	{
		rcTour = rcSnap;
	}
	CRect rcPos, rcTmp, rcTmp2;
	GetDlgItem(IDC_STATIC_PTZ_LINK)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTour.bottom + 12;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_STATIC_PTZ_LINK)->MoveWindow(&rcPos);

	GetDlgItem(IDC_BTN_PTZLINK)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTour.bottom + 8;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_BTN_PTZLINK)->MoveWindow(&rcPos);

	GetDlgItem(IDC_STATIC_DELAY_RECORDTIME)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTour.bottom + 12;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_STATIC_DELAY_RECORDTIME)->MoveWindow(&rcPos);

	GetDlgItem(IDC_EDIT_RECORD_IG_TIME)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTour.bottom + 8;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_EDIT_RECORD_IG_TIME)->MoveWindow(&rcPos);

	GetDlgItem(IDC_STATIC_SEC3)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTour.bottom + 12;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_STATIC_SEC3)->MoveWindow(&rcPos);
	rcTmp = rcPos;

	GetDlgItem(IDC_CHECK_SCREEN_TIP)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTmp.bottom + 12;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_CHECK_SCREEN_TIP)->MoveWindow(&rcPos);

	GetDlgItem(IDC_STATIC_SCREEN_TIP)->GetWindowRect(rcTmp2);
	ScreenToClient(rcTmp2);
	iHeight = rcTmp2.Height();
	iWidth = rcTmp2.Width();
	rcPos.left = rcPos.right + 4;
	rcPos.right = rcPos.left + iWidth;
	GetDlgItem(IDC_STATIC_SCREEN_TIP)->MoveWindow(&rcPos);

	GetDlgItem(IDC_CHECK_EMAIL)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTmp.bottom + 12;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_CHECK_EMAIL)->MoveWindow(&rcPos);

	GetDlgItem(IDC_STATIC_EMAIL)->GetWindowRect(rcTmp2);
	ScreenToClient(rcTmp2);
	iHeight = rcTmp2.Height();
	iWidth = rcTmp2.Width();
	rcPos.left = rcPos.right + 4;
	rcPos.right = rcPos.left + iWidth;
	GetDlgItem(IDC_STATIC_EMAIL)->MoveWindow(&rcPos);
	
	rcTmp = rcPos;

	GetDlgItem(IDC_CHECK_BEEP)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTmp.bottom + 12;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_CHECK_BEEP)->MoveWindow(&rcPos);

	GetDlgItem(IDC_STATIC_BEEP)->GetWindowRect(rcTmp2);
	ScreenToClient(rcTmp2);
	iHeight = rcTmp2.Height();
	iWidth = rcTmp2.Width();
	rcPos.left = rcPos.right + 4;
	rcPos.right = rcPos.left + iWidth;
	GetDlgItem(IDC_STATIC_BEEP)->MoveWindow(&rcPos);
	
	GetDlgItem(IDC_CHECK_FTP)->GetWindowRect(rcPos);
	ScreenToClient(rcPos);
	iHeight = rcPos.bottom - rcPos.top;
	rcPos.top = rcTmp.bottom + 12;
	rcPos.bottom = rcPos.top + iHeight;
	GetDlgItem(IDC_CHECK_FTP)->MoveWindow(&rcPos);

	GetDlgItem(IDC_STATIC_FTP)->GetWindowRect(rcTmp2);
	ScreenToClient(rcTmp2);
	iHeight = rcTmp2.Height();
	iWidth = rcTmp2.Width();
	rcPos.left = rcPos.right + 4;
	rcPos.right = rcPos.left + iWidth;
	GetDlgItem(IDC_STATIC_FTP)->MoveWindow(&rcPos);
	
	
	
	BOOL abet =m_SysFunc.vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_NR];
	if (!abet)
	{
			for (int i=0;i<(nOffset+nSect*MAX_CHANNEL_PER_LINE);++i)
			{
				m_pBtnsSnap[i]->ShowWindow(SW_HIDE);
			}
			GetDlgItem(IDC_STATIC_MOTION_SNAP)->ShowWindow(SW_HIDE);
	}
}

void CAlarmMotion::InitDlgInfo(SDK_MOTIONCONFIG_ALL *pMotionCfgAll, int nChannelNum, int nAlarmInNum, int nAlarmOutNum,SDK_MotionDetectFunction *pMotionDectFuc,SDK_SystemFunction *pSysFunc)
{
	m_nRow = pMotionDectFuc->iGridRow;
	m_nCol = pMotionDectFuc->iGridColumn;
	int i = 0;
	int nIndex = 0;
	m_ctlChannelNum.ResetContent();
	for (;i<nChannelNum;i++)
	{
		CString str;
		str.Format("%d",i+1);
		nIndex = m_ctlChannelNum.AddString(str);
		m_ctlChannelNum.SetItemData(nIndex,i);
	}
	nIndex = m_ctlChannelNum.AddString(_CS("OneClick.All"));
	m_ctlChannelNum.SetItemData(nIndex,nChannelNum);
	m_ctlChannelNum.SetCurSel(0);

	m_nChannelNum = nChannelNum;
	m_nAlarmOutNum = nAlarmOutNum;
	memcpy(&m_MotionCfgAll,pMotionCfgAll,sizeof(SDK_MOTIONCONFIG_ALL));
	memcpy(&m_SysFunc,pSysFunc,sizeof(SDK_SystemFunction));
	ShowInfo(0);

}

void CAlarmMotion::OnSelchangeComboChannelnum() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannelNum.GetCurSel();
	if (nIndex == m_nChannelNum)
	{
		ShowInfo(0);
		m_nLastChannel = nIndex;
	}else
	{
		if (m_nLastChannel ==m_nChannelNum)
		{
			ShowInfo(nIndex);
			m_nLastChannel = nIndex;
		}
		else
		{
			if (nIndex != m_nLastChannel)
			{
			SaveMotionInfo();
			m_nLastChannel = nIndex;
			ShowInfo(nIndex);
			}
		}
	}
}

void CAlarmMotion::CleanAll()
{
	m_ctlChannelNum.SetCurSel(-1);
	m_ctrlDelicacy.SetCurSel(-1);
	SetDlgItemInt(IDC_EDIT_IGNORE_TIME,0);
	SetDlgItemInt(IDC_EDIT_INTERL_TIME,0);
	SetDlgItemInt(IDC_EDIT_RECORD_IG_TIME,0);
	m_ctlEnableAlarm.SetCheck(FALSE);
	m_ctlBeep.SetCheck(FALSE);
	m_ctlFtp.SetCheck(FALSE);
	m_ctlScreenTip.SetCheck(FALSE);
	m_ctlEmail.SetCheck(FALSE);
}

BOOL CAlarmMotion::SaveMotionInfo()
{
	int nIndex = m_ctlChannelNum.GetCurSel();
	if (nIndex == m_nChannelNum)
	{
		for (int i = 0;i<m_nChannelNum;i++)
		{
			m_MotionCfgAll.vMotionDetectAll[i].bEnable = m_ctlEnableAlarm.GetCheck();
			m_MotionCfgAll.vMotionDetectAll[i].iLevel = m_ctrlDelicacy.GetCurSel() + 1;
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.iEventLatch = GetDlgItemInt(IDC_EDIT_INTERL_TIME);
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.iAOLatch = GetDlgItemInt(IDC_EDIT_IGNORE_TIME);
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.iRecordLatch = GetDlgItemInt(IDC_EDIT_RECORD_IG_TIME);
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.bBeep = m_ctlBeep.GetCheck();
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.bFTP = m_ctlBeep.GetCheck();
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.bTip = m_ctlScreenTip.GetCheck();
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.bMail = m_ctlEmail.GetCheck();
			
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.dwAlarmOut = CAlarmInputDlg::GetButtonsCheck(m_pBtnsAlarmOut,m_nAlarmOutNum);
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.dwRecord = CAlarmInputDlg::GetButtonsCheck(m_pBtnsRecord,m_nChannelNum);
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.dwTour = CAlarmInputDlg::GetButtonsCheck(m_pBtnsTour,m_nChannelNum);
			m_MotionCfgAll.vMotionDetectAll[i].hEvent.dwSnapShot = CAlarmInputDlg::GetButtonsCheck(m_pBtnsSnap,m_nChannelNum);
		}
	}else
	{
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].bEnable = m_ctlEnableAlarm.GetCheck();
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].iLevel = m_ctrlDelicacy.GetCurSel() + 1;
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.iEventLatch = GetDlgItemInt(IDC_EDIT_INTERL_TIME);
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.iAOLatch = GetDlgItemInt(IDC_EDIT_IGNORE_TIME);
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.iRecordLatch = GetDlgItemInt(IDC_EDIT_RECORD_IG_TIME);
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.bBeep = m_ctlBeep.GetCheck();
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.bFTP = m_ctlBeep.GetCheck();
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.bTip = m_ctlScreenTip.GetCheck();
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.bMail = m_ctlEmail.GetCheck();
		
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.dwAlarmOut = CAlarmInputDlg::GetButtonsCheck(m_pBtnsAlarmOut,m_nAlarmOutNum);
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.dwRecord = CAlarmInputDlg::GetButtonsCheck(m_pBtnsRecord,m_nChannelNum);
		m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.dwTour = CAlarmInputDlg::GetButtonsCheck(m_pBtnsTour,m_nChannelNum);
	    m_MotionCfgAll.vMotionDetectAll[m_nLastChannel].hEvent.dwSnapShot = CAlarmInputDlg::GetButtonsCheck(m_pBtnsSnap,m_nChannelNum);
	}

	return TRUE;
}

void CAlarmMotion::ShowInfo(int nIndex)
{
	InitWndShow();
	m_ctrlDelicacy.SetCurSel(m_MotionCfgAll.vMotionDetectAll[nIndex].iLevel-1);
	m_ctlEnableAlarm.SetCheck(m_MotionCfgAll.vMotionDetectAll[nIndex].bEnable);
	
	SetDlgItemInt(IDC_EDIT_INTERL_TIME,m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.iEventLatch);
	SetDlgItemInt(IDC_EDIT_IGNORE_TIME,m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.iAOLatch);
	SetDlgItemInt(IDC_EDIT_RECORD_IG_TIME,m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.iRecordLatch);
	m_ctlBeep.SetCheck(m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.bBeep);
	m_ctlFtp.SetCheck(m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.bFTP);
	m_ctlEmail.SetCheck(m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.bMail);
	m_ctlScreenTip.SetCheck(m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.bTip);

	CAlarmInputDlg::SetButtonsCheck(m_pBtnsAlarmOut, m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.dwAlarmOut, m_nAlarmOutNum );
	CAlarmInputDlg::SetButtonsCheck( m_pBtnsRecord, m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.dwRecord, m_nChannelNum );
	CAlarmInputDlg::SetButtonsCheck( m_pBtnsTour,m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.dwTour, m_nChannelNum );		
	CAlarmInputDlg::SetButtonsCheck(m_pBtnsSnap, m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.dwSnapShot, m_nChannelNum);
	OnCheckEnablealarm();
}

void CAlarmMotion::OnCheckEnablealarm() 
{
	// TODO: Add your control notification handler code here
	BOOL bRet = m_ctlEnableAlarm.GetCheck();
	GetDlgItem(IDC_EDIT_INTERL_TIME)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_IGNORE_TIME)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_RECORD_IG_TIME)->EnableWindow(bRet);
	GetDlgItem(IDC_CHECK_SCREEN_TIP)->EnableWindow(bRet);
	GetDlgItem(IDC_CHECK_FTP)->EnableWindow(bRet);
	GetDlgItem(IDC_CHECK_BEEP)->EnableWindow(bRet);
	GetDlgItem(IDC_CHECK_EMAIL)->EnableWindow(bRet);
	GetDlgItem(IDC_BUTTON_SETAREA)->EnableWindow(bRet);
	GetDlgItem(IDC_COMBO_DELICACY)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_BEEP)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_FTP)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_SCREEN_TIP)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_EMAIL)->EnableWindow(bRet);
	GetDlgItem(IDC_BTN_ALARM_CTRL_PERIOD)->EnableWindow(bRet);
	GetDlgItem(IDC_BTN_PTZLINK)->EnableWindow(bRet);
}

void CAlarmMotion::Clear()
{
	int nChanneCount = NET_MAX_CHANNUM;
	
	int i = 0;
	for ( i = 0; i < nChanneCount; ++i )
	{
		if (m_pBtnsRecord[i])
		{
			delete m_pBtnsRecord[i];
			m_pBtnsRecord[i] = NULL;
		}
		
		if (m_pBtnsTour[i])
		{
			delete m_pBtnsTour[i];
			m_pBtnsTour[i] = NULL;
		}
		
		if (m_pBtnsSnap[i])
		{
			delete m_pBtnsSnap[i];
			m_pBtnsSnap[i] = NULL;
		}
	}
	
	int nVideoOutChannel = NET_MAX_CHANNUM;
	
	for ( i = 0; i < nVideoOutChannel; ++i )
	{
		if (m_pBtnsAlarmOut[i])
		{
			delete m_pBtnsAlarmOut[i];
			m_pBtnsAlarmOut[i] = NULL;
		}
	}
}

void CAlarmMotion::OnBtnPtzlink() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannelNum.GetCurSel();
	if (nIndex == -1)
	{
		return;
	}
	if (nIndex + 1 == m_nChannelNum)
	{
		nIndex = 0;
	}
	CPtzLinkDlg dlg( m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.PtzLink);
	dlg.m_nChannelNum = m_nChannelNum;
	if (dlg.DoModal() == IDOK)
	{
		memcpy(m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.PtzLink, dlg.GetPtzConf(), sizeof(m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.PtzLink));
	}
}

void CAlarmMotion::OnBtnAlarmCtrlPeriod() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannelNum.GetCurSel();
	if (nIndex == -1)
	{
		return;
	}
	if (nIndex + 1 == m_nChannelNum)
	{
		nIndex = 0;
	}
	CPeriodTimeSetDlg dlg(&m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.schedule);
	if (dlg.DoModal() == IDOK)
	{
		memcpy(&m_MotionCfgAll.vMotionDetectAll[nIndex].hEvent.schedule,dlg.GetConfigWorkSheet(),
			sizeof(SDK_CONFIG_WORKSHEET));
	}

}
