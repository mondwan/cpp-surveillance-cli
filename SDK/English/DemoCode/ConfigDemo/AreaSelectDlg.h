
#if !defined(AFX_AREASELECTDLG_H__5C0379AA_5DDE_4795_872D_897BA01B170B__INCLUDED_)
#define AFX_AREASELECTDLG_H__5C0379AA_5DDE_4795_872D_897BA01B170B__INCLUDED_

#pragma once

#include "Resource.h"
#include "motiondetect.h"

#define  DEV_MOTION_ROW NET_MD_REGION_ROW
#define  DEV_MOTION_COL sizeof(unsigned int)

#define  ID_MOTION_DETECT (WM_USER + 1000)

class CAreaSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CAreaSelectDlg)
		
public:
	CAreaSelectDlg( short nRow = NET_MD_REGION_ROW, short nCol = sizeof(unsigned int) * 8, unsigned int *mRegion = NULL, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAreaSelectDlg();
	
	enum { IDD = IDD_CONFIG_ALARM_MOTION_AREA };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	
	DECLARE_MESSAGE_MAP()
public:
	void SetChannelInfo(int nChannel);
	

	void SetRowCol(unsigned int *mRegion, short nRow, short nCol);
	
	const unsigned int * GetSetData();
	
	void ShowInformation();
	
	CMotionDetect m_wndMotionDetect;
	
	HINSTANCE OldResourceHanlde;
public:
	virtual BOOL DestroyWindow();
	
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	bool StartPre(bool bPre);
	bool CatchPic();
	long m_lRealHandle;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOk();
	afx_msg void OnCancel();
	
private:	
	int m_nCurChannel;
	BOOL m_bFullScreen;
	short m_nRow;
	short m_nCol;
	unsigned int m_mRegion[NET_MD_REGION_ROW];
public:
	afx_msg void OnPaint();
	long m_pMainDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREASELECTDLG_H__5C0379AA_5DDE_4795_872D_897BA01B170B__INCLUDED_)
