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
//¡°English string¡±convert to ¡°current language string¡±
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

	TCHAR szFull[_MAX_PATH];
	::GetModuleFileName(NULL, szFull, sizeof(szFull)/sizeof(TCHAR));
	strConfig += _T("Config.ini");
	GetPrivateProfileString(_T("themes"), _T("Solution"), _T(""), cVal, 
		sizeof(cVal) / sizeof(TCHAR), strConfig);
	strRet = cVal;
	if(strRet.GetLength()==0)
	{
		//if there is no equal string in ¡°.ini¡±document£¬set the default language£¨English£©
		strRet = _T("English");
	}
	m_strInilangFilePath = szLanguageIniFileName;
	m_strInilangFilePath += _T("Language\\");
	m_strInilangFilePath += strRet + _T(".lang");
}

//////////////////////////////////////////////////////////////
//set the static text in dialog(English to current language)
void CMultiLanguage::SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;

	//set the window text of main windows	
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}

	//set the window text of child windows
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit" || strClassName == "CIPAddressCtrl" || strClassName == "CNetSurveillance")
		{
			//next child window
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		//////////////////////////////////////////////////////////////////////////	
		//set the current text of child windows
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);
		//next child window
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}

CString CMultiLanguage::GetCurrenLanguage()
{
	return m_strInilangFilePath;
}
