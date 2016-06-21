
#ifndef __DECODE_H264PLAY_H__
#define __DECODE_H264PLAY_H__
#include <time.h>

#define H264_PLAY_API extern "C" __declspec(dllexport)

#define CALLMETHOD __stdcall
#define CALLBACK __stdcall

#define  FUNC_MAX_PORT 500              //最大播放通道数

#define TALK_PORT	499
#define TALK_PCM_PORT 500

//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100

//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 

//缓冲类型
#define BUF_VIDEO_SRC 1    //视频源缓冲        
#define BUF_AUDIO_SRC 2    //音频源缓冲
#define BUF_VIDEO_RENDER 3  //解码后视频数据缓冲
#define BUF_AUDIO_RENDER 4  //解码后音频数据缓冲

//错误类型
#define	H264_PLAY_NOERROR               0           //没有错误；
#define H264_PLAY_PARA_OVER             1           //输入参数非法；
#define H264_PLAY_ORDER_ERROR           2           //调用顺序不对；
#define H264_PLAY_TIMER_ERROR           3           //多媒体时钟设置失败；
#define H264_PLAY_DEC_VIDEO_ERROR       4	          //视频解码失败；
#define H264_PLAY_DEC_AUDIO_ERROR       5	          //音频解码失败；
#define H264_PLAY_ALLOC_MEMORY_ERROR    6		       	//分配内存失败；
#define H264_PLAY_OPEN_FILE_ERROR       7			   		//文件操作失败；
#define H264_PLAY_CREATE_OBJ_ERROR      8	          //创建线程事件等失败；
#define H264_PLAY_CREATE_DDRAW_ERROR		9		       	//创建directDraw失败；
#define H264_PLAY_CREATE_OFFSCREEN_ERROR	10		    //创建后端缓存失败；
#define H264_PLAY_BUF_OVER              11	        //缓冲区满，输入流失败；
#define H264_PLAY_CREATE_SOUND_ERROR    12		      //创建音频设备失败；
#define H264_PLAY_SET_VOLUME_ERROR      13	        //设置音量失败；
#define H264_PLAY_SUPPORT_FILE_ONLY     14		      //只能在播放文件时才能使用此接口；
#define H264_PLAY_SUPPORT_STREAM_ONLY   15		      //只能在播放流时才能使用此接口；
#define H264_PLAY_SYS_NOT_SUPPORT       16		      //系统不支持，解码器只能工作在Pentium 3以上；
#define H264_PLAY_FILEHEADER_UNKNOWN    17		      //没有文件头；
#define H264_PLAY_VERSION_INCORRECT     18	        //解码器和编码器版本不对应；
#define H264_PLAY_INIT_DECODER_ERROR    19		      //初始化解码器失败；
#define H264_PLAY_CHECK_FILE_ERROR      20		      //文件太短或码流无法识别；
#define H264_PLAY_INIT_TIMER_ERROR      21		      //初始化多媒体时钟失败；
#define H264_PLAY_BLT_ERROR             22		      //位拷贝失败；
#define H264_PLAY_UPDATE_ERROR          23			   	//显示overlay失败；


//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL  1   
#define DISPLAY_QUARTER 2	

//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 6

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100

#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//系统支持的功能，用于按位表示系统功能
#define SUPPORT_DDRAW		1			// 支持DIRECTDRAW；如果不支持，则播放器不能工作。
#define SUPPORT_BLT         2			// 显卡支持BLT操作；如果不支持，则播放器不能工作
#define SUPPORT_BLTFOURCC   4			// 显卡BLT支持颜色转换；
#define SUPPORT_BLTSHRINKX  8			// 显卡BLT支持X轴缩小；
#define SUPPORT_BLTSHRINKY  16		// 显卡BLT支持Y轴缩小；
#define SUPPORT_BLTSTRETCHX 32		// 显卡BLT支持X轴放大；
#define SUPPORT_BLTSTRETCHY 64		// 显卡BLT支持Y轴放大；
#define SUPPORT_SSE         128		// CPU支持SSE指令,Intel Pentium3以上支持SSE指令；
#define SUPPORT_MMX			256		// CPU支持MMX指令集。

typedef enum _MEDIA_FILE_TYPE
{
	MEDIA_FILE_NONE = 0,
	MEDIA_FILE_H264 = 1,
	MEDIA_FILE_AVI = 2,
	MEDIA_FILE_RMVB = 3,
	MEDIA_FILE_MPG4 = 4,
	MEDIA_FILE_NUM
}MEDIA_FILE_TYPE;
typedef enum _PICTURE_FILE_TYPE
{
	PICTURE_FILE_BMP = 0,
	PICTURE_FILE_JPG = 1
		
}PICTURE_FILE_TYPE;

//Frame position
typedef struct{
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
	long nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	long nErrorLostFrameNum;
	long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

// Frame Info
typedef struct{
	long nWidth;		// 画面宽，单位像素。如果是音频数据则为0；
	long nHeight;		// 画面高。如果是音频数据则为0；
	long nStamp;		// 时标信息，单位毫秒。
	long nType;			// 数据类型，T_AUDIO16，T_RGB32， T_YV12，详见宏定义说明。
	long nFrameRate;	// 编码时产生的图像帧率。
}FRAME_INFO;

typedef struct 
{
	char *pDataBuf;
	long nSize;
	long nFrameNum;
	BOOL bIsAudio;
	long nReserved;
}FRAME_TYPE;

/// 码流类型
enum ENCODE_TYPE
{
	StreamTypeEmpty = 0,
	StreamTypeH264 = 2,
	StreamTypeJpeg = 3,
	StreamTypeGeneral = 4,
	StreamTypePCM8 = 7,
	StreamTypeStd = 8
};

/// 图像帧类型
enum VIDEO_FRAME_TYPE
{
	FrameTypeUnknown = 0,
	FrameTypeVideo = 1,
	FrameTypeAudio = 2,
	FrameTypeData = 3,
};

/// 图像帧子类型
enum VIDEO_FRAME_SUB_TYPE
{
	FrameSubTypeIFrame = 0,
	FrameSubTypePFrame = 1,
	FrameSubTypeBFrame = 2,
	FrameSubTypeSFrame = 3,
	FrameSubTypeDataText = 5,
	FrameSubTypeDataIntl = 6,
};

typedef struct 
{
	unsigned char *pHeader;				///< 帧数据缓冲起始地址
	unsigned char *pContent;
	unsigned long nLength;
	unsigned long nFrameLength;

	unsigned int nType;                ///< 见VIDEO_FRAME_TYPE
	unsigned int nSubType;             ///< 见VIDEO_FRAME_SUB_TYPE

	unsigned int nEncodeType;          ///< 见ENCODE_TYPE

	unsigned long nYear;				///< 帧时间戳
	unsigned long nMonth;
	unsigned long nDay;
	unsigned long nHour;
	unsigned long nMinute;
	unsigned long nSecond;
	unsigned long nTimeStamp;	

	unsigned int  nFrameRate;			///< 视频图像帧率
	int nWidth;							///< 视频图像大小，宽度和高度
	int nHeight;
	unsigned long nRequence;

	unsigned int nChannels;
	unsigned int nBitsPerSample;		///< 音频采样位深
	unsigned int nSamplesPerSecond;		///< 音频采样率

	unsigned long nParam1;		// 扩展用
	unsigned long nParam2;		// 扩展用
} VIDEO_FRAME_INFO;


//字体类型，目前只支持这些
typedef enum 
{
	OSD_TXT_FONT_ARIAL = 1,
	OSD_TXT_FONT_SERIF,
	OSD_TXT_FONT_SANS,
	
	OSD_TXT_FONT_SIMSUN = 101,  // 中文字体，宋体
	OSD_TXT_FONT_SIMHEI
} DEFAULT_OSD_TXT_FONT;

typedef struct
{
	int pos_x;			//相对位置(百分比)
	int pos_y;
	COLORREF color;		//字体颜色
	char text[256];
	DEFAULT_OSD_TXT_FONT font_type;
	int font_size;		//以窗口的百分比来表示

	HFONT out_ft;		//创建的字体对象

	int isBold;			//是否粗体
	int isTransparent;	//是否透明底色
	COLORREF bkColor;	//背景色
} OSD_INFO_TXT;

typedef enum 
{
	STD_FILE_HEAD =	0,	    		// 文件头
		STD_VIDEO_I_FRAME = 1,			// 视频I帧
		STD_VIDEO_B_FRAME =	2,			// 视频B帧
		STD_VIDEO_P_FRAME = 3,			// 视频P帧
		STD_VIDEO_BP_FRAME = 4,			// 视频BP帧
		STD_VIDEO_BBP_FRAME	= 5,		// 视频B帧B帧P帧
		STD_VIDEO_J_FRAME = 6,			// 图片帧
		STD_AUDIO_PACKET = 10,			// 音频包
}MEDIA_DATA_TYPE;

typedef struct
{
	int		nPacketType;				// 包类型,MEDIA_DATA_TYPE
	char*	pPacketBuffer;				// 缓存区地址
	unsigned int	dwPacketSize;				// 包的大小
	
	// 绝对时标
	int		nYear;						// 时标:年		
	int		nMonth;						// 时标:月
	int		nDay;						// 时标:日
	int		nHour;						// 时标:时
	int		nMinute;					// 时标:分
	int		nSecond;					// 时标:秒
	unsigned int 	dwTimeStamp;					// 相对时标低位，单位为毫秒	
	unsigned int   dwFrameNum;             //帧序号
	unsigned int   dwFrameRate;            //帧率
	unsigned short uWidth;              //图像宽度
	unsigned short uHeight;             //图像高度
	unsigned int   nAudioEncodeType;          //音频编码类型IMA	 9 PCM8_VWIS 12 MS_ADPCM 13 G711A 14
	unsigned int   nBitsPerSample;			//音频采样位深
	unsigned int   nSamplesPerSecond;       // 音频采样率
	unsigned int       Reserved[6];            //保留
} STDH264_PACKET_INFO;


// 回调函数类型
typedef void (CALLBACK *AudioCaptureCallBack)(LPBYTE pDataBuffer, DWORD DataLength, long nUser);
typedef void (CALLBACK *DrawCallBack)(LONG nPort,HDC hDc,LONG nUser);
typedef void (CALLBACK *DecodeCallBack)(LONG nPort, LPCSTR pBuf,LONG nSize,FRAME_INFO * pFrameInfo, LONG nPlayedFrames);
typedef void (CALLBACK *DisplayCallBack)(LONG nPort,LPCSTR pBuf,LONG nSize,LONG nWidth,LONG nHeight, LONG nStamp,LONG nType,LONG nUser);
typedef void (CALLBACK *FileCallBack)(LONG nPort, LONG nUser);
typedef void (CALLBACK *VerifyCallBack)(LONG nPort, FRAME_POS * pFilePos, DWORD bIsVideo, LONG nUser);
typedef void (CALLBACK *AudioCallBack)(LONG nPort, PBYTE pAudioBuf, LONG nSize, LONG nStamp, LONG nType, LONG nUser);
typedef void (CALLBACK *DemuxCallBack)(LONG nPort, VIDEO_FRAME_INFO *pFrameInfo,LONG nUser);
typedef void (CALLBACK *SourceBufCallBack)(LONG nPort,DWORD nBufSize, LONG nUser);
typedef void (CALLBACK *ImageSizeChangeCallBack)(LONG nPort, LONG nUser);

typedef void (CALLBACK *CoverFileCallBack) (DWORD CurrentPos, DWORD TotoalPos,long dwUser);//转换进度

//信息帧回调
typedef void (CALLBACK *InfoFramCallBack)(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser);

//以下为对外接口，供用户作二次开发调用

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_OpenFile(LONG nPort, LPCSTR sFileName);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_CloseFile(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Play(LONG nPort, HWND hWnd);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Stop(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Pause(LONG nPort,DWORD nPause);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Fast(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Slow(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_NextFrame(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_PrevFrame(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetPlayPos(LONG nPort, FLOAT fRelativePos);
H264_PLAY_API FLOAT CALLMETHOD 	H264_PLAY_GetPlayPos(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetFileEndCallBack(LONG nPort, FileCallBack pProc,LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetVolume(LONG nPort,WORD nVolume);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StopSound();
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_PlaySound(LONG nPort);
H264_PLAY_API BOOL	CALLMETHOD 	H264_PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_CloseStream(LONG nPort);
H264_PLAY_API LONG  CALLMETHOD 	H264_PLAY_GetCaps();
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetFileTime(LONG nPort);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetPlayedTime(LONG nPort);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetPlayedFrames(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Back(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDecCallBack(LONG nPort, DecodeCallBack pProc);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayCallBack(LONG nPort, DisplayCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ConvertToBmpFile(PBYTE pBuf,LONG nSize,LONG nWidth,LONG nHeight, LPCSTR sFileName,char*pDstBuf=NULL);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetFileTotalFrames(LONG nPort);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetPlayedTimeEx(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetCurrentFrameNum(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetSdkVersion();
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetLastError(LONG nPort);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_RefreshPlay(LONG nPort);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_PlaySoundShare(LONG nPort);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_StopSoundShare(LONG nPort);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetStreamOpenMode(LONG nPort);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetOverlayMode(LONG nPort);
H264_PLAY_API WORD 	CALLMETHOD 	H264_PLAY_GetVolume(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
H264_PLAY_API DWORD CALLMETHOD	H264_PLAY_GetSourceBufferRemain(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ResetSourceBuffer(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetSourceBufCallBack(LONG nPort,DWORD nThreShold, SourceBufCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ResetSourceBufFlag(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetDisplayBuf(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetFileRefCallBack(LONG nPort, FileCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_InitDDrawDevice();
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ReleaseDDrawDevice();
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetDDrawDeviceTotalNums();

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayType(LONG nPort,LONG nType);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetDisplayType(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDecCBStream(LONG nPort,DWORD nStream);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_RigisterDrawFun(LONG nPort, DrawCallBack pProc,LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetTimerType(LONG nPort,DWORD nTimerType);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetTimerType(LONG nPort,DWORD *pTimerType);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ResetBuffer(LONG nPort,DWORD nBufType);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, VerifyCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetAudioCallBack(LONG nPort, AudioCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetImageSizeChangeCallBack(LONG nPort,ImageSizeChangeCallBack pProc,LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD	H264_PLAY_SetImageSizeChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetColor(LONG nPort, DWORD nRegionNum, LONG nBrightness, LONG nContrast, LONG nSaturation, LONG nHue);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetColor(LONG nPort, DWORD nRegionNum, LONG *pBrightness, LONG *pContrast, LONG *pSaturation, LONG *pHue);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetMDRange(LONG nPort,RECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold) ;
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue) ;

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_CatchPic(LONG nPort, LPCSTR sFileName,long ntype=0 ) ;
H264_PLAY_API LONG  CALLMETHOD 	H264_PLAY_CatchPicBuf(LONG nPort, char* pBuf,LONG len,LONG *width,LONG *height,long ntype=0) ;

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StartDataRecord(LONG nPort,  LPCSTR sFileName, LONG nType);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StopDataRecord(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_AdjustFluency(LONG nPort, int level);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_AdjustFluencyEx(LONG nPort, int time);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetPlayFPS(LONG nPort, LONG nFPS);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetPlayFPS(LONG nPort);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDemuxCallBack(LONG nPort, DemuxCallBack pProc, LONG nUser);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StartAudioCapture(AudioCaptureCallBack pProc, LONG nBitsPerSample, LONG nSamplesPerSec, LONG nLength, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StopAudioCapture();
H264_PLAY_API BOOL  CALLMETHOD	H264_PLAY_GetPort(LONG* nPort);
H264_PLAY_API BOOL	CALLMETHOD	H264_PLAY_FreePort(LONG nPort);
H264_PLAY_API COLORREF 	CALLMETHOD	H264_PLAY_GetColorKey(LONG nPort);
H264_PLAY_API LONG	CALLMETHOD	H264_PLAY_GetFileHeadLength();
H264_PLAY_API DWORD CALLMETHOD H264_PLAY_GetCurTimeStamp(LONG nPort);

//设置osd叠加信息,必须在openstream后，play之前设置，否则无效
H264_PLAY_API int CALLMETHOD H264_PLAY_SetOsdTex(LONG nPort, OSD_INFO_TXT * txt);
//删除osd叠加信息,nIndex是H264_PLAY_SetOsdTex的返回值
H264_PLAY_API int CALLMETHOD H264_PLAY_DeleteOsdTex(LONG nPort, int nIndex);
//H264录像文件转Avi录像文件
H264_PLAY_API int CALLMETHOD H264_PLAY_ConvertFile(const char* pSourceFile,const char* pDestFile,  LONG nType, CoverFileCallBack coverPosCallback, DWORD dwUser);

//信息帧回调
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetInfoFrameCallBack(LONG nPort, InfoFramCallBack pProc, LONG nUser);

//只播放I帧
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_OnlyIFrame(LONG nPort, bool bPlayOnlyIFrame);

//标准H264数据写入
H264_PLAY_API BOOL CALLMETHOD H264_PLAY_InputStdH264Data(LONG nPort,STDH264_PACKET_INFO *infor);


#endif

