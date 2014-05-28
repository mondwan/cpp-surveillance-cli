#if !defined(AFX_TOOLMANAGERHARDDISK_H__B2D96CE1_F9A1_462C_89C6_B75B63ABA962__INCLUDED_)
#define AFX_TOOLMANAGERHARDDISK_H__B2D96CE1_F9A1_462C_89C6_B75B63ABA962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolManagerHardDisk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolManagerHardDisk dialog

class CToolManagerHardDisk : public CDialog
{
// Construction
public:
	void OnExecute(SDK_StorageDeviceControl *pDiskCtl);
	afx_msg void OnBnClickedBtnRw();
	afx_msg void OnBnClickedBtnRd();
	afx_msg void OnBnClickedBtnRedu();
	afx_msg void OnBnClickedBtnFormat();
	afx_msg void OnBnClickedBtnRecover();
	afx_msg void OnBnClickedBtnPartation();
    afx_msg void OnBnClickedBtnSnap();
	afx_msg void OnLvnItemchangedListTypeCapa(NMHDR *pNMHDR, LRESULT *pResult);
	
	void OnUpdate();
	void EnableItems(BOOL bEnable);
	void InitDlgInfo(SDK_SystemFunction* pSysFunc,H264_DVR_DEVICEINFO*  pDeviceInfo);
	CToolManagerHardDisk(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CToolManagerHardDisk)
	enum { IDD = IDD_DLG_TOOL_HARDDISK };
	CListCtrl	m_listDisk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolManagerHardDisk)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolManagerHardDisk)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	SDK_StorageDeviceControl m_DiskCtl;
	SDK_StorageDeviceInformationAll m_diskinfo;			//”≤≈Ã–≈œ¢:
	SDK_SystemFunction m_systemFunction;
	int m_nPhyNo; //ŒÔ¿Ì¥≈≈Ã∫≈
	int m_nPartNo; //∑÷«¯∫≈
	int m_nLogicNo;  //¬ﬂº≠¥≈≈Ã∫≈
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLMANAGERHARDDISK_H__B2D96CE1_F9A1_462C_89C6_B75B63ABA962__INCLUDED_)
