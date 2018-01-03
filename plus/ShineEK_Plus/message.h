#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <map>
using namespace std;

//子窗口的ID
enum CHILD_WINDOW_ID
{
	FLASH_PLAYER_WINDOW_ID = 10001, //flash播放器窗口ID
	SUB_FLASH_PLAYER_WINDOW_ID,     //子flash播放器窗口ID
	TEST_MACHINE_PLAYER_WINDOW_ID,  //游戏flash播放器窗口ID
	SCREEN_SHOW_WINDOW_ID,          //屏幕显示窗口ID
	SUB_SCREEN_SHOW_WINDOW_ID,      //屏幕显示窗口的子窗口ID
	LOBBY_LIVE_WINDOW_ID,           //直播窗口id
	PREVIEW_WINDOW_ID,              //预览窗口ID
	TV_WINDOW_ID,                   //电视直播窗口ID
	SOFT_DECODE_WINDOW_ID,          //软解窗口的ID
	HANDWRITING_OCX_ID,             //手写控件的ID
	HANDWRITING_WINDOW_ID,          //手写窗口的ID
	SURVEY_HANDWRITING_WINDOW_ID,   //调查手写窗口的ID
	SLAVE_WINDOW_FLASH_PLAYER_ID,   //被控视频窗口的flash播放器窗口ID
	SLAVE_VIDEO_WINDOW_ID,          //被控视频窗口ID
	GAME_FLASH_PLAYER_WINDOW_ID,    //互动游戏窗口ID
	WALL_PANEL_PLAYER_WINDOW_ID,    //墙面板flash播放器ID
	DOORPLATE_FLASH_PLAYER_WINDOW_ID,//门牌机窗口ID
	LOCAL_GAME_PLAYER_WINDOW_ID,     //本地游戏播放器窗口ID
	DRINKS_FLASH_PLAYER_WINDOW_ID,   //内嵌酒水flash播放器
	AUDIO_EFFECT_WINDOW_ID,          //音效窗口ID
	AD_FLASH_PLAYER_WINDOW_ID,       //广告窗口ID
	REBOOT_PLAYER_CONTROL_TIMER_EVENT_ID, //重启播放控件
	VIDEO_SCREEN_SHOW_WINDOW_ID,        //视频窗口ID
	MSQUARE_SCREEN_SHOW_WINDOW_ID,     //M平方的窗口
	SCORE_SOFT_FLASH_WINDOW_ID,		//软解屏上的分数flash
	SCORE_FLASH_WINDOW_ID,           //分数flash窗口ID
	RECORD_NOISE_TIMER_EVENT_ID,          //录制噪音文件定时ID
	HTML_CTRL_ID,					 //娱乐新闻窗口的ID
	VICE_SCREEN_PLAYER_ID,			 //副屏的ID
	INTER_SCREEN_PLAYER_ID,			//互动场景屏flash播放器ID
	MASTER_SHOW_WINDOW_ID,			//互动场景屏中主视频窗口
	SLAVE_SHOW_WINDOW_ID,			//互动场景屏中辅视频窗口
	ACTIVITY_VIDEO_WND_ID,			//互动场景屏中活动视频窗口
	SCREEN_FLASH_WND_ID,			//
	SCREEN_FLASH_PLAYER_ID,				//异形flash播放器
	ACROSS_PASS_PLAYER_ID,			//百秒夺奖flash播放器ID
	CHALLENGE_STAR_PLAYER_ID,		//挑战大咖flash播放器
	HTML_VIDEO_SHOW_ID,				 //视频秀场的html的ID
	LISTEN_PAGE_TV_ID,				 //听音识曲窗口ID
	PICTURE_MV_TV_ID,				//电视端
	ACTIVE_GAME_PLAYER_ID,			//互动游戏
	//软解flash
	ACROSS_PASS_SOFT_PLAYER_ID,			//百秒夺奖flash播放器ID
	CHALLENGE_STAR_SOFT_PLAYER_ID,		//挑战大咖flash播放器
	LISTEN_PAGE_TV_SOFT_ID,				 //听音识曲窗口ID
	PICTURE_MV_TV_SOFT_ID,				//电视端
	ACTIVE_GAME_SOFT_PLAYER_ID,			//互动游戏软解flash
	WECHAT_INTERACTION_SOFT_PLAYER_ID,	//微信互动-弹幕
	WECHAT_INTERACTION_PLAYER_ID,		//
	WECHAT_GIFT_SOFT_PLAYER_ID,			//微信互动-礼物（魔法表情）
	WECHAT_GIFT_PLAYER_ID,			//
};

//定时器的ID
enum TIMER_EVENT_ID
{
	SHOW_LOGO_TIMER_EVENT_ID=101,         //动画显示logo的定时器ID
	SHOW_CONTROL_OSD_TIMER_EVENT_ID,      //显示控制osd的定时器ID
	SHOW_BMP_PICTURE_TIMER_EVENT_ID,      //显示BMP图片的定时器ID
	SHOW_SCORE_TIMER_EVENT_ID,            //显示分数定时器ID
	SHOW_FLASH_TEXT_TIMER_EVENT_ID,       //在flash上显示滚动文字的定时器ID
	SHOW_TV_TEXT_TIMER_EVENT_ID,          //在电视上显示滚动文字的定时器ID
	SHOW_FLASH_BACKGROUND_TIMER_EVENT_ID, //更新flash背景图片的定时器ID
	SHOW_FLASH_LOGO_TIMER_EVENT_ID,       //在flash上显示logo的定时器ID
	SHOW_TV_LOGO_TIMER_EVENT_ID,          //在电视上显示logo的定时器ID
	SHOW_SCREEN_SAVER_TIMER_EVENT_ID,     //显示屏保的定时器ID
	COMMON_TIMER_EVENT_ID,                //公用定时器ID
	AUTO_TEST_TIMER_EVENT_ID,             //自动测试定时器ID
	HIDE_CHECT_WINDOW_TIMER_EVENT_ID,     //隐藏歌曲复选框定时器ID
	SHOW_POPUP_WINDOW_TIMER_EVENT_ID,     //显示弹出窗口的定时器ID
	SHOW_WALL_PANEL_IMAGE_TIMER_EVENT_ID, //显示墙面板图片的定时ID
	CHECK_FILE_TIMER_EVENT_ID,            //检测文件是否存在的定时器ID
	CHECK_MYSQL_TIMER_EVENT_ID,           //检查mysql的数据库
	CHECK_PK_CONNECT_TIMER_EVENT_ID,      //检查pk是否连接
	SHOW_PK_ACCEPT_WINDOW_TIMER_EVENT_ID, //是否隐藏pk邀请对话框
	REQUEST_HEAD_PICTURE_TIMER_EVENT_ID,          //定时请求头像数据
	SHOW_SCREEN_TO_FLASHS_TIME_EVENT_ID,
	GET_VICE_SCREEN_TO_FLASH_TIME_EVENT_ID, //副屏检测数据定时ID
	SHOW_MUSIC_ENJOY_LYRIC_TIME_EVENT_ID,					//显示平台音乐歌词
	SHOW_SCREEN_FLASH_TIMER_EVENT_ID,		//显示屏幕异形flash动画
	INTER_SCREEN_MAIBA_RULE_TIME_EVENT_ID,		//互动场景屏活动规则定时器
	INTER_SCREEN_MAIBA_SONG_LIST_TIME_EVENT_ID,	//互动场景屏活动信息定时器
	CLOSE_ROOM_TIME_SPACE_TIME_EVENT_ID,		//手动开房后自动关房的时间间隔定时器
	DESTROY_GIFT_WND_TIME_EVENT_ID,				
};

//快划方向
enum QUICK_SCROLL_DIRECTION
{
	QUICK_SCROLL_LEFT, //向左
	QUICK_SCROLL_RIGHT, //向右
};

//自定义的消息
enum DEFINE_MESSAGE
{
	DM_FLASH_INITIALIZATIONF_FINISH=WM_USER+10,   //flash界面初始化完成的消息
	DM_CHECK_DOG,                                 //检测狗的消息
	DM_CHECK_PRECOMPUTER,                         //检测前置的消息
	DM_SCREEN_SAVER_END,                          //屏保结束
	DM_BOX_COM_RECEIVE_MESSAGE,                   //中控盒串口接收到的消息
	DM_SCREEN_COM_RECEIVE_MESSAGE,                //触摸屏串口接受到的消息
	DM_SCREEN_VIDEO_CLICK,                        //屏幕视频单击
	DM_ADD_SING_SONG,                             //增加已唱歌曲到数据库中
	DM_INK_RECOGNITION_FINISH,                    //手写识别完成，可以得到结果
	DM_SUB_WINDOW_MESSAGE,                        //子窗口发送过来的消息
	DM_RECV_SERVER_DATA,                          //接受服务器开关房数据的消息
	DM_RECV_SERVER_MSG,                           //接收到服务器消息的消息
	DM_MASTER_SLAVE_MESSAGE,                      //主被控消息
	DM_WALL_PANEL_COM_RECEIVE_MESSAGE,            //墙面板触摸屏串口接受的消息
	DM_SAVE_SELECT_SONG_ID,                       //保存选择歌曲ID
	DM_SAVE_U_DISK_SONG,                          //保存U盘歌曲
	DM_DOORPLATE_ROOM_INFO,                       //门牌机的包房信息
	DM_DOORPLATE_COM_RECV_MESSAGE,                //门牌机串口接受消息
	DM_PLAY_SONG_TIP_MESSAGE,                     //播放歌曲提示的osd消息
	DM_MSQURE_WINDOW_CLICK_MESSAGE,                //M平方定制歌曲窗口信息
	DM_SHOW_WALL_PANEL_MESSAGE,                   //显示墙面版的消息      
	
	//特殊需求
	DM_FOOD_HANDLE_MSG=61204,                     //长春酒水，发送句柄的消息
	DM_REAL_DUMP_MESSAGE=61205,                   //真实的架子鼓消息

	WM_PlayStateChange = WM_USER + 5555,
	WM_MediaPositionChange = WM_USER + 5556,
	WM_MediaVolChange = WM_USER + 5557,
	WM_SoundSpectrumBegin = WM_USER + 5566, //频谱开始
	WM_SoundSpectrumData = WM_USER + 5565, //频谱数据
	WM_SoundSpectrumEnd = WM_USER + 5567, //频谱结束
	WM_MusicBeat = WM_USER + 5575, //节奏信息
	WM_PLAYER_HANDLE = 6824, //鼓点信息
	WM_NEED_PLAYER_FREDATA = 6825, //工具栏发送给主程序，是否需要频谱数据
};


enum DOG_MESSAGE
{
	CONNECT_DOG_FAIL,       //连接加密狗失败
	DOG_LOGIN_CHECK,        //加密狗过期
	TIMER_CHECK_DOG_FAIL,   //定期检测加密狗失败
	CHECK_DOG_SUCCESS,      //检测加密狗成功
	SOFTWARE_DOG_VALID_DAY_TIP,  //软件狗的有效天数提示
	CONTROL_DOG_VALID_DAY_TIP,   //控件狗的有效天数提示
};

//点歌终端所处的状态
enum PC_STATE
{
	SELECT_SONG_STATE,              //点歌状态
	CLOSE_ROOM_STATE,               //关房状态
};

//会员管理状态
enum MEMBER_MANAGE_STATE
{
	MEMBER_LOGIN_STATE=1,      //登录
	MEMBER_REGISTER_STATE=2,   //注册
	MEMBER_CHANGE_PSW_STATE=3, //修改密码状态
	MEMBER_REGISTER_PHONE=4,   //K友注册手机号
};

//电视的播放模式
enum TV_PLAY_MODE
{
	TV_SINGLY_PLAY_MODE=1,   //单播
	TV_GROUP_PLAY_MODE,      //组播

};

//播放的视频类型,必须从1开始，不要修改
enum PlAY_VIDEO_TYPE
{
	VIDEO_TYPE_SONG=1,        //歌曲
	VIDEO_TYPE_LOBBY_LIVE=2,  //大厅直播
	VIDEO_TYPE_TV=3,          //电视
	VIDEO_TYPE_PREVIEW_SONG=4,//预览歌曲
};

//预览播放控制
enum PLAY_CONTROL
{
	PLAY_CONTROL_PAGE_CLOSE=1,      //预览页面关闭
	PLAY_CONTROL_SONG_PRIORITY=2,   //预览优先
	PLAY_CONTROL_SONG_MEMBER=3,     //歌曲收藏
	PLAY_CONTROL_SONG_SELECT=4,     //点播歌曲
	PLAY_CONTROL_FAST_BACKWARD=5,   //快退
	PLAY_CONTROL_FAST_FORWARD=6,    //快进
};

//会员标志
enum MEMBER_FLAG
{
	MEMBER_FLAG_LOGIN_NO=0,    //没有登录
	MEMBER_FLAG_LOGIN,			//登录过
	MEMBER_FLAG_REGISTRATION,   //新注册的
	MEMBER_FLAG_ERROR,			//404 
	MEMBER_FLAG_LOGIN_ERROR,    //登录1 失败
	MEMBER_FLAG_PHONE_CODE_ERROR,//5 手机验证吗错误
	MEMBER_FLAG_PHONE_REGISTER,  //register12 手机号已注册
};

//flash界面使用的语言
enum FLASH_USE_LANGUAGE
{
	FLASH_LANGUAGE_SIMPLIFIED_CHINESE=0,   //简体
	FLASH_LANGUAGE_TRADITIONAL_CHINESE,    //繁体
	FLASH_LANGUAGE_ENGLISH,                //英文
	FLASH_LANGUAGE_KOREAN,                 //韩语
	FLASH_LANGUAGE_JAPANESE,               //日语
	FLASH_LANGUAGE_MONGOLIA,               //蒙语
};

//发送给后台的消息类型
enum SEND_BACK_SERVER_MSG_TYPE
{
	BACK_SERVER_MSG_TYPE_IP_NAME,      //发送IP和机器名给后台
	BACK_SERVER_MSG_TYPE_CLEAN,        //发送清房消息给后台
	BACK_SERVER_MSG_TYPE_REQUESTOPEN,  //发送请求开房消息给后台
};

//flash上滚动的欢迎词类型
enum FLASH_SCROLL_WELCOME_TYPE
{
	FLASH_WELCOME_TYPE_DOG,    //狗的欢迎词
	FLASH_WELCOME_TYPE_CLIENT, //客户的
	FLASH_WELCOME_TYPE_MSG,    //消息的
};

//flash上歌曲的显示方式
enum FLASH_SONG_SHOW_MODE
{
	SONG_SHOW_MODE_CARD,      //卡片方式显示歌曲
	SONG_SHOW_MODE_LIST,      //列表方式显示歌曲
};

//页操作
enum PAGE_OPERATE
{
	FIRST_PAGE_OPERATE=0, //第一页数据
	CUR_PAGE_OPERATE,     //当前页
	PRE_PAGE_OPERATE,     //向上翻页
	NEXT_PAGE_OPERATE,    //向下翻页
};

//歌星分类方式
enum SINGER_CLASS_MODE
{
	SINGER_CLASS_MODE_OLD,   //旧的方式
	SINGER_CLASS_MODE_NEW,   //新的方式
};

//墙面板显示方式
enum WALL_PANEL_SHOW_MODE
{
	WALL_PANEL_VIDEO_IMAGE=0,   //视频叠加图片
	WALL_PANEL_VIDEO_FLASH,   //视频叠加flash
	WALL_PANEL_IMAGE_FLASH,   //图片叠加flash
	WALL_PANEL_VIDEO,         //只显示视频
};

//界面类型
enum SCREEN_TYPE
{
	SCREEN_TYPE_HORIZON,   //横版
	SCREEN_TYPE_VERTICAL,  //竖版
};

//显示的音量条
enum VOLUMN_BAR_FLAG
{
	MUSIC_VOLUMN_BAR,   //音乐音量条
	MIC_VOLUMN_BAR,     //麦克音量条
};


//键盘类型
enum KEYBOARD_TYPE
{
	KEYBOARD_TYPE_CHINESE,   //中文键盘
	KEYBOARD_TYPE_KOREAN,    //韩文键盘
	KEYBOARD_TYPE_JAPANESE,  //日文键盘
};

enum WEIBO_SHOW_MODE
{
	WEIBO_SHOW_MODE_FULL_SCREEN_V=0,    //竖版全屏
	WEIBO_SHOW_MODE_LEFT,               //左边
	WEIBO_SHOW_MODE_TOP,                //上边
	WEIBO_SHOW_MODE_BOTTOM,             //下边
	WEIBO_SHOW_MODE_RIGHT,              //右边
	WEIBO_SHOW_MODE_FULL_SCREEN_H,      //横版全屏
};

enum SCORE_SYSTEM
{
	SCORE_SYSTEM_NONE=0,  //没有启用评分系统
	SCORE_SYSTEM_SHINE,   //阳光打分系统
	SCORE_SYSTEM_XUNFEI,  //讯飞打分系统
};

//麦霸相关歌曲的类型
enum REQUEST_SONG_TYPE
{
	REQUEST_NO = -1,	//没有请求
	MYRECORDSHARE,		//我的分享
	COUNTRYHOT,			//全国最火
	COUNTRYNEW,			//全国最新
	PLACEHOT,			//本场最火
	PLACENEW,			//本场最新
	MYCOLLECTION,		//我的收藏()
	FREEPK,				//自由pk
	AREAPK,				//擂台pk
	MYPRIVATESONG,       //私房歌曲
	RANKING_POLITE,		//上榜有礼
};

enum  OPERATE
{
	ENCRYPT,
	DECRYPT,
};

enum BUTTON_STATE
{
	GUID_BUTTON_STATE,  //导唱按钮状态
	SCORE_BUTTON_STATE, //评分按钮状态
	TAPE_BUTTON_STATE,  //录音按钮状态
	ENJOY_BUTTON_STATE, //欣赏按钮状态
	ROOM_BUTTON_STATE,  //开关房状态
	DJ_BUTTON_STATE,    //DJ开关状态
	MOVIE_BUTTON_STATE, //电影开关状态
	OPEN_SERVER_WINDOW,  //是否弹出服务对话框
	VIDEO_DATING_STATE, //视频交友按钮状态
	SHOW_CLOUD_SONG_STATE, //显示云加歌状态
};

enum MAIBA_TYPE
{
	MAIBA_SHARE,   //K歌分享
	MAIBA_FIND,		//发现麦霸
	MAIBA_DEKARON, //挑战麦霸 
	PRIVATE_SONG,  //私房歌曲
};

enum PK_HARDWARE_MODE
{
	PK_HARDWARE_MODE_SETBOX = 0,
	PK_HARDWARE_MODE_CAM,
};

//麦霸pk擂台的相关信息
typedef struct MAIBARULE
{
	TCHAR activity_type[5];			//参与类别(1:自由pk，2:擂台pk)
	TCHAR start_time[256];				//活动开始时间
	TCHAR end_time[256];				//活动开始时间
	TCHAR participation_type1[1024];		//参与方式1
	TCHAR participation_song[256];      //参与歌曲
	TCHAR participation_type2[1024];     //参与方式2
	TCHAR rating_methods[1024];          //评比方式
	TCHAR activities_award1[1024];		 //活动奖励1
	TCHAR activities_award2[1024];		 //活动奖励2
	TCHAR activities_award3[1024];		 //活动奖励3
	TCHAR activities_award4[1024];		 //活动奖励4
	TCHAR activities_award5[1024];		 //活动奖励5
}MAIBARULEINFO;

//灯控结构体
typedef struct LINGHT_CONTROL 
{
	unsigned int head_flag;  //头标识
	unsigned int order_content; //指令内容
	char order_param[10];  //指令参数
}LINGHT_CONTROL;

//定义的歌曲游戏结构
typedef struct SONG_GAME
{
	TCHAR name[256];      //名字
	TCHAR path[256];      //路径
	TCHAR song_number[128];//歌曲编号
}SONG_GAME_STRUCT;

typedef struct MAIBA_HEIGHT_RANKING
{
	TCHAR song_id[128];     //歌曲id录音id
	TCHAR song_name[64];   //歌曲名称   
	TCHAR singer_name[32];  //歌星名称 
	TCHAR score[8];         //分数
	TCHAR wave_path[128];		//路径
	TCHAR video_path[125];      
	TCHAR datetime[32];         //录音开始时间
	TCHAR voice_id[128];    //歌曲本身id
	TCHAR member_pic[256];  //会员的头像
	TCHAR nick_name[256];   //用户昵称
	TCHAR voice_code[256];
	TCHAR room_name[64]; //包房名
}MAIBA_HEIGHT_RANKING;


//麦霸歌曲相关信息   献花、收藏、场所id 都传userid
typedef struct MAIBA_SONG_INFO
{
	TCHAR song_id[256];      //歌曲id
	TCHAR song_name[256];   //歌曲名称
	TCHAR singer_name[256];  //歌星信息
	TCHAR song_score[10];   //歌曲分数
	TCHAR member_pic[256];   //会员头像
	TCHAR member_addr[256];  //头像地址(url)
	TCHAR member_pic_name[256];  //会员头像名称
	TCHAR listen_count[64];  //收听次数
	TCHAR flowers_count[64]; //献花次数
	TCHAR voice_id[256];     //歌曲唯一Id
	TCHAR user_id[256];      //用户id
	TCHAR recorder_video[256];  //歌曲的存储路径
	TCHAR song_down_addrss[256];  //歌曲下载地址
	TCHAR wave_path[256];         //录音文件路径
	TCHAR video_path[256];		//视频路径
	TCHAR nick_name[256];      //用户昵称
}MAIBA_SONG_INFO_STU;

//麦霸规则信息
typedef struct MAIBA_RULE_INFO
{   
	TCHAR activity_id[256];
	TCHAR song_id[256];
	TCHAR activity_type[256];
	TCHAR start_time[20];
	TCHAR end_time[20];
	TCHAR participation_type1[512];
	TCHAR participation_song[512];
	TCHAR participation_type2[512];
	TCHAR rating_methods[512];
	TCHAR activities_award1[512];
	TCHAR activities_award2[512];
	TCHAR activities_award3[512];
	TCHAR activities_award4[512];
	TCHAR activities_award5[512];
}MAIBA_RULE_INFO;

// 挑战大咖数据信息
typedef struct TAG_CHALLENGE_STAR_IFNO
{
	TCHAR record_song_id[128];     //歌曲id录音id
	TCHAR song_name[64];   //歌曲名称   
	TCHAR singer_name[32];  //歌星名称 
	TCHAR goal_score[8];			//目标分数
	TCHAR award[128];			//奖励
	TCHAR score[8];         //分数
	TCHAR wave_path[128];		//路径
	TCHAR video_path[125];      
	TCHAR datetime[32];         //录音开始时间
	TCHAR original_song_id[128];    //歌曲本身id
	TCHAR member_pic[256];  //会员的头像
	TCHAR nick_name[256];   //用户昵称
	TCHAR voice_code[256];
	TCHAR room_name[64]; //包房名
	int challenge_times;	//已挑战次数
	bool bUnable;			//true：不可挑战
}CHALLENGE_STAR_IFNO, *P_CHALLENGE_STAR_IFNO;

// 百秒夺奖数据
enum PASS_STATE
{
	UN_ACROSS = 0,	//未挑战
	READY_ACROSS,	//准备开始
	ACROSSING,		//正在挑战
	ACROSS_SUCCESS, //挑战成功
	ACROSS_FAIL,	//挑战失败
};
typedef struct TAG_HUNDRED_SECONDS_PRIZE_SONG
{
	TCHAR song_id[128];			//歌曲id
	TCHAR song_name[256];		//歌曲名称
	TCHAR singer_name[64];		//歌星名字

}HUNDRED_SECONDS_PRIZE_SONG, *P_HUNDRED_SECONDS_PRIZE_SONG;

//定义的推荐歌曲结构体
typedef struct SONG_RECOMMEND
{
	TCHAR song_id[256];  //歌星id
	TCHAR song_name[256];  //歌曲名字
	TCHAR singer_name[256];  //歌星姓名
}SONG_RECOMMEND_STRUCT;

//定义的结构体，用于存储发送给前置机的信息
typedef struct PRECOMPUTER_MESSAGE
{
	char song_id[128];
	char song_name[128];
	time_t start_time;
	unsigned long play_time;
	unsigned char song_type;
}SEND_PRECOMPUTER_MSG;

//结构体，用于存储加密狗打开的功能
// 狗功能字节
typedef struct DOGFUNCTION
{
	unsigned int Com1;    //音效    
	unsigned int Com2;    //音效   
	unsigned int MScreen; //触摸屏
	bool AD;               //广告
	unsigned int OSDSelect;	//OSD点歌
	bool preview;         //预览
	unsigned int Play;    //大厅
	unsigned int Word;    //歌词	
	unsigned int Mob;     //彩铃
	unsigned int KY;      //金永
	unsigned int Rec;     //录像
	bool game;            //游戏
	unsigned int MuCard;  //一机多卡
	unsigned int control; //主被控功能
	bool drinks_software; //后台功能
	unsigned int mouse;   //鼠标功能
	bool precomputer_check; //是否检测前置机
} DOG_FUNCTION;

typedef struct USERINFOR
{
	TCHAR Name[64];   // 客户名称
	TCHAR Tel[16];    //电话长度
	TCHAR Address[80];//用户所在地,
	TCHAR PostAdd[64];//联系方式
	TCHAR Display[64];//要显示的用户信息
} USER_INFOR;

typedef struct SELLINFOR
{
	TCHAR oTel[16]; //联系电话
	TCHAR No[16];   // 代理商编号
	TCHAR Name[64]; //代理商名称
	TCHAR Pesonal[16];//联系人
	TCHAR Tel[16];   //电话
	TCHAR Address[64];//联系方式

} SELL_INFOR;


typedef struct RECORDSONGINFO
{
	TCHAR SongID[128];          //歌曲ID
	TCHAR DateTime[128];        //录音时间
	TCHAR VoiceWavePath[256];   //人声音频文件
	TCHAR MusicWavePath[256];   //伴奏音频文件
	TCHAR mp3Path[256];         //mp3文件路径
	int   DurationTime;         //持续时间
}RECORD_SONG_INFO;

typedef struct SONGSHARESUCCESS
{
	TCHAR song_id[128];  //歌曲id
	TCHAR user_name[64]; //用户名称 
	TCHAR nick_name[64]; //用户昵称
	TCHAR member_pic[256]; //会员头像
	TCHAR voice_code[256]; //二维码分享码
}SONG_SHARE_SUCCESS;

typedef struct RECOMMAND_SONG_INFO
{   
	TCHAR song_id[256];               //歌曲id
	TCHAR song_name[256];             //歌区姓名
	TCHAR song_theme[256];            //歌曲主题
	TCHAR singer_id[256];             //歌星id
	TCHAR issue_year[256];            //发行年代
	TCHAR language[256];              //歌曲语言
	TCHAR singer_sex[256];            //歌星性别 
	TCHAR singer_name[256];           //歌星姓名 
}RECOMMAND_SONG_INFO;

//歌曲和歌星的基本信息
typedef struct ST_MUSIC_ENJOY{
	TCHAR song_id[MAX_PATH];
	TCHAR song_name[MAX_PATH];
	TCHAR singer_id[MAX_PATH];
	TCHAR singer_name[MAX_PATH];
	TCHAR song_cloud_path[MAX_PATH];
	TCHAR song_lyric_cloud_path[MAX_PATH];//歌词路径
	TCHAR song_bk_path[MAX_PATH];//背景视频路径
	int song_top;	//排行
	int song_type;	//平台

	ST_MUSIC_ENJOY(){
		memset(song_id, 0x00, MAX_PATH);
		memset(song_name, 0x00, MAX_PATH);
		memset(singer_id, 0x00, MAX_PATH);
		memset(singer_name, 0x00, MAX_PATH);
		memset(song_cloud_path, 0x00, MAX_PATH);
		memset(song_lyric_cloud_path, 0x00, MAX_PATH);
		memset(song_bk_path, 0x00, MAX_PATH);
		song_top = -1;
		song_type = -1;
	}
}ST_MUSIC_ENJOY;
//榜单歌曲信息
typedef struct Tag_Trend_List_Song_Info
{
	int   nIndex;				//当个榜单内索引（0-9）
	TCHAR szSongId[256];		//歌曲ID
	TCHAR szSongName[256];		//歌曲名称
	TCHAR szSingerId[256];		//歌星ID
	TCHAR szSingerName[256];	//歌星名字

	int song_top;
	int song_type;
}Trend_List_Song_Info,*PTREND_LIST_SONG_INFO;

/************************互动场景屏信息******************/
#define TCHAR_LEN		256
//滚动提示信息
typedef struct Tag_Scroll_Tip_Info
{
	TCHAR szNumber[16];			//显示编号
	bool bExist;				//是否创建
	bool bShow;					//是否显示
	int  nX;					//左上角X坐标
	int  nY;					//左上角Y坐标
	int  nWidth;				//宽度
	int  nHeight;				//高度
	TCHAR szInfo[TCHAR_LEN];	//信息
	TCHAR szPicPath[TCHAR_LEN];	//图片路径
}Scroll_Tip_Info, *PSCROLL_TIP_INFO;
//列表显示框信息
typedef struct Tag_List_Info
{
	TCHAR szNumber[16];			//显示编号
	bool bExist;				//是否创建
	bool bShow;					//是否显示
	int  nX;					//左上角X坐标
	int  nY;					//左上角Y坐标
	int  nWidth;				//宽度
	int  nHeight;				//高度
	TCHAR szInfo[TCHAR_LEN];	//信息
	TCHAR szPicPath[TCHAR_LEN];	//图片路径
}List_Info,*PLIST_INFO;
//(视频/游戏)窗口
typedef struct Tag_Wnd_Info
{
	TCHAR szNumber[16];			//显示编号
	bool bExist;				//是否创建
	bool bShow;					//是否显示
	int  nX;					//左上角X坐标
	int  nY;					//左上角Y坐标
	int  nWidth;				//宽度
	int  nHeight;				//高度
	TCHAR szInfo[TCHAR_LEN];	//信息
	TCHAR szPicPath[TCHAR_LEN];	//图片路径
}Wnd_Info,*PWND_INFO;
//互动场景屏信息
typedef struct Tag_Inter_Screen_Info
{
	int					n_mode;					//模式（1：单视频 2：双视频 3：单辅助视频）
	bool				b_exsit;				//
	int					n_show_activity_wnd;		//显示活动的窗口（0：主窗口显示活动（wnd_slave配置无效，固定101） 
												//				  1：辅窗口显示活动（wnd_master配置无效，固定101））
	bool				b_activity_wnd_full_screen;	//是否全屏显示活动窗口
	int					n_display_number;		//
	int					n_x;		//
	int					n_y;		//
	int					n_width;	//
	int					n_height;	//
	Tag_Scroll_Tip_Info	top_scroll_tip_info;	//上滚动条
	Tag_Scroll_Tip_Info	bottom_scroll_tip_info;	//下滚动条

	Tag_List_Info		left_list_info;			//左列表
	Tag_List_Info		right_list_info;		//右列表

	Tag_Wnd_Info		master_wnd_info;		//主窗口
	Tag_Wnd_Info		slave_wnd_info;			//辅窗口
}Inter_Screen_Info,*PINTER_SCREEN_INFO;
//互动场景屏字幕信息
typedef struct TAG_INTER_SCREEN_CAPTION
{
	TCHAR default_info[256];			//默认字幕
	TCHAR ad_info[256];					//广告字幕
	TCHAR activity_info[256];			//活动字幕
	TCHAR program_info[256];			//节目字幕
	TCHAR challenge_star_info[256];		//挑战大咖字幕
	TCHAR across_pass_info[256];		//百秒夺奖字幕
}INTER_SCREEN_CAPTION,*P_INTER_SCREEN_CAPTION;
/*******************************************************/


//视频秀场结构体
typedef struct st_video_show{
	TCHAR uid[MAX_PATH];
	TCHAR picpath[MAX_PATH];
	TCHAR title[1024*10];
	TCHAR toproomid[MAX_PATH];
	TCHAR roomid[MAX_PATH];
	TCHAR popularity[MAX_PATH];
	TCHAR showroomid[MAX_PATH];
	TCHAR channelname[MAX_PATH];
	st_video_show(){
		ZeroMemory(uid, MAX_PATH);
		ZeroMemory(picpath, MAX_PATH);
		ZeroMemory(title, 1024*10);
		ZeroMemory(toproomid, MAX_PATH);
		ZeroMemory(roomid, MAX_PATH);
		ZeroMemory(popularity, MAX_PATH);
		ZeroMemory(showroomid, MAX_PATH);
		ZeroMemory(channelname, MAX_PATH);
	}
}ST_VIDEO_SHOW;

struct FtpFile {
	const char *filename;
	FILE *stream;
};

#define INTER_GAME_PEOPLE_NUMBER			6				//互动游戏参与最大人数
// 互动游戏人员信息
typedef struct TAG_GAME_PLAYER_INFO
{
	TCHAR szOpenId[256];				//微信用户的唯一标识
	TCHAR szNickName[256];				//微信昵称
	TCHAR szHeadImgUrl[256];		//头像图片服务器路径
	TCHAR szHeadImgPath[256];		//头像图片本地路径
	bool bIsLaunch;					//是否是发起人
	bool bIsSelf;					//是否在摇骰子
	TCHAR szOpenTime[256];			//加入时间
}GAME_PLAYER_INFO,*P_GAME_PLAYER_INFO;

//弹幕传参，所使用的结构体
typedef struct tag_barrage_msg
{
	CWnd *pWnd;
	char szData[20480];
}BARRAGE_MSG, *LPBARRAGE_MSG;

//接收到iis的数据，转为info
typedef struct tag_barrage_info
{
	wstring strGUID;
	wstring strWechatNickName;	//微信昵称
	wstring strWechatHeadPath;	//头像路径
	wstring strWechatHeadName;	//微信头像名称
	wstring strContent;			//内容
	wstring strIp;				//来源IP
	wstring strColor;			//颜色
	int nSpeed;					//速度
	int nSize;					//字号
	int nCount;					//次数
	std::map<wstring,wstring> keyImageMap;//表情<名称，路径>
}BARRAGE_INFO, *LPBARRAGE_INFO;

//保存下载类型结构体
typedef struct tag_wechat_message{
	char guid[128];			//唯一索引
	char filename[128];		//文件名
	char openid[64];	//微信id
	char nickname[64];	//微信昵称
	long num;			//活动类型  8:动画消息 9:礼物（魔法表情）消息 13:照片推送消息
	long notice_type;	//通知消息类型 0:需要下载并显示礼物 1:有礼物过来了  2:下载失败
	char url[256];		//中转服务器的下载地址，即保存在中转服务器上地址
	char filepath[256];		//文件本地保存路径(对应filename)
	char portrait[256]; //微信头像
	char portraitpath[256];	//微信头像本地保存路径
	CWnd *pWnd;			//句柄
	tag_wechat_message()
	{
		memset(guid, 0x00, sizeof(guid));
		memset(filename, 0x00, sizeof(filename));
		memset(openid, 0x00, sizeof(openid));
		memset(nickname, 0x00, sizeof(nickname));
		num = -1;
		notice_type = -1;
		memset(url, 0x00, sizeof(url));
		memset(filepath, 0x00, sizeof(filepath));
		memset(portrait, 0x00, sizeof(portrait));
		memset(portraitpath, 0x00, sizeof(portraitpath));
	}
}WECHAT_MESSAGE, *LPWECHAT_MESSAGE;

typedef  struct tagDownProfile{
	unsigned int head;/*指令头0xaa55aa55*/
	unsigned int order;/*指令0x00000001*/
	long long int total;/*文件总大小*/
	long long int done;/*已经下载完成的*/
	int speed;/*下载速度*/
	char name[256];/*下载文件夹名称*/
} DOWNPROFILE;

typedef enum en_wechat_type{
	WECHAT_ANIMATION = 8,	//动画
	WECHAT_GIFT = 9,		//魔法表情
	WECHAT_PICTURE = 13		//照片推送
};

typedef enum en_wechat_return_type{
	WECHAT_RET_OK = 0,		//礼物已经准备好了，下载并展示
	WECHAT_RET_NOTICE = 1,	//有礼物通知，需要在电视上做提示
	WECHAT_RET_ERROR = 2	//礼物没有准备好，丢了，提示下载失败吧
};

//*******************************道奇电影开发
#define HEAD_FLAG 0xaa55aa55
//消息类型
typedef enum enMovieMsgType{
	//控制消息类型 使用此类型时，只能使用enMovieMsgContent mmc，mmc 内容有效, mssm内容无效。双向传送（点歌系统->电影系统 or 电影系统->点歌系统）。
	MMT_DIAITAL_MSG,
	//消息系统类型 使用此类型时，只能使用MOVIE_SHOW_SYSTEM_MSG mssm，mmc 内容无效, mssm内容有效。单向传送(点歌系统->电影系统)。
	MMT_CHARACTER_MSG
};
//控制消息内容
typedef enum enMovieMsgContent{
	MMCMSG_DEFAULT,			//默认消息 无效消息，只作为默认值
	MMCMSG_OPEN_ROOM,		//开房
	MMCMSG_CLOSE_ROOM,		//关房
	MMCMSG_SERIVCES,		//服务
	MMCMSG_SHOW,			//程序显示
	MMCMSG_HIDE,			//程序隐藏
	MMSMSG_LIGHT_OPEN,		//灯光全开
	MMSMSG_LIGHT_CLOSE,		//灯光全关
};
//消息系统内容
typedef struct tag_MovieShowSystemMsg{
	TCHAR szMsgType[16];		//公告、祝福词、寻人启事、结账预告、服务响应、火警、匪警
	TCHAR szShowMode[16];		//电视上显示、计算机上显示、同时显示
	TCHAR szContentType[16];	//文字、图片、视频、图片和文字、视频和文字
	TCHAR szTextColor[16];		//红色、黄色、蓝色、绿色、紫色、白色
	int iScrollCount;			//滚动次数
	TCHAR szContent[2048];		//消息系统消息内容
}MOVIE_SHOW_SYSTEM_MSG, *LPMOVIE_SHOW_SYSTEM_MSG;
//发送给电影的消息
typedef struct tag_MovieMsgControl
{
	unsigned int head;					//指令头0xaa55aa55
	enMovieMsgType mmt;					//消息类型
	enMovieMsgContent mmc;				//控制消息内容
	MOVIE_SHOW_SYSTEM_MSG mssm;			//消息系统内容
}MOVIE_MSG_CONTROL, *LPMOVIE_MSG_CONTROL;

typedef struct tag_FlashMovieMsg{
	CWnd *pWnd;
	MOVIE_MSG_CONTROL lpMMControl;
}FLASHMOVIEMSG, *LPFLASHMOVIEMSG;
////////////////////////////////////*/

#define RECORDER_AUDIO_MIN_FILE_SIZE        4*1204*1024   //录音文件可以回放的最小文件大小
#define MEMBER_MAX_SONG_COUNT               150           //会员最大允许保存的歌曲数
#define HANDWRITING_ASSOCIATION_WORD_COUNT  100           //手写联想字的个数
#define SURVEY_QUESTION_MAX_COUNT           10            //意见调查的最多数
#define SURVER_SUGGESTION_MAX_WORD_COUNT    100           //手写意见的最大字数
#define SLAVE_COMPUTER_MAX_COUNT            8             //被控机最大数
#define TV_CHANNEL_COUNT                    8             //电视频道数
#define SAMPLE_NUMBER_PER_READ              8192          //每次读取的采样数
#define MAX_MAIBA_PK_COUNT                  90            //麦霸pK的条数
#define MAIBA_RULE_COUNT                    6             //麦霸规则条数
#define MAIBA_HEIGHT_RANKING_LIST           48

const double PLAY_VIDEO_MIN_TIME_LENGTH = 3.0;            //播放视频的最小时间长度
const double AVOID_CUT_MIN_TIME_LENGTH  = 0.4;            //全局防止频繁切换的最小时间长度
const double PREVIEW_CONTROL_MIN_TIME_LENGTH = 2.0;       //预览控制的最小时间长度
const double UPLOAD_DB_TIME_INTERVAL    = 6666.0;         //上传数据库的时间间隔
const double LOAD_BALANCE_TIME_INTERVAL = 240.0;          //负载均衡的最小时间间隔

#define RECOMMAND_SONG_INFO_COUNT           10            //推荐歌曲的个数

#define SURVER_QUESTION_COUNT             5               //电子调查问题数
#define CUSTOM_SONG_COUNT                 11               //定制歌曲

#define MEMBER_LOGIN_COUNT                5				  //会员登录个数


//由于该版本没有，顾添加
#define DM_POSITION                      0x00000020L

//实时频谱的定义值
#define SPECTRUM_MAX_COUNT 120
#define SPECTRUM_MAX_VALUE 10000

#define UDP_PROGREES_RADIO			28010					/*UDP广播下载进度*/

#endif