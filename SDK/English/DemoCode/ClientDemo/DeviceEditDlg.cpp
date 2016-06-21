// DeviceEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DeviceEditDlg.h"
#include "DeviceEdit.h"
#include "ClientDemoDlg.h"
#include "Markup.h"
//about audio talk
#include "Alaw_encoder.c"
#include "hisamr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceEditDlg dialog


CDeviceEditDlg::CDeviceEditDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDeviceEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceEditDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	
	m_pTalkDecodeBuf = NULL;	//buffer audio data
	m_lTalkHandle = 0;
	memset(&m_talkDevice, 0, sizeof(m_talkDevice));
   
	Devc_Map::iterator p=m_devMap.begin();
	while(p!=m_devMap.end())
	{
		p=m_devMap.erase(p);		
	}
}


void CDeviceEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceEditDlg)
	DDX_Control(pDX, IDC_TREE1, m_deviceTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceEditDlg, CDialog)
//{{AFX_MSG_MAP(CDeviceEditDlg)
ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
ON_WM_DESTROY()
ON_WM_PAINT()
ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
ON_NOTIFY(NM_CLICK, IDC_TREE1, OnClickTree1)
ON_WM_TIMER()
//}}AFX_MSG_MAP
ON_COMMAND(ID_ADD_DEVICE, AddDevice)
ON_COMMAND(ID_DELETE_DEVICE, DeleteDevice)
ON_COMMAND(ID_CONNNECT, Connect)
ON_COMMAND(ID_START_TALK, OnTalk)
ON_COMMAND(ID_DEVICE_CAPTURE, OnDeviceCapture)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceEditDlg message handlers

BOOL CDeviceEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ReadXML();
	return TRUE;
}

void CDeviceEditDlg::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult)   //右键单击
{
	CPoint point;
	UINT   pFalg;
	GetCursorPos(&point);
	
	m_deviceTree.ScreenToClient(&point);
	HTREEITEM hitem = m_deviceTree.HitTest(point,&pFalg);
	if (hitem != NULL)
	{
		m_deviceTree.SelectItem(hitem);
	}
	
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	if ( hSelectItem )
	{
		HTREEITEM parentItem = m_deviceTree.GetParentItem(hSelectItem);
		if ( parentItem )
		{
			//if has parent node, is channel node
			CMenu Menu;
			Menu.CreatePopupMenu();
			
			Menu.AppendMenu(MF_STRING , ID_CONNNECT, _CS("Desktop.ConnVideo"));
			Menu.AppendMenu(MF_STRING , ID_ADD_DEVICE, _CS("DeviceManage.DevAdd"));
			
			CPoint pt;
			::GetCursorPos(&pt);
			Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
			
			*pResult = 0;
			
			return;
		}
		//device node
		else
		{
			DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
			if (pDev->lLoginID<=0)
			{
				CMenu Menu;
				Menu.CreatePopupMenu();
				//Menu.AppendMenu(MF_STRING , ID_START_TALK, _CS("Desktop.StartTalk"));
				Menu.AppendMenu(MF_STRING , ID_ADD_DEVICE, _CS("DeviceManage.DevAdd"));
				Menu.AppendMenu(MF_STRING , ID_DELETE_DEVICE, _CS("DeviceManage.DevDel"));

				CPoint pt;
				::GetCursorPos(&pt);
				Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
			}
			
			if ( pDev && pDev->lLoginID > 0 )
			{
				CMenu Menu;
				Menu.CreatePopupMenu();
				
				if ( strcmp(m_talkDevice.szDevName, pDev->szDevName) )
				{
					Menu.AppendMenu(MF_STRING , ID_START_TALK, _CS("Desktop.StartTalk"));
					Menu.AppendMenu(MF_STRING , ID_ADD_DEVICE, _CS("DeviceManage.DevAdd"));
					if (pDev->devctype !=100)
					{
						Menu.AppendMenu(MF_STRING , ID_DELETE_DEVICE, _CS("DeviceManage.DevDel"));
					}		
				}
				else
				{
					Menu.AppendMenu(MF_STRING , ID_START_TALK, _CS("Desktop.StopTalk"));
					Menu.AppendMenu(MF_STRING , ID_ADD_DEVICE, _CS("DeviceManage.DevAdd"));
					Menu.AppendMenu(MF_STRING , ID_DELETE_DEVICE, _CS("DeviceManage.DevDel"));
				}
				Menu.AppendMenu(MF_STRING , ID_DEVICE_CAPTURE, _CS("DeviceManage.CatchPicture"));

				CPoint pt;
				::GetCursorPos(&pt);
				Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);	
				
				return;
			}
		}
	}
	else
	{
		CMenu Menu;
		Menu.CreatePopupMenu();
		Menu.AppendMenu(MF_STRING , ID_ADD_DEVICE, _CS("DeviceManage.DevAdd"));
		CPoint pt;
		::GetCursorPos(&pt);
		Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
	}
}

//add device
void CDeviceEditDlg::AddDevice()
{
	CDeviceEdit dlg;
	if ( IDOK == dlg.DoModal() )
	{
		DEV_INFO *pDev = new DEV_INFO;
		memset( pDev, 0, sizeof(DEV_INFO) );
		memcpy( pDev, &dlg.m_devInfo, sizeof(DEV_INFO) );
		pDev->lID = (long)pDev;
		m_devMap[pDev->lID] = pDev;
		if(pDev->lLoginID>0)
		{
			//add to device tree
			HTREEITEM hAddItem = m_deviceTree.InsertItem(pDev->szDevName);
			m_deviceTree.SetItemData(hAddItem, (DWORD)pDev);
			
			CString strName("");
			for ( int i = 0; i < pDev->nTotalChannel; i ++ )
			{
				strName.Format("CAM %d", i + 1);
				HTREEITEM item = m_deviceTree.InsertItem( strName, 0, 0, hAddItem );
				m_deviceTree.SetItemData(item, i);
			}
			m_deviceTree.SelectItem(hAddItem);
			m_deviceTree.Expand(hAddItem, TVE_EXPAND);
		}
		
	}
}

//del device
void CDeviceEditDlg::DeleteDevice()
{
	HTREEITEM hItem = m_deviceTree.GetSelectedItem();
	
	if ( hItem == NULL )
	{
		return;
	}
	
	DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hItem);
	if ( pDev &&pDev->devctype!=100  )
	{
		if ( pDev->lLoginID > 0 )
		{
			H264_DVR_Logout(pDev->lLoginID);
		}
		
		Devc_Map::iterator bIter = m_devMap.find( pDev->lID );
		if ( bIter != m_devMap.end() )
		{
			m_devMap.erase(bIter);
		}
		m_deviceTree.DeleteItem(hItem);
		CMarkup xml;
		if (xml.Load(GET_MODULE_FILE_INFO.strPath + "UserInfo.xml"))
		{
			while(xml.FindChildElem("ip"))
			{
				xml.IntoElem();
				xml.FindChildElem("ip2");
				if(xml.GetChildData()==pDev->szIpaddress)
				{
					xml.RemoveElem();
					xml.Save(GET_MODULE_FILE_INFO.strPath + "UserInfo.xml");
				}
				xml.OutOfElem();
			}
			
		}
		delete pDev;
		pDev = NULL;
	}	
}


void CDeviceEditDlg::Connect()
{
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	
	if ( hSelectItem )
	{
		HTREEITEM parentItem = m_deviceTree.GetParentItem(hSelectItem);
		if ( parentItem )
		{
			//if has parent node, is channel node
			DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(parentItem);
			if ( pDev )
			{
				int nChannel = m_deviceTree.GetItemData(hSelectItem);
				
				//connet channel
				CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
				if ( pParent )
				{
					int nRet = pParent->Connect(pDev, nChannel);
					if(nRet<=0)
					{
						return;
					}
				}
			}
			return;
		}
	}
	
	//connect channel selected
	if ( hSelectItem )
	{
		DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
		if ( pDev )
		{
			for ( int i = 0; i < pDev->nTotalChannel; i ++ )
			{
				CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
				if ( pParent  )
				{
					int nRet = pParent->Connect(pDev, i, i);
					if ( 0 == nRet )
					{
						//connnect fail, break;
						break;
					}
				}
			}
		}
	}
}

#define MAX_CAPTURE_BUF		100*1024
char g_capturebuf[MAX_CAPTURE_BUF];
void CDeviceEditDlg::OnDeviceCapture()
{
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	
	if ( hSelectItem )
	{
		HTREEITEM parentItem = m_deviceTree.GetParentItem(hSelectItem);
		if ( parentItem ) //设备抓图
		{
			return;
		}
		else
		{
			DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
			if ( pDev && pDev->lLoginID > 0 )
			{
				int nRetLen;
				unsigned long lRetLen;
				SDK_SystemFunction* pSysFunc = new SDK_SystemFunction;
				H264_DVR_GetDevConfig(pDev->lLoginID, E_SDK_CONFIG_ABILITY_SYSFUNC, 0, (char*)pSysFunc, sizeof(SDK_SystemFunction),
					&lRetLen, 5000);
				if (!pSysFunc->vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM])
				{
/*					unsigned long lRetLog;*/
// 					SDK_CustomEnvirDataAllchannl * pOutNas= new SDK_CustomEnvirDataAllchannl;
// 					H264_DVR_GetDevConfig(pDev->lLoginID,E_SDK_CFG_XZHD_ENVIRONMENT,-1, (char*)pOutNas,sizeof(SDK_CustomEnvirDataAllchannl),
// 						&lRetLog,5000);
					MessageBox(_CS("Err.NoSupportSnap"));
					return;
				}
// 				SDK_SPVMN_NAS_SERVER pInNas;
// 				strcpy(pInNas.DowloadIP ,"10.10.37.71");
// 				strcpy(pInNas.DowloadPath , "E:\recorder");
// 				pInNas.Port = 80;
// 				strcpy(pInNas.RootDir , "E:\recorder");
// 				strcpy(pInNas.ServerIP , "192.168.1.1");
// 				BOOL bSuccess = H264_DVR_SetDevConfig(pDev->lLoginID,E_SDK_CFG_NETPLAT_SPVMN_NAS,0,(char*)&pInNas,
// 					sizeof(SDK_SPVMN_NAS_SERVER),3000);
//  				unsigned long lRetLog;
//  				SDK_CustomEnvirDataAll * pOutNas= new SDK_CustomEnvirDataAll;
//  				H264_DVR_GetDevConfig(pDev->lLoginID,E_SDK_CFG_XZHD_ENVIRONMENT,-1, (char*)pOutNas,sizeof(SDK_CustomEnvirDataAllchannl),
//  					&lRetLog,5000);
				bool bRet = H264_DVR_CatchPicInBuffer(pDev->lLoginID, 0, g_capturebuf, MAX_CAPTURE_BUF, &nRetLen);
				if ( bRet )
				{
					CString FileName("Test");
					CString FileType(".jpg");
					FileName += /*szNowtime + */FileType;
					CFileDialog dlgfilepathname(FALSE,"jpg",FileType,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ALL File(.jpg)||", this);
					LPTSTR pszfilename = FileName.GetBuffer(MAX_PATH);//FileName.GetLength());
					//memset(pszfilename,0,MAX_PATH);
					lstrcpy(pszfilename,FileName);
					FileName.ReleaseBuffer(MAX_PATH);
					dlgfilepathname.m_ofn.lpstrFile = pszfilename;
					if (dlgfilepathname.DoModal() == IDOK)
					{
						CFile file;
						file.Open(pszfilename, CFile::modeCreate | CFile::modeReadWrite);
						file.Write(g_capturebuf, nRetLen);
						FileName = dlgfilepathname.GetPathName();
						MessageBox(_CS(_T("Desktop.FileSaved"))+ FileName);
						file.Close();
					}
					FileName.ReleaseBuffer();
				}
				else
				{
					MessageBox(_CS("Desktop.SnapshotFail"));
				}
			}
		}
	}
}
void CDeviceEditDlg::OnTalk()
{
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	
	if ( hSelectItem )
	{
		HTREEITEM parentItem = m_deviceTree.GetParentItem(hSelectItem);
		if ( parentItem )
		{
			return;
		}
		else
		{
			DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
			if ( pDev && pDev->lLoginID > 0 )
			{
				if ( strcmp(m_talkDevice.szDevName, pDev->szDevName) )
				{
					// if talk already started, stop it first.
					if ( m_talkDevice.lLoginID > 0 )
						StopTalk(&m_talkDevice);
					
					StartTalk(pDev);
					
					memcpy( &m_talkDevice, pDev, sizeof(m_talkDevice));
				}
				else
				{
					StopTalk(pDev);
					
					memset( &m_talkDevice, 0 ,sizeof(m_talkDevice));
				}	
			}
		}
	}
}





BOOL CDeviceEditDlg::StartTalk(DEV_INFO *pDevice)
{


	if ( !pDevice )
	{
		return false;
	}
	if(m_lTalkHandle)
	{
			return FALSE;
	}
	else
	{
		if(m_lTalkHandle=H264_DVR_StartLocalVoiceCom(pDevice->lLoginID))
		{
			return TRUE;
		}
		else
		{
			m_lTalkHandle=0;
			return FALSE;
		}		
		
	}	


}

BOOL CDeviceEditDlg::StopTalk(DEV_INFO *pDevice)
{
	if ( !pDevice )
	{
		return false;
	}

	if(m_lTalkHandle)
	{
		H264_DVR_StopVoiceCom(m_lTalkHandle);	
		m_lTalkHandle = 0;
		return true;
	}
	return FALSE;
	
	
}





void CDeviceEditDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	Devc_Map::iterator bIter;
	for ( bIter = m_devMap.begin(); bIter != m_devMap.end(); bIter ++ )
	{
		DEV_INFO *pDev = bIter->second;
		if ( pDev )
		{
			if ( pDev->lLoginID >0)
			{
				H264_DVR_Logout(pDev->lLoginID);
			}
			delete pDev;
			pDev = NULL;
		}
	}
	m_devMap.clear();
}

void CDeviceEditDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	m_deviceTree.MoveWindow(rect);
}

void CDeviceEditDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult)  //双击左键
{
	// TODO: Add your control notification handler code here
	//
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	if(hSelectItem)
	{
		HTREEITEM parentItem = m_deviceTree.GetParentItem(hSelectItem);
		if ( parentItem )
		{
			//channel node
			Connect();
			*pResult = 0;
			return;
		}
		//channel node
		else
		{	//login
			DEV_INFO* pDev= (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
			if(pDev->lLoginID<=0)
			{				
				long loginID=DevLogin(pDev);
				if (loginID >0)
				{					
					pDev->lLoginID=loginID;
					pDev->lID = (long)pDev;
					m_devMap[pDev->lID] = pDev;
					CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
					if ( pParent)
					{
						pParent->SetDevInfo(pDev);
					}
				}
				else 
				{
                    *pResult=true;
					return;
				}
			}
			//logout
			else
			{
				DEV_INFO* pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
				H264_DVR_Logout(pDev->lLoginID);
				pDev->lLoginID=-1;
				pDev->lID = (long)pDev;
				m_devMap[pDev->lID] = pDev;
			}
		}
	}
	*pResult = 0;
}

void CDeviceEditDlg::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult)  //左键单击
{
	// TODO: Add your control notification handler code here
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	if(hSelectItem)
	{
		DEV_INFO *pDev = NULL;
		HTREEITEM parentItem = m_deviceTree.GetParentItem(hSelectItem);
		if ( parentItem ) //channel node
		{
			//if has parent node, is channel node
			pDev = (DEV_INFO *)m_deviceTree.GetItemData(parentItem);
		}
		else //dev node
		{
			pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
		}
		
		if ( pDev )
		{
			CClientDemoDlg *pParent = (CClientDemoDlg *)GetParent();
			if ( pParent  )
			{
				pParent->SetDevInfo(pDev);
			}
		}
	}
	*pResult = 0;
}
DEV_INFO CDeviceEditDlg::ReadXML()
{
	CMarkup xml;
	DEV_INFO devInfo;
	
	devInfo.nPort=0;
	devInfo.lLoginID=0;
	devInfo.lID=0;
	
	if(xml.Load(GET_MODULE_FILE_INFO.strPath + "UserInfo.xml"))
	{
		while(xml.FindChildElem("ip"))
		{
			//read the information from XML
			CString strIP="",strUserName="",strPsw="",strDevName="";
			UINT nPort;
			long byChanNum=0,lID=0;

			UINT bSerialID,nSerPort;
			CString szSerIP="",szSerialInfo="";			
			xml.IntoElem();		

			xml.FindChildElem("ip2");
			strIP=xml.GetChildData();
			xml.FindChildElem("DEVICENAME");
			strDevName=xml.GetChildData();
			xml.FindChildElem("username");
			strUserName=xml.GetChildData();
			xml.FindChildElem("port");
			nPort=atoi(xml.GetChildData());
			xml.FindChildElem("pwd");
			strPsw=xml.GetChildData();
			xml.FindChildElem("byChanNum");
			byChanNum=atoi(xml.GetChildData());
			xml.FindChildElem("lID");
			lID=atoi(xml.GetChildData());

			xml.FindChildElem("bSerialID");
			bSerialID=atoi(xml.GetChildData());
			xml.FindChildElem("szSerIP");
			szSerIP=xml.GetChildData();
			xml.FindChildElem("nSerPort");
			nSerPort=atoi(xml.GetChildData());
			xml.FindChildElem("szSerialInfo");
			szSerialInfo=xml.GetChildData();//新增ddns记录
			xml.FindChildElem("LoginType");
			int LoginType=atoi(xml.GetChildData());
			devInfo.devctype=LoginType;

			xml.OutOfElem();

			

			devInfo.nTotalChannel =byChanNum;
			devInfo.nPort = nPort;

			devInfo.bSerialID=bSerialID;		
			devInfo.nSerPort=nSerPort;
			strcpy(devInfo.szSerIP,szSerIP.GetBuffer(0));		
			strcpy(devInfo.szSerialInfo, szSerialInfo.GetBuffer(0));//新增ddns记录		
			strcpy(devInfo.szDevName, strDevName);
			strcpy(devInfo.szUserName, strUserName);
			strcpy(devInfo.szPsw, strPsw);
			strcpy(devInfo.szIpaddress, strIP);
			DEV_INFO *pDev = new DEV_INFO;
			memset( pDev, 0, sizeof(DEV_INFO) );
			memcpy( pDev, &devInfo, sizeof(DEV_INFO) );
			pDev->lID = (long)pDev;
			m_devMap[pDev->lID] = pDev;
			HTREEITEM hAddItem = m_deviceTree.InsertItem(strDevName);
			m_deviceTree.SetItemData(hAddItem, (DWORD)pDev);
			CString strName("");
			for ( int i = 0; i < byChanNum; i ++)
			{
				strName.Format("CAM %d", i+1);
				HTREEITEM item = m_deviceTree.InsertItem(strName, 0, 0, hAddItem);
				m_deviceTree.SetItemData(item, i);
			}
		}
	}
	return devInfo;
}
extern SocketStyle g_connectType;
long CDeviceEditDlg::DevLogin(DEV_INFO* pdev)
{


	if(pdev->bSerialID)//如果之前是DDNS获取ip;这里先获取动态ip
	{
		int maxDeviceNum = 1000;  //最大支持设备数量100
		DDNS_INFO *pDDNSInfo = new DDNS_INFO[maxDeviceNum];
		SearchMode searchmode;
		int nReNum = 0;  //实际获得的设备数量		
		searchmode.nType = DDNS_SERIAL;		
		strcpy(searchmode.szSerIP,pdev->szSerIP);
		searchmode.nSerPort = pdev->nSerPort ;
		strcpy(searchmode.szSerialInfo, pdev->szSerialInfo);
		CString strTemp;
		bool bret = H264_DVR_GetDDNSInfo(searchmode, pDDNSInfo, maxDeviceNum, nReNum);
		if ( !bret )
		{
			delete pDDNSInfo;
			pDDNSInfo = NULL;
			return FALSE;
		}
		memcpy(pdev->szIpaddress,pDDNSInfo[0].IP,15);
		pdev->nPort=pDDNSInfo[0].MediaPort;
	}

	H264_DVR_DEVICEINFO OutDev;
	int nError = 0;
	//设置尝试连接设备次数和等待时间
	H264_DVR_SetConnectTime(3000, 1);//设置尝试连接1次，等待时间3s
//	H264_DVR_SetLocalBindAddress("10.2.55.25");
	
	long lLogin=0;

		lLogin = H264_DVR_Login(pdev->szIpaddress, pdev->nPort, pdev->szUserName, pdev->szPsw, &OutDev, &nError,(SocketStyle)pdev->devctype);

	if ( lLogin <= 0 )
	{
		int nErr = H264_DVR_GetLastError();  
		if(nErr == H264_DVR_PASSWORD_NOT_VALID)
		{
			MessageBox(_CS("Error.PwdErr"));
		}
		else
		{
			//////////////////////////////////////////////////////
			MessageBox(_CS("Error.NotFound"));
			
		}
		return lLogin;
	}
// 	SDK_AbilitySerialNo serialCfg;
// 	unsigned long lRetu;
// 		long lRet = H264_DVR_GetDevConfig(lLogin, E_SDK_CONFIG_ABILITY_SERIALNO, -1,(char*)&serialCfg,sizeof(serialCfg),&lRetu,5000 );
// 		strcpy(serialCfg.productType,"AAAAAAAAAAAA");
// 		lRet = H264_DVR_SetDevConfig(lLogin, E_SDK_CONFIG_ABILITY_SERIALNO, -1,(char*)&serialCfg,sizeof(serialCfg),5000 );
// 		lRet = H264_DVR_GetDevConfig(lLogin, E_SDK_CONFIG_ABILITY_SERIALNO, -1,(char*)&serialCfg,sizeof(serialCfg),&lRetu,5000 );
	H264_DVR_SetupAlarmChan(lLogin);
	return lLogin;
}

void CDeviceEditDlg::ReConnect(LONG lLoginID, char *pchDVRIP,  LONG nDVRPort)
{
	//put device into reconnet map
	Devc_Map::iterator p = m_devMap.begin();
	while(p!=m_devMap.end())
	{
		DEV_INFO *pDev = p->second;
		if (pDev->lLoginID == lLoginID)
		{
			H264_DVR_Logout(pDev->lLoginID);
			pDev->lLoginID=-1;
			m_devReconnetMap[pDev->lID] = pDev;
			break;
		}
		p++;
	}

	//start timer
	SetTimer(1, 30000, NULL);
}

void CDeviceEditDlg::OnTimer(UINT nIDEvent)
{
	Devc_Map::iterator p = m_devReconnetMap.begin();
	while(p!=m_devReconnetMap.end())
	{
		DEV_INFO *pDev = p->second;
		long loginID=DevLogin(pDev);
		if (loginID >0)
		{					
			pDev->lLoginID=loginID;
			m_devReconnetMap.erase(p++);
		}
		else
		{
			p++;
		}
	}
	if (0 == m_devReconnetMap.size())
	{
		KillTimer(1);
	}
	CDialog::OnTimer(nIDEvent);
}
