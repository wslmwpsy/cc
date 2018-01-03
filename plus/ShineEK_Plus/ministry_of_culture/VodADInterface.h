#ifndef _VODADINTERFACE_H_
#define _VODADINTERFACE_H_

#include "..\\stdafx.h"

//显示设备宏定义
#define DISPLAY_DEVICE_TV    1  //TV 终端
#define DISPLAY_DEVICE_PC    2  //pc终端
//场景及其广告类型定义
#define SCENE_POWER_ON       1  //开机广告
#define SCENE_INTER_MODE     2  //插播
#define AD_TYPE_CAPTION      3  //文字
#define AD_TYPE_LOGO         4  //LOGO
#define AD_TYPE_HELP_MODE    5  //提示信息框
#define AD_TYPE_BACK_MODE    6  //背景
#define AD_TYPE_SAFE_MODE    7  //屏保

//节目源类型
#define AD_TYPE_VIDEO        1  //视频
#define AD_TYPE_PICTURE      2  //图片
//#define AD_TYPE_CAPTION      3  //文字
//#define AD_TYPE_LOGO         4  //LOGO
//#define AD_TYPE_HELP_MODE    5  //提示信息框

//插播的时间段
#define SCENE_INTER_HASSONG    1 //有客人点歌的状态下
#define SCENE_INTER_IDLE       2 //空闲状态下

typedef struct AD_IIEM_FLAG_C
{
	unsigned int nTypename_id;  //节目源类型编号	
	char szCode_id[16];         //节目源编号
	unsigned int nLength;       //文件长度
	unsigned int nTime_len;     //时长
	char szRemark[256];         //备注
	char szFilePath[256];       //file Path
	char szType_code[8];        //类型编号
	int nSwitch_time;           //间隔时间
	int nDisp_time;             //显示时间
}AD_ITEM_CULTURE;


/*
功能：初始化广告系统，必须第一个调用。
参数：
返回值：
成功：1；
失败：-1;
*/
extern "C" long __stdcall InitADSystem_culture();

/*
功能：通知广告系统释放所有分配的资源，在点歌系统退出前调用一次
参数：
返回值：
成功：1；
失败：-1;
*/
//int UninitADSystem();
extern "C" long __stdcall UninitADSystem_culture();

/*
功能：点歌系统调用此接口获取一个广告项
参数：
nDisplayDevice:显示设备。电视终端:1  点播终端:2
nSceneADType：场景或广告播放类型。开机广告：1 插播：2 文字：3 Logo：4 提示信息框：5 背景：6 屏保：7
pItem：指向保存广告项信息的缓冲区。
nInterTime：只有在插播模式下才启作用。1：有客人点歌的状态下；2：空闲时间段

返回值：
成功：1 （如果参数pItem==NULL,返回值是结构体AD_ITEM占的缓冲区的大小，按字节计算）
失败：-1
没有广告播放：0
*/
extern "C" long __stdcall get_ADItem_culture(long nDisplayDevice,long nSceneADType,AD_ITEM_CULTURE** pItem,int nInterTime);

#endif