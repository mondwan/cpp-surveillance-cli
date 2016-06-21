// DlgChannelStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DlgChannelStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChannelStatus dialog


CDlgChannelStatus::CDlgChannelStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChannelStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChannelStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgChannelStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChannelStatus)
	DDX_Control(pDX, IDC_LIST_STATUS, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChannelStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgChannelStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChannelStatus message handlers

BOOL CDlgChannelStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	//list
	m_ctrlList.InsertColumn(0, _CS(_T("DigitalChannel.Channel")), LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(1, _CS(_T("DigitalChannel.MaxResolution")), LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(2, _CS(_T("DigitalChannel.CurResolution")), LVCFMT_LEFT,80);
	m_ctrlList.InsertColumn(3, _CS(_T("DigitalChannel.ConnStatus")), LVCFMT_LEFT, 80);
	m_ctrlList.SetExtendedStyle( m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChannelStatus::InitDlgInfo(SDK_NetDecorderChnStatusAll *pNetChnStatusConfigAll)
{
	memcpy(&m_ChnStatusAll,pNetChnStatusConfigAll,sizeof(SDK_NetDecorderChnStatusAll));
    StructToWinData();
}

bool CDlgChannelStatus::StructToWinData()
{
	int nIndex = 0;
	m_ctrlList.DeleteAllItems();
	while ( nIndex < MAX_HVR_CHNCAP_CHN && strcmp(m_ChnStatusAll.ChnStatusAll[nIndex].ChnName, "")  != 0 )
	{
		int j = 1;
		CString strTemp = _T("");
		CString strUnKnown = _CS(_T("DigitalChannel.UnKnown"));
		strTemp =  m_ChnStatusAll.ChnStatusAll[nIndex].ChnName;
		m_ctrlList.InsertItem(nIndex, strTemp);
		
		if ( strcmp( m_ChnStatusAll.ChnStatusAll[nIndex].pMaxResName , "Unknown") == 0 )
		{
			strTemp = strUnKnown;
		}
		else
		{
			strTemp = m_ChnStatusAll.ChnStatusAll[nIndex].pMaxResName;
		}
		m_ctrlList.SetItemText(nIndex, j++, strTemp);
		
		if ( strcmp( m_ChnStatusAll.ChnStatusAll[nIndex].pCurResName, "Unknown") == 0)
		{
			strTemp = strUnKnown;
		}
		else
		{
			strTemp = m_ChnStatusAll.ChnStatusAll[nIndex].pCurResName;
		}
		m_ctrlList.SetItemText(nIndex, j++, strTemp);
		
		strTemp = _T("DigitalChannel");
		CString strStatus;
		strStatus.Format(_T("%s.%s"), strTemp.GetBuffer(0),  m_ChnStatusAll.ChnStatusAll[nIndex].pStatus);
		m_ctrlList.SetItemText(nIndex, j++, _CS(strStatus));
		nIndex ++;
	}
	return true;

}

void CDlgChannelStatus::ClearAll()
{
	m_ctrlList.DeleteAllItems();
}
