#if !defined(AFX_MOTIONDETECT_H__34412519_F296_4BC6_82E3_4F5732630F7F__INCLUDED_)
#define AFX_MOTIONDETECT_H__34412519_F296_4BC6_82E3_4F5732630F7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotionDetect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotionDetect window

//////////////////////////////////
// Delete By OLinS

//#define GRIDWIDTH             14

#define SELECTCOLOR        RGB(143,197,254)
//#define UNSELECTCOLOR      RGB(68,130,190)
#define UNSELECTCOLOR      RGB(100,100,255)
#define BKCOLOR            RGB(255,255,255)
#define TEXTCOLOR          RGB(255,0,0)
#define RGNWIDTH           16 
#define RGNHEIGHT          12 
#define REC_NON_REALTIME 6	
BOOL MyModifyStyle(HWND hWnd, int nStyleOffset,DWORD dwRemove, DWORD dwAdd, UINT nFlags);
class CMotionDetect : public CWnd
{
// Construction
public:
	CMotionDetect();

// Attributes
public:

// Operations
public:
	COLORREF m_clfUnselect;
	WORD  m_ayRgnMask[12] ;		
    DWORD m_ayRgnMask_mp4[18];
	BOOL  m_ayRgn[36][36];		
	// Add by OLinS
	// 网格大小设置
	CPoint m_ptGridSize;	
	int m_nRgnColNum;			
	int m_nRgnRowNum;		


	CPoint HitTest(CPoint point);
	void DrawGrid(int nRow,int nCol,BOOL bSel,CDC *pDC);
	///////////////////////////////////////////
	// Added by OLinS
	// 全屏窗口
	void FullScreen(BOOL bFull);

	BOOL GetGridValue(long nRow, long nCol);

	void SetWindowRGB(short nRed, short nGreen, short nBlue);

	BOOL SetGridRowCol(short nRow, short nCol) ;

	void SetGridValue(long nRow, long nCol, BOOL bValue);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionDetect)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
private:
	///////////////////////////////////////////////////
 
	WINDOWPLACEMENT _temppl;		//window's placement
	CWnd *			_tempparent;	//window's parent

	BOOL m_bFullScreen;
	CWnd * m_pParentWnd;

	COLORREF m_clfSelect;

	COLORREF m_clfBack;
	COLORREF m_clfText;
	CPoint m_LButtonDownPos;
	BOOL m_bLBtnDownSel;		
	
	BOOL m_bMsDown;				

	void CalcGridSize();
	
public:
	
	virtual ~CMotionDetect();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// Generated message map functions
protected:
	//{{AFX_MSG(CMotionDetect)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONDETECT_H__34412519_F296_4BC6_82E3_4F5732630F7F__INCLUDED_)
