#ifndef _COM_VALUE_H_
#define _COM_VALUE_H_

//发送到串口的命令标示
enum COM_SEND_VALUE_FLAG
{
	COM_SEND_POWER_ON,                   //开机
	COM_SEND_POWER_OFF,                  //关机
	COM_SEND_CLOSE_ROOM,                 //关房
	COM_SEND_OPEN_ROOM,                  //开房
	COM_SEND_NEXT_SONG,                  //下一首
	COM_SEND_AUDIO_EFFECT_STANDARD,      //标准
	COM_SEND_AUDIO_EFFECT_THEATER,       //剧场
	COM_SEND_AUDIO_EFFECT_PROFESSIONAL,  //唱将
	COM_SEND_AUDIO_EFFECT_MAGIC,         //魔音
	COM_SEND_AUDIO_EFFECT_RESERVE1,      //音效预留
	COM_SEND_AUDIO_EFFECT_RESERVE2,      //音效预留
	COM_SEND_AUDIO_EFFECT_RESERVE3,      //音效预留
	COM_SEND_AUDIO_EFFECT_RESERVE4,      //自动
	COM_SEND_MICROPHONE_VOLUME_UP,       //麦克风音量加
	COM_SEND_MICROPHONE_VOLUME_DOWN,     //麦克风音量减
	COM_SEND_TUNE_UP,                    //音调增加
	COM_SEND_TUNE_DOWN,                  //音调降低
	COM_SEND_TUNE_STANDARD,              //音调标准
	COM_SEND_LIGHT_STANDARD,             //灯光 标准
	COM_SEND_LIGHT_BACKGROUND,           //灯光 背景
	COM_SEND_LIGHT_STAGE,                //灯光 舞台
	COM_SEND_LIGHT_SCINTILLATION,        //灯光 屏闪
	COM_SEND_LIGHT_CLOSE,                //灯光 关闭
	COM_SEND_LIGHT_OPEN,                 //灯光 开
	COM_SEND_LIGHT1,                     //灯光1
	COM_SEND_LIGHT2,                     //灯光2
	COM_SEND_LIGHT3,                     //灯光3
	COM_SEND_LIGHT4,                     //灯光4
	COM_SEND_LIGHT5,                     //灯光5
	COM_SEND_LIGHT6,                     //灯光6
	COM_SEND_LIGHT7,                     //灯光7
	COM_SEND_LIGHT8,                     //灯光8
	COM_SEND_LIGHT9,                     //灯光9
	COM_SEND_LIGHT10,                    //灯光10
	COM_SEND_LIGHT_MUTE,				 //静音时灯光
	COM_SEND_LIGHT_PAUSE,				 //暂停时灯光
	COM_SEND_MUSIC_VOLUME_UP,            //音乐的音量增加
	COM_SEND_MUSIC_VOLUME_DOWN,          //音乐的音量降低
	COM_SEND_SCREEN_SWITCH,              //画面交换
	COM_SEND_TV_CHANNEL_UP,              //频道增加
	COM_SEND_TV_CHANNEL_DOWN,            //频道减低
	COM_SEND_REQUEST_SERVER,             //请求服务
	COM_SEND_CANCEL_SERVER,              //取消服务
	COM_SEND_REVERBERATION_DOWN,         //混响减
	COM_SEND_REVERBERATION_UP,           //混响加
	COM_SEND_AIR_CONDITION_STRONG,       //空调强
	COM_SEND_AIR_CONDITION_MID,          //空调中
	COM_SEND_AIR_CONDITION_WEAK,         //空调弱
	COM_SEND_AIR_CONDITION_CLOSE,        //空调关闭
	COM_SEND_DISCHARGE_AIR_FUNCTION,     //排风
	COM_SEND_CLOSE_SERVICE_LIGHT,        //关闭服务灯
	COM_SEND_PLAYER_PLAY,                //播放
	COM_SEND_PLAYER_PAUSE,               //暂停

	COM_SEND_MUSIC_SOUND_STANDARD,      //音乐音效标准
	COM_SEND_MUSIC_SOUND_THEATER,       //音乐音效剧场
	COM_SEND_MUSIC_SOUND_PROFESSIONAL,  //音乐音效唱将
	COM_SEND_MUSIC_SOUND_MAGIC,         //音乐音效魔音
	COM_SEND_MUSIC_SOUND_RESERVE1,      //音乐音效预留
	COM_SEND_MUSIC_SOUND_RESERVE2,      //音乐音效预留
	COM_SEND_MUSIC_SOUND_RESERVE3,      //音乐音效预留
	COM_SEND_MUSIC_SOUND_RESERVE4,      //音乐音效预留
};

//接收串口的命令标示,同步修改 TCHAR com_receive_key_name[][]数组
enum COM_RECEIVE_VALUE_FLAG
{
	COM_RECEIVE_REQUEST_SERVICE,        //请求服务
	COM_RECEIVE_CANCEL_SERVICE,         //取消服务
	COM_RECEIVE_MICROPHONE_VOLUME_UP,   //麦克风音量加
	COM_RECEIVE_MICROPHONE_VOLUME_DOWN, //麦克风音量减
	COM_RECEIVE_MUSIC_VOLUME_UP,        //音乐的音量加
	COM_RECEIVE_MUSIC_VOLUME_DOWN,      //音乐的音量减
	COM_RECEIVE_TUNE_UP,                //音调加
	COM_RECEIVE_TUNE_DOWN,              //音调减
	COM_RECEIVE_TUNE_STANDARD,          //标准调
	COM_RECEIVE_NEXT_SONG,              //下一首
	COM_RECEIVE_REPLAY_SONG,            //重唱
	COM_RECEIVE_KARAOKE_ACCOMPANY,      //原伴唱
	COM_RECEIVE_KARAOKE_TRACK,          //原唱
	COM_RECEIVE_ACCOMPANY_TRACK,        //伴唱
	COM_RECEIVE_PLAY_PAUSE,             //播放暂停
	COM_RECEIVE_PLAY,                   //播放
	COM_RECEIVE_PAUSE,                  //暂停
	COM_RECEIVE_SONG_MUTE,              //静音/取消静音
	COM_RECEIVE_SONG_MUTE_BUTTON,       //静音
	COM_RECEIVE_SONG_UNMUTE_BUTTON,     //取消静音
	COM_RECEIVE_RECORDER,               //录音
	COM_RECEIVE_ATMOSPHERE_APPLAUSE,    //掌声
	COM_RECEIVE_ATMOSPHERE_CHEER,       //欢呼
	COM_RECEIVE_ATMOSPHERE_OUTCRY,      //催眠
	COM_RECEIVE_ATMOSPHERE_WHISTLE,     //狂汗
	COM_RECEIVE_LIGHT1,                 //灯光1
	COM_RECEIVE_LIGHT2,                 //灯光2
	COM_RECEIVE_LIGHT3,                 //灯光3
	COM_RECEIVE_LIGHT4,                 //灯光4
	COM_RECEIVE_LIGHT5,                 //灯光5
	COM_RECEIVE_LIGHT6,                 //灯光6
	COM_RECEIVE_LIGHT7,                 //灯光7
	COM_RECEIVE_LIGHT8,                 //灯光8
	COM_RECEIVE_LIGHT9,                 //灯光9
	COM_RECEIVE_LIGHT10,                //灯光10
	COM_RECEIVE_LIGHT_OPEN,             //灯光开
	COM_RECEIVE_LIGHT_CLOSE,            //灯光关闭
	COM_RECEIVE_AUDIO_EFFECT_STANDARD,      //标准
	COM_RECEIVE_AUDIO_EFFECT_THEATER,       //剧场
	COM_RECEIVE_AUDIO_EFFECT_PROFESSIONAL,  //唱将
	COM_RECEIVE_AUDIO_EFFECT_MAGIC,         //魔音
	COM_RECEIVE_AUDIO_EFFECT_RESERVE1,      //音效预留
	COM_RECEIVE_AUDIO_EFFECT_RESERVE2,      //音效预留
	COM_RECEIVE_AUDIO_EFFECT_RESERVE3,      //音效预留
	COM_RECEIVE_AUDIO_EFFECT_RESERVE4,      //音效预留
	COM_RECEIVE_AUDIO_EFFECT_CHANGE,        //音效改变
	COM_RECEIVE_ENJOY_SONG,                 //欣赏
	COM_RECEIVE_AIR_CONDITION_STRONG,       //空调强
	COM_RECEIVE_AIR_CONDITION_MID,          //空调中
	COM_RECEIVE_AIR_CONDITION_WEAK,         //空调弱
	COM_RECEIVE_AIR_CONDITION_CLOSE,        //空调关闭
	COM_RECEIVE_DISCHARGE_AIR_FUNCTION,     //排风
	COM_RECEIVE_SERVER_LIGHT_STATE,         //服务灯状态
	COM_RECEIVE_LIGHT11,                 //灯光9
	COM_RECEIVE_LIGHT12,                //灯光10

	COM_RECEIVE_ATMOSPHERE_HAOZAN,	//好赞
	COM_RECEIVE_ATMOSPHERE_SHIHUA, //石化
	COM_RECEIVE_ATMOSPHERE_XIEHUA, //献花
	COM_RECEIVE_ATMOSPHERE_TUXIE, //吐血
	COM_RECEIVE_ATMOSPHERE_FEIWEN, //飞吻
	COM_RECEIVE_ATMOSPHERE_XINSUI, //心碎
	COM_RECEIVE_ATMOSPHERE_HAIXIU, //害羞
	COM_RECEIVE_ATMOSPHERE_ZADAN, //砸蛋

	COM_RECEIVE_MUSIC_SOUND_STANDARD,      //音乐音效标准
	COM_RECEIVE_MUSIC_SOUND_THEATER,       //音乐音效剧场
	COM_RECEIVE_MUSIC_SOUND_PROFESSIONAL,  //音乐音效唱将
	COM_RECEIVE_MUSIC_SOUND_MAGIC,         //音乐音效魔音
	COM_RECEIVE_MUSIC_SOUND_RESERVE1,      //音乐音效预留
	COM_RECEIVE_MUSIC_SOUND_RESERVE2,      //音乐音效预留
	COM_RECEIVE_MUSIC_SOUND_RESERVE3,      //音乐音效预留
	COM_RECEIVE_MUSIC_SOUND_RESERVE4,      //音乐音效预留
	COM_RECEIVE_MUSIC_SOUND_CHANGE,        //音乐音效改变

	COM_RECEIVE_VALUE_FLAG_MAX_COUNT,   //接受码的最大数
};

#endif