// NetPre.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetPre.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetPre dialog


CNetPre::CNetPre(SDK_NetOrderConfig* pNetOrder,CWnd* pParent /*=NULL*/)
	: CDialog(CNetPre::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetPre)
	//}}AFX_DATA_INIT
	memcpy(&m_pNetOrder,pNetOrder,sizeof(SDK_NetOrderConfig));
	m_netCount = 3;
}


void CNetPre::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetPre)
	DDX_Control(pDX, IDC_LIST_NETPRE, m_listctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetPre, CDialog)
	//{{AFX_MSG_MAP(CNetPre)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWM, OnButtonDowm)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NETPRE, OnClickListNetpre)
	ON_BN_CLICKED(IDC_CHECK_NETPRE, OnCheckNetpre)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetPre message handlers

BOOL CNetPre::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	int nItem;
	CString  netType[3] = {_CS("ConfigNet.Wirecard"),_CS("ConfigNet.Wireless"),_CS("ConfigNet.Wifi")};
	//int nType;
	m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	for ( int i = 0 ; i < 3; i++)
	{
		nItem = m_pNetOrder.pNetOrder[i].netOrder;
		m_listctrl.InsertItem(nItem,netType[i]);
	}
	((CButton*)GetDlgItem(IDC_CHECK_NETPRE))->SetCheck(m_pNetOrder.bEnable);
	OnCheckNetpre();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetPre::OnButtonUp() 
{
	// TODO: Add your control notification handler code here
	
	m_listctrl.SetFocus();
	if ( IndexInFieldList == -1)
	{
		return;
	}

	if ( IndexInFieldList == 0)
	{
		//AfxMessageBox("已经是第一行");
		return;
	}
	CString tempField;
	tempField = m_listctrl.GetItemText(IndexInFieldList, 0);
	m_listctrl.DeleteItem(IndexInFieldList);

	int tempItem;
	tempItem = m_listctrl.InsertItem(IndexInFieldList-1, _T(tempField));
//	m_pNetOrder.pNetOrder[]
	IndexInFieldList--;

	UINT flag = LVIS_SELECTED | LVIS_FOCUSED;
	m_listctrl.SetItemState(IndexInFieldList, flag, flag);
}

void CNetPre::OnButtonDowm() 
{
	// TODO: Add your control notification handler code here
	m_listctrl.SetFocus();
	if ( IndexInFieldList == -1)
	{
		return;
	}
	
	if ( IndexInFieldList == m_listctrl.GetItemCount()-1)
	{
		//AfxMessageBox("已经是最后一行");
		return;
	}
	CString tempField;
	tempField = m_listctrl.GetItemText(IndexInFieldList, 0);
	m_listctrl.DeleteItem(IndexInFieldList);
	
	int tempItem;
	tempItem = m_listctrl.InsertItem(IndexInFieldList+1, _T(tempField));
	IndexInFieldList++;
	
	UINT flag = LVIS_SELECTED | LVIS_FOCUSED;
	m_listctrl.SetItemState(IndexInFieldList, flag, flag);
}

void CNetPre::OnOK() 
{
	// TODO: Add extra validation here
	CString tempField;
	CString  netType[3] = {_CS("ConfigNet.Wirecard"),_CS("ConfigNet.Wireless"),_CS("ConfigNet.Wifi")};
	for ( int i = 0; i < 3 ; i++)
	{
		tempField = m_listctrl.GetItemText(i,0);
		for ( int j = 0; j < 3 ; j++)
		{
			if (netType[j] == tempField)
			{
				m_pNetOrder.pNetOrder[j].netOrder = i;
			}
		}
	}
	((CClientDemo5Dlg*)AfxGetMainWnd())->SetNetWorkConfigInfo(&m_pNetOrder);
	CDialog::OnOK();
}

void CNetPre::OnClickListNetpre(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos ; 
	pos = m_listctrl.GetFirstSelectedItemPosition();

	IndexInFieldList = m_listctrl.GetNextSelectedItem(pos);
	*pResult = 0;
}

void CNetPre::OnCheckNetpre() 
{
	// TODO: Add your control notification handler code here
	bool bchecked;

	bchecked = ((CButton*)GetDlgItem(IDC_CHECK_NETPRE))->GetCheck();
	m_listctrl.ShowWindow(bchecked);
	GetDlgItem(IDC_BUTTON_UP)->ShowWindow(bchecked);
	GetDlgItem(IDC_BUTTON_DOWM)->ShowWindow(bchecked);
	
}

void CNetPre::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code her

}
