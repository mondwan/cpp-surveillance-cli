#ifndef _DEFINE_H
#define _DEFINE_H
#include "StdAfx.h"

#define		MAXWNDNUM		16		//the maximum number of play window

#define WM_MYCOMMAND		(WM_USER+1)
#define ID_ADD_DEVICE		(WM_USER+2)
#define ID_DELETE_DEVICE	(WM_USER+3)
#define ID_MODIFY_DEVICE	(WM_USER+4)
#define ID_CONNNECT			(WM_USER+5)
#define ID_DISCONNECT		(WM_USER+6)
#define ID_START_TALK		(WM_USER+7)
#define ID_DEVICE_CAPTURE	(WM_USER+8)
#define ID_DEVICE_OPENSOUND	(WM_USER+9)
#define ID_DEVICE_CLOSESOUND (WM_USER+10)

struct ModuleFileInfomations
{
	CString		strFullPath;
	CString		strPath;
	CString		strDrive;
	CString		strDir;
	CString		strName;
	CString		strExt;
};
#endif