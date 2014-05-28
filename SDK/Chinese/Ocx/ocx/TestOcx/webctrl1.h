#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被改写。

/////////////////////////////////////////////////////////////////////////////
// CWebctrl1 包装类

class CWebctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWebctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xFD3BEB0C, 0xAB43, 0x4253, { 0x91, 0x46, 0xC3, 0x71, 0xD4, 0x8F, 0xBE, 0xD } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 属性
public:


// 操作
public:

// _DWeb

// Functions
//

	CString Translate(LPCTSTR str)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, str);
		return result;
	}
	long Login(LPCTSTR lpServerIp, long lPort, LPCTSTR lpUserName, LPCTSTR lpPassword)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lpServerIp, lPort, lpUserName, lpPassword);
		return result;
	}
	BOOL Logout()
	{
		BOOL result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL StopRealPlay()
	{
		BOOL result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void ShowDeviceConfig()
	{
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ShowClientConfig()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ShowLog()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Fullscreen(BOOL bFull)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bFull);
	}
	BOOL ChangeShowWndNum(long nShowNum, BOOL bChangeOcx, long nSplit, long nPreview)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nShowNum, bChangeOcx, nSplit, nPreview);
		return result;
	}
	BOOL StartRealPlay(long lChannel, long lProtocolType, long lStreamType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannel, lProtocolType, lStreamType);
		return result;
	}
	CString GetChannelName()
	{
		CString result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL StopPlayReal(long nChannel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel);
		return result;
	}
	BOOL StartRecord(LPCTSTR lpSaveFile)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lpSaveFile);
		return result;
	}
	BOOL StopRecord()
	{
		BOOL result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL BMPCapturePicture(LPCTSTR lpSaveFile)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lpSaveFile);
		return result;
	}
	BOOL OpenSound(long lSoundMode)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lSoundMode);
		return result;
	}
	BOOL CloseSound(long lSoundMode)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lSoundMode);
		return result;
	}
	BOOL StartTalk()
	{
		BOOL result;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL StopTalk()
	{
		BOOL result;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL PTZCtrlStart(long lChannle, long lCtrlType, long lSpeed)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannle, lCtrlType, lSpeed);
		return result;
	}
	BOOL PTZCtrlStop(long lChannel, long lCtrlType, long lSpeed)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannel, lCtrlType, lSpeed);
		return result;
	}
	BOOL PTZCtrlSetPreset(long lChannel, long lPresetNumb, BOOL bStart)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannel, lPresetNumb, bStart);
		return result;
	}
	BOOL PTZCtrlGotoPreset(long lChannel, long lPresetNumb)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannel, lPresetNumb);
		return result;
	}
	CString GetColor()
	{
		CString result;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL SetColor(long nRegionNum, long lBrightValue, long lContrastValue, long lSaturationValue, long lHueValue)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nRegionNum, lBrightValue, lContrastValue, lSaturationValue, lHueValue);
		return result;
	}
	BOOL PTZCtrlTour(long lChannel, long lTourNumber, BOOL bStart)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannel, lTourNumber, bStart);
		return result;
	}
	BOOL PTZEditTure(long lTourNumber)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lTourNumber);
		return result;
	}
	BOOL StopRealPlayAll()
	{
		BOOL result;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL PlayAll()
	{
		BOOL result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL stopRecordAll()
	{
		BOOL result;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL startRecordAll(LPCTSTR lpSaveFile)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lpSaveFile);
		return result;
	}
	BOOL StartRecordByChannel(long lChannel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannel);
		return result;
	}
	BOOL StopRecordBychannel(long lChannel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lChannel);
		return result;
	}
	BOOL RebootServer()
	{
		BOOL result;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL ShowPlayBack()
	{
		BOOL result;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void OnBntEntermenu()
	{
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL SetOcxBGColor(long BG, long bordBG, long bord)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, BG, bordBG, bord);
		return result;
	}
	BOOL SetSpecialParam(long param)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, param);
		return result;
	}
	long GetDeviceState(long nType, long param)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nType, param);
		return result;
	}
	long SetSpecialParamEx(long nType, long param1, long param2, long param3)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nType, param1, param2, param3);
		return result;
	}
	long SetSpecialParamEx2(long nType, LPCTSTR param1, long param2, LPCTSTR param3)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nType, param1, param2, param3);
		return result;
	}
	BOOL BMPChannelCapturePicture(long nChannel, LPCTSTR lpSaveFile)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel, lpSaveFile);
		return result;
	}
	BOOL OpenChannelSound(long nChannel, long lSoundMode)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel, lSoundMode);
		return result;
	}
	BOOL CloseChannelSound(long nChannel, long lSoundMode)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel, lSoundMode);
		return result;
	}
	BOOL StartPlayAll()
	{
		BOOL result;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL StopChannelRecord(long nChannel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel);
		return result;
	}
	BOOL StartChannelRecord(long nChannel, LPCTSTR lpSaveFile, long nType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel, lpSaveFile, nType);
		return result;
	}
	BOOL StartChannelRealPlay(long nChannel, long lProtocolType, long lStreamType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel, lProtocolType, lStreamType);
		return result;
	}
	BOOL StopChannelRealPlay(long nChannel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel);
		return result;
	}
	BOOL StartRecordAllChannel(LPCTSTR lpSaveFile, long nType)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lpSaveFile, nType);
		return result;
	}
	BOOL StopRecordAllChannel()
	{
		BOOL result;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long GetCurChannel()
	{
		long result;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL StartRemoteRecord(long nChannel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel);
		return result;
	}
	BOOL StopRemoteRecord(long nChannel)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nChannel);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

CString Getip()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}
void Setip(CString propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}
long GetpassPort()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}
void SetpassPort(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}
CString GetLanguage()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}
void SetLanguage(CString propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}
unsigned long GetWndBGColor()
{
	unsigned long result;
	GetProperty(0x4, VT_UI4, (void*)&result);
	return result;
}
void SetWndBGColor(unsigned long propVal)
{
	SetProperty(0x4, VT_UI4, propVal);
}
unsigned long GetBorderBGColor()
{
	unsigned long result;
	GetProperty(0x5, VT_UI4, (void*)&result);
	return result;
}
void SetBorderBGColor(unsigned long propVal)
{
	SetProperty(0x5, VT_UI4, propVal);
}
unsigned long GetBordColor()
{
	unsigned long result;
	GetProperty(0x6, VT_UI4, (void*)&result);
	return result;
}
void SetBordColor(unsigned long propVal)
{
	SetProperty(0x6, VT_UI4, propVal);
}


};
