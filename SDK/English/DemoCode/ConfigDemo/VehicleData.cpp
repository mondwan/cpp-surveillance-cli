// VehicleData.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "VehicleData.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVehicleData dialog


CVehicleData::CVehicleData(CWnd* pParent /*=NULL*/)
	: CDialog(CVehicleData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVehicleData)
	//}}AFX_DATA_INIT
}


void CVehicleData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVehicleData)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVehicleData, CDialog)
	//{{AFX_MSG_MAP(CVehicleData)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVehicleData message handlers

void CVehicleData::OnButtonStart() 
{
	// TODO: Add your control notification handler code here

	long lLoginID = ((CClientDemo5Dlg* )AfxGetMainWnd())->m_LoginID;
	if (lLoginID > 0)
	{
        BOOL bSuccess;
    	bSuccess = H264_DVR_StartUploadData(lLoginID, VEHICLE, UploadDataCallBack, (DWORD)this);
		if (bSuccess == 1)
		{
			AfxMessageBox("success in start");
		} 
	}

}

void CVehicleData::OnButtonStop() 
{
	// TODO: Add your control notification handler code here

//	H264_DVR_API bool CALL_METHOD H264_DVR_StopUploadData(long lLoginID,
//		                                                  UploadDataType upLoadType);
	long lLoginID = ((CClientDemo5Dlg* )AfxGetMainWnd())->m_LoginID;
	if (lLoginID > 0)
	{
        BOOL bSuccess;
		bSuccess = H264_DVR_StopUploadData(lLoginID, VEHICLE);
		if (bSuccess == 1)
		{
			AfxMessageBox("success in stop!");
		} 
	}

}

void __stdcall CVehicleData::UploadDataCallBack(long lLongID, long UpLoadType, char *pBuffer, unsigned long dwBufSize, unsigned long dwUser)
{
	CVehicleData* pVhiDa = (CVehicleData*)dwUser;
	pVhiDa->GetDlgItem(IDC_EDIT1)->SetWindowText(pBuffer);
}
