#if !defined(AFX_CHANNELNAMESET2_H__CF78F48B_3073_4F9B_807E_4F9F039CE3CF__INCLUDED_)
#define AFX_CHANNELNAMESET2_H__CF78F48B_3073_4F9B_807E_4F9F039CE3CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelNameSet2.h : header file
//
#define IDC_STATIC_CNS2 WM_USER+5000
#define IDC_EDIT_CNS2 WM_USER+5600

/////////////////////////////////////////////////////////////////////////////
// CChannelNameSet2 dialog

class CChannelNameSet2 : public CDialog
{
// Construction
public:
	SDK_ChannelNameConfigAll m_ChannelName;
	CEdit *m_edit[NET_MAX_CHANNUM];
	CStatic *m_static[NET_MAX_CHANNUM];
	int m_nChannelTotal;
	byte *m_pBuf;		//记录点阵信息
	int m_nWidth;		//点阵的宽度和高度
	int m_nHeight;
	BOOL InitWindow();
	CChannelNameSet2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChannelNameSet2)
	enum { IDD = IDD_CHANNELNAME2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelNameSet2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelNameSet2)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReadall();
	afx_msg void OnButtonApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void LoadWnd();
	void freeData();
	int GetBuffer(int ch, int nFont);
	void GetData();
	void SaveChannelNS();
	void CleanAll();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELNAMESET2_H__CF78F48B_3073_4F9B_807E_4F9F039CE3CF__INCLUDED_)
