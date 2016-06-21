// ToolManagerHardDisk.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ToolManagerHardDisk.h"
#include "ClientDemo5Dlg.h"
#include "DlgDiskPartation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolManagerHardDisk dialog


CToolManagerHardDisk::CToolManagerHardDisk(CWnd* pParent /*=NULL*/)
	: CDialog(CToolManagerHardDisk::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolManagerHardDisk)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CToolManagerHardDisk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolManagerHardDisk)
	DDX_Control(pDX, IDC_LIST_TYPE_CAPA, m_listDisk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolManagerHardDisk, CDialog)
	//{{AFX_MSG_MAP(CToolManagerHardDisk)
	ON_BN_CLICKED(IDC_BTN_RW, CToolManagerHardDisk::OnBnClickedBtnRw)
	ON_BN_CLICKED(IDC_BTN_RD, CToolManagerHardDisk::OnBnClickedBtnRd)
	ON_BN_CLICKED(IDC_BTN_REDU, CToolManagerHardDisk::OnBnClickedBtnRedu)
	ON_BN_CLICKED(IDC_BTN_FORMAT, CToolManagerHardDisk::OnBnClickedBtnFormat)
	ON_BN_CLICKED(IDC_BTN_RECOVER, CToolManagerHardDisk::OnBnClickedBtnRecover)
	ON_BN_CLICKED(IDC_BTN_PARTATION, CToolManagerHardDisk::OnBnClickedBtnPartation)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TYPE_CAPA, CToolManagerHardDisk::OnLvnItemchangedListTypeCapa)
	ON_BN_CLICKED(IDC_BTN_SS, CToolManagerHardDisk::OnBnClickedBtnSnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolManagerHardDisk message handlers

BOOL CToolManagerHardDisk::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_listDisk.InsertColumn(0, _CS("HDDInfo.IndexNo"), LVCFMT_LEFT, 40);
	m_listDisk.InsertColumn(1, _CS("HDDInfo.Disk"),LVCFMT_LEFT, 80);
	m_listDisk.InsertColumn(2, _CS("HDDInfo.Type"),LVCFMT_LEFT, 80);
	m_listDisk.InsertColumn(3, _CS("HDDInfo.Status"),LVCFMT_LEFT, 80);
	m_listDisk.SetExtendedStyle(m_listDisk.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

	m_nPartNo = -1;
	m_nPhyNo = -1;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CToolManagerHardDisk::InitDlgInfo(SDK_SystemFunction *pSysFunc, H264_DVR_DEVICEINFO *pDeviceInfo)
{
	memcpy(&m_systemFunction,pSysFunc,sizeof(SDK_SystemFunction));

	if (m_systemFunction.vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM])
	{
	 GetDlgItem(IDC_BTN_SS)->ShowWindow(SW_SHOW);
	}
	else
	{
	 GetDlgItem(IDC_BTN_SS)->ShowWindow(SW_HIDE);
	}

	if (strcmp(pDeviceInfo->sSoftWareVersion, "V2.40.R06") >= 0)
	{
		EnableItems(TRUE);
	}
	else
	{
		EnableItems(FALSE);
	}

	OnUpdate();
}

void CToolManagerHardDisk::EnableItems(BOOL bEnable)
{
	GetDlgItem(IDC_BTN_RW)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_RD)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_REDU)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_FORMAT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_RECOVER)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_PARTATION)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_SS)->EnableWindow(bEnable);
}


void  CToolManagerHardDisk::OnUpdate()
{
//	CUserDataManager *pDate = CUserDataManager::instance();
//	int nRet = UpdateParam(E_SDK_CONFIG_DISK_INFO, (char *)&m_diskinfo, sizeof(m_diskinfo), -1, FALSE, FALSE);  
	long lLoginID = ((CClientDemo5Dlg*)AfxGetMainWnd())->m_LoginID;
	DWORD dwRet;

	if (0  == lLoginID)
	{
		return;
	}

	int nRet = H264_DVR_GetDevConfig(lLoginID,E_SDK_CONFIG_DISK_INFO,-1, (char *)&m_diskinfo, sizeof(m_diskinfo),&dwRet,5000);
	if ( TRUE  == nRet && sizeof(m_diskinfo) == dwRet)
	{
		int nIndex = 0;
		char szIndex[8], szDisk[16];
		
		m_listDisk.DeleteAllItems();
		
		CString strType, strStatus;
		int i, j;
		for (i = 0; i < m_diskinfo.iDiskNumber; i ++ )
		{
			for(j = 0; j < m_diskinfo.vStorageDeviceInfoAll[i].iPartNumber; j++)
			{
				sprintf(szIndex, "%d", nIndex + 1);
				m_listDisk.InsertItem(nIndex, szIndex);
				sprintf(szDisk, "%d-%d", m_diskinfo.vStorageDeviceInfoAll[i].iPhysicalNo + 1, j + 1);
				m_listDisk.SetItemText(nIndex, 1, szDisk);
				switch(m_diskinfo.vStorageDeviceInfoAll[i].diPartitions[j].iDriverType )
				{
				case SDK_DRIVER_READ_WRITE:
					strType.Format("%s", _CS("HDDManager.ReadWriteDriver"));
					break;
				case SDK_DRIVER_READ_ONLY:
					strType.Format("%s", _CS("HDDManager.ReadOnlyDriver"));
					break;
				case SDK_DRIVER_EVENTS:
					strType.Format("%s", _CS("HDDManager.EventDriver"));
					break;
				case SDK_DRIVER_REDUNDANT:
					strType.Format("%s", _CS("HDDManager.ReduDriver"));
					break;
				case SDK_DRIVER_SNAPSHOT:
					if (m_systemFunction.vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM])
					{
						GetDlgItem(IDC_BTN_SS)->ShowWindow(SW_SHOW);
						strType.Format("%s",_CS("HDDManager.SnapShotDriver"));
					}
					strType.Format("%s", _CS("HDDManager.SnapShotDriver"));
					break;
				default:
					strType.Format("%s", _CS("HDDManager.ReadWriteDriver"));
					break;
				}
				m_listDisk.SetItemText(nIndex, 2, strType );
				
				if (0 == m_diskinfo.vStorageDeviceInfoAll[i].diPartitions[0].iStatus)
				{
					strStatus.Format("%s", _CS("HDDManager.StateOK"));
				}
				else
				{
					strStatus.Format("%s", _CS("HDDManager.StateErr"));
				}
				m_listDisk.SetItemText(nIndex, 3, strStatus);
				m_listDisk.SetItemData(nIndex, (DWORD)i);
				nIndex++;
			}
		}
		
		m_nPhyNo = -1;
		m_nPartNo = -1;
		m_nLogicNo = -1;
		
		UpdateData(FALSE);
	}
}


void CToolManagerHardDisk::OnBnClickedBtnRw()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nPartNo == -1 || m_nPhyNo == -1 || m_nLogicNo == -1)
	{
		return;
	}
	CString strTemp("");
	strTemp.Format("%s", _CS("HDDManager.TipSetToReadWriteDriver"));
	if ( IDOK == MessageBox( strTemp , _CS( "OneClick.Prompt" ) , MB_OKCANCEL  | MB_ICONQUESTION ) )
	{
		memset(&m_DiskCtl, 0, sizeof(m_DiskCtl));
		m_DiskCtl.iAction = SDK_STORAGE_DEVICE_CONTROL_SETTYPE;
		m_DiskCtl.iPartNo = m_nPartNo;
		m_DiskCtl.iSerialNo = m_nLogicNo;
		m_DiskCtl.iType = SDK_DRIVER_READ_WRITE;
		OnExecute(&m_DiskCtl);
	}
}

void CToolManagerHardDisk::OnBnClickedBtnRd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nPartNo == -1 || m_nPhyNo == -1 || m_nLogicNo == -1)
	{
		return;
	}
	CString strTemp("");
	strTemp.Format("%s", _CS("HDDManager.TipSetToReadOnlyDriver"));
	if ( IDOK == MessageBox( strTemp , _CS( "OneClick.Prompt" ) , MB_OKCANCEL  | MB_ICONQUESTION ) )
	{
		memset(&m_DiskCtl, 0, sizeof(m_DiskCtl));
		m_DiskCtl.iAction = SDK_STORAGE_DEVICE_CONTROL_SETTYPE;
		m_DiskCtl.iPartNo = m_nPartNo;
		m_DiskCtl.iSerialNo = m_nLogicNo;
		m_DiskCtl.iType = SDK_DRIVER_READ_ONLY;
		OnExecute(&m_DiskCtl);
	}
}

void CToolManagerHardDisk::OnBnClickedBtnRedu()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nPartNo == -1 || m_nPhyNo == -1 || m_nLogicNo == -1)
	{
		return;
	}
	CString strTemp("");
	strTemp.Format("%s", _CS("HDDManager.TipSetToReduDriver"));
	if ( IDOK == MessageBox( strTemp , _CS( "OneClick.Prompt" ) , MB_OKCANCEL  | MB_ICONQUESTION ) )
	{
		memset(&m_DiskCtl, 0, sizeof(m_DiskCtl));
		m_DiskCtl.iAction = SDK_STORAGE_DEVICE_CONTROL_SETTYPE;
		m_DiskCtl.iPartNo = m_nPartNo;
		m_DiskCtl.iSerialNo = m_nLogicNo;
		m_DiskCtl.iType = SDK_DRIVER_REDUNDANT;
		OnExecute(&m_DiskCtl);
	}
}

void CToolManagerHardDisk::OnBnClickedBtnFormat()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nPartNo == -1 || m_nPhyNo == -1 || m_nLogicNo == -1)
	{
		return;
	}
	CString strTemp("");
	strTemp.Format("%s", _CS("HDDManager.TipFormatDisk"));
	if ( IDOK == MessageBox( strTemp , _CS( "OneClick.Prompt" ) , MB_OKCANCEL  | MB_ICONQUESTION ) )
	{
		memset(&m_DiskCtl, 0, sizeof(m_DiskCtl));
		m_DiskCtl.iAction = SDK_STORAGE_DEVICE_CONTROL_CLEAR;
		m_DiskCtl.iPartNo = m_nPartNo;
		m_DiskCtl.iSerialNo = m_nLogicNo;
		m_DiskCtl.iType = SDK_STORAGE_DEVICE_CLEAR_DATA;
		OnExecute(&m_DiskCtl);
	}
}

void CToolManagerHardDisk::OnBnClickedBtnRecover()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nPartNo == -1 || m_nPhyNo == -1 || m_nLogicNo == -1)
	{
		return;
	}
	CString strTemp("");
	strTemp.Format("%s", _CS("HDDManager.SuceToExecute"));
	if ( IDOK == MessageBox( strTemp , _CS( "OneClick.Prompt" ) , MB_OKCANCEL  | MB_ICONQUESTION ) )
	{
		memset(&m_DiskCtl, 0, sizeof(m_DiskCtl));
		m_DiskCtl.iAction = SDK_STORAGE_DEVICE_CONTROL_RECOVER;
		m_DiskCtl.iPartNo = m_nPartNo;
		m_DiskCtl.iSerialNo = m_nLogicNo;
		OnExecute(&m_DiskCtl);
	}
}

void CToolManagerHardDisk::OnBnClickedBtnPartation()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nPartNo == -1 || m_nPhyNo == -1 || m_nLogicNo == -1)
	{
		return;
	}
	CDlgDiskPartation dlg;
	dlg.m_nRecord = m_diskinfo.vStorageDeviceInfoAll[m_nLogicNo].diPartitions[0].uiTotalSpace;
	dlg.m_nSnap = m_diskinfo.vStorageDeviceInfoAll[m_nLogicNo].diPartitions[1].uiTotalSpace;
	dlg.m_nTotal = dlg.m_nSnap + dlg.m_nRecord;
	if (IDOK == dlg.DoModal())
	{
		CString strTemp("");
		strTemp.Format("%s", _CS("HDDManager.SuceToExecute"));
		if ( IDOK == MessageBox( strTemp , _CS( "OneClick.Prompt" ) , MB_OKCANCEL  | MB_ICONQUESTION ) )
		{
			memset(&m_DiskCtl, 0, sizeof(m_DiskCtl));
			m_DiskCtl.iAction = SDK_STORAGE_DEVICE_CONTROL_PARTITIONS;
			m_DiskCtl.iSerialNo = m_nLogicNo;
			m_DiskCtl.iPartSize[0] = dlg.m_nRecord;
			m_DiskCtl.iPartSize[1] = dlg.m_nSnap;
			OnExecute(&m_DiskCtl);
		}
	}
}


void CToolManagerHardDisk::OnBnClickedBtnSnap()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nPartNo == -1 || m_nPhyNo == -1 || m_nLogicNo == -1)
	{
		return;
	}
	CString strTemp("");
	strTemp.Format("%s", _CS("HDDManager.TipSetToSnapShotDriver"));
	if ( IDOK == MessageBox( strTemp , _CS( "OneClick.Prompt" ) , MB_OKCANCEL  | MB_ICONQUESTION ) )
	{
		memset(&m_DiskCtl, 0, sizeof(m_DiskCtl));
		m_DiskCtl.iAction = SDK_STORAGE_DEVICE_CONTROL_SETTYPE;
		m_DiskCtl.iPartNo = m_nPartNo;
		m_DiskCtl.iSerialNo = m_nLogicNo;
		m_DiskCtl.iType = SDK_DRIVER_SNAPSHOT;
		OnExecute(&m_DiskCtl);
	}
}

void CToolManagerHardDisk::OnLvnItemchangedListTypeCapa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nSelectIndex = pNMLV->iItem ;
	if ( nSelectIndex < 0 )
	{
		return;
	}
	
	CString strText = m_listDisk.GetItemText(nSelectIndex, 1);
	if (strText.GetLength() > 0)
	{
		sscanf(strText, "%d-%d", &m_nPhyNo, &m_nPartNo);
		if (m_nPhyNo < 1 || m_nPartNo < 1)
		{
			m_nPhyNo = -1;
			m_nPartNo = -1;
			m_nLogicNo = -1;
		}
		else
		{
			m_nPhyNo = m_nPhyNo - 1;
			m_nPartNo = m_nPartNo - 1;
			m_nLogicNo = m_listDisk.GetItemData(nSelectIndex);
		}
	}
	else
	{
		m_nPhyNo = -1;
		m_nPartNo = -1;
		m_nLogicNo = -1;
	}
	*pResult = 0;
}


void CToolManagerHardDisk::OnExecute(SDK_StorageDeviceControl *pDiskCtl)
{
     ((CClientDemo5Dlg*)AfxGetMainWnd())->SetHardDiskInfo(pDiskCtl);
}
