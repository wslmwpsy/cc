#pragma once

//错误码
#define LOCK_OK                   0        //成功
#define LOCK_CREATE_SOCK_FAIL     11       //创建socket失败
#define LOCK_NO_SERVER_IP         12       //接收不到服务器IP
#define LOCK_CONNECT_SERVER_FAIL  13       //连接服务器失败
#define LOCK_SEND_FAIL            14       //发送数据失败
#define LOCK_RECV_FAIL            15       //接收数据失败
#define LOCK_RECV_HEART_BEAT_FAIL 16       //接收服务器心跳失败
#define LOCK_PARA_FLAG_ERROR      18       //输入的参数flag错误

#define LOCK_MODULE_NUM_ERR         50      //模块编号不存在或错误
#define LOCK_MODULE_COUNT_LESS      51      //模块点数不够
#define LOCK_OPEN_FAIL              52      //加密锁打开失败，即找不到加密锁
#define LOCK_USER_NUMBER_FAIL       53      //查找锁内客户编号失败
#define LOCK_NUMBER_SIGN_NO_EXIST   54      //锁编号签名文件不存在
#define LOCK_NUMBER_SIGN_ERR        55      //锁编号签名文件错误
#define LOCK_FUN_SIGN_NO_EXIST      56      //功能签名文件不存在
#define LOCK_FUN_SIGN_ERR           57      //功能签名文件错误
#define LOCK_TIME_EXPIRED           58      //加密锁过期

#define LOCK_UNKNOWN_ERR          111       //未知错误

//用户信息
typedef struct OUTLETS_DATA_STRU
{
	char UserPlaceName[40]; 						//用户场所名称
	char UserDisName[40];							//用户显示名称
	char UserAddress[80];							//用户地址
	char userReservePhone[40];						//用户订座电话
	char UserCity[16];								//用户所属城市	
}OUTLETS_DATA;

//代理商信息
typedef struct AGENT_DATA_STRU
{
	char AgentName[16];							//代理商名称
	char AgentAddress[80];							//代理商地址
	char AgentPhone[16];							//代理商电话
}AGENT_DATA;

//开发商信息
typedef struct ISP_DATA_STRU
{
	char DevelopersName[25];						//开发商名称
	char DevelopersPhone[16];						//开发商电话
	char DevelopersAddress[80];					//开发商地址
}ISP_DATA;


/*******************************************************
函数名称：lock_init
函数说明：初始化基本信息以及建立接收服务器数据的线程
参数：
    void
返回值：
   0 - 成功
   !0 - 失败
********************************************************/
extern "C" int lock_init(void);

/*******************************************************
函数名称：lock_connect_server
函数说明：连接服务器，建立长连接。建议初始化之后3秒在连接
参数：
    void
返回值：
   0 - 成功
   !0 - 失败
********************************************************/
extern "C" int lock_connect_server(void);

/*******************************************************
函数名称：lock_login_check
函数说明：检查该模块是否可用，同时返回剩余时间
参数：
    module_number[in]:模块编号
	valid_time[out]:到期剩余时间，单位：秒
返回值：
   0 - 成功
   !0 - 失败
********************************************************/
extern "C" int lock_login_check(IN int module_number, OUT long *valid_time);

/*******************************************************
函数名称：lock_get_data
函数说明：得到客户、代理商、开发商、辅助功能、加密格式等信息
参数：
    flag[in]:需要获取的信息标示 
	        0----获取客户信息
	        1----获取代理商信息
	        2----获取开发商信息
	        3----获取辅助功能信息
	        4----获取加密模式
	        5----获取系统功能
			6----获取预留区域
			7----获取锁的客户编号
	buffer[out]:用于接收数据的内存地址，结构体方式
	buf_size[in]：接收数据的内存字节数
返回值：
   0 - 成功
   !0 - 失败
********************************************************/
extern "C" int lock_get_data(IN int flag, OUT void *buffer, IN int buf_size);

/*******************************************************
函数名称：lock_common_check
函数说明：定期检查加密是否存在
参数：
    void
返回值：
   0 - 成功
   !0 - 失败
********************************************************/
extern "C" int lock_common_check(void);

/*******************************************************
函数名称：lock_uninit
函数说明：反初始化，终止线程和释放资源
参数：
    void
返回值：
   0 - 成功
   !0 - 失败
********************************************************/
extern "C" int lock_uninit(void);

/*******************************************************
函数名称：lock_get_server_ip
函数说明：得到服务器IP
参数：
    server_ip：服务器IP
	size：参数内存大小
返回值：
   0 - 成功
   !0 - 失败
********************************************************/
extern "C" int lock_get_server_ip(char *server_ip, int size);


//授权点歌系统辅助功能控制 - AidFun
#define AF_MOBILE_VOD		   	0x00000001 				//移动点歌功能
#define AF_LIVE_SCORE         	0x00000002 				//演唱评分功能
#define AF_LEADSING_AP         	0x00000004 				//导唱伴奏功能
#define AF_INTEGRATE_WEICO    	0x00000008 				//集成微博功能
#define AF_INTERACTIVE_GAMES  	0x00000010 				//互动游戏功能
#define AF_VIDEO_INTERACTIVE  	0x00000020 				//视频互动功能
#define AF_VOD         			0x00000040 				//影视点播功能
#define AF_EM_DRINK         	0x00000080  			//内嵌酒水功能
#define AF_ROOM_CONTROL      	0x00000100 				//开关房控制
#define RF_1					0x00000200              //10挑战麦霸
#define RF_2					0x00000400              //发现麦霸
#define RF_3					0x00000800
#define RF_4					0x00001000
#define RF_5					0x00002000
#define RF_6					0x00004000
#define RF_7					0x00008000
#define RF_8					0x00010000
#define RF_9					0x00020000
#define RF_10					0x00040000
#define RF_11					0x00080000
#define RF_12					0x00100000
#define RF_13					0x00200000
#define RF_14					0x00400000
#define RF_15					0x00800000
#define RF_16					0x01000000
#define RF_17					0x02000000
#define RF_18					0x04000000
#define RF_19					0x08000000
#define RF_20					0x10000000