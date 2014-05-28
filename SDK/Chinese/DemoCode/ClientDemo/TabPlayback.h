#pragma once
#include "afxcmn.h"
#include "RemotePlaybackDlg.h"
#include "LocalPlayback.h"
#include "DlgCoverFile.h"



class CTabPlayback : public CDialog
{
	DECLARE_DYNAMIC(CTabPlayback)

public:
	CTabPlayback(CWnd* pParent = NULL);   
	virtual ~CTabPlayback();


	enum { IDD = IDD_DLG_TAB_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	virtual BOOL OnInitDialog() ;
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CRemotePlaybackDlg m_remoteplayback;
	CLocalPlayback m_localplayback;
	//CDialog* m_pTabDlg[2];
	CDialog* m_pTabDlg[3];
	int m_CurSelTab;
	Cdlgcoverfile m_testCovertFile;
};
