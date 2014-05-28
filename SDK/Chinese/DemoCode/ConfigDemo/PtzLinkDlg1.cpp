// PtzLinkDlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "ConfigModule.h"
#include "PtzLinkDlg1.h"
#include "UserDataManager.h"
extern   CConfigModuleApp   theApp;
// CPtzLinkDlg 对话框

IMPLEMENT_DYNAMIC(CPtzLinkDlg, CDialog)

CPtzLinkDlg::CPtzLinkDlg(SDK_PtzLinkConfig *pPtzLink, CWnd* pParent /*=NULL*/)
	: CDialog(CPtzLinkDlg::IDD, pParent)
	, m_nValue1(0)
	, m_nValue10(0)
	, m_nValue11(0)
	, m_nValue12(0)
	, m_nValue13(0)
	, m_nValue14(0)
	, m_nValue15(0)
	, m_nValue16(0)
	, m_nValue9(0)
	, m_nValue2(0)
	, m_nValue3(0)
	, m_nValue4(0)
	, m_nValue5(0)
	, m_nValue6(0)
	, m_nValue7(0)
	, m_nValue8(0)
	, m_nValue17(0)
	, m_nValue18(0)
	, m_nValue19(0)
	, m_nValue20(0)
	, m_nValue21(0)
	, m_nValue22(0)
	, m_nValue23(0)
	, m_nValue24(0)
	, m_nValue25(0)
	, m_nValue26(0)
	, m_nValue27(0)
	, m_nValue28(0)
	, m_nValue29(0)
	, m_nValue30(0)
	, m_nValue31(0)
	, m_nValue32(0)
{
	OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
	AfxSetResourceHandle(theApp.m_hInstance);//设置新的模块      	
	
	if ( NULL != pPtzLink)
	{
		memcpy(&m_PtzLink, pPtzLink, sizeof(m_PtzLink));
	}
	else
	{
		memset( &m_PtzLink, 0, sizeof(m_PtzLink) );
	}
}

CPtzLinkDlg::~CPtzLinkDlg()
{
}

void CPtzLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cmbChannel1);
	DDX_Control(pDX, IDC_COMBO10, m_cmbChannel10);
	DDX_Control(pDX, IDC_COMBO11, m_cmbChannel11);
	DDX_Control(pDX, IDC_COMBO12, m_cmbChannel12);
	DDX_Control(pDX, IDC_COMBO13, m_cmbChannel13);
	DDX_Control(pDX, IDC_COMBO14, m_cmbChannel14);
	DDX_Control(pDX, IDC_COMBO15, m_cmbChannel15);
	DDX_Control(pDX, IDC_COMBO16, m_cmbChannel16);
	DDX_Control(pDX, IDC_COMBO2, m_cmbChannel2);
	DDX_Control(pDX, IDC_COMBO3, m_cmbChannel4);
	DDX_Control(pDX, IDC_COMBO4, m_cmbChannel3);
	DDX_Control(pDX, IDC_COMBO5, m_cmbChannel5);
	DDX_Control(pDX, IDC_COMBO6, m_cmbChannel6);
	DDX_Control(pDX, IDC_COMBO7, m_cmbChannel7);
	DDX_Control(pDX, IDC_COMBO8, m_cmbChannel8);
	DDX_Control(pDX, IDC_COMBO9, m_cmbChannel9);
	DDX_Control(pDX, IDC_COMBO17, m_cmbChannel17);
	DDX_Control(pDX, IDC_COMBO18, m_cmbChannel18);
	DDX_Control(pDX, IDC_COMBO19, m_cmbChannel19);
	DDX_Control(pDX, IDC_COMBO20, m_cmbChannel20);
	DDX_Control(pDX, IDC_COMBO21, m_cmbChannel21);
	DDX_Control(pDX, IDC_COMBO22, m_cmbChannel22);
	DDX_Control(pDX, IDC_COMBO23, m_cmbChannel23);
	DDX_Control(pDX, IDC_COMBO24, m_cmbChannel24);
	DDX_Control(pDX, IDC_COMBO25, m_cmbChannel25);
	DDX_Control(pDX, IDC_COMBO26, m_cmbChannel26);
	DDX_Control(pDX, IDC_COMBO27, m_cmbChannel27);
	DDX_Control(pDX, IDC_COMBO28, m_cmbChannel28);
	DDX_Control(pDX, IDC_COMBO29, m_cmbChannel29);
	DDX_Control(pDX, IDC_COMBO30, m_cmbChannel30);
	DDX_Control(pDX, IDC_COMBO31, m_cmbChannel31);
	DDX_Control(pDX, IDC_COMBO32, m_cmbChannel32);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT1, m_nValue1);
	DDX_Control(pDX, IDC_EDIT10, m_edit10);
	DDX_Control(pDX, IDC_EDIT11, m_edit11);
	DDX_Control(pDX, IDC_EDIT12, m_edit12);
	DDX_Control(pDX, IDC_EDIT13, m_edit13);
	DDX_Control(pDX, IDC_EDIT14, m_edit14);
	DDX_Control(pDX, IDC_EDIT15, m_edit15);
	DDX_Control(pDX, IDC_EDIT16, m_edit16);
	DDX_Control(pDX, IDC_EDIT17, m_edit9);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_EDIT7, m_edit7);
	DDX_Control(pDX, IDC_EDIT8, m_edit8);

	DDX_Control(pDX, IDC_EDIT18, m_edit17);
	DDX_Control(pDX, IDC_EDIT22, m_edit18);
	DDX_Control(pDX, IDC_EDIT24, m_edit19);
	DDX_Control(pDX, IDC_EDIT28, m_edit20);
	DDX_Control(pDX, IDC_EDIT30, m_edit21);
	DDX_Control(pDX, IDC_EDIT33, m_edit22);
	DDX_Control(pDX, IDC_EDIT34, m_edit23);
	DDX_Control(pDX, IDC_EDIT35, m_edit24);
	DDX_Control(pDX, IDC_EDIT36, m_edit25);
	DDX_Control(pDX, IDC_EDIT37, m_edit26);
	DDX_Control(pDX, IDC_EDIT38, m_edit27);
	DDX_Control(pDX, IDC_EDIT39, m_edit28);
	DDX_Control(pDX, IDC_EDIT40, m_edit29);
	DDX_Control(pDX, IDC_EDIT41, m_edit30);
	DDX_Control(pDX, IDC_EDIT42, m_edit31);
	DDX_Control(pDX, IDC_EDIT43, m_edit32);

	DDX_Text(pDX, IDC_EDIT10, m_nValue10);
	DDX_Text(pDX, IDC_EDIT11, m_nValue11);
	DDX_Text(pDX, IDC_EDIT12, m_nValue12);
	DDX_Text(pDX, IDC_EDIT13, m_nValue13);
	DDX_Text(pDX, IDC_EDIT14, m_nValue14);
	DDX_Text(pDX, IDC_EDIT15, m_nValue15);
	DDX_Text(pDX, IDC_EDIT16, m_nValue16);
	DDX_Text(pDX, IDC_EDIT17, m_nValue9);
	DDX_Text(pDX, IDC_EDIT2, m_nValue2);
	DDX_Text(pDX, IDC_EDIT3, m_nValue3);
	DDX_Text(pDX, IDC_EDIT4, m_nValue4);
	DDX_Text(pDX, IDC_EDIT5, m_nValue5);
	DDX_Text(pDX, IDC_EDIT6, m_nValue6);
	DDX_Text(pDX, IDC_EDIT7, m_nValue7);
	DDX_Text(pDX, IDC_EDIT8, m_nValue8);

	DDX_Text(pDX, IDC_EDIT18, m_nValue17);
	DDX_Text(pDX, IDC_EDIT22, m_nValue18);
	DDX_Text(pDX, IDC_EDIT24, m_nValue19);
	DDX_Text(pDX, IDC_EDIT28, m_nValue20);
	DDX_Text(pDX, IDC_EDIT30, m_nValue21);
	DDX_Text(pDX, IDC_EDIT33, m_nValue22);
	DDX_Text(pDX, IDC_EDIT34, m_nValue23);
	DDX_Text(pDX, IDC_EDIT35, m_nValue24);
	DDX_Text(pDX, IDC_EDIT36, m_nValue25);
	DDX_Text(pDX, IDC_EDIT37, m_nValue26);
	DDX_Text(pDX, IDC_EDIT38, m_nValue27);
	DDX_Text(pDX, IDC_EDIT39, m_nValue28);
	DDX_Text(pDX, IDC_EDIT40, m_nValue29);
	DDX_Text(pDX, IDC_EDIT41, m_nValue30);
	DDX_Text(pDX, IDC_EDIT42, m_nValue31);
	DDX_Text(pDX, IDC_EDIT43, m_nValue32);
	
}


BEGIN_MESSAGE_MAP(CPtzLinkDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, CPtzLinkDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, CPtzLinkDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, CPtzLinkDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, CPtzLinkDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, CPtzLinkDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, CPtzLinkDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, CPtzLinkDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, CPtzLinkDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT17, CPtzLinkDlg::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT10, CPtzLinkDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, CPtzLinkDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, CPtzLinkDlg::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, CPtzLinkDlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, CPtzLinkDlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, CPtzLinkDlg::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, CPtzLinkDlg::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT18, CPtzLinkDlg::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT22, CPtzLinkDlg::OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT24, CPtzLinkDlg::OnEnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT28, CPtzLinkDlg::OnEnChangeEdit28)
	ON_EN_CHANGE(IDC_EDIT30, CPtzLinkDlg::OnEnChangeEdit30)
	ON_EN_CHANGE(IDC_EDIT33, CPtzLinkDlg::OnEnChangeEdit33)
	ON_EN_CHANGE(IDC_EDIT34, CPtzLinkDlg::OnEnChangeEdit34)
	ON_EN_CHANGE(IDC_EDIT35, CPtzLinkDlg::OnEnChangeEdit35)
	ON_EN_CHANGE(IDC_EDIT36, CPtzLinkDlg::OnEnChangeEdit36)
	ON_EN_CHANGE(IDC_EDIT37, CPtzLinkDlg::OnEnChangeEdit37)
	ON_EN_CHANGE(IDC_EDIT38, CPtzLinkDlg::OnEnChangeEdit38)
	ON_EN_CHANGE(IDC_EDIT39, CPtzLinkDlg::OnEnChangeEdit39)
	ON_EN_CHANGE(IDC_EDIT40, CPtzLinkDlg::OnEnChangeEdit40)
	ON_EN_CHANGE(IDC_EDIT41, CPtzLinkDlg::OnEnChangeEdit41)
	ON_EN_CHANGE(IDC_EDIT42, CPtzLinkDlg::OnEnChangeEdit42)
	ON_EN_CHANGE(IDC_EDIT43, CPtzLinkDlg::OnEnChangeEdit43)
	ON_BN_CLICKED(IDOK, CPtzLinkDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPtzLinkDlg 消息处理程序

BOOL CPtzLinkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	AfxSetResourceHandle(OldResourceHanlde);//对话框已创建，设置回原来的模块  
	_CWndCS(this);

	m_cmbChannel1.AddString(_CS("PtzControl.None"));
	m_cmbChannel1.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel1.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel1.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel2.AddString(_CS("PtzControl.None"));
	m_cmbChannel2.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel2.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel2.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel3.AddString(_CS("PtzControl.None"));
	m_cmbChannel3.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel3.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel3.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel4.AddString(_CS("PtzControl.None"));
	m_cmbChannel4.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel4.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel4.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel5.AddString(_CS("PtzControl.None"));
	m_cmbChannel5.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel5.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel5.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel6.AddString(_CS("PtzControl.None"));
	m_cmbChannel6.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel6.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel6.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel7.AddString(_CS("PtzControl.None"));
	m_cmbChannel7.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel7.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel7.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel8.AddString(_CS("PtzControl.None"));
	m_cmbChannel8.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel8.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel8.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel9.AddString(_CS("PtzControl.None"));
	m_cmbChannel9.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel9.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel9.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel10.AddString(_CS("PtzControl.None"));
	m_cmbChannel10.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel10.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel10.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel11.AddString(_CS("PtzControl.None"));
	m_cmbChannel11.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel11.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel11.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel12.AddString(_CS("PtzControl.None"));
	m_cmbChannel12.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel12.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel12.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel13.AddString(_CS("PtzControl.None"));
	m_cmbChannel13.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel13.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel13.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel14.AddString(_CS("PtzControl.None"));
	m_cmbChannel14.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel14.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel14.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel15.AddString(_CS("PtzControl.None"));
	m_cmbChannel15.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel15.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel15.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel16.AddString(_CS("PtzControl.None"));
	m_cmbChannel16.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel16.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel16.AddString(_CS("PtzControl.Pattern"));


	m_cmbChannel17.AddString(_CS("PtzControl.None"));
	m_cmbChannel17.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel17.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel17.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel18.AddString(_CS("PtzControl.None"));
	m_cmbChannel18.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel18.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel18.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel19.AddString(_CS("PtzControl.None"));
	m_cmbChannel19.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel19.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel19.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel20.AddString(_CS("PtzControl.None"));
	m_cmbChannel20.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel20.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel20.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel21.AddString(_CS("PtzControl.None"));
	m_cmbChannel21.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel21.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel21.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel22.AddString(_CS("PtzControl.None"));
	m_cmbChannel22.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel22.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel22.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel23.AddString(_CS("PtzControl.None"));
	m_cmbChannel23.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel23.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel23.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel24.AddString(_CS("PtzControl.None"));
	m_cmbChannel24.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel24.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel24.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel25.AddString(_CS("PtzControl.None"));
	m_cmbChannel25.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel25.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel25.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel26.AddString(_CS("PtzControl.None"));
	m_cmbChannel26.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel26.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel26.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel27.AddString(_CS("PtzControl.None"));
	m_cmbChannel27.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel27.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel27.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel28.AddString(_CS("PtzControl.None"));
	m_cmbChannel28.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel28.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel28.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel29.AddString(_CS("PtzControl.None"));
	m_cmbChannel29.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel29.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel29.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel30.AddString(_CS("PtzControl.None"));
	m_cmbChannel30.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel30.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel30.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel31.AddString(_CS("PtzControl.None"));
	m_cmbChannel31.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel31.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel31.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel32.AddString(_CS("PtzControl.None"));
	m_cmbChannel32.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel32.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel32.AddString(_CS("PtzControl.Pattern"));

	CString strtemp;
	m_cmbChannel1.SetCurSel(m_PtzLink[0].iType);
	strtemp.Format("%d", m_PtzLink[0].iValue );
	m_edit1.SetWindowText(strtemp);

	m_cmbChannel2.SetCurSel(m_PtzLink[1].iType);
	strtemp.Format("%d", m_PtzLink[1].iValue );
	m_edit2.SetWindowText(strtemp);

	m_cmbChannel3.SetCurSel(m_PtzLink[2].iType);
	strtemp.Format("%d", m_PtzLink[2].iValue );
	m_edit3.SetWindowText(strtemp);

	m_cmbChannel4.SetCurSel(m_PtzLink[3].iType);
	strtemp.Format("%d", m_PtzLink[3].iValue );
	m_edit4.SetWindowText(strtemp);

	m_cmbChannel5.SetCurSel(m_PtzLink[4].iType);
	strtemp.Format("%d", m_PtzLink[4].iValue );
	m_edit5.SetWindowText(strtemp);

	m_cmbChannel6.SetCurSel(m_PtzLink[5].iType);
	strtemp.Format("%d", m_PtzLink[5].iValue );
	m_edit6.SetWindowText(strtemp);

	m_cmbChannel7.SetCurSel(m_PtzLink[6].iType);
	strtemp.Format("%d", m_PtzLink[6].iValue );
	m_edit7.SetWindowText(strtemp);

	m_cmbChannel8.SetCurSel(m_PtzLink[7].iType);
	strtemp.Format("%d", m_PtzLink[7].iValue );
	m_edit8.SetWindowText(strtemp);

	m_cmbChannel9.SetCurSel(m_PtzLink[8].iType);
	strtemp.Format("%d", m_PtzLink[8].iValue );
	m_edit9.SetWindowText(strtemp);

	m_cmbChannel10.SetCurSel(m_PtzLink[9].iType);
	strtemp.Format("%d", m_PtzLink[9].iValue );
	m_edit10.SetWindowText(strtemp);

	m_cmbChannel11.SetCurSel(m_PtzLink[10].iType);
	strtemp.Format("%d", m_PtzLink[10].iValue );
	m_edit11.SetWindowText(strtemp);

	m_cmbChannel12.SetCurSel(m_PtzLink[11].iType);
	strtemp.Format("%d", m_PtzLink[11].iValue );
	m_edit12.SetWindowText(strtemp);

	m_cmbChannel13.SetCurSel(m_PtzLink[12].iType);
	strtemp.Format("%d", m_PtzLink[12].iValue );
	m_edit13.SetWindowText(strtemp);

	m_cmbChannel14.SetCurSel(m_PtzLink[13].iType);
	strtemp.Format("%d", m_PtzLink[13].iValue );
	m_edit14.SetWindowText(strtemp);

	m_cmbChannel15.SetCurSel(m_PtzLink[14].iType);
	strtemp.Format("%d", m_PtzLink[14].iValue );
	m_edit15.SetWindowText(strtemp);

	m_cmbChannel16.SetCurSel(m_PtzLink[15].iType);
	strtemp.Format("%d", m_PtzLink[15].iValue );
	m_edit16.SetWindowText(strtemp);

	m_cmbChannel17.SetCurSel(m_PtzLink[16].iType);
	strtemp.Format("%d", m_PtzLink[16].iValue );
	m_edit17.SetWindowText(strtemp);

	m_cmbChannel18.SetCurSel(m_PtzLink[17].iType);
	strtemp.Format("%d", m_PtzLink[17].iValue );
	m_edit18.SetWindowText(strtemp);

	m_cmbChannel19.SetCurSel(m_PtzLink[18].iType);
	strtemp.Format("%d", m_PtzLink[18].iValue );
	m_edit19.SetWindowText(strtemp);

	m_cmbChannel20.SetCurSel(m_PtzLink[19].iType);
	strtemp.Format("%d", m_PtzLink[19].iValue );
	m_edit20.SetWindowText(strtemp);

	m_cmbChannel21.SetCurSel(m_PtzLink[20].iType);
	strtemp.Format("%d", m_PtzLink[20].iValue );
	m_edit21.SetWindowText(strtemp);

	m_cmbChannel22.SetCurSel(m_PtzLink[21].iType);
	strtemp.Format("%d", m_PtzLink[21].iValue );
	m_edit22.SetWindowText(strtemp);

	m_cmbChannel23.SetCurSel(m_PtzLink[22].iType);
	strtemp.Format("%d", m_PtzLink[22].iValue );
	m_edit23.SetWindowText(strtemp);

	m_cmbChannel24.SetCurSel(m_PtzLink[23].iType);
	strtemp.Format("%d", m_PtzLink[23].iValue );
	m_edit24.SetWindowText(strtemp);

	m_cmbChannel25.SetCurSel(m_PtzLink[24].iType);
	strtemp.Format("%d", m_PtzLink[24].iValue );
	m_edit25.SetWindowText(strtemp);

	m_cmbChannel26.SetCurSel(m_PtzLink[25].iType);
	strtemp.Format("%d", m_PtzLink[25].iValue );
	m_edit26.SetWindowText(strtemp);

	m_cmbChannel27.SetCurSel(m_PtzLink[26].iType);
	strtemp.Format("%d", m_PtzLink[26].iValue );
	m_edit27.SetWindowText(strtemp);

	m_cmbChannel28.SetCurSel(m_PtzLink[27].iType);
	strtemp.Format("%d", m_PtzLink[27].iValue );
	m_edit28.SetWindowText(strtemp);

	m_cmbChannel29.SetCurSel(m_PtzLink[28].iType);
	strtemp.Format("%d", m_PtzLink[28].iValue );
	m_edit29.SetWindowText(strtemp);

	m_cmbChannel30.SetCurSel(m_PtzLink[29].iType);
	strtemp.Format("%d", m_PtzLink[29].iValue );
	m_edit30.SetWindowText(strtemp);

	m_cmbChannel31.SetCurSel(m_PtzLink[30].iType);
	strtemp.Format("%d", m_PtzLink[30].iValue );
	m_edit31.SetWindowText(strtemp);

	m_cmbChannel32.SetCurSel(m_PtzLink[31].iType);
	strtemp.Format("%d", m_PtzLink[31].iValue );
	m_edit32.SetWindowText(strtemp);

	CUserDataManager *pData = CUserDataManager::instance();
	if ( pData )
	{
		int nChannel = pData->GetSysInfo()->byChanNum + pData->GetSysInfo()->iDigChannel;
		switch(nChannel)
		{
		case 0:
			{
				GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
			}
		case 1:
			{
				GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
			}
		case 2:
			{
				GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
			}
		case 3:
			{
				GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
			}
		case 4:
			{
				GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO5)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
			}
		case 5:
			{
				GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO6)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
			}
		case 6:
			{
				GetDlgItem(IDC_STATIC_7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
			}
		case 7:
			{
				GetDlgItem(IDC_STATIC_8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
			}
		case 8:
			{
				GetDlgItem(IDC_STATIC_9)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO9)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT17)->ShowWindow(SW_HIDE);
			}
		case 9:
			{
				GetDlgItem(IDC_STATIC_10)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO10)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
			}
		case 10:
			{
				GetDlgItem(IDC_STATIC_11)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO11)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT11)->ShowWindow(SW_HIDE);
			}
		case 11:
			{
				GetDlgItem(IDC_STATIC_12)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO12)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT12)->ShowWindow(SW_HIDE);
			}
		case 12:
			{
				GetDlgItem(IDC_STATIC_13)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO13)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT13)->ShowWindow(SW_HIDE);
			}
		case 13:
			{
				GetDlgItem(IDC_STATIC_14)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO14)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT14)->ShowWindow(SW_HIDE);
			}
		case 14:
			{
				GetDlgItem(IDC_STATIC_15)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO15)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT15)->ShowWindow(SW_HIDE);
			}
		case 15:
			{
				GetDlgItem(IDC_STATIC_16)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO16)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT16)->ShowWindow(SW_HIDE);
			}
		case 16:
			{
				GetDlgItem(IDC_STATIC_17)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO17)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT18)->ShowWindow(SW_HIDE);
			}
		case 17:
			{
				GetDlgItem(IDC_STATIC_19)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO18)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT22)->ShowWindow(SW_HIDE);
			}
		case 18:
			{
				GetDlgItem(IDC_STATIC_21)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO19)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT24)->ShowWindow(SW_HIDE);
			}
		case 19:
			{
				GetDlgItem(IDC_STATIC_23)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO20)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT28)->ShowWindow(SW_HIDE);
			}
		case 20:
			{
				GetDlgItem(IDC_STATIC_18)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO21)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT30)->ShowWindow(SW_HIDE);
			}
		case 21:
			{
				GetDlgItem(IDC_STATIC_20)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO22)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT33)->ShowWindow(SW_HIDE);
			}
		case 22:
			{
				GetDlgItem(IDC_STATIC_22)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO23)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT34)->ShowWindow(SW_HIDE);
			}
		case 23:
			{
				GetDlgItem(IDC_STATIC_24)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO24)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT35)->ShowWindow(SW_HIDE);
			}
		case 24:
			{
				GetDlgItem(IDC_STATIC_25)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO25)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT36)->ShowWindow(SW_HIDE);
			}
		case 25:
			{
				GetDlgItem(IDC_STATIC_27)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO26)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT37)->ShowWindow(SW_HIDE);
			}
		case 26:
			{
				GetDlgItem(IDC_STATIC_29)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO27)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT38)->ShowWindow(SW_HIDE);
			}
		case 27:
			{
				GetDlgItem(IDC_STATIC_31)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO28)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT39)->ShowWindow(SW_HIDE);
			}
		case 28:
			{
				GetDlgItem(IDC_STATIC_26)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO29)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT40)->ShowWindow(SW_HIDE);
			}
		case 29:
			{
				GetDlgItem(IDC_STATIC_28)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO30)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT41)->ShowWindow(SW_HIDE);
			}
		case 30:
			{
				GetDlgItem(IDC_STATIC_30)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO31)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT42)->ShowWindow(SW_HIDE);
			}
		case 31:
			{
				GetDlgItem(IDC_STATIC_32)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO32)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT43)->ShowWindow(SW_HIDE);
			}
		}

		CRect clientRect;
		CRect rect;
		GetClientRect(&clientRect);
		GetWindowRect(rect);
		if ( nChannel <= 8 )
		{ 
			int nPos = ( (rect.bottom - rect.top) / 2 - 50);
			rect.bottom -= nPos;
			MoveWindow(rect);
			
			
			GetDlgItem(IDOK)->GetClientRect(&rect);
			GetDlgItem(IDOK)->MoveWindow(100, clientRect.bottom - nPos - 5 - rect.Height(), rect.Width(), rect.Height());
			
			GetDlgItem(IDCANCEL)->GetClientRect(&rect);	
			GetDlgItem(IDCANCEL)->MoveWindow(100 + rect.Width() + 5, clientRect.bottom - nPos - 5 - rect.Height(), rect.Width(), rect.Height());
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

const SDK_PtzLinkConfig *CPtzLinkDlg::GetPtzConf()
{
	return m_PtzLink;
}

void CPtzLinkDlg::OnEnChangeEdit1()
{
	UpdateData();
	if ( m_nValue1 > 255 )
	{
		m_nValue1 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit2()
{
	UpdateData();
	if ( m_nValue2 > 255 )
	{
		m_nValue2 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit3()
{
	UpdateData();
	if ( m_nValue3 > 255 )
	{
		m_nValue3 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit4()
{
	UpdateData();
	if ( m_nValue4 > 255 )
	{
		m_nValue4 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit5()
{
	UpdateData();
	if ( m_nValue5 > 255 )
	{
		m_nValue5 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit6()
{
	UpdateData();
	if ( m_nValue6 > 255 )
	{
		m_nValue6 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit7()
{
	UpdateData();
	if ( m_nValue7 > 255 )
	{
		m_nValue7 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit8()
{
	UpdateData();
	if ( m_nValue8 > 255 )
	{
		m_nValue8 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit17()
{
	UpdateData();
	if ( m_nValue9 > 255 )
	{
		m_nValue9 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit10()
{
	UpdateData();
	if ( m_nValue10 > 255 )
	{
		m_nValue10 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit11()
{
	UpdateData();
	if ( m_nValue11 > 255 )
	{
		m_nValue11 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit12()
{
	UpdateData();
	if ( m_nValue12 > 255 )
	{
		m_nValue12 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit13()
{
	UpdateData();
	if ( m_nValue13 > 255 )
	{
		m_nValue13 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit14()
{
	UpdateData();
	if ( m_nValue14 > 255 )
	{
		m_nValue14 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit15()
{
	UpdateData();
	if ( m_nValue15 > 255 )
	{
		m_nValue15 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit16()
{
	UpdateData();
	if ( m_nValue16 > 255 )
	{
		m_nValue16 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit18()
{
	UpdateData();
	if ( m_nValue17 > 255 )
	{
		m_nValue17 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit22()
{
	UpdateData();
	if ( m_nValue18 > 255 )
	{
		m_nValue18 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit24()
{
	UpdateData();
	if ( m_nValue19 > 255 )
	{
		m_nValue19 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit28()
{
	UpdateData();
	if ( m_nValue20 > 255 )
	{
		m_nValue20 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit30()
{
	UpdateData();
	if ( m_nValue21 > 255 )
	{
		m_nValue21 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit33()
{
	UpdateData();
	if ( m_nValue22 > 255 )
	{
		m_nValue22 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit34()
{
	UpdateData();
	if ( m_nValue23 > 255 )
	{
		m_nValue23 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit35()
{
	UpdateData();
	if ( m_nValue24 > 255 )
	{
		m_nValue24 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit36()
{
	UpdateData();
	if ( m_nValue25 > 255 )
	{
		m_nValue25 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit37()
{
	UpdateData();
	if ( m_nValue26 > 255 )
	{
		m_nValue26 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit38()
{
	UpdateData();
	if ( m_nValue27 > 255 )
	{
		m_nValue27 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit39()
{
	UpdateData();
	if ( m_nValue28 > 255 )
	{
		m_nValue28 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit40()
{
	UpdateData();
	if ( m_nValue29 > 255 )
	{
		m_nValue29 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit41()
{
	UpdateData();
	if ( m_nValue30 > 255 )
	{
		m_nValue30 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit42()
{
	UpdateData();
	if ( m_nValue31 > 255 )
	{
		m_nValue31 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnEnChangeEdit43()
{
	UpdateData();
	if ( m_nValue32 > 255 )
	{
		m_nValue32 = 255;
		UpdateData(FALSE);
	}
}
void CPtzLinkDlg::OnBnClickedOk()
{
	UpdateData();

	m_PtzLink[0].iType = m_cmbChannel1.GetCurSel();
	m_PtzLink[0].iValue = m_nValue1;
	m_PtzLink[1].iType = m_cmbChannel2.GetCurSel();
	m_PtzLink[1].iValue = m_nValue2;
	m_PtzLink[2].iType = m_cmbChannel3.GetCurSel();
	m_PtzLink[2].iValue = m_nValue3;
	m_PtzLink[3].iType = m_cmbChannel4.GetCurSel();
	m_PtzLink[3].iValue = m_nValue4;
	m_PtzLink[4].iType = m_cmbChannel5.GetCurSel();
	m_PtzLink[4].iValue = m_nValue5;
	m_PtzLink[5].iType = m_cmbChannel6.GetCurSel();
	m_PtzLink[5].iValue = m_nValue6;
	m_PtzLink[6].iType = m_cmbChannel7.GetCurSel();
	m_PtzLink[6].iValue = m_nValue7;
	m_PtzLink[7].iType = m_cmbChannel8.GetCurSel();
	m_PtzLink[7].iValue = m_nValue8;
	m_PtzLink[8].iType = m_cmbChannel9.GetCurSel();
	m_PtzLink[8].iValue = m_nValue9;
	m_PtzLink[9].iType = m_cmbChannel10.GetCurSel();
	m_PtzLink[9].iValue = m_nValue10;
	m_PtzLink[10].iType = m_cmbChannel11.GetCurSel();
	m_PtzLink[10].iValue = m_nValue11;
	m_PtzLink[11].iType = m_cmbChannel12.GetCurSel();
	m_PtzLink[11].iValue = m_nValue12;
	m_PtzLink[12].iType = m_cmbChannel13.GetCurSel();
	m_PtzLink[12].iValue = m_nValue13;
	m_PtzLink[13].iType = m_cmbChannel14.GetCurSel();
	m_PtzLink[13].iValue = m_nValue14;
	m_PtzLink[14].iType = m_cmbChannel15.GetCurSel();
	m_PtzLink[14].iValue = m_nValue15;
	m_PtzLink[15].iType = m_cmbChannel16.GetCurSel();
	m_PtzLink[15].iValue = m_nValue16;

	m_PtzLink[16].iType = m_cmbChannel17.GetCurSel();
	m_PtzLink[16].iValue = m_nValue17;

	m_PtzLink[17].iType = m_cmbChannel18.GetCurSel();
	m_PtzLink[17].iValue = m_nValue18;

	m_PtzLink[18].iType = m_cmbChannel19.GetCurSel();
	m_PtzLink[18].iValue = m_nValue19;

	m_PtzLink[19].iType = m_cmbChannel20.GetCurSel();
	m_PtzLink[19].iValue = m_nValue20;

	m_PtzLink[20].iType = m_cmbChannel21.GetCurSel();
	m_PtzLink[20].iValue = m_nValue21;

	m_PtzLink[21].iType = m_cmbChannel22.GetCurSel();
	m_PtzLink[21].iValue = m_nValue22;

	m_PtzLink[22].iType = m_cmbChannel23.GetCurSel();
	m_PtzLink[22].iValue = m_nValue23;

	m_PtzLink[23].iType = m_cmbChannel24.GetCurSel();
	m_PtzLink[23].iValue = m_nValue24;

	m_PtzLink[24].iType = m_cmbChannel25.GetCurSel();
	m_PtzLink[24].iValue = m_nValue25;

	m_PtzLink[25].iType = m_cmbChannel26.GetCurSel();
	m_PtzLink[25].iValue = m_nValue26;

	m_PtzLink[26].iType = m_cmbChannel27.GetCurSel();
	m_PtzLink[26].iValue = m_nValue27;

	m_PtzLink[27].iType = m_cmbChannel28.GetCurSel();
	m_PtzLink[27].iValue = m_nValue28;

	m_PtzLink[28].iType = m_cmbChannel29.GetCurSel();
	m_PtzLink[28].iValue = m_nValue29;

	m_PtzLink[29].iType = m_cmbChannel30.GetCurSel();
	m_PtzLink[29].iValue = m_nValue30;

	m_PtzLink[30].iType = m_cmbChannel31.GetCurSel();
	m_PtzLink[30].iValue = m_nValue31;

	m_PtzLink[31].iType = m_cmbChannel32.GetCurSel();
	m_PtzLink[31].iValue = m_nValue32;
	OnOK();
}
