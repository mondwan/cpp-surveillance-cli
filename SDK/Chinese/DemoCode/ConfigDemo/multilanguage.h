////////////////////////////////////////////////////////////////////////////////////
// MultiLanguage.h
//*******************************    instructions    *********************************//
// the progress of initialization：
// the initialization of language type list＝》 the initialization of interface scheme list ＝》 the initialization of current interface scheme

#ifndef _MULTILANGUAGE_H
#define _MULTILANGUAGE_H

#include <afxwin.h>         // MFC core and standard components
#include <map>

// 为方便使用定义了以下的宏：
//...............................................................

// set the ".ini" file name
#define _LANGUAGE_INIT(x)			CMultiLanguage::SetIniFileName(x)
// translate string or "CString"
#define _CS(x)						CMultiLanguage::ConvertString(x)              // x is string or the object of Cstring  
// translate the strings in dialog
#define _CWndCS(x)					CMultiLanguage::SetWndStaticText(x)  //set the static text in dialog(English to current language) //x is CWnd* pointer

//...............................................................


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

template<class T>
struct strless{
	inline bool operator()(const T& x, const T& y) const
	{
		return (strcmp(x ,y) < 0);
	}
};

typedef std::map<const char *, const char *, strless<const char *> > MAPSTRING;

class CMultiLanguage
{
public:
	CMultiLanguage();
	virtual ~CMultiLanguage();
	static CString ConvertString(CString strText);
	static void SetWndStaticText(CWnd * pWnd);
	static void SetIniFileName(LPCTSTR szLanguageIniFileName );
	static CString GetCurrenLanguage();
protected:
	static CString m_strInilangFilePath;
};



#endif //_MULTILANGUAGE_H