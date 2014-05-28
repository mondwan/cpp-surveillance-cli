// AlarmOuput.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "AlarmOuput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmOuput dialog


CAlarmOuput::CAlarmOuput(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmOuput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmOuput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(m_pBtnsAlarmOutAuto, 0, sizeof(m_pBtnsAlarmOutAuto));
	memset(m_pBtnsAlarmOutMan, 0, sizeof(m_pBtnsAlarmOutMan));
	memset(m_pBtnsAlarmOutClose, 0, sizeof(m_pBtnsAlarmOutClose));
	memset(m_pBtnsAlarmOutState, 0, sizeof(m_pBtnsAlarmOutState));
	memset(m_pStaticAlarm, 0, sizeof(m_pStaticAlarm));

	memset(&m_AlarmOutAll, 0, sizeof(m_AlarmOutAll));
	m_nAlarmOutNum = 0;
}


void CAlarmOuput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmOuput)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmOuput, CDialog)
	//{{AFX_MSG_MAP(CAlarmOuput)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioAuto)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioMan)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmOuput message handlers

BOOL CAlarmOuput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmOuput::OnRadioAuto() 
{
	// TODO: Add your control notification handler code here
	int nVideoOutChannel = m_nAlarmOutNum;
	for (int i = 0; i < nVideoOutChannel; i++)
	{
		m_pBtnsAlarmOutAuto[i]->SetCheck(1);
		m_pBtnsAlarmOutMan[i]->SetCheck(0);
		m_pBtnsAlarmOutClose[i]->SetCheck(0);
	}
}

void CAlarmOuput::OnRadioMan() 
{
	// TODO: Add your control notification handler code here
	int nVideoOutChannel = m_nAlarmOutNum;
	for (int i = 0; i < nVideoOutChannel; i++)
	{
		m_pBtnsAlarmOutAuto[i]->SetCheck(0);
		m_pBtnsAlarmOutMan[i]->SetCheck(1);
		m_pBtnsAlarmOutClose[i]->SetCheck(0);
	}
}

void CAlarmOuput::OnRadioClose() 
{
	// TODO: Add your control notification handler code here
	int nVideoOutChannel = m_nAlarmOutNum;
	for (int i = 0; i < nVideoOutChannel; i++)
	{
		m_pBtnsAlarmOutAuto[i]->SetCheck(0);
		m_pBtnsAlarmOutMan[i]->SetCheck(0);
		m_pBtnsAlarmOutClose[i]->SetCheck(1);
	}
}


BOOL CAlarmOuput::InitWndShow()
{
	Clear();
	
	int nVideoOutChannel = m_nAlarmOutNum;
	CRect rcAll, rcAuto, rcMan, rcClose, rcStatus;
	GetDlgItem(IDC_STATIC_ALL)->GetWindowRect(rcAll);
	ScreenToClient(rcAll);
	GetDlgItem(IDC_RADIO1)->GetWindowRect(rcAuto);
	ScreenToClient(rcAuto);
	CButton *pB = (CButton *)GetDlgItem(IDC_RADIO1);
	pB->SetCheck(0);
	GetDlgItem(IDC_RADIO2)->GetWindowRect(rcMan);
	ScreenToClient(rcMan);
	pB = (CButton *)GetDlgItem(IDC_RADIO2);
	pB->SetCheck(0);
	GetDlgItem(IDC_RADIO3)->GetWindowRect(rcClose);
	ScreenToClient(rcClose);
	pB = (CButton *)GetDlgItem(IDC_RADIO3);
	pB->SetCheck(0);
	rcStatus = rcClose;
	rcStatus.top = rcClose.bottom + 10;
	rcStatus.bottom = rcStatus.top + 20;
	int i = 0;
	
	for (i = 0; i< nVideoOutChannel; i++)
	{
		CString strText;
		strText.Format("%d", i + 1);
		
		rcAll.left = rcAll.right;
		rcAll.right = rcAll.left + 20;
		rcAll.bottom += 2;
		
		m_pStaticAlarm[i] = new CStatic();
		m_pStaticAlarm[i]->Create(strText, WS_CHILD | WS_VISIBLE | SS_CENTER, rcAll, this);
		
		rcAuto.left = rcAuto.right;
		rcAuto.right = rcAuto.left + 20;
		m_pBtnsAlarmOutAuto[i] = new CButton();
		m_pBtnsAlarmOutAuto[i]->Create("", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, rcAuto, this, IDC_BTN_ALARMOUT_SET + i * NET_MAX_CHANNUM);
		
		rcMan.left = rcMan.right;
		rcMan.right = rcMan.left + 20;
		m_pBtnsAlarmOutMan[i] = new CButton();
		m_pBtnsAlarmOutMan[i]->Create("", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rcMan, this, IDC_BTN_ALARMOUT_SET + i * NET_MAX_CHANNUM + 1);
		
		rcClose.left = rcClose.right;
		rcClose.right = rcClose.left + 20;
		m_pBtnsAlarmOutClose[i] = new CButton();
		m_pBtnsAlarmOutClose[i]->Create("", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rcClose, this, IDC_BTN_ALARMOUT_SET + i * NET_MAX_CHANNUM + 2);
		
		rcStatus.left = rcStatus.right;
		rcStatus.right = rcStatus.left + 20;
		m_pBtnsAlarmOutState[i] = new CButton();
		m_pBtnsAlarmOutState[i]->Create("", BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE, rcStatus, this, IDC_BTN_ALARMOUT_STATUS + i);
		m_pBtnsAlarmOutState[i]->EnableWindow(FALSE);
	}
	
	return TRUE;
}

void CAlarmOuput::Clear()
{
	//删除创建的选择CHECK BOX
	int nChanneCount = NET_MAX_CHANNUM;
	
	int i = 0;
	for ( i = 0; i < nChanneCount; ++i )
	{
		if (m_pBtnsAlarmOutAuto[i])
		{
			delete m_pBtnsAlarmOutAuto[i];
			m_pBtnsAlarmOutAuto[i] = NULL;
		}
		
		if (m_pBtnsAlarmOutMan[i])
		{
			delete m_pBtnsAlarmOutMan[i];
			m_pBtnsAlarmOutMan[i] = NULL;
		}
		
		if (m_pBtnsAlarmOutClose[i])
		{
			delete m_pBtnsAlarmOutClose[i];
			m_pBtnsAlarmOutClose[i] = NULL;
		}
		if (m_pBtnsAlarmOutState[i])
		{
			delete m_pBtnsAlarmOutState[i];
			m_pBtnsAlarmOutState[i] = NULL;
		}
		if (m_pStaticAlarm[i])
		{
			delete m_pStaticAlarm[i];
			m_pStaticAlarm[i] = NULL;
		}
	}
}

void CAlarmOuput::InitDlgInfo(SDK_AlarmOutConfigAll* pAlarmOutAll, int nAlarmOutNum)
{
	if ( pAlarmOutAll )
	{
		memcpy(&m_AlarmOutAll, pAlarmOutAll, sizeof(SDK_AlarmOutConfigAll));
	}

	m_nAlarmOutNum = nAlarmOutNum;

	InitWndShow();

	for (int i = 0; i < nAlarmOutNum; i++)
	{
		if (0 == m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutType)
		{
			m_pBtnsAlarmOutAuto[i]->SetCheck(1);
			m_pBtnsAlarmOutMan[i]->SetCheck(0);
			m_pBtnsAlarmOutClose[i]->SetCheck(0);
		}
		else if (1 == m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutType)
		{
			m_pBtnsAlarmOutAuto[i]->SetCheck(0);
			m_pBtnsAlarmOutMan[i]->SetCheck(1);
			m_pBtnsAlarmOutClose[i]->SetCheck(0);
		}
		else if (2 == m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutType)
		{
			m_pBtnsAlarmOutAuto[i]->SetCheck(0);
			m_pBtnsAlarmOutMan[i]->SetCheck(0);
			m_pBtnsAlarmOutClose[i]->SetCheck(1);
		}
		
		m_pBtnsAlarmOutState[i]->SetCheck(m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutStatus);
	}
}

BOOL CAlarmOuput::SaveAlarmOutputInfo()
{
	int nVideoOutChannel = m_nAlarmOutNum;
	for (int i = 0; i < nVideoOutChannel; i++)
	{
		m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutType = 0;
		m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutStatus = 0;
		if (m_pBtnsAlarmOutMan[i]->GetCheck())
		{
			m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutType = 1;
		}
		else if (m_pBtnsAlarmOutClose[i]->GetCheck())
		{
			m_AlarmOutAll.vAlarmOutConfigAll[i].nAlarmOutType = 2;
		}
	}
	CButton *pB = (CButton *)GetDlgItem(IDC_RADIO1);
	pB->SetCheck(0);
	pB = (CButton *)GetDlgItem(IDC_RADIO2);
	pB->SetCheck(0);
	pB = (CButton *)GetDlgItem(IDC_RADIO3);
	pB->SetCheck(0);

	return TRUE;
}
