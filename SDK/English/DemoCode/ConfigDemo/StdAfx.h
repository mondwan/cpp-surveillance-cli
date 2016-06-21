// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1AB56EE8_B58E_4EDA_B4FE_C579222C9EE9__INCLUDED_)
#define AFX_STDAFX_H__1AB56EE8_B58E_4EDA_B4FE_C579222C9EE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#pragma warning(disable: 4786)
#include "define.h"

#include "multilanguage.h"

#pragma warning(disable:  4083 4514 4786 4800 )

#include "..\\bin\\NetSdk.h"
#pragma comment (lib,"..\\bin\\NetSdk") 
#include "..\\bin\\H264Play.h"
#pragma  comment (lib,"..\\bin\\H264Play")
typedef struct _DEV_ATTRIBUTE  
{
	H264_DVR_DEVICEINFO deviveInfo;
	SDK_CONFIG_NORMAL   NormalConfig;
}DEV_ATTRIBUTE;

typedef struct
{
	SDK_MOTIONCONFIG_ALL MotionCfgAll;
	SDK_BLINDDETECTCONFIG_ALL DectectCfgAll;
	SDK_VIDEOLOSSCONFIG_ALL VideoLossCfgAll;
	SDK_ALARM_INPUTCONFIG_ALL AlarmInCfgAll;
	SDK_AlarmOutConfigAll  AlarmOutCfgAll;
	SDK_NETALARMCONFIG_ALL AlarmRmCfgAll;
	

}ALARMCONFIGALL;

typedef struct  
{
	SDK_ChannelNameConfigAll ChanNameCfgAll;
	SDK_GUISetConfig GUISetCfg;
	SDK_VideoWidgetConfigAll   VideoWdtCfgAll;
    SDK_BlindDetectFunction BlindDetFunc[NET_MAX_CHANNUM];
}OUTPUTCONFIGALL;

enum LanguageTypes
{
		ENGLISH,		//英语
		CHINESE_S,		//简体中文
		CHINESE_T,		//繁体中文
		ITALIAN,		//意大利语
		SPANISH,		//西班牙语
		JAPANESE,		//日语
		RUSSIAN,		//俄语
		FRENCH,			//法语
		GERMAN,			//德语
		PORTUGAL,		//葡萄牙文
		TURKEY,			//土耳其文
		POLAND,			//波兰文
		ROMANIAN,       //罗马尼亚
		HUNGARIAN,      //匈牙利语
		FINNISH,		//芬兰语
		ESTONIAN,	    //爱沙尼亚语
		KOREAN,		    //韩语
		FARSI,          //波斯语 
		DANSK,			//丹麦语
		THAI,			//泰国语
		GREEK,			//希腊语
		VIETNAMESE,		//越南语
		UKRAINIAN,      //乌克兰语
		BRAZILIAN,      //巴西语
		HEBREW,         //希伯来语
		INDONESIAN,     //印尼语
		ARABIC,         //阿拉伯语
		SWEDISH,        //瑞典语
		CZECH,          //捷克语
		BULGARIAN,      //保加利亚
		SLOVAKIA,		//斯洛伐克语
		DUTCH,			//荷兰语
		LANG_NR
};

struct ConfigPair
{
	const char* name;
	int value;
};


static ConfigPair s_language[]= 
{
	{"English", ENGLISH},
	{"SimpChinese", CHINESE_S},
	{"TradChinese", CHINESE_T},
	{"Italian", ITALIAN},
	{"Spanish", SPANISH},
	{"Japanese", JAPANESE},
	{"Russian", RUSSIAN},
	{"French", FRENCH},
	{"German", GERMAN},
	{"Portugal",PORTUGAL},
	{"Turkey",TURKEY},
	{"Poland",POLAND},
	{"Romanian",ROMANIAN},
	{"Hungarian",HUNGARIAN},
	{"Finnish",FINNISH},
	{"Estonian",ESTONIAN},
	{"Korean",KOREAN},
	{"Farsi",FARSI},
	{"Dansk",DANSK},
	{"Thai", THAI},
	{"Greek", GREEK},
	{"Vietnamese", VIETNAMESE},
	{"Ukrainian", UKRAINIAN},
	{"Brazilian", BRAZILIAN},
	{"Hebrew", HEBREW},
	{"Indonesian", INDONESIAN},
	{"Arabic", ARABIC},
	{"Swedish", SWEDISH},
	{"Czech", CZECH},
	{"Bulgarian", BULGARIAN},
	{"Slovakia", SLOVAKIA},
	{"Dutch", DUTCH},
	{NULL,}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1AB56EE8_B58E_4EDA_B4FE_C579222C9EE9__INCLUDED_)
