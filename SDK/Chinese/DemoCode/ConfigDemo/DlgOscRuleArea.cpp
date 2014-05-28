// DlgOscRuleArea.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DlgOscRuleArea.h"
//#include "UserDataManager.h"
#include "ClientDemo5.h"
#include "ClientDemo5Dlg.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOscRuleArea dialog
extern   CClientDemo5App   theApp;
extern long loginID;
CDlgOscRuleArea::CDlgOscRuleArea(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOscRuleArea::IDD, pParent)
{
// 	OldResourceHanlde= AfxGetResourceHandle();//保存以前的资源搜索模块   
// 	AfxSetResourceHandle(theApp.m_hInstance);//设置新的模块 
	m_pen.CreatePen(0,2,RGB(0,255,0));
	m_SelectPen.CreatePen(0,2,RGB(255,0,0));
	for ( int i =0 ; i < NET_MAX_CHANNUM; i ++ )
	{
		m_bGet[i] = false;
	}
	m_bGetType = false;
	m_nChannelNum = 0;
	m_MouseDown = false;
	m_bCanDraw = false;
	m_bDrawLine = false;
	m_nPlayhandle = -1;
	m_nPlaydecHandle = -1;
    m_bCallBack=false;
	m_lLastDevID = -1;
	m_lLoginHandle=-1;
}

CDlgOscRuleArea::~CDlgOscRuleArea()
{
	m_contextMenu.DestroyMenu();
}

void CDlgOscRuleArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOscRuleArea)
	DDX_Control(pDX, IDC_STATIC_PIC, m_bkPic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOscRuleArea, CDialog)
	//{{AFX_MSG_MAP(CDlgOscRuleArea)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_MENUCONTEXT_MENU_EDIT, CDlgOscRuleArea::OnMenucontextMenuEdit)
	ON_COMMAND(ID_MENUCONTEXT_MENU_DELETE, CDlgOscRuleArea::OnMenucontextMenuDelete)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOscRuleArea message handlers

void CDlgOscRuleArea::OnOK() 
{
	// TODO: Add extra validation here
	m_contextMenu.DestroyMenu();
	CDialog::OnOK();
}

void CDlgOscRuleArea::OnCancel() 
{
	// TODO: Add extra validation here
	m_contextMenu.DestroyMenu();
	CDialog::OnCancel();
}

BOOL CDlgOscRuleArea::OnInitDialog() 
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
 	
	return TRUE; 
}

void CDlgOscRuleArea::OnPaint() 
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
	DWORD nReturn=0;
	long m_LoginID=0;
	H264_DVR_DEVICEINFO deviceInfo;
	int nRet = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSINFO,-1, (char *)&deviceInfo,sizeof(deviceInfo),&nReturn);
	int nChannelNo =0;//目前只支持单通道（通道一）
	if ( nChannelNo == deviceInfo.byChanNum )
	{
		nChannelNo = 0;
	}	
	CPen *pOldpen = pDC->SelectObject(&m_pen);
	
	DrawRules(pDC, &m_curRule);
	
	pDC->SelectObject( pOldpen );
}

void CDlgOscRuleArea::initDlgInfo(SDK_URP_OSC_RULE_PARA_S *pRulePara, RulePara iRulePara,int nChannelNum)
{
	m_bCanDraw = false;
	m_nChannelNum = nChannelNum;
	m_rulePara = iRulePara;

	m_currentArea = -1;
	m_selectArea = -1;
	m_numPoint =-1;
	if (pRulePara)
	{
		memcpy(&m_curRule,pRulePara,sizeof(SDK_URP_OSC_RULE_PARA_S));
	}
	else
	{
		memcpy(&m_curRule,0,sizeof(SDK_URP_OSC_RULE_PARA_S));
		return;
	}
	
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
}

void CDlgOscRuleArea::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	m_contextMenu.CreatePopupMenu();
 	m_contextMenu.AppendMenu(MF_STRING,ID_MENUCONTEXT_MENU_EDIT,_CS("DeviceManage.DevEdit"));
 	m_contextMenu.AppendMenu(MF_STRING,ID_MENUCONTEXT_MENU_DELETE,_CS("DeviceManage.DevDel"));	
	// TODO: Add your message handler code here
	URP_SDK_POINT_S ptTemp;
	int i = 0,j = 0;
	for (i = 0; i < NET_MAX_OSC_NUM;i++ )
	{
		for (j = 0 ; j < m_curRule.astSpclRgs[i].stOscRg.iPointNum; j++)
		{
			ptTemp = m_curRule.astSpclRgs[i].stOscRg.astPoint[j];
			m_curRule.astSpclRgs[i].stOscRg.astPoint[j].X = (short)(ptTemp.X*((double)m_nPicWidth/8192));
			m_curRule.astSpclRgs[i].stOscRg.astPoint[j].Y = (short)(ptTemp.Y*((double)m_nPicHeight/8192));
		}	
	}	
}
static int __stdcall RealDataCallBack(long lRealHandle, 
									  long dwDataType, unsigned char *pBuffer,
									  long lbufsize,long dwUser)
{
	CDlgOscRuleArea*pDataChnl = (CDlgOscRuleArea*)dwUser;
	H264_PLAY_InputData( pDataChnl->m_nPlaydecHandle ,pBuffer, lbufsize );
	pDataChnl->m_bCallBack = TRUE;
	
	return 1;
}

int CDlgOscRuleArea::ConnectRealPlay(HWND hWnd,int channel)
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

bool CDlgOscRuleArea::StopRealPlay()
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
	
	
	H264_DVR_Logout(m_lLoginHandle);
	m_lLoginHandle = -1;
	
// 	Invalidate();
	return true;
}

// 启动视频预览.
//..............
bool CDlgOscRuleArea::StartUpPreview(BOOL bPreview)
{
	long m_LoginID=0;
	if (bPreview)
	{
		int nFlag = 1;
	// 	int ret = H264_DVR_SetDevConfig(m_LoginID,E_SDK_VIDEO_PREVIEW, -1, (char *)&nFlag, 0 );
		//((CClientDemo5Dlg*)m_lDlg)->OnBtnLogin();
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
		
// 		H264_DVR_Login(deviceInfo.szDevIP, deviceInfo.dwPort, deviceInfo.szUserName, 
// 			deviceInfo.szPassWord, &OutDev, &nError );
// 		ConnectRealPlay(NULL,m_nChannelNum);
		//int ret =CUserDataManager::instance()->StartPreview(NULL, m_nChannelNum);
	}else
	{
		int nFlag = 0;
		// int ret = H264_DVR_SetDevConfig(m_LoginID,E_SDK_VIDEO_PREVIEW, -1, (char *)&nFlag , 0 );
		StopRealPlay();
		//int ret = CUserDataManager::instance()->StopPreview(NULL, m_nChannelNum);
	}
	return 0;
}

bool CDlgOscRuleArea::CatchPic()
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
}

BOOL CDlgOscRuleArea::GetAppPath(char *szPath)
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

void CDlgOscRuleArea::DrawRules(CDC *pDC, SDK_URP_OSC_RULE_PARA_S *pRules)
{
	int i = 0,j=0;
	int pointNum;
	CPen *pOldPen;
	for (i =0; i < NET_MAX_OSC_NUM; i++)
	{
		if (pRules->astSpclRgs[i].stOscRg.iPointNum > 0)
		{
			pointNum = pRules->astSpclRgs[i].stOscRg.iPointNum;
			if (i == m_selectArea)
			{
				pOldPen = pDC->SelectObject(&m_SelectPen);
			}
			for (j = 0; j < pointNum-1 ; j++)
			{
			 	drawline(pDC,pRules->astSpclRgs[i].stOscRg.astPoint[j],pRules->astSpclRgs[i].stOscRg.astPoint[j+1]);
			}
			drawline(pDC,pRules->astSpclRgs[i].stOscRg.astPoint[0],pRules->astSpclRgs[i].stOscRg.astPoint[pointNum-1]);
			if (i == m_selectArea)
			{
				pDC->SelectObject(&m_pen);
			}
		}	
	}
}

void CDlgOscRuleArea::drawline(CDC *pDC, URP_SDK_POINT_S ptStart, URP_SDK_POINT_S ptEnd)
{
	CPoint start(ptStart.X, ptStart.Y);
	CPoint end(ptEnd.X, ptEnd.Y);
	
	pDC->MoveTo(start);
	pDC->LineTo(end);
}

void CDlgOscRuleArea::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint pt;
	//判断是否在图片显示区域内
 	if ( CheckOutArea(point))
 	{
 		CDialog::OnLButtonDown(nFlags, point);
 		return;
 	}
	pt.x = point.x - m_nPicLeft;
	pt.y = point.y - m_nPicTop;

	//不处于画线状态,则查看是否选择某个规则
	if ( !m_bCanDraw && !m_bDrawLine)
	{
		m_selectArea = CheckSelect(pt);

		CRect rtPic;
		m_bkPic.GetWindowRect(&rtPic);
		ScreenToClient(&rtPic);
		InvalidateRect(rtPic);  

//		if (m_selectArea >= 0)
		{
//			DrawSelectArea();
			CDialog::OnLButtonDown(nFlags, point);
			return;
		}
	}
	if (m_bCanDraw && m_currentArea >= 0)
	{
		m_ptOrigin = point;
	
		//有效点数0说明刚开始画曲线
		if (m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum == 0)
		{
			m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[0].X = pt.x;
			m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[0].Y = pt.y;
			m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum = 1;
			m_numPoint = 1;
			m_bDrawLine = true;
			m_ptEnd = point;
		}
		else
		{
			m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum].X = pt.x;
			m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum].Y = pt.y;
			
			CDC *pDC = m_bkPic.GetDC();
			
			CPen *pOldpen = pDC->SelectObject(&m_pen);
			drawline(pDC, m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum - 1], m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum]);
			m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum ++;
			m_numPoint++;
			
			if ( m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum >= SDK_MAX_BOUNDARY_POINT_NUM )
			{
				drawline(pDC, m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[0], m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[SDK_MAX_BOUNDARY_POINT_NUM-1]);
				m_bCanDraw = false;
				m_bDrawLine = false;
				//保存鼠标信心，最多就8个点, 到了8个点就认为已经结束，保存
			//	OnMenucontextMenuEdit();
			}
		
			pDC->SelectObject(pOldpen);
		}	
	}
	CDialog::OnLButtonDown(nFlags, point);
}

bool CDlgOscRuleArea::CheckOutArea(CPoint point)
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


void CDlgOscRuleArea::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_bCanDraw && m_bDrawLine)
	{
		if (CheckOutArea(point))
		{
			m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum = 0;
			m_numPoint = 0;
			memset(&m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint,0,sizeof(SDK_URP_OSC_SPECL_REGIONS_S));
			CRect rtPic;
			m_bkPic.GetWindowRect(&rtPic);
			ScreenToClient(&rtPic);
			rtPic.right+=5;
			rtPic.bottom+=5;
			InvalidateRect(rtPic);   
			m_bDrawLine = false;
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

void CDlgOscRuleArea::OnMenucontextMenuEdit()
{
	m_bCanDraw = true;
	for (int i = 0; i <NET_MAX_OSC_NUM ; i++)
	{
		if (m_curRule.astSpclRgs[i].stOscRg.iPointNum == 0)
		{
			m_currentArea = i;
			memset(&m_curRule.astSpclRgs[i],0,sizeof(SDK_URP_OSC_SPECL_REGIONS_S));
			m_numPoint = 0;
			return;
		}
	}
}

void CDlgOscRuleArea::OnMenucontextMenuDelete()
{
	m_curRule.astSpclRgs[m_selectArea].stOscRg.iPointNum = 0;
	m_selectArea = -1;
	CRect rtPic;
	m_bkPic.GetWindowRect(&rtPic);
	ScreenToClient(&rtPic);
	InvalidateRect(rtPic);   
}

int CDlgOscRuleArea::CheckSelect(CPoint pt)
{
	int bFinded = -1;
	int nPointNum = -1;
	//判断是否在多边形或者矩形内
	for (int i = 0; i < NET_MAX_OSC_NUM;i++)
	{
		if (m_curRule.astSpclRgs[i].stOscRg.iPointNum == 0)
		{
			continue;
		}
		nPointNum = m_curRule.astSpclRgs[i].stOscRg.iPointNum;
		CRgn rgnA;
		CPoint *ptVertex = new CPoint[nPointNum];
		for (int j = 0; j < nPointNum; j++)
		{
			ptVertex[j].x = m_curRule.astSpclRgs[i].stOscRg.astPoint[j].X;
			ptVertex[j].y = m_curRule.astSpclRgs[i].stOscRg.astPoint[j].Y;
		}
		rgnA.CreatePolygonRgn( ptVertex, nPointNum, ALTERNATE);
		if ( rgnA.m_hObject&&rgnA.PtInRegion( pt ) )
		{
			bFinded = i;	
		}
		delete []ptVertex;
	}
	return bFinded;
}

void CDlgOscRuleArea::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_numPoint >= 0 && m_numPoint < 3)
	{
		return;
	}
	if (m_numPoint >= 3 && m_numPoint < SDK_MAX_BOUNDARY_POINT_NUM )
	{
		CDC *pDC = GetDC();
		int oldMode = pDC->SetROP2 (R2_NOT);
		pDC->SelectObject(&m_pen);
		pDC->MoveTo (m_ptOrigin);
		pDC->LineTo (m_ptOrigin);
		pDC->MoveTo (m_ptOrigin);
		pDC->LineTo (point);

		m_curRule.astSpclRgs[m_currentArea].stOscRg.iPointNum = m_numPoint;
		pDC = m_bkPic.GetDC();
		CPen *pOldpen = pDC->SelectObject(&m_pen);	
		
		drawline(pDC, m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[m_numPoint - 1], m_curRule.astSpclRgs[m_currentArea].stOscRg.astPoint[0]);
		pDC->SelectObject(pOldpen);
		m_numPoint = -1;
		m_currentArea = -1;
		m_bCanDraw = false;
		m_bDrawLine = false;
	}
	else
	{


		m_selectArea = CheckSelect(point);

		CRect rtPic;
		m_bkPic.GetWindowRect(&rtPic);
		ScreenToClient(&rtPic);
	    InvalidateRect(rtPic); 

		RefreshMenu();
		ClientToScreen(&point); 
		m_contextMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN,point.x,point.y,this);
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CDlgOscRuleArea::RefreshMenu()
{
	int numArea = 0;
	for(int i = 0; i < NET_MAX_OSC_NUM; i++)
	{
		if(m_curRule.astSpclRgs[i].stOscRg.iPointNum > 0)
		{
			numArea++;
		}
	}
	m_contextMenu.RemoveMenu(ID_MENUCONTEXT_MENU_EDIT,MF_BYCOMMAND);
	m_contextMenu.RemoveMenu(ID_MENUCONTEXT_MENU_DELETE,MF_BYCOMMAND);
	
	if(m_selectArea >= 0 && m_selectArea <= NET_MAX_OSC_NUM)
	{
		m_contextMenu.AppendMenu(MF_STRING,ID_MENUCONTEXT_MENU_DELETE,_CS("DeviceManage.DevDel"));	
	}
	if(numArea < NET_MAX_OSC_NUM)
	{
		m_contextMenu.AppendMenu(MF_STRING,ID_MENUCONTEXT_MENU_EDIT,_CS("DeviceManage.DevEdit"));
	}
}

