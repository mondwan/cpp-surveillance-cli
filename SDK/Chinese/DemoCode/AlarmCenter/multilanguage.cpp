////////////////////////////////////////////////////////////////////////////////////
// MultiLanguage.cpp
#include "stdafx.h"
#include "MultiLanguage.h"

CString CMultiLanguage::m_strInilangFilePath;//ini language file full path(inlude filename)

CMultiLanguage::CMultiLanguage()
{

}

CMultiLanguage::~CMultiLanguage()
{
}

//////////////////////////////////////////////////////////////
//“英文字符串”转换为“当前语言类型的字符串”
CString CMultiLanguage::ConvertString(CString strText)
{
	TCHAR val[300];
	CString strRet;
	
	if (m_strInilangFilePath.GetLength())
	{
		memset(val,0,sizeof(val));
		GetPrivateProfileString(_T("String"),strText,_T(""), val,sizeof(val)/sizeof(TCHAR),m_strInilangFilePath);
		strRet=val;
		if(strRet.GetLength()> 0)
		{
			return strRet;	
		}
	}
	
	const TCHAR *p = _tcsstr(strText, _T("."));
	if (p)
	{
		strRet = p + 1;
	}
	else
	{
		strRet = strText;
	}
	return strRet;
}

// set ini file about transfering multi-language text
void CMultiLanguage::SetIniFileName(LPCTSTR szLanguageIniFileName)
{	
	TCHAR cVal[64] = {0};
	CString strRet;
	CString strConfig = szLanguageIniFileName;

	strConfig += _T("Config.ini");
	GetPrivateProfileString(_T("themes"), _T("Solution"), _T(""), cVal, 
		sizeof(cVal) / sizeof(TCHAR), strConfig);
	strRet = cVal;
	if(strRet.GetLength()==0)
	{
		//如果ini文件中不存在对应的字符串，设置为默认值（英文）
		strRet = _T("English");
	}
	m_strInilangFilePath = szLanguageIniFileName;
	m_strInilangFilePath += _T("Language\\");
	m_strInilangFilePath += strRet + _T(".lang");
}

//////////////////////////////////////////////////////////////
//设置对话框中的静态文本(英文-->当前语言)   
void CMultiLanguage::SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;

	//设置主窗口的标题
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}

	//设置子窗口的标题
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit" || strClassName == "CIPAddressCtrl" || strClassName == "CNetSurveillance")
		{
			//下一个子窗口
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		//////////////////////////////////////////////////////////////////////////	
		//设置子窗口的当前语言文本
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);
		//下一个子窗口
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}

CString CMultiLanguage::GetCurrenLanguage()
{
	return m_strInilangFilePath;
}
