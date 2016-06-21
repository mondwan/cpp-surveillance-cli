// DigitalChannelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DigitalChannelDlg.h"
#include "RemoteChannelDlg.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDigitalChannelDlg dialog


CDigitalChannelDlg::CDigitalChannelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDigitalChannelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDigitalChannelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_niDigChannel = 0;
	m_nChannelLast = 0;
	m_nHavCheck = 0;
	m_nLastMode = 0;
	
	m_bSetcheck = true;
	m_bDel = false;
	memset(&m_NetDigitChnConfig, 0 ,sizeof(SDK_NetDecorderConfigAll_V3));

}


void CDigitalChannelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDigitalChannelDlg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_CONNMODE, m_cmbMode);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_CheckEnable);
	DDX_Control(pDX, IDC_CHECK_SYNC, m_CheckSync);
	DDX_Control(pDX, IDC_EDIT_TOURTIME, m_editTourTime);
	DDX_Control(pDX, IDC_LIST_NETCFG, m_CtrList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDigitalChannelDlg, CDialog)
	//{{AFX_MSG_MAP(CDigitalChannelDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_CONNMODE, OnSelchangeComboConnmode)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_NETCFG, OnItemchangingListNetcfg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NETCFG, OnDblclkListNetcfg)
	ON_EN_CHANGE(IDC_EDIT_TOURTIME, OnChangeEditTourtime)
	ON_EN_KILLFOCUS(IDC_EDIT_TOURTIME, OnKillfocusEditTourtime)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitalChannelDlg message handlers

BOOL CDigitalChannelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);	
	// TODO: Add extra initialization here

	m_CtrList.InsertColumn(0, _CS(_T("Upgrade.NO")), LVCFMT_LEFT, 50);
	m_CtrList.InsertColumn(1, _CS(_T("DigitalChannel.CfgName")), LVCFMT_LEFT, 80);
	m_CtrList.InsertColumn(2, _CS(_T("Desktop.DevType")), LVCFMT_LEFT, 80);
	m_CtrList.InsertColumn(3, _CS(_T("DeviceManage.IPAddress")), LVCFMT_LEFT, 80);
	m_CtrList.InsertColumn(4, _CS(_T("DigitalChannel.RemoteChannel")),LVCFMT_LEFT,80);
	m_CtrList.SetExtendedStyle( m_CtrList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDigitalChannelDlg::InitDlgInfo(SDK_NetDecorderConfigAll_V3* pNetDigitChnConfig,int niDigChannel)
{
	memcpy(&m_NetDigitChnConfig,pNetDigitChnConfig, sizeof(SDK_NetDecorderConfigAll_V3));
	m_niDigChannel = niDigChannel;
    InitWndShow();
	StructToWinData(m_nChannelLast);
}

void CDigitalChannelDlg::StructToWinData(int nChannel)
{
	if ( nChannel < 0 )
	{
		return;
	} 
	m_bSetcheck = true;   //阻止CListCtrl中的setcheck进入OnItemchangingListNetcfg中
	//m_nHavCheck = 0;
    
	SDK_NetDigitChnConfig &DigitChnInfo = m_NetDigitChnConfig.DigitChnConf[nChannel];
	if ( !m_bDel )   //删除时这些就不刷新了
	{
		m_cmbChannel.SetCurSel(nChannel);
		m_CheckEnable.SetCheck( DigitChnInfo.Enable );
		OnCheckEnable();
		m_CheckSync.SetCheck( DigitChnInfo.EnCheckTime );
		m_cmbMode.SetCurSel( DigitChnInfo.ConnType );
		m_nLastMode = DigitChnInfo.ConnType;
	}
	
	m_CtrList.DeleteAllItems();
	
	//while ( strcmp(DigitChnInfo.NetDecorderConf[j].Address , "") != 0  )
	int nIndex = 0;
	for ( int j = 0; j < 32; j++)
	{	
		if ( strcmp(DigitChnInfo.NetDecorderConf[j].Address , "") == 0  )
		{
			continue;
		}
		CString str;
		str.Format(_T("%d"), nIndex + 1);
		m_CtrList.InsertItem(nIndex, str);
		m_CtrList.SetItemText( nIndex , 1, DigitChnInfo.NetDecorderConf[j].ConfName );
		switch ( DigitChnInfo.NetDecorderConf[j].DevType )
		{
			case 0:
				m_CtrList.SetItemText( nIndex , 2, _CS(_T("DigitalChannel.IPC")) );
				break;
			case 1:
				m_CtrList.SetItemText( nIndex , 2, _CS(_T("DigitalChannel.DVR")) );
				break;
			case 2:
				m_CtrList.SetItemText( nIndex , 2, _CS(_T("DigitalChannel.HVR")) );
				break;
			default:
				break;
		}
		m_CtrList.SetItemText( nIndex , 3, DigitChnInfo.NetDecorderConf[j].Address );
		
		str.Format( _T("%d"), DigitChnInfo.NetDecorderConf[j].Channel + 1 );
		m_CtrList.SetItemText( nIndex , 4, str );
		
		//m_CtrList.SetCheck(j, DigitChnInfo.NetDecorderConf[j].Enable);
		
		m_CtrList.SetItemData( nIndex, (long)&(DigitChnInfo.NetDecorderConf[j]) );
		
		nIndex ++;
	}
	
	if ( m_nLastMode )
	{
		if ( !m_bDel ) //删除时这些就不刷新了
		{
			GetDlgItem(IDC_STATIC_TOURTIME)->ShowWindow(SW_SHOW);
			GetDlgItem( IDC_EDIT_TOURTIME )->ShowWindow(SW_SHOW);
			GetDlgItem( IDC_STATIC_SEC )->ShowWindow(SW_SHOW);
			CString strTour;
			strTour.Format(_T("%d"), DigitChnInfo.TourIntv );
			GetDlgItem( IDC_EDIT_TOURTIME )->SetWindowText(strTour);
		}
		
		for ( int i = 0, nIndex = 0; i < m_CtrList.GetItemCount(); i++,nIndex++)   //处理删除异常问题
		{
			while ( strcmp(DigitChnInfo.NetDecorderConf[nIndex].Address , "") == 0  )
			{
				nIndex ++;
			}
			m_CtrList.SetCheck( i, DigitChnInfo.NetDecorderConf[nIndex].Enable );
		}
	}else
	{
		if ( !m_bDel ) //删除时这些就不刷新了
		{
			GetDlgItem( IDC_STATIC_TOURTIME )->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_TOURTIME )->ShowWindow(SW_HIDE);
			GetDlgItem( IDC_STATIC_SEC )->ShowWindow(SW_HIDE);
		}
		
		if ( DigitChnInfo.SingleConnId > 0 )
		{
			m_CtrList.SetCheck( DigitChnInfo.SingleConnId - 1, TRUE);
			m_nHavCheck = 1;
		}
	}
	
	m_bSetcheck = false;
	m_bDel = false;

}

void CDigitalChannelDlg::OnSelchangeComboConnmode() 
{
	// TODO: Add your control notification handler code here
	m_bSetcheck = true;
	// TODO: Add your control notification handler code here
	UpdateData();
	int nCurChannel = m_cmbChannel.GetCurSel();
	if ( m_cmbMode.GetCurSel() != m_nLastMode )
	{
	//	SaveNetConfig(m_nLastMode);
		m_nLastMode = m_cmbMode.GetCurSel();
	}
	if ( m_cmbMode.GetCurSel() )  //多连接
	{
		GetDlgItem(IDC_STATIC_TOURTIME )->ShowWindow(SW_SHOW);
		GetDlgItem( IDC_EDIT_TOURTIME )->ShowWindow(SW_SHOW);
		GetDlgItem( IDC_STATIC_SEC )->ShowWindow(SW_SHOW);
		//		m_NetDigitChnConfig.DigitChnConf[nCurChannel].SingleConnId = 0;  //多连接是设置无效
		int nCount = m_CtrList.GetItemCount();
		for (int i = 0; i < nCount ;i ++)
		{
			m_CtrList.SetCheck(i, m_NetDigitChnConfig.DigitChnConf[nCurChannel].NetDecorderConf[i].Enable);
		}
		CString str;
		str.Format(_T("%d"),m_NetDigitChnConfig.DigitChnConf[nCurChannel].TourIntv);
		m_editTourTime.SetWindowText(str);
	}else  //单连接
	{
		GetDlgItem( IDC_STATIC_TOURTIME )->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TOURTIME )->ShowWindow(SW_HIDE);
		GetDlgItem( IDC_STATIC_SEC )->ShowWindow(SW_HIDE);
		int nCount = m_CtrList.GetItemCount();
		
		for ( int i = 0; i < m_CtrList.GetItemCount(); i++)
		{
			if ( m_NetDigitChnConfig.DigitChnConf[nCurChannel].SingleConnId == i + 1 )
			{
				//m_nHavCheck = 1;
				m_CtrList.SetCheck(i, TRUE);
			}else
			{
				m_CtrList.SetCheck(i, FALSE);
			}
		}
	}
	
	m_bSetcheck = false;
}

void CDigitalChannelDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	int ncount = m_CtrList.GetItemCount();
	CRemoteChannelDlg dlg(NULL,ncount);   //创建默认的远程通道的对话框
	if (dlg.DoModal() == IDOK )
	{
		SDK_NetDecorderConfigV3 *pNetCfg = new SDK_NetDecorderConfigV3;
		dlg.GetRemoteChannel(pNetCfg);
		int nCurChannel = m_cmbChannel.GetCurSel();
		CString str;
		str.Format(_T("%d"), ncount + 1);
		m_CtrList.InsertItem(ncount, str);
		str.Format( _T("%s"), pNetCfg->ConfName);
		m_CtrList.SetItemText( ncount , 1, str);
		switch ( pNetCfg->DevType )
		{
		case 0:
			m_CtrList.SetItemText( ncount , 2, _CS(_T("DigitalChannel.IPC")) );
			break;
		case 1:
			m_CtrList.SetItemText( ncount , 2, _CS(_T("DigitalChannel.DVR")) );
			break;
		case 2:
			m_CtrList.SetItemText( ncount , 2, _CS(_T("DigitalChannel.HVR")) );
			break;
		default:
			break;
		}
		str.Format( _T("%s"), pNetCfg->Address);
		m_CtrList.SetItemText( ncount , 3, str );
		
		str.Format( _T("%d"), pNetCfg->Channel + 1 );
		m_CtrList.SetItemText( ncount , 4, str );
		
		m_CtrList.SetItemData( ncount, (long)pNetCfg );
		
		memcpy( &m_NetDigitChnConfig.DigitChnConf[nCurChannel].NetDecorderConf[ncount], pNetCfg, sizeof(SDK_NetDecorderConfigV3));
        
		 delete pNetCfg;
	}
	dlg.DestroyWindow();
}

void CDigitalChannelDlg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_bDel = true;
	int nIndex = m_CtrList.GetSelectionMark();
	int nCurChannel = m_cmbChannel.GetCurSel();
	if ( nIndex >= 0)
	{
		SDK_NetDecorderConfigV3* pNetcfg = (SDK_NetDecorderConfigV3*)m_CtrList.GetItemData(nIndex);
		m_CtrList.DeleteItem(nIndex);
		//delete pNetcfg;
		pNetcfg = NULL;
		memset( &m_NetDigitChnConfig.DigitChnConf[nCurChannel].NetDecorderConf[nIndex],0,sizeof(SDK_NetDecorderConfigV3));
		StructToWinData(nCurChannel);
		//删除完成后，更新下设备列表中的信息
		for (int i = 0; i < 32; i++)
		{
			if ( i < m_CtrList.GetItemCount() )
			{
				SDK_NetDecorderConfigV3* pNetcfg = (SDK_NetDecorderConfigV3*)m_CtrList.GetItemData(i);
				memcpy( &m_NetDigitChnConfig.DigitChnConf[nCurChannel].NetDecorderConf[i], pNetcfg, sizeof(SDK_NetDecorderConfigV3));
			}else
			{
				memset( &m_NetDigitChnConfig.DigitChnConf[nCurChannel].NetDecorderConf[i], 0, sizeof(SDK_NetDecorderConfigV3));
			}
		}
		UpdateData(FALSE);
	}
}

void CDigitalChannelDlg::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	int nChannel = m_cmbChannel.GetCurSel();
	if ( m_niDigChannel == nChannel)  //全数字通道
	{
		StructToWinData(0);
		m_nChannelLast = nChannel;
	}else
	{
		if ( nChannel != m_nChannelLast )
		{
			WinDataToStruct( m_nChannelLast );  //先保存之前的数字通道
			StructToWinData( nChannel );
			m_nChannelLast = nChannel;
			m_nHavCheck = 0;
		}
	}
}

void CDigitalChannelDlg::OnItemchangingListNetcfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if ( m_bSetcheck )
		return;
	
	//HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	int nCurChannel = m_cmbChannel.GetCurSel();
	if ( m_cmbMode.GetCurSel() )
	{
		
	}
	else
	{
		//int nIndex = m_CtrList.GetSelectionMark();
		//从没有打勾到打勾
		if ( pNMListView->uNewState == 0x2000 && pNMListView->uOldState == 0x1000 )
		{
			TRACE("打勾\n");
			/*			m_nHavCheck ++;
			if ( m_nHavCheck > 1 )
			{
			m_CtrList.SetCheck(nIndex, FALSE);
		}*/
			if ( m_NetDigitChnConfig.DigitChnConf[nCurChannel].SingleConnId > 0)
			{
				m_CtrList.SetCheck(m_NetDigitChnConfig.DigitChnConf[nCurChannel].SingleConnId - 1, FALSE);
			}
			m_NetDigitChnConfig.DigitChnConf[nCurChannel].SingleConnId = pNMListView->iItem + 1;  //暂时记录打钩的情况
		}
		//从打勾到没有打勾
		else if ( pNMListView->uNewState == 0x1000 && pNMListView->uOldState == 0x2000 )
		{
			TRACE("没打勾\n");
			/*			m_nHavCheck --;
			if ( m_nHavCheck < 0 )
			{
			m_nHavCheck = 0;
		}*/
			m_NetDigitChnConfig.DigitChnConf[nCurChannel].SingleConnId = 0;  //暂时记录不打钩的情况
		}
	}
	
	*pResult = 0;
}

void CDigitalChannelDlg::OnDblclkListNetcfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	int nIndex = m_CtrList.GetSelectionMark();
	if ( nIndex >= 0 )
	{
		int nCurChannel = m_cmbChannel.GetCurSel();
		SDK_NetDecorderConfigV3* pNetConfig = (SDK_NetDecorderConfigV3*)m_CtrList.GetItemData( nIndex );
		CRemoteChannelDlg dlg( pNetConfig );
		if ( dlg.DoModal() == IDOK )
		{
			CString str;
			dlg.GetRemoteChannel(pNetConfig);
			str.Format( _T("%s"), pNetConfig->ConfName);
			m_CtrList.SetItemText( nIndex , 1, str);
			switch ( pNetConfig->DevType )
			{
			case 0:
				m_CtrList.SetItemText( nIndex , 2, _CS(_T("DigitalChannel.IPC")) );
				break;
			case 1:
				m_CtrList.SetItemText( nIndex , 2, _CS(_T("DigitalChannel.DVR")) );
				break;
			case 2:
				m_CtrList.SetItemText( nIndex , 2, _CS(_T("DigitalChannel.HVR")) );
				break;
			default:
				break;
			}
			str.Format( _T("%s"), pNetConfig->Address);
			m_CtrList.SetItemText( nIndex , 3, str );
			
			str.Format( _T("%d"), pNetConfig->Channel + 1 );
			m_CtrList.SetItemText( nIndex , 4, str );
			
			memcpy( &m_NetDigitChnConfig.DigitChnConf[nCurChannel].NetDecorderConf[nIndex], pNetConfig, sizeof(SDK_NetDecorderConfigV3));
		}
	}
	*pResult = 0;
}

void CDigitalChannelDlg::OnRefrush() 
{
	// TODO: Add your control notification handler code here

	((CClientDemo5Dlg*)AfxGetMainWnd())->GetNetDecorderCfg();	
	//StructToWinData();
	StructToWinData( m_nChannelLast );
	UpdateData(FALSE);
}

void CDigitalChannelDlg::OnChangeEditTourtime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	CString strValue;
	GetDlgItemText(IDC_EDIT_TOURTIME,strValue);
	if ( atoi(strValue) > 600 )  //最大600秒
	{
		GetDlgItem(IDC_EDIT_TOURTIME)->SetWindowText("600");
	}
	
	GetDlgItem(IDC_EDIT_TOURTIME)->SetFocus();
}

void CDigitalChannelDlg::OnKillfocusEditTourtime() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString strValue;
	GetDlgItemText(IDC_EDIT_TOURTIME,strValue);
	if (  atoi(strValue) > 600 )
	{
		GetDlgItem(IDC_EDIT_TOURTIME)->SetWindowText("600");
	}
	GetDlgItemText(IDC_EDIT_TOURTIME,strValue);
	if ( atoi(strValue) < 10 ) //最小10秒
	{
		GetDlgItem(IDC_EDIT_TOURTIME)->SetWindowText("10");
	}
}
BOOL CDigitalChannelDlg::WinDataToStruct(int nChannel)
{
	UpdateData();
	m_NetDigitChnConfig.DigitChnConf[nChannel].Enable = m_CheckEnable.GetCheck();
	m_NetDigitChnConfig.DigitChnConf[nChannel].EnCheckTime = m_CheckSync.GetCheck();
	
	m_NetDigitChnConfig.DigitChnConf[nChannel].ConnType = m_cmbMode.GetCurSel();
	
	SaveNetConfig(m_nLastMode);  
	return true;
}

void CDigitalChannelDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if ( bShow )
	{
		InitWndShow();
		StructToWinData(m_nChannelLast);

		UpdateData(FALSE);
		if ( IsIconic() )
		{
			ShowWindow(SW_NORMAL);
		}
	}

}
BOOL CDigitalChannelDlg::InitWndShow()
{
	m_bDel = false;  //防止先点击删除，在取消，在进入页面发现显示异常
	m_nChannelLast = 0;
	m_nLastMode = 0;
	int nDigChannel = m_niDigChannel;
	int nChannel = 0;
	m_cmbChannel.ResetContent();
	m_cmbMode.ResetContent();
	for ( int i = 0; i < nDigChannel; i++)
	{
		CString str;
		str.Format( _T("%d"), i + 1 + nChannel );
		m_cmbChannel.AddString(str);
	}
	//m_cmbChannel.AddString( _CS(_T("OneClick.All")));   //暂时不支持全通道的，屏蔽先
	
	m_cmbMode.AddString(_CS(_T("DigitalChannel.SingleLink"))); //单连接
	m_cmbMode.AddString(_CS(_T("DigitalChannel.MulLink")));  //多连接
	
	return TRUE;
}

void CDigitalChannelDlg::SaveNetConfig(int nMode)
{
	UpdateData();
	//int nCurChannel = m_cmbChannel.GetCurSel();
	if ( nMode )   //多连接
	{
		for ( int i = 0; i < m_CtrList.GetItemCount(); i ++)
		{
			m_NetDigitChnConfig.DigitChnConf[m_nChannelLast].NetDecorderConf[i].Enable = m_CtrList.GetCheck(i);
			CString strTourTime;
			m_editTourTime.GetWindowText(strTourTime);
			m_NetDigitChnConfig.DigitChnConf[m_nChannelLast].TourIntv = atoi(strTourTime);
		}
	}else{   //单连接
			 /*		for ( int i = 0; i < m_CtrList.GetItemCount(); i ++)
			 {
			 if ( m_CtrList.GetCheck(i) )
			 {
			 m_NetDigitChnConfig.DigitChnConf[m_nChannelLast].SingleConnId = i + 1;
			 }
	}*/
	}
}
void CDigitalChannelDlg::OnCheckEnable() 
{
	// TODO: Add your control notification handler code here
	if (!m_CheckEnable.GetCheck())
	{
         m_CheckSync.EnableWindow(FALSE);
		 m_cmbMode.EnableWindow(FALSE);
		 m_CtrList.EnableWindow(FALSE);
		 GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
		 GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
	} 
	else
	{
		
		m_CheckSync.EnableWindow(TRUE);
		m_cmbMode.EnableWindow(TRUE);
		m_CtrList.EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
    	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
	}
	
}

void CDigitalChannelDlg::SaveDigitalChnCfg()
{
	UpdateData();
	WinDataToStruct(m_nChannelLast);
	
	
	int nDigChannel = m_niDigChannel;
	BOOL bSuccess = false;
	for ( int i = 0; i < nDigChannel ; i++)
	{
		bSuccess =((CClientDemo5Dlg*)AfxGetMainWnd())->SetNetDecorderCfg(&m_NetDigitChnConfig.DigitChnConf[i],i);
	}
	
	
	if ( bSuccess )
	{
		MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
	}
	
	OnRefrush();
}

void CDigitalChannelDlg::ClearAll()
{
	m_cmbChannel.ResetContent();
	m_cmbMode.ResetContent();
	m_CheckEnable.SetCheck(0);
	m_CheckSync.SetCheck(0);
	m_editTourTime.SetWindowText("");
	m_CtrList.DeleteAllItems();
}
