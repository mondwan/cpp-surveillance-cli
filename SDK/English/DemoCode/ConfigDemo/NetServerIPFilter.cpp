// NetServerIPFilter.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "NetServerIPFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetServerIPFilter dialog


CNetServerIPFilter::CNetServerIPFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CNetServerIPFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetServerIPFilter)
	//}}AFX_DATA_INIT
	m_iBanIPCount = 0;
	m_iTruIPCount = 0;
	m_ensure = FALSE;
}


void CNetServerIPFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetServerIPFilter)
	DDX_Control(pDX, IDC_LIST_IPADDRESS, m_listIP);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_delButton);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_addButton);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_enable);
	DDX_Control(pDX, IDC_COMBO_CONSTRAINTTYPE, m_constrainType);
	DDX_Control(pDX, IDC_IPADDRESS, m_ipAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetServerIPFilter, CDialog)
	//{{AFX_MSG_MAP(CNetServerIPFilter)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_CONSTRAINTTYPE, OnSelchangeComboConstrainttype)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetServerIPFilter message handlers


BOOL CNetServerIPFilter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	m_enable.SetCheck(0);
	m_constrainType.InsertString(0,_CS("ConfigNet.BlackList"));
	m_constrainType.InsertString(1,_CS("ConfigNet.WhiteList"));
	m_constrainType.SetCurSel(0);
	m_listIP.InsertColumn(0,_CS("ConfigNet.No"),LVCFMT_LEFT,50);
	OnSelchangeComboConstrainttype();
	CenterWindow();
	return TRUE; 
}

void CNetServerIPFilter::OnCheckEnable() 
{
	if (m_enable.GetCheck())
	{
		m_constrainType.EnableWindow(TRUE);
		m_ipAddress.EnableWindow(TRUE);
		m_addButton.EnableWindow(TRUE);
		m_delButton.EnableWindow(TRUE);
	}
	else
	{
		m_constrainType.EnableWindow(FALSE);
		m_ipAddress.EnableWindow(FALSE);
		m_addButton.EnableWindow(FALSE);
		m_delButton.EnableWindow(FALSE);
	}
		
}

void CNetServerIPFilter::InitDlgInfo(SDK_NetIPFilterConfig *pNetIPFitCfg)
{
	memcpy(&m_NetIPFitCfg,pNetIPFitCfg,sizeof(SDK_NetIPFilterConfig));
	if (m_NetIPFitCfg.Enable)
		m_enable.SetCheck(1);
	else
		m_enable.SetCheck(0);
	m_constrainType.SetCurSel(0);
	m_ipAddress.ClearAddress();
	m_listIP.DeleteAllItems();
	OnCheckEnable();
	InitListCtrl();
}

void CNetServerIPFilter::OnSelchangeComboConstrainttype() 
{
	int type = m_constrainType.GetCurSel();
	m_listIP.DeleteColumn(1);
	if (0 == type)
	{
		m_listIP.InsertColumn(1,_CS("ConfigNet.BannedIP"),LVCFMT_LEFT,200);
		m_listIP.SetExtendedStyle(m_listIP.GetExtendedStyle()|LVS_EX_CHECKBOXES);
	}
	else if (1 == type)
	{
		m_listIP.InsertColumn(1,_CS("ConfigNet.TrustIP"),LVCFMT_LEFT,200);
		m_listIP.SetExtendedStyle(m_listIP.GetExtendedStyle()|LVS_EX_CHECKBOXES);
	}
	InitListCtrl();
}


void CNetServerIPFilter::InitListCtrl()
{
	m_listIP.DeleteAllItems();
	int i =0;
	CONFIG_IPAddress banIPADD;
	CONFIG_IPAddress truIPADD;
	int type = m_constrainType.GetCurSel();
	if (0 == type )
		m_iBanIPCount = 0;
	else if (1 == type)
		m_iTruIPCount = 0;
	CString ip,szIndex;
	for (i = 0; i < NET_MAX_FILTERIP_NUM; ++i)
	{
		szIndex.Format("%d",i+1);
		banIPADD = m_NetIPFitCfg.BannedList[i];
		truIPADD = m_NetIPFitCfg.TrustList[i];	
		if (0 == type)
		{	
			if (!(0 == banIPADD.c[0] && 0 == banIPADD.c[1] && 0 == banIPADD.c[2] && 0 == banIPADD.c[3]))
			{
				ip.Format("%d.%d.%d.%d",banIPADD.c[0],banIPADD.c[1],banIPADD.c[2],banIPADD.c[3]);
				m_listIP.InsertItem(m_iBanIPCount,szIndex);
				m_listIP.SetItemText(m_iBanIPCount,1,ip);
				++m_iBanIPCount;
			}
		}
		else if (1 == type)
		{
			if (!(0 == truIPADD.c[0] && 0 == truIPADD.c[1] && 0 == truIPADD.c[2] && 0 == truIPADD.c[3]))
			{
				ip.Format("%d.%d.%d.%d",truIPADD.c[0],truIPADD.c[1],truIPADD.c[2],truIPADD.c[3]);
				m_listIP.InsertItem(m_iTruIPCount,szIndex);
				m_listIP.SetItemText(m_iTruIPCount,1,ip);
				++m_iTruIPCount;
			}
		}
	}
}

void CNetServerIPFilter::OnButtonAdd() 
{
	if (!m_ipAddress.IsBlank())
	{
		BYTE c[4];
		CString ip;
		char szIndex[5];
		int type = m_constrainType.GetCurSel();
		int bResult = IsIPRepeat();
		m_ipAddress.GetAddress(c[0],c[1],c[2],c[3]);
		ip.Format("%d.%d.%d.%d",c[0],c[1],c[2],c[3]);
		if (0 == type)									//黑名单
		{
			if (1 == bResult)
			{
				MessageBox(_CS("Error.IPExisted"));
				return;
			}
			else if (2 == bResult)
			{
				MessageBox(_CS("Error.IPInTrustList"));
				return;
			}
			sprintf(szIndex,"%d",m_iBanIPCount + 1);
			m_listIP.InsertItem(m_iBanIPCount,szIndex);
			m_listIP.SetItemText(m_iBanIPCount,1,ip);
			++m_iBanIPCount;
		}
		else if(1 == type)							//白名单
		{
			if (2 == bResult)
			{
				MessageBox(_CS("Error.IPExisted"));
				return;
			}
			else if (1 == bResult)
			{
				MessageBox(_CS("Error.IPInBlackList"));
				return;
			}
			sprintf(szIndex,"%d",m_iTruIPCount + 1);
			m_listIP.InsertItem(m_iTruIPCount,szIndex);
			m_listIP.SetItemText(m_iTruIPCount,1,ip);
			++m_iTruIPCount;
		}
		Update();
	}
}

void CNetServerIPFilter::OnButtonDel() 
{
	int type = m_constrainType.GetCurSel();
	int nItem = 0;
	BOOL state;
	if (0 == type)
	{
		int iBanIPNum = m_iBanIPCount;
		for (nItem = iBanIPNum - 1; nItem >= 0; --nItem)
		{
			state = m_listIP.GetCheck(nItem);
			if (TRUE == state)
			{
				m_listIP.DeleteItem(nItem);
				--m_iBanIPCount;
			}
		}
	}
	else if (1 == type)
	{
		int iTruIPNum = m_iTruIPCount;
		for (nItem = iTruIPNum - 1; nItem >= 0; --nItem)
		{
			state = m_listIP.GetCheck(nItem);
			if (TRUE == state)
			{
				m_listIP.DeleteItem(nItem);
				--m_iTruIPCount;
			}
		}
	}
	Update();
}

int CNetServerIPFilter::IsIPRepeat()
{
	int nItem = 0,bResult = 0;
	int type = m_constrainType.GetCurSel();
	BYTE c[4];
	m_ipAddress.GetAddress(c[0],c[1],c[2],c[3]);
	CONFIG_IPAddress banIP,truIP;
	for (nItem = 0; nItem < m_iBanIPCount; ++nItem)
	{
		banIP = m_NetIPFitCfg.BannedList[nItem];
		if (c[0] == banIP.c[0] && c[1] == banIP.c[1] && c[2] == banIP.c[2] && c[3] == banIP.c[3])
		{
			bResult = 1;
			return bResult;
		}
	}
	
	for (nItem = 0; nItem < m_iTruIPCount; ++nItem)
	{
		truIP = m_NetIPFitCfg.TrustList[nItem];
		if (c[0] == truIP.c[0] && c[1] == truIP.c[1] && c[2] == truIP.c[2] && c[3] == truIP.c[3])
		{
			bResult = 2;
			return bResult;
		}
	}
	return bResult;
}


void CNetServerIPFilter::Update()
{
	int i = 0,j = 0,nIndex = 0,ipLength;
	CString ip,banIP,truIP;
	int type = m_constrainType.GetCurSel();
	if (0 == type)
		memset(m_NetIPFitCfg.BannedList,0,NET_MAX_FILTERIP_NUM);
	else if (1 == type)	
		memset(m_NetIPFitCfg.TrustList,0,NET_MAX_FILTERIP_NUM);
	if (0 == type)
	{
		for (i = 0; i < m_iBanIPCount; ++i)
		{
			banIP = m_listIP.GetItemText(i,1);
			ipLength = banIP.GetLength();
			for (j = 0; j < 3; ++j)
			{
				nIndex = banIP.Find(".");
				m_NetIPFitCfg.BannedList[i].c[j] = atoi(banIP.Left(nIndex));
				ipLength -=nIndex + 1;
				banIP = banIP.Right(ipLength);
			}
			m_NetIPFitCfg.BannedList[i].c[3] = atoi(banIP);
		}
	}
	else if (1 == type)
	{
		for (i = 0; i < m_iTruIPCount; ++i)
		{
			truIP = m_listIP.GetItemText(i,1);
			ipLength = truIP.GetLength();
			for (j = 0; j < 3; ++j)
			{
				nIndex = truIP.Find(".");
				m_NetIPFitCfg.TrustList[i].c[j] = atoi(truIP.Left(nIndex));
				ipLength -=nIndex + 1;
				truIP = truIP.Right(ipLength);
			}
			m_NetIPFitCfg.TrustList[i].c[3] = atoi(truIP);
		}
	}
}

void CNetServerIPFilter::OnOK() 
{
	m_ensure = TRUE;
	m_NetIPFitCfg.Enable = m_enable.GetCheck();
	CDialog::OnOK();
}

void CNetServerIPFilter::OnCancel() 
{
	m_ensure = FALSE;
	CDialog::OnCancel();
}