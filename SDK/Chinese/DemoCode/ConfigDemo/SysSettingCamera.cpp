// SysSettingCamera.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "SysSettingCamera.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysSettingCamera dialog


CSysSettingCamera::CSysSettingCamera( CWnd* pParent /*=NULL*/)
	: CDialog(CSysSettingCamera::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysSettingCamera)
	m_bMirror = FALSE;
	m_bRoll = FALSE;
	m_bFlicker = FALSE;
	m_bIcrSwap = FALSE;
	m_nTime = -1;
	//}}AFX_DATA_INIT
	m_nLastNum = 0;
	m_nTotalNum = 0;
	nSliderDncMin = 10;
	nSliderDncMax = 50;
	nSliderSstMin = 1;
	nSliderSstMax = 10;
	memset( &m_AllCameraPara, 0 , sizeof(SDK_AllCameraParam));
	memset( &m_CameraAbility, 0 , sizeof(SDK_CameraAbility));
}

void CSysSettingCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysSettingCamera)
	DDX_Control(pDX, IDC_COMBO_NTLEVEL, m_ctrlNTLevel);
	DDX_Control(pDX, IDC_RADIO_DAY, m_ctrlTime);
	DDX_Control(pDX, IDC_CHECK_IR_SWAP, m_ctrlIcrSwap);
	DDX_Control(pDX, IDC_EDIT_DEBUG, m_editDebug);
	DDX_Control(pDX, IDC_SLIDER_DNC, m_ctrlDnc);
	DDX_Control(pDX, IDC_SLIDER_SENSITIVITY, m_ctrlSensitivity);
	DDX_Control(pDX, IDC_CHECK_FLICKER, m_ctrlFilcker);
	DDX_Control(pDX, IDC_EDIT_GAINMOST, m_editGainMost);
	DDX_Control(pDX, IDC_COMBO_SHUTTER, m_ctrShutter);
	DDX_Control(pDX, IDC_COMBO_AUTOGAIN, m_ctrlAutoGain);
	DDX_Control(pDX, IDC_EDIT_DEFAULT, m_editDefault);
	DDX_Control(pDX, IDC_EDIT_AE, m_editAE);
	DDX_Control(pDX, IDC_COMBO_IRCUT, m_ctrlIRCUT);
	DDX_Control(pDX, IDC_EDIT_MOSTTIME, m_editMosttime);
	DDX_Control(pDX, IDC_EDIT_LEASTTIME, m_EditLeasttime);
	DDX_Control(pDX, IDC_CHECK_ROLL, m_ctrlroll);
	DDX_Control(pDX, IDC_CHECK_MIRROR, m_ctrlMirror);
	DDX_Control(pDX, IDC_COMBO_AUTO, m_ctrlAuto);
	DDX_Control(pDX, IDC_COMBO_BACKLIGHT, m_ctrlBackLight);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ctrlType);
	DDX_Control(pDX, IDC_COMBO_EXPOSURE, m_ctrlExposure);
	DDX_Control(pDX, IDC_COMBO_DAYNIGHT, m_ctrlDayNight);
	DDX_Control(pDX, IDC_COMBO_BALANCE, m_ctrlBalance);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctrlChannel);
	DDX_Check(pDX, IDC_CHECK_MIRROR, m_bMirror);
	DDX_Check(pDX, IDC_CHECK_ROLL, m_bRoll);
	DDX_Check(pDX, IDC_CHECK_FLICKER, m_bFlicker);
	DDX_Check(pDX, IDC_CHECK_IR_SWAP, m_bIcrSwap);
	DDX_Radio(pDX, IDC_RADIO_DAY, m_nTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysSettingCamera, CDialog)
	//{{AFX_MSG_MAP(CSysSettingCamera)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_EXPOSURE, OnSelchangeComboExposure)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_BN_CLICKED(IDC_BTN_UPGRADE, OnBtnUpgrade)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTOGAIN, OnSelchangeComboAutogain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DNC, OnCustomdrawSliderDnc)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SENSITIVITY, OnCustomdrawSliderSensitivity)
	ON_EN_CHANGE(IDC_EDIT_LEASTTIME, OnChangeEditLeasttime)
	ON_EN_KILLFOCUS(IDC_EDIT_LEASTTIME, OnEnKillfocusEditLeasttime)
	ON_EN_CHANGE(IDC_EDIT_MOSTTIME, OnEnChangeEditMosttime)
	ON_EN_KILLFOCUS(IDC_EDIT_MOSTTIME, OnEnKillfocusEditMosttime)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBnClickedBtnSend)
	ON_EN_CHANGE(IDC_EDIT_AE, OnEnChangeEditAe)
	ON_EN_KILLFOCUS(IDC_EDIT_AE, OnEnKillfocusEditAe)
	ON_EN_CHANGE(IDC_EDIT_GAINMOST, OnEnChangeEditGainmost)
	ON_EN_KILLFOCUS(IDC_EDIT_GAINMOST, OnEnKillfocusEditGainmost)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO_DAY, OnRadioDay)
	ON_BN_CLICKED(IDC_RADIO_NIGHT, OnRadioNight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysSettingCamera message handlers

void CSysSettingCamera::OnOK() 
{
	// TODO: Add extra validation here
	if ( m_ctrlChannel.GetCurSel() != -1 )
	{
		SaveCameraAll();
		((CClientDemo5Dlg *)AfxGetMainWnd())->SetCameraPara(&m_AllCameraPara);
	}
	//CDialog::OnOK();
}

void CSysSettingCamera::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

BOOL CSysSettingCamera::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	m_ctrlDnc.SetRange(nSliderDncMin,nSliderDncMax);
	m_ctrlSensitivity.SetRange(nSliderSstMin,nSliderSstMax);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSysSettingCamera::InitDlgInfo(SDK_AllCameraParam *pCameraParaAll, SDK_CameraAbility* pCameraAbility,int nTotalNum)
{
	if ( pCameraAbility )
	{
		memcpy( &m_CameraAbility, pCameraAbility, sizeof(SDK_CameraAbility));
	}else
	{
		return;
	}
	
	if ( pCameraParaAll )
	{
		memcpy( &m_AllCameraPara, pCameraParaAll, sizeof(SDK_AllCameraParam));
	}else
	{
		return;
	}
	
	CString str;
	m_ctrlChannel.ResetContent();   //通道
	int i = 0;
	for ( ; i < nTotalNum; i++)
	{
		str.Format(_T("%d"), i + 1);
		m_ctrlChannel.AddString(str);
	}
	m_ctrlChannel.AddString(_CS(_T("OneClick.All")));
	m_nTotalNum = nTotalNum;
	m_ctrlChannel.SetCurSel(m_nLastNum);

	m_ctrlDayNight.ResetContent();  //  日/夜模式
	m_ctrlDayNight.AddString(_CS(_T("CameraPara.AutoOper")));
	m_ctrlDayNight.AddString(_CS(_T("CameraPara.Colour")));
	m_ctrlDayNight.AddString(_CS(_T("CameraPara.BlackWhite")));
	m_ctrlDayNight.SetCurSel(pCameraParaAll->vCameraParamAll[m_nLastNum].dayNightColor);

	m_ctrlBackLight.ResetContent();  //背光补偿
	m_ctrlBackLight.AddString(_CS(_T("CameraPara.OFF")));
	m_ctrlBackLight.AddString(_CS(_T("CameraPara.ON")));
	m_ctrlBackLight.AddString(_CS(_T("CameraPara.AutoOper")));

	m_ctrlAuto.ResetContent();  //自动光圈	
	m_ctrlAuto.AddString(_CS(_T("CameraPara.OFF")));
	m_ctrlAuto.AddString(_CS(_T("CameraPara.ON")));




//	m_ctrlBalance.ResetContent();  //白平衡
//	CString strWhiteBalance;
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.Disable")));  //禁止
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.AutoOper")));  //自动
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.Daylight")));   //日光 6500k
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.Cloudy")));  //阴天 7500k
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.IncandeScence"))); //白热光 5000k
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.Fluorescent"))); //日光灯 4400k
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.TungSten"))); //钨丝灯 2800k
//	m_ctrlBalance.AddString(_CS(_T("CameraPara.HandOper")));  //手动
	
	m_ctrlBalance.ResetContent();  //白平衡
	CString strWhiteBalance;
	m_ctrlBalance.AddString(_CS(_T("CameraPara.AutoOper")));  //自动
	m_ctrlBalance.AddString(_CS(_T("CameraPara.Indoor")));  //手动
	m_ctrlBalance.AddString(_CS(_T("CameraPara.Outdoor")));  //禁止


	m_ctrlType.ResetContent();   //信号类型
	m_ctrlType.AddString(_CS(_T("CameraPara.Input")));
	m_ctrlType.SetCurSel(0);  //暂时默认为0

	m_ctrlExposure.ResetContent();  //曝光模式
	CString strExposure;
	m_ctrlExposure.AddString(_CS(_T("CameraPara.AutoOper")));

	//曝光能力级
	for ( i = 0; i < pCameraAbility->count; i++ )
	{
		str.Format(_T("1/%d"), (int)((float)1000000 / (float)(pCameraAbility->speeds[i])));
		strExposure = _CS(_T("CameraPara.HandOper")) + _T("_") + str;
		m_ctrlExposure.AddString(strExposure);
	}

	//自动增益
	m_ctrlAutoGain.ResetContent();
	CString strAutoGain;
	int OnOFF;
	OnOFF=m_AllCameraPara.vCameraParamAll[m_nLastNum].gainConfig.autoGain;
	m_ctrlAutoGain.AddString(_CS("PtzControl.AuxOpen"));
	m_ctrlAutoGain.AddString(_CS("PtzControl.AuxOff"));


	
	m_ctrlAutoGain.SetCurSel(!OnOFF);
	m_editGainMost.EnableWindow(OnOFF);
	//自动增益上限
	CString strGainMost;
	strGainMost.Format(_T("%d"),m_AllCameraPara.vCameraParamAll[m_nLastNum].gainConfig.gain);
	m_editGainMost.SetWindowText(strGainMost);
	//自动曝光参考
	m_editAE.SetWindowText("");
	CString strAE;
	strAE.Format(_T("%d"),m_AllCameraPara.vCameraParamAll[m_nLastNum].elecLevel);
	m_editAE.SetWindowText(strAE);
	
	//曝光参考默认值
	CString strDefault;
	strDefault.Format(_T("%d"),50);
	m_editDefault.SetWindowText(strDefault);
	
	//电子慢快门
	CString strShutter;
	m_ctrShutter.ResetContent();
	m_ctrShutter.AddString(_CS(_T("PtzControl.None")));
	m_ctrShutter.AddString(_CS(_T("CameraShutter.Low")));
	m_ctrShutter.AddString(_CS(_T("CameraShutter.Middle")));		
	m_ctrShutter.AddString(_CS(_T("CameraShutter.Strong")));

	//IR-CUT切换 0 = 红外灯同步切换 1 = 自动切换
	m_ctrlIRCUT.ResetContent();
	m_ctrlIRCUT.AddString(_CS(_T("CameraPara.SyncSwitch")));
	m_ctrlIRCUT.AddString(_CS(_T("CameraPara.AutoSwitch")));

    m_ctrlNTLevel.ResetContent();

	for (i = 0;i <= 5;++ i)
	{
	   str.Format("%d",i);
	   m_ctrlNTLevel.AddString(_T(str));
	}
    m_nTime = 0;
	ShowCamera(m_nLastNum);
	UpdateData(FALSE);
}

void CSysSettingCamera::OnSelchangeComboExposure() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int nIndex = m_ctrlExposure.GetCurSel();
	if (m_nTotalNum > 0)
	{
		if ( !nIndex )
		{
			GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LINE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_MS)->ShowWindow(SW_SHOW);
			m_EditLeasttime.ShowWindow(SW_SHOW);
			m_editMosttime.ShowWindow(SW_SHOW);

		}else
		{
			GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LINE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MS)->ShowWindow(SW_HIDE);
			m_EditLeasttime.ShowWindow(SW_HIDE);
			m_editMosttime.ShowWindow(SW_HIDE);
		}
	}
}

void CSysSettingCamera::SaveCamera(int nChannel)
{
	UpdateData();
	CString strLeast, strMost;
	CString str;
	if ( m_ctrlExposure.GetCurSel() == 0)
	{
		m_editMosttime.GetWindowText(strMost);
		m_EditLeasttime.GetWindowText(strLeast);
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.leastTime = atof(strLeast) * 1000;
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.mostTime = atof(strMost) * 1000;
	}else if(m_ctrlExposure.GetCurSel() >0)
	{
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.leastTime = 0;
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.mostTime = 0;
	}
	else
	{
		return;
	}
	m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.level = m_ctrlExposure.GetCurSel();
	
	m_AllCameraPara.vCameraParamAll[nChannel].dayNightColor = m_ctrlDayNight.GetCurSel();
	m_AllCameraPara.vCameraParamAll[nChannel].whiteBalance = m_ctrlBalance.GetCurSel();
	m_AllCameraPara.vCameraParamAll[nChannel].BLCMode  = m_ctrlBackLight.GetCurSel();
	m_AllCameraPara.vCameraParamAll[nChannel].apertureMode = m_ctrlAuto.GetCurSel();
	m_AllCameraPara.vCameraParamAll[nChannel].gainConfig.autoGain=!m_ctrlAutoGain.GetCurSel();

	m_editAE.GetWindowText(str);
	m_AllCameraPara.vCameraParamAll[nChannel].elecLevel=atoi(str);
	m_AllCameraPara.vCameraParamAll[nChannel].EsShutter=m_ctrShutter.GetCurSel() * 2;
	m_AllCameraPara.vCameraParamAll[nChannel].dnc_thr = m_ctrlDnc.GetPos();
	m_AllCameraPara.vCameraParamAll[nChannel].ae_sensitivity = m_ctrlSensitivity.GetPos();
	m_AllCameraPara.vCameraParamAll[nChannel].ircut_mode = m_ctrlIRCUT.GetCurSel();

	m_AllCameraPara.vCameraParamAll[nChannel].PictureMirror = m_ctrlMirror.GetCheck();
	m_AllCameraPara.vCameraParamAll[nChannel].PictureFlip = m_ctrlroll.GetCheck();
	m_AllCameraPara.vCameraParamAll[nChannel].RejectFlicker = m_ctrlFilcker.GetCheck();
	m_AllCameraPara.vCameraParamAll[nChannel].Ircut_swap = m_ctrlIcrSwap.GetCheck();
	if (m_nTime == 0)
	{
		m_AllCameraPara.vCameraParamAll[nChannel].Day_nfLevel = m_ctrlNTLevel.GetCurSel();
	}else
	{
		m_AllCameraPara.vCameraParamAll[nChannel].Night_nfLevel = m_ctrlNTLevel.GetCurSel();
	}

	m_editGainMost.GetWindowText(str);
	m_AllCameraPara.vCameraParamAll[nChannel].gainConfig.gain=atoi(str);

}


void CSysSettingCamera::ShowCamera(int nChannel)
{
	CString str;
	m_ctrlExposure.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.level);
	m_ctrlBalance.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].whiteBalance);
	m_ctrlBackLight.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].BLCMode);
	m_ctrlAuto.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].apertureMode);
	m_ctrShutter.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].EsShutter / 2);
	m_ctrlIRCUT.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].ircut_mode);
	if (m_nTime == 0)
	{
		m_ctrlNTLevel.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].Day_nfLevel);
	}else
	{
		m_ctrlNTLevel.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].Night_nfLevel);
	}
//	m_ctrlNTLevel.SetCurSel(m_AllCameraPara.vCameraParamAll[m_nLastNum].nf_level[m_nTime]);

	m_bFlicker=m_AllCameraPara.vCameraParamAll[nChannel].RejectFlicker;
	m_bRoll=m_AllCameraPara.vCameraParamAll[nChannel].PictureFlip;
	m_bMirror=m_AllCameraPara.vCameraParamAll[nChannel].PictureMirror;
	m_bIcrSwap = m_AllCameraPara.vCameraParamAll[nChannel].Ircut_swap;
	//日夜转换阈值
	m_ctrlDnc.SetPos(m_AllCameraPara.vCameraParamAll[nChannel].dnc_thr);
	str.Format("%d",m_ctrlDnc.GetPos());
	GetDlgItem(IDC_STATIC_DNC)->SetWindowText(str);
	//AE 灵敏度
	m_ctrlSensitivity.SetPos(m_AllCameraPara.vCameraParamAll[nChannel].ae_sensitivity);
	str.Format("%d",m_ctrlSensitivity.GetPos());
	GetDlgItem(IDC_STATIC_SENSITIVITY)->SetWindowText(str);
	UpdateData(FALSE);
	if ( !m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.level )
	{
		GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LINE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MS)->ShowWindow(SW_SHOW);
		m_EditLeasttime.ShowWindow(SW_SHOW);
		m_editMosttime.ShowWindow(SW_SHOW);
		str.Format(_T("%f"), m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.leastTime / 1000.0);
		m_EditLeasttime.SetWindowText(str);
		str.Format(_T("%f"), m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.mostTime / 1000.0);
		m_editMosttime.SetWindowText(str);


	}else
	{
		GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MS)->ShowWindow(SW_HIDE);
		m_EditLeasttime.ShowWindow(SW_HIDE);
		m_editMosttime.ShowWindow(SW_HIDE);
	}



}

void CSysSettingCamera::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctrlChannel.GetCurSel();
	if (m_nTotalNum > 0)
	{
		if ( nIndex ==  m_nTotalNum)  //全通道
		{
			m_nLastNum = nIndex;
			ShowCamera(0);
		}else if ( m_nLastNum == m_nTotalNum ) //之前通道是全通道，不进行保存，直接显示
		{
			m_nLastNum = nIndex;
			ShowCamera(nIndex);
		}else
		{
			if ( nIndex != m_nLastNum )
			{
				SaveCamera(m_nLastNum);
				m_nLastNum = nIndex;
				ShowCamera(nIndex);
			}
		}
	}
}

void CSysSettingCamera::SaveCameraAll()
{
	int nIndex = m_ctrlChannel.GetCurSel();
	if ( nIndex == m_nTotalNum )
	{
		for ( int i  = 0; i < m_nTotalNum; i ++)
		{
			SaveCamera(i);
		}
	}else
	{
		SaveCamera(nIndex);
	}
}

void CSysSettingCamera::CleanAll()
{
	m_nTotalNum = 0;
	m_nLastNum = 0;
	m_ctrlChannel.SetCurSel(-1);
	m_ctrlExposure.SetCurSel(-1);
	m_ctrlDayNight.SetCurSel(-1);
	m_ctrlBackLight.SetCurSel(-1);
	m_ctrlBalance.SetCurSel(-1);
	m_ctrlType.SetCurSel(-1);
	m_ctrlAuto.SetCurSel(-1);
	m_ctrlMirror.SetCheck(FALSE);
	m_ctrlroll.SetCheck(FALSE);
	m_ctrlIcrSwap.SetCheck(FALSE);
	memset( &m_AllCameraPara, 0 , sizeof(SDK_AllCameraParam));
	memset( &m_CameraAbility, 0 , sizeof(SDK_CameraAbility));
	m_editMosttime.SetWindowText(_T(""));
	m_EditLeasttime.SetWindowText(_T(""));
	m_editAE.SetWindowText(_T(""));
	m_editDefault.SetWindowText(_T(""));
	m_ctrlAutoGain.SetCurSel(-1);
	m_ctrShutter.SetCurSel(-1);
	m_editGainMost.SetWindowText(_T(""));
	m_ctrlDnc.SetPos(nSliderDncMin);
	m_ctrlSensitivity.SetPos(nSliderSstMin);
	GetDlgItem(IDC_STATIC_DNC)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_SENSITIVITY)->SetWindowText(_T(""));
	m_ctrlIRCUT.SetCurSel(-1);
	m_ctrlNTLevel.SetCurSel(-1);
//	m_ctrlTime.SetCheck(-1);
}	

void CSysSettingCamera::OnBtnUpgrade() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg *)AfxGetMainWnd())->GetCameraPara();
}

void CSysSettingCamera::OnSelchangeComboAutogain() 
{
	// TODO: Add your control notification handler code here
	int  sel;
	sel= m_ctrlAutoGain.GetCurSel();
	m_editGainMost.EnableWindow(!sel);


}

void CSysSettingCamera::OnCustomdrawSliderDnc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nTotalNum > 0)
	{
		int nDnc = m_ctrlDnc.GetPos();
		CString str;
		str.Format(_T("%d"), nDnc);
		GetDlgItem(IDC_STATIC_DNC)->SetWindowText(str);

		CRect rc;
		GetDlgItem(IDC_STATIC_DNC)->GetWindowRect(&rc);
		ScreenToClient(&rc);
		InvalidateRect(rc);
	}
	*pResult = 0;
}

void CSysSettingCamera::OnCustomdrawSliderSensitivity(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_nTotalNum > 0)
	{
		CString str;
		int nSense = m_ctrlSensitivity.GetPos();
		CRect rc;
		str.Format (_T("%d"), nSense);
		GetDlgItem(IDC_STATIC_SENSITIVITY)->SetWindowText(str);
		GetDlgItem(IDC_STATIC_SENSITIVITY)->GetWindowRect(&rc);
		ScreenToClient(&rc);
		InvalidateRect(rc);
		*pResult = 0;
	}
}

void CSysSettingCamera::OnChangeEditLeasttime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strleastTime;
	m_EditLeasttime.GetWindowText(strleastTime);
	if ( atof(strleastTime) > 80 )
	{
		m_EditLeasttime.SetWindowText(_T("80"));
		UpdateData(FALSE);
	}
	
	m_EditLeasttime.SetFocus();
}

void CSysSettingCamera::OnEnKillfocusEditLeasttime() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strleastTime;
	m_EditLeasttime.GetWindowText(strleastTime);
	
	if ( atof(strleastTime) > 80 )
	{
		m_EditLeasttime.SetWindowText(_T("80"));
		UpdateData(FALSE);
		return;
	}
	
	if ( atof(strleastTime) < 0.1 )
	{
		m_EditLeasttime.SetWindowText(_T("0.1"));
		UpdateData(FALSE);
	}
	
	CString strMostTime;
	m_EditLeasttime.GetWindowText(strMostTime);
	if ( atof(strleastTime) > atof(strMostTime))
	{
		m_EditLeasttime.SetWindowText(strleastTime);
		UpdateData(FALSE);
	}
}

void CSysSettingCamera::OnEnChangeEditMosttime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strmostTime;
	
	m_editMosttime.GetWindowText(strmostTime);
	if ( atof(strmostTime) > 80 )
	{
		m_editMosttime.SetWindowText(_T("80"));
		UpdateData(FALSE);
	}
	
	m_editMosttime.SetFocus();
}

void CSysSettingCamera::OnEnKillfocusEditMosttime() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strmostTime;
	m_editMosttime.GetWindowText(strmostTime);
	
	if ( atof(strmostTime) > 80 )
	{
		m_editMosttime.SetWindowText(_T("80"));
		UpdateData(FALSE);
		return;
	}
	
	CString strleastTime;
	m_editMosttime.GetWindowText(strleastTime);
	if ( atof(strleastTime) > atof(strmostTime))
	{
		m_editMosttime.SetWindowText(strleastTime);
		UpdateData(FALSE);
		return;
	}
	
	if ( atof(strmostTime) < 0.1 )
	{
		m_editMosttime.SetWindowText(_T("0.1"));
		UpdateData(FALSE);
	}

}

void CSysSettingCamera::OnBnClickedBtnSend() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CString strDebug;
	int nLen;
	DWORD dwTime = GetTickCount();
	UpdateData();
	m_editDebug.GetWindowText(strDebug);
	nLen = strDebug.GetLength();
	str.Format(_T("\n%d\n"), GetTickCount() - dwTime);
	TRACE(str);
}

void CSysSettingCamera::OnEnChangeEditAe() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strAE;
	
	m_editAE.GetWindowText(strAE);
	if ( atoi(strAE) > 100 )
	{
		m_editAE.SetWindowText(_T("100"));
		UpdateData(FALSE);
	}
	
	m_editAE.SetFocus();
}

void CSysSettingCamera::OnEnKillfocusEditAe() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strAE;
	m_editAE.GetWindowText(strAE);
	
	if ( atof(strAE) > 100 )
	{
		m_editAE.SetWindowText(_T("100"));
		UpdateData(FALSE);
		return;
	}
	
	if ( atof(strAE) < 0 )
	{
		m_editAE.SetWindowText(_T("0"));
		UpdateData(FALSE);
	}
}

void CSysSettingCamera::OnEnChangeEditGainmost() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strGain;
	
	m_editGainMost.GetWindowText(strGain);
	if ( atoi(strGain) > 100 )
	{
		m_editGainMost.SetWindowText(_T("100"));
		UpdateData(FALSE);
	}
	
	m_editGainMost.SetFocus();
}

void CSysSettingCamera::OnEnKillfocusEditGainmost() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	CString strGain;
	m_editGainMost.GetWindowText(strGain);
	
	if ( atof(strGain) > 100 )
	{
		m_editGainMost.SetWindowText(_T("100"));
		UpdateData(FALSE);
		return;
	}
	
	if ( atof(strGain) < 0 )
	{
		m_editGainMost.SetWindowText(_T("0"));
		UpdateData(FALSE);
	}
}

void CSysSettingCamera::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CleanAll();
}

void CSysSettingCamera::OnRadioDay() 
{
	// TODO: Add your control notification handler code here
//	UpdateData();
    m_AllCameraPara.vCameraParamAll[m_nLastNum].Night_nfLevel = m_ctrlNTLevel.GetCurSel();
	m_ctrlNTLevel.SetCurSel(m_AllCameraPara.vCameraParamAll[m_nLastNum].Day_nfLevel);;
	 
}
void CSysSettingCamera::OnRadioNight() 
{
	// TODO: Add your control notification handler code here
//	UpdateData();
    m_AllCameraPara.vCameraParamAll[m_nLastNum].Day_nfLevel = m_ctrlNTLevel.GetCurSel();
	m_ctrlNTLevel.SetCurSel(m_AllCameraPara.vCameraParamAll[m_nLastNum].Night_nfLevel);
	
}
