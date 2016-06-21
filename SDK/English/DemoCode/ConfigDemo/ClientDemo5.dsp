# Microsoft Developer Studio Project File - Name="ClientDemo5" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ClientDemo5 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo5.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo5.mak" CFG="ClientDemo5 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientDemo5 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo5 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientDemo5 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 WSOCK32.LIB /nologo /stack:0x200000,0x200000 /subsystem:windows /debug /machine:I386 /out:"../Bin/ConfigDemo.exe"

!ELSEIF  "$(CFG)" == "ClientDemo5 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 WSOCK32.LIB /nologo /stack:0x200000,0x200000 /subsystem:windows /debug /machine:I386 /out:"../bin/ConfigDemo.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ClientDemo5 - Win32 Release"
# Name "ClientDemo5 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlarmException.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmInputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmOuput.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmShelter.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmVideoAnalyse.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmVLostDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChannelNameSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ChannelNameSet2.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDigitalChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigNetServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigPTZ.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigVehicle.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverAreaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitalChannelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChannelMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChannelStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiskPartation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgForbidDirection1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOscRuleArea.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRuleArea.cpp
# End Source File
# Begin Source File

SOURCE=.\LogInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\motiondetect.cpp
# End Source File
# Begin Source File

SOURCE=.\multilanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\NetPre.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServer3G.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerALARM.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerARSP.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerDAS.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerDDNS.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerDNS.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerEmail.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerFTP.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerGodEye.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerIPFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerMobile.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerMultiMedia.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerNAT.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerNetInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerNTP.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerPMS.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerPPPOE.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerRtsp.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerSHISOU.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerSHORTMSG.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerUPNP.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerVVEye.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerWIFI.cpp
# End Source File
# Begin Source File

SOURCE=.\NetServerXINGWANG.cpp
# End Source File
# Begin Source File

SOURCE=.\NewCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PeriodTimeSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PtzLinkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteChannelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Security.cpp
# End Source File
# Begin Source File

SOURCE=.\SnapStorageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StateSort.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysInfoVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\SysSettingCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\SysSettingUserManager.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeLapseSet.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeLineShowWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TitleSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolManagerHardDisk.cpp
# End Source File
# Begin Source File

SOURCE=.\UserAddDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserAddGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserDeleteGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserModifyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserModifyPswDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VehicleData.cpp
# End Source File
# Begin Source File

SOURCE=.\VehicleState.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoAnalyseSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoAVDRuleSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoOSCRuleSetDlg.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ClientDemo5.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo5.rc2
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlarmException.h
# End Source File
# Begin Source File

SOURCE=.\AlarmInputDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmMotion.h
# End Source File
# Begin Source File

SOURCE=.\AlarmOuput.h
# End Source File
# Begin Source File

SOURCE=.\AlarmShelter.h
# End Source File
# Begin Source File

SOURCE=.\AlarmVideoAnalyse.h
# End Source File
# Begin Source File

SOURCE=.\AlarmVLostDlg.h
# End Source File
# Begin Source File

SOURCE=.\AreaSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChannelNameSet.h
# End Source File
# Begin Source File

SOURCE=.\ChannelNameSet2.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.h
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDigitalChannel.h
# End Source File
# Begin Source File

SOURCE=.\ConfigNetServer.h
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.h
# End Source File
# Begin Source File

SOURCE=.\ConfigOutput.h
# End Source File
# Begin Source File

SOURCE=.\ConfigPTZ.h
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.h
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.h
# End Source File
# Begin Source File

SOURCE=.\ConfigVehicle.h
# End Source File
# Begin Source File

SOURCE=.\CoverAreaDlg.h
# End Source File
# Begin Source File

SOURCE=.\CoverSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\DigitalChannelDlg.h
# End Source File
# Begin Source File

SOURCE=.\DlgChannelMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgChannelStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiskPartation.h
# End Source File
# Begin Source File

SOURCE=.\DlgForbidDirection1.h
# End Source File
# Begin Source File

SOURCE=.\DlgOscRuleArea.h
# End Source File
# Begin Source File

SOURCE=.\DlgRuleArea.h
# End Source File
# Begin Source File

SOURCE=.\LogInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\motiondetect.h
# End Source File
# Begin Source File

SOURCE=.\multilanguage.h
# End Source File
# Begin Source File

SOURCE=.\NetPre.h
# End Source File
# Begin Source File

SOURCE=..\bin\netsdk.h
# End Source File
# Begin Source File

SOURCE=.\NetServer3G.h
# End Source File
# Begin Source File

SOURCE=.\NetServerALARM.h
# End Source File
# Begin Source File

SOURCE=.\NetServerARSP.h
# End Source File
# Begin Source File

SOURCE=.\NetServerDAS.h
# End Source File
# Begin Source File

SOURCE=.\NetServerDDNS.h
# End Source File
# Begin Source File

SOURCE=.\NetServerDNS.h
# End Source File
# Begin Source File

SOURCE=.\NetServerEmail.h
# End Source File
# Begin Source File

SOURCE=.\NetServerFTP.h
# End Source File
# Begin Source File

SOURCE=.\NetServerGodEye.h
# End Source File
# Begin Source File

SOURCE=.\NetServerIPFilter.h
# End Source File
# Begin Source File

SOURCE=.\NetServerMobile.h
# End Source File
# Begin Source File

SOURCE=.\NetServerMultiMedia.h
# End Source File
# Begin Source File

SOURCE=.\NetServerNAT.h
# End Source File
# Begin Source File

SOURCE=.\NetServerNetInfo.h
# End Source File
# Begin Source File

SOURCE=.\NetServerNTP.h
# End Source File
# Begin Source File

SOURCE=.\NetServerPMS.h
# End Source File
# Begin Source File

SOURCE=.\NetServerPPPOE.h
# End Source File
# Begin Source File

SOURCE=.\NetServerRtsp.h
# End Source File
# Begin Source File

SOURCE=.\NetServerSHISOU.h
# End Source File
# Begin Source File

SOURCE=.\NetServerSHORTMSG.h
# End Source File
# Begin Source File

SOURCE=.\NetServerUPNP.h
# End Source File
# Begin Source File

SOURCE=.\NetServerVVEye.h
# End Source File
# Begin Source File

SOURCE=.\NetServerWIFI.h
# End Source File
# Begin Source File

SOURCE=.\NetServerXINGWANG.h
# End Source File
# Begin Source File

SOURCE=.\NewCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PeriodTimeSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\PtzLinkDlg.h
# End Source File
# Begin Source File

SOURCE=.\RemoteChannelDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Security.h
# End Source File
# Begin Source File

SOURCE=.\SnapStorageDlg.h
# End Source File
# Begin Source File

SOURCE=.\StateSort.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysInfoVersion.h
# End Source File
# Begin Source File

SOURCE=.\SysSettingCamera.h
# End Source File
# Begin Source File

SOURCE=.\SysSettingUserManager.h
# End Source File
# Begin Source File

SOURCE=.\TimeLapseSet.h
# End Source File
# Begin Source File

SOURCE=.\TimeLineShowWnd.h
# End Source File
# Begin Source File

SOURCE=.\TitleSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\ToolManagerHardDisk.h
# End Source File
# Begin Source File

SOURCE=.\UserAddDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserAddGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserDeleteGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserModifyDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserModifyPswDlg.h
# End Source File
# Begin Source File

SOURCE=.\VehicleData.h
# End Source File
# Begin Source File

SOURCE=.\VehicleState.h
# End Source File
# Begin Source File

SOURCE=.\VideoAnalyseSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\VideoAVDRuleSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\VideoOSCRuleSetDlg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ClientDemo5 : {5C256924-0A6B-4DE8-AD0C-85671AED5BF0}
# 	1:26:IDD_DLG_ALARM_VIDEOANALYSE:144
# 	2:16:Resource Include:resource.h
# 	2:21:AlarmVideoAnalyse.cpp:AlarmVideoAnalyse.cpp
# 	2:26:IDD_DLG_ALARM_VIDEOANALYSE:IDD_DLG_ALARM_VIDEOANALYSE
# 	2:10:ENUM: enum:enum
# 	2:19:AlarmVideoAnalyse.h:AlarmVideoAnalyse.h
# 	2:25:CLASS: CAlarmVideoAnalyse:CAlarmVideoAnalyse
# 	2:19:Application Include:clientdemo5.h
# End Section
# Section ClientDemo5 : {B26EC03A-B1BB-4CEB-B4A7-BB21B2716567}
# 	1:20:IDD_DIALOG_RULE_AREA:161
# 	2:16:Resource Include:resource.h
# 	2:18:DlgOscRuleArea.cpp:DlgOscRuleArea.cpp
# 	2:10:ENUM: enum:enum
# 	2:14:ENUM: RulePara:RulePara
# 	2:16:DlgOscRuleArea.h:DlgOscRuleArea.h
# 	2:22:CLASS: CDlgOscRuleArea:CDlgOscRuleArea
# 	2:19:Application Include:clientdemo5.h
# 	2:20:IDD_DIALOG_RULE_AREA:IDD_DIALOG_RULE_AREA
# End Section
# Section ClientDemo5 : {54EDC177-4394-498B-A897-608B008AA3FB}
# 	1:19:IDD_DLG_USER_MODIFY:106
# 	2:16:Resource Include:resource.h
# 	2:19:IDD_DLG_USER_MODIFY:IDD_DLG_USER_MODIFY
# 	2:17:UserModifyDlg.cpp:UserModifyDlg.cpp
# 	2:10:ENUM: enum:enum
# 	2:21:CLASS: CUserModifyDlg:CUserModifyDlg
# 	2:19:Application Include:ClientDemo5.h
# 	2:15:UserModifyDlg.h:UserModifyDlg.h
# End Section
# Section ClientDemo5 : {CC936556-650F-49C7-9DB1-96AD79BB0494}
# 	1:23:IDD_DLG_SYSINFO_VERSION:189
# 	2:16:SysInfoVersion.h:SysInfoVersion.h
# 	2:16:Resource Include:resource.h
# 	2:22:CLASS: CSysInfoVersion:CSysInfoVersion
# 	2:18:SysInfoVersion.cpp:SysInfoVersion.cpp
# 	2:10:ENUM: enum:enum
# 	2:23:IDD_DLG_SYSINFO_VERSION:IDD_DLG_SYSINFO_VERSION
# 	2:19:Application Include:clientdemo5.h
# End Section
# Section ClientDemo5 : {6B95E4BF-9C14-44E4-A5BA-7352F824B6F3}
# 	1:22:IDD_DLG_USER_ADD_GROUP:105
# 	2:16:Resource Include:resource.h
# 	2:19:UserAddGroupDlg.cpp:UserAddGroupDlg.cpp
# 	2:23:CLASS: CUserAddGroupDlg:CUserAddGroupDlg
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:ClientDemo5.h
# 	2:17:UserAddGroupDlg.h:UserAddGroupDlg.h
# 	2:22:IDD_DLG_USER_ADD_GROUP:IDD_DLG_USER_ADD_GROUP
# End Section
# Section ClientDemo5 : {8DEF9465-353A-4547-AB84-C04E04F25FC8}
# 	1:23:IDD_DIG_FORBIDDIRECTION:188
# 	2:16:Resource Include:resource.h
# 	2:22:DlgForbidDirection.cpp:DlgForbidDirection1.cpp
# 	2:20:DlgForbidDirection.h:DlgForbidDirection1.h
# 	2:23:IDD_DIG_FORBIDDIRECTION:IDD_DIG_FORBIDDIRECTION
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo5.h
# 	2:26:CLASS: CDlgForbidDirection:CDlgForbidDirection
# End Section
# Section ClientDemo5 : {38DB9B3A-94DF-4906-BDB6-FAC1D00E0563}
# 	1:25:IDD_DLG_USER_DELETE_GROUP:108
# 	2:16:Resource Include:resource.h
# 	2:25:IDD_DLG_USER_DELETE_GROUP:IDD_DLG_USER_DELETE_GROUP
# 	2:20:UserDeleteGroupDlg.h:UserDeleteGroupDlg.h
# 	2:10:ENUM: enum:enum
# 	2:26:CLASS: CUserDeleteGroupDlg:CUserDeleteGroupDlg
# 	2:19:Application Include:ClientDemo5.h
# 	2:22:UserDeleteGroupDlg.cpp:UserDeleteGroupDlg.cpp
# End Section
# Section ClientDemo5 : {3B85C491-015B-497E-A1F9-2A57941FE4BD}
# 	1:25:IDD_DLG_ALARM_AVDRULE_SET:149
# 	2:26:CLASS: CVideoAVDRuleSetDlg:CVideoAVDRuleSetDlg
# 	2:16:Resource Include:resource.h
# 	2:22:VideoAVDRuleSetDlg.cpp:VideoAVDRuleSetDlg.cpp
# 	2:20:VideoAVDRuleSetDlg.h:VideoAVDRuleSetDlg.h
# 	2:10:ENUM: enum:enum
# 	2:25:IDD_DLG_ALARM_AVDRULE_SET:IDD_DLG_ALARM_AVDRULE_SET
# 	2:19:Application Include:clientdemo5.h
# End Section
# Section ClientDemo5 : {871A3F33-5C9C-4EE9-92C8-B7E0F70F0D80}
# 	1:25:IDD_DLG_ALARM_OSCRULE_SET:147
# 	2:16:Resource Include:resource.h
# 	2:26:CLASS: CVideoOSCRuleSetDlg:CVideoOSCRuleSetDlg
# 	2:22:VideoOSCRuleSetDlg.cpp:VideoOSCRuleSetDlg.cpp
# 	2:10:ENUM: enum:enum
# 	2:25:IDD_DLG_ALARM_OSCRULE_SET:IDD_DLG_ALARM_OSCRULE_SET
# 	2:20:VideoOSCRuleSetDlg.h:VideoOSCRuleSetDlg.h
# 	2:19:Application Include:clientdemo5.h
# End Section
# Section ClientDemo5 : {76EB3650-95BA-49A5-BC87-69258250AD0E}
# 	1:16:IDD_DLG_USER_ADD:104
# 	2:16:Resource Include:resource.h
# 	2:16:IDD_DLG_USER_ADD:IDD_DLG_USER_ADD
# 	2:10:ENUM: enum:enum
# 	2:12:UserAddDlg.h:UserAddDlg.h
# 	2:18:CLASS: CUserAddDlg:CUserAddDlg
# 	2:19:Application Include:ClientDemo5.h
# 	2:14:UserAddDlg.cpp:UserAddDlg.cpp
# End Section
# Section ClientDemo5 : {E839F261-A7FE-469C-84CB-3A1A14D25EBA}
# 	1:25:IDD_DLG_ALARM_PEARULE_SET:146
# 	2:16:Resource Include:resource.h
# 	2:20:VideoAnalyseSetDlg.h:VideoAnalyseSetDlg.h
# 	2:10:ENUM: enum:enum
# 	2:25:IDD_DLG_ALARM_PEARULE_SET:IDD_DLG_ALARM_PEARULE_SET
# 	2:22:VideoAnalyseSetDlg.cpp:VideoAnalyseSetDlg.cpp
# 	2:26:CLASS: CVideoAnalyseSetDlg:CVideoAnalyseSetDlg
# 	2:19:Application Include:clientdemo5.h
# End Section
# Section ClientDemo5 : {D42F0E86-4D70-45D2-8E11-DC819D8F1426}
# 	2:23:CLASS: CUserDataManager:CUserDataManager
# 	2:19:UserDataManager.cpp:UserDataManager.cpp
# 	2:17:UserDataManager.h:UserDataManager.h
# 	2:19:Application Include:ClientDemo5.h
# End Section
# Section ClientDemo5 : {188991D8-6D6D-447B-96F2-737C2283E441}
# 	1:18:IDD_DLG_MODIFY_PSW:107
# 	2:16:Resource Include:resource.h
# 	2:20:UserModifyPswDlg.cpp:UserModifyPswDlg.cpp
# 	2:10:ENUM: enum:enum
# 	2:18:IDD_DLG_MODIFY_PSW:IDD_DLG_MODIFY_PSW
# 	2:18:UserModifyPswDlg.h:UserModifyPswDlg.h
# 	2:19:Application Include:ClientDemo5.h
# 	2:24:CLASS: CUserModifyPswDlg:CUserModifyPswDlg
# End Section
# Section ClientDemo5 : {DAFDC097-C434-4CBF-85B4-3F23A312417E}
# 	1:20:IDD_DLG_USER_MANAGER:103
# 	2:16:Resource Include:resource.h
# 	2:20:IDD_DLG_USER_MANAGER:IDD_DLG_USER_MANAGER
# 	2:23:SysSettingUserManager.h:SysSettingUserManager.h
# 	2:10:ENUM: enum:enum
# 	2:29:CLASS: CSysSettingUserManager:CSysSettingUserManager
# 	2:19:Application Include:ClientDemo5.h
# 	2:25:SysSettingUserManager.cpp:SysSettingUserManager.cpp
# End Section
