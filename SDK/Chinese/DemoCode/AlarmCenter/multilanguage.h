////////////////////////////////////////////////////////////////////////////////////
// MultiLanguage.h
//*******************************    补充说明    *********************************//
// 多语言界面环境的初始化过程如下：
// 语言种类链表的初始化 ＝》 界面方案链表的初始化 ＝》 选择当前的界面方案

#ifndef _MULTILANGUAGE_H
#define _MULTILANGUAGE_H

#include <afxwin.h>         // MFC core and standard components
#include <map>

// 为方便使用定义了以下的宏：
//...............................................................

// 设置配置文件全名.
#define _LANGUAGE_INIT(x)			CMultiLanguage::SetIniFileName(x)
// 翻译字符串或CString.
#define _CS(x)						CMultiLanguage::ConvertString(x)              // x 为字符串和CString对象  
// 翻译对话框里的字符.
#define _CWndCS(x)					CMultiLanguage::SetWndStaticText(x)  //设置对话框中的静态文本(英文-->当前语言) // x 为 CWnd*指针

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