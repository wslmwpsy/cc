#ifndef _DB_DATA_TYPE_DEF_H_
#define _DB_DATA_TYPE_DEF_H_

#include <string>

using namespace std;

//查询语句的选择表达式
typedef struct DB_SELECT_EXPRESSION 
{
	std::wstring all_column_expr; //所有字段
	int all_column_number;        //所有列数
	std::wstring row_count_expr;  //查询行数的表达式
	std::wstring result_column_expr;//选择的结果字段表达式
	int result_column_nums;         //选择的结果列字段数
}select_expr;


//查询条件的结构体
typedef struct DB_QUERY_CONDITION 
{
	std::wstring column_name; //表中列的名字，字段名
	std::wstring operation_symbols; //操作符，= like > <，有些还需要加分号等
	std::wstring expression; //条件，表达式
	std::wstring wildcard;   //通配符

}query_condition;

//歌曲条件总数
#define SONG_CONDITION_NUMS   23


//上面歌曲条件的下标
enum SONG_CONDITION_SUFFIX
{
	SONG_ID_SUFFIX,                                    //id查询
	SPELL_FIRST_LETTER_ABBREVIATION_SUFFIX,//首字母
	SPELL_FIRST_LETTER_TRADITIONAL_SUFFIX,
	MOIVE_SPELL_FIRST_LETTER_SUFFIX,
	SONG_NAME_WORD_COUNT_SUFFIX,  //歌曲字数
	SONG_NAME_SUFFIX,
	WORD_HEAD_CODE_SUFFIX,
	LANGUAGE_SUFFIX,
	FIRST_WORD_STROKE_NUMBER_SUFFIX,
	SONG_THEME_SUFFIX,
	NEW_SONG_DATA_SUFFIX,
	ISSUE_YEAR_SUFFIX,
	SING_NUMBER_SUFFIX,
	SINGER_NAME_SUFFIX,
	SONG_VERSION_SUFFIX,
	MEMBER_NAME_SUFFIX,
	SONG_TYPE_SUFFIX,
	NEW_SONG_THEME_SUFFIX,
	SINGER_SEX_SUFFIX,
	SINGER_ID1_STUFFIX,
	FILE_FORMAT_SUFFIX,
	SONG_NAME_SORT_SUFFIX,
	SONG_LOCAL_PATH_SUFFIX,
};

//歌星条件总数
#define SINGER_CONDITION_NUMS  8

//歌星条件的下标
enum SINGER_CONDITION_SUFFIX
{
	SINGER_TABLE_NAME_SUFFIX,
	SINGER_REGION_SUFFIX,
	POPULAR_SINGER_SUFFIX,
	SPELL_FIRST_LETTER_ABBREVIATION,
	SINGER_NAME_WORD_COUNT_SUFFIX,
	SINGER_INTRODUCTION_SUFFIX,
	SINGER_SEX_SUBSCRIPT,
	SINGER_ID_SUFFIX,
};

//电影条件总数
#define MOVIE_CONDITION_NUMS 5

//电影条件的下标
enum MOVIE_CONDITION_SUFFIX
{
	MOVIE_STORY_SUFFIX,
	MOVIE_NAME_SUFFIX,
	MOVIE_WORD_COUNT_SUFFIX,
	MOVIE_SFSA_SUFFIX,
	MOVIE_SFLT_SUFFIX,
};

//会员的条件总数
#define MEMBER_CONDITION_NUMS 2
//会员条件的下标
enum MEMBER_CONDITION_SUFFIX
{
	NAME_SUFFIX,
	PASSWORD_SUFFIX,
};

//已唱歌曲的条件数
#define SING_SONG_CONDITION_NUMS 1
//已唱歌曲的条件下标
enum SING_SONG_CONDITION_SUFFIX
{
	SING_SONG_ID,
};

//测试歌曲的条件数
#define TEST_SONG_CONDITION_NUMS 1
//已唱歌曲的条件下标
enum TEST_SONG_CONDITION_SUFFIX
{
	TEST_SONG_ID_SUFFIX,
};


#endif