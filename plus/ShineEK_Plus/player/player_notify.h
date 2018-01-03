#ifndef _INCLUDE_PLAYER_NOFITY_H
#define _INCLUDE_PLAYER_NOFITY_H


enum PLAYER_NOTIFY
{
	PN_MEDIA_OPENED_SUCCEED,	// 打开文件成功
	PN_MEDIA_OPENED_FAILED,		// 打开文件失败

	PN_MEDIA_PLAY_FROZEN,		// 播放卡死
	PN_MEDIA_PLAY_FINISHED,		// 文件播放完成

	PN_TV_AUTOTUNE_DONE = 200,	// 电视卡自动寻台完成, LPARAM = 有效台数

	PN_SRV_RESTARTED    = 300,	// 播放服务被重启
	PN_LYRIC_SCORE      = 400,	// 播放评分
	PN_LYRIC_SCORE_DONE = 401,	// 评分完成
	PN_LYRIC_SENTENCE   = 402,	// 评分文件句数
	PN_LYRIC_REALTIME_SCORE = 403,	// 实时评分
	PN_LYRIC_FIRST_SENTENCE = 404,	// 歌曲开始播放第一句, LPARAM = 当前播放进度(毫秒)

 	PN_SPECTRUM			= 500,	// 歌曲频谱信息, LPARAM = 频谱数据缓冲区指针(BYTE类型)
};

//
// 播放器通知消息, WPARAM = PLAYER_NOTIFY
//
#define WM_PLAYER_NOTIFY	(WM_APP + 132)

//
// 预览(大厅公播)通知消息, WPARAM = PLAYER_NOTIFY
//
#define WM_PREVIEW_NOTIFY	(WM_APP + 133)

//
// 电视卡通知消息, WPARAM = PLAYER_NOTIFY
//
#define WM_TVCARD_NOTIFY	(WM_APP + 134)

//
// OSD 对象播放完成通知消息
// WPARAM 低16 位= OSD 层序号
// LPARAM = LoadBmpFile / LoadText 返回的OSD 对象
//
#define WM_OSD_PLAY_DONE    (WM_APP + 135)

// 第二台电视播放核心( CSecondTV )通知消息
//
#define WM_SECTV_NOTIFY			(WM_APP + 262)

//
// 播放器当前状态
//
enum PlayerState
{
	PLAYER_STATE_ERROR	    = 0xFFFF,	// 格式错

	PLAYER_STATE_INIT	    = 0x0000,	// 初始状态

	PLAYER_STATE_PAUSED	    = 0x0001,	// 暂停
	PLAYER_STATE_STOPPED	= 0x0002,	// 播放完成停止
	PLAYER_STATE_PLAYING	= 0x0004,	// 正在播放
	PLAYER_STATE_SEEKING	= 0x0008,
	PLAYER_STATE_STEPPING	= 0x0010,
	PLAYER_STATE_CLOSED  	= 0x0020,	// 关闭

	PLAYER_STATE_OPENING    = 0x0040,   // 正在打开文件
	PLAYER_STATE_OPENED     = 0x0080,   // 打开文件完成
	PLAYER_STATE_WAITING	= 0x0100,	// 正在等待打开文件

	PLAYER_STATE_READY	= PLAYER_STATE_PAUSED | PLAYER_STATE_STOPPED,
};


//
// 播放核心控制代码( Get Set )
//
enum PCORE_CONTROL
{
	SDI_AUDIOCOUNTS        = 100,	// 音轨数量 (read only)

	SDI_AUDIOINDEX         = 101,	// 当前音频流编号

	SD_VOLUME              = 102,	// 音量大小

	SD_BALANCE             = 103,	// 音量平衡, left: -100, center: 0, right: 100

	SD_TIME_FORMAT         = 104,	// 时间格式 SD_TIME_FORMAT_VAL, (帧、秒、字节...)

	SD_PLAY_STATE          = 106,	// 播放器当前状态 (read only)

	SD_DISPLAY_TARGET      = 107,	// 视频输出 SD_DISPLAY_TARGET_VAL

	SD_DISPLAY_SIZE        = 108,	// 视频显示大小

	SD_VIDEO_BRIGHTNESS    = 109,	// 亮度

	SD_VIDEO_CONTRAST      = 110,	// 对比度

	SD_VIDEO_SATURATION    = 111,	// 饱和度

	SDI_AUDIO_OUTPUT_TYPE  = 112,	// 音频输出类型 (DIGITAL_AUDIO, AC3_AUDIO, PCM_AUDIO)

	SDI_AUDIO_OUTPUT_MODE  = 113,	// 音频输出格式 (RIGHT_ONLY, LEFT_ONLY, STEREO)

	SD_FILE_TYPE           = 114,	// 获取文件类型 (SD_FILE_TYPE_VAL, read only)

	SD_CLIP_LENGTH         = 115,	// 媒体总时长 (单位: 秒, read only)

	SD_POSITION            = 116,	// 当前播放位置 (单位: 秒)

	SD_PERCENT             = 117,   // 当前播放完成的百分比 ( 0 - 100, read only )

	SD_TVSTANDARD_FALG     = 200,	// 神龙卡视频输出制式 (SD_TVSTANDARD_FALG_VAL)

	SD_SIGMAOUT_TARGET     = 201,	// 神龙卡输出目标 ( 默认TV )
	// 0 = TV, 1 = VGA

	SD_SIGMAOUT_CONNECTOR  = 202,	// 神龙卡输出接头 ( 默认复合端子 )
	// 0 = 复合端子, 1 = YUV, 2 = RGB

	SD_SILENT_DB           = 260,	// 最小可听到的音量分贝数(0 - 80, 默认60)

	SD_DEINTERLACE_ONOFF   = 261,	// 是否打开软解反交错功能(CPU 占用率会升高)

	SD_DBG_LOG_PTRF        = 262,	// 设置调试信息接收函数指针

	SD_DBG_LOG_FILE        = 263,   // 调试信息是否输出到文件(0 = 不输出, 1 = 输出)

	SD_ALWAYS_DSHOW        = 264,	// 始终使用dshow 核心播放(0 = 自动选择播放核心, 1 = 始终使用dshow)

	SD_EQ_ACTIVE           = 265,	// 是否启用音频均衡器(0 = 不启用, 1 = 启用)

	SD_RD_EQ_PARAMS        = 266,	// 读取音频均衡器参数

	SD_WT_EQ_PARAMS        = 267,	// 设置音频均衡器参数

	SD_DETACHED_PROCESS    = 268,	// 是否是独立的播放进程(1 = 是, 0 = 否, read only)

	SD_OSD_SWAPPER         = 269,	// OSD 点歌信息交换区指针( read only )

	SD_PLAYSRV_HWND        = 270,	// 独立播放进程的控制窗口句柄( read only )

	SD_SLAVE_VIDEO_HWND    = 271,	// 点唱台视频窗口句柄

	SD_PREVIEW_AUDIO_ONOFF = 272,	// 歌曲预览是否输出声音

	SD_CPU_IS_SLOW         = 273,	// 是否是运行在低配置机器上

	SD_GET_AUDIO_INDEX     = 274,	// 读取有效的音轨编号( read only )

	SD_OSD_ON_SLAVE_WND    = 275,	// 在演唱台上显示OSD

	SD_DISP_VIDEO_HWND     = 300,	// 显示器软屏切视频显示窗口句柄

	SD_DISP_VIDEO_SHOW     = 301,	// 显示或隐藏显示器软屏切视频 (0 = 隐藏, 1 = 显示)

	SD_DISP_VIDEO_ONOFF    = 302,	// 打开或关闭软屏切功能 ( 0 = 关闭, 1 = 打开)

	SD_DUAL_OUTPUT_HWND    = 320,	// 软解双头输出视频窗口句柄, NULL 表示关闭双头输出( 启用硬解 )

	SD_WALL_PAD_HWND       = 330,	// 墙板输出视频窗口句柄

	// 特殊需求
	SD_SECTV_VIDEO_HWND    = 400,	// 第二台电视机显示视频窗口句柄
	SD_SECTV_MEDIA_SOURCE  = 401,	// 第二台电视机播放的媒体源
	SD_SECTV_AUDIO_ONOFF   = 402,	// 选择当前输出的声音
	SD_SECTV_STOP          = 403,	// 第二台电视机停止播放

	SD_LEADING_AUDIOCARD   = 420,	// 设置领唱音频输出声卡
	SD_ORIGNAL_AUDIO       = 421,	// 原唱音轨信息
	SD_GUIDE_AUDIO         = 434,	// 设置导唱音轨(参数等同SD_ORIGNAL_AUDIO)

	// 原唱音轨编号1 ~ 9
	// 左声道时参数= 'L'
	// 右声道时参数= 'R'
	SD_SCORE_ONOFF         = 422,	// 打开或关闭打分功能
	SD_GET_SCORE           = 423,	// 得到歌曲分数

	SD_GUIDE_ONOFF         = 424,	// 打开或关闭导唱功能(打开文件前先设置SD_ORIGNAL_AUDIO)
	SD_GUIDE_VOLUME        = 425,	// 导唱音量(0 ~ 10, 默认5)
	SD_SET_RECORD_DEVICE   = 428,	// 设置录音设备名(不设置将采用系统默认)
	SD_SET_RECORD_FILE     = 429,	// 设置录音文件名(OpenFile 前设置)

	SD_SET_RECORD_CAP_FREQ  = 430,	// 设置录音采样率
	SD_SET_RECORD_SAVE_FREQ = 431,	// 设置录音文件采样率
	SD_SET_RECORD_PORT      = 432,	// 录音数据发送端口
	SD_SET_SCORE_FILEPATH   = 433,	// 设置评分文件所在文件夹路径
	SD_SET_SCORE_LINE_ONOFF = 435,	// 开启或关闭评分线显示(0 = 关闭, 1 = 开启)

	SD_SNAPSHOT             = 460,	// 对当前播放视频抓图

	SD_CUT_BLACK_BORDER     = 461,	// 是否切除视频黑边

	// -- add by cai : 增加ksc歌词和频谱
	SD_SET_KSC_FILEPATH     = 480,	// 歌词文件路径
	SD_SET_KSC_FONT         = 481,  // 歌词字体(默认宋体)
	SD_SET_KSC_TEXT_HEIGHT  = 482,	// 歌词文本高度(36-96, 默认64, 单位像素)
	SD_SET_KSC_TEXT_BOLD    = 483,	// 歌词文本是否用粗体(默认否)
	SD_SET_KSC_TEXT_Y_POS   = 484,	// 歌词文本垂直位置, 从底部算起(默认120)
	SD_SET_KSC_USE_OSD      = 485,	// 是否用OSD 显示歌词(默认否, 使用覆盖窗口)
	SD_SET_KSC_LINE_MODE    = 486,	// 设置歌词行模式(0 = 自动, 1 = 单行, 2 = 双行, 默认0)
	SD_SET_KSC_COLOR_MODE   = 487,  // 设置歌词颜色(0 = 男歌手, 1 = 女歌手)
	SD_SET_KSC_TEXT_X_POS   = 488,	// 歌词文本水平位置(默认20)
	SD_SET_KSC_TEXT_WIDTH   = 489,	// 歌词文本宽度限制(默认窗口宽度-2*KSC_TEXT_X_POS)

	SD_WP_SetFreSpectrumsitify_HWND = 550, //频谱窗口句柄
	SD_WP_SetFreSpectrumsitify_Spec = 551, //设置大小等
	SD_WP_ClearUpSinger        = 552,

	SD_SET_MTV_SAVEFILE    = 701,	// 设置MTV 录制文件全路径名

	// 增强功能
	SD_FULL_SIZE_OSD       = 1001,	// 软解全屏OSD 开关
	SD_PREFECT_MB          = 1002,	// 缓存字节数 (MB)
	SD_MUTE_SECONDS        = 1003,	// 卡歌静音秒数
	SD_LOG_DIRECTORY       = 1004,	// 日志文件保存目录

	SD_FLASH_WAVE_ONOFF    = 1005,	// 打开或关闭flash 声音输出 ( 0 = 关闭, 1 = 打开)
	SD_DUAL_ROTATE_VIDEO   = 1007,	// 打开或关闭软解视频旋转 ( 0 = 关闭, 1 = 打开)
	SD_DUMP_AUDIO          = 1008,	// 保存音频数据(音轨编号, 参考SD_ORIGNAL_AUDIO=文件名)

	SD_SET_SPECTRUM			= 1010,	// 设置频谱波段数量和最高频率(HIWORD = 波段数量, LOWORD = 频率)

	//实时评分
	SD_REALTIME_SCORE      = 1011,	// 开启或关闭实时评分 ( 0 = 关闭, 1 = 打开, 默认关闭)

	// 视频增强
	SD_VIDENH_TRAYICON     = 1200,	// 是否显示通知图标
	SD_VIDENH_ONOFF        = 1201,	// 打开或关闭视频增强
	SD_VIDENH_HALF_ONLY    = 1202,	// 只处理右半部分
	SD_VIDENH_LUM          = 1203,	// 亮度(0 - 256, def = 128)
	SD_VIDENH_CONTRAST     = 1204,	// 对比度(-256 - 256, def = 0)
	SD_VIDENH_HUE          = 1205,	// 色调(-180 - 180, def = 0)
	SD_VIDENH_SAT          = 1206,	// 饱和度(0 - 128, def = 64)
	SD_VIDENH_GAMMA        = 1207,	// gamma(1 - 400, def = 100)
	SD_VIDENH_GAMMA_R      = 1208,	// red gamma(1 - 400, def = 100)
	SD_VIDENH_GAMMA_G      = 1209,	// green gamma(1 - 400, def = 100)
	SD_VIDENH_GAMMA_B      = 1210,	// blue gamma(1 - 400, def = 100)
};

enum SD_DISPLAY_TARGET_VAL
{
	SD_DISP_VGA            = 0,
	SD_DISP_TV             = 1,
};

enum SD_TIME_FORMAT_VAL
{
	SD_TIME_FORMAT_UNKNOWN = 0,
	SD_TIME_FORMAT_FRAME   = 1,
	SD_TIME_FORMAT_TIME    = 2,
	SD_TIME_FORMAT_BYTE    = 3,
	SD_TIME_FORMAT_SAMPLE  = 4,
};

enum SD_TVSTANDARD_FALG_VAL
{
	SD_TVSTANDARD_AUTO     = -1,
	SD_TVSTANDARD_NTSC     = 0,
	SD_TVSTANDARD_PAL      = 1,
	SD_TVSTANDARD_PAL60    = 2,
	SD_TVSTANDARD_PALN     = 3,
};

enum SD_FILE_TYPE_VAL
{
	SDF_UNKNOWN            =  -1,	// unknown
	SDF_DIVXFILE           = 200,	// Media type : divx file
	SDF_MPEG4              = 201,	// Media type : mpeg 4
	SDF_MP3                = 202,	// Media type : mp3
	SDF_MPEG1              = 203,	// Media type : mpeg1
	SDF_MPEG2              = 204,	// Media type : mpeg2
	SDF_DVD                = 205,	// Media type : DVD
	SDF_REAL               = 206,	// Media type : Real
	SDF_QT                 = 207,	// Media type : QuickTime
};


//
// 预览(大厅公播) 控制码
//
enum PREVIEW_CONTROL
{
	PVC_GET_DURATION,				// 获取播放总时长(秒)
	PVC_GET_POSITION,				// 获取当前播放位置(秒)
	PVC_GET_TONE,					// 获取当前播放音调

	PVC_SET_POSITION = 100,			// 设置当前播放位置(秒)

	PVC_SET_INIT_AUDIO,				// 设置预览播放的音轨(在硬解输出时启用, 调用Preview_Open 前设置才有效)
	// argv0 = 'L',   原唱在左声道
	// argv0 = 'R',   原唱在右声道
	// argv0 = 1 ~ 8, 原唱在指定音轨(从数据库中得到)
	// argv0 = -1,    不进行任何设置直接播放音频(默认)

	PVC_SET_TONE,					// 设置预览声音音调

	PVC_SET_TVOUT,					// 设置预览视频在电视上输出方式
	// argv0 = 0, 不输出到电视机
	// argv0 = 1, 输出到电视机
	// argv0 = 2, 通过画中画形式输出到电视
};


//
// 电视卡控制码
//
enum TV_CONTROL
{
	TVC_GET_CHANNEL,				// 获取当前频道
	TVC_GET_TVOUT,					// 获取当前电视输出设备, 返回LONG
	//  HIWORD(r) = 0, 没有输出到电视
	//  HIWORD(r) = 1, 输出到电视
	//  HIWORD(r) = 2, 通过画中画形式输出到电视
	//  LOWORD(r) = 0, 没有输出到显示器
	//  LOWORD(r) = 1, 输出到显示器视频窗口
	TVC_GET_DISP_HWND,				// 获取电视输出视频窗口句柄


	TVC_SET_CHANNEL = 100,			// 设置当前频道, 返回当前的频道号
	TVC_SET_CHL_INCREASE,			// 当前频道加一, 返回当前的频道号
	TVC_SET_CHL_DECREASE,			// 当前频道减一, 返回当前的频道号
	TVC_SET_AUTOTUNE,				// 自动寻台
	TVC_SET_PHYSCONN,				// 设置输入端子(PhysicalConnectorType of strmif.h)

	TVC_SET_DISP_HWND,				// 设置显示器输出视频窗口句柄(在打开电视卡前设置)

	TVC_SET_TVOUT,					// 设置电视卡信号输出目标
	// argv0 = 0, 不输出到电视机
	// argv0 = 1, 输出到电视机
	// argv0 = 2, 通过画中画形式输出到电视
	// argv1 = 0, 不输出到显示器
	// argv1 = 1, 输出到显示器视频窗口
};


//音量改变标示
enum VOLUME_CHANGE_FLAG
{
	VOLUME_UP_FLAG,   //音量加
	VOLUME_DOWN_FLAG, //音量减
	VOLUME_SET_FLAG,  //设置音量
};

//音调改变标示
enum TUNE_CHANGE_FLAG
{
	TUNE_UP_FLAG,        //音调增
	TUNE_DOWN_FLAG,      //音调减
	TUNE_ORIGINAL_FLAG,  //原调
	TUNE_SET_VALUE_FLAG, //设置音调
};

//混响改变标示
enum REVERBERATION_CHANGE_FLAG
{
	REVERBERATION_UP_FLAG,   //混响加
	REVERBERATION_DOWN_FLAG, //混响减
};


#endif
