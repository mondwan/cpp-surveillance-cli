// ClientDemoDlg.h : header file
//

#if !defined(AFX_CLIENTDEMODLG_H__BB7C5B4C_3BEA_495B_8B21_BEE1B73251B2__INCLUDED_)
#define AFX_CLIENTDEMODLG_H__BB7C5B4C_3BEA_495B_8B21_BEE1B73251B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDemoDlg dialog

#include "DeviceEditDlg.h"
#include "ColorDlg.h"
#include "PTZDlg.h"
#include "VideoWnd.h"
#include "DialogKeyBoard.h"
#include "NetAlarmDlg.h"
#include "CruiseEdit.h"

class CClientDemoDlg : public CDialog
{
// Construction
public:
	CClientDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDemoDlg)
	enum { IDD = IDD_CLIENTDEMO_DIALOG };
	CButton	m_checkOsd;
	CComboBox	m_cmbWnd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBtnDevice();
	afx_msg void OnBtnPtz();
	afx_msg void OnBtnColor();
	afx_msg void OnBtnPlayback();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnCapture();
	afx_msg void OnSelchangeCombowndnum();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnDevConfig();
	afx_msg void OnBtnDevKeyboard();
	afx_msg void OnBtnNetAlarm();
	afx_msg void OnCheckOsd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	int m_nTotalWnd;
	int m_nCurIndex;
	CDeviceEditDlg m_devDLg;
	CColorDlg	   m_colorDLg;
	CPTZDlg		   m_ptzDLg;
	CDialogKeyBoard	   m_kbDLg;
	CVideoWnd	   m_videoWnd[MAXWNDNUM];
	CNetAlarmDlg   m_NetAlarmDlg;
	DEV_INFO m_devInfo;
	CCruiseEdit Dlg;
private:
	//initialize the SDK
	BOOL InitSDK();
	BOOL ExitSDk();
	void ArrayWindow(WORD iNumber);
	void DrawActivePage(BOOL bActive);
	void SetColor( int nIndex );	
public:
	bool DealwithAlarm(long lDevcID,  char* pBuf , DWORD dwLen);
	BOOL SetDevChnColor(DWORD nBright, DWORD nContrast, DWORD nSaturation, DWORD nHue);
	void SetActiveWnd(int nIndex);
	int Connect(DEV_INFO *pDev, int nChannel, int nWndIndex = -1);
	void SetColor(DWORD nBright, DWORD nContrast, DWORD nSaturation, DWORD nHue);
	void PtzControl(DWORD dwBtn, bool dwStop);
	void KeyBoardMsg(DWORD dwValue, DWORD dwState);
	void NetAlarmMsg(DWORD dwValue, DWORD dwState);
	Devc_Map *GetDeviceMap();
	void SetDevInfo(DEV_INFO *pDev);
	void ReConnect(LONG lLoginID, char *pchDVRIP,  LONG nDVRPort);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMODLG_H__BB7C5B4C_3BEA_495B_8B21_BEE1B73251B2__INCLUDED_)
