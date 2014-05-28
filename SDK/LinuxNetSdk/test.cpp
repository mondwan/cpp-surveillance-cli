#include <stdio.h>
#include <memory.h>
#include   <unistd.h>
#include <iostream>
using namespace std;
#include "../../include/API/netsdk.h"




	FILE * g_pFile;
int  NetDataCallBack( long lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,long dwUser)
{	
	BOOL bResult = TRUE;
	try
	{	
		fwrite(pBuffer,1,lbufsize,g_pFile);
	}
	catch (...)
	{
		
	}

	// it must return TRUE if decode successfully,or the SDK will consider the decode is failed
	return bResult;

}
int  RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, unsigned int dwUser)
{
	BOOL bResult = TRUE;
	try
	{	
		fwrite(pFrame->pPacketBuffer,1,pFrame->dwPacketSize,g_pFile);
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
		//printf("come TalkDataCallBack :%ld\n",dwBufSize);

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

//#define  DAS
//#define Talk
//#define RealPlay
//#define PlayBack
//#define Config


int  main(void)
{
	g_pFile=NULL;
	H264_DVR_Init(NULL,NULL);

SDK_CONFIG_NET_COMMON m_Device[100];
int nRetLength = 0;
cout<<"start"<<endl;
bool bRet=H264_DVR_SearchDevice((char*)m_Device,sizeof(SDK_CONFIG_NET_COMMON)*100,&nRetLength,5000);
if(bRet)
{		
	cout<<"m_Device->HostIP"<<m_Device[1].HostName<<endl;
	cout<<"m_Device->HostIP2"<<m_Device[2].HostName<<endl;
	printf("H264_DVR_SearchDevice ok number is [%d]\n",nRetLength);
}


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
		printf("Call H264_DVR_StartActiveRigister**********wrong！");
	}
#else
	H264_DVR_DEVICEINFO OutDev;	
	memset(&OutDev,0,sizeof(OutDev));
	int nError = 0;			
	g_LoginID = H264_DVR_Login((char*)"10.2.4.55", 34567,(char*)"admin",(char*)"",(LPH264_DVR_DEVICEINFO)(&OutDev),&nError);		
#endif

 	if(g_LoginID>0)
 	{
		 		printf("**************login ok***************\n");	
				//对讲
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
		//实时监视


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
		//网络配置
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
	//普通配置
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

#ifdef PlayBack
	//回放
			H264_DVR_FINDINFO info;
				 	memset(&info, 0, sizeof(info));
				 	info.nChannelN0=0;
				 	info.nFileType=0;
				 	info.startTime.dwYear=2012;
				 	info.startTime.dwMonth=6;
				 	info.startTime.dwDay=3;
				 	info.startTime.dwHour=0;
				 	info.startTime.dwMinute=0;
				 	info.startTime.dwSecond=0;
				 
				 	info.endTime.dwYear=2012;
				 	info.endTime.dwMonth=6;
				 	info.endTime.dwDay=6;
				 	info.endTime.dwHour=23;
				 	info.endTime.dwMinute=0;
				 	info.endTime.dwSecond=0;
				 	g_pFile = fopen("testPlayBack", "wb+");
				 
				 	long ret=H264_DVR_PlayBackByTime(g_LoginID,&info,NULL,NetDataCallBack,1);	
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
	H264_DVR_Cleanup();
	cout<<"H264_DVR_Cleanup"<<endl;
	if(g_pFile)
	{
		fclose(g_pFile);
	}
	printf("**************OVER************\n");
	return 0;
}
