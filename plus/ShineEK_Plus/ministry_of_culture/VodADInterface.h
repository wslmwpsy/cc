#ifndef _VODADINTERFACE_H_
#define _VODADINTERFACE_H_

#include "..\\stdafx.h"

//��ʾ�豸�궨��
#define DISPLAY_DEVICE_TV    1  //TV �ն�
#define DISPLAY_DEVICE_PC    2  //pc�ն�
//�������������Ͷ���
#define SCENE_POWER_ON       1  //�������
#define SCENE_INTER_MODE     2  //�岥
#define AD_TYPE_CAPTION      3  //����
#define AD_TYPE_LOGO         4  //LOGO
#define AD_TYPE_HELP_MODE    5  //��ʾ��Ϣ��
#define AD_TYPE_BACK_MODE    6  //����
#define AD_TYPE_SAFE_MODE    7  //����

//��ĿԴ����
#define AD_TYPE_VIDEO        1  //��Ƶ
#define AD_TYPE_PICTURE      2  //ͼƬ
//#define AD_TYPE_CAPTION      3  //����
//#define AD_TYPE_LOGO         4  //LOGO
//#define AD_TYPE_HELP_MODE    5  //��ʾ��Ϣ��

//�岥��ʱ���
#define SCENE_INTER_HASSONG    1 //�п��˵���״̬��
#define SCENE_INTER_IDLE       2 //����״̬��

typedef struct AD_IIEM_FLAG_C
{
	unsigned int nTypename_id;  //��ĿԴ���ͱ��	
	char szCode_id[16];         //��ĿԴ���
	unsigned int nLength;       //�ļ�����
	unsigned int nTime_len;     //ʱ��
	char szRemark[256];         //��ע
	char szFilePath[256];       //file Path
	char szType_code[8];        //���ͱ��
	int nSwitch_time;           //���ʱ��
	int nDisp_time;             //��ʾʱ��
}AD_ITEM_CULTURE;


/*
���ܣ���ʼ�����ϵͳ�������һ�����á�
������
����ֵ��
�ɹ���1��
ʧ�ܣ�-1;
*/
extern "C" long __stdcall InitADSystem_culture();

/*
���ܣ�֪ͨ���ϵͳ�ͷ����з������Դ���ڵ��ϵͳ�˳�ǰ����һ��
������
����ֵ��
�ɹ���1��
ʧ�ܣ�-1;
*/
//int UninitADSystem();
extern "C" long __stdcall UninitADSystem_culture();

/*
���ܣ����ϵͳ���ô˽ӿڻ�ȡһ�������
������
nDisplayDevice:��ʾ�豸�������ն�:1  �㲥�ն�:2
nSceneADType���������沥�����͡�������棺1 �岥��2 ���֣�3 Logo��4 ��ʾ��Ϣ��5 ������6 ������7
pItem��ָ�򱣴�������Ϣ�Ļ�������
nInterTime��ֻ���ڲ岥ģʽ�²������á�1���п��˵���״̬�£�2������ʱ���

����ֵ��
�ɹ���1 ���������pItem==NULL,����ֵ�ǽṹ��AD_ITEMռ�Ļ������Ĵ�С�����ֽڼ��㣩
ʧ�ܣ�-1
û�й�沥�ţ�0
*/
extern "C" long __stdcall get_ADItem_culture(long nDisplayDevice,long nSceneADType,AD_ITEM_CULTURE** pItem,int nInterTime);

#endif