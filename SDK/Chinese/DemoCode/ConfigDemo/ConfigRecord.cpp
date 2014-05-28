// ConfigRecord.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigRecord.h"

#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigRecord dialog


CConfigRecord::CConfigRecord(CWnd* pParent /*=NULL*/)
: CDialog(CConfigRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigRecord)
	/*	m_prd1EndHour = 0;
	m_prd1EndMinute = 0;
	m_prd1StartHour = 0;
	m_prd1StartMinute = 0;
	m_prd2EndHour = 0;
	m_prd2StartHour = 0;
	m_prd2StartMinute = 0;
	m_prd2EndMinute = 0;
	m_prd3EndHour = 0;
	m_prd3EndMinute = 0;
	m_prd3StartHour = 0;
	m_prd3StartMinute = 0;
	m_prd4EndHour = 0;
	m_prd4EndMinute = 0;
	m_prd4StartHour = 0;
	m_prd4StartMinute = 0;
	m_prd5EndHour = 0;
	m_prd5EndMinute = 0;
	m_prd5StartHour = 0;
	m_prd5StartMinute = 0;
	m_prd6EndHour = 0;
	m_prd6EndMinute = 0;
	m_prd6StartHour = 0;
	m_prd6StartMinute = 0;*/
	//}}AFX_DATA_INIT
	memset(m_pTimeSectValue,0,sizeof(m_pTimeSectValue));
}


void CConfigRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigRecord)
	DDX_Control(pDX, IDC_CHECK_PRD6, m_ctlPRD6);
	DDX_Control(pDX, IDC_CHECK_PRD5, m_ctlPRD5);
	DDX_Control(pDX, IDC_CHECK_DTT6, m_ctlDTT6);
	DDX_Control(pDX, IDC_CHECK_DTT5, m_ctlDTT5);
	DDX_Control(pDX, IDC_CHECK_ALM6, m_ctlALM6);
	DDX_Control(pDX, IDC_CHECK_ALM5, m_ctlALM5);
	DDX_Control(pDX, IDC_CHECK_PRD4, m_ctlPRD4);
	DDX_Control(pDX, IDC_CHECK_PRD3, m_ctlPRD3);
	DDX_Control(pDX, IDC_CHECK_PRD2, m_ctlPRD2);
	DDX_Control(pDX, IDC_CHECK_PRD1, m_ctlPRD1);
	DDX_Control(pDX, IDC_CHECK_DTT4, m_ctlDTT4);
	DDX_Control(pDX, IDC_CHECK_DTT3, m_ctlDTT3);
	DDX_Control(pDX, IDC_CHECK_DTT2, m_ctlDTT2);
	DDX_Control(pDX, IDC_CHECK_DTT1, m_ctlDTT1);
	DDX_Control(pDX, IDC_CHECK_ALM4, m_ctlALM4);
	DDX_Control(pDX, IDC_CHECK_ALM3, m_ctlALM3);
	DDX_Control(pDX, IDC_CHECK_ALM2, m_ctlALM2);
	DDX_Control(pDX, IDC_CHECK_ALM1, m_ctlALM1);
	DDX_Control(pDX, IDC_CHECK_REDUNDANCY, m_ctlRedundancy);
	DDX_Control(pDX, IDC_COMBO_CHANNO, m_ctlChannel);
	DDX_Control(pDX, IDC_COMBO_RECORDWEEK, m_ctlRecordWeek);
	DDX_Text(pDX, IDC_EDIT_PRD1_E_HOUR, m_prd1EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD1_E_MINUTE, m_prd1EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD1_S_HOUR, m_prd1StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD1_S_MINUTE, m_prd1StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD2_E_HOUR, m_prd2EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD2_S_HOUR, m_prd2StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD2_S_MINUTE, m_prd2StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD2_E_MINUTE, m_prd2EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD3_E_HOUR, m_prd3EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD3_E_MINUTE, m_prd3EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD3_S_HOUR, m_prd3StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD3_S_MINUTE, m_prd3StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD4_E_HOUR, m_prd4EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD4_E_MINUTE, m_prd4EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD4_S_HOUR, m_prd4StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD4_S_MINUTE, m_prd4StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD5_E_HOUR, m_prd5EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD5_E_MINUTE, m_prd5EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD5_S_HOUR, m_prd5StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD5_S_MINUTE, m_prd5StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD6_E_HOUR, m_prd6EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD6_E_MINUTE, m_prd6EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD6_S_HOUR, m_prd6StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD6_S_MINUTE, m_prd6StartMinute);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigRecord, CDialog)
//{{AFX_MSG_MAP(CConfigRecord)	
ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
ON_CBN_SELCHANGE(IDC_COMBO_CHANNO, OnSelchangeComboChanno)
ON_CBN_SELCHANGE(IDC_COMBO_RECORDWEEK, OnSelchangeComboRecordweek)
ON_BN_CLICKED(IDC_RADIO0, OnRadio0)
ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
ON_CONTROL_RANGE(EN_CHANGE, IDC_EDIT_PRD1_S_HOUR, IDC_EDIT_PRD6_E_MINUTE, OnChangeEdit)
ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_EDIT_PRD1_S_HOUR, IDC_EDIT_PRD6_E_MINUTE, OnKillfocusEdit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigRecord message handlers

void CConfigRecord::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	if ( -1 != m_ctlChannel.GetCurSel())
	{
		SaveRecordAll();
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetRecordConfigInfo(&m_RecordCfg);
	}
}

BOOL CConfigRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_ctlRecordWeek.ResetContent();
	int nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.Sun"));
	m_ctlRecordWeek.SetItemData(nIndex,0);
	nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.Mon"));
	m_ctlRecordWeek.SetItemData(nIndex,1);
	nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.Tue"));
	m_ctlRecordWeek.SetItemData(nIndex,2);
	nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.Wed"));
	m_ctlRecordWeek.SetItemData(nIndex,3);
	nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.Thu"));
	m_ctlRecordWeek.SetItemData(nIndex,4);
	nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.Fri"));
	m_ctlRecordWeek.SetItemData(nIndex,5);
	nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.Sat"));
	m_ctlRecordWeek.SetItemData(nIndex,6);
	nIndex = m_ctlRecordWeek.AddString(_CS("OneClick.All"));
	m_ctlRecordWeek.SetItemData(nIndex,7);
	m_nLastChannel = 0;
	m_nLastWeek = 0;
	m_bCheckEdit = FALSE;
	CleanAll();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigRecord::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetRecordConfigInfo();
}

void CConfigRecord::CleanAll()
{
	m_ctlRecordWeek.SetCurSel(-1);
	m_ctlChannel.SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_PRERECLEN, "");
	SetDlgItemText(IDC_EDIT_RECORDLEN, "");
	m_ctlRedundancy.SetCheck(0);
	m_ctlPRD1.SetCheck(0);
	m_ctlPRD2.SetCheck(0);
	m_ctlPRD3.SetCheck(0);
	m_ctlPRD4.SetCheck(0);
	m_ctlDTT1.SetCheck(0);
	m_ctlDTT2.SetCheck(0);
	m_ctlDTT3.SetCheck(0);
	m_ctlDTT4.SetCheck(0);
	m_ctlALM1.SetCheck(0);
	m_ctlALM2.SetCheck(0);
	m_ctlALM3.SetCheck(0);
	m_ctlALM4.SetCheck(0);
	
	int i=0;
	for(;i<6;i++)
	{
		SDK_TIMESECTION periodInfo = {0};
		periodInfo.endHour = 24;
		ShowPeriodInfo(&periodInfo,i+1,0);
	}

	for ( i = 0 ;i < NET_N_TSECT;i++)
	{
		if (m_pTimeSectValue[i])
		{
			delete m_pTimeSectValue[i];
			m_pTimeSectValue[i] = NULL;
		}
	}
}

void CConfigRecord::ShowPeriodInfo(SDK_TIMESECTION *pTime,int nNum ,UINT typeMask)
{
	switch(nNum) {
	case 1:
		m_ctlPRD1.SetCheck((typeMask & 0x01)?1:0);
		m_ctlDTT1.SetCheck((typeMask & 0x04)?1:0);
		m_ctlALM1.SetCheck((typeMask & 0x02)?1:0);
		
		m_prd1StartHour = pTime->startHour;
		m_prd1StartMinute = pTime->startMinute;
		m_prd1EndHour = pTime->endHour;
		m_prd1EndMinute = pTime->endMinute;
		break;
	case 2:
		m_ctlPRD2.SetCheck((typeMask & 0x01)?1:0);
		m_ctlDTT2.SetCheck((typeMask & 0x04)?1:0);
		m_ctlALM2.SetCheck((typeMask & 0x02)?1:0);
		
		m_prd2StartHour = pTime->startHour;
		m_prd2StartMinute = pTime->startMinute;
		m_prd2EndHour = pTime->endHour;
		m_prd2EndMinute = pTime->endMinute;
		break;
	case 3:
		m_ctlPRD3.SetCheck((typeMask & 0x01)?1:0);
		m_ctlDTT3.SetCheck((typeMask & 0x04)?1:0);
		m_ctlALM3.SetCheck((typeMask & 0x02)?1:0);
		
		m_prd3StartHour = pTime->startHour;
		m_prd3StartMinute = pTime->startMinute;
		m_prd3EndHour = pTime->endHour;
		m_prd3EndMinute = pTime->endMinute;
		break;
	case 4:
		m_ctlPRD4.SetCheck((typeMask & 0x01)?1:0);
		m_ctlDTT4.SetCheck((typeMask & 0x04)?1:0);
		m_ctlALM4.SetCheck((typeMask & 0x02)?1:0);
		
		m_prd4StartHour = pTime->startHour;
		m_prd4StartMinute = pTime->startMinute;
		m_prd4EndHour = pTime->endHour;
		m_prd4EndMinute = pTime->endMinute;
		break;
	case 5:
		m_ctlPRD5.SetCheck((typeMask & 0x01)?1:0);
		m_ctlDTT5.SetCheck((typeMask & 0x04)?1:0);
		m_ctlALM5.SetCheck((typeMask & 0x02)?1:0);
		
		m_prd5StartHour = pTime->startHour;
		m_prd5StartMinute = pTime->startMinute;
		m_prd5EndHour = pTime->endHour;
		m_prd5EndMinute = pTime->endMinute;
		break;
	case 6:
		m_ctlPRD6.SetCheck((typeMask & 0x01)?1:0);
		m_ctlDTT6.SetCheck((typeMask & 0x04)?1:0);
		m_ctlALM6.SetCheck((typeMask & 0x02)?1:0);
		
		m_prd6StartHour = pTime->startHour;
		m_prd6StartMinute = pTime->startMinute;
		m_prd6EndHour = pTime->endHour;
		m_prd6EndMinute = pTime->endMinute;
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}

void CConfigRecord::InitDlgInfo(SDK_RECORDCONFIG_ALL *pRecordCfg, int nChannelNum)
{
	m_bCheckEdit = FALSE;
	m_nLastChannel = 0;
	m_nLastWeek = 0;
	int nIndex = 0;
	m_nChannelNum = nChannelNum;
	m_ctlChannel.ResetContent();
	for(int i=0;i<nChannelNum;i++)
	{
		CString str;
		str.Format(_T("%d"),i+1);
		nIndex = m_ctlChannel.AddString(str);
		m_ctlChannel.SetItemData(nIndex,i);
		m_RecordCfg.vRecordConfigAll[i] = pRecordCfg->vRecordConfigAll[i];
	}
	nIndex = m_ctlChannel.AddString(_CS("OneClick.All"));
	m_ctlChannel.SetItemData(nIndex,nChannelNum);
	
	m_ctlChannel.SetCurSel(0);
	
	ShowWindow(0);


	m_nLastWeek=m_ctlRecordWeek.GetCurSel();
	for(int j=0;j<6;j++)
	{
		SDK_TIMESECTION periodInfo = m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[m_nLastWeek][j];
		ShowPeriodInfo(&periodInfo,j+1,m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[m_nLastWeek][j]);
	}
	
	m_bCheckEdit = TRUE;
}

void CConfigRecord::OnSelchangeComboChanno() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if (nIndex == m_nChannelNum)
	{
		ShowWindow(0);
		m_nLastChannel = nIndex;
	}
	else
	{
		if (m_nLastChannel == m_nChannelNum)
		{
			ShowWindow(nIndex);
			m_nLastChannel = nIndex;
		}else
		{
			if (nIndex != m_nLastChannel)
			{
				SaveRecordInfo(m_nLastChannel);
				m_nLastChannel = nIndex;
				ShowWindow(nIndex);
			}
		}
	}
}

void CConfigRecord::SaveRecordInfo(int nIndex)
{
	int   iRadioButton; 
    iRadioButton=GetCheckedRadioButton(IDC_RADIO0,IDC_RADIO2);
	if(iRadioButton == IDC_RADIO0)
	{
		m_RecordCfg.vRecordConfigAll[nIndex].iRecordMode = 2;
	}else if (iRadioButton == IDC_RADIO1)
	{
		m_RecordCfg.vRecordConfigAll[nIndex].iRecordMode = 1;
	}else if (iRadioButton == IDC_RADIO2)
	{
		m_RecordCfg.vRecordConfigAll[nIndex].iRecordMode = 0;
	}
	m_RecordCfg.vRecordConfigAll[nIndex].bRedundancy = m_ctlRedundancy.GetCheck();
	m_RecordCfg.vRecordConfigAll[nIndex].iPreRecord = GetDlgItemInt(IDC_EDIT_PRERECLEN);
	m_RecordCfg.vRecordConfigAll[nIndex].iPacketLength = GetDlgItemInt(IDC_EDIT_RECORDLEN);
	SaveWeekAll();
}

void CConfigRecord::ShowWindow(int nChannel)
{	
	m_ctlRedundancy.SetCheck(m_RecordCfg.vRecordConfigAll[nChannel].bRedundancy);
	SetDlgItemInt(IDC_EDIT_PRERECLEN,m_RecordCfg.vRecordConfigAll[nChannel].iPreRecord);
	SetDlgItemInt(IDC_EDIT_RECORDLEN,m_RecordCfg.vRecordConfigAll[nChannel].iPacketLength);
	if ((m_RecordCfg.vRecordConfigAll[nChannel].iRecordMode == 1) || (m_RecordCfg.vRecordConfigAll[nChannel].iRecordMode == 0))
	{
		if (m_RecordCfg.vRecordConfigAll[nChannel].iRecordMode == 1)
		{
			CheckRadioButton(IDC_RADIO0,IDC_RADIO2,IDC_RADIO1);
		}else
		{
			CheckRadioButton(IDC_RADIO0,IDC_RADIO2,IDC_RADIO2);
		}
		ShowTime(FALSE);
	}else
	{
		CheckRadioButton(IDC_RADIO0,IDC_RADIO2,IDC_RADIO0);
		ShowTime(TRUE);
	}
	ShowTime(FALSE);
	CTime time = CTime::GetCurrentTime();
	m_ctlRecordWeek.SetCurSel(time.GetDayOfWeek()-1);
	m_nLastWeek = 0;
}

void CConfigRecord::OnSelchangeComboRecordweek() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlRecordWeek.GetCurSel();
	if (nIndex == 7)
	{
		for(int i=0;i<6;i++)
		{
			SDK_TIMESECTION periodInfo = m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[0][i];
			ShowPeriodInfo(&periodInfo,i+1,m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[0][i]);
		}
		m_nLastWeek = 7;
	}
	else
	{
		if (m_nLastWeek == 7)
		{
			for(int i=0;i<6;i++)
			{
				SDK_TIMESECTION periodInfo = m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nIndex][i];
				ShowPeriodInfo(&periodInfo,i+1,m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nIndex][i]);
			}
			m_nLastWeek = nIndex;
		}
		else if (nIndex != m_nLastWeek)
		{
			SaveWeekInfo(m_nLastWeek); 
			for(int i=0;i<6;i++)
			{
				SDK_TIMESECTION periodInfo = m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nIndex][i];
				ShowPeriodInfo(&periodInfo,i+1,m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nIndex][i]);
			}
			m_nLastWeek = nIndex;
		}
	}
}

void CConfigRecord::SaveWeekInfo(int nWeek)
{
	UpdateData(TRUE);
	UINT pTypeMask[6] = {0};
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].startHour = m_prd1StartHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].startMinute = m_prd1StartMinute;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].endHour = m_prd1EndHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].endMinute = m_prd1EndMinute;
	if (m_ctlDTT1.GetCheck())
	{
		pTypeMask[0] += 4;
	}
	if (m_ctlALM1.GetCheck())
	{
		pTypeMask[0] += 2;
	}
	if (m_ctlPRD1.GetCheck())
	{
		pTypeMask[0] += 1;
	}
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nWeek][0] = pTypeMask[0];
	
    m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].startHour = m_prd2StartHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].startMinute = m_prd2StartMinute;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].endHour = m_prd2EndHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].endMinute = m_prd2EndMinute;
	if (m_ctlDTT2.GetCheck())
	{
		pTypeMask[1] += 4;
	}
	if (m_ctlALM2.GetCheck())
	{
		pTypeMask[1] += 2;
	}
	if (m_ctlPRD2.GetCheck())
	{
		pTypeMask[1] += 1;
	}
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nWeek][1] = pTypeMask[1];
	
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].startHour = m_prd3StartHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].startMinute = m_prd3StartMinute;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].endHour = m_prd3EndHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].endMinute = m_prd3EndMinute;
	if (m_ctlDTT3.GetCheck())
	{
		pTypeMask[2] += 4;
	}
	if (m_ctlALM3.GetCheck())
	{
		pTypeMask[2] += 2;
	}
	if (m_ctlPRD3.GetCheck())
	{
		pTypeMask[2] += 1;
	}
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nWeek][2] = pTypeMask[2];
	
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].startHour = m_prd4StartHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].startMinute = m_prd4StartMinute;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].endHour = m_prd4EndHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].endMinute = m_prd4EndMinute;
	if (m_ctlDTT4.GetCheck())
	{
		pTypeMask[3] += 4;
	}
	if (m_ctlALM4.GetCheck())
	{
		pTypeMask[3] += 2;
	}
	if (m_ctlPRD4.GetCheck())
	{
		pTypeMask[3] += 1;
	}
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nWeek][3] = pTypeMask[3];
	
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][4].startHour = m_prd5StartHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][4].startMinute = m_prd5StartMinute;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][4].endHour =m_prd5EndHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][4].endMinute = m_prd5EndMinute;
	if (m_ctlDTT5.GetCheck())
	{
		pTypeMask[4] += 4;
	}
	if (m_ctlALM5.GetCheck())
	{
		pTypeMask[4] += 2;
	}
	if (m_ctlPRD5.GetCheck())
	{
		pTypeMask[4] += 1;
	}
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nWeek][4] = pTypeMask[4];
	
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][5].startHour = m_prd6StartHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][5].startMinute = m_prd6StartMinute;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][5].endHour = m_prd6EndHour;
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][5].endMinute = m_prd6EndMinute;
	if (m_ctlDTT6.GetCheck())
	{
		pTypeMask[5] += 4;
	}
	if (m_ctlALM6.GetCheck())
	{
		pTypeMask[5] += 2;
	}
	if (m_ctlPRD6.GetCheck())
	{
		pTypeMask[5] += 1;
	}
	m_RecordCfg.vRecordConfigAll[m_nLastChannel].typeMask[nWeek][5] = pTypeMask[5];
}

void CConfigRecord::ShowTime(BOOL bRet)
{
	m_ctlRecordWeek.EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD1_S_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD1_S_MINUTE)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD1_E_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD1_E_MINUTE)->EnableWindow(bRet);
	m_ctlPRD1.EnableWindow(bRet);
	m_ctlDTT1.EnableWindow(bRet);
	m_ctlALM1.EnableWindow(bRet);
	
	GetDlgItem(IDC_EDIT_PRD2_S_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD2_S_MINUTE)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD2_E_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD2_E_MINUTE)->EnableWindow(bRet);
	m_ctlPRD2.EnableWindow(bRet);
	m_ctlDTT2.EnableWindow(bRet);
	m_ctlALM2.EnableWindow(bRet);
	
	GetDlgItem(IDC_EDIT_PRD3_S_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD3_S_MINUTE)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD3_E_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD3_E_MINUTE)->EnableWindow(bRet);
	m_ctlPRD3.EnableWindow(bRet);
	m_ctlDTT3.EnableWindow(bRet);
	m_ctlALM3.EnableWindow(bRet);
	
	GetDlgItem(IDC_EDIT_PRD4_S_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD4_S_MINUTE)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD4_E_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD4_E_MINUTE)->EnableWindow(bRet);
	m_ctlPRD4.EnableWindow(bRet);
	m_ctlDTT4.EnableWindow(bRet);
	m_ctlALM4.EnableWindow(bRet);
	
	GetDlgItem(IDC_EDIT_PRD5_S_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD5_S_MINUTE)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD5_E_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD5_E_MINUTE)->EnableWindow(bRet);
	m_ctlPRD5.EnableWindow(bRet);
	m_ctlDTT5.EnableWindow(bRet);
	m_ctlALM5.EnableWindow(bRet);
	
	GetDlgItem(IDC_EDIT_PRD6_S_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD6_S_MINUTE)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD6_E_HOUR)->EnableWindow(bRet);
	GetDlgItem(IDC_EDIT_PRD6_E_MINUTE)->EnableWindow(bRet);
	m_ctlPRD6.EnableWindow(bRet);
	m_ctlDTT6.EnableWindow(bRet);
	m_ctlALM6.EnableWindow(bRet);
}

void CConfigRecord::OnRadio0() 
{
	// TODO: Add your control notification handler code here
	ShowTime(TRUE);
}

void CConfigRecord::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	ShowTime(FALSE);
}

void CConfigRecord::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	ShowTime(FALSE);
}

void CConfigRecord::SaveWeekAll()
{
	int nIndex = m_ctlRecordWeek.GetCurSel();
	if (nIndex == 7)
	{
		for (int i = 0;i<7;i++)
		{
			SaveWeekInfo(i);
		}
	}
	else
	{
		SaveWeekInfo(nIndex);
	}
}

void CConfigRecord::SaveRecordAll()
{
	int nIndex = m_ctlChannel.GetCurSel();
	if (nIndex == m_nChannelNum)
	{
		for (int i = 0;i<m_nChannelNum;i++)
		{
			SaveRecordInfo(i);
		}
	}else
	{
		SaveRecordInfo(nIndex);
	}
}

void CConfigRecord::OnChangeEdit(UINT nID) 
{

// 	if (!m_bCheckEdit)
// 	{
// 		return;
// 	}
// 	
// 	UpdateData();
// 	
// 	int nNum = nID - IDC_EDIT_PRD1_S_HOUR;
// 	int nSect = nNum / 4;
// 	
// 	int nWitch = nNum % 4;
// 	
// 	
// 	BOOL bChange = FALSE;
// 
// 	int nSectIndex = IDC_EDIT_PRD1_S_HOUR + nSect * 4;
// 	
// 	int StartHour = GetDlgItemInt(nSectIndex);
// 	int StartMin = GetDlgItemInt(nSectIndex + 1);
// 	int EndHour = GetDlgItemInt(nSectIndex + 2);
// 	int EndMin = GetDlgItemInt(nSectIndex + 3);
// 	
// 	if ( 0 == nWitch || 2 == nWitch )
// 	{
// 		if ( 0 == nWitch )
// 		{
// 			if ( StartHour < 0)
// 			{
// 				StartHour = 0;
// 				bChange = TRUE;
// 			}
// 			else if ( StartHour > 24)
// 			{
// 				StartHour = 24;
// 				bChange = TRUE;
// 			}
// 			
// 		}
// 		else
// 		{
// 			if ( EndHour < 0 )
// 			{
// 				EndHour = 0;
// 				bChange = TRUE;
// 			}
// 			else if ( EndHour > 24 )
// 			{
// 				EndHour = 24;
// 				bChange = TRUE;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if ( 1 == nWitch )
// 		{
// 			if ( StartMin < 0)
// 			{
// 				StartMin = 0;
// 				bChange = TRUE;
// 			}
// 			else if ( StartMin > 59)
// 			{
// 				StartMin = 59;
// 				bChange = TRUE;
// 			}
// 			
// 		}
// 		else
// 		{			
// 			if ( EndMin < 0 )
// 			{
// 				EndMin = 0;
// 				bChange = TRUE;
// 			}
// 			else if ( EndMin > 59 )
// 			{
// 				EndMin = 59;
// 				bChange = TRUE;
// 			}
// 			
// 		}
// 	}
// 	
// 	if (StartHour == 24)
// 	{
// 		StartMin = 0;
// 		bChange = TRUE;
// 	}	
// 	
// 	if (EndHour == 24)
// 	{
// 		EndMin = 0;
// 		bChange = TRUE;
// 	}	
// 	
// 	if (bChange)
// 	{
// 		m_bCheckEdit = FALSE;
// 		SetEditText(nSectIndex, StartHour, "02");
// 		SetEditText(nSectIndex + 1, StartMin, "02");
// 		SetEditText(nSectIndex + 2, EndHour, "02");
// 		SetEditText(nSectIndex + 3, EndMin, "02");
// 		//((CEdit *)GetDlgItem(nID))->SetSel(0,2);
// 		((CEdit *)GetDlgItem(nID))->SetFocus();
// 	}
// 	m_bCheckEdit = TRUE;
}

void CConfigRecord::OnKillfocusEdit(UINT nID) 
{
	// TODO: Add your control notification handler code here
	if (!m_bCheckEdit)
	{
		return;
	}
	
	UpdateData();
	
	int nNum = nID - IDC_EDIT_PRD1_S_HOUR;
	int nSect = nNum / 4;
	int nWitch = nNum % 4;
	
	BOOL bChange = FALSE;
	
	int nSectIndex = IDC_EDIT_PRD1_S_HOUR + nSect * 4;
	
	int StartHour = GetDlgItemInt(nSectIndex);
	int StartMin = GetDlgItemInt(nSectIndex + 1);
	int EndHour = GetDlgItemInt(nSectIndex + 2);
	int EndMin = GetDlgItemInt(nSectIndex + 3);

	if ( 0 == nWitch || 2 == nWitch )
	{
		if ( EndHour < StartHour )
		{
			EndHour = StartHour;
			bChange = TRUE;
		}
	}
	else
	{
		if ( StartHour == EndHour && EndMin < StartMin )
		{
			EndMin = StartMin;
			bChange = TRUE;
		}
	}
	
	if (bChange)
	{
		m_bCheckEdit = FALSE;
		SetEditText(nSectIndex, StartHour, "02");
		SetEditText(nSectIndex + 1, StartMin, "02");
		SetEditText(nSectIndex + 2, EndHour, "02");
		SetEditText(nSectIndex + 3, EndMin, "02");
		//((CEdit *)GetDlgItem(nID))->SetSel(0,2);
		((CEdit *)GetDlgItem(nID))->SetFocus();
	}
	m_bCheckEdit = TRUE;
}

void CConfigRecord::SetEditText(UINT nID, CString strText)
{
	CWnd *pWnd = GetDlgItem(nID);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->SetWindowText(strText);
	}
}

void CConfigRecord::SetEditText(UINT nID, double fText, CString strFormat)
{
	CString strText;
	strText.Format("%" + strFormat + "f", fText);
	SetEditText(nID, strText);
}

void CConfigRecord::SetEditText(UINT nID, unsigned int nText, CString strFormat )
{
	CString strText;
	strText.Format("%" + strFormat + "d", nText);
	SetEditText(nID, strText);
}

void CConfigRecord::SetEditText(UINT nID, int nText, CString strFormat)
{
	CString strText;
	strText.Format("%" + strFormat + "d", nText);
	SetEditText(nID, strText);
}
