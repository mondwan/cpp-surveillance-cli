#if !defined(AFX_CONFIGCHANNEL_H__5DA36722_EFE2_4845_8215_F44E5FB41BDB__INCLUDED_)
#define AFX_CONFIGCHANNEL_H__5DA36722_EFE2_4845_8215_F44E5FB41BDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigChannel.h : header file
#include <map>
using namespace std;
//
#define MAX_RESOLUTION_NUM 9
/////////////////////////////////////////////////////////////////////////////
// CConfigChannel dialog
typedef struct  
{
	CString strText;
	DWORD dwSize;
	DWORD dsMask;
}SResolution;

class CConfigChannel : public CDialog
{
// Construction
public:
    void InitDlgInfo(int ChannnelNum,SDK_EncodeConfigAll_SIMPLIIFY *pEncodeSimpl,
		SDK_CONFIG_NORMAL *pNormalCfg,CONFIG_EncodeAbility *pEncodeAbility,
								 SDK_CombineEncodeConfigAll *pCmbEncode,SDK_SystemFunction *pSysFunc,
								 DEV_ATTRIBUTE *pDevAttribute,SDK_CombEncodeModeAll *pCmbEncodeMode,
								 SDK_EncodeStaticParamAll *pEncodeStatic);
	CConfigChannel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigChannel)
	enum { IDD = IDD_CONFIG_CHANNEL };
	CComboBox	m_combEncodeStaticParam;
	CComboBox	m_ctlBitRate;
	CComboBox	m_ctlGop;
	CComboBox	m_ctlExpandGop;
	CComboBox	m_ctlQuality;
	CComboBox	m_ctlExpandQuality;
	CComboBox	m_ctlExpandBitControl;
	CComboBox	m_ctlBitControl;
	CComboBox	m_ChanNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigChannel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigChannel)
	afx_msg void OnButtonApply();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboResolution();
	afx_msg void OnSelchangeComboBitcontrol();
	afx_msg void OnSelchangeComboQuality();
	afx_msg void OnSelchangeComboFrame();
	afx_msg void OnSelchangeComboExpandBitcontrol();
	afx_msg void OnSelchangeComboExpandBitRate();
	afx_msg void OnSelchangeComboExpandResolution();
	afx_msg void OnSelchangeComboExpandQuality();
	afx_msg void OnSelchangeComboExpandFrame();
	afx_msg void OnCheckExpandVideo();
	afx_msg void OnCheckMainAudio();
	afx_msg void OnCheckExpandAudio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	map<int, CString> m_mapCaptureComp;
	SDK_CONFIG_ENCODE_SIMPLIIFY m_allData;
	int m_nFrame;
	int m_niQuality;
	int m_nResolution;
	void ShowStream(int resolution,int iQuality,int Frame);
	int GetMaxFrame(int nResolution, long lFreePower);
	void ChangeChannel(int CurChannel , SDK_EncodeConfigAll_SIMPLIIFY *m_EncodeConfig);
	void InitCombo();
	bool AllStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType);
	bool StructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType, DWORD dwPower, DWORD dwMask = -1, DWORD dwBitrate = -1);
    DWORD GetExpandUsed();
	DWORD GetComboBoxData(UINT nID, int nIndex = -1);
	BOOL SetComBoxCurSel(UINT nID, DWORD dwData);
	void GetMaxResolAndRate(int &nResolu, int &nRate, long lFreePower );
	void EnableMainVideo(BOOL bEnable);
	DWORD GetMainUsed();
	void EnableExpandVideo(BOOL bEnable);
	void AddCmbResolution( UINT nID, int maxSize, DWORD dwMask );
	void AddCmbFPS( UINT nID, int maxSize );
	int NearBitrate(UINT nID, DWORD dwData);
	bool StructToWin();
	void UpdateCodeFormat(int nStream, UINT nComboBoxID);
	bool NormalStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType);
	DWORD GetFreeDspPower(int nChannelNo);
	DWORD GetFreeBitratePower(int nChannelNo);
	bool CombineStructToWinData(int nChannelNum, SDK_CONFIG_ENCODE_SIMPLIIFY *pConfigEncode, int nEncodeType);
	bool AllWinDataToStruct(int nChannelNum);
	bool NomalWinDataToStruct(int nChannelNum);
	bool WinDataToStruct(SDK_MEDIA_FORMAT &dstFmt, int nEncodeType);
	DWORD GetUsedEnable(UINT nResID, UINT nFrameID, UINT nEnableID);
	void SelchangeComboResolution(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType, DWORD dwPower);
	void SelchangeComboBitcontrol(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType);
	void SelchangeComboFrame(SDK_MEDIA_FORMAT &dstFormat, int nEncodeType);
	bool WinToStruct();
	bool CombineWinDataToStruct(int nChannelNum);
public:
	int m_nAudioInNum;
	int m_nChannelNum;
	void InitResData();
	void CleanAll();
	SDK_EncodeConfigAll_SIMPLIIFY m_EncodeConfig;
	int m_nLastChannelNum;
	int m_nVideoStandard;
	int m_nLastResolutionExtra;
	CONFIG_EncodeAbility m_pEncodeAbility;
	int m_maxBitRate[SDK_CAPTURE_SIZE_NR];
	SResolution m_resolution[SDK_CAPTURE_SIZE_NR];
	SDK_CombineEncodeConfigAll m_CmbEncodeCfg;
	SDK_SystemFunction m_SysFunc;
	DEV_ATTRIBUTE m_DevAttribute;
	bool	m_bMultiStream;
	char m_cVersion[64];
	bool m_bCombineEncode;
	bool m_bCombineSet;
	SDK_CombEncodeModeAll m_CmbEncodeMode;
	SDK_EncodeStaticParamAll m_EncodeStaticParamAll;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCHANNEL_H__5DA36722_EFE2_4845_8215_F44E5FB41BDB__INCLUDED_)
