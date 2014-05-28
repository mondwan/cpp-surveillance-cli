// DlgChannelMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DlgChannelMode.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChannelMode dialog


CDlgChannelMode::CDlgChannelMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChannelMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChannelMode)
		// NOTE: the ClassWizard will add member initialization here

	//}}AFX_DATA_INIT
	m_nCheckItem = -1;
	m_bSetCheck = true;
}


void CDlgChannelMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChannelMode)
	DDX_Control(pDX, IDC_LIST_CHANNELMODE, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChannelMode, CDialog)
	//{{AFX_MSG_MAP(CDlgChannelMode)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CHANNELMODE, OnItemchangedListChannelmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChannelMode message handlers

BOOL CDlgChannelMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here

	//list
	m_ctrlList.InsertColumn(0, _CS(_T("")), LVCFMT_LEFT, 40);
	m_ctrlList.InsertColumn(1, _CS(_T("1080P")), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(2, _CS(_T("720P")), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(3, _CS(_T("960H")), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(4, _CS(_T("D1")),LVCFMT_LEFT,50);
	
	m_ctrlList.InsertColumn(5, _CS(_T("")),LVCFMT_LEFT,13);
	
	m_ctrlList.InsertColumn(6, _CS(_T("1080P")), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(7, _CS(_T("720P")), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(8, _CS(_T("960H")), LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(9, _CS(_T("D1")),LVCFMT_LEFT,50);
	m_ctrlList.SetExtendedStyle( m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChannelMode::InitDlgInfo(SDK_NetDecorderChnModeConfig *pNetChnModeConfig)
{

	memcpy(&m_ChnModeCfg,pNetChnModeConfig,sizeof(SDK_NetDecorderChnModeConfig) );
    StructToWinData();
}

void CDlgChannelMode::OnItemchangedListChannelmode(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if ( m_bSetCheck )
	{
		return;
	}
	NM_LISTVIEW* pNMLV = (NM_LISTVIEW*)pNMHDR;
	//从没有打勾到打勾
	if ( pNMLV->uNewState == 0x2000 && pNMLV->uOldState == 0x1000 )
	{
		TRACE("打勾\n");
		m_bSetCheck = true;
		m_ctrlList.SetCheck(m_nCheckItem, FALSE);
		m_bSetCheck = false;
		m_nCheckItem = pNMLV->iItem;  //暂时记录打钩的情况
	}
	//从打勾到没有打勾
	else if ( pNMLV->uNewState == 0x1000 && pNMLV->uOldState == 0x2000 )
	{
		TRACE("没打勾\n");
		m_bSetCheck = true;
		m_ctrlList.SetCheck(pNMLV->iItem, TRUE);
		m_bSetCheck = false;
		m_nCheckItem = pNMLV->iItem;
	}
	*pResult = 0;
}

bool CDlgChannelMode::StructToWinData()
{
	m_bSetCheck = true;
	m_ctrlList.DeleteAllItems();
	for ( int i = 0 ;  i < m_ChnModeCfg.HVRTotalCap.nHVRCap; i ++)
	{
		int j = 1;
		CString strTemp = _T("");
		m_ctrlList.InsertItem(i,  strTemp);
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].AnalogCap.n1080PChn );
		m_ctrlList.SetItemText(i, j ++, strTemp);
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].AnalogCap.n720PChn );
		m_ctrlList.SetItemText(i, j ++, strTemp);
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].AnalogCap.n960HChn );
		m_ctrlList.SetItemText(i, j ++, strTemp);
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].AnalogCap.nD1Chn );
		m_ctrlList.SetItemText(i, j ++, strTemp);
		
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].DigitalCap.n1080PChn);
		m_ctrlList.SetItemText(i, ++ j , strTemp);
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].DigitalCap.n720PChn);
		m_ctrlList.SetItemText(i, ++ j, strTemp);
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].DigitalCap.n960HChn);
		m_ctrlList.SetItemText(i, ++ j, strTemp);
		strTemp.Format(_T("%d"), m_ChnModeCfg.HVRTotalCap.HVRCap[i].DigitalCap.nD1Chn);
		m_ctrlList.SetItemText(i, ++ j, strTemp);
	}
	
	m_nCheckItem = m_ChnModeCfg.HVRCurCapMode;
	m_ctrlList.SetCheck(m_nCheckItem,  TRUE);
	m_bSetCheck = false;
	
	return true;
}

bool CDlgChannelMode::WinDataToStruct()
{
	m_ChnModeCfg.HVRCurCapMode = m_nCheckItem;
	return true;
}

void CDlgChannelMode::SaveChnModeCfg()
{
	WinDataToStruct(); 
    ((CClientDemo5Dlg*)AfxGetMainWnd())->SetChnModeConfig(&m_ChnModeCfg);	
}

void CDlgChannelMode::ClearAll()
{
	m_ctrlList.DeleteAllItems();
}
