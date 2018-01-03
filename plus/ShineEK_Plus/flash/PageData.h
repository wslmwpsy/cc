#ifndef _PAGEDATA_H_
#define _PAGEDATA_H_



//如果这个枚举类改变，也要相应的改变PageVariable.h中的page_call_para[]变量
enum FLASH_PAGE_CODE
{
	page_homepage=0,     //首页
	page_title,          //歌名点歌
	page_singer,         //歌星点歌
	page_lyric,          //歌词点歌
	page_theme,          //主题点歌
	page_top_song,       //金曲排行
	page_new_song,       //新歌推荐
	page_opera,          //经典戏曲
	page_assist,         //辅助功能
	page_introduce,      //场所介绍
	page_selected,       //已选歌曲
	page_singed,         //已唱歌曲
	page_game,           //娱乐游戏
	page_movie,          //电影欣赏
	page_recording,      //录音管理
	page_video,          //视频转播
	page_U_disk,         //U盘播歌
	page_proposal,       //意见调查
	page_member_manager, //会员管理
	page_member_song,    //会员歌曲
	page_painting,       //绘画
	page_system_manager, //系统管理
	page_preview,        //预览视频
	page_singer_song,    //具体歌星的歌曲列表页面
	page_screen_show,    //屏切页面   没有使用
	page_change_skin,    //换肤页面
	page_system_info,    //系统信息
	page_class,          //分类点歌，即旧的主题
	page_language,       //语种点歌
	page_movie_song,     //影视金曲
	page_era_song,       //年代金曲
	page_number_song,    //编号点歌
	page_custom_singer,  //客户自定义的歌星
	page_earth,          //导航页面
	page_drinks,         //酒水
	page_secondary_song, //歌曲二级页面
	page_search_song,    //搜歌页面
	page_write,          //手写点歌
	page_theme_song,     //主题歌曲
	page_movieMeun,      //电影二级页面
	page_place_video,    //场所视频
	page_concert,        //演唱会
	page_ktvExplain,     //场所攻略
	page_room,           //包厢使用手册
	page_fire,           //消防图解
	page_guide,          //消防指南
	page_pk_manager,   //pk登录
	page_pk,           //pk邀请页面
	page_pk_receive,     //pk接收邀请页面
	page_pkjx,          //pk精选
	page_encode,        //移动点歌
	page_custom_song,  //定制歌曲
	page_karaoke_home, //卡拉OK首页
	page_word_count,   //字数点歌
	page_jewel_box,      //百宝箱
	page_hdmi,           //高清专区
	page_kalaok_pk,		 //麦霸pk
	page_kala_share,     //K歌分享
	page_dekaron_maiba,  //挑战麦霸
	page_find_maiba,	 //发现麦霸
	page_help,            //
	page_maiba_login,    //麦霸登录、注册
	page_consumer,        //消费查询
	page_wechat,		  //微信点歌
	page_maiba_register,  //麦霸注册
	page_home_song,       //首页的点播歌曲
	page_enterainment, //首页的娱乐互动
	page_place_raiders, //首页的场所攻
	page_aider_function, //首页的辅助功能
	page_fast_songs_slow_dance, //劲曲慢舞
	page_music_enjoy, //音乐欣赏
	page_home_theme_song, //首页主题点歌
	page_baidu_music, //百度音乐
	page_qq_music, //QQ音乐
	page_kugou_music, //酷狗音乐
	page_kuwo_music, //酷我音乐
	page_yule_news, //娱乐新闻
	page_language_change, //语言切换
	page_video_dating,	//视频交友
	page_singing_contest, //演唱比赛
	page_sb_ranking_polite, //我要参加-上榜有礼
	page_sb_free_pk,		//我要参加-自由PK
	page_sb_challenge_pk,	//我要参加-擂台PK
	page_free_pk_view_list,			//查看榜单 - 自由PK
	page_challenge_pk_view_list, //查看榜单 - 擂台PK
	page_new_theme_song,		//新主题歌曲
	page_close_clear_msg,		//关房时，跳到清理界面
	page_voice_china,       //中国好声音
	page_yunadd_song,		//云加歌歌曲页面
	page_phone_push,		//手机推送
	page_phone_push_preview, //手机推送预览
	page_movie_detail,       //电影详情页
	page_voice_china_singer,  //好声音下显示歌星
	page_trend_list,		//潮流榜单页面
	page_challenge_star,					//挑战大咖
	page_across_pass,				//百秒夺奖（闯关夺宝）
	page_video_show,			//视频秀场
	page_listen_knowledge_song, //听音识曲
	page_picture_mv,			//照片mv
	page_active_game,			//互动游戏
	page_entertainment_programme,			//娱乐节目
	page_wechat_barrage,			//微信互动-弹幕

	PAGE_MAX_NUMBER,     //最多页数
};

enum FLASH_SEND_FUNCTION_CODE
{
	//快速检索的功能

	//杂项
	//从视频屏保返回点歌界面
	RETURN_SELECT_SONG=10, 

	//翻页
	PAGE_UP  =60,      //上一页
	PAGE_DOWN=61,      //下一页
	PAGE_BACK=63,      //页面返回
	
	//呼叫服务
	CALL_ATTENDANT         =100, //呼叫服务员
	CALL_PR_MANAGER        =101, //公关经理
	CALL_ACOUSTICS_ENGINEER=102, //音响师
	CALL_CLEANER           =103, //保洁员
	CALL_DUTY_MANAGER      =104, //值班经理
	CALL_ORDER_DINNER      =105, //点餐
	CALL_CUP               =106, //杯子
	CALL_PAY_MONEY         =107, //买单
	CALL_CONSULTION        =108, //咨询
	CALL_CANCEL            =115, //取消呼叫服务

	//歌曲控制功能
	SONG_NEXT       =120,        //下一首
	SONG_REPLAY     =121,        //重唱
	SONG_PREVIOUS   =122,        //上一首
	SONG_ACCOMPANY_ORIGINAL=123, //伴唱或原唱
	SONG_PLAY_PAUSE =124,        //播放或暂停
	SONG_MUTE_UNMUTE=125,        //静音/取消静音
	SONG_ENJOYMERT  =127,        //欣赏
	SONG_ORIGINAL   =128,        //原唱
	SONG_ACCOMPANY  =129,        //伴唱
	SONG_PLAY       =130,        //播放
	SONG_PAUSE      =131,        //暂停
	SONG_MUTE       =132,        //静音
	SONG_UNMUTE     =133,        //取消静音


	//音量
	MUSIC_VOLUME_UP       =140,  //音乐的音量加
	MUSIC_VOLUME_DOWN     =141,  //音乐的音量减
	MICROPHONE_VOLUME_UP  =142,  //麦克风的音量加
	MICROPHONE_VOLUME_DOWN=143,  //麦克风的音量减
	TUNE_UP               =144,  //音调增
	TUNE_DOWN             =145,  //音调减
	TUNE_ORIGINAL         =146,  //原调
	REVERBERATION_DOWN    =147,  //混响减
	REVERBERATION_UP      =148,  //混响加

	//气氛
	ATMOSPHERE_APPLAUSE   =160,  //鼓掌
	ATMOSPHERE_CHEER      =161,  //欢呼
	ATMOSPHERE_OUTCRY     =162,  //催眠
	ATMOSPHERE_WHISTLE    =163,  //狂汗

	//音效
	AUDIO_EFFECT_STANDARD    =170,  //标准
	AUDIO_EFFECT_THEATER     =171,  //剧场
	AUDIO_EFFECT_PROFESSIONAL=172,  //唱将
	AUDIO_EFFECT_MAGIC       =173,  //魔音
	AUDIO_EFFECT_RESERVE1    =174,  //预留 自动
	AUDIO_EFFECT_RESERVE2    =175,  //预留
	AUDIO_EFFECT_RESERVE3    =176,  //预留
	AUDIO_EFFECT_RESERVE4    =177,  //预留

	//环境音
	ENVIRONMENT_AUDIO_CLOSE  =180,  //关闭环境音
	ENVIRONMENT_AUDIO_MEETING=181,  //会议
	ENVIRONMENT_AUDIO_AIRPORT=182,  //飞机场
	ENVIRONMENT_AUDIO_ROAD   =183,  //马路上
	ENVIRONMENT_AUDIO_STATION=184,  //火车站
	ENVIRONMENT_AUDIO_MAHJONG=185,  //麻将
	ENVIRONMENT_AUDIO_RAIN   =186,  //下雨中
	
	//灯光
	LIGHT_OPEN               =189,  //灯光
	LIGHT_CLOSE              =190,  //灯光 关闭
	LIGHT_STANDARD           =191,  //灯光 标准
	LIGHT_BACKGROUND         =192,  //灯光 背景
	LIGHT_STAGE              =193,  //灯光 舞台
	LIGHT_SCINTILLATION      =194,  //灯光 屏闪
	LIGHT_OPEN1              =195,   //灯光1
	LIGHT_OPEN2              =196,   //灯光2
	LIGHT_OPEN3              =197,   //灯光3
	LIGHT_OPEN4              =198,   //灯光4
	LIGHT_OPEN5              =199,   //灯光5
	LIGHT_OPEN6              =200,   //灯光6
	LIGHT_OPEN7              =201,   //灯光7
	LIGHT_OPEN8              =202,   //灯光8

	ATMOSPHERE_DRUM_KIT_LEFT_FRUM1   =220,   //左一鼓
	ATMOSPHERE_DRUM_KIT_LEFT_FRUM2   =221,   //左二鼓
	ATMOSPHERE_DRUM_KIT_MIDDLE_FRUM  =222,   //中间的鼓
	ATMOSPHERE_DRUM_KIT_RIGHT_FRUM2  =223,   //右二鼓
	ATMOSPHERE_DRUM_KIT_RIGHT_FRUM1  =224,   //右一鼓
	ATMOSPHERE_DRUM_KIT_PRE_FRUM     =225,   //前大鼓
	ATMOSPHERE_DRUM_KIT_LEFT_CYMBAL1 =226,   //左一镲
	ATMOSPHERE_DRUM_KIT_LEFT_CYMBAL2 =227,   //左二镲
	ATMOSPHERE_DRUM_KIT_RIGHT_CYMBAL2=228,   //右二镲
	ATMOSPHERE_DRUM_KIT_RIGHT_CYMBAL1=229,   //右一镲

	ATMOSPHERE_PIANO_BLACK1 =330,       //钢琴黑键（左起，共15个）
	ATMOSPHERE_PIANO_BLACK2 =331,
	ATMOSPHERE_PIANO_BLACK3 =332,
	ATMOSPHERE_PIANO_BLACK4 =333,
	ATMOSPHERE_PIANO_BLACK5 =334,
	ATMOSPHERE_PIANO_BLACK6 =335,
	ATMOSPHERE_PIANO_BLACK7 =336,
	ATMOSPHERE_PIANO_BLACK8 =337,
	ATMOSPHERE_PIANO_BLACK9 =338,
	ATMOSPHERE_PIANO_BLACK10=339,
	ATMOSPHERE_PIANO_BLACK11=340,
	ATMOSPHERE_PIANO_BLACK12=341,
	ATMOSPHERE_PIANO_BLACK13=342,
	ATMOSPHERE_PIANO_BLACK14=343,
	ATMOSPHERE_PIANO_BLACK15=344,

	ATMOSPHERE_PIANO_WHITE1 =345, //钢琴白键（左起，共21个）
	ATMOSPHERE_PIANO_WHITE2 =346,
	ATMOSPHERE_PIANO_WHITE3 =347,
	ATMOSPHERE_PIANO_WHITE4 =348,
	ATMOSPHERE_PIANO_WHITE5 =349,
	ATMOSPHERE_PIANO_WHITE6 =350,
	ATMOSPHERE_PIANO_WHITE7 =351,
	ATMOSPHERE_PIANO_WHITE8 =352,
	ATMOSPHERE_PIANO_WHITE9 =353,
	ATMOSPHERE_PIANO_WHITE10=354,
	ATMOSPHERE_PIANO_WHITE11=355,
	ATMOSPHERE_PIANO_WHITE12=356,
	ATMOSPHERE_PIANO_WHITE13=357,
	ATMOSPHERE_PIANO_WHITE14=358,
	ATMOSPHERE_PIANO_WHITE15=359,
	ATMOSPHERE_PIANO_WHITE16=360,
	ATMOSPHERE_PIANO_WHITE17=361,
	ATMOSPHERE_PIANO_WHITE18=362,
	ATMOSPHERE_PIANO_WHITE19=363,
	ATMOSPHERE_PIANO_WHITE20=364,
	ATMOSPHERE_PIANO_WHITE21=365,

	ATMOSPHERE_MARACAS      =390,         //沙锤
	ATMOSPHERE_HANDBELL     =391,         //手铃
	ATMOSPHERE_DRUM         =392,         //鼓
	LYRIC_LINK = 400,                     //歌词接龙

	//空调排风
	AIR_CONDITION_STRONG   =422,          //空调强
	AIR_CONDITION_MID      =421,          //空调中
	AIR_CONDITION_WEAK     =420,          //空调弱

	AIR_CONDITION_CLOSE    =430,          //空调关闭

	DISCHARGE_AIR_FUNCTION =440,          //排风


	SHOW_DRAW_IMAG         =460,          //显示绘制的图片

	ENTER_GUIDE_SONG       =500,          //进入导唱（旋律伴奏）
	EXIT_GUIDE_SONG        =501,          //退出导唱



	OPEN_SCORE             =510,          //打开评分
	CLOSE_SCORE            =511,          //关闭评分

	//新欢呼
	ATMOSPHERE_HAOZAN =531, //好赞
	ATMOSPHERE_SHIHUA =532, //石化
	ATMOSPHERE_XIANHUA =533,//献花
	ATMOSPHERE_TUXUE =534, //吐血
	ATMOSPHERE_FEIWEN =535, //飞吻
	ATMOSPHERE_XINSUI =536, //心碎
	ATMOSPHERE_HAIXIU =537, //害羞
	ATMOSPHERE_ZADAN =538, //砸蛋


	//音效
	MUSIC_SOUND_STANDARD    = 550,  //音乐音效标准
	MUSIC_SOUND_THEATER     = 551,  //音乐音效剧场
	MUSIC_SOUND_PROFESSIONAL= 552,  //音乐音效唱将
	MUSIC_SOUND_MAGIC       = 553,  //音乐音效魔音
	MUSIC_SOUND_RESERVE1    = 554,  //音乐音效自动
	MUSIC_SOUND_RESERVE2    = 555,  //音乐音效预留
	MUSIC_SOUND_RESERVE3    = 556,  //音乐音效预留
	MUSIC_SOUND_RESERVE4    = 557,  //音乐音效预留

	LIGHT_AUTO_SWITCH		= 600,

	/**
	*
	* 700 - 799 被占用，切记。因平台微信需要音量。
	*
	**/
	MUSIC_VOLUME_MIN = 700,
	MUSIC_VOLUME_MAX = 799,
};

//flash发送的灯光代码
enum FLASH_SEND_LIGHT_CODE
{
	FLASH_SEND_LIGHT1,               //灯光1
	FLASH_SEND_LIGHT2,               //灯光2
	FLASH_SEND_LIGHT3,               //灯光3
	FLASH_SEND_LIGHT4,               //灯光4
	FLASH_SEND_LIGHT5,               //灯光5
	FLASH_SEND_LIGHT6,               //灯光6
	FLASH_SEND_LIGHT_STANDARD,       //灯光 标准
	FLASH_SEND_LIGHT_BACKGROUND,     //灯光 背景
	FLASH_SEND_LIGHT_STAGE,          //灯光 舞台
	FLASH_SEND_LIGHT_SCINTILLATION,  //灯光 屏闪
	FLASH_SEND_LIGHT_CLOSE,          //灯光 关闭
	FLASH_SEND_LIGHT_OPEN,           //灯光 开
	FLASH_SEND_LIGHT7,               //灯光7
	FLASH_SEND_LIGHT8,               //灯光8
};

//环境音
enum FLASH_SEND_ENVIRONMENT_AUDIO_CODE
{
	FLASH_SEND_ENVIRONMENT_AUDIO_CLOSE,  //关闭环境音
	FLASH_SEND_ENVIRONMENT_AUDIO_MEETING,  //会议
	FLASH_SEND_ENVIRONMENT_AUDIO_AIRPORT,  //飞机场
	FLASH_SEND_ENVIRONMENT_AUDIO_ROAD,     //马路上
	FLASH_SEND_ENVIRONMENT_AUDIO_STATION,  //火车站
	FLASH_SEND_ENVIRONMENT_AUDIO_MAHJONG,  //麻将
	FLASH_SEND_ENVIRONMENT_AUDIO_RAIN,     //下雨中
};

//录音功能
enum FLASH_SEND_TAPE_CODE
{
	FLASH_SEND_TAPE_START=1,         //开始录音
	FLASH_SEND_TAPE_STOP=2,          //停止录音
	FLASH_SEND_TAPE_REPLAY=3,        //录音回放
};

#endif