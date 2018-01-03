#pragma once
#include "../message.h"


#include <string>
using namespace std;

//��Ա����
class memeber_song_manager
{
public:
	memeber_song_manager(void);
	~memeber_song_manager(void);

	//��ʼ������
	void initialized_variables(void);

	MEMBER_FLAG get_login_flags();  //�õ���Ա��¼��־
	bool get_user_name(TCHAR* value);
	bool get_user_password(TCHAR* value);
	bool get_user_sex(TCHAR* value);
	bool get_nick_name(TCHAR* value);
	bool get_user_head(TCHAR* value);
	bool get_user_identitycard(TCHAR* value);
	bool get_member_down_address(TCHAR* value);

	bool set_login_flags(int value);
	bool set_user_name(const TCHAR* value);
	bool set_user_password(const TCHAR* value);
	bool set_user_sex(const TCHAR* value);
	bool set_nick_name(const TCHAR* value);
	bool set_user_head(const TCHAR* value);
	bool set_user_identitycard(const TCHAR* value);

	int get_total_member_count();

	int get_total_member_page();

	int get_current_member_page();
	
	/*
		���ܣ����õ�ǰҳ��
		������
			page_operate:ҳ���ʾ
			page_number:����ҳ��
	*/
	void set_current_member_page(PAGE_OPERATE page_operate/*,int page_number*/);

	/*
		���ܣ�������Ա��Ϣ
		������
			recv_data:������������������
	*/
	bool parse_member_info(char *recv_data);

	/*
		���ܣ�������Ա������Ϣ
	*/
	bool parse_memeber_song_info(char* recv_data,std::wstring &song_id_list);

	/*
		���ܣ�������ͷ�������
		������
			down_addr:ͷ������ص�ַ 
	*/
	bool parse_memeber_head_picture_name(IN TCHAR* down_addr);

private:
 
	MEMBER_FLAG member_flags; //��Ա��־
	TCHAR user_name[256];  //��Ա������
	TCHAR user_password[256];  //��Ա����
	TCHAR user_sex[10];           //�Ա�
	TCHAR nick_name[256];      //�û��ǳ�
	TCHAR user_head[256];     //�û�ͷ��
	TCHAR user_identitycard[256];    //��Ա��Ψһid
	TCHAR member_down_address[256];   //��Աͷ�����ص�ַ
	TCHAR m_service_server_ip[256];   //������ip
	int m_member_song_total_count;   //��Ա����������
	int m_member_song_total_page;     //��Ա������ҳ��
	int m_member_current_page;       //��ǰҳ��
};

