#ifndef _COM_VARIABLE_H_
#define _COM_VARIABLE_H_

#include "com_value.h"

//配置文件中，串口接收的键值
//顺序和 enum COM_RECEIVE_VALUE_FLAG 对应
TCHAR com_receive_key_name[COM_RECEIVE_VALUE_FLAG_MAX_COUNT][128] = 
{
		L"request_service",
		L"cancel_service",
		L"microphone_volume_up",
		L"microphone_volume_down",
		L"music_volume_up",
		L"music_volume_down",
		L"tune_up",
		L"tune_down",
		L"tune_standard",
		L"next_song",
		L"replay_song",
		L"karaoke_accompany",
		L"Karaoke_track",
		L"accompany_track",
		L"play_pause",
		L"play",
		L"pause",
		L"song_mute",
		L"song_mute_button",
		L"song_unmute_button",
		L"recorder_audio",
		L"atmosphere_applause",
		L"atmosphere_cheer",
		L"atmosphere_outcry",
		L"atmosphere_whistle",
		L"light1",
		L"light2",
		L"light3",
		L"light4",
		L"light5",
		L"light6",
		L"light7",
		L"light8",
		L"light9",
		L"light10",
		L"light_open",
		L"light_close",
		L"audio_effect_standard",
		L"audio_effect_threater",
		L"audio_effect_professional",
		L"audio_effect_magic",
		L"audio_effect_reserve1",
		L"audio_effect_reserve2",
		L"audio_effect_reserve3",
		L"audio_effect_reserve4",
		L"audio_effect_change",
		L"enjoy_song",
		L"air_condition_strong",
		L"air_condition_mid",
		L"air_condition_weak",
		L"air_condition_close",
		L"discharge_air",
		L"server_light_state",		
		L"light11",
		L"light12",
		L"atmosphere_haozan",
		L"atmosphere_shihua",
		L"atmosphere_xianhua",
		L"atmosphere_tuxie",
		L"atmosphere_feiwen",
		L"atmosphere_xinsui",
		L"atmosphere_haixiu",
		L"atmosphere_zadan",
		L"music_sound_standard",  //音乐音效标准
		L"music_sound_theater",  //音乐音效剧场
		L"music_sound_professional",  //音乐音效唱将
		L"music_sound_magic",  //音乐音效魔音
		L"music_sound_reserve1",  //音乐音效自动
		L"music_sound_reserve2",  //音乐音效预留
		L"music_sound_reserve3",  //音乐音效预留
		L"music_sound_reserve4",  //音乐音效预留
		L"music_sound_change",  //音乐音效标准
};

#endif