#pragma once

#include "singer_variable.h"
#include "singer_info.h"

class query_singer_manager
{
public:
	query_singer_manager(void);
	~query_singer_manager(void);
	/*
	���ܣ��Ѳ�ѯ�����ֵ�������б�
	������
		query_song_result����ѯ�Ľ��
		result_item_number����ѯ�������ֶ���
		page_count:�ܹ���ҳ��
		cur_page_number����ǰҳ�ı��
	����ֵ��
	true���ɹ�
	false��ʧ��
	*/
	bool set_singer_list(std::wstring query_singer_result[],int result_item_number,int result_column_nums,int page_count,int cur_page_number);
	bool set_handheld_singer_list(std::wstring query_singer_result[],int result_item_number,int result_column_nums);

	/*
	���ܣ���֯��Ŀ����xml�ļ���flash����
	������
		song_list_xml����ɵĽ�Ŀ��xml��ʽ���ַ���
	����ֵ��
		true���ɹ�
		false:ʧ��
	*/
	bool make_singer_list_xml(std::wstring &singer_list_xml);
	/*
	���ܣ���ʼ������
	������
		NULL
	����ֵ��
		void
	*/
	void initialized_variables(void);
	/*
	���ܣ�ͨ���±�õ�ĳ�����ǵ���Ϣ
	������
	    suffix:�±�
	����ֵ��
	    singer_info�����ǵ���Ϣ��
	*/
	singer_info get_singer_info(int suffix);
	singer_info get_handheld_singer_info(int suffix);

	/*
	���ܣ��õ�����ͼƬ·��
	������
	    path������ͼƬ·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_star_picture_path(TCHAR *path);

	/*
	���ܣ�ͨ������������֯xml�ַ���
	������
	    singer_info_class��������Ϣ��
		picture_number�����ܵ�ͼƬ���
		singer_xml����֯�õĸ����ַ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool make_singer_xml_by_name(singer_info &singer_info_class,int picture_number,TCHAR *singer_xml);

	void set_singer_page_show_row_count(int count) {m_singer_page_show_row_count = count; }

private:
	//��ѯ�������ݳ�����Ϣ
	singer_info pre_page_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX];  //ǰһҳ
	singer_info cur_page_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX]; //��ǰҳ
	singer_info next_page_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX]; //��һҳ

	singer_info m_handheld_singer_list[SINGER_PAGE_SHOW_ROW_COUNT_MAX];  //�ֳ��õ�

	bool singer_list_exist;                    //�ݳ����б��Ƿ����
	TCHAR m_star_picture_path[256];            //����ͼƬ·��
	std::wstring m_singer_name_default_color;  //�������ֵ�Ĭ����ɫ

	int m_singer_page_show_row_count;

};
