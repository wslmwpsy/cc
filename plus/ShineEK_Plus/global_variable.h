#ifndef _GLOBAL_VARIABLE_H_
#define _GLOBAL_VARIABLE_H_

#include "ministry_of_culture/ccddt.h"
#include "ministry_of_culture/VodADInterface.h"
#include "common/init_socket.h"
#include "dog/watch_dog.h"
#include "message.h"
#include "PluginsEx.h"

//初始化socket
CInitSocket g_init_socket;


//dog
watch_dog m_watch_dog;                           //加密狗类
long dog_valid_time=0;                           //加密狗的有效期
const double check_dog_time_interval=1200.0;     //检测加密狗的时间间隔
const int DOG_SERVER_PORT=7077;                  //狗服务使用的端口号
const long DOG_SERVER_SOCKET_TIME_OUT=1000000;   //狗服务的连接超时
const int DOG_SERVER_MAX_ERROR_LINK_NUMBER=6;    //狗服务的最大错误连接数
const TCHAR SOFTWARE_MODULE_NUMBER[] = L"0010";  //软件的模块编号  0010
const TCHAR CONTROL_MODULE_NUMBER[] = L"1001";   //控件的模块编号
const TCHAR GAME_MODULE_NUMBER[] = L"5678";      //互动游戏的模块编号 5678
const TCHAR CULTURE_SOFTWARE_MODULE_NUMBER[]=L"9010"; //文化部的软件模块编号9010
const TCHAR SCORE_MODULE_NUMBER[] = L"5666";     //评分模块编号


DOG_FUNCTION g_dog_open_function; //加密狗打开的功能
USER_INFOR user_infor;            //用户信息
SELL_INFOR sell_infor;            //销售信息
TCHAR g_dog_serial_num[16] = {0x00}; //加密狗序列号

//前置机的变量
enum PRECOMPUTER_SEND_TYPE
{
	VIDEO_TYPE,     //视频信息
	PC_TEXT_TYPE,   //点播终端的文字
	TV_TEXT_TYPE,   //电视终端的文字
	PC_BK_TYPE,     //点播终端的背景广告
	PC_LOGO_TYPE,   //点播终端的logo
	TV_LOGO_TYPE,   //电视上的logo
	SCREEN_SAVER_TYPE,//屏保广告
	PROMPT_BOX_TYPE,  //信息提示框
};

struct forbidsong **forbid_song_list=NULL;     //禁止播放歌曲列表
bool send_video_play_recorder=false;           //发送视频点播记录
bool send_pc_text_play_recorder=false;         //发送点播终端的文字记录
bool send_tv_text_play_recorder=false;         //发送电视终端的文字记录
bool send_pc_BK_play_recorder=false;           //发送点播终端背景记录
bool send_pc_logo_play_recorder=false;         //发送点播终端logo记录
bool send_tv_logo_play_recorder=false;         //发送电视终端logo记录
bool send_screen_saver_play_recorder=false;    //发送屏保记录
bool send_prompt_box_play_recorder=false;      //发送信息提示框记录

//要发送给前置机的信息
//每个结构体代表的含义：
//0：视频信息
//1：点播终端的文字
//2：电视终端的文字
//3：点播终端的背景广告
//4：点播终端的logo
//5：电视上的logo
//6：屏保广告
//7：信息提示框
SEND_PRECOMPUTER_MSG send_precomputer_msg[8];  //要发送给前置机的信息
struct pwktvmsg *send_ktv_msg[8];              //要发送给前置机的播放信息

//culture  ad
bool play_culture_video_ad=false;                      //播放文化部的视频广告

AD_ITEM_CULTURE *culture_video_ad = NULL;              //文化部的视频广告
AD_ITEM_CULTURE *culture_pc_text_ad=NULL;              //文化部的点歌终端的文字广告
AD_ITEM_CULTURE *culture_tv_text_ad=NULL;              //文化部的电视终端的文字广告
AD_ITEM_CULTURE *culture_pc_background_ad=NULL;        //文化部的点播终端上的背景广告
AD_ITEM_CULTURE *culture_pc_logo_ad=NULL;              //文化部的点播终端上的logo广告
AD_ITEM_CULTURE *culture_tv_logo_ad=NULL;              //文化部的电视上的logo广告
AD_ITEM_CULTURE *culture_screen_saver_ad=NULL;         //文化部的屏保广告
AD_ITEM_CULTURE *culture_prompt_box_ad=NULL;           //文化部的提示信息框


HANDLE m_assistant_thread_event_handle=NULL;                            //用于线程结束的事件句柄

FLASH_USE_LANGUAGE g_flash_use_language;          //flash使用的语言
SEND_BACK_SERVER_MSG_TYPE g_back_server_msg_type; //发送给后台服务器的消息类型

typedef std::map<CString, song_info> STRING_SONGINFO_MAP; //定义map，key：string val：song_info-------By_v.cai_2015/02/15 09:16

#endif