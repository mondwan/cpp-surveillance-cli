#if !defined(AFX_VIDEOWND_H__98BE2781_143A_4D3D_8443_ECDB0E1F2968__INCLUDED_)
#define AFX_VIDEOWND_H__98BE2781_143A_4D3D_8443_ECDB0E1F2968__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoWnd dialog
#define  DISPLAYREGION

class CVideoWnd : public CDialog
{
// Construction
public:
	CVideoWnd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoWnd)
	enum { IDD = IDD_VIDEO_WND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nIndex;	//index
	long m_iPlayhandle;	//play handle
	BOOL m_bRecord;	//is recording or not
public:
	long m_nPlaydecHandle;	//decode handle
	long m_lLogin; //login handle
	int m_iChannel; //play channel
	void SetWndIndex(int nIndex)
	{
		m_nIndex = nIndex;
	}
	int ConnectRealPlay(DEV_INFO *pDev, int nChannel, bool bOsd = false);

	void GetColor(long *nBright, long *nContrast, long *nSaturation, long *nHue);
	void SetColor(long nBright, long nContrast, long nSaturation, long nHue);

	long GetHandle()
	{
		return m_iPlayhandle;
	}
	BOOL SaveRecord();

	long GetLoginHandle();

	afx_msg void OnDisconnct();

	void drawOSD(LONG nPort,HDC hDc);

	long SetDevChnColor(SDK_CONFIG_VIDEOCOLOR* pVideoColor);

	static void __stdcall videoInfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser);
	CString m_strInfoFrame[100];


public:
	RECT m_oldMouseRect;//局部放大，记入区域
	CPoint m_downPoint;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOWND_H__98BE2781_143A_4D3D_8443_ECDB0E1F2968__INCLUDED_)
