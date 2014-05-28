#include "StdAfx.h"
#if !defined(AFX_IPEDIT_H__E848D115_18C6_4BFB_8565_540371CAD45A__INCLUDED_)
#define AFX_IPEDIT_H__E848D115_18C6_4BFB_8565_540371CAD45A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_IPEDIT_H__E848D115_18C6_4BFB_8565_540371CAD45A__INCLUDED_)
#pragma once



class CIPEdit : public CDialog
{
	DECLARE_DYNAMIC(CIPEdit)

public:
	CIPEdit(CWnd* pParent = NULL); 
	virtual ~CIPEdit();

	enum { IDD = IDD_DIALOG_IPEdit };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	SDK_CONFIG_NET_COMMON m_NetComm;
	// HTTP
	int m_nHttpPort;
	// TCP
	int m_nTCPPort;
	// MAC
	CString m_strMac;
	// IP address
	CIPAddressCtrl m_IPAddrCtrl;
	// Mask
	CIPAddressCtrl m_MaskCtrl;
	// Gateway
	CIPAddressCtrl m_GateCtrl;
	afx_msg void OnBnClickedOk();
	};
