#ifndef _DB_QUERY_CONDITION_H_
#define _DB_QUERY_CONDITION_H_

#include "DBDataTypeDef.h"
#include "..\flash\PageData.h"

//歌曲,字段的顺序不要改变，如果改变了也要改变 query_song_manager.cpp文件中的赋值顺序
select_expr song_select_expr={
	    L"song_id,accompany_sing_track,karaoke_track,song_name,movie_name,show_movie_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,song_name_word_count,singer_number,singer_name,singer_sex,spell_first_letter_abbreviation,spell_first_letter_traditional,moive_spell_first_letter,sing_number,song_version,light_control_set,audio_effect_code,file_format,song_bit_rate,song_theme,new_song_theme,first_word_stroke_number,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,file_size,video_saturation,video_luminance,video_contrast,lyric,word_head_code,culture_code,issue_year,new_song_date,preview_path,singer_id1,singer_id2,singer_id3,singer_id4,file_version",
		//L"song_id,accompany_sing_track,karaoke_track,song_name,movie_name,show_movie_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,song_name_word_count,singer_number,singer_name,singer_sex,spell_first_letter_abbreviation,spell_first_letter_traditional,moive_spell_first_letter,sing_number,song_version,light_control_set,audio_effect_code,file_format,song_bit_rate,song_theme,new_song_theme,first_word_stroke_number,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,file_size,video_saturation,video_luminance,video_contrast,lyric,word_head_code,culture_code,issue_year,new_song_date,preview_path",
		51,
		L"select count(song_id) from song",
		L"select song_id,accompany_sing_track,karaoke_track,guid_track,song_name,show_movie_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,singer_name,singer_sex,song_version,light_control_set,audio_effect_code,file_format,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,video_saturation,video_luminance,video_contrast,lyric,culture_code,preview_path,singer_id1,singer_id2,singer_id3,singer_id4,file_version from song",
		36
};

//成员歌曲
select_expr member_song_select_expr={
	    L"song_id,accompany_sing_track,karaoke_track,guid_track,song_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,song_name_word_count,singer_number,singer_name,spell_first_letter_abbreviation,sing_number,song_version,light_control_set,audio_effect_code,file_format,song_bit_rate,song_theme,new_song_theme,first_word_stroke_number,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,file_size,video_saturation,video_luminance,video_contrast,lyric,word_head_code,culture_code,new_song_date,preview_path,member_name,singer_id1,singer_id2,singer_id3,singer_id4,file_version",
		//L"song_id,accompany_sing_track,karaoke_track,song_name,movie_name,show_movie_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,song_name_word_count,singer_number,singer_name,singer_sex,spell_first_letter_abbreviation,spell_first_letter_traditional,moive_spell_first_letter,sing_number,song_version,light_control_set,audio_effect_code,file_format,song_bit_rate,song_theme,new_song_theme,first_word_stroke_number,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,file_size,video_saturation,video_luminance,video_contrast,lyric,word_head_code,culture_code,issue_year,new_song_date,preview_path,member_name",
		42,
		L"select count(song_id) from member_song",
		L"select song_id,accompany_sing_track,karaoke_track,guid_track,song_name,show_movie_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,singer_name,singer_sex,song_version,light_control_set,audio_effect_code,file_format,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,video_saturation,video_luminance,video_contrast,lyric,culture_code,preview_path,singer_id1,singer_id2,singer_id3,singer_id4,file_version from member_song",
		36
};

//排行歌曲
select_expr top_song_select_expr={
	    L"song_id,accompany_sing_track,karaoke_track,guid_track,song_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,song_name_word_count,singer_number,singer_name,spell_first_letter_abbreviation,sing_number,song_version,light_control_set,audio_effect_code,file_format,song_bit_rate,song_theme,new_song_theme,first_word_stroke_number,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,file_size,video_saturation,video_luminance,video_contrast,lyric,word_head_code,culture_code,new_song_date,preview_path,singer_id1,singer_id2,singer_id3,singer_id4,file_version",
		//L"song_id,accompany_sing_track,karaoke_track,song_name,movie_name,show_movie_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,song_name_word_count,singer_number,singer_name,singer_sex,spell_first_letter_abbreviation,spell_first_letter_traditional,moive_spell_first_letter,sing_number,song_version,light_control_set,audio_effect_code,file_format,song_bit_rate,song_theme,new_song_theme,first_word_stroke_number,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,file_size,video_saturation,video_luminance,video_contrast,lyric,word_head_code,culture_code,issue_year,new_song_date,preview_path",
		41,
		L"select count(song_id) from top_song",
		L"select song_id,accompany_sing_track,karaoke_track,guid_track,song_name,show_movie_name,song_name_sort,accompany_volume,karaoke_volume,language,song_type,singer_name,singer_sex,song_version,light_control_set,audio_effect_code,file_format,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,song_relative_path,video_saturation,video_luminance,video_contrast,lyric,culture_code,preview_path,singer_id1,singer_id2,singer_id3,singer_id4,file_version from top_song",
		36
};

//歌曲条件
query_condition song_query_condition[SONG_CONDITION_NUMS] = {
	{L"song_id",L"=\"",L"",L"\""},
	{L"spell_first_letter_abbreviation",L"like \"",L"",L"%\""},
	{L"spell_first_letter_traditional",L"like \"",L"",L"%\""},
	{L"moive_spell_first_letter",L"like \"",L"",L"%\""},
	{L"song_name_word_count",L"=",L"",L""},
	{L"song_name",L"like \"",L"",L"%\""},
	{L"word_head_code",L"like \"",L"",L"%\""},
	{L"language",L"=\"",L"",L"\""},
	{L"first_word_stroke_number",L"=",L"",L""},
	{L"song_theme",L"=\"",L"",L"\""},
	{L"new_song_date",L">",L"",L""},
	{L"issue_year",L">",L"",L""},
	{L"sing_number",L">",L"",L""},
	{L"singer_name",L" like \"%",L"",L"%\""},
	{L"song_version",L"=\"",L"",L"\""},
	{L"member_name",L"=\"",L"",L"\""},
	{L"song_type",L"=\"",L"",L"\""},
	{L"new_song_theme",L"=\"",L"",L"\""},
	{L"singer_sex",L"=\"",L"",L"\""},
	{L"singer_id1",L"=\"",L"",L"\""},
	{L"file_format",L"=\"",L"",L"\""},
	{L"song_name_sort",L"=\"",L"",L"\""},
	{L"local_path",L"=\"",L"",L"\""},
};

//歌曲条件副本
query_condition song_query_condition_copy[PAGE_MAX_NUMBER][SONG_CONDITION_NUMS];


//歌星
select_expr singer_select_expr={
	L"singer_id,singer_name,singer_sex,singer_region,singer_region_new,popular_singer,spell_first_letter_abbreviation,singer_name_word_count,singer_hot_rank,singer_introduction",
	10,
	L"select count(singer_name) from singer",
	L"select singer_id,singer_name,singer_sex,singer_region_new from singer",
	4
};

//歌星条件
query_condition singer_query_condition[] = {
	{L"singer_name",L" like \"",L"",L"%\""},
	{L"singer_region",L"=\"",L"",L"\""},
	{L"popular_singer",L"=\"",L"",L"\""},
	{L"spell_first_letter_abbreviation",L" like \"",L"",L"%\""},
	{L"singer_name_word_count",L"=",L"",L""},
	{L"singer_introduction",L"=",L"",L""},
	{L"singer_sex",L"=\"",L"",L"\""},
	{L"singer_id",L"!=\"",L"",L"\""},
};

//歌星条件副本
query_condition singer_query_condition_copy[PAGE_MAX_NUMBER][SINGER_CONDITION_NUMS];

//录音
select_expr song_recorder_select_expr={
	L"song_id,song_name,singer_name,video_path,culture_code,wave_path,start_time,datetime,score",
	9,
	L"select count(song_id) from song_recorder",
	L"select song_id,song_name,singer_name,video_path,culture_code,wave_path,start_time,datetime,score from song_recorder",
	9
};

//电影
select_expr movie_select_expr={
	L"id,name,volume,region,story,name_word_count,spell_first_letter_abbreviation,file_format,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,movie_relative_path,video_saturation,video_luminance,video_contrast,culture_code,issue_datetime",
	//L"id,name,volume,region,story,name_word_count,spell_first_letter_abbreviation,/*spell_first_letter_traditional,*/file_format,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,movie_relative_path,video_saturation,video_luminance,video_contrast,culture_code,issue_datetime",
	22,
	L"select count(id) from movie",
	L"select id,name,volume,region,story,file_format,local_path,server_path1,server_path2,server_path3,server_path4,server_path5,server_path6,movie_relative_path,video_saturation,video_luminance,video_contrast,culture_code from movie",
	18,
};

//电影查询条件
query_condition movie_query_condition[] ={
	{L"story",L"=",L"",L""},
	{L"name",L" like \'",L"",L"%\'"},
	{L"name_word_count",L"=",L"",L""},
	{L"spell_first_letter_abbreviation",L" like \"",L"",L"%\""},
	{L"spell_first_letter_traditional",L" like \"",L"",L"%\""},
};

//电影条件副本
query_condition movie_query_condition_copy[PAGE_MAX_NUMBER][MOVIE_CONDITION_NUMS];

//游戏
select_expr game_select_expr={
	L"id,name,path",
	3,
	L"select count(*) from game",
	L"select id,name,path from game",
	3,
};

//会员
select_expr member_select_expr={
	L"name,password",
	2,
	L"select count(*) from member",
	L"select name,password from member",
	2,
};

//会员查询条件
query_condition member_query_condition[]=
{
	{L"name",L"=\"",L"",L"\""},
	{L"password",L"=\"",L"",L"\""},
};

//已唱歌曲
select_expr sing_song_expre={
	L"song_id,sing_count",
	2,
	L"select count(*) from sing_song",
	L"select song_id,sing_count from sing_song",
	2,
};

//已选歌曲查询条件
query_condition sing_song_query_condition[]=
{
	{L"song_id",L"=\"",L"",L"\""},
};

//测机歌曲查询条件
query_condition test_song_query_condition[]=
{
	{L"song_id",L"=\"",L"",L"\""},
};

#endif