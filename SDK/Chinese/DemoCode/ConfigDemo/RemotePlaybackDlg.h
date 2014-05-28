#if !defined(AFX_REMOTEPLAYBACKDLG_H__2B855360_421C_4A39_AAF0_07BC1C10FF69__INCLUDED_)
#define AFX_REMOTEPLAYBACKDLG_H__2B855360_421C_4A39_AAF0_07BC1C10FF69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemotePlaybackDlg.h : header file
//
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CRemotePlaybackDlg dialog
typedef struct _FileInfoNode 
{
	H264_DVR_FILE_DATA fileinfo;
	DEV_INFO         Device;
	int					recSource;
}FileInfoNode;


class CRemotePlaybackDlg : public CDialog
{
// Construction
public:
	CRemotePlaybackDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRemotePlaybackDlg)
	enum { IDD = IDD_REMOTE_PLAYBACK };
	CListCtrl	m_fileList;
	CButton	m_videoWnd;
	CProgressCtrl	m_progress;
	CComboBox	m_cmbType;
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbDevice;
	CTime	m_endData;
	CTime	m_begData;
	CTime	m_begTime;
	CTime	m_endTime;
	BOOL	m_bDownloadByTime;
	BOOL	m_bDownloadByName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemotePlaybackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRemotePlaybackDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDevice();
	afx_msg void OnSearch();
	afx_msg void OnDownload();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnFast();
	afx_msg void OnSlow();
	afx_msg void OnPause();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckDownLoadByName();
	afx_msg void OnCheckDownLoadByTime();
	afx_msg void OnPageUp();
	afx_msg void OnPageDown();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBUTTONAudio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	long m_nPlaybackDecHandle;	//handle of file play,decode

private:
	void ClearResult();
	void OnDownloadByName();
	void OnDownloadByTime();
	void OnPlayByTime();
	void OnPlayByName();
	
	long m_nPlayHandle;		//handle of file play,original data
	long m_lFileHandle;		//handle of file search
	HANDLE m_hFileThread;	//handle of search thread
	//int	 m_nSearchNum;	//search number
	long m_lLoginID;		//login ID
	BOOL m_bPause;			//flag of pause
	long m_lSaveHandle;		//handle of download

	// slow step
	static int s_sSlowType;
	// fast step
	static int s_sFastType;

public:
	CString BrowseForFolder( HWND hWnd );
	vector<H264_DVR_FILE_DATA*>m_pstrFileVector;
	void ClearMapResult();
	int GetNextPageInfo(H264_DVR_FINDINFO* searchInfo);
	void SetPageBtnState();
	void AddFileListInfo(int iNum);
	int m_nTotalPage;
	int m_nCurPage;
	int m_nGetPage;
	int m_nCurRecNum;
	H264_DVR_FINDINFO m_nSearchInfo;


	map<int,H264_DVR_FINDINFO>m_mapTemp;
	int m_mapNum;
	// data stream callback function£¬you may get the data from device when playing back through network in this function
	//.....................................................
	static int __stdcall NetDataCallBack( long lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,long dwUser);
	static int __stdcall NetDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, unsigned int dwUser);

	//SDK progress control callback
	static void  __stdcall SDKDownLoadPosCallback( long lPlayHandle, long lTotalSize, long lDownLoadSize, long dwUser );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMOTEPLAYBACKDLG_H__2B855360_421C_4A39_AAF0_07BC1C10FF69__INCLUDED_)
