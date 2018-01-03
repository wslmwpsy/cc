#ifndef _SINGER_VARIABLE_H_
#define _SINGER_VARIABLE_H_

//#define SINGER_PAGE_SHOW_ROW_COUNT 8

#ifdef DON_GUAN_K_PLUS
static int singer_page_show_row_count = 8; 
#else
static int singer_page_show_row_count = 10; 
#endif // DON_GUAN_K_PLUS

#define SINGER_PAGE_SHOW_ROW_COUNT_MAX 10

//������ʾ��ҳ��
#define SINGER_SCREEN_SHOW_PAGE_COUNT 3

//�����������ж���ҳ����
enum SINGER_PAGE_FLAG
{
	SINGER_NO_PAGE=0,           //û�в�ѯ����������������
	SINGER_ONE_PAGE,          //ֻ��һҳ����
	SINGER_TWO_PAGE,          //��ҳ����
	SINGER_THREE_PAGE,       //��ҳ����
};

//���ǵĹ�����
enum SINGER_REGION
{
	MAINLAND_MALE=1,  //��½�и���
	MAINLAND_FEMALE,//��½Ů����
	HK_TAIWAN_MALE, //��̨�и���
	HK_TAIWAN_FEMALE,//��̨Ů����
	CONCERT_PORTFOLIO,//�ݳ����
	FOREIGN_SINGER,  //�������
	POPULAR_SINGER, //���Ÿ���
	ALL_SINGER,     //ȫ������
	// -- add by cai : ���ӻ��ˡ�ŷ�����������ձ���������ȫ��(���ˡ�ŷ�����������ձ�������) [9/24/2014 syrusn]
	CHINESE,		//����
	EUROPE_AMERICA, //ŷ��
	KOREA,			//����
	JAPAN,			//�ձ�
	OTHER,			//����
};

#endif