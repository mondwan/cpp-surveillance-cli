#include "afxcmn.h"
#include "afxwin.h"
#include "..\\bin\\NetSdk.h"
#if !defined(AFX_DEVICEEDIT_H__8D4C3791_A353_4354_87E1_66030EF5F68D__INCLUDED_)
#define AFX_DEVICEEDIT_H__8D4C3791_A353_4354_87E1_66030EF5F68D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceEdit.h : header file
//
#include "PromptDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CDeviceEdit dialog

class CDeviceEdit : public CDialog
{
// Construction
public:
	CDeviceEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeviceEdit)
	enum { IDD = IDD_CONFIG_DLG };	
	CListCtrl	m_listDevice;
	CEdit	m_editIP;
	CEdit	m_EditUserName;
	CEdit	m_EditTotal;
	CEdit	m_EditPsw;
	CEdit	m_EditPort;
	CEdit	m_EditDevName;
	CString	m_strDevName;
	UINT	m_nPort;
	CString	m_strPsw;
	UINT	m_nChannel;
	CString	m_strUserName;
	CString	m_strIP;
	CString	m_DevSerialID;
	UINT	m_HostPort;
	CString	m_strHostIP;
	BOOL	m_bIP;
	BOOL	m_bSerialID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CDeviceEdit)
	virtual BOOL OnInitDialog();
	virtual void OnOK();	
	/*afx_msg void OnClickListDdnsDev(NMHDR* pNMHDR, LRESULT* pResult);*/
	afx_msg void OnDestroy();
	afx_msg void OnCHECKSerialID();
	afx_msg void OnCheckIp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_nType;		//0:add device;  1:modify device
	DEV_INFO m_devInfo;
	BOOL WriteXML();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	static UINT SearchDevice(LPVOID parm);
	afx_msg void OnBnClickedBtnSearch();
	SDK_CONFIG_NET_COMMON m_Device[100];
	int m_nDevNum;
	HANDLE m_hSearch;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	long m_lUpgradeHandle;
	afx_msg void OnBnClickedBtnSetting();
	void DelArpEntry(DWORD dwAddr);
	afx_msg void OnNMDblclkListUpgrade(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListUpgrade(NMHDR *pNMHDR, LRESULT *pResult);
	CPromptDlg m_PromptDlg;
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaint();
private:
	std::map<int , DEV_INFO> m_mapDev;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEEDIT_H__8D4C3791_A353_4354_87E1_66030EF5F68D__INCLUDED_)
