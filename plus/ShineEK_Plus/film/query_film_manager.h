#include <string>
#include "../dbsql/DbSQL.h"

//每页显示电影数量
const int FILM_PAGE_ROW_COUNT		= 6;

//电影类型(多选项，位移存储)
enum FILM_TYPE
{
	ALL_TYPE	= 0,		//全部
	AIQING		= 1,		//爱情
	XIJU		= 2,		//喜剧
	DONGZUO		= 4,		//动作
	KONGBU		= 8,		//恐怖
	LUNLI		= 16,		//伦理
	XUANYI		= 32,		//悬疑
	KEHUAN		= 64,		//科幻
	FANZUI		= 128		//犯罪
};

//电影地区（单选项）
enum FILM_COUNTRY
{
	ALL_COUNTRY	= 0,		//全部
	NEIDI		= 1,		//内地
	XIANGGANG	= 2,		//香港
	TAIWAN		= 3,		//台湾
	MEIGUO		= 4,		//美国
	OUZHOU		= 5,		//欧洲
	HANGUO		= 6,		//韩国
	RIBEN		= 7,		//日本
	TAIGUO		= 8,		//泰国
	QITA		= 999		//其他
};

//电影排序
enum FILM_ORDER_BY
{
	DEFAULT		= 0,		//默认排序
	NAME		= 1,		//按影片名称
	SCORE		= 2,		//按评分排序
	DATETIME	= 4			//按上映时间
};

typedef struct tag_FilmInfo
{
	std::wstring str_film_id;
	std::wstring str_film_name;
	std::wstring str_film_aliases;				//电影别名    保留
	std::wstring str_film_name_english;
	std::wstring str_film_datetime;
	int			 n_film_time_len;
	FILM_COUNTRY n_film_country;
	std::wstring str_film_name_spell;
	std::wstring str_film_aliases_spell;
	std::wstring str_film_english_name_spell;
	std::wstring str_film_name_spell_traditional;
	int			 n_film_name_count;
	FILM_TYPE	 n_film_type;					//电影类型(剧情、惊悚、爱情、预告片等)
	int			 n_film_rank;
	float		 f_film_price;
	int			 n_film_status;					//电影状态 (正在热映、停播、即将上映等)
	std::wstring str_film_poster;
	std::wstring str_film_poster_small;
	int			 n_film_total_score;
	std::wstring str_film_remark;
	std::wstring str_file_introduction;
	std::wstring str_film_actor_list;			//电影演员列表,多个演员用”;”区分.饰用”:”(如 “12345:叶雯雯;” 高圆圆饰叶雯雯)
	std::wstring str_film_issuing_company;
	std::wstring str_film_trailer_list;			//预告片列表,使用film_id表示并”;”隔开(如”123;234;456”)
	std::wstring str_film_share_url;
	std::wstring str_film_director;
	int			 n_film_track;
	std::wstring str_film_caption;
	std::wstring str_file_format;
	int			 n_resolution;					//清晰度（0标清,1高清,2超清,3蓝光）
	int			 n_volume;						//默认音量（0-100）
	std::wstring str_server_path1;
	std::wstring str_server_path2;
	std::wstring str_server_path3;
	std::wstring str_movie_relative_path;
	std::wstring str_datetime;
}FILMINFO,*PFILMINFO;

typedef struct tag_ActorInfo
{
	std::wstring str_actor_id;
	std::wstring str_actor_name;
	int			 n_actor_type;				//演员类型( 0:导演 1:主演 2:普通演员 3:编剧等)
	int			 n_actor_region;
	std::wstring str_actor_picture;
	std::wstring str_actor_introduction;
	std::wstring str_actor_name_spell;
	int			 n_actor_name_count;
	int			 n_actor_sex;
	int			 n_actor_popular;
}ACTORINFO,*PACTORINFO;

typedef struct tag_ActroItem{
	std::wstring str_name;
	std::wstring str_act_the_part;
}ACTORITEM,*PACTORITEM;

class query_film_manager
{
public:
	query_film_manager(void);
	~query_film_manager(void);

public:
	//初始化
	void Init(Db_sql *connect);
	//查询电影
	bool get_film(std::wstring &xml);
	//电影详情
	bool get_film_detail(std::wstring &xml);
	//返回页码总数
	bool get_film_count(int &count,int &page);
	//返回电影信息
	access_record_set_sql * get_film_by_id(const TCHAR* film_id);

	//查询条件
public:
	FILM_TYPE		m_encodation_type;		//电影类型(多选项，位移存储)
	FILM_COUNTRY	m_encodation_country;	//电影地区（单选项）
	FILM_ORDER_BY	m_encodation_orderby;	//电影排序
	std::wstring	m_strcodation_keyword;	//
	int				m_npage_index;			//
	std::wstring	m_strfilm_id_current;	//电影id
private:
	//拼接sql的where字符串
	void append_condition_sql(TCHAR *szBuffer,TCHAR *sql,const TCHAR* condition);
	//生成sql条件
	void MakeWhereSql();
	//输出xml文件
	void MakeMoviesXml(std::wstring &xml,access_record_set_sql *record,int row_index);
public:
	//读取字段
	CString read_field(access_record_set_sql *record,TCHAR* szFieldName);
	//电影类型转换字符串
	CString FilmTypeToString(FILM_TYPE type);
	//电影地区转换字符串
	CString FilmCountryToString(FILM_COUNTRY type);
	//演员id转换字符串
	CString ActorToString(CString actor);
	//电影好评
	bool PraiseFile(void);
	//电影播放次数
	bool PlayCount(void);
private:
	Db_sql *m_mssql;
	TCHAR m_szWhere[10240];
};