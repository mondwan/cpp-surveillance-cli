#include <stdio.h>
#include <memory.h>
#include   <unistd.h>
#include <iostream>
using namespace std;
#include "../Include/API/netsdk.h"




	FILE * g_pFile;
int  NetDataCallBack( long lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,long dwUser)
{	
	printf("lbufsize:%ld\n",lbufsize);
	
	BOOL bResult = TRUE;
	try
	{	
		//fwrite(pBuffer,1,lbufsize,g_pFile);
	}
	catch (...)
	{
		
	}

	// it must return TRUE if decode successfully,or the SDK will consider the decode is failed
	return bResult;

}
int  RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, long dwUser)
{
	printf("time:%04d-%02d-%02d %02d:%02d:%02d\n",pFrame->nYear,pFrame->nMonth,pFrame->nDay,pFrame->nHour,pFrame->nMinute,pFrame->nSecond);
	BOOL bResult = TRUE;
	//printf("%ld", dwUser);
	try
	{	
		//fwrite(pFrame->pPacketBuffer,1,pFrame->dwPacketSize,g_pFile);
	}
	catch (...)
	{

	}

	// it must return TRUE if decode successfully,or the SDK will consider the decode is failed
	return bResult;
}
void  TalkDataCallBack(LONG lTalkHandle, char *pDataBuf, long dwBufSize, char byAudioFlag, long dwUser)
{
	BOOL bResult = TRUE;
	try
	{
		printf("come TalkDataCallBack :%ld\n",dwBufSize);

		if(g_pFile)
		{
			//printf("come in fwrite");
			fwrite(pDataBuf,1,dwBufSize,g_pFile);
		}
		else
		{
			printf("###################################fWrite wrong!!!!!\n");
		}
		
	}
	catch (...)
	{
		
	}
	// it must return TRUE if decode successfully,or the SDK will consider the decode is failed
	return ;
}

int g_LoginID=0;
bool DevicCallBack(long lLoginID, char *pBuf,
				   unsigned long dwBufLen, long dwUser)
{
	printf("one devic is comeing!");
		//H264_DVR_ACTIVEREG_INFO *info=(H264_DVR_ACTIVEREG_INFO *)pBuf;
		//printf("das device : %s",info->deviceSarialID);
		g_LoginID=lLoginID;
}
//#define SearchDevice
//#define  DAS
//#define Tal//#define RealPlay
#define RealPlay
//#define PLAYBACK_BYNAME
//#define PLAYBACK_BYNAME_V2
//#define PlayBack_BYTIME
//#define PlayBack_BYTIME_V2
void* START_ROUTINE(LPVOID lpThreadParameter)
{
	
	H264_DVR_CLIENTINFO playstru;

	playstru.nChannel = 0;
	playstru.nStream = 0;
	playstru.nMode = 0;
	long nPlayHandle = H264_DVR_RealPlay(g_LoginID,&playstru );
	printf("nPlayHandle=%ld\n",nPlayHandle);
	sleep(1000);
	//return 1;		
}
int  main(void)
{
	g_pFile=NULL;
	H264_DVR_Init(NULL,NULL);
	printf("H264_DVR_Init\n");
#ifdef SearchDevice
	SDK_CONFIG_NET_COMMON_V2 m_Device[100];
	int nRetLength = 0;
	cout<<"start"<<endl;
	bool bRet= H264_DVR_SearchDevice((char*)m_Device,sizeof(SDK_CONFIG_NET_COMMON_V2)*100,&nRetLength,5000);
	if(bRet)
	{		
		cout<<"m_Device->HostIP"<<m_Device[1].HostName<<endl;
		cout<<"m_Device->HostIP2"<<m_Device[2].HostName<<endl;
		printf("H264_DVR_SearchDevice ok number is [%d]\n",nRetLength/sizeof(SDK_CONFIG_NET_COMMON_V2));
	}
#endif

#ifdef DAS
	cout<<"start das"<<endl;
	bool ret =H264_DVR_StartActiveRigister(9400,DevicCallBack,1);
	cout<<"end das"<<endl;
	if(ret>0)
	{
		cout<<"********sleep 2 minit************ "<<endl;
		sleep(120);
	}	
	else
	{
		printf("Call H264_DVR_StartActiveRigister**********wrong£¡");
	}
#else
	H264_DVR_DEVICEINFO OutDev;	
	memset(&OutDev,0,sizeof(OutDev));
	int nError = 0;			
	g_LoginID = H264_DVR_Login((char*)"10.10.32.71", 34567, (char*)"admin",(char*)"13579",(LPH264_DVR_DEVICEINFO)(&OutDev),&nError);	
	printf("g_LoginID=%d,nError:%d\n",g_LoginID,nError);
	
	
	//pthread_t handle;
	//pthread_create(&handle,NULL,START_ROUTINE,NULL);
	
#ifdef ADDUSER	
	USER_INFO userInfo;	
	strcpy(userInfo.Groupname,"admin");	
	strcpy(userInfo.memo,"");
	strcpy(userInfo.name,"12345");
	strcpy(userInfo.passWord,"");

	userInfo.reserved=false;
	userInfo.rigthNum=5;
	strcpy(userInfo.rights[0],"ShutDown");
	strcpy(userInfo.rights[1],"ChannelTitle");
	strcpy(userInfo.rights[2],"RecordConfig");
	strcpy(userInfo.rights[3],"Replay_01");
	strcpy(userInfo.rights[4],"Monitor_01");
	userInfo.shareable=true;
	long lRet2 = H264_DVR_SetDevConfig(g_LoginID, E_SDK_CONFIG_ADD_USER, -1, (char*)&userInfo, sizeof(userInfo), 10000);
	if(lRet2 >0)
	{
	   printf("add user ok\n");
	}else
	{
	   printf("add user err\n");
	}
#endif
	
#endif
	
	H264_DVR_FINDINFO findInfo;
	findInfo.nChannelN0=0;
	findInfo.nFileType=0;			//文件类型, 见SDK_File_Type
	
	time_t t = time(NULL);
	tm * tt= localtime(&t);
	
	findInfo.startTime.dwYear = tt->tm_year+1900;
	findInfo.startTime.dwMonth = tt->tm_mon+1;
	findInfo.startTime.dwDay = tt->tm_mday;
	findInfo.startTime.dwHour = 0;
	findInfo.startTime.dwMinute = 0;
	findInfo.startTime.dwSecond = 0;

	findInfo.endTime.dwYear = tt->tm_year+1900;
	findInfo.endTime.dwMonth = tt->tm_mon+1;
	findInfo.endTime.dwDay = tt->tm_mday;
	findInfo.endTime.dwHour = 23;
	findInfo.endTime.dwMinute = 59;
	findInfo.endTime.dwSecond = 59;
	
	H264_DVR_FILE_DATA *pData = new H264_DVR_FILE_DATA[64];
	int nFindCount = 0;
	
	long lRet= H264_DVR_FindFile(g_LoginID, &findInfo, pData, 64, &nFindCount, 3000);
	if(lRet>0&&nFindCount>0)
	{
	   	printf("search success,playback file num=%d\n", nFindCount);
#ifdef PLAYBACK_BYNAME
	 	lRet = H264_DVR_PlayBackByName(g_LoginID, &pData[0], NULL,NetDataCallBack, NULL);
		if(lRet>0)
		{
			sleep(10);
			printf("Play success\n");
		}else
		{
			printf("Play failed,lRet=%ld\n",lRet);
		}
#else

#ifdef PLAYBACK_BYNAME_V2
		lRet = H264_DVR_PlayBackByName_V2(g_LoginID, &pData[0], NULL,RealDataCallBack_V2, NULL);
		if(lRet>0)
		{
			sleep(10);
			printf("Play success\n");
		}else
		{
			printf("Play failed,lRet=%ld\n",lRet);
		}
#endif
#endif


	//»Ø·Å
					H264_DVR_FINDINFO info;
				 	memset(&info, 0, sizeof(info));
				 	info.nChannelN0=0;
				 	info.nFileType=0;
				 	info.startTime.dwYear = tt->tm_year+1900;
				 	info.startTime.dwMonth = tt->tm_mon+1;
				 	info.startTime.dwDay = tt->tm_mday;
				 	info.startTime.dwHour = 0;
				 	info.startTime.dwMinute = 0;
				 	info.startTime.dwSecond = 0;
				 
				 	info.endTime.dwYear = tt->tm_year+1900;
				 	info.endTime.dwMonth = tt->tm_mon+1;
				 	info.endTime.dwDay = tt->tm_mday;
				 	info.endTime.dwHour = 23;
				 	info.endTime.dwMinute = 59;
				 	info.endTime.dwSecond = 59;
				 	g_pFile = fopen("testPlayBack", "wb+");
					long ret=0;
				 
#ifdef PlayBack_BYTIME
				 	ret=H264_DVR_PlayBackByTime(g_LoginID,&info,NULL,NetDataCallBack,1);
					if(ret)
				 	{
				 		printf("######playBackByTime#########\n");
				 		sleep(10);	

				 	}
				 	else
				 	{
				 		printf("#############playbackWrong#####:%ld\n",ret);
				 	}
#else
#ifdef PlayBack_BYTIME_V2
					ret=H264_DVR_PlayBackByTime_V2(g_LoginID,&info,RealDataCallBack_V2,1,NULL,NULL);
					if(ret)
				 	{
				 		printf("######playBackByTime#########\n");
				 		sleep(10);	

				 	}
				 	else
				 	{
				 		printf("#############playbackWrong#####:%ld\n",ret);
				 	}
	
				 	
#endif
#endif	
	
	}	
	
 	if(g_LoginID>0)
 	{
		 		printf("**************login ok***************\n");	
				//¶Ôœ²
#ifdef Talk
 		g_pFile = fopen("TestTalk", "wb+");			
 		long lHandle = H264_DVR_StartVoiceCom_MR(g_LoginID, TalkDataCallBack, 0);
 		if ( lHandle <= 0 )
 		{
 			printf("start talk wrong");
 		}
 		else
 		{						
 			printf("start talk ok\n");			
 			sleep(6);
 			if(H264_DVR_StopVoiceCom(lHandle))
 			{
 				printf("stop talk ok\n");
 			}
 			else
 			{
 				printf("stop wrong!");
 			}			
 		}
#endif
		//ÊµÊ±ŒàÊÓ


#ifdef RealPlay
		H264_DVR_CLIENTINFO playstru;

		playstru.nChannel = 0;
		playstru.nStream = 0;
		playstru.nMode = 0;
		long m_iPlayhandle = H264_DVR_RealPlay(g_LoginID, &playstru);	
		if(m_iPlayhandle <= 0 )
		{
			printf("start RealPlay wrong!\n");
		}
		else
		{
			g_pFile = fopen("TestRealPlay.h264", "wb+");
			H264_DVR_SetRealDataCallBack_V2(m_iPlayhandle, RealDataCallBack_V2, 0);
			printf("start RealPlay ok!");
			sleep(10);
			if(H264_DVR_StopRealPlay(m_iPlayhandle))
			{
				printf("stop realPlay ok\n");
			}
			else
			{
				printf("stop realPlay Wrong\n");
			}

		}
#endif
		//ÍøÂçÅäÖÃ
#ifdef Config
 		DWORD dwRetLen = 0;
 		int nWaitTime = 10000;
 		SDK_CONFIG_NET_COMMON NetWorkCfg;
 		BOOL bReboot = FALSE;
 		BOOL bSuccess = H264_DVR_GetDevConfig(g_LoginID,E_SDK_CONFIG_SYSNET,0,
 			(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),&dwRetLen,nWaitTime);
 		if (bSuccess && dwRetLen == sizeof (SDK_CONFIG_NET_COMMON))
 		{
 			printf("TCPPort:%d\n",NetWorkCfg.SSLPort);			
 			NetWorkCfg.SSLPort=34567;
 			bSuccess = H264_DVR_SetDevConfig(g_LoginID,E_SDK_CONFIG_SYSNET,0,
 				(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),nWaitTime);
 			if (bSuccess)
 			{
 				printf("setconfig ok\n");
 			}
 			else
 			{
 				printf("setconfig wrong\n");
 			}
 
 		}
 		else
 		{
 			int len=sizeof (SDK_CONFIG_NET_COMMON);
 			printf("GetConfig Wrong:%d,RetLen:%ld  !=  %d\n",bSuccess,dwRetLen,len);
 		}
	//ÆÕÍšÅäÖÃ
 		dwRetLen = 0;
 		nWaitTime = 10000;
 		SDK_CONFIG_NORMAL NormalConfig = {0};
 		bSuccess = H264_DVR_GetDevConfig(g_LoginID, E_SDK_CONFIG_SYSNORMAL ,0, 
 			(char *)&NormalConfig ,sizeof(SDK_CONFIG_NORMAL), &dwRetLen,nWaitTime);
 		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
 		{
 			printf("############language: %d#############\n",NormalConfig.iLanguage);
 			NormalConfig.iLanguage=2;
 			BOOL bSuccess = H264_DVR_SetDevConfig(g_LoginID,E_SDK_CONFIG_SYSNORMAL,0,(char *)&NormalConfig,sizeof(SDK_CONFIG_NORMAL),nWaitTime);
 			if ( bSuccess == H264_DVR_OPT_REBOOT )
 			{
 				printf("####need reboot####\n");
 			}
 			else if(bSuccess>0)
 			{
 				printf("#####setconfig ok####\n");
 			}
 			else
 			{
 				printf("#####setconfig wrong####\n");
 			}
 		}

#endif


 	}
 	else
 	{
 		printf("**************login wrong************\n");	
 	}

#ifdef DAS
	cout<<"H264_DVR_StopActiveRigister1"<<endl;
	H264_DVR_StopActiveRigister();
	cout<<"H264_DVR_StopActiveRigister"<<endl;
#endif

	if(g_LoginID>0)
	{
		H264_DVR_Logout(g_LoginID);
		printf("Logout success!!!\n");
	}
	H264_DVR_Cleanup();
	cout<<"H264_DVR_Cleanup"<<endl;

	if(g_pFile)
	{
		fclose(g_pFile);
	}
	printf("**************OVER************\n");
	return 0;
}
