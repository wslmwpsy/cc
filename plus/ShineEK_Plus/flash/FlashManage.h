#pragma once

#include "../message.h"

#include <vector>
using namespace std;

class CFlashManage
{
public:
	CFlashManage(void);
	~CFlashManage(void);

	/*
	���ܣ�ҳ��ı�
	������
		request:���صĽ��
		array_size�����ؽ���������С
	    page_id:ҳ���ID
		language��ʹ�õ�����
	����ֵ��
	    true:�ɹ�
		false:ʧ��
	*/
	bool page_change(TCHAR *request,int array_size,int page_id,int language,FLASH_SONG_SHOW_MODE song_show_mode);

	/*
	���ܣ���¼ҳ������
	������
		page_index��ҳ������
	����ֵ��
		true:�ɹ�
		false��ʧ��
	*/
	bool write_page_index(int page_index);
	/*
	���ܣ�������һ��ҳ������
	������
		NULL
	����ֵ��
		�ɹ�����һҳ��ҳ����
		��������ҳ��-1
	*/
	int get_pre_page_index();

	/*
	���ܣ��������ҳ������
	������
		NULL
	����ֵ��
		�ɹ������ҳ������
		��������ҳ��-1
	*/
	int get_last_page_index();

	/*
	���ܣ��õ�ҳ�������
	������
	    page_index��ҳ������
	    name��ҳ������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_page_name(int page_index,TCHAR *page_name,FLASH_SONG_SHOW_MODE song_show_mode);

	/*
	���ܣ���֯�ص��������ַ���
	������
		request�����صĽ��
		array_size�����ؽ���������С
		command:��������
		args������
		page_operate_type��ҳ��������
	����ֵ��
		true���ɹ�
		false:ʧ��
	*/
	bool make_request(TCHAR *request,int array_size,const TCHAR *command,const TCHAR *args);
	bool make_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type,FLASH_SONG_SHOW_MODE song_show_mode);
	bool make_singer_request(TCHAR *request,int array_size,const TCHAR *command,const TCHAR *args,bool refresh,int page_index,int page_operate_type);
	bool make_select_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type,FLASH_SONG_SHOW_MODE song_show_mode);
	bool make_recommend_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index);
	bool make_maiba_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type);
	bool make_maiba_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,const TCHAR* flagname,int page_operate_type);
	bool make_web_song_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index);
	bool make_music_enjoy_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type);
	bool make_trend_list_request(TCHAR *request,int array_size,const TCHAR *args,bool refresh,int page_index,int page_operate_type);

private:
	vector<int> screen_index;  //����������ҳ���������ڷ�����һҳ���洢��ҳ�����ܳ��� PAGE_MAX_NUMBER��
};
