// #if !defined(AFX_DLGOSCRULEAREA_H__E14CEDA4_A2EB_46C3_B8CB_7139879441EC__INCLUDED_)
// #define AFX_DLGOSCRULEAREA_H__E14CEDA4_A2EB_46C3_B8CB_7139879441EC__INCLUDED_
// 
// #if _MSC_VER > 1000
#pragma once
// #endif // _MSC_VER > 1000
// DlgOscRuleArea.h : header file
//
#define PREVIEW_DECODER_CHANNEL 90
#define MAXNAMESIZE 64
enum RulePara
{
	ABANDUM = 0,
	STOLEN,
	NOPARKING
};

typedef struct  
{	
	char			szDevIP[MAXNAMESIZE];     				// 机器ip.，启用DDNS后表示DDNS服务的地址
	DWORD			dwPort;          						// 登陆端口号.	
	char			szUserName[MAXNAMESIZE];  				// 登陆用户名.
	char			szPassWord[MAXNAMESIZE];  				// 登陆用户密码.
	long			ID;										// 唯一标识符.
}DEVICE_INFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgOscRuleArea dialog

class CDlgOscRuleArea : public CDialog
{
// Construction
public:
	void RefreshMenu();
	int CheckSelect(CPoint pt);
	bool CheckOutArea(CPoint point);
	void drawline(CDC *pDC, URP_SDK_POINT_S ptStart, URP_SDK_POINT_S ptEnd);
	void DrawRules(CDC *pDC, SDK_URP_OSC_RULE_PARA_S *pRules);
	BOOL GetAppPath(char *szPath);
	bool CatchPic();
	int m_nPlayhandle; //播放句柄
	int m_nPlaydecHandle; //解码句柄
	long m_lDlg;
	BOOL m_bCallBack;
	bool StartUpPreview(BOOL bPreview);
	int ConnectRealPlay(HWND hWnd,int channel);
	bool StopRealPlay();
	void initDlgInfo(SDK_URP_OSC_RULE_PARA_S *pRulePara,RulePara iRulePara,int nChannelNum);
	CDlgOscRuleArea(CWnd* pParent = NULL);   // standard constructor
	~CDlgOscRuleArea();
	TCHAR m_strFileName[256];
	HINSTANCE OldResourceHanlde;
	int m_nChannelNum;
	RulePara m_rulePara;
	SDK_URP_OSC_RULE_PARA_S m_curRule;
	//int	m_nCurPerimeterIndex;
	CMenu m_contextMenu;
	int m_numPoint;	//当前多边形的点数
	int m_currentArea;//当前处理的多边形标记
	int m_selectArea;//当前选中的多边形标记
	bool m_bGet[NET_MAX_CHANNUM];			//记录每个通道是否获取过数据
	bool m_bGetType;			//获取各个通道类型
	//记录显示图片位置离对话框的距离，方便画线
	int m_nPicLeft;
	int m_nPicTop;
	CPen m_pen;
	CPen m_SelectPen;
	bool m_MouseDown;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
//	CBitmap m_bmpBack_Up;
//	bool m_bSelected;		//是否选中一个规则
	bool m_bDrawLine;		//是否处于等待画线状态
	bool m_bCanDraw;
	int m_nPicWidth;
	int m_nPicHeight;
	DEVICE_INFO deviceInfo;
	int m_lLastDevID; //上次登陆的设备ID
	int m_lLoginHandle;     //登陆句柄
// Dialog Data
	//{{AFX_DATA(CDlgOscRuleArea)
	enum { IDD = IDD_DIALOG_RULE_AREA };
	CStatic	m_bkPic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOscRuleArea)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOscRuleArea)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenucontextMenuEdit();
	afx_msg void OnMenucontextMenuDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

// #endif // !defined(AFX_DLGOSCRULEAREA_H__E14CEDA4_A2EB_46C3_B8CB_7139879441EC__INCLUDED_)
