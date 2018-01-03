#pragma once


/*--------��ɫ��ڵ�ṹ����------------------------------*/
typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char reserved;
}RGB_QUAD;

/*--------�����ڵ�ṹ����--------------------------------*/
typedef struct  INDEXTABLENODE
{
	unsigned char node;
	struct INDEXTABLENODE* next;
}INDEX_TABLE_NODE;


class rgb_conv
{
public:
	rgb_conv(void);
	~rgb_conv(void);

	/*-----------------------------------------------------------------------
	*����trans: ����: ʵ��32bitsλͼ��8bits(256ɫ)λͼת��.
	*           ����:
	*           ����ֵ: = 0 ת���ɹ�.
	*                   = 1 ת��ʧ��.
	*-----------------------------------------------------------------------*/
	int rgb32torgb8(TCHAR *rgb32_path,TCHAR *rgb8_path);
	/*---------------------------------------------------------------/
	* ����get_index : ���� : �ɽڵ�rgbֵ���ص�ɫ������
	*                 ���� : unsigned char  r, g, b,����ѯ����rgbֵ
	*                 ���� : �ɹ����ص�ɫ������,���򷵻�0
	*---------------------------------------------------------------*/
	unsigned char get_index(unsigned char r, unsigned char g, unsigned char b);
};
