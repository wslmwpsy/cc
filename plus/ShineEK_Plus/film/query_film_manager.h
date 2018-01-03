#include <string>
#include "../dbsql/DbSQL.h"

//ÿҳ��ʾ��Ӱ����
const int FILM_PAGE_ROW_COUNT		= 6;

//��Ӱ����(��ѡ�λ�ƴ洢)
enum FILM_TYPE
{
	ALL_TYPE	= 0,		//ȫ��
	AIQING		= 1,		//����
	XIJU		= 2,		//ϲ��
	DONGZUO		= 4,		//����
	KONGBU		= 8,		//�ֲ�
	LUNLI		= 16,		//����
	XUANYI		= 32,		//����
	KEHUAN		= 64,		//�ƻ�
	FANZUI		= 128		//����
};

//��Ӱ��������ѡ�
enum FILM_COUNTRY
{
	ALL_COUNTRY	= 0,		//ȫ��
	NEIDI		= 1,		//�ڵ�
	XIANGGANG	= 2,		//���
	TAIWAN		= 3,		//̨��
	MEIGUO		= 4,		//����
	OUZHOU		= 5,		//ŷ��
	HANGUO		= 6,		//����
	RIBEN		= 7,		//�ձ�
	TAIGUO		= 8,		//̩��
	QITA		= 999		//����
};

//��Ӱ����
enum FILM_ORDER_BY
{
	DEFAULT		= 0,		//Ĭ������
	NAME		= 1,		//��ӰƬ����
	SCORE		= 2,		//����������
	DATETIME	= 4			//����ӳʱ��
};

typedef struct tag_FilmInfo
{
	std::wstring str_film_id;
	std::wstring str_film_name;
	std::wstring str_film_aliases;				//��Ӱ����    ����
	std::wstring str_film_name_english;
	std::wstring str_film_datetime;
	int			 n_film_time_len;
	FILM_COUNTRY n_film_country;
	std::wstring str_film_name_spell;
	std::wstring str_film_aliases_spell;
	std::wstring str_film_english_name_spell;
	std::wstring str_film_name_spell_traditional;
	int			 n_film_name_count;
	FILM_TYPE	 n_film_type;					//��Ӱ����(���顢��㤡����顢Ԥ��Ƭ��)
	int			 n_film_rank;
	float		 f_film_price;
	int			 n_film_status;					//��Ӱ״̬ (������ӳ��ͣ����������ӳ��)
	std::wstring str_film_poster;
	std::wstring str_film_poster_small;
	int			 n_film_total_score;
	std::wstring str_film_remark;
	std::wstring str_file_introduction;
	std::wstring str_film_actor_list;			//��Ӱ��Ա�б�,�����Ա�á�;������.���á�:��(�� ��12345:Ҷ����;�� ��ԲԲ��Ҷ����)
	std::wstring str_film_issuing_company;
	std::wstring str_film_trailer_list;			//Ԥ��Ƭ�б�,ʹ��film_id��ʾ����;������(�硱123;234;456��)
	std::wstring str_film_share_url;
	std::wstring str_film_director;
	int			 n_film_track;
	std::wstring str_film_caption;
	std::wstring str_file_format;
	int			 n_resolution;					//�����ȣ�0����,1����,2����,3���⣩
	int			 n_volume;						//Ĭ��������0-100��
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
	int			 n_actor_type;				//��Ա����( 0:���� 1:���� 2:��ͨ��Ա 3:����)
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
	//��ʼ��
	void Init(Db_sql *connect);
	//��ѯ��Ӱ
	bool get_film(std::wstring &xml);
	//��Ӱ����
	bool get_film_detail(std::wstring &xml);
	//����ҳ������
	bool get_film_count(int &count,int &page);
	//���ص�Ӱ��Ϣ
	access_record_set_sql * get_film_by_id(const TCHAR* film_id);

	//��ѯ����
public:
	FILM_TYPE		m_encodation_type;		//��Ӱ����(��ѡ�λ�ƴ洢)
	FILM_COUNTRY	m_encodation_country;	//��Ӱ��������ѡ�
	FILM_ORDER_BY	m_encodation_orderby;	//��Ӱ����
	std::wstring	m_strcodation_keyword;	//
	int				m_npage_index;			//
	std::wstring	m_strfilm_id_current;	//��Ӱid
private:
	//ƴ��sql��where�ַ���
	void append_condition_sql(TCHAR *szBuffer,TCHAR *sql,const TCHAR* condition);
	//����sql����
	void MakeWhereSql();
	//���xml�ļ�
	void MakeMoviesXml(std::wstring &xml,access_record_set_sql *record,int row_index);
public:
	//��ȡ�ֶ�
	CString read_field(access_record_set_sql *record,TCHAR* szFieldName);
	//��Ӱ����ת���ַ���
	CString FilmTypeToString(FILM_TYPE type);
	//��Ӱ����ת���ַ���
	CString FilmCountryToString(FILM_COUNTRY type);
	//��Աidת���ַ���
	CString ActorToString(CString actor);
	//��Ӱ����
	bool PraiseFile(void);
	//��Ӱ���Ŵ���
	bool PlayCount(void);
private:
	Db_sql *m_mssql;
	TCHAR m_szWhere[10240];
};