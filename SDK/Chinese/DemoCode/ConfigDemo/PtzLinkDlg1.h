#pragma once
#include "afxwin.h"

#include "Resource.h"
// CPtzLinkDlg 对话框

class CPtzLinkDlg : public CDialog
{
	DECLARE_DYNAMIC(CPtzLinkDlg)

public:
	CPtzLinkDlg(SDK_PtzLinkConfig *pPtzLink = NULL, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPtzLinkDlg();

// 对话框数据
	enum { IDD = IDD_DLG_PTZ_LINK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cmbChannel1;
	CComboBox m_cmbChannel10;
	CComboBox m_cmbChannel11;
	CComboBox m_cmbChannel12;
	CComboBox m_cmbChannel13;
	CComboBox m_cmbChannel14;
	CComboBox m_cmbChannel15;
	CComboBox m_cmbChannel16;
	CComboBox m_cmbChannel2;
	CComboBox m_cmbChannel4;
	CComboBox m_cmbChannel3;
	CComboBox m_cmbChannel5;
	CComboBox m_cmbChannel6;
	CComboBox m_cmbChannel7;
	CComboBox m_cmbChannel8;
	CComboBox m_cmbChannel9;
	CComboBox m_cmbChannel17;
	CComboBox m_cmbChannel18;
	CComboBox m_cmbChannel19;
	CComboBox m_cmbChannel20;
	CComboBox m_cmbChannel21;
	CComboBox m_cmbChannel22;
	CComboBox m_cmbChannel23;
	CComboBox m_cmbChannel24;
	CComboBox m_cmbChannel25;
	CComboBox m_cmbChannel26;
	CComboBox m_cmbChannel27;
	CComboBox m_cmbChannel28;
	CComboBox m_cmbChannel29;
	CComboBox m_cmbChannel30;
	CComboBox m_cmbChannel31;
	CComboBox m_cmbChannel32;
	CEdit m_edit1;
	int m_nValue1;
	CEdit m_edit10;
	CEdit m_edit11;
	CEdit m_edit12;
	CEdit m_edit13;
	CEdit m_edit14;
	CEdit m_edit15;
	CEdit m_edit16;
	CEdit m_edit9;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	CEdit m_edit7;
	CEdit m_edit8;
	CEdit m_edit17;
	CEdit m_edit18;
	CEdit m_edit19;
	CEdit m_edit20;
	CEdit m_edit21;
	CEdit m_edit22;
	CEdit m_edit23;
	CEdit m_edit24;
	CEdit m_edit25;
	CEdit m_edit26;
	CEdit m_edit27;
	CEdit m_edit28;
	CEdit m_edit29;
	CEdit m_edit30;
	CEdit m_edit31;
	CEdit m_edit32;
	int m_nValue10;
	int m_nValue11;
	int m_nValue12;
	int m_nValue13;
	int m_nValue14;
	int m_nValue15;
	int m_nValue16;
	int m_nValue9;
	int m_nValue2;
	int m_nValue3;
	int m_nValue4;
	int m_nValue5;
	int m_nValue6;
	int m_nValue7;
	int m_nValue8;
	int m_nValue17;
	int m_nValue18;
	int m_nValue19;
	int m_nValue20;
	int m_nValue21;
	int m_nValue22;
	int m_nValue23;
	int m_nValue24;
	int m_nValue25;
	int m_nValue26;
	int m_nValue27;
	int m_nValue28;
	int m_nValue29;
	int m_nValue30;
	int m_nValue31;
	int m_nValue32;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit18();
	afx_msg void OnEnChangeEdit22();
	afx_msg void OnEnChangeEdit24();
	afx_msg void OnEnChangeEdit28();
	afx_msg void OnEnChangeEdit30();
	afx_msg void OnEnChangeEdit33();
	afx_msg void OnEnChangeEdit34();
	afx_msg void OnEnChangeEdit35();
	afx_msg void OnEnChangeEdit36();
	afx_msg void OnEnChangeEdit37();
	afx_msg void OnEnChangeEdit38();
	afx_msg void OnEnChangeEdit39();
	afx_msg void OnEnChangeEdit40();
	afx_msg void OnEnChangeEdit41();
	afx_msg void OnEnChangeEdit42();
	afx_msg void OnEnChangeEdit43();

	SDK_PtzLinkConfig m_PtzLink[NET_MAX_CHANNUM];		// 云台联动项 

	HINSTANCE OldResourceHanlde;
public:
	afx_msg void OnBnClickedOk();
	const SDK_PtzLinkConfig *GetPtzConf();
};
