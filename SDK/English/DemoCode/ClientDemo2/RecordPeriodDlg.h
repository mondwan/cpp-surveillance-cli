#pragma once
#include "staticex.h"
#include "MyButton.h"
#include "TimeLineShowWnd.h"
#include "resource.h"
//#define ID_TIME_DRAW		(WM_USER + 1000)
#define ID_BTN_THUM			(WM_USER + 2000)
#define ID_CAPTION_STATIC	(WM_USER + 2001)
#define ID_STATIC_HOUR		(WM_USER + 3000)
#define ID_STATIC_MINUTE      (WM_USER + 3100)

#define DLG_WIDTH				708
#define STATIC_HEIGTH			12
#define STATIC_WIDTH			50

//数据结构
struct DEC
{
	long pthis;
	long decHandle;
	long playHandle;
	bool bOver;
};
// CRecordPeriodDlg 对话框

class CRecordPeriodDlg : public CDialog
{
//	DECLARE_DYNAMIC(CRecordPeriodDlg)

public:
	CRecordPeriodDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecordPeriodDlg();
	void SetSliderPos(short nHour, short nMin, short nSec = 0) ;
	void UpdateTimeSect(const unsigned char cRecordBitMap[720]);
//SDK进度条回调
//数据流回调.在此函数中得到设备网络回放时的压缩数据
//...................................................
// 对话框数据

	//{{AFX_DATA(CRecordPeriodDlg)
	enum { IDD = IDD_DLG_RECORDPERIOD };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordPeriodDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecordPeriodDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	afx_msg LRESULT OnSliderMouseMove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSliderLButtonDown(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSliderLButtonUp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTimeLineLButtonUp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTimeLineDblClk(WPARAM wParam, LPARAM lParam);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()



private:
	COLORREF m_recTime[24][60];	//录像时间段
	CStatic m_StaticHour;
	CStatic m_StaticMin;
	CStatic m_StaticH[25];
	CStatic m_StaticM[13];
	int m_nTimeSect[24][60]; //表示一天

	bool m_bShow;

	bool m_bDown;			//滑动块是否被按下

	CRect m_rectHourSlider;	//1小时滑动条位置
	CRect m_rectDaySlider;	//24小时滑动条位置
	CSize m_sizeThumb;		//滑动块大小

	//当前滑动块小时、分钟、秒的位置
	int m_nCurHour;			
	int m_nCurMin;
	int m_nCurSec;

	CBrush m_brush;
	//录像刻度线
	CTimeLineShowWnd m_TimeHourDraw;
	CTimeLineShowWnd m_TimeDayDraw;	

	CMyButton m_DayThum;	//24小时滑块
	CMyButton m_HourThum;	//1小时滑块

	CStaticEx m_timeCaption;	//时间提示框
	CFont m_font;
public:
	CBrush m_Brush;
	CRgn m_Rgn;
	CBitmap m_bmpBack_Up;  //前景位图
	DWORD m_lLoginID;
	H264_DVR_TIME m_tmStart;
	H264_DVR_TIME m_tmEnd;
	int m_nRecType; //录像类型
	int m_nChannelNO;
	map<DWORD,WORD> m_nPort;
	int m_nCount;

	DEC *m_dec[64];
#ifdef MULTISTREAM_RECORD	
	long m_pPlayDlg;
#endif

	short GetSelectTime(short * nStartHour, short * nStartMin, short * nEndHour, short * nEndMin) ;

		
};
