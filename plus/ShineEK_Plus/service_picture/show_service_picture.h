#pragma once
#include <string>
#define MAX_SERVICE_PICTURE_COUNT 50

enum SERVICE_PICTRUE_PAGE_OPERATE
{
	SERVICE_PICTRUE_CUR_PAGE,  //��ǰҳ
	SERVICE_PICTRUE_PRE_PAGE,  //����ͼƬ����һҳ
	SERVICE_PICTRUE_NEXT_PAGE, //����ͼƬ����һҳ
};

//��ʾ����ͼƬ����
class show_service_picture
{
public:
	show_service_picture(void);
	~show_service_picture(void);
	/*
	���ܣ���ʼ��
	������
	    path��ͼƬ�ļ���·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool initiate(TCHAR *path);

	/*
	���ܣ��õ�Ҫ��ʾ��ͼƬ·��
	������
	    page_operate��ҳ����
		path���õ����ļ�·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_show_picture(SERVICE_PICTRUE_PAGE_OPERATE page_operate,TCHAR *path);
	bool get_show_picture(SERVICE_PICTRUE_PAGE_OPERATE page_operate,std::wstring &picture_list_xml);

	/*
	���ܣ��õ��ܵ�ҳ���͵�ǰҳ��
	������
	    total_page_count���ܵ�ҳ��
		show_page_number����ʾ��ҳ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_page_info(int &total_page_count, int &show_page_number);

	/*
	���ܣ�����Ҫ��ʾ��ҳ
	������
	    page_number��ҳ��
	����ֵ��
	   void
	*/
	void set_show_page_number(int page_number);


private:
	TCHAR m_picture_path[MAX_SERVICE_PICTURE_COUNT][256]; //ͼƬ·��
	int m_total_picture_count;     //�ܵ�ͼƬ��
	int m_cur_show_picture_number; //��ǰ������ʾ��ͼƬ��� ,��1��ʼ
};
