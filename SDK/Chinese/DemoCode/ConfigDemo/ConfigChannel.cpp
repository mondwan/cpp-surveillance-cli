// ConfigChannel.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigChannel.h"

#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  IFRAME_EQ_PFRAME 10
#define BITMSK(bit)				(int)(1 << (bit))

/////////////////////////////////////////////////////////////////////////////
// CConfigChannel dialog
// #ifndef OEM_RAYSHARP
// static int STREAM_CODE_VALUE[MAX_RESOLUTION_NUM][6] = {
// 	{512, 768, 1024, 1536, 2048, 2560},	///< D1
// 	{384, 512, 768, 1024, 1536, 2048},	///< HD1
// 	{384, 512, 768, 1024, 1536, 2048},	///< BCIF
// 	{64, 192, 384, 512, 768, 1024},		///< CIF
// 	{64, 128, 192, 384,  448,  512},	///< QCIF
// 	{512, 768, 896, 1280, 1536, 2048},	///< VGA
// 	{256, 384, 512, 640, 768, 1024},	///< QVGA
// 	{512, 768, 896, 1280, 1536, 2048},	///< SVCD
// 	{64, 128, 192, 384,  448,  512},	///< QQVGA
// };
// #else
// static int STREAM_CODE_VALUE[MAX_RESOLUTION_NUM][6] = {
// 	{512, 768, 1024, 1536, 2048, 3072},	///< D1
// 	{384, 512, 768, 1024, 1536, 2048},	///< HD1
// 	{384, 512, 768, 1024, 1536, 2048},	///< BCIF
// 	{64, 192, 384, 512, 768, 1024},		///< CIF
// 	{64, 128, 192, 384,  448,  512},	///< QCIF
// 	{512, 768, 896, 1280, 1536, 2048},	///< VGA
// 	{256, 384, 512, 640, 768, 1024},	///< QVGA
// 	{512, 768, 896, 1280, 1536, 2048},	///< SVCD
// 	{64, 128, 192, 384,  448,  512},	///< QQVGA
// };
// #endif
// static int STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_NR][6] = {
// 	{512, 768, 1024, 1536, 2048, 3072},	///< D1
// 	{384, 512, 768, 1024, 1536, 2048},	///< HD1
// 	{384, 512, 768, 1024, 1536, 2048},	///< BCIF
// 	{64, 192, 384, 512, 768, 1024},		///< CIF
// 	{64, 128, 192, 384,  448,  512},	///< QCIF
// 	{512, 768, 896, 1280, 1536, 2048},	///< VGA
// 	{256, 384, 512, 640, 768, 1024},	///< QVGA
// 	{512, 768, 896, 1280, 1536, 2048},	///< SVCD
// 	{64, 128, 192, 384,  448,  512},	///< QQVGA
// 	{64, 128, 256, 448, 512, 768},	///< ND1
// 	{896, 1024, 1536,  2048, 3072, 4096},	///< 650TVL
// 	{1024,1536, 2048, 2560, 3072, 4096},	///< 720P
// 	{1024,1536, 2048, 3072, 4096, 5120},	///< 1_3M
// 	{1024,2048, 3072, 4096, 6144, 8192},	///< UXGA
// 	{1024,2048, 3072, 4096, 6144, 8192}, ///< 1080P
// 	{1177,2355, 3532, 4710, 7065, 10240}, ///< WUXGA
// 	{1280,2560, 3840, 5120, 7680, 10240}, ///< 2_5M
// 	{1536, 3072, 4096, 6144, 8192, 10240}, ///< 3M
// 	{2048, 3072, 4096, 6144, 8192,10240} ///5M
// };
static int STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_NR][6] = {
	{512, 768, 1024, 1536, 2048, 2560},	///< D1
	{384, 512, 768, 1024, 1536, 2048},	///< HD1
	{384, 512, 768, 1024, 1536, 2048},	///< BCIF
	{64, 192, 384, 512, 768, 1024},		///< CIF
	{64, 128, 192, 384,  448,  512},	///< QCIF
	{512, 768, 896, 1280, 1536, 2048},	///< VGA
	{256, 384, 512, 640, 768, 1024},	///< QVGA
	{512, 768, 896, 1280, 1536, 2048},	///< SVCD
	{64, 128, 192, 384,  448,  512},	///< QQVGA
	{64, 128, 256, 448, 512, 768},	///< ND1
	{896, 1024, 1536,  2048, 3072, 4096},	///< 650TVL
	{1024,1536, 2048, 2560, 3072, 4096},	///< 720P
	{1024,1536, 2048, 3072, 4096, 5120},	///< 1_3M
	{1024,2048, 3072, 4096, 6144, 8192},	///< UXGA
	{1024,2048, 3072, 4096, 6144, 8192}, ///< 1080P
	{1177,2355, 3532, 4710, 7065, 10240}, ///< WUXGA
	{1280,2560, 3840, 5120, 7680, 10240}, ///< 2_5M
	{1536, 3072, 4096, 6144, 8192, 10240}, ///< 3M
	{2048, 3072, 4096, 6144, 8192,10240} ///5M
};

enum
{
	    MAIN_STREAM = 0,
		EXPAND_STREAM,
		COMBINE_STREAM,
		STREAM_NUM,
};
enum
{
	CONTROL_RESOLUTION,
		CONTROL_FRAME,
		CONTROL_BITCONTROL,
		CONTROL_QUALITY,
		CONTROL_BIT_RATE,
		CONTROL_GOP,
		CONTROL_VIDEO,
		CONTROL_AUDIO,
		CONTROL_NUM,
};
DWORD ControlID[STREAM_NUM][CONTROL_NUM] =
{
	{IDC_COMBO_RESOLUTION, IDC_COMBO_FRAME, IDC_COMBO_BITCONTROL, IDC_COMBO_QUALITY,
		IDC_COMBO_BIT_RATE, IDC_COMBO_GOP, IDC_CHECK_MAIN_VIDEO, IDC_CHECK_MAIN_AUDIO},
	{IDC_COMBO_EXPAND_RESOLUTION, IDC_COMBO_EXPAND_FRAME, IDC_COMBO_EXPAND_BITCONTROL, IDC_COMBO_EXPAND_QUALITY,
	IDC_COMBO_EXPAND_BIT_RATE, IDC_COMBO_EXPAND_GOP, IDC_CHECK_EXPAND_VIDEO, IDC_CHECK_EXPAND_AUDIO},
	{IDC_COMBO_EXPAND_RESOLUTION, IDC_COMBO_EXPAND_FRAME, IDC_COMBO_EXPAND_BITCONTROL, IDC_COMBO_EXPAND_QUALITY,
	IDC_COMBO_EXPAND_BIT_RATE, IDC_COMBO_EXPAND_GOP, IDC_CHECK_COMBINE_ENCODE, IDC_CHECK_EXPAND_AUDIO},
};

CConfigChannel::CConfigChannel(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigChannel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigChannel)
	//}}AFX_DATA_INIT
}


void CConfigChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigChannel)
	DDX_Control(pDX, IDC_COMBO_EncodeStaticParamMain, m_combEncodeStaticParam);
	DDX_Control(pDX, IDC_COMBO_BIT_RATE, m_ctlBitRate);
	DDX_Control(pDX, IDC_COMBO_GOP, m_ctlGop);
	DDX_Control(pDX, IDC_COMBO_EXPAND_GOP, m_ctlExpandGop);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_ctlQuality);
	DDX_Control(pDX, IDC_COMBO_EXPAND_QUALITY, m_ctlExpandQuality);
	DDX_Control(pDX, IDC_COMBO_EXPAND_BITCONTROL, m_ctlExpandBitControl);
	DDX_Control(pDX, IDC_COMBO_BITCONTROL, m_ctlBitControl);
	DDX_Control(pDX, IDC_COMBO_CHANNO, m_ChanNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigChannel, CDialog)
	//{{AFX_MSG_MAP(CConfigChannel)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNO, OnSelchangeComboChanno)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, OnSelchangeComboResolution)
	ON_CBN_SELCHANGE(IDC_COMBO_BITCONTROL, OnSelchangeComboBitcontrol)
	ON_CBN_SELCHANGE(IDC_COMBO_QUALITY, OnSelchangeComboQuality)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAME, OnSelchangeComboFrame)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPAND_BITCONTROL, OnSelchangeComboExpandBitcontrol)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPAND_BIT_RATE, OnSelchangeComboExpandBitRate)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPAND_RESOLUTION, OnSelchangeComboExpandResolution)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPAND_QUALITY, OnSelchangeComboExpandQuality)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPAND_FRAME, OnSelchangeComboExpandFrame)
	ON_BN_CLICKED(IDC_CHECK_EXPAND_VIDEO, OnCheckExpandVideo)
	ON_BN_CLICKED(IDC_CHECK_MAIN_AUDIO, OnCheckMainAudio)
	ON_BN_CLICKED(IDC_CHECK_EXPAND_AUDIO, OnCheckExpandAudio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigChannel message handlers

void CConfigChannel::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (WinToStruct() && m_ChanNo.GetCurSel() != -1)
	{	if(m_combEncodeStaticParam.IsWindowVisible())
	{
		UpdateData(FALSE);
		m_EncodeStaticParamAll.EncodeStaticParamAll[0].profile=m_combEncodeStaticParam.GetCurSel()+1;
		m_EncodeStaticParamAll.EncodeStaticParamAll[0].level=m_combEncodeStaticParam.GetItemData(m_combEncodeStaticParam.GetCurSel());
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetChannelConfigInfo(&m_EncodeConfig,&m_CmbEncodeCfg,&m_CmbEncodeMode,&m_EncodeStaticParamAll);
	}
	else
	{
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetChannelConfigInfo(&m_EncodeConfig,&m_CmbEncodeCfg,&m_CmbEncodeMode,NULL);
	}
}
}
BOOL CConfigChannel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_nResolution = 0;
	m_niQuality = 0;
	m_nLastChannelNum = 0;
	m_nLastResolutionExtra = 0;
	m_bCombineEncode = false;
	m_bCombineSet = false;
	m_mapCaptureComp[SDK_CAPTURE_COMP_DIVX_MPEG4] = "DIVX MPEG4";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MS_MPEG4] = "MS MPEG4";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MPEG2] = "MPEG2";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MPEG1] = "MPEG1";
	m_mapCaptureComp[SDK_CAPTURE_COMP_H263] = "H.263";
	m_mapCaptureComp[SDK_CAPTURE_COMP_MJPG] = "MJPG";
	m_mapCaptureComp[SDK_CAPTURE_COMP_FCC_MPEG4] = "FCC MPEG4";
	m_mapCaptureComp[SDK_CAPTURE_COMP_H264] = "H.264";

	GetDlgItem(IDC_STATIC_COMBINE_ENCODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK_COMBINE_ENCODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_COMBINEMODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COMBINE_MODE)->ShowWindow(SW_HIDE);
	InitResData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigChannel::InitCombo()
{
	int nIndex = 0;	
	m_ChanNo.ResetContent();
	int i = 0;
	for(;i < m_nChannelNum;i++)
	{
		CString str;
		str.Format(_T("%d"),i+1);
		nIndex = m_ChanNo.AddString(str);
		m_ChanNo.SetItemData(nIndex,i);
	}
	nIndex = m_ChanNo.AddString(_CS("OneClick.All"));
	m_ChanNo.SetItemData(nIndex,m_nChannelNum);
	
	if (m_nChannelNum > 0)
	{
		m_ChanNo.SetCurSel(0);
		m_nLastChannelNum = 0;
	}else
	{
		return;
	}
	CString strTextBitControl[] = {"ConfigEncode.CBR", "ConfigEncode.VBR"};
	m_ctlBitControl.ResetContent();
	for ( i = 0; i< 2;i++)
	{
		nIndex = m_ctlBitControl.AddString(_CS(strTextBitControl[i]));
		m_ctlBitControl.SetItemData(nIndex,i);
	}
	m_ctlExpandBitControl.ResetContent();
	for (i = 0; i < 2;i++)
	{
		nIndex = m_ctlExpandBitControl.AddString(_CS(strTextBitControl[i]));
		m_ctlExpandBitControl.SetItemData(nIndex,i);
	}

#ifdef OEM_RAYSHARP
	GetDlgItem(IDC_COMBO_GOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_EXPAND_GOP)->ShowWindow(SW_HIDE);
#endif

	CString strQuality[] = {"ConfigEncode.Worst", "ConfigEncode.Worse", "ConfigEncode.General", 
		"ConfigEncode.Good", "ConfigEncode.Better", "ConfigEncode.Best"};
	m_ctlQuality.ResetContent();
	for (i = 0;i < 6;i++)
	{
		nIndex = m_ctlQuality.AddString(_CS(strQuality[i]));
		m_ctlQuality.SetItemData(nIndex,i+1);
	}
	m_ctlExpandQuality.ResetContent();
	for ( i = 0;i < 6;i++ )
	{
		nIndex = m_ctlExpandQuality.AddString(_CS(strQuality[i]));
		m_ctlExpandQuality.SetItemData(nIndex,i+1);
	}

	m_ctlGop.ResetContent();
	for ( i = 0;i < 11;i++)
	{
		CString str;
		str.Format(_T("%d"),i+2);
		nIndex = m_ctlGop.AddString(str);
		m_ctlGop.SetItemData(nIndex,i+2);
	}
	m_ctlExpandGop.ResetContent();
	for ( i = 0 ;i < 11;i++)
	{
		CString str;
		str.Format(_T("%d"),i+2);
		nIndex = m_ctlExpandGop.AddString(str);
		m_ctlExpandGop.SetItemData(nIndex,i+2);
	}
}

void CConfigChannel::InitDlgInfo(int ChannnelNum,SDK_EncodeConfigAll_SIMPLIIFY *pEncodeSimpl,
								 SDK_CONFIG_NORMAL *pNormalCfg,CONFIG_EncodeAbility *pEncodeAbility,
								 SDK_CombineEncodeConfigAll *pCmbEncode,SDK_SystemFunction *pSysFunc,
								 DEV_ATTRIBUTE *pDevAttribute,SDK_CombEncodeModeAll *pCmbEncodeMode,
								 SDK_EncodeStaticParamAll *pEncodeStatic)
{
	m_nVideoStandard = pNormalCfg->iVideoFormat;
	m_nChannelNum = ChannnelNum;
	InitCombo();
	m_ChanNo.SetCurSel(0);
	memcpy(&m_EncodeConfig,pEncodeSimpl,sizeof(SDK_EncodeConfigAll_SIMPLIIFY));
	if (pEncodeAbility->iMaxBps == 0)
	{
		m_pEncodeAbility.iMaxBps = 24 * 1024;
	}
	memcpy(&m_pEncodeAbility,pEncodeAbility,sizeof(CONFIG_EncodeAbility));
	memcpy(&m_CmbEncodeCfg,pCmbEncode,sizeof(SDK_CombineEncodeConfigAll));
	memcpy(&m_CmbEncodeMode,pCmbEncodeMode,sizeof(SDK_CombEncodeModeAll));
	memcpy(&m_DevAttribute,pDevAttribute,sizeof(DEV_ATTRIBUTE));
	strcpy(m_cVersion,pDevAttribute->deviveInfo.sSoftWareVersion);
	m_nAudioInNum = pDevAttribute->deviveInfo.iAudioInChannel;
	InitResData();
	memcpy(&m_SysFunc,pSysFunc,sizeof(SDK_SystemFunction));
	m_bMultiStream = pSysFunc->vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM];
	if (m_bMultiStream)
	{
		GetDlgItem(IDC_CHECK_EXPAND_VIDEO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_EXPAND_AUDIO)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_CHECK_EXPAND_VIDEO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_EXPAND_AUDIO)->ShowWindow(SW_HIDE);
	}
	
	if (strcmp(m_cVersion,"V1.22.R03") >= 0 && pSysFunc->vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM])
	{
		GetDlgItem(IDC_CHECK_COMBINE_ENCODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_COMBINE_ENCODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_EXPAND)->ShowWindow(SW_HIDE);
		m_bCombineEncode = true;
		if (strcmp(m_cVersion, "V1.24.R03") >= 0)
		{
			m_bCombineSet = true;
			GetDlgItem(IDC_COMBO_EXPAND_RESOLUTION)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_EXPAND_FRAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_EXPAND_BITCONTROL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_EXPAND_QUALITY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_EXPAND_BIT_RATE)->ShowWindow(SW_SHOW);
#ifndef OEM_RAYSHARP
			GetDlgItem(IDC_COMBO_EXPAND_GOP)->ShowWindow(SW_SHOW);
#endif
			
			GetDlgItem(IDC_COMBO_COMBINEMODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_COMBINE_MODE)->ShowWindow(SW_SHOW);
		}
		else
		{
			m_bCombineSet = false;
			GetDlgItem(IDC_COMBO_EXPAND_RESOLUTION)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_EXPAND_FRAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_EXPAND_BITCONTROL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_EXPAND_QUALITY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_EXPAND_BIT_RATE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_EXPAND_GOP)->ShowWindow(SW_HIDE);
			
			GetDlgItem(IDC_COMBO_COMBINEMODE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_COMBINE_MODE)->ShowWindow(SW_HIDE);
			}
	}else
	{
		GetDlgItem(IDC_CHECK_COMBINE_ENCODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COMBINE_ENCODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_COMBINEMODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COMBINE_MODE)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_COMBO_EXPAND)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_EXPAND_RESOLUTION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_EXPAND_FRAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_EXPAND_BITCONTROL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_EXPAND_QUALITY)->ShowWindow(SW_SHOW);			
		GetDlgItem(IDC_COMBO_EXPAND_BIT_RATE)->ShowWindow(SW_SHOW);
#ifndef OEM_RAYSHARP
		GetDlgItem(IDC_COMBO_EXPAND_GOP)->ShowWindow(SW_SHOW);
#endif
		m_bCombineEncode = false;
		m_bCombineSet = false;
		}	
	//¾²Ì¬±àÂë
	if (pEncodeStatic)
	{
		m_combEncodeStaticParam.ResetContent();					
		m_combEncodeStaticParam.ShowWindow(SW_SHOW);					
		GetDlgItem(IDC_STATIC_EncodeParam)->ShowWindow(SW_SHOW);

		int retIndex=m_combEncodeStaticParam.AddString("baseline");
		m_combEncodeStaticParam.SetItemData(retIndex,51);
		retIndex=m_combEncodeStaticParam.AddString("main profile");
		m_combEncodeStaticParam.SetItemData(retIndex,41);
		retIndex=m_combEncodeStaticParam.AddString("high profile");
		m_combEncodeStaticParam.SetItemData(retIndex,40);								
		
		m_combEncodeStaticParam.SetCurSel(pEncodeStatic->EncodeStaticParamAll[0].profile-1);
	}
	GetDlgItem(IDC_CHECK_MAIN_VIDEO)->EnableWindow(FALSE);
	StructToWin();
}


void CConfigChannel::OnSelchangeComboChanno() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	
	if ( nChannelNum == m_DevAttribute.deviveInfo.byChanNum )
	{
		memcpy(&m_allData, & m_EncodeConfig.vEncodeConfigAll[0], sizeof(SDK_CONFIG_ENCODE));
		
		AllStructToWinData(0, &m_allData, MAIN_STREAM);
		AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		m_nLastChannelNum = nChannelNum;
	}
	else if (m_nLastChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		AllWinDataToStruct(0);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		m_nLastChannelNum = nChannelNum;
	}
	else
	{
		if (nChannelNum != m_nLastChannelNum)
		{
			NomalWinDataToStruct(m_nLastChannelNum);
			NormalStructToWinData(nChannelNum,  &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
			NormalStructToWinData(nChannelNum,  &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
			m_nLastChannelNum = nChannelNum;
		}
	}
	
	if (m_nAudioInNum != m_DevAttribute.deviveInfo.byChanNum)
	{
		GetDlgItem(IDC_CHECK_MAIN_AUDIO)->ShowWindow(nChannelNum < m_nAudioInNum);
		if (m_bMultiStream)
		{
			GetDlgItem(IDC_CHECK_EXPAND_AUDIO)->ShowWindow(nChannelNum < m_nAudioInNum);
		}
	}
	if (m_bCombineEncode)
	{
		GetDlgItem(IDC_CHECK_EXPAND_AUDIO)->ShowWindow(FALSE);
	}
	Invalidate();
}

void CConfigChannel::CleanAll()
{
	for (int i =0; i < STREAM_NUM ;i++)
	{
		CComboBox *pComboBox = (CComboBox *)GetDlgItem(ControlID[i][CONTROL_RESOLUTION]);
		if (pComboBox !=NULL)
		{
			pComboBox->ResetContent();
			pComboBox = NULL;
		}
		pComboBox = (CComboBox *)GetDlgItem(ControlID[i][CONTROL_FRAME]);
		if (pComboBox !=NULL)
		{
			pComboBox->ResetContent();
			pComboBox = NULL;
		}
		pComboBox = (CComboBox *)GetDlgItem(ControlID[i][CONTROL_BITCONTROL]);
		if (pComboBox !=NULL)
		{
			pComboBox->ResetContent();
			pComboBox = NULL;
		}
		pComboBox = (CComboBox *)GetDlgItem(ControlID[i][CONTROL_QUALITY]);
		if (pComboBox !=NULL)
		{
			pComboBox->ResetContent();
			pComboBox = NULL;
		}
		pComboBox = (CComboBox *)GetDlgItem(ControlID[i][CONTROL_BIT_RATE]);
		if (pComboBox !=NULL)
		{
			pComboBox->ResetContent();
			pComboBox = NULL;
		}
		pComboBox = (CComboBox *)GetDlgItem(ControlID[i][CONTROL_GOP]);
		if (pComboBox !=NULL)
		{
			pComboBox->ResetContent();
			pComboBox = NULL;
		}
		CButton * pButton = (CButton *)GetDlgItem(ControlID[i][CONTROL_VIDEO]);
		if (pButton !=NULL)
		{
			pButton->SetCheck(FALSE);
			pButton = NULL;
		}
		pButton = (CButton *)GetDlgItem(ControlID[i][CONTROL_AUDIO]);
		if (pButton !=NULL)
		{
			pButton->SetCheck(FALSE);
			pButton = NULL;
		}
	}
	m_ChanNo.ResetContent();
	((CComboBox *)GetDlgItem(IDC_COMBO_CODE_FORMAT))->ResetContent();
	((CComboBox *)GetDlgItem(IDC_COMBO_EXPAND))->ResetContent();
}

void CConfigChannel::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetChannelConfigInfo();
}

void CConfigChannel::InitResData()
{
	if( m_nVideoStandard == 0 )  //PAL
	{
		m_resolution[SDK_CAPTURE_SIZE_D1].strText =  "D1(704x576)";
		//m_resolution[SDK_CAPTURE_SIZE_HD1].strText = "HD1(352x576)";
		m_resolution[SDK_CAPTURE_SIZE_HD1].strText = "HD1(704x288)";
		//m_resolution[SDK_CAPTURE_SIZE_BCIF].strText = "BCIF(704x288)";
		m_resolution[SDK_CAPTURE_SIZE_BCIF].strText = "BCIF(352x576)";
		m_resolution[SDK_CAPTURE_SIZE_CIF].strText = "CIF(352x288)";
		m_resolution[SDK_CAPTURE_SIZE_QCIF].strText = "QCIF(176x144)";
		m_resolution[SDK_CAPTURE_SIZE_VGA].strText = "VGA(640x480)";
		m_resolution[SDK_CAPTURE_SIZE_QVGA].strText = "QVGA(320x240)";
		m_resolution[SDK_CAPTURE_SIZE_SVCD].strText = "SVCD(480x480)";
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].strText = "QQVGA(160x128)";
		
		m_resolution[SDK_CAPTURE_SIZE_D1].dwSize = 704 * 576;
		//m_resolution[SDK_CAPTURE_SIZE_HD1].dwSize = 352 * 576;
		m_resolution[SDK_CAPTURE_SIZE_HD1].dwSize = 704 * 288;
		//m_resolution[SDK_CAPTURE_SIZE_BCIF].dwSize = 704 * 288;
		m_resolution[SDK_CAPTURE_SIZE_BCIF].dwSize = 352 * 576;
		m_resolution[SDK_CAPTURE_SIZE_CIF].dwSize = 352 * 288;
		m_resolution[SDK_CAPTURE_SIZE_QCIF].dwSize = 176 * 144;
		m_resolution[SDK_CAPTURE_SIZE_VGA].dwSize = 640 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QVGA].dwSize = 320 * 240;
		m_resolution[SDK_CAPTURE_SIZE_SVCD].dwSize = 480 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].dwSize = 160 * 128;
		
// 		m_resolution[SDK_CAPTURE_SIZE_ND1].strText =  "ND1(240*192)";
// 		m_resolution[SDK_CAPTURE_SIZE_650TVL].strText = "960H(960*576)";
// 		m_resolution[SDK_CAPTURE_SIZE_720P].strText = "720(1280*720)";
// 		m_resolution[SDK_CAPTURE_SIZE_1_3M].strText = "1.3M(1280*960)";
// 		m_resolution[SDK_CAPTURE_SIZE_UXGA].strText = "UXGA(1600*1200)";
// 		m_resolution[SDK_CAPTURE_SIZE_1080P].strText = "1080P(1920*1080)";
// 		m_resolution[SDK_CAPTURE_SIZE_WUXGA].strText = "WUXGA(1920*1200)";
// 		m_resolution[SDK_CAPTURE_SIZE_2_5M].strText = "2.5M(1872*1408)";
// 		m_resolution[SDK_CAPTURE_SIZE_3M].strText = "3M(2048*1536)";
// 		m_resolution[SDK_CAPTURE_SIZE_5M].strText = "5M(3744*1408)";
		m_resolution[SDK_CAPTURE_SIZE_ND1].strText =  "ND1(240x192)";
		m_resolution[SDK_CAPTURE_SIZE_650TVL].strText = "960H(960x576)";
		m_resolution[SDK_CAPTURE_SIZE_720P].strText = "720(1280x720)";
		m_resolution[SDK_CAPTURE_SIZE_1_3M].strText = "1.3M(1280x960)";
		m_resolution[SDK_CAPTURE_SIZE_UXGA].strText = "UXGA(1600x1200)";
		m_resolution[SDK_CAPTURE_SIZE_1080P].strText = "1080P(1920x1080)";
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].strText = "WUXGA(1920x1200)";
		m_resolution[SDK_CAPTURE_SIZE_2_5M].strText = "2.5M(1872x1408)";
		m_resolution[SDK_CAPTURE_SIZE_3M].strText = "3M(2048x1536)";
		m_resolution[SDK_CAPTURE_SIZE_5M].strText = "5M(2592x1944)";
		
		m_resolution[SDK_CAPTURE_SIZE_ND1].dwSize = 240*192;
		m_resolution[SDK_CAPTURE_SIZE_650TVL].dwSize =928*576; //960*576;
		m_resolution[SDK_CAPTURE_SIZE_720P].dwSize = 1280*720;
		m_resolution[SDK_CAPTURE_SIZE_1_3M].dwSize = 1280*960;
		m_resolution[SDK_CAPTURE_SIZE_UXGA].dwSize = 1600*1200;
		m_resolution[SDK_CAPTURE_SIZE_1080P].dwSize = 1920*1080;
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].dwSize = 1920*1200;
		m_resolution[SDK_CAPTURE_SIZE_2_5M].dwSize = 1872*1408;
		m_resolution[SDK_CAPTURE_SIZE_3M].dwSize = 2048*1536;
		m_resolution[SDK_CAPTURE_SIZE_5M].dwSize = 3744*1408;
	}		
	else
	{
		m_resolution[SDK_CAPTURE_SIZE_D1].strText =  "D1(704x480)";
		//m_resolution[SDK_CAPTURE_SIZE_HD1].strText = "HD1(352x480)";
		//m_resolution[SDK_CAPTURE_SIZE_BCIF].strText = "BCIF(704x240)";
		m_resolution[SDK_CAPTURE_SIZE_HD1].strText = "HD1(704x240)";
		m_resolution[SDK_CAPTURE_SIZE_BCIF].strText = "BCIF(352x480)";
		m_resolution[SDK_CAPTURE_SIZE_CIF].strText = "CIF(352x240)";
		m_resolution[SDK_CAPTURE_SIZE_QCIF].strText = "QCIF(176x120)";
		m_resolution[SDK_CAPTURE_SIZE_VGA].strText = "VGA(640x480)";
		m_resolution[SDK_CAPTURE_SIZE_QVGA].strText = "QVGA(320x240)";
		m_resolution[SDK_CAPTURE_SIZE_SVCD].strText = "SVCD(480x480)";
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].strText = "QQVGA(160x128)";
		
		m_resolution[SDK_CAPTURE_SIZE_D1].dwSize = 704 * 480;
		//m_resolution[SDK_CAPTURE_SIZE_HD1].dwSize = 352 * 480;
		//m_resolution[SDK_CAPTURE_SIZE_BCIF].dwSize = 704 * 240;
		m_resolution[SDK_CAPTURE_SIZE_HD1].dwSize = 704 * 240;
		m_resolution[SDK_CAPTURE_SIZE_BCIF].dwSize = 352 * 480;
		m_resolution[SDK_CAPTURE_SIZE_CIF].dwSize = 352 * 240;
		m_resolution[SDK_CAPTURE_SIZE_QCIF].dwSize = 176 * 120;
		m_resolution[SDK_CAPTURE_SIZE_VGA].dwSize = 640 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QVGA].dwSize = 320 * 240;
		m_resolution[SDK_CAPTURE_SIZE_SVCD].dwSize = 480 * 480;
		m_resolution[SDK_CAPTURE_SIZE_QQVGA].dwSize = 160 * 128;
		
		
// 		m_resolution[SDK_CAPTURE_SIZE_ND1].strText =  "ND1(240*192)";
// 		m_resolution[SDK_CAPTURE_SIZE_650TVL].strText = "960H(960*480)";
// 		m_resolution[SDK_CAPTURE_SIZE_720P].strText = "720(1280*720)";
// 		m_resolution[SDK_CAPTURE_SIZE_1_3M].strText = "1.3M(1280*960)";
// 		m_resolution[SDK_CAPTURE_SIZE_UXGA].strText = "UXGA(1600*1200)";
// 		m_resolution[SDK_CAPTURE_SIZE_1080P].strText = "1080P(1920*1080)";
// 		m_resolution[SDK_CAPTURE_SIZE_WUXGA].strText = "WUXGA(1920*1200)";
// 		m_resolution[SDK_CAPTURE_SIZE_2_5M].strText = "2.5M(1872*1408)";
// 		m_resolution[SDK_CAPTURE_SIZE_3M].strText = "3M(2048*1536)";
// 		m_resolution[SDK_CAPTURE_SIZE_5M].strText = "5M(3744*1408)";
		m_resolution[SDK_CAPTURE_SIZE_ND1].strText =  "ND1(240x192)";
		m_resolution[SDK_CAPTURE_SIZE_650TVL].strText = "960H(960x480)";
		m_resolution[SDK_CAPTURE_SIZE_720P].strText = "720(1280x720)";
		m_resolution[SDK_CAPTURE_SIZE_1_3M].strText = "1.3M(1280x960)";
		m_resolution[SDK_CAPTURE_SIZE_UXGA].strText = "UXGA(1600x1200)";
		m_resolution[SDK_CAPTURE_SIZE_1080P].strText = "1080P(1920x1080)";
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].strText = "WUXGA(1920x1200)";
		m_resolution[SDK_CAPTURE_SIZE_2_5M].strText = "2.5M(1872x1408)";
		m_resolution[SDK_CAPTURE_SIZE_3M].strText = "3M(2048x1536)";
		m_resolution[SDK_CAPTURE_SIZE_5M].strText = "5M(2592x1944)";
		
		m_resolution[SDK_CAPTURE_SIZE_ND1].dwSize = 240*192;
		m_resolution[SDK_CAPTURE_SIZE_650TVL].dwSize = 928*480;//960*480;
		m_resolution[SDK_CAPTURE_SIZE_720P].dwSize = 1280*720;
		m_resolution[SDK_CAPTURE_SIZE_1_3M].dwSize = 1280*960;
		m_resolution[SDK_CAPTURE_SIZE_UXGA].dwSize = 1600*1200;
		m_resolution[SDK_CAPTURE_SIZE_1080P].dwSize = 1920*1080;
		m_resolution[SDK_CAPTURE_SIZE_WUXGA].dwSize = 1920*1200;
		m_resolution[SDK_CAPTURE_SIZE_2_5M].dwSize = 1872*1408;
		m_resolution[SDK_CAPTURE_SIZE_3M].dwSize = 2048*1536;
		m_resolution[SDK_CAPTURE_SIZE_5M].dwSize = 3744*1408;
	}
	
	m_resolution[SDK_CAPTURE_SIZE_D1].dsMask = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_HD1].dsMask = BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_BCIF].dsMask = BITMSK(SDK_CAPTURE_SIZE_BCIF) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_CIF].dsMask = BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_QCIF].dsMask = BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_VGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_VGA) | BITMSK(SDK_CAPTURE_SIZE_QVGA);
	m_resolution[SDK_CAPTURE_SIZE_QVGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_QVGA);
	m_resolution[SDK_CAPTURE_SIZE_SVCD].dsMask = BITMSK(SDK_CAPTURE_SIZE_SVCD);
	m_resolution[SDK_CAPTURE_SIZE_QQVGA].dsMask = BITMSK(SDK_CAPTURE_SIZE_QQVGA);
	m_resolution[SDK_CAPTURE_SIZE_ND1].dsMask  =  BITMSK(SDK_CAPTURE_SIZE_ND1);
	m_resolution[SDK_CAPTURE_SIZE_650TVL].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_720P].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_1_3M].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_UXGA].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_1080P].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_WUXGA].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_2_5M].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_3M].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	m_resolution[SDK_CAPTURE_SIZE_5M].dsMask  = BITMSK(SDK_CAPTURE_SIZE_D1) | BITMSK(SDK_CAPTURE_SIZE_HD1) | BITMSK(SDK_CAPTURE_SIZE_CIF) | BITMSK(SDK_CAPTURE_SIZE_QCIF);
	
	m_maxBitRate[SDK_CAPTURE_SIZE_D1] =  STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_D1][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_HD1] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_HD1][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_BCIF] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_BCIF][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_CIF] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_CIF][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_QCIF] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_QCIF][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_VGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_VGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_QVGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_QVGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_SVCD] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_SVCD][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_QQVGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_QQVGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_ND1] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_ND1][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_650TVL] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_650TVL][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_720P] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_720P][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_1_3M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_1_3M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_UXGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_UXGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_1080P] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_1080P][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_WUXGA] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_WUXGA][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_2_5M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_2_5M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_3M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_3M][5];
	m_maxBitRate[SDK_CAPTURE_SIZE_5M] = STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_5M][5];
}

int CConfigChannel::GetMaxFrame(int nResolution, long lFreePower)
{
	int nTempRate = lFreePower / m_resolution[nResolution].dwSize;
	if ( 0 == m_nVideoStandard )
	{
		if ( nTempRate > 25 )
		{
			nTempRate = 25;
		}
	}
	else
	{
		if ( nTempRate > 30 )
		{
			nTempRate = 30;
		}
	}
	return nTempRate;	
}

bool CConfigChannel::AllStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType)
{
	if (nEncodeType == MAIN_STREAM || (nEncodeType == EXPAND_STREAM && m_bMultiStream))
	{
		DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;
		int nChannelCount = m_DevAttribute.deviveInfo.byChanNum;
		DWORD dwPower = lFreePower / nChannelCount;
		DWORD dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
		DWORD dwBitrate = -1;
		
		if (nEncodeType == MAIN_STREAM)
		{
			DWORD dwTmpPower = 0xFFFFFFFF;
			DWORD uiResolution = 0xFFFFFFFF;
			int i = 0;
			
			for (i = 0; i < nChannelCount; i++)
			{
				if (m_pEncodeAbility.ImageSizePerChannel[i] &&  m_pEncodeAbility.nMaxPowerPerChannel[i])
				{
					dwTmpPower = 
						(dwTmpPower < m_pEncodeAbility.nMaxPowerPerChannel[i]) ? dwTmpPower : m_pEncodeAbility.nMaxPowerPerChannel[i];
					uiResolution &= m_pEncodeAbility.ImageSizePerChannel[i];
				}
			}
			
			for (i = 0; i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & uiResolution)
				{
					break;
				}
			}
			
			if (m_pEncodeAbility.ImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ImageSizePerChannel[nChannelNum] & uiResolution;
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}
			
			dwPower = (dwPower < dwTmpPower) ? dwPower : dwTmpPower;

			pConfigEncode->dstMainFmt.vfFormat.iResolution = 
				(i > pConfigEncode->dstMainFmt.vfFormat.iResolution) ? i : pConfigEncode->dstMainFmt.vfFormat.iResolution;
			

			dwBitrate = m_pEncodeAbility.iMaxBps / nChannelCount;
		}
		else if (nEncodeType == EXPAND_STREAM)
		{
			DWORD uiResolution = 0xFFFFFFFF;
			int i = 0;
			
			for (i = 0; i < nChannelCount; i++)
			{
				if (m_pEncodeAbility.ExImageSizePerChannel[i])
				{
					uiResolution &= m_pEncodeAbility.ExImageSizePerChannel[i];
				}
			}
			
			for (i = 0; i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & uiResolution)
				{
					break;
				}
			}
			
			if (m_pEncodeAbility.ExImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ExImageSizePerChannel[nChannelNum] & uiResolution;
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}
			
			pConfigEncode->dstExtraFmt.vfFormat.iResolution = 
				(i > pConfigEncode->dstExtraFmt.vfFormat.iResolution) ? i : pConfigEncode->dstExtraFmt.vfFormat.iResolution;
		}
		return StructToWinData(nChannelNum, pConfigEncode, nEncodeType, dwPower, dwMask, dwBitrate);
	}
	return false;
}

bool CConfigChannel::StructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType, DWORD dwPower, DWORD dwMask, DWORD dwBitrate)
{
	if (nEncodeType >= STREAM_NUM)
	{
		return false;
	}
	SDK_MEDIA_FORMAT &dstMainFmt = pConfigEncode->dstMainFmt;
	SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;
	
	SDK_MEDIA_FORMAT &dstExtraFmt = pConfigEncode->dstExtraFmt;
	SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
	
	SDK_MEDIA_FORMAT dstSetFmt = {0};
	SDK_VIDEO_FORMAT vfSetFormat = {0};

	int nResolution = 0, nFPS = 25;
	DWORD dwChnUsed = 0, dwChnFree = 0;
	if (nEncodeType == MAIN_STREAM)
	{
		if (dwMask == -1)
		{
			if (m_pEncodeAbility.ImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ImageSizePerChannel[nChannelNum];
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}
		}
		
		if (m_bMultiStream && dstExtraFmt.bVideoEnable)
		{
			dwChnUsed = m_resolution[vfExFormat.iResolution].dwSize * vfExFormat.nFPS;
		}
		dwChnFree = dwPower - dwChnUsed;
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{
			DWORD dwAvgPower =  (m_pEncodeAbility.iMaxEncodePower - GetExpandUsed()) / m_DevAttribute.deviveInfo.byChanNum;
			dwChnFree = min(dwChnFree, dwAvgPower);
		}


		nResolution = vfFormat.iResolution;
		nFPS = vfFormat.nFPS;
		GetMaxResolAndRate(nResolution, nFPS, dwChnFree);
		EnableMainVideo(dstMainFmt.bVideoEnable);
		dstSetFmt = dstMainFmt;
		vfSetFormat = vfFormat;
	}
	else if (nEncodeType == EXPAND_STREAM)
	{
		if (dwMask == -1)
		{
			if (m_pEncodeAbility.ExImageSizePerChannel[nChannelNum])
			{
				dwMask = m_pEncodeAbility.ExImageSizePerChannel[nChannelNum];
			}
			else
			{
				dwMask = m_pEncodeAbility.vEncodeInfo[0].uiResolution;
			}
		}

		if (m_pEncodeAbility.ExImageSizePerChannelEx[nChannelNum][dstMainFmt.vfFormat.iResolution])
		{
			dwMask &= m_pEncodeAbility.ExImageSizePerChannelEx[nChannelNum][dstMainFmt.vfFormat.iResolution];
		}
		dwMask &= m_resolution[vfFormat.iResolution].dsMask;
		if (dstMainFmt.bVideoEnable)
		{
			dwChnUsed = m_resolution[vfFormat.iResolution].dwSize * vfFormat.nFPS;
		}
		dwChnFree = dwPower - dwChnUsed;
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{
			DWORD dwAvgPower =  (m_pEncodeAbility.iMaxEncodePower - GetMainUsed()) / m_DevAttribute.deviveInfo.byChanNum;
			dwChnFree = min(dwChnFree, dwAvgPower);
		}
		nResolution = vfExFormat.iResolution;
		nFPS = vfExFormat.nFPS;
		GetMaxResolAndRate(nResolution, nFPS, dwChnFree);
		EnableExpandVideo(dstExtraFmt.bVideoEnable);
		dstSetFmt = dstExtraFmt;
		vfSetFormat = vfExFormat;
	}
	else
	{
		dwMask = m_pEncodeAbility.vCombEncInfo[0].uiResolution ? m_pEncodeAbility.vCombEncInfo[0].uiResolution : m_pEncodeAbility.vEncodeInfo[0].uiResolution;
		dwChnUsed = 0;
		dwChnFree = dwPower - dwChnUsed;


		nResolution = SDK_CAPTURE_SIZE_D1;
		nFPS = (0 == m_nVideoStandard) ? 25 : 30;

		EnableExpandVideo(dstMainFmt.bVideoEnable);
		dstSetFmt = dstMainFmt;
		vfSetFormat = vfFormat;
	}
	AddCmbResolution(ControlID[nEncodeType][CONTROL_RESOLUTION], nResolution, dwMask);
	AddCmbFPS(ControlID[nEncodeType][CONTROL_FRAME], nFPS);
	
	SetComBoxCurSel(ControlID[nEncodeType][CONTROL_RESOLUTION], vfSetFormat.iResolution);

	if ( vfSetFormat.nFPS < nFPS )
		SetComBoxCurSel(ControlID[nEncodeType][CONTROL_FRAME], vfSetFormat.nFPS);
	else
		SetComBoxCurSel(ControlID[nEncodeType][CONTROL_FRAME], nFPS);

	SetComBoxCurSel(ControlID[nEncodeType][CONTROL_BITCONTROL], vfSetFormat.iBitRateControl);
	SetComBoxCurSel(ControlID[nEncodeType][CONTROL_QUALITY], vfSetFormat.iQuality);
	SetComBoxCurSel(ControlID[nEncodeType][CONTROL_GOP], vfSetFormat.iGOP);

	int j = 0; 
	int nTmpFPS = 25;
	nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	nTmpFPS = min(vfSetFormat.nFPS, nFPS);
	
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(ControlID[nEncodeType][CONTROL_BIT_RATE]);
	pComboBox->ResetContent();
	for (j = 0; j < sizeof(STREAM_CODE_VALUE[vfSetFormat.iResolution]) / sizeof(int); ++j)
	{
		TCHAR sBitrate[8];

		int iBitrate = STREAM_CODE_VALUE[vfSetFormat.iResolution][j] * (vfSetFormat.iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
		_stprintf(sBitrate, "%d", STREAM_CODE_VALUE[vfSetFormat.iResolution][j] * (vfSetFormat.iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1));
		
		if (dwBitrate == -1 || dwBitrate >= iBitrate)
		{
			int nInsert = pComboBox->AddString(sBitrate);
			pComboBox->SetItemData(nInsert, iBitrate);		
		}
	}
	if (0 == vfSetFormat.iBitRateControl) 
	{
		if (-1 == dwBitrate)
		{
			SetComBoxCurSel(ControlID[nEncodeType][CONTROL_BIT_RATE], NearBitrate(ControlID[nEncodeType][CONTROL_BIT_RATE], vfSetFormat.nBitRate));		
		}
		else
		{
			dwBitrate = (dwBitrate > vfSetFormat.nBitRate) ? vfSetFormat.nBitRate : dwBitrate;
			SetComBoxCurSel(ControlID[nEncodeType][CONTROL_BIT_RATE], NearBitrate(ControlID[nEncodeType][CONTROL_BIT_RATE], dwBitrate));
		}
	}
	else
	{
		if (-1 == dwBitrate)
		{
			SetComBoxCurSel(ControlID[nEncodeType][CONTROL_BIT_RATE], 
				STREAM_CODE_VALUE[vfSetFormat.iResolution][vfSetFormat.iQuality - 1] * (vfSetFormat.iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1));
		}
		else
		{
			DWORD dwCntBitrate = STREAM_CODE_VALUE[vfSetFormat.iResolution][vfSetFormat.iQuality - 1] * (vfSetFormat.iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (vfSetFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
			dwBitrate = (dwBitrate > dwCntBitrate) ? dwCntBitrate : dwBitrate;
			bool nret = SetComBoxCurSel(ControlID[nEncodeType][CONTROL_BIT_RATE],  NearBitrate(ControlID[nEncodeType][CONTROL_BIT_RATE], dwBitrate));
		}
	}
	
	((CButton *)GetDlgItem(ControlID[nEncodeType][CONTROL_VIDEO]))->SetCheck(dstSetFmt.bVideoEnable);
	((CButton *)GetDlgItem(ControlID[nEncodeType][CONTROL_AUDIO]))->SetCheck(dstSetFmt.bAudioEnable && dstSetFmt.bVideoEnable);
	GetDlgItem(ControlID[nEncodeType][CONTROL_BIT_RATE])->EnableWindow(!vfSetFormat.iBitRateControl && dstSetFmt.bVideoEnable );
	GetDlgItem(ControlID[nEncodeType][CONTROL_QUALITY])->EnableWindow(vfSetFormat.iBitRateControl && dstSetFmt.bVideoEnable );

	if (nEncodeType == COMBINE_STREAM)
	{
		SetComBoxCurSel(IDC_COMBO_COMBINEMODE,m_CmbEncodeMode.vEncodeParam[0].iEncodeMode);
		GetDlgItem(IDC_COMBO_COMBINEMODE)->EnableWindow(dstSetFmt.bVideoEnable);
	}
	
	return true;
}

DWORD CConfigChannel::GetExpandUsed()
{
	DWORD lUsePower = 0;
	if (m_bMultiStream)
	{
		for ( int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i ++ )
		{
			if ( m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.bVideoEnable )
			{
				DWORD lSize = m_resolution[ m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.iResolution ].dwSize;
				lUsePower += lSize * m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.nFPS;
			}
		}
	}
	
	return lUsePower;
}

DWORD CConfigChannel::GetComboBoxData(UINT nID, int nIndex)
{
	DWORD dwData = 0;
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(nID);
	if (pComboBox)
	{
		if (-1 == nIndex)
		{
			nIndex = pComboBox->GetCurSel();
		}
		
		if (-1 != nIndex)
		{
			dwData = pComboBox->GetItemData(nIndex);
		}
	}
	
	return dwData;
}

BOOL CConfigChannel::SetComBoxCurSel(UINT nID, DWORD dwData)
{
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(nID); 
	if (!pComboBox)
	{
		return FALSE;
	}
	
	int nCount = pComboBox->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		if (pComboBox->GetItemData(i) == dwData)
		{
			pComboBox->SetCurSel(i);
			return TRUE;
		}
	}
	
	return FALSE;
}

void CConfigChannel::GetMaxResolAndRate(int &nResolu, int &nRate, long lFreePower )
{
	if ( lFreePower <= 0 )
	{
		return;
	}

	int nSize = m_resolution[nResolu].dwSize;
	if ( nSize > lFreePower )
	{
		nResolu = -1;
		nRate = -1;
		return;
	}
	else
	{
		int nTempRate = lFreePower / nSize;
		if ( 0 == m_nVideoStandard )
		{
			if ( nTempRate > 25 )
			{
				nTempRate = 25;
			}
		}
		else
		{
			if ( nTempRate > 30 )
			{
				nTempRate = 30;
			}
		}
		nRate = nTempRate;
	}
	if ( nResolu == 0 )
	{
		return;
	}
	
	long lMaxSize = nSize;
	for ( int i = 0; i < SDK_CAPTURE_SIZE_NR; i ++ )
	{
		long lTempsize = m_resolution[i].dwSize;
		if ( lFreePower >= lTempsize && lMaxSize < lTempsize )
		{
			nResolu = i;
			lMaxSize = lTempsize;
		}
	}
}

void CConfigChannel::EnableMainVideo( BOOL bEnable )
{
	GetDlgItem(IDC_COMBO_CODE_FORMAT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_FRAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_BITCONTROL)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_QUALITY)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_BIT_RATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_GOP)->EnableWindow(bEnable);
}

DWORD CConfigChannel::GetMainUsed()
{
	DWORD lUsePower = 0;
	for ( int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i ++ )
	{
		if ( m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.bVideoEnable )
		{
			DWORD lSize = m_resolution[ m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution ].dwSize;
			lUsePower += lSize * m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nFPS;
		}
	}
	return lUsePower;
}

void CConfigChannel::EnableExpandVideo(  BOOL bEnable )
{
	GetDlgItem(IDC_COMBO_EXPAND)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_EXPAND_RESOLUTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_EXPAND_FRAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_EXPAND_BITCONTROL)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_EXPAND_QUALITY)->EnableWindow(bEnable);	
	GetDlgItem(IDC_COMBO_EXPAND_BIT_RATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_EXPAND_GOP)->EnableWindow(bEnable);
}

void CConfigChannel::AddCmbResolution( UINT nID, int maxSize, DWORD dwMask )
{
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(nID);
	if (!pComboBox)
	{
		return;
	}
	pComboBox->ResetContent();
	
	for (int i = 0; i < SDK_CAPTURE_SIZE_NR ; i ++)
	{
		if ( (m_resolution[i].dwSize <= m_resolution[maxSize].dwSize ) 
			&& ( dwMask & (0x01<<i) ) )
		{
			int nIndex = 0;
			nIndex = pComboBox->AddString(m_resolution[i].strText);
			pComboBox->SetItemData(nIndex, i);
		}
	}	
}

void CConfigChannel::AddCmbFPS( UINT nID, int maxSize )
{
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(nID);
	if (!pComboBox)
	{
		return;
	}
	pComboBox->ResetContent();
	
	for ( int i = 0; i < maxSize; i ++ )
	{
		CString strChannel("");
		strChannel.Format("%d", i + 1);
		pComboBox->AddString(strChannel);
		pComboBox->SetItemData(i, i + 1);
	}
}

int CConfigChannel::NearBitrate(UINT nID, DWORD dwData)
{
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(nID); 
	if (!pComboBox)
	{
		return dwData;
	}
	
	int nCount = pComboBox->GetCount();
	int nBitrate = 0;
	for (int i = 0; i < nCount; i++)
	{
		nBitrate = pComboBox->GetItemData(i);
		if (nBitrate >= dwData)
		{
			break;
		}
	}
	
	return nBitrate;
}

bool CConfigChannel::StructToWin()
{
	bool bRet = false;
	
	//InitResData();
	
	UpdateCodeFormat(0, IDC_COMBO_CODE_FORMAT);
	if (m_bMultiStream)
	{
		UpdateCodeFormat(1, IDC_COMBO_EXPAND);
	}
	else
	{
		UpdateCodeFormat(0, IDC_COMBO_EXPAND);
	}
	
	((CComboBox *)GetDlgItem(IDC_COMBO_CODE_FORMAT))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_EXPAND))->SetCurSel(0);
	
	int nChannelNo =m_ChanNo.GetCurSel();
	if (nChannelNo == m_DevAttribute.deviveInfo.byChanNum)
	{
		nChannelNo = 0;
	}
	NormalStructToWinData(nChannelNo, &m_EncodeConfig.vEncodeConfigAll[nChannelNo], MAIN_STREAM);
	NormalStructToWinData(nChannelNo, &m_EncodeConfig.vEncodeConfigAll[nChannelNo], EXPAND_STREAM);
	CombineStructToWinData(nChannelNo, &m_EncodeConfig.vEncodeConfigAll[0], COMBINE_STREAM);
	
	return true;
}

void CConfigChannel::UpdateCodeFormat(int nStream, UINT nComboBoxID)
{
	CComboBox *pComboBox =(CComboBox *)GetDlgItem(nComboBoxID);
	pComboBox->ResetContent();
	unsigned int uiCompression = 0;
	if (nStream == 2)
	{
		uiCompression = m_pEncodeAbility.vCombEncInfo[0].uiCompression ? m_pEncodeAbility.vCombEncInfo[0].uiCompression : m_pEncodeAbility.vEncodeInfo[0].uiCompression;
	}
	else
	{
		uiCompression = m_pEncodeAbility.vEncodeInfo[nStream].uiCompression;
	}

	for ( int i = 0; i < SDK_CAPTURE_COMP_NR; i ++ )
	{
		if (uiCompression & ( 1 << i ) )
		{
			int nIndex = 0;
			nIndex = pComboBox->AddString(m_mapCaptureComp[i]);
			pComboBox->SetItemData(nIndex, i);	
		}
	}		
}

bool CConfigChannel::NormalStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType)
{
	if (nEncodeType == MAIN_STREAM || (nEncodeType == EXPAND_STREAM && m_bMultiStream))
	{
		DWORD dwPower = GetFreeDspPower(nChannelNum);
		DWORD dwBitrate = -1;
		if (nEncodeType == MAIN_STREAM)
		{
			if (m_pEncodeAbility.nMaxPowerPerChannel[nChannelNum])
			{
				dwPower =(dwPower < m_pEncodeAbility.nMaxPowerPerChannel[nChannelNum]) ? dwPower : m_pEncodeAbility.nMaxPowerPerChannel[nChannelNum];
			}
			
			int i = 0;
			for (i = 0; m_pEncodeAbility.ImageSizePerChannel[nChannelNum] && i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & m_pEncodeAbility.ImageSizePerChannel[nChannelNum])
				{
					break;
				}
			}
			pConfigEncode->dstMainFmt.vfFormat.iResolution = 
				(i > pConfigEncode->dstMainFmt.vfFormat.iResolution) ? i : pConfigEncode->dstMainFmt.vfFormat.iResolution;
			
			dwBitrate = GetFreeBitratePower(nChannelNum);
		}
		else if (nEncodeType == EXPAND_STREAM)
		{
			int i = 0;
			for (i = 0; m_pEncodeAbility.ExImageSizePerChannel[nChannelNum] && i < SDK_CAPTURE_SIZE_NR; i++)
			{
				if ((1 << i) & m_pEncodeAbility.ExImageSizePerChannel[nChannelNum])
				{
					break;
				}
			}
			pConfigEncode->dstExtraFmt.vfFormat.iResolution = 
				(i > pConfigEncode->dstExtraFmt.vfFormat.iResolution) ? i : pConfigEncode->dstExtraFmt.vfFormat.iResolution;
		}
		return StructToWinData(nChannelNum, pConfigEncode, nEncodeType, dwPower, -1, dwBitrate);
	}
	return false;
}

DWORD CConfigChannel::GetFreeDspPower(int nChannelNo)
{
	DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;
	
	for ( int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i ++ )
	{
		if ( i != nChannelNo )
		{
			if ( m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.bVideoEnable )
			{
				DWORD lSize = m_resolution[ m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution ].dwSize;
				lFreePower -= lSize * m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nFPS;
			}
			
			if ( m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.bVideoEnable )
			{
				DWORD lSize = m_resolution[ m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.iResolution ].dwSize;
				lFreePower -= lSize * m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.nFPS;
			}
		}
	}
	
	return lFreePower;
}

DWORD CConfigChannel::GetFreeBitratePower(int nChannelNo)
{
	DWORD lFreePower = m_pEncodeAbility.iMaxBps;
	
	for ( int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i ++ )
	{
		if ( i != nChannelNo )
		{
			if ( m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.bVideoEnable )
			{
				lFreePower -= m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nBitRate;
			}
		}
	}
	
	return lFreePower;
}

bool CConfigChannel::CombineStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType)
{
	DWORD dwPower = 0;
	if (nEncodeType == COMBINE_STREAM && m_bCombineEncode)
	{
		return StructToWinData(nChannelNum, pConfigEncode, nEncodeType, dwPower, -1, -1);
	}
	return false;
}

bool CConfigChannel::AllWinDataToStruct(int nChannelNum)
{
	WinDataToStruct(m_allData.dstMainFmt, MAIN_STREAM);
	WinDataToStruct(m_allData.dstExtraFmt, EXPAND_STREAM);
	return true;
}
bool CConfigChannel::NomalWinDataToStruct(int nChannelNum)
{
	WinDataToStruct(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt, MAIN_STREAM);
	WinDataToStruct(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt, EXPAND_STREAM);
	return true;
}

bool CConfigChannel::WinDataToStruct(SDK_MEDIA_FORMAT &dstFmt, int nEncodeType)
{
	if (nEncodeType >= STREAM_NUM)
	{
		return false;
	}
	SDK_VIDEO_FORMAT &vfFormat = dstFmt.vfFormat;
	
	vfFormat.iResolution = GetComboBoxData(ControlID[nEncodeType][CONTROL_RESOLUTION]);
	vfFormat.nFPS = GetComboBoxData(ControlID[nEncodeType][CONTROL_FRAME]);
	vfFormat.iBitRateControl =  GetComboBoxData(ControlID[nEncodeType][CONTROL_BITCONTROL]);
	vfFormat.iQuality =  GetComboBoxData(ControlID[nEncodeType][CONTROL_QUALITY]);
	
	vfFormat.nBitRate = GetComboBoxData(ControlID[nEncodeType][CONTROL_BIT_RATE]);
	vfFormat.iGOP = GetComboBoxData(ControlID[nEncodeType][CONTROL_GOP]);
	
	dstFmt.bVideoEnable = ((CButton *)GetDlgItem(ControlID[nEncodeType][CONTROL_VIDEO]))->GetCheck();
	dstFmt.bAudioEnable = ((CButton *)GetDlgItem(ControlID[nEncodeType][CONTROL_AUDIO]))->GetCheck();
	
	if (nEncodeType == COMBINE_STREAM)
	{
		dstFmt.bAudioEnable = false;
		m_CmbEncodeMode.vEncodeParam[0].iEncodeMode = GetComboBoxData(IDC_COMBO_COMBINEMODE);
	}
	
	return true;
}

void CConfigChannel::OnSelchangeComboResolution() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;
		DWORD lAvrPower = lFreePower / nChannelNum;
		SDK_MEDIA_FORMAT &dstMainFmt =m_allData.dstMainFmt;
		SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;
		
		
		SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
		SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
		
		int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
		int nResolution = vfFormat.iResolution;
		int nExResolution = 0;
		int nExFPS = 0;
		if (m_bMultiStream && dstExtraFmt.bVideoEnable )
		{
			nExResolution =  m_resolution[vfExFormat.iResolution].dwSize;
			nExFPS =  vfExFormat.nFPS;
		}
		DWORD dwExpandEnable = nExResolution * nExFPS;
		int nMaxFrame = 0;
		if ( lAvrPower - dwExpandEnable <= 0 )
		{
			((CButton *)GetDlgItem(IDC_CHECK_EXPAND_VIDEO))->SetCheck(FALSE);
			return;
		}
		lAvrPower = lAvrPower - dwExpandEnable;
		
		SelchangeComboResolution(m_allData.dstMainFmt, MAIN_STREAM, lAvrPower);
		AllStructToWinData(0, &m_allData, MAIN_STREAM);		
		AllStructToWinData(0, &m_allData, EXPAND_STREAM);
	}
	else
	{
		DWORD lFreePower = 0;
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{
			
			lFreePower =  (m_pEncodeAbility.iMaxEncodePower - GetExpandUsed()) / m_DevAttribute.deviveInfo.byChanNum;
		}
		else
		{
			lFreePower = GetFreeDspPower(nChannelNum);
			lFreePower = lFreePower - GetUsedEnable(IDC_COMBO_EXPAND_RESOLUTION, IDC_COMBO_EXPAND_FRAME, IDC_CHECK_EXPAND_VIDEO);
		}
		SelchangeComboResolution(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt, MAIN_STREAM, lFreePower);
		if (m_pEncodeAbility.iChannelMaxSetSync)
		{
			for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
			{
				if (i != nChannelNum)
				{
					m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.iResolution = 
						m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt.vfFormat.iResolution;
					m_EncodeConfig.vEncodeConfigAll[i].dstMainFmt.vfFormat.nFPS = 
						m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt.vfFormat.nFPS;
				}
			}
		}
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
	}
}

DWORD CConfigChannel::GetUsedEnable(UINT nResID, UINT nFrameID, UINT nEnableID)
{
	if ( !((CButton *)GetDlgItem(nEnableID))->GetCheck() || !m_bMultiStream)
	{
		return 0;
	}
	
	int nData = GetComboBoxData(nResID);
	CString str;
	GetDlgItemText(nFrameID,str);
	int nFrame = atoi(str);
	
	return m_resolution[nData].dwSize * nFrame;
}

void CConfigChannel::SelchangeComboResolution(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType, DWORD dwPower)
{
	int nChannelNum =m_ChanNo.GetCurSel();
	int nCurFrame = GetComboBoxData(ControlID[nEncodeType][CONTROL_FRAME]);
	int iResolution = GetComboBoxData(ControlID[nEncodeType][CONTROL_RESOLUTION]);
	int iQuality = GetComboBoxData(ControlID[nEncodeType][CONTROL_QUALITY]) - 1;
	
	
	SDK_VIDEO_FORMAT &vfFormat = dstFormat.vfFormat;
	int nMaxFrame = 0;
	if (nEncodeType == COMBINE_STREAM)
	{
		nMaxFrame = (0 == m_nVideoStandard) ? 25 : 30;
	}
	else
	{
		nMaxFrame = GetMaxFrame(iResolution, dwPower);
	}
	nCurFrame = min(nCurFrame, nMaxFrame);
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	vfFormat.iResolution = iResolution;
	vfFormat.nFPS = nCurFrame;
	vfFormat.nBitRate = 
		STREAM_CODE_VALUE[iResolution][iQuality] * (vfFormat.iGOP * nCurFrame +  IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
}

void CConfigChannel::OnSelchangeComboBitcontrol() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum =m_ChanNo.GetCurSel();
	
	if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		SelchangeComboBitcontrol(m_allData.dstMainFmt, MAIN_STREAM);
		AllStructToWinData(0, &m_allData, MAIN_STREAM);
	}
	else
	{
		SelchangeComboBitcontrol(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt, MAIN_STREAM);
		NormalStructToWinData(0, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
	}
}

void CConfigChannel::SelchangeComboBitcontrol(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType)
{
	int iResolution = GetComboBoxData(ControlID[nEncodeType][CONTROL_RESOLUTION]);
	int iQuality =  GetComboBoxData(ControlID[nEncodeType][CONTROL_QUALITY]) - 1;
	int iGOP = GetComboBoxData(ControlID[nEncodeType][CONTROL_GOP]);
	int nTmpFPS = GetComboBoxData(ControlID[nEncodeType][CONTROL_FRAME]);
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	nTmpFPS = min(nTmpFPS, nFPS);
	
	dstFormat.vfFormat.iBitRateControl = GetComboBoxData(ControlID[nEncodeType][CONTROL_BITCONTROL]);
	dstFormat.vfFormat.nBitRate = STREAM_CODE_VALUE[iResolution][iQuality] * (iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	if (dstFormat.vfFormat.iBitRateControl)
	{
		GetDlgItem(ControlID[nEncodeType][CONTROL_BIT_RATE])->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(ControlID[nEncodeType][CONTROL_BIT_RATE])->EnableWindow(TRUE && dstFormat.bVideoEnable);
	}
	
	GetDlgItem(ControlID[nEncodeType][CONTROL_QUALITY])->EnableWindow(dstFormat.vfFormat.iBitRateControl && dstFormat.bVideoEnable);
	
	Invalidate();
}

void CConfigChannel::OnSelchangeComboQuality() 
{
	// TODO: Add your control notification handler code here
	int iResolution = GetComboBoxData(IDC_COMBO_RESOLUTION);
	int iQuality =  GetComboBoxData(IDC_COMBO_QUALITY);
	int iGOP = GetComboBoxData(IDC_COMBO_GOP);
	int nTmpFPS = GetComboBoxData(IDC_COMBO_FRAME);
	int nChannelNum = m_ChanNo.GetCurSel();
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	nTmpFPS = min(nTmpFPS, nFPS);
	
	if (nChannelNum ==m_DevAttribute.deviveInfo.byChanNum)
	{
		SDK_MEDIA_FORMAT &dstMainFmt = m_allData.dstMainFmt;
		SDK_VIDEO_FORMAT &vfMainFormat = dstMainFmt.vfFormat;
		vfMainFormat.iQuality = iQuality;
		vfMainFormat.nBitRate = STREAM_CODE_VALUE[iResolution][iQuality - 1] * (iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
		SetComBoxCurSel(IDC_COMBO_BIT_RATE, vfMainFormat.nBitRate);
	}
	else
	{
		SDK_MEDIA_FORMAT &dstMainFmt = m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt;
		SDK_VIDEO_FORMAT &vfMainFormat = dstMainFmt.vfFormat;
		vfMainFormat.iQuality = iQuality;
		vfMainFormat.nBitRate = STREAM_CODE_VALUE[iResolution][iQuality - 1] * (iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
		SetComBoxCurSel(IDC_COMBO_BIT_RATE, vfMainFormat.nBitRate);
	}
	Invalidate();
}

void CConfigChannel::OnSelchangeComboFrame() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		SelchangeComboFrame(m_allData.dstMainFmt, MAIN_STREAM);
		AllStructToWinData(0, &m_allData, MAIN_STREAM);
		AllStructToWinData(0, &m_allData, EXPAND_STREAM);
	}
	else
	{
		SelchangeComboFrame(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt, MAIN_STREAM);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
		NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
	}
}


void CConfigChannel::SelchangeComboFrame(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType)
{
	int nChannelNum = m_ChanNo.GetCurSel();
	int iResolution = GetComboBoxData(ControlID[nEncodeType][CONTROL_RESOLUTION]);
	int iQuality =  GetComboBoxData(ControlID[nEncodeType][CONTROL_QUALITY]) - 1 ;
	
	SDK_VIDEO_FORMAT &vfFormat = dstFormat.vfFormat;
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	int iSrcFPS = vfFormat.nFPS;
	vfFormat.nFPS = GetComboBoxData(ControlID[nEncodeType][CONTROL_FRAME]);
	
	if (vfFormat.iBitRateControl)
	{
		vfFormat.nBitRate = 
			STREAM_CODE_VALUE[iResolution][iQuality] * (vfFormat.iGOP * vfFormat.nFPS +  IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	}
	else
	{
		int nTarget = vfFormat.nBitRate * (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * iSrcFPS +  IFRAME_EQ_PFRAME - 1);
		vfFormat.nBitRate = nTarget * (vfFormat.iGOP * vfFormat.nFPS +  IFRAME_EQ_PFRAME - 1) / (vfFormat.iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	}
}

void CConfigChannel::OnSelchangeComboExpandBitcontrol() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if (m_bMultiStream)
	{
		
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SelchangeComboBitcontrol(m_allData.dstExtraFmt, EXPAND_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			SelchangeComboBitcontrol(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt, EXPAND_STREAM);
			NormalStructToWinData(0, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}
	}
	else if (m_bCombineEncode)
	{
		SelchangeComboBitcontrol(m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0], COMBINE_STREAM);
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy( &EncodeSimp.dstExtraFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt,sizeof(SDK_MEDIA_FORMAT));
		memcpy( &EncodeSimp.dstMainFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt,sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void CConfigChannel::OnSelchangeComboExpandBitRate() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if (m_bMultiStream)
	{
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SDK_MEDIA_FORMAT &dstMainFmt = m_allData.dstMainFmt;
			SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;
			vfFormat.nBitRate = GetComboBoxData(IDC_COMBO_BIT_RATE);
		}
		else
		{
			
			SDK_MEDIA_FORMAT &dstExtraFmt = m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
			vfExFormat.nBitRate = GetComboBoxData(IDC_COMBO_EXPAND_BIT_RATE);
		}
	}
	else
	{
		SDK_MEDIA_FORMAT &dsCombFmt = m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0];
		SDK_VIDEO_FORMAT &vfCombFormat = dsCombFmt.vfFormat;
		vfCombFormat.nBitRate = GetComboBoxData(IDC_COMBO_EXPAND_BIT_RATE);
	}
}

void CConfigChannel::OnSelchangeComboExpandResolution() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if (m_bMultiStream)
	{
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			DWORD lFreePower = m_pEncodeAbility.iMaxEncodePower;
			int nChannelCount = m_DevAttribute.deviveInfo.byChanNum;
			DWORD lAvrPower = lFreePower / nChannelCount;

			SDK_MEDIA_FORMAT &dstMainFmt =m_allData.dstMainFmt;
			SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;

			SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
			
			int nCurFrame = vfExFormat.nFPS;
			int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
			int nExResolution = 0;
			int nExFPS = 0;
			if (dstMainFmt.bVideoEnable )
			{
				nExResolution =  m_resolution[vfFormat.iResolution].dwSize;
				nExFPS =  vfFormat.nFPS;
			}
			DWORD dwExpandEnable = nExResolution * nExFPS;
			int nMaxFrame = 0;
			if ( lAvrPower - dwExpandEnable <= 0 )
			{
				((CButton *)GetDlgItem(IDC_CHECK_EXPAND_VIDEO))->SetCheck(FALSE);
				return;
			}
			lAvrPower = lAvrPower - dwExpandEnable;
			
			SelchangeComboResolution(m_allData.dstExtraFmt, EXPAND_STREAM, lAvrPower);
			AllStructToWinData(0, &m_allData, MAIN_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			DWORD lFreePower = 0;
			if (m_pEncodeAbility.iChannelMaxSetSync)
			{
				
				lFreePower =  (m_pEncodeAbility.iMaxEncodePower - GetMainUsed()) / m_DevAttribute.deviveInfo.byChanNum;
			}
			else
			{
				
				lFreePower = GetFreeDspPower(nChannelNum);
				lFreePower = lFreePower - GetUsedEnable(IDC_COMBO_RESOLUTION, IDC_COMBO_FRAME, IDC_CHECK_MAIN_VIDEO);
			}
			SelchangeComboResolution(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt, EXPAND_STREAM, lFreePower);
			if (m_pEncodeAbility.iChannelMaxSetSync)
			{
				for (int i = 0; i < m_DevAttribute.deviveInfo.byChanNum; i++)
				{
					if (i != nChannelNum)
					{
						m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.iResolution = 
							m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt.vfFormat.iResolution;
						m_EncodeConfig.vEncodeConfigAll[i].dstExtraFmt.vfFormat.nFPS = 
							m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt.vfFormat.nFPS;
					}
				}
			}
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}
	}
	else if(m_bCombineEncode)
	{
		
		SelchangeComboResolution(m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0], COMBINE_STREAM, 0);
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy( &EncodeSimp.dstExtraFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt,sizeof(SDK_MEDIA_FORMAT));
		memcpy( &EncodeSimp.dstMainFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt,sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void CConfigChannel::OnSelchangeComboExpandQuality() 
{
	// TODO: Add your control notification handler code here
	int iResolution = GetComboBoxData(IDC_COMBO_EXPAND_RESOLUTION);
	int iQuality =  GetComboBoxData(IDC_COMBO_EXPAND_QUALITY);
	int iGOP = GetComboBoxData(IDC_COMBO_EXPAND_GOP);
	int nTmpFPS = GetComboBoxData(IDC_COMBO_EXPAND_FRAME);
	int nChannelNum = m_ChanNo.GetCurSel();
	int nFPS = (0 == m_nVideoStandard) ? 25 : 30;
	nTmpFPS = min(nTmpFPS, nFPS);
	
	int nBitrate = STREAM_CODE_VALUE[iResolution][iQuality - 1] * (iGOP * nTmpFPS +  IFRAME_EQ_PFRAME - 1) / (iGOP * nFPS + IFRAME_EQ_PFRAME - 1);
	SetComBoxCurSel(IDC_COMBO_EXPAND_BIT_RATE, nBitrate);
	if (m_bMultiStream)
	{
		
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
			vfExFormat.nBitRate = nBitrate;
			vfExFormat.iQuality = iQuality;
		}
		else
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExFormat = dstExtraFmt.vfFormat;
			vfExFormat.nBitRate = nBitrate;
			vfExFormat.iQuality = iQuality;
		}
	}
	else
	{
		SDK_MEDIA_FORMAT &dsCombFmt = m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0];
		SDK_VIDEO_FORMAT &vfCombFormat = dsCombFmt.vfFormat;
		vfCombFormat.nBitRate = nBitrate;
		vfCombFormat.iQuality = iQuality;
	}
	
	Invalidate();
}

void CConfigChannel::OnSelchangeComboExpandFrame() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if (m_bMultiStream)
	{		
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SelchangeComboFrame(m_allData.dstExtraFmt, EXPAND_STREAM);
			AllStructToWinData(0, &m_allData, MAIN_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			SelchangeComboFrame(m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt, EXPAND_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}
	}
	else if (m_bCombineEncode)
	{
		SelchangeComboFrame(m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0], COMBINE_STREAM);
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy( &EncodeSimp.dstExtraFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt,sizeof(SDK_MEDIA_FORMAT));
		memcpy( &EncodeSimp.dstMainFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt,sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void CConfigChannel::OnCheckExpandVideo() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if (m_bMultiStream)
	{
		if (nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_allData.dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExtraFormat = dstExtraFmt.vfFormat;
			dstExtraFmt.bVideoEnable = ((CButton *)GetDlgItem(IDC_CHECK_EXPAND_VIDEO))->GetCheck();
			AllStructToWinData(0, &m_allData, MAIN_STREAM);
			AllStructToWinData(0, &m_allData, EXPAND_STREAM);
		}
		else
		{
			SDK_MEDIA_FORMAT &dstExtraFmt = m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt;
			SDK_VIDEO_FORMAT &vfExtraFormat = dstExtraFmt.vfFormat;
			dstExtraFmt.bVideoEnable = ((CButton *)GetDlgItem(IDC_CHECK_EXPAND_VIDEO))->GetCheck();
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], MAIN_STREAM);
			NormalStructToWinData(nChannelNum, &m_EncodeConfig.vEncodeConfigAll[nChannelNum], EXPAND_STREAM);
		}
		
		//GetDlgItem(IDC_COMBO_EXPAND_QUALITY)->EnableWindow( GetComboBoxData(IDC_COMBO_EXPAND_BITCONTROL) && m_sysEncode.vEncodeConfigAll[nChannelNum].dstExtraFmt[0].bVideoEnable );
		//GetDlgItem(IDC_COMBO_EXPAND_BIT_RATE)->EnableWindow( !GetComboBoxData(IDC_COMBO_EXPAND_BITCONTROL) && m_sysEncode.vEncodeConfigAll[nChannelNum].dstExtraFmt[0].bVideoEnable );
	}
	else if (m_bCombineEncode)
	{
		SDK_MEDIA_FORMAT &dstMainFmt = m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt[0];
		SDK_VIDEO_FORMAT &vfFormat = dstMainFmt.vfFormat;
		dstMainFmt.bVideoEnable = ((CButton *)GetDlgItem(IDC_CHECK_COMBINE_ENCODE))->GetCheck();
		SDK_CONFIG_ENCODE_SIMPLIIFY EncodeSimp;
		memcpy( &EncodeSimp.dstExtraFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstExtraFmt,sizeof(SDK_MEDIA_FORMAT));
		memcpy( &EncodeSimp.dstMainFmt,&m_CmbEncodeCfg.vEncodeConfigAll[0].dstMainFmt,sizeof(SDK_MEDIA_FORMAT));
		CombineStructToWinData(0, &EncodeSimp, COMBINE_STREAM);
	}
}

void CConfigChannel::OnCheckMainAudio() 
{
	// TODO: Add your control notification handler code here
	int nChannelNum = m_ChanNo.GetCurSel();
	if ( nChannelNum == m_DevAttribute.deviveInfo.byChanNum )
	{
		nChannelNum = 0;
	}
	
	BOOL bEnable = FALSE; 

	BOOL bChoose = ((CButton *)GetDlgItem(IDC_CHECK_MAIN_AUDIO))->GetCheck();
	if ( bChoose )
	{
		bEnable = TRUE;
		if ( !((CButton *)GetDlgItem(IDC_CHECK_MAIN_VIDEO))->GetCheck() )
		{
			bEnable = FALSE;
			((CButton *)GetDlgItem(IDC_CHECK_MAIN_AUDIO))->SetCheck(FALSE);
		}
	}
	
	m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstMainFmt.bAudioEnable = bEnable;
}

void CConfigChannel::OnCheckExpandAudio() 
{
	// TODO: Add your control notification handler code here
	if (m_bMultiStream)
	{
		int nChannelNum = m_ChanNo.GetCurSel();
		if ( nChannelNum == m_DevAttribute.deviveInfo.byChanNum )
		{
			nChannelNum = 0;
		}
		
		BOOL bEnable = FALSE; 
		BOOL bChoose = ((CButton *)GetDlgItem(IDC_CHECK_EXPAND_AUDIO))->GetCheck();
		if ( bChoose )
		{
			bEnable = TRUE;
			if ( !((CButton *)GetDlgItem(IDC_CHECK_EXPAND_VIDEO))->GetCheck() )
			{
				((CButton *)GetDlgItem(IDC_CHECK_EXPAND_AUDIO))->SetCheck(FALSE);
				bEnable = FALSE;
			}
		}	
		m_EncodeConfig.vEncodeConfigAll[nChannelNum].dstExtraFmt.bAudioEnable = bEnable;
	}
}

bool CConfigChannel::WinToStruct()
{
	int nChannelNum = m_ChanNo.GetCurSel();
	
	if ( nChannelNum == m_DevAttribute.deviveInfo.byChanNum)
	{
		
		AllWinDataToStruct(0);
		for (int i = 0; i < nChannelNum; i ++)
		{
			memcpy(&m_EncodeConfig.vEncodeConfigAll[i], &m_allData, sizeof(m_EncodeConfig.vEncodeConfigAll[i]) );
		}
	}
	else
	{
		NomalWinDataToStruct(nChannelNum);
	}
	CombineWinDataToStruct(0);
	return true;
}

bool CConfigChannel::CombineWinDataToStruct(int nChannelNum)
{
	if (m_bCombineEncode)
	{
		WinDataToStruct(m_CmbEncodeCfg.vEncodeConfigAll[nChannelNum].dstMainFmt[0], COMBINE_STREAM);
	}
	return true;
}
