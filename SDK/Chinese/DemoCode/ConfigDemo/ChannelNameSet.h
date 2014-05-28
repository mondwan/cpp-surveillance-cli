#if !defined(AFX_CHANNELNAMESET_H__4C677011_768D_47F3_B40D_115099DFD76C__INCLUDED_)
#define AFX_CHANNELNAMESET_H__4C677011_768D_47F3_B40D_115099DFD76C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelNameSet.h : header file
//
#define IDC_STATIC_CNS WM_USER+4000
#define IDC_EDIT_CNS WM_USER+4600
/////////////////////////////////////////////////////////////////////////////
// CChannelNameSet dialog

class CChannelNameSet : public CDialog
{
// Construction
public:
	CChannelNameSet(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CChannelNameSet)
	enum { IDD = IDD_CHANNELNAME };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelNameSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelNameSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	const SDK_ChannelNameConfigAll* GetChannelName();
	int m_nChannelTotal;
	SDK_ChannelNameConfigAll m_ChannelName;
	HINSTANCE OldResourceHanlde;
	CEdit *m_edit[NET_MAX_CHANNUM];
	CStatic *m_static[NET_MAX_CHANNUM];
	byte *m_pBuf;		//记录点阵信息
	int m_nWidth;		//点阵的宽度和高度
	int m_nHeight;
	
	//释放内存
	void freeData();
	//获取一个字符的点阵信息
	int GetBuffer(int ch, int nFont);
	void CleanAll();
	void InitDlgInfo(SDK_ChannelNameConfigAll *pChannelName,int nbyChanNum );
	BOOL InitWindow();
	void ShowInfo();
	void SaveChannelNS();

	void GetData();


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELNAMESET_H__4C677011_768D_47F3_B40D_115099DFD76C__INCLUDED_)
