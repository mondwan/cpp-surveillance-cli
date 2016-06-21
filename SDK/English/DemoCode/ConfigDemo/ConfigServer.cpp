// ConfigServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigServer.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigServer dialog


CConfigServer::CConfigServer(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigServer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigServer)
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_SelectLanguage);
	DDX_Control(pDX, IDC_COMBO_TIMEFMT, m_ctlTimeFormat);
	DDX_Control(pDX, IDC_COMBO_DATESPR, m_ctlDateSpr);
	DDX_Control(pDX, IDC_COMBO_DATEFMT, m_ctlDateFormat);
	DDX_Control(pDX, IDC_COMBO_VIDEOFMT, m_ctlVideoFormat);
	DDX_Control(pDX, IDC_COMBO_OVERWRITE, m_ctlDiskFull);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigServer, CDialog)
	//{{AFX_MSG_MAP(CConfigServer)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	//}}AFX_MSG_MAP
	//ON_CBN_SELCHANGE(IDC_COMBO_TIMEFMT, &CConfigServer::OnCbnSelchangeComboTimefmt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigServer message handlers

void CConfigServer::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (IsValid())
	{
	DEV_ATTRIBUTE Dev_attribute;
	CString str;
	GetDlgItemText(IDC_EDIT_DEVNAME,str);
	strcpy(Dev_attribute.NormalConfig.sMachineName,str.GetBuffer(0));
	
	Dev_attribute.NormalConfig.iOverWrite = m_ctlDiskFull.GetCurSel();
	Dev_attribute.NormalConfig.iAutoLogout = GetDlgItemInt(IDC_EDIT_STANDBYTIME);
	Dev_attribute.NormalConfig.iDateFormat = m_ctlDateFormat.GetCurSel();
	Dev_attribute.NormalConfig.iTimeFormat = m_ctlTimeFormat.GetCurSel();
	Dev_attribute.NormalConfig.iDateSeparator = m_ctlDateSpr.GetCurSel();
	//Dev_attribute.NormalConfig.iLanguage = m_SelectLanguage.GetCurSel();
	Dev_attribute.NormalConfig.iLocalNo = GetDlgItemInt(IDC_EDIT_DEVNAME);
	Dev_attribute.NormalConfig.iVideoFormat = m_ctlVideoFormat.GetCurSel();
	CString strLang;
	int i = 0;
	int nlanguage = m_SelectLanguage.GetCurSel();
	m_SelectLanguage.GetLBText(nlanguage, strLang);
	for (i = 0; i < sizeof(s_language) / sizeof(ConfigPair); i++)
	{
		CString strTmp("ConfigGeneral.");
		strTmp += s_language[i].name;
		if (0 == strcmp(_CS(strTmp), strLang))
		{
			Dev_attribute.NormalConfig.iLanguage = i;
			break;
		}
	}
	((CClientDemo5Dlg*)AfxGetMainWnd())->SetDeviceConfigInfo(&Dev_attribute);
	}	
}

void CConfigServer::InitComboBox()
{
	m_ctlDiskFull.ResetContent();
	int nIndex = m_ctlDiskFull.AddString(_CS("ConfigGeneral.DiskFullStop"));
	m_ctlDiskFull.SetItemData(nIndex,0);
	nIndex = m_ctlDiskFull.AddString(_CS("ConfigGeneral.DiskFullOverwrite"));
	m_ctlDiskFull.SetItemData(nIndex,1);
	
	m_ctlDateFormat.ResetContent();
	nIndex = m_ctlDateFormat.AddString("YYYY-MM-DD");
	m_ctlDateFormat.SetItemData(nIndex,0);
	nIndex = m_ctlDateFormat.AddString("MM-DD-YYYY");
	m_ctlDateFormat.SetItemData(nIndex,1);
	nIndex = m_ctlDateFormat.AddString("DD-MM-YYYY");
	m_ctlDateFormat.SetItemData(nIndex,2);
	
	m_ctlDateSpr.ResetContent();
	nIndex = m_ctlDateSpr.AddString("\" . \"");
	m_ctlDateSpr.SetItemData(nIndex,0);
	nIndex = m_ctlDateSpr.AddString("\" - \"");
	m_ctlDateSpr.SetItemData(nIndex,1);
	nIndex = m_ctlDateSpr.AddString("\" / \"");
	m_ctlDateSpr.SetItemData(nIndex,2);
	
	m_ctlTimeFormat.ResetContent();
	nIndex = m_ctlTimeFormat.AddString(_CS("ConfigGeneral.Time24"));
	m_ctlTimeFormat.SetItemData(nIndex,0);
	nIndex = m_ctlTimeFormat.AddString(_CS("ConfigGeneral.Time12"));
	m_ctlTimeFormat.SetItemData(nIndex,1);
	
	m_ctlVideoFormat.ResetContent();
	nIndex = m_ctlVideoFormat.AddString("PAL");
	m_ctlVideoFormat.SetItemData(nIndex,0);
	nIndex = m_ctlVideoFormat.AddString("NTSC");
	m_ctlVideoFormat.SetItemData(nIndex,1);

// 	m_SelectLanguage.ResetContent();
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.English"));
// 	m_SelectLanguage.SetItemData(nIndex,0);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.SimpChinese"));
// 	m_SelectLanguage.SetItemData(nIndex,1);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.TradChinese"));
// 	m_SelectLanguage.SetItemData(nIndex,2);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.Italian"));
// 	m_SelectLanguage.SetItemData(nIndex,3);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.Spanish"));
// 	m_SelectLanguage.SetItemData(nIndex,4);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.Japanese"));
// 	m_SelectLanguage.SetItemData(nIndex,5);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.Russian"));
// 	m_SelectLanguage.SetItemData(nIndex,6);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.French"));
// 	m_SelectLanguage.SetItemData(nIndex,7);
// 	nIndex = m_SelectLanguage.AddString(_CS("ConfigGeneral.German"));
// 	m_SelectLanguage.SetItemData(nIndex,8);
}

BOOL CConfigServer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	InitComboBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigServer::InitDlgInfo(DEV_ATTRIBUTE *pDevAttribute,SDK_MultiLangFunction *PLang)
{
	if( pDevAttribute != NULL &&PLang != NULL)
	{
		m_SelectLanguage.ResetContent();

		CString strLang = "English";
		int i = 0;
		for (; i < sizeof(s_language) / sizeof(ConfigPair); i++)
		{
			if (s_language[i].value == pDevAttribute->NormalConfig.iLanguage)
			{
				strLang = s_language[i].name;
				break;
			}
		}
		
		int nindex = 1;
		for (i = 0; i < PLang->nLangNum; i++)
		{
			//判断配置设置的语言设备是否支持
			CString strTmp("ConfigGeneral.");
			strTmp += PLang->vLanguageName[i];
			if ( !strcmp(PLang->vLanguageName[i], strLang.GetBuffer(0)))
			{
				//m_cmbLanguage.SetCurSel(i);
				nindex = i;
			}
			m_SelectLanguage.AddString(_CS(strTmp));
		}
		m_SelectLanguage.SetCurSel(nindex);

		CString str;

		str = (LPCSTR)(LPSTR)pDevAttribute->deviveInfo.sSerialNumber;
		SetDlgItemText(IDC_EDIT_SERIALNO , str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.byChanNum);
		SetDlgItemText(IDC_EDIT_VIDEOINNUM,str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.iVideoOutChannel);
		SetDlgItemText(IDC_EDIT_VIDEOOUTNUM,str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.iAudioInChannel);
		SetDlgItemText(IDC_EDIT_AUDIONUM,str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.byAlarmInPortNum);
		SetDlgItemText(IDC_EDIT_ALARMIN,str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.byAlarmOutPortNum);
		SetDlgItemText(IDC_EDIT_ALARMOUT,str);
		
		str.Format(_T("%d"),pDevAttribute->deviveInfo.iTalkInChannel);
		SetDlgItemText(IDC_EDIT_TALKIN,str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.iTalkOutChannel);
		SetDlgItemText(IDC_EDIT_TALKOUT,str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.iDigChannel);
		SetDlgItemText(IDC_EDIT_DIGITALCHANNEL,str);

		str = (LPCSTR)(LPSTR)pDevAttribute->deviveInfo.sSoftWareVersion;
		SetDlgItemText(IDC_EDIT_SOFTWAREVERSION,str);
		
		if ( pDevAttribute->deviveInfo.uiDeviceRunTime )
		{
			unsigned int nMin = 0, nSec = 0, nHour = 0, nDay = 0;
			nSec = pDevAttribute->deviveInfo.uiDeviceRunTime % 60;  //以秒为单位
			nMin = pDevAttribute->deviveInfo.uiDeviceRunTime / 60;
			if ( nMin > 0)
			{
				nHour = nMin / 60;
				nMin = nMin % 60;
				if ( nHour > 0)
				{
					nDay = nHour / 24;
					nHour = nHour % 24;
				}
			}
			//CString str;
			if ( nDay )
			{
				CString strDay = _T("");
				strDay = _CS(_T("Vesion.Day"));
				str.Format(_T("%d%s %d:%d:%d"), nDay, strDay,nHour, nMin, nSec );
			}else
			{
				str.Format(_T("%d:%d:%d"), nHour, nMin, nSec );
			}
			GetDlgItem(IDC_EDIT_RUNTIME)->SetWindowText(str);
			GetDlgItem(IDC_STATIC_RUNTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_RUNTIME)->ShowWindow(SW_SHOW);
		}else
		{
			GetDlgItem(IDC_STATIC_RUNTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_RUNTIME)->ShowWindow(SW_HIDE);
		}

		str.Format(_T("%d.%d.%d  %d:%d:%d"),pDevAttribute->deviveInfo.tmBuildTime.year,pDevAttribute->deviveInfo.tmBuildTime.month,
			pDevAttribute->deviveInfo.tmBuildTime.day,pDevAttribute->deviveInfo.tmBuildTime.hour,pDevAttribute->deviveInfo.tmBuildTime.minute,
			pDevAttribute->deviveInfo.tmBuildTime.second);
		SetDlgItemText(IDC_EDIT_BUILTTIME,str);

		str.Format(_T("%d"),pDevAttribute->deviveInfo.iExtraChannel);
		SetDlgItemText(IDC_EDIT_EXTRACHANNEL,str);

		str.Format(_T("%d"),pDevAttribute->NormalConfig.iLocalNo);
		SetDlgItemText(IDC_EDIT_DEVNO,str);

		SetDlgItemInt(IDC_EDIT_STANDBYTIME,pDevAttribute->NormalConfig.iAutoLogout);
		
		m_ctlDiskFull.SetCurSel(pDevAttribute->NormalConfig.iOverWrite);
		m_ctlVideoFormat.SetCurSel(pDevAttribute->NormalConfig.iVideoFormat);
		m_ctlDateFormat.SetCurSel(pDevAttribute->NormalConfig.iDateFormat);
		m_ctlDateSpr.SetCurSel(pDevAttribute->NormalConfig.iDateSeparator);
		m_ctlTimeFormat.SetCurSel(pDevAttribute->NormalConfig.iTimeFormat);		

		str = pDevAttribute->NormalConfig.sMachineName;
		SetDlgItemText(IDC_EDIT_DEVNAME,str);

		//m_SelectLanguage.SetCurSel(pDevAttribute->NormalConfig.iLanguage);

	
	}
}

BOOL CConfigServer::IsValid()
{
	BOOL bValid = FALSE;
	int nIndex = m_ctlDiskFull.GetCurSel();
	if(CB_ERR != nIndex)
	{
		nIndex = m_ctlDateFormat.GetCurSel();
		if(CB_ERR != nIndex)
		{
			nIndex = m_ctlDateSpr.GetCurSel();
			if(CB_ERR != nIndex)
			{
				nIndex = m_ctlTimeFormat.GetCurSel();
				if(CB_ERR != nIndex)
				{
					bValid = TRUE;
				}
			}
		}
	}
	
	return bValid;
}

void CConfigServer::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetDeviceConfigInfo();
}

void CConfigServer::CleanAll()
{
	SetDlgItemText(IDC_EDIT_SERIALNO,"");
	SetDlgItemText(IDC_EDIT_VIDEOINNUM,"");
	SetDlgItemText(IDC_EDIT_VIDEOOUTNUM, "");
	SetDlgItemText(IDC_EDIT_AUDIONUM, "");
	SetDlgItemText(IDC_EDIT_ALARMIN, "");
	SetDlgItemText(IDC_EDIT_ALARMOUT, "");
	SetDlgItemText(IDC_EDIT_TALKIN, "");
	SetDlgItemText(IDC_EDIT_TALKOUT, "");
	SetDlgItemText(IDC_EDIT_EXTRACHANNEL, "");
	SetDlgItemText(IDC_EDIT_SOFTWAREVERSION, "");
	SetDlgItemText(IDC_EDIT_BUILTTIME, "");
	SetDlgItemText(IDC_EDIT_DEVNO, "");
	SetDlgItemText(IDC_EDIT_DIGITALCHANNEL,"");
	m_ctlDiskFull.SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_STANDBYTIME, "");
	m_ctlVideoFormat.SetCurSel(-1);
	m_ctlDateFormat.SetCurSel(-1);
	m_ctlDateSpr.SetCurSel(-1);
	m_ctlTimeFormat.SetCurSel(-1);
	SetDlgItemText(IDC_EDIT_DEVNAME, "");
	m_SelectLanguage.SetCurSel(-1);
}

// void CConfigServer::OnCbnSelchangeComboLanguage()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// }
