// SysInfoVersion.cpp : 实现文件
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "SysInfoVersion.h"
//#include "UserDataManager.h"


//extern   CConfigModuleApp   theApp;
// CSysInfoVersion 对话框

IMPLEMENT_DYNAMIC(CSysInfoVersion, CDialog)

CSysInfoVersion::CSysInfoVersion(CWnd* pParent /*=NULL*/)
: m_nAlarmInput(0)
, m_nAlarmOut(0)
, m_strIssuancedate(_T(""))
, m_nTotalChannel(0)
, m_nExtChannel(0)
, m_strVersion(_T(""))
, m_strStatu(_T(""))
, m_strInfo(_T(""))
, m_strSerialID(_T(""))
{
//OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
//	AfxSetResourceHandle(theApp.m_hInstance);//设置新的模块      	
}

CSysInfoVersion::~CSysInfoVersion()
{
}

void CSysInfoVersion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_ALARM_INPUT, m_nAlarmInput);
	DDX_Text(pDX, IDC_STATIC_ALARM_OUT, m_nAlarmOut);
	DDX_Text(pDX, IDC_STATIC_ISSUANCEDATE, m_strIssuancedate);
	DDX_Text(pDX, IDC_STATIC_TOTAL_CHANNEL, m_nTotalChannel);
	DDX_Text(pDX, IDC_STATIC_EXT_CHANNEL, m_nExtChannel);
	DDX_Text(pDX, IDC_STATIC_VERSION, m_strVersion);
	DDX_Text(pDX, IDC_STATIC_PRODUCT, m_strProduct);
	DDX_Text(pDX, IDC_STATIC_COMPANY, m_strCompany);
	DDX_Text(pDX, IDC_STATIC_TEL, m_strTel);

	DDX_Text(pDX, IDC_STATIC_NAT_STATU2, m_strStatu);
	DDX_Text(pDX, IDC_STATIC_NAT_INFO2, m_strInfo);
	DDX_Text(pDX, IDC_EDIT_NAT_SERIALSID, m_strSerialID);
}


BEGIN_MESSAGE_MAP(CSysInfoVersion, CDialog)
	ON_WM_SHOWWINDOW()		
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysInfoVersion 消息处理程序

BOOL CSysInfoVersion::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);
//	AfxSetResourceHandle(OldResourceHanlde);//对话框已创建，设置回原来的模块  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSysInfoVersion::OnPaint()
{
	CDialog::OnPaint();
}

HBRUSH  CSysInfoVersion::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor==CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
		HBRUSH B = CreateSolidBrush(RGB(52,52,52));  
		return (HBRUSH) B;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}



void CSysInfoVersion::InitDlgInfo(H264_DVR_DEVICEINFO *pSysinfo,long loginID)
{
 	m_nAlarmInput = pSysinfo->byAlarmInPortNum;
 	//m_nTotalChannel = GetSysInfo(m_ID)->byChanNum;
 	//增加数字通道
 	m_nTotalChannel = pSysinfo->byChanNum + pSysinfo->iDigChannel;
 	m_nAlarmOut = pSysinfo->byAlarmOutPortNum;
 	m_nExtChannel = pSysinfo->iExtraChannel;
 	m_strIssuancedate.Format("%04d-%02d-%02d %02d:%02d:%02d", 
 								pSysinfo->tmBuildTime.year,
 								pSysinfo->tmBuildTime.month,
 								pSysinfo->tmBuildTime.day,
 								pSysinfo->tmBuildTime.hour,
 								pSysinfo->tmBuildTime.minute,
 								pSysinfo->tmBuildTime.second);
 	m_strVersion = pSysinfo->sSoftWareVersion ;
 	m_strProduct = _CS("Version.ProductType");
 	m_strCompany = _CS("Version.CompanyName");
 	m_strTel = _CS("Version.TelNum");
 
 	if (m_strProduct == _T("ProductType"))//这里是什么意思了？有翻译才显示？以后也许可以考虑去掉
 	{
 		GetDlgItem(IDC_STATIC_PRODUCT)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_COMPANY)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_TEL)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_PROPUCT)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_TELNUM)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_CMPY)->ShowWindow(SW_HIDE);	
 	}
 	else
 	{
 		GetDlgItem(IDC_STATIC_PRODUCT)->ShowWindow(SW_SHOW);
 		GetDlgItem(IDC_STATIC_COMPANY)->ShowWindow(SW_SHOW);
 		GetDlgItem(IDC_STATIC_TEL)->ShowWindow(SW_SHOW);
 		GetDlgItem(IDC_STATIC_PROPUCT)->ShowWindow(SW_SHOW);
 		GetDlgItem(IDC_STATIC_TELNUM)->ShowWindow(SW_SHOW);
 		GetDlgItem(IDC_STATIC_CMPY)->ShowWindow(SW_SHOW);
 	}
 
 	if ( pSysinfo->uiDeviceRunTime )
 	{
 		unsigned int nMin = 0,nHour = 0, nDay = 0;
 		nMin = pSysinfo->uiDeviceRunTime;   //以分为单位//20120711 duchangjiang 		
 		if ( nMin >=60)
 		{
 			nHour = nMin / 60;
 			nMin = nMin % 60;
 			if ( nHour > 0)
 			{
 				nDay = nHour / 24;
 				nHour = nHour % 24;
 			}
 		}
 
 		CString str = _T("");
 		if ( nDay )
 		{
 			CString strDay = _T("");
 			strDay = _CS(_T("Vesion.Day"));
 			str.Format(_T("%d %s %d:%d"), nDay, strDay,nHour, nMin );
 		}else
 		{
 			str.Format(_T("%d:%d"), nHour, nMin);
 		}
 		GetDlgItem(IDC_STATIC_RUN2)->SetWindowText(str);
 		GetDlgItem(IDC_STATIC_RUNTIME2)->ShowWindow(SW_SHOW);
 		GetDlgItem(IDC_STATIC_RUN2)->ShowWindow(SW_SHOW);
 	}else
 	{
 		GetDlgItem(IDC_STATIC_RUNTIME2)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_RUN2)->ShowWindow(SW_HIDE);
 	}
 
 	int index=0;
 	int i=0;
 	for(;i<m_strVersion.GetLength();i++)//根据版本新，第4个‘.’后面的第一个字符为‘1’就开启
 	{
 		if(m_strVersion[i]=='.')
 		{
 			index++;
 			if(index==4)
 			{
 				break;
 			}
 		}		
 	}	
 
 	if(index==4&&m_strVersion[i+1]=='1')	
 	{		
 			SDK_NatStatusInfo natInfo;
			int nWaitTime = 1000;
			DWORD dwRetlen = 0;
			bool bSuccess = H264_DVR_GetDevConfig(loginID,E_SDK_CONFIG_NAT_STATUS_INFO,-1,(char*)&natInfo
			,sizeof(SDK_NatStatusInfo),&dwRetlen,nWaitTime);
 			m_strInfo=natInfo.NatInfoCode;
 			GetDlgItem(IDC_STATIC_NAT_INFO)->ShowWindow(SW_SHOW);
 			GetDlgItem(IDC_STATIC_NAT_INFO2)->ShowWindow(SW_SHOW);
 
 			switch(natInfo.iNatStatus)
 			{
 			case SDK_NAT_STATUS_DISENABLE:
 				{
 					m_strStatu=_CS("NATSTR.DISENABLE");
 					break;
 				}
 			case SDK_NAT_STATUS_PROBING:
 				{
 					m_strStatu=_CS("NATSTR.PROBING");
 					break;
 				}
 			case SDK_NAT_STATUS_CONNECTING:
 				{
 					m_strStatu=_CS("NATSTR.CONNECTING");
 					break;
 				}
 			case SDK_NAT_STATUS_CONNECTED:
 				{
 					m_strStatu=_CS("NATSTR.CONNECTED");
 					break;
 				}
 			}
 			GetDlgItem(IDC_STATIC_NAT_INFO)->ShowWindow(SW_SHOW);
 			GetDlgItem(IDC_STATIC_NAT_INFO2)->ShowWindow(SW_SHOW);
 			GetDlgItem(IDC_STATIC_NAT_STATU)->ShowWindow(SW_SHOW);
 			GetDlgItem(IDC_STATIC_NAT_STATU2)->ShowWindow(SW_SHOW);
 
 	}
 	else
 	{
 	
 		GetDlgItem(IDC_STATIC_NAT_STATU)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_NAT_STATU2)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_NAT_INFO)->ShowWindow(SW_HIDE);
 		GetDlgItem(IDC_STATIC_NAT_INFO2)->ShowWindow(SW_HIDE);
 		
 	}
 
 		GetDlgItem(IDC_STATIC_SERIALSID)->ShowWindow(SW_SHOW);		
 		m_strSerialID=pSysinfo->sSerialNumber;
	UpdateData(FALSE);
}