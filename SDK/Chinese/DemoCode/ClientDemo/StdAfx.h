// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6883B86E_642F_44B1_B5DE_70E38923E30A__INCLUDED_)
#define AFX_STDAFX_H__6883B86E_642F_44B1_B5DE_70E38923E30A__INCLUDED_

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


#pragma warning(disable:  4083 4514 4786)

#include "define.h"

#include "multilanguage.h"

#pragma warning(disable: 4786)
#include <map>
#include <vector>

#include "..\\bin\\NetSdk.h"
#pragma comment (lib,"..\\bin\\NetSdk") 


#include "..\\bin\\H264Play.h"
#pragma comment (lib,"..\\bin\\H264Play") 

//device information
typedef struct _DEV_INFO 
{
	int	nListNum;		   //position in the list

	long lLoginID;			//login handle
	long lID;				//device ID
	char szDevName[60];		//device name
	char szIpaddress[15];		//device IP
	char szUserName[8];		//user name
	char szPsw[8];			//pass word
	int nPort;				//port number
	int nTotalChannel;		//total channel

	SDK_CONFIG_NET_COMMON NetComm;                  // net config
	H264_DVR_DEVICEINFO  NetDeviceInfo;
	
	BOOL bSerialID;//be SerialNumber login
	char szSerIP[DDNS_MAX_DDNS_IPSIZE];//server ip
	int nSerPort;           //server port
	char szSerialInfo[DDNS_MAX_SERIALINFO_SIZE];  //SerialNumber
	int devctype;
}DEV_INFO;

#define PLAYBACK_MAX_FILE_NUM           64

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6883B86E_642F_44B1_B5DE_70E38923E30A__INCLUDED_)
