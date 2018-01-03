#ifndef _DB_DATA_TYPE_DEF_H_
#define _DB_DATA_TYPE_DEF_H_

#include <string>

using namespace std;

//��ѯ����ѡ����ʽ
typedef struct DB_SELECT_EXPRESSION 
{
	std::wstring all_column_expr; //�����ֶ�
	int all_column_number;        //��������
	std::wstring row_count_expr;  //��ѯ�����ı��ʽ
	std::wstring result_column_expr;//ѡ��Ľ���ֶα��ʽ
	int result_column_nums;         //ѡ��Ľ�����ֶ���
}select_expr;


//��ѯ�����Ľṹ��
typedef struct DB_QUERY_CONDITION 
{
	std::wstring column_name; //�����е����֣��ֶ���
	std::wstring operation_symbols; //��������= like > <����Щ����Ҫ�ӷֺŵ�
	std::wstring expression; //���������ʽ
	std::wstring wildcard;   //ͨ���

}query_condition;

//������������
#define SONG_CONDITION_NUMS   23


//��������������±�
enum SONG_CONDITION_SUFFIX
{
	SONG_ID_SUFFIX,                                    //id��ѯ
	SPELL_FIRST_LETTER_ABBREVIATION_SUFFIX,//����ĸ
	SPELL_FIRST_LETTER_TRADITIONAL_SUFFIX,
	MOIVE_SPELL_FIRST_LETTER_SUFFIX,
	SONG_NAME_WORD_COUNT_SUFFIX,  //��������
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

//������������
#define SINGER_CONDITION_NUMS  8

//�����������±�
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

//��Ӱ��������
#define MOVIE_CONDITION_NUMS 5

//��Ӱ�������±�
enum MOVIE_CONDITION_SUFFIX
{
	MOVIE_STORY_SUFFIX,
	MOVIE_NAME_SUFFIX,
	MOVIE_WORD_COUNT_SUFFIX,
	MOVIE_SFSA_SUFFIX,
	MOVIE_SFLT_SUFFIX,
};

//��Ա����������
#define MEMBER_CONDITION_NUMS 2
//��Ա�������±�
enum MEMBER_CONDITION_SUFFIX
{
	NAME_SUFFIX,
	PASSWORD_SUFFIX,
};

//�ѳ�������������
#define SING_SONG_CONDITION_NUMS 1
//�ѳ������������±�
enum SING_SONG_CONDITION_SUFFIX
{
	SING_SONG_ID,
};

//���Ը�����������
#define TEST_SONG_CONDITION_NUMS 1
//�ѳ������������±�
enum TEST_SONG_CONDITION_SUFFIX
{
	TEST_SONG_ID_SUFFIX,
};


#endif