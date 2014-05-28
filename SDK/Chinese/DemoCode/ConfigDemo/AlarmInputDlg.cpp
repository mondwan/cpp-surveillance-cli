// AlarmInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "AlarmInputDlg.h"
#include "PtzLinkDlg.h"
#include "PeriodTimeSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmInputDlg dialog


CAlarmInputDlg::CAlarmInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmInputDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(m_pBtnsRecord, 0, sizeof(m_pBtnsRecord));
	memset(m_pBtnsTour, 0, sizeof(m_pBtnsTour));
	memset(m_pBtnsAlarmOut, 0, sizeof(m_pBtnsAlarmOut));
	memset(m_pBtnsSnap, 0, sizeof(m_pBtnsSnap));
}


void CAlarmInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmInputDlg)
	DDX_Control(pDX, IDC_CHECK_SCREEN_TIP, m_ctlScreenTip);
	DDX_Control(pDX, IDC_CHECK_BEEP, m_ctlBeep);
	DDX_Control(pDX, IDC_CHECK_EMAIL, m_ctlEmail);
	DDX_Control(pDX, IDC_CHECK_FTP, m_ctlFtp);
	DDX_Control(pDX, IDC_CHECK_ENABLEALARM, m_ctlEnableAlarm);
	DDX_Control(pDX, IDC_COMBO_DEV_TYPE, m_ctlDevType);
	DDX_Control(pDX, IDC_COMBO_CHANNELNUM, m_ctlChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmInputDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmInputDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNELNUM, OnSelchangeComboChannelnum)
	ON_BN_CLICKED(IDC_CHECK_ENABLEALARM, OnCheckEnablealarm)
	ON_BN_CLICKED(IDC_BTN_PTZLINK, OnBtnPtzlink)
	ON_BN_CLICKED(IDC_BTN_ALARM_CTRL_PERIOD, OnBtnAlarmCtrlPeriod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmInputDlg message handlers

void CAlarmInputDlg::InitDlgInfo(SDK_ALARM_INPUTCONFIG_ALL *pAlarmInCfgAll, int nChannelNum, int nAlarmInNum, int nAlarmOutNum,SDK_SystemFunction *pSysFunc)
{
	int i = 0;
	int nIndex = 0;
	m_ctlChannel.ResetContent();
	for (;i<nAlarmInNum;i++)
	{
		CString str;
		str.Format("%d",i+1);
		nIndex = m_ctlChannel.AddString(str);
		m_ctlChannel.SetItemData(nIndex,i);
	}
	
	nIndex = m_ctlChannel.AddString(_CS("OneClick.All"));
	m_ctlChannel.SetItemData(nIndex,nAlarmInNum);
	
	m_ctlChannel.SetCurSel(0);

	m_ctlDevType.ResetContent();
	nIndex = m_ctlDevType.AddString(_CS("ConfigAlarm.NormalClose"));
	m_ctlDevType.SetItemData(nIndex,0);
	nIndex = m_ctlDevType.AddString(_CS("ConfigAlarm.NormalOpen"));
	m_ctlDevType.SetItemData(nIndex,1);
	
	m_nAlarmInNum = nAlarmInNum;
	m_nChannelNum = nChannelNum;
	m_nAlarmOutNum = nAlarmOutNum;
	memcpy(&m_AlarmInputCfgAll,pAlarmInCfgAll,sizeof(SDK_ALARM_INPUTCONFIG_ALL));
	memcpy(&m_SysFunc,pSysFunc,sizeof(SDK_SystemFunction));
	ShowInfo(0);
}

void CAlarmInputDlg::InitWndShow()
{
	Clear();
	
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
		bSnap =  m_SysFunc.vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM];
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
	ZeroMemory( m_pBtnsTour, sizeof(m_pBtnsRecord) );
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

BOOL CAlarmInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_nLastChannel = 0;
	m_nAlarmInNum = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmInputDlg::ShowInfo(int nIndex)
{
	InitWndShow();
	m_ctlDevType.SetCurSel(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].iSensorType);
	m_ctlEnableAlarm.SetCheck(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].bEnable);
	
	SetDlgItemInt(IDC_EDIT_INTERL_TIME,m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.iEventLatch);
	SetDlgItemInt(IDC_EDIT_IGNORE_TIME,m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.iAOLatch);
	SetDlgItemInt(IDC_EDIT_RECORD_IG_TIME,m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.iRecordLatch);
	m_ctlBeep.SetCheck(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.bBeep);
	m_ctlFtp.SetCheck(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.bFTP);
	m_ctlEmail.SetCheck(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.bMail);
	m_ctlScreenTip.SetCheck(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.bTip);

	CAlarmInputDlg::SetButtonsCheck(m_pBtnsAlarmOut, m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.dwAlarmOut, m_nAlarmOutNum );
	CAlarmInputDlg::SetButtonsCheck( m_pBtnsRecord, m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.dwRecord, m_nChannelNum );
	CAlarmInputDlg::SetButtonsCheck( m_pBtnsTour, m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.dwTour, m_nChannelNum );		
	CAlarmInputDlg::SetButtonsCheck(m_pBtnsSnap, m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.dwSnapShot, m_nChannelNum);
	
	OnCheckEnablealarm();
}

void CAlarmInputDlg::OnSelchangeComboChannelnum() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if (nIndex == m_nAlarmInNum)
	{
		ShowInfo(0);
		m_nLastChannel = nIndex;
	}else
	{
		if (m_nLastChannel == m_nAlarmInNum)
		{
			ShowInfo(nIndex);
			m_nLastChannel = nIndex;
		}else
		{
			if (nIndex != m_nLastChannel)
			{
				SaveAlarmInputInfo();
				m_nLastChannel = nIndex;
				ShowInfo(nIndex);
			}
		}
	}	
}

void CAlarmInputDlg::OnCheckEnablealarm() 
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
	GetDlgItem(IDC_COMBO_DEV_TYPE)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_BEEP)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_FTP)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_SCREEN_TIP)->EnableWindow(bRet);
	GetDlgItem(IDC_STATIC_EMAIL)->EnableWindow(bRet);
	GetDlgItem(IDC_BTN_ALARM_CTRL_PERIOD)->EnableWindow(bRet);
	GetDlgItem(IDC_BTN_PTZLINK)->EnableWindow(bRet);
}

BOOL CAlarmInputDlg::SaveAlarmInputInfo()
{
	int nIndex = m_ctlChannel.GetCurSel();
	if (nIndex == m_nAlarmInNum)
	{
		for (int i = 0 ;i < m_nAlarmInNum ;i++)
		{
			m_AlarmInputCfgAll.vAlarmConfigAll[i].bEnable = m_ctlEnableAlarm.GetCheck();
			m_AlarmInputCfgAll.vAlarmConfigAll[i].iSensorType = m_ctlDevType.GetCurSel();
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.iEventLatch = GetDlgItemInt(IDC_EDIT_INTERL_TIME);
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.iAOLatch = GetDlgItemInt(IDC_EDIT_IGNORE_TIME);
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.iRecordLatch = GetDlgItemInt(IDC_EDIT_RECORD_IG_TIME);
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.bBeep = m_ctlBeep.GetCheck();
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.bFTP = m_ctlBeep.GetCheck();
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.bTip = m_ctlScreenTip.GetCheck();
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.bMail = m_ctlEmail.GetCheck();
			
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.dwAlarmOut = CAlarmInputDlg::GetButtonsCheck(m_pBtnsAlarmOut,m_nAlarmOutNum);
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.dwRecord = CAlarmInputDlg::GetButtonsCheck(m_pBtnsRecord,m_nChannelNum);
			m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.dwTour = CAlarmInputDlg::GetButtonsCheck(m_pBtnsTour,m_nChannelNum);
	        m_AlarmInputCfgAll.vAlarmConfigAll[i].hEvent.dwSnapShot = CAlarmInputDlg::GetButtonsCheck(m_pBtnsSnap,m_nChannelNum);
		}
	}
	else
	{
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].bEnable = m_ctlEnableAlarm.GetCheck();
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].iSensorType = m_ctlDevType.GetCurSel();
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.iEventLatch = GetDlgItemInt(IDC_EDIT_INTERL_TIME);
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.iAOLatch = GetDlgItemInt(IDC_EDIT_IGNORE_TIME);
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.iRecordLatch = GetDlgItemInt(IDC_EDIT_RECORD_IG_TIME);
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.bBeep = m_ctlBeep.GetCheck();
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.bFTP = m_ctlBeep.GetCheck();
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.bTip = m_ctlScreenTip.GetCheck();
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.bMail = m_ctlEmail.GetCheck();
		
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.dwAlarmOut = CAlarmInputDlg::GetButtonsCheck(m_pBtnsAlarmOut,m_nAlarmOutNum);
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.dwRecord = CAlarmInputDlg::GetButtonsCheck(m_pBtnsRecord,m_nChannelNum);
		m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.dwTour = CAlarmInputDlg::GetButtonsCheck(m_pBtnsTour,m_nChannelNum);
	    m_AlarmInputCfgAll.vAlarmConfigAll[m_nLastChannel].hEvent.dwSnapShot = CAlarmInputDlg::GetButtonsCheck(m_pBtnsSnap,m_nChannelNum);
	}
    
	return TRUE;
}

void CAlarmInputDlg::CleanAll()
{
	m_ctlChannel.SetCurSel(-1);
	m_ctlDevType.SetCurSel(-1);
	SetDlgItemInt(IDC_EDIT_IGNORE_TIME,0);
	SetDlgItemInt(IDC_EDIT_INTERL_TIME,0);
	SetDlgItemInt(IDC_EDIT_RECORD_IG_TIME,0);
	m_ctlEnableAlarm.SetCheck(FALSE);
	m_ctlBeep.SetCheck(FALSE);
	m_ctlFtp.SetCheck(FALSE);
	m_ctlScreenTip.SetCheck(FALSE);
	m_ctlEmail.SetCheck(FALSE);
}

DWORD CAlarmInputDlg::GetButtonsCheck(CButton **pBtn, int nSize)
{
	DWORD dwResult = 0;
	DWORD dwBitValue;
	
	for (int i = 0; i < nSize; i++)
	{
		dwBitValue = 0;
		
		if (pBtn[i]->GetCheck())
		{
			dwResult = dwResult | (1 << i);
		}
	}
	
	return dwResult;
}

BOOL CAlarmInputDlg::SetButtonsCheck(CButton **pBtn, DWORD dwValue, int nSize)
{
	DWORD dwBitValue;
	
	for (int i = 0; i < nSize; i++)
	{
		dwBitValue = 1 << i;
		pBtn[i]->SetCheck(dwValue & dwBitValue);
	}
	
	return TRUE;
}

void CAlarmInputDlg::Clear()
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

void CAlarmInputDlg::OnBtnPtzlink() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if (nIndex == -1)
	{
		return;
	}
	if (nIndex + 1 == m_nChannelNum)
	{
		nIndex = 0;
	}
	CPtzLinkDlg dlg( m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.PtzLink);
	dlg.m_nChannelNum = m_nChannelNum;
	if (dlg.DoModal() == IDOK)
	{
		memcpy(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.PtzLink, dlg.GetPtzConf(), sizeof(m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.PtzLink));
	}
}

void CAlarmInputDlg::OnBtnAlarmCtrlPeriod() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if (nIndex == -1)
	{
		return;
	}
	if (nIndex + 1 == m_nAlarmInNum)
	{
		nIndex = 0;
	}
	
	CPeriodTimeSetDlg dlg(&m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.schedule);
	if (dlg.DoModal() == IDOK)
	{
		memcpy( &m_AlarmInputCfgAll.vAlarmConfigAll[nIndex].hEvent.schedule, 
		   dlg.GetConfigWorkSheet(), sizeof( SDK_CONFIG_WORKSHEET ) );
	}
}
