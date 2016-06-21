// VehicleState.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "VehicleState.h"
#include "StateSort.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define StateCount SDK_CAR_STATUS_NR
/////////////////////////////////////////////////////////////////////////////
// CVehicleState dialog


CVehicleState::CVehicleState(CWnd* pParent /*=NULL*/)
: CDialog(CVehicleState::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVehicleState)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(mCheckBox,0,sizeof(CButton));
	memset(mStatic,0,sizeof(CStatic));
	memset(mInputCB,0,sizeof(CComboBox));
	memset(mStyleCB,0,sizeof(CComboBox));
}


void CVehicleState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVehicleState)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVehicleState, CDialog)
//{{AFX_MSG_MAP(CVehicleState)
ON_BN_CLICKED(IDC_SELECT_BTN, OnSelectBtn)
ON_BN_CLICKED(IDC_VEHICLESTATE,OnBtnCheck)
ON_BN_CLICKED(IDC_VEHICLESTATE+1,OnBtnCheck)
ON_BN_CLICKED(IDC_VEHICLESTATE+2,OnBtnCheck)
ON_BN_CLICKED(IDC_VEHICLESTATE+3,OnBtnCheck)
ON_BN_CLICKED(IDC_VEHICLESTATE+4,OnBtnCheck)
ON_BN_CLICKED(IDC_VEHICLESTATE+5,OnBtnCheck)
ON_BN_CLICKED(IDC_VEHICLESTATE+6,OnBtnCheck)
ON_BN_CLICKED(IDC_VEHICLESTATE+7,OnBtnCheck)

ON_CONTROL_RANGE(CBN_SELCHANGE,IDC_VEHICLESTATE+40,IDC_VEHICLESTATE+47,OnSelChanged)
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVehicleState message handlers
BOOL CVehicleState::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CVehicleState::OnSelectBtn() 
{
	// TODO: Add your control notification handler code here
	CStateSort m_statesort(&mCarStaExg);
	if (m_statesort.DoModal() == IDOK )
	{
		//		CleanAll();
		// 		((CClientDemo5Dlg*)AfxGetMainWnd())->GetVehicleDlg();
		// 		UpdateData(TRUE);
	}
	//m_statesort.InitDlgInfo(&mCarStaExg);
	
	
}

void CVehicleState::InitDlgInfo(SDK_CarStatusExchangeAll *pCarStaExg,int nAlarmInNum)
{
	m_nAlarmInNum = nAlarmInNum;
	CString stylestr[StateCount]={_CS("CarFunc.RunStatus"),_CS("CarFunc.RightLight"),_CS("CarFunc.RightFrontDoor")
		,_CS("CarFunc.RightBackDoor"),_CS("CarFunc.LeftLight"),_CS("CarFunc.LeftFrontDoor"),_CS("CarFunc.LeftBackDoor"),_CS("CarFunc.BackDoor")};
	CString Inputstr = _CS("ConfigAlarm.AlarmIn");
	CString OnOffstr[2] = {_CS("CarFunc.Opened"),_CS("CarFunc.Closed")}; 
	CString str;
	memcpy(&mCarStaExg,pCarStaExg,sizeof(SDK_CarStatusExchangeAll));
	
	CRect mrect;
	GetDlgItem(IDC_TAG)->GetWindowRect(mrect);
	ScreenToClient(mrect);
	
	CRect mCheckRect,mStaticRect,mInputRect,mStyleRect;
	for (int i = 0; i<StateCount; ++i)
	{
		
		if (mCarStaExg.exchangeAll[i].bExist)
		{
			mrect.top +=35;
			mrect.bottom +=35;
			mCheckRect = mrect;
			mStaticRect = mrect;
			mInputRect = mrect;
			mStyleRect = mrect;
			
			mStaticRect.left = mCheckRect.right + 40;
			mStaticRect.right = mStaticRect.left + 70;
			mStaticRect.bottom += 10;
			
			
			mInputRect.left = mStaticRect.right +40;
			mInputRect.right = mInputRect.left +150;
			mInputRect.bottom +=100;
			
			mStyleRect.left = mInputRect.right +40;
			mStyleRect.right = mStyleRect.left +150;
			mStyleRect.bottom +=60;
			
			mCheckBox[i] = new CButton();
			mStatic[i] = new CStatic();
			mInputCB[i] = new CComboBox();
			mStyleCB[i] = new CComboBox();
			
			mCheckBox[i]->Create("",WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,mCheckRect,this,IDC_VEHICLESTATE+i);
			mStatic[i]->Create(stylestr[i],SS_CENTER|WS_CHILD|WS_VISIBLE,mStaticRect,this,IDC_VEHICLESTATE+20+i);
			mInputCB[i]->Create(WS_VSCROLL|CBS_DROPDOWN|CBS_DROPDOWNLIST|WS_CHILD|WS_VISIBLE,mInputRect,this,IDC_VEHICLESTATE+40+i);
			mStyleCB[i]->Create(WS_VSCROLL|CBS_DROPDOWN|CBS_DROPDOWNLIST|WS_CHILD|WS_VISIBLE,mStyleRect,this,IDC_VEHICLESTATE+60+i);
			int j = 0;
			for (;j<m_nAlarmInNum; ++j)
			{
				str.Format(_T("%d"),j+1);
				mInputCB[i]->InsertString(j,Inputstr+str);
				
			}
			mInputCB[i]->InsertString(j,"全");
			for (int k = 0;k<2; ++k)
			{
				mStyleCB[i]->InsertString(k,OnOffstr[k]);
			}
			
			if (mCarStaExg.exchangeAll[i].bEnable)
			{
				mCheckBox[i]->SetCheck(TRUE);
				mInputCB[i]->EnableWindow(TRUE);
				if (mCarStaExg.exchangeAll[i].inputType == 0)//当inputType是本地报警输入时,设备类型选项才有效
				{
					mStyleCB[i]->EnableWindow(TRUE);
				}
				else
				{
					mStyleCB[i]->EnableWindow(FALSE);
				}
				
			}
			else
			{
				mCheckBox[i]->SetCheck(FALSE);
				mInputCB[i]->EnableWindow(FALSE);
				mStyleCB[i]->EnableWindow(FALSE);
			}
			
			
			
			
		}
	}
	InitWindow();
	OnBtnCheck();
}
BOOL CVehicleState::SaveVehicleStInfo()
{
	int n_inputindex,n_sysleindex;
	int i;
	
	for (i = 0; i<StateCount; ++i)
	{		
		if (mCarStaExg.exchangeAll[i].bExist)
		{
			if ( mInputCB[i] != NULL && mStyleCB[i] != NULL )
			{
				n_inputindex = mInputCB[i]->GetCurSel();
				n_sysleindex = mStyleCB[i]->GetCurSel();
				mCarStaExg.exchangeAll[i].bEnable = mCheckBox[i]->GetCheck();
				mCarStaExg.exchangeAll[i].addr = n_inputindex;
				mCarStaExg.exchangeAll[i].sensorType = n_sysleindex;
			}
			else
			{
				return FALSE;
			}
		}
		
		
	}
	return TRUE;	
}
void CVehicleState::InitWindow()
{
	int i;
	int index;
	for (i = 0;i < StateCount ; ++i)
	{
		if ( mCarStaExg.exchangeAll[i].bExist )
		{
			index = mCarStaExg.exchangeAll[i].addr;
			mInputCB[i]->SetCurSel(index);
			index = mCarStaExg.exchangeAll[i].sensorType;
			mStyleCB[i]->SetCurSel(index);
		}
	}
}

void CVehicleState::CleanAll()
{
	int i;
	for ( i = 0 ;i < StateCount ; ++i)
	{
		delete mCheckBox[i];
		mCheckBox[i] = NULL;
		
		delete mStatic[i];
		mStatic[i] = NULL;
		
		delete mInputCB[i];
		mInputCB[i] = NULL;
		
		delete mStyleCB[i];
		mStyleCB[i] = NULL;
	}
	
	// 	memset(mCheckBox,0,sizeof(CButton));
	// 	memset(mStatic,0,sizeof(CStatic));
	// 	memset(mInputCB,0,sizeof(CComboBox));
	// 	memset(mStyleCB,0,sizeof(CComboBox));
	
	
}
void CVehicleState::OnBtnCheck()
{
	//UpdateData();
	int i;
	BOOL mValue;
	for ( i = 0;i < StateCount; ++i)
	{
		if ( mCarStaExg.exchangeAll[i].bExist )
		{
			UpdateData(TRUE);
			mValue = mCheckBox[i]->GetCheck();
			mInputCB[i]->EnableWindow(mValue);
			if ( mCarStaExg.exchangeAll[i].inputType == 0)
			{
				mStyleCB[i]->EnableWindow(mValue);
			}
			else
			{
				mStyleCB[i]->EnableWindow(FALSE);
			}
			
		}
		
	}
}
void CVehicleState::OnSelChanged(UINT nID)
{
	int nflag=0,nflag1,nflag2;
	int i;
	nflag1 = ((CComboBox *)GetDlgItem(nID))->GetCurSel();
	
	for (i = 0; i < StateCount ; i++)
	{
		if ( mCarStaExg.exchangeAll[i].bExist)
		{
			nflag2 = mInputCB[i]->GetCurSel();
			if (nflag2 == nflag1)
			{
				nflag++;
			}
			
			if ( nflag > 1)
			{
				MessageBox("已存在其他输入口","警告!");
				((CComboBox *)GetDlgItem(nID))->SetCurSel(-1);
				break;
			}
		}
	}
}