// RecLineShowWnd.h: interface for the CRecLineShowWnd class.
// Create by Zhengdh  20070801 
// 用于画录象存储情况 类似MS磁盘整理
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECLINESHOWWND_H__82887AFD_2546_4CEB_BB18_9125840D025E__INCLUDED_)
#define AFX_RECLINESHOWWND_H__82887AFD_2546_4CEB_BB18_9125840D025E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
typedef struct _REC_COLOR
{
	COLORREF clColor[100];

}REC_COLOR , *pREC_COLOR;
*/

#define WM_LBUTUP		(WM_USER + 1000)
#define WM_LDBUTUP		(WM_USER + 1001)


class CTimeLineShowWnd : public CWnd  
{
public:
	CTimeLineShowWnd();
	virtual ~CTimeLineShowWnd();

	//是否显示刻度
	void SetShowScale(BOOL bShow);

	//设置中间字体
	void SetMiddleText(char * pchText , COLORREF clText = RGB(0,0,0));

	//开始画色主要InsertDrawSpace函数用
	void Draw();

	void SetColour(long lColour)
	{
		m_colour = lColour;		
	}
	void SetPeriod(COLORREF *pPeriod);

	void InitColourNum(int num);
protected:

	//{{AFX_MSG(CSubWindow)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	COLORREF *m_pclRecColor;		//记录颜色内存块

	CString  m_MidText;				//纪录中间显示字体
	COLORREF m_MidTextColor;		//中间字体显示颜色 

	BOOL     m_bShowScale;//是否现实刻度

	long m_lColourNum;	//内存快数目

	COLORREF m_penColour;	// 分隔线颜色
	COLORREF m_colour;
	COLORREF m_unColour;

	DWORD m_dwTickcount;	//记录鼠标事件时间，区分单击和双击
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_RECLINESHOWWND_H__82887AFD_2546_4CEB_BB18_9125840D025E__INCLUDED_)
