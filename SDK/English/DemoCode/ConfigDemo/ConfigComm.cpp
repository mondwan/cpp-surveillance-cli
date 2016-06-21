// ConfigComm.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigComm.h"

#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigComm dialog


CConfigComm::CConfigComm(CWnd* pParent /*=NULL*/)
: CDialog(CConfigComm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigComm)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigComm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigComm)
	DDX_Control(pDX, IDC_COMBO_FUNCTION232, m_ctlCommFun);
	DDX_Control(pDX, IDC_COMBO_DATABIT232, m_ctlCommData);
	DDX_Control(pDX, IDC_COMBO_STOPBIT232, m_ctlCommStopBit);
	DDX_Control(pDX, IDC_COMBO_BAUD232, m_ctlCommBaud);
	DDX_Control(pDX, IDC_COMBO_PARITY232, m_ctlCommParity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigComm, CDialog)
//{{AFX_MSG_MAP(CConfigComm)
ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigComm message handlers

void CConfigComm::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	SaveComm();
	if (-1 != m_ctlCommFun.GetCurSel())
	{
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetCommConfigInfo(&m_CommConfigAll);
	}
}

BOOL CConfigComm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	InitCombo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigComm::InitCombo()
{
	m_ctlCommData.ResetContent();
	m_ctlCommData.AddString("5");
	m_ctlCommData.AddString("6");
	m_ctlCommData.AddString("7");
	m_ctlCommData.AddString("8");
	
	m_ctlCommStopBit.ResetContent();
	m_ctlCommStopBit.AddString(_T("1"));
	m_ctlCommStopBit.AddString(_T("2"));
	
	m_ctlCommBaud.ResetContent();
	m_ctlCommBaud.AddString("1200");
	m_ctlCommBaud.AddString("2400");
	m_ctlCommBaud.AddString("4800");
	m_ctlCommBaud.AddString("9600");
	m_ctlCommBaud.AddString("19200");
	m_ctlCommBaud.AddString("38400");
	m_ctlCommBaud.AddString("57600");
	m_ctlCommBaud.AddString("115200");
	
	m_ctlCommParity.ResetContent();
	m_ctlCommParity.AddString(_CS("ConfigPtz.None"));
	m_ctlCommParity.AddString(_CS("ConfigPtz.Odd"));
	m_ctlCommParity.AddString(_CS("ConfigPtz.Even"));
	m_ctlCommParity.AddString(_CS("ConfigPtz.Mark"));
	m_ctlCommParity.AddString(_CS("ConfigPtz.Space"));
}

void CConfigComm::InitDlgInfo(SDK_CommConfigAll *pCommCfg,SDK_COMMFUNC *pCommFunc)
{
	int nIndex = 0;
	CString str;
	
	m_ctlCommFun.ResetContent();
	for (int i = 0;i<pCommFunc->nProNum;i++)
	{
		nIndex = m_ctlCommFun.AddString(_CS(pCommFunc->vCommProtocol[i]));
		m_ctlCommFun.SetItemData(nIndex,(long)pCommFunc->vCommProtocol[i]);	
	}
	
	m_ctlCommFun.SetCurSel(0);
	
	memcpy(&m_CommConfigAll,pCommCfg,sizeof(SDK_CommConfigAll));
	ShowComm();
}

void CConfigComm::CleanAll()
{
	m_ctlCommBaud.SetCurSel(-1);
	m_ctlCommParity.SetCurSel(-1);
	m_ctlCommData.SetCurSel(-1);
	m_ctlCommStopBit.SetCurSel(-1);
	m_ctlCommFun.ResetContent();
}

void CConfigComm::SaveComm()
{
	CString str;
	m_ctlCommFun.GetWindowText(str);
	strcpy(m_CommConfigAll.vCommConfig[0].iProtocolName,str.GetBuffer(0));
	m_ctlCommBaud.GetWindowText(str);
	m_CommConfigAll.vCommConfig[0].aCommAttri.iBaudRate = atoi(str.GetBuffer(0));
	m_ctlCommData.GetWindowText(str);
	m_CommConfigAll.vCommConfig[0].aCommAttri.iDataBits = atoi(str.GetBuffer(0));
	m_ctlCommStopBit.GetWindowText(str);
	m_CommConfigAll.vCommConfig[0].aCommAttri.iStopBits = atoi(str.GetBuffer(0));
	m_CommConfigAll.vCommConfig[0].aCommAttri.iParity = m_ctlCommParity.GetCurSel();
}

void CConfigComm::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetCommConfigInfo();
}

void CConfigComm::ShowComm()
{
	CString str;
	SDK_CONFIG_COMM_X *pComm = &m_CommConfigAll.vCommConfig[0];
	if (pComm)
	{
		m_ctlCommFun.SelectString(-1,pComm->iProtocolName);
		str.Format(_T("%d"),pComm->aCommAttri.iDataBits);
		m_ctlCommData.SelectString(-1,str);
		
		str.Format(_T("%d"),pComm->aCommAttri.iBaudRate);
		m_ctlCommBaud.SelectString(-1,str);
		
		str.Format(_T("%d"),pComm->aCommAttri.iStopBits);
		m_ctlCommStopBit.SelectString(-1,str);
		
		m_ctlCommParity.SetCurSel(pComm->aCommAttri.iParity);
	}
}
