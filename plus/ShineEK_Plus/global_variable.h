#ifndef _GLOBAL_VARIABLE_H_
#define _GLOBAL_VARIABLE_H_

#include "ministry_of_culture/ccddt.h"
#include "ministry_of_culture/VodADInterface.h"
#include "common/init_socket.h"
#include "dog/watch_dog.h"
#include "message.h"
#include "PluginsEx.h"

//��ʼ��socket
CInitSocket g_init_socket;


//dog
watch_dog m_watch_dog;                           //���ܹ���
long dog_valid_time=0;                           //���ܹ�����Ч��
const double check_dog_time_interval=1200.0;     //�����ܹ���ʱ����
const int DOG_SERVER_PORT=7077;                  //������ʹ�õĶ˿ں�
const long DOG_SERVER_SOCKET_TIME_OUT=1000000;   //����������ӳ�ʱ
const int DOG_SERVER_MAX_ERROR_LINK_NUMBER=6;    //�������������������
const TCHAR SOFTWARE_MODULE_NUMBER[] = L"0010";  //�����ģ����  0010
const TCHAR CONTROL_MODULE_NUMBER[] = L"1001";   //�ؼ���ģ����
const TCHAR GAME_MODULE_NUMBER[] = L"5678";      //������Ϸ��ģ���� 5678
const TCHAR CULTURE_SOFTWARE_MODULE_NUMBER[]=L"9010"; //�Ļ��������ģ����9010
const TCHAR SCORE_MODULE_NUMBER[] = L"5666";     //����ģ����


DOG_FUNCTION g_dog_open_function; //���ܹ��򿪵Ĺ���
USER_INFOR user_infor;            //�û���Ϣ
SELL_INFOR sell_infor;            //������Ϣ
TCHAR g_dog_serial_num[16] = {0x00}; //���ܹ����к�

//ǰ�û��ı���
enum PRECOMPUTER_SEND_TYPE
{
	VIDEO_TYPE,     //��Ƶ��Ϣ
	PC_TEXT_TYPE,   //�㲥�ն˵�����
	TV_TEXT_TYPE,   //�����ն˵�����
	PC_BK_TYPE,     //�㲥�ն˵ı������
	PC_LOGO_TYPE,   //�㲥�ն˵�logo
	TV_LOGO_TYPE,   //�����ϵ�logo
	SCREEN_SAVER_TYPE,//�������
	PROMPT_BOX_TYPE,  //��Ϣ��ʾ��
};

struct forbidsong **forbid_song_list=NULL;     //��ֹ���Ÿ����б�
bool send_video_play_recorder=false;           //������Ƶ�㲥��¼
bool send_pc_text_play_recorder=false;         //���͵㲥�ն˵����ּ�¼
bool send_tv_text_play_recorder=false;         //���͵����ն˵����ּ�¼
bool send_pc_BK_play_recorder=false;           //���͵㲥�ն˱�����¼
bool send_pc_logo_play_recorder=false;         //���͵㲥�ն�logo��¼
bool send_tv_logo_play_recorder=false;         //���͵����ն�logo��¼
bool send_screen_saver_play_recorder=false;    //����������¼
bool send_prompt_box_play_recorder=false;      //������Ϣ��ʾ���¼

//Ҫ���͸�ǰ�û�����Ϣ
//ÿ���ṹ�����ĺ��壺
//0����Ƶ��Ϣ
//1���㲥�ն˵�����
//2�������ն˵�����
//3���㲥�ն˵ı������
//4���㲥�ն˵�logo
//5�������ϵ�logo
//6���������
//7����Ϣ��ʾ��
SEND_PRECOMPUTER_MSG send_precomputer_msg[8];  //Ҫ���͸�ǰ�û�����Ϣ
struct pwktvmsg *send_ktv_msg[8];              //Ҫ���͸�ǰ�û��Ĳ�����Ϣ

//culture  ad
bool play_culture_video_ad=false;                      //�����Ļ�������Ƶ���

AD_ITEM_CULTURE *culture_video_ad = NULL;              //�Ļ�������Ƶ���
AD_ITEM_CULTURE *culture_pc_text_ad=NULL;              //�Ļ����ĵ���ն˵����ֹ��
AD_ITEM_CULTURE *culture_tv_text_ad=NULL;              //�Ļ����ĵ����ն˵����ֹ��
AD_ITEM_CULTURE *culture_pc_background_ad=NULL;        //�Ļ����ĵ㲥�ն��ϵı������
AD_ITEM_CULTURE *culture_pc_logo_ad=NULL;              //�Ļ����ĵ㲥�ն��ϵ�logo���
AD_ITEM_CULTURE *culture_tv_logo_ad=NULL;              //�Ļ����ĵ����ϵ�logo���
AD_ITEM_CULTURE *culture_screen_saver_ad=NULL;         //�Ļ������������
AD_ITEM_CULTURE *culture_prompt_box_ad=NULL;           //�Ļ�������ʾ��Ϣ��


HANDLE m_assistant_thread_event_handle=NULL;                            //�����߳̽������¼����

FLASH_USE_LANGUAGE g_flash_use_language;          //flashʹ�õ�����
SEND_BACK_SERVER_MSG_TYPE g_back_server_msg_type; //���͸���̨����������Ϣ����

typedef std::map<CString, song_info> STRING_SONGINFO_MAP; //����map��key��string val��song_info-------By_v.cai_2015/02/15 09:16

#endif