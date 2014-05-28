// AlarmException.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "AlarmException.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmException dialog


CAlarmException::CAlarmException(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmException::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmException)
	m_edit = 0;
	//}}AFX_DATA_INIT
	m_nLastEvent = 0;
	memset( &m_bGet, 0 , sizeof(m_bGet));
	
	memset(&m_OldExceptionNoExist, 0, sizeof(m_OldExceptionNoExist));
	memset(&m_OldExceptionFailed, 0, sizeof(m_OldExceptionFailed));
	memset(&m_OldExceptionLowSpace, 0, sizeof(m_OldExceptionLowSpace));
	memset(&m_OldExceptionIpConflict, 0, sizeof(m_OldExceptionIpConflict));
	memset(&m_OldExceptionNetAbort, 0, sizeof(m_OldExceptionNetAbort));
	
	m_bNetIP = false;
	m_bNetAbort = false;
	m_bStorageFailed = false;
	m_bStorageLess = false;
	m_bStorageNoExist = false;
}


void CAlarmException::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmException)
	DDX_Control(pDX, IDC_EDIT_PERCENTAGE, m_editPercentage);
	DDX_Control(pDX, IDC_CHECK_SCREEN_TIP, m_checkScreenTip);
	DDX_Control(pDX, IDC_CHECK_BEEP, m_checkBeep);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEable);
	DDX_Control(pDX, IDC_COMBO_EVENT, m_ctrlEvent);
	DDX_Text(pDX, IDC_EDIT_PERCENTAGE, m_edit);
	DDV_MinMaxInt(pDX, m_edit, 0, 100);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_EVENT, m_ctrlEvent);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkEable);
	DDX_Control(pDX, IDC_CHECK_BEEP, m_checkBeep);
	DDX_Control(pDX, IDC_CHECK_SCREEN_TIP, m_checkScreenTip);
	DDX_Control(pDX, IDC_EDIT_PERCENTAGE, m_editPercentage);
}


BEGIN_MESSAGE_MAP(CAlarmException, CDialog)
	//{{AFX_MSG_MAP(CAlarmException)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_EVENT, OnSelchangeComboEvent)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_EDIT_PERCENTAGE, OnChangeEditPercentage)
	ON_BN_CLICKED(IDC_CHECK_SCREEN_TIP, OnCheckScreenTip)
	ON_BN_CLICKED(IDC_CHECK_BEEP, OnCheckBeep)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_ENABLE, CAlarmException::OnBnClickedCheckEnable)
//	ON_EN_CHANGE(IDC_EDIT_PERCENTAGE, CAlarmException::OnEnChangeEditPercentage)
//	ON_EN_KILLFOCUS(IDC_EDIT_PERCENTAGE, CAlarmException::OnEnKillfocusEditPercentage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmException message handlers

void CAlarmException::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	memset(&m_bGet, 0, sizeof(m_bGet));
	//ructToWinData();
}

void CAlarmException::OnSelchangeComboEvent() 
{
	// TODO: Add your control notification handler code here
	
//	int nIndex = m_ctrlEvent.GetCurSel();
	ShowInfo();

}

BOOL CAlarmException::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmException::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
}


BOOL CAlarmException::SaveAlarmExceptionInfo()
{
	UpdateData();
	int nValue = m_ctrlEvent.GetCurSel();
	switch ( nValue )
	{
	case STORAGE_NOEXIT:
		{
			m_OldExceptionNoExist.bEnable = m_checkEable.GetCheck();
			m_OldExceptionNoExist.hEvent.bBeep = m_checkBeep.GetCheck();
			m_OldExceptionNoExist.hEvent.bTip = m_checkScreenTip.GetCheck();
		}
		break;
	case STORAGE_LOWSPACE:
		{
			m_OldExceptionLowSpace.bEnable = m_checkEable.GetCheck();
			m_OldExceptionLowSpace.hEvent.bBeep = m_checkBeep.GetCheck();
			m_OldExceptionLowSpace.hEvent.bTip = m_checkScreenTip.GetCheck();
			CString strPer;
			m_editPercentage.GetWindowText(strPer);
			m_OldExceptionLowSpace.iLowerLimit = atoi(strPer);
		}
		break;
	case STORAGE_FAILURE:
		{
			m_OldExceptionFailed.bEnable = m_checkEable.GetCheck();
			m_OldExceptionFailed.hEvent.bBeep = m_checkBeep.GetCheck();
			m_OldExceptionFailed.hEvent.bTip = m_checkScreenTip.GetCheck();
		}
		break;
	case NET_IPCONFLICT:
		{
			m_OldExceptionIpConflict.bEnable = m_checkEable.GetCheck();
			m_OldExceptionIpConflict.hEvent.bBeep = m_checkBeep.GetCheck();
			m_OldExceptionIpConflict.hEvent.bTip = m_checkScreenTip.GetCheck();
		}
		break;
	case NET_NETABORT:
		{
			m_OldExceptionNetAbort.bEnable = m_checkEable.GetCheck();
			m_OldExceptionNetAbort.hEvent.bBeep = m_checkBeep.GetCheck();
			m_OldExceptionNetAbort.hEvent.bTip = m_checkScreenTip.GetCheck();
		}
		break;
	default:
		break;
	}
	return true;
}

void CAlarmException::InitDlgInfo(SDK_VIDEOLOSSCONFIG *pStorageNE,SDK_VIDEOLOSSCONFIG *pStorageFL,
								  SDK_VIDEOLOSSCONFIG *pNetipCfg,SDK_VIDEOLOSSCONFIG *pNetaBort,
								  SDK_SystemFunction *pSysFunc,SDK_StorageLowSpaceConfig *pStorageLSCfg)
{
/*	int nRet = 0;*/
	m_pSysFucAll = pSysFunc;
	InitWndShow();
/*	int nValue = m_ctrlEvent.GetCurSel();*/
	if (InitWndShow())
	{
		memcpy(&m_OldExceptionNoExist, pStorageNE, sizeof(m_OldExceptionNoExist));
		memcpy(&m_OldExceptionLowSpace, pStorageLSCfg, sizeof(m_OldExceptionLowSpace));
		memcpy(&m_OldExceptionFailed, pStorageFL, sizeof(m_OldExceptionFailed));
		memcpy(&m_OldExceptionIpConflict, pNetipCfg, sizeof(m_OldExceptionIpConflict));
		memcpy(&m_OldExceptionNetAbort, pNetaBort, sizeof(m_OldExceptionNetAbort));
		ShowInfo();
	}

	OnBnClickedCheckEnable();
	UpdateData(FALSE);
	
// 
// 	return true;
	
}
void CAlarmException::OnBnClickedCheckEnable()
{
	// TODO: 在此添加控件通知处理程序代码
	m_checkBeep.EnableWindow(m_checkEable.GetCheck());
	m_checkScreenTip.EnableWindow(m_checkEable.GetCheck());
	
	if ( m_ctrlEvent.GetCurSel() == 1 )
	{
		m_editPercentage.EnableWindow(m_checkEable.GetCheck());
		m_checkBeep.EnableWindow(m_checkEable.GetCheck());
		m_checkScreenTip.EnableWindow(m_checkEable.GetCheck());
	}
	int nValue = m_ctrlEvent.GetCurSel();
	switch ( nValue )
	{
	case STORAGE_NOEXIT:
		m_OldExceptionNoExist.bEnable=m_checkEable.GetCheck();
		break;
	case STORAGE_FAILURE:
		m_OldExceptionFailed.bEnable = m_checkEable.GetCheck();
		break;
	case STORAGE_LOWSPACE:
		m_OldExceptionLowSpace.bEnable=m_checkEable.GetCheck();
		break;
	case NET_IPCONFLICT:
		m_OldExceptionIpConflict.bEnable = m_checkEable.GetCheck();
		break;
	case NET_NETABORT:
		m_OldExceptionNetAbort.bEnable =m_checkEable.GetCheck();
	default:
		break;
	}

}


BOOL CAlarmException::InitWndShow()
{
	//获取能力级
// 	CUserDataManager *pData = CUserDataManager::instance();
	//获取设备版本具体时间
// 	COleDateTime VesionTime0(2011, 11, 1, 9, 16, 43);
// 	COleDateTime VesionTime1(pData->GetSysInfo()->tmBuildTime.year, pData->GetSysInfo()->tmBuildTime.month, pData->GetSysInfo()->tmBuildTime.day,
// 		pData->GetSysInfo()->tmBuildTime.hour, pData->GetSysInfo()->tmBuildTime.minute, pData->GetSysInfo()->tmBuildTime.second);  //当前设备的版本时间
// 	if ( VesionTime1 >= VesionTime0 )
// 	{
	
 		m_bNetIP =m_pSysFucAll->vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_IP_CONFLICT];
		m_bNetAbort =m_pSysFucAll->vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_NET_ABORT];
		m_bStorageFailed =m_pSysFucAll->vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE];
		m_bStorageLess =m_pSysFucAll->vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_STORAGE_LOWSPACE];
		m_bStorageNoExist =m_pSysFucAll->vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE];
// 	}
// 
	m_ctrlEvent.ResetContent();
	int i = 0;
	if ( m_bStorageNoExist)
	{
		m_ctrlEvent.AddString(_CS("InfoLog.StorageNotExist"));
		m_ctrlEvent.SetItemData(i, STORAGE_NOEXIT);
		i++;

	}
	if ( m_bStorageLess)
	{
		i=m_ctrlEvent.AddString(_CS("InfoLog.StorageLowSpace"));
		m_ctrlEvent.SetItemData(i, STORAGE_LOWSPACE);
		i++;

	}
	if ( m_bStorageFailed)
	{
		i=m_ctrlEvent.AddString(_CS("InfoLog.StorageFailure"));
		m_ctrlEvent.SetItemData(i, STORAGE_FAILURE);
		i++;

	}
	if ( m_bNetIP)
	{
		i=m_ctrlEvent.AddString(_CS("InfoLog.NetIPConflict"));
		m_ctrlEvent.SetItemData(i, NET_IPCONFLICT);
		i++;

	}
	if ( m_bNetAbort)
	{
		i=m_ctrlEvent.AddString(_CS("InfoLog.NetAbort"));
		m_ctrlEvent.SetItemData(i, NET_NETABORT);

	}
	m_ctrlEvent.SetCurSel(0);

	return TRUE;
}

void CAlarmException::ReInit()
{
/*	CDlgSetBase::ReInit();*/

	for ( int i = 0 ; i < STORAGE_NR; i ++ )
	{
		m_bGet[i] = false;
	}
}
void CAlarmException::ShowInfo()
{
//	UpdateData();
	int nValue = m_ctrlEvent.GetCurSel();
	switch ( nValue )
	{
	case STORAGE_NOEXIT:
		{
			m_editPercentage.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SPACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_UNITS)->ShowWindow(SW_HIDE);
			m_checkEable.SetCheck(m_OldExceptionNoExist.bEnable);
			m_checkBeep.SetCheck(m_OldExceptionNoExist.hEvent.bBeep);
			m_checkScreenTip.SetCheck(m_OldExceptionNoExist.hEvent.bTip);

		}
		break;
	case STORAGE_LOWSPACE:
		{
			m_editPercentage.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SPACE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_UNITS)->ShowWindow(SW_SHOW);

			m_checkEable.SetCheck(m_OldExceptionLowSpace.bEnable);
			m_checkBeep.SetCheck(m_OldExceptionLowSpace.hEvent.bBeep);
			m_checkScreenTip.SetCheck(m_OldExceptionLowSpace.hEvent.bTip);
			
			CString strPer;
			strPer.Format(_T("%d"), m_OldExceptionLowSpace.iLowerLimit);
			m_editPercentage.SetWindowText(strPer);
		}
		break;
	case STORAGE_FAILURE:
		{
			m_editPercentage.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SPACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_UNITS)->ShowWindow(SW_HIDE);

			m_checkEable.SetCheck(m_OldExceptionFailed.bEnable);
			m_checkBeep.SetCheck(m_OldExceptionFailed.hEvent.bBeep);
			m_checkScreenTip.SetCheck(m_OldExceptionFailed.hEvent.bTip);

		}
		break;
	case NET_IPCONFLICT:
		{
			m_editPercentage.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SPACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_UNITS)->ShowWindow(SW_HIDE);

			m_checkEable.SetCheck(m_OldExceptionIpConflict.bEnable);
			m_checkBeep.SetCheck(m_OldExceptionIpConflict.hEvent.bBeep);
			m_checkScreenTip.SetCheck(m_OldExceptionIpConflict.hEvent.bTip);

		}
		break;
	case NET_NETABORT:
		{
			m_editPercentage.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SPACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_UNITS)->ShowWindow(SW_HIDE);

			m_checkEable.SetCheck(m_OldExceptionNetAbort.bEnable);
			m_checkBeep.SetCheck(m_OldExceptionNetAbort.hEvent.bBeep);
			m_checkScreenTip.SetCheck(m_OldExceptionNetAbort.hEvent.bTip);
		}
		break;
	default:
		break;
		
	}
	OnBnClickedCheckEnable();
//	return true;

}
void CAlarmException::CleanAll()
{
	m_ctrlEvent.ResetContent();
	m_checkBeep.SetCheck(false);
	m_checkEable.SetCheck(false);
	m_checkScreenTip.SetCheck(false);
	m_editPercentage.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SPACE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_UNITS)->ShowWindow(SW_HIDE);
	UpdateData(false);
}

void CAlarmException::OnChangeEditPercentage() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString value;
	m_editPercentage.GetWindowText(value);
	if (atoi(value) > 100)
	{
		GetDlgItem(IDC_EDIT_PERCENTAGE)->SetWindowText("100");
		
	}
	if (atoi(value) < 0)
	{
		GetDlgItem(IDC_EDIT_PERCENTAGE)->SetWindowText("0");
	}
	// TODO: Add your control notification handler code here
	CString strPer;
	m_editPercentage.GetWindowText(strPer);
	m_OldExceptionLowSpace.iLowerLimit=atoi(strPer);
	
}

void CAlarmException::OnCheckScreenTip() 
{
	// TODO: Add your control notification handler code here
	int nValue = m_ctrlEvent.GetCurSel();
	switch ( nValue )
	{
	case STORAGE_NOEXIT:
		m_OldExceptionNoExist.hEvent.bTip=m_checkScreenTip.GetCheck();
		break;
	case STORAGE_FAILURE:
		m_OldExceptionFailed.hEvent.bTip=m_checkScreenTip.GetCheck();
		break;
	case STORAGE_LOWSPACE:
		m_OldExceptionLowSpace.hEvent.bTip=m_checkScreenTip.GetCheck();
		break;
	case NET_IPCONFLICT:
		m_OldExceptionIpConflict.hEvent.bTip=m_checkScreenTip.GetCheck();
		break;
	case NET_NETABORT:
		m_OldExceptionNetAbort.hEvent.bTip=m_checkScreenTip.GetCheck();
	default:
		break;
	}

}

void CAlarmException::OnCheckBeep() 
{
	// TODO: Add your control notification handler code here
	int nValue = m_ctrlEvent.GetCurSel();
	switch ( nValue )
	{
	case STORAGE_NOEXIT:
		m_OldExceptionNoExist.hEvent.bBeep=m_checkBeep.GetCheck();
		break;
	case STORAGE_FAILURE:
		m_OldExceptionFailed.hEvent.bBeep=m_checkBeep.GetCheck();
		break;
	case STORAGE_LOWSPACE:
		m_OldExceptionLowSpace.hEvent.bBeep=m_checkBeep.GetCheck();
		break;
	case NET_IPCONFLICT:
		m_OldExceptionIpConflict.hEvent.bBeep=m_checkBeep.GetCheck();
		break;
	case NET_NETABORT:
		m_OldExceptionNetAbort.hEvent.bTip=m_checkScreenTip.GetCheck();
	default:
		break;
	}
}
