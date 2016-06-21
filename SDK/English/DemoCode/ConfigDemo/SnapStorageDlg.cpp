// SnapStorageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "SnapStorageDlg.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnapStorageDlg dialog


CSnapStorageDlg::CSnapStorageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnapStorageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSnapStorageDlg)
	m_prd1StartHour = 0;
	m_prd2StartHour = 0;
	m_prd3StartHour = 0;
	m_prd4StartHour = 0;
	m_prd1StartMinute = 0;
	m_prd2StartMinute = 0;
	m_prd3StartMinute = 0;
	m_prd4StartMinute = 0;
	m_prd4EndHour = 0;
	m_prd4EndMinute = 0;
	m_prd1EndHour = 0;
	m_prd2EndHour = 0;
	m_prd3EndHour = 0;
	m_prd1EndMinute = 0;
	m_prd2EndMinute = 0;
	m_prd3EndMinute = 0;

	//}}AFX_DATA_INIT
	memset(m_pTimeSectValue,0,sizeof(m_pTimeSectValue));
}


void CSnapStorageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnapStorageDlg)
	DDX_Control(pDX, IDC_CHECK_ALM4, m_ctlALM4);
	DDX_Control(pDX, IDC_CHECK_ALM3, m_ctlALM3);
	DDX_Control(pDX, IDC_CHECK_ALM2, m_ctlALM2);
	DDX_Control(pDX, IDC_CHECK_ALM1, m_ctlALM1);
	DDX_Control(pDX, IDC_CHECK_DTT5, m_ctlDTT4);
	DDX_Control(pDX, IDC_CHECK_DTT3, m_ctlDTT3);
	DDX_Control(pDX, IDC_CHECK_DTT2, m_ctlDTT2);
	DDX_Control(pDX, IDC_CHECK_DTT1, m_ctlDTT1);
	DDX_Control(pDX, IDC_CHECK_PRD5, m_ctlPRD4);
	DDX_Control(pDX, IDC_CHECK_PRD4, m_ctlPRD3);
	DDX_Control(pDX, IDC_CHECK_PRD2, m_ctlPRD2);
	DDX_Control(pDX, IDC_CHECK_PRD1, m_ctlPRD1);
	DDX_Control(pDX, IDC_COMBO_WEEK, m_ctlRecordWeek);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctlChannel);
	DDX_Text(pDX, IDC_EDIT_PRD1_S_HOUR, m_prd1StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD2_S_HOUR, m_prd2StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD3_S_HOUR, m_prd3StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD4_S_HOUR, m_prd4StartHour);
	DDX_Text(pDX, IDC_EDIT_PRD1_S_MINUTE, m_prd1StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD2_S_MINUTE, m_prd2StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD3_S_MINUTE, m_prd3StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD4_S_MINUTE, m_prd4StartMinute);
	DDX_Text(pDX, IDC_EDIT_PRD4_E_HOUR, m_prd4EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD4_E_MINUTE, m_prd4EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD1_E_HOUR, m_prd1EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD2_E_HOUR, m_prd2EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD3_E_HOUR, m_prd3EndHour);
	DDX_Text(pDX, IDC_EDIT_PRD1_E_MINUTE, m_prd1EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD2_E_MINUTE, m_prd2EndMinute);
	DDX_Text(pDX, IDC_EDIT_PRD3_E_MINUTE, m_prd3EndMinute);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnapStorageDlg, CDialog)
	//{{AFX_MSG_MAP(CSnapStorageDlg)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_RADIO0, OnRadio0)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_CBN_EDITCHANGE(IDC_COMBO_WEEK, OnEditchangeComboWeek)
	ON_CBN_EDITCHANGE(IDC_COMBO_CHANNEL, OnEditchangeComboChannel)
	ON_BN_CLICKED(IDC_BTB_UpDate, OnBTBUpDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnapStorageDlg message handlers

BOOL CSnapStorageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);

	//初始化星期下拉框
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
	CleanAll();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSnapStorageDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CSnapStorageDlg::InitDlgInfo(SDK_SnapshotConfigAll *precordSet,int nChannelNum)
{
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
		m_SnapCfg.vSnapshotConfigAll[i] = precordSet->vSnapshotConfigAll[i];
	}
	nIndex = m_ctlChannel.AddString(_CS("OneClick.All"));
	m_ctlChannel.SetItemData(nIndex,nChannelNum);
	
	m_ctlChannel.SetCurSel(0);
	
	ShowWindow(0);
	
	
	m_nLastWeek=m_ctlRecordWeek.GetCurSel();
	for(int j=0;j<4;j++)
	{
		SDK_TIMESECTION periodInfo = m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[m_nLastWeek][j];
		ShowPeriodInfo(&periodInfo,j+1,m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[m_nLastWeek][j]);
	}
	
}

void CSnapStorageDlg::ShowWindow(int nChannel)
{
// 	m_ctlRedundancy.SetCheck(m_SnapCfg.vSnapshotConfigAll[nChannel].bRedundancy);
 	SetDlgItemInt(IDC_EDIT_LENGTH,m_SnapCfg.vSnapshotConfigAll[nChannel].iPreSnap);
// 	SetDlgItemInt(IDC_EDIT_RECORDLEN,m_SnapCfg.vSnapshotConfigAll[nChannel].iPacketLength);
	if ((m_SnapCfg.vSnapshotConfigAll[nChannel].iSnapMode == 1) || (m_SnapCfg.vSnapshotConfigAll[nChannel].iSnapMode == 0))
	{
		if (m_SnapCfg.vSnapshotConfigAll[nChannel].iSnapMode == 1)
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
	CTime time = CTime::GetCurrentTime();
	m_ctlRecordWeek.SetCurSel(time.GetDayOfWeek()-1);
	m_nLastWeek = 0;
	UpdateData(TRUE);
}

void CSnapStorageDlg::ShowPeriodInfo(SDK_TIMESECTION *pTime,int nNum ,UINT typeMask)
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
	default:
		break;
	}
	UpdateData(FALSE);
}

void CSnapStorageDlg::ShowTime(BOOL bRet)
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
	
}

void CSnapStorageDlg::OnRadio0() 
{
	// TODO: Add your control notification handler code here
	ShowTime(TRUE);
}

void CSnapStorageDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	ShowTime(FALSE);
}

void CSnapStorageDlg::OnRadio2() 
{
		// TODO: Add your control notification handler code here
	ShowTime(FALSE);
}

void CSnapStorageDlg::CleanAll()
{
	m_ctlRecordWeek.SetCurSel(-1);
	m_ctlChannel.SetCurSel(-1);
//	SetDlgItemText(IDC_EDIT_PRERECLEN, "");
	//SetDlgItemText(IDC_EDIT_RECORDLEN, "");
//	m_ctlRedundancy.SetCheck(0);
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
	for(;i<4;i++)
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

void CSnapStorageDlg::OnEditchangeComboWeek() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlRecordWeek.GetCurSel();
	if (nIndex == 7)
	{
		for(int i=0;i<6;i++)
		{
			SDK_TIMESECTION periodInfo = m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[0][i];
			ShowPeriodInfo(&periodInfo,i+1,m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[0][i]);
		}
		m_nLastWeek = 7;
	}
	else
	{
		if (m_nLastWeek == 7)
		{
			for(int i=0;i<6;i++)
			{
				SDK_TIMESECTION periodInfo = m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nIndex][i];
				ShowPeriodInfo(&periodInfo,i+1,m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[nIndex][i]);
			}
			m_nLastWeek = nIndex;
		}
		else if (nIndex != m_nLastWeek)
		{
			SaveWeekInfo(m_nLastWeek); 
			for(int i=0;i<6;i++)
			{
				SDK_TIMESECTION periodInfo = m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nIndex][i];
				ShowPeriodInfo(&periodInfo,i+1,m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[nIndex][i]);
			}
			m_nLastWeek = nIndex;
		}
	}
}

void CSnapStorageDlg::SaveWeekInfo(int nWeek)
{
	UpdateData(TRUE);
	UINT pTypeMask[4] = {0};
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].startHour = m_prd1StartHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].startMinute = m_prd1StartMinute;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].endHour = m_prd1EndHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][0].endMinute = m_prd1EndMinute;
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
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[nWeek][0] = pTypeMask[0];
	
    m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].startHour = m_prd2StartHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].startMinute = m_prd2StartMinute;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].endHour = m_prd2EndHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][1].endMinute = m_prd2EndMinute;
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
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[nWeek][1] = pTypeMask[1];
	
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].startHour = m_prd3StartHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].startMinute = m_prd3StartMinute;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].endHour = m_prd3EndHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][2].endMinute = m_prd3EndMinute;
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
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[nWeek][2] = pTypeMask[2];
	
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].startHour = m_prd4StartHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].startMinute = m_prd4StartMinute;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].endHour = m_prd4EndHour;
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].wcWorkSheet.tsSchedule[nWeek][3].endMinute = m_prd4EndMinute;
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
	m_SnapCfg.vSnapshotConfigAll[m_nLastChannel].typeMask[nWeek][3] = pTypeMask[3];
	
}

void CSnapStorageDlg::SaveSnapInfo(int nIndex)
{
	int   iRadioButton; 
    iRadioButton=GetCheckedRadioButton(IDC_RADIO0,IDC_RADIO2);
	if(iRadioButton == IDC_RADIO0)
	{
		m_SnapCfg.vSnapshotConfigAll[nIndex].iSnapMode = 2;
	}else if (iRadioButton == IDC_RADIO1)
	{
		m_SnapCfg.vSnapshotConfigAll[nIndex].iSnapMode = 1;
	}else if (iRadioButton == IDC_RADIO2)
	{
		m_SnapCfg.vSnapshotConfigAll[nIndex].iSnapMode = 0;
	}

	m_SnapCfg.vSnapshotConfigAll[nIndex].iPreSnap = GetDlgItemInt(IDC_EDIT_LENGTH);

	SaveWeekAll();
}

void CSnapStorageDlg::SaveWeekAll()
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

void CSnapStorageDlg::SaveRecordAll()
{
	int nIndex = m_ctlChannel.GetCurSel();
	if (nIndex == m_nChannelNum)
	{
		for (int i = 0;i<m_nChannelNum;i++)
		{
			SaveSnapInfo(i);
		}
	}else
	{
		SaveSnapInfo(nIndex);
	}
}

void CSnapStorageDlg::OnEditchangeComboChannel() 
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
				SaveSnapInfo(m_nLastChannel);
				m_nLastChannel = nIndex;
				ShowWindow(nIndex);
			}
		}
	}
}

void CSnapStorageDlg::OnOK() 
{
	// TODO: Add extra validation here
	if ( -1 != m_ctlChannel.GetCurSel())
	{
		SaveRecordAll();
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetSnapStorageDlg(&m_SnapCfg);
	}
	//CDialog::OnOK();
}

void CSnapStorageDlg::OnBTBUpDate() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetSnapStorageDlg();
}
