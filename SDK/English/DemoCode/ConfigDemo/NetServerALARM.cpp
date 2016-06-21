// NetServerALARM.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerALARM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerALARM dialog


CNetServerALARM::CNetServerALARM(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerALARM::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerALARM)
	m_sServerName = _T("");
	m_nPort = 0;
	//}}AFX_DATA_INIT
}


void CNetServerALARM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerALARM)
	DDX_Control(pDX, IDC_EDIT_SVR, m_editSVR);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_CHECK_LOG, m_checkLog);
	DDX_Control(pDX, IDC_CHECK_EANBLE, m_checkEnable);
	DDX_Control(pDX, IDC_CHECK_ALARM, m_checkAlarm);
	DDX_Text(pDX, IDC_EDIT_SVR, m_sServerName);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerALARM, CDialog)
	//{{AFX_MSG_MAP(CNetServerALARM)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_CHECK_EANBLE, OnCheckEanble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerALARM message handlers

BOOL CNetServerALARM::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	m_editPort.SetLimitText(5);
	m_editSVR.SetLimitText(63);
	CenterWindow();
	return TRUE;  
}

void CNetServerALARM::InitDlgInfo(SDK_NetAlarmServerConfigAll *pNetAlarmCfg)
{
	m_cmbType.ResetContent();
	m_ensure = FALSE;
	memcpy(&m_netAlarmCenterCfg,pNetAlarmCfg,sizeof(SDK_NetAlarmServerConfigAll));
	for (int i = 0; i < NET_MAX_ALARMSERVER_TYPE; ++i)
	{
		if (strcmp(m_netAlarmCenterCfg.vAlarmServerConfigAll[i].sAlarmServerKey,"NONE"))
		{
			m_cmbType.InsertString(i,m_netAlarmCenterCfg.vAlarmServerConfigAll[i].sAlarmServerKey);
		}
	}
	m_cmbType.SetCurSel(0);
	m_nOldSelect = 0;
	OnCheckEanble();
	UpdateAlarmCenterType(0);
}

void CNetServerALARM::UpdateAlarmCenterType(int nType)
{
	m_sServerName = m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].Server.ServerName;
	m_nPort = m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].Server.Port;
	m_checkAlarm.SetCheck(m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].bAlarm);
	m_checkEnable.SetCheck(m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].bEnable);
	m_checkLog.SetCheck(m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].bLog);
	UpdateData(FALSE);
}

void CNetServerALARM::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_cmbType.GetCurSel();
	if (m_nOldSelect != nSelect)
	{
		SaveConfig(m_nOldSelect);
	}
	m_nOldSelect = nSelect;
	UpdateAlarmCenterType(nSelect);
}

void CNetServerALARM::SaveConfig(int nType)
{
	UpdateData();
	m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].bAlarm = m_checkAlarm.GetCheck();
	m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].bEnable = m_checkEnable.GetCheck();
	m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].bLog = m_checkLog.GetCheck();
	strncpy(m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].Server.ServerName,m_sServerName.GetBuffer(0),
		sizeof(m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].Server.ServerName));
	m_netAlarmCenterCfg.vAlarmServerConfigAll[nType].Server.Port = m_nPort;
}



void CNetServerALARM::OnOK() 
{
	// TODO: Add extra validation here
	m_ensure = TRUE;
	SaveConfig(m_nOldSelect);
	CDialog::OnOK();
}

void CNetServerALARM::OnCheckEanble() 
{
	// TODO: Add your control notification handler code here
	int bEnable = m_checkEnable.GetCheck();
	m_editPort.EnableWindow(bEnable);
	m_editSVR.EnableWindow(bEnable);
	m_checkLog.EnableWindow(bEnable);
	m_checkAlarm.EnableWindow(bEnable);
}
