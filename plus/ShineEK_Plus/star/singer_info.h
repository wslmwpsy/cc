#pragma once


#include <string>
using namespace std;


class singer_info
{
public:
	singer_info(void);
	~singer_info(void);
	//��ֵ
	bool set_singer_name(const TCHAR *value);
	bool set_singer_region(const TCHAR *value);
	bool set_singer_sex(const TCHAR *value);
	bool set_singer_id(const TCHAR *value);

	//�õ�����ֵ
	bool get_singer_name(TCHAR *value);
	bool get_singer_region(TCHAR *value);
	bool get_singer_sex(TCHAR *value);
	bool get_singer_id(TCHAR *value);

	//��ʼ������
    void initialized_variables(void);
private:
	TCHAR singer_name[256];            //���ǵ�����
	TCHAR singer_region[256];          //���ǵ�����
	TCHAR singer_sex[256];             //�����Ա�
	TCHAR singer_id[256];              //����id
};
