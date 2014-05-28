// ConfigOutput.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigOutput.h"
#include "ChannelNameSet2.h"
#include "TitleSetDlg.h"
#include "ClientDemo5Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigOutput dialog


CConfigOutput::CConfigOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigOutput::IDD, pParent)
	, m_nLastChanItem(0)
{
	//{{AFX_DATA_INIT(CConfigOutput)

	//}}AFX_DATA_INIT
	for (int i = 0; i < NET_COVERNUM; i++)
	{
		m_pBtnsCover[i] = NULL;
	}
}


void CConfigOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigOutput)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctlChannel);
	DDX_Control(pDX, IDC_CHECK_TIMETITLE, m_ctlTimeTitle);
	DDX_Control(pDX, IDC_CHECK_CHANTITLE, m_ctlChanTitle);
	DDX_Control(pDX, IDC_CHECK_COVER, m_ctlCover);
	DDX_Control(pDX, IDC_CHECK_ALMSTATUS_DVR, m_ctlAlmStatusD);
	DDX_Control(pDX, IDC_CHECK_CHANTITLE_DVR, m_ctlChanTitleD);
	DDX_Control(pDX, IDC_CHECK_TIMETITLE_DVR, m_ctlTimeTitleD);
	DDX_Control(pDX, IDC_SLIDER_TRANSPAR_DVR, m_ctlTransparD);
	DDX_Control(pDX, IDC_CHECK_RESITWITE_DVR, m_ctlResitWiteD);
	DDX_Control(pDX, IDC_CHECK_RECORDSTATUE_DVR, m_ctlRecordStatusD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigOutput, CDialog)
	//{{AFX_MSG_MAP(CConfigOutput)
	ON_BN_CLICKED(IDC_BUTTON_CHANNS, OnBtnChanNS)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_CHECK_COVER, OnCheckCoverBtns)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TRANSPAR_DVR, OnCusdraSliderTransparDvr)
	ON_BN_CLICKED(IDC_BUTTON_TITLESET, OnBtnTitleset)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnBtnApply)
	ON_BN_CLICKED(IDC_BUTTON_COVSET, OnBtnCovset)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigOutput message handlers

BOOL CConfigOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_ctlTransparD.SetRange(iWndAlphaSlideMin,iWndAlphaSlideMax);
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigOutput::InitDlgInfo(OUTPUTCONFIGALL* pOutputCfgAll,int nbyChanNum)
{
     memcpy(&m_outputCfgAll,pOutputCfgAll,sizeof(OUTPUTCONFIGALL));
	 m_nbyChanNum = nbyChanNum;
	 if (((CClientDemo5Dlg*) AfxGetMainWnd())->m_bOutputCfg[0])
	 {
		GetDlgItem(IDC_BUTTON_CHANNS)->EnableWindow(TRUE);
	 }
	 else
	 {
	 	GetDlgItem(IDC_BUTTON_CHANNS)->EnableWindow(FALSE);
	 }

     InitGUISetCfgInfo();
	 InitVidWdgCfgInfo();

}

void CConfigOutput::OnBtnChanNS() 
{
	// TODO: Add your control notification handler code here
	CChannelNameSet2 dlg;
	dlg.DoModal();
}

void CConfigOutput::InitGUISetCfgInfo()
{
	if ( !((CClientDemo5Dlg*)AfxGetMainWnd())->m_bOutputCfg[1])
	{
		m_ctlChanTitleD.EnableWindow(FALSE);
		m_ctlTimeTitleD.EnableWindow(FALSE);
		m_ctlAlmStatusD.EnableWindow(FALSE);
		m_ctlRecordStatusD.EnableWindow(FALSE);
		m_ctlResitWiteD.EnableWindow(FALSE);
		m_ctlTransparD.EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_TRANSPARNUM)->EnableWindow(FALSE);
	} 
	else
	{
		m_ctlChanTitleD.EnableWindow(TRUE);
		m_ctlTimeTitleD.EnableWindow(TRUE);
		m_ctlAlmStatusD.EnableWindow(TRUE);
		m_ctlRecordStatusD.EnableWindow(TRUE);
		m_ctlResitWiteD.EnableWindow(TRUE);
		m_ctlTransparD.EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_TRANSPARNUM)->EnableWindow(SW_SHOW);

		BOOL bTimeTitle = m_outputCfgAll.GUISetCfg.bTimeTitleEn;
		BOOL bChanTitle = m_outputCfgAll.GUISetCfg.bChannelTitleEn;
		BOOL bRecordStatus = m_outputCfgAll.GUISetCfg.bRecordStatus;
		BOOL bAlarmStatus = m_outputCfgAll.GUISetCfg.bAlarmStatus;
		BOOL bDeflick = m_outputCfgAll.GUISetCfg.bDeflick;
		
		int iWndAlpha = m_outputCfgAll.GUISetCfg.iWindowAlpha;
		CString str;
		str.Format("%d",iWndAlpha);
		
		m_ctlChanTitleD.SetCheck(bChanTitle);
		m_ctlTimeTitleD.SetCheck(bTimeTitle);
		m_ctlAlmStatusD.SetCheck(bAlarmStatus);
		m_ctlRecordStatusD.SetCheck(bRecordStatus);
		m_ctlResitWiteD.SetCheck(bDeflick);
		m_ctlTransparD.SetPos(iWndAlpha);
		
		GetDlgItem(IDC_STATIC_TRANSPARNUM)->SetWindowText(str);
	}

}

void CConfigOutput::InitVidWdgCfgInfo()
{
	if ( !((CClientDemo5Dlg*)AfxGetMainWnd())->m_bOutputCfg[2])
	{
        m_ctlChannel.EnableWindow(FALSE);
		m_ctlTimeTitle.EnableWindow(FALSE);
		m_ctlChanTitle.EnableWindow(FALSE);
		m_ctlCover.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_COVSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TITLESET)->EnableWindow(FALSE);
	} 
	else
	{
		m_ctlChannel.EnableWindow(TRUE);
		m_ctlTimeTitle.EnableWindow(TRUE);
		m_ctlChanTitle.EnableWindow(TRUE);
		m_ctlCover.EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_COVSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_TITLESET)->EnableWindow(TRUE);


		m_ctlChannel.ResetContent();
		CString str;

		int i = 0;
		for( ;i < m_nbyChanNum; ++i)
		{
		   str.Format(_T("%d"),i + 1);
		   m_ctlChannel.AddString(str);
		// m_ctlChannel.SetItemData(nIndex,i);
		}
		m_ctlChannel.SetCurSel(m_nLastChanItem);

		SetBtns();

		BOOL bencodeTimeTit;
		BOOL bencodeChanTit;

		bencodeChanTit = m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem].ChannelTitle.bEncodeBlend;
		m_ctlChanTitle.SetCheck(bencodeChanTit);

		bencodeTimeTit = m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem].TimeTitle.bEncodeBlend;
		m_ctlTimeTitle.SetCheck(bencodeTimeTit);

		OnCheckCoverBtns();
	}

}
 
void CConfigOutput::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here

	for (int i = 0; i < NET_COVERNUM; i++)
	{
		if (m_pBtnsCover[i])
		{

			delete m_pBtnsCover[i];
			m_pBtnsCover[i] = NULL;
		} 
	}

	InitGUISetCfgInfo();
	InitVidWdgCfgInfo();
}

void CConfigOutput::OnCheckCoverBtns() 
{
	// TODO: Add your control notification handler code here
	BOOL bRet = m_ctlCover.GetCheck();
	GetDlgItem(IDC_BUTTON_COVSET)->ShowWindow(bRet);
	int nBlindCoverNum = m_outputCfgAll.BlindDetFunc[m_nLastChanItem].iBlindConverNum;
    int i = 0;
	for (;i < nBlindCoverNum; ++ i)
    {
     	GetDlgItem(IDC_BTN_OUTPUT_COVER + i)->ShowWindow(bRet);
    }
}

void CConfigOutput::OnCusdraSliderTransparDvr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nTranspr = m_ctlTransparD.GetPos();
	CString str;
	str.Format("%d",nTranspr);
	GetDlgItem(IDC_STATIC_TRANSPARNUM)->SetWindowText(str);

	*pResult = 0;
}

void CConfigOutput::OnBtnTitleset() 
{
	// TODO: Add your control notification handler code here
	CTitleSetDlg dlg;
	dlg.DoModal();
}

void CConfigOutput::OnBtnApply() 
{
	// TODO: Add your control notification handler code here
    UpdateData();
	m_outputCfgAll.GUISetCfg.bTimeTitleEn = m_ctlTimeTitleD.GetCheck();
    m_outputCfgAll.GUISetCfg.bChannelTitleEn = m_ctlChanTitleD.GetCheck();
    m_outputCfgAll.GUISetCfg.bRecordStatus = m_ctlRecordStatusD.GetCheck();
    m_outputCfgAll.GUISetCfg.bAlarmStatus = m_ctlAlmStatusD.GetCheck();
    m_outputCfgAll.GUISetCfg.bDeflick = m_ctlResitWiteD.GetCheck();
    m_outputCfgAll.GUISetCfg.iWindowAlpha= m_ctlTransparD.GetPos();
	
    GetBtns();

	m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem].ChannelTitle.bEncodeBlend = m_ctlChanTitle.GetCheck();
	m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem].TimeTitle.bEncodeBlend = m_ctlTimeTitle.GetCheck();

	((CClientDemo5Dlg*)AfxGetMainWnd())->SetOutputConfigInfo(&m_outputCfgAll);

}

void CConfigOutput::OnBtnCovset() 
{
	// TODO: Add your control notification handler code here
	GetBtns();
	
	m_dlgCoverSet.m_dlgCoverArea.m_Videowidget = 
	                 m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem];
	m_dlgCoverSet.m_dlgCoverArea.m_nCoverNum = m_outputCfgAll.BlindDetFunc[m_nLastChanItem].iBlindConverNum;
	m_dlgCoverSet.m_dlgCoverArea.m_nChannelNum = m_nLastChanItem;

	if (IDOK == m_dlgCoverSet.DoModal())
	{
	    memcpy( &m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem],
          	          &m_dlgCoverSet.m_dlgCoverArea.m_Videowidget,sizeof(SDK_CONFIG_VIDEOWIDGET) );
	}
}

void CConfigOutput::GetBtns(){

	BOOL bRet = m_ctlCover.GetCheck();
	int nBlindCoverNum = m_outputCfgAll.BlindDetFunc[m_nLastChanItem].iBlindConverNum;
	int i;
	for (i = 0;i < nBlindCoverNum;++ i)
	{
		if (TRUE == bRet)
		{
			m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem].dstCovers[i].bEncodeBlend
				= m_pBtnsCover[i]->GetCheck();
		}
        else
		{
			m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem].dstCovers[i].bEncodeBlend
				= bRet;		 
		}
		
	}
}

void CConfigOutput::SetBtns()
{
	CString csBtnTitle;
	
	CRect rcBtn;
	GetDlgItem(IDC_CHECK_COVER)->GetWindowRect(rcBtn);
	ScreenToClient(rcBtn);
	
	int nBlindCoverNum = m_outputCfgAll.BlindDetFunc[m_nLastChanItem].iBlindConverNum;
	rcBtn.top += 25;
	rcBtn.bottom += 25;
	int i = 0;
	for (;i < nBlindCoverNum; ++ i)
	{
		if (!m_pBtnsCover[i])
		{
			csBtnTitle.Format("%d",i + 1);
			m_pBtnsCover[i] = new CButton();
			m_pBtnsCover[i]->Create(csBtnTitle,BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE|BS_PUSHLIKE,rcBtn,this,IDC_BTN_OUTPUT_COVER + i);
			rcBtn.left += 20;
			rcBtn.right += 20;
		}
		
	}
	//setBtns
	BOOL bRet;

	m_ctlCover.SetCheck(FALSE);
	for (i = 0;i < nBlindCoverNum;++ i)
	{
        bRet = m_outputCfgAll.VideoWdtCfgAll.vVideoWidegetConfigAll[m_nLastChanItem].dstCovers[i].bEncodeBlend;
        m_pBtnsCover[i]->SetCheck(bRet);
		if (TRUE == bRet)
		{
			m_ctlCover.SetCheck(TRUE);
		}
	}
}

void CConfigOutput::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	m_nLastChanItem = m_ctlChannel.GetCurSel();
    InitVidWdgCfgInfo();
}

void CConfigOutput::CleanAll()
{
	m_ctlChannel.ResetContent();
	m_ctlTimeTitle.SetCheck(FALSE);
	m_ctlChanTitle.SetCheck(FALSE);
	m_ctlCover.SetCheck(FALSE);
	m_ctlAlmStatusD.SetCheck(FALSE);
	m_ctlChanTitleD.SetCheck(FALSE);
	m_ctlTimeTitleD.SetCheck(FALSE);
	m_ctlTransparD.SetPos(-1);
	m_ctlResitWiteD.SetCheck(FALSE);
	m_ctlRecordStatusD.SetCheck(FALSE);
	OnCheckCoverBtns();

}
