using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace ClientDemo
{
    enum SearchModeType
    {
        DDNS_SERIAL = 0,//按序列号
        DDNS_USERNAME,  //按用户名
    }
    public enum SDK_RET_CODE
    {
        H264_DVR_NOERROR = 0,					//没有错误
        H264_DVR_SUCCESS = 1,					//返回成功
        H264_DVR_SDK_NOTVALID = -10000,				//非法请求
        H264_DVR_NO_INIT = -10001,				//SDK未经初始化
        H264_DVR_ILLEGAL_PARAM = -10002,			//用户参数不合法
        H264_DVR_INVALID_HANDLE = -10003,			//句柄无效
        H264_DVR_SDK_UNINIT_ERROR = -10004,			//SDK清理出错
        H264_DVR_SDK_TIMEOUT = -10005,			//等待超时
        H264_DVR_SDK_MEMORY_ERROR = -10006,			//内存错误，创建内存失败
        H264_DVR_SDK_NET_ERROR = -10007,			//网络错误
        H264_DVR_SDK_OPEN_FILE_ERROR = -10008,			//打开文件失败
        H264_DVR_SDK_UNKNOWNERROR = -10009,			//未知错误
        H264_DVR_DEV_VER_NOMATCH = -11000,			//收到数据不正确，可能版本不匹配
        H264_DVR_SDK_NOTSUPPORT = -11001,			//版本不支持

        H264_DVR_OPEN_CHANNEL_ERROR = -11200,			//打开通道失败
        H264_DVR_CLOSE_CHANNEL_ERROR = -11201,			//关闭通道失败
        H264_DVR_SUB_CONNECT_ERROR = -11202,			//建立媒体子连接失败
        H264_DVR_SUB_CONNECT_SEND_ERROR = -11203,			//媒体子连接通讯失败
        /// 用户管理部分错误码
        H264_DVR_NOPOWER = -11300,			//无权限
        H264_DVR_PASSWORD_NOT_VALID = -11301,			// 账号密码不对
        H264_DVR_LOGIN_USER_NOEXIST = -11302,			//用户不存在
        H264_DVR_USER_LOCKED = -11303,			// 该用户被锁定
        H264_DVR_USER_IN_BLACKLIST = -11304,			// 该用户不允许访问(在黑名单中)
        H264_DVR_USER_HAS_USED = -11305,			// 该用户已登陆
        H264_DVR_USER_NOT_LOGIN = -11306,			// 该用户没有登陆
        H264_DVR_CONNECT_DEVICE_ERROR = -11307,			//可能设备不存在
        H264_DVR_ACCOUNT_INPUT_NOT_VALID = -11308,			//用户管理输入不合法
        H264_DVR_ACCOUNT_OVERLAP = -11309,			//索引重复
        H264_DVR_ACCOUNT_OBJECT_NONE = -11310,			//不存在对象, 用于查询时
        H264_DVR_ACCOUNT_OBJECT_NOT_VALID = -11311,			//不存在对象
        H264_DVR_ACCOUNT_OBJECT_IN_USE = -11312,			//对象正在使用
        H264_DVR_ACCOUNT_SUBSET_OVERLAP = -11313,			//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
        H264_DVR_ACCOUNT_PWD_NOT_VALID = -11314,			//密码不正确
        H264_DVR_ACCOUNT_PWD_NOT_MATCH = -11315,			//密码不匹配
        H264_DVR_ACCOUNT_RESERVED = -11316,			//保留帐号
        /// 配置管理相关错误码

        H264_DVR_OPT_RESTART = -11400,			// 保存配置后需要重启应用程序
        H264_DVR_OPT_REBOOT = -11401,			// 需要重启系统
        H264_DVR_OPT_FILE_ERROR = -11402,			// 写文件出错
        H264_DVR_OPT_CAPS_ERROR = -11403,			// 配置特性不支持
        H264_DVR_OPT_VALIDATE_ERROR = -11404,			// 配置校验失败
        H264_DVR_OPT_CONFIG_NOT_EXIST = -11405,			// 请求或者设置的配置不存在
        /// 
        H264_DVR_CTRL_PAUSE_ERROR = -11500,			//暂停失败
        H264_DVR_SDK_NOTFOUND = -11501,			//查找失败，没有找到对应文件
        H264_DVR_CFG_NOT_ENABLE = -11502,           //配置未启用
        H264_DVR_DECORD_FAIL = -11503,           //配置未启用
        //DNS协议解析返回错误码
        H264_DVR_SOCKET_ERROR = -11600,         //创建套节字失败
        H264_DVR_SOCKET_CONNECT = -11601,         //连接套节字失败
        H264_DVR_SOCKET_DOMAIN = -11602,         //域名解析失败
        H264_DVR_SOCKET_SEND = -11603,         //发送数据失败
    }
    public enum SDK_CONFIG_TYPE
    {
        E_SDK_CONFIG_NOTHING = 0,		//
        E_SDK_CONFIG_USER,			//用户信息，包含了权限列表，用户列表和组列表
        E_SDK_CONFIG_ADD_USER,		//增加用户
        E_SDK_CONFIG_MODIFY_USER,		//修改用户
        E_SDK_CONFIG_DELETE_USER,
        E_SDK_CONFIG_ADD_GROUP,		//增加组
        E_SDK_CONFIG_MODIFY_GROUP,	//修改组
        E_SDK_COFIG_DELETE_GROUP,
        E_SDK_CONFIG_MODIFY_PSW,		//修改密码
        E_SDK_CONFIG_ABILITY_SYSFUNC = 9,//支持的网络功能
        E_SDK_CONFIG_ABILTY_ENCODE,	//首先获得编码能力
        E_SDK_CONFIG_ABILITY_PTZPRO,	//云台协议
        E_SDK_COMFIG_ABILITY_COMMPRO,	//串口协议
        E_SDK_CONFIG_ABILITY_MOTION_FUNC,	//动态检测块
        E_SDK_CONFIG_ABILITY_BLIND_FUNC,	//视频遮挡块
        E_SDK_CONFIG_ABILITY_DDNS_SERVER,	//DDNS服务支持类型
        E_SDK_CONFIG_ABILITY_TALK,		//对讲编码类型
        E_SDK_CONFIG_SYSINFO = 17,		//系统信息
        E_SDK_CONFIG_SYSNORMAL,	//普通配置
        E_SDK_CONFIG_SYSENCODE,	//编码配置
        E_SDK_CONFIG_SYSNET,		//网络设置
        E_SDK_CONFIG_PTZ,			//云台页面
        E_SDK_CONFIG_COMM,		//串口页面
        E_SDK_CONFIG_RECORD,		//录像设置界面
        E_SDK_CONFIG_MOTION,		//动态检测页面
        E_SDK_CONFIG_SHELTER,		//视频遮挡
        E_SDK_CONFIG_VIDEO_LOSS,  //视频丢失,
        E_SDK_CONFIG_ALARM_IN,	//报警输入
        E_SDK_CONFIG_ALARM_OUT,	//报警输出
        E_SDK_CONFIG_DISK_MANAGER,//硬盘管理界面
        E_SDK_CONFIG_OUT_MODE,	//输出模式界面
        E_SDK_CONFIG_CHANNEL_NAME,//通道名称
        E_SDK_CONFIG_AUTO,		//自动维护界面配置
        E_SDK_CONFIG_DEFAULT,     //恢复默认界面配置
        E_SDK_CONFIG_DISK_INFO,	//硬盘信息
        E_SDK_CONFIG_LOG_INFO,	//查询日志
        E_SDK_CONFIG_NET_IPFILTER,
        E_SDK_CONFIG_NET_DHCP,
        E_SDK_CONFIG_NET_DDNS,
        E_SDK_CONFIG_NET_EMAIL,
        E_SDK_CONFIG_NET_MULTICAST,
        E_SDK_CONFIG_NET_NTP,
        E_SDK_CONFIG_NET_PPPOE,
        E_SDK_CONFIG_NET_DNS,
        E_SDK_CONFIG_NET_FTPSERVER,
        E_SDK_CONFIG_SYS_TIME,	//系统时间	
        E_SDK_CONFIG_CLEAR_LOG,	//清除日志
        E_SDK_REBOOT_DEV,		//重启启动设备
        E_SDK_CONFIG_ABILITY_LANG,	//支持语言
        E_SDK_CONFIG_VIDEO_FORMAT,
        E_SDK_CONFIG_COMBINEENCODE,	//组合编码
        E_SDK_CONFIG_EXPORT,	//配置导出
        E_SDK_CONFIG_IMPORT,	//配置导入
        E_SDK_LOG_EXPORT,		//日志导出
        E_SDK_CONFIG_COMBINEENCODEMODE, //组合编码模式
        E_SDK_WORK_STATE,	//运行状态
        E_SDK_ABILITY_LANGLIST, //实际支持的语言集
        E_SDK_CONFIG_NET_ARSP,
        E_SDK_CONFIG_SNAP_STORAGE,
        E_SDK_CONFIG_NET_3G, //3G拨号
        E_SDK_CONFIG_NET_MOBILE, //手机监控
        E_SDK_CONFIG_UPGRADEINFO, //获取升级信息
        E_SDK_CONFIG_NET_DECODER,
        E_SDK_ABILITY_VSTD, //实际支持的视频制式
        E_SDK_CONFIG_ABILITY_VSTD,	//支持视频制式
        E_SDK_CONFIG_NET_UPNP, //UPUN设置
        E_SDK_CONFIG_NET_WIFI,
        E_SDK_CONFIG_NET_WIFI_AP_LIST,
        E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, //简化的编码配置
        E_SDK_CONFIG_ALARM_CENTER,  //告警中心
        E_SDK_CONFIG_NET_ALARM,
        E_SDK_CONFIG_NET_MEGA,     //互信互通
        E_SDK_CONFIG_NET_XINGWANG, //星望
        E_SDK_CONFIG_NET_SHISOU,   //视搜
        E_SDK_CONFIG_NET_VVEYE,    //VVEYE
        E_SDK_CONFIG_NET_PHONEMSG,  //短信
        E_SDK_CONFIG_NET_PHONEMEDIAMSG,  //彩信
        E_SDK_VIDEO_PREVIEW,
        E_SDK_CONFIG_NET_DECODER_V2,
        E_SDK_CONFIG_NET_DECODER_V3,//数字通道
        E_SDK_CONFIG_ABILITY_SERIALNO,	// 序列号
        E_SDK_CONFIG_NET_RTSP,    //RTSP
        E_SDK_GUISET,              //GUISET
        E_SDK_CATCHPIC,               //抓图
        E_SDK_VIDEOCOLOR,             //视频颜色设置
        E_SDK_CONFIG_COMM485,
        E_SDK_COMFIG_ABILITY_COMMPRO485, //串口485
        E_SDK_CONFIG_SYS_TIME_NORTC,	//系统时间noRtc
        E_SDK_CONFIG_REMOTECHANNEL,   //远程通道
        E_SDK_CONFIG_OPENTRANSCOMCHANNEL, //打开透明串口
        E_SDK_CONFIG_CLOSETRANSCOMCHANNEL,  //关闭透明串口
        E_SDK_CONFIG_SERIALWIRTE,  //写入透明串口信息
        E_SDK_CONFIG_SERIALREAD,   //读取透明串口信息
        E_SDK_CONFIG_CHANNELTILE_DOT,	//点阵信息
        E_SDK_CONFIG_CAMERA,           //摄象机参数
        E_SDK_CONFIG_ABILITY_CAMERA,    //曝光能力级
        E_SDK_CONFIG_BUGINFO,    //命令调试
        E_SDK_CONFIG_STORAGENOTEXIST,//硬盘不存在
        E_SDK_CONFIG_STORAGELOWSPACE, //硬盘容量不足
        E_SDK_CONFIG_STORAGEFAILURE, //硬盘出错
        E_SDK_CFG_NETIPCONFLICT,    //IP冲突
        E_SDK_CFG_NETABORT,  //网络异常
        E_SDK_CONFIG_CHNSTATUS, //通道状态
        E_SDK_CONFIG_CHNMODE,  //通道模式
        E_SDK_CONFIG_NET_DAS,    //主动注册
        E_SDK_CONFIG_CAR_INPUT_EXCHANGE,   //外部信息输入与车辆状态的对应关系
        E_SDK_CONFIG_DELAY_TIME,       //车载系统延时配置
        E_SDK_CONFIG_NET_ORDER,            //网络优先级
        E_SDK_CONFIG_ABILITY_NETORDER, ////网络优先级设置能力
        E_SDK_CONFIG_CARPLATE,				//车牌号配置
    }
    public enum MEDIA_FILE_TYPE
    {
        MEDIA_FILE_NONE = 0,
        MEDIA_FILE_H264 = 1,
        MEDIA_FILE_AVI = 2,
        MEDIA_FILE_RMVB = 3,
        MEDIA_FILE_MPG4 = 4,
        MEDIA_FILE_NUM
    }

    public enum SocketStyle
    {
        TCPSOCKET = 0,
        UDPSOCKET
    };
    public enum SERIAL_TYPE
    {
        RS232 = 0,
        RS485 = 1,
    };
    public enum SDK_RSSI_SINGNAL
    {
	    SDK_RSSI_NO_SIGNAL,   //<= -90db
	    SDK_RSSI_VERY_LOW,     //<= -81db
	    SDK_RSSI_LOW,          //<= -71db
	    SDK_RSSI_GOOD,         //<= -67db
	    SDK_RSSI_VERY_GOOD,    //<= -57db
	    SDK_RSSI_EXCELLENT     //>-57db
    };
    public enum SDK_DeviceType
    {
        SDK_DEVICE_TYPE_DVR,	///< 普通DVR设备
        SDK_DEVICE_TYPE_NVS,	///< NVS设备
        SDK_DEVICE_TYPE_IPC,	///< IPC设备
        SDK_DEVICE_TYPE_HVR,	///<混合dvr
        SDK_DEVICE_TYPE_IVR,	///<智能dvr
        SDK_DEVICE_TYPE_MVR,	///<车载dvr
        SDK_DEVICE_TYPE_NR
    };

    //本地播放控制
    public enum SDK_LoalPlayAction
    {
        SDK_Local_PLAY_PAUSE,		/*<! 暂停播放 */
        SDK_Local_PLAY_CONTINUE,		/*<! 继续正常播放 */
        SDK_Local_PLAY_FAST,	        /*<! 加速播放 */
        SDK_Local_PLAY_SLOW,	        /*<! 减速播放 */
    };
    //云台操作类型
    public enum PTZ_ControlType
    {
        TILT_UP = 0,			//上
        TILT_DOWN,				//下
        PAN_LEFT,				//左
        PAN_RIGHT,				//右
        PAN_LEFTTOP,			//左上
        PAN_LEFTDOWN,			//左下
        PAN_RIGTHTOP,			//右上
        PAN_RIGTHDOWN,			//右下
        ZOOM_OUT,				//变倍小
        ZOOM_IN,				//变倍大
        FOCUS_FAR,				//焦点后调
        FOCUS_NEAR,				//焦点前调
        IRIS_OPEN,				//光圈扩大
        IRIS_CLOSE,				//光圈缩小13

        EXTPTZ_OPERATION_ALARM,			///< 报警功能 
        EXTPTZ_LAMP_ON,					///< 灯光开
        EXTPTZ_LAMP_OFF,				//灯光关
        EXTPTZ_POINT_SET_CONTROL,			//设置预置点 
        EXTPTZ_POINT_DEL_CONTROL,			//清除预置点 
        EXTPTZ_POINT_MOVE_CONTROL,			//转预置点
        EXTPTZ_STARTPANCRUISE,			//开始水平旋转		20	
        EXTPTZ_STOPPANCRUISE,			//停止水平旋转	
        EXTPTZ_SETLEFTBORDER,			//设置左边界		
        EXTPTZ_SETRIGHTBORDER,			//设置右边界	
        EXTPTZ_STARTLINESCAN,			//自动扫描开始 
        EXTPTZ_CLOSELINESCAN,			//自动扫描开停止 
        EXTPTZ_ADDTOLOOP,				//加入预置点到巡航	p1巡航线路	p2预置点值	
        EXTPTZ_DELFROMLOOP,				//删除巡航中预置点	p1巡航线路	p2预置点值	
        EXTPTZ_POINT_LOOP_CONTROL,			//开始巡航 28
        EXTPTZ_POINT_STOP_LOOP_CONTROL,	//停止巡航
        EXTPTZ_CLOSELOOP,				//清除巡航	p1巡航线路		
        EXTPTZ_FASTGOTO,				//快速定位	
        EXTPTZ_AUXIOPEN,				//辅助开关，关闭在子命令中//param1 参见SDK_PtzAuxStatus，param2传入具体数值
        EXTPTZ_OPERATION_MENU,				//球机菜单操作，其中包括开，关，确定等等
        EXTPTZ_REVERSECOMM,				//镜头翻转
        EXTPTZ_OPERATION_RESET,			///< 云台复位

        EXTPTZ_TOTAL,
    };
    [StructLayout(LayoutKind.Sequential, Size = 4)]
    public struct CONFIG_IPAddress
    {	//IP addr
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public byte[] c;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SDK_CONFIG_NET_COMMON
    {
        //!主机名
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string HostName;
        //!主机IP
        public CONFIG_IPAddress HostIP;
        //!子网掩码
        public CONFIG_IPAddress Submask;
        //!网关IP
        public CONFIG_IPAddress Gateway;
        //!HTTP服务端口
        public int HttpPort;
        //!TCP侦听端口
        public int TCPPort;
        //!SSL侦听端口
        public int SSLPort;
        //!UDP侦听端口
        public int UDPPort;
        //!最大连接数
        public int MaxConn;
        //!监视协议 {"TCP","UDP","MCAST",…}
        public int MonMode;
        //!限定码流值
        public int MaxBps;
        //!传输策略
        //char TransferPlan[NET_NAME_PASSWORD_LEN];
        public int TransferPlan;

        //!是否启用高速录像下载测率
        public byte bUseHSDownLoad;

        //!MAC地址
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string sMac;
    }

     [StructLayout(LayoutKind.Sequential)]
    public struct SDK_CONFIG_NET_COMMON_V2
    {
	    //!主机名
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string HostName;
        //!主机IP
        public CONFIG_IPAddress HostIP;
        //!子网掩码
        public CONFIG_IPAddress Submask;
        //!网关IP
        public CONFIG_IPAddress Gateway;
        //!HTTP服务端口
        public int HttpPort;
        //!TCP侦听端口
        public int TCPPort;
        //!SSL侦听端口
        public int SSLPort;
        //!UDP侦听端口
        public int UDPPort;
        //!最大连接数
        public int MaxConn;
        //!监视协议 {"TCP","UDP","MCAST",…}
        public int MonMode;
        //!限定码流值
        public int MaxBps;
        //!传输策略
        //char TransferPlan[NET_NAME_PASSWORD_LEN];
        public int TransferPlan;

        //!是否启用高速录像下载测率
        public byte bUseHSDownLoad;

	    //!MAC地址
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string sMac;

	    //序列号
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string sSn;
	    //保留
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string Resume;
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct CHANNEL_INFO
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
	    string				szChnnelName;			// 通道名称.
	    public int					nChnnID;							// 用于地图节点管理
        public int nChannelNo;							// 通道号.
        public int bUserRight;							// 用户权限(使能).
        public int PreViewChannel;						// 预览通道
        public int nStreamType;						// 码流类型
        public DEV_INFO DeviceInfo;							// 设备信息.
        public int nCombinType;						// 组合编码模式
        public int dwTreeItem;							//记录设备树中的节点句柄，可以节省查找事件
        public int nFlag;								//1为选择为录像 0 为没有被选择 2 为正在录像
        public int nWndIndex;
    };

    public struct DEV_INFO
    {
        public int nListNum;		   //position in the list
        public int lLoginID;			//login handle
        public int lID;				//device ID
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 60)]
        public string szDevName;		//device name
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 15)]
        public string szIpaddress;		//device IP
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string szUserName;		//user name
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        public string szPsw;			//pass word
        public int nPort;				//port number
        public int nTotalChannel;		//total channel
        public SDK_CONFIG_NET_COMMON_V2 NetComm;                  // net config
        public H264_DVR_DEVICEINFO NetDeviceInfo;
        public byte bSerialID;//be SerialNumber login
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string szSerIP;//server ip
        public int nSerPort;           //server port
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string szSerialInfo;  //SerialNumber
    }
    public struct DDNS_INFO
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string ID;    //设备标识
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string IP;   //内网IP
        public int WebPort; //Web端口,默认为80
        public int MediaPort; //媒体端口,默认为34567
        public int MobilePort;  //手机监控端口，默认为34599
        public int UPNPWebPort;  //UPNP启动下Web端口,UPNP不开启为0
        public int UPNPMediaPort; //UPNP启动下媒体端口,UPNP不开启为0
        public int UPNPMobilePort; //UPNP启动下手机监控端口,UPNP不开启为0
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        string Username; //用户名
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        string Password; //密码
    }
    public struct SDK_NetKeyBoardData
    {
        public int iValue;
        public int iState;
    }
    public struct SDK_NetAlarmInfo
    {
        public int iEvent;  //目前未使用
        public int iState;   //每bit表示一个通道,bit0:第一通道,0-无报警 1-有报警, 依次类推
    }
    public struct SDK_SYSTEM_TIME
    {
        public int year;///< 年。   
        public int month;///< 月，January = 1, February = 2, and so on.   
        public int day;///< 日。   
        public int wday;///< 星期，Sunday = 0, Monday = 1, and so on   
        public int hour;///< 时。   
        public int minute;///< 分。   
        public int second;///< 秒。   
        public int isdst;///< 夏令时标识。   
    }
    public struct TransComChannel//透明窗口
    {
        public SERIAL_TYPE TransComType;//SERIAL_TYPE
        public ushort baudrate;
        public ushort databits;
        public ushort stopbits;
        public ushort parity;
    }
    public struct H264_DVR_DEVICEINFO
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string sSoftWareVersion;	///< 软件版本信息
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string sHardWareVersion;	///< 硬件版本信息
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string sEncryptVersion;	///< 加密版本信息
        public SDK_SYSTEM_TIME tmBuildTime;///< 软件创建时间
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string sSerialNumber;			///< 设备序列号
        public int byChanNum;				///< 视频输入通道数
        public int iVideoOutChannel;		///< 视频输出通道数
        public int byAlarmInPortNum;		///< 报警输入通道数
        public int byAlarmOutPortNum;		///< 报警输出通道数
        public int iTalkInChannel;			///< 对讲输入通道数
        public int iTalkOutChannel;		///< 对讲输出通道数
        public int iExtraChannel;			///< 扩展通道数	
        public int iAudioInChannel;		///< 音频输入通道数
        public int iCombineSwitch;			///< 组合编码通道分割模式是否支持切换
        public int iDigChannel;		///<数字通道数
        public ushort uiDeviceRunTime;	///<系统运行时间
        public SDK_DeviceType deviceTye;	///设备类型
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]                                    ///
        public string sHardWare;		///<设备型号                                   ///
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string uUpdataTime;	///<更新日期 例如 2013-09-03 14:15:13
	    public int uUpdataType;	///<更新内容
	    public int nLanguage;//国家的语言ID,0英语 1中文 2中文繁体 3韩语 4德语 5葡萄牙语 6俄语
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
	    public string sCloudErrCode;//云登陆具体错误内容
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public int[] status;            
    }
    public struct H264_DVR_CLIENTINFO
    {
        public int nChannel;	//通道号
        public int nStream;	//0表示主码流，为1表示子码流
        public int nMode;		//0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-音视频分开(TCP)
        public int nComType;	//只对组合编码通道有效, 组合编码通道的拼图模式
        public IntPtr hWnd;
    }
    public struct SDK_TIMESECTION
    {
        //!使能
        public int enable;
        //!开始时间:小时
        public int startHour;
        //!开始时间:分钟
        public int startMinute;
        //!开始时间:秒钟
        public int startSecond;
        //!结束时间:小时
        public int endHour;
        //!结束时间:分钟
        public int endMinute;
        //!结束时间:秒钟
        public int endSecond;
    }
    //查询录像条件
    public struct H264_DVR_FINDINFO
    {
	    public int nChannelN0;			//通道号
	    public int nFileType;			//文件类型, 见SDK_File_Type
	    public H264_DVR_TIME startTime;	//开始时间
	    public H264_DVR_TIME endTime;	//结束时间
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]     	
        public string szCard;		//卡号
	    public uint hWnd;
    };

    //录像文件返回结构体
    [StructLayout(LayoutKind.Sequential)]
    public struct H264_DVR_FILE_DATA 
     {
        public int ch;						//通道号
        public int size;                    //文件大小
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 108)]     
        public string sFileName;		///< 文件名
        public SDK_SYSTEM_TIME stBeginTime;	///< 文件开始时间
        public SDK_SYSTEM_TIME stEndTime;		///< 文件结束时间
        public IntPtr hWnd;
        public int StreamType;	//码流类型是回放主码流还是辅助码流
//         H264_DVR_FILE_DATA()
//         {
//             hWnd = NULL;
//             StreamType = 0;
//         }
     };

    public struct H264_DVR_TIME {
	    public int dwYear;		//年
        public int dwMonth;	//月
	    public int dwDay;		//日
	    public int dwHour;		//时
	    public int dwMinute;	//分
	    public int dwSecond;	//秒
    };

    public struct SDK_VIDEOCOLOR_PARAM
    {
        public int nBrightness;		///< 亮度	0-100
        public int nContrast;			///< 对比度	0-100
        public int nSaturation;		///< 饱和度	0-100
        public int nHue;				///< 色度	0-100
        public int mGain;				///< 增益	0-100 第７位置1表示自动增益		
        public int mWhitebalance;		///< 自动白电平控制，bit7置位表示开启自动控制.0x0,0x1,0x2分别代表低,中,高等级
        public int nAcutance;          ///< 锐度   0-15
    };
    public struct SDK_VIDEOCOLOR
    {
        public SDK_TIMESECTION tsTimeSection;		/// 时间段
        public SDK_VIDEOCOLOR_PARAM dstColor;			/// 颜色定义
        public int iEnable;
    }
    public struct SDK_CONFIG_VIDEOCOLOR
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public SDK_VIDEOCOLOR[] dstVideoColor;
    }
    public struct SearchMode
    {
        public int nType;        //查询类型，见SearchModeType
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string szSerIP;//服务器地址
        public int nSerPort;           //服务器端口号
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string szSerialInfo;  //如果是按序列号，则为序列号，如果是用户名，则为用户名
    }

    
    //摄象机参数.....

    //曝光配置
    public struct SDK_ExposureCfg
    {
	    public int  level;    //曝光等级
	    public uint leastTime;//自动曝光时间下限或手动曝光时间，单位微秒
	    public uint mostTime; //自动曝光时间上限，单位微秒
    };

    //增益配置
    public struct SDK_GainCfg
    {
	    public int gain;    //自动增益上限(自动增益启用)或固定增益值
	    public int autoGain;//自动增益是否启用，0:不开启  1:开启
    };

    //网络摄像机配置
    public struct SDK_CameraParam
    {
	    public uint whiteBalance;         //白平衡
	    public uint dayNightColor;        //日夜模式，取值有彩色、自动切换和黑白
	    public int elecLevel;             //参考电平值
	    public uint apertureMode;          //自动光圈模式
	    public uint BLCMode;               //背光补偿模式
	    public SDK_ExposureCfg exposureConfig;//曝光配置
	    public SDK_GainCfg     gainConfig;    //增益配置

	    public uint PictureFlip;		//图片上下翻转
	    public uint PictureMirror;	//图片左右翻转(镜像)
	    public uint RejectFlicker;	//日光灯防闪功能
	    public uint EsShutter;		//电子慢快门功能

	    public int ircut_mode;		//IR-CUT切换 0 = 红外灯同步切换 1 = 自动切换

	    public int dnc_thr;			//日夜转换阈值
	    public int ae_sensitivity;	//ae灵敏度配置
	    public int Day_nfLevel;		//noise filter 等级，0-5,0不滤波，1-5 值越大滤波效果越明显
	    public int Night_nfLevel;
	    public int Ircut_swap;		//ircut 正常序= 0        反序= 1
    };

    //所有摄象机配置
    public struct SDK_AllCameraParam
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public SDK_CameraParam[] vCameraParamAll;   //所有的通道
    };
       
    public struct PACKET_INFO_EX
    {
	    public int		nPacketType;				// 包类型,见MEDIA_PACK_TYPE
	    public string	pPacketBuffer;				// 缓存区地址
	    public uint	dwPacketSize;				// 包的大小

	    // 绝对时标
	    public int		nYear;						// 时标:年		
	    public int		nMonth;						// 时标:月
	    public int		nDay;						// 时标:日
	    public int		nHour;						// 时标:时
	    public int		nMinute;					// 时标:分
	    public int		nSecond;					// 时标:秒
	    public uint 	dwTimeStamp;					// 相对时标低位，单位为毫秒
	    public uint	dwTimeStampHigh;        //相对时标高位，单位为毫秒
	    public uint   dwFrameNum;             //帧序号
	    public uint   dwFrameRate;            //帧率
	    public ushort uWidth;              //图像宽度
	    public ushort uHeight;             //图像高度
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
	    public ushort[]       Reserved;            //保留
    } ;
    ///< 夏令时结构
    public struct DSTPoint
    {
        public int iYear;
        public int iMonth;
        public int iWeek;		///<周1:first  to2 3 4 -1:last one   0:表示使用按日计算的方法[-1,4]
        public int iWeekDay;	///<weekday from sunday=0	[0, 6]
        public int Hour;
        public int Minute;
    };
    //普通配置页结构体
    public struct SDK_CONFIG_NORMAL
    {
        public SDK_SYSTEM_TIME sysTime;		//系统时间

	    public int iLocalNo;			/*!< 本机编号:[0, 998] */
        public int iOverWrite;			/*!< 硬盘满时处理 "OverWrite", "StopRecord" */
        public int iSnapInterval;			///< 定时抓图的时间间隔，以秒为单位 
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 64)]
	    public string sMachineName;	///< 机器名
        public int iVideoStartOutPut;	/*!< 输出模式 */
        public int iAutoLogout;			///< 本地菜单自动注销(分钟)	[0, 120]

        public int iVideoFormat;		/*!< 视频制式:“PAL”, “NTSC”, “SECAM” */
        public int iLanguage;			/*!< 语言选择:“English”, “SimpChinese”, “TradChinese”, “Italian”, “Spanish”, “Japanese”, “Russian”, “French”, “German” */
        public int iDateFormat;		/*!< 日期格式:“YYMMDD”, “MMDDYY”, “DDMMYY” */
        public int iDateSeparator;		/*!< 日期分割符:“.”, “-”, “/” */
        public int iTimeFormat;		/*!< 时间格式:“12”, “24” */
        public int iDSTRule;			///< 夏令时规则 
        public int iWorkDay;			///< 工作日
        public DSTPoint dDSTStart;
        public DSTPoint dDSTEnd;
    };
        /// 编码功能
    public enum SDK_EncodeFunctionTypes
    {
	    SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM,		///< 双码流功能
	    SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM,	///< 组合编码功能
	    SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM,		///< 抓图功能
	    SDK_ENCODE_FUNCTION_TYPE_WATER_MARK,		///< 水印功能
	    SDK_ENCODE_FUNCTION_TYPE_NR,
    };
    public enum SDK_AlarmFucntionTypes
    {
	    SDK_ALARM_FUNCTION_TYPE_MOTION_DETECT,	///< 动态检测
	    SDK_ALARM_FUNCTION_TYPE_BLIND_DETECT,	///< 视屏遮挡
	    SDK_ALARM_FUNCTION_TYPE_LOSS_DETECT,	///< 视屏丢失
	    SDK_ALARM_FUNCTION_TYPE_LOCAL_ALARM,	///< 本地报警
	    SDK_ALARM_FUNCTION_TYPE_NET_ALARM,		///< 网络报警
	    SDK_ALARM_FUNCTION_TYPE_IP_CONFLICT,	///< IP地址冲突
	    SDK_ALARM_FUNCTION_TYPE_NET_ABORT,		///< 网络异常
	    SDK_ALARM_FUNCTION_TYPE_STORAGE_NOTEXIST,	///< 存储设备不存在
	    SDK_ALARM_FUNCTION_TYPE_STORAGE_LOWSPACE,	///< 存储设备容量不足
	    SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE,	///< 存储设备访问失败
	    SDK_ALARM_FUNCTION_TYPE_VIDEOANALYSE,///<视频分析
	    SDK_ALARM_FUNCTION_TYPE_NET_ABORT_EXTEND,	//网络异常扩展
	    SDK_ALARM_FUNCTION_TYPE_NR
    };
        /// 网络服务功能
    public enum SDK_NetServerTypes
    {
	    SDK_NET_SERVER_TYPES_IPFILTER,		///< 白黑名单
	    SDK_NET_SERVER_TYPES_DHCP,			///< DHCP功能
	    SDK_NET_SERVER_TYPES_DDNS,			///< DDNS功能
	    SDK_NET_SERVER_TYPES_EMAIL,			///< Email功能
	    SDK_NET_SERVER_TYPES_MULTICAST,		///< 多播功能
	    SDK_NET_SERVER_TYPES_NTP,			///< NTP功能
	    SDK_NET_SERVER_TYPES_PPPOE,
	    SDK_NET_SERVER_TYPES_DNS,
	    SDK_NET_SERVER_TYPES_ARSP,			///< 主动注册服务
	    SDK_NET_SERVER_TYPES_3G,            ///< 3G拨号
	    SDK_NET_SERVER_TYPES_MOBILE=10,        ///< 手机监控
	    SDK_NET_SERVER_TYPES_UPNP,			    ///< UPNP
	    SDK_NET_SERVER_TYPES_FTP,			    ///< FTP
	    SDK_NET_SERVER_TYPES_WIFI,          ///<WIFI
	    SDK_NET_SERVER_TYPES_ALARM_CENTER,  ///< 告警中心
	    SDK_NET_SERVER_TYPES_NETPLAT_MEGA,  ///< 互信互通
	    SDK_NET_SERVER_TYPES_NETPLAT_XINWANG,  ///< 星望
	    SDK_NET_SERVER_TYPES_NETPLAT_SHISOU,  ///< 视搜
	    SDK_NET_SERVER_TYPES_NETPLAT_VVEYE,  ///< 威威眼
	    SDK_NET_SERVER_TYPES_RTSP,     //RTSP
	    SDK_NET_SERVER_TYPES_PHONEMSG=20,     //手机信息发送配置
	    SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG,     //手机信息发送配置
	    SDK_NET_SERVER_TYPES_DAS,          //主动注册
	    SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM,          //网络平台信息设置
	    SDK_NET_SERVER_TYPES_GOD_EYE,///<神眼接警中心系统
	    SDK_NET_SERVER_TYPES_NAT,		///NAT穿透，MTU配置
	    SDK_NET_SERVER_TYPES_VPN,     ///VPN
	    SDK_NET_SERVER_TYPES_NET_KEYBOARD,	///网络键盘配置
	    SDK_NET_SERVER_TYPES_SPVMN,		///28181协议配置
	    SDK_NET_SERVER_TYPES_PMS,      //手机服务
	    SDK_NET_SERVER_TYPE_KAICONG,		///凯聪配置
	    SDK_NET_SERVER_TYPE_PROTOCOL_MAC,///支持MAC协议
	    SDK_NET_SERVER_TYPE_XMHEARTBEAT, //雄迈心跳
	    SDK_NET_SERVER_TYPES_MONITOR_PLATFORM, //神州数码监控平台
	    SDK_NET_SERVER_TYPES_ANJUP2P,			//
	    SDK_NET_SERVER_TYPES_NR,   
    };
    ///串口类型
    public enum SDK_CommTypes
    {
	    SDK_COMM_TYPES_RS485,			///<485串口
	    SDK_COMM_TYPES_RS232,			///<232串口
	    SDK_COMM_TYPES_NR
    };
    //输入法限制
    public enum SDK_InPutMethod
    {
	    SDK_NO_SUPPORT_CHINESE,		//不支持中文输入
	    SDK_NO_SUPPORT_NR
    };
    //报警中标签显示
    public enum SDK_TipShow
    {
	    SDK_NO_BEEP_TIP_SHOW,  //蜂鸣提示
	    SDK_NO_FTP_TIP_SHOW,  //FTP提示
	    SDK_NO_EMAIL_TIP_SHOW,  //EMAIL提示
	    SDK_NO_TIP_SHOW_NR
    };
    /// 预览功能
    public enum SDK_PreviewTypes
    {
	    SDK_PREVIEW_TYPES_TOUR,		///< 轮巡
	    SDK_PREVIEW_TYPES_TALK,		///< GUI界面配置
	    SDK_PREVIEW_TYPES_NR
    };

    ///车载功能
    public enum SDK_MobileCar
    {
	    SDK_MOBILEDVR_STATUS_EXCHANGE,
	    SDK_MOBILEDVR_DELAY_SET,
	    SDK_MOBILEDVR_CARPLATE_SET,
	    SDK_MOBILEDVR_GPS_TIMING,
	    SDK_MOBILEDVR_NR
    };
    ///其他功能
    public enum SDK_OtherFunction
    {
	    SDK_OTHER_DOWNLOADPAUSE,		//录像下载暂停功能
	    SDK_OTHER_USB_SUPPORT_RECORD,	//USB支持录像功能
	    SDK_OTHER_SD_SUPPORT_RECORD,		//SD支持录像功能
	    SDK_OTHER_ONVIF_CLIENT_SUPPORT,	//是否支持ONVIF客户端
	    SDK_OTHER_NET_LOCALSEARCH_SUPPORT,	//是否支持远程搜索
	    SDK_OTHER_MAXPLAYBACK_SUPPORT, //是否支持最大回放通道数显示
	    SDK_OTHER_NVR_SUPPORT, //是否是专业NVR
	    SDK_OTHER_C7_PLATFORM_SUPPORT,//支持C7平台
	    SDK_OTHER_MAIL_TEST_SUPPORT,		//支持邮件测试
	    SDK_OTHER_SHOW_OSD_INFO,            //支持显示3行OSD信息
	    SDK_OTHER_HIDE_DIGITAL, //通道模式屏蔽功能	
	    SDK_OTHER_ACUTANCE_HORIZONTAL,	//锐度
	    SDK_OTHER_ACUTANCE_VERTIAL,
	    SDK_OTHER_BROAD_TRENDS,		//宽动态功能
	    SDK_OTHER_NO_TALK,		//对讲能力
	    SDK_OTHER_ALTER_DIGITAL_NAME,	//修改数字通道名称
	    SDK_OTHER_SHOW_CONNECT_STATUS,      //支持显示wifi 3G 主动注册等的连接状态
	    SDK_OTHER_SUPPORT_ECACT_SEEK,	//支持回放精准定位
	    SDK_OTHER_UPLOAD_TITLEANDSTATE,		//通道标题和数字通道状态上传能力集
	    SDK_OTHER_NO_HDD_RECORD,		//无硬盘录像
	    SDK_OTHER_NR
    };
    ///支持的系统功能
    [StructLayout(LayoutKind.Sequential)]
    public struct SDK_SystemFunction
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_EncodeFunctionTypes.SDK_ENCODE_FUNCTION_TYPE_NR)]
        public byte[] vEncodeFunction;	///< 编码功能SDK_EncodeFunctionTypes
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_AlarmFucntionTypes.SDK_ALARM_FUNCTION_TYPE_NR)]
        public byte[] vAlarmFunction;		///< 报警功能AlarmFucntionTypes
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_NetServerTypes.SDK_NET_SERVER_TYPES_NR)]
        public byte[] vNetServerFunction;	///< 网络服务功能NetServerTypes
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_PreviewTypes.SDK_PREVIEW_TYPES_NR)]
        public byte[] vPreviewFunction;		///< 预览功能PreviewTypes
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_CommTypes.SDK_COMM_TYPES_NR)]
        public byte[] vCommFunction;			///<串口类型SDK_CommTypes
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_InPutMethod.SDK_NO_SUPPORT_NR)]
        public byte[] vInputMethodFunction;  //<输入法限制SDK_InPutMethod>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_TipShow.SDK_NO_TIP_SHOW_NR)]
        public byte[] vTipShowFunction;               //报警标签显示SDK_TipShow>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_MobileCar.SDK_MOBILEDVR_NR)]
        public byte[] vMobileCarFunction;//车载功能
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)SDK_OtherFunction.SDK_OTHER_NR)]
        public byte[] vOtherFunction;				//其他功能OtherFunction
    };

    public struct SDK_NetWifiDevice
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 36)]
	    public string sSSID;            //SSID Number
	    public int nRSSI;                 //SEE SDK_RSSI_SINGNAL
	    public int nChannel;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
	    public string sNetType;         //Infra, Adhoc
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
	    public string sEncrypType;      //NONE, WEP, TKIP, AES
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
	    public string sAuth;            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
    };
   
    public struct SDK_NetWifiDeviceAll
    {
	    public int nDevNumber;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]  ///NET_MAX_AP_NUMBER=32
	    public SDK_NetWifiDevice[] vNetWifiDeviceAll;
    };
    
    ///< WIFI设置
    public struct SDK_NetWifiConfig
    {
	    public byte bEnable;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 36)]
	    public string sSSID;            //SSID Number
	    public int nChannel;                   //channel
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
	    public string sNetType;         //Infra, Adhoc
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
	    public string sEncrypType;      //NONE, WEP, TKIP, AES
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
	    public string sAuth;            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
	    public int  nKeyType;                  //0:Hex 1:ASCII
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)] ///NET_IW_ENCODING_TOKEN_MAX = 128
	    public string sKeys;
	    public CONFIG_IPAddress HostIP;		///< host ip
	    public CONFIG_IPAddress Submask;		///< netmask
	    public CONFIG_IPAddress Gateway;		///< gateway
    };

    public struct SDK_NetDHCPConfig
    {
	    public byte bEnable;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
	    public string ifName;
    };
    /// 所有网卡的DHCP配置
    public struct SDK_NetDHCPConfigAll
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
	    public SDK_NetDHCPConfig[] vNetDHCPConfig;
    };
    class XMSDK
    {
        
        public delegate void fDisConnect(int lLoginID, string pchDVRIP, int nDVRPort, IntPtr dwUser);
        public delegate bool fMessCallBack(int lLoginID, string pBuf, uint dwBufLen, IntPtr dwUser);
        public delegate void fTransComCallBack(int lLoginID, int lTransComType, StringBuilder pBuffer, uint dwBufSize, uint dwUser);
        public delegate void fDownLoadPosCallBack(int lPlayHandle, int lTotalSize, int lDownLoadSize, int dwUser);
       public delegate void fPlayDrawCallBack(int lPlayHand, IntPtr hDc, uint nUser);
        public delegate void fLocalPlayFileCallBack(uint lPlayHand, uint nUser);
        public delegate void InfoFramCallBack(int lPlayHand, uint nType, string pBuf, uint nSize, uint nUser);
        public delegate int fRealDataCallBack_V2(int lRealHandle,ref PACKET_INFO_EX pFrame, int dwUser);
        public delegate int fRealDataCallBack(int lRealHandle, int dwDataType, string strBuf,int lbufsize,int dwUser);

        [DllImport("NetSdk.dll")]
        public static extern void H264_DVR_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, IntPtr lUser);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_Init(fDisConnect cbDisConnect, IntPtr dwUser);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_SetConnectTime(int nWaitTime, int nTryTimes);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_Cleanup();

        [DllImport("NetSdk.dll")]
        public static extern Int32 H264_DVR_Login(string sDVRIP, ushort wDVRPort, string sUserName, string sPassword,
                              out H264_DVR_DEVICEINFO lpDeviceInfo, out int error, SocketStyle socketstyle);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_GetLastError();

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_SetupAlarmChan(long lLoginID);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_ClickKey(int lLoginID, ref SDK_NetKeyBoardData pKeyBoardData);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_SendNetAlarmMsg(int lLoginID, ref SDK_NetAlarmInfo pAlarmInfo);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_GetDevConfig(int lLoginID, uint dwCommand, int nChannelNO, IntPtr bufptr, uint dwOutBufferSize, out uint lpBytesReturned, int waittime);
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_SetDevConfig(int lLoginID, uint dwCommand, int nChannelNO, IntPtr bufptr, uint dwInBufferSize, int waittime);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_StopLocalRecord(int lRealHandle);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_StartLocalRecord(int lRealHandle, string szSaveFileName, int type);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_OpenSound(int lHandle);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_LocalSetColor(int lHandle, UInt32 nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_LocalGetColor(int lHandle, UInt32 nRegionNum, out int pBrightness, out int pContrast, out int pSaturation, out int pHue);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_MakeKeyFrame(int lLoginID, int nChannel, int nStream);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_StopRealPlay(int lLoginID, uint dwUser);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_CloseSound(int lHandle);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_RealPlay(int lLoginID, ref H264_DVR_CLIENTINFO lpClientInfo);
  
        [DllImport("NetSdk.dll")]
        public static extern Int32 H264_DVR_Login(StringBuilder sDVRIP, ushort wDVRPort, StringBuilder sUserName, StringBuilder sPassword,
                              out H264_DVR_DEVICEINFO lpDeviceInfo, out short error, SocketStyle socketstyle);
        [DllImport("NetSdk.dll")]
        public static extern Int32 H264_DVR_Logout(int lLoginID);//登出设备
        [DllImport("NetSdk.dll")]
        public static extern void DisConnectBackCallFunc(Int32 lLoginID, IntPtr pchDVRIP, ushort nDVRPort, uint dwUser);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_OpenTransComChannel(Int32 lLoginID, ref TransComChannel TransInfo, fTransComCallBack cbTransCom, IntPtr dwUser);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_CloseTransComChannel(Int32 lLoginID, SERIAL_TYPE nType);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_SerialWrite(Int32 lLoginID, SERIAL_TYPE nType, string Buffer, int nBufLen);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_StartLocalVoiceCom(int lLoginID);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_StopVoiceCom(int lVoiceHandle);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_GetDDNSInfo(ref SearchMode searchmode, out DDNS_INFO[] pDevicInfo, int maxDeviceNum, out int nretNum);

        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_SetupAlarmChan(int lLoginID);
         
        // 播放本地文件
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_StartLocalPlay(string pFileName, IntPtr hWnd, fPlayDrawCallBack drawCallBack,uint user);

        //关闭本地文件
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_StopLocalPlay(int lPlayHandle);

        //获取播放位置用于回放，和本地播放
        [DllImport("NetSdk.dll")]
        public static extern float  H264_DVR_GetPlayPos(int lPlayHandle);
        //设置播放位置（百分比）用于回放，和本地播放
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_SetPlayPos(int lPlayHandle, float fRelativPos);
        //播放控制（播放，停止，恢复，快发，慢放）
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_LocalPlayCtrl(int lPlayHandle, SDK_LoalPlayAction action, uint lCtrlValue);
        //设置播放结束回调
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_SetFileEndCallBack(int lPlayHandle, fLocalPlayFileCallBack callBack, IntPtr user);
        //设置信息帧回调
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_SetInfoFrameCallBack(int lPlayHandle, InfoFramCallBack callback, uint user);

        //录像查询
        //lLoginID		登陆句柄
        //lpFindInfo	查询条件
        //lpFileData	查找到的录像数据，外部开内存
        //lMaxCount		最大录像数目
        //findcount		查找到的录像数目
        //waittime		查询超时时间
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_FindFile(int lLoginID, ref H264_DVR_FINDINFO lpFindInfo, IntPtr ptr, int lMaxCount, out int findcount, int waittime);
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_GetFileByName(int lLoginID, ref H264_DVR_FILE_DATA sPlayBackFile,string sSavedFileName, 
											fDownLoadPosCallBack cbDownLoadPos , int dwDataUser , fRealDataCallBack fDownLoadDataCallBack);
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_GetFileByTime(int lLoginID, ref H264_DVR_FINDINFO lpFindInfo, string sSavedFileDIR, bool bMerge,
											fDownLoadPosCallBack cbDownLoadPos , int dwDataUser, fRealDataCallBack fDownLoadDataCallBack );
        [DllImport("NetSdk.dll")]
         public static extern int H264_DVR_PlayBackByName_V2(int lLoginID,ref H264_DVR_FILE_DATA sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_V2 fDownLoadDataCallBack, int dwDataUser);
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_PlayBackByTimeEx(int lLoginID, ref H264_DVR_FINDINFO lpFindInfo,fRealDataCallBack fDownLoadDataCallBack, int dwDataUser,
											fDownLoadPosCallBack cbDownLoadPos, int dwPosUser);
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_PlayBackControl(int lPlayHandle, int lControlCode,int lCtrlValue);
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_StopGetFile(int lFileHandle);
           
        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_StopPlayBack(int lPlayHandle);
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_GetDownloadPos(int lFileHandle);

         [DllImport("NetSdk.dll")]
        //抓本地图片 //预览，回放，本地播放 一个函数
        public static extern bool H264_DVR_LocalCatchPic(int lHandle, string strPath);

        [DllImport("NetSdk.dll")]
        public static extern bool H264_DVR_PTZControl(int lLoginID,int nChannelNo, int lPTZCommand, bool bStop, long lSpeed);

    }

}
