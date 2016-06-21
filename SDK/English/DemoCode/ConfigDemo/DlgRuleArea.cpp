// DlgRuleArea.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "DlgRuleArea.h"
//#include "UserDataManager.h"
#include <math.h>
#include "DlgForbidDirection.h"
#include "ClientDemo5Dlg.h" 
#define	 CMS_PICTURE_DIR	_T("Picture\\")
// CDlgRuleArea 对话框
extern   CClientDemo5App   theApp;
extern long loginID;
IMPLEMENT_DYNAMIC(CDlgRuleArea, CDialog)


typedef enum impURP_PERIMETER_MODE_E
{
	IMP_URP_PMODE_INTRUSION = 0,			/**< 入侵 */
	IMP_URP_PMODE_ENTER,				/**< 进入 */
	IMP_URP_PMODE_EXIT				/**< 离开 */
} URP_PERIMETER_MODE_E;

typedef enum impURP_TRIPWIRE_MODE_E
{
	DIRECTION_LEFT_RIGHT = 0, /**<从左到右*/
	DIRECTION_RIGHT_LEFT,/**<从右到左*/
	DIRECTION_UP_DOWN,
	DIRECTION_DOWN_UP
}URP_TRIPWIRE_MODE_E;

CDlgRuleArea::CDlgRuleArea(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRuleArea::IDD, pParent)
{
// 	OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
// 	AfxSetResourceHandle(theApp.m_hInstance);//设置新的模块  
	m_pen.CreatePen(0,2,RGB(0,255,0));
	m_SelectPen.CreatePen(0,2,RGB(0,0,255));
	
	m_nCurIndex = -1;
	for ( int i =0 ; i < NET_MAX_CHANNUM; i ++ )
	{
		m_bGet[i] = false;
	}
	m_bGetType = false;
	m_nChannelNum = 0;
	m_nPerimeterNum = 0;
	m_nTripwireNum = 0;
	m_nLineType = 0;
	m_MouseDown = false;
	m_nPlayhandle = -1;
	m_nPlaydecHandle = -1;
	m_bCallBack=FALSE;
	m_lLoginHandle=-1;
	m_lLastDevID=-1;
}

CDlgRuleArea::~CDlgRuleArea()
{
	m_contextMenu.DestroyMenu();
}

void CDlgRuleArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_bkPic);
}


BEGIN_MESSAGE_MAP(CDlgRuleArea, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, CDlgRuleArea::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, CDlgRuleArea::OnCancel)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MENUCONTEXT_MENU_EDIT, CDlgRuleArea::OnMenucontextMenuEdit)
	ON_COMMAND(ID_MENUCONTEXT_MENU_DELETE, CDlgRuleArea::OnMenucontextMenuDelete)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDlgRuleArea 消息处理程序

BOOL CDlgRuleArea::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rtClient;
	GetClientRect(&rtClient);
	
	CRect rect(10, 10, rtClient.Width()-10,rtClient.Height()-80);
	m_bkPic.MoveWindow(rect);
	m_nPicWidth = rect.Width();
	m_nPicHeight = rect.Height();
	m_nPicLeft = 10;
	m_nPicTop =10;
	// TODO:  在此添加额外的初始化
	// AfxSetResourceHandle(OldResourceHanlde);//对话框已创建，设置回原来的模块  
	_CWndCS(this);
	m_contextMenu.CreatePopupMenu();
	m_contextMenu.AppendMenu(MF_STRING,ID_MENUCONTEXT_MENU_EDIT,_CS("DeviceManage.DevEdit"));
	m_contextMenu.AppendMenu(MF_STRING,ID_MENUCONTEXT_MENU_DELETE,_CS("DeviceManage.DevDel"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDlgRuleArea::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	CDC *pDC = m_bkPic.GetDC();

	CRect rtClient;
	GetClientRect(&rtClient);

	HBITMAP   hbitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),m_strFileName,
		IMAGE_BITMAP,352,228,LR_CREATEDIBSECTION|LR_LOADFROMFILE);    

	if(hbitmap==NULL) 
	{
		return ;   
	}
	CBitmap       bitmap;      
	bitmap.Attach(hbitmap);  

	CRect rtPic;
	m_bkPic.GetWindowRect(&rtPic);
	ScreenToClient(&rtPic);

	BITMAP bitMap;//位图结构体
	bitmap.GetBitmap(&bitMap);//获得原图片尺寸

	CDC dcMem;  //目标DC
	dcMem.CreateCompatibleDC(pDC); //创建与dc兼容的内存DC
	dcMem.SelectObject(&bitmap);//将位图对象m_bmpBK选入内存DC
	pDC->StretchBlt(0,0,rtPic.Width(),rtPic.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);

	int nChannelNo =0;//目前只支持单通道（通道一）
// 	if ( nChannelNo == CUserDataManager::instance()->GetSysInfo()->byChanNum )
// 	{
// 		nChannelNo = 0;
// 	}	
	DWORD nReturn=0;
	long m_LoginID=0;
	H264_DVR_DEVICEINFO deviceInfo;
	int nRet = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSINFO,-1, (char *)&deviceInfo,sizeof(deviceInfo),&nReturn);
// 	int nChannelNo =0;//目前只支持单通道（通道一）
// 	if ( nChannelNo == deviceInfo.byChanNum )
// 	{
// 		nChannelNo = 0;
// 	}	


	CPen *pOldpen = pDC->SelectObject(&m_pen);


	if (m_nRule == SDK_ANALYSE_TRIPWIRE)
	{
		if (&m_curTripwireRule)
		{
			DrawRules(pDC, &m_curTripwireRule);
			if (m_nCurIndex != -1)
			{
				pDC->SelectObject(&m_SelectPen);
				drawline(pDC,m_curTripwire.stLine.stStartPt,m_curTripwire.stLine.stEndPt);
			}
		}
		
	}
	else if (m_nRule == SDK_ANALYSE_PERIMETER)
	{
		if (&m_curPerimeterRule)
		{
			DrawRules(pDC, &m_curPerimeterRule);

			if (m_nCurIndex != -1)
			{
				pDC->SelectObject(&m_SelectPen);
				DrawRules( pDC, &m_curPerimeterRule);
			}
		}
		
	}

	pDC->SelectObject( pOldpen );
	//CDialog::OnPaint();
}

static int __stdcall RealDataCallBack(long lRealHandle, 
									  long dwDataType, unsigned char *pBuffer,
									  long lbufsize,long dwUser)
{
	CDlgRuleArea*pDataChnl = (CDlgRuleArea*)dwUser;
	H264_PLAY_InputData( pDataChnl->m_nPlaydecHandle ,pBuffer, lbufsize );
	pDataChnl->m_bCallBack = TRUE;
	
	return 1;
}

int CDlgRuleArea::ConnectRealPlay(HWND hWnd,int channel)
{
	if(m_nPlayhandle != -1)
	{		
		H264_DVR_DelRealDataCallBack(m_nPlayhandle, RealDataCallBack, (long)this);
		H264_DVR_StopRealPlay(m_nPlayhandle);
	}
	
	if (m_nPlaydecHandle == -1)
	{
		//open decoder
		BYTE byFileHeadBuf;
		if (H264_PLAY_OpenStream(PREVIEW_DECODER_CHANNEL, &byFileHeadBuf, 1, SOURCE_BUF_MIN * 50))
		{	
			H264_PLAY_SetStreamOpenMode(PREVIEW_DECODER_CHANNEL, STREAME_REALTIME);
			H264_PLAY_SetOverlayMode(PREVIEW_DECODER_CHANNEL, TRUE, RGB(100,100,255));
			if (H264_PLAY_Play(PREVIEW_DECODER_CHANNEL, hWnd))
			{
				m_nPlaydecHandle = PREVIEW_DECODER_CHANNEL;
			}
		}	
	}
	H264_DVR_CLIENTINFO playstru;
	
	playstru.nChannel = channel;
	playstru.nStream = 0;
	playstru.nMode = 0;
	m_nPlayhandle = H264_DVR_RealPlay(loginID, &playstru);	
	if(m_nPlayhandle <= 0)
	{
		MessageBox(_CS("Error.SubConErr"));
	}
	else
	{
		H264_DVR_SetRealDataCallBack(m_nPlayhandle, RealDataCallBack, (long)this);
		m_bCallBack = FALSE;
	}
	return m_nPlayhandle;
}
// 启动视频预览.
//..............
bool CDlgRuleArea::StartUpPreview(BOOL bPreview)
{
	long m_LoginID=0;
	if (bPreview)
	{
		int nFlag = 1;
		H264_DVR_DEVICEINFO OutDev;
		int nError = 0;
		if (m_lLoginHandle<=0)
		{
			m_lLoginHandle=H264_DVR_Login(deviceInfo.szDevIP, deviceInfo.dwPort, deviceInfo.szUserName, 
				deviceInfo.szPassWord, &OutDev, &nError );
			if (m_lLoginHandle <= 0)
			{
				return FALSE;
			}
			ConnectRealPlay(NULL,m_nChannelNum);
		}
		else
		{
			if (m_lLastDevID != deviceInfo.ID)
			{
				H264_DVR_Logout(m_lLoginHandle);
				m_lLoginHandle = H264_DVR_Login(deviceInfo.szDevIP, deviceInfo.dwPort, deviceInfo.szUserName, 
					deviceInfo.szPassWord, &OutDev, &nError );
				if (m_lLoginHandle <= 0)
				{
					return FALSE;
				}
				ConnectRealPlay(NULL,m_nChannelNum);
			}
			
		}
		m_lLastDevID = deviceInfo.ID;
		// 	int ret = H264_DVR_SetDevConfig(m_LoginID,E_SDK_VIDEO_PREVIEW, -1, (char *)&nFlag, 0 );
		//((CClientDemo5Dlg*)m_lDlg)->OnBtnLogin();
		//ConnectRealPlay(NULL,m_nChannelNum);
		//int ret =CUserDataManager::instance()->StartPreview(NULL, m_nChannelNum);
	}else
	{
		int nFlag = 0;
		// int ret = H264_DVR_SetDevConfig(m_LoginID,E_SDK_VIDEO_PREVIEW, -1, (char *)&nFlag , 0 );
		StopRealPlay();
		//int ret = CUserDataManager::instance()->StopPreview(NULL, m_nChannelNum);
	}
// 	if (bPreview)
// 	{
// 		int ret =CUserDataManager::instance()->StartPreview(NULL, m_nChannelNum);
// 	}else
// 	{
// 		int ret = CUserDataManager::instance()->StopPreview(NULL, m_nChannelNum);
// 	}
	return 0;
}


bool CDlgRuleArea::StopRealPlay()
{
	if(m_nPlayhandle != -1)
	{		
		H264_DVR_DelRealDataCallBack(m_nPlayhandle, RealDataCallBack, (long)this);
		H264_DVR_StopRealPlay(m_nPlayhandle);
		m_nPlayhandle = -1;
	}	
	
	//关闭解码
	H264_PLAY_CloseStream(m_nPlaydecHandle);
	H264_PLAY_Stop(m_nPlaydecHandle);
	m_nPlaydecHandle = -1;
	
	
	H264_DVR_Logout(m_lLastDevID);
	m_lLastDevID = -1;
	
	// 	Invalidate();
	return true;
}
bool CDlgRuleArea::CatchPic()
{
	long m_LoginID=0;
	// int nRet = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CATCHPIC, -1, 0, 0 );
	//int nRet = CUserDataManager::instance()->CatchPic(NULL ,m_nChannelNum,m_strFileName);
	int i = 0;
	
	while(!m_bCallBack && i < 3)
	{
		
		
		Sleep(1000);
		i++;
	}	
	Sleep(1000);
	return H264_PLAY_CatchPic(m_nPlaydecHandle,m_strFileName);
// 	int nRet = CUserDataManager::instance()->CatchPic(NULL ,m_nChannelNum,m_strFileName);
}

BOOL CDlgRuleArea::GetAppPath(char *szPath)
{
	try
	{	
		CString strCurdir;
		strCurdir = GET_MODULE_FILE_INFO.strPath ;

		strcat( szPath , strCurdir.GetBuffer(0) );	
	}
	catch(...)
	{	
		return FALSE;
	}
	return TRUE;
}
void CDlgRuleArea::InitDlgInfo(SDK_RULECONFIG* pRule,int nRule,int nChannelNum)
{
	
	m_bSelected = false;
	m_bDrawLine = false;
	m_nCurIndex = -1;
	m_nPerimeterNum = 0;
	m_nTripwireNum = 0;
	m_nChannelNum = nChannelNum;
	m_nRule = nRule;
	CString FileName,FilePath;
	COleDateTime dtDateTime;
	dtDateTime = COleDateTime::GetCurrentTime();			
	CString strDateTime = dtDateTime.Format(_T("%Y%m%d_%H%M%S"));

	char lpstrConstring[256];
	memset(lpstrConstring,0,sizeof(lpstrConstring));
	BOOL bResult = GetAppPath(lpstrConstring);

	char szPath[256];
	memset( szPath , 0 , sizeof(szPath));
	sprintf(szPath,"%sPicture",lpstrConstring);
	FilePath = szPath;

	char szName[256];
	memset( szName, 0 , sizeof(szName));
	sprintf(szName,_T("%s\\%s.bmp"),FilePath,strDateTime.GetBuffer(0));
	strcpy(m_strFileName , szName);
 	StartUpPreview(TRUE);
 	CatchPic();
 	StartUpPreview(FALSE);
	
	if (pRule)
	{
		memcpy(&m_curTripwireRule,&pRule->stRulePea.stTripwireRulePara,sizeof(m_curTripwireRule));
		memcpy(&m_curPerimeterRule,&pRule->stRulePea.stPerimeterRulePara,sizeof(m_curPerimeterRule));
		m_nPerimeterNum = m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum;
		for (int i = 0; i< SDK_URP_MAX_TRIPWIRE_CNT; i++)
		{
			if (m_curTripwireRule.astLines[i].iValid)
			{
				m_nTripwireNum++;
			}
			
		}
	}
	else
	{	
		memset( &m_curPerimeterRule, 0, sizeof(m_curPerimeterRule) );
		memset( &m_curTripwireRule, 0, sizeof(m_curTripwireRule) );	
	}

	memset( &m_curTripwire, 0, sizeof(m_curTripwire) );


	if (m_nRule == SDK_ANALYSE_TRIPWIRE)
	{
		m_bCanDraw = m_nTripwireNum>= SDK_URP_MAX_TRIPWIRE_CNT? false:true;
	}
	else if (m_nRule == SDK_ANALYSE_PERIMETER)
	{
		m_bCanDraw = m_nPerimeterNum>=1? false:true;
	}
}


void CDlgRuleArea::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_contextMenu.DestroyMenu();
	OnOK();
}
void CDlgRuleArea::OnCancel()
{
	m_contextMenu.DestroyMenu();
	CDialog::OnCancel();
}
void CDlgRuleArea::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint pt;
	//判断是否在图片显示区域内
	if ( CheckOutArea(point))
	{
		CDialog::OnLButtonDown(nFlags, point);
		return;
	}
	pt.x = point.x - m_nPicLeft;
	pt.y = point.y - m_nPicTop;
	//
	//不处于画线状态,则查看是否选择某个规则
	if ( !m_bDrawLine)
	{
		m_bSelected = CheckSelect(pt);
		if (m_bSelected)
		{
			CDialog::OnLButtonDown(nFlags, point);
			return;
		}
		
	}

	if(m_nCurIndex!=-1)
	{
		m_bSelected = false;
		CDC *pDC = m_bkPic.GetDC();
		CPen *pOldpen = pDC->SelectObject(&m_pen);
		if (SDK_ANALYSE_TRIPWIRE == m_nRule)
		{
			drawline(pDC,m_curTripwire.stLine.stStartPt,m_curTripwire.stLine.stEndPt);
		}
		else if (SDK_ANALYSE_PERIMETER == m_nRule)
		{
			DrawRules( pDC, &m_curPerimeterRule);
		}
			
		pDC->SelectObject( pOldpen );
		m_nCurIndex = -1;
	}
	m_MouseDown = true;
	m_ptOrigin = point;

	if (SDK_ANALYSE_TRIPWIRE == m_nRule && m_bCanDraw)
	{
		
		if (!m_bDrawLine)
		{
			m_curTripwire.stLine.stStartPt.X = pt.x;
			m_curTripwire.stLine.stStartPt.Y = pt.y;
			m_curTripwire.stLine.stEndPt.X = pt.x;
			m_curTripwire.stLine.stEndPt.Y = pt.y;
			
			m_bDrawLine = true;
			m_ptEnd = point;
		}
		else
		{
			m_curTripwire.stLine.stEndPt.X = pt.x;
			m_curTripwire.stLine.stEndPt.Y = pt.y;
			CDC *pDC = m_bkPic.GetDC();

			CPen *pOldpen = pDC->SelectObject(&m_pen);
			drawline(pDC, m_curTripwire.stLine.stStartPt,m_curTripwire.stLine.stEndPt);
			m_curTripwire.iForbiddenDirection = 180;
			OnMenucontextMenuEdit();

			if (m_nTripwireNum>= SDK_URP_MAX_TRIPWIRE_CNT)
			{
				m_bCanDraw = false;
			}
			pDC->SelectObject(pOldpen);
		}
	}
	else if ( SDK_ANALYSE_PERIMETER == m_nRule && m_bCanDraw)
	{
		//有效点数0说明刚开始画曲线
		m_ptOrigin = point;
		if (m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum == 0 && m_bCanDraw)
		{
			m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[0].X = pt.x;
			m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[0].Y = pt.y;
			m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum = 1;
			m_bDrawLine = true;
			m_ptEnd = point;
		}
		else
		{
			m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum].X = pt.x;
			m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum].Y = pt.y;

			CDC *pDC = m_bkPic.GetDC();

			CPen *pOldpen = pDC->SelectObject(&m_pen);
			drawline(pDC, m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum - 1], m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum]);

			m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum ++;

			if ( m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum >= SDK_MAX_BOUNDARY_POINT_NUM )
			{
				drawline(pDC, m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[0], m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[SDK_MAX_BOUNDARY_POINT_NUM-1]);

				//保存鼠标信心，最多就8个点, 到了8个点就认为已经结束，保存
				m_curPerimeterRule.iMode = 0;
				OnMenucontextMenuEdit();
			}

			pDC->SelectObject(pOldpen);
		}	
	}
	CDialog::OnLButtonDown(nFlags, point);

}

void CDlgRuleArea::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnRButtonDown(nFlags, point);
}

void CDlgRuleArea::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bDrawLine && m_bCanDraw)
	{
		if (CheckOutArea(point))
		{
			memset(&m_curPerimeterRule,0,sizeof(SDK_URP_PERIMETER_RULE_PARA_S));
			m_curTripwire.iValid = 0;
			m_MouseDown = false;
			m_bDrawLine = false;

			CRect rtPic;
			m_bkPic.GetWindowRect(&rtPic);
			ScreenToClient(&rtPic);
			rtPic.right+=5;
			rtPic.bottom+=5;
			InvalidateRect(rtPic);   
		}
		else
		{
			CDC *pDC = GetDC();
			pDC->SelectObject(&m_pen);
			int nOldMode = pDC->SetROP2 (R2_NOT);
			pDC->MoveTo (m_ptOrigin);
			pDC->LineTo (m_ptEnd);
			pDC->MoveTo (m_ptOrigin);
			pDC->LineTo (point);
			m_ptEnd = point;		
		}
	
	}
	CDialog::OnMouseMove(nFlags, point);
}
void CDlgRuleArea::ReInit()
{
	for ( int i =0 ; i < NET_MAX_CHANNUM; i ++ )
	{
		m_bGet[i] = false;
	}
	m_bGetType = false;
}	

//保存当前规则
bool CDlgRuleArea::SaveCurRule()
{
	int nChannelNo = 0;
// 	if ( nChannelNo == CUserDataManager::instance()->GetSysInfo()->byChanNum )
// 	{
// 		nChannelNo = 0;
// 	}
	
	if ( SDK_ANALYSE_TRIPWIRE == m_nRule && m_nCurIndex ==-1)
	{
		m_curTripwire.iValid = 1;
		for (int i =0; i < SDK_URP_MAX_TRIPWIRE_CNT ; i++)
		{
			if (m_curTripwireRule.astLines[i].iValid==0)
			{
				m_curTripwireRule.astLines[i] = m_curTripwire;
				memset(&m_curTripwire,0,sizeof(m_curTripwire));
				break;
			}
		}	
		m_nTripwireNum++;
	}
	else if (SDK_ANALYSE_PERIMETER == m_nRule)
	{
		m_nPerimeterNum ++;	
		if (m_nPerimeterNum >=1)
		{
			m_bCanDraw  =false;
		}
	}
	m_bDrawLine = false;
	return true;
}

int CDlgRuleArea::PointToLine(URP_SDK_POINT_S DotPoint, URP_SDK_POINT_S startPoint, URP_SDK_POINT_S endPoint)
{
	bool bSwitch =   false;   
	int nPointToLineDistance;   
	//   如果经过点并且与直线段垂直的直线和直线段的交点在直线段内，计算点到直线段的距离就用通常的   
	//   点到直线的距离公式计算. bSwitch =   true;   
	//   如果经过点并且与直线段垂直的直线和直线段的交点不在直线段内，计算点到直线段的距离就为点到   
	//   直线段两个端点的距离较小的一个. bSwitch =   false;   

	//   点到直线段两端的距离,     
	//   计算点到线段起点的距离   
	int nOffsetX = DotPoint.X - startPoint.X;   
	int nOffsetY = DotPoint.Y - startPoint.Y;   

	double dbSquareOfDistance = pow( (double)abs(nOffsetX), 2 ) + pow( (double)abs(nOffsetY), 2 );   

	double dbPointToptStartDistance = sqrt(dbSquareOfDistance);   

	//   计算点到线段终点的距离   
	nOffsetX = DotPoint.X - endPoint.X;   
	nOffsetY = DotPoint.Y - endPoint.Y;   

	dbSquareOfDistance = pow( (double)abs(nOffsetX), 2 ) + pow( (double)abs(nOffsetY), 2 );   

	double dbPointToptEndDistance = sqrt(dbSquareOfDistance);   

	//   计算直线段的长度   
	nOffsetX = startPoint.X- endPoint.X;   
	nOffsetY = startPoint.Y - endPoint.Y;   

	dbSquareOfDistance = pow((double)abs(nOffsetX), 2) + pow((double)abs(nOffsetY), 2);   

	double dbLineLength = sqrt(dbSquareOfDistance);   

	//   如果经过点并与直线段垂直的直线和直线段的交点在直线段内，点和直线段的两个端点构成的三角形为一个非钝角   
	//   三角形，极限为一个直角三角形，其中一条直边为点到直线段两个端点距离较小的那条，直角三角形的斜边为点到   
	//   直线段两个端点距离较大那条，要符合条件，也就是点到直线段两个端点的距离中较大一个的平方不会不会大于其   
	//   中较小的一条的平方与直线段的长度平方的和.   
	if( dbPointToptStartDistance > dbPointToptEndDistance )   
	{   
		if( pow(dbPointToptStartDistance, 2) > pow(dbPointToptEndDistance, 2) + pow(dbLineLength, 2))   
		{   
			bSwitch = false;   
			nPointToLineDistance = (int)dbPointToptEndDistance;   
		}   
		else   
			bSwitch = true;   
	}   
	else   
	{   
		if( pow(dbPointToptEndDistance, 2) > pow(dbPointToptStartDistance, 2) + pow( dbLineLength, 2 ) )   
		{   
			bSwitch = false;   
			nPointToLineDistance = (int)dbPointToptStartDistance;   
		}   
		else   
			bSwitch = true;   
	}   

	//   经过点并与直线段垂直的直线与直线段的交点在直线段上.   
	if( bSwitch )   
	{   
		//   点到直线的距离   
		if ( endPoint.Y == startPoint.Y )   
		{   
			nPointToLineDistance = abs (DotPoint.Y - startPoint.Y);   
		}   
		else if ( endPoint.X == startPoint.X )   
		{   
			nPointToLineDistance = abs(DotPoint.X - startPoint.X);   
		}   
		else   
		{   
			//   经过点并与X-Axis平行的直线与直线段所在直线相交，点到相交点的距离乘上相交角的正弦   
			//   即为点到直线的距离   
			double k = ((double)(endPoint.Y- startPoint.Y ))/((double)(endPoint.X- startPoint.X));   

			//   水平距离   
			double dbPointToLineHorizotalDistance = fabs((DotPoint.Y - startPoint.Y)/k + startPoint.X- DotPoint.X);   

			//   相交角   
			double  dbAngle = atan(k);   

			nPointToLineDistance = (int)(dbPointToLineHorizotalDistance * sin(fabs(dbAngle)));   
		}   
	}   

	return   nPointToLineDistance;
};
void CDlgRuleArea::DrawRules(CDC *pDC, SDK_URP_TRIPWIRE_RULE_PARA_S *pRules)
{
	if ( !pRules )
	{
		return;
	}
	for (int i = 0; i < SDK_URP_MAX_TRIPWIRE_CNT ; i++)
	{
		if (pRules->astLines[i].iValid)
		{
			URP_SDK_POINT_S ptStart = pRules->astLines[i].stLine.stStartPt;
			URP_SDK_POINT_S ptEnd = pRules->astLines[i].stLine.stEndPt;
			drawline(pDC,ptEnd,ptStart);
			int iDirection = pRules->astLines[i].iForbiddenDirection;
			int iIsDoubleDirection = pRules->astLines[i].iIsDoubleDirection;
			
			if (iIsDoubleDirection)
			{
				CPen* poldPen = pDC->SelectObject(&m_SelectPen);
				Drawarrows(pDC,pRules->astLines[i].stLine.stStartPt,pRules->astLines[i].stLine.stEndPt);
				Drawarrows(pDC,pRules->astLines[i].stLine.stEndPt,pRules->astLines[i].stLine.stStartPt);
				pDC->SelectObject(poldPen);
			}
			else
			{
				CPen* poldPen = pDC->SelectObject(&m_SelectPen);
				Drawarrows(pDC,pRules->astLines[i].stLine.stStartPt,pRules->astLines[i].stLine.stEndPt);
				pDC->SelectObject(poldPen);
			}
		}		
	}
}

double _sqrt(double a)
{
	double x1 = 0.0;
	double x2 = a/2;
	while(x1 != x2)
	{
		x1 = x2;
		x2 = (x1 + a /x1) / 2;
	}
	return x1;
}
void CDlgRuleArea::DrawRules(CDC *pDC, SDK_URP_PERIMETER_RULE_PARA_S *pRules)
{
	//方向未加

	int pointNum = pRules->stLimitPara.stBoundary.iBoundaryPtNum;

	if ( !pRules || pointNum==0)
	{
		return;
	}

	for (int i =0; i < pointNum-1 ; i++)
	{
		drawline(pDC,pRules->stLimitPara.stBoundary.astBoundaryPts[i],pRules->stLimitPara.stBoundary.astBoundaryPts[i+1]);
	}
	drawline(pDC,pRules->stLimitPara.stBoundary.astBoundaryPts[0],pRules->stLimitPara.stBoundary.astBoundaryPts[pointNum-1]);

	int maxLen = 0;        //为了简单，这里就保存两点距离的平方
	int maxLenLineID = 0;  //即编号为这个的点和下一个点的距离最大

	//为了简单，最后一个点和第一个点之间的距离就不计算
	for(int j = 0; j < pointNum-1; j++)
	{
		int len = (pRules->stLimitPara.stBoundary.astBoundaryPts[j].X - pRules->stLimitPara.stBoundary.astBoundaryPts[j+1].X) * (pRules->stLimitPara.stBoundary.astBoundaryPts[j].X - pRules->stLimitPara.stBoundary.astBoundaryPts[j+1].X)
			+ (pRules->stLimitPara.stBoundary.astBoundaryPts[j].Y - pRules->stLimitPara.stBoundary.astBoundaryPts[j+1].Y) * (pRules->stLimitPara.stBoundary.astBoundaryPts[j].Y - pRules->stLimitPara.stBoundary.astBoundaryPts[j+1].Y);

		if(len > maxLen)
		{
			maxLen = len;
			maxLenLineID = j;
		}
	}

	URP_SDK_POINT_S pointBegin, pointEnd;

	pointBegin.X = pRules->stLimitPara.stBoundary.astBoundaryPts[maxLenLineID].X;
	pointBegin.Y = pRules->stLimitPara.stBoundary.astBoundaryPts[maxLenLineID].Y;
	pointEnd.X = pRules->stLimitPara.stBoundary.astBoundaryPts[maxLenLineID + 1].X;
	pointEnd.Y = pRules->stLimitPara.stBoundary.astBoundaryPts[maxLenLineID + 1].Y;

	if(pRules->iMode == IMP_URP_PMODE_INTRUSION)
	{
		Drawarrows(pDC,pointBegin, pointEnd);
		Drawarrows(pDC,pointEnd, pointBegin);
		return;
	}
	else
	{
		//得到该最长线段(简称为线段L)对应的直线的表达式(形如 y = kx + b)，
		//         为了不损失精度，两边同时乘上一个大点的数z，最终格式为 zy = z(kx + b) = mx + n
		//如果其它点都在L对应的直线一侧，则直接画箭头，函数结束
		//如果其它点在L两侧都有
		//  选中线段L的中点，沿着X轴的正方向做射线(如果该射线与线段L的斜率是一样的，则沿着Y轴的正方向做射线)
		//  计算射线与多边形相交的边数，如果一个点交点属于两条边，则算与两条边都相交
		//  如果相交的边数为奇数个，则表示线段L的X轴正方向(或Y轴正方向)属于区域内，画箭头，函数结束
		//  如果相交的边数为偶数个，则表示线段L的X轴正方向(或Y轴正方向)属于区域内部，画箭头，函数结束

		int m; //直线斜率
		int n; //直线与y轴交点

		//表达式两边乘的倍数 z = (pointBegin.x - pointEnd.x)
		m = pointBegin.Y - pointEnd.Y;
		n = (pointBegin.X * pointEnd.Y) - (pointEnd.X * pointBegin.Y);

		int y0 = 0; //因为m和n都乘上了(pointBegin.x - pointEnd.x)，所以判断的时候y0也要乘上这个值
		int x0 = 0;
		int y = 0; //y = m * x0 + n  x0和y0是点的坐标，通过比较y和y0的大小，就可以确定两个点是否在一条直线的同一侧
		int side1 = 0;
		int side2 = 0;

		if(pointBegin.X == pointEnd.X)
		{
			for(int i = 0; i < pointNum; i++)
			{
				x0 = pRules->stLimitPara.stBoundary.astBoundaryPts[i].X;
				if(x0 > pointBegin.X + 3) //加3是考虑到运算的时候可能有精度误差
				{
					side1 ++;
				}
				else if(x0 > pointBegin.X - 3)
				{
					side2 ++;
				}
			}
		}
		else
		{
			for(int i = 0; i < pointNum; i++)
			{
				y0 = pRules->stLimitPara.stBoundary.astBoundaryPts[i].Y * (pointBegin.X - pointEnd.X);
				x0 = pRules->stLimitPara.stBoundary.astBoundaryPts[i].X;
				y  = m * x0 + n;

				if(y > y0 + 3) //加3是考虑到运算的时候可能有精度误差
				{
					side1 ++;
				}
				else if(y < y0 - 3)
				{
					side2 ++;
				}
			}
		}

		//所有点都在最长的线段一侧(在线上的也算)，直接画箭头
		if((side1 == 0 && pRules->iMode == IMP_URP_PMODE_EXIT)
			|| (side2 == 0 && pRules->iMode == IMP_URP_PMODE_ENTER))
		{
			Drawarrows(pDC,pointBegin, pointEnd);
			return;
		}
		else if((side1 == 0 && pRules->iMode == IMP_URP_PMODE_ENTER)
			|| (side2 == 0 && pRules->iMode == IMP_URP_PMODE_EXIT))
		{
			Drawarrows(pDC,pointEnd,pointBegin);
			return;
		}
		else //这些点在线段两侧
		{
			int crossPointCount = 0;

			URP_SDK_POINT_S midPoint;
			midPoint.X = (pointBegin.X + pointEnd.X) / 2;
			midPoint.Y= (pointBegin.Y + pointEnd.Y) / 2;

			if(pointBegin.Y != pointEnd.Y) //最长的线段不是水平的，向X轴正方向做射线
			{
				for(int i = 0; i < pointNum - 1; i++)
				{
					if(i == maxLenLineID)
					{
						continue;
					}
					if(pRules->stLimitPara.stBoundary.astBoundaryPts[i].X >= midPoint.X && pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].X >= midPoint.X)
					{
						if((pRules->stLimitPara.stBoundary.astBoundaryPts[i].Y >= midPoint.Y && pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].Y <= midPoint.Y)
							|| (pRules->stLimitPara.stBoundary.astBoundaryPts[i].Y <= midPoint.Y && pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].Y >= midPoint.Y))
						{
							crossPointCount ++;
						}
					}
				}
			}
			else //向Y轴正方向做射线
			{
				for(int i = 0; i < maxLenLineID - 1; i++)
				{
					if(i == maxLenLineID)
					{
						continue;
					}
					if(pRules->stLimitPara.stBoundary.astBoundaryPts[i].Y > midPoint.Y && pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].Y >= midPoint.Y)
					{
						if((pRules->stLimitPara.stBoundary.astBoundaryPts[i].X >= midPoint.X && pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].X <= midPoint.X)
							|| (pRules->stLimitPara.stBoundary.astBoundaryPts[i].X <= midPoint.X && pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].X >= midPoint.X))
						{
							crossPointCount ++;
						}
					}
				}
			}
			if(crossPointCount % 2 == 1) //最长线段的X轴正方向(或Y轴正方向)是区域内部
			{
				if(pRules->iMode == IMP_URP_PMODE_ENTER)
				{
					if((pointBegin.Y < pointEnd.Y)
						|| ((pointBegin.Y == pointEnd.Y) && (pointBegin.X < pointEnd.X)))
					{
						Drawarrows(pDC,pointEnd,pointBegin);
					}
					else
					{
						Drawarrows(pDC,pointBegin, pointEnd);
					}
				}
				else if(pRules->iMode == IMP_URP_PMODE_EXIT)
				{
					if((pointBegin.Y < pointEnd.Y)
						|| ((pointBegin.Y == pointEnd.Y) && (pointBegin.X < pointEnd.X)))
					{
						Drawarrows(pDC,pointBegin, pointEnd);
					}
					else
					{
						Drawarrows(pDC,pointEnd,pointBegin);
					}
				}
			}
			else //最长线段的X轴负方向(或Y轴负方向)是区域内部
			{
				if(pRules->iMode == IMP_URP_PMODE_ENTER)
				{
					if((pointBegin.Y < pointEnd.Y)
						|| ((pointBegin.Y == pointEnd.Y) && (pointBegin.X < pointEnd.X)))
					{
						Drawarrows(pDC,pointBegin, pointEnd);
					}
					else
					{
						Drawarrows(pDC,pointEnd,pointBegin);
					}
				}
				else if(pRules->iMode == IMP_URP_PMODE_EXIT)
				{
					if((pointBegin.Y < pointEnd.Y)
						|| ((pointBegin.Y == pointEnd.Y) && (pointBegin.X < pointEnd.X)))
					{
						Drawarrows(pDC,pointEnd,pointBegin);
					}
					else
					{
						Drawarrows(pDC,pointBegin, pointEnd);
					}
				}
			}
		}
	}
	/*URP_SDK_POINT_S ptCenter;
	URP_SDK_POINT_S ptMid;
	memset(&ptCenter, 0, sizeof(URP_SDK_POINT_S));
	if (pointNum>2)
	{
		int nItemlengthMax = 0;
		int lengthMax = 0;

		for(int i =0; i < pointNum-1 ; i++)
		{

			ptCenter.X = (ptCenter.X+ pRules->stLimitPara.stBoundary.astBoundaryPts[i].X);
			ptCenter.Y = (ptCenter.Y + pRules->stLimitPara.stBoundary.astBoundaryPts[i].Y);

			int x1 = pRules->stLimitPara.stBoundary.astBoundaryPts[i].X;
			int y1 = pRules->stLimitPara.stBoundary.astBoundaryPts[i].Y;
			int x2 = pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].X;
			int y2 = pRules->stLimitPara.stBoundary.astBoundaryPts[i+1].Y;
			
			int len = _sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));    
			if (len > lengthMax)
			{
				lengthMax = len;
				nItemlengthMax = i;
			}
		}
		ptCenter.X = (ptCenter.X+ pRules->stLimitPara.stBoundary.astBoundaryPts[pointNum - 1].X)/pointNum;
		ptCenter.Y = (ptCenter.Y + pRules->stLimitPara.stBoundary.astBoundaryPts[pointNum - 1].Y)/pointNum;
		ptMid.X = (pRules->stLimitPara.stBoundary.astBoundaryPts[nItemlengthMax].X+pRules->stLimitPara.stBoundary.astBoundaryPts[nItemlengthMax+1].X)/2;
		ptMid.Y =  (pRules->stLimitPara.stBoundary.astBoundaryPts[nItemlengthMax].Y+pRules->stLimitPara.stBoundary.astBoundaryPts[nItemlengthMax+1].Y)/2;

		if(ptCenter.X == ptMid.X)
		{
			ptCenter.X -= 5;
		}
		else if(ptCenter.Y == ptMid.Y)
		{
			ptCenter.Y -= 5;
		}
		float ratio = 1.0 * (ptCenter.Y - ptMid.Y) / (ptCenter.X- ptMid.X);
		float tempPointLeft = _sqrt(225.0/(ratio * ratio +1));
		float tempPointTop = tempPointLeft * ratio;
		URP_SDK_POINT_S tempMidPoint = ptMid;
		switch(pRules->iMode)
		{
		case 1:
			if(ptCenter.X > ptMid.X)
			{
				tempMidPoint.X -= tempPointLeft;
				tempMidPoint.Y -= (int)tempPointTop;
			}
			else
			{
				tempMidPoint.X += tempPointLeft;
				tempMidPoint.Y += tempPointTop;
			}
			break;
		case 2:
			if(ptCenter.X > ptMid.X)
			{
				tempMidPoint.X += tempPointLeft;
				tempMidPoint.Y += tempPointTop;
			}
			else
			{
				tempMidPoint.X -= tempPointLeft;
				tempMidPoint.Y-= tempPointTop;
			}
			break;
		default:
			break;
		}

		tempPointLeft = _sqrt(400.0/(1.0/(ratio * ratio) +1));
		tempPointTop = -tempPointLeft / ratio;

		URP_SDK_POINT_S tempPoint[2];
		tempPoint[0].X = (int)(tempMidPoint.X - tempPointLeft);
		tempPoint[0].Y = (int)(tempMidPoint.Y - tempPointTop);
		tempPoint[1].X = (int)(tempMidPoint.X + tempPointLeft);
		tempPoint[1].Y = (int)(tempMidPoint.Y + tempPointTop);

		CPen* poldPen = pDC->SelectObject(&m_SelectPen);

		if (pRules->iMode == 1 || pRules->iMode == 0)
		{		
			if (ptCenter.X > ptMid.X)
			{
				Drawarrows(pDC,tempPoint[0],tempPoint[1],1);
			}
			else
			{
				Drawarrows(pDC,tempPoint[0],tempPoint[1],-1);
			}
		}
		if (pRules->iMode == 2 || pRules->iMode == 0)
		{
			if (ptCenter.X < ptMid.X)
			{
				Drawarrows(pDC,tempPoint[0],tempPoint[1],1);
			}
			else
			{
				Drawarrows(pDC,tempPoint[0],tempPoint[1],-1);
			}
		}

		pDC->SelectObject(poldPen);

	}*/
	
}
void CDlgRuleArea::drawline(CDC *pDC, URP_SDK_POINT_S ptStart, URP_SDK_POINT_S ptEnd)
{
	CPoint start(ptStart.X, ptStart.Y);
	CPoint end(ptEnd.X, ptEnd.Y);

	pDC->MoveTo(start);
	pDC->LineTo(end);
}
bool CDlgRuleArea::CheckOutArea(CPoint point)
{
	RECT   rcpic;
	m_bkPic.GetWindowRect(&rcpic);
	ScreenToClient(&rcpic);

	if ( point.x <= rcpic.right && point.x >= rcpic.left	&& point.y <= rcpic.bottom && point.y >= rcpic.top )
	{
		return false;
	}
	return true;
}
void CDlgRuleArea::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	if (m_bDrawLine)
	{
		int oldMode = pDC->SetROP2 (R2_NOT);
		pDC->SelectObject(&m_pen);
		pDC->MoveTo (m_ptOrigin);
		pDC->LineTo (m_ptOrigin);
		pDC->MoveTo (m_ptOrigin);
		pDC->LineTo (point);
		if (m_nRule == SDK_ANALYSE_TRIPWIRE)
		{
			m_curTripwire.iValid = 0;	
		}
		if ( m_nRule == SDK_ANALYSE_PERIMETER)
		{

			int ptNum = m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum;
			if (ptNum>2)
			{
				CDC * pDC = m_bkPic.GetDC();
				pDC->SelectObject(&m_pen);
				pDC->SetROP2(oldMode);
				drawline(pDC, m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[0], m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum-1]);
			   OnMenucontextMenuEdit();
			}
			if (ptNum <= 2)
			{
				if (ptNum == 2)
				{
					Invalidate(); //待优化
				}			
				memset(&m_curPerimeterRule,0,sizeof(SDK_URP_PERIMETER_RULE_PARA_S));
				m_nPerimeterNum = 0;
			}
			
		}
		m_bDrawLine = false;
		
	}
	else
	{
		CPoint	pt;
		pt.x = point.x - m_nPicLeft;
		pt.y = point.y - m_nPicTop;
		if (CheckSelect(pt))
		{	
			pt = point;
			ClientToScreen(&pt); 
			m_contextMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN,pt.x,pt.y,this);
		}
	}
	
	
	CDialog::OnRButtonUp(nFlags, point);
}

bool CDlgRuleArea::CheckSelect(CPoint pt)
{
		bool bFinded = false;
		if (m_nRule == SDK_ANALYSE_TRIPWIRE)
		{
			for ( int i = 0; i < SDK_URP_MAX_TRIPWIRE_CNT; i ++ )	
			{
				URP_SDK_POINT_S dotPoint;
				dotPoint.X = pt.x;
				dotPoint.Y = pt.y;
				int len = 0;
				if (m_curTripwireRule.astLines[i].iValid  !=0)
				{
					len = PointToLine(dotPoint, m_curTripwireRule.astLines[i].stLine.stStartPt,
						m_curTripwireRule.astLines[i].stLine.stEndPt);

					if ( len <= 4 )
					{
						bFinded = true;
					}

				}
			
				if ( bFinded )
				{
					CDC *pDC = m_bkPic.GetDC();	
					//原先如果有选中的规则，先把原先的恢复成未选中颜色
					if (m_nCurIndex != -1)
					{
						SDK_URP_LINE_S curLine = m_curTripwireRule.astLines[m_nCurIndex].stLine;
						pDC->SelectObject(&m_pen);
						drawline(pDC,curLine.stStartPt,curLine.stEndPt);
					}

					m_curTripwire = m_curTripwireRule.astLines[i];			
					CPen *pOldpen = pDC->SelectObject(&m_SelectPen);
					drawline(pDC,m_curTripwire.stLine.stStartPt,m_curTripwire.stLine.stEndPt);
					pDC->SelectObject( pOldpen );
					m_nCurIndex = i;
					break;
				}

			}
		}


		//如果线没有选中，则判断是否在多边形或者矩形内
		if (SDK_ANALYSE_PERIMETER == m_nRule)
		{

			int nPointNum = m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum;

			CRgn rgnA;
			CPoint *ptVertex = new CPoint[nPointNum];
			for ( int n = 0; n < nPointNum; n ++ )
			{
				ptVertex[n].x = m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[n].X;
				ptVertex[n].y = m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[n].Y;
			}
			rgnA.CreatePolygonRgn( ptVertex, nPointNum, ALTERNATE);

			if ( rgnA.m_hObject&&rgnA.PtInRegion( pt ) )
			{

				m_curPerimeterRule = m_curPerimeterRule;
				CDC *pDC =m_bkPic.GetDC();

				CPen *pOldpen = pDC->SelectObject(&m_SelectPen);
				DrawRules( pDC, &m_curPerimeterRule);
				pDC->SelectObject( pOldpen );
				m_nCurIndex = 0;
				m_bDrawLine = false;
				bFinded = true;
			}

			delete []ptVertex;

		}
		return bFinded;
}

void CDlgRuleArea::OnMenucontextMenuEdit()
{
	// TODO: 在此添加命令处理程序代码
	int iDirection = 0;
	int iIsDoubleDirection = -1;
	if (m_nRule == SDK_ANALYSE_TRIPWIRE)
	{
		int height;
		int width;
		int x1,x2;
		int y1,y2;

		if (m_nCurIndex>=0)
		{
			iIsDoubleDirection =  m_curTripwireRule.astLines[m_nCurIndex].iIsDoubleDirection;
			x1 = m_curTripwireRule.astLines[m_nCurIndex].stLine.stStartPt.X;
			x2 = m_curTripwireRule.astLines[m_nCurIndex].stLine.stEndPt.X;
			y1 = m_curTripwireRule.astLines[m_nCurIndex].stLine.stStartPt.Y;
			y2 = m_curTripwireRule.astLines[m_nCurIndex].stLine.stEndPt.Y;
		}
		else
		{
			iIsDoubleDirection =  0;
			x1 = m_curTripwire.stLine.stStartPt.X;
			x2 = m_curTripwire.stLine.stEndPt.X;
			y1 = m_curTripwire.stLine.stStartPt.Y;
			y2 = m_curTripwire.stLine.stEndPt.Y;
		}

		height = abs( y2 - y1 );
		width  = abs( x2 - x1 );
		
		int radio = 1000;

		if ( width )
		{
			 radio  = height * 100 / width; //为了保持精度，将高乘上10
		}
	

		if(height == 0 || radio <= 58)
		{
			if ( x2 <= x1 )
			{
				iDirection = DIRECTION_UP_DOWN;
			}
			else
			{
				iDirection = DIRECTION_DOWN_UP;
			}
			
		}
		else if(width == 0 || radio > 58)
		{
			if ( y2 <= y1 )
			{
				iDirection = DIRECTION_RIGHT_LEFT;
			}
			else
			{
				iDirection = DIRECTION_LEFT_RIGHT;
			}
			
		}
	}
	else if(m_nRule == SDK_ANALYSE_PERIMETER)
	{
		iDirection = m_curPerimeterRule.iMode;
	}
	CDlgForbidDirection dlg(m_nRule,iDirection,iIsDoubleDirection);
	if (IDOK == dlg.DoModal())
	{
		if (m_nRule == SDK_ANALYSE_TRIPWIRE)
		{
			if (dlg.m_iIsDoubleDirection)
			{
				if ( m_nCurIndex != -1)
				{
					m_curTripwireRule.astLines[m_nCurIndex].iIsDoubleDirection = 1;
					m_curTripwireRule.astLines[m_nCurIndex].iForbiddenDirection = 360;	
				}
				else
				{
					m_curTripwire.iIsDoubleDirection = 1;
					m_curTripwire.iForbiddenDirection = 360;
				}
			}
			else
			{
				SDK_URP_LINE_S* pLine;
				if ( m_nCurIndex == -1)
				{
					pLine = &m_curTripwire.stLine;
				}
				else
				{
					pLine = &m_curTripwireRule.astLines[m_nCurIndex].stLine;
				}

				
				if ((dlg.m_nDirection - 1) == (iDirection%2))
				{
					URP_SDK_POINT_S ptTemp;
					ptTemp = pLine->stEndPt;
					pLine->stEndPt = pLine->stStartPt;
					pLine->stStartPt = ptTemp;
				}
				
				if ( m_nCurIndex != -1)
				{
					m_curTripwireRule.astLines[m_nCurIndex].iIsDoubleDirection = 0;
					m_curTripwireRule.astLines[m_nCurIndex].iForbiddenDirection = 180;	
				}
				else
				{
					m_curTripwire.iForbiddenDirection = 180;
					m_curTripwire.iIsDoubleDirection = 0;
				}
			}
			
		}
		else if(m_nRule == SDK_ANALYSE_PERIMETER)
		{
			m_curPerimeterRule.iMode = dlg.m_nDirection-1;
		}
		
		SaveCurRule();

	}
	else
	{
		if (m_nCurIndex<0)
		{
			m_curTripwire.iValid = 0;
			memset(&m_curPerimeterRule.stLimitPara.stBoundary,0,sizeof(SDK_URP_PERIMETER_LIMIT_BOUNDARY_S));
		}
		
	}
	m_bDrawLine = false;
	CRect rcpic;
	m_bkPic.GetWindowRect(&rcpic);
	ScreenToClient(&rcpic);
	InvalidateRect(rcpic);
}

void CDlgRuleArea::OnMenucontextMenuDelete()
{
	if (m_nRule == SDK_ANALYSE_TRIPWIRE)
	{
		if (m_curTripwireRule.astLines[m_nCurIndex].iValid !=0)
		{
			m_curTripwireRule.astLines[m_nCurIndex].iValid = 0;
		}	
		m_nTripwireNum--;
		if (m_nTripwireNum < SDK_URP_MAX_TRIPWIRE_CNT)
		{
			m_bCanDraw = true;
		}
		m_nCurIndex = -1;
		memset(&m_curTripwire,0,sizeof(SDK_URP_LINE_S));
	}
	else if (m_nRule == SDK_ANALYSE_PERIMETER)
	{
		memset(&m_curPerimeterRule.stLimitPara.stBoundary,0,sizeof(m_curPerimeterRule.stLimitPara.stBoundary));
		
		m_bCanDraw = true;
		m_nCurIndex = -1;
	}
	CRect rtPic;
	m_bkPic.GetWindowRect(&rtPic);
	ScreenToClient(&rtPic);
	InvalidateRect(rtPic);   

	// TODO: 在此添加命令处理程序代码
}


void CDlgRuleArea::Drawarrows(CDC* pDC,URP_SDK_POINT_S point1, URP_SDK_POINT_S point2)
{
	int xExpand = -1;
	int yExpand = -1;

	if(point1.X == point2.X)
	{
		yExpand = 0;
		if(point2.Y > point1.Y)
		{
			xExpand = 1;
		}
	}
	else if(point1.Y == point2.Y)
	{
		xExpand = 0;
		if(point2.X > point1.X)
		{
			yExpand = 1;
		}
	}
	else
	{
		if(point2.X > point1.X)
		{
			yExpand = 1;
		}

		if(point2.Y < point1.Y)
		{
			xExpand = 1;
		}
	}

	CPoint arrowsPoint1,arrowsPoint2,arrowsPoint3;

	CPoint midPoint;
	midPoint.x = (point1.X + point2.X) / 2;
	midPoint.y = (point1.Y + point2.Y) / 2;

	if(point1.X == point2.X)
	{
		arrowsPoint1.x = (int)midPoint.x + 30 * xExpand;
		arrowsPoint1.y = (int)midPoint.y;
		arrowsPoint2.x = (int)midPoint.x + 20 * xExpand;
		arrowsPoint2.y = (int)midPoint.y - 10;
		arrowsPoint3.x = (int)midPoint.x + 20 * xExpand;
		arrowsPoint3.y = (int)midPoint.y + 10;
	}
	else if(point1.Y == point2.Y)
	{
		arrowsPoint1.x = (int)midPoint.x;
		arrowsPoint1.y = (int)midPoint.y + 30 * yExpand;
		arrowsPoint2.x = (int)midPoint.x - 10;
		arrowsPoint2.y = (int)midPoint.y + 20 * yExpand;
		arrowsPoint3.x = (int)midPoint.x + 10;
		arrowsPoint3.y = (int)midPoint.y + 20 * yExpand;
	}
	else
	{
		float arrowsPointLeft, arrowsPointTop;
		float ratio = 1.0 * (point1.Y - point2.Y)/(point1.X - point2.X);

		arrowsPointLeft = (30.0 / _sqrt(1.0 / (ratio * ratio) +1)) * xExpand;
		arrowsPointTop = abs(arrowsPointLeft / ratio) * yExpand;
		arrowsPoint1.x = (int)(arrowsPointLeft + midPoint.x);
		arrowsPoint1.y = (int)(arrowsPointTop + midPoint.y);

		arrowsPointLeft = (20.0 / _sqrt(1.0 / (ratio * ratio) +1)) * xExpand;
		arrowsPointTop = abs(arrowsPointLeft / ratio) * yExpand;
		float tempPointLeft = _sqrt(100.0/(ratio * ratio +1));
		float tempPointTop  = tempPointLeft * ratio;
		arrowsPoint2.x = (int)(midPoint.x + arrowsPointLeft + tempPointLeft);
		arrowsPoint2.y = (int)(midPoint.y + arrowsPointTop + tempPointTop);
		arrowsPoint3.x = (int)(midPoint.x + arrowsPointLeft - tempPointLeft);
		arrowsPoint3.y = (int)(midPoint.y + arrowsPointTop - tempPointTop);
	}

	arrowsPoint1.x = (arrowsPoint1.x + midPoint.x) / 2;
	arrowsPoint1.y = (arrowsPoint1.y + midPoint.y) / 2;

	arrowsPoint2.x += midPoint.x - arrowsPoint1.x;
	arrowsPoint2.y += midPoint.y - arrowsPoint1.y;

	arrowsPoint3.x += midPoint.x - arrowsPoint1.x;
	arrowsPoint3.y += midPoint.y - arrowsPoint1.y;

	midPoint.x = 2 * midPoint.x - arrowsPoint1.x;
	midPoint.y = 2 * midPoint.y - arrowsPoint1.y;

	pDC->MoveTo(arrowsPoint1.x, arrowsPoint1.y);
	pDC->LineTo(midPoint.x, midPoint.y);

	//画箭头符号
	pDC->MoveTo(arrowsPoint1.x, arrowsPoint1.y);
	pDC->LineTo(arrowsPoint2.x, arrowsPoint2.y);

	pDC->MoveTo(arrowsPoint1.x, arrowsPoint1.y);
	pDC->LineTo(arrowsPoint3.x, arrowsPoint3.y);
}

void CDlgRuleArea::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint	pt;
	pt.x = point.x - m_nPicLeft;
	pt.y = point.y - m_nPicTop;
	if (CheckSelect(pt))
	{	
		OnMenucontextMenuEdit();
	}
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDlgRuleArea::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (m_nRule == SDK_ANALYSE_TRIPWIRE)
	{
		for (int i=0 ; i < SDK_URP_MAX_TRIPWIRE_CNT ; i++)
		{
			SDK_URP_LINE_S lineTemp;
			if (m_curTripwireRule.astLines[i].iValid)
			{
				lineTemp = m_curTripwireRule.astLines[i].stLine;
				m_curTripwireRule.astLines[i].stLine.stStartPt.X = (short)(lineTemp.stStartPt.X*((double)m_nPicWidth/8192));
				m_curTripwireRule.astLines[i].stLine.stStartPt.Y = (short)(lineTemp.stStartPt.Y*((double)m_nPicHeight/8192));
				m_curTripwireRule.astLines[i].stLine.stEndPt.X = (short)(lineTemp.stEndPt.X*((double)m_nPicWidth/8192));
				m_curTripwireRule.astLines[i].stLine.stEndPt.Y = (short)(lineTemp.stEndPt.Y*((double)m_nPicHeight/8192));
			}
		}
	}
	else if (m_nRule == SDK_ANALYSE_PERIMETER)
	{
		URP_SDK_POINT_S ptTemp;
		for (int i=0 ; i<m_curPerimeterRule.stLimitPara.stBoundary.iBoundaryPtNum; i++)
		{
			ptTemp =m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[i];
			m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[i].X = (short)(ptTemp.X*((double)m_nPicWidth/8192));
			m_curPerimeterRule.stLimitPara.stBoundary.astBoundaryPts[i].Y = (short)(ptTemp.Y*((double)m_nPicHeight/8192));
		}	
	}		
	// TODO: 在此处添加消息处理程序代码
}
